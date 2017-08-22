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

#ifndef DEBUG
#define DEBUG
#endif
/* ************************************************************ */
/* debug.c :                                                    */
/* allgemeines DEBUG=Paket                                      */
/* Unterstuetzung automatischen Einrueckens bei verschachteltem */
/* Prozeduraufruf                                               */
/* erstellt : 29.10.89 (uv)                                     */
/* ************************************************************ */

#include <stdio.h>
#include "dbg.h"
/* ========================================================== */
/* modul-lokale Daten                                         */
/* ========================================================== */
static int level = 0;      /* aktuelle Inkarnationstiefe */

/* Unterstuetzte Parameterleiste fuer printf's */
#define FMTPARAMS fmt,p1,p2,p3,p4,p5,p6,p7,p8,p9,p10,p11,p12,p13,p14,p15,p16
#define FMTPARDEC char *fmt;\
                  int p1,p2,p3,p4,p5,p6,p7,p8,p9,p10,p11,p12,p13,p14,p15,p16;

/* ============================================================ */
/* Einruecken der naechsten Ausgabezeile um <level> Leerzeichen */
/* ============================================================ */
void debugIndent()
 {
  register int i;

  for (i = 0; i < level; i++)
    putchar(' ');
 } /* debugIndent */


/* ========================================================== */
/* Initialisierung des debugging=Paketes, muss vor dem ersten */
/* Aufruf eines anderen Dienstes aufgerufen werden            */
/* ========================================================== */
void debugInit()
 {
 } /* debug_init */

/* ========================================================== */
/* Ausgabe einer Startmeldung fuer eine Routine               */
/* ========================================================== */
void debug_begin(FMTPARAMS)
 FMTPARDEC
 {
  debugIndent();
  fputc('<',DBGFILE);
  level++;
  fprintf(DBGFILE,FMTPARAMS);
  fflush(DBGFILE);
 } /* debug_begin */

/* ========================================================== */
/* Ausgabe einer Endemeldung fuer eine Routine                */
/* ========================================================== */
void debug_end(FMTPARAMS)
 FMTPARDEC
 {   
  level--;
  debugIndent();
  fputc('>',DBGFILE);
  fprintf(DBGFILE,FMTPARAMS);
  fflush(DBGFILE);
  if (level < 0)
   {
    fprintf(DBGFILE,"DEBUG : Falscher Gebrauch von DEBUG_BEGIN / DEBUG_END\n");
    level = 0;
   }
 } /* debug_end */

/* ========================================================== */
/* Ausgabe einer Meldung innerhalb einer Routine              */
/* ========================================================== */
void debug_msg(FMTPARAMS)
 FMTPARDEC
 {
  debugIndent();
  fprintf(DBGFILE,FMTPARAMS);
  fflush(DBGFILE);
 } /* debug_msg */

/* ============================================================= */
/* Ausgabe einer Meldung innerhalb einer Routine ohne Einruecken */
/* ============================================================= */
void debug_prt(FMTPARAMS)
 FMTPARDEC
 {
  fprintf(DBGFILE,FMTPARAMS);
  fflush(DBGFILE);
 } /* debug_prt */

