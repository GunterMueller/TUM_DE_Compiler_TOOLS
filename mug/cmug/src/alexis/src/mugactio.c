/*******************************************************************
 *                                                                 
 *                                                                 
 *     AAA     L         EEEEEEEE    XX     XX    III    SSSSS     
 *    A   A    L         E            X     X      I    S     S    
 *   A     A   L         E             X   X       I    S          
 *   AAAAAAA   L         EEEEEE         XXX        I     SSSSS     
 *   A     A   L         E             X   X       I          S    
 *   A     A   L         E            X     X      I    S     S    
 *   A     A   LLLLLLL   EEEEEEEE    XX     XX    III    SSSSS     
 *                                                                 
 *      Advanced LEXical Instrument for Scannergeneration          
 *                                                                 
 *                                                                 
 *******************************************************************
 *
 * (c) copyright 1991 by Technische Universitaet Muenchen, Germany
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
 *
 *******************************************************************
 *
 *  Autoren:   Bernhard Smith, Frank Eiberle
 *
 *  Modul:     mugactio.c
 *
 *  Version:   01/07/91
 *
 *******************************************************************
 *  
 *  Beschreibung:
 *    Dieser Modul stellt die Arbeitsaktionen bereit um erkannte Token
 *    gemaess der C-MUG-Spezifikation an den Aufrufer zurueckzugeben.
 *
 *    Die Funktionen gehen dabei folgendermassen vor:
 *      1. Lesen des Klartextes von der Pufferverwaltung
 *      2. ggf. Bearbeiten des Originaltextes
 *      3. ggf. Eintrag in die Symbo0ltabelle
 *      4. Einlesen der Quelltextinformation (Zeile,Spalte,Datei) 
 *      5. versorgen einer Token-Struktur (scan.h)
 *  
 *******************************************************************
 *
 * Modifikationen:
 * 
 * Datum    modifiziert von   Art der Modifikation
 *------------------------------------------------------------------
 *
 *******************************************************************
 */

#define VERSION "01/07/91/BeSm"

#ifdef __STDC__
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#endif

#include "buffer.h"
#ifdef __STDC__
#include "scan.h"
#endif /* not ! __STDC__ */
#include "actions.h"
#include "mugactio.h"
/* #include "mugactio_proc.h" */
#include "symtab.h"
#include "mugerr.h"
#ifndef __STDC__
#include "scan.h"
#endif /* ! __STDC__ */

/* Bauernfeind: Prototypen, 8.6.93 */
#ifdef __STDC__
extern void BUFGetUCToken(char*);
extern void BUFGetToken(char*);
extern void BUFGetPosition(char**, int*, int*);
#endif

extern int ignore_case;

/*
** Funktion: void MACRetCC( int Class,int Rel )
** 
** Rueckgabe eines Klassen- und Relativcodes an einen Aufrufer
*/ 

#ifdef __STDC__
void MACRetCC(Token Tok, int Class, int Rel)
{ 
#else /* ! __STDC__ */
void MACRetCC( Tok,Class,Rel )
Token Tok;
int Class,Rel;
  { 
#endif /* ! __STDC__ */
  char tok[TOKMAX];
  int Zeile,Spalte;
  char *FileName;

  if (ignore_case)      BUFGetUCToken( tok );
  else                  BUFGetToken( tok );

  if ( !SYTestEntry( Class,Rel) )
    {
    SYInstallEntry( tok,Class,Rel );
    }

  SYM(Tok)    = Class;
  SEMVAL(Tok) = Rel;

  BUFGetPosition( &FileName,&Zeile,&Spalte );  

  QUELL_ORT(Tok)->zeile=Zeile;
  QUELL_ORT(Tok)->spalte=Spalte;
  QUELL_ORT(Tok)->fname=FileName;
  }



/*
**=====================================================================
** Funktion: void MACRetTok( int Class,int Rel,char *tok )
**---------------------------------------------------------------------
** Rueckgabe eines Token unter dem uebergebenen Klassen- und Relativcode
** der Benutzer muss zuvor des Token selbsttaetig aus def Pufferverwaltung
** gelesen haben, ausserdem darf der Benutzer dieses Token modifizieren
**=====================================================================
*/

#ifdef __STDC__
void MACRetTok(Token Tok, int Class, int Rel, char *tok)
#else /* ! __STDC__ */
void MACRetTok( Tok,Class,Rel,tok )
Token Tok;
int Class,Rel;
char *tok;
#endif /* ! __STDC__ */
{ int Zeile,Spalte;
  char *FileName;
  
  if( !SYTestEntry( Class,Rel ) )
    SYInstallEntry( tok,Class,Rel );

  SYM(Tok)    = Class;
  SEMVAL(Tok) = Rel;

  BUFGetPosition( &FileName,&Zeile,&Spalte );

  QUELL_ORT(Tok)->zeile=Zeile;
  QUELL_ORT(Tok)->spalte=Spalte;
  QUELL_ORT(Tok)->fname=FileName;
}


/*
**=====================================================================
** Funktion: void MACRetInt( Token Tok,int Class )
**---------------------------------------------------------------------
** Rueckgabe eines Token unter dem uebergebenen Klassen- und Relativcode
** der Benutzer muss zuvor des Token selbsttaetig aus def Pufferverwaltung
** gelesen haben, ausserdem darf der Benutzer dieses Token modifizieren
**=====================================================================
*/


#ifdef __STDC__
void MACRetInt(Token Tok, int Class)
{
#else /* ! __STDC__ */
void MACRetInt( Tok,Class )
Token Tok;
int Class;
  {
#endif /* ! __STDC__ */
  char tok[TOKMAX];
  int Rel;
  int Zeile,Spalte;
  char *FileName;

  BUFGetToken( tok );

  SYM(Tok)    = Class;
  SEMVAL(Tok) = Rel = atoi( tok );

  if( !SYTestEntry( Class,Rel ) )
    SYInstallEntry( tok,Class,Rel );

  BUFGetPosition( &FileName,&Zeile,&Spalte );  

  QUELL_ORT(Tok)->zeile=Zeile;
  QUELL_ORT(Tok)->spalte=Spalte;
  QUELL_ORT(Tok)->fname=FileName;
}


/*
**=====================================================================
** Funktion: void MACRetTok( int Class,int Rel,char *tok )
**---------------------------------------------------------------------
** Rueckgabe eines Token unter dem uebergebenen Klassen- und Relativcode
** der Benutzer muss zuvor des Token selbsttaetig aus def Pufferverwaltung
** gelesen haben, ausserdem darf der Benutzer dieses Token modifizieren
**=====================================================================
*/

#ifdef __STDC__
void MACRetId(Token Tok, int Class)
{ 
#else /* ! __STDC__ */
void MACRetId( Tok,Class )
Token Tok;
int Class;
  { 
#endif /* ! __STDC__ */
  int Zeile,Spalte;
  char *FileName;
  char tok[TOKMAX];

  if (ignore_case)                BUFGetUCToken( tok );
  else                            BUFGetToken( tok );

  SYM(Tok)    = Class;
  SEMVAL(Tok) = SYGetIdNumber(tok,TYP_ID,Class);

  BUFGetPosition( &FileName,&Zeile,&Spalte );  

  QUELL_ORT(Tok)->zeile=Zeile;
  QUELL_ORT(Tok)->spalte=Spalte;
  QUELL_ORT(Tok)->fname=FileName;
}






/*
**=====================================================================
** Funktion: void MACRetTok( int Class,int Rel,char *tok )
**---------------------------------------------------------------------
** Rueckgabe eines Token unter dem uebergebenen Klassen- und Relativcode
** der Benutzer muss zuvor des Token selbsttaetig aus def Pufferverwaltung
** gelesen haben, ausserdem darf der Benutzer dieses Token modifizieren
**=====================================================================
*/

#ifdef __STDC__
void MACRetProcessedString(Token Tok, int Class, char *str)
{ 
#else /* ! __STDC__ */
void MACRetProcessedString( Tok,Class,str )
Token Tok;
int Class;
char *str;
  { 
#endif /* ! __STDC__ */
  int Zeile,Spalte;
  char *FileName;

  SYM(Tok)    = Class;
  SEMVAL(Tok) = SYGetIdNumber(str,TYP_STR,Class);

  BUFGetPosition( &FileName,&Zeile,&Spalte );

  QUELL_ORT(Tok)->zeile=Zeile;
  QUELL_ORT(Tok)->spalte=Spalte;
  QUELL_ORT(Tok)->fname=FileName;
  }





/*
**=====================================================================
** Funktion: void MACRetTok( int Class,int Rel,char *tok )
**---------------------------------------------------------------------
** Rueckgabe eines Token unter dem uebergebenen Klassen- und Relativcode
** der Benutzer muss zuvor des Token selbsttaetig aus def Pufferverwaltung
** gelesen haben, ausserdem darf der Benutzer dieses Token modifizieren
**=====================================================================
*/


/*******************************************************************}
{*                                                                 *}
{*  Prozedur: MACRetString            Version: 20/05/91            *}
{*                                                                 *}
{*******************************************************************}
{*                                                                 *}
{*  Klassifizierung: Globale Prozedur                              *}
{*                                                                 *}
{*      uebergebenen Klassencode an den Parser. Der String muss    *}
{*      dabei der folgenden Syntax entsprechen:                    *}
{*      (('''' (allbut('''') | '''''')* '''') |                    *}
{*       ('#' (.'0'..'9'.) #1,3             )  ) +                 *}
{*      Der String wird durch einfache Anfuehrungszeichen einge-   *}
{*      rahmt, Anfuehrungszeichen innerhalb des Strings muessen    *}
{*      doppelt geschrieben werden. Explizite Codeangaben koennen  *}
{*      ausserhalb von Anfuehrungszeichen stehen, sie werden durch *}
{*      ein Nummernsymbol eingeleitet, dem maximal 3 Dezimalziffern*}
{*      folgen. Die Dezimalzahl wird umgewandelt in ein Zeichen,   *}
{*      das den entsprechenden Code hat.                           *}
{*******************************************************************/

#ifdef __STDC__
void MACRetString(Token Tok, int Class)
#else /* ! __STDC__ */
void MACRetString( Tok,Class )
Token Tok;
int Class;
#endif /* ! __STDC__ */
{ char tok[TOKMAX],ret[TOKMAX];
  int val;
  char *p,*q;

  BUFGetToken( tok );

  p=tok;

  q=ret;

  while(*p!=0)
    {
    if(*p=='\'')
      {
      ++p;
      while( *p!=0 )
        {
        if( *p=='\'' )
          { 
          p++;              /* erstes ' ueberlesen */ 
          if( *p!='\'' )
            {
            break;
            }
          }
        *q++ = *p++;
        }
      }
    else if(*p=='#')
      {
      ++p;
      val=0;
      while( *p>='0' && *p<='9' )
        {
        val=val*10+ *p++ -'0';
        }
      *q++=val;
      }
    else
      { 
      MEMugRecoverableError(8);
      }
    }
  *q++=0;
  MACRetProcessedString( Tok,Class,ret );
  }


/*
**=====================================================================
** Funktion: void MACInitMugActions( void )
**---------------------------------------------------------------------
** Initialisierung der Arbeitsaktionen, die Symboltabelle wird
** Initialisiert
**=====================================================================
*/

#ifdef __STDC__
void MACInitMugActions(void)
#else /* ! __STDC__ */
void MACInitMugActions()
#endif /* ! __STDC__ */
{ 
#ifdef DEBUG  
 printf("Initialisierung von Mugactio : Version %s\n",version);
#endif
  SYInitSymtab();
}


/*
**=====================================================================
** Funktion: void MACExitMugActions( void )
**---------------------------------------------------------------------
** Dummy-Funktion
**=====================================================================
*/

#ifdef __STDC__
void MACExitMugActions(void)
{ 
#else /* ! __STDC__ */
void MACExitMugActions()
 { 
#endif /* ! __STDC__ */
 }

