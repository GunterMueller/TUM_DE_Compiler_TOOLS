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


/* ****************************************************************** */
/* ti_main.c : Rahmenprogramm zum Tabelleninterpreter zu Testzwecken, */
/*             fuer einfache Uebersetzer etc.                         */
/* falls das Preprozessorsymbol READ_PTAB definiert ist, wird die     */
/*    Parsertabelle eingelesen, sonst muss sie zum Uebersetzer durch  */
/*    linken zugefuegt werden                                         */
/* Aenderung:  10.08.90, READ_PTAB (uv)                               */
/* erstellt  : 23.12.89 (uv)                                          */
/* ****************************************************************** */
#ifdef __STDC__
#include <stddef.h>
#include <stdlib.h>
#endif
#include <stdio.h>

#include "defs.h"
#include "dbg.h"
#include "ti_token.h"
#include "scanfunk.h"
#include "semfunk.h"
#include "parsfunk.h"
#include "ti_defs.h"
#ifdef READ_PTAB
#include "ti_read.h"
#endif
#include "ti_zugr.h"
#include "ti_parse.h"

#ifdef READ_PTAB
static Ptab lalr_tab;   /* Datenstruktur, in die die Tabelle eingelesen wird */
#else
extern Ptab lalr_tab;   /* zugelinkte Parsertabelle                          */
#endif

/* ===================================================================== */
/* Hauptprogramm                                                         */
/* ===================================================================== */
#ifdef __STDC__
int main(int argc, char *argv[])
#else
int main(argc,argv)
 int argc;
 char *argv[];
#endif
 {
  char *scan_file_name;   /* Dateiname Scannereingabe        */
  long errors;		  /* Gesamtzahl Fehler               */

#ifdef LABER
#ifdef ALT
  fputs("\nLRK-Tabellen-Interpreter Version 1.0 alpha\n\n",stderr);
#else
  fputs("\nlalr(1)-Tabellen-Interpreter CMUG-Version 1.0\n\n",stderr);
#endif
#endif /* LABER */
#ifdef READ_PTAB /* Tabelle einlesen */
  if (argc < 3)
   {
    fprintf(stderr,"Aufruf : %s <lalr-Tabelle> <Eingabe> [...]\n",argv[0]);
    exit(20);
   }
  scan_file_name = argv[2];  /* Dateiname Eingabedatei                    */
  if (! readPtab(argv[1],&lalr_tab) )
   {
    fprintf(stderr,"Tabelle %s konnte nicht eingelesen werden\n",argv[1]);
    exit(20);
   }
/*argv[1] = NULL;*/     /* ist das zulaessig? (jedenfalls wirksam)  */
#else		 /* Tabelle zugelinkt */
  if (argc < 2)
   {
    fprintf(stderr,"Aufruf : %s <Eingabe> [...]\n",argv[0]);
    exit(20);
   }
  scan_file_name = argv[1];  /* Dateiname Eingabedatei                    */
#endif
  if (scanInit())                       /* ACHTUNG : neue Schnittstelle */
   {
    int res;

    res = parseTab(argc,argv,scan_file_name,&errors,
                   (void *)&lalr_tab,scanNext,outred,outterm);
    return(res && !errors ? 0 : 20);
   }
  else
    return(20);
 } /* main */

