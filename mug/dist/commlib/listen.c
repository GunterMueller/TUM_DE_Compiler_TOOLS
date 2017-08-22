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
/* listen.c  :                                                            */
/* Verwaltungsroutinen fuer sortierte Listen ueber Datentypen             */
/* die erzeugten Datenstrukturen werden in aufrufenden Modul als char *   */
/* verwaltet, Struktur SORTED LIST OF (info)                              */    
/* Die Listen werden ohne Wiederholung gefuehrt                           */
/* Aenderung : 29.04.90, #ifdef __STDC__                                  */
/* Aenderung : 16.02.90 listenSuche einkopiert aus zweiter Version        */
/* Aenderung : 29.01.90 Bug in listenMerge                                */
/* erstellt  : 3.2.89                                                     */
/* ********************************************************************** */

#include <stdio.h>          /* E/A, NULL etc.                             */
#include "defs.h"           /* diverse Deklarationen                      */
#include "allocate.h"       /* Deklarationen Speicherverwaltung           */
#include "listen.h"         /* Deklarationen Listenverwaltung             */

/* ====================================================================== */
/* Eintragen der Kopie einer Information in eine Liste                    */
/* Neueintrag erfolgt, falls Information noch nicht vorhanden, sonst      */
/* Abgleich zwischen vorhandener und neuer Information                    */
/* Rueckgabe : Zeiger auf Listenelement                                   */
/*             NULL, falls kein Speicher fuer neue Eintraege              */
/* ====================================================================== */
#ifdef __STDC__
Liste listenEintrag(Liste *liste,Liste el,int (*vergl)(Liste,Liste),
                    void (*abgl)(Liste,Liste),void (*cpy)(Liste,Liste),
                    unsigned size,Liste *freil)
#else
Liste listenEintrag(liste,el,vergl,abgl,cpy,size,freil)
 Liste *liste;   /* Liste, in die eingetragen werden soll    */
 Liste el;       /* Zeiger auf einzutragendes Listenlement   */
  /* ....................................................... */
  /* Vergleichsroutine, liefert < 0, falls *info <  element  */
  /*                              0, falls *info == element  */
  /*                            > 0, falls *info <  element  */
  /* ....................................................... */
 int (*vergl)(/*  Liste info, Liste el  */ ); 
  /* ................................................................ */
  /* Abgleichroutine, wird aufgerufen, wenn Eintrag bereits vorhanden */
  /* Argument : bereits vorhandener Eintrag                           */
  /* falls Abgleich nicht gewuenscht : NULL                           */
  /* ................................................................ */
 void (*abgl)(/*  Liste info, Liste el   */ ); 
  /* ........................................................ */
  /* Kopierroutine, um Information in neuen Eintrag schreiben */
  /* ........................................................ */
 void (*cpy)(/*  Liste dest, Liste source   */ ); 
 unsigned size;  /* Groesse eines Elements des Typs          */
 Liste *freil;   /* Freiliste zu diesem Listentyp            */
#endif
 {
  register Liste such;   /* Suchzeiger fuer Returnlis zu pos          */ 
  register Liste vorg;   /* Suchzeiger Vorgaenger                     */ 

  /* ----------------------------------------------------------------------- */
  /* in der sortierten Liste suchen, ob passender Eintrag bereits vorhanden  */
  /* ----------------------------------------------------------------------- */
  vorg = NULL;                       /* kein Vorgaenger                       */
  for(such = (Liste)*liste; such != NULL; such = (Liste)*such)
   {    /* Element in allen Eintraegen such suchen */
    register int   verg;             /* Ergebnis des Vergleiches              */

    if ((verg = vergl(such,el))<0)   /* such zu klein, weiter suchen          */
      vorg = such;                   /* Vorgaenger fuer Einfuegen merken      */
    else if (verg > 0)               /* Rest der Liste groesser               */
      break;                         /* hier neuen Eintrag einfuegen          */
    else                             /* passender Eintrag gefunden            */
     {
      if (abgl != NULL)              /* Abgleich notwendig                    */
        abgl(such,el);               /* Informationen abgleichen              */
      return(such);                  /* Suche beendet, Eintrag melden         */
     }
   } /* for */
  /* ----------------------------------------------------------------------- */
  /* noch kein Eintrag vorhanden, zwischen vorg und NEXTRET(vorg) einhaengen */
  /* ----------------------------------------------------------------------- */
   { 
    register Liste eintr;           /* neuer Eintrag                          */

    if ((eintr = (Liste)flAllocate(size,
                                   (char**)freil)) == NULL) /* Reservierung   */
      return(NULL);                 /* Speicher voll, melden                  */
    cpy(eintr,el);                  /* Informationen kopieren                 */
    if (vorg == NULL)               /* kein Listen-Vorgaenger vorhanden       */
      *liste = eintr;               /* wird erster Eintrag                    */
    else
      *vorg = (char *)eintr;        /* Nachfolger von vorg                    */
    *eintr = (char *)such;          /* Listenrest anhaengen                   */
    return(eintr);                  /* neuen Eintrag melden                   */
   }
 } /* listenEintrag */

/* ====================================================================== */
/* Suchen einer Information in einer Liste                                */
/* Rueckgabe : Zeiger auf Listenelement                                   */
/*             NULL, falls nicht in Liste vorhanden                       */
/* ====================================================================== */
#ifdef __STDC__
Liste listenSuche(Liste *liste,Liste el,int (*vergl)(Liste,Liste))
#else
Liste listenSuche(liste,el,vergl)
 Liste *liste;   /* Liste, in der gesucht werden soll        */
 Liste el;       /* Zeiger auf einzutragendes Listenlement   */
  /* ....................................................... */
  /* Vergleichsroutine, liefert < 0, falls *info <  element  */
  /*                              0, falls *info == element  */
  /*                            > 0, falls *info <  element  */
  /* ....................................................... */
 int (*vergl)(/*  Liste info, Liste el  */ ); 
#endif
 {
  register Liste such;   /* Suchzeiger fuer Returnlis zu pos          */ 
  register Liste vorg;   /* Suchzeiger Vorgaenger                     */ 

  /* ----------------------------------------------------------------------- */
  /* in der sortierten Liste suchen, ob passender Eintrag vorhanden          */
  /* ----------------------------------------------------------------------- */
  vorg = NULL;                       /* kein Vorgaenger                       */
  for(such = (Liste)*liste; such != NULL; such = (Liste)*such)
   {    /* Element in allen Eintraegen such suchen */
    register int   verg;             /* Ergebnis des Vergleiches              */

    if ((verg = vergl(such,el))<0)   /* such zu klein, weiter suchen          */
      continue;  
    else if (verg > 0)               /* Rest der Liste groesser               */
      return(NULL);                  /* dann nicht vorhanden                  */
    else                             /* passender Eintrag gefunden            */
      return(such);                  /* Suche beendet, Eintrag melden         */
   } /* for */
  return(NULL);                      /* Listenende, nicht vorhanden           */
 } /* listenSuche */

/* ====================================================================== */
/* Eintragen der neuen Informationen einer Liste in eine andere Liste     */
/* Neueintrag erfolgt, falls Information noch nicht vorhanden, sonst      */
/* Abgleich zwischen vorhandener und neuer Information                    */
/* Rueckgabe : TRUE, falls erfolgreich                                    */
/*             FALSE, falls kein Speicher fuer neue Eintraege             */
/* ====================================================================== */
#ifdef __STDC__
BOOL listenMerge(Liste *ziel,Liste quelle,int (*vergl)(Liste,Liste),
                 void (*abgl)(Liste,Liste),void (*cpy)(Liste,Liste),
                 unsigned size,Liste *freil)
#else
BOOL listenMerge(ziel,quelle,vergl,abgl,cpy,size,freil)
 Liste *ziel;    /* Liste, in die eingetragen werden soll                */
 Liste quelle;   /* Liste, deren Informationen eingetragen werden sollen */
  /* ....................................................... */
  /* Vergleichsroutine, liefert < 0, falls *info <  element  */
  /*                              0, falls *info == element  */
  /*                            > 0, falls *info <  element  */
  /* ....................................................... */
 int (*vergl)(/*  Liste info, Liste el  */ ); 
  /* ................................................................ */
  /* Abgleichroutine, wird aufgerufen, wenn Eintrag bereits vorhanden */
  /* Argument : bereits vorhandener Eintrag                           */
  /* falls Abgleich nicht gewuenscht : NULL                           */
  /* ................................................................ */
 void (*abgl)(/*  Liste info, Liste el   */ ); 
  /* ........................................................ */
  /* Kopierroutine, um Information in neuen Eintrag schreiben */
  /* ........................................................ */
 void (*cpy)(/*  Liste dest, Liste source   */ ); 
 unsigned size;  /* Groesse eines Elements des Typs          */
 Liste *freil;   /* Freiliste zu diesem Listentyp            */
#endif
 {
  register Liste such;   /* Suchzeiger fuer Returnlis zu pos          */ 
  register Liste zeintr; /* aktueller Eintrag in Zielliste            */ 
  register Liste zvorg;  /* Vorgaenger in Zielliste                   */ 
  register int   verg;   /* Ergebnis des Vergleiches                  */
  register Liste eintr;  /* neuer Eintrag                             */

#ifdef DEBUG
  printf("      listenMerge(%lx -> %lx,%lx)\n",(long)ziel,(long)*ziel,
                (long)quelle);
#endif
  zeintr = *ziel;                 /* erster Eintrag in Zielliste             */
  zvorg = NULL;                   /* kein Vorgaenger                         */
  such = quelle;                  /* erster Quelleintrag                     */
  while (such != NULL)            /* solange Informationen vorhanden         */
   { /* alle Eintraege in quelle suchen         */
    if (zeintr == NULL ||          /* Rest der Zielliste leer                */
      (verg = vergl(such,zeintr) ) /* Inhalte vergleichen                    */
                        < 0 )      /* Rest der Zielliste groesser            */
     { /* hier einfuegen */
      if ((eintr = (Liste)flAllocate(size,(char**)freil)) == NULL)
        return(FALSE);            /* Speicher voll, melden                   */
      cpy(eintr,such);            /* Information kopieren                    */
      if (zvorg == NULL)          /* kein Listen-Vorgaenger vorhanden        */
        *ziel = eintr;            /* wird erster Eintrag                     */
      else
        *zvorg = (char *)eintr;   /* eintr wird Nachfolger von vorg          */
      zvorg = eintr;              /* Vorgaenger merken                       */
      *eintr = (char *)zeintr;    /* Listenrest anhaengen                    */
      such = (Liste)*such;        /* naechste Quellinformation               */
     } /* hier einfuegen */
    else /* zeintr != NULL && verg >= 0 */
     {
      if (verg==0 && abgl != NULL) /* Abgleich notwendig                      */
        abgl(zeintr,such);         /* Informationen abgleichen                */
      if (verg == 0)
        such = (Liste)*such;        /* naechste Quellinformation (uv, 29.1.90)*/
      /* Zielzeiger weiterhaengen */
      zvorg = zeintr;              /* Vorgaenger merken                       */
      zeintr = (Liste)*zeintr;     /* naechster Eintrag in Zielliste          */
     }
   } /* FOREACHLISTEL */
#ifdef DEBUG
  printf("      listenMerge Ende\n");
#endif
  return(TRUE);                    /* erfolgreich beendet                     */
 } /* listenMerge */


