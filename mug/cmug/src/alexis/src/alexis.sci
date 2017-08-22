ScanError
prog
  fehler_aktion();
progend

externals prog
 
#include "actions.h"
#include "buffer.h"
#include "mugactio.h"
 
 
void Ret_Fpar(Tok,Class)
Token Tok;
int Class;
{ char tok[TOKMAX];

  BUFGetToken( tok );
  MACRetTok( Tok,Class, tok[1]-'0',tok );
}
 
 
void Ret_Prog( Tok,Class )
Token Tok;
int Class;
{ char tok[TOKMAX];
  char *help;

  BUFGetToken( tok );
  help=tok+4;                                   /* 'prog'     entfernen */  
  help[strlen(help)-7]='\0';                    /* 'prog end' entfernen */

  MACRetProcessedString(Tok,Class,help );
}
 
 
void IncludeFile( Tok,Class )
Token Tok;
int Class;
  { 
  char tok[TOKMAX];
  char *help;

  MACRetCC(Tok,Class,1);

  BUFGetToken( tok );

  help=tok+9;                      /*    'include ''' entfernen */
  help[strlen(help)-1]='\0';       /*    ''''         entfernen */

  BUFOpenBuffer( help );
  }
 
 
void ReturnChr( Tok,Class )
Token Tok;
int Class;
  {
  char tok[TOKMAX];
  char *help;

  int ord;

  BUFGetToken( tok );
  help=tok+4;                   /* 'chr(' entfernen */
  help[strlen(help)-1]='\0';    /* ')'    entfernen */

  for( ord=0;*help!='\0';++help )
    {
    ord=ord*10+ *help-'0';
    }
  *help=ord;                 /* !!!! Die Zeile stimmt, also Finger weg !!! */
                 /* da stand naemlich anfangs ')', und dahinter steht '\0' */
  MACRetProcessedString( Tok,Class,help );
}
 
 
void fehler_aktion()
{ int z,s;
  Quellort ort;

  char tok[TOKMAX];

  BUFGetPosition( &(ort.fname),&(ort.zeile),&(ort.spalte) );

  BUFGetToken( tok );
  if( strlen(tok)>1 )
    wErrorf(&ort,"Unbekanntes Token >%s<\n",tok);
  else
    wErrorf(&ort,"Unbekanntes Token >#%d=%c<\n",*tok,*tok );
}
 
progend
