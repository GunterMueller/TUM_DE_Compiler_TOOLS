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
/* LRKread.c   :                                                          */
/* LR(k)-Parser-Generator                                                 */
/* Modul : Einleser fuer Grammatikinternform                              */
/* Aenderung : 16.12.89, Kommentarzeile in Internform unterstuetzt        */
/* Aenderung : 01.07.89, schnelleres Einlesen ohne fscanf()               */
/* erstellt  : 23.1.89                                                    */
/* ********************************************************************** */
#ifdef __STDC__
#include <stddef.h>
#include <stdlib.h>
#endif
#include <stdio.h>         /* E/A-Definitionen                   */  
#include <string.h>
#include "defs.h"          /* diverse unspezifische Definitionen */
#include "magics.h"        /* Definitionen der Magic-Numbers     */
#include "checks.h"        /* Ueberpruefungen zur Laufzeit       */
#include "grammar.h"       /* Datentype fuer die Grammatik       */
#include "lrkread.h"       /* Deklarationen Einleser             */
#include "lrkfiles.h"      /* Deklarationen Dateimodul           */
#include "lrkerrors.h"     /* Deklarationen Fehlermodul          */

/* ======================================================================= */
/* Deklarationen, die evtl. von der verwendeten Zahldarstellung abhaengen  */
/* ======================================================================= */

/* ----------------------------------------------------------------------- */
/*Datenstruktur, die fuer das Einlesen der Symbole der Internform         */
/* (vorzeichenbehaftete ganze Zahlen in Dezimaldarstellung )               */
/* geeignet ist (Abstimmung mit Grammatikeinleser)                         */
/* ----------------------------------------------------------------------- */
typedef long Evar; 

/* ----------------------------------------------------------------------- */
/* Formatstring, der das Einlesen einer Variable vom Type Evar erlaubt     */
/* ----------------------------------------------------------------------- */
#define EFMT "%ld"

/* ====================================================================== */
/* Programm-globale Variablen                                             */
/* ====================================================================== */
extern Grammar g;                  /* einzulesende Grammatik                   */

/* ====================================================================== */
/* Modul-globale Variablen                                                */
/* ====================================================================== */
                                   /* Fehlermeldungstext fuer Inkonsistenzen   */
static char *intf_inkons = "Internform inkonsistent\n";

static FILE *intdatei;             /* File-Handle fuer Eingabedatei            */

static Evar delim_prod;            /* Delimiter fuer eine Produktion           */
static Evar delim_regel;           /* Delimiter fuer eine Regel                */
static Evar ende_regeln;           /* Delimiter fuer Folge der Regeln          */

static Evar ext_mint;              /* minimale Terminalzeichennummer in Int.F. */
static Evar ext_maxt;              /* maximale Terminalzeichennummer in Int.F. */
static Evar ext_minn;              /* minimale Nont.zeichennummer in Int.F.    */
static Evar ext_maxn;              /* maximale Nont.zeichennummer in Int.F.    */
static Evar anzp;                  /* Anzahl der Produktionen                  */
static Evar anzi;                  /* Anzahl der Items                         */

static Item topitem;               /* naechstes freies Item in der Liste       */
static Prod topprod;               /* naechste freie Produktion in der Liste   */

/* ====================================================================== */
/* Makros                                                                 */
/* ====================================================================== */

/* --------------------------------------------------------------- */
/* Einlesen einer Dezimalzahl aus der Datei in die Variable v      */
/* Fehlermeldung und Abbruch, falls nicht moeglich                 */
/* --------------------------------------------------------------- */
#define READEVAR(v) readEvar(&v)

/* --------------------------------------------------------------- */
/* Einlesen eines externen Namens in den Puffer b                  */
/* es werden maximal MAXNAMLEN Zeichen gelesen                     */
/* Fehlermeldung und Abbruch, falls nicht moeglich                 */
/* --------------------------------------------------------------- */
#define MAXNAMLEN 100
#define READNAME(b) readName(b)

/* --------------------------------------------------------------- */
/* Testen einer Inkonsistenz-Bedingung i, Abbruch, falls erfuellt  */
/* --------------------------------------------------------------- */
#ifdef CHECKALL
#define INKONSISTENT(i) if ( i ) { Error0(intf_inkons);return(FALSE); }
#else
#define INKONSISTENT(i)
#endif

/* --------------------------------------------------------------- */
/* Test, der Bedingung b, ob Datentypen zu klein                   */
/* falls ja, Fehlermeldung f und Abbruch                           */
/* --------------------------------------------------------------- */
#define ZUGROSS(b,f) if ( b ) { Error0(f);return(FALSE); }

/*====================================================================== */
/* Umrechnung von Symbolexterndarstellungen in die interne Darstellung    */
/*====================================================================== */
#define EXT_TO_INT(e) (Symb)( (e)>=ext_mint && (e)<=ext_maxt? \
                              (e)-ext_mint+CMINT+1 :(e)-ext_minn+CMINN ) 

/*====================================================================== */
/* Einlesen der naechsten Zahl aus der Eingabedatei                       */
/*====================================================================== */
#ifdef __STDC__
static void readEvar(Evar *v)
#else
static void readEvar(v)
 Evar *v;            /* einzulesende Variable        */
#endif
 {
  register Evar n;   /* hier wird der Wert aufgebaut */
  register char c;   /* eingelesenes Zeichen         */
  int neg;           /* Flag fuer : negativ          */

  while ( (c = fgetc(intdatei)) != EOF && c != '-' && (c < '0' || c > '9'));
  
  if (c == EOF ||                  /* Zahl fehlt             */
      (neg = (c == '-') ) &&
      ((c = fgetc(intdatei)) == EOF || c < '0' || c >'9')  )
    Error0(intf_inkons);           /* erste Ziffer fehlt     */
  n = c - '0';                     /* erste Stelle berechnen */
  while ((c = fgetc(intdatei)) != EOF && c >= '0' && c <= '9')
    n = n * 10 + c - '0';
  *v = (neg?-n:n);                 /* Ergebnis eintragen     */
 } /* readEvar */

/*====================================================================== */
/* Einlesen einer Zeile der Eingabedatei als Bezeichner                   */
/*====================================================================== */
#ifdef __STDC__
static void readName(char * b)
#else
static void readName(b)
 register char *b;       /* Puffer, in den der Bezeichner gelesen wird */
#endif
 {
  register short len;    /* aktuell eingelesene Laenge                 */
  register char c;       /* eingelesenes Zeichen                       */

  while ( (c = fgetc(intdatei)) != EOF && (c <= ' ' || c > 126) );
  if (c == EOF)
    Error0(intf_inkons);           /* Name fehlt     */
  len = 0;        
  do  /* druckende Zeichen in Puffer einlesen */ 
   {
    if (len < MAXNAMLEN)
      b[len++] = c;
   } while ((c = fgetc(intdatei) ) != EOF &&
             c > ' ' && c <= 126);

  /* bis zum naechsten Zeilenende lesen */
  while ( c != EOF && c != '\n') c = fgetc(intdatei);

  b[len] = '\0';  
 } /* readName */

/*====================================================================== */
/* Einlesen der Definitionen der Symbolbereiche und der Delimiter         */
/* aus der intdatei                                                       */
/*   Rueckgabe : TRUE, falls fehlerfrei, FALSE sonst                      */
/*====================================================================== */
#ifdef __STDC__
static BOOL readDefs(void)
{
#else
static BOOL readDefs()
 {
#endif
#ifdef DEBUG
  printf(" readDefs()\n");
#endif

  READEVAR(ext_mint);    /* kleinstes Terminalzeichen in der Datei       */
  READEVAR(ext_maxt);    /* groesstes Terminalzeichen in der Datei       */
  READEVAR(ext_minn);    /* kleinstes Nonterminalzeichen in der Datei    */
  READEVAR(ext_maxn);    /* groesstes Nonterminalzeichen in der Datei    */

  READEVAR(anzp);        /* Anzahl der Produktionen der Grammatik        */
  READEVAR(anzi);        /* Anzahl der Positionen der Grammatik          */

  READEVAR(delim_prod);  /* Delimiter fuer Ende einer Produktion         */
  READEVAR(delim_regel); /* Delimiter fuer Ende einer Regel              */ 
  READEVAR(ende_regeln); /* Delimiter fuer Ende aller Regeln             */ 

#ifdef DEBUG
  printf(" t : %ld .. %ld  n : %ld .. %ld  p : %ld  i : %ld\n",
         (long)ext_mint,(long)ext_maxt,(long)ext_minn,(long)ext_maxn,
         (long)anzp,(long)anzi);
  printf(" dp : %ld dr : %ld er : %ld\n",
         (long)delim_prod,(long)delim_regel,(long)ende_regeln);
#endif
  return(TRUE);          /* Definitionen erfolgreich gelesen             */
 } /* readDefs */

/*====================================================================== */
/* Ueberpruefung der Definitionen der Symbolbereiche und der Delimiter    */
/*   Rueckgabe : TRUE, falls fehlerfrei, FALSE sonst                      */
/*====================================================================== */
#ifdef __STDC__
static BOOL checkDefs(void)
{
#else
static BOOL checkDefs()
 {
#endif

  INKONSISTENT(ext_maxt<ext_mint);  /* Obergrenze kleiner Untergrenze    */ 
  INKONSISTENT(ext_maxn<ext_minn);  /* Obergrenze kleiner Untergrenze    */   

  INKONSISTENT(anzp<1);             /* keine Produktionen                */
  INKONSISTENT(anzi<0);             /* Items ungueltig (eps-Prod mgl. !) */

   /* Symbolbereiche duerfen nicht ueberlappen           */
  INKONSISTENT(ext_mint >= ext_minn && ext_mint <= ext_maxn ||
               ext_maxt >= ext_minn && ext_maxt <= ext_maxn);

   /* Produktionsende darf kein Symbol sein              */
  INKONSISTENT(delim_prod >= ext_mint && delim_prod <= ext_maxt ||
               delim_prod >= ext_minn && delim_prod <= ext_maxn);

   /* Regelende darf kein Nonterminalsymbol sein         */
  INKONSISTENT(delim_regel >= ext_minn && delim_regel <= ext_maxn);

   /* Ende der Regeln darf kein Nonterminalsymbol sein   */
  INKONSISTENT(ende_regeln >= ext_minn && ende_regeln <= ext_maxn);

  return(TRUE);          /* Definitionen erfolgreich gelesen             */
 } /* checkDefs */

/*====================================================================== */
/* Einlesen des Axioms der Grammatik und abspeichern in der Datenstruktur */
/*====================================================================== */
#ifdef __STDC__
static BOOL readAxiom(void)
{
#else
static BOOL readAxiom()
 {
#endif
  Evar axiom;         /* externe Nummer des Axioms     */

#ifdef DEBUG
  printf(" readAxiom() ");
#endif
  READEVAR(axiom);               /* Axiom einlesen                */
#ifdef DEBUG
  printf("%ld -> ",(long)axiom);
#endif
  AXIOM = EXT_TO_INT(axiom);     /* in internes Format umwandeln  */
  /* Axiom muss normales Nonterminal sein   */
  INKONSISTENT( ! ISNONT(AXIOM) || AXIOM == METAAXIOM);

#ifdef DEBUG
  printf("  %ld\n",(long)AXIOM);
#endif

  return(TRUE);

 } /* readAxiom */


/*====================================================================== */
/* Initialisierung einer Regel zur linken Seite lhs                       */
/* ====================================================================== */
#ifdef __STDC__
static void initRule(Nont lhs)
#else
static void initRule(lhs)
 Nont lhs;     /* linke Seite der Regel      */
#endif
 {
#ifdef DEBUG
  printf("   initRule(%ld)\n",(long)lhs);
#endif
 } /* initRule */ 

/*====================================================================== */
/* Initialisierung der naechsten Produktion                               */
/* ====================================================================== */
#ifdef __STDC__
static BOOL initProd(Nont lhs)
#else
static BOOL initProd(lhs)
 Nont lhs;     /* linke Seite der Regel      */
#endif
 {

#ifdef DEBUG
  printf("   initProd(%ld)\n",(long)lhs);
#endif
  /* ---------------------------------- */
  /* Liste zur linken Seite fortfuehren */
  /* ---------------------------------- */
  INKONSISTENT(topprod>MAXP);           /* Eintrag nicht mehr moeglich  */
  LHS(topprod) = topitem;               /* linke Seite eintragen        */
  NEXTPROD(topprod) = FIRSTPROD(lhs);   /* Produktion vorne in Liste    */
  FIRSTPROD(lhs) = topprod;             /* erstes Listenelement         */
  topprod++;                            /* naechste freie Produktion    */

  /* ---------------------------------- */
  /* linke Seite eintragen              */
  /* ---------------------------------- */
  INKONSISTENT(topitem>MAXH); /* Eintrag nicht mehr moeglich  */
  ITEMSYM(topitem) = lhs;     /* linke Seite eintragen        */
  ITEMLEN(topitem) = 0;       /* Kennung fuer : linke Seite   */
  topitem++;                  /* naechstes freies Item        */
    
  return(TRUE);
 } /* initProd */ 

/*====================================================================== */
/* Fertigstellen der aktuellen Produktion, Korrektur der Laengenangabe    */
/*====================================================================== */
#ifdef __STDC__
static void setProd(void)
{
#else
static void setProd()
 {
#endif
  register Plength len;   /* Restlaenge der Produktion                   */
  register Item    item;  /* bearbeitetes Item in der Produktion         */

#ifdef DEBUG
  printf("   setProd()\n");
#endif
  len = 0;                  /* Restlaenge fuer letztes item der Produktion */
  for (item = topitem-1;    /* letztes benutztes Item dieser Produktion    */
       ITEMLEN(item) != 0;  /* linke Seite noch nicht erreicht             */
       item--)              /* Vorgaengeritem in der Produktion            */
    ITEMLEN(item) = len++;  /* Laenge bis zum Produktionsende setzen       */
  ITEMLEN(item) = len;      /* linke Seite erhaelt Gesamtlaenge Produktion */
 } /* setProd */

/*====================================================================== */
/* Eintragen des naechsten Symbols der rechten Seite                      */
/* ====================================================================== */
#ifdef __STDC__
static BOOL putRHS(Symb rhs)
#else
static BOOL putRHS(rhs)
 Symb rhs;     /* naechstes Symbol       */
#endif
 {
#ifdef DEBUG
  printf("   putRHS(%ld)\n",(long)rhs);
#endif
  INKONSISTENT(topitem>MAXH); /* Eintrag nicht mehr moeglich   */
  ITEMSYM(topitem) = rhs;     /* Symbol eintragen              */
  ITEMLEN(topitem) = 1;       /* Kennung fuer : rechte Seite   */
  topitem++;                  /* naechstes freies Item         */
  return(TRUE);
 } /* putRHS */

/*====================================================================== */
/* Einlesen einer Regel mit linker Seite lhs und                          */
/* abspeichern in der Datenstruktur                                       */
/*====================================================================== */
#ifdef __STDC__
static BOOL read1Rule(Nont lhs)
#else
static BOOL read1Rule(lhs)
 Nont lhs;   /* linke Seite der Regel */
#endif
 {
  Evar ext_rhs;       /* rechte Seite einer Regel, Externdarstellung  */
  Symb rhs;           /* rechte Seite einer Regel, Interndarstellung  */

#ifdef DEBUG
  printf("  read1Rule(%ld)\n",(long)lhs);
#endif
  initRule(lhs);      /* Regel initialisieren                         */
  READEVAR(ext_rhs);  /* Symbol in der rechte Seite einlesen          */
  while (ext_rhs != delim_regel)  /* alle Produktionen der Regel einlesen  */
   {
    if (!initProd(lhs))    /* Produktion initialisieren                        */
      return(FALSE);
    while (ext_rhs != delim_prod)  /* alle Symbole der rechten Seite einlesen  */
     { 
      rhs = EXT_TO_INT(ext_rhs);     /* in internes Format umwandeln  */
      /* rechte Seite muss normales Symbol sein   */
      INKONSISTENT( ! (ISNONT(rhs) || ISTERM(rhs)) || 
                    rhs == METAAXIOM || rhs == RANDZCH);
      if (!putRHS(rhs))        /* Symbol in rechter Seite eintragen            */
        return(FALSE);
      READEVAR(ext_rhs);  /* naechstes Symbol lesen                       */
     } /* while (ext_rhs != delim_prod) */
    setProd();            /* Produktion vollstaendig, Angaben korrigieren */
    READEVAR(ext_rhs);    /* delim_prod ueberlesen                        */
   } /*  while (ext_rhs != delim_regel) */
#ifdef DEBUG
  printf("  read1Rule Ende\n");
#endif
  return(TRUE);
 } /* read1Rule */



/*====================================================================== */
/* Einlesen der Regeln der Grammatik und abspeichern in der Datenstruktur */
/*====================================================================== */
#ifdef __STDC__
static BOOL readRules(void)
{
#else
static BOOL readRules()
 {
#endif
  Evar ext_lhs;       /* linke Seite einer Regel, Externdarstellung  */
  Symb lhs;           /* linke Seite einer Regel, Interndarstellung  */

#ifdef DEBUG
  printf(" readRules()\n");
#endif
 /* ------------------------------------------------------- */
 /* Initialisierung der Variablen                           */
 /* ------------------------------------------------------- */
  topitem = MINH;     /* erstes freies Item an Anfang       */
  topprod = MINP;     /* erste freie Produktion an Anfang   */

 /* ------------------------------------------------------- */
 /* Einlesen der Regeln                                     */
 /* ------------------------------------------------------- */
  READEVAR(ext_lhs);  /* erste linke Seite einlesen     */
  while (ext_lhs != ende_regeln)  /* alle Regeln einlesen  */
   {
    lhs = EXT_TO_INT(ext_lhs);     /* in internes Format umwandeln  */
    /* linke Seite muss normales Nonterminal sein   */
    INKONSISTENT( ! ISNONT(lhs) || lhs == METAAXIOM);
    if (! read1Rule(lhs) )  /* Regel zu dieser linken Seite einlesen */
      return(FALSE);        /* Fehler in ReadRule                    */
    READEVAR(ext_lhs);      /* naechste linke Seite einlesen         */
   } /* while (ext_lhs != ende_regeln) */
  return(TRUE);
 } /* readRules */

/*====================================================================== */
/* Einlesen der externen Namen der Symbole und Meldung an den Dekoder     */
/*====================================================================== */

#ifdef __STDC__
static BOOL readNames(void)
{
#else
static BOOL readNames()
 {
#endif
  Term t;                 /* Terminalzeichen, dessen Name eingelesenen wird   */ 
  Nont n;                 /* Nonterminalzeichen,dessen Name eingelesenen wird */
  char ebuf[MAXNAMLEN+1]; /* Puffer fuer den Namen                            */

#ifdef DEBUG
  printf(" readNames()\n");
#endif
 /* --------------------------------------------------------------------- */
 /* Einlesen der Namen der Terminalsymbole in die Grammatik               */
 /* --------------------------------------------------------------------- */
  FOREACHTERM(t)                 /* Namen aller Terminalzeichen einlesen */
   {
    if ( t == RANDZCH )          /* Name Randzeichen intern vergeben     */
      TERMNAME(t) = "$EofSY";    /*  fester Name fuer Randzeichen        */
    else  /* Name aus Internform lesen */
     {      
      READNAME(ebuf);            /* String einlesen                      */
      if ( (TERMNAME(t) = (char *)MALLOC(strlen(ebuf)+1) ) ==NULL)
        mAbort();                /* nicht genug Speicher fuer Namen      */ 
      strcpy(TERMNAME(t),ebuf);  /* Namen in Grammatik kopieren          */
     }
#ifdef DEBUG
    printf("  %ld : %s\n",(long)t,TERMNAME(t) );
#endif
   } /* FOREACHTERM */

 /* ----------------------------------------------------------------------- */
 /* Einlesen der Namen der Nonterminalsymbole in die Grammatik              */
 /* ----------------------------------------------------------------------- */
  FOREACHNONT(n)                 /* Namen aller Terminalzeichen einlesen */
   {
    if ( n == METAAXIOM)         /* Name Metaaxiom intern vergeben       */
      NONTNAME(n) = "$Akzept";   /*  fester Name fuer Metaaxiom          */
    else  /* Name aus Internform lesen */
     {      
      READNAME(ebuf);            /* String einlesen                      */
      if ( (NONTNAME(n) = (char *)MALLOC(strlen(ebuf)+1) ) ==NULL)
        mAbort();                /* nicht genug Speicher fuer Namen      */ 
      strcpy(NONTNAME(n),ebuf);  /* Namen in Grammatik kopieren          */
     }
#ifdef DEBUG
    printf("  %ld : %s\n",(long)n,NONTNAME(n) );
#endif
   } /* FOREACHNONT */
  return(TRUE);
 } /* readNames */

/*====================================================================== */
/* Augmentierung der Grammatik                                            */
/* Metaproduktion : METAAXIOM ::= AXIOM RANDZCH                           */
/*====================================================================== */
#ifdef __STDC__
static BOOL augmentGrammar(void)
{
#else
static BOOL augmentGrammar()
 {
#endif
#ifdef DEBUG
  printf(" augmentGrammar()\n");
#endif

  METAPROD = topitem;                /* Anfangsitem abspeichern               */
  initRule(METAAXIOM);               /* Regel der Metaproduktion              */
  if (!initProd(METAAXIOM) )         /* linke Seite der Metaproduktion        */
    return(FALSE);
  if (!putRHS(AXIOM) )               /* Anfang rechte Seite Metaproduktion    */
    return(FALSE);
  if (!putRHS(RANDZCH))              /* Ende rechte Seite Metaproduktion      */
    return(FALSE);
  setProd();                         /* Produktion vervollstaendigen          */

  return(TRUE);

 } /* augmentGrammar */

/*====================================================================== */
/* Bereichspruefung und Initialisierung der Grammatik                     */
/*====================================================================== */
#ifdef __STDC__
static BOOL getGrammar(void)
{
#else
static BOOL getGrammar()
 {
#endif
  /* --------------------------------------------------------- */
  /* Ueberpruefungen, ob Typen ausreichend gross               */
  /* --------------------------------------------------------- */

  /* Terminalsymbole inklusive Randzeichen                     */
  ZUGROSS(ext_maxt-ext_mint+1 > CMAXT-CMINT,"Zu viele Terminalsymbole\n");

  /* Nonterminalsymbole inklusive Metaaxiom                    */
  ZUGROSS(ext_maxn-ext_minn+1 > CMAXN-CMINN,"Zu viele Nonterminalsymbole\n");

  /* Produktionen inklusive Metaproduktion                     */
  ZUGROSS(anzp > CMAXP-CMINP,"Zu viele Produktionen\n");

  /* Items, ergaenzt um linke Seiten und Metaproduktionsitems  */
  ZUGROSS(anzi+anzp+3 > CMAXH-CMINH+1,"Zu viele Positionen\n");

  /* --------------------------------------------------------- */
  /* Aufruf der Initialisierung mit ge"cast"eten Werten        */
  /* Terminale beginnen "hinter" Randzeichen                   */
  /* bei Nonterminalen Metaaxiom beruecksichtigt               */
  /* bei Produktionen und Items Metaproduktion beruecksichtigt */
  /* --------------------------------------------------------- */

  return(initGrammar((Term)(CMINT+ext_maxt-ext_mint+1),
                     (Nont)(CMINN+ext_maxn-ext_minn+1),
                     (Item)(anzp+1),
                     (Item)(anzi+2) ) );

 } /* getGrammar */

/*====================================================================== */
/* Einlesen der Grammatikinternform aus der Datei edatei_name             */
/*   Rueckgabewert : TRUE, falls Einlesen erfolgreich                     */
/*                   FALSE, falls Fehler beim Einlesen                    */
/*====================================================================== */
#ifdef __STDC__
BOOL readInternform(char *edatei_name)
#else
BOOL readInternform(edatei_name)
 char *edatei_name;
#endif
 {

  if ( (intdatei = OpenFile(edatei_name,"r") ) == NULL) /* Datei oeffnen */
   { /* Oeffnen nicht erfolgreich */
    return(FALSE);
   } 

 /* ----------------------------------------------------------- */
 /* Ueberpruefung, ob Eingabedatei gueltige Internformdatei ist */
 /* ----------------------------------------------------------- */
  {
   long magic_nr;    /* Magic-Nr. am Internformanfang */

   fscanf(intdatei,"%lx",&magic_nr);   /* Magic-Nr. einlesen         */
   if (magic_nr != MAGIC_CH2_GRM)      /* Datei ist nicht Internform */
    { /* Pruefen, ob in zweiter Zeile MAGIC vorhanden */
     int c;

     while ((c = fgetc(intdatei) ) != EOF && c != '\n');
     if (c == EOF || 
       (fscanf(intdatei,"%lx",&magic_nr),(magic_nr != MAGIC_CH2_GRM) ) )
      {
       Error0("Eingabedatei ist keine Grammatikinternform\n");
       return(FALSE);
      }
    } /* != MAGIC */
   }

 /* ----------------------------------------------------------- */
 /* Einlesen der Bereichs- und Delimiterdefinitionen            */
 /* ----------------------------------------------------------- */
  if (! readDefs())       /* Definitionen einlesen                            */
    return(FALSE);        /* Fehler in den Definitionen                       */ 

  if (! checkDefs())      /* auf Konsistenz ueberpruefen                      */
    return(FALSE);        /* Definitionen inkonsistent                        */ 

  if (! getGrammar())     /* Datenstrukturen bereitstellen                    */
    return(FALSE);        /* kein Speicher etc.                               */ 

  if (! readAxiom())      /* Axiom einlesen                                   */
    return(FALSE);        /* ungueltig                                        */ 

  if (! readRules())      /* alle Regeln einlesen                             */
    return(FALSE);        /* Fehler beim Einlesen                             */ 

  if (! readNames())      /* Externe Namen der Symbole Einlesen               */
    return(FALSE);        /* Fehler beim Einlesen                             */ 

  if (! augmentGrammar()) /* Grammatik augmentieren ab topitem                */
    return(FALSE);        /* Fehler beim Augmentieren                         */ 

  return(TRUE);	       /* bisher kein Fehler aufgetreten                   */
 } /* readInternform */

