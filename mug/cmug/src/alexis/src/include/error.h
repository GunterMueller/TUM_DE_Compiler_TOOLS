#ifndef EXTERN
#define EXTERN        extern
#endif

EXTERN void Warning P_((int WarningNumber));

EXTERN void RecoverableError P_((int ErrorNumber));

EXTERN void FatalError P_((int ErrorNumber));

EXTERN void SoftwareError P_((int ErrorNumber));

EXTERN void initerror P_((void));

#undef EXTERN
