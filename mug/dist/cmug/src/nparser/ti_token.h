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
/* ti_token.h :                                                */
/* Parser-lokale Version von token.h                           */
/* erstellt  11.01.91, Ulrich Vollath                          */
/* *********************************************************** */

#ifndef TI_TOKEN_H
#define TI_TOKEN_H
typedef long *Token;   /* nur erstes Feld bekannt 	        */
#ifdef __STDC__
typedef void Quellort; /* nur fuer wErrorf, als NULL uebegeben  */
#else
typedef long Quellort; /* nur fuer wErrorf, als NULL uebergeben */
#endif
#define SYM(tok) *(tok)
#endif
