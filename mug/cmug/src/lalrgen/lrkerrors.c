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
/* LRKerrors.c   :                                                        */
/* LR(k)-Parser-Generator                                                 */
/* Modul : Fehlermeldungen                                                */
/* Aenderung : 02.07.89, weitere Abpruefungen (term., benutzt )           */
/* Aenderung : 01.07.89, Fehlermeldungen kompakter, Unterstuetzung von -e */
/* erstellt  : 23.1.89                                                    */
/* ********************************************************************** */
#ifdef __STDC__
#include <stddef.h>
#include <stdlib.h>
#endif
#include <stdio.h>         /* E/A-Definitionen                   */  
#include <time.h>          /* Deklarationen fuer Systemzeit      */

#include "defs.h"          /* diverse unspezifische Definitionen */
#include "listen.h"
#include "grammar.h"      
#include "lrkdec.h"        /* Deklarationen Dekoder              */
#include "lrkmat.h"        /* Deklarationen Matrix               */
#include "lrkerrors.h"     /* Deklarationen Fehlermodul          */

/* --------------------------------------- */
/* globale Options-Variablen               */
/* --------------------------------------- */
extern int  gargc        ;     /* argc-Argument von main()               */
extern char **gargv      ;     /* argv-Argument von main()               */
extern char *errorfile_name;   /* Name der Fehlerdatei                   */
extern BOOL no_stderr    ;     /* keine Fehlermeldungen auf Bildschirm ? */
extern FILE *aktkonf_file;     /* Datei fuer Aktionskonflikte            */

static FILE *errorfile = NULL; /* Fehlerdatei                            */ 

extern Grammar g;              /* bearbeitete Grammatik                  */
/* ------------------------------------------ */
/* Zaehler fuer die Fehlermeldungen           */
/* ------------------------------------------ */
static int anz_konflikte     = 0;
static int anz_aktkonflikte  = 0;
static int anz_warnungen     = 0;

/* ------------------------------------------ */
/* Datentyp fuer Konflikttabelle              */
/* ------------------------------------------ */
/* -------------------------------------------------------------------- */
/* Ueblis : Liste von gleichen Konflikten mit unterschiedlichen         */
/*          Terminalzeichen in einem Zustand                            */
/* -------------------------------------------------------------------- */
typedef struct UeblisR *Ueblis;
typedef struct UeblisR {
                       LISTENFELDER(Ueblis)  
                       Ueberg ueb;   /* erster Uebergang des Konfliktes */
                      } UeblisRec;
#define UEBLISUEB(u) (u).ueb
                                                                  
/* -------------------------------------------------------------------- */
/* Kvork : Vorkommen eines Konfliktes. kueb zeigt auf den ersten        */
/*         Uebergang zu einem Zustand, in dem der Konflikt auftritt     */
/* -------------------------------------------------------------------- */
typedef struct KvorkR *Kvork;
typedef struct KvorkR { /* Vorkommen eines Konfliktes */
                      LISTENFELDER(Kvork)                 
                      Ueblis kueb;
                     } KvorkRec;   
#define KVORKUEB(k) (k).kueb

/* -------------------------------------------------------------------- */
/* Konflikt : Liste von Konflikten, die alle die gleichen Uebergaenge   */
/*            enthalten.                                                */
/*            Der erste Eintrag ist dabei der Repraesentant der Klasse  */
/*            gleicher Konflikte                                        */
/*            Die Liste der Uebergaenge uebs zeigt auf den ersten       */
/*            Uebergang mit diesem Konflikt, der zu einem Zustand       */
/*            existiert, weitere koennen folgen                         */
/*            jeder Konflikt wird terminiert durch einen Uebergang mit  */
/*            einem anderen Terminalzeichen bzw. das Listenende         */
/* -------------------------------------------------------------------- */

typedef struct KonfR *Konflikt;
typedef struct KonfR { /* komplette Beschreibung eines Konfliktes */
                      LISTENFELDER(Konflikt)
                      Kvork klis;  
                     } KonfRec;   
#define KONFLIS(k) (k).klis                                                                          

static Konflikt konflikte = NULL;  /* alle Konflikte dieser Grammatik   */

/* ------------------------------------------ */
/* hier benoetigte Makros                     */
/* ------------------------------------------ */
/* Ausgabe in Datei gewuenscht ? */
#define ERROR_ON_FILE (errorfile_name != NULL)
/* ggf. Fehlerdatei oeffnen      */
#define OPENERR if (errorfile == NULL) openErr();                         
#define SYMS_IN_ZEILE 4

#define IFSTDERR(stmts) if (! no_stderr) stmts 
#define IFFILEERR(stmts) if (ERROR_ON_FILE) {OPENERR;stmts}

#define ABBRUCH mAbort()
/* ------------------------------------------------------------------------ */
/* Ueblis = list of UeblisRec                                               */
/* ------------------------------------------------------------------------ */
/* Setzen der Parameter */
#define BASISTYP UeblisRec
#define LISTTYP  Ueblis
#define LISTTYPSTR  "Ueblis"
#define FREILIS  fl_ueblis
#define INITNAME initUeblis
#define EINTRNAME eintragUeblis
/* #define MERGENAME mergeUeblis */
/* #define FREELISNAME freelisUeblis */
/* Kriterium : unsortiert, immer neu */
#define VERGLEICHE(k1,k2) (-1)
#define VERGLNAME verglUeblis
/* kein Abgleich noetig */
#define KOPIERE(z,q)   *(z) = *(q);
#define KOPNAME kopiereUeblis
#include "list_epd.h"          /* Aufruf der Datenstruktur */


/* ------------------------------------------------------------------------ */
/* Kvork = list of KvorkRec                                                 */
/* ------------------------------------------------------------------------ */
/* Setzen der Parameter */
#define BASISTYP KvorkRec
#define LISTTYP  Kvork
#define LISTTYPSTR  "Kvork"
#define FREILIS  fl_kvork
#define INITNAME initKvork
#define EINTRNAME eintragKvork
/* #define MERGENAME mergeKvork */
/* #define FREELISNAME freelisKvork */
/* Kriterium : Zustandsnummern der Uebergaenge */
#define VERGLEICHE(k1,k2)  (ZUSTNR(*UEBVON(*UEBLISUEB(*KVORKUEB(*k1)))) - \
 ZUSTNR(*UEBVON(*UEBLISUEB(*KVORKUEB(*k2)))) ) 
#define VERGLNAME verglKvork
#define ABGLEICH(z,q) eintragUeblis(&KVORKUEB(*z),KVORKUEB(*q) )
#define ABGLNAME  abglKvork
#define KOPIERE(z,q)   *(z) = *(q); \
  KVORKUEB(*z) = NULL;\
  eintragUeblis(&KVORKUEB(*z),KVORKUEB(*q) )
#define KOPNAME kopiereKvork
#include "list_epd.h"          /* Aufruf der Datenstruktur */

/* ------------------------------------------------------------------------ */
/* Konflikt = list of KonfRec                                               */
/* ------------------------------------------------------------------------ */
/* Setzen der Parameter */
#define BASISTYP KonfRec
#define LISTTYP  Konflikt
#define LISTTYPSTR  "Konflikt"
#define FREILIS  fl_konflikt
#define INITNAME initKonflikt
#define EINTRNAME eintragKonflikt
/* #define MERGENAME mergeKonflikt */
/* #define FREELISNAME freelisKonflikt */
/* Kriterium : Items der Positionen */
/* #define VERGLEICHE(k1,k2) */
int verglKonflikt();
#define VERGLNAME verglKonflikt
#define ABGLEICH(z,q) eintragKvork(&KONFLIS(*z),KONFLIS(*q))
#define ABGLNAME abglKonflikt
/* #define KOPIERE(z,q)   */
void kopiereKonflikt();
#define KOPNAME kopiereKonflikt
#include "list_epd.h"          /* Aufruf der Datenstruktur */

/* ====================================================================== */
/* Oeffnen der Fehlerdatei                                                */
/* ====================================================================== */
static void openErr()
 {
  int  i;
  long ausgzeit;

  if ( (errorfile = fopen(errorfile_name,"w")) == NULL)
   {
    fprintf(stderr,"Fehlerdatei %s kann nicht geoeffnet werden\n",errorfile_name);
    exit(RETURNSTAT_FAIL);
   }
  time(&ausgzeit);                             /* Interne Uhrzeit abspeichern */
  fprintf(errorfile,"Fehlermeldungen Generierung %.20s, Kommando :\n",
         ctime(&ausgzeit) );   /* Uhrzeit dekod. ausgeben */

  for (i = 0; i<gargc; i++)
   {
    fputs(gargv[i],errorfile);
    putc(' ',errorfile);
   }
  fputs("\n---------------------------\n",errorfile); 
 } /* openErr */


/* ====================================================================== */
/* Dekodieren eines Zustandes am Anfang der Meldungen zu diesem Zustand   */
/* ====================================================================== */
static void showZust(ef,zust)
 FILE *ef;       /* Datei, in die Ausgabe erfolgt */
 Zustand zust;   /* anzuzeigender Zustand         */
 {
  register Position pos;       /* eine Position des Zustandes */

  fprintf(ef," im Zustand %ld :\n",
     zust?(long)ZUSTNR(*zust):99999L );
  if (zust)
    FOREACHPOS(*zust,pos)
     {
      fputs("  --> ",ef);
      fdecItem(ef,POSITEM(*pos));
      fputc('\n',ef);
     }
 } /* showZust */

/* ====================================================================== */
/* Ausgabe einer allgemeinen Fehlermeldung, nur Format                    */
/* ====================================================================== */
void Error0(frm)
 char *frm;   /* Format der Meldung */
 {
  if (! no_stderr)         /* Ausgabe auf Bildschirm */
    fputs(frm,stderr);     /* Meldung ausgeben       */
  if (ERROR_ON_FILE)
   {
    OPENERR;
    fputs(frm,errorfile);  /* Meldung ausgeben */
   }
 } /* Error0 */

/* ====================================================================== */
/* Ausgabe einer allgemeinen Fehlermeldung, Format + 1 String             */
/* ====================================================================== */
void Error1(frm,strg)
 char *frm;   /* Format der Meldung   */
 char *strg;  /* zusaetzlicher String */
 {
  if (! no_stderr)                 /* Ausgabe auf Bildschirm */
    fprintf(stderr,frm,strg);      /* Meldung ausgeben       */
  if (ERROR_ON_FILE)
   {
    OPENERR;
    fprintf(errorfile,frm,strg);   /* Meldung ausgeben       */
   }
 } /* Error1 */

/* ====================================================================== */
/* Fehlermeldung : spontane Uebergaenge noetig bei Lookahead 0            */
/* Ausgabe in Datei                                                       */
/* ====================================================================== */
static void fepsError(ef,zust)
 FILE *ef;       /* Datei, in die Ausgabe erfolgt         */
 Zustand zust;   /* Zustand, in dem der Fehler auftritt   */
 {
  register Ueberg ueb;         /* auszugebender Uebergang               */
  
  fputs("**** spontane Uebergaenge bei Lookahead 0",ef);
  showZust(ef,zust);
  fputs("Uebergaenge :\n  ",ef);
  for (ueb = ZUSTEPSUEB(*zust);ueb != NULL;ueb = (Ueberg)LISTNEXT(*ueb) )
    fdecUeb(ef,ueb);
 } /* epsError */

/* ====================================================================== */
/* Fehlermeldung : spontane Uebergaenge noetig bei Lookahead 0            */
/* ====================================================================== */
void epsError(zust)
 Zustand zust;                 /* Zustand, in dem der Fehler auftritt   */
 {
  anz_konflikte++;
  if (! no_stderr)             /* Ausgabe auf Bildschirm                */
    fepsError(stderr,zust);    /* Meldung auf Konsole                   */
  if (ERROR_ON_FILE)
   {
    OPENERR;
    fepsError(errorfile,zust); /* Meldung in Fehlerdatei                */
   }  
 } /* epsError */

/* ====================================================================== */
/* Vergleichsfunktion fuer Konflikte                                      */
/* Konflikte sind gleich, wenn die Uebergaenge des Repraesentanten gleich */
/* sind (modulo Symbol des Uebergangs)                                    */
/* bei Ungleichheit wird immer -1 abgeliefert, so dass die Liste          */
/* unsortiert gefuehrt wird                                               */
/* ====================================================================== */
#ifdef __STDC__
int verglKonflikt(Konflikt lkonf,Konflikt nkonf)
#else
int verglKonflikt (lkonf,nkonf)
 Konflikt lkonf;   /* Konflikt, der bereits in der Liste ist */
 Konflikt nkonf;   /* neuer einzutragender Konflikt          */
#endif
 {                 
  Ueberg lueb;     /* Repraesentant in lkonf                 */
  Ueberg nueb;     /* neue Uebergangsliste                   */
  Ueberg nnext;                                    
  Ueberg lnext;
  Symb   nsym;           
  Symb   lsym;

  CHECKPT(lkonf);
  CHECKPT(KONFLIS(*lkonf));
  CHECKPT(KVORKUEB(*KONFLIS(*lkonf)));
  CHECKPT(UEBLISUEB(*KVORKUEB(*KONFLIS(*lkonf))));
  CHECKPT(nkonf);
  CHECKPT(KONFLIS(*nkonf));
  CHECKPT(KVORKUEB(*KONFLIS(*nkonf)));
  CHECKPT(UEBLISUEB(*KVORKUEB(*KONFLIS(*nkonf))));
                                                               
  for(lueb = UEBLISUEB(*KVORKUEB(*KONFLIS(*lkonf))),
      nueb = UEBLISUEB(*KVORKUEB(*KONFLIS(*nkonf))),
      lsym = UEBSYM(*lueb),
      nsym = UEBSYM(*nueb) ; ;
      lueb = lnext,
      nueb = nnext )
   {          
    if ( (nnext = (Ueberg)LISTNEXT(*nueb) ) == NULL ||
         UEBSYM(*nnext) != nsym) /* dieser Konflikt zu Ende */
     {
      if ( (lnext = (Ueberg)LISTNEXT(*lueb) ) == NULL ||
           UEBSYM(*lnext) != lsym) /* Repraesentant auch zu Ende */
        return(0);
      else /* Konflikte ungleich */
        return(-1);
     }
    else /* Konflikt geht weiter */
     {
      if ( (lnext = (Ueberg)LISTNEXT(*lueb) ) == NULL ||
           UEBSYM(*lnext) != lsym) /* aber Repraesentant zu Ende */
        return(-1);  /* dann ungleich */
      else
       {
        Uebart art;

        if ((art = UEBART(*nueb)) != UEBART(*lueb) ||
             art == SHIFT && UEBSZUST(*nueb) != UEBSZUST(*lueb) ||
             art == SPONTRED && UEBRITEM(*nueb) != UEBRITEM(*lueb) )
          return(-1);  /* Information ungleich */
       }
     }     
   } /* for */
 } /* verglKonfikt */

/* ====================================================================== */
/* Kopierfunktion fuer Konflikte                                          */
/* Der Repraesentant fuer einen neuen Konflikt wird aufgebaut             */
/* ====================================================================== */
#ifdef __STDC__
void kopiereKonflikt(Konflikt zkonf,Konflikt nkonf)
#else
void kopiereKonflikt (zkonf,nkonf)
 Konflikt zkonf;   /* neuer Konflikt                         */
 Konflikt nkonf;   /* einzutragende Konfliktinformation      */
#endif
 {                                                     
  KvorkRec  vork;
  UeblisRec ueblis;                     
            
  UEBLISUEB(ueblis) = UEBLISUEB(*KVORKUEB(*KONFLIS(*nkonf)));
  KVORKUEB(vork) = NULL;                   /* Liste leer       */
  eintragUeblis(&KVORKUEB(vork),&ueblis);  /* einziger Eintrag */
  KONFLIS(*zkonf) = NULL;                  /* Liste leer       */
  eintragKvork(&KONFLIS(*zkonf),&vork);   /* einziger Eintrag */
 } /* kopiereKonflikt */

/* ====================================================================== */
/* Ausgabe eines Uebergangs innerhalb eines Konfliktes                    */
/* ====================================================================== */
void konfUeb(ueb)
 Ueberg ueb;
 {
 /* ----------------------------------------- */
 /* Einelementige Konfliktliste zusammenbauen */
 /* und in Konflikttabelle eintragen          */
 /* ----------------------------------------- */
  KvorkRec  kvork;
  KonfRec   krec;  
  UeblisRec uebrec;

  UEBLISUEB(uebrec) = ueb;
  KVORKUEB(kvork)   = &uebrec;             
  KONFLIS(krec)     = &kvork;
  eintragKonflikt(&konflikte,&krec);
 } /* konfUeb */

/* ====================================================================== */
/* Ausgabe des Zustandes am Anfang von Konflikten                         */
/* ====================================================================== */
void konfStart(zust)
 Zustand zust;   /* Zustand, in dem Konflikte auftreten */
 {
 /* nicht mehr noetig, Gesamttabelle  */
 } /* konfStart */

/* ====================================================================== */
/* mault, wenn aus einem Nonterminal keine terminale Zeichenreihe         */
/* herleitbar ist                                                         */
/* ====================================================================== */
#ifdef __STDC__
void mauleTerm(Nont n)
#else
void mauleTerm(n)
 Nont n;       /* Nonterminal, dass sich daneben benimmt */
#endif
 {
  anz_warnungen++;
  Error1("**** keine terminale Zeichenreihe herleitbar aus %s\n",decSym(n));
 } /* mauleTerm */

/* ====================================================================== */
/* mault, wenn ein Nonterminal nicht benoetigt wird                       */
/* ====================================================================== */
#ifdef __STDC__
void mauleBenutzt(Nont n)
#else
void mauleBenutzt(n)
 Nont n;       /* Nonterminal, dass keine Lust zum Arbeiten hat */
#endif
 {
  anz_warnungen++;
  Error1("**** Nonterminal %s wird nicht benutzt\n",decSym(n));
 } /* mauleBenutzt */

/* ====================================================================== */
/* mault, wenn eine Produktion nicht reduziert wird                       */
/* ====================================================================== */
#ifdef __STDC__
void mauleReduce(Prod p)
#else
void mauleReduce(p)
 Prod p;       /* Produktion, die nicht reduziert wird */
#endif
 {
  if (NONTSTAT(ITEMSYM(LHS(p)) ) & NS_BENUTZT )
   { /* sonst Meldung trivial */
    anz_warnungen++;
    Error0("**** Produktion wird nie reduziert :\n");
    if (! no_stderr)                /* Ausgabe auf Bildschirm */
     {
      fdecItem(stderr,LHS(p));      /* Produktion ausgeben    */
      putc('\n',stderr);
     }
    if (ERROR_ON_FILE)
     {
      OPENERR;
      fdecItem(errorfile,LHS(p));   /* Produktion ausgeben    */
      putc('\n',errorfile);
     }
   }
 } /* mauleReduce */

/* ====================================================================== */
/* Fehlermeldung und Programmabbruch bei unzureichendem Arbeitsspeicher   */
/* ====================================================================== */
void mAbort()
 {
  fprintf(stderr,"Arbeitsspeicher voll, Abbruch !\n");
  exit(RETURNSTAT_FAIL);
 } /* mabort */

/* ====================================================================== */
/* Prueft Uebergang auf reine Aktionskonflikte                            */
/* Rueckgabe TRUE, falls ausschliesslich Aktions-Konflikte vorhanden      */
/* ====================================================================== */
#ifdef __STDC__
BOOL aktKonflikte(Ueberg ueb)
#else
BOOL aktKonflikte(ueb)
 Ueberg  ueb;    /* erster Uebergang des Konfliktes           */
#endif
 {
  Symb    uebsym;
  Ueberg  ende;
  BOOL    nonakt;    /* schon anderen Konflikt gefunden ? */

  uebsym = UEBSYM(*ueb);
  nonakt = FALSE;
  /* ------------------------------------------- */
  /* feststellen, ob nur Aktionskonflikte        */
  /* ------------------------------------------- */
  for (ende = ueb;ende != NULL && UEBSYM(*ende) == uebsym; 
       ende = (Ueberg)LISTNEXT(*ende) )
   {
    Nont n;

    if (UEBART(*ende) == SHIFT || 
        (n = ITEMSYM(lhsItem(UEBRITEM(*ende))),! ISACTION(n)) )
      if (nonakt)  /* mehrere nicht-Aktions-Konflikte */
        return(FALSE);   /* dann explizit melden */
      else
        nonakt = TRUE;
   }
  return(TRUE); /* ausschliesslich durch Aktionen */
 } /* aktKonflikte */

/* ======================================================= */
/* Ausgabe eines Aktionskonfliktes in die Konfliktdatei af */
/* ======================================================= */
#ifdef __STDC__
void outAktkonf(FILE *af,Ueberg ueb)
#else
void outAktkonf(af,ueb)
 FILE *af;
 Ueberg ueb;
#endif
 {
  register Ueberg ende;
  Symb     uebsym;
  int      vorhanden;

  vorhanden = FALSE;
  uebsym = UEBSYM(*ueb);
  for (ende = ueb;ende != NULL && UEBSYM(*ende) == uebsym; 
       ende = (Ueberg)LISTNEXT(*ende) )
   {
    if (UEBART(*ende) != SHIFT)
     {
      Nont n;
      Item lhs;               /* linke Seite bei Reduktion         */

      lhs = lhsItem(UEBRITEM(*ende)) ;
      n = ITEMSYM(lhs);
      if (ISACTION(n)) 
       {
        Ueberg fueb;  /* Folgeuebergang */
        Item   item;
        Position pos;

        fueb = sucheUeb(UEBVON(*ende),n);
        CHECKPT(fueb);
        CHECKBED(UEBART(*fueb) == SHIFT);
        FOREACHPOS(*UEBSZUST(*fueb),pos)
         {
          item = POSITEM(*pos);
          if (!ITEMGEM(item))  /* neuer Konflikt */
           {
            vorhanden = TRUE;
            ITEMGEM(item) = TRUE;
            fprintf(af,"%ld %ld %ld %ld %s\n",
                  (long)prodNr(item),(long)(item-lhsItem(item)),
                  (long)item,n,decSym(n) );
           }
         } /* FOREACHPOS */
       } /* ISACTION */
     } /* UEBART != SHIFT */
   } /* for */
  if (vorhanden)
   {
    anz_aktkonflikte++;
    fputs("#\n",af);
   }
 } /* outAktkonf */

/* ======================================================== */
/* Ausgabe der Tabelle aller Konflikte                      */
/* Rueckgabe : Gesamtzahl aller Konflikte (ohne Warnungen)  */
/* ======================================================== */
int alleKonflikte()
 {
  Konflikt konf;
  Kvork    kvork;
  Ueblis   ueblis;
  Ueberg   ueb;

  for (konf = konflikte; konf != NULL;
       konf = (Konflikt)LISTNEXT(*konf))
   {
    Symb sym;

    ueb = UEBLISUEB(*KVORKUEB(*KONFLIS(*konf)));
    if (aktkonf_file != NULL && aktKonflikte(ueb) )
     {
      outAktkonf(aktkonf_file,ueb);
      continue;
     }
    Error0("*** Konflikt\n");
    anz_konflikte++;
    /* ----------------------------------- */
    /* Uebergaenge des Konfliktes ausgeben */
    /* ----------------------------------- */
    for (sym = UEBSYM(*ueb) ; 
         ueb != NULL && UEBSYM(*ueb) == sym;
         ueb = (Ueberg)LISTNEXT(*ueb) )
     {
      IFSTDERR(fdecUebinf(stderr,ueb);)
      IFFILEERR(fdecUebinf(errorfile,ueb);)
     }
    for (kvork = KONFLIS(*konf); kvork != NULL;
         kvork = (Kvork)LISTNEXT(*kvork) )
    {
     int i;    /* zaehlt Ausgaben im Zustand */

     IFSTDERR(showZust(stderr,UEBVON(*UEBLISUEB(*KVORKUEB(*kvork))));)
     IFFILEERR(showZust(errorfile,UEBVON(*UEBLISUEB(*KVORKUEB(*kvork))));)
     i = -1;  /* noch keine Ausgaben */
     /* -------------------------------- */
     /* alle Vorkommen in diesem Zustand */
     /* -------------------------------- */
     for (ueblis = KVORKUEB(*kvork); ueblis != NULL;
          ueblis = (Ueblis)LISTNEXT(*ueblis))
      {
       if (i == -1)  /* erste Ausgabe         */
        {
         Error0(" mit : ");
         i = 0;
        }
       else if (i==0)
         Error0("       ");
       IFSTDERR
       ({
         fputs(decSym(UEBSYM(*UEBLISUEB(*ueblis))),stderr);
         fputc(' ',stderr);
       })
       IFFILEERR
       ({
         fputs(decSym(UEBSYM(*UEBLISUEB(*ueblis))),errorfile);
         fputc(' ',errorfile);
       })
       if (i++ >= SYMS_IN_ZEILE)
        {
         IFSTDERR(fputc('\n',stderr);)
         IFFILEERR(fputc('\n',errorfile);)
         i = 0;
        }
      } /* for(ueblis...) */
     if (i>0) Error0("\n");
    } /* for(kvork...) */
   }  /* for(konf...) */
  if (anz_konflikte+anz_aktkonflikte+anz_warnungen)
   {
    Error0("**** insgesamt:\n");
    if (anz_konflikte)
     {
      if (anz_konflikte == 1)
        Error0("  1 Konflikt\n");
      else
       {
        IFSTDERR(fprintf(stderr,"  %d Konflikte\n",anz_konflikte);)
        IFFILEERR(fprintf(errorfile,"  %d Konflikte\n",anz_konflikte);)
       }
     } /* anz_konflikte */
    if (anz_aktkonflikte)
     {
      if (anz_aktkonflikte == 1)
        Error0("  1 Aktionskonflikt\n");
      else
       {
        IFSTDERR(fprintf(stderr,"  %d Aktionskonflikte\n",
                 anz_aktkonflikte);)
        IFFILEERR(fprintf(errorfile,"  %d Aktionskonflikte\n",
                  anz_aktkonflikte);)
       }
     } /* anz_aktkonflikte */
    if (anz_warnungen)
     {
      if (anz_warnungen == 1)
        Error0("  1 Warnung\n");
      else
       {
        IFSTDERR(fprintf(stderr,"  %d Warnungen\n",anz_warnungen);)
        IFFILEERR(fprintf(errorfile,"  %d Warnungen\n",anz_warnungen);)
       }
     } /* anz_warnungen */
   } /* if */
  return(anz_konflikte+anz_aktkonflikte);
 } /* alleKonflikte */

