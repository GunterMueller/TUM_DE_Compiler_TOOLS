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
/* allocate.c  :                                                          */
/* allgemeine Speicherverwaltungsroutinen                                 */
/* die verwalteten Typen muessen im ersten Feld einen Pointer enthalten,  */
/* der zur Freilistenverkettung verwendet wird                            */
/* Aenderung : 04.05.90, Statistikinformationen                           */
/* Aenderung : 29.04.90, #ifdef __STDC__                                  */
/* Aenderung : 8.3.89 , Ueberwachungen zur Laufzeit                       */
/* erstellt  : 28.1.89                                                    */
/* ********************************************************************** */
#ifdef __STDC__
#include <stddef.h>
#include <stdlib.h>
#else
extern char *malloc();
#endif
#include <stdio.h>          /* E/A, NULL etc.                             */
#include "checks.h"         /* Deklarationen Ueberwachungen               */
#include "allocate.h"       /* Deklarationen Speicherverwaltung           */

unsigned stat_total_alloc;  /* Gesamtgroesse allokierter Speicher         */

/* --------------------------------------------------------- */
/* Anzahl der gleichzeitig reservierten Elemente             */
/* 2-er-Potenz spart eine Multiplikation (SHIFT)             */
/* --------------------------------------------------------- */
#define POOL (unsigned)64

/* ====================================================================== */
/* Speicherreservierung fuer einen gegebenen Typen                        */
/* unter Beruecksichtigung einer Freiliste                                */ 
/* falls Reservierung nicht moeglich, Rueckgabe von NULL                  */
/* um Overhead und Speicherfragmentierung zu verringern, werden immer     */
/* POOL Elemente gleichzeitig mit malloc() reserviert                     */
/* ====================================================================== */
#ifdef __STDC__
char *flAllocate(unsigned size,char **fl)
#else
char *flAllocate( size, fl)
 unsigned size;  /* Groesse eines Elements des Typs                  */
 char **fl;      /* Freiliste zu diesem Typ                          */
#endif
 {
  register char *pt;    /* Zeiger auf reserviertes Element                    */
  register char **fe;   /* Zeiger auf Freilisten-Element                      */
  register short i;     /* Zaehler fuer Freilistendruchlauf                   */

  CHECKPT(fl);
  CHECKPTN(*fl);
  if ( (pt = *fl)==NULL )
   /* --------------------------------------------------------------- */
   /* die Freiliste ist leer, Speicher mit malloc() reservieren       */
   /* --------------------------------------------------------------- */
   {
    if ( (pt = (char *)malloc(size*POOL)) == NULL) /* POOL Elemente reservieren */
     { /* kein Speicher, Versuch, 1 Element zu reserv.*/
      if ( (pt = (char *)malloc(size)) != NULL) 
        stat_total_alloc += size;
      return(pt);
     } /* kein Speicher */
    stat_total_alloc += size*POOL;
    fe  = (char **)(pt+size); /* Zeiger auf erstes freies Element pt[1]       */
    *fl = (char *)fe;         /* wird Freilistenanfang                        */
    for (i=1; i<POOL-1; i++)  /* alle zusaetzlich reserv. Elemente verketten  */
     {
      *fe = (char *)fe+size;  /* Next-Zeiger auf direkten Nachfolger richten  */
      fe = (char **)*fe;      /* Zeiger auf naechstes Element setzen          */
     }
    *fe = NULL;               /* letztes Element hat keinen Nachfolger        */
   }
  else                   
   /* ----------------------------------------------------------------------- */
   /* Freiliste nicht leer , erstes Freilistenelement verwenden, Zeiger in pt */
   /* ----------------------------------------------------------------------- */
    *fl = *(char **)pt;   /* Freilistenzeiger auf naechstes Element setzen    */
  return(pt);      /* Zeiger auf reseviertes Element abliefern               */
 } /* flAllocate */

/* ====================================================================== */
/* Speicherfreigabe fuer ein Element eines gegebenen Typen                */
/* Eintrag in Freiliste                                                   */ 
/* ====================================================================== */
#ifdef __STDC__
void flFree(char **el,char **fl)
#else
void flFree( el, fl)
 register char **el;    /* Zeiger auf freizugebendes Element                  */
 register char **fl;    /* Freiliste zu diesem Typ                            */
#endif
 {
  if (el != NULL)       /* Element vorhanden ?                                */
   {  /* vorne in Freiliste einfuegen    */
    CHECKPT(el);
    CHECKPT(fl);
    CHECKPTN(*fl);
    *el = *fl;          /* wird erstes Element, Listenrest als next anhaengen */
    *fl = (char *)el;   /* Freilistenzeiger auf freigegebenes Element setzen  */    
   }
 } /* flFree */

/* ====================================================================== */
/* Speicherfreigabe fuer eine Liste eines gegebenen Typen                 */
/* Eintrag in Freiliste                                                   */ 
/* ====================================================================== */
#ifdef __STDC__
void flFreelis(char **lis,char **fl)
#else
void flFreelis( lis, fl)
 register char **lis;     /* Zeiger erstes Element der freizugebenden Liste  */
 register char **fl;      /* Freiliste zu diesem Typ                         */
#endif
 {
  register char **fe;     /* Element in der freizugebenden Liste             */

    if (lis != NULL)        /* Liste nicht leer ?                              */
   {
#ifdef DEBUG
    printf("flFreelis lis %lx :\n",(long)lis);
    for (fe = lis;fe != NULL; fe = (char**)*fe)
      printf("<%lx>",(long)fe); 
    printf("\n          fl  %lx :\n",(long)fl);
    for (fe = (char**)*fl;fe != NULL; fe = (char**)*fe)
      printf("<%lx>",(long)fe); 
    printf("\n");
#endif
    CHECKPT(fl);
    CHECKPTN(*fl);
    /* ------------------------------------------- */
    /* Ende der freizugebenden Liste suchen        */
    /* ------------------------------------------- */
    for (fe = lis; *fe != NULL; fe = (char **)*fe)
       CHECKPT(fe);     /* bis next-Zeiger == NULL gefunden                  */
    /* --------------------------------------------------- */
    /* freizugebende Liste vorne in Freiliste einfuegen    */
    /* --------------------------------------------------- */
    *fe = *fl;          /* bisherige Freiliste an letztes Element anhaengen  */
    *fl = (char *)lis;  /* Freilistenzeiger auf freigegebene Liste setzen    */    
#ifdef DEBUG
    printf("\n          ->  %lx :\n",(long)fl);
    for (fe = (char**)*fl;fe != NULL; fe = (char**)*fe)
      printf("<%lx>",(long)fe); 
    printf("\n");
#endif
   }
 } /* flFreelis */	

