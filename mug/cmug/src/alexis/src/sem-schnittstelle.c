
 
/*  Auswerter-Schnittstelle */
/***************************************************************************/
/*  Standard-Routinen von C  */
#ifdef __STDC__
#include <stddef.h>
#include <stdlib.h>
#endif
#include <stdio.h>
#include <string.h>

#ifndef __DATE__
#define __DATE__ "28. Juni 1991"
#endif

#ifndef TRUE
#define TRUE 1
#define FALSE 0
#endif

FILE *errordatei;   /* Datei fuer Fehlermeldungen        */
int protokoll = 1;  /* Ausgabe von Fehlermeldungen auch auf Datei */
long semerrors = 0L;
char *eingabedateiname;
char *ausgabedateiname;

#ifdef __STDC__
static char *substExt(char *s, char *ext)
{
#else /* ! __STDC__ */
static char *substExt(s,ext)
 char *s;
 char *ext;
 {
#endif /* ! __STDC__ */
  char *base;
  char *point;
  int  baselen;
  char *res;

  if ((base = strrchr(s,'/')) == NULL)
    base = s;
  else
    base++;
  if ((point = strrchr(base,'.')) == NULL)
    baselen = strlen(base);
  else
    baselen = strlen(base) - strlen(point);
  if ((res = (char *)malloc(baselen + strlen(ext)+1)) == NULL)
   {
    fputs("no memory\n",stderr);
    exit(100);
   }
  strncpy(res,base,baselen);
  strcpy(res+baselen,ext);
  return(res);
 }


#ifdef __STDC__
int OpenErr(void)
#else
#ifdef __STDC__
int OpenErr(void)
#else /* ! __STDC__ */
int OpenErr()
#endif /* ! __STDC__ */
#endif
 {
  char *errordateiname;
  if (errordatei == NULL)
   {
    if ((errordatei = fopen(errordateiname=substExt(eingabedateiname,".err"),"w"))
	 == NULL)
     {
      fprintf(stderr,"can't open %s : ",errordateiname);
      perror(NULL);
      return(FALSE);
     }
   }
  return(TRUE);
 }

#ifdef __STDC__
void semAbort(void)
#else
#ifdef __STDC__
void semAbort(void)
#else /* ! __STDC__ */
void semAbort()
#endif /* ! __STDC__ */
#endif
{
   fprintf(stderr,"Abbruch: fataler Fehler aufgetreten !!\n");
   exit(-99);
}

#ifdef __STDC__
void semClose(void)
#else
#ifdef __STDC__
void semClose(void)
#else /* ! __STDC__ */
void semClose()
#endif /* ! __STDC__ */
#endif
 {
 } /* semClose */


#ifdef __STDC__
int semInit(int argc,char *argv[])
#else
int semInit(argc,argv)
 int argc;
 char *argv[];
#endif
{

	eingabedateiname=argv[1];
	ausgabedateiname=substExt(eingabedateiname,".ass");
}
