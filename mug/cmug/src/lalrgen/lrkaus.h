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
/* LRKaus.h   :                                                           */
/* LR(k)-Parser-Generator                                                 */
/* Headerfile fuer Ausgabemodul                                           */
/* erstellt   : 23.1.89                                                   */
/* ********************************************************************** */

#ifndef LRKAUS_H
#define LRKAUS_H

#ifdef __STDC__
BOOL LRKmat_ausgabe(char *);
BOOL LRKmat_ausgabe1(char *);
#else
BOOL LRKmat_ausgabe();
BOOL LRKmat_ausgabe1();
#endif



#endif
