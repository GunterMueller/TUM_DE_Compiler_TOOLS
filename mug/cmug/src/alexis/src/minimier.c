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
/*  Segment: minimier.c                                            */
/*  Version: 25/05/91                                              */
/*                                                                 */
/*  Sprache: C                                                     */
/*                                                                 */
/*-----------------------------------------------------------------*/
/*                                                                 */
/*  Beschreibung:                                                  */
/*                                                                 */
/*  Inhalt:                                                        */
/*        CountSTFree                                              */
/*        CountFKanten                                             */
/*        Minimize                                                 */
/*             KillFang                                            */
/*                  IsFang                                         */
/*             DelBackEdgeSet                                      */
/*             DelDeltaMinus                                       */
/*             InsTransition                                       */
/*             BuildDeltaMinus                                     */
/*             FindUsedEvents                                      */
/*             FindStateUrbild                                     */
/*             FindUrbild                                          */
/*             showPartitions                                      */
/*             SetMinGetStackElem                                  */
/*             PushComp                                            */
/*             InitMinstack                                        */
/*             InitPartitions                                      */
/*             SetZugArray                                         */
/*             statistics                                          */
/*        initminimier                                             */
/*                                                                 */
/*-----------------------------------------------------------------*/
/*                                                                 */
/*                 M O D I F I K A T I O N E N                     */
/*=================================================================*/
/* Datum      modifiziert von    Beschreibung der Modifikation     */
/*=================================================================*/
/*******************************************************************/

#ifdef __STDC__
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#endif

#include <stdio.h>
#include "global.h"
#include "var.h"
#include "autops.h"
#include "autstack.h"
#include "stateset.h"
#include "eveset.h"
#include "error.h"


/* Bauernfeind: 17.06.93; Globale Variablen aus var.c */
extern int MaxState;
extern int MaxAction;
extern int MAX_ID_NO;
extern MakroTable MakTable;


extern void *realloc();


/* Es folgen interne Funktionsdeklarationen */

private int IsFang P_((Status Zustand, Automat Killed));
private void KillFang P_((void));
private void DelBackEdgeSet P_((BackEdgeSet InSet));
private void DelDeltaMinus P_((Automat InAutomat));
#ifdef __STDC__
private void InsTransition P_((Event Ereignis, Status toState, Status from));
#else /* ! __STDC__ */
private void InsTransition P_((int Ereignis, Status toState, Status from));
#endif /* ! __STDC__ */
private void BuildDeltaMinus P_((Automat InAutomat));
private void FindUsedEvents P_((Status ForState, EventMge *Ergebnis));
#ifdef __STDC__
private void FindStateUrbild P_((Status InState, Event TransEvent, StateSet *UrbildFound));
private void FindUrbild P_((StateSet Partcomp, Event TransEvent, StateSet *UrbildFound));
#else /* ! __STDC__ */
private void FindStateUrbild P_((Status InState, int TransEvent, StateSet *UrbildFound));
private void FindUrbild P_((StateSet Partcomp, int TransEvent, StateSet *UrbildFound));
#endif /* ! __STDC__ */
private void SetMinGetStackElem P_((void));
private void PushComp P_((Status Comp));
private void InitMinstack P_((StateSet UsedStates));
private void InitPartitions P_((StateSet *Partitions, Automat inautomat));
private void SetZugArray P_((Status *Zugehoerig));






private Partition        MinParts;
private ZugArray         MinZugeh;
private DeltaMinus       Umkehr;
private ElemCount        CompPow;
private MinStack         MinimizerStack,EventsPerState;
private Automat          MinAutomat;
private CompOnStackCount CompsOnStack;
private Status           CompInArbeit;
private Event            EventInArbeit;
private int              StackElemCount;

private Status           FirstFreePartition,LoopBound,ComponentCount,StateCount;
private int              NumberOfEvents;
private StateSet         GefUrbild,Schnitt,Rest;

  /* Fuer den Epilog */
private KantenMenge      hilfK;
private StateSet         NewStates,NewEndStates;

  /* Fuer Testhilfen */
/*
private int              IterationCount,StackCount;
private char             TestChar;
private Status           MinCompPow;
*/



/*******************************************************************/
/*                                                                 */
/*  Prozedur: IsFang                  Version:  25/05/91           */
/*                                                                 */
/*******************************************************************/
/*                                                                 */
/*  Klassifizierung:  Funktion                                     */
/*                                                                 */
/*  Funktionsbeschreibung:                                         */
/*  Pruft, ob es sich bei Zustand um einen Fangzustand handelt     */
/*-----------------------------------------------------------------*/
/*                                                                 */
/*  Eingabeparameter:                                              */
/*  Zustand                   Status                               */
/*  Ausgabeparameter:                                              */
/*  IsFang                    Boolean                              */
/*  Seiteneffekte:                                                 */
/*                                                                 */
/*  Lokale Variablen:                                              */
/*  erg                       boolean                              */
/*  abbruch                   boolean                              */
/*  hilf                      KantenMenge                          */
/*******************************************************************/

#ifdef __STDC__
private int IsFang(Status Zustand, Automat Killed)
#else /* ! __STDC__ */
private int IsFang(Zustand,Killed)
  Status  Zustand;
  Automat Killed;
#endif /* ! __STDC__ */
{
  KantenMenge hilf;
  int         abbruch;

  if (IsElement(Zustand,Killed->EndZustaende))
    return(0);
  for (abbruch=0,hilf=Delta[Zustand];hilf && !abbruch;hilf=hilf->Nachfolger)
    if (hilf->FolgeZustand!=Zustand)
    {
      abbruch=1;
      return(0);
    }
  return(1);
}




/*******************************************************************/
/*                                                                 */
/*  Prozedur: KillFang                Version:  25/05/91           */
/*                                                                 */
/*******************************************************************/
/*                                                                 */
/*  Klassifizierung:  Prozedur                                     */
/*                                                                 */
/*  Funktionsbeschreibung:                                         */
/*  Loescht alle Zustaende, die Fangzustaende sind, auf die also   */
/*  nur Kanten zeigen, von denen aber keine Kanten auf andere      */
/*  Zustaende ausgehen                                             */
/*-----------------------------------------------------------------*/
/*                                                                 */
/*  Seiteneffekte:                                                 */
/*                                                                 */
/*  Lokale Variablen:                                              */
/*  Killed                    automat                              */
/*  eliminate                 StateSet                             */
/*  hilf                      StateSet                             */
/*  hilf1                     StateSet                             */
/*  Lokale Prozeduren und Funktionen:                              */
/*             IsFang                                              */
/*******************************************************************/

#ifdef __STDC__
private void KillFang(void)
#else /* ! __STDC__ */
private void KillFang()
#endif /* ! __STDC__ */
{
  Automat  Killed;
  StateSet eliminate;		/* Menge der zu loeschenden Zustaende */
  StateSet hilf,hilf1;

  Killed=Top();
  eliminate=EmptyStateSet;
  for (hilf=Killed->BelegteZustaende;hilf;hilf=hilf->Nachfolger)
    if (IsFang(hilf->State,Killed))
    {
      eliminate=InsertState(hilf->State,eliminate);
      if (Killed->StartZustand==hilf->State)
	SoftwareError(13);
      DspState(hilf->State);
    }

  /* Alles weitere macht nur Sinn, wenn Zustaende geloescht wurden */
  if (eliminate)
  {
    MinusStateSet(&Killed->BelegteZustaende,eliminate);
    /* Endzustaende muessen nicht korrigiert werden, weil Endzustand nicht in
       eliminate sein kann */
    /* Jetzt loeschen der Fangzustaende aus den kantenmengen */
    for (hilf=Killed->BelegteZustaende;hilf;hilf=hilf->Nachfolger)
      for (hilf1=eliminate;hilf1;hilf1=hilf1->Nachfolger)
	DeleteFangKanten(hilf->State,hilf1->State);
  }
}





/*******************************************************************/
/*                                                                 */
/*  Prozedur: DelBackEdgeSet          Version:  25/05/91           */
/*                                                                 */
/*******************************************************************/
/*                                                                 */
/*  Klassifizierung:  Prozedur                                     */
/*                                                                 */
/*  Funktionsbeschreibung:                                         */
/*  Loescht eine Kantenmenge der Umkehrfunktion vom Heap           */
/*-----------------------------------------------------------------*/
/*                                                                 */
/*  Transientparameter:                                            */
/*  InSet                     BackEdgeSet                          */
/*  Seiteneffekte:                                                 */
/*                                                                 */
/*  Lokale Variablen:                                              */
/*  hilf                      BackEdgeSet                          */
/*  todelete                  BackEdgeSet                          */
/*******************************************************************/

#ifdef __STDC__
private void DelBackEdgeSet(BackEdgeSet InSet)
#else /* ! __STDC__ */
private void DelBackEdgeSet(InSet)
  BackEdgeSet InSet;
#endif /* ! __STDC__ */
{
  BackEdgeSet  hilf,todelete;

  hilf=InSet;
  while (hilf)
  {
    DisposeStateSet(&hilf->Urbild);
    todelete=hilf;
    hilf=hilf->Nachfolger;
    free(todelete);
  }
}




/*******************************************************************/
/*                                                                 */
/*  Prozedur: DelDeltaMinus           Version:  25/05/91           */
/*                                                                 */
/*******************************************************************/
/*                                                                 */
/*  Klassifizierung:  Prozedur                                     */
/*                                                                 */
/*  Funktionsbeschreibung:                                         */
/*  Loescht die komplette Umkehrfunktion vom Heap                  */
/*-----------------------------------------------------------------*/
/*                                                                 */
/*  Eingabeparameter:                                              */
/*  InAutomat                 Automat                              */
/*  Seiteneffekte:                                                 */
/*                                                                 */
/*  Lokale Variablen:                                              */
/*  DdHs                      StateSet                             */
/*******************************************************************/

#ifdef __STDC__
private void DelDeltaMinus(Automat InAutomat)
#else /* ! __STDC__ */
private void DelDeltaMinus(InAutomat)
  Automat InAutomat;
#endif /* ! __STDC__ */
{
  StateSet DdHs;

  for (DdHs=InAutomat->BelegteZustaende;DdHs;DdHs=DdHs->Nachfolger)
    if (Umkehr[DdHs->State])
      DelBackEdgeSet(Umkehr[DdHs->State]);
}




/**********************************************************************
 *                                                                    *
 * Prozeduren zum Aufbau   der Umkehrfunktion                         *
 *                                                                    *
 **********************************************************************/

/*******************************************************************/
/*                                                                 */
/*  Prozedur: InsTransition           Version:  25/05/91           */
/*                                                                 */
/*******************************************************************/
/*                                                                 */
/*  Klassifizierung:  Prozedur                                     */
/*                                                                 */
/*  Funktionsbeschreibung:                                         */
/*  Einfuegen einer Kante in die Umkehrfunktion                    */
/*                                                                 */
/*-----------------------------------------------------------------*/
/*                                                                 */
/*  Transientparameter:                                            */
/*  Ereignis                  Event                                */
/*  toState                   Status                               */
/*  from                      Status                               */
/*  Seiteneffekte:                                                 */
/*                                                                 */
/*  Lokale Variablen:                                              */
/*  hilf                      BackEdgeSet                          */
/*  schlepp                   BackEdgeSet                          */
/*  rest                      BackEdgeSet                          */
/*******************************************************************/

#ifdef __STDC__
private void InsTransition(Event Ereignis, Status toState, Status from)
#else /* ! __STDC__ */
private void InsTransition(Ereignis,toState,from)
  Event  Ereignis;
  Status toState,from;
#endif /* ! __STDC__ */
{
  BackEdgeSet hilf,schlepp,rest;

  hilf=Umkehr[toState];
  if (!hilf)
  {
    hilf=(BackEdgeSet)malloc(sizeof(struct BackEdge));
    hilf->Nachfolger=NULL;
    hilf->Ereignis=Ereignis;
    hilf->Urbild=InsertState(from,EmptyStateSet);
    Umkehr[toState]=hilf;
  }
  else    /* Fall, das in eine existente Menge etwas eingefuegt wird */
  {
    schlepp=hilf;
    for (hilf=hilf->Nachfolger;hilf && hilf->Ereignis<=Ereignis;hilf=hilf->Nachfolger)
      schlepp=hilf;
    if (schlepp->Ereignis==Ereignis)
      schlepp->Urbild=InsertState(from,schlepp->Urbild);
    else if (!hilf)
    {
      /* schlepp zeigt auf das letzte Element, dessen Ereignis kleiner ist 
	 als das einzufuegende */
      hilf=(BackEdgeSet)malloc(sizeof(struct BackEdge));
      hilf->Nachfolger=NULL;
      hilf->Ereignis=Ereignis;
      hilf->Urbild=InsertState(from,EmptyStateSet);
      schlepp->Nachfolger=hilf;
    }
    else
    {
      /* zwischen Schlepp und hilf muss ein neues Element eingefuegt werden */
      rest=hilf;
      hilf=(BackEdgeSet)malloc(sizeof(struct BackEdge));
      hilf->Nachfolger=rest;
      hilf->Ereignis=Ereignis;
      hilf->Urbild=InsertState(from,EmptyStateSet);
      schlepp->Nachfolger=hilf;
    }
  }
}




/**********************************************************************
 * Aufbau der Umkehrfunktion                                          *
 **********************************************************************/

/*******************************************************************/
/*                                                                 */
/*  Prozedur: BuildDeltaMinus         Version:  25/05/91           */
/*                                                                 */
/*******************************************************************/
/*                                                                 */
/*  Klassifizierung:  Prozedur                                     */
/*                                                                 */
/*  Funktionsbeschreibung:                                         */
/*  Aufbau der Umkehrfunktion fuer den Minimierer                  */
/*-----------------------------------------------------------------*/
/*                                                                 */
/*  Eingabeparameter:                                              */
/*  InAutomat                 Automat                              */
/*  Seiteneffekte:                                                 */
/*  Arbeitet auf den oben deklariereten globalen Variablen fuer    */
/*  die Umkehrfunktion                                             */
/*  Lokale Variablen:                                              */
/*  i                         Status                               */
/*  BdHs                      StateSet                             */
/*  hilf                      KantenMenge                          */
/*******************************************************************/

#ifdef __STDC__
private void BuildDeltaMinus(Automat InAutomat)
#else /* ! __STDC__ */
private void BuildDeltaMinus(InAutomat)
  Automat InAutomat;
#endif /* ! __STDC__ */
{
  KantenMenge hilf;
  StateSet    BdHs;
  Status      i;

  for (i=1;i<=MaxState;Umkehr[i++]=NULL);    /* Setze alle Mengen leer */
  for (BdHs=InAutomat->BelegteZustaende;BdHs;BdHs=BdHs->Nachfolger)
    for (hilf=Delta[BdHs->State];hilf;hilf=hilf->Nachfolger)
      InsTransition(hilf->Ereignis,hilf->FolgeZustand,BdHs->State);
}




/*******************************************************************/
/*                                                                 */
/*  Prozedur: FindUsedEvents          Version:  25/05/91           */
/*                                                                 */
/*******************************************************************/
/*                                                                 */
/*  Klassifizierung:  Prozedur                                     */
/*                                                                 */
/*  Funktionsbeschreibung:                                         */
/* Die Uebergangsfunktion Delta wird nach den wirklich benutzten   */
/* Ereignissen durchsucht, denn nur diese muessen spaeter auch     */
/* betrachtet werden, wenn unerledigte Komponenten auf den Stack   */
/* gepusht werden. Es werden nur benutzte Zustaende betrachtet.    */
/* Es wird zu einem Zustand eine Menge von Events angegeben        */
/*                                                                 */
/*-----------------------------------------------------------------*/
/*                                                                 */
/*  Eingabeparameter:                                              */
/*  ForState                  Status                               */
/*  Transientparameter:                                            */
/*  Ergebnis                  EventMge                             */
/*  Seiteneffekte:                                                 */
/*                                                                 */
/*  Lokale Variablen:                                              */
/*  hilf                      BackEdgeSet                          */
/*  hilfe                     EventMge                             */
/*******************************************************************/

#ifdef __STDC__
private void FindUsedEvents(Status ForState, EventMge *Ergebnis)
#else /* ! __STDC__ */
private void FindUsedEvents(ForState,Ergebnis)
  Status    ForState;
  EventMge *Ergebnis;
#endif /* ! __STDC__ */
{
  BackEdgeSet hilf;
  EventMge    hilfe;

  hilfe=EmptyEventMge;
  *Ergebnis=EmptyEventMge;
  for (hilf=Umkehr[ForState];hilf;hilf=hilf->Nachfolger)
  {
    if (!hilfe)
    {
      hilfe=(EventMge)malloc(sizeof(struct Eventmenge));
      *Ergebnis=hilfe;
    }
    else
    {
      hilfe->Nachfolger=(EventMge)malloc(sizeof(struct Eventmenge));
      hilfe=hilfe->Nachfolger;
    }
    hilfe->Even=hilf->Ereignis;
    hilfe->Nachfolger=EmptyEventMge;
  }
}




/**********************************************************************
 *                                                                    *
 * Prozeduren zur Ermittlung des Urbildes einer Menge von Zustaenden  *
 * (= Urbild einer Partitionskomponente                               *
 *                                                                    *
 **********************************************************************/

/*******************************************************************/
/*                                                                 */
/*  Prozedur: FindStateUrbild         Version:  25/05/91           */
/*                                                                 */
/*******************************************************************/
/*                                                                 */
/*  Klassifizierung:  Prozedur                                     */
/*                                                                 */
/*  Funktionsbeschreibung:                                         */
/*  Findet die Urbildmenge zu einem Zustand InState mit dem Ereigni*/
/*  und liefert sie in UrbildFound als Pointer, nicht als Kopie!   */
/*                                                                 */
/*-----------------------------------------------------------------*/
/*                                                                 */
/*  Eingabeparameter:                                              */
/*  InState                   Status                               */
/*  TransEvent                Event                                */
/*  Transientparameter:                                            */
/*  UrbildFound               StateSet                             */
/*  Seiteneffekte:                                                 */
/*                                                                 */
/*  Lokale Variablen:                                              */
/*  PointBackEdgeSet          BackEdgeSet                          */
/*******************************************************************/

#ifdef __STDC__
private void FindStateUrbild(Status InState,
                             Event TransEvent,
                             StateSet *UrbildFound)
#else /* ! __STDC__ */
private void FindStateUrbild(InState,TransEvent,UrbildFound)
  Status    InState;
  Event     TransEvent;
  StateSet *UrbildFound;
#endif /* ! __STDC__ */
{
  BackEdgeSet PointBackEdgeSet;

  *UrbildFound=EmptyStateSet;
  for (PointBackEdgeSet=Umkehr[InState];PointBackEdgeSet && PointBackEdgeSet->Ereignis<TransEvent;PointBackEdgeSet=PointBackEdgeSet->Nachfolger);
  if (PointBackEdgeSet && PointBackEdgeSet->Ereignis==TransEvent)
    *UrbildFound=PointBackEdgeSet->Urbild;
}




/*******************************************************************/
/*                                                                 */
/*  Prozedur: FindUrbild              Version:  25/05/91           */
/*                                                                 */
/*******************************************************************/
/*                                                                 */
/*  Klassifizierung:  Prozedur                                     */
/*                                                                 */
/*  Funktionsbeschreibung:                                         */
/*  Findet die Urbildmenge zu einer Menge Partcomp  mit dem Ereigni*/
/*  und liefert sie in UrbildFound als kopierte Menge zurueck      */
/*                                                                 */
/*-----------------------------------------------------------------*/
/*                                                                 */
/*  Eingabeparameter:                                              */
/*  Partcomp                  StateSet                             */
/*  TransEvent                Event                                */
/*  Transientparameter:                                            */
/*  UrbildFound               StateSet                             */
/*  Seiteneffekte:                                                 */
/*                                                                 */
/*  Lokale Variablen:                                              */
/*  PointPartComp             StateSet                             */
/*  StateUrbild               StateSet                             */
/*  Hilfsbild                 StateSet                             */
/*******************************************************************/

#ifdef __STDC__
private void FindUrbild(StateSet Partcomp,
                        Event TransEvent,
                        StateSet *UrbildFound)
#else /* ! __STDC__ */
private void FindUrbild(Partcomp,TransEvent,UrbildFound)
  StateSet  Partcomp;
  Event     TransEvent;
  StateSet *UrbildFound;
#endif /* ! __STDC__ */
{
  StateSet StateUrbild;

  for (*UrbildFound=EmptyStateSet;Partcomp;Partcomp=Partcomp->Nachfolger)
  {
    FindStateUrbild(Partcomp->State,TransEvent,&StateUrbild);
    AddStateSet(UrbildFound,StateUrbild);
  }
}




/************************************************************
 Testhilfen, zur Beobachtung des Minimierers
 ************************************************************/

/*******************************************************************/
/*                                                                 */
/*  Prozedur: showPartitions          Version:  25/05/91           */
/*                                                                 */
/*******************************************************************/
/*                                                                 */
/*  Klassifizierung:  Prozedur                                     */
/*                                                                 */
/*  Funktionsbeschreibung:                                         */
/*  Zeigt eine Partition. Wird in der Produktionsversion nicht     */
/*  aufgerufen, also nur verwendet, falls spaeter nochmal Aende-   */
/*  rungen und Tests noetig                                        */
/*-----------------------------------------------------------------*/
/*                                                                 */
/*  Transientparameter:                                            */
/*  MinParts                  Partition                            */
/*  Seiteneffekte:                                                 */
/*                                                                 */
/*  Lokale Variablen:                                              */
/*  StateCount                Status                               */
/*******************************************************************/

#ifdef __STDC__
public void showPartitions(StateSet *MinParts)
                     		/* var Partition */
#else /* ! __STDC__ */
public void showPartitions(MinParts)
  StateSet *MinParts;		/* var Partition */
#endif /* ! __STDC__ */
{
  /* Zeigt die aktuellen Partitionen des Minimierers in den Form
     Komponente 1 ------ 1 2 4 5 **
     Komponente 2 ------ 4 5 **        */
  Status StateCount;

  printf("----------- Anfang Partition ----------\n");
  for (StateCount=1;StateCount<=MaxState;StateCount++)
    if (MinParts[StateCount])
    {
      printf("Komponente %d ");
      PrintStateSet("----",MinParts[StateCount]);
    }
  printf("----------- Ende Partition ----------\n");
  StateCount=getchar();   /* Tastendruck abwarten */
}




/*********************************************************
 Operationen fuer den MinStack
 *********************************************************/

/*******************************************************************/
/*                                                                 */
/*  Prozedur: SetMinGetStackElem      Version:  25/05/91           */
/*                                                                 */
/*******************************************************************/
/*                                                                 */
/*  Klassifizierung:  Prozedur                                     */
/*                                                                 */
/*  Funktionsbeschreibung:                                         */
/*  Holt ein Paar (Component, Ereignis), dessen Komponente         */
/*  eine moeglichst kleine Maechtigkeit hat, aus dem Stack.        */
/*  Teil der Strategie, um zu n * log n Komplexitaet zu kommen     */
/*                                                                 */
/*-----------------------------------------------------------------*/
/*                                                                 */
/*  Seiteneffekte:                                                 */
/*                                                                 */
/*  Lokale Variablen:                                              */
/*  StateCount                Status                               */
/*  Min                       Status                               */
/*  MinComp                   Status                               */
/*  NotFound                  boolean                              */
/*******************************************************************/

#ifdef __STDC__
private void SetMinGetStackElem(void)
#else /* ! __STDC__ */
private void SetMinGetStackElem()
#endif /* ! __STDC__ */
{
  Status StateCount,Min,MinComp;
  int    NotFound;

  /* Erster Schritt: Ermittle die minimale Maechtigkeit aller Partitions
                     komponenten: Diese wird in MinComp gespeichert
     Zweiter Schritt: Das erste Element auf dem Stack, das diese Maechtigkeit
                      hat, wird aus der Liste geholt */
  for (NotFound=1,Min=MaxState,StateCount=1;StateCount<FirstFreePartition && NotFound;StateCount++)
    if (CompPow[StateCount]<=Min && MinimizerStack[StateCount])
    {
      Min=CompPow[StateCount];
      MinComp=StateCount;
      NotFound=(int)(Min!=1);
    }
  CompInArbeit=MinComp;
  EvGiveAndDeleteEvent(&MinimizerStack[MinComp],&EventInArbeit);
  CompsOnStack[MinComp]--;
  StackElemCount--;
}




/*******************************************************************/
/*                                                                 */
/*  Prozedur: PushComp                Version:  25/05/91           */
/*                                                                 */
/*******************************************************************/
/*                                                                 */
/*  Klassifizierung:  Prozedur                                     */
/*                                                                 */
/*  Funktionsbeschreibung:                                         */
/*   Pusht Komponente x Benutzte Ereignisse auf den Stack          */
/*-----------------------------------------------------------------*/
/*                                                                 */
/*  Eingabeparameter:                                              */
/*  Comp                      Status                               */
/*  Seiteneffekte:                                                 */
/*                                                                 */
/*  Lokale Variablen:                                              */
/*  i                         Event                                */
/*  hilf                      StateSet                             */
/*  PushSet                   EventMge                             */
/*  PushSet1                  EventMge                             */
/*******************************************************************/

#ifdef __STDC__
private void PushComp(Status Comp)
#else /* ! __STDC__ */
private void PushComp(Comp)
  Status Comp;
#endif /* ! __STDC__ */
{
  EventMge PushSet;
  StateSet hilf;

  PushSet=EmptyEventMge;
  /* Alle Mengen von Ereignissen, die zu einer Komponente gehoeren, werden
     iterativ vereinigt */
  for (hilf=MinParts[Comp];hilf;hilf=hilf->Nachfolger)
    AddEventMge(&PushSet,EventsPerState[hilf->State]);
  /* Die Ereignisse werden gepusht */
  DisposeEventMge(&MinimizerStack[Comp]);
  MinimizerStack[Comp]=PushSet;
  StackElemCount-=CompsOnStack[Comp];
  CompsOnStack[Comp]=CountEventMge(PushSet);
  StackElemCount+=CompsOnStack[Comp];
}




/*******************************************************************/
/*                                                                 */
/*  Prozedur: InitMinstack            Version:  25/05/91           */
/*                                                                 */
/*******************************************************************/
/*                                                                 */
/*  Klassifizierung:  Prozedur                                     */
/*                                                                 */
/*  Funktionsbeschreibung:                                         */
/*  Initialisiert den Stack mit Komponenten x benutzte Ereignisse  */
/*  Der Stack wird mit nil initialisiert                           */
/*-----------------------------------------------------------------*/
/*                                                                 */
/*  Eingabeparameter:                                              */
/*  UsedStates                StateSet                             */
/*  Seiteneffekte:                                                 */
/*                                                                 */
/*  Lokale Variablen:                                              */
/*  i                         Status                               */
/*  ImHs                      StateSet                             */
/*******************************************************************/

#ifdef __STDC__
private void InitMinstack(StateSet UsedStates)
#else /* ! __STDC__ */
private void InitMinstack(UsedStates)
  StateSet UsedStates;
#endif /* ! __STDC__ */
{
  Status   i;

  /* Je Komponente sind noch keine Komponenten auf dem Stack und der Stack
     jeder Komponente ist noch leer */
  for (i=1;i<=MaxState;MinimizerStack[i++]=NULL)
    CompsOnStack[i]=0;
  /* Fuer alle benutzten Zustaende wird berechnet (aus DeltaMinus),
     welche Ereignisse ueberhaupt ein Urbild ergeben */
  for (;UsedStates;UsedStates=UsedStates->Nachfolger)
    FindUsedEvents(UsedStates->State,&EventsPerState[UsedStates->State]);
  for (i=1;i<FirstFreePartition;PushComp(i++));
}




/*******************************************************************/
/*                                                                 */
/*  Prozedur: InitPartitions          Version:  25/05/91           */
/*                                                                 */
/*******************************************************************/
/*                                                                 */
/*  Klassifizierung:  Prozedur                                     */
/*                                                                 */
/*  Funktionsbeschreibung:                                         */
/*  Initialisierungsprozedur um das Array der Partionen            */
/*  zu initialisieren                                              */
/*-----------------------------------------------------------------*/
/*                                                                 */
/*  Eingabeparameter:                                              */
/*  inautomat                 Automat                              */
/*  Transientparameter:                                            */
/*  Partitions                Partition                            */
/*  Seiteneffekte:                                                 */
/*                                                                 */
/*  Lokale Variablen:                                              */
/*  StateCount                Status                               */
/*  ActionCount               Action                               */
/*  EndMenge                  StateSet                             */
/*  hilf                      StateSet                             */
/*  Verteilung                Partition                            */
/*******************************************************************/

#ifdef __STDC__
private void InitPartitions(StateSet *Partitions, Automat inautomat)
                       		/* Zeiger auf Partition */
                      
#else /* ! __STDC__ */
private void InitPartitions(Partitions,inautomat)
  StateSet *Partitions;		/* Zeiger auf Partition */
  Automat   inautomat;
#endif /* ! __STDC__ */
{
  Partition Verteilung;
  StateSet  EndMenge,hilf;
  Action    ActionCount;
  Status    StateCount;

  /* Bauernfeind: 16.09.93; Initialisierung von "Verteilung" */
  Verteilung = malloc((MaxState+1)*sizeof(StateSet));

  /* Setze alle Mengen in der Verteilung auf leer */
  for (ActionCount=0;ActionCount<=MaxAction;Verteilung[ActionCount++]=NULL);

  /* Setze die Mengen in der Patition auf leer und initialisiere
     die Maechtigkeit aller Mengen mit 0 */
  for (StateCount=0;StateCount<=MaxState;CompPow[StateCount++]=0)
    Partitions[StateCount]=NULL;

  CopyStateSet(inautomat->EndZustaende,&EndMenge);
  /* Die Partitionskomponente 1 erhaelt alle Zustaende ohne die Endzustaende */
  CopyStateSet(inautomat->BelegteZustaende,&Partitions[1]);
  MinusStateSet(&Partitions[1],inautomat->EndZustaende);
  CompPow[1]=CountStateSet(Partitions[1]);

  FirstFreePartition=2;
  /* Verteilen der Menge EndMenge nach zugeordneten Aktionen */
  while (EndMenge)
  {
    Verteilung[ActionTable[EndMenge->State]]=InsertState(EndMenge->State,Verteilung[ActionTable[EndMenge->State]]);
    hilf=EndMenge;
    EndMenge=EndMenge->Nachfolger;
    hilf->Nachfolger=EmptyStateSet;
    DisposeStateSet(&hilf);
  }

  /* Verteilung erhaelt jetzt zu jeder Aktion eine Menge von
     Endzustaenden. Diese Mengen werden als neue Komponenten
     in die anfaengliche Partition eingefuegt. */

  for (ActionCount=0;ActionCount<=MaxAction;ActionCount++)
    if (Verteilung[ActionCount])
    {
      Partitions[FirstFreePartition]=Verteilung[ActionCount];
      CompPow[FirstFreePartition++]=CountStateSet(Verteilung[ActionCount]);
    }
  /* Bauernfeind: 21.06.93; Freigabe des dyn. Speichers */
  free(Verteilung);
}




/*******************************************************************/
/*                                                                 */
/*  Prozedur: SetZugArray             Version:  25/05/91           */
/*                                                                 */
/*******************************************************************/
/*                                                                 */
/*  Klassifizierung:  Prozedur                                     */
/*                                                                 */
/*  Funktionsbeschreibung:                                         */
/*  Besetzt das Array der Zugehoerigkeiten, das fuer die Auswahl   */
/*  eines Repraesentanten jeder Zustandsmenge benoetigt wird       */
/*                                                                 */
/*-----------------------------------------------------------------*/
/*                                                                 */
/*  Eingabeparameter:                                              */
/*  Var                       ZugArray                             */
/*  Seiteneffekte:                                                 */
/*                                                                 */
/*  Lokale Variablen:                                              */
/*  PartitionCount            Status                               */
/*  StateCount                Status                               */
/*  hilf                      StateSet                             */
/*******************************************************************/

#ifdef __STDC__
private void SetZugArray(Status *Zugehoerig)
                     		/* ZugArray */
#else /* ! __STDC__ */
private void SetZugArray(Zugehoerig)
  Status *Zugehoerig;		/* ZugArray */
#endif /* ! __STDC__ */
{
  StateSet hilf;
  Status   PartitionCount,StateCount;

  for (StateCount=1;StateCount<=MaxState;Zugehoerig[StateCount++]=0);
  for (PartitionCount=1;PartitionCount<FirstFreePartition;PartitionCount++)
    for (hilf=MinParts[PartitionCount];hilf;hilf=hilf->Nachfolger)
      Zugehoerig[hilf->State]=MinParts[PartitionCount]->State;
}




/**********************************************************************
 * Statistische Information ueber den zu minimierenden Automaten      *
 **********************************************************************/
 
 
/*******************************************************************/
/*                                                                 */
/*  Prozedur: statistics              Version:  25/05/91           */
/*                                                                 */
/*******************************************************************/
/*                                                                 */
/*  Klassifizierung:  Prozedur                                     */
/*                                                                 */
/*  Funktionsbeschreibung:                                         */
/*  Ausgabe von statistischen Informationen ueber den zu minimie-  */
/*  renden Automaten                                               */
/*-----------------------------------------------------------------*/
/*                                                                 */
/*  Transientparameter:                                            */
/*  Automat                   Automatendescr                       */
/*  Seiteneffekte:                                                 */
/*                                                                 */
/*  Lokale Variablen:                                              */
/*  NumStates                 Status                               */
/*******************************************************************/

#ifdef __STDC__
public void statistics(Automat automat)
#else /* ! __STDC__ */
public void statistics(automat)
  Automat automat;
#endif /* ! __STDC__ */
{
  Status NumStates;

  NumStates=CountStateSet(automat->BelegteZustaende);
  printf("******* Minimierer: Statistische Information *******\nDer Automat hat %d Zustaende\nDie Ausgangspartition hat %d Elemente\nEs werden %d Ereignisse verwendet\n",NumStates,FirstFreePartition-1,NumberOfEvents);
}




/*******************************************************************/
/*                                                                 */
/*  Prozedur: Minimize                Version:  25/07/89A          */
/*                                                                 */
/*******************************************************************/
/*                                                                 */
/*  Klassifizierung:  Prozedur                                     */
/*                                                                 */
/*  Funktionsbeschreibung:                                         */
/*  Der oberste Automat wird minimiert. Falls der Automat nicht    */
/*  deterministisch war, kommt es zu Fehlern, da Minimize nur auf  */
/*  deterministischen Automaten korrekt arbeiten kann              */
/*                                                                 */
/*-----------------------------------------------------------------*/
/*                                                                 */
/*  Eingabeparameter:                                              */
/*  inautomat                 automat                              */
/*  Ausgabeparameter:                                              */
/*  outautomat                automat                              */
/*  Seiteneffekte:                                                 */
/*                                                                 */
/*-----------------------------------------------------------------*/
/*                                                                 */
/*  Lokale Typen:                                                  */
/*                                                                 */
/*  Lokale Variablen:                                              */
/*  Zerlegung                 Partition                            */
/*  Zugehoerig                ZugArray                             */
/*  Umkehr                    DeltaMinus                           */
/*  MinParts                  Partition                            */
/*  CompPow                   ElemCount                            */
/*  MinZugeh                  ZugArray                             */
/*  MinimizerStack            MinStack                             */
/*  EventsPerState            MinStack                             */
/*  MinAutomat                Automat                              */
/*  CompsOnStack              CompOnStackCount                     */
/*  StackElemCount            integer32                            */
/*  CompInArbeit              Status                               */
/*  EventInArbeit             Event                                */
/*  FirstFreePartition        Status                               */
/*  NumberOfEvents            integer32                            */
/*  GefUrbild                 StateSet                             */
/*  LoopBound                 Status                               */
/*  ComponentCount            Status                               */
/*  Schnitt                   StateSet                             */
/*  Rest                      StateSet                             */
/*  StateCount                Status                               */
/*  hilfK                     Kantenmenge                          */
/*  hilf                      StateSet                             */
/*  NewStates                 StateSet                             */
/*  NewEndStates              StateSet                             */
/*  IterationCount            integer32                            */
/*  TestChar                  Char                                 */
/*  StackCount                Integer                              */
/*  MinCompPow                Status                               */
/*  Lokale Prozeduren und Funktionen:                              */
/*             KillFang                                            */
/*                  IsFang                                         */
/*             DelBackEdgeSet                                      */
/*             DelDeltaMinus                                       */
/*             InsTransition                                       */
/*             BuildDeltaMinus                                     */
/*             FindUsedEvents                                      */
/*             FindStateUrbild                                     */
/*             FindUrbild                                          */
/*             showPartitions                                      */
/*             SetMinGetStackElem                                  */
/*             PushComp                                            */
/*             InitMinstack                                        */
/*             InitPartitions                                      */
/*             SetZugArray                                         */
/*             statistics                                          */
/*******************************************************************/

#ifdef __STDC__
public void Minimize(Automat inautomat, Automat *outautomat)
#else /* ! __STDC__ */
public void Minimize(inautomat,outautomat)
  Automat  inautomat;
  Automat *outautomat;
#endif /* ! __STDC__ */
{
/**********************************************************************
 * Prolog des Minimierers = Initialisierung der Datenstrukturen       *
 **********************************************************************/

/* Bauernfeind: 16.09.93; Initialisierung von MinimizerStack,EventsPerState */
/*                        Umkehr */
  static int firstcall = 1;
  static int oldMaxState;
  if (firstcall)   
  {  /* Initialisierung der Zeiger */
     firstcall = 0;
     oldMaxState = MaxState;
     MinimizerStack = malloc((MaxState+1)*sizeof(EventMge));
     EventsPerState = malloc((MaxState+1)*sizeof(EventMge));
     Umkehr = malloc((MaxState+1)*sizeof(BackEdgeSet));
     MinParts = malloc((MaxState+1)*sizeof(StateSet));
     MinZugeh = malloc((MaxState+1)*sizeof(Status));
     CompPow = malloc((MaxState+1)*sizeof(int));
     CompsOnStack = malloc((MaxState+1)*sizeof(int));
  }
  else if (oldMaxState != MaxState)
  {
    oldMaxState = MaxState;
    MinimizerStack = realloc(MinimizerStack, (MaxState+1)*sizeof(EventMge));
    EventsPerState = realloc(EventsPerState,(MaxState+1)*sizeof(EventMge));
    Umkehr = realloc(Umkehr,(MaxState+1)*sizeof(BackEdgeSet));
    MinParts = realloc(MinParts,(MaxState+1)*sizeof(StateSet));
    MinZugeh = realloc(MinZugeh,(MaxState+1)*sizeof(Status));
    CompPow = realloc(CompPow,(MaxState+1)*sizeof(int));
    CompsOnStack = realloc(CompsOnStack,(MaxState+1)*sizeof(int));
  }

  StackElemCount=0;		/* Der Stack ist leer */
  MinAutomat=inautomat;
  BuildDeltaMinus(MinAutomat);
  InitPartitions(MinParts,MinAutomat);
  InitMinstack(MinAutomat->BelegteZustaende);

/**********************************************************************
 * Rumpf des Minimierers = Schleife solange bis der Stack leer ist    *
 **********************************************************************/

  while (StackElemCount)
  {
    SetMinGetStackElem();
    FindUrbild(MinParts[CompInArbeit],EventInArbeit,&GefUrbild);
    if (GefUrbild)		/* Leere Urbilder bewirken keine Zerlegung */
    {
      LoopBound=FirstFreePartition-1;
      for (ComponentCount=1;ComponentCount<=LoopBound;ComponentCount++)
	if (CompPow[ComponentCount]>1)
	{
	  /* Mengen mit <= 1 Elementen koennen nicht zerlegt werden */
	  DivideStateSet(MinParts[ComponentCount],GefUrbild,&Schnitt,&Rest);
	  /* Wenn Schnitt oder Rest leer => Keine Zerlegung */
	  if (Schnitt && Rest)
	  {
	    /* Es erfolgt Zerlegung */
	    DisposeStateSet(&MinParts[ComponentCount]);
	    MinParts[ComponentCount]=Schnitt;
	    CompPow[ComponentCount]=CountStateSet(Schnitt);
	    MinParts[FirstFreePartition]=Rest;
	    CompPow[FirstFreePartition++]=CountStateSet(Rest);
	    /* Stack muss korigiert werden */
	    PushComp(ComponentCount);
	    PushComp(FirstFreePartition-1);
	  }
	  else			/* Die Komponente zerfiel nicht */
	  {
	    DisposeStateSet(&Schnitt);
	    DisposeStateSet(&Rest);
	  }
	}
    }
    DisposeStateSet(&GefUrbild);
  }

/**********************************************************************
 * Epilog des Minimierers = Auswahl der Repraesentanten und Korrektur *
 * der Automatentabelle                                               *
 * Loeschen der nicht mehr benoetigten Daten auf dem Heap             *
 **********************************************************************/

  /* In dem Array mit den Partitionen befinden sich jetzt die neuen
     Partitionskomponenten.
     Jetzt muss zu jeder Komponente das erste Element als Repraesentant
     gewaehlt werden. Die Tabelle Delta der Uebergaenge muss korrigiert
     werden, so dass alle Kanten auf einen Repraesentanten zeigen.

     Es wird also zunaechst das Array MinZugeh mit den Repraesentanten
     statt mit den Partitionskomponenten besetzt. */

  SetZugArray(MinZugeh);

  /* Jetzt wird die Tabelle Delta neu besetzt, und zwar fuer alle
     Repraesentanten von Partitionskomponenten. Dieser Algorithmus
     funktioniert, da der Automat ohnehin deterministisch ist und so nicht die
     Gefahr besteht, dass zwei aufeinanderfolgende KantenElemente ploetzlich
     identisch sind. */

  for (StateCount=1;StateCount<FirstFreePartition;StateCount++)
    for (hilfK=Delta[MinParts[StateCount]->State];hilfK;hilfK=hilfK->Nachfolger)
      hilfK->FolgeZustand=MinZugeh[hilfK->FolgeZustand];

  /* Es bleibt noch, die nicht mehr benoetigten Zustaende wieder freizugeben.
     Aufbau der Liste neuer Zustaende. */

  NewStates=EmptyStateSet;
  for (StateCount=1;StateCount<FirstFreePartition;NewStates=InsertState(MinParts[StateCount++]->State,NewStates));

  /* Loesche alle wegminimierten Zustaende: */

  StateCount=FirstFreePartition-1;
  MinusStateSet(&MinAutomat->BelegteZustaende,NewStates);
  while (MinAutomat->BelegteZustaende)
  {
    GiveAndDeleteState(&MinAutomat->BelegteZustaende,&StateCount);
    DspState(StateCount);
  }
  MinAutomat->BelegteZustaende=NewStates;

  /* Die Endzustaende muessen ebenfalls korrigiert werden: */

  NewEndStates=ClosureStateSet(MinAutomat->BelegteZustaende,MinAutomat->EndZustaende);
  DisposeStateSet(&MinAutomat->EndZustaende);
  MinAutomat->EndZustaende=NewEndStates;

  /* Anfangszustand gegebenenfalls neu benennen */

  MinAutomat->StartZustand=MinZugeh[MinAutomat->StartZustand];

  /* Loeschen der Umkehrfunktion */

  DelDeltaMinus(MinAutomat);

  Push(MinAutomat);
  KillFang();
  MinAutomat=Pop();
  *outautomat=MinAutomat;
}
 



/*******************************************************************/
/*                                                                 */
/*  Prozedur: initminimier            Version:  25/05/91           */
/*                                                                 */
/*******************************************************************/
/*                                                                 */
/*  Klassifizierung:  Prozedur                                     */
/*                                                                 */
/*  Funktionsbeschreibung:                                         */
/*  Dummy, evtl fuer Ausgabe der Versionskennung                   */
/*-----------------------------------------------------------------*/
/*                                                                 */
/*  Seiteneffekte:                                                 */
/*                                                                 */
/*******************************************************************/

#ifdef __STDC__
public void initminimier(void)
#else /* ! __STDC__ */
public void initminimier()
#endif /* ! __STDC__ */
{}
