/*******************************************************************/
/*                                                                 */
/*   Technische Universitaet Muenchen, Institut fuer Informatik    */
/*                 Lehrstuhl Prof. Dr. J. Eickel                   */
/*                                                                 */
/*                                                                 */
/*     AAA     L         EEEEEEEE    XX     XX    III    SSSSS     */
/*    A   A    L         E            X     X      I    S     S    */
/*   A     A   L         E             X   X       I    S          */
/*   AAAAAAA   L         EEEEEE         XXX        I     SSSSS     */
/*   A     A   L         E             X   X       I          S    */
/*   A     A   L         E            X     X      I    S     S    */
/*   A     A   LLLLLLL   EEEEEEEE    XX     XX    III    SSSSS     */
/*                                                                 */
/*      Advanced LEXical Instrument for Scannergeneration          */
/*                                                                 */
/*                                                                 */
/*******************************************************************/
/*                                                                 */
/*  Projekt: ALEXIS  2.0                                           */
/*                                                                 */
/*  Autoren: Bernhard Smith, Frank Eiberle                         */
/*                                                                 */
/*  Copyright: Technische Universitaet Muenchen,                   */
/*             Institut fuer Informatik                            */
/*                                                                 */
/*  Segment: error.c                                               */
/*  Version: 20/05/91                                              */
/*                                                                 */
/*  Sprache: C                                                     */
/*                                                                 */
/*-----------------------------------------------------------------*/
/*                                                                 */
/*  Beschreibung:                                                  */
/*                                                                 */
/*  Inhalt:                                                        */
/*        Warning                                                  */
/*        RecoverableError                                         */
/*        FatalError                                               */
/*        SoftwareError                                            */
/*        initerror                                                */
/*                                                                 */
/*-----------------------------------------------------------------*/
/*                                                                 */
/*                 M O D I F I K A T I O N E N                     */
/*=================================================================*/
/* Datum      modifiziert von    Beschreibung der Modifikation     */
/*=================================================================*/
/*                                                                 */
/*                                                                 */
/*******************************************************************/

#ifdef __STDC__
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#endif

#include <stdio.h>
#include "global.h"



/*******************************************************************/
/*                                                                 */
/*  Prozedur: Warning                 Version:  20/05/91           */
/*                                                                 */
/*******************************************************************/
/*                                                                 */
/*  Klassifizierung:  Prozedur                                     */
/*                                                                 */
/*  Funktionsbeschreibung:                                         */
/*  gibt eine Warnung aus und kehrt zum Programm zurueck           */
/*-----------------------------------------------------------------*/
/*                                                                 */
/*  Eingabeparameter:                                              */
/*  WarningNumber             integer32                            */
/*  Seiteneffekte:                                                 */
/*                                                                 */
/*******************************************************************/

#ifdef __STDC__
void Warning(int WarningNumber)
#else /* ! __STDC__ */
void Warning(WarningNumber)
  int WarningNumber;
#endif /* ! __STDC__ */
{
  printf("\nWARNUNG: ");
  switch (WarningNumber)
  {
    case 1 : printf(" NR. %d\n",WarningNumber);
  }
}




/*******************************************************************/
/*                                                                 */
/*  Prozedur: RecoverableError        Version:  20/05/91           */
/*                                                                 */
/*******************************************************************/
/*                                                                 */
/*  Klassifizierung:  Prozedur                                     */
/*                                                                 */
/*  Funktionsbeschreibung:                                         */
/*  Gibt eine Fehlermeldung aus und kehrt zum Programm zurueck     */
/*-----------------------------------------------------------------*/
/*                                                                 */
/*  Eingabeparameter:                                              */
/*  ErrorNumber               integer32                            */
/*  Seiteneffekte:                                                 */
/*                                                                 */
/*******************************************************************/

#ifdef __STDC__
void RecoverableError(int ErrorNumber)
#else /* ! __STDC__ */
void RecoverableError(ErrorNumber)
  int ErrorNumber;
#endif /* ! __STDC__ */
{
  /* Gibt eine Fehlermeldung aus und kehrt zum Programm zurueck. */
  printf("\n+++Fehler: ");
  switch(ErrorNumber)
  {
    case 1 : printf(" NR. %d\n",ErrorNumber);
  }
  printf("Die Compilierung wird fortgesetzt!\n");
}




/*******************************************************************/
/*                                                                 */
/*  Prozedur: FatalError              Version:  20/05/91           */
/*                                                                 */
/*******************************************************************/
/*                                                                 */
/*  Klassifizierung:  Prozedur                                     */
/*                                                                 */
/*  Funktionsbeschreibung:                                         */
/*  Gibt eine Fehlermeldung aus und bricht ab.                     */
/*-----------------------------------------------------------------*/
/*                                                                 */
/*  Eingabeparameter:                                              */
/*  ErrorNumber               integer32                            */
/*  Seiteneffekte:                                                 */
/*                                                                 */
/*******************************************************************/

#ifdef __STDC__
void FatalError(int ErrorNumber)
#else /* ! __STDC__ */
void FatalError(ErrorNumber)
  int ErrorNumber;
#endif /* ! __STDC__ */
{
  printf("\n!!!Fehler: ");
  switch(ErrorNumber)
  {
    case 1 : printf("Zu viele Zustaende bei der Komprimierung!\n");
             break;
    case 2 : printf("Zu viele Kanten bei der Komprimierung!\n");
             break;
    case 3 : printf("Zu viele Zustaende bei der Generierung!\n");
             break;
  }
  printf("Die Compilierung wird abgebrochen!\n");
  exit(1);
}




/*******************************************************************/
/*                                                                 */
/*  Prozedur: SoftwareError           Version:  20/05/91           */
/*                                                                 */
/*******************************************************************/
/*                                                                 */
/*  Klassifizierung:  Prozedur                                     */
/*                                                                 */
/*  Funktionsbeschreibung:                                         */
/*  Wird bei nicht definierten Situationen aufgerufen und          */
/*  bricht das aufrufende Programm mit einer Fehlermeldung ab      */
/*-----------------------------------------------------------------*/
/*                                                                 */
/*  Eingabeparameter:                                              */
/*  ErrorNumber               Integer                              */
/*  Seiteneffekte:                                                 */
/*                                                                 */
/*******************************************************************/

#ifdef __STDC__
void SoftwareError(int ErrorNumber)
#else /* ! __STDC__ */
void SoftwareError(ErrorNumber)
  int ErrorNumber;
#endif /* ! __STDC__ */
{
  printf("\n!!!Softwarefehler: ");
  switch (ErrorNumber)
  {
    case 1 : printf("Zustand gehoerte nicht zum Automaten");
             break;
    case 2 : printf("Automat enthielt leere Kantenmenge");
             break;
    case 3 : printf("In Kantenmenge fehlt die Defaultkante");
             break;
    case 4 : printf("Stack des Minimierers unerwartet leer");
             break;
    case 5 : printf("DeleteState auf leerer Menge aufgerufen");
             break;
    case 6 : printf("DeleteState mit Element aufgerufen, das nicht Element ist");
             break;
    case 7 : printf("Kante darf nicht leer sein");
             break;
    case 8 : printf("Es sollten fuer t aus T Kanten erzeugt werden, Menge nicht leer");
             break;
    case 9 : printf("DeleteEvent mit Element aufgerufen, das nicht Element ist");
             break;
    case 10 : printf("GiveAndDeleteEvent mit leerer Menge aufgerufen");
              break;
    case 11 : printf("DelteEvent mit leerer Menge aufgerufen");
              break;
    case 12 : printf("Twist mit weniger als 2 Automaten auf dem Stack aufgerufen");
              break;
    case 13 : printf("KillFang:Startzustand wurde als Fangzustand erkannt");
              break;
    case 14 : printf("MakeKantenMenge: from > toEvent");
              break;
    case 15 : printf("ComplStateSet aufgerufen, ohne dass Menge Teilmenge der Grundmenge");
              break;
    case 16 : printf("SetGetMinStackElem konnte keine Partition finden!");
              break;
  }
  exit(1);
}




/*******************************************************************/
/*                                                                 */
/*  Prozedur: initerror               Version:  20/05/91           */
/*                                                                 */
/*******************************************************************/
/*                                                                 */
/*  Klassifizierung:  Prozedur                                     */
/*                                                                 */
/*  Funktionsbeschreibung:                                         */
/*  Dummy                                                          */
/*-----------------------------------------------------------------*/
/*                                                                 */
/*  Seiteneffekte:                                                 */
/*                                                                 */
/*******************************************************************/

#ifdef __STDC__
void initerror(void)
#else /* ! __STDC__ */
void initerror()
#endif /* ! __STDC__ */
{}
