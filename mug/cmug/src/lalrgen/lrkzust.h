/*
 * (c) copyright 1989,1991 by Technische Universitaet Muenchen, Germany
 *
 *      This product is part of CMUG
 *      CMUG is a part of the compiler writing system
 *      MUG (Modularer Uebersetzer-Generator, TU Muenchen)
 *
 * Permission to use, duplicate or disclose this software must be
 * obtained in writing. Requests for such permissions may be sent to
 *
 *      Prof. Dr. J. Eickel
 *      Institut fuer Informatik
 *      Technische Universitaet Muenchen
 *      Postfach  20 24 20
 *      Arcisstr. 21
 *      D-8000 Muenchen 2
 *      Germany
 *
 * No version of this implementation may be used or distributed for gain,
 * all listings must contain our copyright notice, and the headings
 * produced by MUG-Modules must contain the text "MUG" and "TU - Muenchen".
 */


/* ********************************************************************** */
/* LRKzust.h   :                                                          */
/* LR(k)-Parser-Generator                                                 */
/* Deklarationen fuer die Zustandsverwaltung                              */
/* Aenderung  : 13.10.90 , Verwendung von incattr                         */
/* Aenderung  : 04.07.89, Informationen zur Ausgabe in Zustand            */
/* Aenderung  : 02.07.89, Verkettung ueber nextnont                       */
/* Aenderung  : 30.06.89, vollstaendig ueberarbeitet                      */
/* Aenderung  : 10.06.89, EPSRED-Uebergangstyp eliminiert                 */
/* Aenderung  : 25.5.89 , Verkettung Zustaende ueber erstes Item          */
/* erstellt   : 27.1.89                                                   */
/* ********************************************************************** */

#ifndef LRKZUST_H
#define LRKZUST_H
#ifdef INCATTR
#include "iadefs.h"
#include "iaattr.h"
#include "lrklook.h"
#endif
#include "listen.h"      /* Definitionen fuer Listentypen          */

/* ========================================================================= */
/* Datenstrukturen fuer den Typ Zustand                                      */
/* ========================================================================= */
typedef short Zustnr;     /* laufende Nummer eines Zustandes        */

/* Pseudozustandsnummer fuer reine REDUCE-Zustaende  */
#define UNDEFZUSTNR ((Zustnr)(-1))

 /* ---------------------------------------------------------------- */
 /* Diese Information dient dazu, bei rekursiven Durchlaeufen ueber  */
 /* den gesamten Automaten festzustellen, ob in einem bestimmten     */
 /* Lauf ein Uebergang bereits beruecksichtigt wurde (Terminierung)  */
 /* ---------------------------------------------------------------- */
typedef long Recinfo;

 /* -------------------------------------------------------------- */
 /* wird als allgemeiner Tabellenindex verwendet                   */
 /* -------------------------------------------------------------- */
typedef long Tabindex;

 /* -------------------------------------------------------------- */
 /* Position in der Grammatik als Element einer Menge von Items    */
 /* Position = SORTED LIST OF PosRec                               */
 /* -------------------------------------------------------------- */
typedef struct ZustR *Zustand;     /* Liste von Zustaenden                   */
typedef struct PosR *Position;        /* Liste von Positionen, s.u. */
typedef struct PosR{
                LISTENFELDER(Position) /* zur Verkettung            */
                Item      item;    /* Item der Position             */ 
#ifdef INCATTR
		Attribut  attr;       /* zugehoeriges Attribut      */
		Lookset   first;      /* Firstmenge                 */
		Lookset   first_look; /* Lookaheadmenge             */
		Zustand   zust;       /* umfassender Zustand        */
#endif
               } PosRec;

 /* -------------------------------------------------------------- */
 /* Zustand = Menge (implementiert als Liste) von Positionen       */
 /* SORTED LIST OF ZustRec                                         */
 /* -------------------------------------------------------------- */
 /* Listentyp                                                      */

 /* -------------------------------------------------------------- */
 /* Liste der Uebergaenge aus einem Zustand                        */
 /* Ueberg = SORTED LIST OF UebergRec                              */
 /* -------------------------------------------------------------- */	

 /* Art des Uebergangs */
typedef enum  { SHIFT,       /* Shift-Uebergang (bzw REDUCE)            */
                SPONTRED,    /* spontaner Reduce-Uebergang              */ 
                LOOK         /* weiterer Lookahead noetig               */
              } Uebart;

typedef struct UebergR *Ueberg;    /* Liste von Uebergaengen            */
  /* --------------------------------------------------- */
  /* vollstaendige Beschreibung eines Ueberganges        */
  /* --------------------------------------------------- */
typedef struct UebergR{
                LISTENFELDER(Ueberg)      /* zur Verkettung                   */
                Symb      sym;            /* gelesenes Symbol oder SPONTSYM   */
                Zustand   von;            /* Ausgangszustand des Uebergangs   */
                Uebart    art;            /* Art des Uebergangs               */
                Ueberg    nextshift;      /* naechster gleicher SHIFT         */
                Recinfo   inkarn;         /* Terminierungsinformation         */
                Ueberg    nextnont;       /* naechster mit diesem Nonterminal */
                union {                   /* je nach Uebergangsart            */
                       Zustand  szust;    /* SHIFT : Zielzustand              */
                       Item     ritem;    /* SPONTRED : reduz. item           */
                       Ueberg   looks;    /* LOOK  : Soehne                   */
                      } u;
               } UebergRec;

typedef struct ZustR{
                LISTENFELDER(Zustand) /* zur Verkettung                       */
                Zustand  nextinlis; /* weitere Zustaende zu gleichem Item     */
                Position firstpos;  /* Liste der Positionen zu diesem Zustand */
#ifdef INCATTR
                Position firstred;  /* Liste der Positionen zu diesem Zustand */
#endif
                Zustnr   znr;       /* Nummer des Zustandes, falls def.       */
                /* ------------------------------------------- */
                /* Uebergaenge dieses Zustandes                */
                /* ------------------------------------------- */
                Ueberg   termueb;   /* terminale Uebergaenge aus dem Zustand  */
                Ueberg   nontueb;   /* nonterminale Uebergaenge aus d. Zust.  */
                Ueberg   shifts;    /* alle SHIFT's in diesen Zustand         */
                Ueberg   epsueb;    /* spontane Uebergaenge aus dem Zustand   */
                /* ------------------------------------------- */
                /* Informationen fuer die auszugebende Tabelle */
                /* ------------------------------------------- */
                Item     ditem;     /* Item des Default-Uebergangs            */
                Tabindex tvon;      /* Startindex in terminalen Uebergaengen  */
                Tabindex tbis;      /* Endindex in terminalen Uebergaengen    */
               } ZustRec;

/* ----------------------------------------------- */
/* Definition der Uebergange mit einem Nonterminal */
/* ----------------------------------------------- */
typedef struct NuebR *Nueb;
typedef struct NuebR {
                Ueberg ueb;     /* Uebergaenge mit den Nonterminal */
                Tabindex von;   /* Anfangsindex in der Tabelle     */
                Tabindex bis;   /* Endeindex in der Tabelle        */
               } NuebRec;

/* ========================================================================= */
/* Makros                                                                    */
/* ========================================================================= */

 /* ----------------------------------------- */
 /* Zugriffe auf Elemente vom Typ ZustRec     */
 /* ----------------------------------------- */

 /* Zugriff auf erste Position eines ZustRec z */
#define FIRSTPOS(z) (z).firstpos
#ifdef INCATTR
 /* Zugriff auf erste Reduktions-Position eines ZustRec z */
#define FIRSTRED(z) (z).firstred
#endif
 /* Zugriff auf laufende Nummer eines ZustRec z */
#define ZUSTNR(z) (z).znr

 /* Zugriff auf spontane Uebergaenge eines ZustRec z */
#define ZUSTEPSUEB(z) (z).epsueb

 /* Zugriff auf terminale Uebergaenge eines ZustRec z */
#define ZUSTTERMUEB(z) (z).termueb

 /* Zugriff auf nonterminale Uebergaenge eines ZustRec z */
#define ZUSTNONTUEB(z) (z).nontueb

 /* Zugriff auf Liste der diesem Zustand shiftenden Uebergaenge */
#define ZUSTSHIFTS(z) (z).shifts

 /* Zugriff auf Nachfolger in Itemliste                    */
#define NEXTINZUSTLIST(z) (z).nextinlis

/* Item des Default-Uebergangs (SPONTRED), falls vorhanden */
#define DEFAULT(z) (z).ditem

/* Startindex in der Tabelle der terminalen Uebergaenge    */
#define TERMSTART(z) (z).tvon

/* Endindex in der Tabelle der terminalen Uebergaenge      */
#define TERMENDE(z) (z).tbis

 /* ----------------------------------------- */
 /* Zugriffe auf Elemente vom Typ UebergRec   */
 /* ----------------------------------------- */

/* Art des Uebergangs ueb  */
#define UEBART(ueb) (ueb).art

/* Bei Uebergang ueb zu lesendes Symbol */
#define UEBSYM(ueb) (ueb).sym

/* Startzustand des Uebergangs ueb                     */
#define UEBVON(ueb) (ueb).von

/* naechster gleicher SHIFT-Uebergang                  */
#define NEXTSHIFT(ueb) (ueb).nextshift

/* naechster Uebergang mit gleichem Nonterminal        */
#define NEXTNONT(ueb) (ueb).nextnont

/* Terminierungsinformation                            */
#define INKARN(ueb) (ueb).inkarn

/* Ziel des Uebergangs ueb, falls UEBART(ueb) == SHIFT */
#define UEBSZUST(ueb) (ueb).u.szust

/* zu reduzierendes Item, falls UEBART(ueb) == SPONTRED          */
#define UEBRITEM(ueb) (ueb).u.ritem

/* Lookaheaduebergaenge des Uebergangs ueb, falls UEBART(ueb) == LOOK */
#define UEBLOOKS(ueb) (ueb).u.looks

 /* ----------------------------------------- */
 /* Zugriffe auf Elemente vom Typ PosRec      */
 /* ----------------------------------------- */

 /* Zugriff auf Item einer PosRec p */
#define POSITEM(p) (p).item
#ifdef INCATTR
 /* Zugriff auf Attribut zu einer PosRec p */
#define POSATTR(p) (p).attr
#define POSFIRST(p) (p).first
#define POSFIRST_LOOK(p) (p).first_look
#define POSZUST(p) (p).zust
#endif
/* ========================================================================= */
/* Ablaufstruktur-Makros                                                     */
/* ========================================================================= */

 /* Schleife ueber alle Positionen p zu einem ZustRec z */
#define FOREACHPOS(z,p) FOREACHLISTEL(FIRSTPOS(z),p)

/* ========================================================================= */
/* Funktionsdeklarationen                                                    */
/* ========================================================================= */

/*====================================================================== */
/* Funktionsprototypen der Listenoperationen                              */
/*====================================================================== */

/* -------------- */
/* Typ Position   */
/* -------------- */
#ifdef __STDC__
Position eintragPosition(Position*,PosRec*);
BOOL    mergePosition(Position*,Position);
void    freelisPosition(Position);
#else
Position eintragPosition();
BOOL    mergePosition();
void    freelisPosition();
#endif
/* -------------- */
/* Typ Zustand    */
/* -------------- */
#ifdef __STDC__
Zustand eintragZustand(Zustand*,ZustRec*);
BOOL    mergeZustand(Zustand*,Zustand);
#else
Zustand eintragZustand();
BOOL    mergeZustand();
#endif
/* -------------- */
/* Typ Ueberg     */
/* -------------- */
#ifdef __STDC__
Ueberg eintragUeberg(Ueberg*,UebergRec*);
BOOL   mergeUeberg(Ueberg*,Ueberg);
void   freelisUeberg(Ueberg);
#else
Ueberg eintragUeberg();
BOOL   mergeUeberg();
void   freelisUeberg();
#endif
/* ========================================================================= */
/* Listenverwaltung : Eintrag Position in Positionsliste                     */
/* ========================================================================= */
#ifdef __STDC__
Position eintragPosition(Position*,PosRec *);
#else
Position eintragPosition();
#endif
/* ========================================================================= */
/* Listenverwaltung : Eintrag Uebergang in Uebergangsliste                   */
/* ========================================================================= */
#ifdef __STDC__
Ueberg eintragUeberg(Ueberg*,UebergRec *);
#else
Ueberg eintragUeberg();
#endif
/* ========================================================================= */
/* Listenverwaltung : Freigabe einer Liste von Uebergaengen                  */
/* ========================================================================= */
#ifdef __STDC__
void freelisUeberg(Ueberg);
#else
void freelisUeberg();
#endif

/* ========================================================================= */
/* Zustand in die Liste aller Zustaende aufnehmen                            */
/* Rueckgabe : laufende Nummer des Zustandes                                 */
/* ========================================================================= */
#ifdef __STDC__
Zustand putZustand(Zustand);
#else
Zustand putZustand();
#endif
/* ========================================================================= */
/* Bestimmt, ob Zustaende angelegt wurden, die noch nicht verarbeitet wurden */
/* ========================================================================= */
BOOL neueZustaende();

/* ========================================================================= */
/* Rueckgabe des naechsten, noch nicht bearbeiteten Zustandes                */
/* ========================================================================= */
Zustand nextZustand();

/* ====================================================================== */
/* liefert den ersten Zustand der Tabelle aller Zustaende ab              */
/* ====================================================================== */
Zustand firstZustand();

/* ====================================================================== */
/* Initialisierung der Datenstrukturen dieses Moduls, Zustandsmenge leer  */
/* ====================================================================== */
BOOL initZustaende();

#endif /* LRKZUST_H */

