#ifndef EXTERN
#define EXTERN extern
#endif


EXTERN int CountFreeEv P_((void));

EXTERN void DisposeEventMge P_((EventMge *DiSet));

EXTERN void UnionItEventMge P_((EventMge UsSet1, EventMge UsSet2, EventMge *Erg));

EXTERN void AddEventMge P_((EventMge *AsSet1, EventMge AsSet2));

EXTERN EventMge InsertEvent P_((Status IsEvent, EventMge IsSet));

EXTERN void EvGiveAndDeleteEvent P_((EventMge *GdSet, Event *GdEvent));

EXTERN void DeleteEvent P_((EventMge *DsSet, Event DsEvent));

EXTERN void CopyEventMge P_((EventMge InSet, EventMge *OutSet));

EXTERN int CountEventMge P_((EventMge InSet));

EXTERN void initeveset P_((void));


#undef EXTERN
