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
/* Grammar.c   :                                                          */
/* LR(k)-Parser-Generator                                                 */
/* Modul : Verwaltung der Datenstruktur fuer die Grammatik                */
/* Aenderung        : 16.11.89 ak_gem in Initialisierung                  */
/* Aenderung        : 02.07.89 detailliertere Informationen zu nonts      */
/* Aenderung        : 25.5.89  Zustandsliste zu jedem Item                */
/* Aenderung        : 7.3.89,  Ueberwachungen zur Laufzeit                */
/* Aenderung        : 27.2.89, Routine prodNr()                           */
/* erstellt         : 26.1.89                                             */
/* ********************************************************************** */
#ifdef __STDC__
#include <stddef.h>
#include <stdlib.h>
#endif
#include <stdio.h>           /* E/A-Deklarationen                         */
#include "defs.h"            /* diverse unspezifische Definitionen        */
#include "checks.h"          /* Deklarationen fuer Ueberpruefungen        */
#include "grammar.h"         /* Definition der Datenstruktur              */

/* ==================================================================== */
/* globale Datenstruktur fuer die Grammatik                             */
/* ==================================================================== */
Grammar g;                   /* von allen zugreifenden Modulen importiert */

#ifdef __STDC__
extern void mAbort(void);    /* hier definiert, um includes zu minimieren */
#else
extern void mAbort();
#endif

/*====================================================================== */
/* Zugriff auf linke Seite der Produktion, zu der das Item item gehoert   */
/* Produktionsanfaenge sind dadurch gekennzeichnet, dass das              */
/* Vorgaengeritem (falls vorhanden) die Laenge 0 traegt                   */
/*====================================================================== */
#ifdef __STDC__
Item lhsItem(Item item)
#else
Item lhsItem(item)
 Item item;          /* Item, dessen linke Seite gesucht wird  */
#endif
 {
  register Item it;  /* Item fuer Suche                        */

  CHECKBED(ISITEM(item));
  for (it = item; it > MINH && ITEMLEN(it-1)!=0; it--) ; /* Suchen */
  return(it);
 } /* lhsItem */


/*====================================================================== */
/* Berechnen der Nummer der Produktion, zu der das Item item gehoert      */
/*====================================================================== */
#ifdef __STDC__
Prod prodNr(Item item)
#else
Prod prodNr(item)
 Item item;          /* Item, dessen Produktion Seite gesucht wird  */
#endif
 {
  register Prod ap;  /* aktuelle Produktion fuer Suche         */
  register Prod up;  /* Untergrenze fuer die Produktion        */
  register Prod op;  /* Obergrenze fuer die Produktion         */

  CHECKBED(ISITEM(item));
  /* ----------------------------------- */
  /* binaere Suche nach der Produktion   */
  /* ----------------------------------- */
  up = MINP;             /* Untergrenze fuer die Suche               */
  op = MAXP;             /* Obergrenze fuer die Suche                */

  while (up < op)        /* Suchen, bis passende Produktion gefunden */
   {
    ap = (up+op+1)/2;    /* in der Mitte suchen mit Aufrunden        */   
    if (LHS(ap) > item)  /* Produktion ap zu gross                   */
      op = ap - 1;       /* weiter unten suchen                      */
    else                 /* Produktion ap zu klein oder richtig      */
      up = ap;           /* weiter oben suchen, inkl. ap             */
   }
  /* --------------------------------------------------------------- */
  /* bei korrektem Aufruf mit gueltigem item ist up die gesuchte     */
  /* Produktion, deshalb kein weiterer Vergleich                     */
  /* --------------------------------------------------------------- */
  return(up);            /* gefundene Produktion abliefern           */
 } /* prodNr */

/*====================================================================== */
/* Platzreservierung fuer Grammatik-Datenstruktur                         */
/* Initialisierung der Grammatik-Datenstruktur                            */
/* Bereiche, Zeiger etc.                                                  */
/*====================================================================== */
#ifdef __STDC__
BOOL initGrammar(Term maxt,Nont maxn,Item anzp,Item anzi)
#else
BOOL initGrammar(maxt,maxn,anzp,anzi)
 Term maxt;              /* maximal verwendetes Terminalzeichen         */
 Nont maxn;              /* maximale verwendetes Nonterminalzeichen     */
 Item anzp;              /* Anzahl der Produktionen                     */
 Item anzi;              /* Anzahl der Items                            */
#endif
 {
  Nont n;                /* bearbeitetes Nonterminal                   */
  Prod p;                /* bearbeitete Produktion                     */
  Item i;                /* bearbeitetes Item                          */

  /* -------------------------------------------------------------------- */
  /* Bereiche definieren                                                  */
  /* -------------------------------------------------------------------- */
  MAXT = maxt;              /* Obergrenze setzen                          */
  MAXN = maxn;              /* Obergrenze setzen                          */
  METAAXIOM = MAXN;         /* Metaaxiom ist immer letztes Nonterminal    */
  RANDZCH = MINT;           /* Randzeichen ist immer erstes Terminal      */

  MAXH = MINH+anzp-1+anzi;  /* Linke Seiten beruecksichtigen (1 pro Prod.)*/
  MAXP = MINP+anzp-1;       /* anzp Produktionen                          */

  /* -------------------------------------------------------------------- */
  /* Speicher reservieren                                                 */
  /* -------------------------------------------------------------------- */
   /* Array Beschreibungen der Nonterminalzeichen anlegen              */
  if ( (g.nonts = (Nelem *)MALLOC( (MAXN-MINN+1)*sizeof(Nelem) )) == NULL )
    mAbort();    /* nicht genug Speicher */

   /* Array aller Items der Produktionen anlegen                       */
  if ( (g.items = (Helem *)MALLOC( (MAXH-MINH+1)*sizeof(Helem) )) == NULL )
    mAbort();    /* nicht genug Speicher */

   /* Array aller Produktionen der Grammatik anlegen                   */
  if ( (g.prods = (Pelem *)MALLOC( (MAXP-MINP+1)*sizeof(Pelem) )) == NULL )
    mAbort();    /* nicht genug Speicher */

   /* Array Zeiger auf Externdarstellungen der Terminalsymbole anlegen */
  if ( (g.tnames = (char **)MALLOC( (MAXT-MINT+1)*sizeof(char *) )) == NULL )
    mAbort();    /* nicht genug Speicher */

   /* Array Zeiger auf Externdarstellungen der Nonterminalsymbole anlegen */
  if ( (g.nnames = (char **)MALLOC( (MAXN-MINN+1)*sizeof(char *) )) == NULL )
    mAbort();    /* nicht genug Speicher */

  /* -------------------------------------------------------------------- */
  /* Initialisierungen der Listen                                         */
  /* -------------------------------------------------------------------- */
  FOREACHNONT(n)  /* Produktionslisten zu Nonterminalen leer initialisieren */ 
   {
    FIRSTPROD(n) = UNDEFPROD;  /* noch keine Produktion zu n vorhanden      */
    NONTSTAT(n)  = 0;          /* noch nichts bekannt                       */
   }
  FOREACHPROD(p)  /* Produktionen initialisieren                            */ 
   {
    PRODSTAT(p) = 0;           /* noch nichts bekannt                       */
    NEXTPROD(p) = UNDEFPROD;   /* Liste leer                                */
   }
  /* Makro nicht verwendet, da Typ Zustand hier nicht bekannt               */
  FOREACHITEM(i)  /* Items initialisieren                                   */
   {
    g.items[(i)-MINH].zl = NULL;  /* noch keine Zustaende vorhanden         */
    g.items[(i)-MINH].ak_gem = 0; /* noch keine Aktionskonflikte gemeldet   */
   }
 
  return(TRUE);  /* bis jetzt keine Fehler              */

 } /* initGrammar */



