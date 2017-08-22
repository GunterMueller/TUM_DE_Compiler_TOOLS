#ifndef BROWSE_DS_H
#define BROWSE_DS_H

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
/* Struktur fuer G-Satz							*/
/*									*/
/************************************************************************/
struct argument
	{
	char attr[L_ATTRIBUT];
	char art;
	char symbol[L_SYMBOL];
	int id;
	};


/************************************************************************/
/* Struktur fuer F-Satz							*/
/*									*/
/************************************************************************/
struct funktion 
	{
	char aktion[L_SEMACTION];
	int id;
	};


/************************************************************************/
/* Struktur fuer H-Satz							*/
/*									*/
/************************************************************************/
struct header
	{
	char filename[L_FILENAME];
	};


/************************************************************************/
/* Struktur fuer T-Satz							*/
/*									*/
/* enthaelt keine Information						*/
/************************************************************************/
struct trailer	
	{
	char dummy;
	};


/************************************************************************/
/* Struktur fuer V-Satz							*/
/*									*/
/************************************************************************/
struct vater	
	{
	char symbol[L_SYMBOL];
	int id;
	};


/************************************************************************/
/* Struktur fuer S-Satz							*/
/*									*/
/************************************************************************/
struct sohn	
	{
	char symbol[L_SYMBOL];
	int id;
	int is_terminal;
	};


/************************************************************************/
/* Struktur fuer P-Satz							*/
/*									*/
/* enthaelt keine Information						*/
/************************************************************************/
struct prod_end 
	{
	char dummy;
	};


/************************************************************************/
/* Struktur fuer A-Satz							*/
/*									*/
/************************************************************************/
struct attribut 
	{
	char art;
	char attr[L_ATTRIBUT];
	char typ[L_ATTR_TYP];
	int wertlen;
	int is_copy;
	};


/************************************************************************/
/* Struktur fuer E-Satz							*/
/*									*/
/* enthaelt keine Information						*/
/************************************************************************/
struct end_attr 
	{
	char dummy;
	};
	

/************************************************************************/
/* Union ueber alle Strukturen						*/
/*									*/
/* diese Union wird gelesen und geschrieben				*/
/************************************************************************/
union satz_info
	{
	struct header 	h;
	struct trailer	t;
	struct vater	v;
	struct sohn	s;
	struct prod_end p;
	struct attribut a;
	struct argument	g;
	struct end_attr e;
	struct funktion f;
	};

#endif
