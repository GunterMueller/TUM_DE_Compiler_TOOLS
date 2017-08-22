
#ifndef __SYMTAB_H__
#define __SYMTAB_H__

/* #define	MAX_ID_NO	1024
Bauernfeind, statisch->dynamisch, 14.06.93 
jetzt als Variable in var.c */

#define	ENTRY_TYPES	10

#define	TYP_ID		0
#define	TYP_STR		1
#define TYP_NUM		2
#define TYP_KEY		3


#ifdef __STDC__
void 	SYInstallEntry(char *, int, int );
int 	SYTestEntry(int, int);
int 	SYGetIdNumber(char *, int, int );
char *	SYDecSymtab(int , int );
#else /* ! __STDC__ */
void 	SYInstallEntry(/* char *Token, int Class, int Rel */);
int 	SYTestEntry(/* int Class, int Rel */);
int 	SYGetIdNumber(/* char *Token, int Typ, int Class */);
char *	SYDecSymtab(/* int Class, int Rel */);
#endif /* ! __STDC__ */

#ifdef __STDC__
void 	SYSetInvalid(int, int );
#else /* ! __STDC__ */
void 	SYSetInvalid(/* int Class, int Rel */);
#endif /* ! __STDC__ */

#ifdef __STDC__
void 	SYInitSymtab(void);
void 	SYExitSymtab(void);
#else /* ! __STDC__ */
void 	SYInitSymtab(/* void */);
void 	SYExitSymtab(/* void */);
#endif /* ! __STDC__ */

#endif
