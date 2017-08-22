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
/* checks.c :                                                             */
/* Routinen zur Laufzeitueberpruefung von Zugriffen                       */
/* Aenderung 08.02.91, Ulrich Vollath: Fail2(), Ausgaben nach stderr      */
/*		unter unix werden die Speicherzugriffe "echt" getestet 	  */
/* erstellt  : 7.3.89                                              	  */
/* ********************************************************************** */

#ifdef __STDC__
#include <stdlib.h>
#endif
#include <stdio.h>          /* E/A, NULL etc.                             */
#include "defs.h"           /* diverse Deklarationen                      */
#include "checks.h"         /* Deklarationen Ueberpruefungsmodul          */


#ifdef __STDC__
#include <stddef.h>
#include <stdlib.h>
#endif
#include <stdio.h>
#include <string.h>
#ifdef unix
#include <signal.h>
#include <setjmp.h>
static jmp_buf fail_jmp;    	  /* jump-Buffer, falls Signal auftritt   */
typedef unsigned char Dummytype;  /* mit diesem Typ wird Zugriff versucht */
typedef Dummytype *Dummyptr;      /* Zeiger auf Zugriffsvariable	  */
#ifdef SIGBUS			  /* Posix, und damit Linux kennen kein SIGBUS */
static void (*old_sigbus)();
#endif
static void (*old_sigsegv)();

/* ====================================================================== */
/* Eigener Handler fuer ausgeloestes Signal				  */
/* ====================================================================== */
#ifdef __STDC__
static void memFault(int sig)
#else
static void memFault(sig)
 int sig;
#endif
 {
  longjmp(fail_jmp,1);
 } /* memFault */
#endif /* unix */

/* ====================================================================== */
/* Testet die Zulaessigkeit eines schreibenden Zugriffes auf eine Adresse */
/* ====================================================================== */
#ifdef __STDC__
int testWrite(void *addr,unsigned size,const char *msg)
#else
int testWrite(addr,size,msg)
 void     *addr;
 unsigned size;
 char     *msg;
#endif
 {
  int res;

  if (addr == NULL)  /* nie erlaubt */
    res = 0;
#ifdef unix
  else
   {
    if (res = !setjmp(fail_jmp))
     {
      Dummytype save;
#ifdef SIGBUS
      old_sigbus  = signal(SIGBUS,memFault);
#endif
      old_sigsegv = signal(SIGSEGV,memFault);
      save = *((Dummyptr)addr);
      *((Dummyptr)addr) = save;
     }
#ifdef SIGBUS
    signal(SIGBUS,old_sigbus);
#endif
    signal(SIGSEGV,old_sigsegv);
   }
#else  /* !unix */
#ifdef amiga
  else
   {
    if (!(res = ((long)addr < 0 || (long)addr > 2000L)))
     {
      fprintf(stderr,
            "Pointer \"%s\" = 0x%lx in Systemspeicher",msg,(unsigned long)addr);
      return(res);
     }
    else if (!(res = (size < 2 || !((long)addr & 1))))
     {
      fprintf(stderr,
            "ungerader Pointer \"%s\" = 0x%lx",msg,(unsigned long)addr);
      return(res);
     }
   }
#else  /* !amiga */
  /* testWrite fuer andere Betriebssysteme nicht implementiert */
#endif /* !amiga */
#endif /* !unix */
  if (!res && msg != NULL)
    fprintf(stderr,
            "Pointer \"%s\" = 0x%lx nicht schreibbar",msg,(unsigned long)addr);
  return(res);
 } /* testWrite */

/* ====================================================================== */
/* Testet die Zulaessigkeit eines lesenden Zugriffes auf eine Adresse     */
/* ====================================================================== */
#ifdef __STDC__
int testRead(const void *addr,unsigned size,const char *msg)
#else
int testRead(addr,size,msg)
 void     *addr;
 unsigned size;
 char     *msg;
#endif
 {
  int res;

  if (addr == NULL)  /* nie erlaubt */
    res = 0;
#ifdef unix
  else
   {
    if (res = !setjmp(fail_jmp))
     {
      Dummytype save;
#ifdef SIGBUS
      old_sigbus  = signal(SIGBUS,memFault);
#endif
      old_sigsegv = signal(SIGSEGV,memFault);
      save = *((Dummyptr)addr);
     }
#ifdef SIGBUS
    signal(SIGBUS,old_sigbus);
#endif
    signal(SIGSEGV,old_sigsegv);
   }
#else  /* !unix */
#ifdef amiga
  else
   {
    if (!(res = ((long)addr < 0 || (long)addr > 2000L)))
     {
      fprintf(stderr,
            "Pointer \"%s\" = 0x%lx in Systemspeicher",msg,(unsigned long)addr);
      return(res);
     }
    else if (!(res = (size < 2 || !((long)addr & 1))))
     {
      fprintf(stderr,
            "ungerader Pointer \"%s\" = 0x%lx",msg,(unsigned long)addr);
      return(res);
     }
   }
#else  /* !amiga */
   /* testRead fuer andere Betriebssysteme nicht implementiert */
#endif /* !amiga */
#endif /* !unix */
  if (!res && msg != NULL)
    fprintf(stderr,
            "Pointer \"%s\" = 0x%lx nicht lesbar",msg,(unsigned long)addr);
  return(res);
 } /* testRead */

/* ====================================================================== */
/* Abbruch der Programmausfuehrung mit Fehlermeldung                      */
/* ====================================================================== */
#ifdef __STDC__
void Fail(const char *file,int zeile,const char *meld)
#else
void Fail(file,zeile,meld)
 char *file;   /* Dateiname der Fehlerstelle           */
 int  zeile;   /* Zeile der Fehlerstelle               */
 char *meld;   /* optionale Fehlermeldung (sonst NULL) */
#endif
 {
  fprintf(stderr," %s, Quelldatei %s, Zeile %d\n",
         meld==NULL ? "Fehler bei Ueberpruefung" : meld ,file,zeile);
  exit(RETURNSTAT_FAIL);  /* Programmlauf abbrechen */
 } /* Fail */

/* ====================================================================== */
/* Abbruch der Programmausfuehrung mit Fehlermeldung                      */
/* und zusaetzlichen Argument (bei __STDC__ verwendet)			  */
/* ====================================================================== */
#ifdef __STDC__
void Fail2(const char *file,int zeile,const char *meld, const char *arg)
#else
void Fail2(file,zeile,meld,arg)
 char *file;   /* Dateiname der Fehlerstelle           */
 int  zeile;   /* Zeile der Fehlerstelle               */
 char *meld;   /* optionale Fehlermeldung (sonst NULL) */
 char *arg;    /* Argument des aufrufenden Makros      */
#endif
 {
  fprintf(stderr,"*** %s%s, Quelldatei %s, Zeile %d\n",
         meld==NULL ? "Fehler bei Ueberpruefung " : meld,arg,file,zeile);
  exit(RETURNSTAT_FAIL);  /* Programmlauf abbrechen */
 } /* Fail2 */

