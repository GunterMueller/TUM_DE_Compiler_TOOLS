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
/* ti_read.h :                                                            */
/* LR(k)-Parser-Tabellen-Interpreter                                      */
/* Deklarationen Einlesen der Tabelle                                     */
/* ---------------------------------------------------------------------- */
/* erstellt  : 08.07.89                                                   */
/* ********************************************************************** */

#ifndef TI_READ_H
#define TI_READ_H

/* ========================================================= */
/* Einlesen einer Parsertabelle                              */
/* Rueckgabe : != 0, falls erfolgreich eingelesen           */
/* ========================================================= */
#ifdef __STDC__
int readPtab(char*,Ptab *);
#else
int readPtab();
#endif
/* ========================================================= */
/* Speicherfreigabe Parsertabelle                            */
/* ========================================================= */
#ifdef __STDC__
void freePtab(Ptab *);
#else
void freePtab();
#endif

/* ========================================================= */
/* Tabelle als C-Datenstruktur ausgeben                      */
/* ========================================================= */
#ifdef __STDC__
void cDump(FILE *dfile,Ptab *tab);
#else
void cDump();
#endif

/* ========================================================= */
/* Datentypgroessen als C-Defines ausgeben                   */
/* ========================================================= */
#ifdef __STDC__
void cDefines(FILE *dfile,Ptab *tab);
#else
void cDefines();
#endif

#endif

