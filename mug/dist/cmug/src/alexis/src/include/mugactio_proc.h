#ifdef __STDC__
extern void MACRetCC(Token, int, int);
#else /* ! __STDC__ */
extern void MACRetCC();
#endif /* ! __STDC__ */

#ifdef __STDC__
extern void MACRetTok(Token, int, int, char *);
#else /* ! __STDC__ */
extern void MACRetTok();
#endif /* ! __STDC__ */

#ifdef __STDC__
extern void MACRetInt(Token, int);
#else /* ! __STDC__ */
extern void MACRetInt();
#endif /* ! __STDC__ */

#ifdef __STDC__
extern void MACRetId(Token, int);
#else /* ! __STDC__ */
extern void MACRetId();
#endif /* ! __STDC__ */

#ifdef __STDC__
extern void MACRetProcessedString(Token, int, char *);
#else /* ! __STDC__ */
extern void MACRetProcessedString();
#endif /* ! __STDC__ */

#ifdef __STDC__
extern void MACRetString(Token, int);
#else /* ! __STDC__ */
extern void MACRetString();
#endif /* ! __STDC__ */

#ifdef __STDC__
extern void MACInitMugActions(void);
#else /* ! __STDC__ */
extern void MACInitMugActions()
#endif /* ! __STDC__ */

#ifdef __STDC__
extern void MACExitMugActions(void);
#else /* ! __STDC__ */
extern void MACExitMugActions();
#endif /* ! __STDC__ */

