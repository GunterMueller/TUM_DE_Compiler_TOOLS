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
/* LRKkont.h   :                                                          */
/* LR(k)-Parser-Generator                                                 */
/* Deklarationen fuer LALR-Kontextberechnung                              */
/* erstellt  :  28.10.89, vorerst fuer k = 1                              */
/* ********************************************************************** */

#ifndef LRKKONT_H
#define LRKKONT_H
/* ========================================================================= */
/* Berechnung aller terminalen Symbole, die folgen koennen, nachdem im       */
/* Zustand der spontane Uebergang ueb ausgefuehrt wurde                      */
/* fuer jedes gefundene Symbol gsym wird enterLook(gsym) aufgerufen          */ 
/* ========================================================================= */
#ifdef __STDC__
void lrkKontext(Zustand,Ueberg);
#else
void lrkKontext();
#endif
/* ========================================================================== */
/* Initialisierung dieses Moduls                                              */
/* ========================================================================== */
#ifdef __STDC__
void initLRKkont(void);
#else
void initLRKkont();
#endif

#endif /* LRKKONT_H */

