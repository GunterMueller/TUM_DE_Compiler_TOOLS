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
/* LRKdec.c   :                                                           */
/* LR(k)-Parser-Generator                                                 */
/* Modul : Dekodierung von Symbolen, Items etc.                           */
/* ---------------------------------------------------------------------- */
/* Aenderung : 26.02.90, Dekodierung des Items bei SPONTREDUCE korrigiert */
/*                       es wurde immer das Ansprungitem ausgegeben       */
/* Aenderung : 29.10.89, Bug in decUeb..(REDUCE) beseitigt                */
/* Aenderung : 01.07.89, Anpassung an neue Datenstrukturen                */
/* Aenderung : 24.06.89, Uebergaenge ausfuehrlicher, SHIFT korrigiert     */
/* Aenderung : 10.06.89, EPSRED-Uebergangstyp eliminiert                  */
/* Aenderung : 9.3.89 , E/A-Beschleunigung , Verwendung von fputs         */
/* erstellt  : 27.1.89                                                    */
/* ********************************************************************** */

#include <stdio.h>           /* E/A-Deklarationen                         */
#include "defs.h"            /* diverse unspezifische Definitionen        */
#include "grammar.h"         /* Definition der Datenstruktur              */
#include "listen.h"          /* Deklarationen Listenverwaltung            */ 
#include "lrkzust.h"         /* Deklarationen Zustandsverwaltung          */
#include "lrkdec.h"          /* Deklarationen                             */

/* ========================================================================= */
/* Programm-globale Variablen                                                */
/* ========================================================================= */
extern Grammar g;         /* bearbeitete Grammatik                           */

/* ========================================================================= */
/* Dekodierung eines Terminalsymbols                                         */
/* Rueckgabe : Zeiger auf dekodierte Zeichenreihe                            */
/* ========================================================================= */
#ifdef __STDC__
char *decTerm(Term term)
#else
char *decTerm(term)
 Term term;   /* zu dekodierendes Terminalsymbol */
#endif
 {
  return(TERMNAME(term));
 } /* decTerm */

/* ========================================================================= */
/* Dekodierung eines Nonterminalsymbols                                      */
/* Rueckgabe : Zeiger auf dekodierte Zeichenreihe                            */
/* ========================================================================= */
#ifdef __STDC__
char *decNont(Nont nont)
#else
char *decNont(nont)
 Nont nont;   /* zu dekodierendes Nonterminalsymbol */
#endif
 {
  return(NONTNAME(nont));
 } /* decNont */

/* ========================================================================= */
/* Dekodierung eines Symbols                                                 */
/* Rueckgabe : Zeiger auf dekodierte Zeichenreihe                            */
/* ========================================================================= */
#ifdef __STDC__
char *decSym(Symb sym)
#else
char *decSym(sym)
 Symb sym;   /* zu dekodierendes Symbol */
#endif
 {
  if (ISTERM(sym))
    return(TERMNAME(sym));
  else if (ISNONT(sym))
    return(NONTNAME(sym));
  else if (sym == UNDEFSYM)  /* Psudosymbol */
    return("<>");
  else   /* ungueltiger Wert */
    return("Sym???");
 } /* decSym */

/* ========================================================================= */
/* Dekodiert ein Item einer Produktion, Position wird mit '|' markiert       */
/* Ausgabe auf die Datei file                                                */
/* ========================================================================= */
#ifdef __STDC__
void fdecItem(FILE *file,Item item)
#else
void fdecItem(file,item)
 FILE *file;    /* Datei, in die dekodiert wird */
 Item item;     /* zu dekodierendes Item        */
#endif
 {
  register Item aitem;               /* aktuell auszugebendes Item    */

  if (item < MINH || item > MAXH)    /* Fehler : item existiert nicht */
    fprintf(file,"<%ld> ::= ??? ",(long)item);
  else   /* item ist gueltig */
   { 
    aitem = lhsItem(item);           /* linke Seite suchen            */
    fputs(decSym(ITEMSYM(aitem)),file);
    fputs(" ::= ",file);
    if (item == aitem)     
      fputs("| ",file);
    while (ITEMLEN(aitem) != 0)      /* weitere Positionen vorhanden  */
     {
      aitem++;                       /* naechstes Item                */
      fputs(decSym(ITEMSYM(aitem)),file);
      if (item == aitem)
        fputs(" | ",file);
      else
        putc(' ',file);
     }
   } /* item gueltig */
 } /* fdecItem */

/* ========================================================================= */
/* Dekodiert einen Uebergang rekursiv ueber Lookaheads                       */
/* Ausgabe auf die Datei file                                                */
/* ========================================================================= */
#ifdef __STDC__
static void fdecUebrec(FILE *file,Ueberg ueb,int tiefe)
#else
static void fdecUebrec(file,ueb,tiefe)
 FILE *file;              /* Datei, in die dekodiert wird      */
 Ueberg ueb;              /* zu dekodierender Uebergang        */
 int tiefe;               /* Rekursionstiefe                   */
#endif
 {
  register short i;       /* Zaehler fuer Einruecken           */
  Item lhs;               /* linke Seite bei Reduktion         */
  Prod prod;              /* Produktionsnummer bei Reduktionen */
 
  for (i=0;i<tiefe;i++)
    putc(' ',file);     /* um ein Leerzeichen einruecken */
 
  switch (UEBART(*ueb))
   {
    case SHIFT: 
         {
         register Zustand zust;            /* Zielzustand des SHIFT */

         zust = UEBSZUST(*ueb);            /* Ziel bestimmen        */
         if (ZUSTNR(*zust) != UNDEFZUSTNR) /* echter SHIFT          */
          {
           fprintf(file,"%s : SHIFT(%ld)\n",decSym(UEBSYM(*ueb)),
                                 (long)ZUSTNR(*zust) ); 
           { /* Items des Zielzustandes angeben */ 
            register Position pos;
            FOREACHPOS(*zust,pos)
             {
              for (i=0;i<tiefe;i++)
                putc(' ',file);     /* um ein Leerzeichen einruecken */
              fputs("    ",file);
              fdecItem(file,POSITEM(*pos));
              putc('\n',file);
             }
           }
          } /* echter shift */
         else /* Reduktion */
          {
           lhs = lhsItem(POSITEM(*FIRSTPOS(*zust)));
           prod = prodNr(lhs);   /* Nummer zu reduzierende Produktion */
           fprintf(file,"%s : REDUCE(%s,%ld,p %ld)\n",decSym(UEBSYM(*ueb)),
                           decSym(ITEMSYM(lhs)),(long)ITEMLEN(lhs),(long)prod);
          }
         }
         break;
    case SPONTRED: 
         {
          register Nont n;      /* linke Seite                       */

          lhs = lhsItem(UEBRITEM(*ueb));
          n = ITEMSYM(lhs);       
          prod = prodNr(lhs);   /* Nummer zu reduzierende Produktion */
          if (ISACTION(n))      /* == Aktion ausfuehren              */
            fprintf(file,"%s : ACTION(%s)\n",decSym(UEBSYM(*ueb)),decSym(n));
          else
            fprintf(file,"%s : SPONTRED(%s,%ld,p %ld)\n",decSym(UEBSYM(*ueb)),
                          decSym(n),(long)ITEMLEN(lhs),(long)prod);
         }
         break;
    case LOOK: 
         {
         register Ueberg lueb;   /* Uebergang in Lookaheadliste       */

         fputs(decSym(UEBSYM(*ueb)),file);
         fputs(" : LOOK\n",file);
         FOREACHLISTEL(UEBLOOKS(*ueb),lueb)
           fdecUebrec(file,lueb,(short)(tiefe+1));
         }
         break;
    default:
         fputs("ueb???\n",file); 
         break;
   }
 } /* fdecUebrec */

/* ========================================================================= */
/* Dekodiert einen Uebergang                                                 */
/* Ausgabe auf die Datei file                                                */
/* ========================================================================= */
#ifdef __STDC__
void fdecUeb(FILE *file,Ueberg ueb)
#else
void fdecUeb(file,ueb)
 FILE *file;    /* Datei, in die dekodiert wird */
 Ueberg ueb;    /* zu dekodierender Uebergang   */
#endif
 {
  fdecUebrec(file,ueb,(short)0);
 } /* fdecUeb */

/* ========================================================================= */
/* Dekodiert Uebergangsinformation (ohne Symbol )                            */
/* Ausgabe auf die Datei file                                                */
/* ========================================================================= */
#ifdef __STDC__
void fdecUebinf(FILE *file,Ueberg ueb)
#else
void fdecUebinf(file,ueb)
 FILE *file;    /* Datei, in die dekodiert wird */
 Ueberg ueb;    /* zu dekodierender Uebergang   */
#endif
 {
  Item lhs;               /* linke Seite bei Reduktion         */
  Prod prod;              /* Produktionsnummer bei Reduktionen */
 
  switch (UEBART(*ueb))
   {
    case SHIFT: 
         {
         register Zustand zust;            /* Zielzustand des SHIFT */

         zust = UEBSZUST(*ueb);            /* Ziel bestimmen        */
         if (ZUSTNR(*zust) != UNDEFZUSTNR) /* echter SHIFT          */
          {
           fprintf(file,"\tSHIFT(%ld)\n",(long)ZUSTNR(*zust) ); 
           { /* Items des Zielzustandes angeben */ 
            register Position pos;
            FOREACHPOS(*zust,pos)
             {
              fputs("\t\t",file);
              fdecItem(file,POSITEM(*pos));
              putc('\n',file);
             }
           }
          } /* echter shift */
         else /* Reduktion */
          {
           fputs("\tSHIFTREDUCE(",file);
           fdecItem(file,POSITEM(*FIRSTPOS(*zust)));
           fputs(")\n",file);
          }
         }
         break;
    case SPONTRED: 
         {
          register Nont n;      /* linke Seite                       */

          lhs = lhsItem(UEBRITEM(*ueb));
          prod = prodNr(lhs);   /* Nummer zu reduzierende Produktion */
          n = ITEMSYM(lhs);       
          if (ISACTION(n))      /* == Aktion ausfuehren              */
            fprintf(file,"\tACTION(%s)\n",decSym(n));
          else
           {
            fputs("\tSPONTREDUCE(",file);
            fdecItem(file,NNEXTITEM(UEBRITEM(*ueb),ITEMLEN(UEBRITEM(*ueb))));
            fputs(")\n",file);
           }
         }
         break;
    case LOOK: 
         fputs("\tLOOK ???\n",file);
         break;
    default:
         fputs("ueb???\n",file); 
         break;
   }
 } /* fdecUebinf */

