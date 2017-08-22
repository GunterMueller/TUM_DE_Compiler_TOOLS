
/* ******************************************************************* */
/* scanfunk.h: bereitgestellte Funktionalitaten Scanner                */
/* Aenderung 10.01.91, Ulrich Vollath: neue CMUG-Schnittstellen        */
/* Aenderung : 25.10.90 ansifiziert                                    */
/* Deklaration der Funktionalitaten scan1.c ... scan4.c                */
/* ******************************************************************* */
#ifndef SCANFUNK_H
#define SCANFUNK_H
/*
 * (c) copyright 1989 by Technische Universitaet Muenchen, Germany
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

/* ******************************************************************** */
/* Schnittstellen des Scanners						*/
/* ******************************************************************** */

/* ==================================================================== */
/* Anzahl der vom Scanner festgestellten lexikalischen Fehler. 		*/
/* Wird in scanOpen() mit 0 vorbesetzt und bei jedem Fehler erhoeht.    */
/* ==================================================================== */
extern long scanerrors;

/* ==================================================================== */
/* Initialisiert den Scannermodul und seine Datenstrukturen.            */
/* Ergebnis == 0 : Initialisierung war nicht erfolgreich.		*/
/* ==================================================================== */
#ifdef __STDC__
extern int scanInit(void);
#else
extern int scanInit();
#endif

/* ==================================================================== */
/* Der Scanner oeffnet die Eingabedatei mit dem Namen dateiname oder    */
/* kopiert sich z.B. dateiname als Eingabezeichenreihe in einen eigenen */
/* Puffer, dadurch ist Uebersetzung einer interaktiven Benutzereingabe  */
/* moeglich.								*/
/* Ergebnis == 0 : Datei konnte nicht geoeffnet werden.			*/
/* ==================================================================== */
#ifdef __STDC__
extern int scanOpen(char *dateiname);
#else
extern int scanOpen();
#endif

/* ==================================================================== */
/* Eigentliche Scannerfunktion. Liest das naechste Terminalsymbol aus   */
/* der Quelldatei und schreibt die Werte in die Datenstruktur *token.	*/
/* Ergebnis == 0 : Beim Einlesen trat ein fataler Fehler auf, die 	*/
/* lexikalische Analyse kann nicht fortgesetzt werden. Das steuernde 	*/
/* Programm (i.allg. der Parser) ruft die Abbruchroutinen inkl. 	*/
/* scanAbort() auf und beendet die Uebersetzung.			*/
/* ==================================================================== */
#ifdef __STDC__
extern int scanNext(Token token);
#else
extern int scanNext();
#endif
 
/* ==================================================================== */
/* Regulaeres Beenden des Scannermoduls, Freigabe von Datenstrukturen 	*/
/* etc.									*/
/* Die Datei aus dem Aufruf scanOpen() wird wieder geschlossen.		*/
/* Nach dem Aufruf von scanClose() duerfen andere Funktionen als 	*/
/* scanInit()								*/
/* nicht mehr aufgerufen werden.					*/
/* ==================================================================== */
#ifdef __STDC__
extern void scanClose(void);
#else
extern void scanClose();
#endif

/* ==================================================================== */
/* Sofortiger Abbruch des Scannermoduls bei fatalen Fehlern.		*/
/* Diese Routine kann mehrfach aufgerufen werden, der Scanner hat 	*/
/* sicherzustellen, dass Freigaben etc. korrekt nur einmal stattfinden. */
/* Nach dem Aufruf von scanAbort() duerfen andere Funktionen als 	*/
/* scanAbort() und scanInit() nicht mehr aufgerufen werden.		*/
/* ==================================================================== */
#ifdef __STDC__
extern void scanAbort(void);
#else
extern void scanAbort();
#endif

/* ==================================================================== */
/* Speicherreservierung fuer eine Tokendatenstruktur. 			*/
/* Rueckgabe : Reserviertes Token, oder NULL falls Reservierung nicht   */
/* moeglich (kein Speicher etc.).					*/
/* Diese Routine wird vom Parser aufgerufen, um den Parameter		*/
/* zu erhalten, der in der Aufrufen von scan() und outterm() verwendet  */
/* wird. Bei Implementierung eines Lookaheads groesser als 1 kann	*/
/* allocToken() von Parser auch mehrfach aufgerufen werden.		*/
/* ==================================================================== */
#ifdef __STDC__
extern Token allocToken(void);
#else
extern Token allocToken();
#endif

/* ==================================================================== */
/* Freigabe eines zuvor mit allocToken() reservierten Speichers.	*/
/* ==================================================================== */
#ifdef __STDC__
extern void freeToken(Token);
#else
extern void freeToken();
#endif

/* ==================================================================== */
/* Kopieren der Informationen des Tokens source in ein anderes 		*/
/* (zuvor mit allocToken() reserviertes) Token dest			*/
/* Rueckgabe: Zieltoken dest						*/
/* ==================================================================== */
#ifdef __STDC__
extern Token copyToken(Token dest,Token source);
#else
extern Token copyToken();
#endif

/* ==================================================================== */
/* Kennzeichnet die semantischen Informationen des token als ungueltig. */
/* Wird vom Parser verwendet, um bei eingefuegten / geaenderten 	*/
/* Terminalzeichen Zugriffe auf die daraufhin falsche 			*/
/* Semantikinformation zu verhindern. 					*/
/* Ungueltige Token werden nicht dekodiert, Fehlermeldungen, in denen   */
/* ungueltige Token als Parameter vorkommen, werden unterdrueckt.	*/
/* ==================================================================== */
#ifdef __STDC__
extern void setTokeninvalid(Token token);
#else
extern void setTokeninvalid();
#endif

/* ==================================================================== */
/* Rueckgabe != 0, falls die semantischen Informationen von token 	*/
/* gueltig sind, also nicht durch setTokeninvalid() markiert wurden.    */
/* Zweck: Der Semantikteil muss vor Zugriffen pruefen, ob das Token 	*/
/* nicht durch Fehlerbehandlungsoperationen des Parsers enstanden ist.  */
/* ==================================================================== */
#ifdef __STDC__
extern int isTokenvalid(Token token);
#else
extern int isTokenvalid();
#endif


/* ******************************************************************** */
/* Schnittstellen des Dekoders /Fehlerausgabemoduls			*/
/* Initialisierung, Beendigung und Abbruch geschieht in den Routinen	*/
/* des Scanners.							*/
/* ******************************************************************** */
#ifdef __STDC__
extern void  memError(void);
#else
extern void  memError();
#endif


/* ==================================================================== */
/* Dekodiert das Terminalzeichen token in seine Externdarstellung.	*/
/* Das Token darf nicht durch setTokeninvalid() als ungueltig markiert 	*/
/* sein.								*/
/* falls text != NULL, wird das Ergebnis in den Puffer text geschrieben,*/
/* Rueckgabewert ist text, sonst wird ein Zeiger auf das intern		*/
/* dekodierte Token abgeliefert 					*/
/* ==================================================================== */
#ifdef __STDC__
extern char  *scanDecode(char *text ,Token token);
#else
extern char  *scanDecode();
#endif

/* ==================================================================== */
/* Wie scanDecode, es werden aber maximal len Zeichen in den Puffer 	*/
/* text geschrieben (inkl. abschliessendes '\0').			*/
/* Ist die Externdarstellung laenger als len, so wird der 		*/
/* Rest weggelassen.							*/
/* text muss != NULL sein						*/
/* ==================================================================== */
#ifdef __STDC__
extern char  *scannDecode(char *text,Token token,int len);
#else
extern char  *scannDecode();
#endif

/* ====================================================== */
/* Quellort dekodieren                                    */
/* ====================================================== */
#ifdef __STDC__
void fdecQuellort(FILE *file, Quellort *ort);
#else
void fdecQuellort();
#endif

/* ==================================================================== */
/* Formatierte Ausgabe von Fehlermeldungen				*/
/* Die Ausgabe erfolgt nach stderr, sowie zusaetzlich in die Datei 	*/
/* errordatei, falls der Semantikteil die Vaiable protokoll != 0 	*/
/* gesetzt hat (siehe semfunk.h)					*/
/* Als Fehlerort wird die Variable ort dekodiert, sofern sie != NULL    */
/* ist.									*/
/* Der Formatstring fmt kann die folgenden Steuersequenzen enthalten:	*/
/* 	\n : Neue Zeile							*/
/* 	\t : Tabulatorzeichen						*/
/* 	\\ : Das Zeichen '\'						*/
/*	%q : Das naechste Argument ist eine Quellortangabe vom Typ      */
/* 	     Quellort *, die ausgegeben wird				*/
/*	%t : Das naechste Argument ist ein Token, dessen Quellortangabe */
/*	     ausgegeben wird.						*/
/*	%T : Das naechste Argument ist ein Token, das dekodiert und 	*/
/*	     ausgegeben wird.						*/
/* 	%s : Das naechste Argument ist ein C-String (char *)		*/
/* 	%d : Das naechste Argument ist ein Integer-Wert, der als 	*/
/* 	     Dezimalzahl ausgegeben wird				*/
/* 	%c : Das naechste Argument ist ein Integer-Wert, der als 	*/
/* 	     Character ausgegeben wird					*/
/* ==================================================================== */
#ifdef __STDC__
#ifdef SCAN_SOURCE
extern void  wErrorf(Quellort *ort, char *fmt,va_list);
#else
extern void  wErrorf(Quellort *ort, char *fmt, ...);
#endif
#else
extern void  wErrorf(); /* varargs */
#endif

/* ==================================================================== */
/* Ausgabe einer Standardfehlermeldung, wenn die Analyse wegen zu 	*/
/* kleinen Arbeitsspeichers abgebrochen werden muss.			*/
/* Nach diesem Aufruf sollte die Analyse abgebrochen werden.		*/
/* ==================================================================== */
#ifdef __STDC__
extern void memError(void);
#else
extern void memError();
#endif


/* ******************************************************************** */
/* alte Minimug-Schnittstellen						*/
/* ******************************************************************** */
#ifdef __STDC__
extern void mabort(void);
extern long scan(long int *rwert, short int *rpos, short int *rline, 
          short int *rcol, char *token); 
extern void scandecode(char *decstr, long int kc, long int rc, long int pos); 
extern void scaninit(void);
extern void scanende(void);
#else
extern void mabort();
extern long scan();
extern void scandecode();
extern void scaninit();
extern void scanende();
#endif

#endif /* SCANFUNK_H */

