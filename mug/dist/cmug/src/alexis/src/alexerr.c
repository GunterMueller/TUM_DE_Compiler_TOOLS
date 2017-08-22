/*******************************************************************}
{*                                                                 *}
{*   Technische Universitaet Muenchen, Institut fuer Informatik    *}
{*                 Lehrstuhl Prof. Dr. J. Eickel                   *}
{*                                                                 *}
{*                                                                 *}
{*     AAA     L         EEEEEEEE    XX     XX    III    SSSSS     *}
{*    A   A    L         E            X     X      I    S     S    *}
{*   A     A   L         E             X   X       I    S          *}
{*   AAAAAAA   L         EEEEEE         XXX        I     SSSSS     *}
{*   A     A   L         E             X   X       I          S    *}
{*   A     A   L         E            X     X      I    S     S    *}
{*   A     A   LLLLLLL   EEEEEEEE    XX     XX    III    SSSSS     *}
{*                                                                 *}
{*      Advanced LEXical Instrument for Scannergeneration          *}
{*                                                                 *}
{*                                                                 *}
{*******************************************************************}
{*                                                                 *}
{*  Projekt: ALEXIS  V 2.0                                         *}
{*                                                                 *}
{*  Autoren: Bernhard Smith, Frank Eiberle                         *}
{*                                                                 *}
{*  Copyright: Technische Universitaet Muenchen,                   *}
{*             Institut fuer Informatik                            *}
{*                                                                 *}
{*  Segment: alexerr1.c                                            *}
{*  Version: 20/05/91                                              *}
{*                                                                 *}
{*  Sprache: C                                                     *}
{*                                                                 *}
{*-----------------------------------------------------------------*}
{*                                                                 *}
{*  Beschreibung:                                                  *}
{*                                                                 *}
{*  Inhalt:                                                        *}
{*        lperror                                                  *}
{*        AERAlexWarning                                           *}
{*        AERAlexRecoverableError                                  *}
{*        AERAlexFatalError                                        *}
{*        AERAlexSoftwareError                                     *}
{*                                                                 *}
{*-----------------------------------------------------------------*}
{*                                                                 *}
{*                 M O D I F I K A T I O N E N                     *}
{*=================================================================*}
{* Datum      modifiziert von    Beschreibung der Modifikation     *}
{*=================================================================*}
{*                                                                 *}
{*******************************************************************/

#ifdef __STDC__
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#endif


#include "scan.h"


/* Bauernfeind: Prototypen, 9.6.93 */
#ifdef __STDC__
extern void wErrorf(Quellort*, char* , ...);
#endif


 
/*******************************************************************}
{*                                                                 *}
{*  Prozedur: AERAlexWarning          Version:  20/05/91           *}
{*                                                                 *}
{*******************************************************************}
{*                                                                 *}
{*  Klassifizierung:  Prozedur                                     *}
{*                                                                 *}
{*  Funktionsbeschreibung:                                         *}
{*  Ausgabe einer Warnung an den Benutzer uber den Protokoll-      *}
{*  Operator                                                       *}
{*-----------------------------------------------------------------*}
{*                                                                 *}
{*  Eingabeparameter:                                              *}
{*  WarningNumber             int                                  *}
{*  zeile                     int                                  *}
{*  spalte                    int                                  *}
{*  Seiteneffekte:                                                 *}
{*                                                                 *}
{*  Lokale Variablen:                                              *}
{*  fstring                   varfilestring                        *}
{*******************************************************************/

#ifdef __STDC__
void AERAlexWarning(int WarningNumber, Quellort *ort)
#else /* ! __STDC__ */
AERAlexWarning(WarningNumber,ort)
int WarningNumber;
Quellort *ort;
#endif /* ! __STDC__ */
{ switch(WarningNumber) {
     case 1 : wErrorf(ort,"Redefinition eines Aktionsmakros:\nDie alte Definition wurde ueberschrieben\n");
              break;
     case 2 : wErrorf(ort,"Erweiterung einer Spezialaktion:\nEine weitere Aktion wurde angehaengt\n");
              break;
     case 3 : wErrorf(ort,"Redefinition eines lexikalischen Makros:\nDie alte Definition wurde ueberschrieben\n");
              break;
         }
}

   
/*******************************************************************}
{*                                                                 *}
{*  Prozedur: AERAlexRecoverableError    Version:  20/05/91        *}
{*                                                                 *}
{*******************************************************************}
{*                                                                 *}
{*  Klassifizierung:  Prozedur                                     *}
{*                                                                 *}
{*  Funktionsbeschreibung:                                         *}
{*  Ausgabe einer Fehlermeldung an den Benutzer uber den Protokoll-*}
{*  Operator                                                       *}
{*  Die Kontrolle wird an das Programm zurueckgegeben              *}
{*-----------------------------------------------------------------*}
{*                                                                 *}
{*  Eingabeparameter:                                              *}
{*  ErrorNumber             int                                    *}
{*  Seiteneffekte:                                                 *}
{*                                                                 *}
{*  Lokale Variablen:                                              *}
{*  fstring                   varfilestring                        *}
{*******************************************************************/

#ifdef __STDC__
void AERAlexRecoverableError(int ErrorNumber, Quellort *ort)
#else /* ! __STDC__ */
AERAlexRecoverableError(ErrorNumber,ort)
int ErrorNumber;
Quellort *ort;
#endif /* ! __STDC__ */
{ switch(ErrorNumber) {
    case 1 : wErrorf(ort,"Fehler in formaler Parameterliste:\nMehr als 9 Parameter angegeben\n");
             break;
    case 2 : wErrorf(ort,"Anweisung wurde doppelt gegeben\n");
             break;
    case 3 : wErrorf(ort,"Widerspruch in den gesetzten Anweisungen\n");
             break;
    case 4 : wErrorf(ort,"Makro ist schon als Lexmakro definiert\n");
             break;
    case 5 : wErrorf(ort,"Makro ist schon als Aktionsmakro definiert\n");
             break;
    case 6 : wErrorf(ort,"Nicht mehr als 10 Parameter moeglich\n");
             break;
    case 7 : wErrorf(ort,"Fehler in formaler Parameterliste:\n");
             break;
    case 8 :
       /*Diese Fehlermeldung kann nicht durch eine falsche Scannerbeschreibung
         erzeugt werden, sondern kann nur durch falsche Parameteruebergabe
         entstehen */
             wErrorf(ort,"Operator ist nicht spezifiziert\n");
             break;
    case 9 : wErrorf(ort,"Parameterzahl stimmt nicht mit der Definition\ndes Makros ueberein\n");
             break;
   case 10 : wErrorf(ort,"Statt eines Aktionsmakros wurde ein lexikalischer\nMakro angegeben\n");
             break;
   case 11 : wErrorf(ort,"Der angegebene Makro ist nicht definiert\n");
             break;
   case 12 : wErrorf(ort,"Statt eines LexMakros wurde ein AktionsMakro\nangegeben\n");
             break;
   case 13 : wErrorf(ort,"Angabe eines Strings statt eines Einzelzeichens\nin einer Mengendefinition. Erster Buchstabe wurde\nverwendet, Rest abgeschnitten\n");
             break;
      };
  printf("Die Compilierung wird fortgesetzt!\n");
}

 
 
/*******************************************************************}
{*                                                                 *}
{*  Prozedur: AERAlexFatalError          Version:  20/05/91        *}
{*                                                                 *}
{*******************************************************************}
{*                                                                 *}
{*  Klassifizierung:  Prozedur                                     *}
{*                                                                 *}
{*  Funktionsbeschreibung:                                         *}
{*  Ausgabe einer Fehlermeldung an den Benutzer uber den Protokoll-*}
{*  Operator                                                       *}
{*  Das Programm wird abgebrochen                                  *}
{*-----------------------------------------------------------------*}
{*                                                                 *}
{*  Eingabeparameter:                                              *}
{*  ErrorNumber               int                                  *}
{*  zeile                     int                                  *}
{*  spalte                    int                                  *}
{*  Seiteneffekte:                                                 *}
{*                                                                 *}
{*  Lokale Variablen:                                              *}
{*  fstring                   varfilestring                        *}
{*******************************************************************/

#ifdef __STDC__
void AERAlexFatalError(int ErrorNumber, Quellort *ort)
#else /* ! __STDC__ */
AERAlexFatalError(ErrorNumber,ort)
int ErrorNumber;
Quellort *ort;
#endif /* ! __STDC__ */
{ switch (ErrorNumber) {
    case 1 : wErrorf(ort,"Zu viele Zustaende bei der Komprimierung!\n");
             break;
    case 2 : wErrorf(ort,"Zuviele Tokens spezifiziert!\n");
             break;
      }
  printf("Die Compilierung wird abgebrochen!\n");
  exit(1);
} 

 
/*******************************************************************}
{*                                                                 *}
{*  Prozedur: AERAlexSoftwareError       Version:  20/05/91        *}
{*                                                                 *}
{*******************************************************************}
{*                                                                 *}
{*  Klassifizierung:  Prozedur                                     *}
{*                                                                 *}
{*  Funktionsbeschreibung:                                         *}
{*  Ausgabe einer Fehlermeldung an den Benutzer uber den Protokoll-*}
{*  Operator                                                       *}
{*  Programmabbruch. Fuer nicht definierte Zustaende im Programm   *}
{*-----------------------------------------------------------------*}
{*                                                                 *}
{*  Eingabeparameter:                                              *}
{*  ErrorNumber               int                                  *}
{*  zeile                     int                                  *}
{*  spalte                    int                                  *}
{*  Seiteneffekte:                                                 *}
{*                                                                 *}
{*  Lokale Variablen:                                              *}
{*  fstring                   varfilestring                        *}
{*  Lokale Prozeduren und Funktionen:                              *}
{*******************************************************************/
 
#ifdef __STDC__
void AERAlexSoftwareError(int ErrorNumber, Quellort *ort)
#else /* ! __STDC__ */
AERAlexSoftwareError(ErrorNumber,ort)
int ErrorNumber;
Quellort *ort;
#endif /* ! __STDC__ */
{ switch (ErrorNumber) { 
   case 1 :  
       /* Diese Fehlermeldung kann nicht durch eine falsche Scannerbeschreibung
         erzeugt werden, sondern kann nur durch falsche Parameteruebergabe
         entstehen */
        wErrorf(ort,"Operator ist nicht spezifiziert\n");
        break;
      }
  exit(1);
}  
