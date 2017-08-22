/* Bemerkung       : Das QuickSetUnit ist eine Variante des StateSetUnit
   Es implementiert Listen als ungeordnete Listen.
   Diese Darstellung ist fuer manche Anwendungen schneller.

   Diese Unit enthaelt die Deklaration und die Algorithmen fuer den Daten-
   typ QuickSet. Dieser Datentyp realisiert eine Menge von Stati, die
   durch einen Integer-Wert identifiziert werden.
   Implementiert ist die Mengendarstellung als lineare Liste

*/

#ifdef __STDC__
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#endif

#include <stdio.h>
#include "global.h"
#include "error.h"
#define EXTERN
#include "quickset.h"

#define MaxFreeQs 100

private QuickSet FreeQsList;
private int      FreeQsCount;

/* Diese Liste enthaelt alle Elemente, die bereits einmal vom
   Laufzeitsystem
   angefordert worden sind, aber z.Zt. wieder frei sind. Ein Aufruf von
   newState nimmt moeglichst ein Element aus dieser Liste. Nur wenn die
   Liste
   leer ist, wird ein Element vom Heap-Manager angefordert. DispState und
   DisposeStateSet fuehren auf den Mengen keine Dispose aus, sondern
   tragen
   die Elemente nur in diese Liste ein. */




#ifdef __STDC__
private void NewState(QuickSet *NsState)
#else /* ! __STDC__ */
private void NewState(NsState)
  QuickSet *NsState;
#endif /* ! __STDC__ */
{
  if (FreeQsList==NULL)
    *NsState=(QuickSet)malloc(sizeof(struct StateEl));
  else
  {
    FreeQsCount--;
    *NsState=FreeQsList;
    FreeQsList=FreeQsList->Nachfolger;
  }
}




#ifdef __STDC__
private void DispState(QuickSet *DsState)
#else /* ! __STDC__ */
private void DispState(DsState)
  QuickSet *DsState;
#endif /* ! __STDC__ */
{
  if (FreeQsCount>MaxFreeQs)
  {
    free(*DsState);
    *DsState=NULL;
  }
  else
  {
    (*DsState)->Nachfolger=FreeQsList;
    FreeQsList= *DsState;
    *DsState=NULL;
    FreeQsCount++;
  }
}




#ifdef __STDC__
public void DisposeQuickSet(QuickSet *DiSet)
#else /* ! __STDC__ */
public void DisposeQuickSet(DiSet)
  QuickSet *DiSet;
#endif /* ! __STDC__ */
{
  QuickSet  DiHs;

  if (*DiSet)
  {
    DiHs= *DiSet;
    while (DiHs->Nachfolger)
      DiHs=DiHs->Nachfolger;
    DiHs->Nachfolger=FreeQsList;
    FreeQsList= *DiSet;
    *DiSet=NULL;
  }
}




#ifdef __STDC__
public int QSAreEqualQuicksets(QuickSet AeSet1, QuickSet AeSet2)
#else /* ! __STDC__ */
public int QSAreEqualQuicksets(AeSet1,AeSet2)
  QuickSet AeSet1,AeSet2;
#endif /* ! __STDC__ */
{
  int bool;

  /* Schnelltests am Anfang decken statistisch die meisten Faelle ab */
  if (!AeSet1 && !AeSet2)
    return(1);
  if (!AeSet1 || !AeSet2 || CountQuickSet(AeSet1)!=CountQuickSet(AeSet2))
    return(0);
  while (AeSet1 && (bool=QSIsElement(AeSet1->State,AeSet2)))
    AeSet1=AeSet1->Nachfolger;
  return(bool);
}




#ifdef __STDC__
public int QSIsElement(Status IeState, QuickSet IeSet)
#else /* ! __STDC__ */
public int QSIsElement(IeState,IeSet)
  Status   IeState;
  QuickSet IeSet;
#endif /* ! __STDC__ */
{
  int bool;

  if (!IeSet)
    return(0);
  for (bool=0;IeSet && !bool;bool=(int)(IeSet->State==IeState))
    IeSet=IeSet->Nachfolger;
  return(bool);
}





#ifdef __STDC__
public QuickSet UnionQuickSet(QuickSet UsSet1, QuickSet UsSet2)
#else /* ! __STDC__ */
public QuickSet UnionQuickSet(UsSet1,UsSet2)
  QuickSet UsSet1,UsSet2;
#endif /* ! __STDC__ */
{
  QuickSet UsErg,UsHs1,UsHs2;
  Status   HState;

  if (!UsSet1)
    CopyQuickSet(UsSet2,&UsErg);
  else if (!UsSet2)
    CopyQuickSet(UsSet1,&UsErg);
  else
  {
    /* Der Fall, dass beide Mengen leer sind ist jetzt ausgeschlossen */
    CopyQuickSet(UsSet1,&UsErg);
    CopyQuickSet(UsSet2,&UsHs1);
    UsHs2=EmptyQuickSet;
    while (UsHs1)
    {
      QSGiveAndDeleteState(&UsHs1,&HState);
      if (!QSIsElement(HState,UsErg))
	UsHs2=QSInsertState(HState,UsHs2);
    }
    /* UsHs2 enthaelt jetzt alle Elemente, die in das Ergebnis
       eingefuegt werden muessen. UsHs1 ist leer */
    if (UsHs2)
    {
      for (UsHs1=UsHs2;UsHs1->Nachfolger;UsHs1=UsHs1->Nachfolger);
      /* Jetzt steht der Pointer UsHs1 auf dem
	 vorletzten Element, der Menge, die noch zu Erg dazukommt */
      UsHs1->Nachfolger=UsErg;
      UsErg=UsHs2;
    }
  }
  return(UsErg);
}




#ifdef __STDC__
public QuickSet ClosureQuickSet(QuickSet CsSet1, QuickSet CsSet2)
#else /* ! __STDC__ */
public QuickSet ClosureQuickSet(CsSet1,CsSet2)
  QuickSet CsSet1,CsSet2;
#endif /* ! __STDC__ */
{
  QuickSet CsHs1,CsHs2;
  Status   HState;

  if (!CsSet1 || !CsSet2)
    return(EmptyQuickSet);
  CopyQuickSet(CsSet2,&CsHs2);
  CsHs1=EmptyQuickSet;
  while(CsHs2)
  {
    QSGiveAndDeleteState(&CsHs2,&HState);
    if (QSIsElement(HState,CsSet1))
      CsHs1=QSInsertState(HState,CsHs1);
  }
  return(CsHs1);
}




#ifdef __STDC__
public QuickSet QSInsertState(Status IsState, QuickSet IsSet)
#else /* ! __STDC__ */
public QuickSet QSInsertState(IsState,IsSet)
  Status   IsState;
  QuickSet IsSet;
#endif /* ! __STDC__ */
{
  QuickSet IsHs;

  NewState(&IsHs);
  IsHs->State=IsState;
  IsHs->Nachfolger=IsSet;
  return(IsHs);
}




#ifdef __STDC__
public void QSGiveAndDeleteState(QuickSet *GdSet, Status *GdState)
#else /* ! __STDC__ */
public void QSGiveAndDeleteState(GdSet,GdState)
  QuickSet *GdSet;
  Status   *GdState;
#endif /* ! __STDC__ */
{
  QuickSet  GdHs;

  if (!*GdSet)
    SoftwareError(5);
  else
  {
    *GdState=(*GdSet)->State;
    GdHs= *GdSet;
    *GdSet=GdHs->Nachfolger;
    DispState(&GdHs);
  }
}




#ifdef __STDC__
public void QSDeleteState(QuickSet *DsSet, Status DsState)
#else /* ! __STDC__ */
public void QSDeleteState(DsSet,DsState)
  QuickSet *DsSet;
  Status    DsState;
#endif /* ! __STDC__ */
{
  QuickSet  DsHs,DsHs1;
  int       Gefunden;

  if (!*DsSet)
    SoftwareError(5);
  else if ((*DsSet)->State==DsState)
  {
    /* Der zu loeschende Zustand steht an erster Stelle */
    DsHs=(*DsSet)->Nachfolger;
    DispState(DsSet);
    *DsSet=DsHs;
  }
  else
  {
    /* Der zu loeschende Zustand steht nicht! an erster Stelle */
    Gefunden=0;
    DsHs= *DsSet;
    while (DsHs->Nachfolger && !Gefunden)
    {
      if (DsHs->Nachfolger->State==DsState)
      {
	Gefunden=1;
	DsHs1=DsHs->Nachfolger->Nachfolger;
	DispState(&DsHs->Nachfolger);
	DsHs->Nachfolger=DsHs1;
      }
      else
	DsHs=DsHs->Nachfolger;
    }
    if (!Gefunden)
      SoftwareError(6);
  }
}




#ifdef __STDC__
public void CopyQuickSet(QuickSet InSet, QuickSet *OutSet)
#else /* ! __STDC__ */
public void CopyQuickSet(InSet,OutSet)
  QuickSet  InSet;
  QuickSet *OutSet;
#endif /* ! __STDC__ */
{
  QuickSet  lauf,erglauf;

  if (!InSet)
    *OutSet=EmptyQuickSet;
  else
  {
    lauf=InSet;
    NewState(OutSet);
    erglauf= *OutSet;
    while (lauf)
    {
      erglauf=lauf;		/* Strukturkopieren */
      if (lauf->Nachfolger)
	NewState(&erglauf->Nachfolger);
      lauf=lauf->Nachfolger;
      erglauf=erglauf->Nachfolger;
    }
  }
}




#ifdef __STDC__
public void MinusQuickSet(QuickSet *ASet, QuickSet BSet) /* ASet := ASet - BSet */
                 
                 
#else /* ! __STDC__ */
public void MinusQuickSet(ASet,BSet) /* ASet := ASet - BSet */
  QuickSet *ASet;
  QuickSet  BSet;
#endif /* ! __STDC__ */
{
  QuickSet  lauf;

  lauf=BSet;
  while (lauf)
  {
    if (*ASet && QSIsElement(lauf->State,*ASet))
	QSDeleteState(ASet,lauf->State);
    lauf=lauf->Nachfolger;
  }
}




#ifdef __STDC__
private void PrintQuickSetEinb(QuickSet InSet)
#else /* ! __STDC__ */
private void PrintQuickSetEinb(InSet)
  QuickSet InSet;
#endif /* ! __STDC__ */
{
  if (!InSet)
    printf("**\n");
  else
  {
    printf("%d ",InSet->State);
    PrintQuickSetEinb(InSet->Nachfolger);
  }
}




#ifdef __STDC__
public void PrintQuickSet(char *comment, QuickSet InSet)
#else /* ! __STDC__ */
public void PrintQuickSet(comment,InSet)
  char     *comment;
  QuickSet  InSet;
#endif /* ! __STDC__ */
{
  printf("%s  Menge> ",comment);
  if (!InSet)
    printf("**\n");
  else
  {
    printf("%d ",InSet->State);
    PrintQuickSetEinb(InSet->Nachfolger);
  }
}




#ifdef __STDC__
public int CountQuickSet(QuickSet InSet)
#else /* ! __STDC__ */
public int CountQuickSet(InSet)
  QuickSet InSet;
#endif /* ! __STDC__ */
{
  int Erg;

  for (Erg=0;InSet;InSet=InSet->Nachfolger,Erg++);
  return(Erg);
}




#ifdef __STDC__
public void initquickset(void)
#else /* ! __STDC__ */
public void initquickset()
#endif /* ! __STDC__ */
{
  FreeQsList=NULL;
  FreeQsCount=0;
}

