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
{*  Segment: MUGERROR                                              *}
{*  Version: 13/12/90                                              *}
{*                                                                 *}
{*  Sprache: C                                                     *}
{*                                                                 *}
{*-----------------------------------------------------------------*}
{*                                                                 *}
{*  Beschreibung:                                                  *}
{*    Dieses Segment erledigt die Fehlerbehandlung des Laufzeit-   *}
{*    systems. Es enthaelt alle Fehlermeldungen, die durch den     *}
{*    Automaten, die Symboltabelle, das MugInterface oder die      *}
{*    Aktionen erkannt werden. Die Fehler sind in vier Kategorien  *}
{*    aufgeteilt:                                                  *}
{*                                                                 *}
{*       Warnungen: Werden zur Information des Benutzers ausgege-  *}
{*                  ben, ohne jedoch den Abalauf des Scannens      *}
{*                  zu beeinflussen                                *}
{*                                                                 *}
{*       Recoverable Errors: Fehler, die zwar zu berichtigen sind, *}
{*                  aber nach deren Auftreten das Ergebnis des     *}
{*                  Scannens mit hoher Wahrscheinlichkeit sinn-    *}
{*                  los ist.                                       *}
{*                                                                 *}
{*       Fatal Errors: Fehler, die nicht mehr berichtigt werden    *}
{*                  koennen oder deren Auftreten das weitere       *}
{*                  Scannen sinnlos erscheinen lassen.             *}
{*                  Das Auftreten eines solchen Fehlers fuehrt zum *}
{*                  sofortigen Abbruch der Scanlaufes.             *}
{*                                                                 *}
{*       Software Errors: Innerhalb des Generierungssystems sind   *}
{*                  Inkonsistenzen aufgetreten. Diese Meldung tritt*}
{*                  nur auf, wenn sich innerhalb von ALEXIS ein    *}
{*                  Programmfehler befindet. Er fuehrt zum sofor-  *}
{*                  tigen Abbruch des Scannens                     *}
{*                                                                 *}
{*                                                                 *}
{*                                                                 *}
{*  Inhalt:                                                        *}
{*                                                                 *}
{*    procedure MEAlexWarning                                      *}
{*    procedure MEAlexRecoverableError                             *}
{*    procedure MEAlexFatalError                                   *}
{*    procedure MEAlexSoftwareError                                *}
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

#include "mugerr.h"

#define VERSION "BeSm: 13.12.90/a"

/*******************************************************************}
{*                                                                 *}
{*  Prozedur: MEMugWarning            Version: 13/12/90            *}
{*                                                                 *}
{*******************************************************************}
{*                                                                 *}
{*  Klassifizierung: Globale Prozedur                              *}
{*                                                                 *}
{*  Funktionsbeschreibung:                                         *}
{*     Diese Prozedur setzt eine Warnung ab und kehrt zum Aufrufer *}
{*     zurueck. Zur Zeit sind keine Meldungen implementiert, des-  *}
{*     halb fuehrt ein Aufruf dieser Prozedur auf einen Software-  *}
{*     fehler.                                                     *}
{*                                                                 *}
{*-----------------------------------------------------------------*}
{*                                                                 *}
{*  Eingabeparameter:                                              *}
{*      WarningNumber : int; Nummer der Warnung entsprechend       *}
{*         der obigen Liste                                        *}
{*      Zeile : int ; Zeile, in der die Fehlermeldung ange-        *}
{*         zeigt werden soll                                       *}
{*      Spalte: int; Spalte, in der die Fehlermeldung ange-        *}
{*         zeigt werden soll                                       *}
{*                                                                 *}
{*  Seiteneffekte: Aufruf von MEMugSoftwareError                   *}
{*                                                                 *}
{*******************************************************************/
 
#ifdef __STDC__
void MEMugWarning(int WarningNumber)
{ MEMugSoftwareError(1);
#else /* ! __STDC__ */
void MEMugWarning( WarningNumber )
int WarningNumber;
  { MEMugSoftwareError(1);
#endif /* ! __STDC__ */
  }
  
/*******************************************************************}
{*                                                                 *}
{*  Prozedur: MEMUGRecoverableError   Version: 13/12/90            *}
{*                                                                 *}
{*******************************************************************}
{*                                                                 *}
{*  Klassifizierung: Globale Prozedur                              *}
{*                                                                 *}
{*  Funktionsbeschreibung:                                         *}
{*     Diese Prozedur setzt eine Fehlermeldung ab und kehrt zum    *}
{*     Aufrufer zurueck. Es sind folgende Meldungen implementiert: *}
{*                                                                 *}
{*       R1: Integerdeklaration ist inkompatibel zu ReturnInt      *}
{*       R2: decode_id mit ungueltiger Nummer versorgt             *}
{*       R3: Integernummer zu gross                                *}
{*       R4: Steuercodes muessen kleiner als 256 sein              *}
{*       R5: Fliesskommazahlen sind nicht erlaubt                  *}
{*       R6: Ungueltiges Token                                     *}
{*       R7: Include File nicht gefunden, Anweisung ignoriert      *}
{*       R8: Stringdeklaration inkompatibel zu ReturnString        *}
{*                                                                 *}
{*-----------------------------------------------------------------*}
{*                                                                 *}
{*  Eingabeparameter:                                              *}
{*      ErrorNumber : int; Nummer des Fehlers entsprechend         *}
{*         der obigen Liste                                        *}
{*                                                                 *}
{*******************************************************************/
 
#ifdef __STDC__
void MEMugRecoverableError(int ErrorNumber)
{ printf("\n+++ Fehler R%d: ",ErrorNumber);
#else /* ! __STDC__ */
void MEMugRecoverableError( ErrorNumber )
int ErrorNumber;
  { printf("\n+++ Fehler R%d: ",ErrorNumber);
#endif /* ! __STDC__ */
    switch( ErrorNumber )
      { case 1 : printf("Integerdeklaration ist inkompatibel zu ReturnInt");
                 break;
        case 2 : printf("decode_id mit ungueltiger Nummer versorgt");
                 break;
        case 3 : printf("Integernummer zu gross");
                 break;
        case 4 : printf("Steuercodes muessen kleiner als 256 sein");
                 break;
        case 5 : printf("Fliesskommazahlen sind nicht erlaubt");
                 break;
        case 6 : printf("Ungueltiges Token");
                 break;
        case 7 : printf("Include File nicht gefunden, Anweisung ignoriert");
                 break;
        case 8 : printf("Stringdeklaration inkompatibel zu ReturnString");
                 break;
      }
    printf("\nDer Scanlauf wird fortgesetzt!\n");
  }

/*******************************************************************}
{*                                                                 *}
{*  Prozedur: MEMUGFatalError         Version: 13/12/90            *}
{*                                                                 *}
{*******************************************************************}
{*                                                                 *}
{*  Klassifizierung: Globale Prozedur                              *}
{*                                                                 *}
{*  Funktionsbeschreibung:                                         *}
{*     Diese Prozedur setzt eine Fehlermeldung ab und bricht ab    *}
{*     Es sind folgende Meldungen implementiert:                   *}
{*                                                                 *}
{*       R1: Verschachtelung der Include-Files tiefer als erlaubt! *}
{*       R2: Mehr Identifier, als erlaubt!                         *}
{*                                                                 *}
{*-----------------------------------------------------------------*}
{*                                                                 *}
{*  Eingabeparameter:                                              *}
{*      ErrorNumber : int; Nummer des Fehlers entsprechend         *}
{*         der obigen Liste                                        *}
{*                                                                 *}
{*  Seiteneffekte:                                                 *}
{*      Programm wird mit ReturnCode = 1 abgebrochen               *}
{*                                                                 *}
{*******************************************************************/
 
#ifdef __STDC__
void MEMugFatalError(int ErrorNumber)
{ printf("\n!!! Fehler F%d: ",ErrorNumber);
#else /* ! __STDC__ */
void MEMugFatalError( ErrorNumber )
int ErrorNumber;
  { printf("\n!!! Fehler F%d: ",ErrorNumber);
#endif /* ! __STDC__ */
    switch( ErrorNumber )
      { case 1 : printf("Verschachtelung der Include-Files tiefer als erlaubt!");
                 break;
        case 2 : printf("Mehr Identifier, als erlaubt!");
                 break;
      }
    printf("\nDie Compilierung wird abgebrochen!\n");
    exit(1);
  }
 
/*******************************************************************}
{*                                                                 *}
{*  Prozedur: MEMUGSoftwareError      Version: 13/12/90            *}
{*                                                                 *}
{*******************************************************************}
{*                                                                 *}
{*  Klassifizierung: Globale Prozedur                              *}
{*                                                                 *}
{*  Funktionsbeschreibung:                                         *}
{*     Diese Prozedur setzt eine Fehlermeldung ab und bricht ab    *}
{*     Es sind folgende Meldungen implementiert:                   *}
{*                                                                 *}
{*       S1: MugWarning aufgerufen                                 *}
{*       S2: Open_buffer ohne geoeffnetes Hauptfile aufgerufen     *}
{*                                                                 *}
{*-----------------------------------------------------------------*}
{*                                                                 *}
{*  Eingabeparameter:                                              *}
{*      ErrorNumber : int; Nummer des Fehlers entsprechend         *}
{*         der obigen Liste                                        *}
{*                                                                 *}
{*  Seiteneffekte:                                                 *}
{*      Programm wird mit ReturnCode = 2 abgebrochen               *}
{*                                                                 *}
{*******************************************************************/
 
#ifdef __STDC__
void MEMugSoftwareError(int ErrorNumber)
{ printf("\n!!! Fehler S%d: ",ErrorNumber);
#else /* ! __STDC__ */
void MEMugSoftwareError( ErrorNumber )
int ErrorNumber;
  { printf("\n!!! Fehler S%d: ",ErrorNumber);
#endif /* ! __STDC__ */
    switch( ErrorNumber )
      { case 1 : printf("MugWarning aufgerufen!");
                 break;
        case 2 : printf("Open_buffer ohne geoeffnetes Hauptfile aufgerufen!");
                 break;
      }
    printf("\nDie Compilierung wird abgebrochen!\n");
    exit(2);
  }
