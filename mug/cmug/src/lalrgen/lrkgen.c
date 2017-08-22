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
/* LRKgen.c   :                                                           */
/* LR(k)-Parser-Generator                                                 */
/* Hauptmodul : Aufrufe                                                   */
/* Aenderung : 10.07.89, Option -w                                        */
/* Aenderung :  1.3.89 , Ausgabeunterdrueckung bei nil:                   */
/* Aenderung : 27.2.89 , Option -a                                        */
/* erstellt  : 23.1.89                                                    */
/* ********************************************************************** */
#ifdef __STDC__
#include <stddef.h>
#include <stdlib.h>
#endif
#include <stdio.h>         /* E/A-Definitionen                   */  
#include <ctype.h>         /* Deklarationen fuer char            */
#include "millisec.h"
#ifdef AMIGA
#include <time.h>          /* Deklarationen fuer Systemzeit      */
#else
#include <sys/types.h>    
#include <time.h>          /* Deklarationen fuer Systemzeit      */
#endif
#include <string.h>
#include "defs.h"          /* diverse unspezifische Definitionen */
#include "lrkgen.h"        /* Version ...                        */
#include "grammar.h"       /* Datenstrukturen der Grammatik      */
#include "lrkread.h"       /* Deklarationen Einleser             */
#include "lrkmat.h"        /* Deklarationen Generatormodul       */
#include "lrkaus.h"        /* Deklarationen Ausgabemodul         */


/*====================================================================== */
/* globale Variablen                                                      */
/*====================================================================== */
int generrors;                      /* Anzahl gefundener Fehler           */

/* ------------------------------------------------------- */
/* diverse Modul-globale Variablen                         */
/* ------------------------------------------------------- */
static Msecs start_zeit;           /* internes Zeitformat fuer Startzeit */
static char *internform_name;       /* Dateiname der Grammatikinternform  */
static char *tabellen_name;         /* Dateiname der generierten Tabelle  */
static char *klartext_name;         /* Dateiname der Klartext-Tabelle     */
static char *aktkonf_name;          /* Dateiname der Konflikt-Tabelle     */

/* ------------------------------------------------------- */
/* globale Variablen fuer Optionen                         */
/* ------------------------------------------------------- */
int  gargc       ;      /* argc-Argument von main()                     */
char **gargv     ;      /* argv-Argument von main()                     */
BOOL compress    ;      /* komprimieren ?                               */
BOOL force       ;      /* Ausgabe erzwingen ?                          */
BOOL stats       ;      /* Statistik ausgeben ?                         */
BOOL no_stderr   ;      /* keine Fehlermeldungen auf Bildschirm ?       */
int  max_lookahead;     /* maximale Laenge Lookahead                    */
char *errorfile_name;   /* Name der Fehlerdatei                         */
FILE *aktkonf_file;     /* Datei der Aktions-Konflikttabelle            */

/*====================================================================== */
/* Anfangsmeldung auf stdout ausgeben                                     */
/* Startzeit in start_zeit merken                                         */
/*====================================================================== */
#ifdef __STDC__
static void hello(Msecs *szeit)
                 /* Zeiger auf Variable, in der Startzeit abgelegt wird */
#else
static void hello(szeit)
 Msecs *szeit;   /* Zeiger auf Variable, in der Startzeit abgelegt wird */
#endif
 {
  time_t zeit;

  time(&zeit);                              /* Interne Uhrzeit abspeichern */
  printf("\nLALR(1)-Parser-Generator lrkgen Version %s - %s (U.Vollath)\n",
         VERSION,DATUM);
  printf("  Start   : %.20s\n",ctime(&zeit) );  /* Uhrzeit dekodiert ausgeben */
  *szeit = milliSecs();
 } /* hello */


/*====================================================================== */
/* Zwischenmeldung auf stdout ausgeben                                    */
/* Laufzeit Generierung ausgeben                                          */
/*====================================================================== */
#ifdef __STDC__
static void ausgabezeit(Msecs *szeit)
                 /* Zeiger auf Variable, in der Startzeit abgelegt wurde */
#else
static void ausgabezeit(szeit)
 Msecs *szeit;   /* Zeiger auf Variable, in der Startzeit abgelegt wurde */
#endif
 {
  time_t ausgzeit;
  Msecs  gmsecs;

  gmsecs = milliSecs() - *szeit;
  time(&ausgzeit);
  printf("  Ausgabe : %.20s , Generierung %d.%03.3d sec\n",
         ctime(&ausgzeit),
         (int)(gmsecs / 1000),(int)(gmsecs % 1000) ); 
     /* Uhrzeit dekod. ausgeben */
 } /* goodbye */

/*====================================================================== */
/* Endemeldung auf stdout ausgeben                                        */
/* gesamte Laufzeit ausgeben                                              */
/*====================================================================== */
#ifdef __STDC__
static void goodbye(Msecs *szeit)
                 /* Zeiger auf Variable, in der Startzeit abgelegt wurde */
#else
static void goodbye(szeit)
 Msecs *szeit;   /* Zeiger auf Variable, in der Startzeit abgelegt wurde */
#endif
 {
  time_t endzeit;
  Msecs  amsecs;

  amsecs = milliSecs() - *szeit;
  time(&endzeit);                              /* Interne Uhrzeit abspeichern */
  printf("  Ende    : %.20s , Laufzeit %d.%03.3d sec\n",
         ctime(&endzeit),
         (int)(amsecs / 1000),(int)(amsecs % 1000) ); 
 } /* goodbye */

/*====================================================================== */
/* Ausgabe der Aufrufsyntax des Programmes auf stdout                     */   
/*====================================================================== */
#ifdef __STDC__
static void aufruf(char *command)
                           /* erstes Kommandozeilenargument = Kommando */
#else
static void aufruf(command)
 char *command;            /* erstes Kommandozeilenargument = Kommando */
#endif
 {
  
  printf(
"Aufruf : %s [-a AK] [-c] [-e FM] [-f ] [-l k] [-s] [-w KT] Internform Tabelle\n",
          command);
  printf("  Internform : Eingabedatei, die Grammatikinterform enthaelt\n");
  printf("  Tabelle    : Ausgabedatei, C-Quelle fuer Parsertabelle\n");
  printf("  Optionen\n");
  printf("    -a AK : Aktionskonflikte in Datei AK ausgeben, ohne Meldungen\n");
  printf("    -c    : Parsertabelle komprimieren\n");
  printf("    -e FM : Fehlermeldungen zusaetzlich in Datei FM ausgeben\n");
  printf("    -e -  : Fehlermeldungen nicht auf Bildschirm ausgeben\n");
  printf("    -f    : Ausgaben auch bei Generierungsfehlern erzwingen\n");
  printf("    -l k  : maximalen Lookahead k verwenden (Standard : -l 1 )\n");
  printf("    -s    : Statistik der Generierung ausgeben\n");
  printf("    -w KT : Tabelle in Klartext in Datei KT ausgeben\n");

 } /* aufruf */

/*====================================================================== */
/* Initialisierung der Optionen durch ihre Standardwerte (defaults)       */
/*====================================================================== */
#ifdef __STDC__
static void initOpts(void)
{
#else
static void initOpts()
 {
#endif
  compress       = FALSE;             /* nicht Komprimieren               */
  force          = FALSE;             /* Ausgabe nur, wenn fehlerfrei     */
  stats          = FALSE;             /* keine Statistik ausgeben         */
  max_lookahead  = 1;                 /* Standardwert fuer max. Lookahead */
  errorfile_name = NULL;              /* Meldungen nur nach stdout        */
  aktkonf_name   = NULL;              /* Aktionskonflikte als Fehler      */
  no_stderr      = FALSE;             /* Fehlermeldungen auf Bildschirm   */
  klartext_name  = NULL;              /* keine Klartext-Tabelle           */
 } /* initOpts */

/*====================================================================== */
/* Verarbeiten der Kommandozeilenargumente                                */
/*   Einstellen der Optionen                                              */
/*   Bestimmung von Ein- und Ausgabedateien                               */
/*   evtl. Fehlermeldungen auf stdout                                     */ 
/*====================================================================== */
#ifdef __STDC__
static BOOL getArgs(int argc, char **argv)
                       /* Anzahl Kommandozeilenargumente       */
                       /*  Kommandozeilenargumente             */
#else
static BOOL getArgs(argc,argv)
 int  argc;            /* Anzahl Kommandozeilenargumente       */
 char *argv[];         /*  Kommandozeilenargumente             */
#endif
 {
  int  argnr;          /* Index des aktuell bearbeiteten Argumentes */
  int  anz_dat;        /* Anzahl der angegebenen Dateien            */
  char opt;            /* Buchstabe der bearbeiteten Option         */

  gargc = argc;        /* Anzahl global zur Verfuegung stellen      */
  gargv = argv;        /* Werte global zur Verfuegung stellen       */
  anz_dat = 0;         /* noch keine Dateien angegeben              */
  for (argnr = 1; argnr <argc; argnr++)
   {
    if (*argv[argnr] != '\0') /* kein Leerargument */
     { 
      if (*argv[argnr] == '-') 
       { /* Option folgt   */
        opt = *(argv[argnr]+1);       /* Optionsbuchstabe bestimmen    */
        if (opt == '\0') /* Optionsbuchstabe vergessen    */
         {
          printf("\n*** Option nach - erwartet ***\n\n");
          return(FALSE);              /* mit Fehler beenden */ 
         } /* Optionsbuchstabe vergessen */
        if (*(argv[argnr]+2) != '\0') /* Option nicht nur ein Buchstabe    */
         {
          printf("\n*** Option darf nur ein Buchstabe sein ***\n\n");
          return(FALSE);              /* mit Fehler beenden */ 
         } /* mehrere Zeichen */
        switch (opt)
         { /* welche Option ? */
          case 'A' :   /* Datei fuer Aktionskonflikte angegeben   */
          case 'a' :
                     if (++argnr >= argc)   /* Dateiangabe fehlt */
                      {
                       printf("\n*** Konfliktdateiangabe fehlt ***\n\n");
                       return(FALSE);
                      }
                     else  /* Zeiger auf Dateiangabe kopieren */
                       aktkonf_name = argv[argnr];
                     break;
          case 'C' :   /* Komprimieren            */
          case 'c' :
                     printf("c-Option :Komprimierung nicht implementiert\n");
                     compress = TRUE; 
                     break;
          case 'E' :   /* Fehlerdatei angegeben   */
          case 'e' :
                     if (++argnr >= argc)   /* Dateiangabe fehlt */
                      {
                       printf("\n*** Fehlerdateiangabe fehlt ***\n\n");
                       return(FALSE);
                      }
                     else if (strcmp(argv[argnr],"-") == 0)
                       no_stderr = TRUE; /* keine Fehler-Ausgabe */
                     else  /* Zeiger auf Dateiangabe kopieren */
                       errorfile_name = argv[argnr];
                     break;
          case 'F' :   /* Ausgabe erzwingen           */
          case 'f' :
                     force = TRUE; 
                     break;
          case 'L' :   /* Lookahead angegeben     */
          case 'l' :
                     if (++argnr >= argc)   /* Lookaheadangabe fehlt */
                      {
                       printf("\n*** Lookaheadangabe fehlt ***\n\n");
                       return(FALSE);
                      }
                     else  /* Lookahead einlesen  */
                      {
                       sscanf(argv[argnr],"%d",&max_lookahead);
                       if (max_lookahead < 0) 
                        { /* Lookahead ungueltig */ 
                         printf("\n*** Lookaheadangabe %d ungueltig ***\n\n",
                                max_lookahead);
                         return(FALSE);
                        } /* Lookahead ungueltig */ 
#ifndef NLOOKAHEAD
                       if (max_lookahead > 1) 
                        { /* Lookahead zu gross */ 
                         printf(
                           "\n*** Lookahead > 1 nicht implementiert ***\n\n");
                         return(FALSE);
                        } /* Lookahead ungueltig */ 
#endif
                      }   /* Lookahead einlesen  */
                     break;
          case 'S' :   /* Statistik ausgeben      */
          case 's' :
                     stats = TRUE;
                     break;
          case 'W' :   /* Datei fuer Klartext angegeben   */
          case 'w' :
                     if (++argnr >= argc)   /* Dateiangabe fehlt */
                      {
                       printf("\n*** Klartextdateiangabe fehlt ***\n\n");
                       return(FALSE);
                      }
                     else  /* Zeiger auf Dateiangabe kopieren */
                       klartext_name = argv[argnr];
                     break;
          default :    /* Option nicht definiert */
                     printf("\n*** unbekannte Option -%c ***\n\n",opt);
                     return(FALSE);           /* mit Fehler beenden */ 
         } /* switch */
       } /* Option  */    
      else /* keine Option , also Ein- oder Ausgabedatei  */
       {
        anz_dat++;        /* Anzahl der bisher angegebenen Dateien */
        if (anz_dat == 1) /* erste Dateiangabe, Eingabe            */
          internform_name = argv[argnr];
        else if (anz_dat == 2) /* zweite Dateiangabe, Ausgabe      */
          tabellen_name = argv[argnr];
        else  /* anz_dat > 2 */
         {
          printf("\n*** zu viele Dateien angegeben ***\n\n");
          return(FALSE);          /* mit Fehler beenden */ 
         }
       } /* keine Option , also Ein- oder Ausgabedatei  */
     } /* kein Leerargument */
   } /* for */
  if (anz_dat < 2) /* nicht alle Dateien angegeben */
   {
    printf("\n*** zu wenig Dateien angegeben ***\n\n");
    return(FALSE);          /* mit Fehler beenden */ 
   }
  return(TRUE);      /* erfolgreich beendet  */
 } /* getArgs */


/*====================================================================== */
/* Ausgabe der Statistikinformationen auf stdout                          */
/*====================================================================== */
#ifdef __STDC__
static void genstats(void)
{
#else
static void genstats()
 {
#endif
 } /* genstats */

/*====================================================================== */
/* Aufrufmodul                                                            */
/*   Verarbeitung der Kommandozeilenargumente                             */
/*   Aufruf des eigentlichen Generators                                   */
/*====================================================================== */
#ifdef __STDC__
int main(int argc, char **argv)
                       /* Anzahl Kommandozeilenargumente       */
                       /*  Kommandozeilenargumente             */
#else
int main(argc,argv)
 int  argc;            /* Anzahl Kommandozeilenargumente       */
 char **argv;          /*  Kommandozeilenargumente             */
#endif
 {

  hello(&start_zeit);   /* Prompt fuer Programmstart, Startzeit merken       */
  initOpts();           /* Optionen initialisieren (defaults)                */
  if ( ! getArgs(argc,argv) )                /* Kommandozeile verarbeiten    */
   { /* Fehler in der Kommandozeile */
    aufruf(argv[0]);                         /* richtigen Aufruf zeigen      */
    exit(RETURNSTAT_FAIL);                   /* Programmlauf abbrechen       */
   }

  if ( ! readInternform(internform_name) )   /* Grammatikinternform einlesen */
    exit(RETURNSTAT_ERROR);                  /* nach Fehler beenden          */

  if ( aktkonf_name != NULL )                /* Aktionskonflikte separat     */
   {
    if ( (aktkonf_file = fopen(aktkonf_name,"w") ) == NULL)
     {
      fprintf(stderr,"Aktionskonfliktdatei %s kann nicht geoeffnet werden\n",
                      aktkonf_name);
      exit(RETURNSTAT_FAIL);                 /* Programmlauf abbrechen       */
     }
    else
     {
      int i;
      time_t tm;

      fputs("# Aktionskonflikte Generierung ",aktkonf_file);
      tm = time((time_t *)NULL);
      fputs(ctime(&tm),aktkonf_file);
      fputs("# ",aktkonf_file);
      for (i = 0; i < argc; i++)
       {
        fputs(argv[i],aktkonf_file);
        putc(' ',aktkonf_file);
       }
      fputs("\n# Aufbau : Prod Item_in_prod Item_in_grm Nont_nr Nont_name\n",
             aktkonf_file);
     }
   }
  else
    aktkonf_file = NULL;

  if ( ! LRKgen() &&                         /* Uebergangstabelle generieren */
       ! force)
    exit(RETURNSTAT_ERROR);                  /* nach Fehler beenden          */
      
  ausgabezeit(&start_zeit);                  /* Zeit Generierungsende       */
  if (klartext_name != NULL)
    if ( ! LRKmat_ausgabe1(klartext_name) )  /* Klartexttabelle ausgeben     */
      exit(RETURNSTAT_ERROR);                /* nach Fehler beenden          */
  if (strcmp(tabellen_name,"nil:"))          /* falls Ausgabe gewuenscht     */
   {
    if ( ! LRKmat_ausgabe(tabellen_name) )   /* Uebergangstabelle ausgeben   */
      exit(RETURNSTAT_ERROR);                /* nach Fehler beenden          */
   }
  if (stats)                                 /* -s Option                    */
    genstats();                              /* Statistik auf stdout         */

  goodbye(&start_zeit);                      /* Endemeldung                  */
  return(0);
 }  /* main */ 

