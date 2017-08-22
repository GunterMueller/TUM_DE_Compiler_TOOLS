
/* ************************************************************* */
/* scn_glob.c : Funktionslibrary des tabellengetriebenen         */
/*   parametrisierten Scanners, globale Variablen 		 */
/* erstellt  24.01.91, Ulrich Vollath     			 */
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
#include "ps_tab.h"    /* Datenstruktur der Scannertabelle	       */   
#define EXTERN         /* Variablen anlegen			       */
#include "scn_glob.h"  /* globale Vereinbarungen und Variablen         */

/* das war's */
