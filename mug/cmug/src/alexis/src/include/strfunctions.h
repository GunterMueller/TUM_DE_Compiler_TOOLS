/****************************************************
* Forward Deklarationen fuer strfunctions           *
****************************************************/
/* type ActionString = varying [MaxTokLength] of char;
     varfilestring = varying [128] of char; */
struct ActionString {
            short length;
            char body[MAXTOKLENGTH]; };
struct varfilestring {
            short length;
            char body[128] ; };
#ifdef __STDC__
void STRdelete(struct ActionString *,int,int );
void STRdeletefstr(struct varfilestring *,int,int );
int  STRindexx(struct ActionString *,struct varfilestring *);
void STRinttostring(int,struct varfilestring *);
void STRssubstring(struct ActionString *,struct ActionString *,int,int);
void STRstrinsert(struct ActionString *,int,struct varfilestring *);
int  STRstrcontains(struct ActionString *,struct varfilestring *,int *);
void STRrepinstring(struct varfilestring *,int,struct ActionString *);
#else
void STRdelete(/* astring,pos,len */);
void STRdeletefstr(/*astring,pos,len */);
int  STRindexx(/* astring,search */);
void STRinttostring(/* rein,raus */);
void STRssubstring(/* ergebnis,instring,offset,count */);
void STRstrinsert(/* InString,pos,InsString */);
int  STRstrcontains(/* InString,search,position */);
void STRrepinstring(/* InString,instead,progstring */);
#endif
