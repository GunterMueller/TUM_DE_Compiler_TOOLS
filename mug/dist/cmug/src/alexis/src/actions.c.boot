#include <stdio.h>

extern int abort_scan;
int ignore_case = 1; /* TRUE */
#define TOKEN Action_tok

 
#include "actions.h"
#include "buffer.h"
#include "scan.h"
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
{ 
  Quellort ort;

  char tok[TOKMAX];

  BUFGetPosition( &(ort.fname),&(ort.zeile),&(ort.spalte) );

  BUFGetToken( tok );
  if( strlen(tok)>1 )
    wErrorf(&ort,"Unbekanntes Token >%s<\n",tok);
  else
    wErrorf(&ort,"Unbekanntes Token >#%d=%c<\n", *tok, *tok );
}
 
void ACTDo_Action(Action_tok,Action_nr)
Token Action_tok;
int Action_nr;
{ switch (Action_nr) {
  case 0   : MEMugRecoverableError(6);
           break;
  case 1    : abort_scan = 0; /*FALSE*/
             
              break;
  case 2    : abort_scan = 1; /*TRUE*/
                MACRetCC(TOKEN,1,1);   
              break;
  case 3    : abort_scan = 1; /*TRUE*/
                MACRetCC(TOKEN,2,1);   
              break;
  case 4    : abort_scan = 1; /*TRUE*/
                MACRetCC(TOKEN,3,1);   
              break;
  case 5    : abort_scan = 1; /*TRUE*/
                MACRetCC(TOKEN,4,1);   
              break;
  case 6    : abort_scan = 1; /*TRUE*/
              ReturnChr(TOKEN,32); 
              break;
  case 7    : abort_scan = 1; /*TRUE*/
                MACRetCC(TOKEN,6,1);   
              break;
  case 8    : abort_scan = 1; /*TRUE*/
                MACRetCC(TOKEN,7,1);   
              break;
  case 9    : abort_scan = 1; /*TRUE*/
                MACRetCC(TOKEN,8,1);   
              break;
  case 10    : abort_scan = 1; /*TRUE*/
                MACRetCC(TOKEN,9,1);   
              break;
  case 11    : abort_scan = 1; /*TRUE*/
                MACRetCC(TOKEN,10,1);   
              break;
  case 12    : abort_scan = 1; /*TRUE*/
              Ret_Fpar(TOKEN,11); 
              break;
  case 13    : abort_scan = 1; /*TRUE*/
                MACRetCC(TOKEN,13,1);   
              break;
  case 14    : abort_scan = 1; /*TRUE*/
              IncludeFile(TOKEN,14); 
              break;
  case 15    : abort_scan = 1; /*TRUE*/
                MACRetCC(TOKEN,15,1);   
              break;
  case 16    : abort_scan = 1; /*TRUE*/
                MACRetCC(TOKEN,15,2);   
              break;
  case 17    : abort_scan = 1; /*TRUE*/
                MACRetInt(TOKEN,16);     
              break;
  case 18    : abort_scan = 1; /*TRUE*/
                MACRetCC(TOKEN,17,1);   
              break;
  case 19    : abort_scan = 1; /*TRUE*/
                MACRetCC(TOKEN,18,1);   
              break;
  case 20    : abort_scan = 1; /*TRUE*/
                MACRetCC(TOKEN,19,1);   
              break;
  case 21    : abort_scan = 1; /*TRUE*/
                MACRetCC(TOKEN,20,1);   
              break;
  case 22    : abort_scan = 1; /*TRUE*/
                MACRetCC(TOKEN,21,1);   
              break;
  case 23    : abort_scan = 1; /*TRUE*/
                MACRetCC(TOKEN,22,1);   
              break;
  case 24    : abort_scan = 1; /*TRUE*/
                MACRetCC(TOKEN,23,1);   
              break;
  case 25    : abort_scan = 1; /*TRUE*/
                MACRetCC(TOKEN,24,1);   
              break;
  case 26    : abort_scan = 1; /*TRUE*/
                MACRetCC(TOKEN,25,1);   
              break;
  case 27    : abort_scan = 1; /*TRUE*/
                MACRetCC(TOKEN,26,1);   
              break;
  case 28    : abort_scan = 1; /*TRUE*/
              Ret_Prog(TOKEN,27); 
              break;
  case 29    : abort_scan = 1; /*TRUE*/
                MACRetCC(TOKEN,28,1);   
              break;
  case 30    : abort_scan = 1; /*TRUE*/
                MACRetCC(TOKEN,28,2);   
              break;
  case 31    : abort_scan = 1; /*TRUE*/
                MACRetCC(TOKEN,28,3);   
              break;
  case 32    : abort_scan = 1; /*TRUE*/
                MACRetCC(TOKEN,29,1);   
              break;
  case 33    : abort_scan = 1; /*TRUE*/
                MACRetCC(TOKEN,30,1);   
              break;
  case 34    : abort_scan = 1; /*TRUE*/
                MACRetCC(TOKEN,31,1);   
              break;
  case 35    : abort_scan = 1; /*TRUE*/
                MACRetCC(TOKEN,31,2);   
              break;
  case 36    : abort_scan = 1; /*TRUE*/
                MACRetCC(TOKEN,31,3);   
              break;
  case 37    : abort_scan = 1; /*TRUE*/
                MACRetCC(TOKEN,31,4);   
              break;
  case 38    : abort_scan = 1; /*TRUE*/
                MACRetString(TOKEN,32);  
              break;
  case 39    : abort_scan = 1; /*TRUE*/
                MACRetId(TOKEN,12);      
              break;
  }
}

void ACTEnd_Action(Action_tok)
Token Action_tok;
{ 
  MACRetCC(TOKEN,0,0);
}

void ACTInitAction()
{ 
  printf("ALEXIS: Scanner                 (c) TU Muenchen  2. Juli 1991\n");
}

void ACTError_Action()
{ 
  fehler_aktion();
}

