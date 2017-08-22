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
#define MaxState      1900
#define MaxEvent      255          /* Maximale Anzahl der Ereignisse */
#define MinEvent      0            /* im Pas.Quelltxt als char */
#define MaxAction     100
#define NoAction      0
#define MaxString     128
#define maxint        32255


#define MaxKomprState 1000         /* Maximale Anzahl der Zustaende in der
                                      komprimierten Tabelle */
#define MaxClasses    255	   /* Maximale Anzahl der Klassen fuer
                                      Eingabezeichen.
				      wird der Wert erhoeht, muss
				      BsCountKanten in Compress angepasst
				      werden */
#define MaxKomprKanten 10000	   /* Max. Anz. Kanten in kompr. Tab. */
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


typedef KantenMenge UebergangsTabelle[MaxState+1];


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
                KomprState   Default[MaxKomprState+1];
	        int          Base[MaxKomprState+1];
		             /* -maxClasses..maxKomprKanten */
		int          Next[MaxKomprKanten+1];
		             /* -1..maxKomprState */
		KomprState   Check[MaxKomprKanten+1];
		Action       Actions[MaxKomprState+1];
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
typedef KomprState CoStateTable[MaxState+1];
typedef struct CoFreeChainElement  {
                int                       Offset;   /* -1..maxKomprKanten */
		struct CoFreeChainElement *Nachfolger;
	      } *CoFreeChainType;


/* ***************************************************************** */

  /* In Mudul Minimierer verwendete Strukturen */

typedef EventMge MinStack[MaxState+1];
    /* Stack fuer noch unerledigte Partitionskomponenten */

typedef struct BackEdge  {
                Event            Ereignis;
		StateSet         Urbild;
		struct BackEdge *Nachfolger;
	      } *BackEdgeSet;
    /* Umkehrfunktion */

typedef BackEdgeSet DeltaMinus[MaxState+1];

typedef StateSet Partition[MaxState+1];
    /* Beschreibung der Partition */

typedef Status ZugArray[MaxState+1];
    /* Zugehoerigkeit von Zustand zu Partitionskomponente */

typedef int ElemCount[MaxState+1];
    /* Information, wieviele Elemente jede Partitionskomponente enthaelt */

typedef int CompOnStackCount[MaxState+1];
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








