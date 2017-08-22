
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
{*  Segment: genactio.c                                            *}
{*  Version: 20/05/91                                              *}
{*                                                                 *}
{*  Sprache: C                                                     *}
{*                                                                 *}
{*-----------------------------------------------------------------*}
{*                                                                 *}
{*  Beschreibung:                                                  *}
{*  Generiert aus den gespeicherten Aktionen, Aktionsmakros und    *}
{*  den SpecialActions eine grosse Case-Anweisung, die die         *}
{*  Aktionen des fertigen Scanners enthaelt                        *}
{*  Die Ausgabe erfolgt in die Datei actions pascal a              *}
{*  Inhalt:                                                        *}
{*        StrContains                                              *}
{*        StrInsert                                                *}
{*        RepInString                                              *}
{*        expand_makro                                             *}
{*        writeProgString                                          *}
{*        writeActionMakro                                         *}
{*        ActioFile                                                *}
{*             WriteSpecial                                        *}
{*                                                                 *}
{*-----------------------------------------------------------------*}
{*                                                                 *}
{*                 M O D I F I K A T I O N E N                     *}
{*=================================================================*}
{* Datum      modifiziert von    Beschreibung der Modifikation     *}
{*=================================================================*}
{*******************************************************************/

/* define DEBUG */

#include "buffer.h"
#include "strfunctions.h"
#include "symtab.h"

#include "global.h"

#include "stateset.h"
#include "eveset.h"

#include "genactio.h"
#ifdef __STDC__
#include "scan.h"
#endif /* not ! __STDC__ */
#include "alexerr.h"
#include "alexsem.h"


#ifdef __STDC__
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#endif

#include <stdio.h>


/* Bauernfeind: 17.06.93; Globale Variablen aus var.c */
extern int MaxState;
extern int MaxAction;
extern int MAX_ID_NO;
extern MakroTable MakTable;


 
/*******************************************************************}
{*                                                                 *}
{*  Prozedur: expand_makro            Version:  20/05/91           *}
{*                                                                 *}
{*******************************************************************}
{*                                                                 *}
{*  Klassifizierung:  Prozedur                                     *}
{*                                                                 *}
{*  Funktionsbeschreibung:                                         *}
{*  Expandiert den Makro der durch Progstring angegeben ist, indem *}
{*  formale Parameter der Art %1, %2, .. usw. durch den entspre-   *}
{*  chenden Parameter (Integer oder Identifikator) ersetzt         *}
{*-----------------------------------------------------------------*}
{*                                                                 *}
{*  Eingabeparameter:                                              *}
{*  parameters                parstring                            *}
{*  ParCount                  int                                  *}
{*  Transientparameter:                                            *}
{*  progstring                Actionstring                         *}
{*  Seiteneffekte:                                                 *}
{*                                                                 *}
{*  Lokale Variablen:                                              *}
{*  i                         int                                  *}
{*******************************************************************/

#ifdef __STDC__
void ExpandMacro(struct ActionString *progstr,
                 struct varfilestring *par,
                 int cnt)
{ int i;
#else /* ! __STDC__ */
void ExpandMacro(progstr,par,cnt)
struct ActionString *progstr;
parstrings par;
int cnt;
  { int i;
#endif /* ! __STDC__ */
    for(i=1;i<=cnt;i++)
      { 
#ifdef DEBUG        
    printf("Makro %s\n",strtocstr(progstr));
    printf("ParNo %d  ParStr %s\n",i,strtocstr(par[i]));
#endif
        STRrepinstring(&par[i],i,progstr);
#ifdef DEBUG   
    printf("Expand. Makro %s\n",strtocstr(progstr));
#endif
      }   
  }
 

/*******************************************************************}
{*                                                                 *}
{*  Prozedur: writeProgString         Version:  20/05/91           *}
{*                                                                 *}
{*******************************************************************}
{*                                                                 *}
{*  Klassifizierung:  Prozedur                                     *}
{*                                                                 *}
{*  Funktionsbeschreibung:                                         *}
{*  Schreibt einen Progstring in den Ausgabefile zielfile          *}
{*  Dabei werden immer, wenn im String ein chr(13) gefunden wird   *}
{*  Zeilenvorschuebe ausgeloest, weil Pascal dies nicht automatisch*}
{*  bei langen Strings macht. Wuerde Pascal ueberlange Strings     *}
{*  mit Zeilenumbruch ausgeben, so waere diese Prozedur nicht      *}
{*  noetig                                                         *}
{*-----------------------------------------------------------------*}
{*                                                                 *}
{*  Eingabeparameter:                                              *}
{*  progString                string                               *}
{*  Transientparameter:                                            *}
{*  zielfile                  text                                 *}
{*  Seiteneffekte:                                                 *}
{*                                                                 *}
{*  Lokale Variablen:                                              *}
{*  i                         integer32                            *}
{*******************************************************************/

#ifdef __STDC__
void WriteProgString(FILE *file, struct tokenstring *str)
{
#else /* ! __STDC__ */
void WriteProgString(file,str)
FILE *file;
struct tokenstring *str;
  {
#endif /* ! __STDC__ */
  int i;
#ifdef DEBUG
  printf("======> WRITEPROGSTRING %s\n",strtocstr(str));
#endif
  for(i=0;i<str->length;i++)
    {
    if(str->body[i]=='\r')
      { 
      fputc('\n',file);
      }
    else
      {
      fputc(str->body[i],file);
      }  
    }
  }
   
        
/*******************************************************************}
{*                                                                 *}
{*  Prozedur: writeActionMakro        Version:  20/05/91           *}
{*                                                                 *}
{*******************************************************************}
{*                                                                 *}
{*  Klassifizierung:  Prozedur                                     *}
{*                                                                 *}
{*  Funktionsbeschreibung:                                         *}
{*  Liest einen Makro aus der Makrotabelle, decodiert ihn und      *}
{*  expandiert ihn. Schreibt den Makro in den zielfile             *}
{*-----------------------------------------------------------------*}
{*                                                                 *}
{*  Eingabeparameter:                                              *}
{*  Maknumber                 integer32                              *}
{*  pars                      partype                              *}
{*  Transientparameter:                                            *}
{*  zielfile                  text                                 *}
{*  Seiteneffekte:                                                 *}
{*                                                                 *}
{*  Lokale Variablen:                                              *}
{*  makro                     MakTabEntry                          *}
{*  progstring                Actionstring                         *}
{*  parameters                parstrings                           *}
{*  I                         Integer                              *}
{*******************************************************************/

#ifdef __STDC__
void writeActionMacro(int num, int *par, FILE *file)
{
#else /* ! __STDC__ */
void writeActionMacro(num,par,file)
int num;
partype par;
FILE *file;
  {
#endif /* ! __STDC__ */
  struct MakTabEntry makro;
  struct ActionString progstring;
  char *s;
  parstrings parameters;
  int i;

  makro=MakTable[num];

  if( makro.MakArt!=actmak )
    {
    AERAlexRecoverableError(1,NULL);
    }
  else
    {
    s= SYDecSymtab( ProgCC,makro.MakString );
    progstring.length=strlen(s);
    strcpy(progstring.body,s);

    for( i=1; i <=makro.MakParCount;i++)
      {
       s= SYDecSymtab(StrCC,par[i]);
       parameters[i].length=strlen(s);
       strcpy(parameters[i].body,s);
      }
    ExpandMacro(&progstring,parameters,makro.MakParCount);
    WriteProgString(file,(struct tokenstring *)&progstring);
    }
  }


/*******************************************************************}
{*                                                                 *}
{*  Prozedur: WriteSpecial            Version:  20/05/91           *}
{*                                                                 *}
{*******************************************************************}
{*                                                                 *}
{*  Klassifizierung:  Prozedur                                     *}
{*                                                                 *}
{*  Funktionsbeschreibung:                                         *}
{*  Schreibt eine Spezialaktion, die durch eine verkettete Liste   *}
{*  von Progstring gegeben ist, in den Zielfile                    *}
{*-----------------------------------------------------------------*}
{*                                                                 *}
{*  Eingabeparameter:                                              *}
{*  list                      SpecLPoint                           *}
{*  Seiteneffekte:                                                 *}
{*  Ausgabe                                                        *}
{*  Lokale Variablen:                                              *}
{*  lauf                      SpecLPoint                           *}
{*******************************************************************/


#ifdef __STDC__
void WriteSpecial(FILE *file, SpecLPoint list)
{
#else /* ! __STDC__ */
void WriteSpecial(file,list)
SpecLPoint list;
FILE *file;
  {
#endif /* ! __STDC__ */
  char *help;
  SpecLPoint lauf;
  lauf=list;


  while(lauf!=NULL)
    {

    help = SYDecSymtab(ProgCC,lauf->ElemStr);

    fprintf( file,"%s", help );
    lauf=lauf->ElemNachfolger;
    }
  }

/*******************************************************************}
{*                                                                 *}
{*  Prozedur: ActioFile               Version:  20/05/91           *}
{*                                                                 *}
{*******************************************************************}
{*                                                                 *}
{*  Klassifizierung:  Prozedur                                     *}
{*                                                                 *}
{*  Funktionsbeschreibung:                                         *}
{*  Hauptprozedur dieses Segments. Generierung der zentralen       *}
{*  Case-Anweisung und der Specialactions                          *}
{*-----------------------------------------------------------------*}
{*                                                                 *}
{*  Eingabeparameter:                                              *}
{*  incode                    boolean                              *}
{*  Transientparameter:                                            *}
{*  outcode                   boolean                              *}
{*  Seiteneffekte:                                                 *}
{*  Erzugung des Aktionsfiles actions pascal a                     *}
{*  Lokale Variablen:                                              *}
{*  actionfile                text                                 *}
{*  ActLauf                   integer32                              *}
{*  Lokale Prozeduren und Funktionen:                              *}
{*             WriteSpecial                                        *}
{*******************************************************************/

#ifdef __STDC__
void ActioFile(int incode, int *outcode)
#else /* ! __STDC__ */
void ActioFile(incode,outcode)
int incode,*outcode;
#endif /* ! __STDC__ */
{ FILE *actionfile;
  int  ActLauf;
  
  *outcode = incode;
  if (incode=1)
  { /* Datei fuer Aktionen oeffnen */

    actionfile = fopen("actions.c","w");
    if (actionfile == NULL) 
      { printf("Fehler beim oeffnen von actions.c\n");
        exit(1);
      }
    /********************************************************
     Kopf des Actionmodules
    ********************************************************/
    fprintf(actionfile,"#include <stdio.h>\n\n");
    fprintf(actionfile,"#include \"scan.h\"\n\n");

    /********************************************************
     Eigene ExternalDefinitionen fuer die
     unterschiedlichen Aktionen, die
     im fertigen Scanner nach aussen gereicht werden
    ********************************************************/
    fprintf(actionfile,"extern int abort_scan;\n");
    fprintf(actionfile,"int ignore_case = ");
    if (flags[ignorecase] == 1)
      fprintf(actionfile,"1; /* TRUE */\n");
    else  
      fprintf(actionfile,"0; /* FALSE */\n\n");

    /******************************
     Makrodefinition TOKEN
    ******************************/
    fprintf(actionfile,"#define TOKEN Action_tok\n");

    /********************************************************
     Externaldefinitions, wie sie vom
     Benutzer definiert wurden
    ********************************************************/
    WriteSpecial(actionfile,SpecActions[spextern]); 
    /********************************************************
     Generierung von ACTDo_Action
    ********************************************************/
    fprintf(actionfile,"void ACTDo_Action(Action_tok,Action_nr)\n");
    fprintf(actionfile,"Token Action_tok;\n");
    fprintf(actionfile,"int Action_nr;\n");
    fprintf(actionfile,"{ switch (Action_nr) {\n");
    fprintf(actionfile,"  case 0   : MEMugRecoverableError(6);\n           break;\n");
    for(ActLauf=1;ActLauf<Actnumber;ActLauf++)
    { fprintf(actionfile,"  case %d    : ",ActLauf);
      if (ActTable[ActLauf].ignore == 1)
        fprintf(actionfile,"abort_scan = 0; /*FALSE*/\n             ");
      else
        fprintf(actionfile,"abort_scan = 1; /*TRUE*/\n             ");
      if (ActTable[ActLauf].makro == 1)      

      writeActionMacro(ActTable[ActLauf].maknumber,ActTable[ActLauf].parameters,actionfile);
      else
        { if (ActTable[ActLauf].strnumber!=0)
           
     fprintf(actionfile,"%s",SYDecSymtab(ProgCC,ActTable[ActLauf].strnumber));
#ifdef DEBUG 
  else printf(" ===> STRNUMBER in ACTDo_Actions : %d\n\n",ActTable[ActLauf].strnumber);
#endif
        }
      fprintf(actionfile,"\n              break;\n"); 
    }
    fprintf(actionfile,"  }\n}\n\n");

    /********************************************************
     Generierung von ACTEnd_Action
    ********************************************************/
    fprintf(actionfile,"void ACTEnd_Action(Action_tok)\n");
    fprintf(actionfile,"Token Action_tok;\n{ ");
    WriteSpecial(actionfile,SpecActions[spscanexit]);
    fprintf(actionfile,"}\n\n");

    /********************************************************
     Generierung von ACTInit_Action
    ********************************************************/
    fprintf(actionfile,"void ACTInitAction()\n{ ");
    WriteSpecial(actionfile,SpecActions[spscaninit]);
    fprintf(actionfile,"}\n\n");

    /********************************************************
     Generierung von ACTError_Action
    ********************************************************/
    fprintf(actionfile,"void ACTError_Action()\n{ ");
    WriteSpecial(actionfile,SpecActions[spscanerror]);
    fprintf(actionfile,"}\n\n");
    fclose(actionfile);
    printf("actions.c erzeugt  ( Aktionen des Scanners )\n");
   }
 }
