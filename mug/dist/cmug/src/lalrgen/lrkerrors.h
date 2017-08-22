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
/* LRKerrors.h   :                                                        */
/* LR(k)-Parser-Generator                                                 */
/* Deklarationen fuer Fehlermeldungen                                     */
/* Aenderung : 16.12.89, alleKonflikte()                                  */
/* Aenderung : 02.07.89, Meldungen erweitert                              */
/* erstellt  : 23.1.89                                                    */
/* ********************************************************************** */

#ifndef LRKERRORS_H
#define LRKERRORS_H

#include "grammar.h"           /* Deklaration einiger Argumenttypen */
#include "lrkzust.h"           /* Deklaration einiger Argumenttypen */

/* ====================================================================== */
/* Ausgabe einer allgemeinen Fehlermeldung, nur Format                    */
/* ====================================================================== */
#ifdef __STDC__
void Error0(char*);
#else
void Error0();
#endif
/* ====================================================================== */
/* Ausgabe einer allgemeinen Fehlermeldung, Format + 1 String             */
/* ====================================================================== */
#ifdef __STDC__
void Error1(char*,char*);
#else
void Error1();
#endif
/* ====================================================================== */
/* Fehlermeldung : spontane Uebergaenge noetig bei Lookahead 0            */
/* ====================================================================== */
#ifdef __STDC__
void epsError(Zustand);
#else
void epsError();
#endif
/* ====================================================================== */
/* Ausgabe eines Uebergangs innerhalb eines Konfliktes                    */
/* ====================================================================== */
#ifdef __STDC__
void konfUeb(Ueberg);
#else
void konfUeb();
#endif
/* ====================================================================== */
/* Ausgabe des Zustandes am Anfang von Konflikten                         */
/* ====================================================================== */
#ifdef __STDC__
void konfStart(Zustand);
#else
void konfStart();
#endif
/* ====================================================================== */
/* mault, wenn aus einem Nonterminal keine terminale Zeichenreihe         */
/* herleitbar ist                                                         */
/* ====================================================================== */
#ifdef __STDC__
void mauleTerm(Nont);
#else
void mauleTerm();
#endif
/* ====================================================================== */
/* mault, wenn ein Nonterminal nicht benoetigt wird                       */
/* ====================================================================== */
#ifdef __STDC__
void mauleBenutzt(Nont);
#else
void mauleBenutzt();
#endif
/* ====================================================================== */
/* mault, wenn eine Produktion nicht reduziert wird                       */
/* ====================================================================== */
#ifdef __STDC__
void mauleReduce(Prod);
#else
void mauleReduce();
#endif
/* ====================================================================== */
/* Fehlermeldung und Programmabbruch bei unzureichendem Arbeitsspeicher   */
/* ====================================================================== */
void mAbort();

/* ====================================================================== */
/* Prueft Uebergang auf reine Aktionskonflikte und gibt diese aus,        */
/* falls die -a Option verwendet wurde                                    */
/* Rueckgabe TRUE, falls ausschliesslich Aktions-Konflikte vorhanden      */
/* ====================================================================== */
#ifdef __STDC__
BOOL aktKonflikte(Ueberg);
#else
BOOL aktKonflikte();
#endif
 /* ======================================================== */
/* Ausgabe der Tabelle aller Konflikte                       */
/* Rueckgabe : Gesamtzahl aller Konflikte (ohne Warnungen)   */
/* ========================================================= */
int alleKonflikte();

#endif
