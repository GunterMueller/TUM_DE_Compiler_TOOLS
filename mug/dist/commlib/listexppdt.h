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
/* ListexpPDT.h  :                                                         */
/* Parametrisierte Datenstruktur fuer sortierte Listen ueber Datentypen    */
/* Struktur  LISTTYP = sorted list of BASISTYP                             */    
/* Listen ohne Wiederholung, wobei Gleichheit ueber ein Makro definiert    */
/* wird                                                                    */
/* entspricht ListenPDT.h, jedoch alle Routinen expandiert, um den         */
/* Overhead der Routinen in Listen.c einzusparen                           */
/* erstellt  : 11.3.89                                                     */
/* ----------------------------------------------------------------------- */
/* vor der #include-Anweisung muessen folgende Makros definiert sein,      */
/* die die Datenstruktur parametisieren :                                  */
/* BASISTYP  : Name des Basistyps der Datenstruktur                        */
/* LISTTYP   : Name des Listen-Datentyps                                   */
/* FREILIS   : Name der Freiliste fuer den Listentyp                       */
/* INITNAME  : Name der Initialisierungsroutine : BOOL INITNAME()          */
/* EINTRNAME : Name der Eintragroutine          : Liste EINTRNAME(...)     */
/* MERGENAME : Name der Mergeroutine            : BOOL MERGENAME(...)      */
/*             kann weggelassen werden, wenn nicht benoetigt               */
/* VERGLEICHE(e1,e2) : Makro,  vergleicht BASISTYP *e1 und *e2             */
/*                     muss als Expression einsetzbar sein : (stat,.. )    */
/*                     Ergebnis  < 0 : *e1 <  *e2                          */
/*                     Ergebnis    0 : *e1 == *e2                          */
/*                     Ergebnis  > 0 : *e1 > *e2                           */
/*                Soll die Liste unsortiert gefuehrt werden, so ist bei    */
/*                     Ungleichheit immer ein Wert < 0 abzuliefern, dann   */
/*                     werden neue Elemente am Listenende angefuegt        */
/*                Falls VERGLEICHE nicht definiert wird, muss die Routine  */
/*                     VERGLNAME getrennt zur Verfuegung gestellt werden   */
/* VERGLNAME         : Name der erzeugten Funktion fuer den Vergleich      */
/* ABGLEICH(z,q)     : Makro Abgleich, ergaenzt ggf. BASISTYP *z um        */
/*                     zusaetzliche Informationen aus *q                   */
/*                     kann weggelassen werden, wenn Abgleich nicht noetig */
/* ABGLNAME          : Name der erzeugten Funktion fuer den Abgleich       */
/*                     kann weggelassen werden, wenn Abgleich nicht noetig */
/* KOPIERE(z,q)      : Makro zum Kopieren der Informationen aus *q in den  */
/*                     Eintrag *z                                          */
/*                Falls KOPIERE nicht definiert wird, muss die Routine     */
/*                     KOPNAME getrennt zur Verfuegung gestellt werden     */
/* KOPNAME           : Name der erzeugten Kopierfunktion                   */ 
/* ABBRUCH           : Makro zum Abbruch des Programmlaufes bei Fehlern    */
/*                     kann weggelassen werden, dann Rueckgabe NULL        */
/* DEBUG             : Einfuegen von printf's fuer Debugging-Zwecke,       */
/*                     falls dieses Symbol definiert ist                   */
/* LISTTYPSTR        : Listtyp als String fuer Debugging-Meldungen,        */
/*                     falls DEBUG definiert ist                           */
/* Die Makrodefinitionen (ausser DEBUG und ABBRUCH) werden am Ende dieser  */
/* Datei geloescht, da sie fuer jede Instantiierung der Datenstruktur      */
/* unterschiedlich definiert werden.                                       */
/* *********************************************************************** */

#include <stdio.h>               /* E/A, NULL etc.                        */
#include <mylib/defs.h>          /* diverse Deklarationen                 */
#include "Listen.h"              /* Deklarationen der Listenoperationen   */
#include "Checks.h"              /* Deklarationen Ueberwachung            */      

static LISTTYP FREILIS=NULL;     /* Freiliste fuer den Datentyp LISTTYP   */

/* ====================================================================== */
/* Eintrag eines Listenelementes "eintrag" in die Liste "liste"           */
/* falls schon ein gleicher Eintrag existiert, erfolgt ein Abgleich der   */
/* Informationen                                                          */
/* Ergebnis : Zeiger auf das erzeugte/gefundene Listenelement             */
/*            NULL, falls Fehler bei der Durchfuehrung (Speicher voll ..) */
/* ====================================================================== */
LISTTYP EINTRNAME __ARGS((LISTTYP *,BASISTYP *));
LISTTYP EINTRNAME(liste,eintrag)
 LISTTYP *liste;         /* Liste, in die der Eintrag erfolgen soll */
 BASISTYP *eintrag;      /* einzutragende Information               */
 {
  register LISTTYP such;   /* Suchzeiger fuer Returnlis zu pos          */ 
  register LISTTYP vorg;   /* Suchzeiger Vorgaenger                     */ 
  register LISTTYP eintr;  /* neuer Eintrag                             */

#ifdef DEBUG
  printf("  eintrag%s(%lx -> %lx,%lx)\n",LISTTYPSTR,(long)liste,(long)*liste,
         (long)eintrag);
#endif
  CHECKPT(liste);                    /* Test Korrektheit des Listenzeigers   */
  CHECKPTN(*liste);                  /* Test Korrektheit der Liste           */
  CHECKPT(eintrag);                  /* Test Korrektheit des Eintrags        */

  /* ----------------------------------------------------------------------- */
  /* in der sortierten Liste suchen, ob passender Eintrag bereits vorhanden  */
  /* ----------------------------------------------------------------------- */
  vorg = NULL;                       /* kein Vorgaenger                       */
  for(such = *liste; such != NULL; such = LISTNEXT(*such) )
   {    /* Element in allen Eintraegen such suchen */
    register int   verg;                /* Ergebnis des Vergleiches           */

    if ((verg = VERGLEICHE(such,eintrag))
                         <0 )              /* such zu klein, weiter suchen    */
      vorg = such;                         /* Vorgaenger fuer Einfuegen merken*/
    else if (verg > 0)                     /* Rest der Liste groesser         */
      break;                               /* hier neuen Eintrag einfuegen    */
    else                                   /* passender Eintrag gefunden      */
     {
#ifdef ABGLNAME                        /* Abgleich noetig                     */
#ifdef ABGLEICH                        /* als Makro definiert                 */
      ABGLEICH(such,eintrag);          /* Informationen abgleichen            */
#else                                  /* als Funktion definiert              */
      ABGLNAME(such,eintrag);          /* Abgleichfunktion aufrufen           */
#endif ABGLEICH
#endif ABGLNAME
      return(such);                    /* Suche beendet, Eintrag melden       */
     }
   } /* for */
  /* ----------------------------------------------------------------------- */
  /* noch kein Eintrag vorhanden, zwischen vorg und NEXTRET(vorg) einhaengen */
  /* ----------------------------------------------------------------------- */
   { 
#ifdef ABBRUCH
    if ((eintr = (LISTTYP)flAllocate(sizeof(BASISTYP),
                                   (char**)FREILIS)) == NULL) /* Reservierung */
      ABBRUCH;                      /* Programmlauf abbrechen                 */
#else
    if ((eintr = (LISTTYP)flAllocate(sizeof(BASISTYP),
                                   (char**)FREILIS)) == NULL) /* Reservierung */
      return(NULL);                 /* Speicher voll, melden                  */
#endif

#ifdef KOPIERE                         /* als Makro definiert                 */
    KOPIERE(eintr,eintrag);            /* Informationen kopieren              */
#else                                  /* als Funktion definiert              */
    KOPNAME(eintr,eintrag);            /* Kopierfunktion aufrufen             */
#endif KOPIERE
    if (vorg == NULL)               /* kein Listen-Vorgaenger vorhanden       */
      *liste = eintr;               /* wird erster Eintrag                    */
    else
      LISTNEXT(*vorg) = eintr;      /* Nachfolger von vorg                    */
    LISTNEXT(*eintr) = such;        /* Listenrest anhaengen                   */
    return(eintr);                  /* neuen Eintrag melden                   */
   }
 } /* EINTRNAME */

/* ====================================================================== */
/* Ergaenzen LISTTYP *ziel um die Informationen von LISTTYP quelle        */
/* Entspricht Kopieren, falls *ziel leer ist                              */
/* Ergebnis : TRUE : erfolgreich                                          */
/*            FALSE,falls Fehler bei der Durchfuehrung (Speicher voll ..) */
/* ====================================================================== */
#ifdef MERGENAME /* Routine wird benoetigt */
BOOL MERGENAME __ARGS((LISTTYP *,LISTTYP));
BOOL MERGENAME(ziel,quelle)
 LISTTYP *ziel;      /* Liste, in die der Eintrag erfolgen soll     */
 LISTTYP  quelle;    /* Liste der einzutragenden Informationen      */
 {
  register LISTTYP such;   /* Suchzeiger fuer Returnlis zu pos          */ 
  register LISTTYP zeintr; /* aktueller Eintrag in Zielliste            */ 
  register LISTTYP zvorg;  /* Vorgaenger in Zielliste                   */ 
  register int   verg;     /* Ergebnis des Vergleiches                  */
  register LISTTYP eintr;  /* neuer Eintrag                             */

#ifdef DEBUG
  printf("  merge%s(%lx -> %lx,%lx)\n",LISTTYPSTR,(long)ziel,(long)*ziel,
            (long)quelle);
#endif
  CHECKPT(ziel);                     /* Test Korrektheit des Zielzeigers     */
  CHECKPTN(*ziel);                   /* Test Korrektheit der Zielliste       */
  CHECKPTN(quelle);                  /* Test Korrektheit der Quelliste       */

  zeintr = *ziel;                    /* erster Eintrag in Zielliste          */
  zvorg = NULL;                      /* kein Vorgaenger                      */
  such = quelle;                     /* erster Quelleintrag                  */
  while (such != NULL)               /* solange Informationen vorhanden      */
   { /* alle Eintraege in quelle suchen         */
    if (zeintr == NULL ||               /* Rest der Zielliste leer           */
      (verg = VERGLEICHE(such,zeintr) ) /* Inhalte vergleichen               */
                        < 0 )           /* Rest der Zielliste groesser       */
     { /* hier einfuegen */
#ifdef ABBRUCH
      if ((eintr = (LISTTYP)flAllocate(sizeof(BASISTYP),(char**)freil)) == NULL)
        ABBRUCH;                  /* Programmlauf abbrechen                  */
#else
      if ((eintr = (LISTTYP)flAllocate(sizeof(BASISTYP),(char**)freil)) == NULL)
        return(FALSE);            /* Speicher voll, melden                   */
#endif
#ifdef KOPIERE                         /* als Makro definiert                 */
      KOPIERE(eintr,such);             /* Informationen kopieren              */
#else                                  /* als Funktion definiert              */
      KOPNAME(eintr,such);             /* Kopierfunktion aufrufen             */
#endif KOPIERE
      if (zvorg == NULL)          /* kein Listen-Vorgaenger vorhanden        */
        *ziel = eintr;            /* wird erster Eintrag                     */
      else
        LISTNEXT(*zvorg) = eintr; /* eintr wird Nachfolger von vorg          */
      zvorg = eintr;              /* Vorgaenger merken                       */
      LISTNEXT(*eintr) = zeintr;  /* Listenrest anhaengen                    */
      such = LISTNEXT(*such);     /* naechste Quellinformation               */
     } /* hier einfuegen */
    else /* zeintr != NULL && verg >= 0 */
     {
#ifdef ABGLNAME                        /* Abgleich noetig                     */
#ifdef ABGLEICH                        /* als Makro definiert                 */
      if (verg==0)                     /* Abgleich notwendig                  */
        ABGLEICH(zeintr,such);         /* Informationen abgleichen            */
#else                                  /* als Funktion definiert              */
      if (verg==0)                     /* Abgleich notwendig                  */
        ABGLNAME(zeintr,such);         /* Abgleichfunktion aufrufen           */
#endif ABGLEICH
#endif ABGLNAME
      /* Zielzeiger weiterhaengen */
      zvorg = zeintr;              /* Vorgaenger merken                       */
      zeintr = LISTNEXT(*zeintr);  /* naechster Eintrag in Zielliste          */
     }
   } /* FOREACHLISTEL */
#ifdef DEBUG
  printf("  merge%s Ende\n",LISTTYPSTR);  
#endif
 return(TRUE);
 } /* MERGENAME */
#endif MERGENAME /* Routine wird benoetigt */

#ifdef FREELISNAME
/* ====================================================================== */
/* Freigabe einer ganzen Liste von Eintraegen                             */
/* ====================================================================== */
void FREELISNAME __ARGS((LISTTYP));
void FREELISNAME(lis)
 LISTTYP lis;          /* erster Eintrag in der freizugebenden Liste */
 {
  CHECKPTN(lis);                             /* Test Korrektheit der Liste    */
  if (lis != NULL)                           /* aus Effizienzgruenden pruefen */
    flFreelis((char**)lis,(char**)&FREILIS); /* in Speicherverwalt. freigeben */
 } /* FREELISNAME */
#endif FREELISNAME

/* ====================================================================== */
/* Initialisierung der parametrisierten Datenstruktur                     */
/* muss vor der ersten Verwendung einer anderen Operation auf der         */
/* Datenstruktur aufgerufen werden                                        */
/* Ergebnis : TRUE, falls Initialisierung erfolgreich                     */
/*            FALSE, falls Fehler bei Initialisierung                     */
/* ====================================================================== */
BOOL INITNAME()
 {
#ifdef DEBUG
  printf("  init%s()\n",LISTTYPSTR);
#endif
  FREILIS = NULL;                /* Freiliste leer initialisieren         */
#ifdef DEBUG
  printf("  init%s Ende\n",LISTTYPSTR);
#endif
  return(TRUE);                  /* immer erfolgreich beendet             */
 } /* INITNAME */

/* ====================================================================== */
/* Loeschen der Parametermakros                                           */
/* ====================================================================== */
#undef BASISTYP
#undef LISTTYP 
#undef FREILIS 
#undef INITNAME
#undef EINTRNAME
#undef MERGENAME
#undef FREELISNAME
#undef VERGLEICHE
#undef VERGLNAME
#undef ABGLEICH
#undef ABGLNAME 
#undef KOPIERE
#undef KOPNAME 
#undef LISTTYPSTR

