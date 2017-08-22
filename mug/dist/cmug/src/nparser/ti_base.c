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


/* ********************************************************************* */
/* ti_base.c:							         */
/* Routinen zur Implementierung der Parserschnittstellen aus parsfunk.h  */
/* erstellt  13.03.91, Ulrich Vollath, aus ti_stub.c                     */
/* ********************************************************************* */
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

#ifdef L_PARSEINIT
int parseInit()
 {
  return(1);
 } /* parseInit */
#endif

#ifdef L_PARSECLOSE
void parseClose()
 {
 } /* parseClose */
#endif

#ifdef L_PARSEABORT
void parseAbort()
 {
 } /* parseAbort */
#endif

#ifdef L_PARSE
#ifdef __STDC__
int parse(int argc, char *argv[], char *inputname,long *errors)
#else
int parse(argc,argv,inputname,errors)
 int argc;
 char *argv[]; 
 char *inputname;
 long *errors;
#endif
 {
  extern long scanerrors;
  extern long parseerrors; 
  extern Ptab lalr_tab;   /* zugelinkte Parsertabelle  */
  int res; 

  parseerrors = 0;
  if (!semInit(argc,argv) || !scanOpen(inputname))
    return(0);
  res = ti_parse(&lalr_tab,scanNext,outred,outterm);
  *errors = scanerrors + semerrors + parseerrors;
  scanClose();
  if (res)
    semClose();
  else
    semAbort();
  return(res);
 } /* parse */
#endif

#ifdef L_PARSER
#ifdef __STDC__
int parser(int argc,char *argv[],char *scan_file_name)
#else
int parser(argc,argv,scan_file_name)
 int argc;
 char *argv[];
 char *scan_file_name;
#endif
 {
  extern long scanerrors;
  extern long parseerrors;
  extern Ptab lalr_tab;   /* zugelinkte Parsertabelle  */
  int res;
  long errors;

  if (scanInit())
   {
    int res;

    res = parseTab(argc,argv,scan_file_name,&errors,
                   (void *)&lalr_tab,scanNext,outred,outterm);
    return(res && !errors ? 0 : 20);
   }
  else
    return(20);

 } /* parser */
#endif



#ifdef L_PARSETAB
#ifdef __STDC__
int parseTab(int argc, char *argv[], char *inputname,long *errors,
             void *tab,int (*scan)(Token),
             int (*outred)(long,long,long),int (*outterm)(Token) )
#else
int parseTab(argc,argv,inputname,errors,tab,scan,outred,outterm)
 int argc;
 char *argv[]; 
 char *inputname;
 long *errors;
 char *tab;
 int (*scan)();
 int (*outred)();
 int (*outterm)();
#endif
 {
  extern long scanerrors;
  extern long parseerrors; 
  int res; 

  parseerrors = 0;
  if (!semInit(argc,argv) || !scanOpen(inputname))
    return(0);
  res = ti_parse((Ptab *)tab,scan,outred,outterm);
  *errors = scanerrors + semerrors + parseerrors;
  scanClose();
  if (res)
    semClose();
  else
    semAbort();
  return(res);
 } /* parseTab */
#endif

