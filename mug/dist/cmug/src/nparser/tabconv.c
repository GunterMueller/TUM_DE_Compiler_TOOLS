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
/* tabconv.c: Konversion von lrkgen-generierten Tabellen in           */
/*            C-Datenstrukturen                                       */
/* erstellt  : 10.08.90 (uv)                                          */
/* ****************************************************************** */
#ifdef __STDC__
#include <stddef.h>
#include <stdlib.h>
#endif
#include <stdio.h>

#include "defs.h"
#include "dbg.h"

#include "ti_defs.h"
#include "ti_read.h"

/* Dateiname der Defines-Datei */
#define DEFINES "ti_sizes.h"
static Ptab tab;   /* Datenstruktur, in die die Tabelle eingelesen wird */

/* ===================================================================== */
/* Hauptprogramm                                                         */
/* ===================================================================== */
#ifdef __STDC__
int main(int argc, char **argv)
{
#else
int main(argc,argv)
 int argc;
 char *argv[];
 {
#endif
  FILE *dfile;
  int  defines = 0;

  if ((argc != 4 || !(defines = !strcmp(argv[3],"-d"))) && argc != 3)
   {
    fputs("Konversion von lalr(1)-Parsertabellen\n",stderr);
    fprintf(stderr,"Aufruf : %s [-d] <Tabelle> <Ausgabe>\n",argv[0]);
    exit(20);
   }
  if (! readPtab(argv[1],&tab) )
   {
    fprintf(stderr,"Tabelle %s konnte nicht eingelesen werden\n",argv[1]);
    exit(20);
   }
  /* ------------------------ */
  /* C-Datenstruktur ausgeben */
  /* ------------------------ */
  if ((dfile = fopen(argv[2],"w")) == NULL)
   {
    perror("Ausgabedatei kann nicht geoeffnet werden");
    exit(20);
   }
  fprintf(dfile,"/* lalr(1)-Parsertabelle %s */\n\n",argv[1]);
  cDump(dfile,&tab);
  fclose(dfile);
  /* --------------------------------- */
  /* defines fuer Typgroessen ausgeben */
  /* --------------------------------- */
  if (defines)
   {
    if ((dfile = fopen(DEFINES,"w")) == NULL)
     {
      perror("Defines-Datei kann nicht geoeffnet werden");
      exit(20);
     }
    cDefines(dfile,&tab);
    fclose(dfile);
   }
  return(0);
 } /* main */

