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
/* LRKsets.h   :                                                          */
/* LR(k)-Parser-Generator                                                 */
/* Deklarationen Mengenoperationen                                        */
/* Aenderung : 01.07.89, Typ Termset ergaenzt                             */
/* Aenderung : 4.3.89                                                     */
/* erstellt  : 30.1.89                                                    */
/* ********************************************************************** */

#ifndef LRKSETS_H
#define LRKSETS_H

/* ========================================================================= */
/* Datenstrukturen                                                           */
/* ========================================================================= */
typedef unsigned long Mbastyp;  /* Basistyp fuer Bitmaps          */

 /* Shiftcount, Verschiebung um ld(Anzahl bits in Mbastyp)          */ 
#define MSHIFT 5

 /* Maske, Maskierung der untersten ld(Anzahl bits in Mbastyp) Bit  */ 
#define MMASK 31

typedef Mbastyp *Nontset;        /* Zeiger auf Bitmap der Elemente */
typedef Mbastyp *Termset;        /* Zeiger auf Bitmap der Elemente */

/* ========================================================================= */
/* Test der Zugehoerigkeit eines Element zu einer Nonterminalmenge           */
/* ========================================================================= */
#ifdef __STDC__
BOOL inNset(Nont,Nontset);
#else
BOOL inNset();
#endif
/* ========================================================================= */
/* Aufnahme eines Element in eine Nonterminalmenge                           */
/* ========================================================================= */
#ifdef __STDC__
void inclNset(Nont,Nontset);
#else
void inclNset();
#endif

/* ========================================================================= */
/* Speicherresevierung fuer Nonterminalmenge                                 */
/* ========================================================================= */
#ifdef __STDC__
void emptyNset(Nontset);
#else
void emptyNset();
#endif
/* ========================================================================= */
/* Speicherresevierung fuer Nonterminalmenge                                 */
/* ========================================================================= */
#ifdef __STDC__
void getNset(Nontset*);
#else
void getNset();
#endif
/* ========================================================================= */
/* Speicherfreigabe fuer Nonterminalmenge                                    */
/* ========================================================================= */
#ifdef __STDC__
void freeNset(Nontset);
#else
void freeNset();
#endif
/* ========================================================================= */
/* Test der Zugehoerigkeit eines Element zu einer Terminalmenge              */
/* ========================================================================= */
#ifdef __STDC__
BOOL inTset(Term,Termset);
#else
BOOL inTset();
#endif
/* ========================================================================= */
/* Aufnahme eines Element in eine Terminalmenge                              */
/* ========================================================================= */
#ifdef __STDC__
void inclTset(Term,Termset);
#else
void inclTset();
#endif
/* ========================================================================= */
/* Speicherresevierung fuer Terminalmenge                                    */
/* ========================================================================= */
#ifdef __STDC__
void emptyTset(Termset);
#else
void emptyTset();
#endif
/* ========================================================================= */
/* Speicherresevierung fuer Terminalmenge                                    */
/* ========================================================================= */
#ifdef __STDC__
void getTset(Termset*);
#else
void getTset();
#endif
/* ========================================================================= */
/* Speicherfreigabe fuer Terminalmenge                                       */
/* ========================================================================= */
#ifdef __STDC__
void freeTset(Termset);
#else
void freeTset();
#endif
#endif
