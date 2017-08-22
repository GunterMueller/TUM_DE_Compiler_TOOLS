#define spunused NULL
#define IdentCC  12
#define ProgCC   27
#define StrCC    32
                    
/* -----------------------------------------------------------          
       Typdeklarationen und Variable                                    
       fuer die Makrotafeln                                             
   -----------------------------------------------------------  */      

typedef int partype[10];
typedef struct varfilestring parstrings[10];
/*struct actionstring {
           short length;
           char  body[MAXTOKLENGTH]; } ;*/
struct ActTbEintr {
           int ignore,makro,strnumber,maknumber;
           partype parameters;  } ;
/* typedef int MakType; */
#define lexmak 0
#define actmak 1
#define unused 2
/* struct MakTabEntry {
            MakType MakArt;
            Automat MakAutomat;
            int MakString,MakParCount; } ; */

/* Bauernfeind: 17.06.93; statisch->dynamisch */
/* struct MakTabEntry jetzt in global.h */
/* typedefs  jetzt in global.h: MakroTable, MakType */
/* Variablen in var.c: MakTable */
/* typedef struct MakTabEntry MakroTable[MAX_ID_NO+1]; */
/* struct ActTbEintr ActTable[MaxAction+1]; */
struct ActTbEintr *ActTable; 
/* MakroTable MakTable; */
int Actnumber;

                  

/*
{  -----------------------------------------------------------          
       Typdeklarationen und Variable                                    
       fuer spezielle Aktionen                                          
   ----------------------------------------------------------- */       

typedef int SpecType;
#define spextern 0
#define spscaninit 1
#define spscanexit 2
#define spscanerror 3                                                                        

typedef struct SpecLElem {
                  int ElemStr;
                  struct SpecLElem *ElemNachfolger;
                         } *SpecLPoint;
typedef SpecLPoint SpecTable[4];

SpecTable SpecActions;
