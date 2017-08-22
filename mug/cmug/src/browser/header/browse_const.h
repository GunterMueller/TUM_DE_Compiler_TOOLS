#ifndef BROWSE_CONST_H
#define BROWSE_CONST_H

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
/* Allgemeine Konstante							*/
/************************************************************************/
#define MINIMUM		-1000000
#define MAXIMUM		1000000

#define	MAX(x,y)	((x>y) ? x : y)
#define	MIN(x,y)	((x<y) ? x : y)


/************************************************************************/
/* Konstante zur Darstellung von Images					*/
/************************************************************************/
#define IMAGE_WIDTH	16
#define IMAGE_HWIDTH	8
#define IMAGE_HEIGHT	16
#define IMAGE_HHEIGHT	8
#define IMAGE_SPACE	5
#define IMAGE_Y_SPACE	15
#define	IMAGE_BORDER	10


/************************************************************************/
/* Konstante und Makros zur Darstellung von Produktionen		*/
/************************************************************************/
#define PROD_HEIGHT	200
#define PROD_SPACE	60


/************************************************************************/
/* Knoten								*/
/************************************************************************/
#define KNOTEN_WIDTH(x)	(x*9 + 4)
#define KNOTEN_HEIGHT	20
#define KNOTEN_HHEIGHT	10
#define RECT_WIDTH(x)	(x*9 + 4)
#define HALFW_RECT(x)	((x*9)/2 + 2)


/************************************************************************/
/* Konstante und Makros zur Darstellung von semantischen Aktionen	*/
/************************************************************************/
#define SEM_HEIGHT	16
#define SEM_HHEIGHT	8
#define SEM_X_SPACE	50
#define SEM_Y_SPACE	20
#define SEM_WIDTH(x)	(x*10 + 4)


/************************************************************************/
/* Buchstaben								*/
/************************************************************************/
#define BIG_LETTER_H	15
#define SM_LETTER_H	12
#define BIG_HW_LET(x)	((x*9)/2)
#define SM_HW_LETTER(x)	(x*3)


/************************************************************************/
/* Attribute								*/
/************************************************************************/
#define ATTR_NAME	((L_ATTRIBUT+11)*9)
#define ATTR_SPACE	10
#define ATTR_YOFFSET	20
#define ATTR_VP_W	320
#define SCROLL_SIZE	16
#define ATTR_YDIAOFF	41


/************************************************************************/
/* Konstanten zur Ausrichtung des Baumes				*/
/************************************************************************/
#define X_START		0
#define Y_START		0


/************************************************************************/
/* Abhaengigkeitspfeile							*/
/************************************************************************/
#define DEP_Y_SPACE	2
#define ARROW_LENGTH	5
#define ARROW_WIDTH	2
#define ARROW_DIA	4
#define ARROW_DIAW	1
#define COPY_LOOP	20
#define OBEN   		0
#define UNTEN   	1
#define RECHTS  	2
#define LINKS   	3
#define DIST		3
#define BLACK		0
#define RED		1


/************************************************************************/
/* Global View								*/
/************************************************************************/
#define GV_FAKTOR	10

#endif
