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
/* allocate.h  :                                                          */
/* Header fuer allgemeine Speicherverwaltungsroutinen                     */
/* die verwalteten Typen muessen im ersten Feld einen Pointer enthalten,  */
/* der zur Freilistenverkettung verwendet wird                            */
/* Aenderung  : 12.04.90, #ifdef __STDC__                                 */
/* Aenderung  : 20.2.89 , __ARGS-Definitionen                             */
/* erstellt   : 28.1.89                                                   */
/* ********************************************************************** */

#ifndef ALLOCATE_H
#define ALLOCATE_H

/* ====================================================================== */
/* Speicherreservierung fuer einen gegebenen Typen                        */
/* unter Beruecksichtigung einer Freiliste                                */ 
/* falls Reservierung nicht moeglich, Rueckgabe von NULL                  */
/* um Overhead und Speicherfragmentierung zu verringern, werden immer     */
/* POOL Elemente gleichzeitig mit malloc() reserviert                     */
/* ====================================================================== */
#ifdef __STDC__
char *flAllocate(unsigned size, char **fl);
#else
char *flAllocate();
#endif

/* ====================================================================== */
/* Speicherfreigabe fuer ein Element eines gegebenen Typen                */
/* Eintrag in Freiliste                                                   */ 
/* ====================================================================== */
#ifdef __STDC__
void flFree(char **el,char **fl);
#else
void flFree();
#endif

/* ====================================================================== */
/* Speicherfreigabe fuer eine Liste eines gegebenen Typen                 */
/* Eintrag in Freiliste                                                   */ 
/* ====================================================================== */
#ifdef __STDC__
void flFreelis(char **lis, char **fl);
#else
void flFreelis();
#endif
#endif
