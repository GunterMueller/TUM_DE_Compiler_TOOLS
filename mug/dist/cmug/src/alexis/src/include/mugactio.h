/*******************************************
* Forward Deklarationen fuer mugactio      *
*******************************************/

#ifdef __STDC__
void MACRetCC(Token, int, int);                     
void MACRetTok(Token, int, int, char *);                     
void MACRetInt(Token, int);                              
void MACRetId(Token, int);                               
void MACRetProcessedString(Token, int, char *);                     
void MACRetString(Token, int);                           
void MACInitMugActions(void);                                             
void MACExitMugActions(void);                                             
#else /* ! __STDC__ */
void MACRetCC();                     
void MACRetTok();                     
void MACRetInt();                              
void MACRetId();                               
void MACRetProcessedString();                     
void MACRetString();                           
void MACInitMugActions();                                             
void MACExitMugActions();                                             
#endif /* ! __STDC__ */

extern int IntCode,IdentCode,StringCode;
                                                                      
