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
/*  Segment: autstack.c                                            */
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
/*  Von den speziellen Moeglichkeiten von TURBO-Pascal (C)         */
/*  soll hier aus Portabilitaetsgruenden kein Gebrauch gemacht     */
/*  werden. Lediglich das Aufspalten des Programmes in einzelne    */
/*  Units wird wegen der besseren Uebersicht vorgenommen.          */
/*                                                                 */
/*  Zunaechst soll eine einfache Stackmaschine fuer Automaten      */
/*  implementiert werden. Die Moeglichkeit, Automaten in           */
/*  Symboltabellen zu speichern, soll erst spaeter ermoeglicht     */
/*  werden. Dieses Programm stellt die folgenden Funktionen zur    */
/*  Verfuegung:                                                    */
/*                                                                 */
/*  Inhalt:                                                        */
/*        CountFreeEv                                              */
/*        LowCase                                                  */
/*        DisposeAutomaton                                         */
/*        Push                                                     */
/*        PushEvent                                                */
/*        PushSet                                                  */
/*        AGenSet                                                  */
/*        PushTStar                                                */
/*        AGenTStar                                                */
/*        PushStr                                                  */
/*        AGenStr                                                  */
/*        Twist                                                    */
/*        top                                                      */
/*        pop                                                      */
/*        Concat                                                   */
/*        Alternative                                              */
/*        Star                                                     */
/*        Plus                                                     */
/*        Option                                                   */
/*        Myhill                                                   */
/*             MyStateHash                                         */
/*             MyTabIndex                                          */
/*                  MtSolveEndZustaende                            */
/*             MySolveStateSet                                     */
/*             MdDisposeMyTable                                    */
/*        DefineAction                                             */
/*        Negate                                                   */
/*        allbut                                                   */
/*        CopyAutomat                                              */
/*             CPKantenMenge                                       */
/*        Multiply                                                 */
/*        initautstack                                             */
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
#include "autops.h"
#include "stateset.h"
#include "error.h"
#include "minimier.h"
#define EXTERN
#include "autstack.h"


/* Bauernfeind: 17.06.93; Globale Variablen aus var.c */
extern int MaxState;
extern int MaxAction;
/* extern int MaxKomprState; */
/* extern int MaxKomprKanten; */
extern int MAX_ID_NO;
extern int MakTable;





/* Globale Variablen fuer den Myhill-Algorithmus : */

private Automat     GlMyAutomat,GlMyErg;
private MyTableType GlMyTable;
private MyTableList GlMyTabEnd,GlMyTabStart,GlMyUnsolved;

/* Globale Variable fuer fuer CopyAutomat */

/* Bauernfeind: 16.06.93; statisch->dynamisch */
/* private Status      ConvInfo[MaxState+1]; */
private Status      *ConvInfo;



/*******************************************************************/
/*                                                                 */
/*  Prozedur: pop                     Version:  20/05/91           */
/*                                                                 */
/*******************************************************************/
/*                                                                 */
/*  Klassifizierung:  Funktion                                     */
/*                                                                 */
/*  Funktionsbeschreibung:                                         */
/*  Gibt als Ergebnis den Automaten aus dem obersten Stackelement  */
/*  zurueck und entfernt ihn vom Stack. Ist der Stack leer, so     */
/*  wird NULL zurueckgegeben. Wird das Ergebnis nicht mehr         */
/*  benoetigt, so ist der Automat mit "DisposeAutomaton" wieder    */
/*  freizugeben. Das Ergebnis ist nur solange gueltig, bis der     */
/*  Automat in eine Stackoperation ausser Push einbezogen wird.    */
/*                                                                 */
/*-----------------------------------------------------------------*/
/*                                                                 */
/*  Ausgabeparameter:                                              */
/*  pop                       Automat                              */
/*  Seiteneffekte:                                                 */
/*                                                                 */
/*  Lokale Variablen:                                              */
/*  PoHst                     StackTyp                             */
/*******************************************************************/

#ifdef __STDC__
public Automat Pop(void)
#else /* ! __STDC__ */
public Automat Pop()
#endif /* ! __STDC__ */
{
  StackTyp PoHst;
  Automat  Result;

  if (Stack==NULL)
    return(NULL);
  else
  {
    Result=Stack->Inhalt;
    PoHst=Stack;
    Stack=Stack->NextEl;
    free(PoHst);
    return(Result);
  }
}




/*******************************************************************/
/*                                                                 */
/*  Prozedur: LowCase                 Version:  20/05/91           */
/*                                                                 */
/*******************************************************************/
/*                                                                 */
/*  Klassifizierung:  Funktion                                     */
/*                                                                 */
/*  Funktionsbeschreibung:                                         */
/*  Berechnet zu jedem Zeichen (EbcDic den passenden Kleinbuch-    */
/*  staben                                                         */
/*-----------------------------------------------------------------*/
/*                                                                 */
/*  Eingabeparameter:                                              */
/*  inchar                    char                                 */
/*  Ausgabeparameter:                                              */
/*  LowCase                   char                                 */
/*  Seiteneffekte:                                                 */
/*                                                                 */
/*******************************************************************/

#ifdef __STDC__
private Event LowCase(char inchar)
#else /* ! __STDC__ */
private Event LowCase(inchar)
  char inchar;
#endif /* ! __STDC__ */
{
  if ('A'<=inchar && inchar<='Z')
    return(inchar+'a'-'A');
  return(inchar);
}




/*******************************************************************/
/*                                                                 */
/*  Prozedur: DisposeAutomaton        Version:  20/05/91           */
/*                                                                 */
/*******************************************************************/
/*                                                                 */
/*  Klassifizierung:  Prozedur                                     */
/*                                                                 */
/*  Funktionsbeschreibung:                                         */
/*  Diese Prozedur loescht saemtliche Kanten des Automaten und     */
/*  gibt den Speicher, der fuer die Zustaende und den Deskriptor   */
/*  belegt wird, wieder frei. Die Informationen ueber diesen       */
/*  Automaten stehen danach nicht mehr zur Verfuegung.             */
/*                                                                 */
/*-----------------------------------------------------------------*/
/*                                                                 */
/*  Eingabeparameter:                                              */
/*  DaAutomat                 Automat                              */
/*  Seiteneffekte:                                                 */
/*                                                                 */
/*  Lokale Variablen:                                              */
/*  DaState                   Status                               */
/*******************************************************************/

#ifdef __STDC__
public void DisposeAutomaton(Automat DaAutomat)
#else /* ! __STDC__ */
public void DisposeAutomaton(DaAutomat)
  Automat DaAutomat;
#endif /* ! __STDC__ */
{
  Status DaState;

  while (DaAutomat->BelegteZustaende!=EmptyStateSet)
  {
    GiveAndDeleteState(&DaAutomat->BelegteZustaende,&DaState);
    DspState(DaState);
  }
  DisposeStateSet(&DaAutomat->EndZustaende);
  free(DaAutomat);
}




/*******************************************************************/
/*                                                                 */
/*  Prozedur: Push                    Version:  20/05/91           */
/*                                                                 */
/*******************************************************************/
/*                                                                 */
/*  Klassifizierung:  Prozedur                                     */
/*                                                                 */
/*  Funktionsbeschreibung:                                         */
/* Diese Prozedur schiebt den Automaten PuAutomat auf den Stack    */
/*                                                                 */
/*-----------------------------------------------------------------*/
/*                                                                 */
/*  Eingabeparameter:                                              */
/*  PuAutomat                 Automat                              */
/*  Seiteneffekte:                                                 */
/*                                                                 */
/*  Lokale Variablen:                                              */
/*  PuStackEl                 StackTyp                             */
/*******************************************************************/

#ifdef __STDC__
public void Push(Automat PuAutomat)
#else /* ! __STDC__ */
public void Push(PuAutomat)
  Automat PuAutomat;
#endif /* ! __STDC__ */
{
  StackTyp PuStackEl;

  PuStackEl=(struct StackEl *)malloc(sizeof(struct StackEl));
  PuStackEl->Inhalt=PuAutomat;
  PuStackEl->NextEl=Stack;
  Stack=PuStackEl;
}




/*******************************************************************/
/*                                                                 */
/*  Prozedur: PushEvent               Version:  20/05/91           */
/*                                                                 */
/*******************************************************************/
/*                                                                 */
/*  Klassifizierung:  Prozedur                                     */
/*                                                                 */
/*  Funktionsbeschreibung:                                         */
/*  Erzeugt einen Automaten, der nur PeEvent als akzeptierte       */
/*  Wortmenge besitzt und schiebt ihn auf den Stack                */
/*                                                                 */
/*-----------------------------------------------------------------*/
/*                                                                 */
/*  Eingabeparameter:                                              */
/*  PeEvent                   Event                                */
/*  Seiteneffekte:                                                 */
/*                                                                 */
/*  Lokale Variablen:                                              */
/*  PeHa                      Automat                              */
/*  PeHs                      Status                               */
/*******************************************************************/


#ifdef __STDC__
public void PushEvent(Event PeEvent)
#else /* ! __STDC__ */
public void PushEvent(PeEvent)
  Event PeEvent;
#endif /* ! __STDC__ */
{
  Automat PeHa;
  Status  PeHs;

  PeHa=NewAutomaton();
  PeHs=NewState(PeHa);
  if (flags[ignorecase])
    InsertKante(LowCase(PeEvent),PeHs,PeHa->StartZustand,PeHa);
  else
    InsertKante(PeEvent,PeHs,PeHa->StartZustand,PeHa);
  MakeEndzustand(PeHs,PeHa);
  Push(PeHa);
}




/*******************************************************************/
/*                                                                 */
/*  Prozedur: PushSet                 Version:  20/05/91           */
/*                                                                 */
/*******************************************************************/
/*                                                                 */
/*  Klassifizierung:  Prozedur                                     */
/*                                                                 */
/*  Funktionsbeschreibung:                                         */
/* Erzeugt einen Automaten, der alle Elemente aus PsSet als        */
/* akzeptierte Wortmenge besitzt und schiebt ihn auf den Stack     */
/*                                                                 */
/*-----------------------------------------------------------------*/
/*                                                                 */
/*  Eingabeparameter:                                              */
/*  PsSet                     EventSet                             */
/*  Seiteneffekte:                                                 */
/*                                                                 */
/*  Lokale Variablen:                                              */
/*  PsHa                      Automat                              */
/*  PsHs                      Status                               */
/*  PsEvent                   Event                                */
/*******************************************************************/

#ifdef __STDC__
public void PushSet(EventSet PsSet)
#else /* ! __STDC__ */
public void PushSet(PsSet)
  EventSet PsSet;
#endif /* ! __STDC__ */
{
  Automat PsHa;
  Status  PsHs;
  int     PsEvent;
  int     bool,counter;

  PsHa=NewAutomaton();
  PsHs=NewState(PsHa);
  for (PsEvent=MinEvent;PsEvent<=MaxEvent;PsEvent++)
  {
    for (bool=counter=0;!bool && counter<PsSet->Length; counter++)
      if ((Event)PsEvent==PsSet->Set[counter])
        bool=1;
    if (bool)    
    {
      if (flags[ignorecase])
        InsertKante(LowCase((Event)PsEvent),PsHs,PsHa->StartZustand,PsHa);
      else
        InsertKante((Event)PsEvent,PsHs,PsHa->StartZustand,PsHa);
    }
  }
  MakeEndzustand(PsHs,PsHa);
  Push(PsHa);
}




/*******************************************************************/
/*                                                                 */
/*  Prozedur: AGenSet                 Version:  20/05/91           */
/*                                                                 */
/*******************************************************************/
/*                                                                 */
/*  Klassifizierung:  Prozedur                                     */
/*                                                                 */
/*  Funktionsbeschreibung:                                         */
/*  Wie PushSet, aber Automat wird als Pointer zurueckgeliefert    */
/*-----------------------------------------------------------------*/
/*                                                                 */
/*  Eingabeparameter:                                              */
/*  PsSet                     EventSet                             */
/*  Transientparameter:                                            */
/*  outautomat                automat                              */
/*  Seiteneffekte:                                                 */
/*                                                                 */
/*******************************************************************/

#ifdef __STDC__
public void AGenSet(EventSet PsSet, Automat *outautomat)
#else /* ! __STDC__ */
public void AGenSet(PsSet,outautomat)
  EventSet PsSet;
  Automat  *outautomat;
#endif /* ! __STDC__ */
{
  PushSet(PsSet);
  *outautomat=Pop();
}




/*******************************************************************/
/*                                                                 */
/*  Prozedur: PushTStar               Version:  20/05/91           */
/*                                                                 */
/*******************************************************************/
/*                                                                 */
/*  Klassifizierung:  Prozedur                                     */
/*                                                                 */
/*  Funktionsbeschreibung:                                         */
/*  Erzeugt einen Automaten, der T-Stern akzeptiert und schiebt    */
/*  ihn auf den Stack                                              */
/*-----------------------------------------------------------------*/
/*                                                                 */
/*  Seiteneffekte:                                                 */
/*                                                                 */
/*  Lokale Variablen:                                              */
/*  ToPush                    Automat                              */
/*******************************************************************/

#ifdef __STDC__
public void PushTStar(void)
#else /* ! __STDC__ */
public void PushTStar()
#endif /* ! __STDC__ */
{
  Automat ToPush;

  ToPush=NewAutomaton();
  InsertTKante(ToPush->StartZustand,ToPush->StartZustand);
  MakeEndzustand(ToPush->StartZustand,ToPush);
  Push(ToPush);
}




/*******************************************************************/
/*                                                                 */
/*  Prozedur: AGenTStar               Version:  20/05/91           */
/*                                                                 */
/*******************************************************************/
/*                                                                 */
/*  Klassifizierung:  Prozedur                                     */
/*                                                                 */
/*  Funktionsbeschreibung:                                         */
/*  Wie PushTStar, Ergebnis wird als Pointer zurueckgeliefert      */
/*  Hahaha (Anm. d. Ueb., bleibt aber vorerst so)                  */
/*-----------------------------------------------------------------*/
/*                                                                 */
/*  Transientparameter:                                            */
/*  outautomat                automat                              */
/*  Seiteneffekte:                                                 */
/*                                                                 */
/*******************************************************************/

#ifdef __STDC__
public void AGenTStar(Automat *outautomat)
#else /* ! __STDC__ */
public void AGenTStar(outautomat)
  Automat *outautomat;
#endif /* ! __STDC__ */
{
  PushTStar();
  *outautomat=Pop();
}



/*******************************************************************/
/*                                                                 */
/*  Prozedur: PushStr                 Version:  20/05/91           */
/*                                                                 */
/*******************************************************************/
/*                                                                 */
/*  Klassifizierung:  Prozedur                                     */
/*                                                                 */
/*  Funktionsbeschreibung:                                         */
/*  Erzeugt einen Automaten, der den uebergebenen String als       */
/*  akzeptierte Wortmenge besitzt und schiebt ihn auf den Stack.   */
/*  Ist der String Leer, so wird ein Automat erzeugt, der Epsilon  */
/*  akzeptiert.                                                    */
/*                                                                 */
/*-----------------------------------------------------------------*/
/*                                                                 */
/*  Eingabeparameter:                                              */
/*  PsString                  EventString                          */
/*  Seiteneffekte:                                                 */
/*                                                                 */
/*  Lokale Variablen:                                              */
/*  PsHa                      Automat                              */
/*  PsHs                      Status                               */
/*  PsOld                     Status                               */
/*  PsIndex                   integer32                            */
/*******************************************************************/

#ifdef __STDC__
public void PushStr(EventString PsString)   /* Pointer auf EventString-Struktur uebergeben */
                       
#else /* ! __STDC__ */
public void PushStr(PsString)   /* Pointer auf EventString-Struktur uebergeben */
  EventString PsString;
#endif /* ! __STDC__ */
{
  Automat PsHa;
  Status  PsHs,PsOld;
  int     PsIndex;         /* 32 Bit integer */

  PsHa=NewAutomaton();
  PsOld=PsHa->StartZustand;
  for (PsIndex=0;PsIndex<PsString->length;PsIndex++)
  {
    PsHs=NewState(PsHa);
    if (flags[ignorecase])
      InsertKante(LowCase(PsString->body[PsIndex]),PsHs,PsOld,PsHa);
    else
      InsertKante(PsString->body[PsIndex],PsHs,PsOld,PsHa);
    PsOld=PsHs;
  }
  MakeEndzustand(PsOld,PsHa);
  Push(PsHa);
}




/*******************************************************************/
/*                                                                 */
/*  Prozedur: AGenStr                 Version:  20/05/91           */
/*                                                                 */
/*******************************************************************/
/*                                                                 */
/*  Klassifizierung:  Prozedur                                     */
/*                                                                 */
/*  Funktionsbeschreibung:                                         */
/*  Wie PushStr, Automat wird als Pointer zurueckgeliefert         */
/*-----------------------------------------------------------------*/
/*                                                                 */
/*  Eingabeparameter:                                              */
/*  PsString                  EventString                          */
/*  Transientparameter:                                            */
/*  outautomat                automat                              */
/*  Seiteneffekte:                                                 */
/*                                                                 */
/*******************************************************************/

#ifdef __STDC__
public void AGenStr(EventString PsString, Automat *outautomat)
#else /* ! __STDC__ */
public void AGenStr(PsString,outautomat)
  EventString PsString;
  Automat     *outautomat;
#endif /* ! __STDC__ */
{
  PushStr(PsString);
  *outautomat=Pop();
}




/*******************************************************************/
/*                                                                 */
/*  Prozedur: Twist                   Version:  20/05/91           */
/*                                                                 */
/*******************************************************************/
/*                                                                 */
/*  Klassifizierung:  Prozedur                                     */
/*                                                                 */
/*  Funktionsbeschreibung:                                         */
/*  Die beiden obersten Automaten auf dem Stack werden vertauscht  */
/*-----------------------------------------------------------------*/
/*                                                                 */
/*  Seiteneffekte:                                                 */
/*                                                                 */
/*  Lokale Variablen:                                              */
/*  hilf                      StackTyp                             */
/*******************************************************************/

#ifdef __STDC__
public void Twist(void)
#else /* ! __STDC__ */
public void Twist()
#endif /* ! __STDC__ */
{
  StackTyp hilf;

  if (Stack==NULL || Stack->NextEl==NULL)
    SoftwareError(11);
  else
  {
    hilf=Stack;
    Stack=Stack->NextEl;
    hilf->NextEl=Stack->NextEl;
    Stack->NextEl=hilf;
  }
}




/*******************************************************************/
/*                                                                 */
/*  Prozedur: Top                     Version:  20/05/91           */
/*                                                                 */
/*******************************************************************/
/*                                                                 */
/*  Klassifizierung:  Funktion                                     */
/*                                                                 */
/*  Funktionsbeschreibung:                                         */
/*  Gibt als Ergebnis den Automaten aus dem obersten Stackelement  */
/*  zurueck. Der Stack selbst wird nicht veraendert. Ist der Stack */
/*  leer, so wird NULL zurueckgegeben. Das Ergebnis ist nur solange */
/*  gueltig, bis eine andere Stackoperation ausser push            */
/*  durchgefuehrt wird.                                            */
/*                                                                 */
/*-----------------------------------------------------------------*/
/*                                                                 */
/*  Ausgabeparameter:                                              */
/*  top                       Automat                              */
/*  Seiteneffekte:                                                 */
/*                                                                 */
/*******************************************************************/

#ifdef __STDC__
public Automat Top(void)
#else /* ! __STDC__ */
public Automat Top()
#endif /* ! __STDC__ */
{
  if (Stack==NULL)
    return(NULL);
  return(Stack->Inhalt);
}




/*******************************************************************/
/*                                                                 */
/*  Prozedur: Concat                  Version:  20/05/91           */
/*                                                                 */
/*******************************************************************/
/*                                                                 */
/*  Klassifizierung:  Prozedur                                     */
/*                                                                 */
/*  Funktionsbeschreibung:                                         */
/*  Zwei Automaten werden Konkateniert                             */
/*  Der resultierende Automat ist mit  Epsilon-Kanten behaftet,    */
/*  also i.a. Falle nicht mehr deterministisch!                    */
/*-----------------------------------------------------------------*/
/*                                                                 */
/*  Eingabeparameter:                                              */
/*  inaut1                    automat                              */
/*  inaut2                    automat                              */
/*  Transientparameter:                                            */
/*  outautomat                automat                              */
/*  Seiteneffekte:                                                 */
/*                                                                 */
/*  Lokale Variablen:                                              */
/*  CoErg                     Automat                              */
/*  CoHa1                     Automat                              */
/*  CoHa2                     Automat                              */
/*  CoEzstLste                StateSet                             */
/*  CoDispose                 StateSet                             */
/*******************************************************************/

#ifdef __STDC__
public void Concat(Automat inaut1, Automat inaut2, Automat *outautomat)
#else /* ! __STDC__ */
public void Concat(inaut1,inaut2,outautomat)
  Automat inaut1,inaut2;
  Automat *outautomat;
#endif /* ! __STDC__ */
{
  Automat  CoErg,CoHa1,CoHa2;
  StateSet CoEzstLste,CoDispose;

  CoHa2=inaut2;
  CoHa1=inaut1;
  if (inaut1==NULL)
  {
    *outautomat=inaut2;
    return;
  }
  if (inaut2==NULL)
  {
    *outautomat=inaut1;
    return;
  }
  CoErg=(struct AutomatenDescr *)malloc(sizeof(struct AutomatenDescr));
  CoErg->StartZustand=CoHa1->StartZustand;
  CoErg->BelegteZustaende=EmptyStateSet;
  CoErg->EndZustaende=CoHa2->EndZustaende;
  CoEzstLste=CoHa1->EndZustaende;
  do
  {
    InsertEpsilonKante(CoHa2->StartZustand,CoEzstLste->State,CoErg);
    CoDispose=CoEzstLste;
    CoEzstLste=CoEzstLste->Nachfolger;
    free(CoDispose);
  } while (CoEzstLste!=NULL);
  UnionAutomatons(CoHa1,CoHa2,&CoErg);
  *outautomat=CoErg;
}




/*******************************************************************/
/*                                                                 */
/*  Prozedur: Alternative             Version:  20/05/91           */
/*                                                                 */
/*******************************************************************/
/*                                                                 */
/*  Klassifizierung:  Prozedur                                     */
/*                                                                 */
/*  Funktionsbeschreibung:                                         */
/*  Alternativoperation auf den beiden Eingabeautomaten            */
/*  Der resultierende Automat ist mit  Epsilon-Kanten behaftet,    */
/*  also i.a. Falle nicht mehr deterministisch!                    */
/*                                                                 */
/*-----------------------------------------------------------------*/
/*                                                                 */
/*  Eingabeparameter:                                              */
/*  inautomat1                automat                              */
/*  inautomat2                automat                              */
/*  Transientparameter:                                            */
/*  outautomat                automat                              */
/*  Seiteneffekte:                                                 */
/*                                                                 */
/*  Lokale Variablen:                                              */
/*  AlErg                     Automat                              */
/*  AlHa1                     Automat                              */
/*  AlHa2                     Automat                              */
/*  AlEzstLste                StateSet   nicht benoetigt           */
/*  AlDispose                 StateSet   nicht benoetigt           */
/*  AlEzst                    Status     nicht benoetigt           */
/*******************************************************************/

#ifdef __STDC__
public void Alternative(Automat inaut1, Automat inaut2, Automat *outautomat)
#else /* ! __STDC__ */
public void Alternative(inaut1,inaut2,outautomat)
  Automat  inaut1,inaut2;
  Automat  *outautomat;
#endif /* ! __STDC__ */
{
  Automat  AlErg,AlHa1,AlHa2;

  AlHa2=inaut2;
  AlHa1=inaut1;
  if (inaut1==NULL)
  {
    *outautomat=inaut2;
    return;
  }
  if (inaut2==NULL)
  {
    *outautomat=inaut1;
    return;
  }
  AlErg=(struct AutomatenDescr *)malloc(sizeof(struct AutomatenDescr));
  AlErg->BelegteZustaende=NULL;
  AlErg->StartZustand=NewState(AlErg);
  AlErg->EndZustaende=UnionStateSet(AlHa1->EndZustaende,AlHa2->EndZustaende);
  InsertEpsilonKante(AlHa1->StartZustand,AlErg->StartZustand,AlErg);
  InsertEpsilonKante(AlHa2->StartZustand,AlErg->StartZustand,AlErg);
  UnionAutomatons(AlHa1,AlHa2,&AlErg);
  *outautomat=AlErg;
}



/* Entgegen der untenstehenden Behauptungen wird in den folgenden Funktionen
   das Ergebnis nicht auf den Stack geschoben */

/*******************************************************************/
/*                                                                 */
/*  Prozedur: Star                    Version:  20/05/91           */
/*                                                                 */
/*******************************************************************/
/*                                                                 */
/*  Klassifizierung:  Prozedur                                     */
/*                                                                 */
/*  Funktionsbeschreibung:                                         */
/*  Diese Prozedur fuehrt mit inautomat eine Stern-Operation       */
/*  (0 oder mehr Vorkommnisse dieses Ausdruckes) durch und schiebt */
/*  den resultierenden Automaten wieder auf den Stack. Das         */
/*  Ergebnis wird mit Hilfe von Epsilon-Kanten erzeugt, der Automat*/
/*  ist also im allgemeinen Falle nicht mehr deterministisch!      */
/*                                                                 */
/*-----------------------------------------------------------------*/
/*                                                                 */
/*  Eingabeparameter:                                              */
/*  inautomat                 automat                              */
/*  Transientparameter:                                            */
/*  outautomat                automat                              */
/*  Seiteneffekte:                                                 */
/*                                                                 */
/*  Lokale Variablen:                                              */
/*  StAutomat                 Automat                              */
/*  StStart                   Status                               */
/*  StEnde                    Status                               */
/*  StEzstLste                StateSet                             */
/*  StDispose                 StateSet                             */
/*******************************************************************/

#ifdef __STDC__
public void Star(Automat inautomat, Automat *outautomat)
#else /* ! __STDC__ */
public void Star(inautomat,outautomat)
  Automat  inautomat;
  Automat  *outautomat;
#endif /* ! __STDC__ */
{
  Automat  StAutomat;
  Status   StStart;
  StateSet StEzstLste;

  StAutomat=inautomat;
  StStart=NewState(StAutomat);
  MakeEndzustand(StStart,StAutomat);
  InsertEpsilonKante(StAutomat->StartZustand,StStart,StAutomat);
  StEzstLste=StAutomat->EndZustaende;
  do
  {
    InsertEpsilonKante(StAutomat->StartZustand,StEzstLste->State,StAutomat);
    StEzstLste=StEzstLste->Nachfolger;
  } while(StEzstLste!=NULL);
  StAutomat->StartZustand=StStart;
  *outautomat=StAutomat;
}




/*******************************************************************/
/*                                                                 */
/*  Prozedur: Plus                    Version:  20/05/91           */
/*                                                                 */
/*******************************************************************/
/*                                                                 */
/*  Klassifizierung:  Prozedur                                     */
/*                                                                 */
/*  Funktionsbeschreibung:                                         */
/*  Diese Prozedur fuehrt mit inautomat eine Plus-Operation        */
/*  (1 oder mehr Vorkommnisse dieses Ausdruckes) durch und schiebt */
/*  den resultierenden Automaten wieder auf den Stack. Das         */
/*  Ergebnis wird mit Hilfe von Epsilon-Kanten erzeugt, der Automat*/
/*  ist also im allgemeinen Falle nicht mehr deterministisch!      */
/*                                                                 */
/*-----------------------------------------------------------------*/
/*                                                                 */
/*  Eingabeparameter:                                              */
/*  inautomat                 automat                              */
/*  Transientparameter:                                            */
/*  outautomat                automat                              */
/*  Seiteneffekte:                                                 */
/*                                                                 */
/*  Lokale Variablen:                                              */
/*  PlAutomat                 Automat                              */
/*  PlStart                   Status                               */
/*  PlEnde                    Status       nicht benoetigt         */
/*  PlEzstLste                StateSet                             */
/*  PlDispose                 StateSet     nicht benoetigt         */
/*******************************************************************/

#ifdef __STDC__
public void Plus(Automat inautomat, Automat *outautomat)
#else /* ! __STDC__ */
public void Plus(inautomat,outautomat)
  Automat  inautomat;
  Automat  *outautomat;
#endif /* ! __STDC__ */
{
  Automat  PlAutomat;
  Status   PlStart;
  StateSet PlEzstLste;

  PlAutomat=inautomat;
  PlStart=NewState(PlAutomat);
  InsertEpsilonKante(PlAutomat->StartZustand,PlStart,PlAutomat);
  PlEzstLste=PlAutomat->EndZustaende;
  do
  {
    InsertEpsilonKante(PlAutomat->StartZustand,PlEzstLste->State,PlAutomat);
    PlEzstLste=PlEzstLste->Nachfolger;
  } while(PlEzstLste!=NULL);
  PlAutomat->StartZustand=PlStart;
  *outautomat=PlAutomat;
}

 


/*******************************************************************/
/*                                                                 */
/*  Prozedur: Option                  Version:  20/05/91           */
/*                                                                 */
/*******************************************************************/
/*                                                                 */
/*  Klassifizierung:  Prozedur                                     */
/*                                                                 */
/*  Funktionsbeschreibung:                                         */
/*  Diese Prozedur fuehrt mit inautomat eine Option-Operation      */
/*  (0 oder 1 Vorkommnisse dieses Ausdruckes) durch und schiebt    */
/*  den resultierenden Automaten wieder auf den Stack. Das         */
/*  Ergebnis wird mit Hilfe von Epsilon-Kanten erzeugt, der Automat*/
/*  ist also im allgemeinen Falle nicht mehr deterministisch!      */
/*                                                                 */
/*-----------------------------------------------------------------*/
/*                                                                 */
/*  Eingabeparameter:                                              */
/*  inautomat                 automat                              */
/*  Transientparameter:                                            */
/*  outautomat                automat                              */
/*  Seiteneffekte:                                                 */
/*                                                                 */
/*  Lokale Variablen:                                              */
/*  OpAutomat                 Automat                              */
/*  OpStart                   Status                               */
/*  OpEnde                    Status     nicht benoetigt           */
/*  OpEzstLste                StateSet   nicht benoetigt           */
/*  OpDispose                 StateSet   nicht benoetigt           */
/*******************************************************************/

#ifdef __STDC__
public void Option(Automat inautomat, Automat *outautomat)
#else /* ! __STDC__ */
public void Option(inautomat,outautomat)
  Automat  inautomat;
  Automat  *outautomat;
#endif /* ! __STDC__ */
{
  Automat  OpAutomat;
  Status   OpStart;

  OpAutomat=inautomat;
  OpStart=NewState(OpAutomat);
  InsertEpsilonKante(OpAutomat->StartZustand,OpStart,OpAutomat);
  MakeEndzustand(OpStart,OpAutomat);
  OpAutomat->StartZustand=OpStart;
  *outautomat=OpAutomat;
}




/*******************************************************************/
/*                                                                 */
/*  Prozedur: MyStateHash             Version:  20/05/91           */
/*                                                                 */
/*******************************************************************/
/*                                                                 */
/*  Klassifizierung:  Funktion                                     */
/*                                                                 */
/*  Funktionsbeschreibung:                                         */
/*  Diese Funktion berechnet aus einer geg. Zustandsmenge einen    */
/*  HashIndex.                                                     */
/*                                                                 */
/*-----------------------------------------------------------------*/
/*                                                                 */
/*  Eingabeparameter:                                              */
/*  MhStateSet                StateSet                             */
/*  Ausgabeparameter:                                              */
/*  MyStateHash               MyHash                               */
/*  Seiteneffekte:                                                 */
/*                                                                 */
/*  Lokale Variablen:                                              */
/*  MhErg                     integer32                            */
/*  MhIndex                   integer32                            */
/*******************************************************************/

#ifdef __STDC__
private MyHash MyStateHash(StateSet MhStateSet)
#else /* ! __STDC__ */
private MyHash MyStateHash(MhStateSet)
  StateSet MhStateSet;
#endif /* ! __STDC__ */
{
  int MhErg,MhIndex;

  MhErg=0;
  MhIndex=1;
  /* Bauernfeind: Dummy-Funktion */
  while (MhStateSet!=EmptyStateSet)
  {
    MhErg=(MhErg+MhIndex*MhStateSet->State) % MyHashLength;
    MhStateSet=MhStateSet->Nachfolger;
    MhIndex=MhIndex % (maxint / (MaxState+MyHashLength))+1;
  }
  return((MyHash)MhErg);
}




/*******************************************************************/
/*                                                                 */
/*  Prozedur: MtSolveEndZustaende     Version:  20/05/91           */
/*                                                                 */
/*******************************************************************/
/*                                                                 */
/*  Klassifizierung:  Prozedur                                     */
/*                                                                 */
/*  Funktionsbeschreibung:                                         */
/*  Diese Prozedur berechnet fuer den neuen Zustand MpState, ob es */
/*  sich um einen Endzustand handelt, berechnet ggf. die           */
/*  zugehoerige Aktion und traegt ihn in die Endzustandsliste ein. */
/*                                                                 */
/*-----------------------------------------------------------------*/
/*                                                                 */
/*  Eingabeparameter:                                              */
/*  MpStateSet                StateSet                             */
/*  MpState                   Status                               */
/*  Seiteneffekte:                                                 */
/*                                                                 */
/*  Lokale Variablen:                                              */
/*  MpAction                  Action                               */
/*  MpOldAction               Action                               */
/*  MpHs1                     StateSet                             */
/*  MpHs2                     StateSet                             */
/*  MpIsEndZustand            boolean                              */
/*******************************************************************/

#ifdef __STDC__
private void MtSolveEndZustaende(StateSet MpStateSet, Status MpState)
#else /* ! __STDC__ */
private void MtSolveEndZustaende(MpStateSet,MpState)
  StateSet MpStateSet;
  Status   MpState;
#endif /* ! __STDC__ */
{
  Action   MpAction,MpOldAction;
  StateSet MpHs1,MpHs2;
  int      MpIsEndZustand;

  MpAction=NoAction;
  MpHs1=GlMyAutomat->EndZustaende;
  MpHs2=MpStateSet;
  MpIsEndZustand=0;
  while (MpHs1!=EmptyStateSet && MpHs2!=EmptyStateSet)
  {
    if (MpHs1->State==MpHs2->State)
    {
      MpOldAction=ActionTable[MpHs2->State];
      if (((MpOldAction!=NoAction) && (abs(MpOldAction)<abs(MpAction))) || (MpAction==NoAction))
        MpAction=MpOldAction;
      MpIsEndZustand=1;
      MpHs1=MpHs1->Nachfolger;
      MpHs2=MpHs2->Nachfolger;
    }
    else
    {
      if (MpHs1->State<MpHs2->State)
        MpHs1=MpHs1->Nachfolger;
      else
        MpHs2=MpHs2->Nachfolger;
    }
  }
  if (MpIsEndZustand)
  {
    ActionTable[MpState]=MpAction;  /* Aenderung des Originaltextes:
                                       MpState anstatt MtErg, da MtErg an
                                       die Proz. als MpState uebergeben und
                                       nicht veraendert wird */
    GlMyErg->EndZustaende=InsertState(MpState,GlMyErg->EndZustaende);
  }
}




/*******************************************************************/
/*                                                                 */
/*  Prozedur: MyTabIndex              Version:  20/05/91           */
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
/*  MyTabIndex                Status                               */
/*  Transientparameter:                                            */
/*  MtStateSet                StateSet                             */
/*  Seiteneffekte:                                                 */
/*                                                                 */
/*  Lokale Variablen:                                              */
/*  MtTabPtr                  MyTableList                          */
/*  MtFound                   boolean                              */
/*  MtErg                     Status                               */
/*  MtEndZustaende            StateSet    nicht benoetigt          */
/*  MtHashIndex               MyHash                               */
/*  Lokale Prozeduren und Funktionen:                              */
/*             MtSolveEndZustaende                                 */
/*******************************************************************/

#ifdef __STDC__
private Status MyTabIndex(StateSet *MtStateSet)
#else /* ! __STDC__ */
private Status MyTabIndex(MtStateSet)
  StateSet *MtStateSet;
#endif /* ! __STDC__ */
{
  /* Diese Funktion bestimmt zu einer gegebenen Zustandmenge eine
     Zustandsnummer (MtErg). Dabei geht sie so vor:
 
     1. Suche die Zustandsmenge in der Myhill-Tabelle (MyTable)
 
     2. Ist sie bereits enthalten, so entnehme die neue Zustandsnummer
        MtErg der Myhill-Tabelle.
 
     3. Ist sie nicht enthalten, so
        a) generiere einen neuen Zustand MtErg und trage sowohl die
           Zustandsmenge, als auch die neue Nummer in die Tabelle ein.
        b) Ist in der Zustandsmenge ein Endzustand enthalten, so trage
           den neuen Zustand mit Hilfe der Procedure MtSolveEnd-
           Zustaende in die Endzustandsliste des neuen Automaten MyErg
	   ein, ebenso die  Aktion. */

  MyTableList MtTabPtr;
  int         MtFound;
  Status      MtErg;
  MyHash      MtHashIndex;

  /* 1 */
  MtHashIndex=MyStateHash(*MtStateSet);
  MtTabPtr=GlMyTable[MtHashIndex];
  MtFound=0;
  while (MtTabPtr!=NULL && !MtFound)
  {
    if (AreEqualStateSets(*MtStateSet,MtTabPtr->OldStates))
      MtFound=1;
    else
      MtTabPtr=MtTabPtr->HNachfolger;
  }
  if (MtFound)
  {
    /* 2 */
    MtErg=MtTabPtr->NewName;
    DisposeStateSet(MtStateSet);
    *MtStateSet=MtTabPtr->OldStates;
  }
  else
  {
    /* 3a */
    MtErg=NewState(GlMyErg);
    MtTabPtr=(struct MyTableEl *)malloc(sizeof(struct MyTableEl));
    MtTabPtr->NewName=MtErg;
    MtTabPtr->OldStates = *MtStateSet;
    MtTabPtr->HNachfolger=GlMyTable[MtHashIndex];
    MtTabPtr->UNachfolger=NULL;
    GlMyTable[MtHashIndex]=MtTabPtr;
    GlMyTabEnd->UNachfolger=MtTabPtr;
    GlMyTabEnd=MtTabPtr;
    /* 3b */
    MtSolveEndZustaende(*MtStateSet,MtErg);
  }
  return(MtErg);
}



  
/*******************************************************************/
/*                                                                 */
/*  Prozedur: MySolveStateSet         Version:  20/05/91           */
/*                                                                 */
/*******************************************************************/
/*                                                                 */
/*  Klassifizierung:  Prozedur                                     */
/*                                                                 */
/*  Funktionsbeschreibung:                                         */
/*  siehe unten                                                    */
/*-----------------------------------------------------------------*/
/*                                                                 */
/*  Seiteneffekte:                                                 */
/*                                                                 */
/*  Lokale Variablen:                                              */
/*  MsSolveTable              array                                */
/*  MsIndex                   Event                                */
/*  MsMinEvent                Event                                */
/*  MsMaxEvent                Event                                */
/*  MsHs                      StateSet                             */
/*  MsHk                      KantenMenge                          */
/*******************************************************************/

#ifdef __STDC__
private void MySolveStateSet(void)
#else /* ! __STDC__ */
private void MySolveStateSet()
#endif /* ! __STDC__ */
{
  /* In dieser Prozedur werden die Kanten zu dem (neuen) Zustand, auf
     den MyUnsolved in der Myhill-Tabelle zeigt, berechnet. Entstehen
     dabei neue Zustaende, so werden diese in die Tabelle eingetragen.
 
     Um die Kanten zu berechnen wird folgendermassen vorgegangen:
 
      1. Stelle zu jedem Ereignis in der Tabelle MsSolveTable die zuge-
         hoerigen Folgezustaende in einer Zustandsmenge zusammen.
 
      2. Bestimme mit Hilfe der Funktion MyTableIndex fuer jedes
	 Ereignis den Zustand, der zu der Zustandmenge gehoert.
	 Daraus wird dann die Uebergangsfunktion des Zustandes
	 gebildet.
 
      3. Schalte MyUnsolved auf den naechsten Zustand in der Tabelle
	 weiter. */

  StateSet    MsSolveTable[MaxEvent+1];
  Event       MsMinEvent,MsMaxEvent;
  StateSet    MsHs;
  KantenMenge MsHk;
  int         MsIndex;

  for (MsIndex=MinEvent;MsIndex<=MaxEvent;MsIndex++)
    MsSolveTable[MsIndex]=EmptyStateSet;
  MsMinEvent=MaxEvent;
  MsMaxEvent=MinEvent;
  /* 1 */
  MsHs=GlMyUnsolved->OldStates;
  while (MsHs!=EmptyStateSet)
  {
    MsHk=Delta[MsHs->State];
    if (MsHk!=NULL && (MsHk->Ereignis<MsMinEvent))
      MsMinEvent=MsHk->Ereignis;
    while (MsHk!=NULL)
    {
      MsSolveTable[MsHk->Ereignis]=InsertState(MsHk->FolgeZustand,MsSolveTable[MsHk->Ereignis]);
      if (MsHk->Ereignis > MsMaxEvent)
        MsMaxEvent=MsHk->Ereignis;
      MsHk=MsHk->Nachfolger;
    }
    MsHs=MsHs->Nachfolger;
  }
  /* 2 */
  for (MsIndex=MsMinEvent;MsIndex<=(int)MsMaxEvent;MsIndex++)
    if (MsSolveTable[MsIndex]!=EmptyStateSet)
      InsertKante(MsIndex,MyTabIndex(&MsSolveTable[MsIndex]),GlMyUnsolved->NewName,GlMyErg);
  /* 3 */
  GlMyUnsolved=GlMyUnsolved->UNachfolger;
}
      


      
/*******************************************************************/
/*                                                                 */
/*  Prozedur: MdDisposeMyTable        Version:  20/05/91           */
/*                                                                 */
/*******************************************************************/
/*                                                                 */
/*  Klassifizierung:  Prozedur                                     */
/*                                                                 */
/*  Funktionsbeschreibung:                                         */
/*  Diese Prozedur gibt den Speicherplatz, der fuer die Tabelle    */
/*  belegt wurde, wieder frei. Die Informationen in der Tabelle    */
/*  sind danach nicht mehr verfuegbar.                             */
/*                                                                 */
/*-----------------------------------------------------------------*/
/*                                                                 */
/*  Seiteneffekte:                                                 */
/*                                                                 */
/*  Lokale Variablen:                                              */
/*  MdHTable                  MyTableList                          */
/*  MdHStateSet               StateSet       nicht benoetigt       */
/*******************************************************************/

#ifdef __STDC__
private void MdDisposeMyTable(void)
#else /* ! __STDC__ */
private void MdDisposeMyTable()
#endif /* ! __STDC__ */
{
  MyTableList MdHTable;

  while (GlMyTabStart!=NULL)
  {
     DisposeStateSet(&GlMyTabStart->OldStates);
     MdHTable=GlMyTabStart;
     GlMyTabStart=GlMyTabStart->UNachfolger;
     free(MdHTable);
   }
}




/*******************************************************************/
/*                                                                 */
/*  Prozedur: Myhill                  Version:  20/05/91           */
/*                                                                 */
/*******************************************************************/
/*                                                                 */
/*  Klassifizierung:  Prozedur                                     */
/*                                                                 */
/*  Funktionsbeschreibung:                                         */
/*  Diese Prozedur nimmt inautomat, fuehrt mit ihm den             */
/*  Myhill-Algorithmus aus . Bei der Durchfuehrung des Myhill      */
/*  werden Kanten, die auf den Fangzustand gehen, genausowenig     */
/*  beruecksichtigt, wie nicht erreichbare Zustaende.              */
/*  Alle Zustaende des alten Automaten werden freigegeben.         */
/*                                                                 */
/*-----------------------------------------------------------------*/
/*                                                                 */
/*  Eingabeparameter:                                              */
/*  inautomat                 automat                              */
/*  Transientparameter:                                            */
/*  outautomat                automat                              */
/*  Seiteneffekte:                                                 */
/*                                                                 */
/*-----------------------------------------------------------------*/
/*                                                                 */
/*  Lokale Typen:                                                  */
/*                                                                 */
/*  Lokale Variablen:                                              */
/*  MyTable                   MyTableType                          */
/*  MyHashIndex               MyHash                               */
/*  MyTabStart                MyTableList                          */
/*  MyUnsolved                MyTableList                          */
/*  MyTabEnd                  MyTableList                          */
/*  MyErg                     Automat                              */
/*  MyAutomat                 Automat                              */
/*  Lokale Prozeduren und Funktionen:                              */
/*             MyStateHash                                         */
/*             MyTabIndex                                          */
/*                  MtSolveEndZustaende                            */
/*             MySolveStateSet                                     */
/*             MdDisposeMyTable                                    */
/*******************************************************************/

#ifdef __STDC__
public void Myhill(Automat inautomat, Automat *outautomat)
#else /* ! __STDC__ */
public void Myhill(inautomat,outautomat)
  Automat  inautomat;
  Automat *outautomat;
#endif /* ! __STDC__ */
{
  
/* Arbeitsweise der Myhill-Prozedur:
 
  1. Erzeuge neuen Automaten (MyErg). War der Startzustand des alten
     Automaten (MyAutomat) schon ein Endzustand, so wird auch der Start-
     Zustand des neuen Automaten als Endzustand definiert.
 
  2. a) Initialisiere Myhill-Tabelle (MyTable), soda= der neue
	Startzustand mit dem alten identifiziert wird.
     b) Initialisiere Liste der unbearbeiteten Zustaende mit dem neuen
        Startzustand als einzigem Element.
 
  3. Solange noch unbearbeitete Zustaende vorliegen, bearbeite einen
     Zustand aus der Liste mit Hilfe der Prozedur MySolveStateSet.
 
  4. Gib den Speicherplatz fuer den alten Automaten und die
     Myhill-Tabelle wieder frei und schiebe den Ergebnis-Automaten
     auf den Stack.   */

  MyHash MyHashIndex;

  GlMyAutomat=inautomat;
  GlMyErg=NewAutomaton();
  if (IsElement(GlMyAutomat->StartZustand,GlMyAutomat->EndZustaende))
  {
    GlMyErg->EndZustaende=InsertState(GlMyErg->StartZustand,GlMyErg->EndZustaende);
    ActionTable[GlMyErg->StartZustand]=ActionTable[GlMyAutomat->StartZustand];
  }

  /* 2a */
  GlMyTabStart=(struct MyTableEl *)malloc(sizeof(struct MyTableEl));
  GlMyTabStart->OldStates=InsertState(GlMyAutomat->StartZustand,EmptyStateSet);
  GlMyTabStart->NewName=GlMyErg->StartZustand;
  GlMyTabStart->UNachfolger=NULL;
  GlMyTabStart->HNachfolger=NULL;
  GlMyTabEnd=GlMyTabStart;
  for (MyHashIndex=0;MyHashIndex<MyHashLength;MyHashIndex++)
    GlMyTable[MyHashIndex]=NULL;
  GlMyTable[MyStateHash(GlMyTabStart->OldStates)]=GlMyTabStart;

  /* 2b */
  GlMyUnsolved=GlMyTabStart;

  /* 3 */
  do
    MySolveStateSet();
  while (GlMyUnsolved!=NULL);

  /* 4 */
  DisposeAutomaton(GlMyAutomat);
  MdDisposeMyTable();
  *outautomat=GlMyErg;
}




/*******************************************************************/
/*                                                                 */
/*  Prozedur: DefineAction            Version:  20/05/91           */
/*                                                                 */
/*******************************************************************/
/*                                                                 */
/*  Klassifizierung:  Prozedur                                     */
/*                                                                 */
/*  Funktionsbeschreibung:                                         */
/*  Diese Prozedur ordnet allen Endzustaenden des aktuellen        */
/*  Automaten die Aktion DaAction zu. Eventuell schon vorher       */
/*  bestehende Aktionen gehen dabei verloren.                      */
/*                                                                 */
/*-----------------------------------------------------------------*/
/*                                                                 */
/*  Eingabeparameter:                                              */
/*  DaAction                  Action                               */
/*  Seiteneffekte:                                                 */
/*                                                                 */
/*  Lokale Variablen:                                              */
/*  DaHs                      StateSet                             */
/*  DaAutomat                 Automat                              */
/*******************************************************************/

#ifdef __STDC__
public void DefineAction(Action DaAction,
                         Automat inautomat,
                         Automat *outautomat)
                    
                     
                       		/* aus Portabilitaetsgruenden vorerst so wie */
#else /* ! __STDC__ */
public void DefineAction(DaAction,inautomat,outautomat)
  Action   DaAction;
  Automat  inautomat;
  Automat  *outautomat;		/* aus Portabilitaetsgruenden vorerst so wie */
#endif /* ! __STDC__ */
				/* im Pascal-Original (Oh vergebet mir!) */
{
  StateSet DaHs;
  Automat  DaAutomat;

  DaAutomat=inautomat;
  for (DaHs=DaAutomat->EndZustaende;DaHs;DaHs=DaHs->Nachfolger)
    ActionTable[DaHs->State]=DaAction;
  *outautomat=DaAutomat;
}




/*******************************************************************/
/*                                                                 */
/*  Prozedur: Negate                  Version:  20/05/91           */
/*                                                                 */
/*******************************************************************/
/*                                                                 */
/*  Klassifizierung:  Prozedur                                     */
/*                                                                 */
/*  Funktionsbeschreibung:                                         */
/*  Negiert den eingegebenen Automaten                             */
/*-----------------------------------------------------------------*/
/*                                                                 */
/*  Eingabeparameter:                                              */
/*  inautomat                 automat                              */
/*  Transientparameter:                                            */
/*  outautomat                automat                              */
/*  Seiteneffekte:                                                 */
/*                                                                 */
/*  Lokale Variablen:                                              */
/*  Negated                   Automat                              */
/*  lauf                      StateSet                             */
/*  NeuerState                Status                               */
/*******************************************************************/

#ifdef __STDC__
public void Negate(Automat inautomat, Automat *outautomat)
#else /* ! __STDC__ */
public void Negate(inautomat,outautomat)
  Automat inautomat;
  Automat *outautomat;
#endif /* ! __STDC__ */
{
  Automat  Negated;
  StateSet lauf;
  Status   NeuerState;

  Myhill(inautomat,&Negated);

  /* Einfuehren eines neuen kuenstlichen Fangzustandes */
  NeuerState=NewState(Negated);
  /* Vollstaendig machen aller Uebergaenge */
  for (lauf=Negated->BelegteZustaende;lauf;lauf=lauf->Nachfolger)
    MakeCompleteKanten(lauf->State,NeuerState);
  /* Der Automat ist jetzt Vollstaendig, es muss lediglich noch der
     Fangzustand zum Endzustand gemacht werden */
  ComplStateSet(Negated->BelegteZustaende,&Negated->EndZustaende);
  Minimize(Negated,outautomat);
}




/*******************************************************************/
/*                                                                 */
/*  Prozedur: allbut                  Version:  20/05/91           */
/*                                                                 */
/*******************************************************************/
/*                                                                 */
/*  Klassifizierung:  Prozedur                                     */
/*                                                                 */
/*  Funktionsbeschreibung:                                         */
/*  Fuehrt auf einem Automaten die Allbut-Operation durch          */
/*-----------------------------------------------------------------*/
/*                                                                 */
/*  Eingabeparameter:                                              */
/*  inautomat                 automat                              */
/*  Transientparameter:                                            */
/*  outautomat                automat                              */
/*  Seiteneffekte:                                                 */
/*                                                                 */
/*  Lokale Variablen:                                              */
/*  tstar1                    automat                              */
/*  tstar2                    automat                              */
/*  interim1                  automat                              */
/*  interim2                  automat                              */
/*******************************************************************/

#ifdef __STDC__
public void Allbut(Automat inautomat, Automat *outautomat)
#else /* ! __STDC__ */
public void Allbut(inautomat,outautomat)

  Automat inautomat;
  Automat *outautomat;
#endif /* ! __STDC__ */
{
  Automat tstar1,tstar2,interim1,interim2;

  AGenTStar(&tstar1);
  AGenTStar(&tstar2);
  Concat(tstar1,inautomat,&interim1);
  Concat(interim1,tstar2,&interim2);
  Negate(interim2,outautomat);
}




/*******************************************************************/
/*                                                                 */
/*  Prozedur: CPKantenMenge           Version:  20/05/91           */
/*                                                                 */
/*******************************************************************/
/*                                                                 */
/*  Klassifizierung:  Prozedur                                     */
/*                                                                 */
/*  Funktionsbeschreibung:                                         */
/*  Kopiert eine Menge von Kanten                                  */
/*-----------------------------------------------------------------*/
/*                                                                 */
/*  Eingabeparameter:                                              */
/*  alt                       Status                               */
/*  neu                       Status                               */
/*  Seiteneffekte:                                                 */
/*                                                                 */
/*  Lokale Variablen:                                              */
/*  lauf                      KantenMenge                          */
/*  ende                      KantenMenge                          */
/*  hilf                      KantenMenge    nicht benoetigt       */
/*******************************************************************/

#ifdef __STDC__
private void CPKantenMenge(Status alt, Status neu)
#else /* ! __STDC__ */
private void CPKantenMenge(alt,neu)
  Status alt,neu;
#endif /* ! __STDC__ */
{
  KantenMenge lauf;   /* Zeiger auf die alte Menge */
  KantenMenge ende;   /* Zeiger auf das letzte Element der neuen Kantenmenge */

  lauf=Delta[alt];
  if (lauf!=NULL)
  {
    ende=(struct KantenEl *)malloc(sizeof(struct KantenEl));
    Delta[neu]=ende;
    while (lauf)
    {
      ende->Ereignis=lauf->Ereignis;
      ende->FolgeZustand=ConvInfo[lauf->FolgeZustand];
      if (lauf->Nachfolger!=NULL)
      {
        ende->Nachfolger=(struct KantenEl *)malloc(sizeof(struct KantenEl));
        ende=ende->Nachfolger;
      }
      else
        ende->Nachfolger=NULL;
      lauf=lauf->Nachfolger;
    }
  }
}




/*******************************************************************/
/*                                                                 */
/*  Prozedur: CopyAutomat             Version:  20/05/91           */
/*                                                                 */
/*******************************************************************/
/*                                                                 */
/*  Klassifizierung:  Prozedur                                     */
/*                                                                 */
/*  Funktionsbeschreibung:                                         */
/*  Erzeugt eine Kopie eines Automaten, mit neuem Platz im Heap,   */
/*  Ueber den Pointer von Inautomat kann also nicht mehr auf den   */
/*  neuen Automaten zugegriffen werden                             */
/*-----------------------------------------------------------------*/
/*                                                                 */
/*  Eingabeparameter:                                              */
/*  inaut                     automat                              */
/*  Transientparameter:                                            */
/*  outaut                    automat                              */
/*  Seiteneffekte:                                                 */
/*                                                                 */
/*-----------------------------------------------------------------*/
/*                                                                 */
/*  Lokale Typen:                                                  */
/*                                                                 */
/*  Lokale Variablen:                                              */
/*  newaut                    automat                              */
/*  lauf                      StateSet                             */
/*  ConvInfo                  ConvertState                         */
/*  Lokale Prozeduren und Funktionen:                              */
/*             CPKantenMenge                                       */
/*******************************************************************/

#ifdef __STDC__
public void CopyAutomat(Automat inaut, Automat *outaut)
#else /* ! __STDC__ */
public void CopyAutomat(inaut,outaut)
  Automat inaut;
  Automat *outaut;
#endif /* ! __STDC__ */
{
  Automat      newaut;
  StateSet     lauf;

  /* Bauernfeind: 16.06.93; Initialisierung ConvInfo */
  ConvInfo = malloc((MaxState+1)*sizeof(Status));

  newaut=NewAutomaton();
  newaut->EndZustaende=EmptyStateSet;
  newaut->BelegteZustaende=EmptyStateSet;
  for (lauf=inaut->BelegteZustaende;lauf;lauf=lauf->Nachfolger)
  {
    /* Es werden zuerst neue leere Zustaende angelegt */
    ConvInfo[lauf->State]=NewState(newaut);
    if (IsElement(lauf->State,inaut->EndZustaende))
      newaut->EndZustaende=InsertState(ConvInfo[lauf->State],newaut->EndZustaende);
  }
  /* An diesem Punkt gibt es fuer jeden alten einen neuen Zustand und
     die Inform. welche zusammengehoeren ist in ConvInfo abgelegt */
  for (lauf=inaut->BelegteZustaende;lauf;lauf=lauf->Nachfolger)
    CPKantenMenge(lauf->State,ConvInfo[lauf->State]);

  /* Der Neue Automat wird noch gepusht */
  newaut->StartZustand=ConvInfo[inaut->StartZustand];
  *outaut=newaut;
}




/*******************************************************************/
/*                                                                 */
/*  Prozedur: Multiply                Version:  20/05/91           */
/*                                                                 */
/*******************************************************************/
/*                                                                 */
/*  Klassifizierung:  Prozedur                                     */
/*                                                                 */
/*  Funktionsbeschreibung:                                         */
/*  Nimmt den obersten Automaten von Stack und erzeugt einen       */
/*  Automaten fuer Akz(a) [n,m]                                    */
/*  Fehlermoeglichkeiten:                                          */
/*    - n > m, m<>-1  sinnlos                                      */
/*    - n < 0    sinnlos                                           */
/*    - n = m = 0 sinnlos                                          */
/*                                                                 */
/*-----------------------------------------------------------------*/
/*                                                                 */
/*  Eingabeparameter:                                              */
/*  n                         integer32                            */
/*  m                         integer32                            */
/*  Transientparameter:                                            */
/*  inautomat                 automat                              */
/*  Seiteneffekte:                                                 */
/*                                                                 */
/*  Lokale Variablen:                                              */
/*  i                         integer32                            */
/*  noteend                   StateSet                             */
/*  aktaut                    Automat                              */
/*  concaut1                  automat                              */
/*  concaut2                  automat                              */
/*  concerg                   automat                              */
/*  copyerg                   automat                              */
/*  opterg                    automat                              */
/*  pluserg                   automat                              */
/*******************************************************************/
    
#ifdef __STDC__
public void Multiply(Automat *inautomat, int n, int m)
#else /* ! __STDC__ */
public void Multiply(inautomat,n,m)
  Automat *inautomat;
  int     n,m;
#endif /* ! __STDC__ */
{
  StateSet noteend;
  Automat  aktaut;
  Automat  concaut1,concaut2,concerg,copyerg,opterg,pluserg;
  int      i;

  if (n>m && m!=-1)
    RecoverableError(1);
  else
  {
    if (n<0)
      RecoverableError(2);
    else
    {
      if (m==-1)
      {
        /* Fall, dass der Automat n, erzeugt werden soll */
        if (!n)
	{
          Push(*inautomat);
          Star(Pop(),inautomat);
	}
        else
	{
          if (n==1)
	  {
            Push(*inautomat);
            Plus(Pop(),inautomat);
	  }
          else
	  {
            /* jetzt wird n-1 mal kopiert
               der oberste Automat auf dem Stack wird der
               letzte, der mit Plus behandelt wird.
               Danach n-1 mal Concat */
            for (i=1;i<n;i++)
	    {
              CopyAutomat(Top(),&copyerg);
              Push(copyerg);
	    }
            Plus(Pop(),&pluserg);
            Push(pluserg);
            for (i=1;i<n;i++)
	    {
              concaut2=Pop(); 
              concaut1=Pop();
              Concat(concaut1,concaut2,&concerg);
              Push(concerg);
	    }
            *inautomat=Pop();
	  }
	}
      }
      else  /* in diesem Fall sind die Parameter in Ordnung und normal */
      {
        /* Es wird der Automat n,m erzeugt, bei 0 der Automat 1,m,
           der dann spaeter mit Option repariert wird */
        Push(*inautomat);
        if (n<=1)
	{
          aktaut=Top();
          CopyStateSet(aktaut->EndZustaende,&noteend);
	}
        else
          noteend=EmptyStateSet;
        for (i=2;i<=m;i++)
	{
          /* ab 2, weil er schon einmal auf dem Stack liegt */
          CopyAutomat(Top(),&copyerg);
          Push(copyerg);
          if (i>=n)
	  {
            /* muessen die EndZustaende gemerkt werden */
            aktaut=Top();
            AddStateSet(&noteend,aktaut->EndZustaende);
	  }
	}

        /* Auf dem Stack liegen jetzt m Automaten, die mit m-1 maligem
           Concat miteinander verbunden werden */

        for (i=1;i<m;i++)
	{
          concaut2=Pop();
          concaut1=Pop();
          Concat(concaut1,concaut2,&concerg);
          Push(concerg);
	}

        /* Der gesuchte Automat liegt jetzt fast fertig auf dem stack, die
           Endzustaende muessen noch korrigiert werden */
        aktaut=Top();
        AddStateSet(&aktaut->EndZustaende,noteend);
        DisposeStateSet(&noteend);
        if (!n)
	{
          Option(Pop(),&opterg);
          Push(opterg);
	}
        *inautomat=Pop();
      }
    }
  }
}




/*******************************************************************/
/*                                                                 */
/*  Prozedur: initautstack            Version:  20/05/91           */
/*                                                                 */
/*******************************************************************/
/*                                                                 */
/*  Klassifizierung:  Prozedur                                     */
/*                                                                 */
/*  Funktionsbeschreibung:                                         */
/*  Initialisiert AutStack                                         */
/*-----------------------------------------------------------------*/
/*                                                                 */
/*  Seiteneffekte:                                                 */
/*                                                                 */
/*******************************************************************/

#ifdef __STDC__
public void initautstack(void)
#else /* ! __STDC__ */
public void initautstack()
#endif /* ! __STDC__ */
{}
