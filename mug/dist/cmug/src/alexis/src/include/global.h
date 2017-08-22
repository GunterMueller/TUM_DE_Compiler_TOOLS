#define public
#define private       static

#if                   __STDC__
#define P_(a)         a
#else
#define P_(a)         ()
#endif



#define EmptyStateSet (StateSet)NULL
#define EmptyQuickSet (QuickSet)NULL
#define EmptyEventMge (EventMge)NULL
#define MyHashLength  1013         /* fuer Myhill-Funktion */

/* Bauernfeind: 17.06.93; MaxState, MaxAction, MaxKomprState einkommentiert */
/*              sind jetzt als Variablen in .../alexis/src/var.c deklariert */
/*              (und MaxKomprKanten)                                        */
/* #define MaxState      5000 */
#define MaxEvent      255          /* Maximale Anzahl der Ereignisse */
#define MinEvent      0            /* im Pas.Quelltxt als char */
/* #define MaxAction     200 */
#define NoAction      0
#define MaxString     128
#define maxint        32255


/* #define MaxKomprState 1500 */        /* Maximale Anzahl der Zustaende in der
                                      komprimierten Tabelle */
#define MaxClasses    255	   /* Maximale Anzahl der Klassen fuer
                                      Eingabezeichen.
				      wird der Wert erhoeht, muss
				      BsCountKanten in Compress angepasst
				      werden */
/* #define MaxKomprKanten 10000	*/   /* Max. Anz. Kanten in kompr. Tab. */
#define CsHashLength   256         /* MaxEvent+1 */



#define ignorecase    0
#define minimal       1

/* ***************************************************************** */

typedef unsigned char Event;
typedef int Status;                /* Status = 0 .. MaxState */
typedef unsigned int MyHash;       /* MyHash = 0 .. MyHashLength-1 */
typedef int Action;                /* Action = 0 .. MaxAction */

typedef int Classes;		   /* 0..MaxClasses */
typedef int KomprState;		   /* 0..MaxKomprState */
typedef int KomprKante;		   /* 0..MaxKomprKanten */
typedef int CsHashIndex;           /* 0..CsHashLength-1 */

/* ***************************************************************** */


typedef struct  EvSet  {
                  Event Set[MaxEvent+1];
                  int   Length;              /* Anzahl der Elemente */
                } *EventSet,*Class;
	

/* ***************************************************************** */

typedef struct StateEl  {
                  Status         State;
                  struct StateEl *Nachfolger;
                } *StateSet,*QuickSet;


/* ***************************************************************** */

typedef struct Eventmenge {
                  Event             Even;
		  struct Eventmenge *Nachfolger;
		} *EventMge;


/* ***************************************************************** */

typedef struct AutomatenDescr  {
                  Status   StartZustand;
                  StateSet EndZustaende;
                  StateSet BelegteZustaende;
                } *Automat;


/* ***************************************************************** */


typedef struct StackEl  {
                  Automat        Inhalt;
                  struct StackEl *NextEl;
                } *StackTyp;


/* ***************************************************************** */


typedef struct KantenEl  {
                  Event           Ereignis;
                  Status          FolgeZustand;
                  struct KantenEl *Nachfolger;
                } *KantenMenge;


/* ***************************************************************** */


typedef struct MyTableEl  {
                  Status           NewName;
                  StateSet         OldStates;
                  struct MyTableEl *HNachfolger;
                  struct MyTableEl *UNachfolger;
                } *MyTableList;

typedef MyTableList MyTableType[MyHashLength];


/* ***************************************************************** */


typedef struct EventStr  {
                 int      length;
                 Event    body[MaxString+1];
               } *EventString;


/* ***************************************************************** */


/* Bauernfeind: statisch->dynamisch: 14.06.93 */
/* typedef KantenMenge UebergangsTabelle[MaxState+1]; */
typedef KantenMenge *UebergangsTabelle; 
/* Zusaetzlich statt in genactio.h: MakType, MakTabEntry, MakroTable */
typedef int MakType; 
struct MakTabEntry {
            MakType MakArt;
            Automat MakAutomat;
            int MakString,MakParCount; } ; 
typedef struct MakTabEntry *MakroTable;


/* ***************************************************************** */


typedef int instflags[7];


/* ***************************************************************** */

 /* in Modul Compress verwendete Strukturen: */

typedef struct ClassDs  {
                Classes   ClassNumber;
                Classes   EventTable[MaxEvent+1];
	      } *ClassDescr;
 /* obige Deklaration ist reichlich anders als im Pascal-Quelltext */
 /* als var-Parameter uebergebene ClassDescr sind nun EINFACHE Zeiger */

typedef struct KomprUeg  {
                KomprState   StateNumber;
                KomprKante   KantenNumber;
                Action       ActionNumber;
/* Bauernfeind: statisch->dynamisch: 14.06.93 */
/*              KomprState   Default[MaxKomprState+1];  */
                KomprState   *Default;  
/* Bauernfeind: statisch->dynamisch: 14.06.93 */
/*	        int          Base[MaxKomprState+1];  */
	        int          *Base;  
		             /* -maxClasses..maxKomprKanten */
/* Bauernfeind: statisch->dynamisch: 14.06.93 */
/*		int          Next[MaxKomprKanten+1];  */
		int          *Next; 
		             /* -1..maxKomprState */
/* Bauernfeind: statisch->dynamisch: 14.06.93 */
/*		KomprState   Check[MaxKomprKanten+1]; */
		KomprState   *Check; 
/* Bauernfeind: statisch->dynamisch: 14.06.93 */
/*		Action       Actions[MaxKomprState+1]; */
		Action       *Actions; 
	      } *KomprUebergang;
 /* ClassDescr und KomprUebergang sind im Pascaltext die Strukturnamen, hier
    sind es Zeiger auf dieselben */

typedef struct CsClassTb  {
                Status       FolgeState;
		struct EvSet EventKlasse;
	      } CsClassTable[CsHashLength];

typedef struct EvSet ClassTableType[MaxClasses+1];
typedef struct EvSet EventTranslTable[MaxEvent+1];
typedef QuickSet StateLength[MaxClasses+1];


typedef int CoRohKante[MaxClasses+1]; /* -1..maxKomprState */
/* Bauernfeind: neue Struktur, um Komprimierung zu beschleunigen */
typedef struct _KompaktDiff {
                int        class_index;
                int        FolgeState;      /* -1..maxKomprState */
              } KompaktDiff[MaxClasses+1];

/* Bauernfeind: statisch->dynamisch: 14.06.93 */
/* typedef KomprState CoStateTable[MaxState+1]; */
typedef KomprState *CoStateTable; 
typedef struct CoFreeChainElement  {
                int                       Offset;   /* -1..maxKomprKanten */
		struct CoFreeChainElement *Nachfolger;
	      } *CoFreeChainType;


/* ***************************************************************** */

  /* In Mudul Minimierer verwendete Strukturen */

/* Bauernfeind: statisch->dynamisch: 14.06.93 */
/* typedef EventMge MinStack[MaxState+1]; */
typedef EventMge *MinStack;
    /* Stack fuer noch unerledigte Partitionskomponenten */

typedef struct BackEdge  {
                Event            Ereignis;
		StateSet         Urbild;
		struct BackEdge *Nachfolger;
	      } *BackEdgeSet;
    /* Umkehrfunktion */

/* Bauernfeind: statisch->dynamisch: 14.06.93 */
/* typedef BackEdgeSet DeltaMinus[MaxState+1]; */
typedef BackEdgeSet *DeltaMinus;

/* Bauernfeind: statisch->dynamisch: 14.06.93 */
/* typedef StateSet Partition[MaxState+1]; */
typedef StateSet *Partition;
    /* Beschreibung der Partition */

/* Bauernfeind: statisch->dynamisch: 14.06.93 */
/* typedef Status ZugArray[MaxState+1]; */
typedef Status *ZugArray;
    /* Zugehoerigkeit von Zustand zu Partitionskomponente */

/* Bauernfeind: statisch->dynamisch: 14.06.93 */
/* typedef int ElemCount[MaxState+1]; */
typedef int *ElemCount;
    /* Information, wieviele Elemente jede Partitionskomponente enthaelt */

/* Bauernfeind: statisch->dynamisch: 14.06.93 */
/* typedef int CompOnStackCount[MaxState+1]; */
typedef int *CompOnStackCount;
    /* Information, wieviele Kopien einer Komponente auf dem Stack liegen */


/* ***************************************************************** */
/* ***************************************************************** */


#ifndef __STDC__
extern void *malloc();
#endif


/* Funktionsdeklarationen von eigenen Funktionen, die einige Pascal-
   moeglichkeiten ersetzen */


void UnionEvSets P_((Class Erg,Class Set1,Class Set2));
void SchneideEvSets P_((Class Erg,Class Set1,Class Set2));
void MinusEvSets P_((Class Erg,Class Set1,Class Set2));
void CopyEvSets P_((Class Ziel,Class Quelle));
void PrintEvSet P_((Class Set));
int InEvSet P_((int InEvent,Class Set));
void InsertInEvSet P_((int InEvent,Class ISet));


