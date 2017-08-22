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
/* Magics.h   :                                                           */
/* Magische Zahlen zur Identifizierung von Dateien                        */
/* Aenderung        : 09.11.89   MAGIC_LR_TAB                             */
/* erstellt         : 20.2.89                                             */
/* ********************************************************************** */

                                                    
/* Grammatikinternform : Chomsky2-Grammatik mit Aktionen */
#define MAGIC_CH2_GRM 0x81235431L
                                                 
/* Binaertabelle fuer LR-Parser                          */
#define MAGIC_LR_TAB  0x81236400L
