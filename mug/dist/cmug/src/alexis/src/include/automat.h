/**********************************************
*  Include fuer automat.c                     *
**********************************************/

#ifdef __STDC__
void AUTInit_Automat(void);                                                 
void AUTScan_Tokens(Token tok);                            
void AUTExit_Automat(void);                                                  
#else /* ! __STDC__ */
void AUTInit_Automat();                                                 
void AUTScan_Tokens(/* FILE **quellfile */);                            
void AUTExit_Automat();                                                  
#endif /* ! __STDC__ */
                                                                                                                              
int abort_scan;  /*BOOL*/ 
                                                                        
/* Wenn diese Variable von einer Aktionsroutine auf true gesetzt wird, so
   wird der Scanner abgebrochen und die Kontrolle an die aufrufende      
   Routine uebergeben. */
                                                                                                                
                                                                        
                                                                        
