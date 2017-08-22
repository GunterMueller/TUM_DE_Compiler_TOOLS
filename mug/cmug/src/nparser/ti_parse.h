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
/* ti_parse.h :                                                           */
/* LR(k)-Parser-Tabellen-Interpreter                                      */
/* Deklarationen eigentlicher Interpreter                                 */
/* ---------------------------------------------------------------------- */
/* erstellt  : 09.07.89                                                   */
/* ********************************************************************** */
#ifndef TI_PARSE_H
#define TI_PARSE_H

/* ===================================================================== */
/* eigentliche Parserroutine                                             */
/* Rueckgabewert : 0, falls Syntaxanalyse abgebrochen                    */
/*              != 0, falls (inkl. Fehlerbehandlung) Satz gelesen        */
/* ===================================================================== */
#ifdef __STDC__
int ti_parse(Ptab *tab,int (*scan)(Token),
             int (*outred)(long,long,long),int (*outterm)(Token) );
#else
int ti_parse();
#endif

#endif /* TI_PARSE_H */
