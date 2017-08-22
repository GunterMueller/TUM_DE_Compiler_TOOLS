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


/* ******************************************************* */
/* readgakt.c  :                                           */
/* Semantische Aktionen fuer Wort-Grammatikleser ReadG     */
/* Aenderung 11.01.91, Ulrich Vollath: CMUG-Schnittstellen */
/* Aenderung :  28.10.90, Ausgabepuffer                    */
/* Aenderung :  27.10.90, Anpassung an readg / lrkgen      */
/* Aenderung :  12.08.89, Ausgabe beschleunigt             */
/* Aenderung :  10.6.89 , Korrekturen bzgl. Aktionen       */
/* erstellt  :  1.3.89                                     */
/* ------------------------------------------------------- */
/* Kennzeichnung von Ausgaben in die Internformdatei mit   */
/*   Kommentaren :  ......................                 */
/* ******************************************************* */
#ifdef __STDC__
#include <stddef.h>
#include <stdlib.h>
#endif
#include <fcntl.h>
#include <stdio.h> 
#include <string.h>

/*#define TIMING*/
#ifdef TIMING
#include "millisec.h"
#endif
#include "defs.h"                   /* diverse Definitionen                   */
#include "magics.h"                 /* magische Nummern fuer Dateiformate     */
#include "ti_defs.h"
#include "ti_zugr.h"
#include "ps_token.h"
#include "ti_parse.h"
extern Ptab lalr_tab;   /* zugelinkte Parsertabelle                          */
FILE *ScanEin;
#define parsAbort(m) do{fputs(m,stderr);fputc('\n',stderr);\
                        exit(20);}while(0)
#include "scanfunk.h"
#include "semfunk.h"
#include "parsfunk.h"
#include "readg.grm.h"              /* #defines fuer Aktionsnummern           */

/* ====================================================================== */
/* Definitionen fuer den Ausgabepuffer                                    */
/* ====================================================================== */
/* Laengeneinheit fuer den Ausgabepuffer */
#define BUFFER_LEN 20000L
static char *out_buf;   /* Ausgabepuffer                           */
static long outbuf_len; /* Aktuelle Laenge Ausgabepuffer           */
static long outbuf_ptr; /* Index naechstes zu schreibendes Zeichen */

/* ====================================================================== */
/* Definitionen der numerischen Werte fuer die erzeugte Ausgabedatei      */     
/* ====================================================================== */
/* am Produktionsende (eine rechte Seite) ausgegebene Zeichenreihe            */
#define DELIM_PROD  "0\n"
/* am Regelende (rechte Seiten zu einem Nonterminal) ausgegebene Zeichenreihe */
#define DELIM_REGEL "-1\n"
/* Kombination von DELIM_PROD + DELIM_REGEL                                   */
#define DELIM_PROD_REGEL  " 0 -1\n"
/* am Ende aller Regeln ausgegebene Zeichenreihe                              */
#define DELIM_GRAMM  "-2\n"

/* ====================================================================== */
/* Definitionen der numerischen Bereiche fuer die Symbole                 */     
/* ACHTUNG : Kompatibilitaet mit den Datentypen und Nichtueberlappung     */
/* mit oben definierten Delimitern beachten                               */
/* ====================================================================== */
/* erste verwendete Nummer fuer Terminalzeichen                    */
#define MIN_TERM    1
/* groesste verwendbare Nummer fuer Terminalzeichen                */
#define MAX_TERM    32000
/* erste verwendete Nummer fuer Nonterminalzeichen + Aktionen      */
#define MIN_NONT    (-32000)
/* groesste verwendbare Nummer fuer Nonterminalzeichen + Aktionen  */
#define MAX_NONT    (-3)

/* ====================================================================== */
/* Makros fuer die Vergabe der laufenden Nummern                          */
/* ====================================================================== */
/* Vergabe der naechsten laufenden Nummer fuer Terminalzeichen     */
#define NEXTTERMNR if (++maxt > MAX_TERM) \
                     parsAbort("Zu viele Terminalzeichen");
/* Vergabe der naechsten laufenden Nummer fuer Nonterminalzeichen  */
#define NEXTNONTNR if (++maxn > MAX_NONT) \
                     parsAbort("Zu viele Aktionen und Nonterminalzeichen");
/* Vergabe der naechsten laufenden Nummer fuer Aktionen            */
#define NEXTACTNR if (++maxa > MAX_NONT) \
                     parsAbort("Zu viele Aktionen");

/* ====================================================================== */
/* Variablen fuer Fehlerbehandlung                                        */
/* ====================================================================== */
/* Fehlerdatei wird nur geoeffnet, falls tatsaechlich Fehler vorhanden    */
/* Fehlerausgabe parallel auf Fehlerdatei readg.err und stderr            */
/* ====================================================================== */
/* Datei fuer Fehlermeldungen, vom Scanner importiert */
FILE *errorfile = NULL; 
FILE *errordatei = NULL; 
int protokoll = 1;
#define mabort() do{memError();exit(25);}while(0)
/* Oeffnen der Fehlermeldungsdatei, falls noch nicht geschehen */
#define OPENERR if (errorfile==NULL) OpenErr();

long SemErrors; /* Anzahl der semantischen Fehler */
long semerrors; /* Anzahl der semantischen Fehler */
/* ====================================================================== */
/* sonstige globale Variablen                                             */
/* ====================================================================== */
static char *ZielDatei;        /* 2. Kommandozeilenargument, aus parser.o     */

typedef short Idnr;            /* von Scanner gelieferte Id-Nummer            */
static Idnr maxt;              /* laufende Nummer letztes Terminalsymbol      */
static Idnr maxa;              /* laufende Nummer letzte  Aktion              */
static Idnr maxn;              /* laufende Nummer letztes Nonterminalsymbol   */
static Idnr maxp;              /* laufende Nummer letzte  Produktion          */
static Idnr maxi;              /* laufende Nummer letztes Item                */

static Token akt_token;        /* aktuelles Token vom Scanner                 */

/* ====================================================================== */
/* Ausgabe eines Zeichens in den Ausgabepuffer                            */
/* ====================================================================== */
#ifdef __STDC__
static void bputc(int c)
#else
static void bputc(c)
 int c;
#endif
 {
  if (outbuf_ptr >= outbuf_len)
   { /* Puffer muss vergroessert werden */
    outbuf_len += BUFFER_LEN;
    if ((out_buf = (char *)realloc((void *)out_buf,outbuf_len)) == NULL)
      mabort();
   }
  out_buf[outbuf_ptr++] = c;
 } /* bputc */

/* ====================================================================== */
/* Ausgabe eines Strings in den Ausgabepuffer                             */
/* ====================================================================== */
#ifdef __STDC__
static void bputs(char *s)
#else
static void bputs(s)
 char *s;
#endif
 {
  char *p;
  if (s != NULL)
    for (p = s; *p ; bputc(*p++));
 } /* bputs */

/* ====================================================================== */
/* Ausgabe einer vorzeichenbehafteten Zahl in den Ausgabepuffer           */
/* ====================================================================== */
static char *xdigs = "0123456789abcdef";
#ifdef __STDC__
static void bputi(long n)
#else
static void bputi(n)
 long n;
#endif
 {
#define NUMBUFLEN 20
  char numbuf[NUMBUFLEN];
  long num;
  int  neg;
  char *p;

  p = &numbuf[NUMBUFLEN-1];
  *p-- = '\0';
  *p-- = ' ';
  num = (neg = (n < 0)) ? -n : n;
  do 
   {
    *p-- = xdigs[num % 10];
    num = num / 10;
   }
  while (num);
  if (neg)
    *p-- = '-';
  bputs(p+1);
 } /* bputi */

/* ====================================================================== */
/* Ausgabe einer Sedezimalzahl in den Ausgabepuffer                       */
/* ====================================================================== */
#ifdef __STDC__
static void bputx(unsigned long n)
#else
static void bputx(n)
 unsigned long n;
#endif
 {
#define XBUFLEN 20
  char xbuf[XBUFLEN];
  unsigned long num;
  char *p;

  p = &xbuf[XBUFLEN-1];
  *p-- = '\0';
  *p-- = ' ';
  num = n;
  do 
   {
    *p-- = xdigs[num & 15];
    num >>= 4;
   }
  while (num);
  bputs(p+1);
 } /* bputx */

/* ====================================================================== */
/* Id-Tabellen-Verwaltung                                                 */ 
/* Identifizierung von Bezeichnern                                        */
/* ====================================================================== */
/* maximale Anzahl verwendbare Bezeichner    */
#define IDTABLEN 2000

/* --------------------------------------- */
/* moegliche Arten von Idtab-Eintraegen    */
/* --------------------------------------- */
/* kein Eintrag vorhanden          */
#define IDUNDEF    0

/* Eintrag fuer Terminalzeichen    */
#define IDTERM     1

/* Eintrag fuer Nonterminalzeichen */
#define IDNONT     2

/* Eintrag fuer Aktionen           */
#define IDACTION   3

/* ---------------------------------------------- */
/* Datenstrukturen fuer Eintraege in Id-Tabelle   */
/* ---------------------------------------------- */
struct IdtabEl  { /* Eintrag in Id-Tabelle */
                 struct IdtabEl *next; /* naechster Eintrag in Liste          */
                 int      idtyp;       /* Typ des Eintrags : ID...            */
                 Idnr     lfdnr;       /* Laufende Nummer des jeweiligen Typs */
                 char     *text;       /* Klartext fuer Dekodierung           */
		 Quellort ort;
                 union {    /* Information abhaengig von idtyp */
                        /*  */         /* Fall IDTERM                         */
                        /*  */         /* Fall IDACTION                       */
                        char nontdef;  /* Fall IDNONT : Prod. vorhanden       */
                       } u;       
                };  /* struct IdtabEl  */

static struct IdtabEl *idtab[IDTABLEN];      /* Id-Tabelle, Index = Id-Nummer */
static struct IdtabEl *firstterm,*lastterm;  /* Liste der Terminalzeichen     */
static struct IdtabEl *firstnont,*lastnont;  /* Liste der Nonterminalzeichen  */

/* Anzahl gleichzeitig reservierter dynamischer Variablen */
#define POOL 64L

static struct IdtabEl *IdtabElFL;  /* Freiliste struct IdtabEl   */

/* ===================================================================== */
/* Oeffnen des Fehlerfiles bei der ersten Fehlermeldung                  */
/* ===================================================================== */
#ifdef __STDC__
int OpenErr(void)
#else
int OpenErr()
#endif
 {
  if (errordatei==NULL)            /* sonst schon geoeffnet */
   {
    if ((errordatei=fopen("readg.err","w")) == NULL)
     {
      fputs("Fehlerdatei readg.err kann nicht geoeffnet werden !\n",stderr);
      exit(RETURNSTAT_FAIL);      /* Fataler Fehler        */
      return(0);
     }
    fprintf(errordatei,"readg: Fehler beim Einlesen der Grammatik %s\n\n",
            ZielDatei);
   }
  errorfile = errordatei;
  return(1);
 } /* OpenErr */

/* ===================================================================== */
/* Ausgabe einer Fehlermeldung                                           */
/* ===================================================================== */
#ifdef __STDC__
static void semerror(Quellort *wo,char *s1,Token tok,char *s2, Quellort *decl)
#else
static void semerror(wo,s1,tok,s2,decl)
 Quellort *wo;
 char  *s1;
 Token tok;
 char  *s2;
 Quellort *decl;
#endif
 {
  wErrorf(wo," %s%T%s %q\n",s1,tok,s2,decl);
  SemErrors++;
  semerrors++;
 } /* semerror */

/* ====================================================== */
/* Speicher fuer Tabellenelement reservieren              */
/* um Verwaltungsoverhead und Speicherfragmentierung zu   */
/* minimieren, werden immer POOL Elemente gleichzeitig    */
/* reserviert                                             */
/* ====================================================== */
#ifdef __STDC__
static struct IdtabEl *allocIdtabEl(void)
#else
static struct IdtabEl *allocIdtabEl()
#endif
 {
   struct IdtabEl *pt; /* Zeiger auf freien Speicher */
   short i; /* Index in Freiliste */ 
 
  if (IdtabElFL == NULL) /* Freiliste leer */
   {
    if ( (pt=(struct IdtabEl *)malloc(POOL*sizeof(struct IdtabEl))) == NULL ) 
      mabort(); /* kein Speicher mehr vorhanden */
    IdtabElFL = &(pt[1]); /* restliche Elemente in Freiliste */
    for (i = 1; i<POOL-1;i++) 
      pt[i].next = &(pt[i+1]); /* Freiliste verketten */
    pt[i].next = NULL; /* Ende der Freiliste */
   }
  else
   {
    pt = IdtabElFL; /* erstes Element der Freiliste */
    IdtabElFL = IdtabElFL->next; /* Rest(..) */
   };
  return(pt);
 } /* allocIdtabEl */


/* =================================================================== */
/* Initialisierung der Id-Tabelle                                      */
/* =================================================================== */
#ifdef __STDC__
static void initidtab(void)
#else
static void initidtab()
#endif
 {
  Idnr idnr;  /* momentaner Eintrag */

  for (idnr = 0; idnr < IDTABLEN; idnr ++) /* gesamte Tabelle     */
    idtab[idnr] = NULL;  /* noch kein Eintrag                     */
  IdtabElFL = NULL;      /* Freiliste ist leer                    */
  firstterm = NULL;      /* Liste der Terminalzeichen ist leer    */
  lastterm  = NULL;      /* Liste der Terminalzeichen ist leer    */
  firstnont = NULL;      /* Liste der Nonterminalzeichen ist leer */
  lastnont  = NULL;      /* Liste der Nonterminalzeichen ist leer */
 } /* initidtab */

/* ============================================ */
/* Suchen eines Eintrags in der Idtabelle       */
/* Ergebnis : gesuchter Eintrag oder NULL       */
/* ============================================ */
#ifdef __STDC__
static struct IdtabEl *lookupid (Idnr idnr)
#else
static struct IdtabEl *lookupid(idnr)
 Idnr idnr;   /* Idnummer des gesuchten Eintrags */
#endif
 {
  if (idnr < 0 )              /* ungueltige Nummer, sollte nicht auftreten   */
    parsAbort("Interner Fehler, Ungueltiger Identifier");
  else if (idnr >= IDTABLEN)  /* Id-Tabelle voll, Abbruch                    */ 
    parsAbort("Id-Tabelle voll");
  return(idtab[idnr]);        /* Zeiger auf Eintrag in der Tabelle           */  
 } /* lookupid */

/* ======================================================== */
/* Eintrag in Liste von Id-Tabelleneintraegen               */
/* ======================================================== */
#ifdef __STDC__
static void liste(struct IdtabEl *eintr, struct IdtabEl **first,
                  struct IdtabEl **last )
#else
static void liste(eintr,first,last)
 struct IdtabEl *eintr;   /* Eintrag, der eingehaengt wird */
 struct IdtabEl **first;  /* Anfang der Liste              */
 struct IdtabEl **last;   /* Ende der Liste                */
#endif
 {
  if ( (*first) == NULL)  /* Liste ist leer                */
   {
    *first = eintr;       /* einziger Eintrag              */
   } /* Liste ist leer */
  else                    /* an Listenende anhaengen       */
   {
    (*last)->next = eintr;  /* Vorgaenger verketten */
   }
  eintr->next = NULL;     /* Listenende           */
  *last = eintr;    /* wird letzter Eintrag  */
 } /* liste */

/* ======================================================== */
/* Eintrag eines neuen Terminalsymbols in die Id-Tabelle    */
/* ======================================================== */
#ifdef __STDC__
static struct IdtabEl *enterTerm(Token token,Idnr lfd)
#else
static struct IdtabEl *enterTerm(token,lfd)
 Token token; /* Token des Bezeichners                 */
 Idnr lfd;    /* laufende Nummer des Terminalzeichens  */
#endif
 {
  Idnr idnr;                   /* Id-Nummer des Bezeichners             */
  struct IdtabEl *eintr;       /* Zeiger auf neuen Eintrag              */

  if (!isTokenvalid(token))
    return(NULL);
  idnr = SEMVAL(token);
  if ((eintr = lookupid(idnr)) != NULL)  /* bereits Eintrag vorhanden       */
   {
    semerror(QUELL_ORT(token),"Bezeichner fuer Terminalsymbol ",token,
             " bereits verwendet bei ",&eintr->ort);
    return(NULL);
   }
  else /* Eintrag moeglich */
   {
    eintr = allocIdtabEl();                 /* neuer Eintrag                */
    eintr->idtyp  = IDTERM ;                /* Eintrag fuer Terminalzeichen */
    eintr->lfdnr  = lfd ;                   /* laufende Nummer              */ 
    eintr->text   = scanDecode(NULL,token); /* fuer Dekoder                 */
    eintr->ort    = *(QUELL_ORT(token));     /* Ort kopieren                 */
    liste(eintr,&firstterm,&lastterm);      /* Liste ergaenzen              */
    idtab[idnr] = eintr;                    /* in Tabelle eintragen         */
    return(eintr);                          /* Zeiger auf Element abliefern */
   } /* Eintrag moeglich */
 } /* enterTerm */

/* =========================================================== */
/* Eintrag einer neuen Aktion in die Id-Tabelle                */
/* =========================================================== */
#ifdef __STDC__
static struct IdtabEl *enterAction(Token token,Idnr lfd)
#else
static struct IdtabEl *enterAction(token,lfd)
 Token token; /* Token des Bezeichners                 */
 Idnr lfd;    /* laufende Nummer der Aktion            */
#endif
 {
  Idnr idnr;                   /* Id-Nummer des Bezeichners             */
  struct IdtabEl *eintr;               /* Zeiger auf neuen Eintrag  */

  if (!isTokenvalid(token))
    return(NULL);
  idnr = SEMVAL(token);
  if ((eintr = lookupid(idnr)) != NULL)  /* bereits Eintrag vorhanden       */
   {
    semerror(QUELL_ORT(token),"Bezeichner fuer Aktion ",token,
             " bereits verwendet bei ",&eintr->ort);
    return(NULL);
   }
  else /* Eintrag moeglich */
   {
    eintr = allocIdtabEl();            /* neuer Eintrag                   */
    eintr->idtyp  = IDACTION;          /* Eintrag fuer Nonterminalzeichen */
    eintr->lfdnr  = lfd ;              /* laufende Nummer                 */ 
    eintr->text   = scanDecode(NULL,token); /* fuer Dekoder               */
    eintr->ort    = *(QUELL_ORT(token));     /* Ort kopieren                 */
    eintr->u.nontdef = TRUE;           /* eps-Produktion vorhanden        */
    liste(eintr,&firstnont,&lastnont); /* Liste ergaenzen                 */
    idtab[idnr] = eintr;               /* in Tabelle eintragen            */
    return(eintr);                     /* Zeiger auf Eintrag abliefern    */
   } /* Eintrag moeglich */
 } /* enterAction */

/* =========================================================== */
/* Eintrag eines neuen Nonterminalsymbols in die Id-Tabelle    */
/* =========================================================== */
#ifdef __STDC__
static struct IdtabEl *enterNont(Token token,Idnr lfd)
#else
static struct IdtabEl *enterNont(token,lfd)
 Token token; /* Token des Bezeichners                    */
 Idnr lfd;    /* laufende Nummer des Nonterminalzeichens  */
#endif
 {
  Idnr idnr;                   /* Id-Nummer des Bezeichners             */
  struct IdtabEl *eintr;  /* Zeiger auf neuen Eintrag */

  if (!isTokenvalid(token))
    return(NULL);
  idnr = SEMVAL(token);
  if ((eintr = lookupid(idnr)) != NULL)  /* bereits Eintrag vorhanden       */
   {
    semerror(QUELL_ORT(token),"Bezeichner fuer Nonterminalsymbol ",token,
             " bereits verwendet bei ",&eintr->ort);
    return(NULL);
   }
  else /* Eintrag moeglich */
   {
    eintr = allocIdtabEl();            /* neuer Eintrag                   */
    eintr->idtyp  = IDNONT ;           /* Eintrag fuer Nonterminalzeichen */
    eintr->lfdnr  = lfd ;              /* laufende Nummer                 */ 
    eintr->text   = scanDecode(NULL,token); /* fuer Dekoder               */
    eintr->ort    = *(QUELL_ORT(token));     /* Ort kopieren               */
    eintr->u.nontdef = FALSE ;         /* noch keine Produktion           */
    liste(eintr,&firstnont,&lastnont); /* Liste ergaenzen                 */
    idtab[idnr] = eintr;               /* in Tabelle eintragen            */
    return(eintr);
   } /* Eintrag moeglich */
 } /* enterNont */

/* ======================================================= */
/* vom Parser "angestossene" semantische Aktionen          */
/* ======================================================= */
#ifdef __STDC__
int outred(long p,long l,long n)
#else
int outred(p,l,n)
 long p,l,n;
#endif
 { 
  struct IdtabEl *eintr;  /* Eintrag in Id-Tabelle           */

  switch ( p ) {  /* Nummer aufgerufene semantische Aktion */
    case S_TERMNR: 
        /* ------------------------------------------------------- */
        /* Klasse des naechsten Terminalsymbols eingelesen         */
        /* Ueberpruefung, ob Terminalzeichen fortlaufend numeriert */
        /* relcode = eingelesene laufende Nummer 		   */
        /* ------------------------------------------------------- */
        if (isTokenvalid(akt_token) && SEMVAL(akt_token) != maxt) 
          semerror(QUELL_ORT(akt_token),"Terminalnumerierung ",akt_token,
                   " stimmt nicht",NULL);
        break;

    case S_FIRSTTERM: 
        /* ------------------------------------------------------- */
        /* Initialisierung der Terminalsymbol-Liste                */
        /* aufgerufen nach Lesen des ersten Terminal-Bezeichners   */
        /* momentan kein Unterschied zu S_NEWTERM (s.u.)           */
        /* ------------------------------------------------------- */
    case S_NEWTERM:
        /* ------------------------------------------------------- */
        /* Eintrag des Bezeichners des naechsten Terminalsymbols   */
        /* in die Symboltabelle                                    */
        /* aufgerufen nach Lesen eines Terminal-Bezeichners        */
        /* Ueberpruefung, ob Name neu ist                          */
        /* ------------------------------------------------------- */
        /* gelesenen Bezeichner in die Symboltabelle eintragen, */
        /* Eindeutigkeit wird in enterterm()  ueberprueft       */
        enterTerm(akt_token,(Idnr)maxt);
        NEXTTERMNR;               /* naechste laufende Nummer vergeben */
        break;

    case S_ENDTERMS: 
        /* ------------------------------------------------------- */
        /* Einlesen Terminalsymbole beendet                        */
        /* Vorbereitung des Einlesens der Aktionen                 */
        /* ------------------------------------------------------- */
        maxa = MIN_NONT; /* erste laufende Nummer fuer Aktionen    */
        break;


    case S_ACTIONNR:
        /* ------------------------------------------------------- */
        /* Klasse der naechsten Aktion eingelesen                  */
        /* Ueberpruefung, ob Aktionen fortlaufend numeriert        */
        /* ------------------------------------------------------- */
        /* relcode = eingelesene laufende Nummer der Aktion        */
        if (isTokenvalid(akt_token) && SEMVAL(akt_token) != maxa-MIN_NONT+1) 
          semerror(QUELL_ORT(akt_token),"Aktionsnumerierung ",akt_token,
                   " stimmt nicht",NULL);
        break;


    case S_NEXTACTION:
        /* ------------------------------------------------------- */
        /* naechste Aktion eintragen                               */
        /* ------------------------------------------------------- */
        /* identisch mit S_NEWACTION                               */
        /* ------------------------------------------------------- */
    case S_NEWACTION:
        /* ------------------------------------------------------- */
        /* Eintrag des Bezeichners der naechsten Aktion            */
        /* in die Symboltabelle                                    */
        /* aufgerufen nach Lesen eines Aktions-Bezeichners         */
        /* Ueberpruefung, ob Name neu ist                          */
        /* ------------------------------------------------------- */

        /* gelesenen Bezeichner in die Symboltabelle eintragen,   */
        /* Eindeutigkeit wird in enterAction()  ueberprueft       */
        if (enterAction(akt_token,(Idnr)maxa) != NULL)
          NEXTACTNR;         /* naechste laufende Nummer vergeben */
        break;

    case S_ENDACTIONS:
        /* ------------------------------------------------------- */
        /* Einlesen Aktionen beendet                               */
        /* ------------------------------------------------------- */
        break;


    case S_AXIOM:
        /* ------------------------------------------------------- */
        /* Name des Axioms eingelesen                              */
        /* Produktionen zu den Aktionen ausgeben                   */
        /* Ueberpruefung, ob angegebener Bezeichner neu ist        */
        /* ------------------------------------------------------- */

        maxn = maxa;              /* Initialisierung erste laufende Nummer */
                                  /* direkt hinter den Aktionen            */

        /* >>>>>>>>>>>>>>>>>>>>>>>> */
        /* Ausgabe des Axioms       */
        /* >>>>>>>>>>>>>>>>>>>>>>>> */
        bputi((long)maxn);       

        /* .............................................. */
        /* Epsilonproduktionen fuer die Aktionen ausgeben */
        /* .............................................. */
        maxp = 0;           /* erste laufende Nummer Produktionen        */
        for (eintr = firstnont; eintr != NULL; eintr = eintr->next)
         {
          bputi((long)eintr->lfdnr);
          bputs(DELIM_PROD_REGEL);
          maxp++;           /* Eps-Prods. zaehlen         */
         }
        /* Axiom als Nonterminalzeichen eintragen */
        enterNont(akt_token,(Idnr)maxn);

        NEXTNONTNR;         /* naechste laufende Nummer der Nonterminale */
        maxi = 0;           /* erste laufende Nummer Items               */
        break;

    case S_LHS: 
        /* ------------------------------------------------------- */
        /* Bezeichner linke Seite eingelesen                       */
        /* Ueberpruefung, ob Nonterminal und ob noch keine         */
        /* Produktionen zu diesem Symbol definiert                 */
        /* ------------------------------------------------------- */

        /* Feststellen, ob Bezeichner schon verwendet */
	if (!isTokenvalid(akt_token))
	 {
	  eintr = NULL;
	  break;
	 }

        eintr = lookupid((Idnr)SEMVAL(akt_token));  /* Eintrag vorhanden ? */
        if (eintr == NULL) /* neuer Bezeichner -> neues Nonterminal */
         {
          /* als neues Nonterminalsymbol eintragen */
          if ((eintr = enterNont(akt_token,(Idnr)maxn)) != NULL)
            eintr->u.nontdef = TRUE;    /* Produktionen jetzt vorhanden */
          /* ........................ */
          /* laufende Nummer ausgeben */
          /* ........................ */
          bputi((long)maxn );
          NEXTNONTNR;        /* naechste laufende Nummer vergeben      */
         }      
        else if (eintr->idtyp == IDTERM)
          semerror(QUELL_ORT(akt_token),"linke Seite ",akt_token,
                   " ist Terminalzeichen, deklariert bei ",&eintr->ort);
        else if (eintr->idtyp == IDACTION)
          semerror(QUELL_ORT(akt_token),"linke Seite ",akt_token,
                   " ist Aktion, deklariert bei ",&eintr->ort);
        else if (eintr->u.nontdef)  /* bereits Regeln gelesen */
         {
          semerror(QUELL_ORT(akt_token),
                   "Mehrere Regeln fuer das Nichtterminal ",
                   akt_token,", deklariert bei ",&eintr->ort);
          bputi((long)eintr->lfdnr );
         }
        else  /* Eintrag in Ordnung */
         {
          eintr->u.nontdef = TRUE;    /* merken, dass Prod. jetzt vorh. */
          /* ........................ */
          /* laufende Nummer ausgeben */
          /* ........................ */
          bputi((long)eintr->lfdnr );
         }
        break;

    case S_ENDALTLIST: 
        /* ------------------------------------------------------- */
        /* Ende aller Alternativen zu einer linker Seite           */
        /* ------------------------------------------------------- */
          /* ........................ */
          /* Delimiter ausgeben       */
          /* ........................ */
        bputs(DELIM_REGEL);
        break;

    case S_ENDALT:     
        /* ------------------------------------------------------- */
        /* Ende einer Alternative zu einem Nonterminal             */
        /* ------------------------------------------------------- */
        /* ........................ */
        /* Delimiter ausgeben       */
        /* ........................ */
        bputs(DELIM_PROD);

        maxp++;            /* Produktionen zaehlen   */

        break;

    case S_SYMBAUS:
        /* -------------------------------------------------------- */
        /* Bezeichner eines Symbols in der rechten Seite gelesen    */
        /* falls Bezeichner neu, als Nonterminalzeichen deklarieren */
        /* -------------------------------------------------------- */

        /* Feststellen, ob Bezeichner schon verwendet */
	if (!isTokenvalid(akt_token))
	 {
	  eintr = NULL;
	  break;
	 }
        eintr = lookupid((Idnr)SEMVAL(akt_token));  /* Eintrag vorhanden ? */

        if (eintr == NULL) /* neuer Bezeichner -> neues Nonterminal */
         {
          /* als neues Nonterminalsymbol eintragen */
          if ((eintr = enterNont(akt_token,(Idnr)maxn)) != NULL)
           {
            eintr->u.nontdef = FALSE;     /* keine Produktionen vorhanden  */
            NEXTNONTNR;       /* naechste laufende Nummer der Nonterminale */
           }
         }
        /* ........................ */
        /* laufende Nummer ausgeben */
        /* ........................ */
        bputi((long)eintr->lfdnr);

        maxi++;            /* Items zaehlen       */

        break;

    default: 
        /* ------------------------------------------------------- */
        /* Die reduzierte Produktion gehoert nicht zu einer Aktion */
        /* ------------------------------------------------------- */ 
        break;

  } /* case */;
  return(1);
 } /* outred */

/* ======================================================== */
/* Initialisierung der semantischen Aktionen                */
/* ======================================================== */
#ifdef __STDC__
int semInit(int argc,char *argv[])
#else
int semInit(argc,argv)
 int argc;
 char *argv[];
#endif
 {
  initidtab();        /* Idtabelle leer initialisieren                       */
  maxt = MIN_TERM;    /* Initialisierung erste laufende Nummer Terminalzchn. */
  SemErrors = 0;      /* noch keine semantischen Fehler aufgetreten          */
  /* ............................. */
  /* Ausgabepuffer initialisieren  */
  /* ............................. */
  if ((out_buf = (char *)malloc(BUFFER_LEN)) == NULL)
    mabort();
  outbuf_len = BUFFER_LEN;
  outbuf_ptr = 0;
  /* .............................................................. */
  /* Platzreservierung fuer Magic, Anzahlen etc. am Dateianfang     */
  /* .............................................................. */
  for (outbuf_ptr = 0; outbuf_ptr < 79; out_buf[outbuf_ptr++] = ' ');
  out_buf[outbuf_ptr++] = '\n';
  return((akt_token = allocToken()) != NULL);
 } /* semInit */

/* ======================================================== */
/* Abschluss der Aktionen nach Beendigung der Syntaxanalyse */
/* ======================================================== */
#ifdef __STDC__
void semClose(void)
#else
void semClose()
#endif
 { 
  struct IdtabEl *eintr;  /* Eintrag in Liste              */ 
  char *headername;       /* Name der Headerdatei          */
  long save_ptr;          /* Ende des Ausgabepuffers       */
  int  ausfile;           /* Filenr. der Ausgabedatei      */
  extern int write();
  extern int close();

  if (akt_token != NULL)
   {
    freeToken(akt_token);
    akt_token = NULL;
   }
  /* ....................................... */
  /* Delimiter fuer Abschluss Produktionen   */
  /* ....................................... */
  bputs(DELIM_GRAMM);

/* ----------------------------------------------------------------- */
/* Ausgabe der Liste der Namen der Terminalzeichen                   */
/* ----------------------------------------------------------------- */
  for (eintr = firstterm; eintr != NULL; eintr = eintr->next)
   {
    /* ..................................................... */
    /* Terminalzeichennamen ausgeben                         */
    /* ..................................................... */
    bputs(eintr->text);
    bputc('\n');
   }

/* -------------------------------------------------------------------- */
/* Ausgabe der Liste der Namen der Nonterminalzeichen                   */
/* -------------------------------------------------------------------- */
  for (eintr = firstnont; eintr != NULL; eintr = eintr->next)
   {
    if (! eintr->u.nontdef)
      semerror(NULL,"keine Regeln zu Nonterminal ",NULL,
               eintr->text,&eintr->ort);
    /* ..................................................... */
    /* Nonterminalnamen ausgeben                             */
    /* ..................................................... */
    bputs(eintr->text);
    bputc('\n');
   }
  if (SemErrors)
    return;  /* keine Ausgaben bei fehlerhafter Eingabe */

/* ================================================================= */
/* Ausgabe der  Anzahlen am Dateianfang                              */
/* ================================================================= */
  /* ..................................................... */
  /* zur Ergaenzung der Daten am Dateianfang positionieren */
  /* ..................................................... */
   save_ptr = outbuf_ptr;
   outbuf_ptr = 0;
  /* ..................................................... */
  /* Ausgabe MAGIC, Delimiter und Anzahlen                 */
  /* ..................................................... */
  bputx((unsigned long)MAGIC_CH2_GRM);
  bputc('\n');
  bputi((long)MIN_TERM);
  bputi((long)(maxt-1));
  bputi((long)MIN_NONT);
  bputi((long)(maxn-1));
  bputc('\n');
  bputi((long)maxp);
  bputi((long)maxi);
  bputc('\n');
  bputs(DELIM_PROD);
  bputc(' ');
  bputs(DELIM_REGEL);
  bputc(' ');
  bputs(DELIM_GRAMM); 

  /* ........................ */
  /* Ausgabedatei oeffnen     */ 
  /* ........................ */
  if ( (ausfile = open(ZielDatei,O_WRONLY | O_CREAT,0666)) == -1 ) 
   {
    fputs("Zieldatei \"",stderr);
    fputs(ZielDatei,stderr);
    parsAbort("\" kann nicht geoeffnet werden");
   }
  /* ........................ */
  /* Puffer ausgeben          */ 
  /* ........................ */
  if (write(ausfile,out_buf,save_ptr) == -1)
    parsAbort("Fehler beim Ausgeben der Internform");
  /* ........................ */
  /* Ausgabedatei schliessen  */ 
  /* ........................ */
  close(ausfile);

/* -------------------------------------------------------------------- */
/* Ausgabe der Headerdatei fuer den Semantikteil                        */
/* -------------------------------------------------------------------- */
  if (maxa > MIN_NONT)   /* Aktionen vorhanden */
   {
    outbuf_ptr = 0;
    bputs("/* Definition der Aktionsnummern der Grammatik ");
    bputs(ZielDatei);
    bputs(" */");
    for (eintr = firstnont; eintr != NULL; eintr = eintr->next)
      if (eintr->idtyp == IDACTION)
       {
        /* ..................................................... */
        /* Aktionsnamen ausgeben                                 */
        /* ..................................................... */
        bputs("\n#define\t");
        bputs(eintr->text);
        bputc('\t');
        bputi((long)(eintr->lfdnr - MIN_NONT+1));
       }
    bputc('\n');
    /* ........................ */
    /* Ausgabedatei oeffnen     */
    /* ........................ */
    if ( (headername = (char *)malloc((unsigned)(strlen(ZielDatei)+3)) )
      == NULL)
      mabort();  /* kein Platz fuer Namen */
    strcpy(headername,ZielDatei);  /* Name der codierten Grammatik   */
    strcat(headername,".h");       /* plus ".h"                      */
    /* ........................ */
    /* Ausgabedatei oeffnen     */ 
    /* ........................ */
    if ( (ausfile = open(headername,O_WRONLY | O_CREAT,0666)) == -1 ) 
     {
      fputs("Headerdatei \"",stderr);
      fputs(headername,stderr);
      parsAbort("\" kann nicht geoeffnet werden");
     }
    /* ........................ */
    /* Puffer ausgeben          */ 
    /* ........................ */
    if (write(ausfile,out_buf,outbuf_ptr) == -1)
      parsAbort("Fehler beim Ausgeben der Headerdatei");
    /* ........................ */
    /* Ausgabedatei schliessen  */ 
    /* ........................ */
    close(ausfile);
   } /* Aktionen vorhanden */
 } /* semClose */

/* ===================================================================== */
/* aktuelles Token merken                                                */
/* ===================================================================== */
#ifdef __STDC__
int outterm(Token tok)
#else
int outterm (tok)
 Token tok;
#endif 
 {
  copyToken(akt_token,tok);
  return(1);
 } /* outterm */

/* ===================================================================== */
/* Abbruch aller Bruecken						 */
/* ===================================================================== */
#ifdef __STDC__
void semAbort(void)
#else
void semAbort()
#endif
 {
  if (akt_token != NULL)
   {
    freeToken(akt_token);
    akt_token = NULL;
   }
 } /* semClose */

/* ===================================================================== */
/* Hauptprogramm                                                         */
/* ===================================================================== */
#ifdef __STDC__
int main(int argc,char *argv[])
#else
int main(argc,argv)
 int argc;
 char *argv[];
#endif
 {
  int res;
#ifdef TIMING
  Msecs zeit;
#endif

#ifdef TIMING
  zeit = milliSecs();
#endif
  if (argc != 3)
   {
    fprintf(stderr,"Aufruf : %s <Grammatik> <Internform>\n",argv[0]);
    exit(20);
   }
  if ((ScanEin = fopen(argv[1],"r") ) == NULL)
   {
    fprintf(stderr,"Eingabedatei %s konnte nicht geoeffnet werden\n",
            argv[1]);
    exit(20);
   }
  ZielDatei = argv[2];
  if (! scanInit())
    exit(20);
  parseInit();
  res = parseTab(argc,argv,argv[1],&parseerrors,
                 (void *)&lalr_tab,scanNext,outred,outterm);
#ifdef TIMING
  zeit = milliSecs() - zeit;
  fprintf(stderr,"%d.%0.03d Sekunden\n",zeit / 1000, zeit % 1000);
#endif
  return(res && !parseerrors && !semerrors && !scanerrors ? 0 : 20);
 } /* main */

