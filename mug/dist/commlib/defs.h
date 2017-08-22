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
/* defs.h   :                                                             */
/* diverse unspezifische Definitionen                                     */
/* letzte Aenderung : 02.07.89                                            */
/* erstellt   : 23.1.89                                                   */
/* ********************************************************************** */
#ifndef DEFS_H
#define DEFS_H

#ifdef LATTICE
#include <stdlib.h>
#else
#ifdef __STDC__
#define __ARGS(a) a
#else
#undef __ARGS
#define __ARGS(a) ()
#endif
#endif

#ifndef BOOL
#define BOOL int
#endif

#ifndef TRUE
#define TRUE ((BOOL)1)
#endif

#ifndef FALSE
#define FALSE ((BOOL)0)
#endif

/* -------------------------------------------------------- */
/* Statuscodes fuer exit(..)-Funktion, AMIGADOS-spezifisch  */
/* -------------------------------------------------------- */
/* Programm erfolgreich beendet */
#define RETURNSTAT_OK 0L

/* Programm mit Warnungen beendet */
#define RETURNSTAT_WARN 5L

/* Programm mit Fehlern beendet */
#define RETURNSTAT_ERROR 10L

/* Programm abgebrochen , fataler Fehler */
#define RETURNSTAT_FAIL 20L

/* ========================================================== */
/* Deklarationen gaengiger Funktionen                         */
/* ========================================================== */
#ifndef __STDC__
char *malloc(); 
/*typedef long time_t;*/
#endif
#ifndef MALLOC
#define MALLOC(siz) malloc((unsigned)(siz))
#endif
#endif

