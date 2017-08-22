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
/* LRKzust.c   :                                                          */
/* LR(k)-Parser-Generator                                                 */
/* Modul : Verwaltung der Zustaende des Automaten                         */
/* Aenderung  : 02.07.89, Effizienzsteigerung in verglUeberg              */
/* Aenderung  : 01.07.89, vollstaendig ueberarbeitet                      */
/* Aenderung  : 24.06.89, Bug beim Vergleichen von SPONTRED's beseitigt   */
/* Aenderung  : 25.5.89 , Verkettung Zustaende ueber erstes Item          */
/* Aenderung  : 8.3.89 , Ueberpruefungen zur Laufzeit                     */
/* erstellt   : 27.1.89                                                   */
/* ********************************************************************** */

#include <stdio.h>         /* E/A-Deklarationen                  */
#include "defs.h"          /* diverse unspezifische Definitionen */
#include "checks.h"        /* Deklarationen fuer Ueberpruefungen */
#include "grammar.h"       /* Datenstrukturen Grammatik          */
#include "allocate.h"      /* Deklarationen Speicherverwaltung   */
#include "listen.h"        /* Deklarationen Listenverwaltung     */
#include "lrkerrors.h"
#include "lrkzust.h"       /* Headerfile dieses Moduls           */

/* ========================================================================= */
/* Programm-globale Variablen                                                */
/* ========================================================================= */
extern Grammar g;         /* berarbeitete Grammatik                          */

/* ========================================================================= */
/* Aufruf parametrisierter Datenstrukturen                                   */
/* ========================================================================= */
 /* Makro zum Abbruch bei unzureichendem Speicher etc. */
#define ABBRUCH mAbort()

/* ------------------------------------------------------------------------ */
/* Position = sorted list of PosRec                                         */
/* ------------------------------------------------------------------------ */
/* Setzen der Parameter */
#define BASISTYP PosRec
#define LISTTYP  Position
#define LISTTYPSTR  "Position"
#define FREILIS  fl_position
#define INITNAME initPosition
#define EINTRNAME eintragPosition
/* #define MERGENAME mergePosition */
#define FREELISNAME freelisPosition
/* Kriterium : Items der Positionen */
#define VERGLEICHE(p1,p2) (p1->item-p2->item)
#define VERGLNAME verglPosition
/* kein Abgleich noetig */
#ifdef INCATTR
#define KOPIERE(z,q)   POSITEM(*z) = POSITEM(*q),POSATTR(*z)=NULL
#else
#define KOPIERE(z,q)   POSITEM(*z) = POSITEM(*q)
#endif
#define KOPNAME kopierePosition
#include "list_epd.h"          /* Aufruf der Datenstruktur */

/* ------------------------------------------------------------------------ */
/* Ueberg = sorted list of UebergRec                                        */
/* ------------------------------------------------------------------------ */
/* Setzen der Parameter */
#define BASISTYP UebergRec
#define LISTTYP  Ueberg
#define LISTTYPSTR  "Ueberg"
#define FREILIS  fl_ueberg
#define INITNAME initUeberg
#define EINTRNAME eintragUeberg
#define FREELISNAME freelisUeberg
static int verglUeberg();            /* forward-Deklaration Vergleichsroutine */
#define VERGLNAME verglUeberg
/* kein Abgleich noetig */
#define KOPNAME kopierUeberg    
#define KOPIERE(z,q)   (*z = *q,NEXTSHIFT(*z) = NULL,INKARN(*z) = 0)
#include "list_epd.h"          /* Aufruf der Datenstruktur */

/* ========================================================================= */
/* Modul-globale Variablen                                                   */
/* ========================================================================= */
Zustnr  nextzustnr;             /* Naechste zu vergebende Zustandsnummer     */
static Zustand zustaende;       /* Zustaende der Uebergangstabelle           */
static Zustand neuezustaende;   /* Zeiger noch nicht verarbeitete Zustaende  */
static Zustand endezustaende;   /* Zeiger auf letzten angelegten Zustand     */
static Zustand fl_Zustand;      /* Freiliste fuer Typ Zustand                */

/* ========================================================================= */
/* Makros                                                                    */
/* ========================================================================= */

 /* Schleife ueber alle bereits erfassten Zustaende z            */
#define FOREACHZUST(z) FOREACHLISTEL(*zustaende,z)

#define allocZustand(z) if ( (z = (Zustand)flAllocate(sizeof(ZustRec),\
                            (char**)&fl_Zustand))==NULL) mAbort();

/* ========================================================================= */
/* Vergleich zweier Uebergaenge                                              */
/* Sortierreihenfolge : zuerst (spontane) Uebergaenge mit UNDEFSYM           */
/*                         sortiert nach POSITEM(rpos)                       */
/*                      dann restliche Uebergaenge,                          */
/*                         sortiert nach POSITEM(rpos)                       */
/* ACHTUNG : Liste darf entweder ausschliesslich Uebergaenge mit UNDEFSYM    */
/*           oder ausschliesslich "echte" Symbole enthalten                  */
/* ========================================================================= */
static int verglUeberg(u1,u2)
 register Ueberg u1;    /*erster zu vergleichender Uebergang  */
 register Ueberg u2;    /*zweiter zu vergleichender Uebergang */
 {
  register int erg;     /* Ergebnis eines Vergleiches          */
  register Symb sym;    /* Symbol des ersten Ueberganges       */

  CHECKPT(u1);
  CHECKPT(u2);
  if ((sym = UEBSYM(*u1)) != UNDEFSYM)
   { /* erster Uebergang lesend */
    CHECKBED(UEBSYM(*u2) == UNDEFSYM); 
    if (erg = (int)(sym-UEBSYM(*u2)) )         /* Symbole verschieden    */
      return(erg);                             /* Differenz als Ergebnis */
    /* -------------------------------------------------------------------- */
    /* Symbole gleich, Uebergangsart betrachten                             */
    /* -------------------------------------------------------------------- */
    if (erg = (int)((int)UEBART(*u1)-(int)UEBART(*u2)) ) /* Uebergangsarten verschieden */
      return(erg);                             /* Differenz als Ergebnis      */
    else /* gleicher Uebergang */
      if (UEBART(*u1) != SPONTRED)  /* SHIFT/SHIFT-Konflikte gibt es nicht    */
        return(0);
      else  /* zu reduzierende Positionen vergleichen */
        return((int)(UEBRITEM(*u1)-UEBRITEM(*u2)));
   } /* erster Uebergang lesend */
  else /* sym == UNDEFSYM, zwangslaeufig SPONTRED */
   { /* Symbol fuer ersten Uebergang noch nicht bekannt */
    CHECKBED(UEBSYM(*u2) == UNDEFSYM );  /* zweiter ebenfalls,items vergl. */
    return((int)(UEBRITEM(*u1)-UEBRITEM(*u2)));
   } /* erster Uebergang ohne Symbol */
 } /* verglUeberg */

/* ========================================================================= */
/* Test, ob zwei Zustaende aequivalent sind                                  */ 
/* Zwei Zustaende gelten als gleich, wenn die item-Informationen aller       */
/* Eintraege in den Positionslisten uebereinstimmen (LR(0)-Aequivalenz)      */
/* Ergebnis : != 0, falls Zustaende aequivalent                              */
/*            0, falls nicht aequivalent (Einfuegen am Ende,s. ListenPDT.h)  */
/* ========================================================================= */
static int aequZust(z1,z2)
 Zustand z1;    /*erster zu vergleichender Zustand  */
 Zustand z2;    /*zweiter zu vergleichender Zustand */
 {
  register Position p1;    /* Position zu Zustand z1              */
  register Position p2;    /* Position zu Zustand z2              */


#ifdef DEBUG 
  printf("    aequZust(%lx,%lx)\n",(long)z1,(long)z2);
#endif
  CHECKPT(z1);
  CHECKPT(z2);

  /* ------------------------------------------------------------------- */
  /* Feststellen, ob alle sich Positionen der Zustaende auf die gleichen */
  /* Items beziehen                                                      */
  /* ------------------------------------------------------------------- */
  p2 = FIRSTPOS(*z2);      /* Zeiger auf erste Position von z2    */
  CHECKPT(p2);
  FOREACHPOS(*z1,p1)       /* alle Positionen von z1 ueberpruefen */
   {
    CHECKPT(p1);
#ifdef DEBUG
    printf("     zp-> ");
    fdecItem(stdout,POSITEM(*p1) );
    printf("\n");
    if (p2 != NULL)
     {
      printf("     qp-> ");
      fdecItem(stdout,POSITEM(*p2) );
      printf("\n");
     }
#endif
    if ( p2 == NULL ||                   /* z1 besitzt mehr Positionen als z2 */
         POSITEM(*p1) != POSITEM(*p2))   /* Items ungleich,nicht LR(0)-aequ.  */
      return(0);                         /* Zustaende sind verschieden        */
    p2 = (Position)LISTNEXT(*p2);        /* naechste z2-Position              */
    CHECKPTN(p2);
   } /* alle Positionen von z1 ueberpruefen */
  return(p2 == NULL);                    /* ungleich, falls z2 mehr Pos. hat  */
 } /* aequZust */


/* ========================================================================= */
/* Zustand in die Liste aller Zustaende aufnehmen                            */
/* Achtung : Positionen und Rueckkehrlisten werden uebernommen und duerfen   */
/* nach dem Aufruf nicht mehr veraendert (oder freigegeben) werden           */
/* Rueckgabe : laufende Nummer des Zustandes                                 */
/* ========================================================================= */
Zustand putZustand(zust)
 Zustand zust;             /* aufzunehmender Zustand                 */
 {
  register Item     fit;   /* erstes Item zum Zustand                */
  register Zustand  szust; /* Suchzustand in der Liste               */

#ifdef DEBUG 
  printf("   putZustand(%lx)\n",(long)zust);
#endif
  
  CHECKPT(zust);
  CHECKPT(FIRSTPOS(*zust));

  fit = POSITEM(*FIRSTPOS(*zust));  /* erstes Item bestimmen           */
#ifdef DEBUG
  printf("     fit = ");
  fdecItem(stdout,fit);
  printf("\n");
#endif
  /* --------------------------------------------------------------- */
  /* Zustand in der Liste aller Zustande suchen, deren erstes Item   */
  /* gleich fit ist                                                  */
  /* --------------------------------------------------------------- */
  for (szust = (Zustand)ZUSTLIST(fit) ; szust != NULL; 
       szust = NEXTINZUSTLIST(*szust))
   {
    if (aequZust(szust,zust))            /* passenden Zustand gefunden */
     {
      freelisPosition(FIRSTPOS(*zust));  /* Positionen freigeben       */
      FIRSTPOS(*zust) = NULL;            /* Zugriffe sperren           */
#ifdef DEBUG
      printf("      gefunden: %lx\n",(long)szust);
#endif
      return(szust);                     /* gefundenen abliefern       */
     }
   }
  /* --------------------------------------------------*/
  /* Zustand noch nicht vorhanden, in Tabelle eintragen */
  /* -------------------------------------------------- */
  allocZustand(szust);                     /* Speicher fuer neuen Zustand */
  CHECKPT(szust);
  /* ---------------------------------------------------------------------- */
  /* Feststellen, ob angelegter Zustand nur einen REDUCE-Uebergang zulaesst */
  /* wenn ja, in Zustandsnummer markieren (Beschleunigung)                  */
  /* ---------------------------------------------------------------------- */
  FIRSTPOS(*szust) = FIRSTPOS(*zust);  /* Positionsliste uebernehmen        */
  FIRSTPOS(*zust) = NULL;              /* keine Zugriffe mehr auf die Daten */
#ifdef INCATTR
  FIRSTRED(*szust) = NULL;
#endif
  /* ---------------------------------------------------------------------- */
  /* Feststellen, ob angelegter Zustand nur einen REDUCE-Uebergang zulaesst */
  /* wenn ja, in Zustandsnummer markieren (Beschleunigung)                  */
  /* ---------------------------------------------------------------------- */
  if(ITEMLEN(POSITEM(*FIRSTPOS(*szust)))==0 && /* erster Uebergang ist REDUCE */
       LISTNEXT(*FIRSTPOS(*szust)) == NULL)    /* einziger Uebergang          */
    ZUSTNR(*szust) = UNDEFZUSTNR;              /* als ueberfluessig markieren */
  else  /* Zustand muss angesprungen werden, Nummer vergeben */
   {
    ZUSTNR(*szust) = nextzustnr++; /* naechste laufende Nummer vergeben       */
    if (neuezustaende == NULL)     /* erster neuer Zustand                    */
      neuezustaende = szust;       /* Zeiger auf nicht verarbeitete Zustaende */
   }

  ZUSTEPSUEB(*szust)  = NULL;      /* noch keine spont. Uebergaenge berechnet */
  ZUSTTERMUEB(*szust) = NULL;      /* noch keine term. Uebergaenge berechnet  */
  ZUSTNONTUEB(*szust) = NULL;      /* noch keine nont. Uebergaenge berechnet  */
  ZUSTSHIFTS(*szust)  = NULL;      /* Zustand wurde noch nicht angesprungen   */

  if (endezustaende != NULL)    
    endezustaende->next = szust;   /* an Ende der Liste anhaengen             */ 
  szust->next = NULL;              /* letzter Eintrag                         */
  endezustaende = szust;           /* neues Ende der Liste                    */ 
  if (zustaende == NULL)           /* erster Zustand                          */
    zustaende = szust;            
 /* --------------------------------------------- */
 /* Verkettung in Liste der Items weiterfuehren   */
 /* --------------------------------------------- */
  CHECKPTN(ZUSTLIST(fit)); 
  NEXTINZUSTLIST(*szust) = (Zustand)ZUSTLIST(fit); /* bisherige Eintraege anhaengen    */
  ZUSTLIST(fit) = (char *)szust;          /* wird erster Eintrag              */ 
#ifdef DEBUG
  printf("      neu : %lx\n",(long)szust);
#endif
  return(szust);                          /* Zustand abliefern                */

 } /* putZustand */

/* ========================================================================= */
/* Bestimmt, ob Zustaende angelegt wurden, die noch nicht verarbeitet wurden */
/* ========================================================================= */
BOOL neueZustaende()
 {
  CHECKPTN(neuezustaende);
  return(neuezustaende != NULL); /* unbearbeitete Zustaende vorhanden        */
 } /* neueZustaende */

/* ========================================================================= */
/* Rueckgabe des naechsten, noch nicht bearbeiteten Zustandes                */
/* aktueller erster neuer Zustand wird nach Aufruf als bearbeitet angesehen  */
/* und neuezustaende auf den naechsten nicht beschleunigten Zustand gesetzt  */
/* ========================================================================= */
Zustand nextZustand()
 {  
  register Zustand neue;      /* erstes Element der neuen Zustaende          */

  CHECKPTN(neuezustaende);
  if ((neue=neuezustaende) != NULL)               /* Neue Zustaende vorhanden */
    neuezustaende = (Zustand)LISTNEXT(*neuezustaende); /* Listenrest bilden   */
  /* ---------------------------------------------------- */
  /* naechsten Zustand suchen, der bearbeitet werden muss */
  /* ---------------------------------------------------- */
  while (neuezustaende != NULL && ZUSTNR(*neuezustaende)==UNDEFZUSTNR)
    neuezustaende = (Zustand)LISTNEXT(*neuezustaende);   
  return(neue);                /* erster Zustand in der Liste neuer Zustaende */
 } /* nextZustand */

/* ====================================================================== */
/* liefert den ersten Zustand der Tabelle aller Zustaende ab              */
/* ====================================================================== */
Zustand firstZustand()
 {
  return(zustaende);   /* erster Zustand in der Liste zustaende */
 } /* firstZustand*/


/* ====================================================================== */
/* Initialisierung der Datenstrukturen dieses Moduls, Zustandsmenge leer  */
/* ====================================================================== */
BOOL initZustaende()
 {
  nextzustnr    = 0;           /* erste zu vergebende Nummer                 */
  zustaende     = NULL;        /* Tabelle leer                               */
  neuezustaende = NULL;        /*noch keine neuen Zeilen                    */ 
  endezustaende = NULL;        /*Ende der leeren Liste                      */ 
  fl_Zustand = NULL;           /* Freiliste ist leer                         */
  return(initPosition() &&     /* Datenstruktur Typ Position initialisieren  */
         initUeberg() );       /* Datenstruktur Typ Ueberg initialisieren    */
 } /* initZustaende */

