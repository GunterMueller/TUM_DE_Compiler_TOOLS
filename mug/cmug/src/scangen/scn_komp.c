
/* ******************************************************************* */
/* scn_comp.c: Kompatibilitaets-Routinen fuer die alten Schnittstellen */
/* erstellt  22.01.91, Ulrich Vollath                                  */
/* ******************************************************************* */

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
#else
extern char *malloc();
#endif
#include <string.h>
#include <stdio.h>

#include "ps_token.h"  /* allgemeine Definitionen fuer Scanner         */
#include "pstokenP.h"  /* private Definitionen fuer Scanner            */
#include "scanfunk.h"  /* Funktionalitaten Scanner                     */
#include "ps_tab.h"
#include "scn_glob.h"

#ifdef L_O_MABORT
/* ===================================================== */
/* Abbruch des Programms bei vollem Speicher             */
/* alte Schnittstelle, nur aus Kompatibilitaetsgruenden  */
/* vorhanden                                             */
/* ===================================================== */
#ifdef __STDC__
void mabort(void)
#else
void mabort()
#endif
 {
  fputs("Speicher voll, Abbruch !\n",stderr);
  EXIT;      /* fataler Fehler */
 } /* mabort */
#endif /* L_O_MABORT */

#ifdef L_O_SCANDECODE
/* ===================================================== */
/* alte Dekoderschnittstelle                             */
/* ===================================================== */
#ifdef __STDC__
void scandecode(char *decstr,long kc,long rc,long pos)
#else
void scandecode(decstr,kc,rc,pos)
 char *decstr;   /* erhaelt dekodiertes token              */
 long kc,rc,pos; /* Eingabe : von Scanner gelieferte Werte */
#endif
 {
  char *res;

  if (decstr == NULL)
    return;
  if ((res = (char *)pos) == NULL)
    res = "nicht dekodierbar";
  strcpy(decstr,res);
 } /* scandecode */
#endif /* L_SCANDECODE */

#ifdef L_O_SCAN
/* *************************************************** */
/* eigentlicher Scanner, Ergebnis : Klasse des Symbols */
/* *************************************************** */
#ifdef __STDC__
long scan(long *rwert,short *rpos,short *rline,short *rcol,char *token)
#else
long scan(rwert,rpos,rline,rcol,token)
  long  *rwert;        /* Relativcode des Symbols     */
  short *rpos;         /* Stelle in der Stringtabelle */
  short *rline,*rcol;  /* Quelltextreferenz           */
  char  *token;        /* Text erkanntes Symbol       */
#endif
  {
   TokenRec tok;

   if (!scanNext(&tok))
     EXIT;
   *rwert = SEMVAL(&tok);
   *rpos  = 0; /* nicht mehr zu dekodieren !!! */
   *rline = (QUELL_ORT(&tok))->zeile;
   *rcol  = (QUELL_ORT(&tok))->spalte;
   if (token != NULL)
     strcpy(token,tok.decinf); 
   return(SYM(&tok)); 
 }
#endif /* L_O_SCAN */
