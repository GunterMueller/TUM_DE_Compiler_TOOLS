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
/* LRKfiles.c   :                                                         */
/* LR(k)-Parser-Generator                                                 */
/* Modul : Dateioperationen                                               */
/* erstellt   : 23.1.89                                                   */
/* ********************************************************************** */

#include <stdio.h>         /* E/A-Definitionen                   */  

#include "defs.h"          /* diverse unspezifische Definitionen */
#include "lrkfiles.h"      /* Deklarationen Dateimodul           */
#include "lrkerrors.h"     /* Deklarationen Fehlermodul          */

/* ====================================================================== */
/* Oeffnen einer Datei, ggf. mit Fehlermeldung                            */
/*   Rueckgabe : Filehandle, der geoeffneten Datei, falls erfolgreich     */
/*               NULL sonst                                              */
/* ====================================================================== */
#ifdef __STDC__
FILE *OpenFile(char *name, char *mode)
               /* Dateiname der zu oeffnenden Datei   */
               /* Modus, in dem Datei zu oeffnen ist  */
#else
FILE *OpenFile(name,mode)
 char *name;   /* Dateiname der zu oeffnenden Datei   */
 char *mode;   /* Modus, in dem Datei zu oeffnen ist  */
#endif
 {
  FILE *handle;  /* Handle der geoeffneten Datei      */

  if ( (handle = fopen(name,mode) ) == NULL)  /* Datei oeffnen */
    /* Oeffnen nicht erfolgreich */		
    Error1("Datei %s kann nicht geoeffnet werden\n",name);
  return(handle);

 } /* OpenFile */


