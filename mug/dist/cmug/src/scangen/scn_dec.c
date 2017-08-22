
/* ****************************************************************** */
/* scn_dec.c: Dekoder-Routinen fuer den tabellengetriebenen           */
/*            parametrisierten Scanner                                */
/* erstellt  22.01.91, Ulrich Vollath                                 */
/* ****************************************************************** */

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

#ifdef __STDC__
#include <stddef.h>
#include <stdlib.h>
#endif
#include <stdio.h>
#include <string.h>
#include <varargs.h>

#include "ps_token.h"  /* allgemeine Definitionen fuer Scanner         */
#include "pstokenP.h"  /* private Definitionen fuer Scanner            */
#ifndef L_WERRORF
#else
#define SCAN_SOURCE    /* varargs-Definition fuer wErrorf() korrekt    */
#endif
#include "scanfunk.h"  /* Funktionalitaten Scanner                     */
#include "semfunk.h"
#include "ps_tab.h"    /* Datenstruktur Scannertabelle                 */
#include "scn_glob.h"  /* globale Variablendefinitionen		       */

#ifdef L_SCANNDECODE
/* ===================================================== */
/* neue Schnittstelle: Dekodieren eines Tokens           */
/* ===================================================== */
#ifdef __STDC__
char *scannDecode(char *text, Token tok, int len)
#else
char *scannDecode(text, tok, len)
 char  *text;
 Token tok;
 int   len;
#endif
 {
  char *res;

  if (tok != NULL && isTokenvalid(tok))
    res = tok->decinf;
  else
    res = "nicht_dekodierbar";
  if (text != NULL)
   {
    if (len <= 1)
      *text = '\0';
    else
      strncpy(text,res,len-1); /* dekodiertes Token kopieren */   
   }
  return(text);
 } /* scannDecode */
#endif /* L_SCANNDECODE */

#ifdef L_SCANDECODE
/* ===================================================== */
/* neue Schnittstelle: Dekodieren eines Tokens           */
/* ===================================================== */
#ifdef __STDC__
char *scanDecode(char *text, Token tok)
#else
char *scanDecode(text, tok)
 char *text;
 Token tok;
#endif
 {
  char *res;

  if (tok != NULL && isTokenvalid(tok))
    res = tok->decinf;
  else
    res = "nicht_dekodierbar";
  if (text == NULL)             /* Token direkt zurueckgeben             */
    return(res);                /* Dekodiertes Token direkt zurueckgeben */
  else
    return(strcpy(text,res));
 } /* scanDecode */
#endif /* L_SCANDECODE */

#ifdef L_FDECQUELL
/* ====================================================== */
/* Quellort dekodieren                                    */
/* ====================================================== */
#ifdef __STDC__
void fdecQuellort(FILE *file, Quellort *ort)
#else
void fdecQuellort(file,ort)
 FILE     *file;
 Quellort *ort;
#endif
 {
  if (ort != NULL)
   {
    if (QUELL_FN(ort) != NULL)
     {
      fputs(QUELL_FN(ort),file);
      fputc(':',file);
     }
    if (QUELL_ZL(ort) && QUELL_SP(ort) )
      fprintf(file,"%ld,%ld",(long)QUELL_ZL(ort),(long)QUELL_SP(ort));
   }
 } /* fdecQuellort */
#endif /* L_FDECQUELL */

#ifdef L_WERRORF
extern int  protokoll;
extern FILE *errordatei;
static int err_tried = 0;
/* ====================================================== */
/* interne Routine mit Angabe der Ausgabedatei            */
/* ====================================================== */
#ifdef __STDC__
static void intern_wErrorf(FILE *file,Quellort *ort,char *fmt,va_list arglist)
#else
static void intern_wErrorf(file,ort,fmt,arglist)
 FILE     *file;
 Quellort *ort;
 char     *fmt;
 va_list  arglist; 
#endif
 {
  char    *f;       /* Zeiger in den Formatstring */

  if (ort != NULL)
   { /* Quellort angegeben */
    if ((!QUELL_ZL(ort) || !QUELL_SP(ort)) )
     { /* Ort angegeben, aber ungueltig */
      fputs("unqualifizierte Fehlermeldung: ",file);
      if (fmt != NULL)
        fputs(fmt,file);
      fputc('\n',file);
      return; 
     } /* Quellort ungueltig */
    fdecQuellort(file,ort);
    fputs(": ",file);
   } /* Quellort angegeben */
  for (f = fmt; *f; f++)
   {
    if (*f == '\\' && f[1] != '\0')
     {
      /* -------------- */
      /* escape Sequenz */
      /* -------------- */
      f++;
      if (*f == 'n')
        fputc('\n',file);
      else if (*f == 't')
        fputc('\t',file);
      else /* kein spezielles Zeichen, ohne \ ausgeben */
        fputc(*f,file);
     } /* escape Sequenz */
    else if (*f == '%' && f[1] != '\0')
     { 
      /* ---------------- */
      /* Format-Kontrolle */
      /* ---------------- */
      f++;
      if (*f == 's') /* char */
       {
        char *s;

        s = va_arg(arglist,char *);
        fputs(s,file);
       }
      else if (*f == 'd') /* Integer */
       {
        int i;

	i = va_arg(arglist,int);
	fprintf(file,"%d",i);
       }
      else if (*f == 'c') /* Zeichen */
       {
        int i;

	i = va_arg(arglist,int);
	fputc(i,file);
       }
      else if (*f == 'q') /* Quellort */
       {
        Quellort *q;

	q = va_arg(arglist,Quellort *);
        fdecQuellort(file,q);
       }
      else if (*f == 't') /* Quellort des Tokens */
       {
        Token tok;
	Quellort *q;

	if ((tok = va_arg(arglist,Token)) != NULL)
         {
  	  q = QUELL_ORT(tok);
	  if (SYM(tok) == Keof && QUELL_FN(q) != NULL)
           {
            fputs(QUELL_FN(q),file);
	    fputc(':',file);
           }
          else
            fdecQuellort(file,q); /* normaler Quellort */
         } /* != NULL */
       } /* 't' */
      else if (*f == 'T') /* Token selbst*/
       {
        Token tok;

	if ((tok = va_arg(arglist,Token)) != NULL)
	 {
	  if (SYM(tok) == Keof)
            fputs("END-OF-FILE",file);
          else
            fputs(scanDecode(NULL,tok),file);
	 } /* != NULL */
       } /* Token selbst */
      else
       { /* undefinierte %-Anweisung */
        fputc('%',file);
        fputc(*f,file);
       }
     } /* Format-Kontrolle */
    else
      fputc(*f,file);  /* ganz normales Zeichen */
   } /* for f */
 } /* intern_wErrorf */

/* ====================================================== */
/* neue Schnittstelle: formatierte Fehlermeldung ausgeben */
/* Formate:  %s : char *                                  */
/*           %d : int als Zahl                            */
/*           %c : int als Zeihen                          */
/*           %q : Quellort                                */
/*           %t : Quellort des angegebenen Tokens         */
/*           %T : dekodiertes Token                       */
/*           \n : newline                                 */
/*           \t : Tabulator                               */
/* ====================================================== */
#ifdef __STDC__
void wErrorf(Quellort *ort,char *fmt,va_list va_alist)
#else
void wErrorf(ort,fmt,va_alist)
 Quellort *ort;
 char *fmt;
 va_dcl
#endif
 {
  va_list arglist;

  va_start(arglist);
  intern_wErrorf(stderr,ort,fmt,arglist);
  if (! err_tried && protokoll && errordatei == NULL)
   {
    err_tried = 1;
    OpenErr();
   }
  if (protokoll && errordatei != NULL)
   {
    va_start(arglist);
    intern_wErrorf(errordatei,ort,fmt,arglist);
   }
 } /* wErrorf */
#endif /* L_WERRORF */

#ifdef L_MEMERROR
/* ===================================================== */
/* Fehlermeldung bei chronischem Speichermangel          */
/* ===================================================== */
#ifdef __STDC__
void memError(void)
#else
void memError()
#endif
 {
  wErrorf(NULL,"Arbeitsspeicher voll !!!\n");
 } /* memError */
#endif /* L_MEMERROR */

