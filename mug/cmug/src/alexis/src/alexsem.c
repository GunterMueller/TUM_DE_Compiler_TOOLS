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
{*  Segment: alexsem3.c                                            *}
{*  Version: 24/05/91                                              *}
{*                                                                 *}
{*  Sprache: C                                                     *}
{*                                                                 *}
{*-----------------------------------------------------------------*}
{*                                                                 *}
{*  Beschreibung:                                                  *}
{*  Implementierung der semantischen Aktionen, die zur Befriedi-   *}
{*  gung der Aufrufe aus dem MUG-Baumauswerter benoetigt werden    *}
{*  Dieses Segment ruft die Stackmaschine, den Komprimierer,       *}
{*  die Tabellengenerierung und die Generirung des Aktionsfiles    *}
{*  auf und ist somit auch fuer die Fehlermeldungen verantwort-    *}
{*  die im Protokoll auftauchen (einzige Ausnahme GENACTIO PASCAL  *}
{*  Inhalt:                                                        *}
{*  Initialisierungsprozeduren:                                    *}
{*        init_MakroTable                                          *}
{*        init_SpecActions                                         *}
{*        init_flags                                               *}
{*  Interne Prozeduren                                             *}
{*        InitAlexis                                               *}
{*  Externe Prozeduren fuer den Aufruf durch den MUG-Auswerter     *}
{*        skompress                                                *}
{*        sgentable                                                *}
{*        SGenActions                                              *}
{*        GenEProg                                                 *}
{*        GenMOne                                                  *}
{*        GenZero                                                  *}
{*        GenEmptPars                                              *}
{*        SetInstFl                                                *}
{*        DispLexMak                                               *}
{*        SMyhill                                                  *}
{*        SNegate                                                  *}
{*        SMinimize                                                *}
{*        InstActMak                                               *}
{*        StoreSpec                                                *}
{*        InstLexMak                                               *}
{*        SAlternative                                             *}
{*        InsParam                                                 *}
{*        SemIntToStr                                              *}
{*        inttostring                                              *}
{*        SemStrToStr                                              *}
{*        ChkFormPar                                               *}
{*        DefMakAct                                                *}
{*        DefAction                                                *}
{*        SConcat                                                  *}
{*        SMultiply                                                *}
{*        RegOperator                                              *}
{*        StringToAut                                              *}
{*        ExpndLexMak                                              *}
{*        SAllbut                                                  *}
{*        ComplSet                                                 *}
{*        makeset                                                  *}
{*        union_sets                                               *}
{*        SSetToAut                                                *}
{*        SStrToAut                                                *}
{*                                                                 *}
{*-----------------------------------------------------------------*}
{*                                                                 *}
{*                 M O D I F I K A T I O N E N                     *}
{*=================================================================*}
{* Datum      modifiziert von    Beschreibung der Modifikation     *}
{*=================================================================*}
{*                                                                 *}
{*******************************************************************/

#define version "version 25/05/91/FrEi"
#define TRUE 1
#define FALSE 0

#ifdef __STDC__
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#endif

#include <stdio.h>

#include "cdebug.h"

#include "AttrGlob.h"


/* Include Files fuer die MUG-Backend */
#include "buffer.h"
#include "symtab.h"
#include "actions.h"
#include "mugactio.h"

/* Include Files fuer die Stackmaschine */
#include "stateset.h"
#include "error.h"
#include "quickset.h"
#include "eveset.h"
#include "autops.h"
#include "autstack.h"
#include "minimier.h"
#include "kompress.h"
#include "maketab.h"
#include "alexerr.h"
#include "alexsem.h"
#include "genactio.h"
#include "strfunctions.h"



/* Bauernfeind: 17.06.93; Globale Variablen aus var.c */
#include "var.h"
extern int MaxState;
extern int MaxAction;
extern int MaxKomprState;
extern int MaxKomprKanten;
extern int MAX_ID_NO;
extern MakroTable MakTable;



/* Bauernfeind: Prototypen, 9.6.93 */
extern void *realloc();
#ifdef __STDC__
extern void initkompress(void);
extern void ActioFile(int, int*);
#endif



/*****************************************************************
	  I M P L E M E N T I E R U N G :
	  L O K A L E    R O U T I N E N
		  I N I T I A L I S I E R U N G S P R O Z E D U R E N
 ****************************************************************}
 
{*********************************************************
          I N I T I A L I S I E R U N G
 *********************************************************}
{*******************************************************************}
{*                                                                 *}
{*  Prozedur: init_MakroTable         Version:  25/05/91           *}
{*                                                                 *}
{*******************************************************************}
{*                                                                 *}
{*  Klassifizierung:  Prozedur                                     *}
{*                                                                 *}
{*  Funktionsbeschreibung:                                         *}
{*  Belegt die Makrotabelle mit leeren Makros (Konstante unused)   *}
{*-----------------------------------------------------------------*}
{*                                                                 *}
{*  Seiteneffekte:                                                 *}
{*  Initialisierung                                                *}
{*  Lokale Variablen:                                              *}
{*  lauf                      id_numb_Type (int)                   *}
{*******************************************************************/

#ifdef __STDC__
void init_MakroTable(void)
#else /* ! __STDC__ */
void init_MakroTable()
#endif /* ! __STDC__ */
{ int lauf;
  MakTable = malloc((MAX_ID_NO+1)*sizeof(struct MakTabEntry));
  for(lauf=0;lauf<=MAX_ID_NO;MakTable[lauf++].MakArt=unused);
}
 

/*******************************************************************}
{*                                                                 *}
{*  Prozedur: init_SpecActions        Version:  25/05/91           *}
{*                                                                 *}
{*******************************************************************}
{*                                                                 *}
{*  Klassifizierung:  Prozedur                                     *}
{*                                                                 *}
{*  Funktionsbeschreibung:                                         *}
{*  Die Specialactions sind Listen von Progstrings. Alle diese     *}
{*  Listen werden nil gesetzt                                      *}
{*-----------------------------------------------------------------*}
{*                                                                 *}
{*  Seiteneffekte:                                                 *}
{*                                                                 *}
{*  Lokale Variablen:                                              *}
{*  lauf                      SpecType                             *}
{*******************************************************************/ 
 
#ifdef __STDC__
void init_SpecActions(void)
#else /* ! __STDC__ */
void init_SpecActions()
#endif /* ! __STDC__ */
{ SpecType lauf;
  for(lauf=spextern;lauf<=spscanerror;SpecActions[lauf++]=spunused);
}


/*******************************************************************}
{*                                                                 *}
{*  Prozedur: init_flags              Version:  25/05/91           *}
{*                                                                 *}
{*******************************************************************}
{*                                                                 *}
{*  Klassifizierung:  Prozedur                                     *}
{*                                                                 *}
{*  Funktionsbeschreibung:                                         *}
{*  Initialisiert alle Flags des Uebersetzers, die Ausgabe und     *}
{*  Verhalten steuern mit FALSE. Die Flags koennen in der          *}
{*  Beschreibung ueber OPTIONS .. gesetzt werden                   *}
{*-----------------------------------------------------------------*}
{*                                                                 *}
{*  Seiteneffekte:                                                 *}
{*                                                                 *}
{*  Lokale Variablen:                                              *}
{*  i                         instruction                          *}
{*******************************************************************/

#ifdef __STDC__
void init_flags(void)
#else /* ! __STDC__ */
void init_flags()
#endif /* ! __STDC__ */
{ instruction i;
  for(i=ignorecase;i<=minimal;flags[i++]=FALSE);
}

#ifdef __STDC__
void decode(struct ActionString *ErgString, int ClassCode, int RelCode)
#else /* ! __STDC__ */
void decode(ErgString,ClassCode,RelCode)
struct ActionString *ErgString;
int ClassCode,RelCode;
#endif /* ! __STDC__ */
{ struct ActionString help;
  char *s;

  _BEGIN_
  if (ClassCode==16)
    STRinttostring(RelCode,(struct varfilestring *)ErgString);
  else
    { 
      s =  SYDecSymtab(ClassCode,RelCode);
      help.length=strlen(s);
      strcpy(help.body,s);
      STRssubstring(ErgString,&help,1,128);
    }
  _END_
}
  

 
/*********************************************************
	  I M P L E M E N T I E R U N G
	  G L O B A L E R    R O U T I N E N
 *********************************************************}
 
{*******************************************************************}
{*                                                                 *}
{*  Prozedur: InitAlexis              Version:  25/05/91           *}
{*                                                                 *}
{*******************************************************************}
{*                                                                 *}
{*  Klassifizierung:  Prozedur                                     *}
{*                                                                 *}
{*  Funktionsbeschreibung:                                         *}
{*  Ruft die Initialisierungsprozeduren saemtlicher Segmente       *}
{*  auf .. wird in der Produktion P1 der AG angestossen            *}
{*  Ruft ausserdem die Initialisierung fuer die Datenstrukturen    *}
{*  dieses Segmentes auf                                           *}
{*-----------------------------------------------------------------*}
{*                                                                 *}
{*  Eingabeparameter:                                              *}
{*  incode                    boolean                              *}
{*  Transientparameter:                                            *}
{*  outcode                   boolean                              *}
{*  Seiteneffekte:                                                 *}
{*                                                                 *}
{*******************************************************************/

#ifdef __STDC__
extern void InitAlexis(BOOL incode, BOOL *outcode)
#else /* ! __STDC__ */
extern void InitAlexis(incode,outcode)
BOOL incode,*outcode;
#endif /* ! __STDC__ */
{ _BEGIN_
  *outcode = incode;
  Actnumber=1;

  /* Bauernfeind: 16.06.93; Initialisierung globaler dynamischer */
  /*                        Variablen.(Delta, ActionTable)       */
  MaxState = 1000;
  MaxAction = 100;
  MAX_ID_NO = 200;
  MaxKomprState = 500; 
  MaxKomprKanten = 1000; 
  Delta = malloc((MaxState+1)*sizeof(KantenMenge));
  ActionTable = malloc((MaxState+1)*sizeof(Action));
  ActTable = malloc((MaxAction+1)*sizeof(struct ActTbEintr));

  init_MakroTable();
  init_flags();
  initerror();
  initeveset();
  initstateset();
  initquickset();
  initautops();
  initautstack();
  initkompress();
  initmaketab();
  initminimier();
  printf("\nALEXIS V 2.0 (Advanced lexical instrument for scannergeneration)\n");
  printf("(c) TU Muenchen 3. Juni 1991\n\n");
  _END_
}


/*******************************************************************}
{*                                                                 *}
{*  Prozedur: skompress               Version:  25/05/91           *}
{*                                                                 *}
{*******************************************************************}
{*                                                                 *}
{*  Klassifizierung:  Prozedur                                     *}
{*                                                                 *}
{*  Funktionsbeschreibung:                                         *}
{*  Aufruf des Komprimierers , genaue Funktionsbeschreibung des    *}
{*  des Komprimierers siehe Segment KOMPRESS PASCAL                *}
{*-----------------------------------------------------------------*}
{*                                                                 *}
{*  Eingabeparameter:                                              *}
{*  incode                    boolean                              *}
{*  inaut                     automat                              *}
{*  Transientparameter:                                            *}
{*  outclass                  classDescr                           *}
{*  outkompr                  boolean                              *}
{*  outcode                   boolean                              *}
{*  Seiteneffekte:                                                 *}
{*                                                                 *}
{*******************************************************************/

#ifdef __STDC__
extern void SKompress(BOOL incode, AUTOMAT inaut, BOCLKO *outcodeclasskompr)
#else /* ! __STDC__ */
extern void SKompress(incode,inaut,outcodeclasskompr)
BOOL incode;
BOCLKO *outcodeclasskompr;
AUTOMAT inaut;
#endif /* ! __STDC__ */
{ BOOL *outcode;
  CLASSDESC *outclass;
  KOMPRUEB *outkompr;
#ifdef DEBUG
  printf("\n\nAUTOMAT vor COMPRESS\n\n");
  PrintAutomat(inaut);
#endif

  /* Bauernfeind: 24.06.93; Initialisierung von KomprUeg-Struktur: */
  /*                        Variable outcodeclasskompr->komprueg   */
  outcodeclasskompr->komprueb.Default = malloc((MaxKomprState+1)*sizeof(KomprState));
  outcodeclasskompr->komprueb.Base    = malloc((MaxKomprState+1)*sizeof(int));
  outcodeclasskompr->komprueb.Next    = malloc((MaxKomprKanten+1)*sizeof(int));
  outcodeclasskompr->komprueb.Check   = malloc((MaxKomprKanten+1)*sizeof(KomprState));
  outcodeclasskompr->komprueb.Actions = malloc((MaxKomprState+1)*sizeof(Action));
  outcodeclasskompr->komprueb.Actions[0] = 0;
  outcodeclasskompr->komprueb.Base[0] = 0;
  
  outcode = &(outcodeclasskompr->bool);
  outclass = &(outcodeclasskompr->classdesc);
  outkompr = &(outcodeclasskompr->komprueb);
  _BEGIN_
  *outcode=incode;
  if (incode) {
         printf("Automat wird komprimiert\n");
         Compress(inaut,outclass,outkompr);
              } 
  _END_
}
 

/*******************************************************************}
{*                                                                 *}
{*  Prozedur: sgentable               Version:  25/05/91           *}
{*                                                                 *}
{*******************************************************************}
{*                                                                 *}
{*  Klassifizierung:  Prozedur                                     *}
{*                                                                 *}
{*  Funktionsbeschreibung:                                         *}
{*  Aufruf des Tabellengenarators .   Funktionsbeschreibung des    *}
{*  des Tabellengenerators siehe Segment MAKETAB PASCAL            *}
{*-----------------------------------------------------------------*}
{*                                                                 *}
{*  Eingabeparameter:                                              *}
{*  incode                    boolean                              *}
{*  inkompr                   komprUebergang                       *}
{*  inclass                   ClassDesr                            *}
{*  Transientparameter:                                            *}
{*  outcode                   boolean                              *}
{*  Seiteneffekte:                                                 *}
{*                                                                 *}
{*******************************************************************/

#ifdef __STDC__
extern void sgentable(BOOL incode,
                      KOMPRUEB inkompr,
                      CLASSDESC inclass,
                      BOOL *outcode)
#else /* ! __STDC__ */
extern void sgentable(incode,inkompr,inclass,outcode)
BOOL incode,*outcode;
KOMPRUEB inkompr;
CLASSDESC inclass;
#endif /* ! __STDC__ */
{ _BEGIN_
  *outcode=incode;
  if (incode) gen_table(&inkompr,&inclass);
  _END_
}
 

/*******************************************************************}
{*                                                                 *}
{*  Prozedur: SGenActions             Version:  25/05/91           *}
{*                                                                 *}
{*******************************************************************}
{*                                                                 *}
{*  Klassifizierung:  Prozedur                                     *}
{*                                                                 *}
{*  Funktionsbeschreibung:                                         *}
{*  Aufruf der Prozedur ActioFile, die die Datei mit den Aktionen  *}
{*  Erzeugt. Es wird ein compilierbares Pascal-Programm erzeugt    *}
{*  Dokumentation siehe Segment GENACTIO PASCAL                    *}
{*-----------------------------------------------------------------*}
{*                                                                 *}
{*  Eingabeparameter:                                              *}
{*  incode                    boolean                              *}
{*  Transientparameter:                                            *}
{*  outcode                   boolean                              *}
{*  Seiteneffekte:                                                 *}
{*                                                                 *}
{*******************************************************************/

#ifdef __STDC__
extern void SGenActions(BOOL incode, BOOL *outcode)
#else /* ! __STDC__ */
extern void SGenActions(incode,outcode)
BOOL incode,*outcode;
#endif /* ! __STDC__ */
{ _BEGIN_
  *outcode = incode;
  if (incode) ActioFile(incode,outcode);
  _END_
}
 

/*******************************************************************}
{*                                                                 *}
{*  Prozedur: GenEProg                Version:  25/05/91           *}
{*                                                                 *}
{*******************************************************************}
{*                                                                 *}
{*  Klassifizierung:  Prozedur                                     *}
{*                                                                 *}
{*  Funktionsbeschreibung:                                         *}
{*  Erzeugt einen leeres Progstringsy                              *}
{*-----------------------------------------------------------------*}
{*                                                                 *}
{*  Transientparameter:                                            *}
{*  out                       progstrings                          *}
{*  Seiteneffekte:                                                 *}
{*                                                                 *}
{*******************************************************************/

#ifdef __STDC__
extern void GenEProg(PROGSTRINGSY *out)
#else /* ! __STDC__ */
extern void GenEProg(out)
PROGSTRINGSY *out;
#endif /* ! __STDC__ */
{ out->semval=0;
  out->ort.zeile=0;
  out->ort.spalte=0;
  out->ort.fname = "";
}

 
/*******************************************************************}
{*                                                                 *}
{*  Prozedur: GenMOne                 Version:  25/05/91           *}
{*                                                                 *}
{*******************************************************************}
{*                                                                 *}
{*  Klassifizierung:  Prozedur                                     *}
{*                                                                 *}
{*  Funktionsbeschreibung:                                         *}
{*  Generiert ein Integersy mit dem Wert -1                        *}
{*-----------------------------------------------------------------*}
{*                                                                 *}
{*  Transientparameter:                                            *}
{*  out                       integersy                            *}
{*  Seiteneffekte:                                                 *}
{*                                                                 *}
{*******************************************************************/

#ifdef __STDC__
extern void GenMOne(INTEGERSY *out)
#else /* ! __STDC__ */
extern void GenMOne(out)
INTEGERSY *out;
#endif /* ! __STDC__ */
{ out->semval= -1;
  out->ort.zeile=0;
  out->ort.spalte=0;
  out->ort.fname = "";
}
 

/*******************************************************************}
{*                                                                 *}
{*  Prozedur: GenZero                 Version:  25/05/91           *}
{*                                                                 *}
{*******************************************************************}
{*                                                                 *}
{*  Klassifizierung:  Prozedur                                     *}
{*                                                                 *}
{*  Funktionsbeschreibung:                                         *}
{*  Generiert ein Integersy mit dem Wert 0                         *}
{*-----------------------------------------------------------------*}
{*                                                                 *}
{*  Transientparameter:                                            *}
{*  out                       integersy                            *}
{*  Seiteneffekte:                                                 *}
{*                                                                 *}
{*******************************************************************/

#ifdef __STDC__
extern void GenZero(INTEGERSY *out)
#else /* ! __STDC__ */
extern void GenZero(out)
INTEGERSY *out;
#endif /* ! __STDC__ */
{ out->semval=0;
  out->ort.zeile=0;
  out->ort.spalte=0;
  out->ort.fname = "";
}
 

/*******************************************************************}
{*                                                                 *}
{*  Prozedur: GenEmptPars             Version:  25/05/91           *}
{*                                                                 *}
{*******************************************************************}
{*                                                                 *}
{*  Klassifizierung:  Prozedur                                     *}
{*                                                                 *}
{*  Funktionsbeschreibung:                                         *}
{*  Erzeugt ein leeres Parameterarray zur Aufnahme der Aufruf-     *}
{*  parameter eines Aktionsmakros.                                 *}
{*-----------------------------------------------------------------*}
{*                                                                 *}
{*  Transientparameter:                                            *}
{*  empty                     partype                              *}
{*  Seiteneffekte:                                                 *}
{*                                                                 *}
{*  Lokale Variablen:                                              *}
{*  i                         integer32                            *}
{*******************************************************************/

#ifdef __STDC__
extern void GenEmptPars(PARTYPE *empty)
#else /* ! __STDC__ */
extern void GenEmptPars(empty)
PARTYPE *empty;
#endif /* ! __STDC__ */
{ int i;
  for(i=0;i<=9;empty->par[i++]=0);
}
 

/*******************************************************************}
{*                                                                 *}
{*  Prozedur: SetInstFl               Version:  25/05/91           *}
{*                                                                 *}
{*******************************************************************}
{*                                                                 *}
{*  Klassifizierung:  Prozedur                                     *}
{*                                                                 *}
{*  Funktionsbeschreibung:                                         *}
{*                                                                 *}
{*  Erhaelt als Eingabe ein InstructSy, also ein Terminal der      *}
{*  Art minimize, target pascal, code ascii o.a.                   *}
{*  Prueft ob das zugehoerige Flag schon gesetzt ist und gibt      *}
{*  eine Fehlermeldung aus, falls die gewaehlte Option zu          *}
{*  einer bereits gesetzten im logischen Widerspruch steht         *}
{*  Beispiel:   code ascii    und   code ebcdic                    *}
{*  sind unvereinbare Optionen                                     *}
{*                                                                 *}
{*-----------------------------------------------------------------*}
{*                                                                 *}
{*  Eingabeparameter:                                              *}
{*  incode                    boolean                              *}
{*  innum                     instructsy                           *}
{*  Transientparameter:                                            *}
{*  outcode                   boolean                              *}
{*  Seiteneffekte:                                                 *}
{*                                                                 *}
{*  Lokale Variablen:                                              *}
{*  inst                      instruction                          *}
{*  gueltig                   boolean                              *}
{*******************************************************************/

#ifdef __STDC__
extern void SetInstFl(BOOL incode, INSTRUCTSY innum, BOOL *outcode)
#else /* ! __STDC__ */
extern void SetInstFl(incode,innum,outcode)
BOOL incode;
INSTRUCTSY innum;
BOOL *outcode;
#endif /* ! __STDC__ */
{ instruction inst;
  *outcode = incode;
  _BEGIN_
  inst = (instruction) innum.semval-1;
  if (flags[inst]) {
        AERAlexRecoverableError(2,&(innum.ort));
        *outcode = FALSE;
          }
    else flags[inst] = TRUE;
  _END_
}


/*******************************************************************}
{*                                                                 *}
{*  Prozedur: DispLexMak              Version:  25/05/91           *}
{*                                                                 *}
{*******************************************************************}
{*                                                                 *}
{*  Klassifizierung:  Prozedur                                     *}
{*                                                                 *}
{*  Funktionsbeschreibung:                                         *}
{*  Verwirft alle lexikalischen Makros, indem die zugehoerigen     *}
{*  Automaten vom Heap geloescht werden                            *}
{*-----------------------------------------------------------------*}
{*                                                                 *}
{*  Eingabeparameter:                                              *}
{*  inautomat                 automat                              *}
{*  icode                     boolean                              *}
{*  Transientparameter:                                            *}
{*  outautomat                automat                              *}
{*  dcode                     boolean                              *}
{*  Seiteneffekte:                                                 *}
{*                                                                 *}
{*  Lokale Variablen:                                              *}
{*  i                         id_numb_type                         *}
{*******************************************************************/

#ifdef __STDC__
extern void DispLexMak(AUTOMAT inautomat, BOOL icode, AUTBOOL *outautomatdcode)
#else /* ! __STDC__ */
extern void DispLexMak(inautomat,icode,outautomatdcode)
AUTOMAT inautomat;
BOOL icode;
AUTBOOL *outautomatdcode;
#endif /* ! __STDC__ */
{ BOOL *dcode;
  AUTOMAT *outautomat;
  int i;
  _BEGIN_
  outautomat = &(outautomatdcode->automat);
  dcode      = &(outautomatdcode->bool);
  *outautomat = inautomat;
  *dcode = icode;
#ifdef DEBUG
  printf("\n\nAUTOMAT in DISPLEXMAK\n\n");
  PrintAutomat(inautomat);
#endif
  if(icode)
    { for(i=0;i<=MAX_ID_NO;i++)
        { if(MakTable[i].MakArt==lexmak)
             { DisposeAutomaton(MakTable[i].MakAutomat);
               MakTable[i].MakAutomat = NULL;
             }
        }
    }
  _END_
} 


/*******************************************************************}
{*                                                                 *}
{*  Prozedur: SMyhill                 Version:  25/05/91           *}
{*                                                                 *}
{*******************************************************************}
{*                                                                 *}
{*  Klassifizierung:  Prozedur                                     *}
{*                                                                 *}
{*  Funktionsbeschreibung:                                         *}
{*  Aufruf der Myhill-Prozedur. Diese wird im Segment              *}
{*  AUTSTACK PASCAL naeher beschrieben                             *}
{*-----------------------------------------------------------------*}
{*                                                                 *}
{*  Eingabeparameter:                                              *}
{*  inautomat                 Automat                              *}
{*  incode                    boolean                              *}
{*  Transientparameter:                                            *}
{*  outautomat                Automat                              *}
{*  outcode                   boolean                              *}
{*  Seiteneffekte:                                                 *}
{*                                                                 *}
{*******************************************************************/

#ifdef __STDC__
extern void SMyhill(AUTOMAT inautomat, BOOL incode, AUTBOOL *outautomatcode)
#else /* ! __STDC__ */
extern void SMyhill(inautomat,incode,outautomatcode)
AUTOMAT inautomat;
BOOL incode;
AUTBOOL *outautomatcode;
#endif /* ! __STDC__ */
{ AUTOMAT *outautomat;
  BOOL *outcode;
  _BEGIN_
  outautomat = &(outautomatcode->automat);
  outcode    = &(outautomatcode->bool);
  *outcode=incode;
#ifdef DEBUG
  printf("\n\nAUTOMAT vor MYHILL\n\n"); 
  PrintAutomat(inautomat);
#endif
  if (incode) Myhill(inautomat,outautomat);
#ifdef DEBUG
  printf("\n\nAUTOMAT nach MYHILL\n\n"); 
  PrintAutomat(*outautomat);
#endif




  _END_
} 


/*******************************************************************}
{*                                                                 *}
{*  Prozedur: SNegate                 Version:  25/05/91           *}
{*                                                                 *}
{*******************************************************************}
{*                                                                 *}
{*  Klassifizierung:  Prozedur                                     *}
{*                                                                 *}
{*  Funktionsbeschreibung:                                         *}
{*  Aufruf des Negierers fuer einen Automaten. Dieser wird in      *}
{*  AUTSTACK PASCAL naeher beschrieben                             *}
{*-----------------------------------------------------------------*}
{*                                                                 *}
{*  Eingabeparameter:                                              *}
{*  inautomat                 Automat                              *}
{*  Transientparameter:                                            *}
{*  outautomat                Automat                              *}
{*  Seiteneffekte:                                                 *}
{*                                                                 *}
{*******************************************************************/

#ifdef __STDC__
extern void SNegate(AUTOMAT inautomat, AUTOMAT *outautomat)
#else /* ! __STDC__ */
extern void SNegate(inautomat,outautomat)
AUTOMAT inautomat,*outautomat;
#endif /* ! __STDC__ */
{ Negate(inautomat,outautomat);
}
 

/*******************************************************************}
{*                                                                 *}
{*  Prozedur: SMinimize               Version:  25/05/91           *}
{*                                                                 *}
{*******************************************************************}
{*                                                                 *}
{*  Klassifizierung:  Prozedur                                     *}
{*                                                                 *}
{*  Funktionsbeschreibung:                                         *}
{*  Aufruf des Minimierers. Dieser wird in MINIMIER PASCAL naeher  *}
{*  beschrieben. Der Minimierer wird nur aufgerufen, wenn das      *}
{*  Flag, dass durch die Option MINIMIZE gesetzt werden kann, auf  *}
{*  TRUE steht. Der Minimierer wird aber auch noch von anderer     *}
{*  Stelle aus aufgerufen, naemlich bei der Allbut Operation       *}
{*  Das Segment mit dem Minimierer ist also unverzichtbar          *}
{*-----------------------------------------------------------------*}
{*                                                                 *}
{*  Eingabeparameter:                                              *}
{*  inautomat                 Automat                              *}
{*  incode                    boolean                              *}
{*  Transientparameter:                                            *}
{*  outautomat                Automat                              *}
{*  outcode                   boolean                              *}
{*  Seiteneffekte:                                                 *}
{*                                                                 *}
{*******************************************************************/

#ifdef __STDC__
extern void SMinimize(AUTOMAT inautomat, BOOL incode, AUTBOOL *outautomatcode)
#else /* ! __STDC__ */
extern void SMinimize(inautomat,incode,outautomatcode)
AUTOMAT inautomat;
BOOL incode;
AUTBOOL *outautomatcode;
#endif /* ! __STDC__ */
{ BOOL *outcode;
  AUTOMAT *outautomat;
  _BEGIN_

#ifdef DEBUG
  printf("\n\nAUTOMAT vor SMINIMIZE\n\n");
  PrintAutomat(inautomat);
#endif
 
  outautomat = &(outautomatcode->automat);
  outcode    = &(outautomatcode->bool);
  *outcode=incode;
  if ((incode) && (flags[minimal])) Minimize(inautomat,outautomat);
     else *outautomat=inautomat; 
#ifdef DEBUG
  printf("\n\nAUTOMAT nach SMINIMIZE\n\n");
  PrintAutomat(*outautomat);
#endif
  _END_
}


/*******************************************************************}
{*                                                                 *}
{*  Prozedur: InstActMak              Version:  25/05/91           *}
{*                                                                 *}
{*******************************************************************}
{*                                                                 *}
{*  Klassifizierung:  Prozedur                                     *}
{*                                                                 *}
{*  Funktionsbeschreibung:                                         *}
{*  Installiert einen Aktionsmakro in der Makrotabelle, deren      *}
{*  Struktur in GENTABLE COPY deklariert ist.                      *}
{*                                                                 *}
{*  Der Makro wird an der Stelle in der Tabelle abgelegt, die      *}
{*  durch die Nummer seines Identifikators markiert ist.           *}
{*                                                                 *}
{*  Es handelt sich hier um das definierende auftreten des Makros  *}
{*-----------------------------------------------------------------*}
{*                                                                 *}
{*  Eingabeparameter:                                              *}
{*  incode                    boolean                              *}
{*  inident                   stringsy                             *}
{*  inparanz                  integer32                              *}
{*  inprogstring              progstringsy                         *}
{*  Transientparameter:                                            *}
{*  outcode                   boolean                              *}
{*  Seiteneffekte:                                                 *}
{*  in der Datenstruktur v. GENTABLE COPY  siehe oben              *}
{*  Lokale Variablen:                                              *}
{*  erfolg                    boolean                              *}
{*******************************************************************/

#ifdef __STDC__
extern void InstActMak(BOOL incode,
                       IDENT inident,
                       INT inparanz,
                       PROGSTRINGSY inprogstring,
                       BOOL *outcode)
#else /* ! __STDC__ */
extern void InstActMak(incode,inident,inparanz,inprogstring,outcode)
BOOL incode,*outcode;
INT inparanz;
IDENT inident;
PROGSTRINGSY inprogstring;
#endif /* ! __STDC__ */
{ int erfolg;
  _BEGIN_
  *outcode=incode;
  switch(MakTable[inident.semval].MakArt) {
    case lexmak: *outcode=FALSE;
                 erfolg=FALSE;
                 AERAlexRecoverableError(4,&(inident.ort));
                 break;
    case actmak: erfolg=TRUE;
                 AERAlexWarning(1,&(inident.ort));
                 break;
    case unused: erfolg=TRUE;
    }
  if (erfolg)
    {  MakTable[inident.semval].MakArt = actmak;
       MakTable[inident.semval].MakString = inprogstring.semval;
       MakTable[inident.semval].MakParCount = inparanz;
    }
  _END_
}  

 
/*******************************************************************}
{*                                                                 *}
{*  Prozedur: StoreSpec               Version:  25/05/91           *}
{*                                                                 *}
{*******************************************************************}
{*                                                                 *}
{*  Klassifizierung:  Prozedur                                     *}
{*                                                                 *}
{*  Funktionsbeschreibung:                                         *}
{*  Speichert eine Spezialaktion, die in Form eines Progstrings    *}
{*  vorliegt in die Tabelle der Spezialaktionen durch Anhangen     *}
{*  an eine Liste, deren Anker in einem Array liegt, das je        *}
{*  Spezialaktion einen Eintrag hat.                               *}
{*  Bei der Definition einer neuen Spezialaktion wird der neue     *}
{*  Teil hinten eingehaengt.                                       *}
{*  Die Datenstruktur fuer Speziualaktionen ist in GENACTIO COPY   *}
{*  deklariert                                                     *}
{*-----------------------------------------------------------------*}
{*                                                                 *}
{*  Eingabeparameter:                                              *}
{*  incode                    boolean                              *}
{*  inspecial                 specialsy                            *}
{*  inprogstring              progstringsy                         *}
{*  Transientparameter:                                            *}
{*  outcode                   boolean                              *}
{*  Seiteneffekte:                                                 *}
{*                                                                 *}
{*  Lokale Variablen:                                              *}
{*  specvar                   SpecType                             *}
{*  lauf                      SpecLPoint                           *}
{*******************************************************************/

#ifdef __STDC__
extern void StoreSpec(BOOL incode,
                      SPECIALSY inspecial,
                      PROGSTRINGSY inprogstring,
                      BOOL *outcode)
#else /* ! __STDC__ */
extern void StoreSpec(incode,inspecial,inprogstring,outcode)
BOOL incode,*outcode;
SPECIALSY inspecial;
PROGSTRINGSY inprogstring;
#endif /* ! __STDC__ */
{ SpecType specvar;
  SpecLPoint lauf;
  _BEGIN_
  switch (inspecial.semval) {
    case 1: specvar=spextern;
            break;
    case 2: specvar=spscanexit;
            break;
    case 3: specvar=spscanerror;
            break;
    case 4: specvar=spscaninit;
            break;
     }
  if(SpecActions[specvar]==spunused)
    { SpecActions[specvar] = malloc(sizeof(struct SpecLElem));
      SpecActions[specvar]->ElemNachfolger = NULL;
      SpecActions[specvar]->ElemStr = inprogstring.semval;
#ifdef DEBUG
  printf("\n\nSTORESPEC ( %d ) \n",inprogstring.semval);
#endif
      *outcode = incode;
    }
   else {
      AERAlexWarning(2,&(inspecial.ort));
      lauf = SpecActions[specvar];
      while (lauf->ElemNachfolger != NULL)
          lauf = lauf->ElemNachfolger;
      lauf->ElemNachfolger = malloc(sizeof(struct SpecLElem));
      lauf = lauf->ElemNachfolger;         
      lauf->ElemNachfolger = NULL;
      lauf->ElemStr = inprogstring.semval;
      *outcode = incode;
      }
  _END_
}



/*******************************************************************}
{*                                                                 *}
{*  Prozedur: InstLexMak              Version:  25/05/91           *}
{*                                                                 *}
{*******************************************************************}
{*                                                                 *}
{*  Klassifizierung:  Prozedur                                     *}
{*                                                                 *}
{*  Funktionsbeschreibung:                                         *}
{*  Installiert einen lexikalischen Makro (definierendes Auf-      *}
{*  treten), indem in die Makrotabelle (siehe GENACTIO COPY)       *}
{*  unter der Nummer des Identifikators ein Zeiger auf den         *}
{*  Automaten inautomat abgespeichert wird.                        *}
{*                                                                 *}
{*-----------------------------------------------------------------*}
{*                                                                 *}
{*  Eingabeparameter:                                              *}
{*  incode                    boolean                              *}
{*  inname                    stringsy                             *}
{*  inautomat                 automat                              *}
{*  Transientparameter:                                            *}
{*  outcode                   boolean                              *}
{*  Seiteneffekte:                                                 *}
{*                                                                 *}
{*  Lokale Variablen:                                              *}
{*  erfolg                    boolean                              *}
{*******************************************************************/


#ifdef __STDC__
extern void InstLexMak(BOOL incode,
                       IDENT inname,
                       AUTOMAT inautomat,
                       BOOL *outcode)
#else /* ! __STDC__ */
extern void InstLexMak(incode,inname,inautomat,outcode)
BOOL incode,*outcode;
IDENT inname;
AUTOMAT inautomat;
#endif /* ! __STDC__ */
{ int erfolg;
  _BEGIN_
  *outcode = incode;
#ifdef DEBUG
  printf("\n\nAUTOMAT in INSTLEXMAK\n\n");
  PrintAutomat(inautomat);
#endif
  switch(MakTable[inname.semval].MakArt) {
   case actmak: *outcode = 0;
                erfolg = 0;
                AERAlexRecoverableError(5,&(inname.ort));
                break;
   case lexmak: erfolg = 1;
                AERAlexWarning(3,&(inname.ort));
                DisposeAutomaton(MakTable[inname.semval].MakAutomat);
                break;
   case unused: erfolg = 1;
    }
  if (erfolg) {
    MakTable[inname.semval].MakArt = lexmak;
    MakTable[inname.semval].MakAutomat = inautomat;
    }
  _END_
}



/*******************************************************************}
{*                                                                 *}
{*  Prozedur: SAlternative            Version:  25/05/91           *}
{*                                                                 *}
{*******************************************************************}
{*                                                                 *}
{*  Klassifizierung:  Prozedur                                     *}
{*                                                                 *}
{*  Funktionsbeschreibung:                                         *}
{*  Ruft die Prozedur Alternative der Stackmaschine auf            *}
{*  Die beiden Automaten werden mit der ODER-Operation zu          *}
{*  outautomat verknuepft.                                         *}
{*  siehe auch STACKMAS PASCAL                                     *}
{*-----------------------------------------------------------------*}
{*                                                                 *}
{*  Eingabeparameter:                                              *}
{*  inautomat1                Automat                              *}
{*  inautomat2                Automat                              *}
{*  icode                     boolean                              *}
{*  Transientparameter:                                            *}
{*  outautomat                Automat                              *}
{*  Seiteneffekte:                                                 *}
{*                                                                 *}
{*******************************************************************/

#ifdef __STDC__
extern void SAlternative(AUTOMAT inautomat1,
                         AUTOMAT inautomat2,
                         BOOL icode,
                         AUTBOOL *outautomatdcode)
#else /* ! __STDC__ */
extern void SAlternative(inautomat1,inautomat2,icode,outautomatdcode)
AUTOMAT inautomat1,inautomat2;
AUTBOOL *outautomatdcode;
BOOL icode;
#endif /* ! __STDC__ */
{ AUTOMAT *outautomat;
  BOOL *dcode;
  _BEGIN_
  outautomat = &(outautomatdcode->automat); 
  dcode      = &(outautomatdcode->bool);
  *dcode = icode;
  if (icode) Alternative(inautomat1,inautomat2,outautomat);
  _END_
} 




/*******************************************************************}
{*                                                                 *}
{*  Prozedur: InsParam                Version:  25/05/91           *}
{*                                                                 *}
{*******************************************************************}
{*                                                                 *}
{*  Klassifizierung:  Prozedur                                     *}
{*                                                                 *}
{*  Funktionsbeschreibung:                                         *}
{*  Tritt bei der auftretenden Verwendung eines Aktionsmakros      *}
{*  auf. Dabei wird die Nummer des Parameters, die auf einen       *}
{*  String in der Symboltabelle zeigt, in das Parameterarray       *}
{*  eingetragen. Somit kann spaeter ueber dieses Array der         *}
{*  Parameter wieder decodiert werden                              *}
{*                                                                 *}
{*  Datenstrukturen siehe GENACTIO COPY                            *}
{*-----------------------------------------------------------------*}
{*                                                                 *}
{*  Eingabeparameter:                                              *}
{*  incode                    boolean                              *}
{*  inpar                     integer32                              *}
{*  inpararray                partype                              *}
{*  inparno                   integer32                              *}
{*  zeile                     integer32                              *}
{*  spalte                    integer32                              *}
{*  Transientparameter:                                            *}
{*  outcode                   boolean                              *}
{*  outpararray               partype                              *}
{*  Seiteneffekte:                                                 *}
{*                                                                 *}
{*******************************************************************/


#ifdef __STDC__
extern void InsParam(BOOL incode,
                     INT inpar,
                     PARTYPE inpararray,
                     INT inparno,
                     Quellort ort,
                     BOOLPAR *outcodepararray)
#else /* ! __STDC__ */
extern void InsParam(incode,inpar,inpararray,inparno,ort,outcodepararray)
BOOL incode;
INT inpar,inparno;
Quellort ort;
BOOLPAR *outcodepararray;
PARTYPE inpararray;
#endif /* ! __STDC__ */
{ BOOL *outcode;
  PARTYPE *outpararray;
  int i;
  _BEGIN_
  outcode = &(outcodepararray->bool);
  outpararray = &(outcodepararray->partype);
  if(inparno<=9)
    { *outcode = incode;
      for(i=0;i<10;i++)
         outpararray->par[i] = inpararray.par[i];
      outpararray->par[inparno] = inpar;
    }
   else 
    { *outcode = 0;
      AERAlexRecoverableError(6,&ort);
    }
  _END_
}
 


/*******************************************************************}
{*                                                                 *}
{*  Prozedur: SemIntToStr             Version:  25/05/91           *}
{*                                                                 *}
{*******************************************************************}
{*                                                                 *}
{*  Klassifizierung:  Prozedur                                     *}
{*                                                                 *}
{*  Funktionsbeschreibung:                                         *}
{*  Wandelt einen Integer in einen String um, speichert den        *}
{*  String in der Symboltabelle und gibt den Hashindex der         *}
{*  Symboltabelle an den Aufrufer zurueck   -   Wird benoetigt     *}
{*  wenn ein makro mit einem Integer als Parameter aufgerufen      *}
{*  wird. Dann muss der Integer beim Expandieren als Text vor-     *}
{*  liegen                                                         *}
{*-----------------------------------------------------------------*}
{*                                                                 *}
{*  Eingabeparameter:                                              *}
{*  inint                     integersy                            *}
{*  Transientparameter:                                            *}
{*  outstring                 integer32                              *}
{*  zeile                     integer32                              *}
{*  spalte                    integer32                              *}
{*  Seiteneffekte:                                                 *}
{*                                                                 *}
{*  Lokale Variablen:                                              *}
{*  transstr                  string                               *}
{*  Lokale Prozeduren und Funktionen:                              *}
{*******************************************************************/


#ifdef __STDC__
extern void SemIntToStr(INTEGERSY inint, INTORT *outstringort)
#else /* ! __STDC__ */
extern void SemIntToStr(inint,outstringort)
INTEGERSY inint;
INTORT *outstringort;
#endif /* ! __STDC__ */
{ INT *outstring;
  QUELLORT *ort;
  struct varfilestring transstr;
  _BEGIN_
  outstring = &(outstringort->i1);
  ort  = &(outstringort->ort);
  STRinttostring(inint.semval,&transstr);
  transstr.body[transstr.length]=0;
  *outstring = SYGetIdNumber(transstr.body,TYP_STR,StrCC);
  *ort = inint.ort;
  _END_
}

 

/*******************************************************************}
{*                                                                 *}
{*  Prozedur: SemStrToStr             Version:  25/05/91           *}
{*                                                                 *}
{*******************************************************************}
{*                                                                 *}
{*  Klassifizierung:  Prozedur                                     *}
{*                                                                 *}
{*  Funktionsbeschreibung:                                         *}
{*  Wandelt ein Stringsymbol in einen reinen Zeiger in die         *}
{*  Symboltabelle um. Dabei wird die Information Zeile und         *}
{*  Spalte an zwei weitere Attribute weitergereicht.               *}
{*  Die Prozedur zerlegt also nur den Record stringsy in seine     *}
{*  Komponenten                                                    *}
{*-----------------------------------------------------------------*}
{*                                                                 *}
{*  Eingabeparameter:                                              *}
{*  instr                     stringsy                             *}
{*  Transientparameter:                                            *}
{*  outstring                 integer32                              *}
{*  zeile                     integer32                              *}
{*  spalte                    integer32                              *}
{*  Seiteneffekte:                                                 *}
{*                                                                 *}
{*******************************************************************/


#ifdef __STDC__
extern void SemStrToStr(STRINGSY instr, INTORT *outstringort)
#else /* ! __STDC__ */
extern void SemStrToStr(instr,outstringort)
STRINGSY instr;
INTORT *outstringort;
#endif /* ! __STDC__ */
{ QUELLORT *ort;
  INT *outstring;
  _BEGIN_
  outstring = &(outstringort->i1);
  ort  = &(outstringort->ort);
  *outstring = instr.semval;
  *ort = instr.ort;
  _END_
}




/*******************************************************************}
{*                                                                 *}
{*  Prozedur: ChkFormPar              Version:  25/05/91           *}
{*                                                                 *}
{*******************************************************************}
{*                                                                 *}
{*  Klassifizierung:  Prozedur                                     *}
{*                                                                 *}
{*  Funktionsbeschreibung:                                         *}
{*  Ueberprueft ob ein formaler Parameter                          *}
{*  eine Nummer 1 <= N <= 9 hat                                    *}
{*  seine Stellung auch stimmt. Wird bei der Definition eines      *}
{*  Aktionsmakros benoetigt. Beispiel fuer erkannten Fehler:       *}
{*  code(%1,%3)                                                    *}
{*           Fehler                                                *}
{*           Stellung des Parameters nicht korrekt                 *}
{*           hier sollte ja %2 stehen                              *}
{*-----------------------------------------------------------------*}
{*                                                                 *}
{*  Eingabeparameter:                                              *}
{*  incode                    boolean                              *}
{*  inpar                     formpar                              *}
{*  parnumber                 integer32                              *}
{*  Transientparameter:                                            *}
{*  outcode                   boolean                              *}
{*  Seiteneffekte:                                                 *}
{*                                                                 *}
{*******************************************************************/


#ifdef __STDC__
extern void ChkFormPar(BOOL incode,
                       FORMPAR inpar,
                       INT parnumber,
                       BOOL *outcode)
#else /* ! __STDC__ */
extern void ChkFormPar(incode,inpar,parnumber,outcode)
BOOL incode,*outcode;
INT parnumber;
FORMPAR inpar;
#endif /* ! __STDC__ */
{ _BEGIN_
  _TRA_ " inpar.semval = %d  ,  parnumber = %d\n",inpar.semval,parnumber _TRE_
  *outcode = incode;
  if ((parnumber>9) || (inpar.semval<0) )
    { *outcode = 0;
      AERAlexRecoverableError(1,&(inpar.ort));
    }
  else
    { if(parnumber != inpar.semval)
        { *outcode = 0;
          AERAlexRecoverableError(7,&(inpar.ort));
        }
    }
  _END_
}




/*******************************************************************}
{*                                                                 *}
{*  Prozedur: DefMakAct               Version:  25/05/91           *}
{*                                                                 *}
{*******************************************************************}
{*                                                                 *}
{*  Klassifizierung:  Prozedur                                     *}
{*                                                                 *}
{*  Funktionsbeschreibung:                                         *}
{*                                                                 *}
{*  Eine Makroaktion wird in die Aktionstabelle eingetragen        *}
{*  Anwendendes Auftreten eines Aktionsmakros                      *}
{*  Struktur der Tabelle siehe GENACTIO COPY                       *}
{*                                                                 *}
{*  Inignore ist ein boolescher Wert, der je nachdem gesetzt wird  *}
{*  ob das Token ignoriert werden soll oder nicht                  *}
{*  Siehe auch Produktionen 131,132  (dort wird inignore besetzt)  *}
{*  und P141, P142 (Aufruf dieser Prozedur)                        *}
{*-----------------------------------------------------------------*}
{*                                                                 *}
{*  Eingabeparameter:                                              *}
{*  incode                    boolean                              *}
{*  inignore                  boolean                              *}
{*  inautomat                 Automat                              *}
{*  inparanz                  integer32                              *}
{*  inident                   stringsy                             *}
{*  inpars                    partype                              *}
{*  Transientparameter:                                            *}
{*  dautom                    automat                              *}
{*  outcode                   boolean                              *}
{*  Seiteneffekte:                                                 *}
{*                                                                 *}
{*  Lokale Variablen:                                              *}
{*  checked                   boolean                              *}
{*******************************************************************/

#ifdef __STDC__
extern void DefMakAct(BOOL incode,
                      INT inignore,
                      AUTOMAT inautomat,
                      INT inparanz,
                      IDENT inident,
                      PARTYPE inpars,
                      AUTBOOL *outcodedautom)
#else /* ! __STDC__ */
extern void DefMakAct(incode,inignore,inautomat,inparanz,inident,inpars,outcodedautom)
BOOL incode;
INT inignore,inparanz;
AUTBOOL *outcodedautom;
AUTOMAT inautomat;
IDENT inident;
PARTYPE inpars;
#endif /* ! __STDC__ */
{ AUTOMAT *dautom;
  BOOL *outcode;
  int checked,i;
  _BEGIN_
  dautom = &(outcodedautom->automat);
  outcode = &(outcodedautom->bool);
  checked = 1;
  *outcode = incode;
  if(MakTable[inident.semval].MakArt != actmak)
    { switch(MakTable[inident.semval].MakArt) {
       case lexmak: AERAlexRecoverableError(10,&(inident.ort));
                    *outcode = 0;
                    break;
       case unused: AERAlexRecoverableError(11,&(inident.ort));
                    *outcode = 0;
                    break;
              }
      checked = 0;
    }
  else
    { if (inparanz !=  MakTable[inident.semval].MakParCount)
        { AERAlexRecoverableError(9,&(inident.ort));
          checked = 0;
          *outcode = 0;
        }
    }
  if (checked)
    { ActTable[Actnumber].ignore = inignore;
      for(i=0;i<10;i++)      
        { ActTable[Actnumber].parameters[i] = inpars.par[i];
       /* printf("DefMakro %d: Par[%d]=%d\n",Actnumber,i,inpars.par[i]); */ }
      ActTable[Actnumber].makro = 1;
      ActTable[Actnumber].maknumber = inident.semval;
    }
  if (incode) DefineAction(Actnumber,inautomat,dautom);
  Actnumber++;
  if (Actnumber>MaxAction)
  /* Bauernfeind: 17.06.93; statisch->dynamisch */
  /*   AERAlexFatalError(2,&(inident.ort)); */
  {
      ActTable = realloc(ActTable,(MaxAction*2+1)*sizeof(struct ActTbEintr));
      MaxAction = MaxAction*2;
  }
  _END_
}   


 
/*******************************************************************}
{*                                                                 *}
{*  Prozedur: DefAction               Version:  25/05/91           *}
{*                                                                 *}
{*******************************************************************}
{*                                                                 *}
{*  Klassifizierung:  Prozedur                                     *}
{*                                                                 *}
{*  Funktionsbeschreibung:                                         *}
{*  Eine Aktion, die aus einem Progstring besteht, wird in die     *}
{*  Aktionstabelle eingetragen . Inignore gibt an, ob nach der     *}
{*  Aktion der Scanner weiterlaufen soll oder nicht (wie bei       *}
{*  DefMakAct). Siehe hierzu wieder P131, P132. Die Aktionstabelle *}
{*  ist in GENACTIO COPY deklariert und wird veraendert.           *}
{*-----------------------------------------------------------------*}
{*                                                                 *}
{*  Eingabeparameter:                                              *}
{*  incode                    boolean                              *}
{*  inignore                  boolean                              *}
{*  inautomat                 Automat                              *}
{*  inactnumber               progstringsy                         *}
{*  Transientparameter:                                            *}
{*  dautom                    automat                              *}
{*  outcode                   boolean                              *}
{*  Seiteneffekte:                                                 *}
{*                                                                 *}
{*******************************************************************/

 
#ifdef __STDC__
extern void DefAction(BOOL incode,
                      INT inignore,
                      AUTOMAT inautomat,
                      PROGSTRINGSY inactnumber,
                      AUTBOOL *dautomoutcode)
#else /* ! __STDC__ */
extern void DefAction(incode,inignore,inautomat,inactnumber,dautomoutcode)
BOOL incode;
INT inignore;
AUTBOOL *dautomoutcode;
AUTOMAT inautomat;
PROGSTRINGSY inactnumber;
#endif /* ! __STDC__ */
{ BOOL *outcode;
  AUTOMAT *dautom;
  _BEGIN_
  outcode = &(dautomoutcode->bool);
  dautom  = &(dautomoutcode->automat);
  if (incode)
    { ActTable[Actnumber].ignore = inignore;
      *outcode = incode;
      *dautom = inautomat;
      DefineAction(Actnumber,inautomat,dautom);
      if (Actnumber>MaxAction)
         AERAlexFatalError(2,&(inactnumber.ort));
      ActTable[Actnumber].makro = 0;
#ifdef DEBUG
  printf("*****DefAction : strnumber = %d\n",inactnumber.semval);
#endif
      ActTable[Actnumber].strnumber = inactnumber.semval;
      Actnumber++;
    }
     else *outcode = incode;
  _END_
}



/*******************************************************************}
{*                                                                 *}
{*  Prozedur: SConcat                 Version:  25/05/91           *}
{*                                                                 *}
{*******************************************************************}
{*                                                                 *}
{*  Klassifizierung:  Prozedur                                     *}
{*                                                                 *}
{*  Funktionsbeschreibung:                                         *}
{*  Aufruf der Konkatenation von Automaten .                       *}
{*  siehe STACKMAS PASCAL                                          *}
{*-----------------------------------------------------------------*}
{*                                                                 *}
{*  Eingabeparameter:                                              *}
{*  inautomat1                Automat                              *}
{*  inautomat2                Automat                              *}
{*  icode                     boolean                              *}
{*  Transientparameter:                                            *}
{*  outautomat                Automat                              *}
{*  Seiteneffekte:                                                 *}
{*                                                                 *}
{*******************************************************************/


#ifdef __STDC__
extern void SConcat(AUTOMAT inautomat1,
                    AUTOMAT inautomat2,
                    BOOL icode,
                    AUTBOOL *outautomatdcode)
#else /* ! __STDC__ */
extern void SConcat(inautomat1,inautomat2,icode,outautomatdcode)
AUTOMAT inautomat1,inautomat2;
AUTBOOL *outautomatdcode;
BOOL icode;
#endif /* ! __STDC__ */
{ AUTOMAT *outautomat;
  BOOL *dcode;
  _BEGIN_
  outautomat = &(outautomatdcode->automat);
  dcode      = &(outautomatdcode->bool);
  *dcode = icode;
  if (icode) Concat(inautomat1,inautomat2,outautomat);
  _END_
}




/*******************************************************************}
{*                                                                 *}
{*  Prozedur: SMultiply               Version:  25/05/91           *}
{*                                                                 *}
{*******************************************************************}
{*                                                                 *}
{*  Klassifizierung:  Prozedur                                     *}
{*                                                                 *}
{*  Funktionsbeschreibung:                                         *}
{*  Aufruf der Vervielfachung von Automaten. Siehe auch STACKMAS   *}
{*  PASCAL. Die Versorgung mit inkonsistenten Ober- und Unter-     *}
{*  grenzen loest eine Fehlermeldung der Stackmaschine aus.        *}
{*                                                                 *}
{*-----------------------------------------------------------------*}
{*                                                                 *}
{*  Eingabeparameter:                                              *}
{*  incode                    boolean                              *}
{*  inautomat                 Automat                              *}
{*  untergr                   integersy                            *}
{*  obergr                    integersy                            *}
{*  Transientparameter:                                            *}
{*  outcode                   integer32                              *}
{*  outaut                    automat                              *}
{*  Seiteneffekte:                                                 *}
{*                                                                 *}
{*******************************************************************/


#ifdef __STDC__
extern void SMultiply(BOOL incode,
                      AUTOMAT inautomat,
                      INTEGERSY untergr,
                      INTEGERSY obergr,
                      AUTBOOL *outcodeoutaut)
#else /* ! __STDC__ */
extern void SMultiply(incode,inautomat,untergr,obergr,outcodeoutaut)
BOOL incode;
AUTBOOL *outcodeoutaut;
AUTOMAT inautomat;
INTEGERSY untergr,obergr;
#endif /* ! __STDC__ */
{ AUTOMAT *outaut;
  BOOL *outcode;
  _BEGIN_
  outaut  = &(outcodeoutaut->automat);
  outcode = &(outcodeoutaut->bool);
  *outcode = incode;
  *outaut = inautomat;
  if (incode)
      Multiply(outaut,untergr.semval,obergr.semval);
  _END_
}




/*******************************************************************}
{*                                                                 *}
{*  Prozedur: RegOperator             Version:  25/05/91           *}
{*                                                                 *}
{*******************************************************************}
{*                                                                 *}
{*  Klassifizierung:  Prozedur                                     *}
{*                                                                 *}
{*  Funktionsbeschreibung:                                         *}
{*  Aufruf der Regulaeren Operatoren +,*,? aus der Stackmaschine   *}
{*  die in der Grammatik unter einem Nichtterminal zusammengefasst *}
{*  sind                                                           *}
{*-----------------------------------------------------------------*}
{*                                                                 *}
{*  Eingabeparameter:                                              *}
{*  inautomat                 Automat                              *}
{*  Operator                  RegOp                                *}
{*  icode                     boolean                              *}
{*  Transientparameter:                                            *}
{*  outautomat                Automat                              *}
{*  dcode                     boolean                              *}
{*  Seiteneffekte:                                                 *}
{*                                                                 *}
{*******************************************************************/
 

#ifdef __STDC__
extern void RegOperator(AUTOMAT inautomat,
                        REGOP operator,
                        BOOL icode,
                        AUTBOOL *outautomatdcode)
#else /* ! __STDC__ */
extern void RegOperator(inautomat,operator,icode,outautomatdcode)
AUTOMAT inautomat;
AUTBOOL *outautomatdcode;
REGOP operator;
BOOL icode;
#endif /* ! __STDC__ */
{ AUTOMAT *outautomat;
  BOOL *dcode;
  _BEGIN_
  outautomat = &(outautomatdcode->automat);
  dcode      = &(outautomatdcode->bool);
  *dcode = icode;
  if (icode)
    { switch (operator.semval) {
       case 1:  Star(inautomat,outautomat);
                break;
       case 2:  Plus(inautomat,outautomat);
                break;
       case 3:  Option(inautomat,outautomat);
                break;
       default: AERAlexSoftwareError(1,&(operator.ort));
                *dcode = 0;
         }
    }
  else *outautomat = NULL;
  _END_
}




/*******************************************************************}
{*                                                                 *}
{*  Prozedur: StringToAut             Version:  25/05/91           *}
{*                                                                 *}
{*******************************************************************}
{*                                                                 *}
{*  Klassifizierung:  Prozedur                                     *}
{*                                                                 *}
{*  Funktionsbeschreibung:                                         *}
{*  Verwandelt einen String in einen Automaten. Siehe auch         *}
{*  AUTSTACK PASCAL                                                *}
{*-----------------------------------------------------------------*}
{*                                                                 *}
{*  Eingabeparameter:                                              *}
{*  instring                  stringsy                             *}
{*  Transientparameter:                                            *}
{*  outautomat                Automat                              *}
{*  Seiteneffekte:                                                 *}
{*                                                                 *}
{*******************************************************************/


#ifdef __STDC__
extern void StringToAut(STRINGSY instring, AUTOMAT *outautomat)
#else /* ! __STDC__ */
extern void StringToAut(instring,outautomat)
STRINGSY instring;
AUTOMAT *outautomat;
#endif /* ! __STDC__ */
{ _BEGIN_
  struct varfilestring help;
  char *s;
  s=SYDecSymtab(StrCC,instring.semval);
  help.length=strlen(s);
  strcpy(help.body,s);
  AGenStr((EventString)&help,outautomat);
  _END_
}



 
/*******************************************************************}
{*                                                                 *}
{*  Prozedur: ExpndLexMak             Version:  25/05/91           *}
{*                                                                 *}
{*******************************************************************}
{*                                                                 *}
{*  Klassifizierung:  Prozedur                                     *}
{*                                                                 *}
{*  Funktionsbeschreibung:                                         *}
{*  Anwendendes Auftreten eines lexikalischen Makros. Der Automat  *}
{*  auf den der Eintrag in der Makrotabelle (GENACTIO COPY)        *}
{*  zeigt, wird physikalisch kopiert und in den Automaten der      *}
{*  dem aktuellen Stand der Auswertung entspricht, eingebaut       *}
{*-----------------------------------------------------------------*}
{*                                                                 *}
{*  Eingabeparameter:                                              *}
{*  incode                    boolean                              *}
{*  makronumber               ident                                *}
{*  Transientparameter:                                            *}
{*  outcode                   boolean                              *}
{*  outautomat                Automat                              *}
{*  Seiteneffekte:                                                 *}
{*                                                                 *}
{*******************************************************************/


 
#ifdef __STDC__
extern void ExpndLexMak(BOOL incode,
                        IDENT makronumber,
                        AUTBOOL *outcodeoutautomat)
#else /* ! __STDC__ */
extern void ExpndLexMak(incode,makronumber,outcodeoutautomat)
BOOL incode;
AUTBOOL *outcodeoutautomat;
IDENT makronumber;
#endif /* ! __STDC__ */
{  BOOL *outcode;
   AUTOMAT *outautomat;
   _BEGIN_
   outcode = &(outcodeoutautomat->bool);
   outautomat = &(outcodeoutautomat->automat);
   if (incode)
   { *outcode = incode;
     switch ( MakTable[makronumber.semval].MakArt) {
      case unused: AERAlexRecoverableError(11,&(makronumber.ort));
                   *outautomat = NULL;
                   *outcode = 0;
                   break;
      case actmak: AERAlexRecoverableError(12,&(makronumber.ort));
                   *outautomat = NULL;
                   *outcode = 0;
                   break; 
      case lexmak: CopyAutomat(MakTable[makronumber.semval].MakAutomat,outautomat);
             }
   }
  else *outcode = incode;
  _END_
}




/*******************************************************************}
{*                                                                 *}
{*  Prozedur: SAllbut                 Version:  25/05/91           *}
{*                                                                 *}
{*******************************************************************}
{*                                                                 *}
{*  Klassifizierung:  Prozedur                                     *}
{*                                                                 *}
{*  Funktionsbeschreibung:                                         *}
{*  Aufruf von allbut in STACKMAS PASCAL                           *}
{*-----------------------------------------------------------------*}
{*                                                                 *}
{*  Eingabeparameter:                                              *}
{*  inautomat                 Automat                              *}
{*  icode                     boolean                              *}
{*  Transientparameter:                                            *}
{*  outautomat                Automat                              *}
{*  dcode                     boolean                              *}
{*  Seiteneffekte:                                                 *}
{*                                                                 *}
{*******************************************************************/



#ifdef __STDC__
extern void SAllbut(AUTOMAT inautomat, BOOL icode, AUTBOOL *outautomatdcode)
#else /* ! __STDC__ */
extern void SAllbut(inautomat,icode,outautomatdcode)
AUTOMAT inautomat;
AUTBOOL *outautomatdcode;
BOOL icode;
#endif /* ! __STDC__ */
{ AUTOMAT *outautomat;
  BOOL *dcode;
  outautomat = &(outautomatdcode->automat);
  dcode      = &(outautomatdcode->bool);
  _BEGIN_
  *dcode = icode;
  if (icode) Allbut(inautomat,outautomat);
  _END_
}

 


/*******************************************************************}
{*                                                                 *}
{*  Prozedur: ComplSet                Version:  25/05/91           *}
{*                                                                 *}
{*******************************************************************}
{*                                                                 *}
{*  Klassifizierung:  Prozedur                                     *}
{*                                                                 *}
{*  Funktionsbeschreibung:                                         *}
{*  Komplementiert eine Menge von Zeichen (Ereignissen)            *}
{*  fur die not - Operation                                        *}
{*-----------------------------------------------------------------*}
{*                                                                 *}
{*  Eingabeparameter:                                              *}
{*  inset                     EventSet                             *}
{*  Transientparameter:                                            *}
{*  outset                    EventSet                             *}
{*  Seiteneffekte:                                                 *}
{*                                                                 *}
{*******************************************************************/

#ifdef __STDC__
extern void ComplSet(CHARSET inset, CHARSET *outset)
#else /* ! __STDC__ */
extern void ComplSet(inset,outset)
CHARSET inset,*outset;
#endif /* ! __STDC__ */
{ int flags[256],i,j;
  _BEGIN_
  for(i=0;i<256;flags[i++]=0);
  for(i=0;i<inset.Length;flags[(unsigned int) inset.Set[i++] ] = 1);
  j = 0;
  for(i=0;i<256;i++)
    if (!flags[i]) outset->Set[j++] = (char) i;
  outset->Length = 256-inset.Length;
  _END_
}
                


/*******************************************************************}
{*                                                                 *}
{*  Prozedur: makeset                 Version:  25/05/91           *}
{*                                                                 *}
{*******************************************************************}
{*                                                                 *}
{*  Klassifizierung:  Prozedur                                     *}
{*                                                                 *}
{*  Funktionsbeschreibung:                                         *}
{*  Macht aus einer Ober- und einer Untergrenze (je ein Zeichen)   *}
{*  eine Menge von Ereignissen                                     *}
{*-----------------------------------------------------------------*}
{*                                                                 *}
{*  Eingabeparameter:                                              *}
{*  lower                     stringsy                             *}
{*  higher                    stringsy                             *}
{*  icode                     boolean                              *}
{*  Transientparameter:                                            *}
{*  outset                    charset                              *}
{*  Seiteneffekte:                                                 *}
{*                                                                 *}
{*  Lokale Variablen:                                              *}
{*  lowchar                   char                                 *}
{*  highchar                  char                                 *}
{*  lowstring                 string                               *}
{*  highstring                string                               *}
{*******************************************************************/

#ifdef __STDC__
extern void makeset(STRINGSY lower,
                    STRINGSY higher,
                    BOOL icode,
                    CHARBOOL *outsetdcode)
#else /* ! __STDC__ */
extern void makeset(lower,higher,icode,outsetdcode)
STRINGSY lower,higher;
BOOL icode;
CHARBOOL *outsetdcode;
#endif /* ! __STDC__ */
{ unsigned char lowchar,highchar;
  struct ActionString lowstring,highstring;
  int i;
  BOOL *dcode;
  CHARSET *outset;
  _BEGIN_
  dcode = &(outsetdcode->bool);
  outset = &(outsetdcode->ch);
  if (icode)
   { *dcode = icode;
     decode(&lowstring,32,lower.semval);
     decode(&highstring,32,higher.semval);
     lowchar = lowstring.body[0];
     highchar = highstring.body[0];
     outset->Length = (int)highchar - (int)lowchar + 1;
     for(i=0;i<outset->Length;i++)
         outset->Set[i] = (char) ( (int)lowchar + i );
     if (lowstring.length > 1) 
      { AERAlexRecoverableError(13,&(lower.ort));
        *dcode = FALSE;
      }
     if (highstring.length > 1)
      { AERAlexRecoverableError(13,&(higher.ort));
        *dcode = FALSE;
      }
    }
  else
   { *dcode = icode;
     outset->Length = 0;
   }
  _END_
}  



 
/*******************************************************************}
{*                                                                 *}
{*  Prozedur: union_sets              Version:  25/05/91           *}
{*                                                                 *}
{*******************************************************************}
{*                                                                 *}
{*  Klassifizierung:  Prozedur                                     *}
{*                                                                 *}
{*  Funktionsbeschreibung:                                         *}
{*  Vereinigung von zwei Event-Sets                                *}
{*-----------------------------------------------------------------*}
{*                                                                 *}
{*  Eingabeparameter:                                              *}
{*  inset1                    charset                              *}
{*  inset2                    charset                              *}
{*  Transientparameter:                                            *}
{*  outset                    charset                              *}
{*  Seiteneffekte:                                                 *}
{*                                                                 *}
{*******************************************************************/


#ifdef __STDC__
extern void union_sets(CHARSET inset1, CHARSET inset2, CHARSET *outset)
#else /* ! __STDC__ */
extern void union_sets(inset1,inset2,outset)
CHARSET inset1,inset2,*outset;
#endif /* ! __STDC__ */
{ _BEGIN_
  UnionEvSets((Class)outset,(Class)&inset1,(Class)&inset2);
  _END_
}

 

/*******************************************************************}
{*                                                                 *}
{*  Prozedur: SSetToAut               Version:  25/05/91           *}
{*                                                                 *}
{*******************************************************************}
{*                                                                 *}
{*  Klassifizierung:  Prozedur                                     *}
{*                                                                 *}
{*  Funktionsbeschreibung:                                         *}
{*  Unwandlung einer Menge von Events in einen Automaten.          *}
{*  siehe auch AUTSTACK PASCAL                                     *}
{*-----------------------------------------------------------------*}
{*                                                                 *}
{*  Eingabeparameter:                                              *}
{*  inset                     EventSet                             *}
{*  Transientparameter:                                            *}
{*  outaut                    automat                              *}
{*  Seiteneffekte:                                                 *}
{*                                                                 *}
{*******************************************************************/

#ifdef __STDC__
extern void SSetToAut(CHARSET inset, AUTOMAT *outaut)
#else /* ! __STDC__ */
extern void SSetToAut(inset,outaut)
CHARSET inset;
AUTOMAT *outaut;
#endif /* ! __STDC__ */
{ 
  _BEGIN_
  AGenSet(&inset,outaut);
  _END_
}

 

/*******************************************************************}
{*                                                                 *}
{*  Prozedur: SStrToAut               Version:  25/05/91           *}
{*                                                                 *}
{*******************************************************************}
{*                                                                 *}
{*  Klassifizierung:  Prozedur                                     *}
{*                                                                 *}
{*  Funktionsbeschreibung:                                         *}
{*  Verwandelt ein Stringsymbol in einen Automaten . Der           *}
{*  String muss erst decodiert werden, da er lediglich als         *}
{*  Symboltabelleneintrag vorliegt.                                *}
{*-----------------------------------------------------------------*}
{*                                                                 *}
{*  Eingabeparameter:                                              *}
{*  instring                  stringsy                             *}
{*  Transientparameter:                                            *}
{*  outaut                    automat                              *}
{*  Seiteneffekte:                                                 *}
{*                                                                 *}
{*  Lokale Variablen:                                              *}
{*  auxstring                 EventString                          *}
{*  Lokale Prozeduren und Funktionen:                              *}
{*******************************************************************/


#ifdef __STDC__
extern void SStrToAut(STRINGSY instring, AUTOMAT *outaut)
#else /* ! __STDC__ */
extern void SStrToAut(instring,outaut)
STRINGSY instring;
AUTOMAT *outaut;
#endif /* ! __STDC__ */
{ struct EventStr auxstring;
  char *s;

  _BEGIN_
  s= SYDecSymtab(StrCC,instring.semval);
  auxstring.length = strlen(s);
  memcpy(auxstring.body,s,auxstring.length);

  AGenStr((EventString)&auxstring,outaut);
  _END_
} 




/****************** Hilfsfunktionen zur Vorbesetzung von Attributen *******************/



#ifdef __STDC__
extern void ScanTrue(BOOL *bool)
#else /* ! __STDC__ */
extern void ScanTrue(bool)
BOOL *bool;
#endif /* ! __STDC__ */
{ *bool = TRUE; }

#ifdef __STDC__
extern void AutomatNil(AUTOMAT *aut)
#else /* ! __STDC__ */
extern void AutomatNil(aut)
AUTOMAT *aut;
#endif /* ! __STDC__ */
{ *aut = NULL; }

#ifdef __STDC__
extern void IPlus1(INT in, INT *out)
#else /* ! __STDC__ */
extern void IPlus1(in,out)
INT in,*out;
#endif /* ! __STDC__ */
{ _BEGIN_ 
  *out = in + 1; 
  _END_
}

#ifdef __STDC__
extern void IntNull(INT *null)
#else /* ! __STDC__ */
extern void IntNull(null)
INT *null;
#endif /* ! __STDC__ */
{ *null = 0; }

#ifdef __STDC__
extern void SetTrue(BOOL *true)
#else /* ! __STDC__ */
extern void SetTrue(true)
BOOL *true;
#endif /* ! __STDC__ */
{ *true = TRUE; }

#ifdef __STDC__
extern void SetFalse(BOOL *false)
#else /* ! __STDC__ */
extern void SetFalse(false)
BOOL *false;
#endif /* ! __STDC__ */
{ *false = FALSE; }


/************** Spaltfunktionen zur Zerlegung von Strukturen in ihre ******************/
/********* Komponenten bei semantischen Funktionen mit mehreren Ergebnissen ***********/

#ifdef __STDC__
extern void boclko2bool(BOCLKO bck, BOOL *bo)
#else /* ! __STDC__ */
extern void boclko2bool(bck,bo)
BOCLKO bck;
BOOL *bo;
#endif /* ! __STDC__ */
{ *bo = bck.bool; }

#ifdef __STDC__
extern void boclko2class(BOCLKO bck, CLASSDESC *class)
#else /* ! __STDC__ */
extern void boclko2class(bck,class)
BOCLKO bck;
CLASSDESC *class;
#endif /* ! __STDC__ */
{ *class = bck.classdesc; }

#ifdef __STDC__
extern void boclko2kompr(BOCLKO bck, KOMPRUEB *kompr)
#else /* ! __STDC__ */
extern void boclko2kompr(bck,kompr)
BOCLKO bck;
KOMPRUEB *kompr;
#endif /* ! __STDC__ */
{
#if defined ( ultrix ) && ! defined ( __STDC__)
bcopy(&bck.komprueb,kompr,sizeof(bck.komprueb));
#else  
 *kompr = bck.komprueb;
#endif
}



#ifdef __STDC__
extern void autbo2aut(AUTBOOL ab, AUTOMAT *aut)
#else /* ! __STDC__ */
extern void autbo2aut(ab,aut)
AUTBOOL ab;
AUTOMAT *aut;
#endif /* ! __STDC__ */
{ *aut = ab.automat; }

#ifdef __STDC__
extern void autbo2bool(AUTBOOL ab, BOOL *bo)
#else /* ! __STDC__ */
extern void autbo2bool(ab,bo)
AUTBOOL ab;
BOOL *bo;
#endif /* ! __STDC__ */
{ *bo = ab.bool; }



#ifdef __STDC__
extern void bopar2bool(BOOLPAR bopa, BOOL *bo)
#else /* ! __STDC__ */
extern void bopar2bool(bopa,bo)
BOOLPAR bopa;
BOOL *bo;
#endif /* ! __STDC__ */
{ *bo = bopa.bool; }

#ifdef __STDC__
extern void bopar2par(BOOLPAR bopa, PARTYPE *par)
#else /* ! __STDC__ */
extern void bopar2par(bopa,par)
BOOLPAR bopa;
PARTYPE *par;
#endif /* ! __STDC__ */
{ int i;
  for(i=0;i<=9;i++)
    par->par[i] = bopa.partype.par[i]; }



#ifdef __STDC__
extern void intort2i(INTORT intort, INT *i)
#else /* ! __STDC__ */
extern void intort2i(intort,i)
INTORT intort;
INT *i;
#endif /* ! __STDC__ */
{ *i = intort.i1; }

#ifdef __STDC__
extern void intort2o(INTORT intort, QUELLORT *i)
#else /* ! __STDC__ */
extern void intort2o(intort,i)
INTORT intort;
QUELLORT *i;
#endif /* ! __STDC__ */
{ *i = intort.ort; }


#ifdef __STDC__
extern void charbo2char(CHARBOOL chbo, CHARSET *ch)
#else /* ! __STDC__ */
extern void charbo2char(chbo,ch)
CHARBOOL chbo;
CHARSET *ch;
#endif /* ! __STDC__ */
{ *ch = chbo.ch; }

#ifdef __STDC__
extern void charbo2bool(CHARBOOL chbo, BOOL *bo)
#else /* ! __STDC__ */
extern void charbo2bool(chbo,bo)
CHARBOOL chbo;
BOOL *bo;
#endif /* ! __STDC__ */
{ *bo = chbo.bool; }


#ifdef DEBUG
#include "var.h"
int PrintAutomat(inaut)
  Automat inaut;
{
  StateSet    Set;
  KantenMenge Kante;

  printf("\nStartZustand %d\nEndZustaende:\n",inaut->StartZustand);
  for (Set=inaut->EndZustaende;Set;Set=Set->Nachfolger)
    printf("  %d",Set->State);
  printf("\nBelegteZustaende:\n");
  for (Set=inaut->BelegteZustaende;Set;Set=Set->Nachfolger)
    printf("  %d",Set->State);
  for (Set=inaut->BelegteZustaende;Set;Set=Set->Nachfolger)
    for (Kante=Delta[Set->State];Kante;Kante=Kante->Nachfolger)
      printf("\nVon Zustand %d mit Ereignis %d (%c) nach Zustand %d.",Set->State,Kante->Ereignis,Kante->Ereignis,Kante->FolgeZustand);
  printf("\n");
}

PrintSet(inset)
EventSet inset;
{ int i;
  printf("FUNKTION PrintSet\n\nLaenge von INSET : %d\n\n",inset->Length);
  for(i=0;i<inset->Length;printf("%d ",(int) inset->Set[i++]));
  printf("\n\n");
}

#endif
