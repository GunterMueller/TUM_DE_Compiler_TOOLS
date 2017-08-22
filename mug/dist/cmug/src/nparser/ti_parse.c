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
/* ti_parse.c :                                                           */ 
/* LR(k)-Parser-Tabellen-Interpreter                                      */ 
/* Modul : eigentlicher Interpreter                                       */ 
/* ---------------------------------------------------------------------- */ 
/* Aenderung : 23.12.89 , vollstaendig ueberarbeitet, Schnapschuesse      */ 
/* Aenderung : 23.07.89 , Fehlerbehandlung verbessert                     */ 
/* Aenderung : 22.07.89 (JG), Verbesserungen in Interpreterschleife       */ 
/*                            Fehlerbehandlung                            */ 
/* erstellt  : 09.07.89                                                   */ 
/* ********************************************************************** */

#ifdef __STDC__
#include <stddef.h>
#include <stdlib.h>
#endif
#include <stdio.h>
#include <time.h>
#include "defs.h"
#include "dbg.h"

#include "ti_token.h"
#include "scanfunk.h"
#include "ti_defs.h"
#include "ti_read.h"
#include "ti_zugr.h"
#include "ti_parse.h"
#include "ti_errs.h"

extern Ptab *atab;         /* aktuelle Tabelle                               */

#define MAXSIM 30          /* maximale Anzahl Interpreterschritte Simulation */

/* ---------------------------- */
/* Datentyp fuer Parser-Zustand */
/* ---------------------------- */
typedef struct {
        /* -------------------- */
        /* Verwaltung Token     */
        /* -------------------- */
        Zust   akt;        /* aktueller Zustand der Parsers               */
        Token  aktsym;     /* aktuelles Terminalzeichen                   */
        Token  nextsym;    /* naechstes Terminalzeichen, falls insert     */
        int    insert;     /* aktuelles Terminalzeichen war eingefuegt    */ 
        /* -------------------- */
        /* Tabelle und Zugriffe */
        /* -------------------- */
        Ptab   *tab;       /* Zeiger auf Parser-Tabelle                   */   
        Ueb    uebmsk;     /* Maske fuer Uebergangsart                    */
        Ueb    infmsk;     /* Maske fuer Uebergangsinformation            */
        Ueb    shiftueb;   /* Wert Shift-Uebergang                        */
        Ueb    redueb;     /* Wert Shift-Reduce-Uebergang                 */
        Ueb    spontueb;   /* Wert spontaner Reduce-Uebergang             */
        /* -------------------- */
        /* sonstiger Muell      */
        /* -------------------- */
        char *tstat;       /* Status aller zu testenden Terminalzeichen   */
        /* -------------------- */
        /* Semantik-Routinen    */
        /* -------------------- */
#ifdef __STDC__
        int (*scan)(Token);
        int (*outred)(long,long,long);
        int (*outterm)(Token);
#else
        int (*scan)();
        int (*outred)();
        int (*outterm)();
#endif
        /* -------------------- */
        /* eigentlicher Keller  */
        /* -------------------- */
	Zust   *stack;     /* Array der Kellereintraege                   */
	Uint32 top;        /* Kellerzeiger, Index oberster Eintrag        */
	Uint32 len;        /* aktuelle Kellerlaenge                       */
        /* --------------------- */
        /* letzter Schnappschuss */
        /* --------------------- */
        int    in_snap;    /* Schnappschuss aktiviert                     */
	Zust   *sav;       /* Array der geretteten Kellereintraege        */
	Uint32 stop;       /* Kellerzeiger zum Zeitpunkt der Aufnahme     */
	Uint32 mtop;       /* bisher kleinster Kellerzeiger               */
        Uint32 sanz;       /* Anzahl gerettete Eintraege                  */
	Uint32 slen;       /* Aktuelle Groesse sav                        */
        Prod   *sred;      /* gemerkte Reduktionen                        */
        Uint32 nreds;      /* Anzahl gemerkte Reduktionen                 */
        Uint32 rlen;       /* Aktuelle Groesse sred                       */
	} Pstate;

/* Groesseneinheit, in der Keller angelegt und verlaengert wird           */
#define KLENUNIT ((unsigned)1024)

/* Groesseneinheit, in der Schnappschuss angelegt und verlaengert wird    */
#define SLENUNIT ((unsigned)64)

/* Groesseneinheit, in der Reduktionsliste angelegt und verlaengert wird  */
#define RLENUNIT ((unsigned)64)

/* Pop-Operation                                          */
#define POP_KELLER(s,len) {(s).top -= len}

/* Zugriff auf obersten Eintrag                           */
#define TOP_KELLER(s) (s).stack[(s).top]

/* Zugriff auf aktuellen Zustand                          */
#define AKT_ZUST(s) (s).akt

/* Zugriff auf Klassencode des aktuellen Terminalzeichens */
#define AKT_SYM(s)  SYM((s).aktsym)

/* maximale Anzahl gezeigter Kellereintraege                         */
#define MAX_KSHOW 4

/* maximale Anzahl der Reduktionsversuche bei Fehlerbehandlung       */
#define MAXREDS 5

/* Randzeichen */
#define EOFSY ((Term)0)

/* ===================================================================== */
/* Datenstrukturen initialisiert bereitstellen                           */
/* Rueckgabe : Initialisierung erfolgreich                               */
/* ===================================================================== */
#ifdef __STDC__
static int initState(Pstate *s)
#else
static int initState(s)
 Pstate *s;  /* zu initialisierende Datenstruktur */
#endif
 {
  DBGPRT(( "initState\n"));
  /* -------------------------------------------- */
  /* alle Pointer auf NULL setzen, fuer Freigaben */
  /* -------------------------------------------- */
  s->stack   = NULL;
  s->sav     = NULL;
  s->sred    = NULL;
  s->aktsym  = NULL;
  s->nextsym = NULL;
  s->tstat   = NULL;
  /* ---------------------------------- */
  /* eigentlichen Keller initialisieren */
  /* ---------------------------------- */
  s->len = KLENUNIT;      /* initiale Laenge des Kellers            */
  if ((s->stack = (Zust *)malloc((unsigned)(s->len*sizeof(Zust))) ) == NULL)
    return(FALSE);
  s->top = 0;             /* keine Eintraege vorhanden              */
  s->akt = 0;             /* Startzustand                           */
  /* ---------------------------------- */
  /* Schnappschuss initialisieren       */
  /* ---------------------------------- */
  s->in_snap = FALSE;     /* Schnappschuss nicht aktiviert          */
  s->slen = SLENUNIT;     /* initiale Laenge gerettete Eintraege    */
  if ((s->sav = (Zust *)malloc((unsigned)(s->slen*sizeof(Zust))) ) == NULL)
    return(FALSE);
  s->stop = 0; 
  s->mtop = 0; 
  s->sanz = 0;
  s->rlen = RLENUNIT;     /* initiale Laenge gemerkte Reduktionen   */
  if ((s->sred = (Prod *)malloc((unsigned)(s->rlen*sizeof(Prod))) ) == NULL)
    return(FALSE); 
  s->nreds = 0;
  if ((s->aktsym = allocToken() ) == NULL ||
      (s->nextsym = allocToken() ) == NULL ||
      (s->tstat = (char *)malloc((unsigned)(s->tab->tmax+1))) == NULL)
    return(FALSE);
  s->insert    = FALSE;   /* kein Zeichen eingefuegt                */
  return(TRUE);
 } /* initState */

/* ===================================================================== */
/* Freigabe alle allokierten Datenstrukturen                             */
/* ===================================================================== */
#ifdef __STDC__
static void freeState(Pstate *s)
#else
static void freeState(s)
 Pstate *s;  /* freizugebende Datenstruktur */
#endif
 {
  if (s->stack   != NULL) free(s->stack);
  if (s->sav     != NULL) free(s->sav);
  if (s->sred    != NULL) free(s->sred);
  if (s->aktsym  != NULL) freeToken(s->aktsym);
  if (s->nextsym != NULL) freeToken(s->nextsym);
  if (s->tstat   != NULL) free(s->tstat);
 } /* freeState */

/* ===================================================================== */
/* Push-Operation in SNAPSHOT, Snap noetigenfalls verlaengern             */
/* ===================================================================== */
#ifdef __STDC__
static int pushSnap(Pstate *s,Zust z)
#else
static int pushSnap(s,z)
 Pstate *s;
 Zust z;
#endif
 {
  if (s->sanz+1 >= s->slen) /* muss verlaengert werden */
   {
    s->slen += SLENUNIT;
    if ((s->sav = (Zust *)realloc((char *)s->sav,
                  (unsigned)(s->slen*sizeof(Zust))) ) == NULL) 
      return(FALSE);
   }
  s->sav[s->sanz++] = z;
  return(TRUE);
 } /* pushSnap */

/* ===================================================================== */
/* Push-Operation, akt kellern, Keller noetigenfalls verlaengern         */
/* Rueckgabe : erfolgreich ausgefuehrt                                   */
/* ===================================================================== */
#ifdef __STDC__
static int pushKeller(Pstate *s,Zust zust)
#else
static int pushKeller(s,zust)
 Pstate *s;   /* Syntaxkeller  */
 Zust   zust; /* neuer Zustand */
#endif
 {
  DBGPRT(("pushKeller(%ld)\n",(long)zust));
  if (s->top+1 >= s->len) /* Keller muss vergroessert werden */
   {
    s->len += KLENUNIT;
    if ((s->stack = (Zust *)realloc((char *)s->stack,
                    (unsigned)(s->len*sizeof(Zust))) ) == NULL) 
      return(FALSE);
   }
  s->stack[s->top++] = s->akt; /* aktuellen Zustand kellern */
  s->akt = zust;               /* neuen Zustand eintragen   */
  return(TRUE);
 } /* pushKeller */

/* ===================================================================== */
/* Reduktion ausfuehren, in Schnappschuss merken                         */
/* ===================================================================== */
#ifdef __STDC__
static int reduceKeller(Pstate *s,Prod prod,int spont,int sim)
#else
static int reduceKeller(s,prod,spont,sim)
 Pstate *s;    /* Parserzustand                */
 Prod   prod;  /* zu reduzierende Produktion   */
 int    spont; /* Reduktion sponan             */
 int    sim;   /* simuliert (Fehlerbehandlung) */
#endif
 {
  Plen len;    /* Laenge von prod            */

  len  =  PRLEN(*s->tab,prod);
  IFDEBUG
  ({
    Nont nont;

    nont = PRLHS(*s->tab,prod);
    DBGPRT(("reduceKeller(prod %ld,lhs %s,len %ld,%s)\n",(long)prod,
            decNont(nont),(long)len,spont?"spont":"shift"));
  })
  if (!s->in_snap && !sim) /* sofort an Semantikteil melden */
   {
    Nont nont;             /* linke Seite von prod          */

    nont =  PRLHS(*s->tab,prod);
    s->outred((long)(prod+1),(long)nont,(long)len);
   }
  if (!spont)  /* kombiniertes SHIFT/REDUCE      */
    len--;     /* letzer Zustand nicht geshiftet */
  if (len)
   {
    if (s->top < len)
     { 
      internFehler(ierrKUL,s->aktsym); /* Kellerunterlauf */
      return(FALSE);
     }
    if (s->in_snap)
     {
      while(len--)
       {
        if (s->top < s->mtop)
         { /* zu rettende Eintraege vorhanden */
          s->mtop = s->top;
          if (!pushSnap(s,TOP_KELLER(*s)))
            return(FALSE);
         }
        s->top--;
       }
     } /* s->in_snap */
    else
      s->top -= len;
    AKT_ZUST(*s) = TOP_KELLER(*s);
   }
  if (s->in_snap && !sim)
   {
    /* ------------------------ */
    /* Reduktionen merken       */
    /* ------------------------ */
    if (s->nreds+1 >= s->rlen) /* muss verlaengert werden */
     {
      s->rlen += SLENUNIT;
      if ((s->sred = (Prod *)realloc((char *)s->sred,
                    (unsigned)(s->rlen*sizeof(Prod))) ) == NULL) 
        return(FALSE);
     }
    s->sred[s->nreds++] = prod;
   } /* reduktionen merken */
  return(TRUE);
 } /* reduceKeller */

/* ===================================================================== */
/* Anfang eines neuen Schnappschusses                                    */
/* ===================================================================== */
#ifdef __STDC__
static int beginSnap(Pstate *s)
#else
static int beginSnap(s)
 Pstate *s;
#endif
 {
  DBGPRT(("beginSnap()\n"));
  s->sanz   = 0;             /* Anzahl gerettete Zustaende          */
  if (!pushSnap(s,s->akt))   /* aktuellen Zustand retten            */
    return(FALSE);
  s->stop   = s->top;        /* Kellerzeiger merken                 */ 
  s->mtop   = s->top;        /* als kleinsten Kellerzeiger merken   */ 
  if (s->nreds) 
    fprintf(stderr,"beginSnap() : nreds = %ld\n",(long)s->nreds);
  s->nreds  = 0;             /* noch keine Reduktionen gemerkt      */
  s->in_snap = TRUE;         /* Modus merken                        */
  return(TRUE);
 } /* beginSnap */

/* ===================================================================== */
/* Parser-Zustand aus Schnappschuss wiederherstellen                     */
/* ===================================================================== */
#ifdef __STDC__
static void restoreSnap(Pstate *s)
#else
static void restoreSnap(s)
 Pstate *s;
#endif
 {
  Uint32 i,t;

  if (s->in_snap)  /* Schnappschuss vorhanden */
   {
    for (t = s->mtop,i = s->sanz - 1; i > 0; i--,t++)
     {
      s->stack[t] = s->sav[i];
     }
    AKT_ZUST(*s) = s->sav[0];  /* aktueller Zustand zurueck           */
    s->top    = s->stop;       /* Kellerzeiger restaurieren           */ 
    s->nreds  = 0;             /* keine Reduktionen mehr gemerkt      */
    s->in_snap = FALSE;
   }
 } /* restoreSnap */



/* ===================================================================== */
/* verzoegerte Reduktionen melden                                        */
/* ===================================================================== */
#ifdef __STDC__
static void execSnap(Pstate *s)
#else
static void execSnap(s)
 Pstate *s;
#endif
 {
  Uint32 rnr;

  if (s->in_snap)
   {
    for (rnr = 0; rnr < s->nreds; rnr++)
     { /* gemerkte Reduktionen an Semantikteil */
      Prod prod;   /* Produktion                 */
      Nont nont;   /* linke Seite von prod       */
      Plen len;    /* Laenge von prod            */

      prod =  s->sred[rnr];  /* zu reduzierende Produktion          */
      nont =  PRLHS(*s->tab,prod);
      len  =  PRLEN(*s->tab,prod);
      s->outred((long)(prod+1),(long)nont,(long)len);
     } /* for */
    s->in_snap = FALSE;
    s->nreds   = 0;
   } /* if */
 } /* execSnap */


/* ===================================================================== */
/* das Terminalsymbol aktsym wurde korrekt verarbeitet                   */
/* verzoegerte Semantikroutinen aufrufen                                 */                 
/* Schnappschuss ausfuehren                                              */
/* oberster geretter Zustand ist akt                                     */    
/* Rueckgabe : erfolgreich ausgefuehrt                                   */
/* ===================================================================== */
#ifdef __STDC__
static int nextSym(Pstate *s)
#else
static int nextSym(s)
 Pstate *s;
#endif
 {
  Token h;                      /* Hilfsvariable fuer Dreickstausch    */

  execSnap(s);                  /* Reduktionen melden                  */
  s->outterm(s->aktsym);        /* an Semantikteil melden              */
  if (s->insert)                /* aktsym war eingefuegt               */
   {
    s->insert = FALSE;
    h = s->aktsym;
    s->aktsym  = s->nextsym;
    s->nextsym = h;
   } 
  else 
    s->scan(s->aktsym);         /* neues Terminalsymbol lesen          */
  return(TRUE);
 } /* nextSym */

/* ===================================================================== */
/* Simulation des Parsens mit geaenderter Eingabe tsym + AKT_SYM(*s)     */
/* Rueckgabe 0 : tsym kann nicht gelesen werden                          */
/*           1 : tsym kann gelesen werden, aktsym nicht                  */
/*           2 : tsym und aktsym koennen gelesen werden                  */
/* ===================================================================== */
#ifdef __STDC__
static int simParse(Pstate *s,Term tsym,Ueb ueb)
#else
static int simParse(s,tsym,ueb)
 Pstate *s;   /* Ausgangszustand Simulation          */
 Term   tsym; /* naechstes terminales Eingabezeichen */
 Ueb    ueb;  /* Uebergang mit tsym                  */
#endif
 {
  Ueb  uebart;   /* Art des aktuellen Ueberganges    */
  BOOL nv;       /* Nonterminal in Eingabe vorhanden */
  int  gelesen;  /* Anzahl gelesener Terminalsymbole */  
  int  simanz;   /* Anzahl Schritte des Simulators   */

#define AKTSYM (gelesen?AKT_SYM(*s):tsym)

  DBGPRT(("simparse %s %s, stk = %ld\n",
           decTerm(tsym),decTerm((Term)(AKT_SYM(*s))),(long)s->top));
  gelesen = 0;
  nv      = FALSE;
  simanz  = 0;
  while (TRUE)   /* beendet durch return-Anweisungen */
   /* ---------------------- */
   /* Interpreterschleife    */
   /* ---------------------- */
   {
    DBGPRT(("z %ld, e %s%s\n",(long)AKT_ZUST(*s),
            nv?"nont ":"",decTerm((Term)(AKTSYM)) ));
    if (simanz++ > MAXSIM)            /* timeout                       */
      return(0);
    uebart  = ueb & s->uebmsk;        /* Art des Uebergangs            */
    if (uebart == s->shiftueb)
     { /* Shift-Uebergang           */
      if (!nv &&                   /* Terminalzeichen gelesen             */
          (gelesen ||              /* Simulation beendet                  */
           AKTSYM == EOFSY))       /* Randzeichen verarbeitet, akzeptiert */
       {
        DBGPRT((" = %d\n",gelesen+1));
        return(gelesen+1);         /* erfolgreiches Parsen melden         */
       }
      else
       {
        if (nv)                                     /* Nonterm verarbeitet    */
          nv = FALSE;       
        else
          gelesen++;                 /* aktuelles Terminalzeichen verarbeitet */
        if (!pushKeller(s,(Zust)(ueb & s->infmsk))) /* angesprungener Zustand */
          return(gelesen);
        ueb = getTueb(AKT_ZUST(*s),(Term)AKTSYM);
       }
     } /* Shift-Uebergang */
    else if (ueb)
     { /* Reduktion                 */
      Prod prod;   /* zu reduzierende Produktion */
      Nont nont;   /* linke Seite von prod       */

      prod = ueb & s->infmsk;        /* zu reduzierende Produktion          */
      if (uebart == s->redueb)       /* Shift-Reduce                        */
       {                      
        if (!nv &&                   /* Terminalzeichen gelesen             */
          (gelesen ||                /* Simulation beendet                  */
           AKTSYM == EOFSY))         /* Randzeichen verarbeitet, akzeptiert */
         {
          DBGPRT((" = %d\n",gelesen+1));
          return(gelesen+1);         /* erfolgreiches Parsen melden         */
         }
        else
         {
          if (nv)                  /* Symbol war nonterminal                */
            nv = FALSE;            /* Nonterminal verarbeitet               */
          else
            gelesen++;             /* aktuelles Terminalzeichen verarbeitet */
          if (!reduceKeller(s,prod,FALSE,TRUE))
            return(gelesen);
         }
       } /* Shift-Reduce */
      else if (uebart == s->spontueb) /* spontane Reduktion                  */
       {
        if (!reduceKeller(s,prod,TRUE,TRUE))
          return(gelesen);
       }
      else /* interner Fehler */
       {
        internFehler(ierrUGU,s->aktsym); /* ungueltiger Uebergang */
        return(0);
       }
      nv   = TRUE;                           /* Nonterminal in der Eingabe */
      nont = PRLHS(*s->tab,prod);
      ueb  = getNueb(AKT_ZUST(*s),nont);     /* naechster Uebergang        */
     } /* Reduktion */
    else 
    /* ueb == 0 , kein Uebergang */
     {
      DBGPRT((" = %d\n",gelesen));
      return(gelesen);  /* mehr gibts nicht */
     }
   } /* while TRUE */
  return(0);
 } /* simParse */

/* ===================================================================== */
/* Fehlerbehandlung                                                      */
/* Rueckgabe : neuen Uebergang nach Fehlerbehandlung                     */
/*             0, falls Wiederaufsetzen nicht moeglich                   */
/* ===================================================================== */
#ifdef __STDC__
static Ueb fehlerBehandlung(Pstate *s)
#else
static Ueb fehlerBehandlung(s)
 Pstate *s;
#endif
 {
  Term   tsym;    /* zu testendes Terminalzeichen                 */
  Ueb    tueb;    /* Uebergang mit tsym                           */
  Uint32 anzins;  /* Anzahl der moeglichen inserts                */
  Uint32 anzles;  /* Anzahl der lesbaren Symbole                  */
  Term   isym;    /* ggf. einzufuegendes Symbol                   */
  Term   esym;    /* ggf. erwartetes Symbol                       */

  /* Statuswerte der Terminalzeichen */
#define NOINSERT 2
#define GOODTERM 1

  DBGPRT(("fehlerBehandlung aus Zustand %ld\n",(long)AKT_ZUST(*s) ));
  FOR_EACHTERM(*s->tab,tsym)
    s->tstat[tsym] = 0;  /* Tabelle initialisieren */
  END_EACHTERM
  do  /* bis zum Wiederaufsetzen */
   {
    if (s->insert)
     {
      internFehler(ierrINS,s->aktsym); /* kein Uebergang mit eingefuegtem Symbol */
      return((Ueb)0);
     }
    anzins = 0;   /* keine Einfuegungen                          */
    anzles = 0;   /* Anzahl der lesbaren Terminalzeichen         */
    /* -------------------------------------------------------------------- */
    /* Feststellen, welche Symbole direkt lesbar und evtl. einfuegbar sind  */
    /* -------------------------------------------------------------------- */
    if (s->tstat[AKT_SYM(*s)] & NOINSERT)
     { /* aktsym sicher falsch */
      if (AKT_SYM(*s) == EOFSY)
       {
        DBGPRT(("  # unerwartetes Dateiende, Abbruch\n"));
        dateiEnde(s->aktsym); 
        return((Ueb)0);
       }
      else
       {
        DBGPRT(("  # %s ignoriert\n",decTerm((Term)(AKT_SYM(*s))) ));    
        symIgnoriert(s->aktsym);
        s->scan(s->aktsym);        /* naechstes Zeichen lesen */
        if (s->tstat[AKT_SYM(*s)]) /* kann gelesen werden     */
         {
          if (tueb = getTueb(AKT_ZUST(*s),AKT_SYM(*s)))
           {
            DBGPRT(("  # Wiederaufsetzen bei %s\n",
                    decTerm((Term)(AKT_SYM(*s))) ));   
            wiederAufsetzen(s->aktsym);
           }
         }
        else
          tueb = 0;
       }
     }
    else
     { /* Einfuegung evtl. noch moeglich */
      int sim;  /* Ergebnis von simParse() */

      FOR_EACHTERMUEB(*s->tab,AKT_ZUST(*s),tsym,tueb)
        if (tsym != AKT_SYM(*s))
         {
          anzles++;
          esym = tsym;        /* Symbol merken, falls eindeutig       */
          if (!beginSnap(s))  /* Ausgangszustand merken               */
            return((Ueb)0);
          if (sim = simParse(s,tsym,tueb))
           {
            s->tstat[tsym] |= GOODTERM;
            if (sim > 1)
             {
              anzins++;    /* als einzufuegendes Zeichen geeignet */
              isym = tsym; /* Symbol merken, falls eindeutig       */
             }
           }
          DBGPRT(("  - %s : %d gelesen, Zielzust  %ld \n",
                  decTerm(tsym),(int)s->tstat[tsym],(long)AKT_ZUST(*s) ));
          restoreSnap(s); /* Ausgangszustand wiederherstellen */
         }
      END_EACHTERMUEB
    
      if ((tueb = TDEF(*s->tab,AKT_ZUST(*s)) ) != 0)
       {
        /* --------------------------------------------------- */
        /* default-Symbole untersuchen                         */
        /* der Uebergang tueb kann nur vom Typ spontueb sein ! */
        /* --------------------------------------------------- */
        DBGPRT((" - default\t" ));
        DBGPRT(("SPONTRED(%ld)\n",(long)tueb & s->infmsk));
        FOR_EACHTERM(*s->tab,tsym)
          if (tsym != AKT_SYM(*s) && ! s->tstat[tsym] )
           { /* nicht bereits abgelehnt bzw. akzeptiert */
            if (!beginSnap(s))  /* Ausgangszustand merken */
              return((Ueb)0);
            if (sim = simParse(s,tsym,tueb))
             {
              anzles++;
              s->tstat[tsym] |= GOODTERM;
              esym = tsym;   /* Symbol merken, falls eindeutig       */
              DBGPRT(("  - %s : %d gelesen, Zielzust  %ld \n",
                      decTerm(tsym),(int)s->tstat[tsym],(long)AKT_ZUST(*s) ));
              if (sim > 1)
               {
                anzins++;    /* als einzufuuegendes Zeichen geeignet */
                isym = tsym; /* Symbol merken, falls eindeutig       */
               }
             }
            restoreSnap(s); /* Ausgangszustand wiederherstellen */
           } /* nicht bereits abgelehnt bzw. akzeptiert */
        END_EACHTERM
       } /* default-Uebergaenge */
    /* ------------------------------------------------------------- */
    /* Wiederaufsetzen durch Einfuegen oder Loeschen von Symbolen    */
    /* ------------------------------------------------------------- */
      if (anzins == 1)
       { /* Einfuegen eindeutig moeglich */
        Token h;

        h          = s->aktsym;  /* Token tauschen       */
        s->aktsym  = s->nextsym;
        s->nextsym = h;
        SYM(s->aktsym) = isym;      /* Eingabe modifizieren */
	setTokeninvalid(s->aktsym); /* ungueltig markieren  */
        s->insert  = TRUE;       /* Einfuegen merken     */
        DBGPRT(("### %s eingefuegt\n",decTerm(isym) ));
        symEinfuegen(isym,s->aktsym);
        tueb = getTueb(AKT_ZUST(*s),isym);
       }
      else
       { /* kein Einfuegen */
        s->tstat[AKT_SYM(*s)] |= NOINSERT; /* fuer spaeter merken */
        if (anzles == 1)
         {
          if (esym == EOFSY)
           {
            DBGPRT(("  # Rest nach akzeptierter Eingabe ignoriert\n"));
            restIgnoriert();
            SYM(s->aktsym) = EOFSY; /* Parsen abwuergen */
            return((Ueb)(getTueb(AKT_ZUST(*s),esym)) );
           }
          else
           {
            DBGPRT(("  # %s erwartet\n",decTerm(esym)));
            symErwartet(esym);
           }
         }
        if (AKT_SYM(*s) == EOFSY)
         {
          DBGPRT(("  # unerwartetes Dateiende, Abbruch\n"));
          dateiEnde(s->aktsym);
          return((Ueb)0);
         }
        else
         {
          DBGPRT(("  # %s ignoriert\n",decTerm((Term)(AKT_SYM(*s))) ));    
          symIgnoriert(s->aktsym);
          s->scan(s->aktsym);        /* naechstes Zeichen lesen */
          if (s->tstat[AKT_SYM(*s)] & GOODTERM) /* kann gelesen werden     */
           {
            if (tueb = getTueb(AKT_ZUST(*s),AKT_SYM(*s)))
             {
              DBGPRT(("  # Wiederaufsetzen bei %s\n",
                      decTerm((Term)(AKT_SYM(*s))) ));   
              wiederAufsetzen(s->aktsym);
             }
           }
          else
            tueb = 0;
         }
       } /* kein Einfuegen */
     } /* Einfuegung evtl. noch moeglich */
   } while (!tueb);
  return(tueb);
 } /* fehlerBehandlung */

/* ===================================================================== */
/* eigentliche Parserroutine                                             */
/* Rueckgabewert : 0, falls Syntaxanalyse abgebrochen                    */
/*              != 0, falls (inkl. Fehlerbehandlung) Satz gelesen        */
/* ===================================================================== */
#ifdef __STDC__
int ti_parse(Ptab *tab,int (*scan)(Token),
             int (*outred)(long,long,long),int (*outterm)(Token) )
#else
int ti_parse(tab,scan,outred,outterm)
 Ptab *tab;                       /* zu interpretierende Tabelle */
 int (*scan)();                   /* zugehoerige Scannerroutine  */
 int (*outred)();
 int (*outterm)();
#endif
 {
  Pstate s;          /* Parserzustand                               */
  Ueb    ueb;        /* auszufuehrender Uebergang                   */
  Ueb    uebart;     /* Art von ueb                                 */
  BOOL   nv;         /* Nonterminal in der Eingabe ?                */

  DBGPRT(( "ti_parse\n"));
  s.tab = tab;                           /* Tabelle global zugaenglich      */
  atab  = tab;                           /* Tabelle global zugaenglich      */
 /* Masken berechnen */
  zugrMask(&s.uebmsk,&s.infmsk,&s.shiftueb,&s.redueb,&s.spontueb); 
  /* ------------------------------------------------- */
  /* Initialisierung von s etc.                   */
  /* ------------------------------------------------- */
  if (!initState(&s))                  /* s initialisieren            */
   {
    freeState(&s); /* Datenstrukturen freigeben     */
    memError();
    return(FALSE);
   }
  nv           = FALSE;                /* kein Nonterminal in der Eingabe */
  scan(s.aktsym);                      /* erstes Token lesen              */
  ueb = getTueb(AKT_ZUST(s),(Term)AKT_SYM(s));/* Uebergang damit      */

  s.outred  = outred;
  s.outterm = outterm;
  s.scan    = scan;

  while (TRUE)   /* beendet durch return-Anweisungen */
   /* ---------------------- */
   /* Interpreterschleife    */
   /* ---------------------- */
   {
    DBGPRT(( "Zust %ld Eingabe %s ",(long)AKT_ZUST(s),
             nv?"Nont":decTerm((Term)AKT_SYM(s)) ));
    IFDEBUG
    ({
      Int32 i;
      for (i = (Int32)s.top-1; 
           i >= 0 && i >= (Int32)s.top - MAX_KSHOW; 
           i--)
        DBGPRT(( "<%ld>",(long)s.stack[i] ));
      if (i<0)
        DBGPRT(( "\n" ));
      else
        DBGPRT(( "...\n"));
    })

    uebart  = ueb & s.uebmsk;            /* Art des Uebergangs            */
    if (uebart == s.shiftueb)
    /* ------------------------- */
    /* Shift-Uebergang           */
    /* ------------------------- */
     {
      if (!nv && AKT_SYM(s) == EOFSY)
       /* Randzeichen verarbeitet, akzeptiert */
       {
        execSnap(&s);                  /* Reduktionen melden                  */
        DBGPRT(( "AKZEPT\n" ));
        freeState(&s);                 /* Datenstrukturen freigeben           */
        return(TRUE);                  /* erfolgreiches Parsen melden         */
       }
      else
       {
        if (nv)                                /* Nonterminal verarbeitet     */
          nv = FALSE;       
        else
         /* -------------------------------------------------------- */
         /* Terminalzeichen geshiftet, merken, bis folgendes gelesen */
         /* -------------------------------------------------------- */
         {
          if (!nextSym(&s))                         /* naechstes Eingabezeichen    */
           {
            freeState(&s); /* Datenstrukturen freigeben     */
            return(FALSE);
           }
         }
        if (!pushKeller(&s,(Zust)(ueb & s.infmsk))) /* angesprungener Zustand */
         {
          freeState(&s); /* Datenstrukturen freigeben     */
          memError();
          return(FALSE);
         }
        DBGPRT(( "SHIFT(%ld)\n",(long)AKT_ZUST(s) ));
       /* naechster Uebergang         */
        ueb = getTueb(AKT_ZUST(s),(Term)AKT_SYM(s));
       }
     } /* Shift-Uebergang */
    else if (ueb)
    /* ------------------------- */
    /* Reduktion                 */
    /* ------------------------- */
     {
      Prod prod;   /* zu reduzierende Produktion */
      Nont nont;   /* linke Seite von prod       */

      prod = ueb & s.infmsk;            /* zu reduzierende Produktion          */
      if (uebart == s.redueb)
       /* ------------------------- */
       /* Shift-Reduce              */
       /* ------------------------- */
       {	
        if (! nv && AKT_SYM(s) == EOFSY) /* Randzeichen, akzeptiert */
         {
          execSnap(&s);
          DBGPRT(( "AKZEPT\n" ));
          freeState(&s);              /* Datenstrukturen freigeben           */
          return(TRUE);               /* erfolgreiches Parsen melden         */
         }
        else
         { /* ausgelassenen Shift-Uebergang an Semantik melden */
          if (nv) /* Symbol war nonterminal */
            nv = FALSE;              /* Nonterminal verarbeitet             */
          else
           /* -------------------------------------------------------- */
           /* Terminalzeichen geshiftet, merken, bis folgendes gelesen */
           /* -------------------------------------------------------- */
            if (!nextSym(&s))               /* naechstes Eingabezeichen    */
             {
              freeState(&s); /* Datenstrukturen freigeben     */
              return(FALSE);
             }
          DBGPRT(( "REDUCE(%ld)\n",(long)prod ));
          if (!reduceKeller(&s,prod,FALSE,FALSE))
           {
            freeState(&s); /* Datenstrukturen freigeben     */
            memError();
            return(FALSE);
           }
         }
       } /* Shift-Reduce */
      else if (uebart == s.spontueb)
       /* -------------------------------------------------- */
       /* spontane Reduktion                                 */
       /* Zustand merken, Terminalzeichen nicht verarbeitet  */
       /* -------------------------------------------------- */
       {
        DBGPRT(( "SPONTRED(%ld)\n",(long)prod ));
        if ( !(s.in_snap || beginSnap(&s)) ||
            !reduceKeller(&s,prod,TRUE,FALSE))
         {
          freeState(&s); /* Datenstrukturen freigeben     */
          memError();
          return(FALSE);
         }
       }
      else
       {
        internFehler(ierrUGU,s.aktsym); /* ungueltiger Uebergang */
        freeState(&s); /* Datenstrukturen freigeben     */
        return(FALSE);
       }
      nv   = TRUE;                           /* Nonterminal in der Eingabe */
      nont =  PRLHS(*s.tab,prod);
      ueb  = getNueb(AKT_ZUST(s),nont); /* naechster Uebergang        */
     } /* Reduktion */
    else 
    /* ---------------------------------------- */
    /* ueb == 0 , kein Uebergang, Syntaxfehler  */
    /* ---------------------------------------- */
     {
      if (nv) /* Fehler mit Nonterminal, verdaechtig bis kriminell */
       {
        internFehler(ierrNON,s.aktsym); /* kein Uebergang mit Nonterminal */
        freeState(&s); /* Datenstrukturen freigeben     */
        return(FALSE);
       }
      else /* Syntaxfehler */
       {
        DBGPRT(( "### Syntaxfehler bei Symbol %s\n",
                 decTerm((Term)AKT_SYM(s)) ));
        fehlerAnf(s.aktsym);
        if (s.in_snap)
          restoreSnap(&s); /* mit restauriertem Zustand           */
        if ((ueb = fehlerBehandlung(&s)) == 0) 
         {
          freeState(&s); /* Datenstrukturen freigeben     */
          return(FALSE); /* kein Wiederaufsetzen moeglich */ 
         }
       } /* Syntaxfehler */
     } /* kein Uebergang */	
   } /* while TRUE */
  return(FALSE);          /* um ueberempfindliche Compiler zu beruhigen */
 } /* ti_parse */

