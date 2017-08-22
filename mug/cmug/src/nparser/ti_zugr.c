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
/* ti_zugr.c :                                                            */
/* LR(k)-Parser-Tabellen-Interpreter                                      */
/* Modul : Zugriffe auf die Tabelle                                       */
/* ---------------------------------------------------------------------- */
/* Aenderung : 23.12.89, zugrMask                                         */
/* Aenderung : 14.08.89, vollstaediges 'typeing'                          */
/* Aenderung :12.08.89, Zugriffsfunktionen getTab?()                      */
/* Aenderung : 23.07.89, unbedingt()                                      */
/* Aenderung : 13.07.89, Bug in getTueb beseitigt                         */
/* erstellt  : 09.07.89                                                   */
/* ********************************************************************** */
#ifdef __STDC__
#include <stddef.h>
#include <stdlib.h>
#endif
#include <stdio.h>
#include "defs.h"      /* diverse unspezifische Definitionen        */

#include "ti_defs.h" 
#include "ti_zugr.h"

Ptab *atab;                  /* aktuelle Tabelle                          */

/* ===================================================================== */
/* Zugriff auf 8-Bit-Tabelle                                             */
/* ===================================================================== */
#ifdef __STDC__
Tabindex getTab1(Tabelle tab, Tabindex ind)
{
#else
Tabindex getTab1(tab,ind)
 Tabelle  tab;
 Tabindex ind;
 {
#endif
  return((Tabindex)((Uint8 *)tab)[ind]);
 } /* getTab1 */

/* ===================================================================== */
/* Zugriff auf 16-Bit-Tabelle                                            */
/* ===================================================================== */
#ifdef __STDC__
Tabindex getTab2(Tabelle tab, Tabindex ind)
{
#else
Tabindex getTab2(tab,ind)
 Tabelle  tab;
 Tabindex ind;
 {
#endif
  return((Tabindex)((Uint16 *)tab)[ind]);
 } /* getTab2 */

/* ===================================================================== */
/* Zugriff auf 32-Bit-Tabelle                                            */
/* ===================================================================== */
#ifdef __STDC__
Tabindex getTab4(Tabelle tab, Tabindex ind)
{
#else
Tabindex getTab4(tab,ind)
 Tabelle  tab;
 Tabindex ind;
 {
#endif
  return((Tabindex)((Uint32 *)tab)[ind]);
 } /* getTab4 */

/* ===================================================================== */
/* Zugriff auf eine der Tabellen                                         */
/* ===================================================================== */
#ifdef __STDC__
Tabindex getTab(Tabelle tab,Typlen len,Tabindex ind)
#else
Tabindex getTab(tab,len,ind)
 Tabelle  tab;
 Typlen   len;
 Tabindex ind;
#endif
 {
  switch(len)
   {
    case 1:
            return((Tabindex)((Uint8 *)tab)[ind]);
    case 2:
            return((Tabindex)((Uint16 *)tab)[ind]);
    case 4:
            return((Tabindex)((Uint32 *)tab)[ind]);
    default:
            printf("Fehler in getTab()\n");
            exit(25);
   } /* switch */
  return((Tabindex)0);
 } /* getTab */

/* ===================================================================== */
/* liefert passende Zugriffsfunktion ab                                  */
/* ===================================================================== */
#ifdef __STDC__
ZFN_TYPE(getTabfunkt(Typlen len))
#else
ZFN_TYPE(getTabfunkt(len))
 Typlen len;
#endif
 {
  switch(len)
   {
    case 1:
            return(getTab1);
    case 2:
            return(getTab2);
    case 4:
            return(getTab4);
    default:
            fputs("Fehler in getTabfunkt()\n",stderr);
            exit(25);
   } /* switch */
  return(NULL);
 } /* getTabfunkt */


/* ===================================================================== */
/* liefert Grundlaenge der passenden Zugriffsfunktion ab                 */
/* ===================================================================== */
#ifdef __STDC__
Typlen getTabfunktlen(Tabindex (*fkt) (Tabelle, Tabindex))
{
#else
Typlen getTabfunktlen(fkt)
 ZFN_TYPE(fkt);
 {
#endif
  if (fkt == getTab1)
    return((Typlen)1);
  else if (fkt == getTab2)
    return((Typlen)2);
  else if (fkt == getTab4)
    return((Typlen)4);
  else
   {
    fputs("Fehler in getTabfunktlen()\n",stderr);
    exit(25);
   }
  return((Typlen)0);
 } /* getTabfunktlen */

/* ===================================================================== */
/* liefert Namen der passenden Zugriffsfunktion ab                       */
/* ===================================================================== */
#ifdef __STDC__
char *getTabfunktname(Tabindex (*fkt) (Tabelle, Tabindex))
{
#else
char *getTabfunktname(fkt)
 ZFN_TYPE(fkt);
 {
#endif
  if (fkt == getTab1)
    return("getTab1");
  else if (fkt == getTab2)
    return("getTab2");
  else if (fkt == getTab4)
    return("getTab4");
  else
   {
    fputs("Fehler in getTabfunktname()\n",stderr);
    exit(25);
   }
  return(NULL);
 } /* getTabfunktname */

/* ===================================================================== */
/* berechnet den shift-count fuer Uebergangs-Zugriffe                    */
/* ===================================================================== */
#ifdef __STDC__
int getUebshift (Typlen len)
#else
int getUebshift (len)
 Typlen len;
#endif
 {
  switch(len)
   {
    case 1:
            return((int)(sizeof(Uint8)*8-UEBARTBITS));
    case 2:
            return((int)(sizeof(Uint16)*8-UEBARTBITS));
    case 4:
            return((int)(sizeof(Uint32)*8-UEBARTBITS));
    default:
            printf("Fehler in getUebshift()\n");
            exit(25);
   } /* switch */
  return(0);
 } /* getUebshift */


/* ===================================================================== */
/* Dekodieren eines Terminalzeichens                                     */
/* ===================================================================== */
#ifdef __STDC__
char *decTerm(Term t)
{
#else
char *decTerm(t)
 Term t;
 {
#endif
  return(TNAM(*atab,t));
 } /* decTerm */

/* ===================================================================== */
/* Dekodieren eines Nonterminalzeichens                                  */
/* ===================================================================== */
#ifdef __STDC__
char *decNont(Nont n)
{
#else
char *decNont(n)
 Nont n;
 {
#endif
  return(NNAM(*atab,n));
 } /* decNont */


/* ===================================================================== */
/* terminalen Uebergang bestimmen                                        */
/* Rueckgabe : gefundenen Uebergang, 0 falls kein Uebergang moeglich     */
/* ===================================================================== */
#ifdef __STDC__
Ueb getTueb(Zust zust, Term term)
              /* Zustand, aus dem der Uebergang erfolgt */
              /* zu lesendes Terminalsymbol             */
#else
Ueb getTueb(zust,term)
 Zust zust;   /* Zustand, aus dem der Uebergang erfolgt */
 Term term;   /* zu lesendes Terminalsymbol             */
#endif
 {
  register Tabindex a;     /* aktueller Index                          */
  register Tabindex u,o;
  register Term  t;        /* Eintrag in Terminalsymbol-Tabelle        */

  DBGPRT((" getTueb(%ld,%s)",(long)zust,decTerm(term)));

  u = TINDVON(*atab,zust); /* kleinster Index */
  if ( (o = TINDBIS(*atab,zust) ) > u)
   {  /* Bisektionssuche in den Uebergaengen */
    o--;                     /* Index korrigieren (ausschl.->einschl.)   */
    DBGPRT(("[%ld .. %ld]",(long)u,(long)o));
    while (u < o)            /* Suchen, bis passende Produktion gefunden */
     {
      a = (u+o)/2;             /* in der Mitte suchen                    */   
      t = TERMUEBSYM(*atab,a); /*zu lesendes Terminalzeichen            */
      DBGPRT(("<%ld %s>",(long)a,decTerm(t)));
      if (t < term)          /* Index a zu klein                         */
        u = a + 1;           /* weiter oben suchen, inkl. a              */
      else                   /* Index a zu gross oder richtig            */
        o = a;               /* weiter unten suchen                      */
     } /* while u < o */
    if ( TERMUEBSYM(*atab,u) == term)
     {
      DBGPRT((" = %lx (g)\n",(long)TERMUEB(*atab,u) )) ; 
      return((Ueb)TERMUEB(*atab,u)); /* Uebergang abliefern */
    }
   }
  DBGPRT((" = %lx (d)\n",(long)TDEF(*atab,zust) )); 
  return( (Ueb)TDEF(*atab,zust)); /* Default abliefern   */
 } /* getTueb */

/* ===================================================================== */
/* nonterminalen Uebergang bestimmen                                     */
/* Rueckgabe : gefundenen Uebergang, 0 falls kein Uebergang moeglich     */
/* ===================================================================== */
#ifdef __STDC__
Ueb getNueb(Zust zust, Nont nont)
              /* Zustand, aus dem der Uebergang erfolgt    */
              /* zu lesendes Nonterminalsymbol             */
#else
Ueb getNueb(zust,nont)
 Zust zust;   /* Zustand, aus dem der Uebergang erfolgt    */
 Nont nont;   /* zu lesendes Nonterminalsymbol             */
#endif
 {
  register Tabindex a;       /* aktueller Index                          */
  register Tabindex u,o;
  register Zust  z;        /* Eintrag in Zustands-Tabelle              */

  DBGPRT((" getNueb(%ld,%s)",(long)zust,decNont(nont) ));
  u = NINDVON(*atab,nont);
  if ( (o = NINDBIS(*atab,nont)) > u)
   {  /* Bisektionssuche in den Uebergaengen */
    o--;                     /* Index korrigieren (ausschl.->einschl.)   */
    DBGPRT(("[%ld .. %ld]",(long)u,(long)o));
    while (u < o)            /* Suchen, bis passende Produktion gefunden */
     {
      a = (u+o)/2;           /* in der Mitte suchen                      */   
      z = NUEBZUST(*atab,a);
      DBGPRT(("<%ld %ld>",(long)a,(long)z) );
      if (z > zust)          /* Index a zu klein (umgekehrt sortiert)    */
        u = a + 1;           /* weiter oben suchen, inkl. a              */
      else                   /* Index a zu gross oder richtig            */
        o = a;               /* weiter unten suchen                      */
     } /* while u < o */
    if (NUEBZUST(*atab,u) == zust)
     {
      DBGPRT((" = %lx (g)\n",(long)NUEB(*atab,u) )); 
      return((Ueb)NUEB(*atab,u) ); /* Uebergang abliefern */
     }
   } /* if (o> u) */
  DBGPRT((" = %lx (d)\n",(long)NDEF(*atab,nont) )); 
  return ((Ueb)NDEF(*atab,nont)); /* Default abliefern   */
 } /* getNueb */

/* ============================================================= */
/* stellt fest, ob im Zustand zust nur ein Terminalzeichen term  */
/* gelesen werden kann                                           */
/* dann Rueckgabe TRUE                                           */
/* ============================================================= */
#ifdef __STDC__
int unbedingt(Zust zust, Term *term, Ueb *ueb)
              /* zu testender Zustand             */
              /* ggf. zu lesendes Terminalzeichen */
              /* Uebergang mit term               */
#else
int unbedingt(zust,term,ueb)
 Zust zust;   /* zu testender Zustand             */
 Term *term;  /* ggf. zu lesendes Terminalzeichen */
 Ueb  *ueb;   /* Uebergang mit term               */
#endif
 {
  register Tabindex ind;  /* Index des unbedingt-Uebergangs */


  if ( (ind = TINDVON(*atab,zust)) + 1
        == TINDBIS(*atab,zust) )
   { /* nur ein terminaler Uebergang */
    *term = TERMUEBSYM(*atab,ind);
    *ueb  = TERMUEB(*atab,ind);
    return(TRUE);
   }
  else
    return(FALSE);
 } /* unbedingt */

/* ============================================================= */
/* Berechnung der Zugriffsmasken fuer die Tabelle                */
/* ============================================================= */
#ifdef __STDC__
void zugrMask(Ueb *uebmsk,Ueb *infmsk,Ueb *shiftueb,
              Ueb *redueb,Ueb *spontueb)
#else
void zugrMask(uebmsk,infmsk,shiftueb,redueb,spontueb)
 Ueb *uebmsk;     /* Maske fuer Uebergangsart                    */
 Ueb *infmsk;     /* Maske fuer Uebergangsinformation            */
 Ueb *shiftueb;   /* Wert Shift-Uebergang                        */
 Ueb *redueb;     /* Wert Shift-Reduce-Uebergang                 */
 Ueb *spontueb;   /* Wert spontaner Reduce-Uebergang             */
#endif
 {
  register int sc;   /* Shiftcount */
   
  sc = USHIFT(*atab); 
  *uebmsk   = UEBARTMSK << sc;
  *infmsk   = 0xFFFFFFFFL & ~*uebmsk;
  *shiftueb = UEBARTSHIFT << sc;
  *redueb   = UEBARTRED << sc;
  *spontueb = UEBARTSPONT << sc;
  DBGPRT(("uebmsk   = %8lx\n",(long)*uebmsk));
  DBGPRT(("infmsk   = %8lx\n",(long)*infmsk));
  DBGPRT(("shiftueb = %8lx\n",(long)*shiftueb));
  DBGPRT(("redueb   = %8lx\n",(long)*redueb));
  DBGPRT(("spontueb = %8lx\n",(long)*spontueb));
 } /* zugrMask */

