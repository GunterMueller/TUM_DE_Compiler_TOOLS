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
{*  Segment: Buffer                                                *}
{*  Version: 20/05/91                                              *}
{*                                                                 *}
{*  Sprache: C                                                     *}
{*                                                                 *}
{*-----------------------------------------------------------------*}
{*                                                                 *}
{*  Beschreibung:                                                  *}
{*    Die in diesem Segment enthaltenen Prozeduren und Funktionen  *}
{*    bilden das Interface zwischen dem Eingabefile und dem Auto-  *}
{*    maten bzw. den Benutzeraktionen. Sie realisieren einen po-   *}
{*    tentiell unendlich groaen Eingabepuffer, in dem die Position *}
{*    des naechsten auszulesenden Zeichens jederzeit wieder auf    *}
{*    die zuletzt gekennzeichnete Position innerhalb des Tokens    *}
{*    zurueckgesetzt werden kann. Die Schnittstelle nach aussen    *}
{*    ist in zwei Teile aufgeteilt: Die Schnittstelle zum Automa-  *}
{*    ten, die einen Backtracking-faehigen Eingabepuffer beliebiger*}
{*    Laenge realisiert und die Schnittstelle zu den Benutzeraktio-*}
{*    nen, die den Zugriff auf den Tokentext ermglicht und Posi-  *}
{*    tionsinformationen zur Verfuegung stellt.                    *}
{*       Der Puffer ist realisiert als Liste von Strings. Jeder    *}
{*    String enthaelt genau eine Zeile des Eingabetextes. Fnf     *}
{*    Pointer regeln den Zugriff:                                  *}
{*      buffer_start: zeigt auf das erste gueltige Zeichen im      *}
{*         Puffer. Dies ist auch das erste Zeichen des z.Zt. ge-   *}
{*         lesenen Tokens.                                         *}
{*      token_ende: Zeigt auf das letzte Zeichen, das mit Sicher-  *}
{*         heit noch zum aktuellen Token gehoert. Dieser Pointer    *}
{*         wird vom Automaten jedesmal dann mit Hilfe der Proze-   *}
{*         dur set_token_end auf die momentane Position gesetzt,   *}
{*         wenn der Automat in einen Endzustand kommt. Ist der     *}
{*         Fangzustand erreicht, so zeigt der Pointer auf das      *}
{*         Ende des Tokens.                                        *}
{*      position: Zeigt auf das Zeichen, das als nchstes gelesen  *}
{*         wird. Wurde ein Token erkannt, so wird dieser Pointer   *}
{*         vom Automaten mit der Prozedur set_token_start auf das  *}
{*         Zeichen hinter token_ende gesetzt.                      *}
{*      buffer_ende: Zeigt auf das letzte gueltige Zeichen im      *}
{*         Puffer. Wird versucht, ein Zeichen zu lesen, wenn po-   *}
{*         sition auf buffer_ende zeigt, so wird automatisch       *}
{*         weiterer Text nachgeladen.                              *}
{*                                                                 *}
{*    Um Include-Files zu ermoeglichen, sind diese vier Pointer    *}
{*    als Arrays ausgelegt, wobei jedes Array-Element eine Include-*}
{*    ebene darstellt. Welche Ebene momentan aktiv ist, ist in der *}
{*    Variablen IncPtr enthalten. Das wechseln der Ebene erfolgt   *}
{*    durch vom Automaten bzw. den Aktionsroutinen aus durch die   *}
{*    beiden Routinen open_buffer und close_buffer.                *}
{*       Schliesslich existiert  noch der Pointer token_start, der *}
{*    beim zeichenweisen Auslesen eines Tokens die momentane       *}
{*    Position angibt.                                             *}
{*       Fuer die Anwenderroutinen stehen zwei verschiedene Mecha- *}
{*    nismen zur Verfgung, um den Text des Tokens zu erhalten:    *}
{*    Mit der Funktion sget_token (bzw. UsGetUC_token) wird das    *}
{*    Token als String zurueckgegeben. Diese Methode funktioniert  *}
{*    Allerding nur, solange das Token kuerzer ist, als die        *}
{*    Konstante MaxTokLength angibt. Ansonsten muss das Token      *}
{*    zeichenweise mit den beiden Funktionen get_first_token_char/ *}
{*    cget_token_char (bzw. UfGetUC_first_token_char/              *}
{*    UcGetUc_token_char) geholt werden. Die Token werden unab-    *}
{*    hngig von der IgnoreCase-Option beim Generieren immer in    *}
{*    der Schwreibweise bergeben, in der sie im Quelltext stehen. *}
{*    Soll die Gross-/Kleinschreibung im Quelltext nicht berueck-  *}
{*    sichtigt werden, so steht ein alternativer Funktionensatz    *}
{*    (oben in Klammern) zu Verfgung, der alle Kleinbuchstaben    *}
{*    in Grossbuchstaben umwandelt.                                *}
{*       Zwei weitere Funktionen stehen zur Verfgung, die An-     *}
{*    wenderroutinen die Mglichkeit geben, Informationen ueber    *}
{*    die Laenge des Tokens und dessen Position zu erhalten.       *}
{*                                                                 *}
{*                                                                 *}
{*  Inhalt:                                                        *}
{*                                                                 *}
{*  I. Interne Routinen                                            *}
{*                                                                 *}
{*    procedure read_buffer                                        *}
{*    procedure int_open_buffer                                    *}
{*                                                                 *}
{*  II. Globale Routinen                                           *}
{*  IIa. Puffer-Verwaltung                                         *}
{*                                                                 *}
{*    procedure open_buffer                                        *}
{*    function close_buffer                                        *}
{*                                                                 *}
{*  IIb. Routinen fuer den Automaten                               *}
{*                                                                 *}
{*    function get_next_char                                       *}
{*    procedure set_buffer_start                                   *}
{*    procedure set_token_end                                      *}
{*                                                                 *}
{*  IIc Routinen fuer die Anwenderroutinen                         *}
{*  IIc1. Routine fuer Zugriff auf das Originaltoken               *}
{*                                                                 *}
{*    function get_first_token_char                                *}
{*    function cget_token_char                                     *}
{*    function sget_token                                          *}
{*                                                                 *}
{*  IIc2. Routinen fuer Zugriff auf das Token in Grossbuchstaben   *}
{*                                                                 *}
{*    function UfGetUC_first_token_char                            *}
{*    function UcGetUC_token_char                                  *}
{*    function UsGetUC_token                                       *}
{*                                                                 *}
{*  IIc3. Routinen fuer Informatione ueber das Token.              *}
{*                                                                 *}
{*    function lget_token_length                                   *}
{*    function pget_position                                       *}
{*                                                                 *}
{*  III. Initialisierung und Exit:                                 *}
{*                                                                 *}
{*    procedure InitBuffer                                         *}
{*    procedure ExitBuffer                                         *}
{*                                                                 *}
{*-----------------------------------------------------------------*}
{*                                                                 *}
{*                 M O D I F I K A T I O N E N                     *}
{*=================================================================*}
{* Datum      modifiziert von    Beschreibung der Modifikation     *}
*===========================================================*}
{*                                                                 *}
{*                                                                 *}
{*******************************************************************/

#define version "22/1/91/FrEi"
/* #define DEBUG */
#include "buffer.h"
#include "buffer_proc.h"
#include "cdebug.h"
#include "strfunctions.h"


#include "alexmem.h"

/* #include <malloc.h> */

#ifdef __STDC__
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#endif

#include <stdio.h>

/* Bauernfeind: Prototypen, 8.6.93 */
#ifdef __STDC__
extern void MEMugFatalError(int);
#endif

/*******************************************************************}
{*                                                                 *}
{* Die folgenden Konstanten sind in der Datei BUFFER COPY dekla-   *}
{* riert:                                                          *}
{*                                                                 *}
{*    buffer_laenge = 255;                                         *}
{*    maxString = 256;                                             *}
{*                                                                 *}
{*      maxTokLength = 5000;   Maximale Laenge eines Tokens, das   *}
{*         mit sget_token (UsGetUc_token) geholt werden kann.      *}
{*                                                                 *}
{*      FnLength     = 32; Maximale Laenge eines Filenamens mit    *}
{*         Filetyp und Filemodus                                   *}
{*                                                                 *}
{*    maxInclude = 10;                                             *}
{*                                                                 *}
{*      eof_char = chr(26);     End of File Delimiter              *}
{*      eoln_char = chr(13);    End of Line Delimiter              *}
{*      eotok_char = chr(0);    End of Token Delimiter             *}
{*                                                                 *}
{*******************************************************************}
*/

struct buffer_block {
           struct varfilestring buffer_inhalt;
           int buffer_zeile;
           struct buffer_block *nachfolger; } ;

struct buffer_zeiger {
           struct buffer_block *block;
           int zeichen; /* 1..(buffer_laenge+1) */ };


static struct buffer_zeiger buffer_start[MAXINCLUDE],
                            token_ende[MAXINCLUDE],
                            position[MAXINCLUDE],
                            buffer_ende[MAXINCLUDE],
                            token_start;
FILE *quellfiles[MAXINCLUDE];
static char *quellname[MAXINCLUDE];
static int IncludePtr; /* 0..maxInclude */


/*******************************************************************}
{*                                                                 *}
{*  Prozedur: read_buffer             Version: 11/7/89/a           *}
{*                                                                 *}
{*******************************************************************}
{*                                                                 *}
{*  Klassifizierung: Interne Prozedur                              *}
{*                                                                 *}
{*  Funktionsbeschreibung:                                         *}
{*      Eroeffnet einen neuen Puffer-Block, haengt ihn an den      *}
{*      Puffer an, auf den buffer_ende zeigt, korrigiert           *}
{*      buffer_ende und besetzt den Puffer_block mit der naechsten *}
{*      Zeile im Eingabefile. Am Ende der Zeile wird noch das      *}
{*      Zeichen eoln_char angehaengt. Ist der Eingabefile am Ende  *}
{*      angelangt, so wird das Zeichen eof_char abgespeichert.     *}
{*                                                                 *}
{*-----------------------------------------------------------------*}
{*                                                                 *}
{*  Eingabeparameter:                                              *}
{*      qfile: text; File, aus dem der Puffer gelesen werden soll. *}
{*                                                                 *}
{*  Seiteneffekte:                                                 *}
{*      buffer_ende^.block.Nachfolger,                            *}
{*      buffer_ende                                                *}
{*                                                                 *}
{*******************************************************************}
*/

#ifdef __STDC__
static void Read_Buffer(FILE *qfile)  /* Bauernfeind: void eingefuegt */
#else /* ! __STDC__ */                /* 8.6.93 */
static void Read_Buffer(qfile)        /* Bauernfeind: void eingefuegt */
FILE *qfile;
#endif /* ! __STDC__ */
{ struct varfilestring eof_str;
  int i,c;
_BEGIN_
  eof_str.body[0]=EOF_CHAR;
  eof_str.length=1;
  buffer_ende[IncludePtr].block->nachfolger = 
            (struct buffer_block *)MEMAlloc(sizeof(struct buffer_block));
  buffer_ende[IncludePtr].block->nachfolger->buffer_zeile = 
         buffer_ende[IncludePtr].block->buffer_zeile + 1;
  buffer_ende[IncludePtr].block->nachfolger->nachfolger = NULL;
  buffer_ende[IncludePtr].block = buffer_ende[IncludePtr].block->nachfolger;
  i=0;
  c=fgetc(qfile);
                        /*  buffer_ende[IncludePtr].block->buffer_inhalt.body[0]=fgetc(qfile);  */
  if ( !feof(qfile) ) 
   {  while( c!=EOLN_CHAR && !feof(qfile) )
        { buffer_ende[IncludePtr].block->buffer_inhalt.body[i++]=c;
          c=fgetc(qfile);
        }
      buffer_ende[IncludePtr].block->buffer_inhalt.body[i]='\n';  
      buffer_ende[IncludePtr].block->buffer_inhalt.length = i+1;
    }
   else
    { _TRA_ "EOF reached\n" _TRE_
      buffer_ende[IncludePtr].block->buffer_inhalt = eof_str;
    }
#ifdef debug
    for(i=0;i<buffer_ende[IncludePtr].block->buffer_inhalt.length;printf("%c",
    buffer_ende[IncludePtr].block->buffer_inhalt.body[i++]));
#endif
    _TRA_ "\n length: %d\n",buffer_ende[IncludePtr].block->buffer_inhalt.length _TRE_
_END_
}



/*******************************************************************}
{*                                                                 *}
{*  Prozedur: open_buffer             Version: 11/7/89/a           *}
{*                                                                 *}
{*******************************************************************}
{*                                                                 *}
{*  Klassifizierung: Globale Prozedur fuer Anwenderroutinen        *}
{*                                                                 *}
{*  Funktionsbeschreibung:                                         *}
{*      Diese Prozedur dient dazu, einen Include-File zu eroeffnen.*}
{*      Sie ueberprueft lediglich, ob die Eroeffnung des Include-  *}
{*      Files legal ist und ruft dann int_open_buffer auf.         *}
{*                                                                 *}
{*-----------------------------------------------------------------*}
{*                                                                 *}
{*  Eingabeparameter:*}
{*      ob_quellfilename : string(FnLength); Name des Includefiles *}
{*          siehe auch Eingabeparameter von int_open_buffer        *}
{*                                                                 *}
{*  Seiteneffekte: siehe int_open_buffer                           *}
{*                                                                 *}
{*-----------------------------------------------------------------*}
{*                                                                 *}
{*  Lokale Variablen:                                              *}
{*      dummy : text; Diese Variable dient lediglich dazu, die     *}
{*          Schnittstelle von int_opne_buffer zu befriedigen.      *}
{*                                                                 *}
{*******************************************************************}
*/

#ifdef __STDC__
void BUFOpenBuffer(char *filename)
#else /* ! __STDC__ */
void BUFOpenBuffer( filename )
char *filename;
#endif /* ! __STDC__ */
{ _BEGIN_
  
  struct buffer_block *dummy_buffer;

  _TRA_ "Filename: %s\n",filename _TRE_

  if (IncludePtr==MAXINCLUDE) MEMugFatalError(1);

  ++IncludePtr;

  if ((quellfiles[IncludePtr] = fopen(filename,"r")) == NULL)
    { printf("Dateifehler: %s\n",filename);
      exit(1);
    }
  dummy_buffer = (struct buffer_block *) MEMAlloc(sizeof(*dummy_buffer));
  buffer_ende[IncludePtr].block = dummy_buffer;
  buffer_ende[IncludePtr].block->buffer_zeile = 0;
  buffer_ende[IncludePtr].block->nachfolger = NULL;

  Read_Buffer(quellfiles[IncludePtr]);

  buffer_start[IncludePtr] = buffer_ende[IncludePtr];
  buffer_start[IncludePtr].zeichen = 0;

  token_ende[IncludePtr] = buffer_start[IncludePtr];
  position[IncludePtr] = buffer_start[IncludePtr];

  quellname[IncludePtr]=(char *)MEMAlloc( strlen(filename)+1 );
  strcpy( quellname[IncludePtr],filename );

  MEMFree(dummy_buffer);
_END_
}


/*******************************************************************}
{*                                                                 *}
{*  Prozedur:close_buffer             Version: 11/7/89/a           *}
{*                                                                 *}
{*******************************************************************}
{*                                                                 *}
{*  Klassifizierung: Globale Funktion fuer den Automaten           *}
{*                                                                 *}
{*  Funktionsbeschreibung:                                         *}
{*      Schliesst den Quellfile, der mit open_buffer eroeffnet     *}
{*      wurde und gibt den gesamten Speicherplatz, der noch fuer   *}
{*      den Puffer belegt ist, wieder frei. Es liegt in der Verant-*}
{*      wortung des Benutzers, dass alle Zeichen des Files gelesen *}
{*      wurden, eine Abpruefung findet nicht statt.                *}
{*                                                                 *}
{*-----------------------------------------------------------------*}
{*                                                                 *}
{*  Ausgabeparameter: Ergebnis: boolean;                           *}
{*      War der File ein Includefile, so wird als Funktionsergeb-  *}
{*      nis false geliefert, andernfalss ist der Scanlauf beendet  *}
{*      und es wird true zurueckgegeben.                           *}
{*                                                                 *}
{*  Seiteneffekte: IncludePtr                                      *}
{*                                                                 *}
{*-----------------------------------------------------------------*}
{*                                                                 *}
{*  Lokale Variablen:                                              *}
{*      cb_pointer : buffer_pointer; Dieser Pointer dient dazu,    *}
{*      die gesamte Kette der noch belegten Puffer zu loeschen-    *}
{*                                                                 *}
{*******************************************************************}
*/

#ifdef __STDC__
int BUFClose_Buffer(void)
#else /* ! __STDC__ */
int BUFClose_Buffer()
#endif /* ! __STDC__ */
{ struct buffer_block *cb_pointer;
  if (IncludePtr<2) return(1);
    else {
           fclose(quellfiles[IncludePtr]);
           while (buffer_start[IncludePtr].block != NULL)
              { cb_pointer = buffer_start[IncludePtr].block;
                buffer_start[IncludePtr].block = 
                     buffer_start[IncludePtr].block->nachfolger;
                MEMFree(cb_pointer);
              };
           --IncludePtr;
           return(0);
         };
}


/*******************************************************************}
{*                                                                 *}
{*  Prozedur: get_next_char           Version: 11/7/89/a           *}
{*                                                                 *}
{*******************************************************************}
{*                                                                 *}
{*  Klassifizierung: Globale Funktion fuer den Automaten           *}
{*                                                                 *}
{*  Funktionsbeschreibung:                                         *}
{*      Diese Funktion liest das naechste Zeichen aus dem Puffer.  *}
{*      Ist der Puffer bei eof angelangt,so wird eof_char zurueck- *}
{*      gegeben, sonst das Zeichen bei Position. Anschliessend wird*}
{*      Position inkrementiert.                                    *}
{*      Steht Position am Ende des letzten Pufferblocks, so wird   *}
{*      (fuer den Benutzer transparent) ein neuer Puffer nachge-   *}
{*      laden.                                                     *}
{*         Da das MUG-System keine Moeglichkeit bietet, in der     *}
{*      Scanner-initialisierung bereits die Puffer zu laden, muss  *}
{*      zusaetzlich Ueberprueft werden, ob der Puffer bereits ini- *}
{*      tialisiert wurde. Ist dies noch nicht geschehen, so wird   *}
{*      int_open_buffer aufgerufen.                                *}
{*                                                                 *}
{*-----------------------------------------------------------------*}
{*                                                                 *}
{*  Eingabeparameter:                                              *}
{*      gn_quellfile : text; Enthaelt den Hauptfile. Sind Include- *}
{*          files eroeffnet, so wird dieser Parameter ignoriert.   *}
{*          Andernfalls wird der neue Puffer aus diesem File gela- *}
{*          den.                                                   *}
{*                                                                 *}
{*  Ausgabeparameter: Ergebnis: char;                              *}
{*                                                                 *}
{*  Seiteneffekte:                                                 *}
{*     position,                                                   *}
{*     siehe auch read_buffer, int_open_buffer                     *}
{*                                                                 *}
{*******************************************************************}
*/

#ifdef __STDC__
char BUFGet_Next_Char(void)
#else /* ! __STDC__ */
char BUFGet_Next_Char(/* void */)

#endif /* ! __STDC__ */
{ char ergebnis;

 _BEGIN_

  if (position[IncludePtr].block->
           buffer_inhalt.body[position[IncludePtr].zeichen] != EOF_CHAR)
     { ergebnis =
          position[IncludePtr].block->
               buffer_inhalt.body[position[IncludePtr].zeichen];
       if (position[IncludePtr].block == buffer_ende[IncludePtr].block)
          { Read_Buffer(quellfiles[IncludePtr]);
          }

       ++position[IncludePtr].zeichen;

       if (position[IncludePtr].zeichen == 
               position[IncludePtr].block->buffer_inhalt.length)
          { position[IncludePtr].block = 
                  position[IncludePtr].block->nachfolger;
            position[IncludePtr].zeichen = 0;
          }
     }
  else { ergebnis = EOF_CHAR;
         _TRA_ "FILEENDE\n" _TRE_  }
     _TRA_ "ZEICHEN: %d %c\n",(int)ergebnis,ergebnis _TRE_
_RETURN_
/*  printf("==>%c<==\n",ergebnis);*/
  return(ergebnis);
}         


/*******************************************************************}
{*                                                                 *}
{*  Prozedur: set_buffer_start        Version: 11/7/89/a           *}
{*                                                                 *}
{*******************************************************************}
{*                                                                 *}
{*  Klassifizierung: Globale Prozedur fuer den Automaten           *}
{*                                                                 *}
{*  Funktionsbeschreibung:                                         *}
{*      Diese Prozedur setzt den Beginn des Puffer auf das Zeichen *}
{*      bei token_ende. Werden dabei Bloecke frei, so wird der     *}
{*      zugehoerige Heap freigegeben.                              *}
{*         Sie wird vom Automaten aufgerufen, bevor er mit dem     *}
{*      Scannen eines neuen Tokens beginnt                         *}
{*                                                                 *}
{*-----------------------------------------------------------------*}
{*                                                                 *}
{*  Seiteneffekte:                                                 *}
{*      position                                                   *}
{*      buffer_start                                               *}
{*-----------------------------------------------------------------*}
{*                                                                 *}
{*  Lokale Variablen:                                              *}
{*      sb_pointer : buffer_pointer; Dient zum Abarbeiten der      *}
{*         Pufferkette, wenn ein Block freigegeben wird.           *}
{*                                                                 *}
{*******************************************************************}
procedure set_buffer_start;
  var sb_pointer : buffer_pointer;
  begin
    position(.IncludePtr.) := token_ende(.IncludePtr.);
    with buffer_start(.IncludePtr.)
    do begin
      while block <> position(.IncludePtr.).block
      do begin
        sb_pointer := block;
        block := block^.nachfolger;
        dispose(sb_pointer);
        end;
      zeichen := position(.IncludePtr.).zeichen;
      end;
    end;
*/

#ifdef __STDC__
void BUFSet_Buffer_Start(void)
#else /* ! __STDC__ */
void BUFSet_Buffer_Start()
#endif /* ! __STDC__ */
{ struct buffer_block *sb_pointer;
  position[IncludePtr] = token_ende[IncludePtr];
  while (buffer_start[IncludePtr].block != position[IncludePtr].block)
     {  sb_pointer = buffer_start[IncludePtr].block;
        buffer_start[IncludePtr].block = buffer_start[IncludePtr].block->nachfolger;
        MEMFree(sb_pointer);
     }
  buffer_start[IncludePtr].zeichen = position[IncludePtr].zeichen;
}


/*******************************************************************}
{*                                                                 *}
{*  Prozedur: set_token_end           Version: 11/7/89/a           *}
{*                                                                 *}
{*******************************************************************}
{*                                                                 *}
{*  Klassifizierung: Globale Prozedur fuer den Automaten           *}
{*                                                                 *}
{*  Funktionsbeschreibung:                                         *}
{*      Diese Prozedur setzt den Token_end auf die momentane       *}
{*      Position.                                                  *}
{*         Sie wird vom Automat aufgerufen, wenn dieser in einen   *}
{*      Endzustand kommt. Nach dem Erreichen des Fangzustandes     *}
{*      steht token_ende dann auf dem letzten Zeichen des Tokens   *}
{*                                                                 *}
{*-----------------------------------------------------------------*}
{*                                                                 *}
{*  Seiteneffekte: IncludePtr                                      *}
{*                                                                 *}
{*******************************************************************}
procedure set_token_end;
  begin
    token_ende(.IncludePtr.) := position(.IncludePtr.);
    end;
*/

#ifdef __STDC__
void BUFSet_Token_End(void)
#else /* ! __STDC__ */
void BUFSet_Token_End()
#endif /* ! __STDC__ */
{ token_ende[IncludePtr] = position[IncludePtr];
}


/*******************************************************************}
{*                                                                 *}
{*  Prozedur: sget_token              Version: 11/7/89/a           *}
{*                                                                 *}
{*******************************************************************}
{*                                                                 *}
{*  Klassifizierung: Globale Prozedur fuer Anwenderroutinen        *}
{*                                                                 *}
{*  Funktionsbeschreibung:                                         *}
{*      Diese Funktion liest das zuletzt erkannte Token vollstaen- *}
{*      dig ein und uebergibt es als String an den Aufrufer. Ist   *}
{*      das Token laenger, als MaxTokLength, so werden nur die     *}
{*      ersten MaxTokLength Zeichen uebergeben.                    *}
{*                                                                 *}
{*-----------------------------------------------------------------*}
{*                                                                 *}
{*  Ausgabeparameter: Ergebnis: string(MaxTokLength); Tokentext    *}
{*                                                                 *}
{*-----------------------------------------------------------------*}
{*                                                                 *}
{*  Lokale Variablen:                                              *}
{*     gtToken : string(MaxTokLength); Das Token ist u.U. ueber    *}
{*        mehrere Pufferblcke verteilt. Es wird in dieser Varia- *}
{*        blen zusammengesetzt                                     *}
{*     gtBlock: buffer_pointer; Dieser Pointer zeigt auf den Puf-  *}
{*        ferblock, aus dem der naechste Teil fuer gtToken geholt  *}
{*        wird.                                                    *}
{*     gtOffset: integer32; Enthaelt das naechste Zeichen, das in  *}
{*        gtToken gesammelt werden muss                            *}
{*     gtLength: integer32; Enthaelt die Laenge des Blocks, der auf*}
{*        einmal in gtToken kopiert werden kann.                   *}
{*                                                                 *}
{*******************************************************************}
*/

#ifdef __STDC__
void BUFGetToken(char *Token)
#else /* ! __STDC__ */
void BUFGetToken(Token)
char *Token;
#endif /* ! __STDC__ */
{ struct buffer_block *block,*lastblock;
  int zeichen,lastzeichen,len;

  char *tok,*body;

  _BEGIN_

  block=buffer_start[IncludePtr].block;             /* von (block,zeichen) */
  zeichen=buffer_start[IncludePtr].zeichen;
  
  lastblock=token_ende[IncludePtr].block;           /* bis (lastblock,lastzeichen) */
  lastzeichen=token_ende[IncludePtr].zeichen;       /* geht das Token */

  tok=Token;

  while(block!=lastblock)                            /* Rest des Anfangsblocks    */
    { len=block->buffer_inhalt.length-zeichen;       /* und alle Folgebloecke     */
      body=block->buffer_inhalt.body+zeichen;        /* bis auf den letzten Block */
      memcpy(tok,body,len);                          /* anhaengen                 */
      tok+=len;
      zeichen=0;
      block=block->nachfolger;
    }
  len=lastzeichen-zeichen;                           /* Zeichen des letzten Blocks   */
  body=lastblock->buffer_inhalt.body+zeichen;        /* anhaengen                    */
  memcpy(tok,body,len);                              /*! zeichen ist NICHT IMMER 0 ! */     
  tok+=len;
  *tok='\0';
 
  _TRA_ "GetToken liefert %s\n",Token _TRE_ 
  _END_
  }


/*******************************************************************}
{*                                                                 *}
{*  Prozedur: UsGetUC_token           Version: 11/7/89/a           *}
{*                                                                 *}
{*******************************************************************}
{*                                                                 *}
{*  Klassifizierung: Globale Prozedur fuer Anwenderroutinen        *}
{*                                                                 *}
{*  Funktionsbeschreibung:                                         *}
{*      Diese Funktion ist identisch mit sGet_Token, nur dass      *}
{*      saemtliche Kleinbuchstaben in dem Token in Grossbuchstaben *}
{*      umgewandelt werden.                                        *}
{*                                                                 *}
{*-----------------------------------------------------------------*}
{*                                                                 *}
{*  Ausgabeparameter: Ergebnis: string(MaxTokLength); Tokentext    *}
{*                                                                 *}
{*-----------------------------------------------------------------*}
{*                                                                 *}
{*  Lokale Variablen:                                              *}
{*      UgErg: string(MaxTokLength); Enthaelt das Token waehrend   *}
{*         der Umwandlung von Klein- in Grossbuchstaben            *}
{*      UgIndex: integer32; Laufvariable zur Umwandlung            *}
{*                                                                 *}
{*******************************************************************}
*/

#ifdef __STDC__
void BUFGetUCToken(char *Token)
{
#else /* ! __STDC__ */
void BUFGetUCToken( Token )
char *Token;
  {
#endif /* ! __STDC__ */
  char *p;
  BUFGetToken( Token );
  for( p=Token ; *p!='\0' ; ++p )
    { if( *p>='a' && *p<='z' )
      { *p +='A'-'a';
      }
    }
  }

/*******************************************************************}
{*                                                                 *}
{*  Prozedur: lget_token_length       Version: 11/7/89/a           *}
{*                                                                 *}
{*******************************************************************}
{*                                                                 *}
{*  Klassifizierung: Globale Funktion fuer Anwenderroutinen        *}
{*                                                                 *}
{*  Funktionsbeschreibung:                                         *}
{*      Diese Funktion gibt die Laenge des aktuellen Tokens an den *}
{*      Aufrufer zurueck, falls diese kleiner als MaxInt ist. Sonst*}
{*      wird Maxint abgeliefert.                                   *}
{*         Dazu wird die Laenge der belgten Pufferblocke ermittelt,*}
{*      wobei der jeweils erste und letzte Block nur soweit ge-    *}
{*      zaehlt wird, wie er vom Token belegt wird.                 *}
{*                                                                 *}
{*-----------------------------------------------------------------*}
{*                                                                 *}
{*  Ausgabeparameter: Ergebnis: integer32;siehe Funktionsbeschreibung*}
{*                                                                 *}
{*-----------------------------------------------------------------*}
{*                                                                 *}
{*  Lokale Variablen:                                              *}
{*      gtOffset: integer32; enthaelt bei Token, die ueber mehrere   *}
{*         Pufferbloecke gehen, die bisher ermittelte Laenge des   *}
{*         Tokens                                                  *}
{*      gtBlock: buffer_pointer; Laufvariable zum Bearbeiten von   *}
{*         Token, die ueber mehrere Pufferbloecke gehen.           *}
{*                                                                 *}
{*******************************************************************}
*/

#ifdef __STDC__
int BUFGetLength(void)
{
#else /* ! __STDC__ */
int BUFGetLength()
  {
#endif /* ! __STDC__ */
  struct buffer_block *block,*lastblock;
  int len,zeichen,lastzeichen;

  _BEGIN_

  block=buffer_start[IncludePtr].block;             /* von (block,zeichen) */
  zeichen=buffer_start[IncludePtr].zeichen;
  
  lastblock=token_ende[IncludePtr].block;           /* bis (lastblock,lastzeichen) */
  lastzeichen=token_ende[IncludePtr].zeichen;       /* geht das Token */

  len=0;

  while(block!=lastblock)                            /* Rest des Anfangsblocks    */
    { len+=block->buffer_inhalt.length-zeichen;      /* und alle Folgebloecke     */
                                                     /* bis auf den letzten Block */
                                                     /* anhaengen                 */
      zeichen=0;
      block=block->nachfolger;
    }
  len+=lastzeichen-zeichen;                          /* Zeichen des letzten Blocks   */
                                                     /* anhaengen                    */
                                                     /*! zeichen ist NICHT IMMER 0 ! */     

  _TRA_ "GetLength liefert %d\n",len _TRE_ 
  _END_

  return len;
  }



/*******************************************************************}
{*                                                                 *}
{*  Prozedur: pget_token_position     Version: 11/7/89/a           *}
{*                                                                 *}
{*******************************************************************}
{*                                                                 *}
{*  Klassifizierung: Globale Prozedur fuer Anwenderroutinen        *}
{*                                                                 *}
{*  Funktionsbeschreibung:                                         *}
{*      Diese Prozedur gibt den Filenamen, Zeile und Spalte des    *}
{*      Zeichens, auf das buffer_start zeigt, zurueck. Dieses Zei- *}
{*      chen ist das erste Zeichen des zuletzt erkannten Tokens.   *}
{*                                                                 *}
{*-----------------------------------------------------------------*}
{*                                                                 *}
{*  Ausgabeparameter:                                              *}
{*     gpFilename: string(FnLength); Enthaelt den Filenamen des    *}
{*        Files, in dem das Token erkannt wurde. Ist dies der      *}
{*        Hauptfile, so wird nur 'MAINFILE' zurueckgegeben.        *}
{*     gpZeile: integer32; Gibt die Zeile des ersten Zeichens des  *}
{*        Tokens an. Die erste Zeile eines Files wird dabei als    *}
{*        Zeile 1 gerechnet.                                       *}
{*     gpSpalte: integer32; Enthaelt die Spalte des ersten Zeichens.*}
{*        Die erste Spalte einer Zeile wird dabei als Spalte 1     *}
{*        gerechnet. Diese Angabe ist jedoch nur korrekt, wenn     *}
{*        keine Tabulatoren im File enthalten sind.                *}
{*                                                                 *}
{*******************************************************************}
*/

#ifdef __STDC__
void BUFGetPosition(char **FileName, int *Zeile, int *Spalte)
#else /* ! __STDC__ */
void BUFGetPosition( FileName,Zeile,Spalte )
char **FileName;
int *Zeile,*Spalte;
#endif /* ! __STDC__ */
{ *FileName=quellname[IncludePtr];
  *Zeile =  buffer_start[IncludePtr].block->buffer_zeile;
  *Spalte = buffer_start[IncludePtr].zeichen;
}


/*******************************************************************}
{*                                                                 *}
{*  Prozedur: InitBuffer              Version: 11/7/89/a           *}
{*                                                                 *}
{*******************************************************************}
{*                                                                 *}
{*  Klassifizierung: Globale Prozedur                              *}
{*                                                                 *}
{*  Funktionsbeschreibung:                                         *}
{*      Diese Prozedur initialisiert den IncludePtr. Alle weiteren *}
{*      Initialisierungen werden erst bei int_open_buffer erledigt.*}
{*                                                                 *}
{*-----------------------------------------------------------------*}
{*                                                                 *}
{*  Seiteneffekte: IncludePtr                                      *}
{*                                                                 *}
{*******************************************************************}
*/

#ifdef __STDC__
void BUFInitBuffer(void)
#else /* ! __STDC__ */
void BUFInitBuffer()
#endif /* ! __STDC__ */
{
#ifdef DEBUG
 printf("Initialisierung des Buffers  : Version %s\n",version);
#endif
  IncludePtr = 0; 
}


/*******************************************************************}
{*                                                                 *}
{*  Prozedur: ExitBuffer              Version: 11/7/89/a           *}
{*                                                                 *}
{*******************************************************************}
{*                                                                 *}
{*  Klassifizierung: Globale Prozedur                              *}
{*                                                                 *}
{*  Funktionsbeschreibung:                                         *}
{*      Diese Prozedur schliesst alle von open_buffer geoeffneten  *}
{*      Include-Files und gibt den gesamten noch  belegten Spei-   *}
{*      cher frei. IncludePtr wird auf 0 gesetzt. Nach dem Aufruf  *}
{*      dieser Prozedur darf keine Routine aus Buffer mehr ver.    *}
{*      wendet werden.                                             *}
{*                                                                 *}
{*-----------------------------------------------------------------*}
{*                                                                 *}
{*  Seiteneffekte: Alle Pufferzeiger,                              *}
{*                 Alle geoeffneten Files,                         *}
{*                 IncludePtr                                      *}
{*                                                                 *}
{*-----------------------------------------------------------------*}
{*                                                                 *}
{*  Lokale Variablen:                                              *}
{*      cb_pointer: buffer_pointer; Laufvariable zum loeschen der  *}
{*         gesamten Pufferliste.                                   *}
{*      dummy: boolean; Variable zur Befriedigung des Aufrufs von  *}
{*         close_buffer. Wird nicht weiter verwendet.              *}
{*                                                                 *}
{*******************************************************************}
*/

#ifdef __STDC__
void BUFExitBuffer(void)
#else /* ! __STDC__ */
void BUFExitBuffer()
#endif /* ! __STDC__ */
{ struct buffer_block *cb_pointer;
  int dummy,dummy1;
  while (IncludePtr >= 2) dummy = BUFClose_Buffer();
  dummy1=dummy;
  while (buffer_start[IncludePtr].block != NULL)
      { cb_pointer = buffer_start[IncludePtr].block;
        buffer_start[IncludePtr].block = buffer_start[IncludePtr].block->nachfolger;
        MEMFree(cb_pointer);
      };
  IncludePtr = 0;
}
