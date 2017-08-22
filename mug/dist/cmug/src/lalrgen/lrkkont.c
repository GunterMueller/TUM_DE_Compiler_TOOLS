/*
 * (c) copyright 1989,1991 by Technische Universitaet Muenchen, Germany
 *
 *      This product is part of CMUG
 *      CMUG is a part of the compiler writing system
 *      MUG (Modularer Uebersetzer-Generator, TU Muenchen)
 *
 * Permission to use, duplicate or disclose this software must be
 * obtained in writing. Requests for such permissions may be sent to
 *
 *      Prof. Dr. J. Eickel
 *      Institut fuer Informatik
 *      Technische Universitaet Muenchen
 *      Postfach  20 24 20
 *      Arcisstr. 21
 *      D-8000 Muenchen 2
 *      Germany
 *
 * No version of this implementation may be used or distributed for gain,
 * all listings must contain our copyright notice, and the headings
 * produced by MUG-Modules must contain the text "MUG" and "TU - Muenchen".
 */


/* ********************************************************************** */
/* lrkkont.c   :                                                          */
/* LR(k)-Parser-Generator                                                 */
/* Modul : Generierung des Lookaheads (k > 1 noch nicht implementiert)    */
/* Aenderung :  16.12.90, Bug in getNext() beseitigt, der Weiterlesen     */
/*                        des Kontextes am Produktionsende verursachte    */
/* Aenderung :  06.11.89, groessere Anderungen in Aufrufstruktur ,        */
/*                        Parametern,... von getNext()                    */
/* Aenderung :  02.11.89, getNext() liefert Status ab, keine Rekursion    */
/* Aenderung :  29.10.89, kleinere Aenderungen zur Effizienzsteigerung    */
/*                        firstsym() eingesetzt in getNext()              */
/*                        lalr korrigiert durch azust-Parameter           */
/* erstellt  :  28.10.89, vorerst fuer k = 1                              */
/* ********************************************************************** */

#include <stdio.h>           /* E/A-Deklarationen                         */
#include "defs.h"            /* diverse unspezifische Definitionen        */
#include "dbg.h"             /* Routinen zum Debuggen                     */
#include "checks.h"          /* Definitionen fuer Ueberwachungen          */
#include "grammar.h"         /* Definition der Datenstruktur              */
#include "listen.h"          /* Deklarationen Listenverwaltung            */ 
#include "allocate.h"        /* Deklarationen Speicherverwaltung          */
#include "alpharel.h"
#include "lrkzust.h"         /* Deklarationen Zustandsverwaltung          */
#include "lrkmat.h"          /* Deklarationen erster Pass                 */
#include "lrkmatp2.h"        /* Deklarationen zweiter Pass                */
#include "lrksets.h"         /* Deklarationen Mengenoperationen           */
#include "lrkdec.h"          /* Deklarationen Dekoder                     */
#include "lrkmatp2.h"        /* Deklarationen Generatormodul 2.Pass       */
#include "lrkkont.h"         /* Deklarationen Kontextberechnung           */
#ifdef INCATTR
#include "iadefs.h"
#include "iaattr.h"
#include "iasemfkt.h"
#endif

/* ========================================================================= */
/* Programm-globale Variablen                                                */
/* ========================================================================= */
extern Grammar g;            /* bearbeitete Grammatik                        */
extern int max_lookahead;    /* maximale Laenge Lookahead (-k Option)        */
extern int generrors;        /* Anzahl Generierungsfehler                    */
extern NuebRec *nontinvuebs; /* Array der Zustaende zu Nonterminalen         */

/* ========================================================================= */
/* Modul-globale Variablen                                                   */
/* ========================================================================= */
static Recinfo reccnt = 0;     /* aktuell laufende Rekursionsebene           */
static Termset ausgegeben;     /* bereits gemeldete Terminalzeichen          */
#ifdef INCATTR
#define ATTRSEM(p) *((Position *)&(POSATTR(p)->sem))
#define SEM(attr)  *((Position *)&((attr)->sem))

static Lookset *glook;
/* ========================================================================= */
/* fuer Anfangs-Terminalzeichen aufgerufen                                   */
/* ========================================================================= */
#ifdef __STDC__
void firstTerm(Symb sym)
#else
void firstTerm(sym)
 Symb sym;  /* erstes ableitbares Terminalsymbol (first_1)          */
#endif
 {
  CHECKPT(glook);
  CHECKBED(ISTERM(sym));
  DEBUG_BEGIN(("enterLookset(%s) first",decSym(sym) ));
  enterLookset(sym,glook);
  DEBUG_END((" \n"));
 } /* firstTerm */

/*====================================================================== */
/* Firstmenge berechnen, minimale Laenge eines Eintrags abliefern        */
/* FIRST-LOOK-Menge initialisieren                                       */
/*====================================================================== */
#ifdef __STDC__
static int getFirstset(Position pos)
#else
static int getFirstset(pos)
 Position pos; /* Position, deren terminale Anfaenge berechnet werden */
#endif
 {
  Item item;
  int ende;              /* Ende der Produktion erreicht     */

  DEBUG_BEGIN(("getFirstset()\n"));fflush(stdout);
  CHECKPT(pos);
  item = POSITEM(*pos);
  ende = TRUE;
  POSFIRST(*pos) = NULL; /* leer vorbesetzen                 */
  while(ITEMLEN(item))   /* solange innerhalb der Produktion */
   {
    Symb sym;

    item = NEXTITEM(item);           /* naechstes zu lesendes ...  */
    sym = ITEMSYM(item);             /*  Symbol bestimmen          */
    if (ISTERM(sym))
     {
     /* ------------------------------- */
     /* terminal, direkt ausgeben       */
     /* ------------------------------- */
      enterLookset(sym,&POSFIRST(*pos));
      DEBUG_MSG(("enterLookset(%s) term\n",decSym(sym) ));
      ende = FALSE;     /* Kontext hier beendet             */
      break;            /* Rest der Produktion irrelevant   */
     } /* ISTERM(sym) */
    else
     {
     /* ------------------------------- */
     /* Nonterminal, Anfaenge berechnen */
     /* ------------------------------- */
      DEBUG_MSG(("Aufruf Alphaeps(%s)\n",decSym(sym) ));fflush(stdout);
      glook = &POSFIRST(*pos);
      forAlphaeps(sym);         /* first1 berechnen                 */
      if (!ISEPS(sym))
       {
        ende = FALSE;           /* Kontext hier beendet             */
        break;                  /* Rest der Produktion irrelevant   */
       }
     } /* ISTERM(sym) */
   } /* while (ITEMLEN(item)) */
  POSFIRST_LOOK(*pos) = NULL;
  unionLookset(&POSFIRST_LOOK(*pos),POSFIRST(*pos)); /* firstlook init. */
  if (ende)
   {
    enterLookset(EOLOOK,&POSFIRST(*pos)); 
    DEBUG_END(("getFirstset() = 0\n"));
    return(0);
   }    
  DEBUG_END(("getFirstset() = 1\n"));
  return(1);
 } /* getFirstset */

/* ========================================================================= */
/* reichert Position um die Attributinformationen an                         */
/* Rueckgabe: Attributzeiger                                                 */
/* ========================================================================= */
#ifdef __STDC__
static Attribut makeAttrpos(Position pos, Zustand zust)
#else
static Attribut makeAttrpos(pos,zust)
 Position pos;   /* anzureichernde Position */
 Zustand  zust;  /* umfassender Zustand     */
#endif
 {
  CHECKPT(pos);
  CHECKPT(zust);
  CHECKPTN(POSATTR(*pos));
  DEBUG_BEGIN(("makeAttrpos()\n"));
  if (POSATTR(*pos) == NULL)
   {
    POSATTR(*pos) = newAttribut();
    POSZUST(*pos)  = zust;
    ATTRSEM(*pos)  = pos;
    getFirstset(pos);
   }
  DEBUG_END(("makeAttrpos() Ende\n"));fflush(stdout);
  return(POSATTR(*pos));
 } /* makeAttrpos */

/* ========================================================================= */
/* Eintragen in Abhaengigkeitsliste, falls noch nicht vorhanden              */
/* Rueckgabe: neuer Eintrag, NULL, falls bereits vorhanden                   */
/* ========================================================================= */
#ifdef __STDC__
static Attributlis verynewDepend(Attributlis *lis, Attribut attr)
#else
static Attributlis verynewDepend(lis,attr)
 Attributlis *lis;
 Attribut attr;
#endif
 {
  Attributlis eintr;

  CHECKPT(lis);
  CHECKPTN(*lis);
  CHECKPT(attr);
  for (eintr = *lis; eintr != NULL; eintr = eintr->next)
    if (eintr->attr == attr)
      return(NULL);
  return(newDepend(lis,attr));
 } /* verynewDepend */

/* ========================================================================= */
/* Berechnung der direkten Kontexte eines Zustandes                          */
/* ========================================================================= */
#ifdef __STDC__
static void zustKont(Zustand zust,Zustand szust,Ueberg sueb, 
                     Attributlis *attr_lis )
#else
static void zustKont(zust,szust,sueb,attr_lis)
 Zustand zust;           /* Ausgangszustand                            */
 Zustand szust;          /* Zustand, dessen Kontexte berechnet werden  */
 Ueberg  sueb;           /* Uebergang zust -> szust                    */
 Attributlis *attr_lis;  /* Liste, in die gefundene eingetragen werden */
#endif
 {
  Position pos;          
                
  CHECKPT(zust);
  CHECKPT(szust);
  CHECKPT(sueb);
  CHECKPT(attr_lis);
  CHECKPTN(*attr_lis);

  DEBUG_BEGIN(("zustKont(aus %ld\n",(long)ZUSTNR(*zust) ));
  IFDEBUG
  (
   FOREACHPOS(*zust,pos)
    {
     DEBUG_INDENT;
     fdecItem(DBGFILE,POSITEM(*pos));
     putc('\n',DBGFILE);
    }
   )
  DEBUG_MSG(("         Zust %ld\n",(long)ZUSTNR(*szust) ));
  IFDEBUG
  ({
   FOREACHPOS(*szust,pos)
    {
     DEBUG_INDENT;
     fdecItem(DBGFILE,POSITEM(*pos));
     putc('\n',DBGFILE);
    }
  })
  FOREACHPOS(*szust,pos)
   {               
    verynewDepend(attr_lis,makeAttrpos(pos,szust));
   }
  DEBUG_END(("zustKont() Ende\n"));
 } /* zustKont */

/* ========================================================================= */
/* Zurueckgehen um len Uebergaenge im LR(0)-Automaten zu den Zustaenden, die */
/* Vorgaenger des Items item enthalten                                       */
/* dann weiter vorwaerts mit reduzierter linker Seite                        */
/* die gefundenen Ausgangszustaende werden in attr_lis eingetragen           */
/* ========================================================================= */
#ifdef __STDC__
static void getReturns(Zustand zust,Plength len,Item item,
                              Attributlis *attr_lis)
#else
static void getReturns(zust,len,item,attr_lis)
 Zustand zust;          /* Zustand, aus dem zurueckverfolgt wird   */
 Plength len;           /* Anzahl zurueckzugehender Uebergaenge    */
 Item    item;          /* Zielitem, zu dem zurueckgegangen wird   */
 Attributlis *attr_lis; /* Liste der gefundenen Positionen         */
#endif
 {
  Ueberg sueb;          /* Uebergang, den zurueckgegangen wird */
  Zustand nzust;        /* neuer Zustand                       */
  
  
  DEBUG_BEGIN(("getReturns(%ld\n",(long)ZUSTNR(*zust) ));
  IFDEBUG
  ({ /* Items des Zielzustandes angeben */ 
   register Position pos;
   FOREACHPOS(*zust,pos)
    {
     DEBUG_MSG(("        "));
     fdecItem(DBGFILE,POSITEM(*pos));
     putc('\n',DBGFILE);
    }
  })
  DEBUG_MSG(("        ,%ld,",(long)len));
  IFDEBUG
  ({ 
    fdecItem(DBGFILE,item);
    fputs(")\n",DBGFILE);
  })

  if (len==0)
   {            
    /* --------------------------------------------------------------- */
    /* Reduktionszustand bereits erreicht, Kontext vorwaerts berechnen */
    /* --------------------------------------------------------------- */
    Ueberg ueb;
                                                                               
    CHECKBED(item == lhsItem(item));    /* tatsaechlich linke Seite ? */
    ueb = sucheUeb(zust,ITEMSYM(item)); /* Vorwaertsuebergang suchen  */
    if (ueb == NULL)                    /* keine vorhanden            */
     {       
      DEBUG_END(("getReturns(,0,) ueb == NULL\n"));
      return;
     }
    CHECKPT(ueb);
    CHECKBED(UEBART(*ueb) == SHIFT);
    DEBUG_MSG(("Reduce-Kontext von Zustand  %ld\n",(long)ZUSTNR(*zust) ));
    zustKont(zust,UEBSZUST(*ueb),ueb,attr_lis); 
   } /* len == 0 */
  else if (len == 1)                        
   {
   /* ------------------------------------------------------------------- */
   /* Am Anfang einer Produktion angelangt, alle Ausgangszustaende melden */
   /* ------------------------------------------------------------------- */
    for (sueb = ZUSTSHIFTS(*zust);
         sueb != NULL;
         sueb = NEXTSHIFT(*sueb) )
     {
      CHECKPT(sueb);
      if (INKARN(*sueb) != reccnt)       /* Uebergang neu            */
       {                
        Ueberg ueb;

        nzust = UEBVON(*sueb);                /* Ausgangs-Zustand         */
        CHECKPT(nzust);         
        DEBUG_MSG(("zurueck zu Zustand %ld, Symbol %s, Anfang\n",
                   (long)ZUSTNR(*nzust),
                   decSym(UEBSYM(*sueb)) ));
        DEBUG_MSG(("sueb markiert: "));
        IFDEBUG(fdecUeb(DBGFILE,sueb);)
        INKARN(*sueb) = reccnt;               /* merken, dass ausgewertet  */
        ueb = sucheUeb(nzust,ITEMSYM(lhsItem(item)) );  /* Folgeuebergang            */
        CHECKPT(ueb);
        DEBUG_MSG(("vorwaerts in Zustand %ld mit Symbol %s\n",
                   (long)ZUSTNR(*UEBSZUST(*ueb)),
                   decSym(ITEMSYM(lhsItem(item))) ));
        zustKont(nzust,UEBSZUST(*ueb),ueb,attr_lis);  /* Kontexte dieses Zustandes */
       } /* Uebergang neu */
      else /* reccnt gleich */
       {
        DEBUG_MSG(("--reccnt -- (Anfang) "));
        IFDEBUG(fdecUeb(DBGFILE,sueb));
       }         
     } /* for */
   } /* len == 1 */
  else /* len > 1 */
   {
  /* -------------------------------------------------- */
  /* die zum Item passenden Ausgangszustaende suchen    */
  /* -------------------------------------------------- */
    for (sueb = ZUSTSHIFTS(*zust);
         sueb != NULL;
         sueb = NEXTSHIFT(*sueb) )
     {
      Position pos;   /* Position in zust       */
      Item     such;  /* Zielitem zu item       */

      CHECKPT(sueb);
       {
        nzust = UEBVON(*sueb);               /* Ausgangs-Zustand        */
        CHECKPT(nzust);         
        /* ------------------------------------------------------- */
        /* Feststellen, ob zust das Vorgaengeritem von it enthaelt */
        /* ------------------------------------------------------- */
        such = NNEXTITEM(item,
               len-(ITEMLEN(lhsItem(item))-ITEMLEN(item))- 1);   /* Zielitem bestimmen */
        IFDEBUG
        ({
          DEBUG_MSG(("item    = "));
          fdecItem(stdout,item);
          fputc('\n',stdout);
          DEBUG_MSG(("such    = "));
          fdecItem(stdout,such);
          fputc('\n',stdout);
        })
        FOREACHPOS(*nzust,pos)
         {
          DEBUG_MSG(("positem = "));
          IFDEBUG
          ({
            fdecItem(stdout,POSITEM(*pos));
            fputc('\n',stdout);
          })
          if (POSITEM(*pos) == such)
            break;                           /* gefunden, zust o.k.     */
         }
        if (pos != NULL)
         {
          DEBUG_MSG(("zurueck zu Zustand %ld, Symbol %s, Restlaenge %ld\n",
                     (long)ZUSTNR(*nzust),
                     decSym(UEBSYM(*sueb)),(long)(len-1) ));
          getReturns(nzust,(Plength)(len-1),item,attr_lis); /* weiter zurueck      */
         }
        else 
         {
          DEBUG_MSG(("nicht zurueck zu Zustand %ld, Symbol %s, Restlaenge %ld\n",
                     (long)ZUSTNR(*nzust),
                     decSym(UEBSYM(*sueb)),(long)(len-1) ));
         } 
       } /* Uebergang neu */
     } /* for */
   } /* len > 1 */                       
  DEBUG_END(("getReturns() Ende\n" ));
 } /* getReturns */


/*====================================================================== */
/* Firstmenge einer Position berechnen. Falls noetig,                    */
/* Liste aller Positionen berechnen, von denen eine Position abhaengig   */
/*====================================================================== */
#ifdef __STDC__
Attributlis getDepends(Attribut attr)
#else
Attributlis getDepends(attr)
 Attribut attr;
#endif
 {
  Position pos;       /* Position des Attributes     */

  pos = (Position)attr->sem;
  DEBUG_MSG(("getdepends:"));
  IFDEBUG
  ({
    fdecItem(stdout,POSITEM(*pos));
    fputc('\n',stdout);
  })

  if (getFirstset(pos) < max_lookahead)
   { /* Anfaenge nicht ausreichend */
    Attributlis result; /* Liste der Argumentattribute */

    result = NULL;                    /* Abhaengigkeitsliste leer      */
    reccnt++;                         /* neue Rekursionsinformation    */
    getReturns(POSZUST(*pos), 
               ITEMLEN(lhsItem(POSITEM(*pos)))-ITEMLEN(POSITEM(*pos)),  
               POSITEM(*pos),&result);
    return(result);
   }
  else 
    return(NULL);                      /* keine Abhaengigkeiten        */
 } /* getDepends */

#else /* !defined(INCATTR) */
/* ========================================================================= */
/* forward-Deklarationen                                                     */
/* ========================================================================= */
#ifdef __STDC__
static void traceBack(Zustand,Plength,Item);
#else
static void traceBack();
#endif

/* ========================================================================= */
/* fuer Anfangs-Terminalzeichen aufgerufen                                   */
/* ========================================================================= */
#ifdef __STDC__
void firstTerm(Symb sym)
#else
void firstTerm(sym)
 Symb sym;  /* erstes ableitbares Terminalsymbol (first_1)          */
#endif
 {
  if (!inTset(sym,ausgegeben))   /* noch nicht gemeldet */
   {
    inclTset(sym,ausgegeben);    /* Ausgabe merken      */
    DEBUG_BEGIN(("enterLook(%s) first",decSym(sym) ));
    DEBUG_END((" \n"));
    enterLook(sym);              /* melden              */
   }
 } /* firstTerm */

/* ========================================================================= */
/* Berechnung der Terminalzeichen, die in einem Zustand zust gelesen         */
/* werden koennen                                                            */
/* zust darf kein Reduktionszustand sein (ZUSTNR(*zust) != UNDEFZUSTNR))     */
/* bei Zustaenden ohne epsilon-Uebergaenge sollten die 1-Lookaheads direkt   */
/* mit getNextterm() aus den terminalen Uebergaengen berechnet werden        */
/* Rueckgabe der Liste der Items, deren Lookahead noch nicht komplett, da    */
/* das Produktionsende erreicht wurde                                        */
/* ========================================================================= */
#ifdef __STDC__
static Position getNext(Position posl)
#else
static Position getNext(posl)
 Position posl;     /* Liste der Positionen, deren Kontexte berechnet */
#endif
 {                                                                        
 /* ------------------------------------------ */
 /* Kontext aus first-Mengen und LALR-Kontext  */
 /* ------------------------------------------ */               
  Position eposl;          /* Liste der Positionen, fuer die Ende erreicht */
  register Position pos;   /* Position in zust                             */

  DEBUG_BEGIN(("getNext()\n" ));
  eposl = NULL;            /* bis jetzt kein Ende erreicht                 */
  FOREACHLISTEL(posl,pos)  /* alle Positionen auswerten                    */
   {
   /* alle Items dieses Zustandes auswerten    */

    register Item item;            /* Item zur Position      */
    BOOL ende;                     /* Kontextsuche beenden   */
                             
    item = POSITEM(*pos); 
    DEBUG_MSG(("  item : "));
    IFDEBUG
    ({
      fdecItem(DBGFILE,item);
      fputc('\n',DBGFILE);
    })
    ende = TRUE;          /* falls kein Abbruch mit break     */
    while(ITEMLEN(item))  /* solange innerhalb der Produktion */
     {
      register Symb sym;

      item = NEXTITEM(item);           /* naechstes zu lesendes ...  */
      sym = ITEMSYM(item);             /*  Symbol bestimmen          */
      if (ISTERM(sym))
       {
       /* ------------------------------- */
       /* terminal, direkt ausgeben       */
       /* ------------------------------- */
        if (!inTset(sym,ausgegeben))   /* noch nicht gemeldet */
         {
          inclTset(sym,ausgegeben);
          DEBUG_MSG(("enterLook(%s) term\n",decSym(sym) ));
          enterLook(sym);              /* melden              */
         }
        ende = FALSE;     /* Kontext hier beendet             */
        break;            /* Rest der Produktion irrelevant   */
       } /* ISTERM(sym) */
      else
       {
       /* ------------------------------- */
       /* Nonterminal, Anfaenge berechnen */
       /* ------------------------------- */
        DEBUG_MSG(("Aufruf Alphaeps(%s)\n",decSym(sym) ));
        forAlphaeps(sym);         /* first1 berechnen                 */
        if (!ISEPS(sym))
         {
          ende = FALSE;           /* Kontext hier beendet             */
          break;                  /* Rest der Produktion irrelevant   */
         }
       } /* ISTERM(sym) */
     } /* while (ITEMLEN(item)) */
    if (ende)
     {                  
     /* ------------------------------- */
     /* Ende der Produktion erreicht    */
     /* LALR-Kontext beruecksichtigen   */
     /* ------------------------------- */
      DEBUG_MSG(("  Ende Item "));
      IFDEBUG
      ({
        fdecItem(DBGFILE,item);
        fputc('\n',DBGFILE);
      })
      eintragPosition(&eposl,pos);             /* in die Liste eintragen  */
     } /* Ende der Produktion erreicht */
   } /* FOREACHPOS */                     
  DEBUG_END(("getNext() Ende\n" ));
  return(eposl);       /* Status der Berechnung abliefern  */
 } /* getNext */            

/* ========================================================================= */
/* Berechnung der Terminalzeichen, die in einer Liste terminaler             */
/* Uebergaenge uebs gelesen werden                                           */
/* ========================================================================= */
#ifdef __STDC__
static void getNextterm(Ueberg uebs)
#else
static void getNextterm(uebs)
 Ueberg uebs;   /* Liste der terminalen Uebergaenge */
#endif
 {
  /* ----------------------------------------------------- */
  /* alle moeglichen Terminalsymbole als Lookahead melden  */
  /* ----------------------------------------------------- */
  register Ueberg ueb;

  DEBUG_BEGIN(("getNextterm()\n"));
  for (ueb = uebs; ueb != NULL; 
       ueb = (Ueberg)LISTNEXT(*ueb) )
   { /* alle terminalen Uebergaenge betrachten */
    register Term term; 

    term = UEBSYM(*ueb);
    CHECKBED(ISTERM(term));
    if (!inTset(term,ausgegeben))   /* noch nicht gemeldet */
     {
      inclTset(term,ausgegeben);
      DEBUG_MSG(("enterLook(%s) direkt\n",decSym(term) ));
      enterLook(term);              /* melden              */
     }
   } /* alle terminalen Uebergaenge betrachten */
  DEBUG_END(("getNextterm() = NULL\n"));
 } /* getNextterm */


/* ========================================================================= */
/* Berechnung der direkten Kontexte eines Zustandes                          */
/* ========================================================================= */
#ifdef __STDC__
static void zustKont(Zustand zust,Zustand szust,Ueberg sueb)
#else
static void zustKont(zust,szust,sueb)
 Zustand zust;   /* Ausgangszustand                           */
 Zustand szust;  /* Zustand, dessen Kontexte berechnet werden */
 Ueberg  sueb;   /* Uebergang zust -> szust                   */
#endif
 {
  Position pos;          
                                                                         
  DEBUG_BEGIN(("zustKont(aus %ld\n",(long)ZUSTNR(*zust) ));
  IFDEBUG
  ({ /* Items des Zielzustandes angeben */ 
   register Position pos;                             
  )
  IFDEBUG
  (
   FOREACHPOS(*zust,pos)
    {
     DEBUG_INDENT;
     fdecItem(DBGFILE,POSITEM(*pos));
     putc('\n',DBGFILE);
    }
   )
  DEBUG_MSG(("         Zust %ld\n",(long)ZUSTNR(*szust) ));
  IFDEBUG
  (
   FOREACHPOS(*szust,pos)
    {
     DEBUG_INDENT;
     fdecItem(DBGFILE,POSITEM(*pos));
     putc('\n',DBGFILE);
    }
  })

  if (ZUSTNR(*szust) == UNDEFZUSTNR)    /* kein Kontext aus getNext() */
   {               
    Item litem;
          
    litem = lhsItem(POSITEM(*FIRSTPOS(*szust)));
    DEBUG_MSG(("Zustand == UNDEF !!!\n"));
    if (sueb != NULL)             /* uebergang markieren */
      INKARN(*sueb) = reccnt;
    traceBack(zust,(Plength)(ITEMLEN(litem) - 1),litem);
    DEBUG_END(("zustKont() Ende\n"));
    return;
   }
  else    
   {
    if (ZUSTEPSUEB(*szust) == NULL) /* keine spontanen Uebergaenge */
     {
      getNextterm(ZUSTTERMUEB(*szust)); /* terminale Uebergaenge direkt    */
      DEBUG_END(("zustKont() Ende\n"));
      return;                           /* Kontext fertig                  */
     }                                                                    
    else
      pos = getNext(FIRSTPOS(*szust));  /* Kontext aus den Items berechnen */
   }
  while (pos != NULL)
   {      
    Item ritem;
    Item litem;
    Plength len;

    ritem = POSITEM(*pos);
    litem = lhsItem(ritem);
    if ((len = ITEMLEN(litem) - ITEMLEN(ritem)) == 1)
     { /* Position aus "Ansprung", in diesem Zustand weiter */
      DEBUG_MSG(("Ansprung aus "));
      IFDEBUG
      ({
        fdecItem(DBGFILE,ritem);
        fputc('\n',DBGFILE);
      })
      if (sueb != NULL)                    /* Uebergang markieren */
        INKARN(*sueb) = reccnt;
      traceBack(zust,(Plength)0,litem);    /* weiteren Kontext    */
     }                              
    else /* Position aus "weiter", vor diesem Zustand weiter */
     {
      DEBUG_MSG(("weiter aus "));
      IFDEBUG
      ({
        fdecItem(DBGFILE,ritem);
        fputc('\n',DBGFILE);
      })
      traceBack(zust,(Plength)(len-1),litem); 
     }
    pos = (Position)LISTNEXT(*pos);
   } /* while */
  freelisPosition(pos);
  DEBUG_END(("zustKont() Ende\n"));
 } /* zustKont */

/* ========================================================================= */
/* Zurueckgehen um len Uebergaenge im LR(0)-Automaten zu den Zustaenden, die */
/* Vorgaenger des Items item enthalten                                       */
/* dann weiter vorwaerts mit reduzierter linker Seite                        */
/* fuer die gefundenen Ausgangszustaende wird getNext() aufgrufen            */
/* ========================================================================= */
#ifdef __STDC__
static void traceBack(Zustand zust,Plength len,Item item)
#else
static void traceBack(zust,len,item)
 Zustand zust;     /* Zustand, aus dem zurueckverfolgt wird            */
 Plength len;      /* Anzahl zurueckzugehender Uebergaenge             */
 Item    item;     /* Zielitem, zu dem zurueckgegangen wird            */
#endif
 {
  register Ueberg sueb;   /* Uebergang, den zurueckgegangen wird */
  register Zustand nzust; /* neuer Zustand                       */

  DEBUG_BEGIN(("traceBack(%ld\n",(long)ZUSTNR(*zust) ));
  IFDEBUG
  ({ /* Items des Zielzustandes angeben */ 
   register Position pos;
   FOREACHPOS(*zust,pos)
    {
     DEBUG_MSG(("        "));
     fdecItem(DBGFILE,POSITEM(*pos));
     putc('\n',DBGFILE);
    }
  })
  DEBUG_MSG(("        ,%ld,",(long)len));
  IFDEBUG
  ({ 
    fdecItem(DBGFILE,item);
    fputs(")\n",DBGFILE);
  })

  if (len==0)
   {            
    /* --------------------------------------------------------------- */
    /* Reduktionszustand bereits erreicht, Kontext vorwaerts berechnen */
    /* --------------------------------------------------------------- */
    Ueberg ueb;
                                                                               
    CHECKBED(item == lhsItem(item));  /* tatsaechlich linke Seite ? */
    ueb = sucheUeb(zust,ITEMSYM(item));
    if (ueb == NULL)
     {       
      DEBUG_END(("traceBack(,0,) ueb == NULL\n"));
      return;
     }
#if 0 /* hier nicht testen ! */
    if (INKARN(*ueb) == reccnt)            /* Uebergang nicht neu */
     {
      DEBUG_END(("traceBack() Ende : reccnt (Kontext vorwaerts) "));
      IFDEBUG(fdecUeb(DBGFILE,ueb));
      return;
     }
    else
     {                      
      /* DEBUG_MSG(("ueb markiert: "));
      IFDEBUG(fdecUeb(DBGFILE,ueb);)
      INKARN(*ueb) = reccnt; */
     }
#endif
    CHECKPT(ueb);
    CHECKBED(UEBART(*ueb) == SHIFT);
    DEBUG_MSG(("Reduce-Kontext von Zustand  %ld\n",(long)ZUSTNR(*zust) ));
    zustKont(zust,UEBSZUST(*ueb),ueb);
   } /* len == 0 */
  else if (len == 1)                        
   {
   /* ------------------------------------------------------------------- */
   /* Am Anfang einer Produktion angelangt, alle Ausgangszustaende melden */
   /* ------------------------------------------------------------------- */
    for (sueb = ZUSTSHIFTS(*zust);
         sueb != NULL;
         sueb = NEXTSHIFT(*sueb) )
     {
      CHECKPT(sueb);
      if (INKARN(*sueb) != reccnt)       /* Uebergang neu            */
       {                
        Ueberg ueb;

        nzust = UEBVON(*sueb);                /* Ausgangs-Zustand         */
        CHECKPT(nzust);         
        DEBUG_MSG(("zurueck zu Zustand %ld, Symbol %s, Anfang\n",
                   (long)ZUSTNR(*nzust),
                   decSym(UEBSYM(*sueb)) ));

        DEBUG_MSG(("sueb markiert: "));
        IFDEBUG(fdecUeb(DBGFILE,sueb);)
        INKARN(*sueb) = reccnt;              /* merken, dass ausgewertet  */
        ueb = sucheUeb(nzust,ITEMSYM(item)); /* Folgeuebergang            */
        CHECKPT(ueb);
        DEBUG_MSG(("vorwaerts in Zustand %ld mit Symbol %s\n",
                   (long)ZUSTNR(*UEBSZUST(*ueb)),
                   decSym(ITEMSYM(item)),(long)(len-1) ));
        zustKont(nzust,UEBSZUST(*ueb),ueb);  /* Kontexte dieses Zustandes */
       } /* Uebergang neu */
      else /* reccnt gleich */
       {
        DEBUG_MSG(("--reccnt -- (Anfang) "));
        IFDEBUG(fdecUeb(DBGFILE,sueb));
       }         
     } /* for */
   } /* len == 1 */
  else /* len > 1 */
   {
  /* -------------------------------------------------- */
  /* die zum Item passenden Ausgangszustaende suchen    */
  /* -------------------------------------------------- */
    for (sueb = ZUSTSHIFTS(*zust);
         sueb != NULL;
         sueb = NEXTSHIFT(*sueb) )
     {
      Position pos;   /* Position in zust       */
      Item     such;  /* Zielitem zu item       */

      CHECKPT(sueb);
       {
        nzust = UEBVON(*sueb);               /* Ausgangs-Zustand        */
        CHECKPT(nzust);         
        /* ------------------------------------------------------- */
        /* Feststellen, ob zust das Vorgaengeritem von it enthaelt */
        /* ------------------------------------------------------- */
#if 0
        such = NNEXTITEM(item,len-1);        /* Zielitem bestimmen      */
#else
        such = NNEXTITEM(item,
               len-(ITEMLEN(lhsItem(item))-ITEMLEN(item))- 1);   /* Zielitem bestimmen */
#endif
        FOREACHPOS(*nzust,pos)
          if (POSITEM(*pos) == such)
            break;                           /* gefunden, zust o.k.     */
        if (pos != NULL)
         {
          DEBUG_MSG(("zurueck zu Zustand %ld, Symbol %s, Restlaenge %ld\n",
                     (long)ZUSTNR(*nzust),
                     decSym(UEBSYM(*sueb)),(long)(len-1) ));
          traceBack(nzust,(Plength)(len-1),item); /* weiter zurueck      */
         } 
       } /* Uebergang neu */
     } /* for */
   } /* len > 1 */                       
  DEBUG_END(("trace_back() Ende\n" ));
 } /* traceBack */

/* ========================================================================= */
/* Berechnung aller terminalen Symbole, die folgen koennen, nachdem im       */
/* Zustand zust der spontane Uebergang ueb ausgefuehrt wurde                 */
/* fuer jedes gefundene Symbol gsym wird enterLook(gsym) aufgerufen          */ 
/* ========================================================================= */
#ifdef __STDC__
static void getKont(Zustand zust,Ueberg ueb)
#else
static void getKont(zust,ueb)
 Zustand zust;         /* Zustand, in dem Uebergang erfolgt           */
 Ueberg  ueb;          /* auszufuehrender Uebergang                   */
#endif
 {
  register Item ritem;  /* zu reduzierendes Item                      */
  register Plength len; /* Laenge der Reduktion                       */

  CHECKPT(zust);
  CHECKPT(ueb);
  DEBUG_BEGIN(("getKont %ld ",(long)ZUSTNR(*zust) ));
  IFDEBUG(fdecUeb(DBGFILE,ueb));
  CHECKBED(UEBART(*ueb) == SPONTRED);  /* andere erst bei k>1           */
  
  ritem  = UEBRITEM(*ueb);             /* item der Reduktion            */
  len    = ITEMLEN(lhsItem(ritem));    /* Laenge des backtrace          */
  traceBack(zust,len,ritem);           /* Kontext berechnen             */
  DEBUG_END(("getKont() Ende\n"));
 } /* getKont */

/* ========================================================================= */
/* Berechnung aller terminalen Symbole, die folgen koennen, nachdem im       */
/* Zustand der spontane Uebergang ueb ausgefuehrt wurde                      */
/* fuer jedes gefundene Symbol gsym wird enterLook(gsym) aufgerufen          */ 
/* ========================================================================= */
#ifdef __STDC__
void lrkKontext(Zustand zust,Ueberg ueb)
#else
void lrkKontext(zust,ueb)
 Zustand zust;            /* Zustand, in dem Uebergang erfolgt           */
 Ueberg  ueb;             /* auszufuehrender Uebergang                   */
#endif
 {
  CHECKPT(zust);
  CHECKPT(ueb);
  DEBUG_BEGIN(("-------------\n" ));
  DEBUG_MSG(("lrkKontext %ld ",(long)ZUSTNR(*zust) ));
  IFDEBUG(fdecUeb(DBGFILE,ueb ));
  CHECKBED(UEBART(*ueb) == SPONTRED);  /* andere erst bei k>1           */
  
  emptyTset(ausgegeben);               /* noch keine Symbole gemeldet   */
  reccnt++;                            /* neue Rekursionsinformation    */
  getKont(zust,ueb);                   /* Kontexte berechnen            */
  DEBUG_END(("lrkKontext() Ende\n" ));
 } /* lrkKontext */
#endif

/* ========================================================================= */
/* Initialisierung dieses Moduls                                             */
/* ========================================================================= */
#ifdef __STDC__
void initLRKkont(void)
{
#else
void initLRKkont()
 {
#endif
  getTset(&ausgegeben);          /* Speicher fuer Menge reservieren          */
 } /* initLRKkont */


