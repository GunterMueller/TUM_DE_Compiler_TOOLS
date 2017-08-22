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
/* ti_errs.h :                                                            */ 
/* LR(k)-Parser-Tabellen-Interpreter                                      */ 
/* Vereinbarungen Ausgabe und Komprimierung von Fehlermeldungen           */ 
/* ---------------------------------------------------------------------- */ 
/* erstellt  : 26.12.89                                                   */ 
/* ********************************************************************** */

#ifndef TI_ERRS_H
#define TI_ERRS_H

/* ------------------------------------ */
/* Fehlernummern fuer interne Fehler    */
/* ------------------------------------ */
#define ierrKUL 0  /* Kellerunterlauf                        */
#define ierrUGU 1  /* ungueltiger Uebergang                  */
#define ierrINS 2  /* kein Uebergang mit eingefuegtem Symbol */
#define ierrNON 3  /* kein Uebergang mit Nonterminalsymbol   */

/* ======================================================================= */
/* Anfang einer Fehlerbehandlung melden                                    */
/* ======================================================================= */
#ifdef __STDC__
extern void fehlerAnf(Token);
#else
extern void fehlerAnf();
#endif

/* ======================================================================= */
/* Meldung , dass Token ignoriert wurde                                    */
/* ======================================================================= */
#ifdef __STDC__
extern void symIgnoriert(Token);
#else
extern void symIgnoriert();
#endif

/* ======================================================================= */
/* genau ein Token wurde erwartet, selbiges merken fuer spaeter            */
/* ======================================================================= */
#ifdef __STDC__
extern void symErwartet(Term);
#else
extern void symErwartet();
#endif

/* ======================================================================= */
/* Wiederaufsetzen bei passendem Token                                     */
/* ======================================================================= */
#ifdef __STDC__
extern void wiederAufsetzen(Token);
#else
extern void wiederAufsetzen();
#endif

/* ======================================================================= */
/* Einfuegen eines Symbols und Wiederaufsetzen damit                       */
/* ======================================================================= */
#ifdef __STDC__
extern void symEinfuegen(Term,Token);
#else
extern void symEinfuegen();
#endif

/* ======================================================================= */
/* vorzeitiges Dateiende, bevor Wiederaufsetzen moeglich                   */
/* ======================================================================= */
#ifdef __STDC__
extern void dateiEnde(Token);
#else
extern void dateiEnde();
#endif

/* ======================================================================= */
/* Akzeptiert durch Fehlerbehandlung, Resteingabe vorhanden                */
/* ======================================================================= */
#ifdef __STDC__
extern void restIgnoriert(void);
#else
extern void restIgnoriert();
#endif

/* ======================================================================= */
/* interner Fehler, sollte nicht auftreten                                 */
/* ======================================================================= */
#ifdef __STDC__
extern void internFehler(int,Token);
#else
extern void internFehler();
#endif

/* ======================================================================= */
/* Fehlermeldung : kein Speicher                                           */
/* ======================================================================= */
#ifdef __STDC__
extern void memError(void);
#else
extern void memError();
#endif

#endif /* TI_ERRS_H */
