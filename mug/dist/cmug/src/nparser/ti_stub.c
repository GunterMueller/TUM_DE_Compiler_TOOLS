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


/* *********************************************************************** */
/* ti_stub.c:							       	   */
/* Stummelroutinen zur Kompatibilitaet mit den alten Parserschnittstellen  */
/* Aenderung 13.03.91, Ulrich Vollath: neue Schnittstellen -> ti_base.c	   */
/* Aenderung 11.01.91, Ulrich Vollath: L_...-Symbole                       */
/* erstellt  10.01.91, Ulrich Vollath                                      */
/* *********************************************************************** */

#ifdef __STDC__
#include <stddef.h>
#include <stdlib.h>
#endif
#include <stdio.h>
#include "ti_token.h"
#include "ti_defs.h"
#include "ti_parse.h"
#include "scanfunk.h"
#include "parsfunk.h"
#include "semfunk.h"

#ifdef L_SEMERRORS
long semerrors;
#endif

#ifdef L_SEMINIT
#ifdef __STDC__
int semInit(int argc,char *argv[])
#else
int semInit(argc,argv)
 int argc;
 char *argv[];
#endif
 {
  return(1);
 } /* semInit */
#endif

#ifdef L_SEMCLOSE
#ifdef __STDC__
void semClose(void)
#else
void semClose()
#endif
 {
 } /* semClose */
#endif

#ifdef L_SEMABORT
#ifdef __STDC__
void semAbort(void)
#else
void semAbort()
#endif
 {
 } /* semAbort */
#endif

#ifdef L_ERRDAT
FILE *errordatei;
#endif

#ifdef L_ERRFILE
FILE *errorfile;
#endif

#ifdef L_SCANEIN
FILE *ScanEin;
#endif

#ifdef L_PROTO
int protokoll;
#endif

#ifdef L_OPENERR
/* ===================================================================== */
/* Oeffnen des Fehlerfiles bei der ersten Fehlermeldung                  */
/* ===================================================================== */
/* vollstaendiger Name der anzulegenden Fehler-Protokoll-Datei */
#define FEHLER_DATEI_NAME "parser.err"
#ifdef __STDC__
int OpenErr(void)
#else
int OpenErr()
#endif
 {
  extern FILE *errorfile;
  if (errordatei == NULL)            /* sonst schon geoeffnet */
   {
    if ((errordatei=fopen(FEHLER_DATEI_NAME,"w")) == NULL)
     {
      fprintf(stderr,"Fehlerprotokolldatei %s kann nicht geoeffnet werden !\n",
                     FEHLER_DATEI_NAME);
      return(0);
     }
   } /* errordatei == NULL */
  errorfile = errordatei;
  return(1);  /* erfolgreich */
 } /* OpenErr */
#endif /* L_OPENERR */

#ifdef L_OUT
/* ===================================================================== */
/* Pseudo-outred()                                                       */
/* ===================================================================== */
#ifdef __STDC__
int outred(long p,long l,long n)
#else
int outred (p,l,n)
 long p;
 long l;
 long n;
#endif
 {
  DBGPRT(("outred prod %ld ls %s len %ld\n",(long)p,decNont((Nont)l),(long)n ));
  return(1);
 } /* outred */

/* ===================================================================== */
/* Pseudo-outterm()                                                      */
/* ===================================================================== */
#ifdef __STDC__
int outterm(Token tok)
#else
int outterm (tok)
 Token tok;
#endif 
 {
  DBGPRT(("outterm %s\n",decTerm((Term)SYM(tok)) ));
  return(1);
 } /* outterm */
#endif /* L_OUT */

