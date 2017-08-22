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
/* KellerPDT.h  :                                                          */
/* Parametrisierte Datenstruktur fuer Keller ueber Datentypen              */
/* Die Basisstruktur ist die gleiche wie bei ListenPDT.h                   */
/* aufgrund des kompakten Aufbaus der Routinen werden alle expandiert      */
/* Struktur  LISTTYP = Keller of BASISTYP                                  */    
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
/* Kopierroutine fuer die Listenverwaltung                                */
/* kopiert Informationen von BASISTYP *e2 nach BASISTYP *e2               */
/* ====================================================================== */
#ifdef KOPIERE                   /* falls Routine nicht getrennt definiert */
static void KOPNAME __ARGS(( BASISTYP *,BASISTYP *));
static void KOPNAME(e1,e2)
 BASISTYP *e1;                   /* Ziel der Kopieroperation               */
 BASISTYP *e2;                   /* Quelle der Kopieroperation             */
 {
  CHECKPT(e1);                   /* Test Korrektheit des ersten Zeigers  */
  CHECKPT(e2);                   /* Test Korrektheit des zweiten Zeigers */
  KOPIERE(e1,e2);                /* Kopiermakro benutzen                  */
 } /* KOPNAME */
#endif KOPIERE                   /* falls Routine nicht getrennt definiert */

/* ====================================================================== */
/* Eintrag eines Kellerelementes "eintrag" in den Keller "liste" (push)   */
/* Ergebnis : Zeiger auf das erzeugte/gefundene Listenelement             */
/*            NULL, falls Fehler bei der Durchfuehrung (Speicher voll ..) */
/* ====================================================================== */
LISTTYP EINTRNAME __ARGS((LISTTYP *,BASISTYP *));
LISTTYP EINTRNAME(liste,eintrag)
 register LISTTYP *liste;   /* Keller, in den der Eintrag erfolgen soll */
 BASISTYP *eintrag;         /* einzutragende Information                */
 {
  register LISTTYP erg;       /* neuer Eintrag                            */

#ifdef DEBUG
  printf("  eintrag%s(%lx -> %lx,%lx)\n",LISTTYPSTR,(long)liste,(long)*liste,
         (long)eintrag);
#endif
  CHECKPT(liste);                    /* Test Korrektheit des Listenzeigers   */
  CHECKPTN(*liste);                  /* Test Korrektheit der Liste           */
  CHECKPT(eintrag);                  /* Test Korrektheit des Eintrags        */

#ifdef ABBRUCH   /* Abbruchmakro angegeben   */
  if ((erg = (LISTTYP)flAllocate(sizeof(BASISTYP),(char**)&FREILIS))==NULL)
    ABBRUCH;                         /* Programmlauf beenden                 */
#else
  if ((erg = (LISTTYP)flAllocate(sizeof(BASISTYP),(char**)&FREILIS))==NULL)
    return(NULL);                    /* Speicher voll, melden                */
#endif
  KOPIERE(erg,eintrag);              /* Informationen kopieren               */ 
  LISTNEXT(*erg) = *liste;           /* Listenrest anhaengen                 */
  *liste = erg;                      /* erg ist erstes Element               */
  return(erg);                       /* neuen Eintrag melden                 */
 } /* EINTRNAME */

/* ====================================================================== */
/* Ergaenzen LISTTYP *ziel um die Informationen von LISTTYP quelle        */
/* der gesamte Keller quelle wird kopiert und vorne in ziel eingehaengt   */
/* Ergebnis : TRUE : erfolgreich                                          */
/*            FALSE,falls Fehler bei der Durchfuehrung (Speicher voll ..) */
/* ====================================================================== */
#ifdef MERGENAME /* Routine wird benoetigt */
BOOL MERGENAME __ARGS((LISTTYP *,LISTTYP));
BOOL MERGENAME(ziel,quelle)
 LISTTYP *ziel;           /* Keller, in den der Eintrag erfolgen soll     */
 LISTTYP  quelle;         /* Liste der einzutragenden Informationen       */
 {
  register LISTTYP erg;   /* neuer Eintrag                                */
  register LISTTYP eintr; /* Element von quelle                           */

#ifdef DEBUG
  printf("  merge%s(%lx -> %lx,%lx)\n",LISTTYPSTR,(long)ziel,(long)*ziel,
            (long)quelle);
#endif
  CHECKPT(ziel);                     /* Test Korrektheit des Zielzeigers     */
  CHECKPTN(*ziel);                   /* Test Korrektheit der Zielliste       */
  CHECKPTN(quelle);                  /* Test Korrektheit der Quelliste       */

  for (eintr = quelle; eintr != NULL ; eintr = LISTNEXT(*eintr) )
   { /* alle Eintraege von quelle kopieren */
#ifdef ABBRUCH   /* Abbruchmakro angegeben   */
    if ((erg = (LISTTYP)flAllocate(sizeof(BASISTYP),(char**)&FREILIS))==NULL)
      ABBRUCH;                         /* Programmlauf beenden               */
#else
    if ((erg = (LISTTYP)flAllocate(sizeof(BASISTYP),(char**)&FREILIS))==NULL)
      return(FALSE);                   /* Speicher voll, melden              */
#endif
    KOPIERE(erg,eintr);                /* Informationen kopieren             */ 
    LISTNEXT(*erg) = *ziel;            /* Listenrest anhaengen               */
    *ziel = erg;                       /* erg ist erstes Element             */
   } /* alle Eintraege von quelle kopieren */
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
  CHECKPTN(lis);                           /* Test Korrektheit der Liste      */
  flFreelis((char**)lis,(char**)&FREILIS); /* in Speicherverwaltung freigeben */
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
#undef KOPIERE
#undef KOPNAME 
#undef LISTTYPSTR

