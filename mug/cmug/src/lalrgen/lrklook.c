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


/* *********************************************** */
/* lrklook.c:                                      */
/* Modul: Datenstruktur Lookaheadset               */
/* erstellt:  14.10.1990 (Ulrich Vollath)          */
/* *********************************************** */
#ifdef __STDC__
#include <stddef.h>
#include <stdlib.h>
#endif
#include <stdio.h>
#include "defs.h"
#include "allocate.h"
#include "grammar.h"
#include "lrkdec.h"
#include "lrklook.h"

extern int max_lookahead;  /* Parameter der Datenstruktur    */

#define MAXK max_lookahead
static Lookset lookset_fl = NULL;

#define allocLookset() ((Lookset)flAllocate(sizeof(LooksetRec),\
                        (char **)&lookset_fl))

#define ERRFILE stderr
/* Makro zum Abbruch mit Fehlermeldung bei vollem Speicher */
#define MABORT do {fputs("memory full\n",ERRFILE);exit(20);}while(0)

/* ======================================================== */
/* Ausgabe eines Lookaheadset in Externdarstellung          */
/* rekursive modulprivate Implementierung                   */
/* ======================================================== */
#ifdef __STDC__
static void printLooksetP(FILE *f,Lookset set,int tiefe)
#else
static void printLooksetP(f,set,tiefe)
 FILE *f;
 Lookset set;
 int tiefe;
#endif
 {
  Lookset ein;

  if (tiefe > MAXK)
   {
    fputs("$ ",f); /* Ende ergaenzen */
   }
  else if (set != NULL)
   {
    if (set->others != NULL)
      fputc('{',f);
    for (ein = set; ein != NULL; ein = ein->others)
     { 
      if (ein->val != EOLOOK)
       {
        fputs(decTerm(ein->val),f);
        fputc(' ',f);    
        printLooksetP(f,ein->rest,tiefe+1);
       }
      else
       {
        fputs("$ ",f);
        if (ein->rest != NULL)
          fputc('?',f);
       }
      if (ein->others != NULL)
        fputc(',',f);
     } /* for */
    if (set->others != NULL)
      fputc('}',f);
   } /* set != NULL */
 } /* printLooksetP */

/* ======================================================== */
/* Ausgabe eines Lookaheadset <set> in Externdarstellung    */
/* in die Datei <f>                                         */
/* ======================================================== */
#ifdef __STDC__
void printLookset(FILE *f,Lookset set)
#else
void printLookset(f,set)
 FILE *f;
 Lookset set;
#endif
 {
  printLooksetP(f,set,0);
 } /* printLookset */

/* ======================================================== */
/* traegt Zeichen in Lookaheadset ein                       */
/* Rueckgabe: Zeiger auf Eintrag mit dem Zeichen            */
/* ======================================================== */
#ifdef __STDC__
Lookset enterLookset(Term c,Lookset *set)
#else
Lookset enterLookset(c,set)
 Term c;
 Lookset *set;
#endif
 {
  Lookset ein;   /* aktueller Eintrag */
  Lookset *vorg; /* Vorgaengerzeiger  */

  for (vorg = set, ein = *set; ein != NULL && ein->val < c;
       vorg = &(ein->others),ein = ein->others); /* Eintragstelle suchen            */
  if (ein != NULL && ein->val == c)
   {
    return(ein);                                 /* vorhandenen Eintrag abliefern   */
   }
  else /* ein == NULL || ein->val > c */         /* nach vorg eintragen             */
   {
    Lookset neu;

    if ((neu = allocLookset()) == NULL)
      MABORT;
    neu->val    = c;
    neu->rest   = NULL;
    neu->others = ein;
    *vorg       = neu;
    return(neu);
   }
 } /* enterLookset */

/* ================================================== */
/* Vergleich zweier Lookaheadsets                     */
/* Rueckgabe != 0 bei Gleichheit                      */
/* ================================================== */
#ifdef __STDC__
int gleichLookset(Lookset set1,Lookset set2)
#else
int gleichLookset(set1,set2)
 Lookset set1;
 Lookset set2;
#endif
 {
  Lookset s1,s2;

  for (s1 = set1, s2 = set2; 
       s1 != NULL && s2 != NULL; 
       s1 = s1->others, s2 = s2->others)
    if (s1->val != s2->val || !gleichLookset(s1->rest,s2->rest) )
      return(0);
  return(s1 == s2);
 } /* gleichLookset */

/* ======================================================== */
/* vereinigt Lookaheadset <*dest> um die Elemente aus <src> */
/* Rueckgabe: Lookaheadset hat sich geaendert               */
/* rekursive modulprivate Implementierung                   */
/* ======================================================== */
#define INDENT(f,i) do {int ii; for (ii = 1; ii < i;ii++) fputs("  ",f);}while(0)
#ifdef __STDC__
static int unionLooksetP(Lookset *dest, Lookset src,int aktk)
#else
static int unionLooksetP(dest,src,aktk)
 Lookset *dest;
 Lookset src;
 int aktk;
#endif
 {
  int changed;
  Lookset d,s,*vorg;

#ifdef DEBUG
  INDENT(DBGFILE,aktk);
  fputs("unionLooksetP(",DBGFILE);
  printLookset(DBGFILE,*dest,1);
  fputc(',',DBGFILE);
  printLookset(DBGFILE,src,1);
  fprintf(DBGFILE,",%d)\n",aktk);
#endif

  if (aktk > MAXK)
    return(0);
  changed = 0;
  for (vorg = dest, d = *dest, s = src;
       s != NULL;)
   {
    if (d == NULL || s->val < d->val)
     { /* Neuen Eintrag nach *vorg einhaengen */
      Lookset neu;

      if ((neu = allocLookset()) == NULL)
        MABORT;
      neu->val    = s->val;
      neu->rest   = NULL;
      if (aktk < MAXK && s->val != EOLOOK)
        unionLooksetP(&neu->rest,s->rest,aktk+1);
      neu->others = d;
      *vorg       = neu;
      vorg = &neu->others;
      changed = 1;
      s = s->others;
     }
    else 
     {
      if (s->val == d->val) /* gleiches Zeichen, Rest vereinigen */
       {
        changed |= unionLooksetP(&d->rest,s->rest,aktk+1);
        s = s->others;
       }
      vorg = &d->others;
      d = d->others;
     }
   } /* for */  
  return(changed);
 } /* unionLooksetP */

/* ======================================================== */
/* vereinigt Lookaheadset <*dest> um die Elemente aus <src> */
/* Rueckgabe: Lookaheadset hat sich geaendert               */
/* ======================================================== */
#ifdef __STDC__
int unionLookset(Lookset *dest, Lookset src)
#else
int unionLookset(dest,src)
 Lookset *dest;
 Lookset src;
#endif
 {
  return(unionLooksetP(dest,src,1));
 } /* unionLookset */
 
/* ========================================================== */
/* Berechnung des konkatenierten Lookaheadsets <src>          */
/* paarweise konkateniert mit den Elementen aus <conc>        */
/* Rueckgabe: berechnetes Lookaheadset                        */
/* rekursive modulprivate Implementierung                   */
/* ========================================================== */
#ifdef __STDC__
static void unionconcLooksetP(Lookset *dest,Lookset src, 
                              Lookset conc,int aktk)
#else
static void unionconcLooksetP(dest,src,conc,aktk)
 Lookset *dest;
 Lookset src;
 Lookset conc;
 int aktk;
#endif
 {
  Lookset s;

#ifdef DEBUG
  INDENT(DBGFILE,aktk);
  fputs("unionconcLookset(",DBGFILE);
  printLookset(DBGFILE,*dest,1);
  fputc(',',DBGFILE);
  printLookset(DBGFILE,src,1);
  fputc(',',DBGFILE);
  printLookset(DBGFILE,conc,1);
  fprintf(DBGFILE,",%d)\n",aktk);
#endif

  if (aktk > MAXK)
    return;
  for (s = src; s != NULL; s = s->others)
   {
#ifdef DEBUG
    INDENT(DBGFILE,aktk);
    fputs(" s = ",DBGFILE);
    printLookset(DBGFILE,s);
    fputc('\n',DBGFILE);
#endif

    if (s->val == EOLOOK) /* src enthaelt 'epsilon' */
     { /* Ende erstes Element, Zweites anhaengen */
      unionLooksetP(dest,conc,aktk);
     } /* Ende erstes Element, Zweites anhaengen */
    else
     { /* Rest des ersten Elementes kopieren */
      Lookset el;

      el = enterLookset(s->val,dest);  /* Zeichen kopieren */
      unionconcLooksetP(&el->rest,s->rest,conc,aktk+1);
     } /* Rest des ersten Elementes kopieren */
   } /* for */
 } /* unionconcLooksetP */

/* ========================================================== */
/* Berechnung des konkatenierten Lookaheadsets <src>          */
/* paarweise konkateniert mit den Elementen aus <conc>        */
/* ========================================================== */
#ifdef __STDC__
void unionconcLookset(Lookset *dest,Lookset src, Lookset conc)
#else
void unionconcLookset(dest,src,conc)
 Lookset *dest;
 Lookset src;
 Lookset conc;
#endif
 {
  unionconcLooksetP(dest,src,conc,1);
 } /* unionconcLookset */

/* ================================================== */
/* recursive descend parser fuer die Grammatik :      */
/*     B  ::=  c | c B | { BL }                       */
/*     BL ::=  B | B , BL                             */
/* rekursive modulprivate Implementierung             */
/* ================================================== */
#define MKTREE_ERR(msg,str) do {fputs("makeLookset: ",ERRFILE);\
   fprintf(ERRFILE,msg,str);fputc('\n',ERRFILE);exit(20);}while(0)
#define SKIP(p) do {while(*(p) == ' ') (p)++;} while (0)
#ifdef __STDC__
static char *makeLookset1(char *darst,Lookset *set, int tiefe)
#else
static char *makeLookset1(darst,set,tiefe)
 char *darst;
 Lookset *set;
 int tiefe;
#endif
 {
  char *p;
  Lookset *s;
  int t;

  p = darst;
  s = set; 
  t = tiefe;
  while(1)
   {
    SKIP(p);
    if (*p == '{')
     { /* Variante B ::= { BL } */
      p++;   /* '{' ueberlesen */
      while (1)
       {
        SKIP(p);
        p = makeLookset1(p,s,t); /* B parsen                 */
        if (*p == ',')           /* solange ", BL" vorhanden */
          p++;                   /* ',' ueberlesen           */
        else
          break;
       }
      if (*p != '}')
        MKTREE_ERR("missing '}' before \"%s\"",p);
      p++;                       /* '}' ueberlesen           */
      SKIP(p);
      return(p);
     }
    else if (*p == '\0')
      MKTREE_ERR("empty (partial) tree",p);
    else if (*p == ',')
      MKTREE_ERR("unexpected ',' at \"%s\"",p);
    else if (*p == '}')
      MKTREE_ERR("too much '}' at \"%s\"",p);
    else
     { /* Variante B ::= c oder B ::= c B */
      int vorg_eps;

      if (vorg_eps = (*p == '$'))
       {
        if (t <= MAXK)
         {
          Lookset hpfix; /* damit der daemliche hp-c89 den Adressoperator frisst */

          hpfix = enterLookset(EOLOOK,s);    /* End-Element eintragen     */ 
          s     = &hpfix->rest;
         }
       }
      else
       {
        if (*p == '\\' && p[1] != '\0')
          p++;                           /* Fluchtsymbol '\' ueberlesen */
        if (t <= MAXK)
         {
          Lookset hpfix; /* damit der daemliche hp-c89 den Adressoperator frisst */

          hpfix = enterLookset(*p,s);    /* Element eintragen           */ 
          s     = &hpfix->rest;
         }
       }
      p++;                               /* c ueberlesen                */
      SKIP(p);
      if (*p == '\0' || *p == '}' || *p == ',')
       {
        if (t < MAXK && !vorg_eps)  
          enterLookset(EOLOOK,s);        /* Stringende einlesen         */
        return(p);
       }
      else if (vorg_eps)
        MKTREE_ERR("sons after '$' at \"%s\"",p);
      else
        t++;
     } /* Variante B ::= c oder B ::= c B */
   } /* while(1) */
  /* NOTREACHED */
 } /* makeLookset1 */


/* ======================================================== */
/* wandelt Externdarstellung in Lookaheadset um             */
/* Eingabeform:                                             */
/*     B  ::=  c | c B | { BL }                             */
/*     BL ::=  B | B , BL                                   */
/* ======================================================== */
#ifdef __STDC__
void makeLookset(char *darst,Lookset *set)
#else
void makeLookset(darst,set)
 char *darst;
 Lookset *set;
#endif
 {
#if 0
  char *p;

  if (*(p = makeLookset1(darst,set,1)) != '\0')
    MKTREE_ERR("unexpected rest \"%s\" after tree",p); 
#endif
 } /* makeLookset */

