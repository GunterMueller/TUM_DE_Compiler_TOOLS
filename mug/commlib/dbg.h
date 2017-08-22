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


/* ************************************************************ */
/* debug.h :                                                    */
/* Deklarationen und Makros zum DEBUG=Paket                     */
/* Unterstuetzung automatischen Einrueckens bei verschachteltem */
/* Prozeduraufruf                                               */
/* aktiviert durch  #define DEBUG im einbindenden Modul         */
/* erstellt : 29.10.89 (uv)                                     */
/* ************************************************************ */

#ifdef DEBUG
/* Datei fuer Debug-Ausgaben */
#define DBGFILE stdout
/* ========================================================== */
/* Initialisierung des debugging=Paketes, muss vor dem ersten */
/* Aufruf eines anderen Dienstes aufgerufen werden            */
/* ========================================================== */
void debugInit();
#define DEBUG_INIT debugInit()                                 
/* ============================================================ */
/* Einruecken der naechsten Ausgabezeile um <level> Leerzeichen */
/* ============================================================ */
void debugIndent();
#define DEBUG_INDENT debugIndent()
/* ========================================================== */
/* Ausgabe einer Startmeldung fuer eine Routine               */
/* ========================================================== */
void debug_begin();
#define DEBUG_BEGIN(fmt) debug_begin fmt
/* ========================================================== */
/* Ausgabe einer Endemeldung fuer eine Routine                */
/* ========================================================== */
void debug_end();
#define DEBUG_END(fmt) debug_end fmt
/* ========================================================== */
/* Ausgabe einer Meldung innerhalb einer Routine              */
/* ========================================================== */
void debug_msg();
#define DEBUG_MSG(fmt) debug_msg fmt
/* ============================================================== */
/* Ausgabe einer Meldung innerhalb einer Routine ohne Einruecken  */
/* ============================================================== */
void debug_prt();
#define DEBUG_PRT(fmt) debug_prt fmt
/* ========================================================== */
/* Ausfuehren von Befehlen, falls im DEBUG=Modus              */
/* ========================================================== */
#define IFDEBUG(stmts) stmts
#else /* Stummel, wenn kein debugging gewuenscht */
#define DEBUG_INIT 
#define DEBUG_INDENT
#define DEBUG_BEGIN(fmt)
#define DEBUG_END(fmt)
#define DEBUG_MSG(fmt)
#define DEBUG_PRT(fmt)
#define IFDEBUG(stmts)
#endif
