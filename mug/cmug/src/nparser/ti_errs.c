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
/* ti_errs.c :                                                            */ 
/* LR(k)-Parser-Tabellen-Interpreter                                      */ 
/* Modul : Ausgabe und Komprimierung von Fehlermeldungen                  */ 
/* ---------------------------------------------------------------------- */ 
/* erstellt  : 26.12.89                                                   */ 
/* ********************************************************************** */
#ifdef __STDC__
#include <stddef.h>
#include <stdlib.h>
#endif
#include <stdio.h>
#include <time.h>
#include "defs.h"
#include "dbg.h"

#include "ti_token.h"
#include "scanfunk.h"
#include "ti_defs.h"
#include "ti_read.h"
#include "ti_zugr.h"
#include "ti_parse.h"
#include "ti_errs.h"

static int  anzign;             /* Anzahl ignorierter Token       */
static int  in_fb;              /* in Fehlerbehandlung ?          */
static int  erwartet;           /* genau ein Token erwartet       */
static Term eterm;              /* naemlich genau dieses          */
static Token anf_token = NULL;  /* Token des Anfangs des Fehlers  */
static Token end_token = NULL;  /* Token des Endes des Fehlers    */
long parseerrors;               /* Anzahl der Syntaxfehler        */

/* ======================================================================= */
/* Anfang einer Fehlerbehandlung melden                                    */
/* ======================================================================= */
#ifdef __STDC__
void fehlerAnf(Token tok)
             /* erstes fehlerhaftes Token */
#else
void fehlerAnf(tok)
 Token tok;  /* erstes fehlerhaftes Token */
#endif
 {
  if (anf_token == NULL && 
      (anf_token = allocToken()) == NULL) 
   {
    memError();
    exit(20);
   }
  copyToken(anf_token,tok);
  anzign   = 0;
  in_fb    = TRUE;
  erwartet = FALSE;
 } /* fehlerAnf */

/* ======================================================================= */
/* Meldung , dass Token ignoriert wurde                                    */
/* ======================================================================= */
#ifdef __STDC__
void symIgnoriert(Token tok)
#else
void symIgnoriert(tok)
 Token tok;  /* ignoriertes Token, schnueff */
#endif
 {
  if (++anzign > 1)
   {
    if (end_token == NULL && 
      (end_token = allocToken()) == NULL) 
     {
      memError();
      exit(20);
     }
    copyToken(end_token,tok);
   }
 } /* symIgnoriert */

/* ======================================================================= */
/* genau ein Token wurde erwartet, selbiges merken fuer spaeter            */
/* ======================================================================= */
#ifdef __STDC__
void symErwartet(Term term)
             /* Klassencode des erwarteten Tokens */
#else
void symErwartet(term)
 Term term;  /* Klassencode des erwarteten Tokens */
#endif
 {
  erwartet = TRUE;
  eterm    = term;
 } /* symErwartet */

/* ======================================================================= */
/* Wiederaufsetzen bei passendem Token                                     */
/* ======================================================================= */
#ifdef __STDC__
void wiederAufsetzen(Token tok)
             /* passendes Token */
#else
void wiederAufsetzen(tok)
 Token tok;  /* passendes Token */
#endif
 {
  if (anzign > 1) /* mehrere geloescht */
    wErrorf(NULL,"%t: \"%T\" bis einschliesslich %t \"%T\" geloescht\n",
            anf_token,anf_token,end_token,end_token);
  else if (anzign == 1)
    wErrorf(NULL,"%t: \"%T\" geloescht\n",anf_token,anf_token);
  else
    wErrorf(NULL,"%t: \"%T\", Wiederaufsetzpunkt\n",anf_token,anf_token);
  in_fb = FALSE;
  parseerrors++;
  anzign = 0;
 } /* wiederAufsetzen */

/* ======================================================================= */
/* Einfuegen eines Symbols und Wiederaufsetzen damit                       */
/* ======================================================================= */
#ifdef __STDC__
void symEinfuegen(Term ins, Token tok)
#else
void symEinfuegen(ins,tok)
 Term  ins;   /* eingefuegte Symbolklasse        */
 Token tok;   /* Token, vor dem eingefuegt wurde */
#endif
 {
  if (anzign > 1) /* mehrere geloescht */
    wErrorf(NULL,
            "%t: \"%T\" bis einschliesslich %t \"%T\" ersetzt durch %s\n",
            anf_token,anf_token,end_token,end_token,decTerm(ins));
  else if (anzign == 1)
    wErrorf(NULL,"%t: \"%T\" ersetzt durch %s\n",
                 anf_token,anf_token,decTerm(ins));
  else /* reines Einfuegen */
    wErrorf(NULL,"%t: %s vor \"%T\" eingefuegt\n",
            anf_token,decTerm(ins),anf_token);
  in_fb = FALSE;
  parseerrors++;
  anzign = 0;
 } /* symEinfuegen */

/* ======================================================================= */
/* vorzeitiges Dateiende, bevor Wiederaufsetzen moeglich                   */
/* ======================================================================= */
#ifdef __STDC__
void dateiEnde(Token tok)
             /* Dateiendetoken */
#else
void dateiEnde(tok)
 Token tok;  /* Dateiendetoken */
#endif
 {
  if (anzign > 1) /* mehrere geloescht */
    wErrorf(NULL,"%t: \"%T\" bis %t \"%T\" geloescht, Dateiende unerwartet\n",
            anf_token,anf_token,end_token,end_token);
  else if (anzign == 1)
    wErrorf(NULL,"%t: \"%T\" geloescht, Dateiende unerwartet\n",
            anf_token,anf_token);
  else
    wErrorf(NULL,"%t: Dateiende unerwartet\n",anf_token);
  in_fb = FALSE;
  parseerrors++;
  anzign = 0;
 } /* dateiEnde */

/* ======================================================================= */
/* Akzeptiert durch Fehlerbehandlung, Resteingabe vorhanden                */
/* ======================================================================= */
#ifdef __STDC__
void restIgnoriert(void)
#else
void restIgnoriert()
#endif
 {
  wErrorf(NULL,"Resteingabe nach gueltiger Eingabe ignoriert\n");
  in_fb = FALSE;  
  parseerrors++;
  anzign = 0;
 } /* restIgnoriert */

/* ======================================================================= */
/* interner Fehler, sollte nicht auftreten                                 */
/* ======================================================================= */
#ifdef __STDC__
void internFehler(int nr, Token tok)
             /* Fehlernummer                       */
             /* Symbol, bei dem der Fehler auftrat */
#else
void internFehler(nr,tok)
 int   nr;   /* Fehlernummer                       */
 Token tok;  /* Symbol, bei dem der Fehler auftrat */
#endif
 {
  static char *meld[] = {
                  /* ierrKUL */  "Kellerunterlauf\n",
                  /* ierrUGU */  "ungueltiger Uebergang\n",
                  /* ierrINS */  "kein Uebergang mit eingefuegtem Symbol\n",
                  /* ierrNON */  "kein Uebergang mit Nonterminalsymbol\n"
                        };
  if (in_fb)
    wErrorf(NULL,"%t: interner Parserfehler in Fehlerbehandlung: %s\n",
                 tok,meld[nr]);
  else
    wErrorf(NULL,"%t: interner Parserfehler: %s\n",tok,meld[nr]);
  parseerrors++;
  anzign = 0;
 } /* internFehler */


