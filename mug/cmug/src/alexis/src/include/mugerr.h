/*******************************************************
*  Forward Deklarationen fuer mugerr.c                 *
*******************************************************/

#ifdef __STDC__
void MEMugWarning(int WarningNumber);
void MEMugRecoverableError(int ErrorNumber);
void MEMugFatalError(int ErrorNumber);
void MEMugSoftwareError(int ErrorNumber);
#else /* ! __STDC__ */
void MEMugWarning(/* int WarningNumber */);
void MEMugRecoverableError(/* int ErrorNumber */);
void MEMugFatalError(/* int ErrorNumber */);
void MEMugSoftwareError(/* int ErrorNumber */);
#endif /* ! __STDC__ */
                                                                       
