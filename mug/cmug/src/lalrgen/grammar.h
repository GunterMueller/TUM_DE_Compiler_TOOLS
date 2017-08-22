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
/* Grammar.h   :                                                          */
/* LR(k)-Parser-Generator                                                 */
/* Definition der Datenstruktur fuer die Grammatik und                    */
/* der Zugriffsmakros darauf                                              */
/* Aenderung        : 16.11.89 ITEMGEM                                    */
/* Aenderung        : 28.10.89 PREVITEM,NNEXTITEM                         */ 
/* Aenderung        : 12.08.89 PS_REDUCE                                  */ 
/* Aenderung        : 02.07.89 detailliertere Informationen zu nonts      */
/* Aenderung        : 25.5.89  Zustandsliste zu jedem Item                */
/* Aenderung        : 7.3.89   Ueberwachungen zur Laufzeit                */
/* Aenderung        : 26.2.89  Einfuehrung von UNDEFSYM                   */
/* erstellt         : 24.1.89                                             */
/* ********************************************************************** */

#ifndef GRAMMAR_H
#define GRAMMAR_H

#include "gramconst.h"         /* maximale Wertebereiche          */

/* ============================================================ */
/* Definitionen der Datentypen fuer Grammatiken                 */
/* ACHTUNG : die Typen muessen mit den angegebenen Bereichen    */
/* kompatibel sein                                              */
/* ============================================================ */

typedef short Term; /* Typ fuer Terminalsymbole, Bereich CMINT .. CMAXT    */
typedef short Nont; /* Typ fuer Nonterminalsymbole, Bereich CMINN .. CMAXN */
typedef short Symb; /* Typ fuer Symbole, Bereich  Term + Nont              */

typedef short Item; /* Typ fuer Position in der Grammatik CMINI .. CMAXI   */
typedef short Prod; /* Typ fuer Produktionen, Bereich CMINP ..CMAXP       */

typedef Prod  Altset;  /* Zeiger auf erste Produktion der Alternativen     */
typedef short Plength; /* Laenge  einer Produktion, Groessenordnung Item   */

typedef short Nontstat;/* Status eines Nonterminals, Werte folgen          */
/* Nontstat : Nonterminal ist epsilonerzeugend       */
#define NS_EPSERZ 1

/* Nontstat : Nonterminal leitet terminale Zeichenreihe ab */
#define NS_TERMERZ 2

/* Nontstat : Nonterminal wird benoetigt             */
#define NS_BENUTZT 4

typedef short Prodstat;/* Status einer Produktion, Werte folgen            */
/* Prodstat : Produktion ist epsilonerzeugend       */
#define PS_EPSERZ 1

/* Prodstat : Produktion ist nicht epsilonerzeugend */
#define PS_NEPSERZ 2

/* Prodstat : Produktion wird benoetigt             */
#define PS_BENUTZT 4

/* Prodstat : Produktion leitet terminale Zeichenreihe ab */
#define PS_TERMERZ 8

/* Prodstat : Produktion wird mind. einmal reduziert      */
#define PS_REDUCE 16

typedef struct {  /* Beschreibung eines Nonterminals */
                Prod alts;   /* erste Alternative zu diesesm Nonterminal */
		Nontstat st; /* Status des Nonterminals                  */
               } Nelem;

typedef struct { /* Beschreibung Element einer rechten Seite */
                Plength len; /* Restlaenge der Produktion */
                Symb    sym; /* Symbolnummer des Elements */
                char   *zl;  /* Liste der Zustaende, in denen dieses Item
                                als erstes vorkommt                           */
                char ak_gem; /* Aktionskonflikt hier schon gemeldet           */
               } Helem;

typedef struct { /* Beschreibung einer Produktion            */
                Item lhs;    /* linke Seite der Produktion                    */
                Prod next;   /* naechste Produktion zur gleichen linken Seite */
                             /* UNDEFPROD, falls keine naechste Produktion    */
                Prodstat st; /* Status der Produktion                         */
               } Pelem;

typedef struct {  /* gesamte Grammatik */
           Term  maxt;     /* groesstes benutztes Terminalsymbol              */
           Nont  maxn;     /* groesstes Nonterminalsymbol                     */
           Nont  ax;       /* Axiom der Grammatik                             */
           Nont  aax;      /* Axiom der augmentierten Grammatik               */
           Term  augt;     /* Randzeichen in der augmentierten Grammatik      */
           Item  maxh;     /* letzte Position in der Grammatik                */
           Item  augp;     /* Metaproduktion in der augmentierten Grammatik   */
           Prod  maxp;     /* letzte Produktion                               */
           Nelem *nonts;   /* Array Beschreibungen der Nonterminalzeichen     */
           Helem *items;   /* Array aller Items der Produktionen              */
           Pelem *prods;   /* Produktionen der Grammatik                      */
           char **tnames;  /* Externdarstellungen der Terminalzeichen         */
           char **nnames;  /* Externdarstellungen der Nonterminalzeichen      */
               } Grammar ;
extern Grammar g;           /* bearbeitete Grammatik                         */
/* ========================================================================== */
/* Zugriffsmakros                                                             */
/* ========================================================================== */

#define MINT       CMINT  /* kleinstes benutztes Terminalsymbol              */
#define MAXT       g.maxt /* groesstes benutztes Terminalsymbol              */
#define MINN       CMINN  /* kleinstes Nonterminalsymbol                     */
#define MAXN       g.maxn /* groesstes Nonterminalsymbol                     */
#define AXIOM      g.ax   /* Axiom der Grammatik                             */
#define METAAXIOM  g.aax  /* Axiom der augmentierten Grammatik               */
#define RANDZCH    g.augt /* Randzeichen in der augmentierten Grammatik      */
#define MINH       CMINH  /* erste Position in der Grammatik                 */
#define MAXH       g.maxh /* letzte Position in der Grammatik                */
#define METAPROD   g.augp /* Metaproduktion in der augmentierten Grammatik   */
#define MINP       CMINP  /* erste Produktion                                */
#define MAXP       g.maxp /* letzte Produktion                               */
#define UNDEFPROD  (Prod)(MAXP+1)  /* Kennung fuer undefinierte Produktion   */
#define UNDEFITEM  (Item)(MAXH+1)  /* Kennung fuer undefiniertes Item        */
#define UNDEFSYM   (Symb)(MAXT+1)  /* Kennung fuer ubdefiniertes Symbol      */

 /* erste Produktion zu n             */
#define FIRSTPROD(n) g.nonts[(n)-MINN].alts  

 /* Information, ob Nonterminal n epsilonerzeugend */
#define ISEPS(n) (g.nonts[(n)-MINN].st & NS_EPSERZ)  

 /* Restlaenge zu Item i              */
#define ITEMLEN(i) g.items[(i)-MINH].len

 /* AKtionskonflikt in diesem Item gemeldet */
#define ITEMGEM(i) g.items[(i)-MINH].ak_gem

 /* Nachfolger des Items i            */
#define NEXTITEM(i) (Item)((i)+1)

 /* n-ter Nachfolger des Items i      */
#define NNEXTITEM(i,n) (Item)((i)+(n))

 /* Vorgaenger des Items i            */
#define PREVITEM(i) (Item)((i)-1)

 /* Liste der Zustaende, die mit Item i beginnen  */
#define ZUSTLIST(i) g.items[(i)-MINH].zl

 /* Symbol des Items i                */
#define ITEMSYM(i) g.items[(i)-MINH].sym

 /* Externdarstellung des Terminalsymbols s   */
#define TERMNAME(s) g.tnames[(s)-MINT]

 /* Externdarstellung des Nonterminalsymbols s   */
#define NONTNAME(s) g.nnames[(s)-MINN]

 /* Statusinformation des Nonterminalsymbols s   */
#define NONTSTAT(n) g.nonts[(n)-MINN].st

 /* naechste Produktion mit gleicher linker Seite wie p */
#define NEXTPROD(p) g.prods[(p)-MINP].next

 /* Item linke Seite der Produktion p            */
#define LHS(p) g.prods[(p)-MINP].lhs

 /* Status der Produktion p */
#define PRODSTAT(p) g.prods[(p)-MINP].st

/*====================================================================== */
/* Diskriminierungsmakros                                                 */
/*====================================================================== */

/* Symbol s ist Terminalzeichen ?          */
#define ISTERM(s) ((s) >= MINT && (s) <= MAXT)

/* Symbol s ist Nonterminalzeichen ?       */
#define ISNONT(s) ((s) >= MINN && (s) <= MAXN)

/* Symbol s ist Aktions-Nonterminal ?      */
#define ISACTION(a) ((a) >= MINN && (a) < AXIOM)

/* Item i ist definiert ?                  */
#define ISITEM(i) ((i) >= MINH && (i) <= MAXH)

/* Produktion p ist definiert ?            */
#define ISPROD(p) ((p) >= MINP && (p) <= MAXP)


/*====================================================================== */
/* Makros fuer Datenstrukturgesteuerte Ablaufkonstrukte                   */
/*====================================================================== */

 /* Schleife ueber alle Terminalzeichen t     */
#define FOREACHTERM(t) for (t=MINT; t<=MAXT; t++)

 /* Schleife ueber alle Nonterminalzeichen n  */
#define FOREACHNONT(n) for (n=MINN; n<=MAXN; n++)

 /* Schleife ueber alle Produktionen p        */
#define FOREACHPROD(p) for (p=MINP; p<=MAXP; p++)

 /* Schleife ueber alle Items i        */
#define FOREACHITEM(p) for (i=MINH; i<=MAXH; i++)

 /* Schleife ueber alle Produktionen p zu einem Nonterminal n */
#define FOREACHPRODTO(n,p) CHECKBED(ISNONT(n));\
                           for (p=FIRSTPROD(n);p!=UNDEFPROD;p=NEXTPROD(p))

/*====================================================================== */
/* Funktionsdeklarationen                                                 */
/*====================================================================== */

/*====================================================================== */
/* Zugriff auf linke Seite der Produktion, zu der das Item item gehoert   */
/* Produktionsanfaenge sind dadurch gekennzeichnet, dass das              */
/* Vorgaengeritem (falls vorhanden) die Laenge 0 traegt                   */
/*====================================================================== */
#ifdef __STDC__
Item lhsItem(Item);
#else
Item lhsItem();
#endif
/*====================================================================== */
/* Berechnen der Nummer der Produktion, zu der das Item item gehoert      */
/*====================================================================== */
#ifdef __STDC__
Prod prodNr(Item);
#else
Prod prodNr();
#endif
/*====================================================================== */
/* Platzreservierung fuer Grammatik-Datenstruktur                         */
/* Initialisierung der Grammatik-Datenstruktur                            */
/* Bereiche, Zeiger etc.                                                  */
/*====================================================================== */
#ifdef __STDC__
BOOL initGrammar(Term,Nont,Item,Item);
#else
BOOL initGrammar();
#endif

#endif /* GRAMMAR_H */

