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
/*  Segment: autops.c                                              */
/*  Version: 20/05/91                                              */
/*                                                                 */
/*  Sprache: C                                                     */
/*                                                                 */
/*-----------------------------------------------------------------*/
/*                                                                 */
/*  Beschreibung:                                                  */
/*  Diese Unit enthaelt alle Operationen, die als interne          */
/*  Operationen fuer AutStack benoetigt werden. AutStack enthaelt  */
/*  nur die weitergegebenen Operationen. Teilung wurde durch       */
/*  64K-Sourcegrenze bei Turbo-Pascal erforderlich. Die geschach-  */
/*  telten Prozeduren, z.B. eigene fuer Myhill oder Minimierer     */
/*  wurden nicht ausgelagert                                       */
/*                                                                 */
/*  Inhalt:                                                        */
/*        CountFKanten                                             */
/*        newKante                                                 */
/*        DispKante                                                */
/*        DisposeKantenMenge                                       */
/*        CountFKanten                                             */
/*        NewState                                                 */
/*        DspState                                                 */
/*        MakeEndzustand                                           */
/*        IstEndzustand                                            */
/*        NewAutomaton                                             */
/*        UnionAutomatons                                          */
/*        InsertKante                                              */
/*        InsertEpsilonKante                                       */
/*        InsertTKante                                             */
/*        MakeKantenMenge                                          */
/*        MakeCompleteKanten                                       */
/*             (ordnum wird in der C-Fassung nicht mehr benoetigt) */
/*        DeleteFangKanten                                         */
/*        ExistsEvent                                              */
/*        InitAutops                                               */
/*        MyPurgeHeap                                              */
/*                                                                 */
/*-----------------------------------------------------------------*/
/*                                                                 */
/*                 M O D I F I K A T I O N E N                     */
/*=================================================================*/
/* Datum      modifiziert von    Beschreibung der Modifikation     */
/*=================================================================*/
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
#include "stateset.h"
#include "autstack.h"
#include "error.h"
#define EXTERN 
#include "autops.h"

/* Bauernfeind: 17.06.93; Globale Variablen aus var.c */
extern int MaxState;
extern int MaxAction;
extern int MAX_ID_NO;
extern MakroTable MakTable;

extern void *realloc();


/* Interne Funktionsdeklarationen */

private void NewKante P_((KantenMenge *NkKante));
private void DispKante P_((KantenMenge *DkKante));
private void DisposeKantenMenge P_((KantenMenge *DkMenge));
private int CountFKanten P_((void));
#ifdef __STDC__
private void MakeKantenMenge P_((Event from, Event toEvent, 
                                 Status toState, KantenMenge *pbegin, 
                                 KantenMenge *pend));
#else /* ! __STDC__ */
private void MakeKantenMenge P_((int from, int toEvent, Status toState, KantenMenge *pbegin, KantenMenge *pend));
#endif /* ! __STDC__ */


private KantenMenge FreeKtList;
private Status      FirstFreeState;
private StateSet    FreeStateSet;

/* Diese Liste enthaelt alle Elemente, die bereits einmal vom
   Laufzeitsystem angefordert worden sind, aber z.Zt. wieder frei
   sind. Ein Aufruf von newKante nimmt moeglichst ein Element aus
   dieser Liste. Nur wenn die Liste leer ist, wird ein Element vom
   Heap-Manager angefordert. DispKante und DisposeKantenMenge
   fuehren auf den Mengen keine Dispose aus, sondern tragen
   die Elemente nur in diese Liste ein. */

/*******************************************************************/
/*                                                                 */
/*  Prozedur: newKante                Version:  20/05/91           */
/*                                                                 */
/*******************************************************************/
/*                                                                 */
/*  Klassifizierung:  Prozedur                                     */
/*                                                                 */
/*  Funktionsbeschreibung:                                         */
/*  Ersetzt den Aufruf von New(PointerVar)                         */
/*-----------------------------------------------------------------*/
/*                                                                 */
/*  Transientparameter:                                            */
/*  NkKante                   KantenMenge                          */
/*  Seiteneffekte:                                                 */
/*                                                                 */
/*******************************************************************/

#ifdef __STDC__
private void NewKante(KantenMenge *NkKante)
#else /* ! __STDC__ */
private void NewKante(NkKante)
  KantenMenge *NkKante;
#endif /* ! __STDC__ */
{
  if (FreeKtList==NULL)
    *NkKante=malloc(sizeof(struct KantenEl));
  else
  {
    *NkKante=FreeKtList;
    FreeKtList=FreeKtList->Nachfolger;
  }
}




/*******************************************************************/
/*                                                                 */
/*  Prozedur: DispKante               Version:  20/05/91           */
/*                                                                 */
/*******************************************************************/
/*                                                                 */
/*  Klassifizierung:  Prozedur                                     */
/*                                                                 */
/*  Funktionsbeschreibung:                                         */
/*  Ersetzt den Aufruf von free(PointerVar)                     */
/*-----------------------------------------------------------------*/
/*                                                                 */
/*  Transientparameter:                                            */
/*  DkKante                   KantenMenge                          */
/*  Seiteneffekte:                                                 */
/*                                                                 */
/*******************************************************************/

#ifdef __STDC__
private void DispKante(KantenMenge *DkKante)
#else /* ! __STDC__ */
private void DispKante(DkKante)
  KantenMenge *DkKante;
#endif /* ! __STDC__ */
{
  (*DkKante)->Nachfolger=FreeKtList;
  FreeKtList = *DkKante;
  *DkKante=NULL;
}




/*******************************************************************/
/*                                                                 */
/*  Prozedur: DisposeKantenMenge      Version:  20/05/91           */
/*                                                                 */
/*******************************************************************/
/*                                                                 */
/*  Klassifizierung:  Prozedur                                     */
/*                                                                 */
/*  Funktionsbeschreibung:                                         */
/*  Loescht eine Menge von Kanten                                  */
/*-----------------------------------------------------------------*/
/*                                                                 */
/*  Transientparameter:                                            */
/*  DkMenge                   KantenMenge                          */
/*  Seiteneffekte:                                                 */
/*                                                                 */
/*  Lokale Variablen:                                              */
/*  DkHk                      KantenMenge                          */
/*******************************************************************/

#ifdef __STDC__
private void DisposeKantenMenge(KantenMenge *DkMenge)
#else /* ! __STDC__ */
private void DisposeKantenMenge(DkMenge)
  KantenMenge *DkMenge;
#endif /* ! __STDC__ */
{
  KantenMenge DkHk;

  if (*DkMenge!=NULL)
  {
    DkHk = *DkMenge;
    while (DkHk->Nachfolger!=NULL)
      DkHk=DkHk->Nachfolger;
    DkHk->Nachfolger=FreeKtList;
    FreeKtList = *DkMenge;
    *DkMenge=NULL;
  }
}




/*******************************************************************/
/*                                                                 */
/*  Prozedur: CountFKanten            Version:  20/05/91           */
/*                                                                 */
/*******************************************************************/
/*                                                                 */
/*  Klassifizierung:  Funktion                                     */
/*                                                                 */
/*  Funktionsbeschreibung:                                         */
/*  Siehe open                                                     */
/*-----------------------------------------------------------------*/
/*                                                                 */
/*  Ausgabeparameter:                                              */
/*  CountFKanten              Integer                              */
/*  Seiteneffekte:                                                 */
/*                                                                 */
/*******************************************************************/

#ifdef __STDC__
private int CountFKanten(void)
#else /* ! __STDC__ */
private int CountFKanten()
#endif /* ! __STDC__ */
{
  KantenMenge CfKs,CfKd;
  int Erg;

  CfKs=FreeKtList;
  Erg=0;
  while (CfKs!=NULL)
  {
    Erg++;
    CfKd=CfKs;
    CfKs=CfKs->Nachfolger;
    free(CfKd);
  }
  FreeKtList=NULL;
  return(Erg);
}




/*******************************************************************/
/*                                                                 */
/*  Prozedur: NewState                Version:  20/05/91           */
/*                                                                 */
/*******************************************************************/
/*                                                                 */
/*  Klassifizierung:  Funktion                                     */
/*                                                                 */
/*  Funktionsbeschreibung:                                         */
/*  Diese Funktion findet einen neuen Zustand in der Uebergangs-   */
/*  tabelle, markiert ihn als belegt und traegt ihn in die Liste   */
/*  der von NsAutomat belegten Zustaende ein. Die Uebergaenge des  */
/*  Zustandes werden leer vorbesetzt, also geht der Zustand mit    */
/*  allen Ereignissen auf den Fangzustand                          */
/*                                                                 */
/*-----------------------------------------------------------------*/
/*                                                                 */
/*  Eingabeparameter:                                              */
/*  NsAutomat                 Automat                              */
/*  Ausgabeparameter:                                              */
/*  NewState                  Status                               */
/*  Seiteneffekte:                                                 */
/*                                                                 */
/*  Lokale Variablen:                                              */
/*  NsErg                     Status                               */
/*  NsStateEl                 StateSet                             */
/*******************************************************************/

#ifdef __STDC__
public Status NewState(Automat NsAutomat)
#else /* ! __STDC__ */
public Status NewState(NsAutomat)
  Automat NsAutomat;
#endif /* ! __STDC__ */
{
  Status   NsErg;

  if (EmptyStateSet!=FreeStateSet)
    GiveAndDeleteState(&FreeStateSet,&NsErg);
  else
  {
    if (FirstFreeState>=MaxState)
    {
      /* Bauernfeind: 16.06.93; Vergroessern der globalen Variablen */
      /* FatalError(3); */
      MaxState = 2*MaxState;
      Delta = realloc(Delta,(MaxState+1)*sizeof(KantenMenge));
      ActionTable = realloc(ActionTable,(MaxState+1)*sizeof(Action));
    }
    NsErg=FirstFreeState++;
  }
  NsAutomat->BelegteZustaende=InsertState(NsErg,NsAutomat->BelegteZustaende);
  Delta[NsErg]=NULL;
  ActionTable[NsErg]=NoAction;
  return(NsErg);
}




/*******************************************************************/
/*                                                                 */
/*  Prozedur: DspState                Version:  20/05/91           */
/*                                                                 */
/*******************************************************************/
/*                                                                 */
/*  Klassifizierung:  Prozedur                                     */
/*                                                                 */
/*  Funktionsbeschreibung:                                         */
/*  Diese Prozedure traegt einen Zustand in die Liste der freien   */
/*  Zustaende ein, nachdem sie saemtliche Kanten dieses Zustandes  */
/*  freigegeben hat. Der Zustand steht dann fuer eine neue Vergabe */
/*  frei. Solange er nicht neu belegt wurde ist sein Inhalt        */
/*  undefiniert.                                                   */
/*                                                                 */
/*-----------------------------------------------------------------*/
/*                                                                 */
/*  Eingabeparameter:                                              */
/*  DsState                   Status                               */
/*  Seiteneffekte:                                                 */
/*                                                                 */
/*******************************************************************/

#ifdef __STDC__
public void DspState(Status DsState)
#else /* ! __STDC__ */
public void DspState(DsState)
  Status DsState;
#endif /* ! __STDC__ */
{
  DisposeKantenMenge(&Delta[DsState]);
  FreeStateSet=InsertState(DsState,FreeStateSet);
}




/*******************************************************************/
/*                                                                 */
/*  Prozedur: MakeEndzustand          Version:  20/05/91           */
/*                                                                 */
/*******************************************************************/
/*                                                                 */
/*  Klassifizierung:  Prozedur                                     */
/*                                                                 */
/*  Funktionsbeschreibung:                                         */
/*  Diese Funktion fuegt den Zustand MeState in die Liste der      */
/*  Endzustaende des Automaten MeAutomat ein.                      */
/*                                                                 */
/*-----------------------------------------------------------------*/
/*                                                                 */
/*  Eingabeparameter:                                              */
/*  MeState                   Status                               */
/*  MeAutomat                 Automat                              */
/*  Seiteneffekte:                                                 */
/*                                                                 */
/*******************************************************************/

#ifdef __STDC__
public void MakeEndzustand(Status MeState, Automat MeAutomat)
#else /* ! __STDC__ */
public void MakeEndzustand(MeState,MeAutomat)
  Status  MeState;
  Automat MeAutomat;
#endif /* ! __STDC__ */
{
  MeAutomat->EndZustaende=InsertState(MeState,MeAutomat->EndZustaende);
}




/*******************************************************************/
/*                                                                 */
/*  Prozedur: IstEndzustand           Version:  20/05/91           */
/*                                                                 */
/*******************************************************************/
/*                                                                 */
/*  Klassifizierung:  Funktion                                     */
/*                                                                 */
/*  Funktionsbeschreibung:                                         */
/*  Diese Funktion stellt fest, ob der Zustand IeState ein         */
/*  Endzustand des Automaten IeAutomat ist und gibt in diesem      */
/*  Falle true zurueck, sonst false.                               */
/*                                                                 */
/*-----------------------------------------------------------------*/
/*                                                                 */
/*  Eingabeparameter:                                              */
/*  IeState                   Status                               */
/*  IeAutomat                 Automat                              */
/*  Ausgabeparameter:                                              */
/*  IstEndzustand             boolean                              */
/*  Seiteneffekte:                                                 */
/*                                                                 */
/*  Lokale Variablen:                                              */
/*  IeHs                      StateSet                             */
/*******************************************************************/

#ifdef __STDC__
public int IstEndzustand(Status IeState, Automat IeAutomat)
#else /* ! __STDC__ */
public int IstEndzustand(IeState,IeAutomat)
  Status  IeState;
  Automat IeAutomat;
#endif /* ! __STDC__ */
{
  return(IsElement(IeState,IeAutomat->EndZustaende));
}




/*******************************************************************/
/*                                                                 */
/*  Prozedur: NewAutomaton            Version:  20/05/91           */
/*                                                                 */
/*******************************************************************/
/*                                                                 */
/*  Klassifizierung:  Funktion                                     */
/*                                                                 */
/*  Funktionsbeschreibung:                                         */
/*  Diese Funktion erzeugt einen neuen Automaten und initialisiert */
/*  ihn mit dem Startzustand. Die Endzustandsmenge ist leer. Der   */
/*  Startzustand erhaelt keine Kante, geht also mit allen          */
/*  Ereignissen auf den Fangzustand ueber.                         */
/*                                                                 */
/*-----------------------------------------------------------------*/
/*                                                                 */
/*  Ausgabeparameter:                                              */
/*  NewAutomaton              Automat                              */
/*  Seiteneffekte:                                                 */
/*                                                                 */
/*  Lokale Variablen:                                              */
/*  NaAutomat                 Automat                              */
/*******************************************************************/

#ifdef __STDC__
public Automat NewAutomaton(void)
#else /* ! __STDC__ */
public Automat NewAutomaton()
#endif /* ! __STDC__ */
{
  Automat NaAutomat;

  NaAutomat=malloc(sizeof(struct AutomatenDescr));
  NaAutomat->BelegteZustaende=EmptyStateSet;
  NaAutomat->EndZustaende=EmptyStateSet;
  NaAutomat->StartZustand=NewState(NaAutomat);
  return(NaAutomat);
}




/*******************************************************************/
/*                                                                 */
/*  Prozedur: UnionAutomatons         Version:  20/05/91           */
/*                                                                 */
/*******************************************************************/
/*                                                                 */
/*  Klassifizierung:  Prozedur                                     */
/*                                                                 */
/*  Funktionsbeschreibung:                                         */
/*  Diese Prozedur wird allen Operationen nachgeschaltet, die zwei */
/*  Automaten miteinander verknuepfen. Sie erfuellt zwei Funktionen*/
/*  1. Die Mengen der belegten Zustaende der Automaten UaAutomat1, */
/*     UaAutomat2 und UaDestAutomat werden vereinigt und bei       */
/*     BelegteZustaende von UaDestAutomat eingetragen.             */
/*  2. Die Deskriptoren der Automaten UaAutomat1 und UaAutomat2    */
/*     werden freigegeben.                                         */
/*                                                                 */
/*-----------------------------------------------------------------*/
/*                                                                 */
/*  Eingabeparameter:                                              */
/*  UaAutomat1                Automat                              */
/*  UaAutomat2                Automat                              */
/*  Transientparameter:                                            */
/*  UaDestAutomat             Automat                              */
/*  Seiteneffekte:                                                 */
/*                                                                 */
/*******************************************************************/

#ifdef __STDC__
public void UnionAutomatons(Automat UaAutomat1,
                            Automat UaAutomat2,
                            Automat *UaDestAutomat)
#else /* ! __STDC__ */
public void UnionAutomatons(UaAutomat1,UaAutomat2,UaDestAutomat)
  Automat UaAutomat1,UaAutomat2;
  Automat *UaDestAutomat;
#endif /* ! __STDC__ */
{
  /* 1 */
  (*UaDestAutomat)->BelegteZustaende=UnionStateSet(UnionStateSet((*UaDestAutomat)->BelegteZustaende,UaAutomat1->BelegteZustaende),UaAutomat2->BelegteZustaende);
  /* 2 */
  free(UaAutomat1);
  free(UaAutomat2);
}




/*******************************************************************/
/*                                                                 */
/*  Prozedur: InsertKante             Version:  20/05/91           */
/*                                                                 */
/*******************************************************************/
/*                                                                 */
/*  Klassifizierung:  Prozedur                                     */
/*                                                                 */
/*  Funktionsbeschreibung:                                         */
/*  Diese Prozedur fuegt eine Kante, die mit IkEvent und           */
/*  IkFolgezustand spezifiziert wird, in die Uebergangsmenge zu    */
/*  dem State IkStaus ein. Ist zu diesem Ereignis bereits ein      */
/*  Uebergang vorhanden, der auf einen anderen Folgezustand weist, */
/*  so wird der Automat nichtdeterministisch.                      */
/*                                                                 */
/*-----------------------------------------------------------------*/
/*                                                                 */
/*  Eingabeparameter:                                              */
/*  IkEvent                   Event                                */
/*  IkFolgezustand            Status                               */
/*  IkState                   Status                               */
/*  IkAutomat                 Automat                              */
/*  Seiteneffekte:                                                 */
/*                                                                 */
/*  Lokale Variablen:                                              */
/*  IkHs                      KantenMenge                          */
/*  IkHs1                     KantenMenge                          */
/*  IkHk                      KantenMenge                          */
/*  IkHsm                     KantenMenge                          */
/*******************************************************************/

#ifdef __STDC__
public void InsertKante(Event IkEvent,
                        Status IkFolgezustand,
                        Status IkState,
                        Automat IkAutomat)
#else /* ! __STDC__ */
public void InsertKante(IkEvent,IkFolgezustand,IkState,IkAutomat)
  Event   IkEvent;
  Status  IkFolgezustand,IkState;
  Automat IkAutomat;
#endif /* ! __STDC__ */
{
  KantenMenge IkHs,IkHs1;

  if (Delta[IkState]==NULL)
  {
    NewKante(&Delta[IkState]);
    Delta[IkState]->Ereignis=IkEvent;
    Delta[IkState]->FolgeZustand=IkFolgezustand;
    Delta[IkState]->Nachfolger=NULL;
  }
  else
  {
    IkHs=Delta[IkState];
    while (IkHs->Nachfolger!=NULL && (IkHs->Ereignis<IkEvent || (IkHs->Ereignis==IkEvent && IkHs->FolgeZustand<IkFolgezustand)))
      IkHs=IkHs->Nachfolger;
    if (IkHs->Ereignis>IkEvent || (IkHs->Ereignis==IkEvent && IkHs->FolgeZustand>IkFolgezustand))
    {
      NewKante(&IkHs1);

      /* IkHs1^ := IkHs^; ins folgende uebersetzt : */
  /*  IkHs1->Ereignis=IkHs->Ereignis;
      IkHs1->FolgeZustand=IkHs->FolgeZustand;
      IkHs1->Nachfolger=IkHs->Nachfolger; */
      *IkHs1 = *IkHs;

      IkHs->Ereignis=IkEvent;
      IkHs->FolgeZustand=IkFolgezustand;
      IkHs->Nachfolger=IkHs1;
    }
    else
    {
      if (IkHs->Ereignis<IkEvent || (IkHs->Ereignis==IkEvent && IkHs->FolgeZustand<IkFolgezustand))
      {
        NewKante(&IkHs1);
        IkHs1->Ereignis=IkEvent;
        IkHs1->FolgeZustand=IkFolgezustand;
        IkHs1->Nachfolger=NULL;
        IkHs->Nachfolger=IkHs1;
      }
    }
  }
}




/*******************************************************************/
/*                                                                 */
/*  Prozedur: InsertEpsilonKante      Version:  20/05/91           */
/*                                                                 */
/*******************************************************************/
/*                                                                 */
/*  Klassifizierung:  Prozedur                                     */
/*                                                                 */
/*  Funktionsbeschreibung:                                         */
/*  Diese Routine beseitigt Epsilon-Kanten, indem sie beim         */
/*  Auftreten einer Epsilon-Kante die Zustandsuebergangsfunktion   */
/*  des Quellzustandes mit der des Folgezustandes verschmelzen.    */
/*  ist der Folgezustand ein Endzustand, so wird der Quellzustand  */
/*  ebenfalls in die Liste der Endzustaende eingetragen, als       */
/*  Aktion wird die kleinst Aktion, die nicht Null ist,            */
/*  eingetragen. Durch die Elemination von Epsilon-Kanten koennen  */
/*  sowohl Nichtdeterminismen als auch unerreichbare Zustaende     */
/*  auftreten.                                                     */
/*                                                                 */
/*-----------------------------------------------------------------*/
/*                                                                 */
/*  Eingabeparameter:                                              */
/*  IkFolgezustand            Status                               */
/*  IkState                   Status                               */
/*  IkAutomat                 Automat                              */
/*  Seiteneffekte:                                                 */
/*                                                                 */
/*  Lokale Variablen:                                              */
/*  IkHs                      KantenMenge                          */
/*  IkHs1                     KantenMenge                          */
/*  IkHk                      KantenMenge                          */
/*  IkHsm                     KantenMenge                          */
/*******************************************************************/

#ifdef __STDC__
public void InsertEpsilonKante(Status IkFolgezustand,
                               Status IkState,
                               Automat IkAutomat)
#else /* ! __STDC__ */
public void InsertEpsilonKante(IkFolgezustand,IkState,IkAutomat)
  Status  IkFolgezustand,IkState;
  Automat IkAutomat;
#endif /* ! __STDC__ */
{
  KantenMenge IkHk;

  /* Es liegt eine Epsilon-Kante vor, die eleminiert werden muss */
  if (IkFolgezustand!=IkState)
  {
    /* Schleifen von Epsilon-Kanten werden ignoriert */
    IkHk=Delta[IkFolgezustand];
    while (IkHk!=NULL)
    {
      InsertKante(IkHk->Ereignis,IkHk->FolgeZustand,IkState,IkAutomat);
      IkHk=IkHk->Nachfolger;
    }
    if (IstEndzustand(IkFolgezustand,IkAutomat))
    {
      MakeEndzustand(IkState,IkAutomat);
      if ((ActionTable[IkFolgezustand]!=NoAction && ActionTable[IkFolgezustand]<ActionTable[IkState]) || ActionTable[IkState]==NoAction)
        ActionTable[IkState]=ActionTable[IkFolgezustand];
      else
        ActionTable[IkFolgezustand]=ActionTable[IkState];
    }
  }
}




/*******************************************************************/
/*                                                                 */
/*  Prozedur: InsertTKante            Version:  20/05/91           */
/*                                                                 */
/*******************************************************************/
/*                                                                 */
/*  Klassifizierung:  Prozedur                                     */
/*                                                                 */
/*  Funktionsbeschreibung:                                         */
/*  fuegt von Kante von nach Kante nach fuer jedes Zeichen         */
/*  (0 .. 255) eine Kante ein. Voraussetzung: Kantenmenge bei von  */
/*  muss noch leer sein                                            */
/*                                                                 */
/*-----------------------------------------------------------------*/
/*                                                                 */
/*  Eingabeparameter:                                              */
/*  von                       Status                               */
/*  nach                      Status                               */
/*  Seiteneffekte:                                                 */
/*                                                                 */
/*  Lokale Variablen:                                              */
/*  i                         Event                                */
/*  Ende                      KantenMenge                          */
/*******************************************************************/

#ifdef __STDC__
public void InsertTKante(Status von, Status nach)
#else /* ! __STDC__ */
public void InsertTKante(von,nach)
  Status von,nach;
#endif /* ! __STDC__ */
{
  int         i;
  KantenMenge Ende;

  if (Delta[von]!=NULL)
    SoftwareError(8);
  else
  {
    NewKante(&Delta[von]);
    Delta[von]->Ereignis=0;
    Delta[von]->FolgeZustand=nach;
    Delta[von]->Nachfolger=NULL;
    Ende=Delta[von];
    for (i=1;i<=MaxEvent;i++)
      if (!(flags[ignorecase] && ('A'<=i && i<='Z')))  /* EBCDIC */
      {
        NewKante(&Ende->Nachfolger);
        Ende=Ende->Nachfolger;
        Ende->Ereignis=i;
        Ende->FolgeZustand=nach;
        Ende->Nachfolger=NULL;
      }
  }
}




/*******************************************************************/
/*                                                                 */
/*  Prozedur: MakeKantenMenge         Version:  20/05/91           */
/*                                                                 */
/*******************************************************************/
/*                                                                 */
/*  Klassifizierung:  Prozedur                                     */
/*                                                                 */
/*  Funktionsbeschreibung:                                         */
/*  Erzeugt eine Menge von Kanten mit den Ereignissen from bis     */
/*  toEvent und liefert den pointer auf die erste und letzte Kante */
/*  der Menge                                                      */
/*                                                                 */
/*-----------------------------------------------------------------*/
/*                                                                 */
/*  Eingabeparameter:                                              */
/*  from                      Event                                */
/*  toEvent                   Event                                */
/*  tostate                   Status                               */
/*  Transientparameter:                                            */
/*  pbegin                    KantenMenge                          */
/*  pend                      KantenMenge                          */
/*  Seiteneffekte:                                                 */
/*                                                                 */
/*  Lokale Variablen:                                              */
/*  i                         Event                                */
/*******************************************************************/

#ifdef __STDC__
private void MakeKantenMenge(Event from,
                             Event toEvent,
                             Status toState,
                             KantenMenge *pbegin,
                             KantenMenge *pend)
#else /* ! __STDC__ */
private void MakeKantenMenge(from,toEvent,toState,pbegin,pend)
  Event       from,toEvent;
  Status      toState;
  KantenMenge *pbegin,*pend;
#endif /* ! __STDC__ */
{
  int i;

  if (from>toEvent)
    SoftwareError(14);
  NewKante(pbegin);
  (*pbegin)->Ereignis=from;
  (*pbegin)->FolgeZustand=toState;
  (*pbegin)->Nachfolger=NULL;
  *pend = *pbegin;
  if (from<toEvent)
  {
    for (i = ++from;i<=(int)toEvent;i++)
     if (!(flags[ignorecase] && ('A'<=i && i<='Z')))   /* EBCDIC */
     {
       NewKante(&(*pend)->Nachfolger);
       *pend=(*pend)->Nachfolger;
       (*pend)->FolgeZustand=toState;
       (*pend)->Ereignis=i;
       (*pend)->Nachfolger=NULL;
     }
  }
}




/*******************************************************************/
/*                                                                 */
/*  Prozedur: MakeCompleteKanten      Version:  20/05/91           */
/*                                                                 */
/*******************************************************************/
/*                                                                 */
/*  Klassifizierung:  Prozedur                                     */
/*                                                                 */
/*  Funktionsbeschreibung:                                         */
/*  Macht eine Menge von Kanten vollstaendig, in dem in die Menge  */
/*  von fuer jedes t aus T eine Kante auf nach eingefuegt wird,    */
/*  sofern noch keine Kante vorhanden ist                          */
/*                                                                 */
/*-----------------------------------------------------------------*/
/*                                                                 */
/*  Eingabeparameter:                                              */
/*  von                       Status                               */
/*  nach                      Status                               */
/*  Seiteneffekte:                                                 */
/*                                                                 */
/*  Lokale Variablen:                                              */
/*  hilf                      Kantenmenge                          */
/*  ende                      Kantenmenge                          */
/*  merke                     Kantenmenge                          */
/*  i                         Event                                */
/*  ug                        Event                                */
/*  og                        Event                                */
/*  Lokale Prozeduren und Funktionen:                              */
/*             (ordnum nun direkt implementiert)                   */
/*******************************************************************/

#ifdef __STDC__
public void MakeCompleteKanten(Status von, Status nach)
#else /* ! __STDC__ */
public void MakeCompleteKanten(von,nach)
  Status von,nach;
#endif /* ! __STDC__ */
{
  KantenMenge hilf,ende,merke;
  Event       ug,og;
  int         i;

  if (Delta[von]==NULL)
    InsertTKante(von,nach);
  else
  {
    if (Delta[von]->Ereignis>0)
    {
      /* vorne auffuellen */
      MakeKantenMenge(0,Delta[von]->Ereignis-1,nach,&merke,&hilf);
      hilf->Nachfolger=Delta[von];
      Delta[von]=merke;
    }
    else
      hilf=Delta[von];
    while (hilf->Nachfolger!=NULL)
    {
      if ((int)hilf->Ereignis+1 < (int)(hilf->Nachfolger)->Ereignis)
      {
        /* es muessen Kanten zwischengebaut werden */
        ug=hilf->Ereignis+1;
        og=(hilf->Nachfolger)->Ereignis-1;
        merke=hilf->Nachfolger;
        ende=hilf;
        for (i=ug;i<=(int)og;i++)
	  if (!(flags[ignorecase] && ('A'<=i && i<='Z'))) /* EBCDIC */
	  {
            NewKante(&ende->Nachfolger);
            ende=ende->Nachfolger;
            ende->Ereignis=i;
            ende->FolgeZustand=nach;
            ende->Nachfolger=NULL;
	  }
        ende->Nachfolger=merke;
        hilf=merke;
      }
      else
        hilf=hilf->Nachfolger;
    }
    /* Jetzt schauen, ob schon am Ende angelangt */
    i=hilf->Ereignis;
    if (i<MaxEvent)
    {
      ug=hilf->Ereignis+1;
      og=MaxEvent;
      ende=hilf;
      for (i=ug;i<=(int)og;i++)
        if (!(flags[ignorecase] && ('A'<=i && i<='Z')))  /* EBCDIC */
	{
          NewKante(&ende->Nachfolger);
          ende=ende->Nachfolger;
          ende->Ereignis=i;
          ende->FolgeZustand=nach;
          ende->Nachfolger=NULL;
	}
    }
  }
}




/*******************************************************************/
/*                                                                 */
/*  Prozedur: DeleteFangKanten        Version:  20/05/91           */
/*                                                                 */
/*******************************************************************/
/*                                                                 */
/*  Klassifizierung:  Prozedur                                     */
/*                                                                 */
/*  Funktionsbeschreibung:                                         */
/*  Loescht alle Kanten, die auf den Zustand fang fuehren aus der  */
/*  Kantenmenge von LoescheIn                                      */
/*                                                                 */
/*-----------------------------------------------------------------*/
/*                                                                 */
/*  Eingabeparameter:                                              */
/*  LoescheIn                 Status                               */
/*  fang                      Status                               */
/*  Seiteneffekte:                                                 */
/*                                                                 */
/*  Lokale Variablen:                                              */
/*  hilf                      KantenMenge                          */
/*  schlepp                   KantenMenge                          */
/*******************************************************************/

#ifdef __STDC__
public void DeleteFangKanten(Status LoescheIn, Status fang)
#else /* ! __STDC__ */
public void DeleteFangKanten(LoescheIn,fang)
  Status LoescheIn,fang;
#endif /* ! __STDC__ */
{
  KantenMenge hilf,schlepp;

  if (Delta[LoescheIn]!=NULL)
  {
    schlepp=Delta[LoescheIn]; 
    hilf=schlepp->Nachfolger;
    do
    {
      if (hilf!=NULL)
      {
        if (hilf->FolgeZustand==fang)
	{
          /* Loeschen der Kante, auf die Hilf zeigt */
          schlepp->Nachfolger=hilf->Nachfolger;
          DispKante(&hilf);
          hilf=schlepp->Nachfolger;
	}
        else
	{
          schlepp=hilf;
          hilf=hilf->Nachfolger;
	}
      }
    } while (hilf!=NULL);
    /* Jetzt sind alle Elemente geloescht, die auf fang
       fuehren. Lediglich das erste ist noch nicht geprueft */
    if (Delta[LoescheIn]!=NULL && Delta[LoescheIn]->FolgeZustand==fang)
    {
      hilf=Delta[LoescheIn];
      Delta[LoescheIn]=Delta[LoescheIn]->Nachfolger;
      DispKante(&hilf);
    }
  }
}




/*******************************************************************/
/*                                                                 */
/*  Prozedur: ExistsEvent             Version:  20/05/91           */
/*                                                                 */
/*******************************************************************/
/*                                                                 */
/*  Klassifizierung:  Funktion                                     */
/*                                                                 */
/*  Funktionsbeschreibung:                                         */
/*  Prueft, ob zu einem Paar aus Zustand x Ereignis irgendeine     */
/*  Kante existiert                                                */
/*                                                                 */
/*-----------------------------------------------------------------*/
/*                                                                 */
/*  Eingabeparameter:                                              */
/*  EEState                   Status                               */
/*  EEEvent                   Event                                */
/*  Ausgabeparameter:                                              */
/*  ExistsEvent               var                                  */
/*  Seiteneffekte:                                                 */
/*                                                                 */
/*******************************************************************/

#ifdef __STDC__
public int ExistsEvent(Status EEState, Event EEEvent)
#else /* ! __STDC__ */
public int ExistsEvent(EEState,EEEvent)
  Status EEState;
  Event  EEEvent;
#endif /* ! __STDC__ */
{
  KantenMenge hilf;
  int         Erg;

  Erg=0;
  hilf=Delta[EEState];
  if (hilf!=NULL)
  {
    while (!(hilf==NULL || Erg))
    {
      if (hilf->Ereignis==EEEvent)
        Erg=1;
      hilf=hilf->Nachfolger;
    }
  }
  return(Erg);
}




/*******************************************************************/
/*                                                                 */
/*  Prozedur: InitAutops              Version:  20/05/91           */
/*                                                                 */
/*******************************************************************/
/*                                                                 */
/*  Klassifizierung:  Prozedur                                     */
/*                                                                 */
/*  Funktionsbeschreibung:                                         */
/*  Diese Prozedur initialisiert die globalen Variablen zu beginn  */
/*  des Programmlaufes                                             */
/*                                                                 */
/*-----------------------------------------------------------------*/
/*                                                                 */
/*  Seiteneffekte:                                                 */
/*                                                                 */
/*******************************************************************/

#ifdef __STDC__
public void initautops(void)
#else /* ! __STDC__ */
public void initautops()
#endif /* ! __STDC__ */
{
  FirstFreeState=1;
  FreeStateSet=EmptyStateSet;
  FreeKtList=NULL;
  Stack=NULL;
}




/*******************************************************************/
/*                                                                 */
/*  Prozedur: MyPurgeHeap             Version:  20/05/91           */
/*                                                                 */
/*******************************************************************/
/*                                                                 */
/*  Klassifizierung:  Prozedur                                     */
/*                                                                 */
/*  Funktionsbeschreibung:                                         */
/*  Loescht bei Bedarf die Menge der freien Kanten, um Platz auf   */
/*  dem Heap zu gewinnen                                           */
/*-----------------------------------------------------------------*/
/*                                                                 */
/*  Seiteneffekte:                                                 */
/*                                                                 */
/*  Lokale Variablen:                                              */
/*  hilf                      KantenMenge                          */
/*  Lokale Prozeduren und Funktionen:                              */
/*******************************************************************/

#ifdef __STDC__
public void MyPurgeHeap(void)
#else /* ! __STDC__ */
public void MyPurgeHeap()
#endif /* ! __STDC__ */
{
  KantenMenge hilf;

  while (FreeKtList!=NULL)
  {
    hilf=FreeKtList;
    FreeKtList=FreeKtList->Nachfolger;
    free(hilf);
  }
}

