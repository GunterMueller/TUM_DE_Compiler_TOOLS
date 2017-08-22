
#ifdef __STDC__
#include <stddef.h>
#include <stdlib.h>
#endif
#include <stdio.h>

#ifndef __DATE__
#define __DATE__ "25. Mai 1990"
#endif
#include "AttrGlob.h"
#include "ps_token.h"
#include "scanfunk.h"

FILE *errordatei;   /* Datei fuer Fehlermeldungen        */
int  protokoll = 1; /* Fehlermeldungen auch in die Datei */
long semerrors;

#ifdef __STDC__
int OpenErr(void)
#else /* ! __STDC__ */
int OpenErr()
#endif /* ! __STDC__ */
 {
  if (errordatei == NULL)
   {
    if ((errordatei = fopen("compiler.err","w")) == NULL)
     {
      perror("can't open compiler.err");
      return(0);
     }
   }
  return(1);
 } /* OpenErr */

void semAbort()
{
   fprintf(stderr,"Abbruch: fataler Fehler aufgetreten !!\n");
   exit(-99);
}

int semInit(argc, argv)
int argc; 
char *argv[];
{

	printf( "\n  MINIMUG: Expression Auswerter  \t\t(c) TU Muenchen %s\n", __DATE__);
#if 0 
 if(argc != 2)
   {
      fprintf(stderr,"Gebrauch: expr Datei \n");
      semAbort() ;
   }
#endif
   /* argv[1] ist jetzt genau der Dateiname   */
   /* Also dann starte das eigentliche Parsen */
   return(1);
}


   
void semClose()
{
   fprintf(stdout,"\n          Ende gut alles gut !!!\n");
}
  



/* Hier beginnen die sematischen Aktionen */


void printresult(i,erg)
int i;
int *erg;
{  
  printf("Das Ergebnis lautet: %d\n",i);
  *erg = i;
}

void makeadd(i,add,j,erg)
int i,j;
Token add;
int *erg;
{  
  if(SEMVAL(add) == 1)
      *erg = i +j ;
  else
      *erg = i - j ;
}

void makemult(i,mult,j,erg)
int i,j;
Token mult;
int *erg;
{  
  if(SEMVAL(mult)==1)
      *erg = i * j ;
   else
      if(j==0)
      {
			printf("*** DIVISION durch 0 !! ***\n");
         parseAbort();
         semAbort();
       }
       else
          *erg = i / j;
}


#ifdef __STDC__
void readmultop(Token token, Token *op)
#else
void readmultop(token,op)
 Token token;
 Token *op; /* multop */
#endif
 {
  *op = (Token)allocToken();
  copyToken(*op,token);
 } /* readmultop */

#ifdef __STDC__
void readaddop(Token token, Token *op)
#else
void readaddop(token,op)
 Token token;
 Token *op; /* addop */
#endif
 {
  *op = (Token)allocToken();
  copyToken(*op,token);
 } /* readaddop */
#ifdef __STDC__
void readnumber(Token token, number *id)
#else
void readnumber(token,id)
 Token token;
 number *id;
#endif
 {
 *id = (number) SEMVAL(token);
 }
