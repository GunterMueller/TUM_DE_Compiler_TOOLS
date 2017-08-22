#ifdef __STDC__
extern int BUFClose_Buffer(void);
#else /* ! __STDC__ */
extern int BUFClose_Buffer();
#endif /* ! __STDC__ */

#ifdef __STDC__
extern char BUFGet_Next_Char(void);
#else /* ! __STDC__ */
extern char BUFGet_Next_Char(/* void */);
#endif /* ! __STDC__ */

#ifdef __STDC__
extern void BUFSet_Buffer_Start(void);
#else /* ! __STDC__ */
extern void BUFSet_Buffer_Start();
#endif /* ! __STDC__ */

#ifdef __STDC__
extern void BUFSet_Token_End(void);
#else /* ! __STDC__ */
extern void BUFSet_Token_End();
#endif /* ! __STDC__ */

#ifdef __STDC__
extern void BUFGetToken(char * Token);
#else /* ! __STDC__ */
extern void BUFGetToken();
#endif /* ! __STDC__ */

#ifdef __STDC__
extern void BUFGetUCToken(char *);
#else /* ! __STDC__ */
extern void BUFGetUCToken();
#endif /* ! __STDC__ */

#ifdef __STDC__
extern int BUFGetLength(void);
#else /* ! __STDC__ */
extern int BUFGetLength();
#endif /* ! __STDC__ */

#ifdef __STDC__
extern void BUFGetPosition(char **, int *, int *);
#else /* ! __STDC__ */
extern void BUFGetPosition();
#endif /* ! __STDC__ */

#ifdef __STDC__
extern void BUFInitBuffer(void);
#else /* ! __STDC__ */
extern void BUFInitBuffer();
#endif /* ! __STDC__ */

#ifdef __STDC__
extern void BUFExitBuffer(void);
#else /* ! __STDC__ */
extern void BUFExitBuffer();
#endif /* ! __STDC__ */

