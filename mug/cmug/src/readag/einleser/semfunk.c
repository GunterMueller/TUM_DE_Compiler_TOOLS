/*
 * (c) copyright 1989,1991 by Technische Universitaet Muenchen, Germany
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
 */
#ifdef __STDC__
#include <stddef.h>
#include <stdlib.h>
#endif
#include <stdio.h>
#include <string.h>

#include "gramtyp.h"
#include "scanfunk.h"


FILE *errordatei;   /* Datei fuer Fehlermeldungen        */
int  protokoll = 1; /* Fehlermeldungen auch in die Datei */

int  druckegrammar,readonly,druckekeller;
long *errors;


static char *eingabedateiname;

char *substExt(s,ext)
 char *s;
 char *ext;
 {
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
#else /* ! __STDC__ */
int OpenErr()
#endif /* ! __STDC__ */
 {
 char *errdatname;

  errdatname=substExt(eingabedateiname,".err");
  if (errordatei == NULL)
   {
    if ((errordatei = fopen(errdatname,"w")) == NULL)
     {
      perror("can't open compiler.err");
      return(FALSE);
     }
   }
  return(TRUE);
 } /* OpenErr */

#ifdef __STDC__
void semAbort(void)
#else /* ! __STDC__ */
void semAbort()
#endif /* ! __STDC__ */
{
   fprintf(stderr,"fataler Fehler, Programmabbruch\n");
   exit(30);
}

#ifdef __STDC__
int semInit(int argc, char **argv)
#else /* ! __STDC__ */
int semInit( argc, argv)
int argc; 
char *argv[];
#endif /* ! __STDC__ */
{
	char *s;
	char *pname;
	int fehler_option = 0;

	fputs("AG-Einleser\n",stderr);
	pname = argv[0];
	/*printf("\n CMUG-Grammatikeinleser \t\t (c) TU Muenchen %s\n\n",
		__DATE__);*/
	druckegrammar = readonly = druckekeller = FALSE;
	eingabedateiname=argv[1];
	argc--;argv++; /* ueberlesen  Parameter datei */
	/* Optionen pruefen */
	while(--argc >0 && (*++argv)[0] == '-')
	  if (argv[0] != NULL)
		for(s=argv[0]+1;*s != '\0';s++)
			switch(*s) {
			case 'g':
				druckegrammar = TRUE;
				break;
			case 'l' :
				readonly = TRUE;
				break;
			case 'v' :
				druckekeller = TRUE;
				break;
			default:
				fprintf(stderr,"unbekannte Option : %c\n",*s);
				argc = 0;
				fehler_option = 1;
				break;
			}

	if(fehler_option)
	{
		fprintf(stderr,"Aufruf: %s Datei [-g -l -v] \n",pname);
		semAbort() ;
	}
   return(TRUE);
} 

#ifdef __STDC__
void semClose(void)
#else /* ! __STDC__ */
void semClose()
#endif /* ! __STDC__ */
{
}  

#ifdef __STDC__
void readident(Token token, ident *id)
#else
void readident(token,id)
 Token token;
 ident *id;
#endif
 {
  *id = allocToken();
  copyToken(*id,token);
 }

#ifdef __STDC__
void readstring(Token token, string *str)
#else
void readstring(token,str)
 Token token;
 string *str;
#endif
 {
  *str = scanDecode(NULL,token);
 }

#ifdef __STDC__
void readnumber(Token token, long *nr)
#else
void readnumber(token,nr)
 Token token;
 long *nr;
#endif
 {
  *nr = SEMVAL(token);
 }

