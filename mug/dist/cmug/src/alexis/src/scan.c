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
{*  Segment: alexis3scan.c                                         *}
{*  Version: 20/05/91                                              *}
{*                                                                 *}
{*  Sprache: C                                                     *}
{*                                                                 *}
{*-----------------------------------------------------------------*}
{*                                                                 *}
{*  Beschreibung:                                                  *}
{*    Dieses Modul adaptiert den ALEXIS-Scanner an den MUG. Dies   *}
{*    ist notwendig, da die Scanner/Parser-Schnittstelle des MUG   *}
{*    von der Konzeption her auf den zuerst implementierten para-  *}
{*    meterisierten Scanner ausgelegt ist, diese Konzeption jedoch *}
{*    nicht mit der Philosophie vereinbar ist, die ALEXIS zugrunde *}
{*    liegt.                                                       *}
{*                                                                 *}
{*    Schnittstelle zum Parser:                                    *}
{*                                                                 *}
{*       Der Parser findet alle Routinen des alten Scanners in     *}
{*       moeglichst unveraenderter Form vor. Die folgenden vier    *}
{*       Aenderungen sind systemimmanent und damit nicht zu        *}
{*       vermeiden:                                                *}
{*                                                                 *}
{*       1) Die Klassencodes fuer Integers, Strings und Ids koennen*}
{*          nicht mehr in der Scannerquelle definiert werden. Daher*}
{*          werden hier drei Konstanten deklariert, die diese Klas-*}
{*          sencodes festlegen.                                    *}
{*                                                                 *}
{*       2) Aufgrund des beliebig langen Lookaheads ist es nicht   *}
{*          moeglich, unter dem Programmablauf VOM PARSER aus das  *}
{*          Eingabefile mit den Parametern der Funktion Scan umzu- *}
{*          schalten. Dies ist keine echte Einschraenkung, da die  *}
{*          Verwendung dieses Features auch beim alten, parametri- *}
{*          sierten Scanner zu nicht vorhersehbaren Ergebnissen    *}
{*          gefuehrt haette. Dafuer steht jetzt die Funktion       *}
{*          "open_buffer" der Pufferverwaltung zur Verfuegung, die *}
{*          die Includefile-Verwaltung des Puffers adaptiert.      *}
{*                                                                 *}
{*       3) Die beiden (identischen) Funktionen decode und         *}
{*          ScanDecode liefern nur noch korrekte Ergebnisse, wenn  *}
{*          die an sie uebergebenen Codes zuvor von der Funktion   *}
{*          Scan berechnet wurden. Ansonsten wird eine Fehlermel-  *}
{*          dung abgesetzt.                                        *}
{*                                                                 *}
{*       4) Die Funktion IsKeyword unterscheidet nicht mehr        *}
{*          zwischen Keywords und Sonderzeichen, sondern gibt      *}
{*          grundsaetzlich TRUE zurueck, wenn es sich nicht um     *}
{*          einen Identifier, Integer- oder String-Token handelt.  *}
{*                                                                 *}
{*                                                                 *}
{*    Schnittstelle zu den Aktionsroutinen:                        *}
{*                                                                 *}
{*       Die Parameter der Prozedur Scan werden zum Teil von den   *}
{*       Aktionsroutinen besetzt. Dazu steht ein Satz globaler     *}
{*       statischer Variablen zur Verfuegung, der unten beschrieben*}
{*       ist.                                                      *}
{*                                                                 *}
{*                                                                 *}
{*  Inhalt:                                                        *}
{*                                                                 *}
{*  I. interne Routinen:                                           *}
{*                                                                 *}
{*                                                                 *}
{*  II. Globale Routinen:                                          *}
{*  IIa. Scannerroutinen:                                          *}
{*                                                                 *}
{*    procedure ScanInit                                           *}
{*    procedure Scan                                               *}
{*    procedure ScanEnde                                           *}
{*    procedure ScanDecode                                         *}
{*                                                                 *}
{*  IIb. Decoderroutinen:                                          *}
{*                                                                 *}
{*    procedure DecInit                                            *}
{*    procedure decode                                             *}
{*    procedure DecEnde                                            *}
{*                                                                 *}
{*  IIc. Klassifizierungsroutinen:                                 *}
{*                                                                 *}
{*    function IsIdent                                             *}
{*    function IsNumber                                            *}
{*    function IsString                                            *}
{*    function IsKeyword                                           *}
{*                                                                 *}
{*  IId. Neue Routinen fuer zukuenftige Parser:                    *}
{*                                                                 *}
{*    function GetFileName                                         *}
{*                                                                 *}
{*-----------------------------------------------------------------*}
{*                                                                 *}
{*                 M O D I F I K A T I O N E N                     *}
{*=================================================================*}
{* Datum      modifiziert von    Beschreibung der Modifikation     *}
{*=================================================================*}
{*                                                                 *}
{*******************************************************************/

#include "buffer.h"

#include "scan.h"

#include "symtab.h"

#include "alexmem.h"


#ifdef __STDC__
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#endif

#include <stdio.h>

/*
#include "automat_proc.h"
#include "buffer_proc.h"
#include "mugactio_proc.h"
*/

/*
int SvClassCode,SvRelCode,SvZeile,SvSpalte;
char *SvFileName;
*/
long scanerrors;

static int scanAborted;

/* Bauernfeind: Prototypen, 8.6.93 */
#ifdef __STDC__
extern void AUTInit_Automat(void);
extern void MACInitMugActions(void);
extern void ACTInitAction(void);
extern void BUFOpenBuffer(char*);
extern void AUTScan_Tokens(Token);
extern void AUTExit_Automat(void);
extern void MACExitMugActions(void);
#endif

#ifdef __STDC__
int scanInit(void)
{ 
#else /* ! __STDC__ */
int scanInit()
  { 
#endif /* ! __STDC__ */
#ifdef DEBUG
 printf("scanInit()\n");
#endif
    AUTInit_Automat();
    BUFInitBuffer();
    MACInitMugActions();
    ACTInitAction();
/*  initkeller();  Darf nicht in die Bibliothek, da beim KWGEN nicht mehr vorhanden */ 

    scanAborted=0;
    return 1;
  }

#ifdef __STDC__
int scanOpen(char *name)
{ 
#else /* ! __STDC__ */
int scanOpen(name)
char *name;
  { 
#endif /* ! __STDC__ */
#ifdef DEBUG
 printf("scanOpen(%s)\n",name);
#endif
    scanerrors=0;
    BUFOpenBuffer(name);
    return 1;
  }

#ifdef __STDC__
int scanNext(Token tok)
{ 
#else /* ! __STDC__ */
int scanNext(tok)
Token tok;
  { 
#endif /* ! __STDC__ */
    AUTScan_Tokens(tok);
/*
if( tok->kc!=SvClassCode ||
    tok->rcode!=SvRelCode ||
    tok->ort.zeile!=SvZeile ||
    tok->ort.spalte!=SvSpalte ||
    tok->ort.fname!=SvFileName )
      printf("*** K:%d R:%d Z:%d S:%d N:%s\n",
               SvClassCode,SvRelCode,SvZeile,SvSpalte,SvFileName );

    tok->kc=SvClassCode;
    tok->rcode=SvRelCode;
    tok->ort.zeile=SvZeile;
    tok->ort.spalte=SvSpalte;
    tok->ort.fname=SvFileName;
*/

  }

#ifdef __STDC__
void scanClose(void)
{ scanAborted=1;
#else /* ! __STDC__ */
void scanClose()
  { scanAborted=1;
#endif /* ! __STDC__ */
    AUTExit_Automat();
    MACExitMugActions();

  }

void scanAbort()
  { if(!scanAborted)
      { scanAborted=1;
        AUTExit_Automat();
        MACExitMugActions();
      }
  }


#ifdef __STDC__
char *scanDecode(char *text, Token tok)
{ 
#else /* ! __STDC__ */
char *scanDecode(text,tok)
char *text;
Token tok;
  { 
#endif /* ! __STDC__ */
  char *token;
  token=SYDecSymtab(tok->kc,tok->rcode);
  if( text!=0l )
    {
    strcpy(text,token);
    }
  else 
    {
    text=token;
    }
  return text;
  } 

#ifdef __STDC__
char *scannDecode(char *text, Token tok, int len)
{ 
#else /* ! __STDC__ */
char *scannDecode(text,tok,len)
char *text;
Token tok;
int len;
  { 
#endif /* ! __STDC__ */
  char *token;
  token=SYDecSymtab(tok->kc,tok->rcode);
  if( text!=0l )
    {
    strncpy(text,token,len);
    }
  else 
    {
    text=token;
    }
  return text;
  } 


#include <varargs.h>
#include <stdio.h>
#ifdef __STDC__
void wErrorf(Quellort *ort, char *fmt, int va_alist)
{ 
#else /* ! __STDC__ */
void wErrorf(ort,fmt,va_alist)
Quellort *ort;
char *fmt;
va_dcl
  { 
#endif /* ! __STDC__ */
  va_list arg;
  Token tok;
  int i;
  char *str;
  Quellort *qo;
  char *s;
  char *token;

  if( ort!=NULL )
    {  
    printf("Zeile %d Spalte %d Datei %s: ",
        ort->zeile,ort->spalte,ort->fname );
    }

  va_start(arg);
   
  for(str=fmt;*str!='\0';str++)
    { 
    if(*str=='%')
      { 
      switch(str[1])
        { case '\0': --str;
                     break;

          case 't': tok=va_arg(arg,Token);
                    printf("Zeile %d Spalte %d Datei %s: ",
                       tok->ort.zeile,tok->ort.spalte,tok->ort.fname);
                    fflush(stdout);
                    break;

          case 'T': tok=va_arg(arg,Token);
                    token=SYDecSymtab(tok->kc,tok->rcode);
                    printf("%s",token);
                    fflush(stdout);
                    break;                    


         case 's':  s=va_arg(arg,char*);
                    printf("%s",s);
                    break; 

         case 'd':  i=va_arg(arg,int);
                    printf("%d",i);
                    break; 

         case 'c':  i=va_arg(arg,int);
                    printf("%c",i);
                    break; 

          case 'q': qo=va_arg(arg,Quellort*);
                    printf("Zeile %d Spalte %d Datei %s: ",
                       qo->zeile,qo->spalte,qo->fname);
                    fflush(stdout);
                    break;

          default:  putchar('%');
                    putchar( str[1] );
                    break;
          
        }
      ++str;
      }
    else
      {
      putchar(*str);
      }
    }
  }

#ifdef __STDC__
void memError(void)
{ printf("OUT OF MEMORY ?!!\n");
#else /* ! __STDC__ */
void memError()
  { printf("OUT OF MEMORY ?!!\n");
#endif /* ! __STDC__ */
  }

#ifdef __STDC__
Token allocToken(void)
{ 
#else /* ! __STDC__ */
Token allocToken()
  { 
#endif /* ! __STDC__ */
#ifdef DEBUG
  printf("ALLOC_TOKEN\n");
#endif
    return (Token)MEMAlloc(sizeof(TokenRec));
  }


#ifdef __STDC__
void freeToken(Token token)
{ 
#else /* ! __STDC__ */
void freeToken(token)
Token token;
  { 
#endif /* ! __STDC__ */
#ifdef DEBUG
  printf("FREE_TOKEN\n");
#endif
    MEMFree(token);
  }
 

#ifdef __STDC__
Token copyToken(Token dest, Token src)
{ memcpy((char *)dest,(char *)src,sizeof(TokenRec));
#else /* ! __STDC__ */
Token copyToken(dest,src)
Token dest,src;
  { memcpy((char *)dest,(char *)src,sizeof(TokenRec));
#endif /* ! __STDC__ */
    return dest;
  }

#ifdef __STDC__
void setTokeninvalid(Token tok)
{
#else /* ! __STDC__ */
void setTokeninvalid(tok)
Token tok;
  {
#endif /* ! __STDC__ */
  SYSetInvalid(tok->kc,tok->rcode);
  }

#ifdef __STDC__
int isTokenvalid(Token tok)
{
#else /* ! __STDC__ */
int isTokenvalid(tok)
Token tok;
  {
#endif /* ! __STDC__ */
  if( SYDecSymtab(tok->kc,tok->rcode)[0]=='\0' ) return 0;
  else return 1;
  }
