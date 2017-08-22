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

/* Aktueller Stand vom 19.4.90 */
/* Aenderungen: */
/* copyanz */
/* auxcopyanz */
#ifdef __STDC__
#include <stddef.h>
#include <stdlib.h>
#endif
#include <string.h>
#include <stdio.h>
#include <ctype.h>

#ifndef __DATE__
#define __DATE__ "19. April 1990"
#endif
#include "zufunc.h"

typedef int    integer;
typedef char   boolean;
# define false ((boolean)0)
# define true ((boolean)1)

# define maxloklength 200
# define D_NAME_LAENGE 100      /* Maximale Laenge eines Datei-Namens    */
# define D_EXT_LAENGE  100      /* Maximale Laenge einer Datei-Extension */

/********************************** globaldatenstruktur *******/
typedef struct attmenge * ptattmenge;          
typedef struct attmenge {       /* attribut-ringliste :       */
   ptattmenge  nachatt;         /* pt auf naechstes ringelem. */
   Attr        attname;         /* pt auf naechstes ringelem. */
}  attmenge;                    

typedef struct teilmenge * ptteilmenge; 
typedef struct teilmenge {      /* pt-tripel mit pt auf:      */
   ptteilmenge nachftm;         /* naechste attr.-teilmenge des gleichen sym */
   ptteilmenge identtm;         /* identifizierte attr.-tm    */
   ptattmenge  attring;         /* attribut-ringliste         */
}  teilmenge;

typedef struct globdat * ptglobdat; /* struct S64 */
typedef struct globdat {        /* enthaelt pt auf:           */
   Vocabel  symbname;           /* symbol                     */
   ptteilmenge derivedtm;       /* derived attr.-teilmenge    */
   ptteilmenge inherettm;       /* inherited attr.-teilmenge  */
   ptglobdat   nachfsymb;       /* naechstes symbol           */
}  globdat;

/******************************* lokaldatenstruktur ******************/
typedef struct  {               /* lokaldatenelement :               */      
   integer  index;              /* verweis auf identifiz. teilmengen */
   Attr attr;                   /* attribut                          */
   Attrpos attpos;              /* attributposition                  */
}  lok;                         /*************************************/


typedef lok lokdat[maxloklength]; /*lokaldatenstruktur */

#define LDCOPY(q,z) do{int i; for(i=0; i<maxloklength; i++) z[i] = q[i];} \
			while(0)

/******************************* copysymbol-information *************/
typedef struct copy *ptcopy;   /*                                   */
typedef struct copy {          /* copy-symbol:                      */
   ptcopy   nextcopy;          /* pt auf naechstes copy-symbol      */
   integer  name;              /* laufende nummer der copy-sysmbole */
   integer  inhnumb;           /* anz. der kopierten inherited attr.*/
   Product  prod;              /* einfuegestelle : produktion       */
   Prodpos  propos;            /*                  prod.-position   */
}  copy;                       /*************************************/

/******************************* neueingefuehrte berechnungsregeln **/ 
typedef struct merkeregel * ptmerkeregel;
typedef struct merkeregel {    /* neueingefuehrte regel:            */
   ptmerkeregel   pmr;         /* pt auf naechstes element          */
   Product  mrprod;            /* zugehoerige produktion            */
   Attrpos  mrziel;            /* ziel :=                           */
   Attrpos  mrquelle;          /* neue berechnungsregel             */
}  merkeregel;                 /*************************************/

EXTERN char phasen_id[D_NAME_LAENGE + 1]; /* Datei-Name + abschl. 0 */ 

typedef struct merketm * ptmerketm; 
typedef struct merketm {       
                              /* alle teilmengen der Lokaldatenstruktur: */
   ptmerketm   ntm;           /* Verweis auf naechste Komponente         */
	ptteilmenge ptm;           /* eingetragene Teilmenge                  */
   integer  adresse;          /* Nummer des Feldelements der Lokal-      */
}  merketm;                   /* datenstruktur, in die das erste Attribut*/
                              /* der Teilmenge eingetragen wurde         */

EXTERN FILE *outglob, *outprod, *outcopy;

EXTERN Vocabel     a_axiom;
EXTERN ptglobdat   globstrukt;         /* globaldatenstruktur                    */
EXTERN ptcopy   copyinfo;              /* information ueber copy-symbole         */
EXTERN ptmerkeregel   mregel;          /* information ueber neue berechn.-regeln */
EXTERN boolean  forcopy;               /* Schalter fuer copy-Bearbeitung         */
EXTERN boolean  foroutput;
EXTERN lokdat   lokstrukt;             /* lokaldatenstruktur                     */
EXTERN integer  beranfang;             /* index des 1. inh. attr.                */
EXTERN integer  loklength;             /* index des letzten attr.                */
EXTERN integer  copyname;              /* eindeutige laufende nr. d.COPY-Symbols */
EXTERN boolean  nofehler;              /* fehlervariable                         */
EXTERN integer  copyanz;               /* anzahl der Copys (nach identcop)       */
EXTERN integer  auxcopyanz;            /* Anzahl der Auxiliary-Copy's            */

