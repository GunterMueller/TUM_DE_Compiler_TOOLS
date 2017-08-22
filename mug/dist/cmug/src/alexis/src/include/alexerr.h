#ifdef __STDC__
extern void AERAlexWarning(int WarningNumber, Quellort *ort);
extern void AERAlexRecoverableError(int ErrorNumber, Quellort *ort);
extern void AERAlexFatalError(int ErrorNumber, Quellort *ort);
extern void AERAlexSoftwareError(int ErrorNumber, Quellort *ort);
#else /* ! __STDC__ */
extern void AERAlexWarning();
extern void AERAlexRecoverableError();
extern void AERAlexFatalError();
extern void AERAlexSoftwareError();
#endif /* ! __STDC__ */
