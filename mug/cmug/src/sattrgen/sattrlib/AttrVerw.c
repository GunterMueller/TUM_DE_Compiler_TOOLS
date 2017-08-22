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
#include <stdio.h>
#include <string.h>

/* Modul zum Verwalten des Attributkellers */


#define MAX_LAENGE 200

#ifndef TRUE
#define TRUE 1
#endif
#ifndef FALSE
#define FALSE 0
#endif

#ifndef __STDC__
extern char *malloc();
extern char *realloc();
#endif


int top = 0,auxtop = 0;
int EndOfKeller = 0,EndOfAuxKeller = 0;

char **keller = NULL;
char **auxkeller = NULL;


#ifdef __STDC__
void pushattr(char *what)
#else /* ! __STDC__ */
void pushattr(what)
char *what;
#endif /* ! __STDC__ */
 {
  if (top+1 >= EndOfKeller)
   {
    if (EndOfKeller)
      EndOfKeller += EndOfKeller >> 1;
    else
      EndOfKeller = MAX_LAENGE;
    if(keller == NULL &&
         (keller = (char **)malloc(EndOfKeller * sizeof(char *))) == NULL ||
          keller != NULL &&
         (keller = (char **)realloc(keller,EndOfKeller * sizeof(char *)))
           == NULL)
     {
	memError();
       /* Hier sollte SemAbort oder so etwas stehen !!!! */
	exit(13);
     }
   }
  keller[top++] = what;
 }

/*
 stellt sicher, dass noch Platz fuer einen Eintrag der Laenge <len>
 auf dem Attributkeller ist
*/
#ifdef __STDC__
void allocAttr(unsigned long len)
#else /* ! __STDC__ */
void allocAttr(len)
 unsigned long len;
#endif /* ! __STDC__ */
 {
  if (top + len >= EndOfKeller)
   {
    if (EndOfKeller)
      EndOfKeller += EndOfKeller >> 1;
    else
      EndOfKeller = MAX_LAENGE;
    if( keller == NULL &&
       (keller = (char **)malloc(EndOfKeller * sizeof(char *))) == NULL ||
        keller != NULL &&
       (keller = (char **)realloc(keller,EndOfKeller * sizeof(char *)))
           == NULL)
      {
	memError();
        /* Hier sollte SemAbort oder so etwas stehen !!!! */
	exit(13);
      }
   }
 } /* allocAttr */

#ifdef __STDC__
void pushaux(char *what)
#else /* ! __STDC__ */
void pushaux(what)
char *what;
#endif /* ! __STDC__ */
 {
  if (auxtop + 1 >= EndOfAuxKeller)
   {
    if (EndOfAuxKeller)
      EndOfAuxKeller += EndOfAuxKeller >> 1;
    else
      EndOfAuxKeller = MAX_LAENGE;
    if(auxkeller == NULL &&
      (auxkeller = (char **)malloc(EndOfAuxKeller * sizeof(char *))) == NULL ||
       auxkeller == NULL &&
      (auxkeller = (char **)realloc(auxkeller,EndOfAuxKeller * sizeof(char *)))
           == NULL)
     {
		memError();
       /* Hier sollte SemAbort oder so etwas stehen !!!! */
		exit(14);
     }
   }
  auxkeller[auxtop++] = what;
 }

/*
 stellt sicher, dass noch Platz fuer einen Eintrag der Laenge <len>
 auf dem Auxiliarykeller ist
*/
#ifdef __STDC__
void allocAux(unsigned long len)
#else /* ! __STDC__ */
void allocAux(len)
 unsigned long len;
#endif /* ! __STDC__ */
 {
  if (auxtop + len >= EndOfAuxKeller)
   {
    if (EndOfAuxKeller)
      EndOfAuxKeller += EndOfAuxKeller >> 1;
    else
      EndOfAuxKeller = MAX_LAENGE;
    if( auxkeller == NULL &&
       (auxkeller = (char **)malloc(EndOfAuxKeller * sizeof(char *))) == NULL ||
        auxkeller != NULL &&
       (auxkeller = (char **)realloc(auxkeller,EndOfAuxKeller * sizeof(char *)))
           == NULL)
      {
	memError();
        /* Hier sollte SemAbort oder so etwas stehen !!!! */
	exit(13);
      }
   }
 } /* allocAux */

#ifdef __STDC__
char *getattr(int which)
#else /* ! __STDC__ */
char *getattr(which)
int which;
#endif /* ! __STDC__ */
{
	return(keller[top-which]);
}

#ifdef __STDC__
char *getaux(int which)
#else /* ! __STDC__ */
char *getaux(which)
int which;
#endif /* ! __STDC__ */
{
	return(auxkeller[auxtop-which]);
}

/*       Funktion redattr raeumt den Keller nach einer 
		   Reduktion auf: es werden die	derived Attribute der linken
   	   Seite an die Spitze kopiert und des Speicherplatz
		   wird wieder freigegeben  
*/

#ifdef __STDC__
void redattr(int wo, int derived)
#else /* ! __STDC__ */
void redattr(wo,derived)
int	wo;
int derived;
#endif /* ! __STDC__ */
{
   	register int i;
      register int ort;
		
		ort = wo+top;	 

   /* Die Zwischendinge freeen !!!  */

   for(i = ort; i < (top-derived); i++)
      free(keller[i]);

	for(i=0;i<derived;i++)
		keller[ort+i]= keller[top - derived + i];	

	top = ort + derived; 

}

/*       Funktion redattr1 raeumt den Keller nach einer 
		   Reduktion auf: es werden die	derived Attribute der linken
   	   Seite an die Spitze kopiert und des Speicherplatz
		   wird wieder freigegeben  
*/
/* wie redattr, aber wo -> -wo - derived */
#ifdef __STDC__
void redattr1(int wo, int derived)
#else /* ! __STDC__ */
void redattr1(wo,derived)
int	wo;
int derived;
#endif /* ! __STDC__ */
{
  register int i;
  register int ort;
		
  ort = -wo - derived + top;	 

   /* Die Zwischendinge freeen !!!  */

   for(i = ort; i < (top-derived); i++)
      free(keller[i]);

	for(i=0;i<derived;i++)
		keller[ort+i]= keller[top - derived + i];	

	top = ort + derived; 

}
/* wie redattr1, aber ohne free()'s */
#ifdef __STDC__
void redattr2(int wo, int derived)
#else /* ! __STDC__ */
void redattr2(wo,derived)
int	wo;
int derived;
#endif /* ! __STDC__ */
{
  register int i;
  register int ort;
		
  ort = -wo - derived + top;
  for (i=0;i<derived;i++)
    keller[ort+i]= keller[top - derived + i];	
  top = ort + derived; 
}

#ifdef __STDC__
void redaux(int anzahl)
#else /* ! __STDC__ */
void redaux(anzahl)
int anzahl;
#endif /* ! __STDC__ */
{
 	register int i;
	
	for(i=1; i<=anzahl; i++)
		free(auxkeller[--auxtop]);
}


