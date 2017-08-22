#ifndef BROWSE_TYPES_H
#define BROWSE_TYPES_H

/*
 * (c) copyright 1995 by Technische Universitaet Muenchen, Germany
 *
 *	This product is part of MUGBrowser
 *	MUGBrowser is a part of the compiler writing system
 *	MUG (Modularer Uebersetzer-Generator, TU Muenchen)
 *
 * Permission to use, duplicate or disclose this software must be
 * obtained in writing. Requests for such permissions may be sent to
 *
 *	Prof. Dr. J. Eickel
 *	Institut fuer Informatik
 *	Technische Universitaet Muenchen
 *	D-80290 Muenchen
 *	Germany
 *
 * No version of this implementation may be used or distributed for gain,
 * all listings must contain our copyright notice, and the headings
 * produced by MUG-Modules must contain the text "MUG" and "TU - Muenchen".
 */

/************************************************************************/
/* InputList								*/
/* 									*/
/* enthaelt die Verbindungen von einem Attribut zu einem anderen (bei	*/
/* Zuweisungen) bzw. zu einer semantischen Aktion (als Parameter)	*/
/************************************************************************/
typedef struct InputList_Elem
	{
	struct InputList_Elem *prev;
	struct InputList_Elem *next;

	/* aktion und attr schliessen sich wechselseitig aus, d.h.	*/
	/* es ist immer genau eines gleich NULL.			*/
	struct SemList_Elem *aktion;
	struct AList_Elem *attr;
	} ILE, *ILEP;

typedef struct InputList
	{
	int anzahl;
	ILEP first;
	ILEP last;
	} InputList;


/************************************************************************/
/* AList (Attribut-Liste)						*/
/* 									*/
/* enthaelt alle Informationen zu einem Attribut			*/
/************************************************************************/
typedef struct AList_Elem
	{
	struct AList_Elem *prev;
	struct AList_Elem *next;

	char attr[L_ATTRIBUT];
	int x;					/* linke obere Ecke	*/
	int y;
	int image;
	char art;				/* 'I', 'D', 'A'	*/
	char typ[L_ATTR_TYP];			/* C-Typ, z.B. "int"	*/

	int wertlen;		/* Laenge des Wertebereichs in Bytes	*/
	char *wert;		/* Zeiger auf den Wertebereich		*/

	/* Wie wird das Attribut berechnet?				*/
	/* copy_of und result_of schliessen sich wechselseitig aus,	*/
	/* d.h. es ist immer genau eines gleich NULL.			*/
	struct ArguList_Elem *copy_of;
	struct SemList_Elem *result_of;	

	InputList input_to;	/* Wo wird das Attribut verwendet?	*/

	struct Tree_Elem *node;	/* Knoten, zu dem das Attribut gehoert */
	} ALE, *ALEP;

typedef struct AList
	{
	int anzahl;
	ALEP first;
	ALEP last;
	} AList;


/************************************************************************/
/* NameList								*/
/* 									*/
/* enthaelt die Ergebnisse einer sem. Aktion mit Namen und Knoten	*/
/* noetig zur Unterscheidung mehrfach vorkommender sem. Aktionen	*/
/************************************************************************/
typedef struct NameList_Elem
	{
	struct NameList_Elem *prev;
	struct NameList_Elem *next;

	char symbol[L_SYMBOL];				/* Knoten	*/
	int id;			/* Id des Knotens, von MUG uebernommen	*/
	char attr[L_ATTRIBUT];				/* Attribut	*/
	} NLE, *NLEP;

typedef struct NameList
	{
	int anzahl;
	NLEP first;
	NLEP last;
	} NameList;


/************************************************************************/
/* ArguList (Argument-Liste)						*/
/* 									*/
/* enthaelt Information ueber Argumente (Attribute oder Terminals)	*/
/************************************************************************/
typedef struct ArguList_Elem
	{
	struct ArguList_Elem *prev;
	struct ArguList_Elem *next;

	/* terminal und attr schliessen sich wechselseitig aus, d.h.	*/
	/* es ist immer genau eines gleich NULL.			*/
	ALEP attr;
	struct Tree_Elem *terminal;
	} ArgLE, *ArgLEP;

typedef struct ArguList
	{
	int anzahl;
	ArgLEP first;
	ArgLEP last;
	} ArguList;


/************************************************************************/
/* SemList (Liste semantischer Aktionen)				*/
/* 									*/
/* enthaelt alle Informationen zu einer semantischen Aktion		*/
/************************************************************************/
typedef struct SemList_Elem
	{
	struct SemList_Elem *prev;
	struct SemList_Elem *next;

	char aktion[L_SEMACTION];
	int x;				/* Mittelpunkt der x-Werte	*/
	int y;				/* obere Grenze			*/
	int x_min;			/* linke Grenze			*/
	int x_max;			/* rechte Grenze		*/
	int id;
	ArguList argumente;
	ArguList results;
	NameList result_name;		/* Zur Unterscheidung 		*/
	} SemLE, *SemLEP;

typedef struct SemList
	{
	int anzahl;
	SemLEP first;
	SemLEP last;
	} SemList;


/************************************************************************/
/* TEPList (Baumelement-Liste)						*/
/* 									*/
/* enthaelt die Soehne in Form von Zeigern auf Baumelemente		*/
/************************************************************************/
typedef struct TEPList_Elem
	{
	struct TEPList_Elem *prev;
	struct TEPList_Elem *next;

	struct Tree_Elem *symbol;		/* Knoten oder Blatt	*/
	} TEPLE, *TEPLEP;

typedef struct TEPList
	{
	int anzahl;
	TEPLEP first;
	TEPLEP last;
	} TEPList;


/************************************************************************/
/* Baumelement								*/
/* 									*/
/* enthaelt alle Informationen zu einem Knoten oder Blatt im Baum	*/
/************************************************************************/
typedef struct Tree_Elem
	{
	char symbol[L_SYMBOL];
	int x;						/* Mittelpunkt	*/
	int y;						/* obere Grenze	*/
	int breite_rechts;		/* Platzbedarf incl. Attribute	*/
	int breite_links;		/* Platzbedarf incl. Attribute	*/
	int baumhoehe;		/* Baumhoehe unterhalb des Knotens	*/
	int vater_id;	/* Verschiedene Id's, da von MUG uebernommen	*/
	int sohn_id;
	int is_terminal;				/* boolesch	*/
	struct Tree_Elem *vater;
	TEPList soehne;
	TEPLEP elem_of;	/* Zeiger auf Listenelement, zu dem es gehoert	*/
	AList iattr;				/* inherited Attribute	*/
	AList dattr;				/* derived Attribute	*/
	AList aattr;				/* Auxiliaries		*/
	SemList aktionen;		/* alle Aktionen der Produktion	*/
	InputList input_to;			/* nur fuer Terminals	*/
	} TE, *TEP, Tree;


/************************************************************************/
/* ANList (Attributname-Liste)						*/
/* 									*/
/* enthaelt die Zuordnung von Images zu Attributen 			*/
/************************************************************************/
typedef struct Attrnamen_elem
	{
	struct Attrnamen_elem *next;

	char attr[L_ATTRIBUT];
	char prefix[4];					/* prefixes */
	int nr;						/* Image-Nummer	*/
	} ANLE, *ANLEP;

typedef struct ANList
	{
	int anzahl;
	ANLEP first;
	}ANList;


/************************************************************************/
/* x_list								*/
/* 									*/
/* enthaelt ALLE Elemente des Baums (also Knoten, Blaetter, Attribute	*/
/* und semantische Aktionen) nach x-Koordinaten geordnet.		*/
/* Auf dieser Datenstruktur setzt das Backend auf!			*/
/************************************************************************/
typedef struct x_list_elem
	{
	struct x_list_elem *next_min;		/* Aufsteigend sortiert	*/
	struct x_list_elem *next_max;		/* Aufsteigend sortiert	*/

	int x_min;			/* Beschreibung der 4 Ecken	*/
	int y_min;
	int x_max;
	int y_max;
	char art;				/* 'A', 'T', 'S'	*/
	union xunion
		{
		TEP t_element;			/* Knoten und Blaetter	*/
		ALEP a_element;			/* Attribute		*/
		SemLEP s_element;		/* sem. Aktionen	*/
		} info;
	} XLE, *XLEP;

typedef struct x_list
	{
	int anzahl;
	XLEP first_min;
	XLEP first_max;
	} x_list;

#endif
