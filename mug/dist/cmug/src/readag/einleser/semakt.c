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
*
*	Semantische Funktionen fuer den AG-Einleser
*
* 25.01.89  fz, js  angelegt
* 19.04.89  fz      dynamische Speicherverwaltung ergaenzt
* 29.06.89  fz      Fehlerbehandlung verbessert
* 21.11.89  oliver  EnterSemTerm: semantisches relevantes Terminal
*                   bekommt als Typ sich selbst zugewiesen und NICHT integer ! 
*                   Wichtig fuer Attributberechnung 
* 06.06.91  lahner  Durchnummerierung der Nonterminals und der Produktionen
*                   in Quellreihenfolge. Dadurch identisch zur Pascalversion.
* 17.06.91  wittner Ueberpruefung semantischer Aktionen auf Vollstaendigkeit
		    auch fuer Auxiliaries (chk_completeness)
*****************************************************************************/

/***** Bei Verwendung des alten Scanners auf der MicroVax: ****/
/* #define OldScan */

#ifdef __STDC__
#include <stddef.h>
#include <stdlib.h>
#endif

#include <stdio.h>

#ifndef OldScan
#include <string.h>
#endif

#include "gramtyp.h"

#ifndef OldScan
#include "scanfunk.h"
#define pperror(ort/*a,b*/,c) wErrorf(ort,"%s\n",c)
#endif

#ifndef __STDC__
extern char *realloc();
#endif

/********************************/
/* globale Variablen */
/********************************/

gramptr gr;

static int anzfehler;
#ifdef OldScan
static int zeile, spalte; 
#else
static Quellort ort1;
static Quellort *ort = &ort1;
#endif
static vocabelIndex lastLP;     /* Linke Seite der unter anzprod eingetragenen
				   Produktion */
static functIndex copy;		/* Kopierfunktion fuer einfache Zuweisung */
static entryIndex entry_issem; 	/* Name des Attributs aller
				                        semantisch relevanten Terminals */
static typIndex	integer;	/* Typ fuer Integer */


#define STARTSIZE 10	/* Startgroesse fuer alle Felder */

#define MAXRELCODE 4000	/* Max. Symboltabelleneintraege */

#define MAXTERM 255	/* Max. Anzahl Terminals */
#define MAXNONTERM 256	/* Max. Anzahl Nonterminals */

/* ******************************** */
/* Dynamische Speicherreservierung  */
/* ******************************** */
#if defined ( ultrix ) && ! defined ( __STDC__)
typedef int size_t;
#endif

#ifdef __STDC__
static char *getMem(size_t amount)
{
#else /* ! __STDC__ */
static char *getMem( amount)
 size_t amount;
 {
#endif /* ! __STDC__ */
/* Bricht Programm ab, wenn kein Speicherplatz mehr vorhanden */

  char *ptr;
  
  if ( (ptr = (char *)malloc( amount)) == NULL )
   { 
#ifdef OldScan
     pperror(0, 0, "\n***** Abbruch wegen Speichermangel *****");
#else
     memError();
#endif
     exit(10);
   }
  return(ptr);    
 } /* getMem */


/********************************/
/* --- nicht in Grammatik --- */
/* Funktionen zum Belegen neuer Feldelemente mit Bereichsgrenzenpruefung
   und evtl. Feldvergroesserung */
/********************************/
#ifdef __STDC__
int Resize(int max, int size, char **tab)
#else /* ! __STDC__ */
int Resize(max, size, tab)
int max, size;
char **tab;
#endif /* ! __STDC__ */
{
	if (*tab == 0) {
		*tab = getMem(STARTSIZE*size);
		return(STARTSIZE);
	} 
	else {
		*tab = realloc(*tab, 2*max*size);
		return(2*max);
	}
}
#define resize(m,s,t) Resize((int)(m),(int)(s),(char **)(t))

#ifdef __STDC__
entryIndex newentry(gramptr g)
#else /* ! __STDC__ */
entryIndex newentry(g)
gramptr g;
#endif /* ! __STDC__ */
{
	static int max;
	if (!g->entrytab || g->anzentries >= max-1) {
		max = resize(max, sizeof(entry), &g->entrytab);
	}
	return (++g->anzentries);
}

#ifdef __STDC__
nontermIndex newnonterm(gramptr g)
#else /* ! __STDC__ */
nontermIndex newnonterm(g)
gramptr g;
#endif /* ! __STDC__ */
{
	static int max;
	if (!g->nontermtab || g->anznonterm >= max-1) {
		max = resize(max, sizeof(nonterminal), &g->nontermtab);
	}
	return (++g->anznonterm);
}

#ifdef __STDC__
termIndex newterm(gramptr g)
#else /* ! __STDC__ */
termIndex newterm(g)
gramptr g;
#endif /* ! __STDC__ */
{
	static int max;
	if (!g->termtab || g->anzterm >= max-1) {
		max = resize(max, sizeof(terminal), &g->termtab);
	}
	return (++g->anzterm);
}

#ifdef __STDC__
functIndex newfunct(gramptr g)
#else /* ! __STDC__ */
functIndex newfunct(g)
gramptr g;
#endif /* ! __STDC__ */
{
	static int max;
	if (!g->functtab || g->anzfunct >= max-1) {
		max = resize(max, sizeof(funct), &g->functtab);
	}
	return (++g->anzfunct);
}

#ifdef __STDC__
attrIndex newattr(gramptr g)
#else /* ! __STDC__ */
attrIndex newattr(g)
gramptr g;
#endif /* ! __STDC__ */
{
	static int max;
	if (!g->attrtab || g->anzattr >= max-1) {
		max = resize(max, sizeof(attribut), &g->attrtab);
	}
	return (++g->anzattr);
}

#ifdef __STDC__
productIndex newproduct(gramptr g)
#else /* ! __STDC__ */
productIndex newproduct(g)
gramptr g;
#endif /* ! __STDC__ */
{
	static int max;
	if (!g->prodtab || g->anzprod >= max-1) {
		max = resize(max, sizeof(product), &g->prodtab);
	}
	return (++g->anzprod);
}

#ifdef __STDC__
typIndex newtyp(gramptr g)
#else /* ! __STDC__ */
typIndex newtyp(g)
gramptr g;
#endif /* ! __STDC__ */
{
	static int max;
	if (!g->typtab || g->anztyp >= max-1) {
		max = resize(max, sizeof(typ), &g->typtab);
	}
	return (++g->anztyp);
}

#ifdef __STDC__
prodposIndex newprodpos(gramptr g)
#else /* ! __STDC__ */
prodposIndex newprodpos(g)
gramptr g;
#endif /* ! __STDC__ */
{
	static int max;
	if (!g->prodpostab || g->anzprodpos >= max-1) {
		max = resize(max, sizeof(prodpos), &g->prodpostab);
	}
	return (++g->anzprodpos);
}

#ifdef __STDC__
attrposIndex newattrpos(gramptr g)
#else /* ! __STDC__ */
attrposIndex newattrpos(g)
gramptr g;
#endif /* ! __STDC__ */
{
	static int max;
	if (!g->attrpostab || g->anzattrpos >= max-1) {
		max = resize(max, sizeof(attrpos), &g->attrpostab);
	}
	return (++g->anzattrpos);
}

#ifdef __STDC__
aufrufIndex newaufruf(gramptr g)
#else /* ! __STDC__ */
aufrufIndex newaufruf(g)
gramptr g;
#endif /* ! __STDC__ */
{
	static int max;
	if (!g->aufruftab || g->anzaufruf >= max-1) {
		max = resize(max, sizeof(aufruf), &g->aufruftab);
	}
	return (++g->anzaufruf);
}

#ifdef __STDC__
aparamIndex newaparam(gramptr g)
#else /* ! __STDC__ */
aparamIndex newaparam(g)
gramptr g;
#endif /* ! __STDC__ */
{
	static int max;
	if (!g->aparamtab || g->anzaparam >= max-1) {
		max = resize(max, sizeof(aparam), &g->aparamtab);
	}
	return (++g->anzaparam);
}

#ifdef __STDC__
fparamIndex newfparam(gramptr g)
#else /* ! __STDC__ */
fparamIndex newfparam(g)
gramptr g;
#endif /* ! __STDC__ */
{
	static int max;
	if (!g->fparamtab || g->anzfparam >= max-1) {
		max = resize(max, sizeof(fparam), &g->fparamtab);
	}
	return (++g->anzfparam);
}

/********************************/

#ifdef __STDC__
#ifdef OldScan
void error (int zeile, int spalte, int errnr)
#else
void error(Quellort *ort, int errnr)
#endif              
    
#else /* ! __STDC__ */
#ifdef OldScan
void error(zeile, spalte, errnr)
int zeile, spalte, errnr;
#else
void error(ort , errnr)
Quellort *ort;
int  errnr;
#endif /* OldScan */
#endif /* ! __STDC__ */
/*
	Gibt Fehlermeldung Nr.'errnr' aus fuer Quelltext-'zeile' und -'spalte'
	Eingaben: zeile Quelltextzeile
		  spalte Quelltestspalte
		  errnr Fehlernummer
	Ausgaben: -
	*/
{
	filestring st;

	switch(errnr) {
	case  1:
		sprintf(st, "Identifier declared twice.");
		break;
	case  2:
		sprintf(st, "Too many nonterminals (Max %3d).",
		MAXNONTERM);
		break;
	case  3:
		sprintf(st, "Too many terminals (Max %3d).",
		MAXTERM);
		break;
	case  4:
		sprintf(st, "Identifier not declared.");
		break;
	case  5:
		sprintf(st, "LHS must be a nonterminal.");
		break;
	case  7:
		sprintf(st, "Attribute has double type.");
		break;
	case  8:
		sprintf(st, "Illegal or missing position number.");
		break;
	case  9:
		sprintf(st, "Attribute declared twice.");
		break;
	case 10:
		sprintf(st, "Function not declared.");
		break;
	case 11:
		sprintf(st, 
		"Illegal position number or vocabel not found.");
		break;
	case 12:
		sprintf(st, "Unknown attribute.");
		break;
	case 15:
		sprintf(st, "Formal to actual parameter mismatch.");
		break;
	case 16: 
		sprintf(st, "Function result mismatch.");
		break;
	case 17: 
		sprintf(st, "Type mismatch.");
		break;
	case 18:
		sprintf(st, "Missing attribute.");
		break;
	case 21:
		sprintf(st, 
		"Axiom must have exactly one synthesized attribute.");
		break;
	case 22:
		sprintf(st, "Axiom must be a nonterminal.");
		break;
	case 23:
		sprintf(st, "Terminal must be semantic.");
		break;
       /* ACHTUNG: neue Meldung */
	case 24:
		sprintf(st, "multiple results not yet implemented.");
		break;
	default:
		sprintf(st, "Unknown error #%0d.", errnr);
	} /* switch */
#ifdef OldScan
	pperror(zeile, spalte, st);
#else
	pperror(ort, st);
#endif
	anzfehler++;
} /* error() */


#ifdef __STDC__
void symerror(gramptr g, entryIndex Xentry, int errnr)
          
                  
          
#else /* ! __STDC__ */
void symerror(g, Xentry, errnr)
gramptr g;
entryIndex Xentry;
int errnr;
#endif /* ! __STDC__ */
/*
	Gibt Fehlermeldung Nr.'errnr' fuer Symbol 'entry' aus
	Eingaben: g   Grammatik
		  entry Entry-Nr. des Symbols
		  errnr Fehlernummer
	Ausgaben: -
	*/
{
	identifier id;
	filestring msg;

	id = g->entrytab[Xentry].name;

	switch(errnr) {
	case  6:
		sprintf(msg, "%s: Attribute has double direction.", id);
		break;
	case  7:
		sprintf(msg, "%s: Attribute has double type.", id);
		break;
	case  8:
		sprintf(msg, "%s: Illegal or missing position number.",
		id);
		break;
	case 13:
		sprintf(msg, "%s: Too many semantic rules.", id);
		break;
	case 14:
		sprintf(msg, "%s: No semantic rules.", id);
		break;
	case 19:
		sprintf(msg, 
		"%s: Synthesized attribute not allowed here.", id);
		break;
	case 20:
		sprintf(msg,
		"%s: Inherited attribute not allowed here.", id);
		break;
	default:
		sprintf(msg, "%s: Unknown error #%0d.", id,
		errnr);
	} /* switch */
#ifdef OldScan
	pperror(zeile, spalte, msg);
#else
	pperror(ort, msg);
#endif
	anzfehler++;
} /* symerror() */


#ifdef __STDC__
void attrposerror(gramptr g, attrposIndex ap, int errnr)
          
                
          
#else /* ! __STDC__ */
void attrposerror(g, ap, errnr)
gramptr g;
attrposIndex ap;
int errnr;
#endif /* ! __STDC__ */
/*
	Gibt Fehlermeldung Nr.'errnr' fuer Attributposition 'ap' aus
	Eingaben: g   Grammatik
		  ap    Attrpos-Nr.
		  errnr Fehlernummer
	Ausgaben: -
	*/
{
	identifier id1,id2;
	nontermIndex nt;
	attrIndex at;
	int pos;
	filestring msg;

	pos = g->prodpostab[g->attrpostab[ap].prodpos].pos;
	nt = g->prodpostab[g->attrpostab[ap].prodpos].vocabel;
	at = g->attrpostab[ap].attr;
	id1 = g->entrytab[g->nontermtab[nt].name].name;
	id2 = g->entrytab[g->attrtab[at].name].name;
	if (pos >= 0) sprintf(msg, "%s<%d>.%s: ",id1,pos,id2);
	else sprintf(msg, "%s.%s: ",id1,id2);

	switch(errnr) {
	case 13:
		strcat(msg, "Too many semantic rules.");
		break;
	case 14:
		strcat(msg, "No semantic rules.");
		break;
	case 19:
		strcat(msg, "Synthesized attribute not allowed here.");
		break;
	case 20:
		strcat(msg, "Inherited attribute not allowed here.");
		break;
	default:
		sprintf(msg, "%s: Unknown error #%0d.", id1, errnr);
	} /* switch */
#ifdef OldScan
	pperror(zeile, spalte, msg);
#else
	pperror(ort, msg);
#endif
	anzfehler++;
} /* attrposerror() */


#ifdef __STDC__
bool CompareId(gramptr g, entryIndex e1, entryIndex e2)
          
                  
#else /* ! __STDC__ */
bool CompareId(g, e1, e2)
gramptr g;
entryIndex e1, e2;
#endif /* ! __STDC__ */
/*
	Vergleicht zwei Symbole
	Eingaben: g   Grammatik
		  e1  Entry fuer Symbol 1
		  e2    "    "     "    2
	Ausgaben: true, falls Gleichheit, sonst false
	*/
{
	identifier id1, id2;

	id1 = g->entrytab[e1].name;
	id2 = g->entrytab[e2].name;
	return(!strcmp(id1, id2));
} /* CompareId() */


#ifdef __STDC__
char *trim(char *str)
#else /* ! __STDC__ */
char *trim(str)
char *str;
#endif /* ! __STDC__ */
{
	char *s;

	s = str;
	while ((*s != ' ') && (*s != '\0')) s++;
	*s = '\0';
	return(str);
}


#ifdef __STDC__
void enter(grammar *gr, ident id, symbolclass c, entryIndex *s, bool *unique)
            
         
              
              
             
#else /* ! __STDC__ */
void enter(gr, id, c, s, unique)
grammar *gr;
ident id;
symbolclass c;
entryIndex *s;
bool *unique;
#endif /* ! __STDC__ */
/*
   traegt einen Identifier in die Symboltabelle ein bzw.
   sucht einen Identifier aus der Symboltabelle
   die Symbolklassen FUNCT und SFUNCT werden
   zusammengenommen
   (TERM und NONTERM auch ?)   
   Eingaben: gr  Grammatik 
        id  Identifier   
  
   */
{
	entryIndex t;
	char *name;

#ifdef OldScan
	*s = t = gr->relcodetab[id.nr];
	zeile = id.zeile;
	spalte = id.spalte; 
#else
	*s = t = gr->relcodetab[SEMVAL(id)];
	*ort = *QUELL_ORT(id);
#endif
	if((c == SFUNCT) || (c == FUNCT)) {
		while((*s != 0) && (gr->entrytab[*s].class != SFUNCT) && 
		    (gr->entrytab[*s].class != FUNCT)) {
			*s = gr->entrytab[*s].otherclass;
		}
	} 
	else {
		while((*s != 0) && (gr->entrytab[*s].class != c)) {
			*s = gr->entrytab[*s].otherclass;
		}
	}
	if(*s != 0 && c != ATTRIBUT) {
		*unique = FALSE;
		return;
	}
	*s = newentry(gr); /* ++gr->anzentries; */
#ifdef OldScan
	name = (char *)malloc(sizeof(filestring));
	decode(name, 9, id.nr, id.hash);
#else
	name = (char *)getMem(sizeof(filestring));
	/* strcpy(name,scan_decode(SEMVAL(id))); */
	scannDecode(name,id,sizeof(filestring));
#endif
	name = trim(name);
	gr->entrytab[*s].name = name;
	gr->entrytab[*s].class = c;
	if(t == 0) {
		gr->entrytab[*s].otherclass = 0;
	} 
	else {
		gr->entrytab[*s].otherclass = t;
	}
#ifdef OldScan
	gr->relcodetab[id.nr] = *s;
#else
	gr->relcodetab[SEMVAL(id)] = *s;
#endif
	*unique = TRUE;
	return;
} /* enter() */


#ifdef __STDC__
void lookup(grammar *gr, ident id, symbolclass c, entryIndex *s)
            
         
              
              
#else /* ! __STDC__ */
void lookup(gr, id, c, s)
grammar *gr;
ident id;
symbolclass c;
entryIndex *s;
#endif /* ! __STDC__ */
/*
	sucht einen Identifier aus der Symboltabelle
	Eingaben: gr  Grammatik
		  id  Identifier
		  c   Symbolklasse des Identifiers
	Ausgaben: s   Entry-Nummer des Identifiers oder NIL, falls nichts gef.
	*/
{

#ifdef OldScan
	*s = gr->relcodetab[id.nr];
	zeile = id.zeile;
	spalte = id.spalte; 
#else
	*s = gr->relcodetab[SEMVAL(id)];
	*ort = *QUELL_ORT(id);
#endif
	if((c == SFUNCT) || (c == FUNCT)) {
		while((*s != 0) && ((gr->entrytab[*s].class != SFUNCT) &&	
		    (gr->entrytab[*s].class != FUNCT))) {
			*s = gr->entrytab[*s].otherclass;
		}
	} 
	else {
		while((*s != 0) && (gr->entrytab[*s].class != c)) {
			*s = gr->entrytab[*s].otherclass;
		}
	}
	return;
}


#ifdef __STDC__
void lookupattr(grammar *gr, ident id, vocabelIndex voc, entryIndex *s)
            
         
                 
              
#else /* ! __STDC__ */
void lookupattr(gr, id, voc, s)
grammar *gr;
ident id;
vocabelIndex voc;
entryIndex *s;
#endif /* ! __STDC__ */
/*
	sucht nach einem Attribut zu einer Vokabel
	Eingaben: gr  Grammatik
		  id  Identifier des Attributs
		  voc Vokabel
	Ausgaben: s   Entry-Nummer des Attributs oder NIL
	*/
{
#ifdef OldScan
	*s = gr->relcodetab[id.nr];
	zeile = id.zeile;
	spalte = id.spalte; 
#else
	*s = gr->relcodetab[SEMVAL(id)];
	*ort = *QUELL_ORT(id);
#endif
	while((*s != 0) && ((gr->entrytab[*s].class != ATTRIBUT) ||
	    (gr->attrtab[gr->entrytab[*s].index.attribut].voc != voc))) {
		*s = gr->entrytab[*s].otherclass;
	}
	return;
}


#ifdef __STDC__

productIndex shift_for_alt (gramptr g, vocabelIndex LP)
          
#else /* ! __STDC__ */
productIndex shift_for_alt (g, LP)
gramptr g;
vocabelIndex LP;
#endif /* ! __STDC__ */
/* Der unter anzprod bereitgestellte Platz wird zum Eintrag einer
   Alternative von LP nach vorn geschiftet */
{	productIndex h, hh;
	prodposIndex pp;
	vocabelIndex N;
	entryIndex e;
	for (h = g->anzprod; h>0; --h)
	{	pp = g->prodtab[hh=h-1].firstprodpos;
		if (g->prodtab[hh].nextprod != NIL)
	 	  	g->prodtab[h].nextprod = h+1;
		else  {
	 	  g->prodtab[h].nextprod = NIL;
		  if (pp != NIL
		      && (N = g->prodpostab[pp].vocabel) <= g->anznonterm)
			if (N == LP)  return h;
			else  ++ g->nontermtab[N].firstproduct;
		}
		g->prodtab[h].prodname = e = g->prodtab[hh].prodname;
		g->prodtab[h].firstprodpos = pp;
		g->prodtab[h].firstaufruf = g->prodtab[hh].firstaufruf;
		g->prodtab[h].firstauxattrpos = g->prodtab[hh].firstauxattrpos;
		++ g->entrytab[e].index.product;
		while (! g->prodpostab[pp].ende) 
			++ g->prodpostab[pp++].product;
	}
}


#ifdef __STDC__
void syminit(gramptr g)
          
#else /* ! __STDC__ */
void syminit(g)
gramptr g;
#endif /* ! __STDC__ */
/*
	generiert Eintraege fuer die vordefinierte Funktion
	"makeid" (identische Funktion = einfache Zuweisung)
	und den Attributnamen
	"entry_issem" fuer semantisch relevante Terminalsymbole
	** Hilfsfunktion von graminit **
	Eingaben: g   Grammatik
	Ausgaben: -
	*/
{
	entryIndex e;

	/* Typeintrag fuer "INTEGER" generieren */

	integer = newtyp(g);
	e = newentry(g); 
	g->typtab[integer].name = e;
	g->typtab[integer].tkenn = SEMTYP;

	g->entrytab[e].name = "INTEGER";
	g->entrytab[e].otherclass = 0;
	g->entrytab[e].class = TYP;
	g->entrytab[e].index.typ = integer;

	/* Typeintrag fuer "makeid" generieren */

	copy = newfunct(g);
	e = newentry(g); 
	g->functtab[copy].name = e;
	g->functtab[copy].iscopy = TRUE;
	g->functtab[copy].firstarg = NIL;
	g->functtab[copy].firsterg = NIL;

	g->entrytab[e].name = "makeid";
	g->entrytab[e].otherclass = 0;
	g->entrytab[e].class = FUNCT;
	g->entrytab[e].index.funct = copy;

	/* Typeintrag fuer "entry_issem" generieren */

	entry_issem = newentry(g); 
	g->entrytab[entry_issem].name = "issem";
	g->entrytab[entry_issem].otherclass = 0;
	g->entrytab[entry_issem].class = ATTRIBUT;
	g->entrytab[entry_issem].index.attribut = NIL; 

	/* wird fuer alle
								  sem.Terms verwendet */
}

#ifdef __STDC__
void graminit(gramptr *gr)
            
#else /* ! __STDC__ */
void graminit(gr)
gramptr *gr;
#endif /* ! __STDC__ */
/*
	Initialisierung der Grammatik:
	-  Anlegen des grammar-Records
	-  Anlegen der einzelnen Felder mit Standardlaengen
	-  Alle Feldlaengenangaben auf 0 setzen
	Eingaben: -
	Ausgaben: gr  Grammatik
	*/
{
	gramptr g;
	int i;

	g = (gramptr)getMem(sizeof(grammar));

	g->firstfunct = 0;

	g->relcodetab = (relcodeArray)getMem(MAXRELCODE * sizeof(int));
	for(i=0; i<MAXRELCODE; i++) g->relcodetab[i] = 0;

	g->entrytab = 0;
	g->termtab = 0;
	g->nontermtab = 0;
	g->functtab = 0;
	g->attrtab = 0;
	g->prodtab = 0;
	g->typtab = 0;
	g->prodpostab = 0;
	g->attrpostab = 0;
	g->aufruftab = 0;
	g->fparamtab = 0;
	g->aparamtab = 0;

	g->anzentries = 
	    g->anznonterm =
	    g->anzterm = 
	    g->anzfunct = 
	    g->anzattr = 
	    g->anzprod = 
	    g->anztyp = 
	    g->anzprodpos = 
	    g->anzattrpos = 
	    g->anzaufruf = 
	    g->anzaparam = 
	    g->anzfparam = 0;

	syminit(g);
	anzfehler = 0;
	*gr = g;
}


#ifdef __STDC__
void GramName(gramptr g, ident id1, ident id2, ident id3, gramptr *out)
          
                  
             
#else /* ! __STDC__ */
void GramName(g, id1, id2, id3, out)
gramptr g;
ident id1,id2,id3;
gramptr *out;
#endif /* ! __STDC__ */
/*
	Traegt Phasen-, Eingabe- und Ausgabegrammatikname ein
	Eingaben: id1  Identifier fuer Phasenname
		  id2       "          Eingabegrammatik
		  id3       "          Ausgabegrammatik
	Ausgaben: out Grammatik
	*/
{
	entryIndex s1,s2,s3;
	bool	unique;

	enter(g,id1, GRAM, &s1, &unique);
	enter(g,id2, GRAM, &s2, &unique);
	if (!unique)
#ifdef OldScan
		error(id2.zeile, id2.spalte, 1);
#else
		error(QUELL_ORT(id2), 1);
#endif
			/* declared twice */
	enter(g,id3, GRAM, &s3, &unique);
	if (!unique)
#ifdef OldScan
		error(id3.zeile, id3.spalte, 1);
#else
		error(QUELL_ORT(id3), 1);
#endif
			/* declared twice */
	g->phasenid = s1;
	g->ingname = s2;
	g->outgname = s3;

	*out = g;
}


#ifdef __STDC__
void GramReturn(gramptr g, gramptr *out)
               
#else /* ! __STDC__ */
void GramReturn(g, out)
gramptr g,*out;
#endif /* ! __STDC__ */
/*
	uebergeben des gesammelten Information an globale Variablen
	Initialisierung der Zugriffsfunktion
	Aufruf einer Grammatik-Anwenderprozedur AGuser()
	Eingaben: g   Grammatik
	Ausgaben: out NIL-Pointer
	*/
{

/*
 * Hier koennten die Namen fuer Projekt und eingelesene Datei
   initialisiert werden. Sie werden momentan nicht benutzt. Bei
   Bedarf koennten sie z.B. in der Shellscript, mit der der Ein-
   leser gestartet wird, angegeben werden
     setenv projekt $argv[1]
     setenv datei $argv[2] 
   und hier mit 
	InitNames(getenv("projekt"), getenv("datei"));
   ausgelesen werden.
*/

	if(!anzfehler)
	{
		gr = g;
		InitZug(); 
		AGuser();	
	}
	else
#ifdef OldScan
	{       filestring st;
		sprintf(st,"\n**** Gesamt: %d Fehler beim Einlesen ! ****\n",anzfehler);
		pperror(0, 0, st);
	}
#else
		wErrorf(NULL,"\n**** Gesamt: %d Fehler beim Einlesen ! ****\n",anzfehler);
#endif

	free(g);
	*out = NIL;
}


#ifdef __STDC__
void CreateTerm(gramptr g, ident id, termIndex *t)
          
         
             
#else /* ! __STDC__ */
void CreateTerm(g, id, t)
gramptr g;
ident id;
termIndex *t;
#endif /* ! __STDC__ */
/*
	Traegt ein Terminal in der Grammatik ein.
	Hilfsfunktion von EnterTerm, EnterSemTerm
	Eingaben: g   Grammatik
		  id  Identifier des Terminal
	Ausgaben: t   Terminal
	*/
{
	entryIndex newsym;
	termIndex newt;
	bool	unique;

	enter(g, id, TERM, &newsym, &unique);
	if (unique) {
		newt = newterm(g);

		g->entrytab[newsym].index.term = newt;

		g->termtab[newt].name = newsym;
		g->termtab[newt].attr = NIL;
		*t = newt;
	} 
	else {
			/* declared twice */
#ifdef OldScan
		error(id.zeile, id.spalte, 1);
#else
		error(QUELL_ORT(id), 1);
#endif
		*t = NIL;
	}
	if (g->anzterm > MAXTERM)
		 /* too many t */
#ifdef OldScan
		error(zeile, spalte, 3);
#else
		error(ort, 3);
#endif
}


#ifdef __STDC__
void EnterTerm(gramptr g, ident id, gramptr *out)
          
         
             
#else /* ! __STDC__ */
void EnterTerm(g, id, out)
gramptr g;
ident id;
gramptr *out;
#endif /* ! __STDC__ */
/*
	Traegt ein Terminal in der Grammatik ein.
	Ersetzt die bisherigen Funktionen MakeTerm, PrefixTerm, EnterTerm
	Eingaben: g   Grammatik
		  id  Identifier des Terminal
	Ausgaben: out Grammatik
	*/
{
	termIndex t;

	CreateTerm(g, id, &t);
	if (t) {
		g->termtab[t].issemantic = FALSE;
	}
	*out = g;
}

#ifdef __STDC__
void EnterSemTerm(gramptr g, ident id, gramptr *out)
          
         
             
#else /* ! __STDC__ */
void EnterSemTerm(g, id, out)
gramptr g;
ident id;
gramptr *out;
#endif /* ! __STDC__ */
/*
	Traegt ein semantisch relevantes Terminal in der Grammatik ein.
	Ersetzt die bisherigen Funktionen MakeSemTerm, PrefixTerm, EnterTerm
	Eingaben: g   Grammatik
		  id  Identifier des Terminal
	Ausgaben: out Grammatik
	*/

{
	attrIndex a;
	termIndex t;

	CreateTerm(g, id, &t);
	if (t) {
		a = newattr(g);
		g->attrtab[a].name = entry_issem;
		g->attrtab[a].voc = t + g->anznonterm;
		g->attrtab[a].akenn = SEMTERM;
		g->attrtab[a].typ = CreateTyp(g,id);
		g->attrtab[a].ende = TRUE;

		g->termtab[t].issemantic = TRUE;
		g->termtab[t].attr = a;
	}
	*out = g;
}


#ifdef __STDC__
nontermIndex CreateNT(gramptr g, ident id, nontermIndex first)
          
         
#else /* ! __STDC__ */
nontermIndex CreateNT(g, id, first)
gramptr g;
ident id;
nontermIndex first;
#endif /* ! __STDC__ */
/*
	Hilfsfunktion fuer MakeNT und PrefixNT
	Eingaben: g   Grammatik
		  id  Identifier des Noterminal
	Ausgabe:  Index des eingetragenen Nonterminals
	*/
{
	entryIndex newsym, e;
	nontermIndex newnt;
	bool	unique;

	enter(g, id, NONTERM, &newsym, &unique);
	if (unique) {
	  newnt = newnonterm(g);

	  g->nontermtab[newnt].firstattr = NIL;
	  g->nontermtab[newnt].firstproduct = NIL;
	  g->nontermtab[newnt].firstoccurence = NIL;
	  if (first!=NIL)
	    do {
	     g->nontermtab[newnt].name = e = g->nontermtab[newnt-1].name;
	     ++g->entrytab[e].index.nonterm;
	     }
	     while (--newnt > first);

	  g->nontermtab[newnt].name = newsym;
	  g->entrytab[newsym].index.nonterm = newnt;
	  if (g->anznonterm > MAXNONTERM)    /* too many nt */
#ifdef OldScan
			error(zeile, spalte, 2);
#else
			error(ort, 2);
#endif
	  return (newnt);
	} 
	else {
#ifdef OldScan
		error(id.zeile, id.spalte, 1);
#else
		error(QUELL_ORT(id), 1);
#endif
		/* declared twice */
		return (first);
	}
}

#ifdef __STDC__
void MakeNT(gramptr g, ident id, nontermIndex *nt)
          
         
                 
#else /* ! __STDC__ */
void MakeNT(g, id, nt)
gramptr g;
ident id;
nontermIndex *nt;
#endif /* ! __STDC__ */
/*
	Traegt ein Nonterminal in die Grammatik ein (Start einer NT-"Liste").
	Eingaben: g   Grammatik
		  id  Identifier des Nonterminal
	Ausgaben: nt  Nonterminal - Index
	*/
{
	*nt = CreateNT(g, id, NIL);
}


#ifdef __STDC__
void PrefixNT(gramptr g, ident id, nontermIndex nt, nontermIndex *first)
          
         
                        
#else /* ! __STDC__ */
void PrefixNT(g, id, nt, first)
gramptr g;
ident id;
nontermIndex nt, *first;
#endif /* ! __STDC__ */
/*
	Traegt ein Nonterminal in die aktuelle NT-"Liste" ein.
	Liste = Bereich von nt bis g->anznonterm
	Eingaben: g   Grammatik
		  id  Identifier des Nonterminal
		  nt  Anfang der NT-Liste
	Ausgaben: first neuer Anfang der NT-Liste
	*/
{
	*first = CreateNT(g, id, nt);
}

#ifdef __STDC__
typIndex CreateTyp(gramptr g, ident id)
          
         
#else /* ! __STDC__ */
typIndex CreateTyp(g, id)
gramptr g;
ident id;
#endif /* ! __STDC__ */
/*
	Hilfsfunktion fuer SpecAttr, CreateAux
	Eingaben: g   Grammatik
		  id  Identifier des Types
	Ausgabe:  Index des Typs
	*/
{
	entryIndex sym;
	typIndex ty;
	bool unique;

	enter(g, id, TYP, &sym, &unique);

	if (unique) {
		ty = newtyp(g);
		g->entrytab[sym].index.typ = ty;

		g->typtab[ty].name = sym;
		g->typtab[ty].tkenn = CTYP;

		return(ty);
	} 
	else
		return(g->entrytab[sym].index.typ);
}


#ifdef __STDC__
void InitAList(gramptr g, attrIndex *al)
          
              
#else /* ! __STDC__ */
void InitAList(g, al)
gramptr g;
attrIndex *al;
#endif /* ! __STDC__ */
/*
	Beginnt eine Attribut-Liste
	Eingaben: g   Grammatik
	Ausgaben: al  Startelement der Attributliste
	*/
{
	*al = g->anzattr + 1;
}


#ifdef __STDC__
attrIndex CreateAttr(gramptr g, ident id)
          
         
#else /* ! __STDC__ */
attrIndex CreateAttr(g, id)
gramptr g;
ident id;
#endif /* ! __STDC__ */
/*
	Hilfsfunktion fuer AddAttr 
	Eingaben: g   Grammatik
		  id  Identifier des Attributs 
	Ausgabe:  Index des eingetragenen Attributs   
	*/
{
	entryIndex e;
	attrIndex newa;
	bool unique;
	nontermIndex akt;

	akt = g->anznonterm + 1;	/* Vokabelnr.fuer aktuelle Attr-Liste */

	/* Attribut zu dieser Vokabel schon vorhanden ? */
	lookupattr(g, id, akt, &e);
	if(e) {
#ifdef OldScan
		error(id.zeile, id.spalte, 9);
#else
		error(QUELL_ORT(id), 9);
#endif
		/* attr declared twice */
		return(NIL);
	}
	enter(g, id, ATTRIBUT, &e, &unique);
	newa = newattr(g);

	g->entrytab[e].index.attribut = newa;

	g->attrtab[newa].name = e;
	g->attrtab[newa].voc = akt; 	/* Attr. gehoert zur aktuellen Liste */
	g->attrtab[newa].typ = NIL;	/* wird bei Abschluss der */
	g->attrtab[newa].ende = FALSE;	/* Liste mit LinkAttr korrigiert */
	return (newa);
}


#ifdef __STDC__
void MakeAttr(gramptr g, ident id, attrIndex *out)
          
         
               
#else /* ! __STDC__ */
void MakeAttr(g, id, out)
gramptr g;
ident id;
attrIndex *out;
#endif /* ! __STDC__ */
/*
	generiert ein Attribut-Feld
	Eingaben: g   Grammatik
		  id  Identifier des Attributs
	Ausgaben: out neuer Anfang der Attributliste
	*/
{
	*out = CreateAttr(g, id);
}


#ifdef __STDC__
void AddAttr(gramptr g, attrIndex list, ident id, attrIndex *out)
          
               
         
               
#else /* ! __STDC__ */
void AddAttr(g, list, id, out)
gramptr g;
attrIndex list;
ident id;
attrIndex *out;
#endif /* ! __STDC__ */
/*
	Traegt ein Attribut in die aktuelle Attribut-"Liste" ein.
	Liste = Bereich von list bis g->anzattr, dient zum Sammeln von
		Attributen des selben Typs 
	Eingaben: g   Grammatik
		 list Anfang der Attributliste
		  id  Identifier des Attributs
	Ausgaben: out neuer Anfang der Attributliste
	*/
{
	*out = CreateAttr(g, id);
	if (list) *out = list;
}


#ifdef __STDC__
void SpecAttr(gramptr g,
              attrIndex list,
              ident id,
              attrkenn dir,
              attrIndex *out)
          
               
         
             
               
#else /* ! __STDC__ */
void SpecAttr(g, list, id, dir, out)
gramptr g;
attrIndex list;
ident id;
attrkenn dir;
attrIndex *out;
#endif /* ! __STDC__ */
/*
	Weist allen Attributen in der Liste typ ID und Richtung DIR zu.
	Eingaben: g   Grammatik
		 list Anfang der Attributliste
		  id  Identifier des Typs
		  dir Richtung der Attribute
	Ausgaben: out Anfang der Attributliste ("never used")
	*/
{
	attrIndex i;
	typIndex ntyp;
	ntyp = CreateTyp(g, id);

	if(list) for (i=list; i <= g->anzattr; i++) {
		g->attrtab[i].akenn = dir;
		g->attrtab[i].typ = ntyp;
	}
	*out = list;
}


#ifdef __STDC__
void LinkAttr(gramptr g, nontermIndex nt, attrIndex alist, gramptr *out)
          
                
                
             
#else /* ! __STDC__ */
void LinkAttr(g, nt, alist, out)
gramptr g;
nontermIndex nt;
attrIndex alist;
gramptr *out;
#endif /* ! __STDC__ */
/*
	Weist allen Nonterminals in der NT-Liste die Attribute aus
	der alist-Liste zu.
	Die Attributfelder werden dabei eventuell mehrfach kopiert
	(fuer jedes Nonterminal)
	Eingaben: g   Grammatik
		  nt  Anfang der NT-Liste
		alist Anfang der Attributliste
	Ausgaben: out Grammatik
	*/
{
	nontermIndex i;
	entryIndex ae,ne;
	attrIndex j,a,anz;

	if(alist) g->attrtab[g->anzattr].ende = TRUE;

	/* Alle Nonterminals in der NT-Liste */
	if(nt) for (i=nt; i <= g->anznonterm; i++) {
		g->nontermtab[i].firstattr = alist;
		anz = g->anzattr + 1;

		/* Alle Attribute in der alist-Liste */
		if(alist) for (j=alist; j < anz; j++) {
			g->attrtab[j].voc = i; /* Rueckverweis */
			if (i < g->anznonterm) {
				/* es kommen noch mehr NT's */
				ae = g->attrtab[j].name;
				ne = newentry(g);
				g->entrytab[ne] = g->entrytab[ae];
				g->entrytab[ne].otherclass = 
				    g->entrytab[ae].otherclass;
				g->entrytab[ae].otherclass = ne;
				a = newattr(g);
				g->entrytab[ne].index.typ = a;
				g->attrtab[a] = g->attrtab[j];
				g->attrtab[a].name = ne;
				/* rueberkopieren */
			}
		}
		alist = anz;
	}
	else {
		/* Fehler bei der NT-Deklaration 
				  => Attribute unschaedlich machen */
		if(alist) for(j=alist; j <= g->anzattr; j++)
			g->attrtab[j].voc = NIL; 
	}		
	*out = g;
}


#ifdef __STDC__
void NoAttr(gramptr g, nontermIndex nt, gramptr *out)
          
                
             
#else /* ! __STDC__ */
void NoAttr(g, nt, out)
gramptr g;
nontermIndex nt;
gramptr *out;
#endif /* ! __STDC__ */
/*
	Die Nonterminals in der NT-Liste haben keine Attribute
	Eingaben: g   Grammatik
		  out Grammatik
	*/
{
	*out = g;
}


#ifdef __STDC__
void EnterAxiom(grammar *gr, ident id, grammar **out) 
            
         
              
#else /* ! __STDC__ */
void EnterAxiom(gr, id, out) 
grammar *gr;
ident id;
grammar **out;
#endif /* ! __STDC__ */
/*
	traegt das Axiom in die Grammatik ein
	Eingaben: gr  Grammatik
		  id  Identifier des Axioms
	Ausgaben: out Grammatik
	*/
{
	entryIndex s;
	nontermIndex n;
	attrIndex ai;
	attribut a;

	lookup(gr, id, NONTERM, &s);

	if(s == NIL) {
		 /* axiom must be nt */
#ifdef OldScan
		error(id.zeile, id.spalte, 22);
#else
		error(QUELL_ORT(id), 22);
#endif
		gr->axiom = NIL;
	} 
	else {
		gr->axiom = n = gr->entrytab[s].index.nonterm;
		/* pruefe, ob genau ein synthesized Attribut vorliegt */
		ai = gr->nontermtab[n].firstattr;
		a = gr->attrtab[ai];
		if (ai == NIL || a.akenn != SYNTHESIZED || a.ende == FALSE) {
			 /* ax. must have exactly one synthesized */
#ifdef OldScan
		error(id.zeile, id.spalte, 21);
#else
		error(QUELL_ORT(id), 21);
#endif
		}
	}
	*out = gr;
} /* EnterAxiom() */


#ifdef __STDC__
void MakeInherited(attrkenn *k)
            
#else /* ! __STDC__ */
void MakeInherited(k)
attrkenn *k;
#endif /* ! __STDC__ */
/*
	liefert die Attributkennung 'INHERITED'
	Eingaben: -
	Ausgaben: k   Attributkennung
	*/
{
	*k = INHERITED;
	return;
} /* MakeInherited() */


#ifdef __STDC__
void MakeSynthesized(attrkenn *k)
            
#else /* ! __STDC__ */
void MakeSynthesized(k)
attrkenn *k;
#endif /* ! __STDC__ */
/*
	liefert die Attributkennung 'SYNTHESIZED'
	Eingaben: -
	Ausgaben: k   Attributkennung
	*/
{
	*k = SYNTHESIZED;
	return;
}


#ifdef __STDC__
void MakeSemTerm(attrkenn *k)
            
#else /* ! __STDC__ */
void MakeSemTerm(k)
attrkenn *k;
#endif /* ! __STDC__ */
/*
	liefert die Attributkennung 'SEMTERM' fuer sem. rel. Terminal
	Eingaben: -
	Ausgaben: k   Attributkennung
	*/
{
	*k = SEMTERM;
	return;
}


#ifdef __STDC__
void EmptyArg(fparamIndex *fp)
                
#else /* ! __STDC__ */
void EmptyArg(fp)
fparamIndex *fp;
#endif /* ! __STDC__ */
/*
	gibt eine leere formale Parameterliste zurueck
	Eingaben: -
	Ausgaben: fp  Startelement der formalen Parameterliste (=NIL)
	*/
{
	*fp = NIL;
	return;
} /* EmptyArg() */


#ifdef __STDC__
void CreateArg(grammar *gr, ident id, fparamIndex *fp)
            
         
                
#else /* ! __STDC__ */
void CreateArg(gr, id, fp)
grammar *gr;
ident id;
fparamIndex *fp;
#endif /* ! __STDC__ */
/*
	generiert fparam-Feld aus Typ-Identifier fuer Funkt. mit einem Ergebnis
	Eingaben: gr  Grammatik
		  id  Identifier
	Ausgaben: fp  fparam-Feld
	*/
{
	bool unique;
	entryIndex e;
	typIndex t;

	enter(gr, id, TYP, &e, &unique);
	*fp = newfparam(gr);
	if (unique) {
		t = newtyp(gr);
		gr->typtab[t].name = e;
		gr->typtab[t].tkenn = CTYP;
		gr->entrytab[e].index.typ = t;
	} 
	else {
		t = gr->entrytab[e].index.typ;
	}
	gr->fparamtab[*fp].typ = t;
	gr->fparamtab[*fp].ende = TRUE;
	return;
} /* CreateArg() */


#ifdef __STDC__
void PrefixArg(grammar *gr, ident id, fparamIndex fp, fparamIndex *afp)
            
         
               
                 
#else /* ! __STDC__ */
void PrefixArg(gr, id, fp, afp)
grammar *gr;
ident id;
fparamIndex fp;
fparamIndex *afp;
#endif /* ! __STDC__ */
/*
	traegt ein fparam-Feld in die aktuelle fparam-"Liste" ein
	Eingaben: gr  Grammatik
		  id  Identifier
		  fp  alter Listenanfang
	Ausgaben: afp neuer Listenanfang
	*/
{
	CreateArg(gr, id, afp);
	gr->fparamtab[*afp].ende = FALSE;
	if (fp) *afp = fp;
	return;
} /* PrefixArg() */


#ifdef __STDC__
void StartArg(gramptr g, fparamIndex *afp)
          
                 
#else /* ! __STDC__ */
void StartArg(g, afp)
gramptr g;
fparamIndex *afp;
#endif /* ! __STDC__ */
/*
	beginnt eine fparam-"Liste"
	Eingaben: g   Grammatik
	Ausgaben: afp Listenanfang
	*/
{
	*afp = g->anzfparam + 1;
}


#ifdef __STDC__
void EndArg(gramptr g, fparamIndex fp, fparamIndex *afp)
          
                     
#else /* ! __STDC__ */
void EndArg(g, fp, afp)
gramptr g;
fparamIndex fp, *afp;
#endif /* ! __STDC__ */
/*
	beendet die aktuelle fparam-"Liste"
	Eingaben: g   Grammatik
		  fp  alter Listenanfang
	Ausgaben: afp neuer Listenanfang
	*/
{
	if (fp) g->fparamtab[g->anzfparam].ende = TRUE;
	*afp = fp;
}


#ifdef __STDC__
void CreateFunct(gramptr g,
                 ident name,
                 fparamIndex param,
                 fparamIndex erg,
                 gramptr *out)
          
           
                       
             
#else /* ! __STDC__ */
void CreateFunct(g, name, param, erg, out)
gramptr g;
ident name;
fparamIndex param, erg;
gramptr *out;
#endif /* ! __STDC__ */

/*
	Erzeugt Eintrag fuer Funktion aus
	- Funktionsname
	- Parameter- und Ergebnisliste
	Eingaben: g   Grammatik
		 name Funktionsname
	   param, erg formale Parameterliste fuer Argumente und Ergebnisse
	Ausgaben: out Grammatik
	*/
{
	entryIndex newsym;
	bool unique;
	functIndex f;
	enter(g, name, FUNCT, &newsym, &unique);
	if (!unique)
#ifdef OldScan
		error(name.zeile, name.spalte, 1);
#else
		error(QUELL_ORT(name), 1);
#endif
	else {
		f = newfunct(g);
		g->entrytab[newsym].index.funct = f;
		g->functtab[f].name = newsym;
		g->functtab[f].iscopy = FALSE;
		g->functtab[f].firstarg = param;
		g->functtab[f].firsterg = erg;
	}
	*out = g;
}


#ifdef __STDC__
void CreateSFunct(gramptr g,
                 ident name,
                 fparamIndex fplist,
                 ident res,
                 gramptr *out)
          
#else /* ! __STDC__ */

void CreateSFunct(g, name, fplist, res, out)
gramptr g;
ident name;
fparamIndex fplist;
ident res;
gramptr *out;
#endif /* ! __STDC__ */
	/*
	Erzeugt Eintrag fuer syntaktische Funktion aus
	- Funktionsname
	- formale Parameter-Liste (Funktionsargumente)
	- Funktionsergebnis
	Eingaben: g   Grammatik
		 name Funktionsname
		fplist formale Parameterliste
		  res Name des Ergebnistyps
	Ausgaben: out Grammatik
	*/
{
entryIndex newsym;
fparamIndex resindex;
bool unique;
functIndex sf;
	CreateArg(g, res, &resindex);
	enter(g, name, SFUNCT, &newsym, &unique);
	if (!unique)
#ifdef OldScan
		error(name.zeile, name.spalte, 1);
#else
		error(QUELL_ORT(name), 1);
#endif
	else {
		sf = newfunct(g);
		g->entrytab[newsym].index.funct = sf;
		g->functtab[sf].name = newsym;
		g->functtab[sf].iscopy = FALSE;
		g->functtab[sf].firstarg = fplist;
		g->functtab[sf].firsterg = resindex;
	}
	/* Ergebnistyp SYNTYP-Machen  */
	g->typtab[g->fparamtab[resindex].typ].tkenn = SYNTYP;
	*out = g;
}


#ifdef __STDC__
void NoPos(int *p)
       
#else /* ! __STDC__ */
void NoPos(p)
int *p;
#endif /* ! __STDC__ */
/*
	Liefert Posnr. -1 fuer Produktionspositionen ohne Nummer
	z.B. bei STATLIST<0> -> STAT STATLIST<1> ist STAT ohne Posnr.
	Eingaben: -
	Ausgaben: Posnr.
	*/
{
	*p = -1;
}


#ifdef __STDC__
void EmptyRHS(prodposIndex *rlist)
                    
#else /* ! __STDC__ */
void EmptyRHS(rlist)
prodposIndex *rlist;
#endif /* ! __STDC__ */
/*
	Liefert eine leere prodpos-Liste fuer Produktionen ohne rechte Seite
	Eingaben: -
	Ausgaben: Prodposindex = NIL
	*/
{
	*rlist = NIL;
}


#ifdef __STDC__
void CreateProdpos(gramptr g, ident id, int n, prodposIndex *res)
                  
#else /* ! __STDC__ */
void CreateProdpos(g, id, n, res)
gramptr g;
ident id;
int n;
prodposIndex *res;
#endif /* ! __STDC__ */
/*
	Erzeugt Eintrag fuer Produktionsposition
	Eingaben: g   Grammatik
		  id  Identifier fuer Prodpos
		  n   Positionsnummer
	Ausgaben: res Nummer der erzeugten Prodpos
	*/
{
	entryIndex v;
	termIndex t;
	nontermIndex nt;
	attrIndex a;
	attrposIndex ap,fap;
	symbolclass class;
	prodposIndex pp;

	ap = NIL;
	fap = NIL;
	lookup(g, id, NONTERM, &v);
	class = NONTERM;

	if (!v) {
		lookup(g, id, TERM, &v);
		class = TERM;
	}
	if (!v) {
		 /* Ident not declared */
#ifdef OldScan
		error(id.zeile, id.spalte, 4);
#else
		error(QUELL_ORT(id), 4);
#endif
		*res = NIL;
	} 
	else {
		pp = newprodpos(g);
		g->prodpostab[pp].pos = n;

		if (class == TERM) {
			t = g->entrytab[v].index.term;
			if (a = g->termtab[t].attr) {
				/* Attribut zu Attrpos kopieren */
				fap = ap = newattrpos(g);
				g->attrpostab[ap].attr = a;
				g->attrpostab[ap].prodpos = pp;
				g->attrpostab[ap].aufruf = NIL;
				g->attrpostab[ap].ende = TRUE;
			}
			g->prodpostab[pp].vocabel = t + g->anznonterm;
		} 
		else {
			nt = g->entrytab[v].index.nonterm;
			if (a = g->nontermtab[nt].firstattr) do {
				/* Attributliste zu Attrpos kopieren */
				ap = newattrpos(g);
				if (!fap) fap = ap;
				g->attrpostab[ap].attr = a;
				g->attrpostab[ap].prodpos = pp;
				g->attrpostab[ap].aufruf = NIL;
				g->attrpostab[ap].ende = FALSE;
			} 
			while (!g->attrtab[a++].ende);
			if(ap) g->attrpostab[ap].ende = TRUE;

			g->prodpostab[pp].vocabel = nt;
		}
		g->prodpostab[pp].product = NIL;
		g->prodpostab[pp].firstattrpos = fap;
		g->prodpostab[pp].ende = FALSE;

		*res = pp;
	}
}


#ifdef __STDC__
void PrefixProdpos(gramptr g,
                   ident id,
                   int n,
                   prodposIndex list,
                   prodposIndex *newlist)
          
         
      
                            
#else /* ! __STDC__ */
void PrefixProdpos(g, id, n, list, newlist)
gramptr g;
ident id;
int n;
prodposIndex list, *newlist;
#endif /* ! __STDC__ */
/*
	Traegt eine Prodpos in die aktuelle Prodpos-Liste ein
	Eingaben: g   Grammatik
		  id  Identifier fuer Prodpos
		  n   Positionsnummer
		  list Anfang der PPos-Liste
	Ausgaben: newlist neuer Anfang der Prodpos-Liste
	*/
{
	CreateProdpos(g, id, n, newlist);
	if (list) *newlist = list;
}


#ifdef __STDC__
void CreateProd(gramptr g, ident id, prodposIndex pplist, productIndex *prod)
                   
#else /* ! __STDC__ */
void CreateProd(g, id, pplist, prod)
gramptr g;
ident id;
prodposIndex pplist;
productIndex *prod;
#endif /* ! __STDC__ */
/*
	Erzeugt Eintrag fuer Produktion. 
	Die auf pplist stehende Produktion wird abgeschlossen.
	Fuer Alternativen werden aufeinanderfolgende Eintraege
	garantiert. Damit wird dieselbe Nummerierung wie in der
	alten Pascalimplementierung erzielt.
	Eingaben: g   Grammatik
		  id  Name der Produktion (nicht der linken Seite !!)
	          pplist Anfang der Produktionspositionsliste
	Ausgaben: prod Nummer der erzeugten Produktion
	*/
{
	bool unique;
	entryIndex e;
	prodposIndex i,j;
	productIndex p;
	vocabelIndex voc;
	int posnr;

	enter(g, id, PRODUCT, &e, &unique);
	if (!unique)
#ifdef OldScan
		error(id.zeile, id.spalte, 1);
#else
		error(QUELL_ORT(id), 1);
#endif

	p = newproduct(g);
	if (pplist == NIL)  lastLP = NIL;
	else if ((voc = g->prodpostab[pplist].vocabel) > g->anznonterm)  {
				/* linke Seite ist Term */
#ifdef OldScan
			error(id.zeile, id.spalte, 5);
#else
			error(QUELL_ORT(id), 5);
#endif
			lastLP = NIL;
 	     }
	else if (g->nontermtab[voc].firstproduct == NIL) {
		g->nontermtab[voc].firstproduct = p;
		lastLP = voc;
	     }
	else {
		if (voc != lastLP)  p = shift_for_alt(g,voc);
		g->prodtab[p-1].nextprod = p;
	     }
	*prod = p;

	g->entrytab[e].index.product = p;
	g->prodtab[p].prodname = e;
	g->prodtab[p].firstprodpos = pplist;
	g->prodtab[p].firstaufruf = NIL;
	g->prodtab[p].firstauxattrpos = NIL;
	g->prodtab[p].nextprod = NIL;

	if (pplist == NIL)  return;

	g->prodpostab[g->anzprodpos].ende = TRUE; /* PPosliste beenden */

	/* Rueckverweis auf Produktion fuer alle Prodpositionen 
		in der Liste eintragen, PP-Nummern eintragen */
	for (i=pplist; i <= g->anzprodpos; i++) {
		voc = g->prodpostab[i].vocabel;
		if ( (g->prodpostab[i].num = i-pplist) != 0 )  {
			if (voc <= g->anznonterm) {
	 			g->prodpostab[i].nextoccur = 
					g->nontermtab[voc].firstoccurence;
				g->nontermtab[voc].firstoccurence = i;
                        }
		}
		g->prodpostab[i].product = p;
		/* Positionsnummer pruefen */
		posnr = g->prodpostab[i].pos;
		for (j=pplist; j < i; j++) {
			if (g->prodpostab[j].pos == posnr &&
			    voc && g->prodpostab[j].vocabel == voc)
				 /* Illegal or miss pos Nr. */
#ifdef OldScan
				error(id.zeile, id.spalte, 8);
#else
				error(QUELL_ORT(id), 8);
#endif

		}
	}
}


#ifdef __STDC__
void AddAuxInf(gramptr g, productIndex p, attrposIndex aux, productIndex *out)
          
               
                 
                  
#else /* ! __STDC__ */
void AddAuxInf(g, p, aux, out)
gramptr g;
productIndex p;
attrposIndex aux;
productIndex *out;
#endif /* ! __STDC__ */
/*
	Fuegt die Auxiliary-Information zu einer Produktion hinzu
	Eingaben: g   Grammatik
		  p   Produktion
		  aux Anfang der Auxiliary-Liste (als attrpos-Liste)
	Ausgaben: out Produktion
	*/
{
	prodposIndex pp;
	vocabelIndex voc;
	attrposIndex i;
	g->prodtab[p].firstauxattrpos = aux;

	/* Auxiliary-Liste abschliessen */
	if (aux != NIL) {
		g->attrpostab[g->anzattrpos].ende = TRUE;

		/* ppos und voc der Auxattrpositionen eintragen */
		pp = g->prodtab[p].firstprodpos;
		voc = g->prodpostab[pp].vocabel;
		for (i=aux; i <= g->anzattrpos; i++) {
			g->attrpostab[i].prodpos = pp;
			g->attrtab[g->attrpostab[i].attr].voc = voc;
		}
	}
	*out = p;
}


#ifdef __STDC__
void CreateAux(gramptr g, ident i1, ident i2, attrposIndex *out)
          
            
                  
#else /* ! __STDC__ */
void CreateAux(g, i1, i2, out)
gramptr g;
ident i1,i2;
attrposIndex *out;
#endif /* ! __STDC__ */
/*
	Erzeugt Eintrag fuer Auxiliary-Attribut
	Eingaben: g   Grammatik
		  i1  Attributname
		  i2  Attributtyp
	Ausgaben: out Attrpos-Feld
	*/
{
	attrIndex a,t;
	attrposIndex ap;

	t = CreateTyp(g, i2);
	a = CreateAttr(g, i1);
	if (a) {
		g->attrtab[a].typ = t;
		g->attrtab[a].akenn = AUXILIARY;
		ap = newattrpos(g);
		g->attrpostab[ap].attr = a;
		g->attrpostab[ap].aufruf = NIL;
		g->attrpostab[ap].ende = FALSE;
		*out = ap;
	} 
	else
		*out = NIL;
}


#ifdef __STDC__
void PrefixAux(attrposIndex left, attrposIndex right, attrposIndex *out)
                         
                  
#else /* ! __STDC__ */
void PrefixAux(left, right, out)
attrposIndex left, right;
attrposIndex *out;
#endif /* ! __STDC__ */
/*
	Verwaltung der Auxiliary-Liste
	koennte auch in der Grammatik durch Attributierung erledigt werden
	Eingaben: left Anfang der 1. Auxiliary-Liste
		  right Anfang der 2. Auxiliary-Liste
	Ausgaben: out  Anfang der Gesamtauxiliaryliste
	*/
{
	if (left)
		*out = left;
	else
		*out = right;
}


#ifdef __STDC__
void NoAux(attrposIndex *out)
#else /* ! __STDC__ */
void NoAux(out)
attrposIndex *out;
#endif /* ! __STDC__ */
{
	*out = NIL;
}

#ifdef __STDC__
attrposIndex search_alist(gramptr g, attrposIndex al, attrIndex attr)
          
                
               
#else /* ! __STDC__ */
attrposIndex search_alist(g, al, attr)
gramptr g;
attrposIndex al;
attrIndex attr;
#endif /* ! __STDC__ */
/*
	Hilfsfunktion von CrtAttrAuftr
	Sucht Attribut in einer Attributpositionsliste
	Eingaben: g   Grammatik
		  al  Anfang der Attributpositionsliste
		  attr zu suchendes Attribut
	Ausgaben: return-Wert Attributposition
	*/
{
	attrposIndex i;

	for (i = al; ; i++) {
		if (g->attrpostab[i].attr == attr)
			return(i);
		if (g->attrpostab[i].ende) break;
	}
	return(NIL);
}


#ifdef __STDC__
void CrtAttrAuftr(gramptr g,
                  productIndex p,
                  nontermIndex voc,
                  attrIndex attr,
                  int posnr,
                  aparamIndex *ap)
          
               
                 
               
          
                
#else /* ! __STDC__ */
void CrtAttrAuftr(g, p, voc, attr, posnr, ap)
gramptr g;
productIndex p;
nontermIndex voc;
attrIndex attr;
int posnr;
aparamIndex *ap;
#endif /* ! __STDC__ */
/*
	Hilfsfunktion fuer CrtAuftr und aCrtSemAuftr und fCrtSemAuftr
	Generiert aparam fuer ein Attribut-Auftreten
	Eingaben: g   Grammatik
		  p   Produktion
		  voc Vokabel
		 attr Attribut
		 posnr Positionsnummer
	Ausgaben: ap  aparam-Feld
	*/
{
	prodposIndex ppos,i;
	attrposIndex apos;

	ppos = NIL;

	/* Vokabel suchen */
	for (i = g->prodtab[p].firstprodpos; ppos==NIL ; i++) {
		if (g->prodpostab[i].vocabel == voc
		    && g->prodpostab[i].pos == posnr)
			ppos = i;

		if (g->prodpostab[i].ende) break;
	}
	if (!ppos) {
		 /* error position or vocabel */
#ifdef OldScan
		error(zeile, spalte, 11);
#else
		error(ort, 11);
#endif
		*ap = NIL;
	} 
	else {
		/* Attribut suchen */
		apos = search_alist(g, g->prodpostab[ppos].firstattrpos,attr);
		if (!apos
		    /* in der Attributliste nicht gefunden ? */
		&& !g->prodpostab[ppos].num ) {
			/* linke Seite der Produktion ? */
			/* Hilfsattribute durchsuchen */
			apos = search_alist(g, g->prodtab[p].firstauxattrpos,attr);
		}
		if (!apos) {
			 /* unknown attribut */
#ifdef OldScan
			error(zeile, spalte, 12);
#else
			error(ort, 12);
#endif
			*ap = NIL;
		} 
		else {
			*ap = newaparam(g);
			g->aparamtab[*ap].aktparam = apos;
			g->aparamtab[*ap].ende = FALSE;
		}
	}
}


#ifdef __STDC__
void fCrtSemAuftr(gramptr g, productIndex p, ident id, int n, functIndex *f)
          
               
         
      
              
#else /* ! __STDC__ */
void fCrtSemAuftr(g, p, id, n, f)
gramptr g;
productIndex p;
ident id;
int n;
functIndex *f;
#endif /* ! __STDC__ */
/*
	liefert Index einer
	semantischen Funktion ohne Argumente
	Eingaben: g   Grammatik
		  p   Produktion
		  id  Bezeichner des Terminals oder der Funktion
	Ausgaben: f   Funktion, wird NIL, falls Terminal gefunden
	*/
{
	entryIndex fe;

	if (n == -1) {
		/* Pruefe, ob es sich um eine Funktion ohne Args handelt
		   num moeglich, falls keine Positionsnummer vorhanden */
		lookup(g, id, FUNCT, &fe);
		/* lookup sucht nach FUNCT/REL Eintraegen */
		if (fe) { /* gefunden */
			*f = g->entrytab[fe].index.funct;
			return;
		}
	}
	/* es muss semantisch rel. Terminalsymbol vorliegen */
	*f = NIL;
}

#ifdef __STDC__
void aCrtSemAuftr(gramptr g, productIndex p, ident id, int n, aparamIndex *ap)
#else /* ! __STDC__ */
void aCrtSemAuftr(g, p, id, n, ap)
gramptr g;
productIndex p;
ident id;
int n;
aparamIndex *ap;
#endif /* ! __STDC__ */
/*
	Generiert aparam fuer Terminal-Auftreten 
	Eingaben: g   Grammatik
		  p   Produktion
		  id  Bezeichner des Terminals oder der Funktion
	Ausgaben: ap  aparam, wird NIL falls Funktion gefunden
	*/
{
	entryIndex fe,tentry;
	vocabelIndex voc;
	termIndex term;

	if (n == -1) {
		/* Pruefe, ob es sich um eine Funktion ohne Args handelt
		   num moeglich, falls keine Positionsnummer vorhanden */
		lookup(g, id, FUNCT, &fe);
		/* lookup sucht nach FUNCT/REL Eintraegen */
		if (fe) { /* gefunden */
			*ap = NIL;
			return;
		}
	}
	/* es muss semantisch rel. Terminalsymbol vorliegen */
	lookup(g, id, TERM, &tentry);
	if (!tentry) {
		 /* not declared */
#ifdef OldScan
		error(id.zeile, id.spalte, 4);
#else
		error(QUELL_ORT(id), 4);
#endif
		*ap = NIL;
	} 
	else {
		term = g->entrytab[tentry].index.term;
		if (!g->termtab[term].issemantic)
			 /* not semantic */
#ifdef OldScan
			error(id.zeile, id.spalte, 23);
#else
			error(QUELL_ORT(id), 23);
#endif

		voc = term + g->anznonterm;
		CrtAttrAuftr(g, p, voc, g->termtab[term].attr, n, ap);
	}
}



#ifdef __STDC__
void NoFunct(functIndex *f)
              
#else /* ! __STDC__ */
void NoFunct(f)
functIndex *f;
#endif /* ! __STDC__ */
/*
	wird bei einfachen Zuweisungen benoetigt, liefert die NIL-Funktion
	Eingaben: -
	Ausgaben: Funktionsindex
	*/
{
	*f = NIL;
}


#ifdef __STDC__
void CrtAuftr(gramptr g,
              productIndex p,
              ident i1,
              int n,
              ident i2,
              aparamIndex *ap)
          
               
         
      
         
                
#else /* ! __STDC__ */
void CrtAuftr(g, p, i1, n, i2, ap)
gramptr g;
productIndex p;
ident i1;
int n;
ident i2;
aparamIndex *ap;
#endif /* ! __STDC__ */
/*
	Generiert aparam fuer Nonterminal-Auftreten
	Eingaben: g   Grammatik
		  p   Produktion
		  i1  Bezeichner fuer Nonterminal
		  n   Positionsnummer
		  i2  Bezeichner fuer Attribut
	Ausgaben: ap  aparam-Feld
	*/
{
	entryIndex ventry,aentry;
	vocabelIndex voc;
	attrIndex attr;

	lookup(g, i1, NONTERM, &ventry);
	if (!ventry) {
		 /* not declared */
#ifdef OldScan
		error(i1.zeile, i1.spalte, 4);
#else
		error(QUELL_ORT(i1), 4);
#endif
		*ap = NIL;
	} 
	else {
		voc = g->entrytab[ventry].index.nonterm;
		lookupattr(g, i2, voc, &aentry);
		if (!aentry) {
			/* unknown Attr */
#ifdef OldScan
			error(i2.zeile, i2.spalte, 12);
#else
			error(QUELL_ORT(i2), 12);
#endif
			*ap = NIL;
		} 
		else {
			attr = g->entrytab[aentry].index.attribut;
			CrtAttrAuftr(g, p, voc, attr, n, ap);
		}
	}
}


#ifdef __STDC__
void PrefAuftr(aparamIndex left, aparamIndex right, aparamIndex *out)
                        
                 
#else /* ! __STDC__ */
void PrefAuftr(left, right, out)
aparamIndex left, right;
aparamIndex *out;
#endif /* ! __STDC__ */
/*
	Verwaltung der Aparam-Liste
	koennte auch in der Grammatik durch Attributierung erledigt werden
	Eingaben: left Anfang der 1. Aparam-Liste
		  right Anfang der 2. Aparam-Liste
	Ausgaben: out  Anfang der gesamt Aparam-Liste
	*/
{
	if (left)
		*out = left;
	else
		*out = right;
}


#ifdef __STDC__
void CrtQ(gramptr g, functIndex fun, aparamIndex ap, aufrufIndex *au)
          
               
               
                
#else /* ! __STDC__ */
void CrtQ(g, fun, ap, au)
gramptr g;
functIndex fun;
aparamIndex ap;
aufrufIndex *au;
#endif /* ! __STDC__ */
/*
	Generiert aufruf-Feld fuer Funktionsaufruf mit Parametern
	Hilfsfunktion von CrtQuelle und CrtMakeid
	Eingaben: g   Grammatik
		  fun Funktion
		  ap  Parameterliste (aparam-Felder)
	Ausgaben: au  aufruf-Feld
	*/
{
	if (ap != NIL)
		g->aparamtab[g->anzaparam].ende = TRUE;
	/* Argumentliste beenden */

	*au = newaufruf(g);
	g->aufruftab[*au].funct = fun;
	g->aufruftab[*au].firstarg = ap;
	g->aufruftab[*au].firsterg = NIL;
	g->aufruftab[*au].ende = FALSE;
}


#ifdef __STDC__
void CrtQuelle(gramptr g, ident id, aparamIndex ap, aufrufIndex *au)
          
         
               
                
#else /* ! __STDC__ */
void CrtQuelle(g, id, ap, au)
gramptr g;
ident id;
aparamIndex ap;
aufrufIndex *au;
#endif /* ! __STDC__ */
/*
	Generiert aufruf-Feld fuer Funktionsaufruf mit Parametern
	Eingaben: g   Grammatik
		  id  Funktionsname
		  ap  Parameterliste (aparam-Felder)
	Ausgaben: au  aufruf-Feld
	*/
{
	entryIndex fe;
	functIndex fun;

	lookup(g, id, FUNCT, &fe);
	if (!fe) {
		 /* funct not declared */
#ifdef OldScan
		error(id.zeile, id.spalte, 10);
#else
		error(QUELL_ORT(id), 10);
#endif
		fun = NIL;
	} 
	else {
		fun = g->entrytab[fe].index.funct;
	}
	CrtQ(g, fun, ap, au);
}


#ifdef __STDC__
void CrtMakeid(gramptr g, aparamIndex ap, functIndex f, aufrufIndex *au)
          
               
             
                
#else /* ! __STDC__ */
void CrtMakeid(g, ap, f, au)
gramptr g;
aparamIndex ap;
functIndex f;
aufrufIndex *au;
#endif /* ! __STDC__ */
/*
	Generiert aufruf-Feld fuer einfache Zuweisung   O D E R
	gibt aufruf-Feld fuer Parameterlose Funktion nach oben weiter
	Eingaben: g   Grammatik
		  ap  Parameter (NIL, falls keine Parameter)
		  f   Funktion (NIL, falls einfache Zuweisung)
	Ausgaben: au  aufruf-Feld
	*/
{
	if (f)
		CrtQ(g, f, NIL, au);
	else
		CrtQ(g, copy, ap, au);
}


#ifdef __STDC__
bool match(gramptr g, fparamIndex fdescr, aparamIndex args)
          
                   
                 
#else /* ! __STDC__ */
bool match(g, fdescr, args)
gramptr g;
fparamIndex fdescr;
aparamIndex args;
#endif /* ! __STDC__ */
/*
	Vergleicht formale mit aktueller Parameterliste
	Hilfsfunktion von CrtRule
	Eingaben: g   Grammatik
		  fdescr erster formaler Parameter
		  args   erster aktueller Parameter
	Ausgaben: true, falls Uebereinstimmung, sonst false
	*/
{
	attrIndex a;

	if (fdescr != NIL && args != NIL) {
		fdescr--;
		args--;
		do {
			fdescr++;
			args++;
			a = g->attrpostab[g->aparamtab[args].aktparam].attr;
			if(g->attrtab[a].akenn == SEMTERM) {
				/* Parameter ist sem.relev. Terminal */
				if(! CompareId(g,
				g->termtab[g->attrtab[a].voc - g->anznonterm].name,
				g->typtab[g->fparamtab[fdescr].typ].name) ) {
					return(FALSE);
				}
			} 
			else {
				/* Parameter ist Attribut */
				if(! CompareId(g,
				g->typtab[g->attrtab[a].typ].name,
				g->typtab[g->fparamtab[fdescr].typ].name) ) {
					return(FALSE);
				}
			}
		} 
		while(!g->fparamtab[fdescr].ende && !g->aparamtab[args].ende);
		return(g->fparamtab[fdescr].ende && g->aparamtab[args].ende);
	} 
	else {
		return (fdescr == NIL && args == NIL);
	}
}


#ifdef __STDC__
void CrtRule(gramptr g, aparamIndex al, aufrufIndex q, aufrufIndex *sl)
          
               
              
                
#else /* ! __STDC__ */
void CrtRule(g, al, q, sl)
gramptr g;
aparamIndex al;
aufrufIndex q;
aufrufIndex *sl;
#endif /* ! __STDC__ */
/* 
	Traegt die Ergebnisparameterliste in das Aufruffeld ein
	Vergleicht Typ und Anzahl von Parametern und Ergebnissen
	Eingaben: g   Grammatik
		  al  Ergebnisparameterliste
		  q   Aufruf-Feld
		  sl  Erzeugtes Aufruf-Feld
	*/
{
	functIndex f;
	aparamIndex pl;
	attrIndex a,b;
	attrposIndex ap;

	pl = g->aufruftab[q].firstarg;
	f = g->aufruftab[q].funct;

	if (pl != NIL)
		g->aparamtab[pl-1].ende = TRUE; /* Ergebnisliste beenden */
	else if (al != NIL)
		g->aparamtab[g->anzaparam].ende = TRUE;

	/* Ergebnisparameterliste eintragen */
	g->aufruftab[q].firsterg = al;

	if(g->functtab[f].iscopy && al && pl) {
		/* einfache Zuweisung */
		a = g->attrpostab[g->aparamtab[pl].aktparam].attr; /* 1.arg */
		b = g->attrpostab[g->aparamtab[al].aktparam].attr; /* 1.erg */
		if(g->attrtab[a].akenn == SEMTERM) {
			/* rechte Seite = sem.rel. Terminal */
			/* => Vergleich von Typname und Terminalname */
			if(! CompareId(g,
			g->termtab[g->attrtab[a].voc - g->anznonterm].name,
			g->typtab[g->attrtab[b].typ].name) ) {
				 /* type mismatch */
#ifdef OldScan
				error(zeile, spalte, 17);
#else
				error(ort, 17);
#endif
			}
		} 
		else {
			/* rechte Seite = Nonterminal */
			/* => Vergleich der beiden Typnamen */
			if(! CompareId(g,
			g->typtab[g->attrtab[a].typ].name,
			g->typtab[g->attrtab[b].typ].name) ) {
				 /* type mismatch */
#ifdef OldScan
				error(zeile, spalte, 17);
#else
				error(ort, 17);
#endif
			}
		}
	} 
	else if(f) {
		/* Funktionsaufruf => Vergleich mit match-Funktion */
		if (!match(g, g->functtab[f].firstarg, pl)) {
			 /* parameter mismatch */
#ifdef OldScan
			error(zeile, spalte, 15);
#else
			error(ort, 15);
#endif
		}
		if (!match(g, g->functtab[f].firsterg, al)) {
			 /* result mismatch */
#ifdef OldScan
			error(zeile, spalte, 16);
#else
			error(ort, 16);
#endif
		}
	}
	/* Firstrule initialisieren entfaellt */			

	/* pruefe Attributrichtungen der linken Seite */

	if (al != NIL) do {
		ap = g->aparamtab[al].aktparam;	/* attrpos des aparams */
		a = g->attrpostab[ap].attr;	/* attribut der attrpos */
		if (g->prodpostab[g->attrpostab[ap].prodpos].num == 0) {
			/* auf der linken Seite der Produktion */
			if (g->attrtab[a].akenn == INHERITED) {
				attrposerror(g, ap, 20); /* inh attr
											not allowed here */
			}
		} 
		else {
			/* auf der rechten Seite der Produktion */
			if (g->attrtab[a].akenn == SYNTHESIZED) {
				attrposerror(g, ap, 19); /* syn attr
											not allowed here */
			}
		}
	} 
	while(!g->aparamtab[al++].ende);
	*sl = q;
}	


#ifdef __STDC__
void PrefixRule(aufrufIndex left, aufrufIndex right, aufrufIndex *out)
                        
                 
#else /* ! __STDC__ */
void PrefixRule(left, right, out)
aufrufIndex left, right;
aufrufIndex *out;
#endif /* ! __STDC__ */
/*
	Verwaltung der Aufruf-Liste
	aktuelle Aufrufliste = Bereich von left/out bis g->anzaufruf
	koennte auch in der Grammatik durch Attributierung geloest werden
	Eingaben: left Anfang der 1. Aufrufliste
		  right Anfang der 2. Aufrufliste
	Ausgaben: out Anfang der Gesamtaufrufliste
	*/
{
	if (left)
		*out = left;
	else
		*out = right;
}


#ifdef __STDC__
int count_assign(gramptr g, productIndex p, attrposIndex a)
          
               
               
#else /* ! __STDC__ */
int count_assign(g, p, a)
gramptr g;
productIndex p;
attrposIndex a;
#endif /* ! __STDC__ */
/*
	Zaehlt Vorkommnisse des Attributs a auf der linken Seite von Regeln in p
	Hilfsfunktion von chk_assign
	Eingaben: g   Grammatik
		  p   Produktion
		  a   Attribut
	Ausgaben: Zahl des Auftretens
	*/
{
	int n;
	aufrufIndex aufr;
	aparamIndex attr;

	n = 0;
	aufr = g->prodtab[p].firstaufruf;
	if (aufr != NIL) do {
		attr = g->aufruftab[aufr].firsterg;
		if (attr != NIL) do {
			if ( a == g->aparamtab[attr].aktparam) {
				n++;
			}
		} 
		while (!g->aparamtab[attr++].ende);
	} 
	while (!g->aufruftab[aufr++].ende);
	return(n);
}


#ifdef __STDC__
void chk_assign(gramptr g, productIndex p, prodposIndex pp, attrkenn d)
          
               
                
           
#else /* ! __STDC__ */
void chk_assign(g, p, pp, d)
gramptr g;
productIndex p;
prodposIndex pp;
attrkenn d;
#endif /* ! __STDC__ */
/*
	Prueft, ob fuer jedes Attribut von pp mit Richtung d genau eine
	semantische Regel in der Produktion p existiert
	Hilfsfunktion von chk_completeness
	Eingaben: g   Grammatik
		  p   Produktion
		  pp  Produktionsposition
		  d   Richtung
	Ausgaben: -
	*/
{
	attrposIndex ap;
	attrIndex at;
	int count;

	ap = g->prodpostab[pp].firstattrpos;
	if (ap != NIL) do {
		at = g->attrpostab[ap].attr;
		if (g->attrtab[at].akenn == d) {
			count = count_assign(g, p, ap);
			if (count == 0)
				attrposerror(g, ap, 14);
			else if (count > 1)
				attrposerror(g, ap, 13);
		}
	} 
	while (!g->attrpostab[ap++].ende);
}


#ifdef __STDC__
void chk_completeness(gramptr g, productIndex p)
          
               
#else /* ! __STDC__ */
void chk_completeness(g, p)
gramptr g;
productIndex p;
#endif /* ! __STDC__ */
/*
	Prueft Vollstaendigkeit einer Produktion
	Hilfsfunktion von EnterRules und NoRules
	Eingaben: g   Grammatik
		  p   Produktion
	Ausgaben: -
	*/
{
	prodposIndex pp;
	attrposIndex ap;
	int count;

	/* ueberpruefe semantische Aktionen auf Vollstaendigkeit */

	/* 1. synthesized Attribute der linken Seite */
	pp = g->prodtab[p].firstprodpos;
	if (pp == NIL)
		return;
	chk_assign(g, p, pp, SYNTHESIZED);

        /*2. Auxiliaries */
        ap=g->prodtab[p].firstauxattrpos;
        if (ap != NIL ) do {
                count = count_assign(g, p, ap);
                if (count == 0)
                        attrposerror(g, ap, 14);
                else if (count > 1)
                        attrposerror(g, ap, 13);
                } while (!g->attrpostab[ap++].ende);

	/* 3. inherited Attribute der rechten Seite */
	while (!g->prodpostab[pp++].ende) {
		if(g->prodpostab[pp].vocabel <= g->anznonterm) {
			/* NONTERMINAL */
			chk_assign(g, p, pp, INHERITED);
		}
	} 
	;
}


#ifdef __STDC__
void EnterRules(gramptr g, productIndex p, aufrufIndex s, gramptr *out)
          
               
              
             
#else /* ! __STDC__ */
void EnterRules(g, p, s, out)
gramptr g;
productIndex p;
aufrufIndex s;
gramptr *out;
#endif /* ! __STDC__ */
/*
	traegt semantische Regeln in Produktion ein
	testet Vollstaendigkeit der semantischen Regeln
	Eingaben: g  Grammatik
		  p  Produktion
		  s  aufruf-Liste fuer sem.Regeln
	Ausgaben: out Grammatik
	*/
{

	/* Liste abschliessen */
	g->aufruftab[g->anzaufruf].ende = TRUE;
	/* und eintragen */
	g->prodtab[p].firstaufruf = s;

	chk_completeness(g, p);
	*out = g;
}


#ifdef __STDC__
void NoRules(gramptr g, productIndex p, gramptr *out)
          
               
             
#else /* ! __STDC__ */
void NoRules(g, p, out)
gramptr g;
productIndex p;
gramptr *out;
#endif /* ! __STDC__ */
/*
	testet Vollstaendigkeit einer Produktion ohne semantische Regeln
	Eingaben: g   Grammatik
		  p   Produktion
		  out Grammatik
	*/
{
	chk_completeness(g, p);
	*out = g;
}

#ifdef __STDC__
void SecondAttr(attrIndex a1, attrIndex a2, attrIndex *out)
          
               
             
#else /* ! __STDC__ */
void SecondAttr(a1, a2, out)
attrIndex a1;
attrIndex a2;
attrIndex *out;
#endif /* ! __STDC__ */
/*
        Dummy-Prozedur zur Erzielung benoetigter Attributabhaengigkeiten
	liefert den zweiten Parameter als Ergebnis
	*/
{
	*out = a2;
}


/* ACHTUNG: Ergebnistyp falsch */
#ifdef __STDC__
void WarnMehrfErg(void)
{
#else /* ! __STDC__ */
void WarnMehrfErg()
 {
#endif /* ! __STDC__ */
#ifdef OldScan
		error(zeile, spalte, 24);
#else
		error(ort, 24);
#endif
 } /* WarnMehrfErg */
