/*********************************************
* Include fuer Buffer.c                      *
* version 22/1/91/FrEi                       *
*********************************************/                                                 
                                                                        
#define BUFFER_LAENGE 127
#define MAXSTRING 128
#define MAXTOKLENGTH 5000
#define FNLENGTH 128
#define MAXINCLUDE 10
#define EOF_CHAR ((char)-1)
#define EOLN_CHAR ((char)10)
#define EOTOK_CHAR ((char)0)
#define MAXINT 32767

struct tokenstring {
               short length;
               char body[MAXTOKLENGTH];
                   };
/*struct varfilestring {
               short length;
               char body[MAXSTRING];
                     }; */
typedef char filestring[MAXSTRING];

#define TOKMAX 10000

void BUFOpen_Buffer();
#ifdef __STDC__
int  BUFClose_Buffer(void);
char BUFGet_Next_Char(void);
void BUFSet_Buffer_Start(void);
void BUFSet_Token_End(void);
#else /* ! __STDC__ */
int  BUFClose_Buffer();
char BUFGet_Next_Char();
void BUFSet_Buffer_Start();
void BUFSet_Token_End();
#endif /* ! __STDC__ */
char BUFCget_Token_Char();
char BUFGet_First_Token_Char();
char BUFUFgetUc_first_token_char();
char BUFUcgetUc_token_char();
void BUFSget_Token(/* struct tokenstring *Token */);
void BUFUsgetUc_Token(/* struct tokenstring *Token */);
int  BUFLget_Token_length();
void BUFPget_Token_Position();
#ifdef __STDC__
void BUFInitBuffer(void);
void BUFExitBuffer(void);
#else /* ! __STDC__ */
void BUFInitBuffer();
void BUFExitBuffer();
#endif /* ! __STDC__ */
