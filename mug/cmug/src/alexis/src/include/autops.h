#ifndef EXTERN
#define EXTERN        extern
#endif

EXTERN Status NewState P_((Automat NsAutomat));

EXTERN void DspState P_((Status DsState));

EXTERN void MakeEndzustand P_((Status MeState,Automat MeAutomat));

EXTERN int IstEndzustand P_((Status IeState,Automat IeAutomat));

EXTERN Automat NewAutomaton P_((void));

EXTERN void UnionAutomatons P_((Automat UaAutomat1,Automat UaAutomat2,Automat *UaDestAutomat));

EXTERN void InsertKante P_((Event IkEvent,Status IkFolgezustand,Status IkState,Automat IkAutomat));

EXTERN void InsertEpsilonKante P_((Status IkFolgezustand,Status IkState,Automat IkAutomat));

EXTERN void InsertTKante P_((Status von,Status nach));                                
    /*fuegt von Kante von nach Kante nach fuer jedes Zeichen (0 .. 255) 
      eine Kante ein. Voraussetzung: Kantenmenge bei von muss noch leer 
      sein*/

EXTERN void MakeCompleteKanten P_((Status von,Status nach));
    /*Macht eine Menge von Kanten vollstaendig, in dem in die Menge von 
      fuer jedes t aus T eine Kante auf nach eingefuegt wird, sofern    
      noch keine Kante vorhanden ist*/

EXTERN void DeleteFangKanten P_((Status LoescheIn,Status fang));
    /*Loescht alle Kanten, die auf den Zustand fang fuehren aus der     
      Kantenmenge von LoescheIn*/

EXTERN int ExistsEvent P_((Status EEState,Event EEEvent));

EXTERN void MyPurgeHeap P_((void));

EXTERN void initautops P_((void));

#undef EXTERN
