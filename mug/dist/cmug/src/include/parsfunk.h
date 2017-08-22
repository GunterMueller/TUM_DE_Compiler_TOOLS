
/* ******************************************************************* */
/* parsfunk.h: bereitgestellte Funktionalitaten Parser                 */
/* Aenderung 10.01.91, Ulrich Vollath                                  */
/* ******************************************************************* */
#ifndef PARSFUNK_H
#define PARSFUNK_H
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

/* ================================================================== */
/* Anzahl der vom Parser festgestellten syntaktischen Fehler.         */
/* Wird in parseInit() mit 0 vorbesetzt und bei jedem Fehler erhoeht. */
/* ================================================================== */
extern long parseerrors;

/* ================================================================== */
/* Initialisiert den Parsermodul und seine Datenstrukturen.           */
/* Ergebnis == 0 : Initialisierung war nicht erfolgreich.             */
/* ================================================================== */
#ifdef __STDC__
extern int parseInit(void);
#else
extern int parseInit();
#endif

/* ==================================================================== */
/* Durchfuehrung einer Uebersetzung.   				      	*/
/* Diese Routinen stellen die Applikationsschnittstelle des fertigen  	*/
/* Uebersetzers dar.						      	*/
/* -------------------------------------------------------------------- */
/* Die Parameter argc und argv werden dem Semantikteil 		      	*/
/* von parse() bzw parseTab() mit semInit(), der 		      	*/
/* Parameter dateiname dem Scanner durch den Aufruf scanOpen() 	      	*/
/* gemeldet (s.u. scanfunk.h).					      	*/
/* Die Variable *errors erhaelt die Summe von lexikalischen,       	*/
/* syntaktischen und semantischen Fehlern (semerrors + parseerrors +  	*/
/* scanerrors).								*/
/* nach Beendigung wird scanClose() und semClose() aufgerufen           */
/* -------------------------------------------------------------------- */
/* bei parseTab() werden zusaetzlich Tabelle tab, Scannerroutine scan() */
/* und die Semantikroutinen outred() und outterm() angegeben.           */
/* Das ermoeglicht die Verwendung mehrerer Parser in einem Programm     */
/* -------------------------------------------------------------------- */
/* Ergebnis == 0 : Waehrend der Uebersetzung trat ein schwerwiegender 	*/
/* Fehler auf, die Analyse wurde abgebrochen, die Ergebnisse koennen  	*/
/* inkomplett sein (unvollstaendiger Syntaxbaum etc.).		      	*/
/* ==================================================================== */
#ifdef __STDC__
extern int parse(int argc,char *argv[],char *dateiname,long *errors);
#else
extern int parse();
#endif

#ifdef __STDC__
extern int parseTab(int argc, char *argv[], char *inputname,long *errors,
             void *tab,int (*scan)(Token),
             int (*outred)(long,long,long),int (*outterm)(Token) );
#else
extern int parseTab();
#endif
                                    
/* ====================================================================== */
/* Regulaeres Beenden des Parsermoduls, Freigabe von Datenstrukturen etc. */   
/* Nach dem Aufruf von parseClose() duerfen andere Funktionen als 	  */
/* parseInit() nicht mehr aufgerufen werden.                              */
/* ====================================================================== */
#ifdef __STDC__
void parseClose(void);
#else
void parseClose();
#endif

/* ====================================================================== */
/* Sofortiger Abbruch des Parsermoduls bei fatalen Fehlern.		  */
/* Diese Routine kann mehrfach aufgerufen werden, der Parser hat          */
/* sicherzustellen, dass Freigaben etc. korrekt nur einmal stattfinden.   */
/* Nach dem Aufruf von parseAbort() duerfen andere Funktionen als	  */
/* parseAbort() und parseInit() nicht mehr aufgerufen werden.             */
/* ====================================================================== */
#ifdef __STDC__
void parseAbort(void);
#else
void parseAbort();
#endif

#endif /* PARSFUNK_H */

