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

/******************************************************************************

*		 Datenstrukturen fuer Internform des AG-Einlesers
*
* 07.12.88  fz, js  angelegt
* 12.12.88  fz	    Aenderungen der Namen, Ergaenzungen
* 14.12.88  fz, js  Ergaenzungen
* 04.01.89  js	    Verbesserungen, Ergaenzungen
* 05.01.89  fz, js  Verbesserungen, Ergaenzungen
* 11.01.89  fz, js  Verbesserungen
* 25.01.89  fz, js  Verbesserungen
* 14.03.89  fz	    Ergaenzungen
* 06.07.89  letzte Aenderung
******************************************************************************/

typedef char *identifier;	/* Name eines Hasthtabeintrags */

	/* Datentypen des MUG-Systems */

typedef char filestring[129];

#include "ps_token.h"
typedef Token ident;
typedef int number;
typedef char *string;
	/* Enumeration - Definitionen */
#ifndef FALSE
#define FALSE ((int)0)
#endif
#ifndef TRUE
#define TRUE ((int)1)
#endif

#ifndef BOOL_T
#define BOOL_T
typedef int bool;
#endif

typedef enum {
	GRAM, TERM, NONTERM, FUNCT, SFUNCT, ATTRIBUT, PRODUCT, TYP
} symbolclass;
				/* Typ eines Identifikators
				   GRAM     Bezeichner fuer Grammatikphasen
				   VOCABEL  Terminal- und Nonterminalsymbole
				   FUNCT    Semantische Funktion
				   SFUNCT   Syntaktische Funktion
				   ATTRIBUT Attribut
				   PRODUCT  Produktion
				   TYP	    Datentyp (z.B. fuer Attribut... */
typedef enum {INHERITED, SYNTHESIZED, SEMTERM, AUXILIARY} attrkenn;
				/* INHERITED Normales, ererbtes Attribut
				   SYNTHESIZED Normales Attribut von unten
				   SEMTERM semantisch relevantes SYNTHESIZED
					   Terminal
				   AUXILIARY Auxiliary-Attribut */
typedef enum {CTYP, SEMTYP, SYNTYP} typkenn;
				/* SEMTYP Semantisch relev. Terminalsymbol
				   SYNTYP Arg. oder Erg. von synt.  Funktionen
				   CTYP   normaler C-Datentyp */
typedef enum {LINKS, RECHTS, NOURSPRUNG} urspruenge;
				/* Gibt an, auf welcher
				   Seite ein Attribut auftritt */

	/* ArrayIndex - Datentypen */
		/* Haupt-Arrays */
#ifndef INDEX_T
#define INDEX_T
typedef int Index;
#endif

#define NIL 0
				/* Index = NIL => Element nicht vorhanden */

#ifndef ENTRYINDEX_T
#define ENTRYINDEX_T
typedef Index entryIndex;	/* Index in Tabelle mit Identifikatoren */
#endif

typedef Index vocabelIndex;	/* virtueller Index fuer Vokabeln */

typedef Index nontermIndex;	/* Index in Tabelle mit Nonterminals */

typedef Index termIndex;	/* Index in Tabelle mit Terminals */

typedef Index functIndex;	/* Index in Tabelle mit Funktionen */

typedef Index sfunctIndex;	/* Index in Tabelle mit Funktionen */

typedef Index attrIndex;	/* Index in Tabelle mit Attributen */

typedef Index productIndex;	/*   -"-  Produktionen */

typedef Index typIndex; 	/* Index in Tabelle mit Typen */

		/* Unter-Arrays fuer Produktionen, sem.Regeln */

typedef Index prodposIndex;	/*   -"-  Produktionspositionen */

typedef Index attrposIndex;	/*   -"-  Attributpositionen */

typedef Index aufrufIndex;	/*   -"-  Funktionsaufrufe */

typedef Index aparamIndex;	/*   -"-  Globale Liste fuer aktuelle Par. */

typedef Index fparamIndex;	/*   -"-  Globale Liste fuer formale Par. */

	/* Anzahl - Datentypen */

typedef Index anzahl;	/* gleicher Typ wie Indexe */

typedef anzahl entryAnz;	/* Anzahl der Identifikatoren */

typedef anzahl attributAnz;	/* Anzahl der Attribute */

typedef anzahl termAnz; 	/* Anzahl der Terminale */

typedef anzahl nontermAnz;	/* Anzahl der Nonterminale */

typedef anzahl vocabelAnz;	/* Anzahl der Vokabeln */

typedef anzahl productAnz;	/* Anzahl der Produktionen */

typedef anzahl typAnz;		/* Anzahl der Typen */

typedef anzahl functAnz;	/* Anzahl der Funktionen */

typedef anzahl aparamAnz;	/* Anzahl der aktuellen Parameter */

typedef anzahl fparamAnz;	/* Anzahl der formalen Parameter */

typedef anzahl attrposAnz;	/* Anzahl der Attribute einer Produktion */

typedef anzahl aufrufAnz;	/* Anzahl der Aufrufe im System */

typedef anzahl prodposAnz;	/* Laenge einer Produktion == Anzahl der
				   Positionen einer Produktion */

typedef struct {		/* Struktur fuer Attributpositionen */
	attrIndex	attr;	/* Index zu Attribut */
	prodposIndex	prodpos;
				/* Index zu Produktionsposition */
	aufrufIndex	aufruf; /* Index zu Aufruf; eigentl. ueberfluessig, da
				   ueber prodpos und product in Aufrufliste
				   bis Uebereinstimmung der attrpos gesucht
				   werden koennte */
	/* prodpos und aufruf werden nicht durch die Einlesefunktionen
	   besetzt, sondern von den Initialisierungsfunktionen abhaengig von
	   den jeweiligen aktuellen Parametern */
	bool		ende;	/* relativ zu prodpos */
} attrpos;

typedef struct {		/* Struktur fuer Produktionspositionen */
	int		num;	/* Numerierung innerhalb einer Produktion */
	int		pos;	/* Positionsnummer fuer Mehrfachauftreten
				   einer Vocabel in einer Produktion */
	vocabelIndex	vocabel;
				/* Index zu Vokabel an dieser Position */
	productIndex	product;
				/* Index zu zugehoeriger Produktion
				   == Rueckverweis */
	attrposIndex	firstattrpos;
				/* Index zu erster Attributposition */
	prodposIndex	nextoccur;
				/* Index zu naechstem Auftreten der Vokabel */
	bool		ende;	/* relativ zu product */
} prodpos;

typedef prodpos *prodposArray;	/* Array fuer Produktionspositionen */

typedef attrpos *attrposArray;	/* Array fuer Attributpositionen */

typedef struct {		/* Struktur fuer Aufrufe */
	functIndex	funct;	/* Index zu betreffender Funktion */
	aparamIndex	firstarg;
				/* Index zu erstem Argument */
	aparamIndex	firsterg;
				/* Index zu erstem Ergebnisparameter */
	bool		ende;	/* eigentl. ueberfluessig (siehe Bem. zu
				   firstaufruf in Struktur product) */
} aufruf;

typedef aufruf *aufrufArray;	/* Array fuer Aufrufe */

typedef struct {		/* Struktur fuer aktuelle Parameter */
	attrposIndex	aktparam;
				/* Index zu Attributposition */
	bool		ende;	/* ende == TRUE => Ende der Parameter
				   erreicht */
} aparam;  /* aktueller Parameter */

typedef struct {		/* Struktur fuer formale Parameter */
	typIndex	typ;	/* Index zu Typ */
	bool		ende;
} fparam;  /* formaler Parameter */

typedef aparam *aparamArray;	/* Array fuer aktuelle Parameter */

typedef fparam *fparamArray;	/* Array fuer formale Paramter */

typedef struct {		/* Struktur fuer Hashtabelleneintrag */
	identifier	name;	/* Bezeichner; wird spaeter Relativcode */
	entryIndex	otherclass;
				/* Kollisionsaufloesung: Index zu Eintrag
				   einer anderen Klasse */
	symbolclass	class;	/* Symbolklasse des Bezeichners */
	union { 		/* Union fuer verschiedene Indices je nach
				   Symbolklasse */
		termIndex	term;
				/* Index zu Terminalsymbolen */
		nontermIndex	nonterm;
				/* Index zu Nonterminalsymbolen */
		functIndex	funct;
				/* Index zu Funktionen */
		attrIndex	attribut;
				/* Index zu Attributen */
		typIndex	typ;
				/* Index zu Typen */
		productIndex	product;
				/* Index zu Produktionen */
	} index;
} entry;

typedef struct {		/* Struktur fuer Produktionen */
	entryIndex	prodname;
				/* Index zu Produktionsnamen */
	prodposIndex	firstprodpos;
				/* Index zu erster Produktionsposition =
				   linke Seite */
	aufrufIndex	firstaufruf;
				/* Index zu erstem Funktionsaufruf
				   (einschliesslich der einfachen Zuweisung);
				   eigentl. fuer Schnittstelle nicht noetig */
	attrposIndex	firstauxattrpos;
				/* Index zu erster Auxiliaryposition */
	productIndex	nextprod;
				/* Index zu naechst. Prod. mit der gleichen
				   linken Seite */
} product;

typedef product *productArray;	/* Array fuer Produktionen */


typedef entry *entryArray;	/* Array fuer Tabelleneintraege */

typedef struct {		/* Struktur fuer Vokabeln */
	entryIndex	name;	/* Index zu Tabelleneintrag */
	bool		issemantic;
				/* Ist Terminal semantisch relevant ? */
	attrIndex	attr;	/* Attribut fuer semantisch rel. Terminals */
} terminal;

typedef struct {
	entryIndex	name;	/* Index zu Hashtabelleneintrag */
	attrIndex	firstattr;
				/* Index zu erster Attributposition */
	productIndex	firstproduct;
				/* Index zu erster Produktion */
	prodposIndex	firstoccurence;
				/* Index zum ersten Auftreten in einer
				   Produktion des Nonterminals */
} nonterminal;

typedef terminal *termArray;	/* Array fuer Vokabeln */

typedef nonterminal *nontermArray;
				/* Array fuer Vokabeln */

typedef struct {		/* Struktur fuer Funktionen */
	entryIndex	name;	/* Index zu Hashtabelleneintrag */
	bool		iscopy; /* es handelt sich um eine einfache Zuweisung */
	fparamIndex	firstarg;
				/* Index zu erstem Argument */
	fparamIndex	firsterg;
				/* Index zu erstem Ergebnisparameter */
} funct;

typedef funct *functArray;	/* Array fuer Funktionen */

typedef struct {		/* Struktur fuer Attribute */
	entryIndex	name;	/* Index zu Tabelleneintrag */
	vocabelIndex	voc;	/* Index der zugehoerigen Vokabel */
	attrkenn	akenn;	/* Richtung und Art des Attributs */
	typIndex	typ;	/* Index zu Typ */
	bool		ende;	/* ende == TRUE => Ende der Attribute
				   erreicht; relativ zu Nonterminalen */
} attribut;

typedef attribut *attributArray;
				/* Array fuer Attribute */

typedef struct {		/* Struktur fuer Typen */
	entryIndex	name;	/* Index zu Tabelleneintrag */
	typkenn 	tkenn;	/* Typkennung */
} typ;

typedef typ *typArray;		/* Array fuer Typen */

typedef entryIndex *relcodeArray;

typedef struct {		/* Struktur fuer Grammatiken */
		/* Namen */
	entryIndex	phasenid;
				/* Phasenname */
	entryIndex	ingname;
				/* Name der Eingabegrammatik */
	entryIndex	outgname;
				/* Name der Ausgabegrammatik */
		/* Indexe */
	nontermIndex	axiom;	/* Axiom */
	functIndex	firstfunct;
				/* Erste semantische Funktion */
		/* Anzahl */
	entryAnz	anzentries;
	termAnz 	anzterm;
	nontermAnz	anznonterm;
				/* Anzahl der Vokabeln */
	functAnz	anzfunct;
				/* Anzahl der Funktionen */
	attributAnz	anzattr;
				/* Anzahl der Attribute */
	productAnz	anzprod;
				/* Anzahl der Produktionen */
	typAnz		anztyp; /* Anzahl der Typen */
	prodposAnz	anzprodpos;
				/* Anzahl der Produktionspositionen */
	attrposAnz	anzattrpos;
				/* Anzahl der Attributpositionen */
	aufrufAnz	anzaufruf;
				/* Anzahl der Aufrufe */
	aparamAnz	anzaparam;
				/* Anzahl der aktuellen Parameter */
	fparamIndex	anzfparam;
				/* Anzahl der formalen Parameter */
		/* Tabellen */
	relcodeArray	relcodetab;
				/* Abbildung relcodes -> entries */
	entryArray	entrytab;
				/* Tabelle der Objekte */
	termArray	termtab;
				/* Terminaltabelle */
	nontermArray	nontermtab;
				/* Nonterminaltabelle */
	functArray	functtab;
				/* Funktionstabelle */
	attributArray	attrtab;
				/* Attributtabelle */
	productArray	prodtab;
				/* Produktionstabelle */
	typArray	typtab; /* Typtabelle */
	prodposArray	prodpostab;
				/* Produktionspositionstabelle */
	attrposArray	attrpostab;
				/* Attributpositionstabelle */
	aufrufArray	aufruftab;
				/* Aufruftabelle */
	fparamArray	fparamtab;
				/* formale Parametertabelle */
	aparamArray	aparamtab;
				/* aktuelle Parametertabelle */
} grammar, *gramptr;
