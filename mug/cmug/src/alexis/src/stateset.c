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
/*  Segment: stateset.c                                            */
/*  Version: 20/05/91                                              */
/*                                                                 */
/*  Sprache: C                                                     */
/*                                                                 */
/*-----------------------------------------------------------------*/
/*                                                                 */
/* Beschreibung:                                                   */
/*                                                                 */
/* Diese Unit enthaelt die Deklaration und die Algorithmen fuer den*/
/* Datentyp StateSet. Dieser Datentyp realisiert eine Menge von    */
/* Stati, die durch einen Integer-Wert identifiziert werden.       */
/* Implementiert ist die Mengendarstellung als lineare, aufsteigend*/
/* geordnete Liste.                                                */
/*                                                                 */
/*  Inhalt:                                                        */
/*        CountSTFree                                              */
/*        newState          MODULINTERN                            */
/*        DispState         MODULINTERN                            */
/*        DisposeStateSet                                          */
/*        CountSTFree                                              */
/*        AreEqualStateSets                                        */
/*        IsElement                                                */
/*        UnionStateSet                                            */
/*        UnionItStateSet                                          */
/*             KopiereEnde                                         */
/*        AddStateSet                                              */
/*        ClosureStateSet                                          */
/*        InsertState                                              */
/*        GiveAndDeleteState                                       */
/*        DeleteState                                              */
/*        CopyStateSet                                             */
/*        MinusStateSet                                            */
/*        ComplStateSet                                            */
/*        DivideStateSet                                           */
/*        PrintStateSet                                            */
/*             PrintStateSetEinb                                   */
/*        CountStateSet                                            */
/*        initstateset                                             */
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

#define MaxFreeStates 100  /* Gibt an, wieviele freie Zustaende maximal in der
                              Liste der freien Zustaende sein duerfen. */

#ifdef __STDC__
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#endif

#include <stdio.h>
#include "global.h"
#include "autstack.h"
#include "error.h"
#define EXTERN
#include "stateset.h"

private StateSet FreeStList;
private int      FreeStCount;    /* Zaehler fuer die Liste der freien Zustandskanten */

 /* Diese Liste enthaelt alle Elemente, die bereits einmal vom
    Laufzeitsystem angefordert worden sind, aber z.Zt. wieder frei
    sind. Ein Aufruf von newState nimmt moeglichst ein Element aus
    dieser Liste. Nur wenn die Liste leer ist, wird ein Element vom
    Heap-Manager angefordert. DispState und DisposeStateSet fuehren
    auf den Mengen keine Dispose aus, sondern tragen die Elemente
    nur in diese Liste ein. */


/*******************************************************************/
/*                                                                 */
/*  Prozedur: CountSTFree             Version:  18/07/89A          */
/*                                                                 */
/*******************************************************************/
/*                                                                 */
/*  Klassifizierung:  Funktion                                     */
/*                                                                 */
/*  Funktionsbeschreibung:                                         */
/*                                                                 */
/*-----------------------------------------------------------------*/
/*                                                                 */
/*  Ausgabeparameter:                                              */
/*  CountSTFree               integer32                            */
/*  Seiteneffekte:                                                 */
/*                                                                 */
/*******************************************************************/

#ifdef __STDC__
public int CountStFree(void)
#else /* ! __STDC__ */
public int CountStFree()
#endif /* ! __STDC__ */
{
  StateSet CfHs,CfHd;
  int      Erg;

  for (Erg=0,CfHs=FreeStList;CfHs!=NULL;Erg++)
  {
    CfHd=CfHs;
    CfHs=CfHs->Nachfolger;
    free(CfHd);
  }
  FreeStList=NULL;
  return(Erg);
}




/*******************************************************************/
/*                                                                 */
/*  Prozedur: newState                Version:  18/07/89A          */
/*                                                                 */
/*******************************************************************/
/*                                                                 */
/*  Klassifizierung:  Prozedur                                     */
/*                                                                 */
/*  Funktionsbeschreibung:                                         */
/*  Ersetzt den Aufruf von new(PointerVar)                         */
/*  Nur innerhalb dieses Moduls benoetigt                          */
/*  wird nicht nach aussen hin deklariert                          */
/*-----------------------------------------------------------------*/
/*                                                                 */
/*  Transientparameter:                                            */
/*  NsState                   StateSet                             */
/*  Seiteneffekte:                                                 */
/*                                                                 */
/*******************************************************************/

#ifdef __STDC__
private void NewState(StateSet *NsState)
#else /* ! __STDC__ */
private void NewState(NsState)
  StateSet *NsState;
#endif /* ! __STDC__ */
{
  if (FreeStList==NULL)
    *NsState=(StateSet)malloc(sizeof(struct StateEl));
  else
  {
    FreeStCount--;
    *NsState=FreeStList;
    FreeStList=FreeStList->Nachfolger;
  }
}




/*******************************************************************/
/*                                                                 */
/*  Prozedur: DispState               Version:  18/07/89A          */
/*                                                                 */
/*******************************************************************/
/*                                                                 */
/*  Klassifizierung:  Prozedur                                     */
/*                                                                 */
/*  Funktionsbeschreibung:                                         */
/*  Ersetzt den Aufruf von Dispose(PointerVar)                     */
/*  Nur innerhalb dieses Moduls benoetigt                          */
/*  wird nicht nach aussen hin deklariert                          */
/*-----------------------------------------------------------------*/
/*                                                                 */
/*  Transientparameter:                                            */
/*  DsState                   StateSet                             */
/*  Seiteneffekte:                                                 */
/*                                                                 */
/*******************************************************************/

#ifdef __STDC__
private void DispState(StateSet *DsState)
#else /* ! __STDC__ */
private void DispState(DsState)
  StateSet *DsState;
#endif /* ! __STDC__ */
{
  if (FreeStCount>MaxFreeStates)
  {
    free(*DsState);
    *DsState=NULL;
  }
  else
  {
    (*DsState)->Nachfolger=FreeStList;
    FreeStList= *DsState;
    *DsState=NULL;
    FreeStCount++;
  }
}





/*******************************************************************/
/*                                                                 */
/*  Prozedur: DisposeStateSet         Version:  18/07/89A          */
/*                                                                 */
/*******************************************************************/
/*                                                                 */
/*  Klassifizierung:  Prozedur                                     */
/*                                                                 */
/*  Funktionsbeschreibung:                                         */
/*  Loescht ein StateSet                                           */
/*-----------------------------------------------------------------*/
/*                                                                 */
/*  Transientparameter:                                            */
/*  DiSet                     StateSet                             */
/*  Seiteneffekte:                                                 */
/*                                                                 */
/*  Lokale Variablen:                                              */
/*  DiHs                      StateSet                             */
/*******************************************************************/

#ifdef __STDC__
public void DisposeStateSet(StateSet *DiSet)
#else /* ! __STDC__ */
public void DisposeStateSet(DiSet)
  StateSet *DiSet;
#endif /* ! __STDC__ */
{
  StateSet DiHs;

  if (*DiSet!=EmptyStateSet)
  {
    for (DiHs= *DiSet;DiHs->Nachfolger!=NULL;DiHs=DiHs->Nachfolger);
    DiHs->Nachfolger=FreeStList;
    FreeStList= *DiSet;
    *DiSet=NULL;
  }
}




/*******************************************************************/
/*                                                                 */
/*  Prozedur: AreEqualStateSets       Version:  18/07/89A          */
/*                                                                 */
/*******************************************************************/
/*                                                                 */
/*  Klassifizierung:  Funktion                                     */
/*                                                                 */
/*  Funktionsbeschreibung:                                         */
/*  Prueft zwei Statesets auf Gleichheit                           */
/*-----------------------------------------------------------------*/
/*                                                                 */
/*  Eingabeparameter:                                              */
/*  AeSet1                    StateSet                             */
/*  AeSet2                    StateSet                             */
/*  Ausgabeparameter:                                              */
/*  AreEqualStateSets         boolean                              */
/*  Seiteneffekte:                                                 */
/*                                                                 */
/*  Lokale Variablen:                                              */
/*  AeHs1                     StateSet                             */
/*  AeHs2                     StateSet                             */
/*  AeErg                     boolean                              */
/*******************************************************************/

#ifdef __STDC__
public int AreEqualStateSets(StateSet AeSet1, StateSet AeSet2)
#else /* ! __STDC__ */
public int AreEqualStateSets(AeSet1,AeSet2)
  StateSet AeSet1,AeSet2;
#endif /* ! __STDC__ */
{
  StateSet AeHs1,AeHs2;
  int      AeErg;

  AeHs1=AeSet1;
  AeHs2=AeSet2;
  AeErg=1;
  while (AeErg && AeHs1!=NULL && AeHs2!=NULL)
  {
    if (AeHs1->State!=AeHs2->State)
      AeErg=0;
    AeHs1=AeHs1->Nachfolger;
    AeHs2=AeHs2->Nachfolger;
  }
  if (AeErg && AeHs1==NULL && AeHs2==NULL)
    return(1);
  else
    return(0);
}




/*******************************************************************/
/*                                                                 */
/*  Prozedur: IsElement               Version:  18/07/89A          */
/*                                                                 */
/*******************************************************************/
/*                                                                 */
/*  Klassifizierung:  Funktion                                     */
/*                                                                 */
/*  Funktionsbeschreibung:                                         */
/*  Prueft, ob IeState in IeSet enthalten ist                      */
/*-----------------------------------------------------------------*/
/*                                                                 */
/*  Eingabeparameter:                                              */
/*  IeState                   Status                               */
/*  IeSet                     StateSet                             */
/*  Ausgabeparameter:                                              */
/*  IsElement                 boolean                              */
/*  Seiteneffekte:                                                 */
/*                                                                 */
/*  Lokale Variablen:                                              */
/*  IeHs                      StateSet                             */
/*******************************************************************/

#ifdef __STDC__
public int IsElement(Status IeState, StateSet IeSet)
#else /* ! __STDC__ */
public int IsElement(IeState,IeSet)
  Status   IeState;
  StateSet IeSet;
#endif /* ! __STDC__ */
{
  if (IeSet==EmptyStateSet)
    return(0);
  for (;IeSet->Nachfolger!=NULL && IeSet->State<IeState;IeSet=IeSet->Nachfolger);
  if (IeSet->State==IeState)
    return(1);
  else
    return(0);
}




/*******************************************************************/
/*                                                                 */
/*  Prozedur: UnionStateSet           Version:  18/07/89A          */
/*                                                                 */
/*******************************************************************/
/*                                                                 */
/*  Klassifizierung:  Funktion                                     */
/*                                                                 */
/*  Funktionsbeschreibung:                                         */
/*  Diese Funktion vereinigt zwei StateSets. Die Argumente werden  */
/*  dabei zerstoert                                                */
/*                                                                 */
/*-----------------------------------------------------------------*/
/*                                                                 */
/*  Eingabeparameter:                                              */
/*  UsSet1                    StateSet                             */
/*  UsSet2                    StateSet                             */
/*  Ausgabeparameter:                                              */
/*  UnionStateSet             StateSet                             */
/*  Seiteneffekte:                                                 */
/*                                                                 */
/*  Lokale Variablen:                                              */
/*  UsErg                     StateSet                             */
/*  UsHs1                     StateSet                             */
/*  UsHs2                     StateSet                             */
/*******************************************************************/

#ifdef __STDC__
public StateSet UnionStateSet(StateSet UsSet1, StateSet UsSet2)
#else /* ! __STDC__ */
public StateSet UnionStateSet(UsSet1,UsSet2)
  StateSet UsSet1,UsSet2;
#endif /* ! __STDC__ */
{
  StateSet UsErg;

  if (UsSet1==EmptyStateSet)
    return(UsSet2);
  if (UsSet2==EmptyStateSet)
    return(UsSet1);
  if (UsSet1->State==UsSet2->State)
  {
    UsErg=UnionStateSet(UsSet1,UsSet2->Nachfolger);
    DispState(&UsSet2);
    return(UsErg);
  }
  if (UsSet1->State<UsSet2->State)
  {
    UsSet1->Nachfolger=UnionStateSet(UsSet1->Nachfolger,UsSet2);
    return(UsSet1);
  }
  UsSet2->Nachfolger=UnionStateSet(UsSet1,UsSet2->Nachfolger);
  return(UsSet2);
}




/*******************************************************************/
/*                                                                 */
/*  Prozedur: KopiereEnde             Version:  18/07/89A          */
/*                                                                 */
/*******************************************************************/
/*                                                                 */
/*  Klassifizierung:  Prozedur                                     */
/*                                                                 */
/*  Funktionsbeschreibung:                                         */
/*  Kopiert ein Element an das Ende von Erg                        */
/*-----------------------------------------------------------------*/
/*                                                                 */
/*  Seiteneffekte:                                                 */
/*                                                                 */
/*******************************************************************/

#ifdef __STDC__
private void KopiereEnde(StateSet *Erg, StateSet *EndeErg, Status Kopie)
#else /* ! __STDC__ */
private void KopiereEnde(Erg,EndeErg,Kopie)
  StateSet *Erg,*EndeErg;
  Status   Kopie;
#endif /* ! __STDC__ */
{
  if (*Erg==NULL)
  {
    /* Fall, dass die Liste noch leer ist */
    NewState(Erg);
    (*Erg)->State=Kopie;
    (*Erg)->Nachfolger=NULL;
    *EndeErg= *Erg;
  }
  else
  {
    NewState(&(*EndeErg)->Nachfolger);
    *EndeErg=(*EndeErg)->Nachfolger;
    (*EndeErg)->Nachfolger=NULL;
    (*EndeErg)->State=Kopie;
  }
}




/*******************************************************************/
/*                                                                 */
/*  Prozedur: UnionItStateSet         Version:  18/07/89A          */
/*                                                                 */
/*******************************************************************/
/*                                                                 */
/*  Klassifizierung:  Prozedur                                     */
/*                                                                 */
/*  Funktionsbeschreibung:                                         */
/*  Vereinigung der Mengen UsSet1 und UsSet2 zu Erg, aber keine    */
/*  Vernichtung der Eingabemengen und entrekursiviert, also        */
/*  schneller                                                      */
/*                                                                 */
/*-----------------------------------------------------------------*/
/*                                                                 */
/*  Eingabeparameter:                                              */
/*  UsSet1                    StateSet                             */
/*  UsSet2                    StateSet                             */
/*  Ausgabeparameter:                                              */
/*  Erg                       StateSet                             */
/*                                                                 */
/*  Lokale Variablen:                                              */
/*  EndeErg                   StateSet                             */
/*  PointSet1                 StateSet                             */
/*  PointSet2                 StateSet                             */
/*  Schranke                  Status                               */
/*  Abbruch                   Boolean                              */
/*  Kopie                     Status                               */
/*  Lokale Prozeduren und Funktionen:                              */
/*             KopiereEnde                                         */
/*******************************************************************/

#ifdef __STDC__
public void UnionItStateSet(StateSet UsSet1, StateSet UsSet2, StateSet *Erg)
#else /* ! __STDC__ */
public void UnionItStateSet(UsSet1,UsSet2,Erg)
  StateSet UsSet1,UsSet2;
  StateSet *Erg;
#endif /* ! __STDC__ */
{
  StateSet EndeErg;
  StateSet PointSet1,PointSet2;
  Status   Schranke,Kopie;
  int      Abbruch;

  Abbruch=0;
  PointSet1=UsSet1;
  PointSet2=UsSet2;
  EndeErg= *Erg=NULL;
  do
  {
    if (PointSet1==NULL)
    {
      /* Kopiere den Rest von PointSet2 in die Vereinigung */
      while (PointSet2!=NULL)
      {
        Kopie=PointSet2->State;
        KopiereEnde(Erg,&EndeErg,Kopie);
        PointSet2=PointSet2->Nachfolger;
      }
      Abbruch=1;
    }
    else if (PointSet2==NULL)
    {
      /* Kopiere den Rest von PointSet1 in die Vereinigung */
      while (PointSet1!=NULL)
      {
        Kopie=PointSet1->State;
        KopiereEnde(Erg,&EndeErg,Kopie);
        PointSet1=PointSet1->Nachfolger;
      }
      Abbruch=1;
    }
    else if (PointSet1->State==PointSet2->State)
    {
      Kopie=PointSet1->State;
      KopiereEnde(Erg,&EndeErg,Kopie);
      PointSet1=PointSet1->Nachfolger;
      PointSet2=PointSet2->Nachfolger;
    }
    else if (PointSet1->State<PointSet2->State)
    {
      Schranke=PointSet2->State;
      while (PointSet1!=NULL && PointSet1->State<Schranke)
      {
        Kopie=PointSet1->State;
        KopiereEnde(Erg,&EndeErg,Kopie);
        PointSet1=PointSet1->Nachfolger;
      }
    }
    else
    {
      /* Es gilt PointSet1->State > PointSet2->State */
      Schranke=PointSet1->State;
      while (PointSet2!=NULL && PointSet2->State<Schranke)
      {
        Kopie=PointSet2->State;
        KopiereEnde(Erg,&EndeErg,Kopie);
        PointSet2=PointSet2->Nachfolger;
      }
    }
  } while (!Abbruch);
}




/*******************************************************************/
/*                                                                 */
/*  Prozedur: AddStateSet             Version:  18/07/89A          */
/*                                                                 */
/*******************************************************************/
/*                                                                 */
/*  Klassifizierung:  Prozedur                                     */
/*                                                                 */
/*  Funktionsbeschreibung:                                         */
/*  Fuegt der Menge AsSet1 alle Elemente aus AsSet2 hinzu. AsSet1  */
/*  wird dabei veraendert, AsSet2 nicht.                           */
/*                                                                 */
/*-----------------------------------------------------------------*/
/*                                                                 */
/*  Eingabeparameter:                                              */
/*  AsSet2                    StateSet                             */
/*  Transientparameter:                                            */
/*  AsSet1                    StateSet                             */
/*  Seiteneffekte:                                                 */
/*                                                                 */
/*  Lokale Variablen:                                              */
/*  AsHe1                     StateSet                             */
/*  AsHe2                     StateSet                             */
/*  AsHe3                     StateSet                             */
/*  AsDisp                    StateSet                             */
/*******************************************************************/

#ifdef __STDC__
public void AddStateSet(StateSet *AsSet1, StateSet AsSet2)
#else /* ! __STDC__ */
public void AddStateSet(AsSet1,AsSet2)
  StateSet *AsSet1;
  StateSet AsSet2;
#endif /* ! __STDC__ */
{
  StateSet AsHe1,AsHe2,AsHe3,AsDisp;

  NewState(&AsHe1);    /* Dummy-Element zur Vereinfachung der Routine */
  AsDisp=AsHe1;
  AsHe1->Nachfolger= *AsSet1;
  AsHe2=AsSet2;
  while (AsHe1->Nachfolger!=EmptyStateSet && AsHe2!=EmptyStateSet)
  {
    if ((AsHe1->Nachfolger)->State>=AsHe2->State)
    {
      if ((AsHe1->Nachfolger)->State>AsHe2->State)
      {
        NewState(&AsHe3);
        AsHe3->Nachfolger=AsHe1->Nachfolger;
        AsHe3->State=AsHe2->State;
        AsHe1->Nachfolger=AsHe3;
        AsHe1=AsHe3;
        AsHe2=AsHe2->Nachfolger;
      }
      else
      {
        AsHe1=AsHe1->Nachfolger;
        AsHe2=AsHe2->Nachfolger;
      }
    }
    else
      AsHe1=AsHe1->Nachfolger;
  }
  while (AsHe2!=EmptyStateSet)
  {
    NewState(&AsHe1->Nachfolger);
    AsHe1=AsHe1->Nachfolger;
    AsHe1->State=AsHe2->State;
    AsHe1->Nachfolger=EmptyStateSet;
    AsHe2=AsHe2->Nachfolger;
  }
  *AsSet1=AsDisp->Nachfolger;
  DispState(&AsDisp);
}




/*******************************************************************/
/*                                                                 */
/*  Prozedur: ClosureStateSet         Version:  18/07/89A          */
/*                                                                 */
/*******************************************************************/
/*                                                                 */
/*  Klassifizierung:  Funktion                                     */
/*                                                                 */
/*  Funktionsbeschreibung:                                         */
/*  Diese Funktion bildet die Schnittmenge der beiden StateSets.   */
/*  Die Argumente bleiben dabei unveraendert.                      */
/*                                                                 */
/*-----------------------------------------------------------------*/
/*                                                                 */
/*  Eingabeparameter:                                              */
/*  CsSet1                    StateSet                             */
/*  CsSet2                    StateSet                             */
/*  Ausgabeparameter:                                              */
/*  ClosureStateSet           StateSet                             */
/*  Seiteneffekte:                                                 */
/*                                                                 */
/*  Lokale Variablen:                                              */
/*  CsDummy                   StateSet                             */
/*  CsHs1                     StateSet                             */
/*******************************************************************/

#ifdef __STDC__
public StateSet ClosureStateSet(StateSet CsSet1, StateSet CsSet2)
#else /* ! __STDC__ */
public StateSet ClosureStateSet(CsSet1,CsSet2)
  StateSet CsSet1,CsSet2;
#endif /* ! __STDC__ */
{
  StateSet CsDummy,CsHs1;

  NewState(&CsDummy);  /* Dieses Element dient nur der Vereinfachung
			        der Prozedur und wird am Ende wieder
			        geloescht! */
  CsDummy->Nachfolger=NULL;
  CsHs1=CsDummy;
  while (CsSet1!=NULL && CsSet2!=NULL)
  {
    if (CsSet1->State==CsSet2->State)
    {
      NewState(&CsHs1->Nachfolger);
      CsHs1=CsHs1->Nachfolger;
      CsHs1->Nachfolger=NULL;
      CsHs1->State=CsSet1->State;
      CsSet1=CsSet1->Nachfolger;
      CsSet2=CsSet2->Nachfolger;
    }
    else if (CsSet1->State<CsSet2->State)
      CsSet1=CsSet1->Nachfolger;
    else
      CsSet2=CsSet2->Nachfolger;
  }
  CsHs1=CsDummy->Nachfolger;
  DispState(&CsDummy);
  return(CsHs1);
}




/*******************************************************************/
/*                                                                 */
/*  Prozedur: InsertState             Version:  18/07/89A          */
/*                                                                 */
/*******************************************************************/
/*                                                                 */
/*  Klassifizierung:  Funktion                                     */
/*                                                                 */
/*  Funktionsbeschreibung:                                         */
/*  Diese Funktion fuegt den State IsState in die Menge IsSet ein. */
/*  Die Menge IsSet wird dabei zerstoert.                          */
/*                                                                 */
/*-----------------------------------------------------------------*/
/*                                                                 */
/*  Eingabeparameter:                                              */
/*  IsState                   Status                               */
/*  IsSet                     StateSet                             */
/*  Ausgabeparameter:                                              */
/*  InsertState               StateSet                             */
/*  Seiteneffekte:                                                 */
/*                                                                 */
/*  Lokale Variablen:                                              */
/*  IsHs                      StateSet                             */
/*  IsHs1                     StateSet                             */
/*  IsSetHilf                 StateSet                             */
/*******************************************************************/

#ifdef __STDC__
public StateSet InsertState(Status IsState, StateSet IsSet)
#else /* ! __STDC__ */
public StateSet InsertState(IsState,IsSet)
  Status   IsState;
  StateSet IsSet;
#endif /* ! __STDC__ */
{
  StateSet IsHs,IsHs1,IsSetHilf;

  IsSetHilf=IsSet;
  if (IsSet==EmptyStateSet)
  {
    NewState(&IsSetHilf);
    IsSetHilf->State=IsState;
    IsSetHilf->Nachfolger=NULL;
  }
  else
  {
    for (IsHs=IsSetHilf;IsHs->Nachfolger!=NULL && IsHs->State<IsState;IsHs=IsHs->Nachfolger);
    if (IsHs->State>IsState)
    {
      NewState(&IsHs1);
      /* IsHs1^ := IsHs^; uebersetzt in : */
  /*  IsHs1->State=IsHs->State;
      IsHs1->Nachfolger=IsHs->Nachfolger; */
      *IsHs1= *IsHs;

      IsHs->State=IsState;
      IsHs->Nachfolger=IsHs1;
    }
    else if (IsHs->State<IsState)
    {
      NewState(&IsHs1);
      IsHs1->State=IsState;
      IsHs1->Nachfolger=NULL;
      IsHs->Nachfolger=IsHs1;
    }
  }
  return(IsSetHilf);
}




/*******************************************************************/
/*                                                                 */
/*  Prozedur: GiveAndDeleteState      Version:  18/07/89A          */
/*                                                                 */
/*******************************************************************/
/*                                                                 */
/*  Klassifizierung:  Prozedur                                     */
/*                                                                 */
/*  Funktionsbeschreibung:                                         */
/*  Diese Prozedur gibt ein beliebiges Element aus der Menge GdSet */
/*  und loescht es aus dieser Menge. Das Element wird in GdState   */
/*  uebergeben. Ist GdSet leer, so bricht die Unit mit einer       */
/*  Fehlermeldung ab.                                              */
/*                                                                 */
/*-----------------------------------------------------------------*/
/*                                                                 */
/*  Transientparameter:                                            */
/*  GdSet                     StateSet                             */
/*  GdState                   Status                               */
/*  Seiteneffekte:                                                 */
/*                                                                 */
/*  Lokale Variablen:                                              */
/*  GdHs                      StateSet                             */
/*******************************************************************/

#ifdef __STDC__
public void GiveAndDeleteState(StateSet *GdSet, Status *GdState)
#else /* ! __STDC__ */
public void GiveAndDeleteState(GdSet,GdState)
  StateSet *GdSet;
  Status   *GdState;
#endif /* ! __STDC__ */
{
  StateSet GdHs;

  if (*GdSet==EmptyStateSet)
    SoftwareError(5);
  else
  {
    *GdState=(*GdSet)->State;
    GdHs= *GdSet;
    *GdSet=(*GdSet)->Nachfolger;
    DispState(&GdHs);
  }
}




/*******************************************************************/
/*                                                                 */
/*  Prozedur: DeleteState             Version:  18/07/89A          */
/*                                                                 */
/*******************************************************************/
/*                                                                 */
/*  Klassifizierung:  Prozedur                                     */
/*                                                                 */
/*  Funktionsbeschreibung:                                         */
/*  Diese Prozedur loescht das Element DsState aus der Menge DsSet.*/
/*  Ist DsSet leer, oder ist DsState nicht in DsSet enthalten, so  */
/*  bricht die Unit mit  einer Fehlermeldung ab.                   */
/*                                                                 */
/*-----------------------------------------------------------------*/
/*                                                                 */
/*  Eingabeparameter:                                              */
/*  DsState                   Status                               */
/*  Transientparameter:                                            */
/*  DsSet                     StateSet                             */
/*  Seiteneffekte:                                                 */
/*                                                                 */
/*  Lokale Variablen:                                              */
/*  DsHs                      StateSet                             */
/*  DsHs1                     StateSet                             */
/*******************************************************************/

#ifdef __STDC__
public void DeleteState(StateSet *DsSet, Status DsState)
#else /* ! __STDC__ */
public void DeleteState(DsSet,DsState)
  StateSet *DsSet;
  Status   DsState;
#endif /* ! __STDC__ */
{
  StateSet DsHs,DsHs1;

  if (*DsSet==EmptyStateSet)
    SoftwareError(5);
  else
  {
    DsHs= *DsSet;
    if (DsHs->State==DsState)
      *DsSet=DsHs->Nachfolger;
    else if (DsHs->Nachfolger==NULL)
      SoftwareError(6);
    else
    {
      do
      {
        DsHs1=DsHs;
        DsHs=DsHs->Nachfolger;
      } while (DsHs->Nachfolger!=NULL && DsHs->State<DsState);
      if (DsHs->State!=DsState)
        SoftwareError(6);
      else
      {
        DsHs1->Nachfolger=DsHs->Nachfolger;
        DispState(&DsHs);
      }
    }
  }
}




/*******************************************************************/
/*                                                                 */
/*  Prozedur: CopyStateSet            Version:  18/07/89A          */
/*                                                                 */
/*******************************************************************/
/*                                                                 */
/*  Klassifizierung:  Prozedur                                     */
/*                                                                 */
/*  Funktionsbeschreibung:                                         */
/*  Erzeugt eine Kopie von InSet und gibt sie in OutSet zurueck    */
/*  Dabei wird nicht nur ein zweiter Pointer auf dieselbe Menge    */
/*  gesetzt, sondern eine zweite Menge auf dem Heap angelegt       */
/*                                                                 */
/*-----------------------------------------------------------------*/
/*                                                                 */
/*  Eingabeparameter:                                              */
/*  InSet                     Stateset                             */
/*  Transientparameter:                                            */
/*  OutSet                    StateSet                             */
/*  Seiteneffekte:                                                 */
/*                                                                 */
/*  Lokale Variablen:                                              */
/*  lauf                      StateSet                             */
/*  erglauf                   StateSet                             */
/*******************************************************************/

#ifdef __STDC__
public void CopyStateSet(StateSet InSet, StateSet *OutSet)
#else /* ! __STDC__ */
public void CopyStateSet(InSet,OutSet)
  StateSet InSet;
  StateSet *OutSet;
#endif /* ! __STDC__ */
{
  StateSet lauf,erglauf;

  if (InSet==NULL)
    *OutSet=InSet;
  else
  {
    lauf=InSet;
    NewState(OutSet);
    erglauf= *OutSet;
    while (lauf!=NULL)
    {
      /* erglauf^ := lauf^; uebersetzt in : */
  /*  erglauf->State=lauf->State;
      erglauf->Nachfolger=lauf->Nachfolger; */
      *erglauf= *lauf;

      if (lauf->Nachfolger!=NULL)
        NewState(&erglauf->Nachfolger);
      lauf=lauf->Nachfolger;
      erglauf=erglauf->Nachfolger;
    }
  }
}




/*******************************************************************/
/*                                                                 */
/*  Prozedur: MinusStateSet           Version:  18/07/89A          */
/*                                                                 */
/*******************************************************************/
/*                                                                 */
/*  Klassifizierung:  Prozedur                                     */
/*                                                                 */
/*  Funktionsbeschreibung:                                         */
/*  MiSet1 := MiSet1 - MiSet2 ; MiSet1 wird veraendert, MiSet2     */
/*  nicht.                                                         */
/*-----------------------------------------------------------------*/
/*                                                                 */
/*  Eingabeparameter:                                              */
/*  MiSet2                    StateSet                             */
/*  Transientparameter:                                            */
/*  MiSet1                    StateSet                             */
/*  Seiteneffekte:                                                 */
/*                                                                 */
/*  Lokale Variablen:                                              */
/*  MiHs1                     StateSet                             */
/*  MiHs2                     StateSet                             */
/*  MiDisp                    StateSet                             */
/*  MiLoop                    boolean                              */
/*******************************************************************/

#ifdef __STDC__
public void MinusStateSet(StateSet *MiSet1, StateSet MiSet2)
#else /* ! __STDC__ */
public void MinusStateSet(MiSet1,MiSet2)
  StateSet *MiSet1;
  StateSet MiSet2;
#endif /* ! __STDC__ */
{
  StateSet MiHs1,MiHs2,MiDisp;
  int      MiLoop;    /* Bool */

  MiHs1= *MiSet1;
  MiHs2=MiSet2;
  MiLoop=1;
  while (MiHs1!=EmptyStateSet && MiHs2!=EmptyStateSet && MiLoop)
  {
    if (MiHs1->State==MiHs2->State)
    {
      *MiSet1=(*MiSet1)->Nachfolger;
      DispState(&MiHs1);
      MiHs1= *MiSet1;
      MiHs2=MiHs2->Nachfolger;
    }
    else
      MiLoop=0;
  }
  if (MiHs1==EmptyStateSet)
    return;
  while (MiHs1->Nachfolger!=EmptyStateSet && MiHs2!=EmptyStateSet)
  {
    if ((MiHs1->Nachfolger)->State==MiHs2->State)
    {
      MiDisp=MiHs1->Nachfolger;
      MiHs1->Nachfolger=(MiHs1->Nachfolger)->Nachfolger;
      DispState(&MiDisp);
    }
    else
      MiHs1=MiHs1->Nachfolger;
    if (MiHs1->Nachfolger!=EmptyStateSet && (MiHs1->Nachfolger)->State>MiHs2->State)
      MiHs2=MiHs2->Nachfolger;
  }
}




/*******************************************************************/
/*                                                                 */
/*  Prozedur: ComplStateSet           Version:  18/07/89A          */
/*                                                                 */
/*******************************************************************/
/*                                                                 */
/*  Klassifizierung:  Prozedur                                     */
/*                                                                 */
/*  Funktionsbeschreibung:                                         */
/* Bildet Das Komplement von CsSet bezueglich der Grundmenge       */
/* CsBasis und gibt es in CsSet zurueck. der urspruengliche Wert   */
/* von CsSet geht dabei verloren.                                  */
/*                                                                 */
/*-----------------------------------------------------------------*/
/*                                                                 */
/*  Eingabeparameter:                                              */
/*  CsBasis                   StateSet                             */
/*  Transientparameter:                                            */
/*  CsSet                     StateSet                             */
/*  Seiteneffekte:                                                 */
/*                                                                 */
/*  Lokale Variablen:                                              */
/*  CsErg                     StateSet                             */
/*  CsHs1                     StateSet                             */
/*  CsHs2                     StateSet                             */
/*  CsHs3                     StateSet                             */
/*  CsDisp                    StateSet                             */
/*  CsInsert                  boolean                              */
/*******************************************************************/

#ifdef __STDC__
public void ComplStateSet(StateSet CsBasis, StateSet *CsSet)
#else /* ! __STDC__ */
public void ComplStateSet(CsBasis,CsSet)
  StateSet CsBasis;
  StateSet *CsSet;
#endif /* ! __STDC__ */
{
  StateSet CsErg,CsHs1,CsHs2,CsHs3,CsDisp;
  int      CsInsert;  /* Bool */

  NewState(&CsErg); /* Dummy-Element, das am Ende wieder geloescht wird */
  CsHs1=CsBasis;
  CsHs2= *CsSet;
  CsHs3=CsErg;
  while (CsHs1!=EmptyStateSet)
  {
    if (CsHs2==EmptyStateSet)
      CsInsert=1;
    else
      CsInsert=0;
    if (!CsInsert && CsHs2->State!=CsHs1->State)
         CsInsert=1;
    if (CsInsert)
    {
      NewState(&CsHs3->Nachfolger);
      CsHs3=CsHs3->Nachfolger;
      CsHs3->State=CsHs1->State;
    }
    else if (CsHs2!=EmptyStateSet && CsHs2->State<=CsHs1->State)
    {
      CsDisp=CsHs2;
      CsHs2=CsHs2->Nachfolger;
      DispState(&CsDisp);
    }
    CsHs1=CsHs1->Nachfolger;
  }
  CsHs3->Nachfolger=EmptyStateSet;
  if (CsHs2!=EmptyStateSet)
    SoftwareError(15);
  *CsSet=CsErg->Nachfolger;
  DispState(&CsErg);
}




/*******************************************************************/
/*                                                                 */
/*  Prozedur: DivideStateSet          Version:  18/07/89A          */
/*                                                                 */
/*******************************************************************/
/*                                                                 */
/*  Klassifizierung:  Prozedur                                     */
/*                                                                 */
/*  Funktionsbeschreibung:                                         */
/*  Zerlegt die Menge PartComp in Schnitt und Rest bezueglich der  */
/*  Menge Urbild                                                   */
/*-----------------------------------------------------------------*/
/*                                                                 */
/*  Eingabeparameter:                                              */
/*  Partcomp                  StateSet                             */
/*  Urbild                    StateSet                             */
/*  Transientparameter:                                            */
/*  Schnitt                   StateSet                             */
/*  Rest                      StateSet                             */
/*  Seiteneffekte:                                                 */
/*                                                                 */
/*  Lokale Variablen:                                              */
/*  DsHs1                     StateSet                             */
/*  DsHs2                     StateSet                             */
/*  DsHs3                     StateSet                             */
/*  DsHs4                     StateSet                             */
/*  DsDisp1                   StateSet                             */
/*  DsDisp2                   StateSet                             */
/*******************************************************************/

#ifdef __STDC__
public void DivideStateSet(StateSet Partcomp,
                           StateSet Urbild,
                           StateSet *Schnitt,
                           StateSet *Rest)
#else /* ! __STDC__ */
public void DivideStateSet(Partcomp,Urbild,Schnitt,Rest)
  StateSet Partcomp,Urbild;
  StateSet *Schnitt,*Rest;
#endif /* ! __STDC__ */
{
  StateSet DsHs1,DsHs2,DsHs3,DsHs4,DsDisp1,DsDisp2;

  DsHs1=Partcomp;
  DsHs2=Urbild;
  NewState(&DsDisp1);
  DsHs3=DsDisp1;
  NewState(&DsDisp2);
  DsHs4=DsDisp2;
  while (DsHs1!=EmptyStateSet && DsHs2!=EmptyStateSet)
  {
    if (DsHs1->State==DsHs2->State)
    {
      NewState(&DsHs3->Nachfolger);
      DsHs3=DsHs3->Nachfolger;
      /* DsHs3^ := DsHs1^; uebersetzt in : */
   /* DsHs3->State=DsHs1->State;
      DsHs3->Nachfolger=DsHs1->Nachfolger; */
      *DsHs3= *DsHs1;

      DsHs1=DsHs1->Nachfolger;
      DsHs2=DsHs2->Nachfolger;
    }
    else if (DsHs1->State<DsHs2->State)
    {
      NewState(&DsHs4->Nachfolger);
      DsHs4=DsHs4->Nachfolger;
      /* DsHs4^ := DsHs1^; uebersetzt in : */
   /* DsHs4->State=DsHs1->State;
      DsHs4->Nachfolger=DsHs1->Nachfolger; */
      *DsHs4= *DsHs1;

      DsHs1=DsHs1->Nachfolger;
    }
    else
      DsHs2=DsHs2->Nachfolger;
  }
  while (DsHs1!=EmptyStateSet)
  {
    NewState(&DsHs4->Nachfolger);
    DsHs4=DsHs4->Nachfolger;
    /* DsHs4^ := DsHs1^; uebersetzt in : */
 /* DsHs4->State=DsHs1->State;
    DsHs4->Nachfolger=DsHs1->Nachfolger; */
    *DsHs4= *DsHs1;

    DsHs1=DsHs1->Nachfolger;
  }
  DsHs3->Nachfolger=EmptyStateSet;
  DsHs4->Nachfolger=EmptyStateSet;
  *Schnitt=DsDisp1->Nachfolger;
  DispState(&DsDisp1);
  *Rest=DsDisp2->Nachfolger;
  DispState(&DsDisp2);
}




/*******************************************************************/
/*                                                                 */
/*  Prozedur: CountStateSet           Version:  18/07/89A          */
/*                                                                 */
/*******************************************************************/
/*                                                                 */
/*  Klassifizierung:  Funktion                                     */
/*                                                                 */
/*  Funktionsbeschreibung:                                         */
/*  Liefert die Anzahl der Elemente in einem StateSet              */
/*-----------------------------------------------------------------*/
/*                                                                 */
/*  Eingabeparameter:                                              */
/*  InSet                     StateSet                             */
/*  Ausgabeparameter:                                              */
/*  CountStateSet             integer32                            */
/*  Seiteneffekte:                                                 */
/*                                                                 */
/*  Lokale Variablen:                                              */
/*  Erg                       Integer                              */
/*  hilf                      StateSet                             */
/*******************************************************************/

#ifdef __STDC__
public int CountStateSet(StateSet InSet)
#else /* ! __STDC__ */
public int CountStateSet(InSet)
  StateSet InSet;
#endif /* ! __STDC__ */
{
  int Erg;

  for (Erg=0;InSet!=EmptyStateSet;Erg++)
    InSet=InSet->Nachfolger;
  return(Erg);
}




/*******************************************************************/
/*                                                                 */
/*  Prozedur: initstateset            Version:  18/07/89A          */
/*                                                                 */
/*******************************************************************/
/*                                                                 */
/*  Klassifizierung:  Prozedur                                     */
/*                                                                 */
/*  Funktionsbeschreibung:                                         */
/*  Initialisiert die statischen Variablen in StateSet             */
/*-----------------------------------------------------------------*/
/*  Lokale Prozeduren und Funktionen:                              */
/*******************************************************************/

#ifdef __STDC__
public void initstateset(void)
#else /* ! __STDC__ */
public void initstateset()
#endif /* ! __STDC__ */
{
  FreeStList=NULL;
  FreeStCount=0;
}




/*******************************************************************/
/*                                                                 */
/*  Prozedur: PrintSSEinb             Version:  18/07/89A          */
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
/*  InSet                     StateSet                             */
/*  Seiteneffekte:                                                 */
/*                                                                 */
/*******************************************************************/

#ifdef __STDC__
private void PrintSSEinb(StateSet InSet)
#else /* ! __STDC__ */
private void PrintSSEinb(InSet)
  StateSet InSet;
#endif /* ! __STDC__ */
{
  if (InSet==EmptyStateSet)
    printf("**\n");
  else
  {
    printf("%c ",InSet->State);
    PrintSSEinb(InSet->Nachfolger);
  }
}




/*******************************************************************/
/*                                                                 */
/*  Prozedur: PrintStateSet           Version:  18/07/89A          */
/*                                                                 */
/*******************************************************************/
/*                                                                 */
/*  Klassifizierung:  Prozedur                                     */
/*                                                                 */
/*  Funktionsbeschreibung:                                         */
/*  Gibt eine Menge auf dem Bildschirm aus. Eingebaut fuer         */
/*  Diagnosezwecke waehrend der Testphase                          */
/*-----------------------------------------------------------------*/
/*                                                                 */
/*  Eingabeparameter:                                              */
/*  comment                   string                               */
/*  InSet                     StateSet                             */
/*  Seiteneffekte:                                                 */
/*                                                                 */
/*  Lokale Prozeduren und Funktionen:                              */
/*             PrintSSEinb                                         */
/*******************************************************************/

#ifdef __STDC__
public void PrintStateSet(char *comment, StateSet InSet)
#else /* ! __STDC__ */
public void PrintStateSet(comment,InSet)
  char     *comment;
  StateSet InSet;
#endif /* ! __STDC__ */
{
  printf("%s  Menge> ",comment);
  if (InSet==EmptyStateSet)
    printf("**\n");
  else
  {
    printf("%c ",InSet->State);
    PrintSSEinb(InSet->Nachfolger);
  }
}
