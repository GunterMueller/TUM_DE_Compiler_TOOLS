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
/* LRKeps.c   :                                                           */
/* LR(k)-Parser-Generator                                                 */
/* Modul : Berechnung der epsilonerzeugenden Nonterminale                 */
/* Aenderung        : 02.07.89 detailliertere Informationen zu nonts      */
/* erstellt         : 28.1.89                                             */
/* ********************************************************************** */

#include <stdio.h>           /* E/A-Deklarationen                         */
#include "defs.h"            /* diverse unspezifische Definitionen        */
#include "grammar.h"         /* Definition der Datenstruktur              */
#include "lrkeps.h"          /* Deklaration dieses Moduls                 */
#include "lrkdec.h"          /* Deklarationen Dekoder                     */

/*====================================================================== */
/* Programmglobale Variablen                                              */
/*====================================================================== */
extern Grammar g;            /* bearbeitete Grammatik                     */

/*====================================================================== */
/* Berechnung der epsilonerzeugenden Nonterminalzeichen                   */
/*====================================================================== */
#ifdef __STDC__
void epsErz(void)
{
#else
void epsErz()
 {
#endif
  BOOL neue;        /* neues psilonerzeugendes Nonterminal gefunden ? */
  register Prod p;  /* betrachtete Produktion                         */
  register Item it; /* betrachtetes Item                              */
  BOOL epsprod;     /* aktuelle Produktion ist epsilonerzeugend       */
  BOOL termprod;    /* aktuelle Produktion ist terminalerzeugend      */
  Symb s;           /* zu lesendes Symbol                             */

#ifdef DEBUG
  printf("epserz()\n");
#endif

  do                /*solange neues epsilonerzeugendes Nonterminal   */
   {
    neue = FALSE;   /* keine Aenderungen in diesem Durchlauf gefunden */
    FOREACHPROD(p)  /* alle Produktionen betrachten                   */
     {
      if (! ( (PRODSTAT(p) & (PS_EPSERZ | PS_NEPSERZ)) &&
              (PRODSTAT(p) & PS_TERMERZ)                 ) )
       { /* vollstaendiger Status dieser Produktion noch nicht bekannt */
        epsprod = TRUE;          /* vorbesetzen fuer Test          */
        termprod = TRUE;         /* vorbesetzen fuer Test          */
        it = LHS(p);             /* Item der linken Seite          */
        while (ITEMLEN(it) != 0) /* bis Ende erreicht oder break   */
         {
          it++;                  /* naechstes zu lesendes Item       */
          s = ITEMSYM(it);       /* zu lesendes Symbol               */
          if (ISTERM(s) )              /* p kann nicht epsilonerzeugend sein */
           {
            PRODSTAT(p) |= PS_NEPSERZ; /* Kennung dafuer setzen              */ 
            epsprod = FALSE;           /* keine epsilonerzeugende Produktion */
           }
          else /* Symbol ist Nonterminal */
           {
            if (!ISEPS(s))  /* in dieser "Runde" nicht feststellbar */
              epsprod = FALSE;  /* keine epsilonerzeugende Produktion   */
            if (! (NONTSTAT(s) & NS_TERMERZ))  /* keine weiteren Inf. */
             {
              termprod = FALSE; /* keine terminalerzeugende Prod.     */
              break;            /* Abbruch while                      */ 
             }
           } /* Symbol ist Nonterminal */
         } /* bis Ende erreicht oder break */
        if (epsprod) /* Ende erreicht, epsilonerzeugend */
         {
          s = ITEMSYM(LHS(p));  /* linke Seite der Produktion */
          if (!ISEPS(s))        /* neue Information           */
           {
            NONTSTAT(s) |= NS_EPSERZ | NS_TERMERZ;  /* Eigenschaft speichern  */
#ifdef DEBUG
            printf("  ISEPS(%s)\n",decSym(s));
#endif
            neue     = TRUE;    /* Aenderung merken           */
           } /* neue Information           */
          PRODSTAT(p) |= PS_EPSERZ | PS_TERMERZ;  /* Produktion kennzeichenen */
         } /* Ende erreicht */
        else if (termprod) /* Produktion ist terminalerzeugend */
         {
          s = ITEMSYM(LHS(p));                  /* linke Seite der Produktion */
          if (!(NONTSTAT(s) & NS_TERMERZ))      /* neue Information           */
           {
            NONTSTAT(s) |= NS_TERMERZ;          /* Eigenschaft speichern      */
#ifdef DEBUG
            printf("  ISTERM(%s)\n",decSym(s));
#endif
            neue     = TRUE;    /* Aenderung merken           */
           } /* neue Information           */
          PRODSTAT(p) |= PS_TERMERZ;          /* Produktion kennzeichnen    */
         } /* terminalerzeugend */
       } /* Status dieser Produktion nicht bekannt */
     } /* FOREACHPROD(p) */
   } while (neue);  /*solange neues epsilonerzeugendes Nonterminal    */
#ifdef DEBUG
  printf("epserz() Ende\n");
#endif
 } /* epsErz */

