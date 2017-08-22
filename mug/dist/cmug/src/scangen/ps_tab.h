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


/* *********************************************************** */
/* ps_tab.h : Deklaration der Typen fuer die Tabelle des       */
/*            Datenstrukturgesteuerten parametrsierten Scanner */
/* erstellt  22.01.91, Ulrich Vollath                          */
/* *********************************************************** */

#ifndef PS_TAB_H
#define PS_TAB_H

typedef struct  { /* Definition eines Schluesselwortes */
		 char  *strg;  /* Klartext des Schluesselwortes   */
		 long  kc;     /* syntaktische Klasse             */
		 long  val;    /* Semantischer Wert (Relativcode) */
		 long  ign;    /* Token wird nicht gemeldet ?     */
		} Keywddef;

typedef struct  { /* Definition eines Sonderzeichentokens */
		 char  *strg;     /* Klartext des Tokens             */
		 long  kc;        /* syntaktische Klasse             */
		 long  val;       /* Semantischer Wert (Relativcode) */
		 long  ign;   	  /* Token wird nicht gemeldet ?     */
		 int  (*fctn)();  /* Special-Routine                 */
		} Specdef;

/* ---------------------------------------- */
/* Deklarationen der Bibliotheksroutinen    */
/* ---------------------------------------- */
#ifdef __STDC__
extern int  psScanspecials(Token);
extern int  psComments(Token,Specdef *);
extern int  psMcomments(Token,Specdef *);
extern int  psCcomments(Token,Specdef *);
extern int  psIdents(Token);
extern int  psKeywds(Token);
extern int  psStrings(Token,Specdef *);
extern int  psNumbers(Token);
extern int  psReals(Token);
extern int  psCstrings(Token,Specdef *);
extern int  psCnumbers(Token);
extern int  psCreals(Token);
extern int  psCchars(Token,Specdef *);
extern void psLinedirs(void);
#else
extern int  psScanspecials();
extern int  psComments();
extern int  psMcomments();
extern int  psCcomments();
extern int  psIdents();
extern int  psKeywds();
extern int  psStrings();
extern int  psNumbers();
extern int  psReals();
extern int  psCstrings();
extern int  psCnumbers();
extern int  psCreals();
extern int  psCchars();
extern void psLinedirs();
#endif

typedef struct  { /* Komplette Scannertabelle */
		 Keywddef  *keywords; /* Array der Keywords, mit 
                                        {NULL,0L,0L} abgeschlossen         */
		 Specdef   *specdefs; /* Array der Specials, mit 
                                         {NULL,0L,0L} abgeschlossen        */
		 int  (*specials)();  /* Routine fuer Specials             */
		 long max_look;       /* maximal verwendeter Lookahead     */
		 int  dollar_idents;  /* $ in Bezeichnern erlaubt          */
		 int  case_sensitive; /* Gross- und Kleinschreibung sig.   */
		 long kc_idents;      /* Klassencode fuer Bezeichner       */
		 long sv_idents;      /* semantischer Wert Bezeichner      */
		 long ign_idents;     /* ignoriere Bezeichner ?            */
		 int  (*idents)();    /* Routine fuer Bezeichner           */ 
		 long kc_numbers;     /* Klassencode fuer Zahlen           */
		 long ign_numbers;    /* ignoriere Zahlen ?                */
		 long kc_reals;       /* Klassencode fuer Real-Zahlen      */
		 long ign_reals;      /* ignoriere Reals ?                 */
		 int  (*numbers)();   /* Routine fuer Zahlen (inkl. reals) */
		 int  num_and_real;   /* Beide Klassen vorhanden           */
		 int  dotdot_fix;     /* gesonderte Behandlung von .. ?    */
		 void (*linedirs)();  /* Routine fuer #-Direktiven         */
		} Pscantab;


#endif /* PS_TAB_H */
