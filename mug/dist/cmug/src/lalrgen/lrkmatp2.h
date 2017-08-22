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
/* LRKmatP2.h   :                                                         */
/* LR(k)-Parser-Generator                                                 */
/* Header fuer Generierung der Uebergangsmatrix, Pass 2                   */
/* Aenderung  : 27.10.89 , ueberarbeitet wg. LRKkont                      */
/* erstellt   : 6.3.89                                                    */
/* ********************************************************************** */

#ifndef LRKMATP2_H
#define LRKMATP2_H

/*====================================================================== */
/* Eintragen eines Lookaheads in einen Uebergang                          */
/*====================================================================== */
#ifdef __STDC__
void enterLook(Term);
#else
void enterLook();
#endif
/*====================================================================== */
/* Uebergaenge eines Zustandes des fertigen LR(0)-Automaten berechnen     */
/*====================================================================== */
#ifdef __STDC__
void zUebergaenge(Zustand);
#else
void zUebergaenge();
#endif
#ifdef INCATTR
#ifdef __STDC__
void zUebergaenge2(Zustand);
void berechneLooks(void);
#else
void zUebergaenge2();
void berechneLooks();
#endif

#endif
#endif
