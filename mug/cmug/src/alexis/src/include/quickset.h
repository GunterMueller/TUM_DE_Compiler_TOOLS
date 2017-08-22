/* quickset.c */

#ifndef EXTERN
#define EXTERN        extern
#endif

EXTERN public void DisposeQuickSet P_((QuickSet *DiSet));

EXTERN public int QSAreEqualQuicksets P_((QuickSet AeSet1, QuickSet AeSet2));

EXTERN public int QSIsElement P_((Status IeState, QuickSet IeSet));

EXTERN public QuickSet UnionQuickSet P_((QuickSet UsSet1, QuickSet UsSet2));

EXTERN public QuickSet ClosureQuickSet P_((QuickSet CsSet1, QuickSet CsSet2));

EXTERN public QuickSet QSInsertState P_((Status IsState, QuickSet IsSet));

EXTERN public void QSGiveAndDeleteState P_((QuickSet *GdSet, Status *GdState));

EXTERN public void QSDeleteState P_((QuickSet *DsSet, Status DsState));

EXTERN public void CopyQuickSet P_((QuickSet InSet, QuickSet *OutSet));

EXTERN public void MinusQuickSet P_((QuickSet *ASet, QuickSet BSet));

EXTERN public void PrintQuickSet P_((char *comment, QuickSet InSet));

EXTERN public int CountQuickSet P_((QuickSet InSet));

EXTERN public void initquickset P_((void));

#undef EXTERN
