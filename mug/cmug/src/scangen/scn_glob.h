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


/* ************************************************************** */
/* scn_glob.h: globale Vereinbarungen Scanner-Bibliothek          */
/* erstellt  23.01.91, Ulrich Vollath                             */
/* ************************************************************** */
#ifndef SCN_GLOB_H
#define SCN_GLOB_H

#ifndef NO_FAST_SCAN
#define FAST_SCAN
#endif

#ifndef EXTERN
#define EXTERN extern /* in diesem Fall nur Zugriffe erzeugen */
#endif

#define EXIT  exit (25)
#define IDLEN  64    /* maximale signifikante Laenge Identifier */
#define REALLEN 64   /* maximale signifikante Laenge Realzahlen */
#define STRLEN 1024  /* maximale Laenge Strings                 */

/* Anfaenge von und Zeichen in Bezeichnern */
#define IS_IDENT_BEGIN(c) (isalpha((c)) || (c) == '_' || \
                          scantab.dollar_idents && (c) == '$')
#define IS_IDENT_CHAR(c) (isalpha((c)) || isdigit((c)) || (c) == '_' || \
                          scantab.dollar_idents && (c) == '$')
#define IS_NUMBER_BEGIN(c,c1) (isdigit((c)) || \
                          (c) == '.' && isdigit((c1)) )
#define IS_WHITE_SPACE(c) isspace(c)
/* ----------------------------- */
/* Fehlermeldungen des Scanners  */
/* ----------------------------- */
#define serrEOF "Versuch, nach Dateiende zu lesen\n"
#define serrUNG "ungueltiges Eingabezeichen\n"
/*#ifdef Kstringsy
#define serrITV "zu viele Identifikatoren oder Strings\n"
#else*/
#define serrITV "zu viele Identifikatoren\n"
/*#endif*/
#define serrCOM "offener Kommentar am Dateiende\n"
#define serrSTO "offener String an Dateiende\n"
#define serrSTL "String zu lang, gekuerzt\n"
#define serrKWD "unbekanntes Schluesselwort\n"
#define serrNUM "Integer zu gross\n"

extern Pscantab scantab;  /* vom Compiler dazugelinkt           */

#define Keof   0  /* Klassencode fuer Dateiende */

#ifndef TRUE
#define TRUE   1
#endif
#ifndef FALSE
#define FALSE  0
#endif

#ifdef FAST_SCAN
#define EndeEin ( ps_file_ptr >= ps_file_len )
#else /* FAST_SCAN */
#define LEIN   150        /* maximale Laenge Eingabezeile        */
#define EndeEin ( feof(ps_scanein) && (ps_lein<1) )
#endif /* FAST_SCAN */

#define MAXINT LONG_MAX /* 32 bit: 2147483647, groesste darstellbare Zahl */

/* Variable */
#ifndef FAST_SCAN
EXTERN FILE *ps_scanein; /* Eingabefile fuer Scanner */
#endif
EXTERN long scanerrors;  /* neue Schnittstelle !, exportiert                 */

#ifdef FAST_SCAN
EXTERN char *ps_file_buffer;     /* Eingabepuffer                       */
EXTERN long ps_file_len;         /* Laenge der Eingabedatei             */
EXTERN long ps_file_ptr;         /* Zeiger auf aktuelles Zeichen        */
#else /* FAST_SCAN */
EXTERN char ps_einz[LEIN+1];     /* Eingabepuffer                       */
EXTERN int  ps_lein;             /* momentane Laenge Eingabepuffer      */
#endif /* FAST_SCAN */

EXTERN Quellort ps_quellref;     /* Quellreferenz                       */
EXTERN Quellort ps_errref;       /* Quellreferenz fuer Fehlermeldungen  */
EXTERN int  ps_endeeingem;       /* Flag, of Keof-Symbol gemeldet       */
EXTERN char ps_ezchn;            /* aktuelles Eingabezeichen            */
EXTERN long ps_nextid;           /* naechste vergebene Idnummer         */
EXTERN long ps_nextstr;          /* naechste vergebene Stringnummer     */
EXTERN long ps_nextreal;         /* naechste vergebene Realnummer     */
EXTERN long ps_maxspec;          /* groesster Index in Specialtab       */

typedef struct HashR *Hash;
typedef struct HashR {
		      Hash next;    /* naechster in Kollisionsklasse      */
		      char *strg;   /* zugehoeriges Token                 */
                      long kcode;   /* Klassencode bei Schluesselwoertern */
                      long rcode;   /* Relativcode bei Schluesselwoertern */
		      int  iskwd;   /* TRUE, falls Schluesselwort         */
		      int  ign;     /* TRUE, falls Schluesselwort ignor.  */
		      char *semptr; /* Semantikzeiger                     */
		     } HashRec;

/* --------------------------------------------- */
/* innerhalb der Bibliothek verwendete Routinen  */
/* --------------------------------------------- */
#ifdef __STDC__
/* extern void psNextz(void); */
extern void psLiesn(void);
extern void psSkipein(long);
extern char psScanlah(long);
extern void psScanerror(char *);
extern Hash psEnterhashtab(Token,char *,long,long,long,long *,int,int,int);
/* extern void psInithash(void); */
/* extern void psInitspecials(void); */
/* extern void psInitkeywords(void); */
#else
extern void psNextz();
extern void psLiesn();
extern void psSkipein();
extern char psScanlah();
extern void psScanerror();
extern Hash psEnterhashtab();
extern void psInithash();
extern void psInitspecials();
extern void psInitkeywords();
#endif

#endif /* SCN_GLOB_H */
