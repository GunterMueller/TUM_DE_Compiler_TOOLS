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
/*  Segment: eveset.c                                              */
/*  Version: 20/05/91                                              */
/*                                                                 */
/*  Sprache: C                                                     */
/*                                                                 */
/*-----------------------------------------------------------------*/
/*                                                                 */
/*  Beschreibung:                                                  */
/*  Diese Unit enthaelt die Deklaration und die Algorithmen fuer   */
/*  den Datentyp EventMge. Dieser Datentyp realisiert eine Menge   */
/*  von Events, die durch einen Integer-Wert identifiziert werden. */
/*  Wird als lineare, geordnete Listen implementiert.              */
/*                                                                 */
/*  Es handelt sich um eine 1:1 Kopie von StateSet.pascal,         */
/*  deshalb ist die komplette Dokumentation fuer jede Prozedur     */
/*  dort analog vorhanden und wird hier weggelassen                */
/*                                                                 */
/*  Inhalt:                                                        */
/*        CountFreeEv                                              */
/*        newState                                                 */
/*        DispState                                                */
/*        newEvent                                                 */
/*        DispEvent                                                */
/*        DisposeEventMge                                          */
/*        CountFreeEv                                              */
/*        UnionItEventMge                                          */
/*             KopiereEnde                                         */
/*        AddEventMge                                              */
/*        InsertEvent                                              */
/*        EvGiveAndDeleteEvent                                     */
/*        DeleteEvent                                              */
/*        CopyEventMge                                             */
/*        CountEventMge                                            */
/*        initeveset                                               */
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
#define MaxFreeEvent  100          /* Gibt an, wieviele freie Zustaende */
				   /* max. in der Liste der freien Zustaende */
				   /* von eveset.c sein duerfen */

#ifdef __STDC__
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#endif

#include <stdio.h>
#include "global.h"
#include "error.h"


private EventMge FreeEvList;
private int      FreeEvCount;  /* Zaehler fuer die Liste der freien Zustandskanten */

/* Diese Liste enthaelt alle Elemente, die bereits einmal vom
   Laufzeitsystem angefordert worden sind, aber z.Zt. wieder frei
   sind. Ein Aufruf von newEvent nimmt moeglichst ein Element
   aus dieser Liste. Nur wenn die Liste leer ist, wird ein Element
   vom Heap-Manager angefordert. DispEvent und DisposeEventMge
   fuehren auf den Mengen keine Dispose aus, sondern tragen
   die Elemente nur in diese Liste ein. */


/*******************************************************************/
/*                                                                 */
/*  Prozedur: CountFreeEv             Version:  20/05/91           */
/*                                                                 */
/*******************************************************************/
/*                                                                 */
/*  Klassifizierung:  Funktion                                     */
/*                                                                 */
/*  Funktionsbeschreibung:                                         */
/*  siehe stateset.pascal                                          */
/*-----------------------------------------------------------------*/
/*                                                                 */
/*  Ausgabeparameter:                                              */
/*  CountFreeEv               var                                  */
/*  Seiteneffekte:                                                 */
/*                                                                 */
/*******************************************************************/

#ifdef __STDC__
public int CountFreeEv(void)
#else /* ! __STDC__ */
public int CountFreeEv()
#endif /* ! __STDC__ */
{
  EventMge CfHs,CfHd;
  int      Erg;

  for (Erg=0,CfHs=FreeEvList;CfHs!=NULL;Erg++)
  {
    CfHd=CfHs;
    CfHs=CfHs->Nachfolger;
    free(CfHd);
  }
  FreeEvList=NULL;
  return(Erg);
}




/*******************************************************************/
/*                                                                 */
/*  Prozedur: newEvent                Version:  20/05/91           */
/*                                                                 */
/*******************************************************************/
/*                                                                 */
/*  Klassifizierung:  Prozedur                                     */
/*                                                                 */
/*  Funktionsbeschreibung:                                         */
/*  siehe stateset.pascal                                          */
/*-----------------------------------------------------------------*/
/*                                                                 */
/*  Transientparameter:                                            */
/*  NsEvent                   EventMge                             */
/*  Seiteneffekte:                                                 */
/*                                                                 */
/*******************************************************************/

#ifdef __STDC__
private void NewEvent(EventMge *NsEvent)
#else /* ! __STDC__ */
private void NewEvent(NsEvent)
  EventMge *NsEvent;
#endif /* ! __STDC__ */
{
  if (FreeEvList==NULL)
    *NsEvent=(EventMge)malloc(sizeof(struct Eventmenge));
  else
  {
    *NsEvent=FreeEvList;
    FreeEvList=FreeEvList->Nachfolger;
  }
}




/*******************************************************************/
/*                                                                 */
/*  Prozedur: DispEvent               Version:  20/05/91           */
/*                                                                 */
/*******************************************************************/
/*                                                                 */
/*  Klassifizierung:  Prozedur                                     */
/*                                                                 */
/*  Funktionsbeschreibung:                                         */
/*  Siehe stateset.pascal                                          */
/*-----------------------------------------------------------------*/
/*                                                                 */
/*  Transientparameter:                                            */
/*  DsEvent                   EventMge                             */
/*  Seiteneffekte:                                                 */
/*                                                                 */
/*******************************************************************/

#ifdef __STDC__
private void DispEvent(EventMge *DsEvent)
#else /* ! __STDC__ */
private void DispEvent(DsEvent)
  EventMge *DsEvent;
#endif /* ! __STDC__ */
{
  (*DsEvent)->Nachfolger=FreeEvList;
  FreeEvList = *DsEvent;
  *DsEvent=NULL;
}




/*******************************************************************/
/*                                                                 */
/*  Prozedur: DisposeEventMge         Version:  20/05/91           */
/*                                                                 */
/*******************************************************************/
/*                                                                 */
/*  Klassifizierung:  Prozedur                                     */
/*                                                                 */
/*  Funktionsbeschreibung:                                         */
/*  siehe stateset.pascal                                          */
/*-----------------------------------------------------------------*/
/*                                                                 */
/*  Transientparameter:                                            */
/*  DiSet                     EventMge                             */
/*  Seiteneffekte:                                                 */
/*                                                                 */
/*  Lokale Variablen:                                              */
/*  DiHs                      EventMge                             */
/*******************************************************************/

#ifdef __STDC__
public void DisposeEventMge(EventMge *DiSet)
#else /* ! __STDC__ */
public void DisposeEventMge(DiSet)
  EventMge *DiSet;
#endif /* ! __STDC__ */
{
  EventMge DiHs;

  if (*DiSet!=EmptyEventMge)
  {
    for (DiHs = *DiSet;DiHs->Nachfolger!=NULL;DiHs=DiHs->Nachfolger);
    DiHs->Nachfolger=FreeEvList;
    FreeEvList = *DiSet;
    *DiSet=NULL;
  }
}




/*******************************************************************/
/*                                                                 */
/*  Prozedur: KopiereEnde             Version:  20/05/91           */
/*                                                                 */
/*******************************************************************/
/*                                                                 */
/*  Klassifizierung:  Prozedur                                     */
/*                                                                 */
/*  Funktionsbeschreibung:                                         */
/*  siehe stateset.pascal                                          */
/*-----------------------------------------------------------------*/
/*                                                                 */
/*  Seiteneffekte:                                                 */
/*                                                                 */
/*******************************************************************/

#ifdef __STDC__
private void KopiereEnde(EventMge *Erg, EventMge *EndeErg, Event Kopie)
#else /* ! __STDC__ */
private void KopiereEnde(Erg,EndeErg,Kopie)
  EventMge *Erg,*EndeErg;
  Event   Kopie;
#endif /* ! __STDC__ */
{
  if (*Erg==NULL)
  {
    /* Fall, dass die Liste noch leer ist */
    NewEvent(Erg);
    (*Erg)->Even=Kopie;
    (*Erg)->Nachfolger=NULL;
    *EndeErg = *Erg;
  }
  else
  {
    NewEvent(&(*EndeErg)->Nachfolger);
    *EndeErg=(*EndeErg)->Nachfolger;
    (*EndeErg)->Nachfolger=NULL;
    (*EndeErg)->Even=Kopie;
  }
}




/*******************************************************************/
/*                                                                 */
/*  Prozedur: UnionItEventMge         Version:  20/05/91           */
/*                                                                 */
/*******************************************************************/
/*                                                                 */
/*  Klassifizierung:  Prozedur                                     */
/*                                                                 */
/*  Funktionsbeschreibung:                                         */
/*  siehe stateset.pascal                                          */
/*-----------------------------------------------------------------*/
/*                                                                 */
/*  Eingabeparameter:                                              */
/*  UsSet1                    EventMge                             */
/*  UsSet2                    EventMge                             */
/*  Transientparameter:                                            */
/*  Erg                       EventMge                             */
/*  Seiteneffekte:                                                 */
/*                                                                 */
/*  Lokale Variablen:                                              */
/*  EndeErg                   EventMge                             */
/*  PointSet1                 EventMge                             */
/*  PointSet2                 EventMge                             */
/*  Schranke                  Event                                */
/*  Abbruch                   Boolean                              */
/*  Kopie                     Event                                */
/*  Lokale Prozeduren und Funktionen:                              */
/*             KopiereEnde                                         */
/*******************************************************************/

#ifdef __STDC__
public void UnionItEventMge(EventMge UsSet1, EventMge UsSet2, EventMge *Erg)
#else /* ! __STDC__ */
public void UnionItEventMge(UsSet1,UsSet2,Erg)
  EventMge UsSet1,UsSet2;
  EventMge *Erg;
#endif /* ! __STDC__ */
{
  EventMge EndeErg;
  EventMge PointSet1,PointSet2;
  Event    Schranke,Kopie;
  int      Abbruch;

  Abbruch=0;
  PointSet1=UsSet1;
  PointSet2=UsSet2;
  EndeErg = *Erg=NULL;
  do
  {
    if (PointSet1==NULL)
    {
      /* Kopiere den Rest von PointSet2 in die Vereinigung */
      while (PointSet2!=NULL)
      {
        Kopie=PointSet2->Even;
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
        Kopie=PointSet1->Even;
        KopiereEnde(Erg,&EndeErg,Kopie);
        PointSet1=PointSet1->Nachfolger;
      }
      Abbruch=1;
    }
    else if (PointSet1->Even==PointSet2->Even)
    {
      Kopie=PointSet1->Even;
      KopiereEnde(Erg,&EndeErg,Kopie);
      PointSet1=PointSet1->Nachfolger;
      PointSet2=PointSet2->Nachfolger;
    }
    else if (PointSet1->Even<PointSet2->Even)
    {
      Schranke=PointSet2->Even;
      while (PointSet1!=NULL && PointSet1->Even<Schranke)
      {
        Kopie=PointSet1->Even;
        KopiereEnde(Erg,&EndeErg,Kopie);
        PointSet1=PointSet1->Nachfolger;
      }
    }
    else
    {
      /* Es gilt PointSet1->Even > PointSet2->Even */
      Schranke=PointSet1->Even;
      while (PointSet2!=NULL && PointSet2->Even<Schranke)
      {
        Kopie=PointSet2->Even;
        KopiereEnde(Erg,&EndeErg,Kopie);
        PointSet2=PointSet2->Nachfolger;
      }
    }
  } while (!Abbruch);
}




/*******************************************************************/
/*                                                                 */
/*  Prozedur: AddEventMge             Version:  20/05/91           */
/*                                                                 */
/*******************************************************************/
/*                                                                 */
/*  Klassifizierung:  Prozedur                                     */
/*                                                                 */
/*  Funktionsbeschreibung:                                         */
/*  siehe stateset.pascal                                          */
/*-----------------------------------------------------------------*/
/*                                                                 */
/*  Eingabeparameter:                                              */
/*  AeSet2                    EventMge                             */
/*  Transientparameter:                                            */
/*  AeSet1                    EventMge                             */
/*  Seiteneffekte:                                                 */
/*                                                                 */
/*  Lokale Variablen:                                              */
/*  AeHe1                     EventMge                             */
/*  AeHe2                     EventMge                             */
/*  AeHe3                     EventMge                             */
/*  AeDisp                    EventMge                             */
/*******************************************************************/

#ifdef __STDC__
public void AddEventMge(EventMge *AsSet1, EventMge AsSet2)
#else /* ! __STDC__ */
public void AddEventMge(AsSet1,AsSet2)
  EventMge *AsSet1;
  EventMge AsSet2;
#endif /* ! __STDC__ */
{
  EventMge AsHe1,AsHe2,AsHe3,AsDisp;

  NewEvent(&AsHe1);    /* Dummy-Element zur Vereinfachung der Routine */
  AsDisp=AsHe1;
  AsHe1->Nachfolger= *AsSet1;
  AsHe2=AsSet2;
  while (AsHe1->Nachfolger!=EmptyEventMge && AsHe2!=EmptyEventMge)
  {
    if ((AsHe1->Nachfolger)->Even>=AsHe2->Even)
    {
      if ((AsHe1->Nachfolger)->Even>AsHe2->Even)
      {
        NewEvent(&AsHe3);
        AsHe3->Nachfolger=AsHe1->Nachfolger;
        AsHe3->Even=AsHe2->Even;
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
  while (AsHe2!=EmptyEventMge)
  {
    NewEvent(&AsHe1->Nachfolger);
    AsHe1=AsHe1->Nachfolger;
    AsHe1->Even=AsHe2->Even;
    AsHe1->Nachfolger=EmptyEventMge;
    AsHe2=AsHe2->Nachfolger;
  }
  *AsSet1=AsDisp->Nachfolger;
  DispEvent(&AsDisp);
}




/*******************************************************************/
/*                                                                 */
/*  Prozedur: InsertEvent             Version:  20/05/91           */
/*                                                                 */
/*******************************************************************/
/*                                                                 */
/*  Klassifizierung:  Funktion                                     */
/*                                                                 */
/*  Funktionsbeschreibung:                                         */
/*  siehe stateset.pascal                                          */
/*-----------------------------------------------------------------*/
/*                                                                 */
/*  Eingabeparameter:                                              */
/*  IsEvent                   Event                                */
/*  IsSet                     EventMge                             */
/*  Ausgabeparameter:                                              */
/*  InsertEvent               EventMge                             */
/*  Seiteneffekte:                                                 */
/*                                                                 */
/*  Lokale Variablen:                                              */
/*  IsHs                      EventMge                             */
/*  IsHs1                     EventMge                             */
/*  IsSetHilf                 EventMge                             */
/*******************************************************************/

#ifdef __STDC__
public EventMge InsertEvent(Status IsEvent, EventMge IsSet)
#else /* ! __STDC__ */
public EventMge InsertEvent(IsEvent,IsSet)
  Status   IsEvent;
  EventMge IsSet;
#endif /* ! __STDC__ */
{
  EventMge IsHs,IsHs1,IsSetHilf;

  IsSetHilf=IsSet;
  if (IsSet==EmptyEventMge)
  {
    NewEvent(&IsSetHilf);
    IsSetHilf->Even=IsEvent;
    IsSetHilf->Nachfolger=NULL;
  }
  else
  {
    for (IsHs=IsSetHilf;IsHs->Nachfolger!=NULL && (Status)IsHs->Even<IsEvent;IsHs=IsHs->Nachfolger);
    if ((Status)IsHs->Even>IsEvent)
    {
      NewEvent(&IsHs1);
      /* IsHs1^ := IsHs^; uebersetzt in : */
   /* IsHs1->Even=IsHs->Even;
      IsHs1->Nachfolger=IsHs->Nachfolger; */
      *IsHs1= *IsHs;

      IsHs->Even=IsEvent;
      IsHs->Nachfolger=IsHs1;
    }
    else if ((Status)IsHs->Even<IsEvent)
    {
      NewEvent(&IsHs1);
      IsHs1->Even=IsEvent;
      IsHs1->Nachfolger=NULL;
      IsHs->Nachfolger=IsHs1;
    }
  }
  return(IsSetHilf);
}




/*******************************************************************/
/*                                                                 */
/*  Prozedur: EvGiveAndDeleteEvent    Version:  20/05/91           */
/*                                                                 */
/*******************************************************************/
/*                                                                 */
/*  Klassifizierung:  Prozedur                                     */
/*                                                                 */
/*  Funktionsbeschreibung:                                         */
/*  siehe stateset.pascal                                          */
/*-----------------------------------------------------------------*/
/*                                                                 */
/*  Transientparameter:                                            */
/*  GdSet                     EventMge                             */
/*  GdEvent                   Event                                */
/*  Seiteneffekte:                                                 */
/*                                                                 */
/*  Lokale Variablen:                                              */
/*  GdHs                      EventMge                             */
/*******************************************************************/

#ifdef __STDC__
public void EvGiveAndDeleteEvent(EventMge *GdSet, Event *GdEvent)
#else /* ! __STDC__ */
public void EvGiveAndDeleteEvent(GdSet,GdEvent)
  EventMge *GdSet;
  Event    *GdEvent;
#endif /* ! __STDC__ */
{
  EventMge GdHs;

  if (*GdSet==EmptyEventMge)
    SoftwareError(10);
  else
  {
    *GdEvent=(*GdSet)->Even;
    GdHs= *GdSet;
    *GdSet=(*GdSet)->Nachfolger;
    DispEvent(&GdHs);
  }
}




/*******************************************************************/
/*                                                                 */
/*  Prozedur: DeleteEvent             Version:  20/05/91           */
/*                                                                 */
/*******************************************************************/
/*                                                                 */
/*  Klassifizierung:  Prozedur                                     */
/*                                                                 */
/*  Funktionsbeschreibung:                                         */
/*  siehe stateset.pascal                                          */
/*-----------------------------------------------------------------*/
/*                                                                 */
/*  Eingabeparameter:                                              */
/*  DsEvent                   Event                                */
/*  Transientparameter:                                            */
/*  DsSet                     EventMge                             */
/*  Seiteneffekte:                                                 */
/*                                                                 */
/*  Lokale Variablen:                                              */
/*  DsHs                      EventMge                             */
/*  DsHs1                     EventMge                             */
/*******************************************************************/

#ifdef __STDC__
public void DeleteEvent(EventMge *DsSet, Event DsEvent)
#else /* ! __STDC__ */
public void DeleteEvent(DsSet,DsEvent)
  EventMge *DsSet;
  Event    DsEvent;
#endif /* ! __STDC__ */
{
  EventMge DsHs,DsHs1;

  if (*DsSet==EmptyEventMge)
    SoftwareError(11);
  else
  {
    DsHs= *DsSet;
    if (DsHs->Even==DsEvent)
      *DsSet=DsHs->Nachfolger;
    else if (DsHs->Nachfolger==NULL)
      SoftwareError(9);
    else
    {
      do
      {
        DsHs1=DsHs;
        DsHs=DsHs->Nachfolger;
      } while (DsHs->Nachfolger!=NULL && DsHs->Even<DsEvent);
      if (DsHs->Even!=DsEvent)
        SoftwareError(6);
      else
      {
        DsHs1->Nachfolger=DsHs->Nachfolger;
        DispEvent(&DsHs);
      }
    }
  }
}




/*******************************************************************/
/*                                                                 */
/*  Prozedur: CopyEventMge            Version:  20/05/91           */
/*                                                                 */
/*******************************************************************/
/*                                                                 */
/*  Klassifizierung:  Prozedur                                     */
/*                                                                 */
/*  Funktionsbeschreibung:                                         */
/*  siehe stateset.pascal                                          */
/*-----------------------------------------------------------------*/
/*                                                                 */
/*  Eingabeparameter:                                              */
/*  InSet                     EventMge                             */
/*  Transientparameter:                                            */
/*  OutSet                    EventMge                             */
/*  Seiteneffekte:                                                 */
/*                                                                 */
/*  Lokale Variablen:                                              */
/*  lauf                      EventMge                             */
/*  erglauf                   EventMge                             */
/*******************************************************************/

#ifdef __STDC__
public void CopyEventMge(EventMge InSet, EventMge *OutSet)
#else /* ! __STDC__ */
public void CopyEventMge(InSet,OutSet)
  EventMge InSet;
  EventMge *OutSet;
#endif /* ! __STDC__ */
{
  EventMge lauf,erglauf;

  if (InSet==NULL)
    *OutSet=InSet;
  else
  {
    lauf=InSet;
    NewEvent(OutSet);
    erglauf= *OutSet;
    while (lauf!=NULL)
    {
      /* erglauf^ := lauf^; uebersetzt in : */
   /* erglauf->Even=lauf->Even;
      erglauf->Nachfolger=lauf->Nachfolger; */
      *erglauf= *lauf;

      if (lauf->Nachfolger!=NULL)
        NewEvent(&erglauf->Nachfolger);
      lauf=lauf->Nachfolger;
      erglauf=erglauf->Nachfolger;
    }
  }
}




/*******************************************************************/
/*                                                                 */
/*  Prozedur: CountEventMge           Version:  20/05/91           */
/*                                                                 */
/*******************************************************************/
/*                                                                 */
/*  Klassifizierung:  Funktion                                     */
/*                                                                 */
/*  Funktionsbeschreibung:                                         */
/*  siehe stateset.pascal                                          */
/*-----------------------------------------------------------------*/
/*                                                                 */
/*  Eingabeparameter:                                              */
/*  InSet                     EventMge                             */
/*  Ausgabeparameter:                                              */
/*  CountEventMge             integer32                            */
/*  Seiteneffekte:                                                 */
/*                                                                 */
/*  Lokale Variablen:                                              */
/*  Erg                       Integer                              */
/*  hilf                      EventMge                             */
/*******************************************************************/

#ifdef __STDC__
public int CountEventMge(EventMge InSet)
#else /* ! __STDC__ */
public int CountEventMge(InSet)
  EventMge InSet;
#endif /* ! __STDC__ */
{
  int Erg;

  for (Erg=0;InSet!=EmptyEventMge;Erg++)
    InSet=InSet->Nachfolger;
  return(Erg);
}




/*******************************************************************/
/*                                                                 */
/*  Prozedur: initeveset              Version:  20/05/91           */
/*                                                                 */
/*******************************************************************/
/*                                                                 */
/*  Klassifizierung:  Prozedur                                     */
/*                                                                 */
/*  Funktionsbeschreibung:                                         */
/*  siehe stateset.pascal                                          */
/*-----------------------------------------------------------------*/
/*                                                                 */
/*  Seiteneffekte:                                                 */
/*                                                                 */
/*******************************************************************/

#ifdef __STDC__
public void initeveset(void)
#else /* ! __STDC__ */
public void initeveset()
#endif /* ! __STDC__ */
{
  FreeEvList=NULL;
  FreeEvCount=0;
}
