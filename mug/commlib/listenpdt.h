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
/* ListenPDT.h  :                                                          */
/* Parametrisierte Datenstruktur fuer sortierte Listen ueber Datentypen    */
/* Struktur  LISTTYP = sorted list of BASISTYP                             */
/* Listen ohne Wiederholung, wobei Gleichheit ueber ein Makro definiert    */
/* wird                                                                    */
/* Aenderung : 29.04.90, #ifdef __STDC__                                   */
/* Aenderung : 19.1.90, SUCHNAME ...                                       */
/* Aenderung :  7.3.89, Ueberwachungen zur Laufzeit                        */
/* Aenderung :  1.3.89, Routine FREELISNAME                                */
/* Aenderung : 20.2.89, __ARGS-Definitionen                                */
/* erstellt  : 6.2.89                                                      */
/* ----------------------------------------------------------------------- */
/* vor der #include-Anweisung muessen folgende Makros definiert sein,      */
/* die die Datenstruktur parametisieren :                                  */
/* BASISTYP  : Name des Basistyps der Datenstruktur                        */
/* LISTTYP   : Name des Listen-Datentyps                                   */
/* FREILIS   : Name der Freiliste fuer den Listentyp                       */
/* INITNAME  : Name der Initialisierungsroutine : BOOL INITNAME()          */
/* EINTRNAME : Name der Eintragroutine          : Liste EINTRNAME(...)     */
/* SUCHNAME  : Name der Suchroutine             : Liste SUCHNAME(...)      */
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
#include "defs.h"                /* diverse Deklarationen                 */
#include "listen.h"              /* Deklarationen der Listenoperationen   */
#include "checks.h"              /* Deklarationen Ueberwachung            */      

static LISTTYP FREILIS=NULL;     /* Freiliste fuer den Datentyp LISTTYP   */

#ifdef __STDC__
#define LISTPARAMS (Liste,Liste)
#else
#define LISTPARAMS ()
#endif

/* ====================================================================== */
/* Vergleichsroutine fuer die Listenverwaltung                            */
/* vergleicht zwei BASISTYP *e1, *e2                                      */
/* Ergebnis :     < 0 : *e1 <  *e2                                        */
/*                  0 : *e1 == *e2                                        */
/*                > 0 : *e1 > *e2                                         */
/* ====================================================================== */
#ifdef VERGLEICHE               /* falls Routine nicht getrennt definiert */
#ifdef __STDC__
static int VERGLNAME(LISTTYP e1,LISTTYP e2)
#else
static int VERGLNAME(e1,e2)
 LISTTYP e1;                       /* erster zu vergleichender Eintrag     */
 LISTTYP e2;                       /* zweiter zu vergleichender Eintrag    */
#endif
 {
  CHECKPT(e1);                       /* Test Korrektheit des ersten Zeigers  */
  CHECKPT(e2);                       /* Test Korrektheit des zweiten Zeigers */
  return((int)(VERGLEICHE(e1,e2)));  /* Vergleichsmakro benutzen             */
 } /* VERGLNAME */
#endif VERGLEICHE    /* falls Routine nicht getrennt definiert */

/* ====================================================================== */
/* Abgleichroutine fuer die Listenverwaltung                              */
/* ergaenzt BASISTYP *e1 um Informationen von BASISTYP *e2                */
/* ====================================================================== */
#ifdef ABGLEICH                  /* falls Abgleich noetig                 */
#ifdef __STDC__
static void ABGLNAME(LISTTYP e1,LISTTYP e2)
#else
static void ABGLNAME(e1,e2)
 LISTTYP e1;                   /* erster zu vergleichender Eintrag      */
 LISTTYP e2;                   /* zweiter zu vergleichender Eintrag     */
#endif
 {
  CHECKPT(e1);                   /* Test Korrektheit des ersten Zeigers  */
  CHECKPT(e2);                   /* Test Korrektheit des zweiten Zeigers */
  ABGLEICH(e1,e2);               /* Abgleichmakro benutzen                */
 } /* ABGLNAME */
#endif ABGLEICH                  /* falls Abgleich noetig                 */

/* ====================================================================== */
/* Kopierroutine fuer die Listenverwaltung                                */
/* kopiert Informationen von BASISTYP *e2 nach BASISTYP *e2               */
/* ====================================================================== */
#ifdef KOPIERE                   /* falls Routine nicht getrennt definiert */
#ifdef __STDC__
static void KOPNAME( LISTTYP e1,LISTTYP e2)
#else
static void KOPNAME(e1,e2)
 LISTTYP e1;                   /* Ziel der Kopieroperation               */
 LISTTYP e2;                   /* Quelle der Kopieroperation             */
#endif
 {
  CHECKPT(e1);                   /* Test Korrektheit des ersten Zeigers  */
  CHECKPT(e2);                   /* Test Korrektheit des zweiten Zeigers */
  KOPIERE(e1,e2);                /* Kopiermakro benutzen                  */
 } /* KOPNAME */
#endif KOPIERE                   /* falls Routine nicht getrennt definiert */

/* ====================================================================== */
/* Eintrag eines Listenelementes "eintrag" in die Liste "liste"           */
/* falls schon ein gleicher Eintrag existiert, erfolgt ein Abgleich der   */
/* Informationen                                                          */
/* Ergebnis : Zeiger auf das erzeugte/gefundene Listenelement             */
/*            NULL, falls Fehler bei der Durchfuehrung (Speicher voll ..) */
/* ====================================================================== */
#ifdef __STDC__
LISTTYP EINTRNAME(LISTTYP *liste,BASISTYP *eintrag)
#else
LISTTYP EINTRNAME(liste,eintrag)
 LISTTYP *liste;         /* Liste, in die der Eintrag erfolgen soll */
 BASISTYP *eintrag;      /* einzutragende Information               */
#endif
 {
  register LISTTYP erg;  /* Ergebnis des Eintragens                 */

#ifdef DEBUG
  printf("  eintrag%s(%lx -> %lx,%lx)\n",LISTTYPSTR,(long)liste,(long)*liste,
         (long)eintrag);
#endif
  CHECKPT(liste);                    /* Test Korrektheit des Listenzeigers   */
  CHECKPTN(*liste);                  /* Test Korrektheit der Liste           */
  CHECKPT(eintrag);                  /* Test Korrektheit des Eintrags        */
  /* ----------------------------------------------------------- */
  /* Eintrag mit dem entsprechenden Dienst des Moduls Listen     */
  /* ----------------------------------------------------------- */
#ifdef ABGLEICH
#ifdef ABBRUCH   /* Abbruchmakro angegeben   */
  if ((  erg = (LISTTYP)listenEintrag((Liste *)liste,(Liste)eintrag,
                (int (*)LISTPARAMS)VERGLNAME,
                (void (*)LISTPARAMS)ABGLNAME,
                (void (*)LISTPARAMS)KOPNAME,
                sizeof(BASISTYP),(Liste *)&FREILIS))==NULL)
    ABBRUCH;     /* Programmlauf beenden     */
#else            /* Fehler durch NULL melden */
  erg = (LISTTYP)listenEintrag((Liste *)liste,(Liste)eintrag,
                VERGLNAME,ABGLNAME,KOPNAME,sizeof(BASISTYP),
                (Liste *)&FREILIS);
#endif ABBRUCH
#else  /* ohne Abgleichroutine */
#ifdef ABBRUCH   /* Abbruchmakro angegeben   */
  if ((erg = (LISTTYP)listenEintrag((Liste *)liste,(Liste)eintrag,
                (int (*)LISTPARAMS)VERGLNAME,
                (void (*)LISTPARAMS)NULL,
                (void (*)LISTPARAMS)KOPNAME,
                sizeof(BASISTYP),(Liste *)&FREILIS)) == NULL)
    ABBRUCH;     /* Programmlauf beenden     */
#else            /* Fehler durch NULL melden */
  erg = (LISTTYP)listenEintrag((Liste *)liste,(Liste)eintrag,
                (int (*)LISTPARAMS)VERGLNAME,
                (void (*)LISTPARAMS)NULL,
                (void (*)LISTPARAMS)KOPNAME,
                sizeof(BASISTYP),(Liste *)&FREILIS);
#endif ABBRUCH
#endif ABGLEICH
#ifdef DEBUG
  printf("  eintrag%s = %lx\n",LISTTYPSTR,(long)erg);
#endif
  return(erg);   /* Zeiger auf gefundenen Eintrag abliefern */
 } /* EINTRNAME */

/* ====================================================================== */
/* Suchen eines Listenelementes "eintrag" in die Liste "liste"            */
/* Ergebnis : Zeiger auf das gefundene Listenelement                      */
/*            NULL, falls Eintrag nicht gefunden                          */
/* ====================================================================== */
#ifdef SUCHNAME
#ifdef __STDC__
LISTTYP SUCHNAME(LISTTYP *liste,BASISTYP *eintrag)
#else
LISTTYP SUCHNAME(liste,eintrag)
 LISTTYP *liste;         /* Liste, in der gesucht wird              */
 BASISTYP *eintrag;      /* einzutragende Information               */
#endif
 {
  register LISTTYP erg;  /* Ergebnis des Eintragens                 */

#ifdef DEBUG
  printf("  suche%s(%lx -> %lx,%lx)\n",LISTTYPSTR,(long)liste,(long)*liste,
         (long)eintrag);
#endif
  CHECKPT(liste);                    /* Test Korrektheit des Listenzeigers   */
  CHECKPTN(*liste);                  /* Test Korrektheit der Liste           */
  CHECKPT(eintrag);                  /* Test Korrektheit des Eintrags        */
  /* ----------------------------------------------------------- */
  /* Eintrag mit dem entsprechenden Dienst des Moduls Listen     */
  /* ----------------------------------------------------------- */
  erg = (LISTTYP)listenSuche((Liste *)liste,(Liste)eintrag,
                (int (*)LISTPARAMS)VERGLNAME);
#ifdef DEBUG
  printf("  suche%s = %lx\n",LISTTYPSTR,(long)erg);
#endif
  return(erg);   /* Zeiger auf gefundenen Eintrag abliefern */
 } /* SUCHNAME */
#endif

/* ====================================================================== */
/* Ergaenzen LISTTYP *ziel um die Informationen von LISTTYP quelle        */
/* Entspricht Kopieren, falls *ziel leer ist                              */
/* Ergebnis : TRUE : erfolgreich                                          */
/*            FALSE,falls Fehler bei der Durchfuehrung (Speicher voll ..) */
/* ====================================================================== */
#ifdef MERGENAME /* Routine wird benoetigt */
#ifdef __STC__
BOOL MERGENAME(LISTTYP *ziel,LISTTYP quelle)
#else
BOOL MERGENAME(ziel,quelle)
 LISTTYP *ziel;      /* Liste, in die der Eintrag erfolgen soll     */
 LISTTYP  quelle;    /* Liste der einzutragenden Informationen      */
#endif
 {
  BOOL erg;          /* Ergebnis von listenMerge()                  */

#ifdef DEBUG
  printf("  merge%s(%lx -> %lx,%lx)\n",LISTTYPSTR,(long)ziel,(long)*ziel,
            (long)quelle);
#endif
  CHECKPT(ziel);                     /* Test Korrektheit des Zielzeigers     */
  CHECKPTN(*ziel);                   /* Test Korrektheit der Zielliste       */
  CHECKPTN(quelle);                  /* Test Korrektheit der Quelliste       */
  /* ----------------------------------------------------------- */
  /* Eintrag mit dem entsprechenden Dienst des Moduls Listen     */
  /* ----------------------------------------------------------- */
#ifdef ABGLEICH
#ifdef ABBRUCH   /* Abbruchmakro angegeben   */
  if (! (erg = listenMerge((Liste *)ziel,(Liste)quelle,
                (int (*)LISTPARAMS)VERGLNAME,
                (void (*)LISTPARAMS)ABGLNAME,
                (void (*)LISTPARAMS)KOPNAME,
                sizeof(BASISTYP),(Liste *)&FREILIS)))
    ABBRUCH;
#else            /* Fehler durch FALSE melden */
  erg = listenMerge((Liste *)ziel,(Liste)quelle,
                VERGLNAME,ABGLNAME,KOPNAME,sizeof(BASISTYP),
                (Liste *)&FREILIS);
#endif ABBRUCH
#else  /* ohne Abgleichroutine */
#ifdef ABBRUCH   /* Abbruchmakro angegeben   */
  if (! (erg = listenMerge((Liste *)ziel,(Liste)quelle,
                (int (*)LISTPARAMS)VERGLNAME,
                (void (*)LISTPARAMS)NULL,
                (void (*)LISTPARAMS)KOPNAME,
                sizeof(BASISTYP),(Liste *)&FREILIS)))
    ABBRUCH;
#else            /* Fehler durch FALSE melden */
  erg = listenMerge((Liste *)ziel,(Liste)quelle,
                (int (*)LISTPARAMS)VERGLNAME,
                (void (*)LISTPARAMS)NULL,
                (void (*)LISTPARAMS)KOPNAME,
                sizeof(BASISTYP),(Liste *)&FREILIS);
#endif ABBRUCH
#endif ABGLEICH
#ifdef DEBUG
  printf("  merge%s Ende\n",LISTTYPSTR);  
#endif
 return(erg);
 } /* MERGENAME */
#endif MERGENAME /* Routine wird benoetigt */

#ifdef FREELISNAME
/* ====================================================================== */
/* Freigabe einer ganzen Liste von Eintraegen                             */
/* ====================================================================== */
#ifdef __STDC__
void FREELISNAME(LISTTYP lis )
#else
void FREELISNAME(lis)
 LISTTYP lis;          /* erster Eintrag in der freizugebenden Liste */
#endif
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

#undef LISTPARAMS
/* ====================================================================== */
/* Loeschen der Parametermakros                                           */
/* ====================================================================== */
#undef BASISTYP
#undef LISTTYP 
#undef FREILIS 
#undef INITNAME
#undef EINTRNAME
#undef SUCHNAME
#undef MERGENAME
#undef FREELISNAME
#undef VERGLEICHE
#undef VERGLNAME
#undef ABGLEICH
#undef ABGLNAME 
#undef KOPIERE
#undef KOPNAME 
#undef LISTTYPSTR

