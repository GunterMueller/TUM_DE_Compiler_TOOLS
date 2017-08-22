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
/* list_epd.h  :                                                          */
/* Verwaltungsroutinen fuer sortierte Listen ueber Datentypen             */
/* Die Routinen werden direkt durch Expansion von Quellen aus listen.c in */
/* listenpdt.h erzeugt -> Luafzeiteffizienz, groessere Programme          */
/* erstellt  : 16.02.90 aus listen.c listenpdt.h (uv)                     */

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

#include <stdio.h>          /* E/A, NULL etc.                             */
#include "defs.h"           /* diverse Deklarationen                      */
#include "allocate.h"       /* Deklarationen Speicherverwaltung           */
#include "listen.h"         /* Deklarationen Listenverwaltung             */
#include "checks.h"         /* Deklarationen Ueberwachung                 */

static LISTTYP FREILIS=NULL;     /* Freiliste fuer den Datentyp LISTTYP   */

/* ====================================================================== */
/* Eintrag eines Listenelementes "el" in die Liste "liste"                */
/* falls schon ein gleicher Eintrag existiert, erfolgt ein Abgleich der   */
/* Informationen                                                          */
/* Ergebnis : Zeiger auf das erzeugte/gefundene Listenelement             */
/*            NULL, falls Fehler bei der Durchfuehrung (Speicher voll ..) */
/* ====================================================================== */
#ifdef __STDC__
LISTTYP EINTRNAME(LISTTYP * liste,BASISTYP *el)
#else
LISTTYP EINTRNAME(liste,el)
 LISTTYP *liste;         /* Liste, in die der Eintrag erfolgen soll */
 BASISTYP *el;           /* einzutragende Information               */
#endif
 {
  register LISTTYP such;   /* Suchzeiger fuer Returnlis zu pos          */ 
  register LISTTYP vorg;   /* Suchzeiger Vorgaenger                     */ 

#ifdef DEBUG
  printf("  eintrag%s(%lx -> %lx,%lx)\n",LISTTYPSTR,(long)liste,(long)*liste,
         (long)el);
#endif
  CHECKPT(liste);                    /* Test Korrektheit des Listenzeigers   */
  CHECKPTN(*liste);                  /* Test Korrektheit der Liste           */
  CHECKPT(el);                       /* Test Korrektheit des Eintrags        */

  /* ----------------------------------------------------------------------- */
  /* in der sortierten Liste suchen, ob passender Eintrag bereits vorhanden  */
  /* ----------------------------------------------------------------------- */
  vorg = NULL;                       /* kein Vorgaenger                       */
  for (such = *(LISTTYP *)liste; such != NULL; such = *(LISTTYP *)such)
   {    /* Element in allen Eintraegen such suchen */
    register int   verg;             /* Ergebnis des Vergleiches              */
#ifdef VERGLEICHE /* Vergleichsmakro angegeben    */
    if ((verg = VERGLEICHE(such,el)) < 0)  /* such zu klein, weiter suchen    */
#else             /* Vergleichsroutinen angegeben */
    if ((verg = VERGLNAME(such,el))<0)     /* such zu klein, weiter suchen    */
#endif /* VERGLEICHE */
      vorg = such;                   /* Vorgaenger fuer Einfuegen merken      */
    else if (verg > 0)               /* Rest der Liste groesser               */
      break;                         /* hier neuen Eintrag einfuegen          */
    else                             /* passender Eintrag gefunden            */
     {
#ifdef ABGLNAME                      /* Abgleich notwendig                    */
#ifdef ABGLEICH                      /* Abgleichmakro angegeben               */
      ABGLEICH(such,el);             /* Informationen abgleichen              */
#else                                /* Abgleichroutine angegeben             */
      ABGLNAME(such,el);             /* Informationen abgleichen              */
#endif /* ABGLEICH */
#endif /* ABGLNAME */
#ifdef DEBUG
      printf("  eintrag%s = %lx\n",LISTTYPSTR,(long)such);
#endif
      return(such);                  /* Suche beendet, Eintrag melden         */
     }
   } /* for */
  /* ----------------------------------------------------------------------- */
  /* noch kein Eintrag vorhanden, zwischen vorg und NEXTRET(vorg) einhaengen */
  /* ----------------------------------------------------------------------- */
   { 
    register LISTTYP eintr;           /* neuer Eintrag                          */

    if ((eintr = (LISTTYP)flAllocate(sizeof(BASISTYP),
                        (char**)&FREILIS)) == NULL) /* Reservierung           */
#ifdef ABBRUCH                      /* Abbruchmakro angegeben                 */
      ABBRUCH;                      /* Programmlauf beenden                   */
#else                               /* Fehler durch NULL melden               */
      return(NULL);                 /* Speicher voll, melden                  */
#endif /* ABBRUCH */
#ifdef KOPIERE                      /* Kopiermakro angegeben                  */
    KOPIERE(eintr,el);              /* Informationen kopieren                 */
#else                               /* Kopierroutine angegeben                */
    KOPNAME(eintr,el);              /* Informationen kopieren                 */
#endif /* KOPIERE */
    if (vorg == NULL)               /* kein Listen-Vorgaenger vorhanden       */
      *(LISTTYP *)liste = eintr;    /* wird erster Eintrag                    */
    else
      *(LISTTYP *)vorg  = eintr;    /* Nachfolger von vorg                    */
    *(LISTTYP *)eintr   = such;     /* Listenrest anhaengen                   */
#ifdef DEBUG
    printf("  eintrag%s = %lx\n",LISTTYPSTR,(long)eintr);
#endif
    return(eintr);                  /* neuen Eintrag melden                   */
   }
 } /* EINTRNAME */

/* ====================================================================== */
/* Suchen eines Listenelementes "el" in der Liste "liste"                 */
/* Ergebnis : Zeiger auf das gefundene Listenelement                      */
/*            NULL, falls Eintrag nicht gefunden                          */
/* ====================================================================== */
#ifdef SUCHNAME
#ifdef __STDC__
LISTTYP SUCHNAME(LISTTYP *liste,BASISTYP *el)
#else
LISTTYP SUCHNAME(liste,el)
 LISTTYP *liste;         /* Liste, in der gesucht wird              */
 BASISTYP *el;           /* zu suchende Information                 */
#endif
 {

  register LISTTYP such;   /* Suchzeiger fuer Returnlis zu pos          */ 
  register LISTTYP vorg;   /* Suchzeiger Vorgaenger                     */ 

#ifdef DEBUG
  printf("  suche%s(%lx -> %lx,%lx)\n",LISTTYPSTR,(long)liste,(long)*liste,
         (long)el);
#endif
  CHECKPT(liste);                    /* Test Korrektheit des Listenzeigers   */
  CHECKPTN(*liste);                  /* Test Korrektheit der Liste           */
  CHECKPT(el);                       /* Test Korrektheit des Eintrags        */

  /* ----------------------------------------------------------------------- */
  /* in der sortierten Liste suchen, ob passender Eintrag vorhanden          */
  /* ----------------------------------------------------------------------- */
  vorg = NULL;                       /* kein Vorgaenger                       */
  for (such = *(LISTTYP *)liste; such != NULL; such = *(LISTTYP *)such)
   {    /* Element in allen Eintraegen such suchen */
    register int   verg;             /* Ergebnis des Vergleiches              */

#ifdef VERGLEICHE /* Vergleichsmakro angegeben    */
    if ((verg = VERGLEICHE(such,el)) < 0)  /* such zu klein, weiter suchen    */
#else             /* Vergleichsroutinen angegeben */
    if ((verg = VERGLNAME(such,el))<0)     /* such zu klein, weiter suchen    */
#endif /* VERGLEICHE */
      continue;  
    else if (verg > 0)               /* Rest der Liste groesser               */
      return(NULL);                  /* dann nicht vorhanden                  */
    else                             /* passender Eintrag gefunden            */
      return(such);                  /* Suche beendet, Eintrag melden         */
   } /* for */
  return(NULL);                      /* Listenende, nicht vorhanden           */
 } /* SUCHNAME */
#endif /* SUCHNAME */

/* ====================================================================== */
/* Ergaenzen LISTTYP *ziel um die Informationen von LISTTYP quelle        */
/* Entspricht Kopieren, falls *ziel leer ist                              */
/* Ergebnis : TRUE : erfolgreich                                          */
/*            FALSE,falls Fehler bei der Durchfuehrung (Speicher voll ..) */
/* ====================================================================== */
#ifdef MERGENAME /* Routine wird benoetigt */
#ifdef __STDC__
BOOL MERGENAME(LISTTYP *ziel,LISTTYP quelle)
#else
BOOL MERGENAME(ziel,quelle)
 LISTTYP *ziel;      /* Liste, in die der Eintrag erfolgen soll     */
 LISTTYP  quelle;    /* Liste der einzutragenden Informationen      */
#endif
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
  /* ----------------------------------------------------------- */
  /* Eintrag mit dem entsprechenden Dienst des Moduls Listen     */
  /* ----------------------------------------------------------- */
#ifdef ABGLEICH
#ifdef ABBRUCH   /* Abbruchmakro angegeben   */
  if (! (erg = listenMerge((Liste *)ziel,(Liste)quelle,
                VERGLNAME,ABGLNAME,KOPNAME,sizeof(BASISTYP),
                (Liste *)&FREILIS)))
    ABBRUCH;
#else            /* Fehler durch FALSE melden */
  erg = listenMerge((Liste *)ziel,(Liste)quelle,
                VERGLNAME,ABGLNAME,KOPNAME,sizeof(BASISTYP),
                (Liste *)&FREILIS);
#endif /* ABBRUCH */
#else  /* ohne Abgleichroutine */
#ifdef ABBRUCH   /* Abbruchmakro angegeben   */
  if (! (erg = listenMerge((Liste *)ziel,(Liste)quelle,
                VERGLNAME,NULL,KOPNAME,sizeof(BASISTYP),
                (Liste *)&FREILIS)))
    ABBRUCH;
#else            /* Fehler durch FALSE melden */
  erg = listenMerge((Liste *)ziel,(Liste)quelle,
                VERGLNAME,NULL,KOPNAME,sizeof(BASISTYP),
                (Liste *)&FREILIS);
#endif /* ABBRUCH */
#endif /* ABGLEICH */

  zeintr = *ziel;                 /* erster Eintrag in Zielliste             */
  zvorg = NULL;                   /* kein Vorgaenger                         */
  such = quelle;                  /* erster Quelleintrag                     */
  while (such != NULL)            /* solange Informationen vorhanden         */
   { /* alle Eintraege in quelle suchen         */
    if (zeintr == NULL ||          /* Rest der Zielliste leer                */

#ifdef VERGLEICHE /* Vergleichsmakro angegeben    */
      (verg = VERGLEICHE(such,zeintr) ) /* Inhalte vergleichen               */
#else             /* Vergleichsroutinen angegeben */
      (verg = VERGLNAME(such,zeintr) )  /* Inhalte vergleichen               */
#endif /* VERGLEICHE */
                        < 0 )      /* Rest der Zielliste groesser            */
     { /* hier einfuegen */
      if ((eintr = (LISTTYP)flAllocate(sizeof(BASISTYP,(char**)&FREILIS)) 
           == NULL)
#ifdef ABBRUCH                      /* Abbruchmakro angegeben                 */
       ABBRUCH;                      /* Programmlauf beenden                   */
#else                               /* Fehler durch NULL melden               */
       return(FALSE);                 /* Speicher voll, melden                  */
#endif /* ABBRUCH */

#ifdef KOPIERE                    /* Kopiermakro angegeben                   */
      KOPIERE(eintr,such);        /* Information kopieren                    */
#else                             /* Kopierroutine angegeben                 */
      KOPNAME(eintr,such);        /* Information kopieren                    */
#endif /* KOPIERE */
      if (zvorg == NULL)          /* kein Listen-Vorgaenger vorhanden        */
        *(LISTTYP *)ziel = eintr; /* wird erster Eintrag                     */
      else
        *(LISTTYP *)zvorg = eintr;/* eintr wird Nachfolger von vorg          */
      zvorg = eintr;              /* Vorgaenger merken                       */
      *(LISTTYP *)eintr = zeintr; /* Listenrest anhaengen                    */
      such = (Liste)*such;        /* naechste Quellinformation               */
     } /* hier einfuegen */
    else /* zeintr != NULL && verg >= 0 */
     {
      if (verg==0 && abgl != NULL) /* Abgleich notwendig                      */
#ifdef ABGLNAME                      /* Abgleich notwendig                    */
#ifdef ABGLEICH                      /* Abgleichmakro angegeben               */
        ABGLEICH(zeintr,such);       /* Informationen abgleichen                */
#else                                /* Abgleichroutine angegeben             */
        ABGLNAME(zeintr,such);       /* Informationen abgleichen                */
#endif /* ABGLEICH */
#endif /* ABGLNAME */
      if (verg == 0)
        such = *(LISTTYP *)such;   /* naechste Quellinformation (uv, 29.1.90)*/
      /* Zielzeiger weiterhaengen */
      zvorg = zeintr;              /* Vorgaenger merken                       */
      zeintr = *(LISTTYP*)zeintr;  /* naechster Eintrag in Zielliste          */
     }
   } /* FOREACHLISTEL */
#ifdef DEBUG
  printf("  merge%s Ende\n",LISTTYPSTR);  
#endif
  return(TRUE);                    /* erfolgreich beendet                     */
 } /* MERGENAME */
#endif /* MERGENAME */ /* Routine wird benoetigt */

#ifdef FREELISNAME
/* ====================================================================== */
/* Freigabe einer ganzen Liste von Eintraegen                             */
/* ====================================================================== */
#ifdef __STDC__
void FREELISNAME(LISTTYP lis)
#else
void FREELISNAME(lis)
 LISTTYP lis;          /* erster Eintrag in der freizugebenden Liste */
#endif
 {
  CHECKPTN(lis);                           /* Test Korrektheit der Liste      */
  flFreelis((char**)lis,(char**)&FREILIS); /* in Speicherverwaltung freigeben */
 } /* FREELISNAME */
#endif /* FREELISNAME */

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


