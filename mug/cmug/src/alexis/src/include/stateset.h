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
/*  Projekt: ALEXIS  V 1.0                                         */   
/*                                                                 */   
/*  Autoren: Wolfgang Keller, Jens Coldewey                        */   
/*                                                                 */   
/*  Copyright: Technische Universitaet Muenchen,                   */   
/*             Institut fuer Informatik                            */   
/*                                                                 */   
/*  Segment: stateset.copy                                         */   
/*  Version: 19/07/89A                                             */   
/*                                                                 */   
/*  Sprache: VSPASCAL                                              */   
/*                                                                 */   
/*-----------------------------------------------------------------*/   
/*                                                                 */   
/*  Beschreibung:                                                  */   
/*                                                                 */   
/*  Inhalt:                                                        */   
/*        AreEqualStateSets                                        */   
/*        IsElement                                                */   
/*        UnionStateSet                                            */   
/*        UnionItStateSet                                          */   
/*        AddStateSet                                              */   
/*        ClosureStateSet                                          */   
/*        InsertState                                              */   
/*        GiveAndDeleteState                                       */   
/*        DeleteState                                              */   
/*        DisposeStateSet                                          */   
/*        CopyStateSet                                             */   
/*        MinusStateSet                                            */   
/*        ComplStateSet                                            */   
/*        PrintStateSet                                            */   
/*        CountStateSet                                            */   
/*        DivideStateSet                                           */   
/*        initstateset                                             */   
/*        CountSTFree                                              */
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

#ifndef EXTERN
#define EXTERN extern
#endif

EXTERN int AreEqualStateSets P_((StateSet AeSet1,StateSet AeSet2));

EXTERN int IsElement P_((Status IeState,StateSet IeSet));

EXTERN StateSet UnionStateSet P_((StateSet UsSet1,StateSet UsSet2));

EXTERN void UnionItStateSet P_((StateSet UsSet1,StateSet UsSet2,StateSet *Erg));

EXTERN void AddStateSet P_((StateSet *AsSet1,StateSet AsSet2));

EXTERN StateSet ClosureStateSet P_((StateSet CsSet1,StateSet CsSet2));

EXTERN StateSet InsertState P_((Status IsState,StateSet IsSet));

EXTERN void GiveAndDeleteState P_((StateSet *GdSet,Status *GdState));

EXTERN void DeleteState P_((StateSet *DsSet,Status DsState));

EXTERN void DisposeStateSet P_((StateSet *DiSet));

EXTERN void CopyStateSet P_((StateSet InSet,StateSet *OutSet));

EXTERN void MinusStateSet P_((StateSet *MiSet1,StateSet MiSet2));

EXTERN void ComplStateSet P_((StateSet CsBasis,StateSet *CsSet));

EXTERN void PrintStateSet P_((char *comment,StateSet InSet));

EXTERN int CountStateSet P_((StateSet InSet));

EXTERN void DivideStateSet P_((StateSet Partcomp,StateSet Urbild,StateSet *Schnitt,StateSet *Rest));

EXTERN void initstateset P_((void));

EXTERN int  CountSTFree P_((void));

#undef EXTERN
