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
/* LRKsets.c   :                                                          */
/* LR(k)-Parser-Generator                                                 */
/* Modul : Implementierung Mengenoperationen                              */
/* Aenderung : 01.07.89, Typ Termset ergaenzt                             */
/* Aenderung : 7.3.89, Ueberpruefungen zur Laufzeit                       */
/* erstellt   : 30.1.89                                                   */
/* ********************************************************************** */

#include <stdio.h>         /* E/A-Deklarationen                  */
#include "defs.h"          /* diverse unspezifische Definitionen */
#include "checks.h"        /* Deklarationen fuer Ueberpruefungen */
#include "grammar.h"       /* Datenstrukturen der Grammatik      */
#include "allocate.h"      /* Deklarationen Speicherverwaltung   */     
#include "lrkdec.h"        /* Deklarationen Dekodermodul         */
#include "lrkerrors.h"
#include "lrksets.h"       /* Deklarationen dieses Moduls        */     

/* ========================================================================= */
/* Programm-globale Variablen                                                */
/* ========================================================================= */
extern Grammar g;          /* bearbeitete Grammatik                          */

/* ========================================================================= */
/* Modul-globale Variablen                                                   */
/* ========================================================================= */
static Nontset *fl_nset=NULL; /* Freiliste fuer Type Nontset                 */
static Termset *fl_tset=NULL; /* Freiliste fuer Type Termset                 */

 /* Anzahl der Worte fuer eine Nonterminalmenge */
#define LENNSET  (((MAXN-MINN)>>MSHIFT)+1)

 /* Anzahl der Worte fuer eine Terminalmenge */
#define LENTSET  (((MAXT-MINT)>>MSHIFT)+1)

/* ========================================================================= */
/* Operationen auf Mengen von Nonterminalen                                  */
/* ========================================================================= */

/* ========================================================================= */
/* Test der Zugehoerigkeit eines Element zu einer Nonterminalmenge           */
/* ========================================================================= */
#ifdef __STDC__
BOOL inNset(Nont nont,Nontset nset)
#else
BOOL inNset(nont,nset)
 Nont    nont;     /* Element                */
 Nontset nset;     /* Menge                  */
#endif
 {
  register Nont elno; /* laufende Nummer in der Menge */

#ifdef CHECKALL
  CHECKPT(nset);
  CHECKBED(ISNONT(nont));
#endif

  elno = nont-MINN;        /* mit 0 beginnend numeriert    */
  return((BOOL)(nset[elno>>MSHIFT] & (1 << (elno & MMASK))));
 } /* inNset */

/* ========================================================================= */
/* Aufnahme eines Element in eine Nonterminalmenge                           */
/* ========================================================================= */
#ifdef __STDC__
void inclNset(Nont nont,Nontset nset)
#else
void inclNset(nont,nset)
 Nont nont;           /* aufzunehmendes Element */
 Nontset nset;        /* Menge                  */
#endif
 {
  register Nont elno; /* laufende Nummer in der Menge */

#ifdef DEBUG
  printf("inclNset(%s,%lx)\n",decSym(nont),(long)nset);
#endif

#ifdef CHECKALL
  CHECKPT(nset);
  CHECKBED(ISNONT(nont));
#endif

  elno = nont-MINN;   /* mit 0 beginnend numeriert    */
  nset[elno>>MSHIFT] |= (1 << (elno & MMASK)); /* Bit setzen */ 

 } /* inclNset */

/* ========================================================================= */
/* Speicherresevierung fuer Nonterminalmenge                                 */
/* ========================================================================= */
#ifdef __STDC__
void emptyNset(Nontset nset)
#else
void emptyNset(nset)
 Nontset nset;     /* zu leerende Menge          */
#endif
 {
  register short i; /* Zaehler ueber Bitset-Array */

#ifdef DEBUG
  printf("emptyNset(%lx)\n",(long)nset);
#endif

#ifdef CHECKALL
  CHECKPT(nset);
#endif

  for (i=0; i<LENNSET; i++)
    nset[i] = 0;    /* leer */
 } /* emptyNset */

/* ========================================================================= */
/* Speicherresevierung fuer Nonterminalmenge                                 */
/* ========================================================================= */
#ifdef __STDC__
void getNset(Nontset *nset)
#else
void getNset(nset)
 Nontset *nset;     /* Zeiger auf reservierte Menge     */
#endif
 {
  if ((*nset=(Nontset)flAllocate(LENNSET*sizeof(Mbastyp),
                                 (char **)&fl_nset))==NULL)
    mAbort();   /* Speicherreservierung erfolglos */
 } /* getNset */

/* ========================================================================= */
/* Speicherfreigabe fuer Nonterminalmenge                                    */
/* ========================================================================= */
#ifdef __STDC__
void freeNset(Nontset nset)
#else
void freeNset(nset)
 Nontset nset;     /* freizugebende Menge     */
#endif
 {
#ifdef CHECKALL
  CHECKPT(nset);
#endif
  flFree((char**)nset,(char **)&fl_nset);    /* Freigabe in die Freiliste */
 } /* freeNset */

/* ========================================================================= */
/* Operationen auf Mengen von Terminalen                                     */
/* ========================================================================= */

/* ========================================================================= */
/* Test der Zugehoerigkeit eines Element zu einer Terminalmenge              */
/* ========================================================================= */
#ifdef __STDC__
BOOL inTset(Term term,Termset tset)
#else
BOOL inTset(term,tset)
 Term    term;     /* Element                */
 Termset tset;     /* Menge                  */
#endif
 {
  register Term elno; /* laufende Nummer in der Menge */

#ifdef CHECKALL
  CHECKPT(tset);
  CHECKBED(ISTERM(term));
#endif

  elno = term-MINT;        /* mit 0 beginnend numeriert    */
  return((BOOL)(tset[elno>>MSHIFT] & (1 << (elno & MMASK))));
 } /* inTset */

/* ========================================================================= */
/* Aufnahme eines Element in eine Terminalmenge                           */
/* ========================================================================= */
#ifdef __STDC__
void inclTset(Term term,Termset tset)
#else
void inclTset(term,tset)
 Term term;           /* aufzunehmendes Element */
 Termset tset;        /* Menge                  */
#endif
 {
  register Term elno; /* laufende Nummer in der Menge */

#ifdef DEBUG
  printf("inclTset(%s,%lx)\n",decSym(term),(long)tset);
#endif

#ifdef CHECKALL
  CHECKPT(tset);
  CHECKBED(ISTERM(term));
#endif

  elno = term-MINT;   /* mit 0 beginnend numeriert    */
  tset[elno>>MSHIFT] |= (1 << (elno & MMASK)); /* Bit setzen */ 

 } /* inclTset */

/* ========================================================================= */
/* Speicherresevierung fuer Terminalmenge                                 */
/* ========================================================================= */
#ifdef __STDC__
void emptyTset(Termset tset)
#else
void emptyTset(tset)
 Termset tset;     /* zu leerende Menge          */
#endif
 {
  register short i; /* Zaehler ueber Bitset-Array */

#ifdef DEBUG
  printf("emptyTset(%lx)\n",(long)tset);
#endif

#ifdef CHECKALL
  CHECKPT(tset);
#endif

  for (i=0; i<LENTSET; i++)
    tset[i] = 0;    /* leer */
 } /* emptyTset */

/* ========================================================================= */
/* Speicherresevierung fuer Terminalmenge                                 */
/* ========================================================================= */
#ifdef __STDC__
void getTset(Termset *tset)
#else
void getTset(tset)
 Termset *tset;     /* Zeiger auf reservierte Menge     */
#endif
 {
  if ((*tset=(Termset)flAllocate(LENTSET*sizeof(Mbastyp),
                                 (char **)&fl_tset))==NULL)
    mAbort();   /* Speicherreservierung erfolglos */
 } /* getTset */

/* ========================================================================= */
/* Speicherfreigabe fuer Terminalmenge                                    */
/* ========================================================================= */
#ifdef __STDC__
void freeTset(Termset tset)
#else
void freeTset(tset)
 Termset tset;     /* freizugebende Menge     */
#endif
 {
#ifdef CHECKALL
  CHECKPT(tset);
#endif
  flFree((char**)tset,(char **)&fl_tset);    /* Freigabe in die Freiliste */
 } /* freeTset */

