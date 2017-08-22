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
/* LRKread.h   :                                                          */
/* LR(k)-Parser-Generator                                                 */
/* Headerfile fuer Einleser fuer Grammatikinternform                      */
/* erstellt   : 23.1.89                                                   */
/* ********************************************************************** */

#ifndef LRKREAD_H
#define LRKREAD_H

/*====================================================================== */
/* Einlesen der Grammatikinternform aus der Datei edatei_name             */
/*   Rueckgabewert : TRUE, falls Einlesen erfolgreich                     */
/*                   FALSE, falls Fehler beim Einlesen                    */
/*====================================================================== */
#ifdef __STDC__
BOOL readInternform(char *edatei_name);
#else
BOOL readInternform( /*  char *  */);
#endif

#endif
