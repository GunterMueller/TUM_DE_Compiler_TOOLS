/*******************************************************************/
/*                                                                 */
/*   Technische Universitaet Muenchen, Institut fuer Informatik    */
/*                 Lehrstuhl Prof. Dr. J. Eickel                   */
/*                                                                 */
/*                                                                 */
/*     AAA     L         EEEEEEEE    XX     XX    III    SSSSS     */
/*    A   A    L         E            X     X      I    S     S    */
/*   A     A   L         E             X   X       I    S          */
/*   AAAAAAA   L         EEEEEE         XXX        I     SSSSS     */
/*   A     A   L         E             X   X       I          S    */
/*   A     A   L         E            X     X      I    S     S    */
/*   A     A   LLLLLLL   EEEEEEEE    XX     XX    III    SSSSS     */
/*                                                                 */
/*      Advanced LEXical Instrument for Scannergeneration          */
/*                                                                 */
/*                                                                 */
/*******************************************************************/
/*                                                                 */
/*  Projekt: ALEXIS  V 2.0                                         */
/*                                                                 */
/*  Autoren: Bernhard Smith, Frank Eiberle                         */
/*                                                                 */
/*  Copyright: Technische Universitaet Muenchen,                   */
/*             Institut fuer Informatik                            */
/*                                                                 */
/*  Segment: cymtab.c                                              */
/*  Version: 27/06/91                                              */
/*                                                                 */
/*  Sprache: C                                                     */
/*                                                                 */
/*-----------------------------------------------------------------*/
/*                                                                 */
/*  Beschreibung:                                                  */
/*    Dieses Segment realisiert eine Hashtabelle fuer den ALEXIS-  */
/*    Scanner. Es enthaelt Routinen, um Eintraege entweder noch    */
/*    ihrem Text oder nach dem Klassen- und Relativcode zu finden, */
/*    neue Token in die Symboltabelle einzutragen und Eintraege    */
/*    je nach Typ mit fortlaufenden Nummern zu versehen.           */
/*                                                                 */
/*  Inhalt:                                                        */
/*                                                                 */
/*      I. Lokale Routinen:                                        */
/*           IdHash                                                */
/*           NumHash                                               */
/*           procedure int_install_entry                           */
/*                                                                 */
/*                                                                 */
/*     II. Globale Routinen                                        */
/*           procedure install_entry                               */
/*           function  get_id_number                               */
/*                                                                 */
/*-----------------------------------------------------------------*/
/*                                                                 */
/*                 M O D I F I K A T I O N E N                     */
/*=================================================================*/
/* Datum      modifiziert von    Beschreibung der Modifikation     */
/*=================================================================*/
/*                                                                 */
/*                                                                 */
/*******************************************************************/


/*#define DEBUG*/

#ifdef __STDC__
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#endif

#include <stdio.h>
#include "global.h"
#include "symtab.h"

#include "alexmem.h"

/* Bauernfeind: 17.06.93; Globale Variablen aus var.c */
extern int MaxState;
extern int MaxAction;
extern int MAX_ID_NO;
extern MakroTable MakTable;


#define VERSION "Version 27.06.1991/1"


#define HASH_LENGTH 2053
#define MAXNUM 314159l
#define spunused NULL
#define unused 2


/* Bauernfeind: Prototypen, 8.6.93 */
extern void *realloc();
#ifdef __STDC__
extern void MEMugFatalError(int);
#endif


struct NumHash { char *token;
                 int rel;
                 int class;
                 struct NumHash *next;
               } *NumHashTab[HASH_LENGTH];

 

struct IdHash { struct NumHash *descr;
                struct IdHash *next;
              } *IdHashTab[HASH_LENGTH];
 


static int HashFactor[]={41,36,31,23,19,3,5,17,29};


static int NextRel[ENTRY_TYPES];


/*******************************************************************/
/*                                                                 */
/*  Lokale Funktion IdHash            Version: 27/06/91 BeSm       */
/*                                                                 */
/*******************************************************************/
/*                                                                 */
/*  Funktionsbeschreibung:                                         */
/*     Realisierung einer Hash-Funktion, die einem C-String einen  */
/*     Hashindex zuordnet.                                         */
/*                                                                 */
/*-----------------------------------------------------------------*/
/*                                                                 */
/*  Eingabeparameter:                                              */
/*     char *Token            - C-String                           */
/*                                                                 */
/*  Ausgabeparameter:                                              */
/*                                                                 */
/*  Rueckgabewert:                                                 */
/*     int                    - Hashindex                          */
/*                                                                 */
/*******************************************************************/

#ifdef __STDC__
static int IdHash(char *Token)
{ int i,erg,len;
#else /* ! __STDC__ */
static int IdHash( Token )
char *Token;
  { int i,erg,len;
#endif /* ! __STDC__ */
    char *first,*middle,*tail;

    erg=0;
    len=strlen(Token);
    first=Token;
    tail=Token+len-3;
    middle=Token+(len>>1)-2;
    switch( len )
      {
      case 0:
      case 1:
      case 2:
        for(i=0;i<len ;i++)
          { erg=(erg+HashFactor[i]*first[i]) % HASH_LENGTH;
          }
        break;
      case 3:
      case 4:
      case 5:
        for(i=0;i<3;i++)
          { erg=(erg+HashFactor[i]*first[i]+
                 HashFactor[i+6]*tail[i]) % HASH_LENGTH;
          }
        break;
      default:
        for(i=0;i<3;i++)
          { erg=(erg+HashFactor[i]*first[i]+
                 HashFactor[i+3]*middle[i]+
                 HashFactor[i+6]*tail[i]) % HASH_LENGTH;
          }
        break;
      }
    return erg;
  }
 

/*******************************************************************/
/*                                                                 */
/*  Lokale Funktion NumHash           Version: 20/05/91            */
/*                                                                 */
/*******************************************************************/
/*                                                                 */
/*  Funktionsbeschreibung:                                         */
/*     Diese Funktion berechnet aus dem Klassen- und dem Relativ-  */
/*     code eines Tokens den Hashindex fuer numb_hash_tab. Der     */
/*     Index wird als Linearkombination aus dem Klassen- und       */
/*     Relativcode gebildet, wobei die Faktoren so gewaehlt wurden,*/
/*     dass moeglichst wenige Kollisionen auftreten.               */
/*                                                                 */
/*-----------------------------------------------------------------*/
/*                                                                 */
/*  Eingabeparameter:                                              */
/*     int Class                  - Klassencode                    */
/*     int Rel                    - Relativcode                    */
/*                                                                 */
/*  Ausgabeparameter:                                              */
/*                                                                 */
/*  Rueckgabewert:                                                 */
/*     int                        - Hashindex                      */
/*                                                                 */
/*******************************************************************/

#ifdef __STDC__
static int NumHash(int class, int rel)
{ int erg;
#else /* ! __STDC__ */
static int NumHash(class,rel)
int class,rel;
  { int erg;
#endif /* ! __STDC__ */

    erg= ( (class %(MAXNUM/41))*41 +
           (rel%(MAXNUM/3))*3 ) % HASH_LENGTH;

    return erg;
  }


/*******************************************************************/
/*                                                                 */
/*  Lokale Funktion IntInstEntry      Version: 27/06/91            */
/*                                                                 */
/*******************************************************************/
/*                                                                 */
/*  Funktionsbeschreibung:                                         */
/*     Diese Prozedur traegt ein Element, das durch Klassencode,   */
/*     Relativcode und Tokentext spezifiziert ist, in die          */
/*     NumHashTab ein. Der Aufrufer erhaelt einen Zeiger in die    */
/*     NumHashTab.                                                 */
/*                                                                 */
/*-----------------------------------------------------------------*/
/*                                                                 */
/*  Eingabeparameter:                                              */
/*     IeString: string(MaxTokLength); Text des Tokens, das ab-    */
/*        speichert werden soll.                                   */
/*     IeType: entry_type; Art des Tokens, das abgespeichert       */
/*        werden soll. Dieser Parameter wird lediglich abgespei-   */
/*        chert und erst bei der Suche nach dem Token ueberprueft. */
/*     IeClass: integer32; Klassencode des Tokens, das abgespeichert */
/*        werden soll. Er dient auch zur Berechnung des Hashindex  */
/*     IeRel: integer32; Relativcode des Tokens, das abgespeichert   */
/*        werden soll. Er dient auch zur Berechnung des Hashindex  */
/*                                                                 */
/*  Ausgabeparameter:                                              */
/*     IePtr: num_hash_list_type; Pointer auf den Eintrag          */
/*                                                                 */
/*                                                                 */
/*                                                                 */
/*******************************************************************/

#ifdef __STDC__
static struct NumHash *IntInstEntry(char *Token, int Class, int Rel)
{ int hashnum;
#else /* ! __STDC__ */
static struct NumHash *IntInstEntry( Token,Class,Rel )
char *Token;
int Class,Rel;
  { int hashnum;
#endif /* ! __STDC__ */
    struct NumHash *list;
    int size;
	    
    hashnum=NumHash(Class,Rel);
    size=strlen(Token)+1;
    list= (struct NumHash *)MEMAlloc(sizeof(*list));

    list->token=(char *)MEMAlloc(size);
    strcpy( list->token,Token );

    list->rel=Rel;
    list->class=Class;

    list->next=NumHashTab[hashnum];
    NumHashTab[hashnum]=list;

    return list;
  }


/*******************************************************************/
/*                                                                 */
/*  Prozedur: SYInstallEntry          Version: 20/05/91            */
/*                                                                 */
/*******************************************************************/
/*                                                                 */
/*  Klassifizierung: globale Prozedur                              */
/*                                                                 */
/*  Funktionsbeschreibung:                                         */
/*     Diese Prozedur dient externen Routinen zum Eintrag von      */
/*     Token, die spaeter nur ueber Klassen- und Relativcode       */
/*     aufgerufen werden sollen. Sie wird typischer Weise fuer     */
/*     Token verwendet, bei denen der Tokentext bereits direkt     */
/*     aus Klassen- und Relativcode hervorgeht, also zum Beispiel  */
/*     bei Schluesselwoertern. Bevor diese Routine aufgerufen      */
/*     wird, muss mit der Funktion test_entry sichergestellt sein, */
/*     dass dieses Token noch nicht eingetragen wurde.             */
/*                                                                 */
/*        Diese Prozedur ist bis auf die Parametrisierung identisch*/
/*     mit int_install_entry, sie dient lediglich zur Abschirmung  */
/*     von extern nicht relevanten Informationen, wie dem Pointer  */
/*     auf den Eintrag.                                            */
/*                                                                 */
/*-----------------------------------------------------------------*/
/*                                                                 */
/*  Eingabeparameter:                                              */
/*     IeString: string(MaxTokLength); Text des Tokens, das ab-    */
/*        speichert werden soll.                                   */
/*     IeType: entry_type; Art des Tokens, das abgespeichert       */
/*        werden soll. Dieser Parameter wird lediglich abgespei-   */
/*        chert und erst bei der Suche nach dem Token ueberprueft. */
/*     IeClass: integer32; Klassencode des Tokens, das abgespeichert */
/*        werden soll.                                             */
/*     IeRel: integer32; Relativcode des Tokens, das abgespeichert   */
/*        werden soll.                                             */
/*                                                                 */
/*  Seiteneffekte:                                                 */
/*     siehe int_install_entry                                     */
/*                                                                 */
/*-----------------------------------------------------------------*/
/*                                                                 */
/*  Lokale Variablen:                                              */
/*     IeDummy: num_hash_list_type; Dummy-Parameter zur Befriedi-  */
/*        gung der Aufrufschnittstelle von int_install_entry.      */
/*        Dieser Variablen kommt lediglich syntaktische Bedeutung  */
/*        zu.                                                      */
/*                                                                 */
/*******************************************************************/


#ifdef __STDC__
void SYInstallEntry(char *Token, int Class, int Rel)
{ 
#else /* ! __STDC__ */
void SYInstallEntry(Token,Class,Rel)
char *Token;
int Class,Rel;
  { 
#endif /* ! __STDC__ */
    (int)IntInstEntry(Token,Class,Rel);

  }


/*******************************************************************/
/*                                                                 */
/*  Prozedur: SYGetIdNumber           Version: 20/05/91            */
/*                                                                 */
/*******************************************************************/
/*                                                                 */
/*  Klassifizierung: globale Funktion                              */
/*                                                                 */
/*  Funktionsbeschreibung:                                         */
/*     Diese Funktion sucht in der Symboltabelle nach einem Token  */
/*     mit dem gleichen Tokentext, der gleichen Tokenklasse und    */
/*     dem gleichen Klassencode, wie das uebergebene Token. Wird   */
/*     ein solches Token gefunden, so gibt die Funktion den abge-  */
/*     speicherten Relativcode des Tokens (die Id-Nummer) als      */
/*     Ergebnis zurueck. Wird der Eintrag nicht gefunden, so wird  */
/*     zu dem uebergebenen Tokentyp die naechste freie Id-Nummer   */
/*     berechnet und das Token mit dieser Nummer als Relativcode   */
/*     in beide Hashtabellen eingetragen. Der Relativcode ist      */
/*     dann ebenfalls das Funktionsergebnis.                       */
/*        Nach Aufruf dieser Funktion ist das Token sowohl ueber   */
/*     seinen Text als auch ueber Klassen- und Relativcode erreich-*/
/*     bar.                                                        */
/*                                                                 */
/*        Diese Funktion bildet zunaechst mit der Funktion id_hash */
/*     den Hashindex fuer die id_hash_tab und sucht die so festge- */
/*     legte Liste nach dem uebergebenen Eintrag durch. Wird der   */
/*     Eintrag nicht gefunden, so wird eine neue Id_number gene-   */
/*     riert und mit dieser die Routine int_install_entry aufge-   */
/*     rufen. Mit Hilfe des zurueckgelieferten Pointers wird dann  */
/*     das Token noch in die id_hash_tab eingetragen.              */
/*        Ist kein Relativcode mehr verfuegbar so wird der         */
/*     MUG Fatal Error #3 ausgeloest und der Scannlauf abgebrochen.*/
/*                                                                 */
/*-----------------------------------------------------------------*/
/*                                                                 */
/*  Eingabeparameter:                                              */
/*     GnToken : string(MaxTokLength); Text des Tokens             */
/*     GnType: entry_type; Art des Tokens                          */
/*     GnClass: integer32; Klassencode, mit dem das Token abgespei-  */
/*        chert werden soll.                                       */
/*                                                                 */
/*  Ausgabeparameter:                                              */
/*     Ergebnis: id_numb_type; Relativcode des Tokens. War das     */
/*        Token bereits in der Symboltabelle enthalten, so wird    */
/*        der gespeicherte Wert zurueckgegeben, sonst ein neu      */
/*        generierter.                                             */
/*                                                                 */
/*  Seiteneffekte:                                                 */
/*     id_hash_tab wird veraendert                                 */
/*     next_numbers[GnType] wird moeglicherweise inkrementiert     */
/*     weitere Seiteneffekte siehe int_install_entry               */
/*                                                                 */
/*-----------------------------------------------------------------*/
/*                                                                 */
/*  Lokale Variablen:                                              */
/*     GnIndex: hash_number; Index des Tokens in der id_hash_tab,  */
/*        berechnet ueber id_hash                                  */
/*     GnCont: boolean; Flag, ob die Liste der Eintraege unter     */
/*        id_hash_tab(.GnCont.) weiter durchsucht werden muss      */
/*        (TRUE) oder das Token bereits gefunden wurde (FALSE)     */
/*     GnListPtr: id_hash_list_type; Pointer auf das naechste      */
/*        zu ueberpruefende Element in der id_hash_list            */
/*     GnNumListPtr: num_hash_list_type; Pointer auf den durch     */
/*        int_install_entry generierten Eintrag.                   */
/*     erg: id_numb_type; Relativcode des Tokens, wird als         */
/*        Funktionsergebnis zurueckgegeben                         */
/*                                                                 */
/*******************************************************************/



 
#ifdef __STDC__
int SYGetIdNumber(char *Token, int Typ, int Class)
{ int idhash;
#else /* ! __STDC__ */
int SYGetIdNumber(Token,Typ,Class)
char *Token;
int Typ,Class;
  { int idhash;
#endif /* ! __STDC__ */
    struct IdHash *idlist;
    int erg;
    int lauf;

    idhash=IdHash(Token);
    idlist=IdHashTab[idhash];
    while( idlist!=NULL && ( idlist->descr->class!=Class || 
                             strcmp(idlist->descr->token,Token)!=0 ) )
      { idlist=idlist->next;
      }
    if( idlist==NULL)
      { if((erg=NextRel[Typ]++)==MAX_ID_NO )
          { 
/* Bauernfeind: 15.06.93; Reallokation von MakTable */
/*            MEMugFatalError(3); */
            MakTable = realloc(MakTable,(2*MAX_ID_NO+1)*sizeof(struct MakTabEntry));
            for(lauf=MAX_ID_NO+1;lauf<=2*MAX_ID_NO;MakTable[lauf++].MakArt=unused);
            MAX_ID_NO += MAX_ID_NO;
          }

        idlist=(struct IdHash *)MEMAlloc(sizeof(struct IdHash));
        idlist->descr=IntInstEntry(Token,Class,erg);
        idlist->next=IdHashTab[idhash];
        IdHashTab[idhash]=idlist;
      }
 /*   printf("IdNum(%s)=%d\n",Token,idlist->descr->rel);*/

    return idlist->descr->rel;
  }


/*******************************************************************/
/*                                                                 */
/*  Prozedur: SYDecSymtab             Version: 20/05/91            */
/*                                                                 */
/*******************************************************************/
/*                                                                 */
/*  Klassifizierung: globale Funktion                              */
/*                                                                 */
/*  Funktionsbeschreibung:                                         */
/*     Diese Funktion sucht in der Symboltabelle nach einem Token, */
/*     das durch Klassen- und Relativcode spezifiziert ist. wurde  */
/*     das Token gefunden, so wird dessen Text zurueckgegeben,     */
/*     sonst der String '--- Fehler ---'.                          */
/*                                                                 */
/*        Diese Funktion generiert zunaechst mit Hilfe von num_hash*/
/*     den Hashindex des Tokens und sucht dann die so gefundene    */
/*     Liste nach dem Token durch. Anschliessend wird das Funk-    */
/*     tionsergbenis entsprechend besetzt.                         */
/*                                                                 */
/*-----------------------------------------------------------------*/
/*                                                                 */
/*  Eingabeparameter:                                              */
/*     DcClass: integer32; Klassencode des Tokens, nach dem gesucht  */
/*        werden soll.                                             */
/*     DcRelCode: id_numb_type: Relativcode, nach dem gesucht      */
/*        werden soll.                                             */
/*                                                                 */
/*  Ausgabeparameter:                                              */
/*     Ergebnis: string(MaxTokLength); Der Text des Tokens, wenn   */
/*        dieses gefunden wurde, sonst der String '--- Fehler ---' */
/*                                                                 */
/*-----------------------------------------------------------------*/
/*                                                                 */
/*  Lokale Variablen:                                              */
/*     DcPtr: num_hash_list_type: Pointer auf den Eintrag, der als */
/*        naechstes ueberprueft werden soll                        */
/*     DcCont: boolean; Flag, ob weiter gesucht werden muss (TRUE) */
/*        oder der Eintrag bereits gefunden wurde (FALSE)          */
/*                                                                 */
/*******************************************************************/


#ifdef __STDC__
char *SYDecSymtab(int Class, int Rel)
{ struct NumHash *numlist;
#else /* ! __STDC__ */
char *SYDecSymtab(Class,Rel)
int Class,Rel;
  { struct NumHash *numlist;
#endif /* ! __STDC__ */
 
    numlist=NumHashTab[NumHash(Class,Rel)];
    while( numlist!=NULL && ( numlist->class!=Class ||
                              numlist->rel!=Rel ) )
      { numlist=numlist->next;
      }
    if( numlist==NULL )
      { 
        return "---- Fehler ----";
      }

    return numlist->token;
  }


/*******************************************************************/
/*                                                                 */
/*  Prozedur: SYTestEntry             Version: 20/05/91            */
/*                                                                 */
/*******************************************************************/
/*                                                                 */
/*  Klassifizierung: globale Funktion                              */
/*                                                                 */
/*  Funktionsbeschreibung:                                         */
/*     Diese Funktion ueberprueft, ob ein Token, das durch Klassen-*/
/*     und Relativcode spezifiziert ist, bereits eingetragen ist.  */
/*     Faellt der Test positiv aus, so wird TRUE zurueckgegeben,   */
/*     sonst FALSE. Die Tokenart wird dabei ebenfalls beruecksich- */
/*     tigt.                                                       */
/*        Die Ueberpruefung findet mit Hilfe der num_hash_tab      */
/*     statt.                                                      */
/*                                                                 */
/*-----------------------------------------------------------------*/
/*                                                                 */
/*  Eingabeparameter:                                              */
/*     TeType: entry_type; Typ des Tokens, das gesucht wird        */
/*     TeClass: integer32; Klassencode                               */
/*     TeRel: integer32;   Relativcode                               */
/*                                                                 */
/*  Ausgabeparameter:                                              */
/*     Ergebnis: boolean; TRUE -^ Eintrag ist bereits vorhanden   */
/*                        FALSE -^ Eintrag ist noch nicht vorhan- */
/*                                  den.                           */
/*                                                                 */
/*-----------------------------------------------------------------*/
/*                                                                 */
/*  Lokale Variablen:                                              */
/*     TePtr: num_hash_list_type; Pointer auf das naechste zu      */
/*        pruefende Element                                        */
/*     TeCont: boolean; Flag, ob weiter gesucht werden muss (TRUE) */
/*        oder das Element bereits gefunden wurde (FALSE)          */
/*                                                                 */
/*******************************************************************/




#ifdef __STDC__
int SYTestEntry(int Class, int Rel)
{ struct NumHash *numlist;
#else /* ! __STDC__ */
int SYTestEntry(Class,Rel)
int Class,Rel;
  { struct NumHash *numlist;
#endif /* ! __STDC__ */
    
    numlist=NumHashTab[ NumHash(Class,Rel) ];

    while( numlist!=NULL && ( numlist->class!=Class ||
                              numlist->rel!=Rel ))
      { numlist=numlist->next;
      }

    return numlist!=NULL;
  }



#ifdef __STDC__
void SYSetInvalid(int Class, int Rel)
{ struct NumHash *numlist;
#else /* ! __STDC__ */
void SYSetInvalid(Class,Rel)
int Class,Rel;
  { struct NumHash *numlist;
#endif /* ! __STDC__ */

    numlist=NumHashTab[ NumHash(Class,Rel) ];

    while( numlist!=NULL && ( numlist->class!=Class ||
                              numlist->rel!=Rel ))
      { numlist=numlist->next;
      }

    if( numlist!=NULL )
      { 
      numlist->token[0]='\0';
      }
    else
      {
      IntInstEntry("",Class,Rel);
      }

  }



/*******************************************************************/
/*                                                                 */
/*  Prozedur: ExitSymTab              Version: 20/05/91            */
/*                                                                 */
/*******************************************************************/
/*                                                                 */
/*  Klassifizierung: globale Prozedur                              */
/*                                                                 */
/*  Funktionsbeschreibung:                                         */
/*     Diese Prozedur gibt den gesamten durch die Symboltabelle    */
/*     belegten Speicherplatz frei, nachdem die id_hash_tab be-    */
/*     reits mit der Funktion dispose_symtab freigegeben wurde.    */
/*                                                                 */
/*-----------------------------------------------------------------*/
/*                                                                 */
/*  Seiteneffekte:                                                 */
/*     Der Speicherplatz, der durch die Symboltabelleneintraege    */
/*     belegt wurde, wird freigegeben.                             */
/*                                                                 */
/*-----------------------------------------------------------------*/
/*                                                                 */
/*  Lokale Variablen:                                              */
/*     DsIndex: hash_number; Laufindex zum durchlaufen von         */
/*        num_hash_tab                                             */
/*     DsNumList: num_hash_list_type; Pointer auf das naechste     */
/*        zu loeschende Element                                    */
/*     DsHn: num_hash_list_type; Hilfspointer zum freigeben von    */
/*        Elementen                                                */
/*                                                                 */
/*******************************************************************/


#ifdef __STDC__
void SYExitSymtab(void)
{ int i;
#else /* ! __STDC__ */
void SYExitSymtab()
  { int i;
#endif /* ! __STDC__ */
    struct NumHash *numlist,*help;

    for(i=0;i<HASH_LENGTH;i++)
      { numlist=NumHashTab[i];
        while(numlist!=NULL)
          { help=numlist->next;
            MEMFree(numlist->token);
            MEMFree(numlist);
            numlist=help;
          }
        NumHashTab[i]=NULL;
        IdHashTab[i]=NULL;
      }

  }


/*******************************************************************/
/*                                                                 */
/*  Prozedur: InitSymtab              Version: 20/05/91            */
/*                                                                 */
/*******************************************************************/
/*                                                                 */
/*  Klassifizierung: globale Prozedur                              */
/*                                                                 */
/*  Funktionsbeschreibung:                                         */
/*     Diese Prozedur initialisiert die Symboltabelle. Im einzelnen*/
/*     werden dabei folgende Aktionen durchgefuehrt:               */
/*        I. Alle Elemente von next_numbers werden auf 1 gesetzt   */
/*       II. Alle Elemente von id_hash_tab werden auf NIL gesetzt  */
/*      III. Alle Elemente von num_hash_tab werden auf NIL gesetzt */
/*                                                                 */
/*-----------------------------------------------------------------*/
/*                                                                 */
/*  Seiteneffekte:                                                 */
/*     siehe Funktionsbeschreibung                                 */
/*                                                                 */
/*-----------------------------------------------------------------*/
/*                                                                 */
/*  Lokale Variablen:                                              */
/*     IsEntry_type: entry_type; Laufindex fuer next_numbers       */
/*     index: hash_number; Laufindex fuer id_hash_tab und          */
/*        num_hash_tab                                             */
/*                                                                 */
/*******************************************************************/

#ifdef __STDC__
void SYInitSymtab(void)
{ int i;
#else /* ! __STDC__ */
void SYInitSymtab()
  { int i;
#endif /* ! __STDC__ */

    for(i=0;i<ENTRY_TYPES;i++)
      { NextRel[i]=1;
      }
    for(i=0;i<HASH_LENGTH;i++)
      { NumHashTab[i]=NULL;
        IdHashTab[i]=NULL;
      }
  }
