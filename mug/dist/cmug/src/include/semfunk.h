

/* ******************************************************************* */
/* semfunk.h: Funktionalitaten CMUG-Semantikteil                       */
/* Aenderung 10.01.91, Ulrich Vollath                                  */
/* ******************************************************************* */
#ifndef SEMFUNK_H
#define SEMFUNK_H

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
                                       

/* ==================================================================== */
/* Anzahl der vom Semantikteil festgestellten semantischen Fehler. Wird */
/* in semInit() mit 0 vorbesetzt und bei jedem Fehler erhoeht.         	*/
/* ==================================================================== */
extern long semerrors;


/* ==================================================================== */
/* Initialisiert den Semantikmodul und seine Datenstrukturen.		*/
/* Uebergeben werden argc Parameter argv[] vom Typ char*, die		*/
/* normalerweise den Kommandozeilenparametern des Uebersetzeraufrufs	*/
/* entsprechen (ohne Programmnamen und reine Interpreterargumente).	*/
/* Ergebnis == 0 : Initialisierung war nicht erfolgreich.		*/
/* ==================================================================== */
#ifdef __STDC__
extern int semInit(int argc,char *argv[]);
#else
extern int semInit();
#endif
 
/* ==================================================================== */
/* Regulaeres Beenden des Semantikmoduls, Freigabe von Datenstrukturen  */
/* etc.									*/
/* Nach dem Aufruf von semClose() duerfen andere Funktionen als 	*/
/* semInit() nicht mehr aufgerufen werden.				*/
/* ==================================================================== */
#ifdef __STDC__
extern void semClose(void);
#else
extern void semClose();
#endif

/* ==================================================================== */
/* Sofortiger Abbruch des Semantikmoduls bei fatalen Fehlern.		*/
/* Diese Routine kann mehrfach aufgerufen werden, der Semantikteil hat 	*/
/* sicherzustellen, dass Freigaben etc. korrekt nur einmal stattfinden.	*/
/* Nach dem Aufruf von semAbort() duerfen andere Funktionen als 	*/
/* semAbort() und semInit() nicht mehr aufgerufen werden.		*/
/* ==================================================================== */
#ifdef __STDC__
extern void semAbort(void);
#else
extern void semAbort();
#endif

/* ==================================================================== */
/* Meldung des Parsers an den Semantikteil, dass das Terminalzeichen 	*/
/* token verarbeitet wurde (i.allg. Shift-Operation).			*/
/* Die Datenstruktur ist nur waehrend des Aufrufs gueltig, benoetigte	*/
/* Daten muessen vom Semantikteil vor Rueckkehr kopiert werden.		*/
/* Ergebnis == 0 : Beim Bearbeiten des Terminalzeichens im Semantikteil */
/* trat ein fataler Fehler auf, der eine Fortfuehrung des 		*/
/* Programmlaufes verbietet.						*/
/* Das steuernde Programm (i.allg. der Parser) ruft die Abbruchroutinen */
/* inkl. semAbort() auf und beendet die Uebersetzung.			*/
/* ==================================================================== */
#ifdef __STDC__
extern int outterm(Token);
#else
extern int outterm();
#endif
       
/* ==================================================================== */
/* Meldung einer Reduktion des Parsers an den Semantikteil.		*/
/* prod ist die laufende Nummer der Produktion (mit 0 beginnend 	*/
/* numeriert) in der Grammatik, lseite ist die linke Seite der 		*/
/* Produktion, plen die Laenge. 					*/
/* Ergebnis == 0 : Beim Bearbeiten der Reduktion im Semantikteil trat	*/
/* ein fataler Fehler auf, der eine Fortfuehrung des Programmlaufes 	*/
/* verbietet. Das steuernde Programm (i.allg. der Parser) ruft die 	*/
/* Abbruchroutinen inkl. semAbort() auf und beendet die Uebersetzung.	*/
/* ==================================================================== */
#ifdef __STDC__
extern int outred(long prod,long lseite,long plen);
#else
extern int outred();
#endif

/* ==================================================================== */
/* Oeffnet eine evtl. gewuenschte Fehlerprotokolldatei beim ersten 	*/
/* auftretenden Fehler (Aufruf durch Fehlermodul / Dekoder).		*/
/* Falls protokoll != 0 gesetzt wird, so werden alle folgenden 		*/
/* Fehlermeldungen parallel auf stderr und errordatei geschrieben.	*/
/* Rueckgabe == 0 : Fehlerdatei kann nicht geoeffnet werden.		*/
/* ==================================================================== */
extern FILE *errordatei;
extern int  protokoll;
#ifdef __STDC__
extern int OpenErr(void);
#else
extern int OpenErr();
#endif

/* ==================================================================== */
/* Falls nicht NULL, wird jedes erkannte Token durch diese Routine	*/
/* geschleust, und kann somit geaendert werden				*/
/* Das Ergebnis ist der gewuenschte Return-Wert von scanNext()		*/
/* ==================================================================== */
#ifdef __STDC__
extern int (*changeToken)(Token);
#else
extern int (*changeToken)();
#endif
                               
#endif /* SEMFUNK_H */
