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


/* *********************************************** */
/* lrklook.h:                                      */
/* Deklarationen Datenstruktur Lookaheadset        */
/* erstellt:  14.10.1990 (Ulrich Vollath)          */
/* *********************************************** */
#ifndef LOOK_H
#define LOOK_H

extern int max_lookahead;  /* Parameter der Datenstruktur    */

/* =================================================== */
/* Datentyp: Lookaheadset + Prozeduren                 */
/* implementiert als Baum, Knoten mit                  */
/* Terminalzeichen markiert.                           */
/* Terminalzeichen EOLOOK terminiert einen Lookahead   */
/* =================================================== */
#define EOLOOK (MAXT+1)
typedef struct LooksetR *Lookset;
typedef struct LooksetR {
			Lookset rest;   /* Rest dieses Strings */
			Lookset others; /* weitere Strings     */
			Term    val;    /* Zeichen im Knoten   */
			} LooksetRec;

/* ======================================================== */
/* Ausgabe eines Lookaheadset <set> in Externdarstellung    */
/* in die Datei <f>                                         */
/* ======================================================== */
#ifdef __STDC__
void printLookset(FILE *f,Lookset set);
#else
void printLookset();
#endif
/* ======================================================== */
/* traegt Zeichen in Lookaheadset ein                       */
/* Rueckgabe: Zeiger auf Eintrag mit dem Zeichen            */
/* ======================================================== */
#ifdef __STDC__
Lookset enterLookset(Term c,Lookset *set);
#else
Lookset enterLookset();
#endif
/* ================================================== */
/* Vergleich zweier Lookaheadsets                     */
/* Rueckgabe != 0 bei Gleichheit                      */
/* ================================================== */
#ifdef __STDC__
int gleichLookset(Lookset set1,Lookset set2);
#else
int gleichLookset();
#endif
/* ======================================================== */
/* vereinigt Lookaheadset <*dest> um die Elemente aus <src> */
/* Rueckgabe: Lookaheadset hat sich geaendert               */
/* ======================================================== */
#ifdef __STDC__
int unionLookset(Lookset *dest, Lookset src);
#else
int unionLookset();
#endif
/* ========================================================== */
/* Berechnung des konkatenierten Lookaheadsets <src>          */
/* paarweise konkateniert mit den Elementen aus <conc>        */
/* ========================================================== */
#ifdef __STDC__
void unionconcLookset(Lookset *dest,Lookset src, Lookset conc);
#else
void unionconcLookset();
#endif
/* ======================================================== */
/* wandelt Externdarstellung in Lookaheadset um             */
/* Eingabeform:                                             */
/*     B  ::=  c | c B | { BL }                             */
/*     BL ::=  B | B , BL                                   */
/* ======================================================== */
#ifdef __STDC__
void makeLookset(char *darst,Lookset *set);
#else
void makeLookset();
#endif

#endif /* LOOK_H */
