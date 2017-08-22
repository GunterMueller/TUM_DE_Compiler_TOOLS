
/* ************************************************************* */
/* scn_link.c : Funktionslibrary des tabellengetriebenen         */
/*       parametrisierten Scanners, bei Bedarf zugelinkte Teile	 */
/* fuer jedes #define L_... einmal zu uebersetzen                */
/* erstellt  24.01.91, Ulrich Vollath				 */
/* ************************************************************* */

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

#ifdef __STDC__
#include <stddef.h>
#include <stdlib.h>
#endif
#include <varargs.h>
#include <limits.h>
#include "dbg.h"

#include <string.h>
#include <stdio.h>
#include <ctype.h>

#include "ps_token.h"  /* allgemeine Definitionen fuer Scanner         */
#include "pstokenP.h"  /* private Definitionen fuer Scanner            */
#include "scanfunk.h"  /* Funktionalitaten Scanner                     */
#include "ps_tab.h"    /* Datenstruktur der Scannertabelle             */
#include "scn_glob.h"  /* globale Vereinbarungen und Variablen         */

#ifdef L_SCANLAH
#ifdef FAST_SCAN
/* =============================================================== */
/* Lookahead, mit vorgegebener Weite                               */
/* =============================================================== */
#ifdef __STDC__
char psScanlah(long weite)
#else
char psScanlah(weite)
 long weite; /* Weite des Look-Aheads */
#endif
 {
  char la;

  if (ps_file_ptr + weite - 1 < ps_file_len) /* noch innerhalb des Puffers */
   {
    la = ps_file_buffer[ps_file_ptr + weite-1];
#if 0
    if ( (la<32) || (la>126) ) 
      la=' ';
#endif
   }
  else
    la=' ';
  return(la);
 } /* psScanlah */
#else /* ! FAST_SCAN */
/* =============================================================== */
/* lookahead, nur innerhalb einer Zeile, da Zeilenende Delimiter   */
/* =============================================================== */
#ifdef __STDC__
char psScanlah(long weite)
#else
char psScanlah(weite)
 long weite; /* Weite des Look-Aheads */
#endif
 {
  char la;

  if (ps_lein>0) /* noch innerhalb aktueller Zeile */
   {
    la = ps_einz[ps_quellref.spalte-1+ps_weite];
#if 0
    if ( (la<32) || (la>126) ) 
      la=' ';
#endif
   }
  else
    la=' ';
  return(la);
 } /* psScanlah */
#endif /* ! FAST_SCAN */
#endif /* L_SCANLAH */

#ifdef L_SCANSPECIALS
/* =================================================================== */
/* Scannen von Sonderzeichentokens                                     */
/* =================================================================== */
#ifdef __STDC__
int psScanspecials(Token token)
#else
int psScanspecials(token)
 Token token;
#endif
 {
  long    maxi;    /* maximaler Index fuer dieses Special    */
  long    mini;    /* minimaler Index fuer dieses Special    */
  long    len;     /* aktuelle Laenge des erkannten Specials */
  Specdef *found;  /* letztes gefundenes Specials            */
  long    flen;    /* Laenge zu found                        */
  char    akt;     /* aktuelles Zeichen                      */

  found = NULL;
  akt   = ps_ezchn;
  len   = 0;
  flen  = 0;
  mini  = 0;
  maxi  = ps_maxspec-1;
  while(1)
   {
    /* ------------------------------------- */
    /* aktuell passenden Bereich suchen      */
    /* ------------------------------------- */
    long altmaxi,aktind; /* Indices fuer binaere Suche in Specialtabelle */

    altmaxi = maxi; /* Obergrenze merken                            */
    while (mini < maxi)
     {
      if (scantab.specdefs[aktind = (mini + maxi) / 2].strg[len] < akt)
        mini = aktind+1;
      else
        maxi = aktind;
     }
    if (mini != maxi || scantab.specdefs[mini].strg[len] != akt )
      break; /* while(1): kein (weiterer) Eintrag vorhanden */
    while(maxi < altmaxi && scantab.specdefs[maxi+1].strg[len] == akt)
      maxi++; /* groessten passenden suchen */
    /* -------------------------------- */
    /* mindestens ein Special passt     */
    /* -------------------------------- */
    if (scantab.specdefs[mini].strg[len+1] == '\0')
     { /* bisher laengstes akzeptiertes */
      found = &scantab.specdefs[mini];
      flen = len;
      if (mini >= maxi)
        break; /* while(1): kein (weiterer) Eintrag vorhanden */
     }
    akt = psScanlah(++len);      /* weiter, laengere Specials existieren */
   } /* while(1) */
  if (found != NULL)
   { /* in die Hashtabelle eintragen ! */
    if (found->fctn == NULL)
     { /* ganz gewoehnliches Special */
      psEnterhashtab(token,found->strg,found->kc,found->val,found->ign,NULL,
                     (int)scantab.case_sensitive,(int)TRUE,(int)FALSE);
      psSkipein(flen+1);
      return(found->ign ? -1 : 1);
     }
    else
     { /* gesonderte Behandlung */
      return(found->fctn(token,found));
     }
   } /* in die Hashtabelle eintragen ! */
  return(0);
 } /* psScanspecials */ 
#endif /* L_SCANSPECIALS*/

#ifdef L_COMMENTS
/* ============================================================= */
/* scannt Kommentare in { .. }                                   */
/* ============================================================= */
#ifdef __STDC__
int psComments(Token token,Specdef *specdef)
#else
int psComments(token,specdef)
 Token   token;
 Specdef *specdef; 
#endif
 {
  psSkipein(1L);
  while (!EndeEin && ps_ezchn != '}')
    psLiesn();
  if (EndeEin )    /* Dateiende in Kommentar         */
    psScanerror(serrCOM);
  else
    psLiesn();     /* abschliessendes } ueberlesen   */
  return(specdef->ign ? -1 : 1);      /* kein Token ausgeben            */
 } /* psComments */
#endif /* L_COMMENTS */

#ifdef L_MCOMMENTS
/* =============================================================== */
/* Kommentare wie in MODULA-2 in (* ... *), nicht verschachtelt !! */
/* =============================================================== */
#ifdef __STDC__
int psMcomments(Token token,Specdef *specdef)
#else
int psMcomments(token,specdef)
 Token   token;
 Specdef *specdef;
#endif
 {
  psSkipein(2L); /* (* ueberlesen */
  while (!EndeEin && (ps_ezchn != '*' || psScanlah(1L) != ')' ) ) 
    psLiesn();
  if (EndeEin ) /* Dateiende im Kommentar */
    psScanerror(serrCOM);
  else
    psSkipein(2L); /* abschliessendes *) ueberlesen */
  return(specdef->ign ? -1 : 1);  /* kein Token ausgeben            */
 } /* psMcomments */
#endif /* L_MCOMMENTS */

#ifdef L_CCOMMENTS
/* =============================================================== */
/* Kommentare wie in C in / *  ... * /                             */
/* =============================================================== */
#ifdef __STDC__
int psCcomments(Token token,Specdef *specdef)
#else
int psCcomments(token,specdef)
 Token   token;
 Specdef *specdef;
#endif
 {
  psSkipein(2L); /* /_* ueberlesen */
  while(!EndeEin && (ps_ezchn != '*' || psScanlah(1L) != '/' ) )
    psLiesn();
  if (EndeEin ) /* Dateiende im Kommentar */
    psScanerror(serrCOM);
  else
    psSkipein(2L); /* abschliessendes * / ueberlesen */
  return(specdef->ign ? -1 : 1);  /* kein Token ausgeben            */
 } /* psCcomments */
#endif /* L_CCOMMENTS */

#ifdef L_IDENTS
/* =============================================================== */
/* Bezeichner oder Schluesselwort lesen                            */
/* =============================================================== */
#ifdef __STDC__
int psIdents(Token token)
#else
int psIdents(token)
 Token token;
#endif
 {
  int idlen;                  /* Laenge des eingetragenen Bezeichners */
  char aktident[IDLEN+1]; 
  Hash hash;

  aktident[0] = ps_ezchn;
  idlen = 1;
  for (psLiesn(); !EndeEin && IS_IDENT_CHAR(ps_ezchn); psLiesn() )
   {
    if (idlen < IDLEN ) /* falls Identifier zu lang : kuerzen */
      aktident[idlen++] = ps_ezchn; 
   }
  aktident[idlen] = '\0';
  /* ------------------------ */
  /* in Hashtabelle nachsehen */
  /* ------------------------ */
  hash = psEnterhashtab(token,aktident,(long)scantab.kc_idents,0L,
                        (long)scantab.ign_idents,&ps_nextid,
                        (int)scantab.case_sensitive,(int)FALSE,(int)TRUE);
  return(hash->iskwd && hash->ign ? -1 : 1);
 } /* psIdents */
#endif /* L_IDENTS */

#ifdef L_KEYWDS
/* =============================================================== */
/* Schluesselwort lesen, fuer Scannertabellen ohne Identifier      */
/* =============================================================== */
#ifdef __STDC__
int psKeywds(Token token)
#else
int psKeywds(token)
 Token token;
#endif
 {
  int  idlen;    /* Laenge des eingetragenen Bezeichners */
  char aktident[IDLEN+1]; 
  Hash hash;

  aktident[0] = ps_ezchn;
  idlen = 1;
  for (psLiesn(); !EndeEin && IS_IDENT_CHAR(ps_ezchn); psLiesn() )
   {
    if (idlen < IDLEN ) /* falls Identifier zu lang : kuerzen */
      aktident[idlen++] = ps_ezchn; 
   }
  aktident[idlen] = '\0';
  /* ------------------------ */
  /* in Hashtabelle nachsehen */
  /* ------------------------ */
  hash = psEnterhashtab(token,aktident,0L,0L,1L /* !!! */,NULL,
                      (int)scantab.case_sensitive,(int)FALSE,(int)FALSE);
  if (!hash->iskwd) /* kein Schluesselwort */
   {
    psScanerror(serrKWD); /* Schluesselwort unbekannt */
    return(0);            /* kein Symbol ausgeben     */
   }
  return(hash->ign ? -1 : 1);
 } /* psKeywds */
#endif /* L_KEYWDS */

#ifdef L_REALS
/* =============================================================== */
/* Einlesen einer Realzahl                                         */
/* =============================================================== */
#ifdef __STDC__
int psReals(Token token)
#else
int psReals(token)
 Token token;
#endif
 {
  char dstr[REALLEN+1]; /* Puffer fuer die Zahldarstellung */
  int  rlen;            /* Index im Puffer                 */
  int  numf;            /* Fehler bereits gemeldet ?       */
  /* ------------------------------------------------------------------------ */
  /* endlicher Automat fuer Realzahlen:                                       */
  /* digit = 0..9, ~ = sonst. Zeichen  					      */
  /* ------------------------------------------------------------------------ */
  /*                 							      */
  /*             digit 							      */
  /*              /--\  						      */
  /*              |  |  			  			      */
  /*              v  /  ~  						      */
  /*            >(fdig)---->| intval |  				      */
  /*     digit /   |         						      */
  /*          /   .|            digit 			        digit	      */
  /* ->(start)     |            /--\   >|rval|			/--\	      */
  /*         \     |            |  |  /				|  |	      */
  /*         .\    v     digit  v  / / e,E      +,-       digit v  / ~        */
  /*           >(fdot)--------->(sdig)--->(expo)--->(exps)---->(edig)->|rval| */
  /*            /  |  \                  ^      \             ^	              */
  /*          ~/  .|    \ e,E            /       \ digit     /                */
  /*          v    v     \--------------/         \---------/                 */
  /*      |rval| |dotdot|                                                     */
  /*                                                                          */
  /* -------------------------------------------------------------------------*/
#define PUTZ(c) do{if(rlen < REALLEN)dstr[rlen++]=(c);else \
        if (!numf){psScanerror(serrNUM);numf=TRUE;setTokeninvalid(token);};\
        psLiesn();}while(0)

  rlen  = 0;
  numf  = FALSE;      /* noch kein Fehler                */
  /* --------------------------------------------------- */
  /* Startzustand, Zusicherung ps_ezchn = digit oder '.' */
  /* --------------------------------------------------- */
  /* --------------------------------------------------- */
  /* mindestens eine Ziffer im Vorkommateil gelesen      */
  /* --------------------------------------------------- */
  while (isdigit(ps_ezchn))
    PUTZ(ps_ezchn);                          /* naechste Ziffer speichern  */
  if  (ps_ezchn != '.' ||                           /* kein Nachkomma      */
       scantab.dotdot_fix && psScanlah(1L) == '.' ) /* .. ist neues Token  */
   {
    /* --------------------------------------------------- */  
    /* Zahl im Puffer liegt in Integer-Darstellung vor     */
    /* --------------------------------------------------- */
    dstr[rlen] = '\0';        /* Zeichenreihe abschliessen  */
    if (scantab.num_and_real) /* als Integerzahl ausgeben   */
     {
      psEnterhashtab(token,dstr,scantab.kc_numbers,
                     (numf ? 0 : atol(dstr)),scantab.ign_numbers,NULL,
                     (int)FALSE,(int)FALSE,(int)FALSE);
      return(scantab.ign_numbers ? -1 : 1);
     }
    else                      /* als Realzahl ausgeben      */
     {
      psEnterhashtab(token,dstr,scantab.kc_reals,0L,scantab.ign_reals,
                     &ps_nextreal,(int)TRUE,(int)FALSE,(int)FALSE);
      return(scantab.ign_reals ? -1 : 1);
     }
   }
  /* --------------------------------------------------- */
  /* ersten Punkt gelesen (nicht gespeichert!)           */
  /* --------------------------------------------------- */
  PUTZ(ps_ezchn);                  /* erster Punkt gehoert zur Zahl       */
  if (ps_ezchn == 'e' || ps_ezchn == 'E')
    PUTZ(ps_ezchn);                /* E speichern                         */
  else if (isdigit(ps_ezchn))      /* erste Nachkommastelle gelesen       */
   { /* Nachkommastellen vorhanden */
    PUTZ(ps_ezchn);                /* Nachkommastelle speichern           */
    /* --------------------------------------------------- */
    /* Nachkommastellen lesen  				   */
    /* --------------------------------------------------- */
    while (isdigit(ps_ezchn))  /* erste Nachkommastellen lesen       */
      PUTZ(ps_ezchn);          /* Nachkommastelle speichern          */
    if (ps_ezchn == 'e' || ps_ezchn == 'E')
      PUTZ(ps_ezchn);          /* E speichern                        */
    else /* sonstige Zeichen: Zahl beendet */
     {
      dstr[rlen] = '\0';       /* Zeichenreihe abschliessen */
      psEnterhashtab(token,dstr,scantab.kc_reals,0L,scantab.ign_reals,
                     &ps_nextreal,(int)TRUE,(int)FALSE,(int)FALSE);
      return(scantab.ign_reals ? -1 : 1);
     }
   } /* Nachkommastellen vorhanden */
  else
   {
    dstr[rlen] = '\0';       /* Zeichenreihe abschliessen */
    psEnterhashtab(token,dstr,scantab.kc_reals,0L,scantab.ign_reals,
                   &ps_nextreal,(int)TRUE,(int)FALSE,(int)FALSE);
    return(scantab.ign_reals ? -1 : 1);
   }
  /* --------------------------------------------------- */
  /* e vom Exponenten gelesen				 */
  /* --------------------------------------------------- */
  if (ps_ezchn == '+' || ps_ezchn == '-')
    PUTZ(ps_ezchn);  /* Vorzeichen des Exponenten speichern       */
  /* --------------------------------------------------- */
  /* im Exponenten nach e und +-		   	 */
  /* --------------------------------------------------- */
  while (isdigit(ps_ezchn))      /* Exponentenstelle gelesen   */
    PUTZ(ps_ezchn);              /* Stelle speichern           */
  dstr[rlen] = '\0';             /* Zeichenreihe abschliessen  */
  psEnterhashtab(token,dstr,scantab.kc_reals,0L,scantab.ign_reals,
                 &ps_nextreal,(int)TRUE,(int)FALSE,(int)FALSE);
  return(scantab.ign_reals ? -1 : 1);
 } /* psReals */
#endif /* L_REALS */

#ifdef L_CREALS
/* =============================================================== */
/* Einlesen einer Realzahl                                         */
/* =============================================================== */
#ifdef __STDC__
int psCreals(Token token)
#else
int psCreals(token)
 Token token;
#endif
 {
  char dstr[REALLEN+1]; /* Puffer fuer die Zahldarstellung */
  int  rlen;            /* Index im Puffer                 */
  int  numf;            /* Fehler bereits gemeldet ?       */
  /* ------------------------------------------------------------------------ */
  /* endlicher Automat fuer Realzahlen:                                       */
  /* digit = 0..9, ~ = sonst. Zeichen  					      */
  /* ------------------------------------------------------------------------ */
  /*                 							      */
  /*             digit 							      */
  /*              /--\  						      */
  /*              |  |  			  			      */
  /*              v  /  ~  						      */
  /*            >(fdig)---->| intval |  				      */
  /*     digit /   |         						      */
  /*          /   .|            digit 			        digit	      */
  /* ->(start)     |            /--\   >|rval|			/--\	      */
  /*         \     |            |  |  /				|  |	      */
  /*         .\    v     digit  v  / / e,E      +,-       digit v  / ~        */
  /*           >(fdot)--------->(sdig)--->(expo)--->(exps)---->(edig)->|rval| */
  /*            /  |  \                  ^      \             ^	              */
  /*          ~/  .|    \ e,E            /       \ digit     /                */
  /*          v    v     \--------------/         \---------/                 */
  /*      |rval| |dotdot|                                                     */
  /*                                                                          */
  /* -------------------------------------------------------------------------*/
#define PUTZ(c) do{if(rlen < REALLEN)dstr[rlen++]=(c);else \
        if (!numf){psScanerror(serrNUM);numf=TRUE;setTokeninvalid(token);};\
        psLiesn();}while(0)

  rlen  = 0;
  numf  = FALSE;      /* noch kein Fehler                */
  /* --------------------------------------------------- */
  /* Startzustand, Zusicherung ps_ezchn = digit oder '.' */
  /* --------------------------------------------------- */
  /* --------------------------------------------------- */
  /* mindestens eine Ziffer im Vorkommateil gelesen      */
  /* --------------------------------------------------- */
  if (scantab.num_and_real &&
      ps_ezchn == '0' && (psScanlah(1L) == 'x' || psScanlah(1L) == 'X'))
    /* --------------------------------------------------- */
    /* Sedezimalzahl folgt				   */
    /* --------------------------------------------------- */
   {
    PUTZ(ps_ezchn); /* 0 IN PUFFER */
    PUTZ(ps_ezchn); /* xX IN PUFFER */
    while (isxdigit(ps_ezchn))
      PUTZ(ps_ezchn);                          /* naechste Ziffer speichern  */
    if (!EndeEin && (ps_ezchn == 'u' || ps_ezchn == 'U'))
      PUTZ(ps_ezchn); /* Laengenangabe abspeichern */
    if (!EndeEin && (ps_ezchn == 'l' || ps_ezchn == 'L'))
      PUTZ(ps_ezchn); /* Laengenangabe abspeichern */
    dstr[rlen] = '\0';        /* Zeichenreihe abschliessen  */
    psEnterhashtab(token,dstr,scantab.kc_numbers,
                   (numf ? 0 : atol(dstr)),scantab.ign_numbers,NULL,
                   (int)FALSE,(int)FALSE,(int)FALSE);
    return(scantab.ign_numbers ? -1 : 1);
   }
  while (isdigit(ps_ezchn))
    PUTZ(ps_ezchn);                          /* naechste Ziffer speichern  */
  if  (ps_ezchn != '.' ||                           /* kein Nachkomma      */
       scantab.dotdot_fix && psScanlah(1L) == '.' ) /* .. ist neues Token  */
   {
    /* --------------------------------------------------- */  
    /* Zahl im Puffer liegt in Integer-Darstellung vor     */
    /* --------------------------------------------------- */
    if (!EndeEin && (ps_ezchn == 'u' || ps_ezchn == 'U'))
      PUTZ(ps_ezchn); /* Laengenangabe abspeichern */
    if (!EndeEin && (ps_ezchn == 'l' || ps_ezchn == 'L'))
      PUTZ(ps_ezchn); /* Laengenangabe abspeichern */
    dstr[rlen] = '\0';        /* Zeichenreihe abschliessen  */
    if (scantab.num_and_real) /* als Integerzahl ausgeben   */
     {
      psEnterhashtab(token,dstr,scantab.kc_numbers,
                     (numf ? 0 : atol(dstr)),scantab.ign_numbers,NULL,
                     (int)FALSE,(int)FALSE,(int)FALSE);
      return(scantab.ign_numbers ? -1 : 1);
     }
    else                      /* als Realzahl ausgeben      */
     {
      psEnterhashtab(token,dstr,scantab.kc_reals,0L,scantab.ign_reals,
                     &ps_nextreal,(int)TRUE,(int)FALSE,(int)FALSE);
      return(scantab.ign_reals ? -1 : 1);
     }
   }
  /* --------------------------------------------------- */
  /* ersten Punkt gelesen (nicht gespeichert!)           */
  /* --------------------------------------------------- */
  PUTZ(ps_ezchn);                  /* erster Punkt gehoert zur Zahl       */
  if (ps_ezchn == 'e' || ps_ezchn == 'E')
    PUTZ(ps_ezchn);                /* E speichern                         */
  else if (isdigit(ps_ezchn))      /* erste Nachkommastelle gelesen       */
   { /* Nachkommastellen vorhanden */
    PUTZ(ps_ezchn);                /* Nachkommastelle speichern           */
    /* --------------------------------------------------- */
    /* Nachkommastellen lesen  				   */
    /* --------------------------------------------------- */
    while (isdigit(ps_ezchn))  /* erste Nachkommastellen lesen       */
      PUTZ(ps_ezchn);          /* Nachkommastelle speichern          */
    if (ps_ezchn == 'e' || ps_ezchn == 'E')
      PUTZ(ps_ezchn);          /* E speichern                        */
    else /* sonstige Zeichen: Zahl beendet */
     {
      dstr[rlen] = '\0';       /* Zeichenreihe abschliessen */
      psEnterhashtab(token,dstr,scantab.kc_reals,0L,scantab.ign_reals,
                     &ps_nextreal,(int)TRUE,(int)FALSE,(int)FALSE);
      return(scantab.ign_reals ? -1 : 1);
     }
   } /* Nachkommastellen vorhanden */
  else
   {
    dstr[rlen] = '\0';       /* Zeichenreihe abschliessen */
    psEnterhashtab(token,dstr,scantab.kc_reals,0L,scantab.ign_reals,
                   &ps_nextreal,(int)TRUE,(int)FALSE,(int)FALSE);
    return(scantab.ign_reals ? -1 : 1);
   }
  /* --------------------------------------------------- */
  /* e vom Exponenten gelesen				 */
  /* --------------------------------------------------- */
  if (ps_ezchn == '+' || ps_ezchn == '-')
    PUTZ(ps_ezchn);  /* Vorzeichen des Exponenten speichern       */
  /* --------------------------------------------------- */
  /* im Exponenten nach e und +-		   	 */
  /* --------------------------------------------------- */
  while (isdigit(ps_ezchn))      /* Exponentenstelle gelesen   */
    PUTZ(ps_ezchn);              /* Stelle speichern           */
  dstr[rlen] = '\0';             /* Zeichenreihe abschliessen  */
  psEnterhashtab(token,dstr,scantab.kc_reals,0L,scantab.ign_reals,
                 &ps_nextreal,(int)TRUE,(int)FALSE,(int)FALSE);
  return(scantab.ign_reals ? -1 : 1);
 } /* psReals */
#endif /* L_CREALS */

#ifdef L_NUMBERS
/* =============================================================== */
/* Einlesen einer vorzeichenlosen ganzen Zahl                      */
/* =============================================================== */
#ifdef __STDC__
int psNumbers(Token token)
#else
int psNumbers(token)
 Token token;
#endif
 {
#define dval(x) ( (int)(x) - (int)('0') )
  char dstr[20];
  char *dptr;
  int val;           /* Wert der Zahl          */
  int numf;          /* Fehler aufgetreten ?   */

  if (ps_ezchn == '.')
    return(0);              /* nur bei reals erlaubt     */
  val     = dval(ps_ezchn); /* erste Ziffer auswerten    */
  dptr    = dstr;           /* Zeiger in Klartextpuffer  */
  *dptr++ = ps_ezchn;       /* erstes Zeichen speichern  */
  numf = FALSE;          /* noch kein Fehler          */ 
  for (psLiesn(); !EndeEin && isdigit(ps_ezchn); psLiesn() )
   {
    if ( (val == (val*10) / 10 ) &&
         (val * 10 <= MAXINT - dval(ps_ezchn) ) )
     {
      val = val*10 + dval(ps_ezchn);      /* noch darstellbar          */
      *dptr++ = ps_ezchn;
     }
    else if (!numf)                   /* Folgefehlerunterdrueckung */
     {
      psScanerror(serrNUM);
      numf = TRUE;
      setTokeninvalid(token);
     }
   } /* Ende Zahl scannen */
  *dptr = '\0';
  psEnterhashtab(token,dstr,scantab.kc_numbers,(numf ? 0 : val),
                 scantab.ign_numbers,NULL,
                 (int)FALSE,(int)FALSE,(int)FALSE);
  return(scantab.ign_numbers ? -1 : 1);
 } /* psNumbers */
#endif /* L_NUMBERS */


#ifdef L_CNUMBERS
/* =============================================================== */
/* Einlesen einer C-Integer-Konstanten                             */
/* =============================================================== */
#ifdef __STDC__
int psCnumbers(Token token)
#else
int psCnumbers(token)
 Token token;
#endif
 {
#define dval(x) ( (int)(x) - (int)('0') )
  char dstr[25];
  char *dptr;
  int val;           /* Wert der Zahl          */
  int numf;          /* Fehler aufgetreten ?   */

  if (ps_ezchn == '.')
    return(0);              /* nur bei reals erlaubt     */
  val     = dval(ps_ezchn); /* erste Ziffer auswerten    */
  dptr    = dstr;           /* Zeiger in Klartextpuffer  */
  *dptr++ = ps_ezchn;       /* erstes Zeichen speichern  */
  numf = FALSE;          /* noch kein Fehler          */ 
  for (psLiesn(); !EndeEin && isdigit(ps_ezchn); psLiesn() )
   {
    if ( (val == (val*10) / 10 ) &&
         (val * 10 <= MAXINT - dval(ps_ezchn) ) )
     {
      val = val*10 + dval(ps_ezchn);      /* noch darstellbar          */
      *dptr++ = ps_ezchn;
     }
    else if (!numf)                   /* Folgefehlerunterdrueckung */
     {
      psScanerror(serrNUM);
      numf = TRUE;
      setTokeninvalid(token);
     }
   } /* Ende Zahl scannen */
  if (!EndeEin && (ps_ezchn == 'u' || ps_ezchn == 'U'))
   {
    *dptr++ = ps_ezchn;
    psLiesn(); /* Laengenangabe ueberlesen */
   }
  if (!EndeEin && (ps_ezchn == 'l' || ps_ezchn == 'L'))
   {
    *dptr++ = ps_ezchn;
    psLiesn(); /* Laengenangabe ueberlesen */
   }
  *dptr = '\0';
  psEnterhashtab(token,dstr,scantab.kc_numbers,(numf ? 0 : val),
                 scantab.ign_numbers,NULL,
                 (int)FALSE,(int)FALSE,(int)FALSE);
  return(scantab.ign_numbers ? -1 : 1);
 } /* psCnumbers */
#endif /* L_CNUMBERS */

#ifdef L_STRINGS
/* =============================================================== */
/* Einlesen eines Strings                                          */
/* =============================================================== */
#ifdef __STDC__
int psStrings(Token token,Specdef *specdef)
#else
int psStrings(token,specdef)
 Token token;
 Specdef *specdef;
#endif
 {
  long strlen;            /* aktuelle Laenge String   */
  int  strf;              /* Fehlerflag               */
  char estr[STRLEN+1];    /* Puffer fuer String       */
  char quote;             /* Delimiter des Strings    */

  quote = ps_ezchn; /* Delimiter merken */
  strlen = 0;
  strf = FALSE;
  for ( psLiesn(); !EndeEin && (ps_ezchn != quote) ; psLiesn() )
   {
    if (strlen < STRLEN) /* String passt noch in Puffer etc. */
      estr[strlen++] = ps_ezchn;
    else if (!strf) /* Folgefehlerunterdrueckung */
     {
      psScanerror(serrSTL); /* zu lang */
      strf = TRUE;
     }
   }  /* Ende String lesen */
  estr[strlen] = '\0';
  if (EndeEin )
   {
    psScanerror(serrSTO);
    return(0);
   }
  psLiesn(); /* abschliessendes ' ueberlesen  */
  psEnterhashtab(token,estr,specdef->kc,0L,specdef->ign,&ps_nextstr,
                 (int)TRUE,(int)FALSE,(int)FALSE);
  return(specdef->ign ? -1 : 1);
 } /* psStrings */
#endif /* L_STRINGS */

#ifdef L_CSTRINGS
/* =============================================================== */
/* Einlesen eines C-Strings                                        */
/* =============================================================== */
#ifdef __STDC__
int psCstrings(Token token,Specdef *specdef)
#else
int psCstrings(token,specdef)
 Token token;
 Specdef *specdef;
#endif
 {
  long strlen;            /* aktuelle Laenge String   */
  int  strf;              /* Fehlerflag               */
  char estr[STRLEN+1];    /* Puffer fuer String       */
  int  bs_seen;		  /* letztes Zeichen war \    */

  strlen  = 0;
  strf    = FALSE;
  bs_seen = FALSE;
  for ( psLiesn(); !EndeEin && (bs_seen || ps_ezchn != '"') ; psLiesn() )
   {
    if (bs_seen)
     { /* \-Sequencen uebersetzen */
      bs_seen = FALSE; 
      switch (ps_ezchn)
       {
        case '\\':
          break; /* nix zu tun, \ ist schon da */
        case 'n':
          estr[strlen-1] = '\n'; /* \ ueberschreiben */
          break;
        case 't':
          estr[strlen-1] = '\t'; /* \ ueberschreiben */
          break;
        case 'v':
          estr[strlen-1] = '\v'; /* \ ueberschreiben */
          break;
        case 'b':
          estr[strlen-1] = '\b'; /* \ ueberschreiben */
          break;
        case 'r':
          estr[strlen-1] = '\r'; /* \ ueberschreiben */
          break;
        case '\'':
          estr[strlen-1] = '\''; /* \ ueberschreiben */
          break;
        case '\"':
          estr[strlen-1] = '\"'; /* \ ueberschreiben */
          break;
        default: /* unbekannte Sequenzen aendern das Zeichen nicht */
          estr[strlen-1] = ps_ezchn; /* \ ueberschreiben */
          break;
       } /* switch */
     } /* \-Sequencen uebersetzen */
    else
     {
      if (strlen < STRLEN) /* String passt noch in Puffer etc. */
        estr[strlen++] = ps_ezchn;
      else if (!strf) /* Folgefehlerunterdrueckung */
       {
        psScanerror(serrSTL); /* zu lang */
        strf = TRUE;
       }
      bs_seen = ps_ezchn == '\\';
     }
   }  /* Ende String lesen */
  estr[strlen] = '\0';
  if (EndeEin )
   {
    psScanerror(serrSTO);
    return(0);
   }
  psLiesn(); /* abschliessendes " ueberlesen  */
  psEnterhashtab(token,estr,specdef->kc,0L,specdef->ign,&ps_nextstr,
                 (int)TRUE,(int)FALSE,(int)FALSE);
  return(specdef->ign ? -1 : 1);
 } /* psCstrings */
#endif /* L_CSTRINGS */

#ifdef L_CCHARS
/* =============================================================== */
/* Einlesen einer C-Zeichenkonstanten                              */
/* =============================================================== */
#ifdef __STDC__
int psCchars(Token token,Specdef *specdef)
#else
int psCchars(token,specdef)
 Token token;
 Specdef *specdef;
#endif
 {
  long strlen;            /* aktuelle Laenge String   */
  int  strf;              /* Fehlerflag               */
  char estr[STRLEN+1];    /* Puffer fuer String       */
  int  bs_seen;		  /* letztes Zeichen war \    */

  strlen  = 0;
  strf    = FALSE;
  bs_seen = FALSE;
  for ( psLiesn(); !EndeEin && (bs_seen || ps_ezchn != '\'') ; psLiesn() )
   {
    if (strlen < STRLEN) /* String passt noch in Puffer etc. */
      estr[strlen++] = ps_ezchn;
    else if (!strf) /* Folgefehlerunterdrueckung */
     {
      psScanerror(serrSTL); /* zu lang */
      strf = TRUE;
     }
    bs_seen = !bs_seen && ps_ezchn == '\\';
   }  /* Ende String lesen */
  estr[strlen] = '\0';
  if (EndeEin )
   {
    psScanerror(serrSTO);
    return(0);
   }
  psLiesn(); /* abschliessendes ' ueberlesen  */
  psEnterhashtab(token,estr,specdef->kc,0L,specdef->ign,&ps_nextstr,
                 (int)TRUE,(int)FALSE,(int)FALSE);
  return(specdef->ign ? -1 : 1);
 } /* psCstrings */
#endif /* L_CCHARS */


#ifdef L_LINEDIRS
/* =================================================================== */
/* Line-Direktiven verarbeiten , wie sie vom C-Praeprozessor kommen    */
/* =================================================================== */
#ifdef __STDC__
void psLinedirs(void)
#else
void psLinedirs()
#endif
 {
  psLiesn();   /* '#' ueberlesen */
  while (!EndeEin && !isdigit(ps_ezchn) && ps_ezchn != '\r' && ps_ezchn != '\n')
    psLiesn();  /* Zeilennummer suchen */
  if (isdigit(ps_ezchn))
   { /* Zeilennummer vorhanden, auswerten und setzen */
#define dval(x) ( (int)(x) - (int)('0') )
    int line;
    line = dval(ps_ezchn); /* erste Ziffer auswerten    */
    for (psLiesn(); !EndeEin && isdigit(ps_ezchn); psLiesn() )
      line = line*10 + dval(ps_ezchn);
    ps_quellref.zeile = line - 1; /* abschliessendes Zeilenende beruecks. */
    while (!EndeEin && ps_ezchn != '"' && ps_ezchn != '\r' && ps_ezchn != '\n')
      psLiesn();  /* Dateinamen suchen */
    if (ps_ezchn == '"')
     { /* Dateiname vorhanden */
      int len;			/* aktuelle Laenge Dateiname	*/
      char fname[STRLEN+1];	/* Puffer fuer Dateinamen	*/

      for (psLiesn(),len = 0; len < STRLEN && ps_ezchn != '"'; 
           len++,psLiesn())
        fname[len] = ps_ezchn;
      fname[len] = '\0';
      if ((ps_quellref.fname = (char *)malloc(len+1)) == NULL)
        ps_quellref.fname = "?";
      else
        strcpy(ps_quellref.fname,fname);
     } /* Dateiname vorhanden */
   } /* Zeilennummer vorhanden */
  while (!EndeEin && ps_ezchn != '\r' && ps_ezchn != '\n')
    psLiesn(); /* bis Zeilenende lesen */
 }
#endif /* L_LINEDIRS */

