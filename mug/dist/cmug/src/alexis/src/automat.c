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
{*  Segment: automat.c                                             *}
{*  Version: 20/05/91                                              *}
{*                                                                 *}
{*  Sprache: C                                                     *}
{*                                                                 *}
{*-----------------------------------------------------------------*}
{*                                                                 *}
{*  Beschreibung:                                                  *}
{*    Diese Segment bildet das eigentliche Hauptprogramm des       *}
{*    Scanners. Es wird vom Parser bzw. dem Parser-Interface auf-  *}
{*    gerufen und kehrt wieder zurueck, wenn entweder ein Token    *}
{*    erkannt wurde, das nicht mit ignore deklariert wurde, oder   *}
{*    wenn der gesamte Quelltext gescannt wurde. Das Segment stellt*}
{*    drei globale Prozeduren zur Verfuegung: Init_Automat,        *}
{*    scan_tokens und ExitAutomat. Die weiter unten beschrieben    *}
{*    werden.                                                      *}
{*       Bei der Generierung des Scanners wird in dieses Segment   *}
{*    die von ALEXIS generierte Tabelle textuell eingebunden und   *}
{*    dann uebersetzt. Es ist das einzige Segment, das Zugriff auf *}
{*    Elemente aus der Tabelle hat. Der Weg, dieses Seggment bei   *}
{*    jeder Generierung neu zu uebersetzen, wurde gewaehlt, um die *}
{*    Datenstrukturen der Tabelle nicht zu kompliziert zu gestalten*}
{*    und nicht auf schwer verstaendliche Tricks bei der Deklara-  *}
{*    tion zurueckgreifen zu muessen.                              *}
{*       Wird mit der DEBUG-Option generiert, so wird statt dieses *}
{*    Segments das Segment AUTDEBUG uebersetzt, das zusaetzlich    *}
{*    noch Routinen zur Dokumentation der Vorgaenge innerhalb des  *}
{*    Automaten enthaelt.                                          *}
{*                                                                 *}
{*  Inhalt:                                                        *}
{*                                                                 *}
{*     Interne Routinen:                                           *}
{*                                                                 *}
{*        function get_next_state                                  *}
{*                                                                 *}
{*     Globale Routinen:                                           *}
{*                                                                 *}
{*        procedure Init_Automat                                   *}
{*                                                                 *}
{*        procedure scan_tokens                                    *}
{*                                                                 *}
{*        procedure ExitAutomat                                    *}
{*                                                                 *}
{*-----------------------------------------------------------------*}
{*                                                                 *}
{*                 M O D I F I K A T I O N E N                     *}
{*=================================================================*}
{* Datum      modifiziert von    Beschreibung der Modifikation     *}
{*=================================================================*}
{*                                                                 *}
{*******************************************************************/

#define version "30/1/91/FrEi"

#include <stdio.h>

#include "buffer.h"
#include "table.h"
#include "actions.h"
#include "scan.h"
#include "automat.h"
#include "automat_proc.h"

#include "cdebug.h"

#define Fangzustand 0
#define Startzustand 1
#define NoAction 0

static TStateType state;



/*******************************************************************}
{*                                                                 *}
{*  Prozedur: get_next_state          Version: 20/05/91            *}
{*                                                                 *}
{*******************************************************************}
{*                                                                 *}
{*  Klassifizierung: Interne Funktion                              *}
{*                                                                 *}
{*  Funktionsbeschreibung:                                         *}
{*      Diese Funktion ermittelt aus der komprimierten Automaten-  *}
{*      tabelle zu einem gegebenen Zustand und Ereignis den        *}
{*      Folgezustand. Es ist die entrekursivierte Fassung der      *}
{*      Funktion "nextstate", die beschrieben ist in:              *}
{*                                                                 *}
{*         AHO, SETHI, ULLMAN: "Compilers; Principles, Techniques  *}
{*         and Tools"; Addison Wesley 1986, Seite 145              *}
{*                                                                 *}
{*-----------------------------------------------------------------*}
{*                                                                 *}
{*  Eingabeparameter:                                              *}
{*      gnEvent: TEventType; Ist die Ereignisklasse, zu der das    *}
{*          Ereignis gehoert. Diese Eventklasse muss vor dem Auf-  *}
{*          ruf der von ALEXIS generierten und in TABLE COPY ent-  *}
{*          haltenen Tabelle Char_Table entnommen werden. Der Typ  *}
{*          TEventType ist ebenfalls in TABLE enthalten.           *}
{*      gnState: TStateType: Zustand, in dem sich der Automat mo-  *}
{*          mentan befindet. Der Typ TStateType ist in TABLE COPY  *}
{*          deklariert                                             *}
{*                                                                 *}
{*  Ausgabeparameter:                                              *}
{*      Ergebnis: TStateType; Gibt den Folgezustand an.            *}
{*                                                                 *}
{*-----------------------------------------------------------------*}
{*                                                                 *}
{*  Lokale Variablen:                                              *}
{*      gnoffset: TEdgeType; Gibt den Wert an, der auf gnEvent     *}
{*          addiert werden muss, um in der next-Tabelle den zu.    *}
{*          hoerigen Eintrag zu finden.                            *}
{*      gnNewState: TStateType: Enthaelt den Zustand, der als Basis*}
{*          fuer die Suche verwendet wurde. Wird mit gnState vor-  *}
{*          besetzt und dann jeweils mit Werten aus Default        *}
{*          aktualisiert.                                          *}
{*                                                                 *}
{*******************************************************************/

#ifdef __STDC__
static TStateType get_next_state(TEventType gnEvent, TStateType gnState)
#else /* ! __STDC__ */
static TStateType get_next_state(gnEvent,gnState)
TEventType gnEvent;
TStateType gnState;
#endif /* ! __STDC__ */
{ TEdgeType gnOffset;
  TStateType gnNewState;
  _BEGIN_
  gnNewState = gnState;
  gnOffset = ( Base[gnNewState] + gnEvent) % (TmaxEdge + 1);
  while ( (Check[gnOffset] != gnNewState) &&
          (gnNewState != Fangzustand) )
     {  gnNewState = Default[gnNewState];
        gnOffset = ( Base[gnNewState] + gnEvent) % (TmaxEdge + 1);
     };
  _RETURN_
  if (gnNewState != Fangzustand)
     return(Next[gnOffset]);
   else return(Fangzustand);
}
 
 
/*******************************************************************}
{*                                                                 *}
{*  Prozedur: Init_Automat            Version: 20/05/91            *}
{*                                                                 *}
{*******************************************************************}
{*                                                                 *}
{*  Klassifizierung: Globale Prozedur                              *}
{*                                                                 *}
{*  Funktionsbeschreibung:                                         *}
{*      Initialisiert den Automaten, indem der aktuelle Zustand    *}
{*      mit dem Startzustand vorbesetzt wird.                      *}
{*                                                                 *}
{*-----------------------------------------------------------------*}
{*                                                                 *}
{*  Seiteneffekte: state                                           *}
{*                                                                 *}
{*******************************************************************/

#ifdef __STDC__
void AUTInit_Automat(void)
#else /* ! __STDC__ */
void AUTInit_Automat()
#endif /* ! __STDC__ */
{ state = Startzustand;
#ifdef DEBUG 
      printf("Initialisierung des Automaten: Version %s\n",version);
#endif
}


/*******************************************************************}
{*                                                                 *}
{*  Prozedur: scan_tokens             Version: 20/05/91            *}
{*                                                                 *}
{*******************************************************************}
{*                                                                 *}
{*  Klassifizierung: Globale Prozedur                              *}
{*                                                                 *}
{*  Funktionsbeschreibung:                                         *}
{*      Diese Prozedur ist die eigentliche Hauptroutine des er-    *}
{*      zeugten Scanners. Sie liest die Eingabezeichen ueber die   *}
{*      Pufferverwaltung ein und durchlauft den Automaten mit      *}
{*      ihnen. Wird ein Endzustand erkannt, so wird die Position   *}
{*      und Aktionsnummer gespeichert und der Lauf fortgesetzt.    *}
{*      Beim Erreichen des Fangzustandes wird dann die Aktion, die *}
{*      zur gespeicherten Aktionsnummer gehoert, ausgefuehrt und   *}
{*      der Eingabepuffer auf die gespeicherte Position zurueckge- *}
{*      setzt. Wurde die Aktion ohne ignore spezifiziert, so ist   *}
{*      die Routine beendet, sonst wird mit dem naechsten Token    *}
{*      fortgefahren.                                              *}
{*         Wird das Ende des Files erreicht, so wird die Funktion  *}
{*      close_buffer der Pufferverwaltung aufgerufen. Stellt       *}
{*      diese fest, dass das Ende des Hauptfiles erreicht wurde,   *}
{*      so wird end_of_scan gesetzt und die Aktion End_Action      *}
{*      aufgerufen, anschliessend die Routine verlassen.           *}
{*         Wenn der Fangzustand erreicht wird, ohne dass ein       *}
{*      Endzustand durchlaufen wurde, so wird die Aktion           *}
{*      Error_Action aufgerufen und der Pufferzeiger auf das       *}
{*      zweite Zeichen des Tokens gesetzt. Es wird also genau ein  *}
{*      Zeichen uebersprungen und der Scanlauf fortgefuehrt. Der   *}
{*      Parser erhaelt von diesem Vorgang keine Kenntnis, wenn     *}
{*      dies nicht im Rahmen der Error_Action passiert.            *}
{*                                                                 *}
{*-----------------------------------------------------------------*}
{*                                                                 *}
{*  Eingabeparameter:                                              *}
{*     quellfile: text; Gibt den Quellfile an, der den Haupttext   *}
{*        enthaelt. Dieser File muss vor dem ersten Aufruf ge-     *}
{*        oeffnet und zurueckgesetzt werden und darf zwischen      *}
{*        weiteren Aufrufen nicht veraendert werden. Auch darf     *}
{*        kein anderes Programm auf diesen File zugreifen.         *}
{*                                                                 *}
{*  Seiteneffekte:                                                 *}
{*     Der Quellfile, state sowie die gesamte Pufferverwaltung     *}
{*     werden veraendert. Ausserdem koennen die Aktionsroutinen    *}
{*     Seiteneffekte verursachen                                   *}
{*                                                                 *}
{*-----------------------------------------------------------------*}
{*                                                                 *}
{*  Lokale Variablen:                                              *}
{*     ch: char; In dieser Variablen wird das als letztes gelesene *}
{*        Zeichen zwischengespeichert                              *}
{*     action_nr: TActionType; Enthaelt die Aktionsnummer, die mit *}
{*        dem zuletzt erkannten Token assoziiert ist. Geraet der   *}
{*        Automat in den Fangzustand, so enthaelt diese Variable   *}
{*        somit die auszufuehrende Aktion. Ist in action_nr noch   *}
{*        der Initialisierungswert NoAction enthalten, so ist der  *}
{*        Eingabetext zu keinem Token zugehoerig.                  *}
{*     first: boolean; Ist TRUE, wenn das erste Zeichen eines      *}
{*        Tokens gescannt wird. Diese Variable wird benoetigt, um  *}
{*        im Fehlerfall den Puffer um genau ein Zeichen weiter-    *}
{*        schalten zu koennen und so eine Endlosschleife durch     *}
{*        den Backtracking-Mechanismus zu verhindern.              *}
{*     end_of_scan: boolean; Diese Variable ist TRUE, wenn das     *}
{*        Ende des Hauptfiles erreicht wurde. Sie ist ein Abbruch- *}
{*        kriterium des Scanners.                                  *}
{*                                                                 *}
{*******************************************************************/

#ifdef __STDC__
void AUTScan_Tokens(Token tok)
#else /* ! __STDC__ */
void AUTScan_Tokens(tok)
Token tok;
#endif /* ! __STDC__ */
{ char ch;
  TActionType action_nr;
  int first,end_of_scan;  /*BOOL*/
  _BEGIN_

#ifdef DEBUG
printf("[0]STATE: %d\n",state);
#endif

  abort_scan = 0;
  end_of_scan = 0;
  action_nr = NoAction;
  first = 1;

  ch = BUFGet_Next_Char();

  /* BUFSet_Buffer_Start(); */

#ifdef DEBUG
printf("[0]CHAR : >%c<\n",ch);
#endif

  do {
     if (ch!= EOF_CHAR)
       { state = get_next_state(char_table[(int)ch],state);

#ifdef DEBUG
printf("[1]STATE: %d\n",state);
#endif

         if ( (TAction[state] > NoAction) || first )
            { BUFSet_Token_End();
              action_nr = TAction[state];
              first = 0;
            }
       }
     if ( (state==Fangzustand) || (ch==EOF_CHAR) )
       { if ( (ch!=EOF_CHAR) || (action_nr!=NoAction) )
           { if (action_nr!=NoAction)
                 ACTDo_Action(tok,action_nr);
               else ACTError_Action();
           }
           else end_of_scan = BUFClose_Buffer();
         BUFSet_Buffer_Start();
         state = Startzustand;

#ifdef DEBUG
printf("[2]STATE: %d\n",state);
#endif

         action_nr = NoAction;
         first = 1;
       }
     if (!abort_scan)
       {
       ch = BUFGet_Next_Char();

#ifdef DEBUG
printf("[1]CHAR : >%c<\n",ch);
#endif
       }

     } while (!(abort_scan || end_of_scan));
  if (end_of_scan)
     ACTEnd_Action(tok);
  _END_
}
         
    
/*
**=====================================================================
** Funktion: void AUTExit_Automat( void )
**---------------------------------------------------------------------
** Dummy-Funktion
**=====================================================================
*/

#ifdef __STDC__
void AUTExit_Automat(void)
#else /* ! __STDC__ */
void AUTExit_Automat()
#endif /* ! __STDC__ */
{}
