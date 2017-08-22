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



/* ************************************************************** */
/* millisec.c: Zeitmessungsroutinen                               */
/* erstellt  :  18.10.90 (uv)                                     */
/* ************************************************************** */
#ifdef __STDC__
#include <stddef.h>
#include <stdlib.h>
#endif
#include <stdio.h>
#include "defs.h"
#include "millisec.h"
#ifdef AMIGA
#define HZ 50
#else
#include <sys/types.h>
#include <sys/times.h>
#include <sys/param.h>
#endif
#ifdef ultrix
#define HZ 50 /* traurig, aber wahr */
#endif
#ifdef apollo
#define HZ 50 /* traurig, aber wahr */
#endif

#ifdef AMIGA
struct DateStamp {		/* Yes, this is a hack, but doing it right */
	long ds_Days;		/* is incredibly ugly without splitting this */
	long ds_Minute;		/* off into a separate file */
	long ds_Tick;
};

static int first_clock = TRUE;
static struct DateStamp begin;
static struct DateStamp elapsed;

/* ======================================================== */
/* Gibt die abgelaufene Zeit in Millisekunden an            */
/* ======================================================== */
Msecs milliSecs()
 {
    register struct DateStamp *now;
    register Msecs millisec = 0;
    register Msecs min = 0;
    extern void *AllocMem ();

    now = (struct DateStamp *) AllocMem ((long) sizeof (struct DateStamp), 0L);
    if (now != NULL) {
	if (first_clock == TRUE) {
	    first_clock = FALSE;
	    (void)DateStamp (now);
	    begin = *now;
	}
	(void)DateStamp (now);
	min = 24 * 60 * (now -> ds_Days - begin.ds_Days);
	min += (now -> ds_Minute - begin.ds_Minute);
	millisec +=  min * 60000L + (1000 / HZ) * (now -> ds_Tick - begin.ds_Tick);
	(void) FreeMem (now, (long) sizeof (struct DateStamp));
    }
    return (millisec);
 } /* milliSecs */

#else /* NOT amiga */
/* ======================================================== */
/* Gibt die aktuelle Rechenkernzeit in Millisekunden an     */
/* ======================================================== */
Msecs milliSecs()
 {
  struct tms buffer;

  if (times(&buffer) == -1)
   {
    perror("times ");
    return(0L);
   }
  else
    return((Msecs)(((buffer.tms_utime+buffer.tms_stime)*1000L) / HZ));
 } /* milliSecs */
#endif /* amiga */
