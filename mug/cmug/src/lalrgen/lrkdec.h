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
/* LRKdec.h  :                                                            */
/* LR(k)-Parser-Generator                                                 */
/* Header fuer Dekoder                                                    */
/* Aenderung        : 24.10.90 ANSIfiziert                                */
/* erstellt         : 27.1.89                                             */
/* ********************************************************************** */

#ifndef LRKDEC_H
#define LRKDEC_H

#include "defs.h"            /* diverse unspezifische Definitionen        */
#include "grammar.h"         /* Definition der Datenstruktur              */
#include "lrkzust.h"         /* Datentypen einiger Argumente              */

/* ========================================================================= */
/* Dekodierung eines Terminalsymbols                                         */
/* Rueckgabe : Zeiger auf dekodierte Zeichenreihe                            */
/* ========================================================================= */
#ifdef __STDC__
char *decTerm(Term);
#else
char *decTerm();
#endif
/* ========================================================================= */
/* Dekodierung eines Nonterminalsymbols                                      */
/* Rueckgabe : Zeiger auf dekodierte Zeichenreihe                            */
/* ========================================================================= */
#ifdef __STDC__
char *decNont(Nont);
#else
char *decNont();
#endif
/* ========================================================================= */
/* Dekodierung eines Symbols                                                 */
/* Rueckgabe : Zeiger auf dekodierte Zeichenreihe                            */
/* ========================================================================= */
#ifdef __STDC__
char *decSym(Symb);
#else
char *decSym();
#endif
/* ========================================================================= */
/* Dekodiert ein Item einer Produktion, Position wird mit '|' markiert       */
/* Ausgabe auf die Datei file                                                */
/* ========================================================================= */
#ifdef __STDC__
void fdecItem(FILE*,Item);
#else
void fdecItem();
#endif
/* ========================================================================= */
/* Dekodiert einen Uebergang                                                 */
/* Ausgabe auf die Datei file                                                */
/* ========================================================================= */
#ifdef __STDC__
void fdecUeb(FILE*,Ueberg);
#else
void fdecUeb();
#endif
/* ========================================================================= */
/* Dekodiert Uebergangsinformation (ohne Symbol )                            */
/* Ausgabe auf die Datei file                                                */
/* ========================================================================= */
#ifdef __STDC__
void fdecUebinf(FILE*,Ueberg);
#else
void fdecUebinf();
#endif

#endif

