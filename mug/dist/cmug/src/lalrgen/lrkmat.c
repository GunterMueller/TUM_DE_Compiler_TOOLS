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
/* LRKmat.c   :                                                           */
/* LR(k)-Parser-Generator                                                 */
/* Modul : Generierung der Uebergangsmatrix                               */
/* Aenderung  : 02.07.89, weitere Abpruefungen (term., benutzt )          */
/* Aenderung  : 30.06.89, ueberarbeitet wg. LRKsim                        */
/* Aenderung  : 24.06.89, Behandlung von epsilon-Produktionen korrigiert  */
/* Aenderung  : 10.06.89, EPSRED-Uebergangstyp eliminiert                 */
/* Aenderung  : 11.3.89 , Datentyp Pueblis als Keller ausprogrammiert     */
/* Aenderung  : 10.3.89 , Zusatzinformationen in prov. Tabelle            */
/* Aenderung  :  7.3.89 , Ueberwachung zur Laufzeit                       */
/* erstellt   : 23.1.89                                                   */
/* ********************************************************************** */
#ifdef __STDC__
#include <stddef.h>
#include <stdlib.h>
#endif
#include <stdio.h>         /* E/A-Deklarationen                   */
#include "defs.h"          /* diverse unspezifische Definitionen  */
#include "checks.h"        /* Deklarationen fuer Ueberpruefungen  */
#include "allocate.h"      /* Deklarationen Speicherverwaltung    */
#include "listen.h"        /* Deklarationen Listenverwaltung      */
#include "grammar.h"       /* Datenstrukturen der Grammatik       */
#include "lrkzust.h"       /* Deklarationen Zustandsmodul         */
#include "lrkdec.h"        /* Deklarationen Dekoder               */
#include "lrkmat.h"        /* Deklarationen Generatormodul        */
#include "lrkmatp2.h"      /* Deklarationen Generatormodul 2.Pass */
#include "lrkkont.h"       /* Deklarationen Kontextmodul          */
#include "lrkerrors.h"     /* Deklarationen Fehlermeldungsmodul   */
#include "lrkeps.h"
#include "alpharel.h"      /* Deklarationen Ansprungmodul         */

/* ========================================================================= */
/* Programm-globale Variablen                                                */
/* ========================================================================= */
extern Grammar g;           /* bearbeitete Grammatik                         */
extern int max_lookahead;   /* maximale Laenge Lookahead (-k Option)         */
extern int generrors;       /* Anzahl gefundener Fehler                      */

/* ========================================================================= */
/* im Modul verwendete Datenstrukturen                                       */
/* ========================================================================= */
#ifdef INCATTR
static Zustand gzust;
#endif
/* ------------------------------------------------------------------------ */
/* Puebbas : Listenanker fuer Pueb mit Zusatzverkettung                     */
/* erlaubt ausschliessliche Freigabe und Bearbeiten von benutzten Listen    */
/* Aufgrund Laufzeituntersuchungen : 14 % der Laufzeit fuer freelisPueb     */
/* ------------------------------------------------------------------------ */
typedef struct PuebbaslisR *Puebbaslis;
typedef struct PuebbaslisR{
                Puebbaslis next;      /* naechster in Liste der benutzten */
                Position   zielitems; /* Liste der Zielitems              */
                Symb       sym;       /* gelesenes Symbol                 */
               } Puebbas;


/* ========================================================================= */
/* Aufruf parametrisierter Datenstrukturen                                   */
/* ========================================================================= */
 /* zum Abbruch bei vollem Speicher etc. */
#define ABBRUCH mAbort()

/* ========================================================================= */
/* globale Variablen                                                         */
/* ========================================================================= */
NuebRec *nontinvuebs;      /* Array der Zustaende zu Nonterminalen           */
static Puebbas *nontuebs;  /* Array der Uebergaenge mit Nonterminalen        */
static Puebbas *termuebs;  /* Array der Uebergaenge mit Terminalen           */
static Position  epsuebs;  /* Items der epsilon-Uebergaenge                  */
static Puebbaslis puebbas; /* Liste aller benutzten Uebergaenge              */

/* ========================================================================= */
/* Makros                                                                    */
/* ========================================================================= */

/* Zugriffe auf die einzelnen Eintraege */
#define NONTUEBS(n) nontuebs[n-MINN]
#define TERMUEBS(t) termuebs[t-MINT]
#define EPSUEBS epsuebs

/*====================================================================== */
/* Suchen einers Uebergangs mit einem Nonterminal-Symbol in einem Zustand*/
/*====================================================================== */
#ifdef __STDC__
Ueberg sucheUeb(Zustand zust ,Symb sym)
#else
Ueberg sucheUeb(zust,sym)
 register Zustand zust;
 register Symb sym;
#endif
 {
  register Ueberg such;

  CHECKPT(zust);
  CHECKBED(ISNONT(sym));
  for (such = NONTINVUEB(sym);
       such != NULL && UEBVON(*such) != zust;
       such = (Ueberg)NEXTNONT(*such));
  return(such);
 } /* sucheUeb */
/*====================================================================== */
/* Eintragen eines Uebergangs in eine provisorische Uebergangsliste       */
/*====================================================================== */
#ifdef __STDC__
static void pEintrag(Position* liste,Item item)
#else
static void pEintrag(liste,item)
 Position *liste;     /* Liste, in die der Uebergang eingetragen wird  */
 Item     item;       /* Zielitem des Ueberganges                      */
#endif
 {
  PosRec       pos;   /* Zielposition                                  */

#ifdef DEBUG
  printf("    pEintrag(%lx -> %lx,%ld\n",(long)liste,(long)*liste,(long)item);
#endif /* DEBUG */
  CHECKPT(liste);                      /* Test Korrektheit Listenzeiger   */
  CHECKPTN(*liste);                    /* Test Korrektheit Liste          */
  CHECKBED(ISITEM(item));              /* Item gueltig ?                  */

  POSITEM(pos) = item;                 /* angesprungenes Item             */
  eintragPosition(liste,&pos);         /* in Liste eintragen              */
 } /* pEintrag */

/*====================================================================== */
/* Uebergang zu einem Item in die provisorische Uebergangsliste eintragen */
/* globale Routine, wird auch von forAnsprung aufgerufen                  */
/*====================================================================== */
#ifdef __STDC__
void doUeb(Item item)
#else
void doUeb(item)
 Item item;    /* Item, dessen Uebergang betrachtet wird                   */
#endif
 {
  register Symb       sym;    /* zu lesendes Symbol                        */
  register Puebbaslis baslis; /* Listenbasis fuer Eintrag Uebergang        */

#ifdef DEBUG
  printf("    doUeb(%ld)\n",(long)item);
#endif /* DEBUG */
  CHECKBED(ISITEM(item));             /* Item gueltig ?                    */

  if (ITEMLEN(item)==0) 
   /* ---------------------------------------------------------------- */
   /* spontaner Uebergang, Reduktion                                   */
   /*entweder epsilon-Produktion oder aus Reduktionszustand erreicht  */
   /* ---------------------------------------------------------------- */
   {
    /* Produktionsende schon erreicht          */
    /* Reduktion mit allen gueltigen Kontexten */
#ifdef DEBUG
    {
      Item     lhs;         /* linke Seite, falls Reduktion            */
      lhs = lhsItem(item);  /* linke Seite der Reduktion bestimmen     */
      printf("      spontRed(%s,%d)\n",decSym(ITEMSYM(lhs)),(int)ITEMLEN(lhs));
    }
#endif /* DEBUG */
  /* in Liste der eps-Uebergaenge eintragen  */
    pEintrag(&EPSUEBS,item);
#ifdef INCATTR
    {
     PosRec posr;

     LISTNEXT(posr) = NULL;
     POSITEM(posr) = item;
     eintragPosition(&FIRSTRED(*gzust),&posr);
    }
#endif
   } /* spontane Reduktion */
  else /* lesender Uebergang */
   {
   /* ----------------------------------------------- */
   /* lesender Uebergang                              */
   /* ----------------------------------------------- */
    item++;                            /* naechstes Item                 */
    sym = ITEMSYM(item);               /* naechstes zu lesendes Zeichen  */
#ifdef DEBUG
    if (ITEMLEN(item)==0)              /* spontaner Uebergang, Reduktion */
     {
      /* Produktionsende erreicht          */
      Item     lhs;         /* linke Seite, falls Reduktion         */
      lhs = lhsItem(item);  /* linke Seite der Reduktion bestimmen  */
      printf("      %s : Reduktion(%s,%d)\n",decSym(sym),decSym(ITEMSYM(lhs)),
                                           (int)ITEMLEN(lhs));
     } /* Reduktion */
    else /* Noch zu Lesen, Shifts */
     {
      printf("      %s : Shift(",decSym(sym));
      fdecItem(stdout,item);
      printf(")\n");
     } /* shift */
#endif /* DEBUG */
    if (ISNONT(sym))                         /* Uebergang mit Nonterminal  */
      baslis = &NONTUEBS(sym);               /* Zeiger auf Listenbasis     */
    else                                     /* Uebergang mit Terminal     */
      baslis = &TERMUEBS(sym);               /* Zeiger auf Listenbasis     */
    /* Weiterfuehren der Liste der benutzten Uebergaenge  */
    if (baslis->zielitems == NULL)           /* Liste noch nicht benutzt   */
     { /* neue Liste vorne einfuegen */
      baslis->next = puebbas;                /* Listenrest anhaengen       */
      puebbas = baslis;                      /* wird erster Eintrag        */
     }
    pEintrag(&(baslis->zielitems),item);     /*eintragen                  */   
   } /* lesender Uebergang */
 } /* doUeb */

/*====================================================================== */
/* Eintragen eines Ueberganges in die Uebergaenge eines Zustandes         */
/*====================================================================== */
#ifdef __STDC__
static void putUeb(Zustand zust ,Symb sym ,Uebart art,
                   Zustand szust ,Item ritem)
#else
static void putUeb(zust,sym,art,szust,ritem)
 Zustand zust;     /* Zustand, aus dem Uebergang erfolgt   */
 Symb    sym;      /* Symbol, mit dem Uebergang erfolgt    */
 Uebart  art;      /* Art des Ueberganges                  */
 Zustand szust;    /* Zielzustand, falls SHIFT             */
 Item    ritem;    /* Reduktions-Item                      */
#endif
 {
  register Ueberg nueb; /* angelegter Uebergang                 */
  UebergRec ueb;        /* gesamte Information des Ueberganges  */

#ifdef DEBUG
  printf("putUeb\n");
#endif /* DEBUG */
  CHECKPT(zust);
  CHECKBED(ISNONT(sym)||ISTERM(sym)||sym==UNDEFSYM);
  CHECKPTN(szust);
  CHECKBED(ritem == UNDEFITEM || ISITEM(ritem));

  switch(UEBART(ueb) = art)           /* Art des Ueberganges      */
   {
    case SHIFT:
         UEBSZUST(ueb) = szust;       /* Zielzustand eintragen    */
         break;
    case SPONTRED:
         UEBRITEM(ueb)  = ritem;  /* Reduktionsitem eintragen */
         break;
    case LOOK:
         UEBLOOKS(ueb) = NULL;    /* noch nicht implementiert */
         break;
    default:
         return;                  /* nicht zulaessig          */
   } /* switch */
  UEBSYM(ueb) = sym;              /* Symbol eintragen                    */
  UEBVON(ueb) = zust;             /* Ausgangszustand eintragen           */
  if (ISTERM(sym))                /* in Liste der terminalen Uebergaenge */
    nueb = eintragUeberg(&ZUSTTERMUEB(*zust),&ueb);  
  else if (ISNONT(sym))           /* in Liste der nonterm. Uebergaenge   */
   {
    nueb = eintragUeberg(&ZUSTNONTUEB(*zust),&ueb);  
    NEXTNONT(*nueb) = NONTINVUEB(sym);  /* in inverse Liste eintragen    */
    NONTINVUEB(sym) = nueb;             /* erster Eintrag                */
   }
  else                            /* spontaner Uebergang                 */
    nueb = eintragUeberg(&ZUSTEPSUEB(*zust),&ueb);  
  if (art == SHIFT)  /* Verkettung fuer Simulation */
   {
    NEXTSHIFT(*nueb) = ZUSTSHIFTS(*szust);
    ZUSTSHIFTS(*szust) = nueb;
   }
#ifdef DEBUG
  printf("putUeb Ende\n");
#endif /* DEBUG */
 } /* putUeb */

/*====================================================================== */
/* Berechnen der tatsaechlichen spontanen Uebergaenge                     */
/*====================================================================== */
#ifdef __STDC__
static void berechneEpsueb(Zustand zust ,Position ueblis)
#else
static void berechneEpsueb(zust,ueblis)
 Zustand  zust;   /* Zustand, aus dem Uebergang erfolgt   */
 Position ueblis; /* Liste der Zielitems                  */
#endif
 {
  register Position pos; /* ein Uebergang aus der Liste                    */

  CHECKPT(zust);
  CHECKPTN(ueblis);
  CHECKBED(ueblis != NULL);

#ifdef DEBUG
  printf("  berechneEpsueb(%lx)\n",(long)ueblis);
#endif /* DEBUG */
  FOREACHLISTEL(ueblis,pos)      /* alle zu reduzierenden Positionen      */
   {  
#ifdef DEBUG
    {
      register Item    lhs;  /* linke Seite, falls Reduktion                   */

      lhs = lhsItem(POSITEM(*pos));   /* linke Seite der Reduktion bestimmen   */
      printf("\t(%ld,<>) --> SPONTRED(%s,%d)\n",(long)ZUSTNR(*zust),
                      decSym(ITEMSYM(lhs)),(int)ITEMLEN(lhs));
    }
#endif /* DEBUG */
    putUeb(zust,UNDEFSYM,SPONTRED,
           (Zustand)NULL,lhsItem(POSITEM(*pos))); /* Uebergang eintragen */
    /*PRODSTAT(prodNr(POSITEM(*pos))) |= PS_REDUCE;*/ /* erst bei Lookahead */ 
   } /* FOREACHLISTEL(ueblis,ueb) */
#ifdef DEBUG
    printf("  berechneEpsueb Ende\n");
#endif /* DEBUG */
 } /* berechneEpsueb */

/*====================================================================== */
/* Berechnen der tatsaechlichen Uebergaenge mit einem Symbol              */
/* die angesprungenen Items werden in einen Zielzustand umgerechnet       */
/*====================================================================== */
#ifdef __STDC__
static void berechneUeb(Zustand z,Symb sym,Position ueblis)
#else
static void berechneUeb(z,sym,ueblis)
 Zustand z;          /* Zustand, aus dem Uebergang erfolgt */
 Symb sym;           /* zu lesendes Symbol                 */
 Position ueblis;    /* Liste der Zielitems                */
#endif
 {
  ZustRec  zust;       /* anzulegender Automatenzustand                  */
  Zustand  zzust;      /* angesprungener Zustand                         */
 
  CHECKPT(z);
  CHECKPTN(ueblis);
  CHECKBED(ISTERM(sym) || ISNONT(sym));
  CHECKBED(ueblis != NULL);   

#ifdef DEBUG
    printf("  berechneUeb(%s,%lx)\n",decSym(sym),(long)ueblis);
#endif /* DEBUG */
 /* ------------------------------------------- */
 /* Zielzustand aufbauen                        */
 /* ------------------------------------------- */
  FIRSTPOS(zust) = ueblis;   /* Zielzustands-Beschreibung aufbauen        */
#ifdef DEBUG
  { Position p;
    FOREACHPOS(zust,p)
     {
      printf("    :: ");
      fdecItem(stdout,POSITEM(*p));
      printf("\n");
     }
   }
#endif /* DEBUG */
  zzust = putZustand(&zust);  /* Zustand in Liste der Zustaende aufnehmen */
#ifdef DEBUG
  { Position p;
    FOREACHPOS(*zzust,p)
     {
      printf("    || ");
      fdecItem(stdout,POSITEM(*p));
      printf("\n");
     }
   }
  if (ZUSTNR(*zzust) == UNDEFZUSTNR)  /* beschleunigter Zustand           */
   {
    Item    lhs;                  /* linke Seite, falls Reduktion         */
    lhs = lhsItem(ueblis->item);  /* linke Seite der Reduktion bestimmen  */
    printf("\t(%ld,%s) --> REDUCE(%s,%d)\n",(long)ZUSTNR(*z),decSym(sym),
                           decSym(ITEMSYM(lhs)),(int)ITEMLEN(lhs));
   }
  else  /* Shift auszufuehren */
    printf("\t(%ld,%s) --> SHIFT(%d)\n",(long)ZUSTNR(*z),decSym(sym),
                                      (int)ZUSTNR(*zzust));
#endif /* DEBUG */
  if (ZUSTNR(*zzust) == UNDEFZUSTNR)   
    PRODSTAT(prodNr(ueblis->item)) |= PS_REDUCE; 
  putUeb(z,sym,SHIFT,zzust,UNDEFITEM); /* SHIFT-Uebergang eintragen        */
 } /* berechneUeb */


/*====================================================================== */
/* Berechnung der LR(0)-Uebergaenge aus einem Zustand                     */
/*====================================================================== */
#ifdef __STDC__
static void lr0Ueberg(Zustand zust)
#else
static void lr0Ueberg(zust)
 Zustand zust;           /* Zustand, dessen Uebergaenge berechnet werden    */
#endif
 {
  register Item item;           /* zugehoeriges Item                        */
  register Symb sym;            /* zu lesendes Symbol                       */
  register Position pos;        /* momentan bearbeitete Position            */
  register Puebbaslis baseintr; /* Zeiger auf benutzte Uebergangsliste      */

#ifdef DEBUG
  printf("lr0Ueberg(%lx %ld)\n",zust,(long)ZUSTNR((*zust)));
#endif /* DEBUG */
#ifdef INCATTR
  gzust = zust;
#endif
 /* ------------------------------------------------------------------ */
 /* Uebergaenge in der provisorischen Tabelle anlegen                  */
 /* ------------------------------------------------------------------ */
  FOREACHPOS((*zust),pos)   /* Uebergaenge zu allen Positionen des Zustandes    */
   {
    item = POSITEM(*pos);   /* Item zu dieser Position bestimmen                */
#ifdef DEBUG
    printf(" p %lx i %ld=(",(long)pos,(long)item);
    fdecItem(stdout,item);
    printf(")\n");
#endif /* DEBUG */
   /* -------------------------------------------------------------- */
   /* direkten Uebergang eintragen                                   */
   /* -------------------------------------------------------------- */
    doUeb(item);                        /* direkten Uebergang bearbeiten      */
    if (ITEMLEN(item) != 0)             /* lesender Uebergang                 */
     {
      sym = ITEMSYM(item+1);            /* erstes zu lesendes Zeichen         */
#ifdef DEBUG
      printf("vor forAnsprung\n");
#endif /* DEBUG */
   /* -------------------------------------------------------------- */
   /* im nonterminalen Fall Anspruenge eintragen                     */
   /* -------------------------------------------------------------- */
      if (ISNONT(sym) )                 /* Nonterminal zu lesen        */
        forAnsprung(sym);               /* Produktionen anspringen     */
     } /* lesender Uebergang */
   } /* Uebergaenge zu allen Positionen dieses Zustandes */

 /* ------------------------------------------------------------------ */
 /* aus provisorischer Tabelle die konkreten Uebergaenge bestimmen     */
 /* ------------------------------------------------------------------ */
  for (baseintr = puebbas; baseintr != NULL; baseintr = baseintr->next)
   { /* fuer jedes zu lesende Symbol die Uebergaenge berechnen */
    berechneUeb(zust,baseintr->sym,baseintr->zielitems);
    baseintr->zielitems = NULL;    /* Uebergaenge leer                    */
   }
  puebbas = NULL;                  /* Ring frei fuer die naechste Runde   */
  if (EPSUEBS!=NULL)               /*spontane Uebergaenge vorhanden      */
   {
    berechneEpsueb(zust,EPSUEBS);  /* eps-Uebergaenge bearbeiten          */
    EPSUEBS = NULL;                /* eps-Uebergaenge leer                */
   }
#ifdef DEBUG
  printf("lr0Ueberg Ende\n");
#endif /* DEBUG */
 } /* lr0Ueberg */


/*====================================================================== */
/* Erzeugung des Startzustandes des Automaten und Abspeichern in der      */
/* Menge aller Zustaende                                                  */
/* Position :   METAAXIOM ::= . AXIOM RANDZCH                             */
/*====================================================================== */
#ifdef __STDC__
static void startZustand(Item item)
#else
static void startZustand(item)
 Item item;               /* Position des Startzustandes in der Grammatik   */
#endif
 {
  ZustRec zust;           /* anzulegender Automatenzustand                  */
  PosRec pos;             /* Position des Startzustandes                    */

#ifdef DEBUG
  printf("startZustand(%ld)\n",(long)item);
  printf("  zust %lx  pos %lx\n",(long)&zust,(long)&pos);

#endif /* DEBUG */
  POSITEM(pos) = item;    /* Item des Startzustandes                        */
 /* item des Startzustandes in zust aufnehmen                               */
  FIRSTPOS(zust) = NULL;  /* Positionsliste leer                            */
  eintragPosition(&FIRSTPOS(zust),&pos);
  putZustand(&zust);      /* Zustand in die Liste aller Zustaende aufnehmen */
 } /* startZustand */


/*====================================================================== */
/* Reservieren der Datenstrukturen fuer die provisorische Tabelle         */
/*====================================================================== */
#ifdef __STDC__
static void initLRKgen(void)
{
#else
static void initLRKgen()
 {
#endif
  register Symb sym;    /* Symbol, dessen Uebergaenge initialisiert werden */

  generrors = 0;        /* noch keine Fehler gemeldet                      */
  /* --------------------------------------------------- */
  /* Speicher fuer die Uebergangslisten reservieren      */
  /* --------------------------------------------------- */
  if ( (nontinvuebs = (NuebRec *)MALLOC((MAXN-MINN+1)*sizeof(NuebRec))) == NULL)
    mAbort(); 
  if ( (nontuebs = (Puebbas *)MALLOC((MAXN-MINN+1)*sizeof(Puebbas)) ) == NULL)
    mAbort(); 
  if ( (termuebs = (Puebbas *)MALLOC((MAXT-MINT+1)*sizeof(Puebbas)) ) == NULL)
    mAbort(); 
  /* --------------------------------------------------- */
  /* Uebergangslisten initialisieren                     */
  /* --------------------------------------------------- */
  FOREACHNONT(sym)
   {
    NONTINVUEB(sym) = NULL;         /* inverse Uebergangsliste leer      */
    NONTUEBS(sym).zielitems = NULL; /* nonterminale Uebergaenge leer     */
    NONTUEBS(sym).sym   = sym;      /* Symbolwert setzen                 */
   }
  FOREACHTERM(sym)
   {
    TERMUEBS(sym).zielitems = NULL; /* terminale Uebergaenge leer        */
    TERMUEBS(sym).sym   = sym;      /* Symbolwert setzen                 */
   }
  EPSUEBS = NULL;               /* eps-Uebergaenge leer                  */
  puebbas = NULL;               /* Liste aller Uebergaenge leer          */
 } /* initLRKgen */

/*====================================================================== */
/* Generierung der Uebergangsmatrix                                       */
/*   Rueckgabewert :  TRUE, falls erfolgreich                             */
/*                    FALSE, falls Fehler beim Generieren                 */
/*====================================================================== */
#ifdef __STDC__
BOOL LRKgen(void)
{
#else
BOOL LRKgen()
 {
#endif

  printf(" Pass 1 : Berechnung des LR(0)-Automaten\n");
  initLRKgen();                  /* Datenstrukturen bereitstellen             */
  epsErz();                      /* Epsilonerzeugende Nonterminale berechnen */
  initAlpharel();                /* Ansprungmodul initialisieren              */
  initZustaende();               /* Zustandsmodul initialisieren              */
  startZustand(METAPROD);        /* Anfang Metaproduktion als Startzustand    */
  /*-------------------------------------------------------------------- */
  /* Aufbau des mit Zusatzinformationen angereicherten LR0-Automaten      */ 
  /*-------------------------------------------------------------------- */
  while (neueZustaende())        /* solange neue Zustaende angelegt wurden    */
    lr0Ueberg(nextZustand() );   /* Uebergaenge aus diesem Zustand berechnen  */

  /*-------------------------------------------------------------------- */
  /* einige Abpruefungen koennen jetzt stattfinden                        */
  /*-------------------------------------------------------------------- */
  {
   register Nont n;              /* zu ueberpruefendes Nonterminal          */

   FOREACHNONT(n)
     if (n != METAAXIOM)         /* nichts beschimpfen, was selbst erzeugt  */
      {
       if (! ( NONTSTAT(n) & NS_TERMERZ) )
         mauleTerm(n);           /* leitet keine terminale Zeichenreihe her */
       if (! ( NONTSTAT(n) & NS_BENUTZT) )
         mauleBenutzt(n);        /* wird nicht benutzt                      */
      }
  }  

  /*-------------------------------------------------------------------- */
  /* Berechnung der noetigen Lookaheads fuer den LALR(k)-Automaten        */
  /*-------------------------------------------------------------------- */
  printf(" Pass 2 : Berechnung der Lookaheads\n");
  initLRKkont();                        /* Kontextmodul initialisieren       */
  {
    register Zustand zust;              /* bearbeiteter Zustand              */

    FOREACHLISTEL(firstZustand(),zust)  /* alle Zustaende bearbeiten         */
      if (ZUSTNR(*zust) != UNDEFZUSTNR) /* Zustand wird tatsaechlich benutzt */
        zUebergaenge(zust);             /* Uebergaenge berechnen             */
#ifdef INCATTR
    berechneLooks();
    FOREACHLISTEL(firstZustand(),zust)  /* alle Zustaende bearbeiten         */
      if (ZUSTNR(*zust) != UNDEFZUSTNR) /* Zustand wird tatsaechlich benutzt */
        zUebergaenge2(zust);            /* Uebergaenge berechnen             */
#endif
  }
  {
   register Prod p;              /* zu ueberpruefende Produktion            */

   FOREACHPROD(p)
     if (! ( PRODSTAT(p) & PS_REDUCE) )
      {
       mauleReduce(p);           /* wird nie reduziert                      */
      }
  }  
  return(!alleKonflikte());
 } /* LRKgen */


