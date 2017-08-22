/*******************************************************************/
/*                                                                 */
/*   Technische Universitaet Muenchen, Institut fuer Informatik    */
/*                 Lehrstuhl Prof. Dr. J. Eickel                   */
/*                                                                 */
/*                                                                 */
/*     AAA     L         EEEEEEEE    XX     XX    III    SSSSS     */
/*    A   A    L         E            X     X      I    S     S    */
/*   A     A   L         E             X   X       I    S          */
/*   AAAAAAA   L         EEEEEE         XXX        I     SSSSS     */
/*   A     A   L         E             X   X       I          S    */
/*   A     A   L         E            X     X      I    S     S    */
/*   A     A   LLLLLLL   EEEEEEEE    XX     XX    III    SSSSS     */
/*                                                                 */
/*      Advanced LEXical Instrument for Scannergeneration          */
/*                                                                 */
/*                                                                 */
/*******************************************************************/
/*                                                                 */
/*  Projekt: ALEXIS  V 2.0                                         */
/*                                                                 */
/*  C-Portierung: Thorsten Gesing                                  */
/*                                                                 */
/*  Copyright: Technische Universitaet Muenchen,                   */
/*             Institut fuer Informatik                            */
/*                                                                 */
/*  Segment: maketab.c                                             */
/*  Version: 20/05/91                                              */
/*                                                                 */
/*  Sprache: C                                                     */
/*                                                                 */
/*-----------------------------------------------------------------*/
/*                                                                 */
/*  Beschreibung:                                                  */
/*  Tabellengenerator fuer PASCAL (schreibt die Automatentabellen) */
/*  Inhalt:                                                        */
/*        gen_table                                                */
/*        initmaketab                                              */
/*                                                                 */
/*-----------------------------------------------------------------*/
/*                                                                 */
/*                 M O D I F I K A T I O N E N                     */
/*=================================================================*/
/* Datum      modifiziert von    Beschreibung der Modifikation     */
/*=================================================================*/
/*******************************************************************/

#define EntryPerLine   16

#include <stdio.h>
#include "global.h"
#include "var.h"


/*******************************************************************/
/*                                                                 */
/*  Prozedur: gen_table               Version:  20/05/91           */
/*                                                                 */
/*******************************************************************/
/*                                                                 */
/*  Klassifizierung:  Prozedur                                     */
/*                                                                 */
/*  Funktionsbeschreibung:                                         */
/*  Schreibt die Tabelle, die als Datenstruktur im Komprimierer    */
/*  erzeugt wurde, als Pascal-Copyfile unter dem Namen table.copy  */
/*-----------------------------------------------------------------*/
/*                                                                 */
/*  Transientparameter:                                            */
/*  Table                     KomprUebergang                       */
/*  Class                     ClassDescr                           */
/*  Seiteneffekte:                                                 */
/*                                                                 */
/*  Lokale Variablen:                                              */
/*  EvIndex                   char                                 */
/*  index                     integer32                            */
/*  zielfile                  text                                 */
/*******************************************************************/

#ifdef __STDC__
public void gen_table(KomprUebergang Table, ClassDescr Klasse)
#else /* ! __STDC__ */
public void gen_table(Table,Klasse)
  KomprUebergang Table;
  ClassDescr     Klasse;
#endif /* ! __STDC__ */
{
  FILE *fp;
  int  EvIndex;
  int   index;

  fp=fopen("table.h","w");
  if (!fp)
  {
    printf("Fehler bei der Eroeffnung der Datei table.h .\n");
    return;
  }
  fprintf(fp,"#define TmaxState    %d\n",Table->StateNumber);
  fprintf(fp,"#define TmaxEvent    %d\n",Klasse->ClassNumber);
  fprintf(fp,"#define TmaxAction   %d\n",Table->ActionNumber);
  fprintf(fp,"#define TmaxEdge     %d\n\n",Table->KantenNumber);

  fprintf(fp,"typedef int TStateType;  /* 0..TmaxState */\n");
  fprintf(fp,"typedef int TState1Type; /* 1..TmaxState */\n");
  fprintf(fp,"typedef int TEventType;  /* 0..TmaxEvent */\n");
  fprintf(fp,"typedef int TActionType; /* 0..TmaxAction */\n");
  fprintf(fp,"typedef int TEdgeType;   /* 0..TmaxEdge */\n\n");

  fprintf(fp,"typedef TStateType  TNextArray[TmaxEdge+1];\n");
  fprintf(fp,"typedef TEdgeType   TBaseArray[TmaxState+1];\n");
  fprintf(fp,"typedef TState1Type TDefArray[TmaxState+1]; /* beginnt bei Index 1 */\n");
  fprintf(fp,"typedef TEventType  TCharArray[256];\n");
  fprintf(fp,"typedef TActionType TActionArray[TmaxState+1];\n\n\n");

  fprintf(fp,"TCharArray char_table = {\n");
  for (EvIndex=MinEvent;EvIndex<MaxEvent;EvIndex++)
  {
    fprintf(fp,"%3d,",Klasse->EventTable[EvIndex]);
    if (EvIndex % EntryPerLine==EntryPerLine-1)
      putc('\n',fp);
  }
  fprintf(fp,"%d};\n\n",Klasse->EventTable[MaxEvent]);

  fprintf(fp,"TActionArray TAction = {\n");
  for (index=0;index<Table->StateNumber;index++)
  {
    fprintf(fp,"%3d,",Table->Actions[index]);
    if (index % EntryPerLine==EntryPerLine-1)
      putc('\n',fp);
  }
  fprintf(fp,"%d};\n\n",Table->Actions[Table->StateNumber]);

  fprintf(fp,"TDefArray Default = { 0,  /* DUMMY-Element, beginnt ab Index 1 */\n");
  for (index=1;index<Table->StateNumber;index++)
  {
    fprintf(fp,"%3d,",Table->Default[index]);
    if (index % EntryPerLine==EntryPerLine-1)
      putc('\n',fp);
  }
  fprintf(fp,"%d};\n\n",Table->Default[Table->StateNumber]);

  fprintf(fp,"TBaseArray Base = {\n");
  for (index=0;index<Table->StateNumber;index++)
  {
    fprintf(fp,"%3d,",Table->Base[index]);
    if (index % EntryPerLine==EntryPerLine-1)
      putc('\n',fp);
  }
  fprintf(fp,"%d};\n\n",Table->Base[Table->StateNumber]);

  fprintf(fp,"TNextArray Next = {\n");
  for (index=0;index<Table->KantenNumber;index++)
  {
    if (Table->Next[index]>0)
      fprintf(fp,"%3d,",Table->Next[index]);
    else
      fprintf(fp,"  0,");
    if (index % EntryPerLine==EntryPerLine-1)
      putc('\n',fp);
  }
  fprintf(fp,"%d};\n\n",Table->Next[Table->KantenNumber]);

  fprintf(fp,"TNextArray Check = {\n");
  for (index=0;index<Table->KantenNumber;index++)
  {
    fprintf(fp,"%3d,",Table->Check[index]);
    if (index % EntryPerLine==EntryPerLine-1)
      putc('\n',fp);
  }
  fprintf(fp,"%d};\n",Table->Check[Table->KantenNumber]);

  fclose(fp);
  printf("table.h   erzeugt  ( Includefile mit den Automatentabellen )\n");
}




/*******************************************************************/
/*                                                                 */
/*  Prozedur: initmaketab             Version:  20/05/91           */
/*                                                                 */
/*******************************************************************/
/*                                                                 */
/*  Klassifizierung:  Prozedur                                     */
/*                                                                 */
/*  Funktionsbeschreibung:                                         */
/*  Schreibt eine Versionsnummer auf die Standardausgabe           */
/*-----------------------------------------------------------------*/
/*                                                                 */
/*  Seiteneffekte:                                                 */
/*                                                                 */
/*  Lokale Prozeduren und Funktionen:                              */
/*******************************************************************/

#ifdef __STDC__
public void initmaketab(void)
#else /* ! __STDC__ */
public void initmaketab()
#endif /* ! __STDC__ */
{}
