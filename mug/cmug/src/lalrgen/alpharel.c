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
/* alpharel.c   :                                                         */
/* LR(k)-Parser-Generator                                                 */
/* Modul : Anspruenge und Alpha(k)-Relation                               */
/* Aenderung : 28.10.89, forAlphaeps()                                    */
/* Aenderung : 02.07.89, Abpruefung auf ueberfluessige Nonterminale       */
/* Aenderung : 30.06.89, ueberarbeitet wg. LRKsim                         */
/* Aenderung : 9.3.89 , auszufuehrende Routine nicht als Argument         */
/* erstellt  : 30.1.89                                                    */
/* ********************************************************************** */
#ifdef __STDC__
#include <stddef.h>
#include <stdlib.h>
#endif
#include <stdio.h>         /* E/A-Deklarationen                   */
#include "defs.h"          /* diverse unspezifische Definitionen  */
#include "checks.h"        /* Ueberpruefungen zur Laufzeit        */
#include "listen.h"        /* Deklarationen Listenverwaltung      */
#include "grammar.h"       /* Datenstrukturen der Grammatik       */
#include "lrkmat.h"        /* Deklarationen Generatormodul        */
#include "lrksets.h"       /* Deklarationen Mengenoperationen     */
#include "alpharel.h"      /* Deklarationen dieses Moduls         */     

/* ========================================================================= */
/* Programm-globale Variablen                                                */
/* ========================================================================= */
extern Grammar g;          /* bearbeitete Grammatik                          */

/* ========================================================================= */
/* Modul-globale Variablen                                                   */
/* ========================================================================= */

static BOOL aktiv;        /* zur Verhinderung rekursiver Aufrufe forAnsprung */ 

/* ------------------------------------------------------------------------- */
/* statische Variablen, um Stack in der Rekursion einzusparen                */
/* ------------------------------------------------------------------------- */
static Nontset  bearbeitet;         /* Rekursionsmerker fuer Anspruenge      */
static Symb nontpar;                /* eigentlich Parameter f. forAnsprung   */


/* ========================================================================== */
/* rekursive Version von forAlphaeps                                          */
/* ========================================================================== */
#ifdef __STDC__
static void forAlphaepsrec(void)
#else
static void forAlphaepsrec( /* nont */ )
#endif
 /* Symb nont;   */         /* global : Nonterminal, das angesprungen wird  */
 {
  register Prod prod;       /* Produktion zu nont                           */
  register Item item;       /* angesprungenes Item                          */
  /* ------------------------------------------------------------------------ */
  /* Die folgenden Variablen werden static vereinbart, um Stack zu sparen     */
  /* Dies ist moeglich, da sie in jedem Schleifendurchlauf vor ihrer          */
  /* Verwendung zugewiesen, und nach dem rekursiven Aufruf nicht mehr         */
  /* verwendet werden                                                         */
  /* ------------------------------------------------------------------------ */
  static Symb sym;              /* Symbol zu Item                             */

#ifdef DDEBUG
  printf(" forAlphaepsrec(%s)\n",decSym(nontpar) );
#endif
  FOREACHPRODTO(nontpar,prod)       /* alle Produktionen zu nont anspringen   */
  /* ab hier wird der Wert von nontpar nicht mehr benoetigt !!*/
   {
    item = LHS(prod);           /* linke Seite                    */
    if (ITEMLEN(item))          /* Epsilonproduktionen ignorieren */
     {
      do
       {
        /* ----------------------------------------- */
        /* in rechter Seite lesen, bis Ende erreicht */
        /* ----------------------------------------- */
        item = NEXTITEM(item);    /* naechstes Item in rechter Seite  */
        sym = ITEMSYM(item);      /* zu lesendes Symbol               */
        if (ISTERM(sym))          /* Terminalsymbol direkt melden */
         {
          /* ----------------------------- */
          /* Terminalzeichen direkt melden */
          /* ----------------------------- */
#ifdef DDEBUG
          printf("      it ");
          fdecItem(stdout,item);
          printf("\n");
#endif
          firstTerm(sym);         /* Zeichen melden                   */
          break;                  /* Produktion beendet               */
         }
        else
         {
          /* ------------------------------ */
          /* Nonterminal, Anfaenge rekursiv */
          /* ------------------------------ */
#ifdef DDEBUG
          fputs(" ansp Prod ",stdout);
          fdecItem(stdout,item);
          putchar('\n');
#endif
          nontpar = sym;                         /* erstes Symbol            */
          if (!inNset(nontpar,bearbeitet))       /* noch nicht angesprungen  */
           {  /* Anspruenge rekursiv berechnen */
            /* ab hier wird der Wert von sym nicht mehr benoetigt   */
            inclNset(nontpar,bearbeitet); /* als bearbeitet markieren           */
            forAlphaepsrec();             /*Rekursion mit neuer Rueckkehrinf.  */
           }
         } /* Nonterminal */
       } while (ITEMLEN(item) && ISEPS(ITEMSYM(item)));
     } /* keine Epsilon-Produktion */
   } /* FOREACHPRODTO*/
#ifdef DDEBUG
  printf(" forAlphaepsrec Ende\n");
#endif
 } /* forAlphaepsrec */

/* ========================================================================== */
/* Berechnung aller des ersten Terminalzeichens, das aus dem Nonterminal nont */
/* hergeleitet werden kann                                                    */
/* Fuer jedes gefundene Symbol wird firstTerm() aufgerufen                    */
/* ========================================================================== */
#ifdef __STDC__
void forAlphaeps(Nont nont)
#else
void forAlphaeps(nont)
 Nont nont;                     /* Nonterminal, das erzeugt werden soll       */
#endif
 {
#ifdef DDEBUG
  printf(" forAlphaeps(%s)\n",decSym(nont) );
#endif
  if (aktiv)                    /* forAnsprung laeuft bereits !               */
   {
    printf("Rekursiver Aufruf von forAlphaeps\n");
    exit(RETURNSTAT_FAIL);      /* Abbruch, keine sinnvollen Ergebnisse       */
   }
  aktiv = TRUE;                 /* merken, dass Routine laeuft                */
  emptyNset(bearbeitet);        /* bereits bearbeitet                         */
  inclNset(nont,bearbeitet);    /* initialisieren                             */
 /* ------------------------------------------ */
 /* Parameter fuer rekursive Loesung setzen    */
 /* ------------------------------------------ */
  nontpar = nont;               /* Nonterminal , dessen Produktionen anzuspr. */
  forAlphaepsrec();             /*rekursive Loesung aufrufen                 */
  aktiv = FALSE;                /* Routine wieder "freigeben"                 */
#ifdef DDEBUG
  printf(" forAlphaeps Ende\n");
#endif
 } /* forAlphaeps */

/* ========================================================================== */
/* Berechnung aller items, die zum Erzeugen des Nonterminals nont             */
/* angesprungen werden muessen (=linke Seiten der angesprungenen Produktionen)*/
/* Fuer jedes gefundene Item it wird doUeb(it) aufgerufen                     */
/* rekursive Loesung mit Terminierung ueber "bearbeitet", ein Parameter ist   */
/* global, dadurch geringerer Stackbedarf pro Rekursion.                      */
/* ========================================================================== */
#ifdef __STDC__
static void forAnsprungrec(void)
#else
static void forAnsprungrec( /* nont */ )
#endif
 /* Symb nont;   */         /* global : Nonterminal, das angesprungen wird  */
 {
  register Prod prod;       /* Produktion zu nont                           */
  /* ------------------------------------------------------------------------ */
  /* Die folgenden Variablen werden static vereinbart, um Stack zu sparen     */
  /* Dies ist moeglich, da sie in jedem Schleifendurchlauf vor ihrer          */
  /* Verwendung zugewiesen, und nach dem rekursiven Aufruf nicht mehr         */
  /* verwendet werden                                                         */
  /* ------------------------------------------------------------------------ */
  static Item item;             /* angesprungenes Item                        */

#ifdef DEBUG
  printf(" forAnsprungrec(%s)\n",decSym(nontpar) );
#endif
  NONTSTAT(nontpar) |= NS_BENUTZT;  /* Dieses Nonterminal wird angesprungen   */
  FOREACHPRODTO(nontpar,prod)       /* alle Produktionen zu nont anspringen   */
  /* ab hier wird der Wert von nontpar nicht mehr benoetigt !!*/
   {
    doUeb((item = LHS(prod) ));           /* linke Seite melden       */
#ifdef DEBUG
  fputs(" ansp Prod ",stdout);
  fdecItem(stdout,item);
  putchar('\n');
#endif
    if (ITEMLEN(item)>0)                     /* keine Epsilonproduktion  */
     {
      nontpar = ITEMSYM(++item);             /* erstes Symbol            */
      if ( ISNONT(nontpar) &&                /* erstes Item nonterminal  */
        !inNset(nontpar,bearbeitet))         /* noch nicht angesprungen  */
       {  /* Anspruenge rekursiv berechnen */
          /* ab hier wird der Wert von item nicht mehr benoetigt */
            inclNset(nontpar,bearbeitet); /* als bearbeitet markieren           */
            forAnsprungrec();             /*Rekursion mit neuer Rueckkehrinf.  */
       }
     } 
   } /* FOREACHPRODTO*/
#ifdef DEBUG
  printf(" forAnsprungrec Ende\n");
#endif
 } /* forAnsprungrec */

/* ========================================================================== */
/* Berechnung aller items, die zum Erzeugen des Nonterminals nont             */
/* angesprungen werden muessen (=linke Seiten der angesprungenen Produktionen)*/
/* Fuer jedes gefundene Item it wird doUeb() aufgerufen                       */
/* ========================================================================== */
#ifdef __STDC__
void forAnsprung(Nont nont)
#else
void forAnsprung(nont)
 Nont nont;                     /* Nonterminal, das erzeugt werden soll       */
#endif
 {
#ifdef DEBUG
  printf(" forAnsprung(%s)\n",decSym(nont) );
#endif
  if (aktiv)                    /* forAnsprung laeuft bereits !               */
   {
    printf("Rekursiver Aufruf von forAnsprung\n");
    exit(RETURNSTAT_FAIL);      /* Abbruch, keine sinnvollen Ergebnisse       */
   }
  aktiv = TRUE;                 /* merken, dass Routine laeuft                */
  emptyNset(bearbeitet);        /* bereits bearbeitet                         */
  inclNset(nont,bearbeitet);    /* initialisieren                             */
 /* ------------------------------------------ */
 /* Parameter fuer rekursive Loesung setzen    */
 /* ------------------------------------------ */
  nontpar = nont;               /* Nonterminal , dessen Produktionen anzuspr. */
  forAnsprungrec();             /*rekursive Loesung aufrufen                 */
  aktiv = FALSE;                /* Routine wieder "freigeben"                 */
#ifdef DEBUG
  printf(" forAnsprung Ende\n");
#endif
 } /* forAnsprung */


/* ========================================================================== */
/* Initialisierung dieses Moduls                                              */
/* ========================================================================== */
#ifdef __STDC__
void initAlpharel(void)
{
#else
void initAlpharel()
 {
#endif
  getNset(&bearbeitet);          /* Speicher fuer Menge reservieren           */
  aktiv = FALSE;                 /* Routine noch nicht in Benutzung           */
 } /* initAlpharel */


