
/* *********************************************************************** */
/* parlist.h  :                                                            */
/* Parametrisierte Datenstruktur fuer sortierte Listen ueber Datentypen    */
/* Struktur  Listtyp = sorted list of Basistyp                             */
/* Listen ohne Wiederholung, wobei Gleichheit ueber ein Makro definiert    */
/* wird                                                                    */
/* Die Namen werden massiv ueber Tokenkonkatenation etc. erzeugt.	   */
/* ----------------------------------------------------------------------- */
/* erstellt  : 10.10.91, Ulrich Vollath aus listenpdt.h                    */
/* ----------------------------------------------------------------------- */
/* Eine sortierte Listendatenstruktur wird instantiiert mit		   */
/* INSTANZ_SLIST(Listtyp,Basistyp,vergleich,abgleich,kopiere,abbruch)      */
/* ....................................................................... */
/*  Die Parameter haben die folgende Bedeutung:				   */
/*   Listtyp  : Erzeugter (Pointer-)Datentyp fuer Listen ueber...	   */
/*   Basistyp : Basistyp, Grundinformation der Listenelemente		   */
/*   vergleich: Vergleicht Basistyp *ziel mit Basistyp *quelle	   	   */
/*   abgleich:  Gleicht    Basistyp *ziel mit Basistyp *quelleab	   */
/*   init_neu:  Initialisiert Basistyp *ziel ueber Basistyp *quelle	   */
/*		Aufgerufen bei der Erzeugung neuer Eintraege		   */
/*   abbruch:   Abbruch des Programmlaufs bei Fehlern (Speicher voll...)   */
/* *********************************************************************** */
#ifndef PARLIST_H
#define PARLIST_H

#include <stdio.h>               /* E/A, NULL etc.                        */
#include "checks.h"              /* Deklarationen Ueberwachung            */
#include "allocate.h"		 /* Deklarationen Speicherverwaltung	  */
/* #include "defs.h"  */              /* diverse Deklarationen                 */
/*#include "listen.h" */             /* Deklarationen der Listenoperationen   */

/* ------------------ */
/* Selektormakros     */
/* ------------------ */
#define LISTFIRST(l) (l)->first
#define LISTREST(l)  (l)->rest

#define INSTANZ_SLIST(Listtyp,Basistyp,vergleich,init_neu,abgleich,abbruch)\
typedef struct Listtyp##R *Listtyp; /* Listentyp ist Zeiger auf u.a. struct */\
typedef struct Listtyp##R{\
		Listtyp  rest;\
		Basistyp first;\
	       } Listtyp##Rec;\
static Listtyp fl##Listtyp=NULL;     /* Freiliste fuer den Datentyp Listtyp */\
\
/* ====================================================================== */\
/* Eintrag eines Listenelementes "quelle" in die Liste "liste"            */\
/* falls schon ein gleicher Eintrag existiert, erfolgt ein Abgleich der   */\
/* Informationen                                                          */\
/* Ergebnis : Zeiger auf das erzeugte/gefundene Listenelement             */\
/*            NULL, falls Fehler bei der Durchfuehrung (Speicher voll ..) */\
/* ====================================================================== */\
Listtyp enter##Listtyp(Listtyp *liste,Basistyp *quelle)\
 {\
  Listtyp   such;       /* Suchzeiger fuer Returnlis zu pos                  */ \
  Listtyp   vorg;	/* Suchzeiger Vorgaenger                             */ \
  Listtyp   neu;        /* neuer Eintrag                                     */\
  Basistyp *ziel;     	/* Inhalte zur Uebergabe an vergleich, abgleich, ... */\
\
  CHECKPT(liste);         /* Test Korrektheit des Listenzeigers   */\
  CHECKPTN(*liste);       /* Test Korrektheit der Liste           */\
  CHECKPT(quelle);        /* Test Korrektheit des Eintrags        */\
  /* ---------------------------------------------------------------------- */\
  /* in der sortierten Liste suchen, ob passender Eintrag bereits vorhanden */\
  /* ---------------------------------------------------------------------- */\
  vorg = NULL;           		/* kein Vorgaenger                  */\
  for (such = *liste; such != NULL; such = LISTREST(such) )\
   { /* Element in allen Eintraegen such suchen */\
    int   verg;                		/* Ergebnis des Vergleiches	    */\
\
    ziel = &LISTFIRST(such);		/* Basiselement fuer Vergleich      */\
    if ((verg = (vergleich)) < 0 )	/* such zu klein, weiter suchen	    */\
      vorg = such;			/* Vorgaenger fuer Einfuegen merken */\
    else if (verg > 0)			/* Rest der Liste groesser          */\
      break;				/* hier neuen Eintrag einfuegen     */\
    else				/* passender Eintrag gefunden       */\
     {\
      abgleich; 			/* Informationen abgleichen	    */\
      return(such);			/* Suche beendet, Eintrag melden    */\
     }\
   } /* for */\
  /* ----------------------------------------------------------------------- */\
  /* noch kein Eintrag vorhanden, zwischen vorg und NEXTRET(vorg) einhaengen */\
  /* ----------------------------------------------------------------------- */\
  if ((neu = (Listtyp)flAllocate(sizeof(Listtyp##Rec),(char**)&fl##Listtyp)) \
      == NULL)\
   { /* Speicherplatzreservierung nicht moeglich */\
    abbruch;                  	/* Programmlauf abbrechen                 */\
    return(NULL);             	/* Speicher voll, melden                  */\
   }\
  ziel = &LISTFIRST(neu); 	/* Ziel des Kopierens			  */\
  *ziel = *quelle;          	/* Informationen "grob" kopieren	  */\
  init_neu;   			/* Informationen initialisieren           */\
  if (vorg == NULL)           	/* kein Listen-Vorgaenger vorhanden       */\
    *liste = neu;		/* wird erster Eintrag                    */\
  else\
    LISTREST(vorg) = neu;	/* Nachfolger von vorg                    */\
  LISTREST(neu)    = such;	/* Listenrest anhaengen                   */\
  return(neu);			/* neuen Eintrag melden                   */\
 } /* enter##Listtyp */\
\
/* ====================================================================== */\
/* Suchen eines Listenelementes "quelle" in der Liste "liste"             */\
/* Ergebnis : Zeiger auf das gefundene Listenelement                      */\
/*            NULL, falls Eintrag nicht gefunden                          */\
/* ====================================================================== */\
Listtyp lookup##Listtyp(Listtyp *liste,Basistyp *quelle)\
 {\
\
  Listtyp such;   /* Suchzeiger fuer Returnlis zu pos          */ \
  Listtyp vorg;   /* Suchzeiger Vorgaenger                     */ \
\
  CHECKPT(liste);                    /* Test Korrektheit des Listenzeigers   */\
  CHECKPTN(*liste);                  /* Test Korrektheit der Liste           */\
  CHECKPT(quelle);                   /* Test Korrektheit des Eintrags        */\
\
  /* ----------------------------------------------------------------------- */\
  /* in der sortierten Liste suchen, ob passender Eintrag vorhanden          */\
  /* ----------------------------------------------------------------------- */\
  vorg = NULL;                       /* kein Vorgaenger                      */\
  for (such = *liste; such != NULL; such = LISTREST(such))\
   {    /* Element in allen Eintraegen such suchen */\
    int      verg;           	/* Ergebnis des Vergleiches              */\
    Basistyp *ziel;		/* Information fuer Vergleich		 */\
\
    ziel = &LISTFIRST(such);\
    if ((verg = (vergleich)) < 0)    /* such zu klein, weiter suchen    */\
      continue;  \
    else if (verg > 0)               /* Rest der Liste groesser            */\
      return(NULL);                  /* dann nicht vorhanden               */\
    else                             /* passender Eintrag gefunden         */\
      return(such);                  /* Suche beendet, Eintrag melden      */\
   } /* for */\
  return(NULL);                      /* Listenende, nicht vorhanden        */\
 } /* lookup##Listtyp */\
\
/* ====================================================================== */\
/* Ergaenzen Listtyp *zielliste um die Informationen von Listtyp quelle   */\
/* Entspricht Kopieren, falls *zielliste leer ist                         */\
/* Ergebnis : Ergaenzte Liste						  */\
/*            NULL, falls Fehler bei der Durchfuehrung (Speicher voll ..) */\
/* ====================================================================== */\
Listtyp merge##Listtyp(Listtyp *zielliste,Listtyp quelliste)\
 {\
  Listtyp such;           /* Suchzeiger fuer Returnlis zu pos          */ \
  Listtyp zeintr;         /* aktueller Eintrag in Zielliste            */ \
  Listtyp zvorg;          /* Vorgaenger in Zielliste                   */ \
\
  CHECKPT(zielliste);                /* Test Korrektheit des Zielzeigers     */\
  CHECKPTN(*zielliste);              /* Test Korrektheit der Zielliste       */\
  CHECKPTN(quellist);                /* Test Korrektheit der Quelliste       */\
\
  zeintr = *zielliste;               /* erster Eintrag in Zielliste          */\
  zvorg  = NULL;                     /* kein Vorgaenger                      */\
  such   = quelliste;		     /* erster Quelleintrag                  */\
  while (such != NULL)               /* solange Informationen vorhanden      */\
   { /* alle Eintraege in quelle suchen         */\
    int       verg;          	     /* Ergebnis des Vergleiches             */\
    Basistyp *quelle;                /* Information zu Element such          */\
    Basistyp *ziel;                  /* Information in Zielliste             */\
\
    quelle = &LISTFIRST(such);	     /* Zeiger auf Information der Quelliste */\
    if (zeintr == NULL ||            /* Rest der Zielliste leer              */\
      (ziel = &LISTFIRST(zeintr),verg = (vergleich)) < 0 ) /* Rest groesser  */\
     { \
      /* ------------------------------------------------------------------ */\
      /* neues, nicht in ziel vorhandenes Element aus quelle hier einfuegen */\
      /* ------------------------------------------------------------------ */\
      Listtyp neu;		     /* neuer Eintrag in Zielliste	     */\
\
      if ((neu = (Listtyp)flAllocate(sizeof(Listtyp##Rec),\
                 (char**)&fl##Listtyp)) == NULL)\
       { /* Speicherplatzreservierung nicht moeglich */\
        abbruch;               	 /* Programmlauf abbrechen                 */\
        return NULL;          	 /* Speicher voll, melden                  */\
       }\
      ziel = &LISTFIRST(neu);	 /* Ziel des Kopierens			   */\
      *ziel = *quelle;        	 /* Informationen "grob" kopieren	   */\
      init_neu;   		 /* Informationen initialisieren           */\
\
      if (zvorg == NULL)         /* kein Listen-Vorgaenger vorhanden       */\
        *zielliste = neu;        /* wird erster Eintrag                    */\
      else\
        LISTREST(zvorg) = neu;   /* eintr wird Nachfolger von vorg         */\
      zvorg = neu;               /* Vorgaenger merken                      */\
      LISTREST(neu) = zeintr;    /* Listenrest anhaengen                   */\
      such = LISTREST(such);     /* naechste Quellinformation              */\
     } /* hier einfuegen */\
    else /* zeintr != NULL && verg >= 0 */\
     {\
      if (!verg)		 /* Abgleich notwendig			   */\
        abgleich;         	 /* Informationen abgleichen               */\
      /* Zielzeiger weiterhaengen */\
      zvorg = zeintr;             /* Vorgaenger merken                     */\
      zeintr = LISTREST(zeintr);  /* naechster Eintrag in Zielliste        */\
     }\
   } /* while (such != NULL) */\
 return(*zielliste);\
 } /* merge##Listtyp */\
\
/* ====================================================================== */\
/* Freigabe einer ganzen Liste von Eintraegen                             */\
/* ====================================================================== */\
void freelis##Listtyp(Listtyp lis)\
 {\
  CHECKPTN(lis);                                 /* Test Korrektheit Liste */\
  if (lis != NULL)                               /* aus Effizienzgruenden  */\
    flFreelis((char**)lis,(char**)&fl##Listtyp); /* Speicher freigeben     */\
 } /* freelis##Listtyp */\
\
/* ====================================================================== */\
/* Initialisierung der parametrisierten Datenstruktur                     */\
/* muss vor der ersten Verwendung einer anderen Operation auf der         */\
/* Datenstruktur aufgerufen werden                                        */\
/* Ergebnis : TRUE, falls Initialisierung erfolgreich                     */\
/*            FALSE, falls Fehler bei Initialisierung                     */\
/* ====================================================================== */\
int init##Listtyp(void)\
 {\
  fl##Listtyp = NULL;            /* Freiliste leer initialisieren         */\
  return 1;			 /* immer erfolgreich beendet             */\
 } /* init##Listtyp */
/* Ende von INSTANZ_PARLIST */

#endif /* PARLIST_H */

