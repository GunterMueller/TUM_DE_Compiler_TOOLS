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
/* LRKmat.h   :                                                           */
/* LR(k)-Parser-Generator                                                 */
/* Header fuer Generierung der Uebergangsmatrix                           */
/* Aenderung  : 01.07.89, ueberarbeitet wg. LRKsim                        */
/* Aenderung  : 11.3.89 , Datentyp Pueblis als Keller ausprogrammiert     */
/* erstellt   : 23.1.89                                                   */
/* ********************************************************************** */

#ifndef LRKMAT_H
#define LRKMAT_H

#include "listen.h" 
#include "lrkzust.h"

/* ============================================================= */
/* Datenstrukturen                                               */
/* ============================================================= */
#define NONTINVUEB(n) nontinvuebs[(n)-MINN].ueb
#define NONTINVVON(n) nontinvuebs[(n)-MINN].von
#define NONTINVBIS(n) nontinvuebs[(n)-MINN].bis

/*====================================================================== */
/* Suchen eines Uebergangs mit einem Nonterminal-Symbol in einem Zustand */
/*====================================================================== */
#ifdef __STDC__
Ueberg sucheUeb(Zustand,Symb);
#else
Ueberg sucheUeb();
#endif
/*====================================================================== */
/* Uebergang zu einem Item in die provisorische Uebergangsliste eintragen */
/* globale Routine, wird auch von forAnsprung aufgerufen                  */
/*====================================================================== */
#ifdef __STDC__
void doUeb(Item);
#else
void doUeb();
#endif
/*====================================================================== */
/* Generierung der Uebergangsmatrix                                       */
/*   Rueckgabewert :  TRUE, falls erfolgreich                             */
/*                    FALSE, falls Fehler beim Generieren                 */
/*====================================================================== */
#ifdef __STDC__
BOOL LRKgen(void);
#else
BOOL LRKgen();
#endif

#endif
