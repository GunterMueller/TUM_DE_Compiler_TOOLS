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
/* lrkmatp2.c   :                                                         */
/* LR(k)-Parser-Generator                                                 */
/* Modul : Generierung der Uebergangsmatrix, Pass 2 : Lookaheads          */
/* Aenderung  : 13.10.90 , Verwendung von incattr                         */
/* Aenderung  : 27.10.89 , ueberarbeitet wg. LRKkont                      */
/* Aenderung  : 24.06.89 , Ausgabe von Konflikten korrigiert              */
/* Aenderung  : 10.06.89 , Optimierung fuer k = 1                         */
/*                         EPSRED-Uebergangstyp eliminiert                */
/* erstellt   : 6.3.89                                                    */
/* ********************************************************************** */

#include <stdio.h>         /* E/A-Deklarationen                    */
#include "defs.h"          /* diverse unspezifische Definitionen   */
#include "dbg.h"
#include "checks.h"        /* Ueberpruefungen                      */
#include "grammar.h"       /* Datenstrukturen der Grammatik        */
#include "lrkzust.h"       /* Deklarationen Zustandsmodul          */
#include "lrkdec.h"        /* Deklarationen Dekoder                */
#include "lrkkont.h"       /* Deklarationen Kontextmodul           */
#include "lrkerrors.h"
#include "lrkmat.h"        /* Deklarationen Generatormodul         */
#include "lrkmatp2.h"      /* Deklarationen Generatormodul 2.Pass  */
#ifdef INCATTR
#include "iadefs.h"
#include "iaattr.h"
#include "iadsort.h"
#include "iawert.h"
#include "iasemfkt.h"
#include "lrklook.h"
#endif


/* ========================================================================= */
/* Programm-globale Variablen                                                */
/* ========================================================================= */
extern Grammar g;           /* bearbeitete Grammatik                         */
extern int max_lookahead;   /* maximale Laenge Lookahead (-k Option)         */
extern int generrors;       /* Anzahl gefundener Fehler                      */
extern FILE *aktkonf_file;  /* Datei fuer Aktionskonflikte                   */

#ifdef INCATTR
#define ATTRSEM(p) *((Position *)&(POSATTR(p)->sem))
#define SEM(attr)  *((Position *)&((attr)->sem))
/* ======================================================== */
/* Ausgabe der Information (Kommentar) eines Attributes     */
/* ======================================================== */
#ifdef __STDC__
void printSeminfo(FILE *f,Attribut attr)
#else
void printSeminfo(f,attr)
 FILE *f;
 Attribut attr;
#endif
 {
  fdecItem(f,POSITEM(*SEM(attr)));
 } /* printSeminfo */

/* ======================================================== */
/* Ausgabe des Wertes eines Attributes                      */
/* ======================================================== */
#ifdef __STDC__
void printSemattr(FILE *f,Attribut attr)
#else
void printSemattr(f,attr)
 FILE *f;
 Attribut attr;
#endif
 {
  printLookset(f,(SEM(attr))->first);
  fputc('@',f);
  printLookset(f,(SEM(attr))->first_look);
  fputc('\n',f);
 } /* printSeminfo */

/* ========================================================== */
/* Erzeugen einer neuen initialisierten Attributinstanz       */
/* ========================================================== */
#ifdef __STDC__
void newSem(Attribut attr,char *id,char *first)
#else
void newSem(attr,id,first)
 Attribut attr;
 char *id;
 char *first;
#endif
 {
 /* nicht benutzt */
 } /* newSem */

/* ======================================================== */
/* Auswertung eines Attributes                              */
/* Rueckgabe != 0 : Wert hat sich geaendert                 */
/* ======================================================== */
#ifdef __STDC__
int calcSem(Attribut attr)
#else
int calcSem(attr)
 Attribut attr;
#endif
 {
  Lookset     neu;      /* neuer Wert des Attributes          */
  Lookset     look;     /* neuer Wert des Attributes          */
  Attributlis depend;   /* Attribute, von denen attr abhaengt */

  IFDEBUG
  ({
    fprintf(stdout,"- calcSem: ");
    printSeminfo(stdout,attr);
    fprintf(stdout," ");
    printSemattr(stdout,attr);
  })

  neu = NULL;                /* neuen Wert initialisieren */
  for (depend = attr->depend; depend != NULL; depend = depend->next)
   { /* alle Vorgaenger betrachten */
    IFDEBUG
    ({
      fprintf(stdout,"  - depend: ");
      printSeminfo(stdout,depend->attr);
      fprintf(stdout," ");
      printSemattr(stdout,depend->attr);
    })

    unionLookset(&neu,(SEM(depend->attr))->first_look);
   }
  look = NULL;
  unionconcLookset(&look,(SEM(attr))->first,neu);
  if (!gleichLookset((SEM(attr))->first_look,look))
   {
    (SEM(attr))->first_look=look;
    return(1);
   }
  else
    return(0);
} /* calcSem */
#endif /* INKATTR */

/* ========================================================================= */
/* globale Variablen                                                         */
/* ========================================================================= */
static UebergRec gueb;    /* gesamte Information des Ueberganges             */
static Ueberg *basueb;    /* Zeiger auf Basisliste fuer Uebergaenge          */


/*====================================================================== */
/* Eintragen eines Lookaheads in einen Uebergang                          */
/*====================================================================== */
#ifdef __STDC__
void enterLook(Term sym)
#else
void enterLook(sym)
 Term sym;        /* zu lesendes Symbol                          */
#endif
 {
#ifdef DEBUG
  printf("enterLook %s ",decSym(sym));
#endif /* DEBUG */
  CHECKBED(ISTERM(sym));

  gueb.sym = sym;                 /* Symbol eintragen, fuer EPSRED irrelevant */
#ifdef DEBUG
  fdecUeb(stdout,&gueb);
  printf(" -> %lx\n",(long)eintragUeberg(basueb,&gueb)); /* eintragen */
  printf("enterLook Ende\n");
#else
  eintragUeberg(basueb,&gueb);    /* Uebergang eintragen                      */
#endif /* DEBUG */
  PRODSTAT(prodNr(UEBRITEM(gueb))) |= PS_REDUCE; 
 } /* enterLook */

/*====================================================================== */
/* Konflikte in den Uebergaengen eines Zustandes des LR(1)-Automaten      */
/* feststellen und beschimpfen                                            */
/*====================================================================== */
#ifdef __STDC__
void checkKonflikte(Zustand zust)
                            /* Zustand, dessen Konflikte beschimpft werden */
#else
void checkKonflikte(zust)
 Zustand zust;              /* Zustand, dessen Konflikte beschimpft werden */
#endif
 {
  register Ueberg ueb;      /* bearbeiteter LR(1)-Uebergang                 */
  register Ueberg next;     /* Nachfolge von ueb                            */
  int      konflikte;       /* Flag fuer : Konflikte vorhanden              */

#ifdef DEBUG
  printf("** checkKonflikte(%ld)\n",(long)ZUSTNR(*zust));
#endif /* DEBUG */
  konflikte = FALSE;        /* noch keine Konflikte vorhanden               */
  /* ------------------------------------------------------------------- */
  /* Liste der Zustaende abarbeiten, Konflikte erkennen                  */
  /* ------------------------------------------------------------------- */
  for (ueb = ZUSTTERMUEB(*zust); 
       ueb != NULL;
       ueb = next )
   {
    next = (Ueberg)LISTNEXT(*ueb);   /* naechster in der Liste           */
    if (next != NULL && UEBSYM(*next) == UEBSYM(*ueb) )
     { /* Konflikt vorhanden */
      generrors++;          /* Fehler zaehlen                 */
      if (! konflikte)      /* erster gefundener Konflikt     */
       {
        konflikte = TRUE;
        konfStart(zust);    /* Zustand melden                 */
       }
      konfUeb(ueb);  /* erster Uebergang der Konflikte */
      do
       {
        ueb = next;
        next = (Ueberg)LISTNEXT(*ueb);   /* naechster in der Liste           */
       } while (next != NULL && UEBSYM(*next) == UEBSYM(*ueb));
     } /* Konflikt vorhanden */
   } /* for (ueb ...) */
#ifdef DEBUG
  printf("checkKonflikte Ende\n");
#endif /* DEBUG */
 } /* checkKonflikte */

#ifdef INCATTR
static Inkarn akt_ink = 0;
static Attributlis attr_of_int = NULL; /* Liste der Positionen mit Konflikten */
#endif
#
/*====================================================================== */
/* Uebergaenge eines Zustandes des fertigen LR(0)-Automaten berechnen     */
/*====================================================================== */
#ifdef __STDC__
void zUebergaenge(Zustand zust)
                            /* Zustand, dessen Uebergaenge berechnet werden */
#else
void zUebergaenge(zust)
 Zustand zust;              /* Zustand, dessen Uebergaenge berechnet werden */
#endif
 {
#ifndef INCATTR
  Ueberg ueb;      /* bearbeiteter LR(0)-Uebergang                 */
#endif

#ifdef DEBUG
  printf("** zUebergaenge(%ld)\n",(long)ZUSTNR(*zust));
#ifdef DDEBUG
  {
   register Position pos;
   FOREACHPOS(*zust,pos)
    {
     printf("--> ");
     fdecItem(stdout,POSITEM(*pos));
     printf("\n");
     /* printRet(pos); */
    }
  }
#endif /* DDEBUG */
#endif /* DEBUG */
  if (max_lookahead == 0)     /* kein Lookahead zu verwenden       */
   { 
    if (ZUSTEPSUEB(*zust) != NULL) /* spontane Uebergaenge vorhanden    */
     {
      generrors++;                 /* Fehler zaehlen                    */
      epsError(zust);              /* Fehlermeldung                     */
     }
   }
  else
   {
    /* --------------------------------------------------- */
    /* 1-Lookahead zu den spontanen Uebergaengen berechnen */
    /* --------------------------------------------------- */
#ifdef INCATTR
    Position    pos;
    /* ------------------------------------------------------------------- */
    /* Liste der spontanen Uebergaenge abarbeiten, Lookaheads berechnen    */
    /* Lookaheads fuer SHIFTS erst bei k > 1 relevant                      */
    /* ------------------------------------------------------------------- */
    for (pos = FIRSTRED(*zust); 
         pos != NULL;
         pos = (Position)LISTNEXT(*pos) )
     {
#ifdef DEBUG
      fdecItem(stdout,POSITEM(*pos));
      fputc('\n',stdout);
#endif /* DEBUG */
      if (POSATTR(*pos) == NULL)
       {
        POSATTR(*pos) = newAttribut();
        POSZUST(*pos) = zust;
        ATTRSEM(*pos) = pos;
        POSFIRST(*pos) = NULL;
        POSFIRST_LOOK(*pos) = NULL;
       }
      newDepend(&attr_of_int,POSATTR(*pos));
     } /* for */
#else /* NOT INCATTR */
    basueb = &ZUSTTERMUEB(*zust);          /* Liste, in die eingetragen wird    */
    UEBART(gueb) = SPONTRED;               /* Art des einzutragenden Uebergangs */
    UEBVON(gueb) = zust;                   /* Ausgangszustand setzen            */
    /* ------------------------------------------------------------------- */
    /* Liste der spontanen Uebergaenge abarbeiten, Lookaheads berechnen    */
    /* Lookaheads fuer SHIFTS erst bei k > 1 relevant                      */
    /* ------------------------------------------------------------------- */
    for (ueb = ZUSTEPSUEB(*zust); 
         ueb != NULL;
         ueb = (Ueberg)LISTNEXT(*ueb) )
     {
#ifdef DEBUG
      fdecUeb(stdout,ueb);
      printf("---------- Lookaheads --------\n");
#endif /* DEBUG */
      /* ------------------------------------------------- */
      /* Zusicherungen :                                   */
      /* guebart == SPONTRED && UEBSYM(*ueb) == UNDEFSYM   */ 
      /* ------------------------------------------------- */
      UEBRITEM(gueb) = UEBRITEM(*ueb);
      lrkKontext(zust,ueb);    /* Lookaheads berechnen */
#ifdef DEBUG
      printf("---------- Lookaheads Ende --------\n");
      fdecUeb(stdout,ueb);
#endif /* DEBUG */
     } /* alle Uebergaenge */
    checkKonflikte(zust);
#endif /* NOT INCATTR */
   } /* 1-Lookahead berechnen */
  /*
  freelisUeberg(ZUSTEPSUEB(*zust));
  ZUSTEPSUEB(*zust) = NULL; */  /* spontane Uebergaenge entfernen    */
#ifdef DEBUG
  printf("zUebergaenge Ende\n");
#endif /* DEBUG */
 } /* zUebergaenge */

#ifdef INCATTR
/*====================================================================== */
/* Uebergaenge eines Zustandes des fertigen LR(0)-Automaten berechnen     */
/*====================================================================== */
#ifdef __STDC__
void zUebergaenge2(Zustand zust)
                            /* Zustand, dessen Uebergaenge berechnet werden */
#else
void zUebergaenge2(zust)
 Zustand zust;              /* Zustand, dessen Uebergaenge berechnet werden */
#endif
 {

#ifdef DEBUG
  printf("** zUebergaenge2(%ld)\n",(long)ZUSTNR(*zust));
#ifdef DDEBUG
  {
   register Position pos;
   FOREACHPOS(*zust,pos)
    {
     printf("--> ");
     fdecItem(stdout,POSITEM(*pos));
     printf("\n");
     /* printRet(pos); */
    }
  }
#endif /* DDEBUG */
#endif /* DEBUG */
  if (max_lookahead == 0)     /* kein Lookahead zu verwenden       */
    return; 
  else
   {
    /* --------------------------------------------------- */
    /* 1-Lookahead zu den spontanen Uebergaengen berechnen */
    /* --------------------------------------------------- */
    Position    pos;
    /* ----------------------------------- */
    /* Resultierende Uebergaenge eintragen */
    /* ----------------------------------- */
    for (pos = FIRSTRED(*zust); 
         pos != NULL;
         pos = (Position)LISTNEXT(*pos) )
     {
      Lookset eintr;
      UebergRec uebr;

      uebr.next = NULL;
      UEBART(uebr)   = SPONTRED;               /* Art des einzutragenden Uebergangs */
      UEBVON(uebr)   = zust;                   /* Ausgangszustand setzen            */
      UEBRITEM(uebr) = POSITEM(*pos);
      for (eintr = POSFIRST_LOOK(*pos); eintr != NULL; eintr = eintr->others)
       {
        if ((uebr.sym  = eintr->val) != EOLOOK)
         {
#ifdef DEBUG
          printf("-- Lookaheads:");
          fdecUeb(stdout,&uebr);
#endif /* DEBUG */
          PRODSTAT(prodNr(UEBRITEM(uebr))) |= PS_REDUCE; 
          eintragUeberg(&ZUSTTERMUEB(*zust),&uebr); /* Uebergang eintragen          */
         }
       }
      checkKonflikte(zust);
     } /* for (pos) */
   } /* 1-Lookahead berechnen */
  /*
  freelisUeberg(ZUSTEPSUEB(*zust));
  ZUSTEPSUEB(*zust) = NULL; */  /* spontane Uebergaenge entfernen    */
#ifdef DEBUG
  printf("zUebergaenge2 Ende\n");
#endif /* DEBUG */
 } /* zUebergaenge2 */
#endif

#ifdef INCATTR
/* ======================================================================= */
/* Auswertung aller an Konflikt beteiligten Positionen veranlassen         */
/* ======================================================================= */
#ifdef __STDC__
void berechneLooks(void)
#else
void berechneLooks()
#endif
 {
  Auswert ausw;

  /* --------------------------- */
  /* Auswerter anwerfen          */
  /* --------------------------- */
  if (attr_of_int != NULL)
   {
    akt_ink = 1;
    ausw = dyntopSort(attr_of_int,akt_ink);
    ausWerter(ausw,&akt_ink);
   }
 } /* berechneLooks */
#endif
