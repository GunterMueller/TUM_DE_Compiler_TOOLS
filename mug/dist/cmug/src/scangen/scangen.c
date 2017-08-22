
/* *************************************************************** */
/* Scangen.c : Scanner-Generator Hauptmodul                        */
/* --------------------------------------------------------------- */
/* zu verwenden mit generiertem Scanner sgsc                       */
/* --------------------------------------------------------------- */
/* Aenderung 11.12.91, Ulrich Vollath: Erweiterung um die Specials */
/*			cstingsy, cnumbersy, ccharsy		   */
/* Aenderung 23.01.91, Ulrich Vollath: Erweiterungen realsy,       */
/*                           $idents, case_sensitive               */
/* Aenderung 22.01.91, Ulrich Vollath: Ausgabe einer Datenstruktur */
/* Aenderung 10.01.91, Ulrich Vollath: neue CMUG-Schnittstellen    */
/*                     grosses Aufraeumen, Ausgaben nur noch       */
/*                     fehlerfreier Eingabe (decfile)              */
/* Aenderung : 25.10.90, ansifiziert                               */
/* Aenderung : 14.11.89, isEscape(), da GCC ueberfluessig          */
/*             ge-\-te Zeichen kritisiert                          */
/* Aenderung : 14.07.89, generierte include-Pfade geaendert        */
/* Aenderung : 09.06.89, #ifdef __MSDOS__                          */
/* Aenderung : 20.2.88 : Anpassung an                              */
/*                 MUG-Benutzeroberflaeche,                        */
/*  ersetzen aller int durch long oder short                       */
/*  Abpruefung der malloc's auf NULL                               */
/* *************************************************************** */


/*
 * (c) copyright 1989 by Technische Universitaet Muenchen, Germany
 *
 *      This product is part of MiniMUG (Modularer Uebersetzer-Generator)
 *
 * Permission to use, sell, duplicate or disclose this software must be
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

#ifdef __STDC__
#include <stddef.h>
#include <stdlib.h>
#endif
#include <string.h>  
#include <time.h>
#include <ctype.h>
#ifdef __MSDOS__
#include <alloc.h>
#include <process.h>
#include <dos.h>
#endif /* __MSDOS__ */
#include <stdio.h>
#include "scangen.h"   /* Headerfile Generator                            */
#include "ps_token.h"  /* vom Scanner geliefertes Token                   */
#include "scanfunk.h"  /* Funktionalitaeten generierte Scanner */

#ifndef __STDC__
char *malloc();
#endif

#ifndef TRUE
#define TRUE 1
#endif
#ifndef FALSE
#define FALSE 0
#endif

/* Klassencode fuer Dateiende */
#define Keof 0L

/* ==================================== */
/* Fehlermeldungen                      */
/* ==================================== */
#define sgerrEOF "unerwartetes Dateiende"
#define sgerrIOS "Klasse oder Steueranweisung erwartet"
#define sgerrST  "Steueranweisung erwartet"
#define sgerrREL "Relativcode erwartet"
#define sgerrSDF "Symboldefinition erwartet"
#define sgerrSPD "SPECIAL bereits verwendet"
#define sgerrKDP "KEYWORD bereits verwendet"
#define sgerrWSK "Warnung : KEYWORD-Definition nach #SPECIALS"
#define sgerrUSP "SPECIAL unbekannt"
#define sgerrCOM "COMBEGSY / COMENDSY nicht gemeinsam"

/* =================================================================== */
/* Fehlerbehandlung                                                    */
/* ------------------------------------------------------------------- */
/* Fehlerdatei wird nur geoeffnet, falls tatsaechlich Fehler vorhanden */
/* Fehlerausgabe parallel auf Fehlerdatei scangen.err und stderr       */
/* =================================================================== */
FILE *errordatei = NULL; /* Datei fuer Fehlermeldungen, vom Scanner import.*/
FILE *errorfile  = NULL; /* Datei fuer Fehlermeldungen, vom Scanner import.*/
int  protokoll   = 1;    /* Fehlerprotokoll in Datei gewuenscht,           */

/* Fehlerstatus fuer Abbruch der Generierung */
#define FEHLER 20

/* ==================================== */
/* globale Variablen                    */
/* ==================================== */
FILE *ScanEin; /* Eingabedatei, wird vom Scanner importiert */
/* --------------- */
/* Ausgabedateien  */
/* --------------- */
typedef int bool;

static FILE *headerfile,*initfile,*specfile,*decfile;
static FILE *dsfile;           /* Datei fuer die Datenstruktur              */

static bool  alt;              /* Erzeugung der alten Ausgaben              */
static Token symb;             /* aktuelles erkanntes Symbol                */
static Token looksym;          /* bei Lookaheadfunktion eingelesenes Symbol */
static int   lookahvorh;       /* Lookaheadsymbol vorhanden                 */
extern char  *strtab[];        /* Stringtabelle von sgsc, dreckiger Trick   */
static int   ScangenErrors;    /* Anzahl Generatorfehler                    */
static long  klasse,relcode;   /* des einzutragenden Symbols                */
static bool  ignore;           /* aktuelles Symbol wird nicht gemeldet      */
static char  *decspec;         /* dekodiertes aktuelles Special             */
static long  decspec_size = 0; /* aktuell allokierte Groesse                */
#define DECSPEC_INCR 100       /* Inkrement fuer Vergroessern des Strings   */

/* Zur Ausgabe einer nicht benoetigten Funktion in die Tabelle */
static char *null_function = "NULL,\n";

typedef struct KeydefR *Keydef;
typedef struct KeydefR { /* Beschreibung eines Keywords */
			Keydef next;  /* naechtser in Gesamtliste         */
        	        long kc;      /* Klassencode (synt. Wert)         */
                	long rc;      /* Relativcode (semant. Wert)       */
			bool issym;   /* ist als Symbol definiert         */
			bool ignore;  /* Token nicht ausgegeben           */
			bool cstyle;  /* Token C-(un)artig interpretieren */
			char *strg;   /* dekodiertes Schluesselwort       */
	               } KeydefRec;

/* ------------------------------------------------ */
/* Variablen fuer die Scannerspezifikation          */
/* ------------------------------------------------ */
static bool      comments;          /* Kommentare in {...}                */
static bool      mcomments;         /* Kommentare in (*...*)              */
static bool      ccomments;         /* Kommentare in /_* ... *_/          */
static bool      linedirs;          /* line-Direktiven # line "file"      */
static bool      combegsy,comendsy; /* MUG-Version fuer comments          */
static bool      dollar_idents;     /* $ in Bezeichnern erlaubt ?         */
static bool      case_sensitive;    /* Gross- und Kleinschreibung signif. */
static long      max_look;          /* maximale Zeichenvorausschau        */
static Keydef    keywords;          /* Liste aller Keywords               */
static KeydefRec Identsy;	    /* Spezifikation zu Bezeichnern       */
static KeydefRec Stringsy;          /* Spezifikation zu Strings           */
static KeydefRec Intsy;             /* Spezifikation zu ganzen Zahlen     */
static KeydefRec Realsy;            /* Spezifikation zu Real-Zahlen       */
static KeydefRec Charsy;            /* Spezifikation zu Character-Konst.  */
static bool      dotdot;	    /* .. ist Special                     */

/* ================================================================ */
/* Initialisierung der Flags fuer den generierten Scanner           */
/* ================================================================ */
#ifdef __STDC__
static void initDefaults(void)
#else
static void initDefaults()
#endif
 {
   comments       = FALSE;
   mcomments      = FALSE;
   ccomments      = FALSE;
   combegsy       = FALSE;
   comendsy       = FALSE;
   linedirs	  = FALSE;
   dollar_idents  = FALSE;
   case_sensitive = FALSE;
   lookahvorh     = FALSE;
   max_look       = 0;
   Intsy.issym    = FALSE;
   Stringsy.issym = FALSE;
   Identsy.issym  = FALSE;
   Realsy.issym   = FALSE;
   Charsy.issym   = FALSE;
   dotdot         = FALSE;
 } /* initDefaults */

/* ==================================================== */
/* Oeffnen des Fehlerfiles bei der ersten Fehlermeldung */
/* ==================================================== */
#ifdef __STDC__
int OpenErr(void)
#else
int OpenErr()
#endif
 {
  if (errordatei == NULL) /* sonst schon geoeffnet */
   {
    if ((errordatei=fopen("scangen.err","w")) == NULL)
     {
      fputs("Fehlerdatei scangen.err kann nicht geoeffnet werden !\n",stderr);
      return(0); 
     }
   }
  errorfile = errordatei;
  return(1);
 } /* OpenErr */


/* ==================================================== */
/* Fehlermeldung des Generators                         */
/* ==================================================== */
#ifdef __STDC__
static void sgerr(char *meld)
#else
static void sgerr(meld)
 char *meld;
#endif
 {
  wErrorf(QUELL_ORT(symb),"bei \"%T\": %s\n",symb,meld);
  ScangenErrors++;
 } /* sgerr */

/* *********************** */
/* Sonderzeichenverwaltung */
/* *********************** */
typedef int Fctn;
#define FCTN_UNDEF     ((Fctn)0)
#define FCTN_COMMENTS  ((Fctn)1)
#define FCTN_MCOMMENTS ((Fctn)2)
#define FCTN_CCOMMENTS ((Fctn)3)
#define FCTN_STRINGS   ((Fctn)4)
#define FCTN_CSTRINGS  ((Fctn)5)
#define FCTN_CCHARS    ((Fctn)6)
#define FCTN_LINEDIRS  ((Fctn)7)
static char *fctn_names[] = {
	"NULL",  	/* keine Funktion verwendet 	*/
	"psComments",   /* Kommentare in {...}      	*/
	"psMcomments",  /* Kommentare in (*...*)    	*/
	"psCcomments",  /* Kommentare in {...}      	*/
	"psStrings",    /* Strings in "..." oder '...' 	*/
	"psCstrings",	/* Strings wie in C		*/
	"psCchars",	/* Characterkonstanten wie in C */
	"psLinedirs",	/* Linedirektiven a la cpp      */
	};

typedef struct SpecElRec *SpecPt; /* Zeiger auf SPECIAL         */
typedef struct SpecElRec {    /* Element der SPECIAL-Trees             */
	      SpecPt next;    /* Brueder                               */
	      SpecPt sons;    /* Soehne                                */
              long   kc;      /* Klassencode                           */
              long   rc;      /* Relcode, falls Symbol                 */
              int    issym;   /* TRUE, falls gueltiges Symbol bis hier */
	      bool   ignore;  /* wird nicht gemeldet         	       */
	      Fctn   fctn;    /* zugeordnete Funktion oder NULL        */
              char   sz;      /* Sonderzeichen                         */
              } SpecEl;
static SpecPt SpecTree; /* alle SPECIALs im Baum      */
static SpecPt SpecPos;  /* momentane Position im Baum */

/* ==================================================== */
/* liefert Sonderzeichen zum aktuellen Symbol           */
/* ==================================================== */
#ifdef __STDC__
static char getsz(void)
{
#else
static char getsz()
 {
#endif
  static char sz[] = "!\"$%&\'()*+,-./:;<=>?@[\\]^_`}|{~";
  char  dsz; /* dekodiertes Sonderzeichen */

  if (SYM(symb) ==4)
    dsz = '#';
  else
    dsz = sz[SEMVAL(symb)-1];
  return(dsz);
 }  /* getsz */

/* ================================================================ */
/* liefert TRUE, falls sonderzeichen in Konstanten escaped werden   */
/* muss                                                             */
/* ================================================================ */
#ifdef __STDC__
static bool isEscape(char c)
{
#else
static bool isEscape(c)
 char c;
 {
#endif
  switch(c) 
   {
    case '\\':
    case '\"':
    case '\'':
      return(1);
    default:
      return(0);
   }
 } /* isEscape */

/* ================================================================ */
/* liefert SPECIAL-String zum aktuellen Symbol (= vordef. Special ) */
/* ================================================================ */
#ifdef __STDC__
static char *getdef(void)
{
#else
static char *getdef()
 {
#endif
  static char *szs[] = { /* Array der dekodierten Specials */
   /* relcode */  /* SPECIAL */
   /* 1 */        "->",
   /* 2 */        "",
   /* 3 */        ";",
   /* 4 */        ":=",
   /* 5 */        ".",
   /* 6 */        "",
   /* 7 */        ":",
   /* 8 */        ",",
   /* 9 */        "$",
   /* 10 */        "=",
   /* 11 */        "<=",
   /* 12 */        "<",
   /* 13 */        "[",
   /* 14 */        "(",
   /* 15 */        "-",
   /* 16 */        "..",
   /* 17 */        "@",
   /* 18 */        "<>",
   /* 19 */        "%",
   /* 20 */        "]",
   /* 21 */        "+",
   /* 22 */        "",
   /* 23 */        ")",
   /* 24 */        "/",
   /* 25 */        "*",
   /* 26 */        ">",
   /* 27 */        ">="   }; /* Ende Initialisierung */
  char *dsp; /* dekodiertes SPECIAL */

  dsp = szs[SEMVAL(symb) - 1];
  return (dsp);
 } /* getdef */

/* ================================================================ */
/* liefert Zeiger auf Eintrag mit sz in ebene, ggf Neuerfassung     */
/* Ebene sortiert nach sz                                           */
/* ================================================================ */
#ifdef __STDC__
static SpecPt getpos(char sz, SpecPt *ebene)
#else
static SpecPt getpos(sz,ebene)
 char sz; /* gesuchtes Sonderzeichen */
 SpecPt *ebene; /* zu durchsuchende Ebene */
#endif
 {
  SpecPt such,vorg;

  for(such = *ebene,vorg = NULL; such != NULL && such->sz < sz ;
      vorg = such, such = such->next);
  if (such == NULL || such->sz > sz) /* nicht gefunden */
    {
     if ( (such = (SpecPt)malloc(sizeof(SpecEl) ))==NULL)
      {
       memError();
       exit(FEHLER); /* fataler Fehler */
      }
     if (vorg == NULL)    
      {
       such->next  = *ebene; /* Prefix-Operation in Ebene */
       *ebene = such;        /* neues erstes Element */
      }
     else
      {
       such->next = vorg->next;    /* nach vorg einfuegen  */
       vorg->next = such;          /* nach vorg einfuegen  */
      }
     such->sons  = NULL;   /* wird neue Blatt      */
     such->sz    = sz;     /* Zeichen setzen       */
     such->issym = FALSE;  /* initialisieren       */
    }
  return(such);
 } /* getpos */

/* ================================================================ */
/* setzt Suchpfad fuer SPECIALS in erste Ebene                      */
/* ================================================================ */
#ifdef __STDC__
static void InitSpec(char sz)
          /* Stelle in wurzelebene */
#else
static void InitSpec(sz)
 char sz; /* Stelle in wurzelebene */
#endif
 {
  SpecPos = getpos(sz,&SpecTree);
 } /* InitSpec */


/* ================================================================ */
/* verlaengert aktuellen Special-Pfad um ein Zeichen                */
/* ================================================================ */
#ifdef __STDC__
static void AppendSpec(char sz)
#else
static void AppendSpec(sz)
 char sz;
#endif
 {
  SpecPos = getpos(sz,&(SpecPos->sons) ) ; /* in naechste Ebene */
 } /* AppendSpec */

/* ================================================================ */
/* Setzt aktuellen Specialpfad als Symbol                           */
/* ================================================================ */
#ifdef __STDC__
static void SpecEintrag(Fctn fctn)
#else
static void SpecEintrag(fctn)
 Fctn fctn;
#endif
 {
  if (SpecPos->issym) /* schon definiert */
    sgerr(sgerrSPD);  /* SPECIAL doppelt */
  else
   {
    SpecPos->issym  = TRUE;
    SpecPos->fctn   = fctn;
    SpecPos->kc     = klasse;
    SpecPos->rc     = relcode;
    SpecPos->ignore = ignore;
   }
  } /* SpecEintrag */

/* ================================================================ */
/* Setzt einen String im Special-Baum   			    */
/* ================================================================ */
#ifdef __STDC__
static void specStrg(char *strg,Fctn fctn)
#else
static void specStrg(strg,fctn)
 char *strg;
 Fctn fctn;
#endif
 {
  char *spd;

  InitSpec(*strg); /* erstes Zeichen */
  for (spd = strg+1; *spd!='\0';spd++)
    AppendSpec(*spd); /* Pfad abarbeiten */
  SpecEintrag(fctn);
 } /* specStrg */

/* ================================================================ */
/* gibt Programmteil fuer erkanntes SPECIAL aus                     */
/* ================================================================ */
#ifdef __STDC__
static void erkanntaus(int tiefe, long kc, long rc)
#else
static void erkanntaus(tiefe,kc,rc)
 int   tiefe; /* Anzahl der Zeichen aus dem SPECIAL besteht */
 long  kc;
 long  rc;    /* Symbolwerte                                */
#endif
 {
  fprintf(specfile,"skipein(%ldL);*rwert=%ldL;return(%ldL);\n",
          (long)tiefe,rc,(long)kc); /* Code fuer ueberlesen und Token setzen */
 } /* erkanntaus */

/* ================================================================ */
/* Initialisierung des dekodierten Specials                         */
/* ================================================================ */
#ifdef __STDC__
static void initDecspec(void)
#else
static void initDecspec()
#endif
 {
 } /* initDecSpec */

/* ================================================================ */
/* Ausgabe des dekodierten Specials in Dekoderdatei                 */
/* ================================================================ */
#ifdef __STDC__
static void outDecspec(long kc, long rc, long ign, Fctn fctn)
#else
static void outDecspec(kc,rc,ign,fctn)
 long kc;
 long rc;
 long ign;
 Fctn fctn;
#endif
 {
  char *s;

  if (alt)  
    fprintf(decfile,"if ((kc==%ld)&&(rc==%ld)){\nstrcpy(decstr,\"",
            kc,rc); /* fuer Dekodergenerierung */
  else
    fputs("{\"",dsfile);
  for (s = decspec; s != NULL && *s; s++)
   {
    if (isEscape(*s))
     {
      if (alt)
        fputc('\\',decfile);
      else
        fputc('\\',dsfile);
     }
    if (alt)
      fputc(*s,decfile);
    else
      fputc(*s,dsfile);
   }
  if (alt)
    fputs("\");\nreturn;\n};\n",decfile);
  else
    fprintf(dsfile,"\",%ldL,%ldL,%ldL,%s},\n",kc,rc,ign,fctn_names[fctn]);
  dotdot |= !strcmp("..",decspec);  /* Special ".." ? */
 } /* outDecspec */

/* ================================================================ */
/* Eintragen eines Zeichens in dekodierten Special                  */
/* ================================================================ */
#ifdef __STDC__
static void putDecspec(int c,int i)
#else
static void putDecspec(c,i)
 int c;
 int i;
#endif
 {
  while (i > decspec_size)
   { /* Puffer vergroessern */
    decspec_size += DECSPEC_INCR;
    if (decspec == NULL)
      decspec = (char *)malloc(decspec_size);
    else
      decspec = (char *)realloc(decspec,decspec_size);
   } /* Puffer vergroessern */
  decspec[i-1] = c;
  decspec[i] = '\0';
 } /* putDecspec */

/* ================================================================ */
/* setzt rekursiv Ebene in Fallunterscheidungen um                  */
/* ================================================================ */
#ifdef __STDC__
static void SpecTreeP(SpecPt ebene, int tiefe, SpecPt erkannt)
#else
static void SpecTreeP(ebene,tiefe,erkannt)
 SpecPt ebene;   /* abzuarbeitende Ebene                 */
 int    tiefe;   /* Tiefe im gesamten SPECIALS-Baum      */
 SpecPt erkannt; /* Zeiger auf bereits erkanntes SPECIAL */
#endif
 {
  SpecPt aktsz; /* momentan bearbeitetes Zeichen im Baum */

  if (tiefe==1) /* Wurzelebene : Fallunterscheidung ueber ezchn */
   {
    initDecspec();
    if (alt)
      fputs("switch(ezchn){\n",specfile);
   }
  else          /* mit Lookahead                                */
   {
    if (alt)
      fprintf(specfile,"switch(scanlah(%ldL)){\n",(long)(tiefe-1));
    if (tiefe-1 > max_look)
      max_look = tiefe-1;
   }
  /* ebene abarbeiten */
  for (aktsz=ebene ; aktsz != NULL ; aktsz = (SpecPt)aktsz->next)
   {   /* ueber alle Elemente */
    putDecspec(aktsz->sz,tiefe); /* an dekodiertes Special anhaengen */
    if (aktsz->issym)
      outDecspec((long)aktsz->kc,(long)aktsz->rc,(long)aktsz->ignore,
                 aktsz->fctn);
    if (alt)
     {
      fputs("case '",specfile);
      if (isEscape(aktsz->sz))
        fputc('\\',specfile);
      fputc((int)aktsz->sz,specfile);
      fputs("' :\n",specfile);
     }
    if (aktsz->sons != NULL)    /* moegliche laengere SPECIALS abarbeiten */
     {
      if (aktsz->issym) /* kann bereits ausgegeben werden */
        SpecTreeP(aktsz->sons,tiefe+1,aktsz);
      else  /* Sonderzeichenfolge nicht in dieser Ebene */
        SpecTreeP(aktsz->sons,tiefe+1,NULL);
     }
    else if (alt) /* Element ist Blatt, ausgeben */
      erkanntaus(tiefe,aktsz->kc,aktsz->rc);
   }  /* Ende Schleife ueber alle Ebenen-Elemente */
  if (alt)
   {
    if (tiefe>1) /* evtl. noch kuerzere Symbole vorhanden */
     {
      if (erkannt != NULL)    /* Teil des Pfades ist ein Symbol     */
       {
        fputs("};",specfile); /* case abschliessen, kurzeres Symbol */
        erkanntaus(tiefe-1,erkannt->kc,erkannt->rc);
       }
      else
        fputs("};break;\n",specfile); /* case  beenden, Sackgasse  */
     }
    else
      fputs("};\n",specfile); /* Ende aeusserer switch */
   }
 } /* Ende SpecTreeP */

/* ================================================================ */
/* traegt Token als Keyword ein                                     */
/* ================================================================ */
#ifdef __STDC__
static void Eintrag(Token symb)
#else
static void Eintrag(symb)
 Token symb;
#endif
 {
  if (!isTokenvalid(symb))
    return;
  if (SEMPTR(symb) != NULL && 
      ((Keydef)SEMPTR(symb))->issym)
    sgerr(sgerrKDP); /* Keyword doppelt */
  else
   {
    if (SEMPTR(symb) == NULL)
     {
      if ((SEMPTR(symb) = (char *)malloc(sizeof(KeydefRec))) == NULL)
       {
        memError();
        exit(FEHLER);
       }
      ((Keydef)SEMPTR(symb))->next  = keywords; /* vorne in Liste */
      keywords = (Keydef)SEMPTR(symb);
     }
    ((Keydef)SEMPTR(symb))->issym  = TRUE;
    ((Keydef)SEMPTR(symb))->kc     = klasse;
    ((Keydef)SEMPTR(symb))->rc     = relcode;
    ((Keydef)SEMPTR(symb))->ignore = ignore;
    ((Keydef)SEMPTR(symb))->strg   = scanDecode(NULL,symb);
   }
 } /* Eintrag */

/* ================================================================ */
/* Initialisieren der Tabellen etc                                  */
/* ================================================================ */
#ifdef __STDC__
static void inittabs(void)
#else
static void inittabs()
#endif
 {
  SpecTree = NULL;
  keywords = NULL;
  if ((symb = allocToken()) == NULL ||
      (looksym = allocToken()) == NULL)
   {
    memError();
    exit(FEHLER);
   }
 } /* inittabs */

/* ================================================================ */
/* Einlesen des naechsten Symbols                                   */
/* ================================================================ */
#ifdef __STDC__
static void nextsym(void)
#else
static void nextsym()
#endif
 {
  if (lookahvorh) /* Lookahead vorhanden */
   {
    Token h;              /* Hilfsvariable fuer Ringtausch        */

    h          = symb;
    symb       = looksym;
    looksym    = h;
    lookahvorh = FALSE;   /* Lookahead "aufgebraucht"             */
   }
  else if (!scanNext(symb))
    exit(FEHLER);
 } /* nextsym */

/* ================================================================ */
/* Lookahead-Generierung                                            */
/* Ergebnis : Klasse der naechsten Symbols                          */
/* ================================================================ */
#ifdef __STDC__
static long lookahsym(void)
#else
static long lookahsym()
#endif
 {
  if (SYM(symb) !=Keof)
   {
    scanNext(looksym);
    lookahvorh = TRUE;
    return((long)SYM(looksym));
   }
  return((long)Keof);
 }

/* ******************************** */
/* Verwaltung der erzeugten Dateien */
/* ******************************** */

/* ================================================================ */
/* oeffnet Datei <scannername>ext als file                          */
/* ================================================================ */
#ifdef __STDC__
static FILE *openaus(char *scanner, char *ext)
#else
static FILE *openaus(scanner,ext)
 char *scanner; /* scannername */
 char *ext; /* extension */
#endif
 {
  char *filename; /* gesamter Dateiname inkl. Pfad */
  FILE *af;       /* Ausgabefile-Pointer           */
#ifndef __MSDOS__
  long clock;     /* Internes Zeitformat           */
#else /* __MSDOS__ */
  struct date da;
  struct time uz; /* Internes Zeitformat           */

  getdate(&da); gettime(&uz);
#endif /* __MSDOS__ */

  if ((filename = (char *)malloc(strlen(scanner)+strlen(ext)+1)) == NULL)
   {
    memError();
    exit(FEHLER);
   }
  strcat(strcpy(filename,scanner),ext);
  if ((af = fopen(filename,"w") ) == NULL ) /* nicht geoeffnet */
   {
    fprintf(stderr,"Ausgabedatei %s kann nicht geoeffnet werden\n",
                    filename);
    exit(FEHLER);
   }
  /* Dateiidentifikation ausgeben, erzeugte Dateien sind C-Programme */
#ifndef __MSDOS__
   time(&clock); /* Interne Uhrzeit */
   fprintf(af,"/* Datei : %s , generiert : %.24s */\n",filename,
              ctime(&clock) );
#else /* __MSDOS__ */
     fprintf(af,"/* Datei : %s , generiert : %02d-%02d-%d : %02d:%02d */\n",filename,
              da.da_day, da.da_mon, da.da_year, uz.ti_hour, uz.ti_min );
#endif /* __MSDOS__ */
   return(af);
 } /* openaus */

/* ================================================================ */
/* Hauptprogramm                                                    */
/* ================================================================ */
#ifdef __STDC__
int main(int argc, char *argv[])
{
#else
int main(argc,argv)
 int argc;
 char *argv[];
 {
#endif
  bool   special;             /* Flag, welcher Eingabetyp aktuell    */
  int    Zust;                /* aktueller Zustand endlicher Automat */
  Keydef kw;                  /* momentan verarbeitetes KEYWORD      */
  char   *input_name = NULL;  /* Name der Eingabedatei               */
  char   *output_name = NULL; /* Name der Eingabedatei(en)           */

  printf("CMUG-Scannergenerator 2.0 vom %s (U.Vollath)\n",ProgDatum);
  if (argc == 3)
   {
    input_name = argv[1];
    output_name = argv[2];
   }
  else if (argc == 4 && (alt = !strcmp(argv[1],"-old")))
   {
    input_name = argv[2];
    output_name = argv[3];
   }
  else /* falscher Aufruf */
   {
    fprintf(stderr,
            "Aufruf : %s [-old] <Scannerbeschreibung> <Scannername>\n",
            argv[0] );
    exit(FEHLER);
   }
  /* ================== */
  /* Decoderfile-Anfang */
  /* ================== */
  if (!scanInit() || !scanOpen(input_name))
    exit(FEHLER);         /* Scanner initialisieren  */
  inittabs();             /* Tabellen initialisieren */ 
  initDefaults();         /* Voreinstellungen        */
  nextsym();              /* erstes Symbol lesen     */
  ScangenErrors = 0;      /* Anzahl Fehler           */
  /* -------------------------------------------------------- */
  /* endlichen Automaten fuer die Eingabedatei abarbeiten     */
  /* -------------------------------------------------------- */
  special       = FALSE;    /* default-Wert                          */
  Zust = 0;                 /* Start-Zustand des endlichen Automaten */
  while (SYM(symb) != Keof) /* gesamte Eingabe lesen                 */
   {
    switch(Zust)
     { /* Implementierung des endlichen Automaten */
      case 0 : /* Startzustand */
         switch(SYM(symb))
           {
            case 2 : /* Integerzahl */
                 klasse = SEMVAL(symb);  /* Klassencode merken   */
		 ignore = FALSE;         /* wird nicht ignoriert */
                 Zust = 2;
                 nextsym();
                 break;
            case 4 : /* # */
                 Zust = 1;
                 nextsym();
                 break;
	    case 8 : /* ignore */
                 klasse = 0;
                 relcode = 0;
		 ignore = TRUE;          /* Symbol wird ignoriert  */
                 Zust = 3;               /* weiter mit dem Symbol  */
                 nextsym();
                 break;
            default :
                 sgerr(sgerrIOS); /* Integer oder Steueranweisung erwartet */
                 if (SYM(symb) != Keof) nextsym();
           }
          break; /* Ende Zustand 0 */

        case 1 : /* # gelesen */
          switch(SYM(symb))
           {
            case 3 : /* gueltige Steueranweisung */
                 switch(SEMVAL(symb)){
                 case 1 : /* #specials */
                          special = TRUE;
                          break;
                 case 2 : /* #keywords */
                          special = FALSE;
                          break;
                 case 3 : /* #comments  */
                           comments = TRUE;
			   ignore   = TRUE;
			   specStrg("{",FCTN_COMMENTS);
                           break;
                 case 4 : /* #mcomments */
                           mcomments = TRUE;
			   ignore   = TRUE;
			   specStrg("(*",FCTN_MCOMMENTS);
                           break;
                 case 5 : /* #ccomments */
                           ccomments = TRUE;
			   ignore   = TRUE;
			   specStrg("/*",FCTN_CCOMMENTS);
                           break;
                 case 6 : /* $idents */
                           dollar_idents = TRUE;
                           break;
                 case 7 : /* case_sensitive */
                           case_sensitive = TRUE;
                           break;
                 case 8 : /* line_directives */
                           linedirs = TRUE;
                           break;
                 }; /* switch */
                 Zust = 0;
                 nextsym();
                 break;
            default :
                 sgerr(sgerrST); /* Steueranweisung erwartet */
                 Zust = 0;
                 if (SYM(symb) != Keof)  nextsym();
           }
          break; /* Ende Zustand 1 */

        case 2 : /* Klasse gelesen */
          switch(SYM(symb))
           {
            case 2 : /* Integerzahl */
                 relcode = SEMVAL(symb); /* Relativcode */
                 Zust = 3;
                 nextsym();
                 break;
            default :
                 sgerr(sgerrREL); /* Relativcode erwartet */
                 if (SYM(symb) != Keof) nextsym();
           }
          break; /* Ende Zustand 2 */

        case 3 : /* Klasse/Relcode gelesen */
          switch(SYM(symb))
           {
            case 1 : /* Identifier */
                 if (special)
                   sgerr(sgerrUSP); /* Special unbekannt */
                 else /* !!!!!!!! */
                   Eintrag(symb); /* in Schluesselworttabelle */
                 Zust = 0; 
                 break;
            case 3 : /* SPECIALS oder KEYWORDS : umwandeln */
                 if (special)                  
                  {
		   switch(SEMVAL(symb))
                    {
                     case 3 : /* #comments  */
                        comments = TRUE;
			specStrg("{",FCTN_COMMENTS);
                        break;
                     case 4 : /* #mcomments */
                        mcomments = TRUE;
			specStrg("(*",FCTN_MCOMMENTS);
                        break;
                     case 5 : /* #ccomments */
                        ccomments = TRUE;
			specStrg("/*",FCTN_CCOMMENTS);
                        break;
		     default:
                       sgerr(sgerrUSP); /* Special unbekannt */
		       break;
		    }	
                  }
                 else /* !!!!!!! */
                   Eintrag(symb); /* in Schluesselworttabelle */
                 Zust = 0;
                 break;
	    case 8 : /* ignore : dito			   */
                 if (special)
                  {
                   sgerr(sgerrUSP); /* Special unbekannt */
                  }
                 else /* !!!!!!! */
                   Eintrag(symb); /* in Schluesselworttabelle */
                 Zust = 0;
                 break;
            case 4 : /* # als Sonderzeichen interpretieren */
            case 5 : /* Sonderzeichen                      */
                 if (!special) 
                   sgerr(sgerrWSK); /* SPECIAL nach #keywords */
                 InitSpec(getsz()); /* char-Wert des Sonderzeichens */
                 if (lookahsym() == Keof) /* Dateiende folgt */
                  {
                   SpecEintrag(FCTN_UNDEF);
                   Zust = 0;
                  }
                 else
                   Zust = 4;
                 break;
            case 6 : /* vordefinierte SPECIALs */
                 if (special) /* vordefiniertes SPECIAL verwenden */
                  {
                   switch (SEMVAL(symb)) /* spezielle Werte extrahieren */
                    {
                     case 2 : /* Identsy */
                             if (Identsy.issym)
                               sgerr(sgerrSPD); /* bereits verwendet */
                             else
                              {
                               Identsy.kc     = klasse;
                               Identsy.rc     = relcode;
                               Identsy.issym  = TRUE;
                               Identsy.ignore = ignore;
                              }
                             break;
                     case 6  : /* strings    */
                             if (Stringsy.issym)
                               sgerr(sgerrSPD); /* bereits verwendet */
                             else
                              {
                               Stringsy.kc     = klasse;
                               Stringsy.rc     = relcode;
                               Stringsy.issym  = TRUE;
                               Stringsy.ignore = ignore;
			       Stringsy.cstyle = FALSE;
			       specStrg("\"",FCTN_STRINGS);
			       specStrg("'",FCTN_STRINGS);
                              }
                             break;
                     case 31 : /* C-strings  */
                             if (Stringsy.issym)
                               sgerr(sgerrSPD); /* bereits verwendet */
                             else
                              {
                               Stringsy.kc     = klasse;
                               Stringsy.rc     = relcode;
                               Stringsy.issym  = TRUE;
                               Stringsy.ignore = ignore;
			       Stringsy.cstyle = TRUE;
			       specStrg("\"",FCTN_CSTRINGS);
                              }
                             break;
                     case 22 : /* Integers */
                     case 33 : /* C-Integers */
                             if (Intsy.issym)
                              {
                               sgerr(sgerrSPD); /* bereits verwendet */
                              }
                             else
                              {
                               Intsy.kc     = klasse;
                               Intsy.rc     = relcode;
                               Intsy.issym  = TRUE;
                               Intsy.ignore = ignore;
			       Intsy.cstyle = (SEMVAL(symb) == 33);
                              }
                             break;
                     case 28 : /* combegsy */
                             if (combegsy)
                               sgerr(sgerrSPD);
                             else
			      {
                               combegsy = TRUE;
   			       ignore   = TRUE;
			       specStrg("{",FCTN_COMMENTS);
			      }
                             break;
                     case 29 : /* comendsy */
                             if (comendsy)
                               sgerr(sgerrSPD);
                             else
                               comendsy = TRUE;
                             break;
                     case 30 : /* realsy  */
		     case 34 : /* crealsy */
                             if (Realsy.issym)
                               sgerr(sgerrSPD);
                             else
                              {
                               Realsy.kc     = klasse;
                               Realsy.rc     = relcode;
                               Realsy.issym  = TRUE;
                               Realsy.ignore = ignore;
			       Realsy.cstyle = (SEMVAL(symb) == 34);
                              }
			     break;
                     case 32 : /* ccharsy */
                             if (Charsy.issym)
                               sgerr(sgerrSPD);
                             else
                              {
                               Charsy.kc     = klasse;
                               Charsy.rc     = relcode;
                               Charsy.issym  = TRUE;
                               Charsy.ignore = ignore;
			       Charsy.cstyle = TRUE;
			       specStrg("'",FCTN_CCHARS);
                              }
			     break;
                     default :  /* nach Definition eintragen */
			     specStrg(getdef(),FCTN_UNDEF);
                             break;
                    }  /* switch */
                  } /* if (special) */
                 else /* ! special : vordefiniertes als Text interpretieren */
                  { /* !!!!!!!! */
                   Eintrag(symb);
                  }
                 Zust = 0;
                 break;
            case 7: /* Stringsy */
		 if (special)  /* Klartext des Specials eintragen */
		   specStrg(scanDecode(NULL,symb),FCTN_UNDEF); 
		 else
		   sgerr(sgerrSDF);
		 Zust = 0;
                 break;
            default :
                 sgerr(sgerrSDF); /* Symboldefinition erwartet */
           }
          if (SYM(symb) != Keof) 
	    nextsym();
          break; /* Ende Zustand 3 */

        case 4 : /* SPECIAL definieren */
          switch(SYM(symb))
           {
            case 4 : /* # als Sonderzeichen interpretieren,
                          falls nicht Steueranweisung folgt */
                 if (lookahsym() == 3)  /* Steueranweisung */
                  {
                   SpecEintrag(FCTN_UNDEF);
                   Zust=0;
                   break; /* # in der Eingabe lassen */
                  }
            case 5 : /* Sonderzeichen */
                 AppendSpec(getsz()); /* an Pfad anhaengen */
                 if (lookahsym() == Keof) /* Dateiende folgt */
                  {
                   SpecEintrag(FCTN_UNDEF);
                   Zust=0;
                  }
                 else
                   Zust = 4;
                 nextsym();
                 break;
            default : /* Definition beendet */
                 SpecEintrag(FCTN_UNDEF); /* kc,rc setzen */
                 Zust = 0;
           } /* switch(SYM(symb)) */
          break; /* Ende Zustand 4 */
       } /* switch(Zust) */
    } /* while !EOF */
    if (Zust != 0) 
      sgerr(sgerrEOF); /* Ende nicht in Anfangszustand */
    if (combegsy != comendsy) 
      sgerr(sgerrCOM); /* nur gemeinsam erlaubt */
  scanClose();
 /* ================ */
 /* Code-Generierung */
 /* ================ */
  if (scanerrors + ScangenErrors) /* Fehler beim Generieren */
   {
    fprintf(stderr,"%d Fehler beim Generieren, keine Ausgaben\n",
                   (int)(scanerrors+ScangenErrors));
    exit(FEHLER);
   }
  fputs("Ausgabe des Scannerprogramms\n",stdout);
 /* ================ */
 /* Ausgabe Keywords */
 /* ================ */
  if (alt)
   {
    initfile = openaus(output_name,"init.c");
    fprintf(initfile,"/* KEYWORDS fuer Scanner %s */\n",output_name);
   }
  else
   {
    dsfile   = openaus(output_name,"");
    fputs("#include <stdio.h>\n",dsfile);
    fputs("#include \"ps_token.h\"\n",dsfile);
    fputs("#include \"ps_tab.h\"\n",dsfile);
    fputs("static Keywddef keywds[] = {\n",dsfile);
   }
  for (kw = keywords; kw != NULL; kw = kw->next)
   {
    if ( kw->issym )
     {
      if (alt)
        fprintf(initfile,"looktab(\"%s\",%ldL,%ldL,FALSE);\n",
                kw->strg,(long)kw->kc,(long)kw->rc);
      else
        fprintf(dsfile,"{\"%s\",%ldL,%ldL,%ldL},\n",
                kw->strg,(long)kw->kc,(long)kw->rc,(long)kw->ignore);
     }
   }
  if (alt)
    fclose(initfile);
  else
    fputs("{NULL,0L,0L,0L}}; /* keywds */\n",dsfile);
  /* ======== */
  /* SPECIALS */
  /* ======== */
  if (alt)
   {
    specfile    = openaus(output_name,"spec.c");
    fprintf(specfile,"/* SPECIALS Scanner %s */ \n",output_name);
    decfile     = openaus(output_name,"dec.c");
    fprintf(decfile,"/* Decoder Scanner %s */\n",output_name);
   }
  else
    fputs("static Specdef specs[] = {\n",dsfile);
  if (SpecTree!=NULL) /* Baum in Fallunterscheidungen umsetzen */
    SpecTreeP(SpecTree,1,NULL); /* erste Ebene uebergeben */
  if (alt)
   {
    fclose(specfile);
    fclose(decfile);
   }
  else
    fputs("{NULL,0L,0L,0L}}; /* specs */\n",dsfile);
  /* ========== */
  /* Headerfile */
  /* ========== */
  if (Realsy.issym && dotdot && max_look < 2)
    max_look = 2;   /* ".." voraussehen */
  if (alt)
   {
    headerfile  = openaus(output_name,".h");
    fprintf(headerfile,"/* Headerfile fuer Scanner %s */ \n",output_name);
    if (max_look > 0)
      fprintf(headerfile,"#define MAXLOOK %ldL\n",(long)max_look);
   }
  else
   {
    fputs("Pscantab scantab = {\nkeywds,specs,\n",dsfile);
    if (SpecTree != NULL)
      fputs("psScanspecials,\n",dsfile);
    else
      fputs(null_function,dsfile);
    fprintf(dsfile,"%ldL,\n",(long)max_look);
   }
  if (alt)
   {
    /* -------------------------------------------------- */
    /* #defines fuer Kommentare besetzen     		*/
    /* -------------------------------------------------- */
    if (comments || combegsy)
      fputs("#define comments\n",headerfile);
    if (mcomments) 
      fputs("#define mcomments\n",headerfile);
    if (ccomments) 
      fputs("#define ccomments\n",headerfile);
   }
  /* ----------------------------------------------------------- */
  /* #defines und Routinen fuer Zahlen, Strings und Bezeichner   */
  /* ----------------------------------------------------------- */
  if (dollar_idents)
   {
    if(alt)
      fputs("#define DOLLAR_IDENTS\n",headerfile);
    else
      fputs("1,",dsfile);
   }
  else if (!alt)
    fputs("0,",dsfile);
  if (case_sensitive)
   {
    if(alt)
      fputs("#define CASE_SENSITIVE\n",headerfile);
    else
      fputs("1,",dsfile);
   }
  else if (!alt)
    fputs("0,",dsfile);
  if (!alt)
    fprintf(dsfile,"%ldL,%ldL,%ldL,",(long)Identsy.kc,(long)Identsy.rc,  
            (long)Identsy.ignore);
  if (Identsy.issym)
   {
    if (alt)
     {
      fprintf(headerfile,"#define Kidentsy %ldL\n",(long)Identsy.kc);
      fprintf(headerfile,"#define Ridentsy %ldL\n",(long)Identsy.rc);
     }
    else
      fputs("psIdents,\n",dsfile);
   }
  else if (!alt)
   {
    if (keywords != NULL)
      fputs("psKeywds,\n",dsfile);
    else
      fputs(null_function,dsfile);
   }
  if (Stringsy.issym)
   {
    if (alt)
      fprintf(headerfile,"#define Kstringsy %ldL\n",(long)Stringsy.kc);
   }
  if (!alt)
    fprintf(dsfile,"%ldL,%ldL,",(long)Intsy.kc,(long)Intsy.ignore);
  if (Intsy.issym && alt)
      fprintf(headerfile,"#define Knumbersy %ldL\n",(long)Intsy.kc);
  if (!alt)
   {
    fprintf(dsfile,"%ldL,%ldL,",(long)Realsy.kc,(long)Realsy.ignore);
    if (Realsy.issym)
      if (Realsy.cstyle)
        fputs("psCreals,\n",dsfile);
      else
        fputs("psReals,\n",dsfile);
    else if (Intsy.issym)
      if (Intsy.cstyle)
        fputs("psCnumbers,\n",dsfile);
      else
        fputs("psNumbers,\n",dsfile);
    else
      fputs(null_function,dsfile);
    if (Intsy.issym && Realsy.issym)
      fputs("1,\n",dsfile);
    else
      fputs("0,\n",dsfile);
    if (Realsy.issym && dotdot) 
      fputs("1,\n",dsfile);
    else
      fputs("0,\n",dsfile);
    if (linedirs != NULL)
      fputs("psLinedirs\n",dsfile);
    else
      fputs(null_function,dsfile);
    fputs("}; /* scantab */\n",dsfile);
   }
  if (alt)
    fclose(headerfile);
  else
    fclose(dsfile);
  if (alt)
   { 
    FILE *programfile;

    /* -------------------- */
    /* Programfile          */
    /* -------------------- */
    programfile = openaus(output_name,".c");
    fprintf(programfile,
    "/* Haupt-Programm Scanner %s,\n   aus Scannerbeschreibung %s */\n",
     output_name,argv[1]);
    fprintf(programfile,
            "#include \"%s.h\"\n",output_name);
    fputs("#include \"scan1.c\"\n",programfile);
    fprintf(programfile,
            "#include \"%sspec.c\"\n",output_name);
    fputs("#include \"scan2.c\"\n",programfile);
    fprintf(programfile,
            "#include \"%sdec.c\"\n",output_name);
    fputs("#include \"scan3.c\"\n",programfile);
    fprintf(programfile,
            "#include \"%sinit.c\"\n",output_name);
    fputs("#include \"scan4.c\"\n",programfile);
    fclose(programfile);
   }
  if (alt)
    printf("C-Programm auf : %s.c\n",output_name);
  else
    printf("Scanner-Tabelle-Programm auf : %s\n",output_name);
  return(0);
 } /* Ende main */
  
  
