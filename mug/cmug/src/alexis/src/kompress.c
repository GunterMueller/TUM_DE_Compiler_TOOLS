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
/*  Segment: kompress.c                                            */
/*  Version: 20/05/91                                              */
/*                                                                 */
/*  Sprache: C                                                     */
/*                                                                 */
/*-----------------------------------------------------------------*/
/*                                                                 */
/*  Beschreibung:                                                  */
/*  Diese Unit dient dazu, Datenstrukturen und Manipulations-      */
/*  algorithmen fuer endliche Automaten zu testen. Dabei sollen    */
/*  die einzelnen Routinen und Definitionen so strukturiert sein,  */
/*  dass sie spaeter ohne Aenderung in den ALEXIS-Compiler         */
/*  uebernommen werden koennen.                                    */
/*  Von den speziellen Moeglichkeiten von TURBO-Pascal (C) soll    */
/*  hier aus Portabilitaetsgruenden kein Gebrauch gemacht werden.  */
/*  Lediglich das Aufspalten des Programmes in einzelne Units wird */
/*  wegen der besseren Uebersicht vorgenommen.                     */
/*  In dieser Unit werden die Algorithmen zur Komprimierung der    */
/*  Zustandsuebergangstabelle realisiert. Im wesentlichen handelt  */
/*  es sich dabei um die Routine Kompress, die aus einem gegebenen */
/*  Automaten in intern-Darstellung einen Automaten mit kompri-    */
/*  mierten Uebergangstabellen erzeugt.                            */
/*                                                                 */
/*  Inhalt:                                                        */
/*        CountFKanten              <included>                     */
/*        Classify                                                 */
/*             ClPartition                                         */
/*                  IsOneElementic                                 */
/*             ClassifyState                                       */
/*                  CsHash                                         */
/*             ClTransformTable                                    */
/*             InitTranslTable                                     */
/*        Compress                                                 */
/*             BuildStateLength                                    */
/*                  BsCountKanten                                  */
/*             CoFindeAehnlichsten                                 */
/*                  CfTransformKante                               */
/*                  CfFindeFolge                                   */
/*                  CfVergleiche                                   */
/*             CoInsertState                                       */
/*                  CiFindePosition                                */
/*             CoInit                                              */
/*             CoDisposeHeap                                       */
/*        initkompress                                             */
/*                                                                 */
/*-----------------------------------------------------------------*/
/*                                                                 */
/*                 M O D I F I K A T I O N E N                     */
/*=================================================================*/
/* Datum      modifiziert von    Beschreibung der Modifikation     */
/*=================================================================*/
/*                                                                 */
/*                                                                 */
/*******************************************************************/

#ifdef __STDC__
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#endif

#include <stdio.h>
#include "global.h"
#include "var.h"
#include "error.h"
#include "quickset.h"
#define EXTERN
#include "kompress.h"


/* Bauernfeind: 17.06.93; Globale Variablen aus var.c */
extern int MaxState;
extern int MaxAction;
extern int MaxKomprState; 
extern int MaxKomprKanten; 
extern int MAX_ID_NO;
extern MakroTable MakTable;

extern void *realloc();




/* GLOBALE VARIABLEN FUER CLASSIFY */

private int              ClFirstOne;  /* 0..maxClasses + 1 */
private ClassTableType   ClassTable;  /* Array von EvSet-Strukturen */
    /*  Dies ist das Array, in dem die Partitionen jeweils abgespeichert werden. */
private EventTranslTable ClTranslTable;
    /*  In diesem Array stehen zu jedem Event die Ereignisse, die zu ihm
        aequivalent sind. Es ist von Bedeutung, wenn die Option
        IGNORE_CASE
        gesetzt ist, oder der Scanner fuer eine andere Codierung erstellt
        werden soll, als die, mit der der Generator gerade arbeitet. */
private CsClassTable     CsHashTab;
private ClassDescr ClErg;	/*  Hierhin wird ClErgPtr kopiert, damit
				    er global erreichbar ist */


/* GLOBALE VARIABLEN FUER COMPRESS */

private Automat         CoAutomat;
private ClassDescr      CoClasses;
private KomprUebergang  CoKomp;
private StateLength     CoBearbeitet;
private CoStateTable    CoNewState;
private CoFreeChainType CoFreeChain,CoChainEnd;
private int             CoFirstFree;

/* *************************************************************** */
/*            INTERNE FUNKTIONSDEKLARATIONEN                       */
/* *************************************************************** */


private int IsOneElementic P_((Class IoSet));
private void ClPartition P_((Class CpClass));
private int CsHash P_((Status ChState));
private void ClassifyState P_((Status CsState));
private void ClTransformTable P_((void));
private void InitTranslTable P_((void));
private Classes BsCountKanten P_((Status BcState,ClassDescr BsClasses));
private void BuildStateLength P_((Automat BsAutomat,ClassDescr BsClasses,QuickSet *BsStateLength,KomprState *BsNewState,KomprState *BsStateNumber));
private int CfFindeFolge P_((KomprState  CffState,Classes CffEvent,KomprState *CffErg));
private void CfTransformKante P_((Status CtState,int *CtKante));
private void CfVergleiche P_((int *CvKante,KomprState CvState,Classes CvMaxRate,Classes *CvRate,int *CvMaxRek,int *CvDifferenz));
private void CoFindeAehnlichsten P_((Status CfNewState,int CfLaenge,Status *CfDefState,int *CfDifferenzen));
private void CiFindePosition P_((KomprState CpState,int *CpDifferenzen,KomprUebergang CpErg));
private void CoInsertState P_((Status CiState,KomprState CiDefState,int *CiDifferenzen,KomprUebergang CiErg));
private void CoInit P_((void));
private void CoDisposeHeap P_((void));



/* *************************************************************** */
/*           EIGENE FUNKTIONEN (z. Tl. zu Testzwecken)             */
/* *************************************************************** */


#ifdef __STDC__
public void UnionEvSets(Class Erg, Class Set1, Class Set2) /* Set1,Set2 muessen definiert sein */
                      
#else /* ! __STDC__ */
public void UnionEvSets(Erg,Set1,Set2) /* Set1,Set2 muessen definiert sein */
  Class Erg,Set1,Set2;
#endif /* ! __STDC__ */
{
  Class smallerset,largerset;
  int   newlength,oldlength;
  int   i,j;
  Event c;

  /* Bildet Set1 vereinigt Set2 */
  /* Zuerst wird groesseres Set in Erg kopiert, dann wird jedes Element aus */
  /* kleinerem Set getestet, ob es darin vorkommt, und gegebenenfalls kopiert */
  if (Set1->Length>Set2->Length)
  {
    smallerset=Set2;
    largerset=Set1;
  }
  else
  {
    smallerset=Set1;
    largerset=Set2;
  }
  for (oldlength=newlength=largerset->Length,i=0;i<oldlength;i++)
    Erg->Set[i]=largerset->Set[i];
  for (i=0;i<smallerset->Length;i++)
  {
    c=smallerset->Set[i];
    for (j=0;j<oldlength && largerset->Set[j]!=c;j++);
    if (j==oldlength)
      Erg->Set[newlength++]=c;
  }
  Erg->Length=newlength;
}

/* *************************************************************** */

#ifdef __STDC__
public void SchneideEvSets(Class Erg, Class Set1, Class Set2) /* Set1,Set2 muessen definiert sein */
                      
#else /* ! __STDC__ */
public void SchneideEvSets(Erg,Set1,Set2) /* Set1,Set2 muessen definiert sein */
  Class Erg,Set1,Set2;
#endif /* ! __STDC__ */
{
  int   newlength;
  int   i,j;
  Event c;

  for (newlength=i=0;i<Set1->Length;i++)
    for (j=0,c=Set1->Set[i];j<Set2->Length;j++)
      if (Set2->Set[j]==c)
      {
	Erg->Set[newlength++]=c;
	break;
      }
  Erg->Length=newlength;
}

/* *************************************************************** */

#ifdef __STDC__
public void MinusEvSets(Class Erg, Class Set1, Class Set2) /* Set1,Set2 muessen definiert sein */
                      
#else /* ! __STDC__ */
public void MinusEvSets(Erg,Set1,Set2) /* Set1,Set2 muessen definiert sein */
  Class Erg,Set1,Set2;
#endif /* ! __STDC__ */
{
  /* liefert Set1 \ Set2 in Erg */

  int   newlength;
  int   i,j;
  Event c;

  for (newlength=i=0;i<Set1->Length;i++)
  {
    for (c=Set1->Set[i],j=0;j<Set2->Length;j++)
      if (c==Set2->Set[j])
	break;
    if (j==Set2->Length)
      Erg->Set[newlength++]=c;
  }
  Erg->Length=newlength;
}

/* *************************************************************** */

#ifdef __STDC__
public void CopyEvSets(Class Ziel, Class Quelle)
#else /* ! __STDC__ */
public void CopyEvSets(Ziel,Quelle)
  Class Ziel,Quelle;
#endif /* ! __STDC__ */
{
  int i;

  /* Bauernfeind: 23.07.93; nicht normierte for-Schleife */
  /* for (i=Ziel->Length=Quelle->Length;i;Ziel->Set[--i]=Quelle->Set[i]); */

  i = 0;
  Ziel->Length = Quelle->Length;
  while(i < Quelle->Length)
  {
      Ziel->Set[i] = Quelle->Set[i];
      i++;
  }
}

/* *************************************************************** */

#ifdef __STDC__
public int InEvSet(int InEvent, Class ISet) /* ersetzt Pascal: Event IN Eventset */
              
             
#else /* ! __STDC__ */
public int InEvSet(InEvent,ISet) /* ersetzt Pascal: Event IN Eventset */
  int InEvent;
  Class ISet;
#endif /* ! __STDC__ */
{
  int i;

  for (i=0;i<ISet->Length;i++)
    if ((Event)InEvent==ISet->Set[i])
      return(1);
  return(0);
}

/* *************************************************************** */

#ifdef __STDC__
public void InsertInEvSet(int InEvent, Class ISet)
#else /* ! __STDC__ */
public void InsertInEvSet(InEvent,ISet)
  int InEvent;
  Class ISet;
#endif /* ! __STDC__ */
{
  ISet->Set[ISet->Length++]=(Event)InEvent;
}

/* *************************************************************** */
/*
public void PrintEvSet(Set)
  Class Set;
{
  int i;

  for (i=0;i<Set->Length;i++)
    printf(" %d",Set->Set[i]);
  printf(" EOS\n");
}
*/

#ifdef __STDC__
Class test(void)
#else /* ! __STDC__ */
Class test()
#endif /* ! __STDC__ */
{
  Class Set;

  Set=(Class)malloc(sizeof(struct EvSet));
  printf("%d Bytes.\n",sizeof(struct EvSet));
  return(Set);
}

/* *************************************************************** */
/* Nicht mehr noetig, da dieses C Strukturen kopieren kann. */
/* Bauernfeind: 24.06.93; nicht mehr noetig, da Algorithmus in */
/*      CiFindePos geaendert wurde.                            */
/*
public void CopyKomprUebergang(Ziel,Quelle)
  KomprUebergang Ziel;
  KomprUebergang Quelle;
{
  int i;

  Ziel->StateNumber=Quelle->StateNumber;
  Ziel->KantenNumber=Quelle->KantenNumber;
  Ziel->ActionNumber=Quelle->ActionNumber;
  for (i=0;i<=MaxKomprState;i++)
    Ziel->Default[i]=Quelle->Default[i];
  for (i=0;i<=MaxKomprState;i++)
    Ziel->Base[i]=Quelle->Base[i];
  for (i=0;i<=MaxKomprKanten;i++)
    Ziel->Next[i]=Quelle->Next[i];
  for (i=0;i<=MaxKomprKanten;i++)
    Ziel->Check[i]=Quelle->Check[i];
  for (i=0;i<=MaxKomprState;i++)
    Ziel->Actions[i]=Quelle->Actions[i];
}
*/




/*******************************************************************/
/*                                                                 */
/*  Prozedur: IsOneElementic          Version:  20/05/91           */
/*                                                                 */
/*******************************************************************/
/*                                                                 */
/*  Klassifizierung:  Funktion                                     */
/*                                                                 */
/*  Funktionsbeschreibung:                                         */
/*  Diese Funktion liefert true, wenn IoSet 0 oder 1 Element       */
/*  besitzt, sonst false.                                          */
/*-----------------------------------------------------------------*/
/*                                                                 */
/*  Eingabeparameter:                                              */
/*  IoSet                     Class                                */
/*  Ausgabeparameter:                                              */
/*  IsOneElementic            boolean                              */
/*  Seiteneffekte:                                                 */
/*                                                                 */
/*  Lokale Variablen:                                              */
/*  IoLowBound                Event                                */
/*  IoMiddle                  Event                                */
/*  IoUpBound                 Event                                */
/*  IoFertig                  boolean                              */
/*  IoErg                     boolean                              */
/* entfallen alle                                                  */
/*******************************************************************/

#ifdef __STDC__
private int IsOneElementic(Class IoSet)
#else /* ! __STDC__ */
private int IsOneElementic(IoSet)
  Class IoSet;
#endif /* ! __STDC__ */
{
  return((int)IoSet->Length<=1);
}




/*******************************************************************/
/*                                                                 */
/*  Prozedur: ClPartition             Version:  20/05/91           */
/*                                                                 */
/*******************************************************************/
/*                                                                 */
/*  Klassifizierung:  Prozedur                                     */
/*                                                                 */
/*  Funktionsbeschreibung:                                         */
/*  In dieser Prozedur wird die bestehende Partition (ClassTable)  */
/*  auf ihre Gueltigkeit bezueglich der Menge CpClass ueberprueft  */
/*  und ggf. so verfeinert, dass sie wieder gueltig ist:           */
/*                                                                 */
/*  1. Fuer jeden Eintrag in ClassTable:                           */
/*     a) Zerlege den Eintrag die Elemente, die in CpClass         */
/*        enthalten sind (CpHc1) und jene, die nicht in CpClass    */
/*        enthalten sind (CpHc2).                                  */
/*     b) Sind beide Mengen nicht leer, wird der Eintrag also von  */
/*        CpClass  echt zerlegt, so loesche den alten Eintrag und  */
/*        trage die beiden Teile der Zerlegung als neue Elemente   */
/*        in die Tabelle ein.                                      */
/*                                                                 */
/*                                                                 */
/*-----------------------------------------------------------------*/
/*                                                                 */
/*  Eingabeparameter:                                              */
/*  CpClass                   Class                                */
/*  Seiteneffekte:                                                 */
/*                                                                 */
/*  CpEvent                   Event                                */
/*  CpIndex                   0..maxclasses + 1                    */
/*  CpHc1                     Class                                */
/*  CpHc2                     Class                                */
/*  CpIs11                    boolean                              */
/*  CpIs12                    boolean                              */
/*  Lokale Prozeduren und Funktionen:                              */
/*             IsOneElementic                                      */
/*******************************************************************/

#ifdef __STDC__
private void ClPartition(Class CpClass)
                		/* Pointer auf EvSet-Struktur */
#else /* ! __STDC__ */
private void ClPartition(CpClass)
  Class CpClass;		/* Pointer auf EvSet-Struktur */
#endif /* ! __STDC__ */
{
/*  Event  CpEvent;  wird wahrscheinlich nicht benoetigt */
  int    CpIndex;		/* 0..MaxClasses+1 */
  struct EvSet CpHc1,CpHc2;	/* Class-Strukturen */
  int    CpIs11,CpIs12;		/* boolean */

  CpIndex=0;
  while (CpIndex<ClFirstOne)
  {
    /* 1a */
    SchneideEvSets(&CpHc1,&ClassTable[CpIndex],CpClass);
    MinusEvSets(&CpHc2,&ClassTable[CpIndex],&CpHc1);
    /* 1b */
    if (CpHc1.Length && CpHc2.Length)
    {
      CpIs11=IsOneElementic(&CpHc1);
      CpIs12=IsOneElementic(&CpHc2);
      if (CpIs11==CpIs12)
      {
	if (CpIs11)
	{
	  CopyEvSets(&ClassTable[ClErg->ClassNumber++],&CpHc2);
	  CopyEvSets(&ClassTable[CpIndex],&ClassTable[--ClFirstOne]);
	  CopyEvSets(&ClassTable[ClFirstOne],&CpHc1);
	}
	else
	{
          CopyEvSets(&ClassTable[ClErg->ClassNumber++],&ClassTable[ClFirstOne]);
	  CopyEvSets(&ClassTable[CpIndex],&CpHc1);
	  CopyEvSets(&ClassTable[ClFirstOne++],&CpHc2);
	}
      }
      else
      {
	if (CpIs11)
	{
	  CopyEvSets(&ClassTable[ClErg->ClassNumber++],&CpHc1);
	  CopyEvSets(&ClassTable[CpIndex],&CpHc2);
	}
	else
	{
	  CopyEvSets(&ClassTable[ClErg->ClassNumber++],&CpHc2);
	  CopyEvSets(&ClassTable[CpIndex],&CpHc1);
	}
      }
    }
    else
      CpIndex++;
  }
}




/*******************************************************************/
/*                                                                 */
/*  Prozedur: CsHash                  Version:  20/05/91           */
/*                                                                 */
/*******************************************************************/
/*                                                                 */
/*  Klassifizierung:  Funktion                                     */
/*                                                                 */
/*  Funktionsbeschreibung:                                         */
/*  Diese Funktion berechnet die Position eines Zustandes in der   */
/*  HashTabelle. Die Tabelle ist als Hash-Tabelle mit einfacher    */
/*  Konfliktaufloesung (sukkzessives Durchsuchen nach freien       */
/*  Eintraegen realisiert.                                         */
/*                                                                 */
/*-----------------------------------------------------------------*/
/*                                                                 */
/*  Eingabeparameter:                                              */
/*  ChState                   Status                               */
/*  Ausgabeparameter:                                              */
/*  CsHash                    CsHashIndex                          */
/*  Seiteneffekte:                                                 */
/*                                                                 */
/*  Lokale Variablen:                                              */
/*  ChErg                     CsHashIndex                          */
/*******************************************************************/

#ifdef __STDC__
private int CsHash(Status ChState)
#else /* ! __STDC__ */
private int CsHash(ChState)
  Status ChState;
#endif /* ! __STDC__ */
{
  CsHashIndex ChErg;

  for (ChErg=ChState % CsHashLength;CsHashTab[ChErg].FolgeState!=ChState && CsHashTab[ChErg].FolgeState;ChErg=(ChErg+13) % CsHashLength);
  if (!CsHashTab[ChErg].FolgeState)
  {
    CsHashTab[ChErg].FolgeState=ChState;
    CsHashTab[ChErg].EventKlasse.Length=0;
  }
  return(ChErg);
}




/*******************************************************************/
/*                                                                 */
/*  Prozedur: ClassifyState           Version:  20/05/91           */
/*                                                                 */
/*******************************************************************/
/*                                                                 */
/*  Klassifizierung:  Prozedur                                     */
/*                                                                 */
/*  Funktionsbeschreibung:                                         */
/*  Diese Prozedur ueberprueft, ob die durch ClassTable gegebene   */
/*  Partition fuer den gegebenen Zustand CsState vertraeglich ist  */
/*  und verfeinert sie ggf. so, dass dies der Fall ist. Sie darf   */
/*  nur aufgerufen werden, wenn der angegebene Zustand mindestens  */
/*  eine Kante hat, also Delta(.CsState.) <> nil ist               */
/*                                                                 */
/*  1. Bilde in der Hashtabelle zu jedem Folgezustand in den       */
/*     Kanten von CsState die Menge der Ereignisse, die auf        */
/*     diesen Zustand fuehren. Die Laenge der Hashtabelle reicht   */
/*     aus, da jeder Zustand maximal so viele Kanten haben kann,   */
/*     wie es Ereignisse gibt. (deterministischer Automat!) und    */
/*     die Konfliktaufloesung der Hashfunktion eine vollstaen-     */
/*     dige Belegung der Tabelle ermoeglicht.                      */
/*  2. Fuer jede berechnete Menge und die Menge der Ereignisse, die*/
/*     nicht in der Kante vorkommen (CsDefault) wird die Vertraeg- */
/*     lichkeit der Bisherigen Partition mit ClParttion            */
/*     ueberprueft und diese ggf. verfeinert.                      */
/*-----------------------------------------------------------------*/
/*                                                                 */
/*  Eingabeparameter:                                              */
/*  CsState                   Status                               */
/*  Seiteneffekte:                                                 */
/*                                                                 */
/*-----------------------------------------------------------------*/
/*                                                                 */
/*  Lokale Typen:                                                  */
/*                                                                 */
/*  Lokale Variablen:                                              */
/*  CsHk                      KantenMenge                          */
/*  CsHashIndx                CsHashIndex                          */
/*  CsHashTab                 CsClassTable                         */
/*  CsClass                   Class                                */
/*  CsDefault                 Class                                */
/*  Lokale Prozeduren und Funktionen:                              */
/*             CsHash                                              */
/*******************************************************************/

#ifdef __STDC__
private void ClassifyState(Status CsState)
#else /* ! __STDC__ */
private void ClassifyState(CsState)
  Status CsState;
#endif /* ! __STDC__ */
{
  KantenMenge  CsHk;
  CsHashIndex  CsHashIndx;
  struct EvSet CsDefault,Dummy;
  int          i;

  /* 1 */
  for (CsHashIndx=0;CsHashIndx<CsHashLength;CsHashTab[CsHashIndx++].FolgeState=0);
  for (i=MinEvent,CsDefault.Length=(MaxEvent-MinEvent+1);i<=MaxEvent;i++)
    CsDefault.Set[i]=(Event)i;
  for (CsHk=Delta[CsState];CsHk;CsHk=CsHk->Nachfolger)
  {
    CsHashIndx=CsHash(CsHk->FolgeZustand);
    UnionEvSets(&Dummy,&CsHashTab[CsHashIndx].EventKlasse,&ClTranslTable[CsHk->Ereignis]);
    CopyEvSets(&CsHashTab[CsHashIndx].EventKlasse,&Dummy);
  }
  /* 2 */
  for (CsHashIndx=0;CsHashIndx<CsHashLength;CsHashIndx++)
    if (CsHashTab[CsHashIndx].FolgeState)
    {
      ClPartition(&CsHashTab[CsHashIndx].EventKlasse);
      MinusEvSets(&Dummy,&CsDefault,&CsHashTab[CsHashIndx].EventKlasse);
      CopyEvSets(&CsDefault,&Dummy);
    }
  ClPartition(&CsDefault);
}




/*******************************************************************/
/*                                                                 */
/*  Prozedur: ClTransformTable        Version:  20/05/91           */
/*                                                                 */
/*******************************************************************/
/*                                                                 */
/*  Klassifizierung:  Prozedur                                     */
/*                                                                 */
/*  Funktionsbeschreibung:                                         */
/*  Diese Prozedur wandelt die Partitionstabelle (ClassTable)      */
/*  in eine Tabelle um, die zu jedem Ereignis die Klasse angibt,   */
/*  in der das Ereignis steht. Dabei findet sie fuer jedes         */
/*  definierte Ereignis durch lineares Suchen in ClassTable die    */
/*  zugehoerige Klasse und traegt diese in ClErg.EventTable ein.   */
/*                                                                 */
/*                                                                 */
/*-----------------------------------------------------------------*/
/*                                                                 */
/*  Seiteneffekte:                                                 */
/*                                                                 */
/*  Lokale Variablen:                                              */
/*  CtIndex                   0..maxclasses + 1                    */
/*  CtFound                   boolean                              */
/*  CtEvent                   Event                                */
/*******************************************************************/

#ifdef __STDC__
private void ClTransformTable(void)
#else /* ! __STDC__ */
private void ClTransformTable()
#endif /* ! __STDC__ */
{
  int   CtIndex;	       	/* 0..MaxClasses+1 */
  int   CtFound;		/* boolean */
  int   CtEvent;		/* (Event) */

  for (CtEvent=MinEvent;CtEvent<=MaxEvent;CtEvent++)
  {
    CtIndex=CtFound=0;
    while (!CtFound)
    {
      if (InEvSet(CtEvent,&ClassTable[CtIndex]))
      {
	ClErg->EventTable[CtEvent]=CtIndex;
	CtFound=1;
      }
      else
	CtIndex++;
    }
  }
}




/*******************************************************************/
/*                                                                 */
/*  Prozedur: InitTranslTable         Version:  20/05/91           */
/*                                                                 */
/*******************************************************************/
/*                                                                 */
/*  Klassifizierung:  Prozedur                                     */
/*                                                                 */
/*  Funktionsbeschreibung:                                         */
/*  Diese Routine initialisiert je nach Zustand der Variablen      */
/*  ignore_case die ClTranslTable                                  */
/*                                                                 */
/*-----------------------------------------------------------------*/
/*                                                                 */
/*  Seiteneffekte:                                                 */
/*                                                                 */
/*  Lokale Variablen:                                              */
/*  ItIndex                   Event                                */
/*******************************************************************/

#ifdef __STDC__
private void InitTranslTable(void)
#else /* ! __STDC__ */
private void InitTranslTable()
#endif /* ! __STDC__ */
{
  int ItIndex;

  for (ItIndex=MinEvent;ItIndex<=MaxEvent;ItIndex++)
  {
    ClTranslTable[ItIndex].Length=0;
    if (flags[ignorecase])
    { /* EBCDIC muesste hier geaendert werden */
      if ('a'<=ItIndex && ItIndex<='z')
      {
	InsertInEvSet(ItIndex,&ClTranslTable[ItIndex]);
	InsertInEvSet(ItIndex-'a'+'A',&ClTranslTable[ItIndex]);
                /* Durch PushEvent, PushSet und PushStr
                   (^ siehe AutStack) wird sichergestellt,
                   dass falls flags(.ignorecase.) gesetzt ist  n u r
                   Kleinbuchstaben als Kante erzeugt werden (niemals Gross-
                   buchstaben). */
      }
      else if ('A'<=ItIndex && ItIndex<='Z')
	;
      else
	InsertInEvSet(ItIndex,&ClTranslTable[ItIndex]);
    }
    else
      InsertInEvSet(ItIndex,&ClTranslTable[ItIndex]);
  }
}




/*******************************************************************/
/*                                                                 */
/*  Prozedur: Classify                Version:  20/05/91           */
/*                                                                 */
/*******************************************************************/
/*                                                                 */
/*  Klassifizierung:  Prozedur                                     */
/*                                                                 */
/*  Funktionsbeschreibung:                                         */
/*  Diese Prozedur fasst zu einem gegebenen Automaten die Eingabe- */
/*  zeichen so zu moeglichst wenigen Klassen zusammen, dass die    */
/*  Funktion des Automaten davon unbeeintraechtigt bleibt. Dies    */
/*  minimiert die Anzahl der benoetigten Kanten und verkleinert    */
/*  somit die Groesse der Uebergangstabelle bei vernachlaessigbarer*/
/*  Erhoehung der Zeitkomplexitaet waehrend der Ausfuehrung        */
/*  (ein Array-Zugriff mehr).                                      */
/*                                                                 */
/*  Das Ergebnis der Prozedur ist eine Tabelle, die jedem          */
/*  Eingabezeichen eine Klasse zuordnet, sowie eine Variable, die  */
/*  die Anzahl der Erzeugten Klassen beinhaltet.                   */
/*                                                                 */
/*  Zur Loesung der Aufgabe wird die groebste Partition der Menge  */
/*  aller Eingabezeichen berechnet und dann in die Transformations-*/
/*  tabelle umgenwandelt:                                          */
/*                                                                 */
/*  1. Erzeuge als einzige Partition die Menge aller Eingabezeichen*/
/*     und trage sie in die Partitionstabelle (ClassTable) ein.    */
/*                                                                 */
/*  2. Verfeinere die Partition fuer jeden Zustand des Automaten   */
/*     mit Hilfe der Prozedur ClassifyState.                       */
/*                                                                 */
/*  3. Wandele die Partitionstabelle in die gewuenschte            */
/*     Transformationstabelle um (ClTransformTable).               */
/*                                                                 */
/*-----------------------------------------------------------------*/
/*                                                                 */
/*  Eingabeparameter:                                              */
/*  ClAutomat                 Automat                              */
/*  Transientparameter:                                            */
/*  ClErg                     ClassDescr                           */
/*  Seiteneffekte:                                                 */
/*                                                                 */
/*-----------------------------------------------------------------*/
/*                                                                 */
/*  Lokale Typen:                                                  */
/*                                                                 */
/*  Lokale Variablen:                                              */
/*  ClassTable                ClassTableType                       */
/*  ClTranslTable             EventTranslTable                     */
/*  ClFirstOne                0..maxClasses+1                      */
/*  ClHs                      StateSet                             */
/*  Lokale Prozeduren und Funktionen:                              */
/*             ClPartition                                         */
/*                  IsOneElementic                                 */
/*             ClassifyState                                       */
/*                  CsHash                                         */
/*             ClTransformTable                                    */
/*             InitTranslTable                                     */
/*******************************************************************/

#ifdef __STDC__
public void Classify(Automat ClAutomat, ClassDescr ClErgPtr)
#else /* ! __STDC__ */
public void Classify(ClAutomat,ClErgPtr)
  Automat    ClAutomat;
  ClassDescr ClErgPtr;
#endif /* ! __STDC__ */
{
  StateSet ClHs;
  int i;

  ClErg=ClErgPtr;

  /* 1 */
  ClErg->ClassNumber=1;
  ClFirstOne=1;
  for (i=MinEvent,ClassTable[0].Length=(MaxEvent-MinEvent+1);i<=MaxEvent;i++)
    ClassTable[0].Set[i]=(Event)i;
  InitTranslTable();

  /* 2 */
  for (ClHs=ClAutomat->BelegteZustaende;ClHs && ClFirstOne;ClHs=ClHs->Nachfolger)
    if (Delta[ClHs->State])
      ClassifyState(ClHs->State);

  /* 3 */
  ClTransformTable();
}




/*******************************************************************/
/*                                                                 */
/*  Prozedur: BsCountKanten           Version:  20/05/91           */
/*                                                                 */
/*******************************************************************/
/*                                                                 */
/*  Klassifizierung:  Funktion                                     */
/*                                                                 */
/*  Funktionsbeschreibung:                                         */
/*  Diese Funktion bestimmt die Laenge eines gegebenen Zustandes   */
/*  (BcState). Dazu werden alle Kanten dieses Zustaendes betrachtet*/
/*  und das Ergebnis fuer jede Kante inkrementiert, falls noch     */
/*  keine Kante mit einem Ereignis der gleichen Klasse zuvor       */
/*  vorkam.                                                        */
/*                                                                 */
/*-----------------------------------------------------------------*/
/*                                                                 */
/*  Eingabeparameter:                                              */
/*  BcState                   Status                               */
/*  Ausgabeparameter:                                              */
/*  BsCountKanten             Classes                              */
/*  Seiteneffekte:                                                 */
/*                                                                 */
/*  Lokale Variablen:                                              */
/*  BcHk                      KantenMenge                          */
/*  BcClassSet                set                                  */
/*  BcErg                     integer32                            */
/*  BcEvent                   Event                                */
/*******************************************************************/

#ifdef __STDC__
private Classes BsCountKanten(Status BcState, ClassDescr BsClasses)
#else /* ! __STDC__ */
private Classes BsCountKanten(BcState,BsClasses)
  Status     BcState;
  ClassDescr BsClasses;
#endif /* ! __STDC__ */
{
  KantenMenge  BcHk;
  struct EvSet BcClassSet;	/* geht von 0 bis 255 */
  int          BcErg;
  Event        BcEvent;

  BcHk=Delta[BcState];
  BcClassSet.Length=0;
  BcErg=0;
  while (BcHk)
  {
    BcEvent=BcHk->Ereignis;
    if (!InEvSet(BsClasses->EventTable[BcEvent],&BcClassSet))
    {
      BcErg++;
      InsertInEvSet(BsClasses->EventTable[BcEvent],&BcClassSet);
    }
    BcHk=BcHk->Nachfolger;
  }
  return(BcErg);
}




/*******************************************************************/
/*                                                                 */
/*  Prozedur: BuildStateLength        Version:  20/05/91           */
/*                                                                 */
/*******************************************************************/
/*                                                                 */
/*  Klassifizierung:  Prozedur                                     */
/*                                                                 */
/*  Funktionsbeschreibung:                                         */
/*  Diese Prozedur baut aus dem Automaten (BsAutomat) nach der     */
/*  Klassifizierung eine Tabelle auf, die jede moegliche           */
/*  Zustandslaenge (d.h. Anzahl der unterschiedlichen Folgezu-     */
/*  staende eines Zustandes) auf die Menge der Zustaende abbildet, */
/*  die diese Laenge haben. Das Ergebnis wird in BsStateLength     */
/*  zurueckgegeben. Gleichzeitig wird jedem Zustand eine           */
/*  neue Nummer zugewiesen, die Abbildung von der alten auf        */
/*  die neue Zustandsnummer wird in BsNewState festgehalten.       */
/*  Der Fangzustand erhaelt die Nummer 0, der Startzustand die     */
/*  Nummer 1. Die Prozedur geht dabei so vor, dass sie, nachdem    */
/*  alle Eintraege der Tabelle auf die leere Menge gesetzt wurden, */
/*  fuer jeden Zustand des Automaten dessen Laenge mit Hilfe der   */
/*  Funktion BsCountKanten ermittelt und den Zustand dann in die   */
/*  entsprechende Menge aus der Tabelle eintraegt.                 */
/*                                                                 */
/*-----------------------------------------------------------------*/
/*                                                                 */
/*  Eingabeparameter:                                              */
/*  BsAutomat                 Automat                              */
/*  BsClasses                 ClassDescr                           */
/*  Transientparameter:                                            */
/*  BsStateLength             StateLength                          */
/*  BsNewState                CoStateTable                         */
/*  BsStateNumber             KomprState                           */
/*  Seiteneffekte:                                                 */
/*                                                                 */
/*  Lokale Variablen:                                              */
/*  BsIndex                   Classes                              */
/*  BsKantenNumber            Classes                              */
/*  BsHs                      StateSet                             */
/*  BsStateIndex              2..mackomprstate+1                   */
/*  Lokale Prozeduren und Funktionen:                              */
/*             BsCountKanten                                       */
/*******************************************************************/

#ifdef __STDC__
private void BuildStateLength(Automat BsAutomat,
                              ClassDescr BsClasses,
                              QuickSet *BsStateLength,
                              KomprState *BsNewState,
                              KomprState *BsStateNumber)
                         
                         
                             	/* Zeiger auf array[0] uebergeben */
                          	/* Zeiger auf array[0] uebergeben */
                             
#else /* ! __STDC__ */
private void BuildStateLength(BsAutomat,BsClasses,BsStateLength,BsNewState,BsStateNumber)
  Automat      BsAutomat;
  ClassDescr   BsClasses;
  QuickSet    *BsStateLength;	/* Zeiger auf array[0] uebergeben */
  KomprState  *BsNewState;	/* Zeiger auf array[0] uebergeben */
  KomprState  *BsStateNumber;
#endif /* ! __STDC__ */
{
  Classes  BsIndex,BsKantenNumber;
  StateSet BsHs;
  int      BsStateIndex;	/*  2..maxKomprState+1 */

  BsNewState[CoAutomat->StartZustand]=1;
  BsStateIndex=2;

  for (BsIndex=0;BsIndex<=BsClasses->ClassNumber;BsStateLength[BsIndex++]=EmptyStateSet);
  BsHs=BsAutomat->BelegteZustaende;
  while (BsHs!=EmptyStateSet)
  {
    if (BsHs->State!=CoAutomat->StartZustand)
    {
      if (BsStateIndex>MaxKomprState)
      /* Bauernfeind: 24.06.93; statisch->dynamisch */
	/* FatalError(1); */
      {
        MaxKomprState += MaxKomprState;
        CoKomp->Default = realloc(CoKomp->Default,(MaxKomprState+1)*sizeof(KomprState));
        CoKomp->Base    = realloc(CoKomp->Base,(MaxKomprState+1)*sizeof(int));
        CoKomp->Actions = realloc(CoKomp->Actions,(MaxKomprState+1)*sizeof(Action));
      }
     
      BsNewState[BsHs->State]=BsStateIndex++;
    }
    BsKantenNumber=BsCountKanten(BsHs->State,BsClasses);
    BsStateLength[BsKantenNumber]=(QuickSet)QSInsertState(BsHs->State,BsStateLength[BsKantenNumber]);
    BsHs=BsHs->Nachfolger;
  }
  *BsStateNumber=BsStateIndex-1;
}




/*******************************************************************/
/*                                                                 */
/*  Prozedur: CfTransformKante        Version:  20/05/91           */
/*                                                                 */
/*******************************************************************/
/*                                                                 */
/*  Klassifizierung:  Prozedur                                     */
/*                                                                 */
/*  Funktionsbeschreibung:                                         */
/*  In dieser Prozedur wird die Kante zum Zustand CtState umgewan- */
/*  delt in eine Rohkante.                                         */
/*                                                                 */
/*-----------------------------------------------------------------*/
/*                                                                 */
/*  Eingabeparameter:                                              */
/*  CtState                   Status                               */
/*  Transientparameter:                                            */
/*  CtKante                   CoRohKante                           */
/*  Seiteneffekte:                                                 */
/*                                                                 */
/*  Lokale Variablen:                                              */
/*  CtIndex                   Classes                              */
/*  CtHk                      KantenMenge                          */
/*  CtDefaultClass            Class                                */
/*******************************************************************/

#ifdef __STDC__
private void CfTransformKante(Status CtState, int *CtKante)
#else /* ! __STDC__ */
private void CfTransformKante(CtState,CtKante)
  Status CtState;
  int    *CtKante;
#endif /* ! __STDC__ */
{
  Classes     CtIndex;
  KantenMenge CtHk;

  for (CtIndex=0;CtIndex<CoClasses->ClassNumber;CtKante[CtIndex++]=0);
  CtHk=Delta[CtState];
  while (CtHk)
  {
    CtKante[CoClasses->EventTable[CtHk->Ereignis]]=CoNewState[CtHk->FolgeZustand];
    CtHk=CtHk->Nachfolger;
  }
}




/*******************************************************************/
/*                                                                 */
/*  Prozedur: CfFindeFolge            Version:  20/05/91           */
/*                                                                 */
/*******************************************************************/
/*                                                                 */
/*  Klassifizierung:  Prozedur                                     */
/*                                                                 */
/*  Funktionsbeschreibung:                                         */
/*  Diese Prozedur entnimmt zu einem bereits bearbeiteten Zustand  */
/*  den Folgezustand bei CffEvent aus der komprimierten Tabelle    */
/*  und gibt zusaetzlich die Anzahl der dafuer benoetigten         */
/*  Rekursionen zurueck.                                           */
/*                                                                 */
/*-----------------------------------------------------------------*/
/*                                                                 */
/*  Eingabeparameter:                                              */
/*  CffState                  KomprState                           */
/*  CffEvent                  Classes                              */
/*  Transientparameter:                                            */
/*  CffErg                    KomprState                           */
/*  CffRekTiefe               integer32 Wert wird zurueckgeliefert */
/*  Seiteneffekte:                                                 */
/*                                                                 */
/*  Lokale Variablen:                                              */
/*  CffOffset                 0                                    */
/*  CffNewState               KomprState                           */
/*******************************************************************/

#ifdef __STDC__
private int CfFindeFolge(KomprState CffState,
                         Classes CffEvent,
                         KomprState *CffErg)
#else /* ! __STDC__ */
private int CfFindeFolge(CffState,CffEvent,CffErg)
  KomprState  CffState;
  Classes     CffEvent;
  KomprState *CffErg;
#endif /* ! __STDC__ */
{
  int         CffOffset;	/* 0..maxKomprKanten */
  int         CffRekTiefe;

  CffRekTiefe=0;
  CffOffset=CoKomp->Base[CffState]+CffEvent;
  while (CoKomp->Check[CffOffset]!=CffState && CffState)
  {
    CffState=CoKomp->Default[CffState];
    CffOffset=CoKomp->Base[CffState]+CffEvent;
    CffRekTiefe++;
  }
  if (CffState)
    *CffErg=CoKomp->Next[CffOffset];
  else
    *CffErg=0;
  return(CffRekTiefe);
}




/*******************************************************************/
/*                                                                 */
/*  Prozedur: CfVergleiche            Version:  20/05/91           */
/*                                                                 */
/*******************************************************************/
/*                                                                 */
/*  Klassifizierung:  Prozedur                                     */
/*                                                                 */
/*  Funktionsbeschreibung:                                         */
/*  Diese Prozedur vergleicht die beiden Kanten und gibt die       */
/*  Differenzkante sowie die Anzahl der Abweichungen zurueck.      */
/*                                                                 */
/*-----------------------------------------------------------------*/
/*                                                                 */
/*  Eingabeparameter:                                              */
/*  CvKante                   CoRohKante                           */
/*  CvState                   KomprState                           */
/*  CvMaxRate                 Classes                              */
/*  Transientparameter:                                            */
/*  CvRate                    Classes                              */
/*  CvMaxRek                  integer32                            */
/*  CvDifferenz               CoRohKante                           */
/*  Seiteneffekte:                                                 */
/*                                                                 */
/*  Lokale Variablen:                                              */
/*  CvIndex                   Classes                              */
/*  CvRekTiefe                integer32                            */
/*  CvFolgeZustand            KomprState                           */
/*******************************************************************/  

#ifdef __STDC__
private void CfVergleiche(int *CvKante,
                          KomprState CvState,
                          Classes CvMaxRate,
                          Classes *CvRate,
                          int *CvMaxRek,
                          int *CvDifferenz)
                     		/* array of integer (CoRohKante) */
                     
                       
                    
                      
                         	/* array of integer */
#else /* ! __STDC__ */
private void CfVergleiche(CvKante,CvState,CvMaxRate,CvRate,CvMaxRek,CvDifferenz)
  int       *CvKante;		/* array of integer (CoRohKante) */
  KomprState CvState;
  Classes    CvMaxRate;
  Classes   *CvRate;
  int       *CvMaxRek;
  int       *CvDifferenz;	/* array of integer */
#endif /* ! __STDC__ */
{
  Classes    CvIndex;
  int        CvRekTiefe;
  KomprState CvFolgeZustand;

  *CvRate= *CvMaxRek=0;
  CvIndex=0;
  while (CvIndex<CoClasses->ClassNumber && *CvRate<=CvMaxRate)
  {
    CvRekTiefe=CfFindeFolge(CvState,CvIndex,&CvFolgeZustand);
    if (CvKante[CvIndex]==CvFolgeZustand)
    {
      CvDifferenz[CvIndex]= -1;
      if (*CvMaxRek<CvRekTiefe)
	*CvMaxRek=CvRekTiefe;
    }
    else
    {
      CvDifferenz[CvIndex]=CvKante[CvIndex];
      (*CvRate)++;
    }
    CvIndex++;
  }
}




/*******************************************************************/
/*                                                                 */
/*  Prozedur: CoFindeAehnlichsten     Version:  20/05/91           */
/*                                                                 */
/*******************************************************************/
/*                                                                 */
/*  Klassifizierung:  Prozedur                                     */
/*                                                                 */
/*  Funktionsbeschreibung:                                         */
/*  Diese Prozedur findet aus den bereits bearbeiteten Zustaenden  */
/*  denjenigen, der dem Zustand CfNewState am aehnlichsten ist, und*/
/*  gibt dessen Nummer (CfDefState) sowie alle Kanten, in denen    */
/*  sich die beiden Zustaende unterscheiden (CfDifferenzen)        */
/*  zurueck. CfDifferenzen enthaelt bei identischen Kanten den     */
/*  Eintrag -1, sonst den Eintrag  des Folgezustandes.             */
/*                                                                 */
/*-----------------------------------------------------------------*/
/*                                                                 */
/*  Eingabeparameter:                                              */
/*  CfNewState                Status                               */
/*  CfLaenge                  integer32                            */
/*  Transientparameter:                                            */
/*  CfDefState                Status                               */
/*  CfDifferenzen             CoRohKante                           */
/*  Seiteneffekte:                                                 */
/*  Lokale Variable:                                               */
/*  CfTestDifferenz           CoRohKante                           */
/*  CfTestState               Status                               */
/*  CfMaxRate                 Classes                              */
/*  CfRate                    Classes                              */
/*  CfMinRekTiefe             integer32                            */
/*  CfRekTiefe                integer32                            */
/*  CfIndex                   integer32                            */
/*  CfIndexOffset             integer32                            */
/*  CfStateSet                QuickSet                             */
/*  CfNeueKante               CoRohKante                           */
/*  CfTestKante               CoRohKante                           */
/*  Lokale Prozeduren und Funktionen:                              */
/*             CfTransformKante                                    */
/*             CfFindeFolge                                        */
/*             CfVergleiche                                        */
/*******************************************************************/

#ifdef __STDC__
private void CoFindeAehnlichsten(Status CfNewState,
                                 int CfLaenge,
                                 Status *CfDefState,
                                 int *CfDifferenzen)
#else /* ! __STDC__ */
private void CoFindeAehnlichsten(CfNewState,CfLaenge,CfDefState,CfDifferenzen)
  Status      CfNewState;
  int         CfLaenge;
  Status     *CfDefState;
  int        *CfDifferenzen;
#endif /* ! __STDC__ */
{
  CoRohKante  CfNeueKante,CfTestDifferenz;
  Status      CfTestState;
  Classes     CfMaxRate,CfRate;
  int         CfMinRekTiefe,CfRekTiefe,CfIndex,CfIndexOffset;
  QuickSet    CfStateSet;
  int         i;

  CfTransformKante(CfNewState,CfNeueKante);
  CfMaxRate=CoClasses->ClassNumber;
  *CfDefState=0;
  CfMinRekTiefe=maxint;
  for (i=0;i<=MaxClasses;i++)
    CfDifferenzen[i]=CfNeueKante[i];
  CfIndex=CfLaenge;
  CfIndexOffset=1;
  while (abs(CfIndexOffset)<CfMaxRate && CfMaxRate)
  {
    if (CfIndex>=0 && CfIndex<=CoClasses->ClassNumber)
    {
      CfStateSet=CoBearbeitet[CfIndex];
      while (CfStateSet!=EmptyStateSet && (CfIndexOffset!=1 || CfMaxRate!=1))
      {
	 /* Die Heuristik in dieser Abfrage bewirkt zwar, da= identische
            Zustaende nicht immer als solche erkannt werden. Dieser
            Nachteil,
            der je nach Scanner zwischen 1% und 5% schlechtere
            Komprimie-
            rungsergebnisse bringt, bewirkt jedoch Laufzeiteinsparungen
            zwischen 20% und 40%!  */
	CfTestState=CfStateSet->State;
	CfVergleiche(CfNeueKante,CoNewState[CfTestState],CfMaxRate,&CfRate,&CfRekTiefe,CfTestDifferenz);
	if (CfRate<CfMaxRate || (CfRate==CfMaxRate && CfMinRekTiefe>CfRekTiefe))
	{
	  CfMaxRate=CfRate;
	  CfMinRekTiefe=CfRekTiefe;
	  for (i=0;i<=MaxClasses;i++)
	    CfDifferenzen[i]=CfTestDifferenz[i];
	  *CfDefState=CoNewState[CfTestState];
	}
	CfStateSet=CfStateSet->Nachfolger;
      }
    }
    CfIndex+=CfIndexOffset;
    if (CfIndexOffset>0)
      CfIndexOffset= -CfIndexOffset-1;
    else
      CfIndexOffset=1-CfIndexOffset;
  }
}






/*******************************************************************/
/*                                                                 */
/*  Prozedur: CiFindePosition         Version:  20/05/91           */
/*                                                                 */
/*******************************************************************/
/*                                                                 */
/*  Klassifizierung:  Prozedur                                     */
/*                                                                 */
/*  Funktionsbeschreibung:                                         */
/*                                                                 */
/*-----------------------------------------------------------------*/
/*                                                                 */
/*  Eingabeparameter:                                              */
/*  CpState                   KomprState                           */
/*  CpDifferenzen             CoRohKante                           */
/*  Transientparameter:                                            */
/*  CpErg                     KomprUebergang                       */
/*  Seiteneffekte:                                                 */
/*                                                                 */
/*  Lokale Variablen:                                              */
/*  CpLokalErg                KomprUebergang                       */
/*  CpChainPointer            CoFreeChainType                      */
/*  CpHelpPointer             CoFreeChainType                      */
/*  CpEvent                   0..maxClasses + 1                    */
/*  CpEventIndex              0..maxClasses + 1                    */
/*  CpFound                   boolean                              */
/*  CpSuccess                 boolean                              */
/*  CpIndex                   -maxClasses .. maxKomprKanten        */
/*  CpLastIndex               KomprKante                           */
/*  CpFirstFree               KomprKante                           */
/*  CpInitIndex               KomprKante                           */
/*******************************************************************/

#ifdef __STDC__
private void CiFindePosition(KomprState CpState,
                             int *CpDifferenzen,
                             KomprUebergang CpErg)
                         
                               	        /* array */
                       
#else /* ! __STDC__ */
private void CiFindePosition(CpState,CpDifferenzen,CpErg)
  KomprState     CpState;
  int           *CpDifferenzen;	        /* array */
  KomprUebergang CpErg;
#endif /* ! __STDC__ */
{
  CoFreeChainType CpChainPointer,CpHelpPointer;
  int             CpEvent,CpEventIndex;	/* 0..(maxClasses + 1) */
  int             CpFound,CpSuccess;    /* boolean */
  int             CpIndex;		/* -maxClasses..maxKomprKanten */
  int             loop_count;    /* Schleifenzaehler */
  KomprKante      CpLastIndex,CpFirstFree,CpInitIndex;
  KompaktDiff     NeuDifferenzen;  

  /* Fuellen der Kompaktstruktur: Differenzen "direkt hintereinander" */
  CpIndex = 0;
  NeuDifferenzen[0].class_index = -1;   /* Marke fuer Ende der Differenzen setzen */
  for(CpEvent=0;CpEvent<CoClasses->ClassNumber;CpEvent++)
       if (CpDifferenzen[CpEvent] > -1)      /* "Differenz gefunden " */
       {
          NeuDifferenzen[CpIndex].class_index = CpEvent;
          NeuDifferenzen[CpIndex].FolgeState  = CpDifferenzen[CpEvent];
          CpIndex++;
          NeuDifferenzen[CpIndex].class_index = -1;
       }

  CpChainPointer=CoFreeChain;
  CpFirstFree=CoFirstFree;
  CpEvent=CpFound=0;

  if (NeuDifferenzen[0].class_index > -1) CpFound = 1;

  if (CpFound)
  {
    CpEvent = NeuDifferenzen[0].class_index;
    do
    {
        /* Erstes freies Element in Next-Feld suchen und Index bestimmen */
        if (CpChainPointer->Offset>-1)
            CpIndex=CpChainPointer->Offset-CpEvent;
        else if (CpFirstFree>MaxKomprKanten)
           /* Bauernfeind: 24.06.93; statisch->dynamisch */
	   /* FatalError(2); */			/* keine Fortsetzung */
           {
             CpInitIndex = MaxKomprKanten;
             MaxKomprKanten += 2000;
             CoKomp->Next  = realloc(CoKomp->Next,(MaxKomprKanten+1)*sizeof(int));
             CoKomp->Check = realloc(CoKomp->Check, (MaxKomprKanten+1)*sizeof(KomprState));
             /* Initialisierung der neuen Feldelemente */
             for (CpInitIndex++;CpInitIndex<=MaxKomprKanten;CpInitIndex++)
             {
                 CoKomp->Next[CpInitIndex] = -1;
                 CoKomp->Check[CpInitIndex] = 0;
             }
             CiFindePosition(CpState,CpDifferenzen,CpErg);
             return;
           }
        else
        {
	  CpIndex=CpFirstFree-CpEvent;
	  CpFirstFree++;
        }

        /* Versuch, alle weiteren Differenzen in Next-Feld unterzubringen */
        CpSuccess=1;
        CpEventIndex = 0;
        while (NeuDifferenzen[CpEventIndex].class_index != -1 && CpEventIndex<CoClasses->ClassNumber && CpSuccess)
        {
	    if (CpErg->Next[(CpIndex+NeuDifferenzen[CpEventIndex].class_index)]==-1)
	        CpLastIndex=CpIndex+NeuDifferenzen[CpEventIndex].class_index;
	    else
	        CpSuccess=0;
	    CpEventIndex++;
        }

        /* Wenn Versuch fehlgeschlagen, dann mit neuer Basis neu versuchen */
        if (CpChainPointer->Nachfolger)
	    CpChainPointer=CpChainPointer->Nachfolger;
    } while (!CpSuccess);


    /* Differenz kann in Next untergebracht werden. Hier erfolgen die */
    /* Eintragungen in das Next- und Check-Feld */
    CpErg->Base[CpState] = CpIndex;
    for (CpEventIndex=0;NeuDifferenzen[CpEventIndex].class_index > -1;CpEventIndex++)
    {
        CpErg->Next[(CpIndex+NeuDifferenzen[CpEventIndex].class_index)] =
                   NeuDifferenzen[CpEventIndex].FolgeState;
        CpErg->Check[CpIndex+NeuDifferenzen[CpEventIndex].class_index] = CpState;
    }

    CpChainPointer=CoFreeChain;
    while (CpChainPointer->Offset>-1)
    {
      if (CpErg->Next[CpChainPointer->Offset]>-1)
      {
	CpHelpPointer=CpChainPointer->Nachfolger;
	CpChainPointer->Offset=(CpChainPointer->Nachfolger)->Offset;
	CpChainPointer->Nachfolger=(CpChainPointer->Nachfolger)->Nachfolger;
	free(CpHelpPointer);
      }
      else
	CpChainPointer=CpChainPointer->Nachfolger;
    }
    CoChainEnd=CpChainPointer;

    if (CpLastIndex>=CoFirstFree)
    {
      for (CpIndex=CoFirstFree;CpIndex<=CpLastIndex;CpIndex++)
      {
	if (CpErg->Next[CpIndex]==-1)
	{
	  if (CoFirstFree>MaxKomprKanten)
           /* Bauernfeind: 24.06.93; statisch->dynamisch */
	   /* FatalError(2); */			/* keine Fortsetzung */
           {
             CpInitIndex = MaxKomprKanten;
             MaxKomprKanten += 2000;
             CoKomp->Next  = realloc(CoKomp->Next,(MaxKomprKanten+1)*sizeof(int));
             CoKomp->Check = realloc(CoKomp->Check, (MaxKomprKanten+1)*sizeof(KomprState));
             /* Initialisierung der neuen Feldelemente */
             for (CpInitIndex++;CpInitIndex<=MaxKomprKanten;CpInitIndex++)
             {
                 CoKomp->Next[CpInitIndex] = -1;
                 CoKomp->Check[CpInitIndex] = 0;
             }
           }

	  CoChainEnd->Offset=CpIndex;
	  CoChainEnd->Nachfolger=(CoFreeChainType)malloc(sizeof(struct CoFreeChainElement));
	  CoChainEnd=CoChainEnd->Nachfolger;
	  CoChainEnd->Offset= -1;
	  CoChainEnd->Nachfolger=NULL;
	}
      }
      CoFirstFree=CpLastIndex+1;
    }
  }
  else                /*  Die Kante ist identisch mit der Default-Kante*/
    CpErg->Base[CpState]=0;
}




/*******************************************************************/
/*                                                                 */
/*  Prozedur: CoInsertState           Version:  20/05/91           */
/*                                                                 */
/*******************************************************************/
/*                                                                 */
/*  Klassifizierung:  Prozedur                                     */
/*                                                                 */
/*  Funktionsbeschreibung:                                         */
/*    Diese Prozedur traegt den neuen Zustand CiState in die       */
/*    komprimierte Uebergangstabelle ein, falls es sich nicht um   */
/*    den Fangzustand handelt.                                     */
/*                                                                 */
/*-----------------------------------------------------------------*/
/*                                                                 */
/*  Eingabeparameter:                                              */
/*  CiState                   Status                               */
/*  CiDefState                KomprState                           */
/*  CiDifferenzen             CoRohKante                           */
/*  Transientparameter:                                            */
/*  CiErg                     KomprUebergang                       */
/*  Seiteneffekte:                                                 */
/*  Lokale Variable:                                               */
/*  CiNewState                KomprState                           */
/*                                                                 */
/*  Lokale Prozeduren und Funktionen:                              */
/*             CiFindePosition                                     */
/*******************************************************************/

#ifdef __STDC__
private void CoInsertState(Status CiState,
                           KomprState CiDefState,
                           int *CiDifferenzen,
                           KomprUebergang CiErg)
                         
                            
                               	      /* darf nicht veraendert werden */
                       
#else /* ! __STDC__ */
private void CoInsertState(CiState,CiDefState,CiDifferenzen,CiErg)
  Status         CiState;
  KomprState     CiDefState;
  int           *CiDifferenzen;	      /* darf nicht veraendert werden */
  KomprUebergang CiErg;
#endif /* ! __STDC__ */
{
  KomprState     CiNewState;

  CiNewState=CoNewState[CiState];
  if (CiNewState>0)
  {
    CiErg->Default[CiNewState]=CiDefState;
    CiErg->Actions[CiNewState]=ActionTable[CiState];
    if (abs(CiErg->Actions[CiNewState]) > CiErg->ActionNumber)
      CiErg->ActionNumber=abs(CiErg->Actions[CiNewState]);
  }
  CiFindePosition(CiNewState,CiDifferenzen,CiErg);
}




/*******************************************************************/
/*                                                                 */
/*  Prozedur: CoInit                  Version:  20/05/91           */
/*                                                                 */
/*******************************************************************/
/*                                                                 */
/*  Klassifizierung:  Prozedur                                     */
/*                                                                 */
/*  Funktionsbeschreibung:                                         */
/*                                                                 */
/*-----------------------------------------------------------------*/
/*                                                                 */
/*  Seiteneffekte:                                                 */
/*                                                                 */
/*  Lokale Variablen:                                              */
/*  CbIndex                   KomprKante                           */
/*******************************************************************/

#ifdef __STDC__
private void CoInit(void)
#else /* ! __STDC__ */
private void CoInit()
#endif /* ! __STDC__ */
{
  KomprKante CbIndex;

  CoFreeChain=(CoFreeChainType)malloc(sizeof(struct CoFreeChainElement));
  CoChainEnd=(CoFreeChainType)malloc(sizeof(struct CoFreeChainElement));
  CoFreeChain->Offset=0;
  CoFreeChain->Nachfolger=CoChainEnd;
  CoChainEnd->Offset= -1;
  CoChainEnd->Nachfolger=NULL;
  CoFirstFree=1;
  for (CbIndex=0;CbIndex<=MaxKomprKanten;CbIndex++)
  {
    CoKomp->Next[CbIndex]= -1;
    CoKomp->Check[CbIndex]=0;
  }
  CoKomp->ActionNumber=0;
}




/*******************************************************************/
/*                                                                 */
/*  Prozedur: CoDisposeHeap           Version:  20/05/91           */
/*                                                                 */
/*******************************************************************/
/*                                                                 */
/*  Klassifizierung:  Prozedur                                     */
/*                                                                 */
/*  Funktionsbeschreibung:                                         */
/*  Gibt den noch belegten Heap wieder frei, namentlich die Tabelle*/
/*  CoBearbeitet und die noch belegten Elemente der CoFreeList     */
/*                                                                 */
/*-----------------------------------------------------------------*/
/*                                                                 */
/*  Seiteneffekte:                                                 */
/*                                                                 */
/*  Lokale Variablen:                                              */
/*  CdIndex                   0                                    */
/*  CdPointer                 CoFreeChainType                      */
/*******************************************************************/

#ifdef __STDC__
private void CoDisposeHeap(void)
#else /* ! __STDC__ */
private void CoDisposeHeap()
#endif /* ! __STDC__ */
{
  int             CdIndex;
  CoFreeChainType CdPointer;

  for (CdIndex=0;CdIndex<=CoClasses->ClassNumber;DisposeQuickSet(&CoBearbeitet[CdIndex++]));
  while (CoFreeChain)
  {
    CdPointer=CoFreeChain;
    CoFreeChain=CoFreeChain->Nachfolger;
    free(CdPointer);
  }
}




/*******************************************************************/
/*                                                                 */
/*  Prozedur: Compress                Version:  20/05/91           */
/*                                                                 */
/*******************************************************************/
/*                                                                 */
/*  Klassifizierung:  Prozedur                                     */
/*                                                                 */
/*  Funktionsbeschreibung:                                         */
/*                                                                 */
/*-----------------------------------------------------------------*/
/*                                                                 */
/*  Eingabeparameter:                                              */
/*  CoAutomat                 Automat                              */
/*  Transientparameter:                                            */
/*  CoClasses                 ClassDescr                           */
/*  CoKomp                    KomprUebergang                       */
/*  Seiteneffekte:                                                 */
/*                                                                 */
/*-----------------------------------------------------------------*/
/*                                                                 */
/*  Lokale Typen:                                                  */
/*                                                                 */
/*  Lokale Variablen:                                              */
/*  CoUnbearbeitet            StateLength                          */
/*  CoBearbeitet              StateLength                          */
/*  CoEvent                   0..maxclasses-1                      */
/*  CoState                   Status                               */
/*  CoDefState                Status                               */
/*  CoDifferenzen             CoRohKante                           */
/*  CoNewState                CoStateTable                         */
/*  CoFreeChain               CoFreeChainType                      */
/*  CoChainEnd                CoFreeChainType                      */
/*  CoFirstFree               0..maxkompresskanten+1               */
/*  Lokale Prozeduren und Funktionen:                              */
/*             BuildStateLength                                    */
/*                  BsCountKanten                                  */
/*             CoFindeAehnlichsten                                 */
/*                  CfTransformKante                               */
/*                  CfFindeFolge                                   */
/*                  CfVergleiche                                   */
/*             CoInsertState                                       */
/*                  CiFindePosition                                */
/*             CoInit                                              */
/*             CoDisposeHeap                                       */
/*******************************************************************/

#ifdef __STDC__
public void Compress(Automat CoAutomat2,
                     ClassDescr CoClasses2,
                     KomprUebergang CoKomp2)                            
#else /* ! __STDC__ */
public void Compress(CoAutomat2,CoClasses2,CoKomp2)
  Automat        CoAutomat2;
  ClassDescr     CoClasses2;	      /* Pointer auf Struktur, in Pascal
				         Struktur als var-Parameter */
  KomprUebergang CoKomp2;	      /* Pointer auf Struktur, in Pascal
				         Struktur als var-Parameter */
#endif /* ! __STDC__ */
{
  StateLength CoUnbearbeitet;
  int         CoEvent;		      /* 0..maxclasses-1 */
  Status      CoState,CoDefState;
  CoRohKante  CoDifferenzen;

  /* Jetzt werden globale Variablen fuer die Parameter von Compress angelegt */
  CoAutomat=CoAutomat2;
  CoClasses=CoClasses2;
  CoKomp=CoKomp2;

/* Bauernfeind: 15.06.93; Modul-globale Variable initialisieren */
   CoNewState = malloc((MaxState+1)*sizeof(KomprState));

  Classify(CoAutomat,CoClasses);
  BuildStateLength(CoAutomat,CoClasses,CoUnbearbeitet,CoNewState,&CoKomp->StateNumber);
  CoInit();

  for (CoEvent=0;CoEvent<=CoClasses->ClassNumber;CoBearbeitet[CoEvent++]=EmptyStateSet);
  for (CoEvent=CoClasses->ClassNumber;CoEvent>=0;CoEvent--)
  {
printf("Zustand %4d\r",CoEvent);
fflush(stdout);
    while (CoUnbearbeitet[CoEvent]!=EmptyStateSet)
    {
      QSGiveAndDeleteState(&CoUnbearbeitet[CoEvent],&CoState);
      /* Suche aehnlichsten Zustand in CoBearbeitet und berechne die
	 Unterschiede */
      CoFindeAehnlichsten(CoState,CoEvent,&CoDefState,CoDifferenzen);
      /* Trage die Unterschiede in die Tabellen ein */
      CoInsertState(CoState,CoDefState,CoDifferenzen,CoKomp);
      /* Trage CoState in CoBearbeitet(.CoEvent.) ein */
      CoBearbeitet[CoEvent]=QSInsertState(CoState,CoBearbeitet[CoEvent]);
    }
  }
printf("\n");
  CoKomp->KantenNumber=CoFirstFree-1;
  /* Freigabe des belegten Heaps */
  CoDisposeHeap();
}




/*******************************************************************/
/*                                                                 */
/*  Prozedur: initkompress            Version:  20/05/91           */
/*                                                                 */
/*******************************************************************/
/*                                                                 */
/*  Klassifizierung:  Prozedur                                     */
/*                                                                 */
/*  Funktionsbeschreibung:                                         */
/*  Dummy                                                          */
/*-----------------------------------------------------------------*/
/*                                                                 */
/*  Seiteneffekte:                                                 */
/*                                                                 */
/*  Lokale Prozeduren und Funktionen:                              */
/*******************************************************************/
#ifdef __STDC__
public void initkompress(void)
#else /* ! __STDC__ */
public void initkompress()
#endif /* ! __STDC__ */
{
}
