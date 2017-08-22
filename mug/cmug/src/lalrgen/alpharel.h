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
/* Alpharel.h   :                                                         */
/* LR(k)-Parser-Generator                                                 */
/* Deklarationen Anspruenge und Alpha(k)-Relation                         */
/* Aenderung : 28.10.89, forAlphaeps()                                    */
/* Aenderung : 30.06.89, ueberarbeitet wg. LRKsim                         */
/* Aenderung : 9.3.89 , auszufuehrende Routine nicht als Argument         */
/* erstellt   : 30.1.89                                                   */
/* ********************************************************************** */

#ifndef ALPHAREL_H
#define ALPHAREL_H

/* =================== */
/* Aufgerufene Routine */
/* =================== */
#ifdef __STDC__
void firstTerm(Symb);
#else
void firstTerm();
#endif

/* ========================================================================== */
/* Berechnung aller des ersten Terminalzeichens, das aus dem Nonterminal nont */
/* hergeleitet werden kann                                                    */
/* Fuer jedes gefundene Symbol wird firstTerm() aufgerufen                    */
/* ========================================================================== */
#ifdef __STDC__
void forAlphaeps(Nont);
#else
void forAlphaeps();
#endif
/* ========================================================================== */
/* Berechnung aller items, die zum Erzeugen des Nonterminals nont             */
/* angesprungen werden muessen (=linke Seiten der angesprungenen Produktionen */
/* Fuer jedes gefundene Item wird shiftAnf() aufgerufen                       */
/* ========================================================================== */
#ifdef __STDC__
void forAnsprung(Nont);
#else
void forAnsprung();
#endif
/* ========================================================================== */
/* Initialisierung dieses Moduls                                              */
/* ========================================================================== */
#ifdef __STDC__
void initAlpharel(void);
#else
void initAlpharel();
#endif

#endif
