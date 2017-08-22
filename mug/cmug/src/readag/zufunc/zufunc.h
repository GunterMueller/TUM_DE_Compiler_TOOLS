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

/***********************************************************************
*
*  zufunc.h
*
*  Datendefinitionen fuer Anwender der Zugriffsfunktionen
*
* 28.03.90  letzte Aenderung
***********************************************************************/
 
#ifndef FALSE
#define FALSE ((int)0)
#endif
#ifndef TRUE
#define TRUE ((int)1)
#endif 


#ifndef BOOL_T
#define BOOL_T
typedef int bool;
#endif
  
#ifndef INDEX_T
#define INDEX_T
typedef int Index;
#endif
 
#define NIL 0           /* Index = NIL => Element nicht vorhanden */
 
typedef Index Entry;       /* Index in Tabelle mit Identifikatoren */

#ifndef ENTRYINDEX_T
#define ENTRYINDEX_T
typedef Index entryIndex;	/* Index in Tabelle mit Identifikatoren */
#endif

typedef Index Vocabel;  /* virtueller Index fuer Vokabeln */
 
typedef Index Nonterm;  /* Index in Tabelle mit Nonterminals */
 
typedef Index Term;     /* Index in Tabelle mit Terminals */
 
typedef Index Funct;    /* Index in Tabelle mit Funktionen */
 
typedef Index Attr;     /* Index in Tabelle mit Attributen */
 
typedef Index Product;  /*   -"-  Produktionen */
 
typedef Index Typ;      /* Index in Tabelle mit Typen */
 
                /* Unter-Arrays fuer Produktionen, sem.Regeln */
 
typedef Index Prodpos;  /*   -"-  Produktionspositionen */
 
typedef Index Attrpos;  /*   -"-  Attributpositionen */
 
typedef Index Aufruf;   /*   -"-  Funktionsaufrufe */
 
typedef Index Aparam;   /*   -"-  Globale Liste fuer aktuelle Par. */
 
typedef Index Fparam;   /*   -"-  Globale Liste fuer formale Par. */
 
 
        /* Zugriffsfunktionen */

#ifdef __STDC__
extern Entry GetPhasenId(void);
extern Entry GetInGName(void);
extern Entry GetOutGName(void);
extern char *SymString(entryIndex hentry);
extern void DruckeSym(FILE *file, entryIndex hentry);
extern Vocabel NextSym(Vocabel vocabel);
extern Vocabel FirstSym(void);
extern bool Is_Terminal(Vocabel vocabel);
extern bool Is_Semantisch(Vocabel vocabel);
extern Entry Sym_Name(Vocabel vocabel);
extern Attr FirstAttr(Vocabel vocabel);
extern Attr NextAttr(Attr hattribut);
extern bool Is_Inherited(Attr hattribut);
extern bool Is_SynTyp(Attr hattribut);
extern Entry Attr_Name(Attr hattribut);
extern Entry Attr_Typ(Attr hattribut);
extern Typ Typ_Of_Attr(Attr hattribut);
extern Entry Typ_Name(Typ htyp);
extern Product FirstProd(Vocabel hvocabel);
extern Product NextProd(Product hproduct);
extern int Prod_Nummer(Product hproduct);
extern Entry Prod_Name(Product hproduct);
extern Attrpos FirstAuxPos(Product hproduct);
extern Attrpos NextAuxPos(Attrpos hattrpos);
extern Prodpos FirstPPos(Product hproduct);
extern Prodpos NextPPos(Prodpos hprodpos);
extern int PPos_Pos(Prodpos hprodpos);
extern int PPos_Nummer(Prodpos hprodpos);
extern Vocabel Grm_Symbol(Prodpos hprodpos);
extern Attr PPos_Of_AttPos(Attrpos hattrpos);
extern Attr Attr_Of_AttPos(Attrpos hattrpos);
extern bool Is_Auxiliary(Attrpos hattrpos);
extern Attrpos FirstAPos(Prodpos hprodpos);
extern Attrpos NextAPos(Attrpos hattrpos);
extern Aufruf Ber_Aufruf(Attrpos hattrpos);
extern bool Is_Copy(Aufruf haufruf);
extern Entry B_Funktion(Aufruf haufruf);
extern Funct Funkt_Of_Aufruf(Aufruf haufruf);
extern Entry Funkt_Name(Funct hfunct);
extern Aparam FirstArg(Aufruf haufruf);
extern Aparam NextArg(Aparam haparam);
extern Aparam FirstErg(Aufruf haufruf);
extern Aparam NextErg(Aparam haparam);
extern Attrpos AttPos_Of_Param(Aparam haparam);
extern int CardEntry(void);
extern int CardVocabel(void);
extern int CardNonterm(void);
extern int CardTerm(void);
extern int CardAttr(void);
extern int CardTyp(void);
extern int CardProd(void);
extern int CardProdpos(void);
extern int CardAttrpos(void);
extern int CardFunct(void);
extern int CardAufruf(void);
extern int CardAparam(void);
extern int CardFparam(void);

extern Funct FirstFunct(void);
extern Funct NextFunct(Funct X);
extern Product FirstProduct(void);
extern Product NextProduct(Product X);
extern Fparam FirstFPar(Funct X);
extern Fparam NextFPar(Fparam X);
extern Fparam FirstFErg(Funct X);
extern Fparam NextFErg(Fparam X);
extern Typ Typ_Of_Fparam(Fparam X);
extern bool Is_SynTTyp(Typ X);
extern bool Is_SemTTyp(Typ X);
extern Prodpos FirstOcc(Vocabel X);
extern Prodpos NextOcc(Prodpos X);
#else /* ! __STDC__ */
extern Entry GetPhasenId();
extern Entry GetInGName();
extern Entry GetOutGName();
extern char *SymString();
extern void DruckeSym();
extern Vocabel NextSym();
extern Vocabel FirstSym();
extern bool Is_Terminal();
extern bool Is_Semantisch();
extern Entry Sym_Name();
extern Attr FirstAttr();
extern Attr NextAttr();
extern bool Is_Inherited();
extern bool Is_SynTyp();
extern Entry Attr_Name();
extern Entry Attr_Typ();
extern Typ Typ_Of_Attr();
extern Entry Typ_Name();
extern Product FirstProd();
extern Product NextProd();
extern int Prod_Nummer();
extern Entry Prod_Name();
extern Attrpos FirstAuxPos();
extern Attrpos NextAuxPos();
extern Prodpos FirstPPos();
extern Prodpos NextPPos();
extern int PPos_Pos();
extern int PPos_Nummer();
extern Vocabel Grm_Symbol();
extern Attr PPos_Of_AttPos();
extern Attr Attr_Of_AttPos();
extern bool Is_Auxiliary();
extern Attrpos FirstAPos();
extern Attrpos NextAPos();
extern Aufruf Ber_Aufruf();
extern bool Is_Copy();
extern Entry B_Funktion();
extern Funct Funkt_Of_Aufruf();
extern Entry Funkt_Name();
extern Aparam FirstArg();
extern Aparam NextArg();
extern Aparam FirstErg();
extern Aparam NextErg();
extern Attrpos AttPos_Of_Param();
extern int CardEntry();
extern int CardVocabel();
extern int CardNonterm();
extern int CardTerm();
extern int CardAttr();
extern int CardTyp();
extern int CardProd();
extern int CardProdpos();
extern int CardAttrpos();
extern int CardFunct();
extern int CardAufruf();
extern int CardAparam();
extern int CardFparam();

extern Funct FirstFunct();
extern Funct NextFunct();
extern Product FirstProduct();
extern Product NextProduct();
extern Fparam FirstFPar();
extern Fparam NextFPar();
extern Fparam FirstFErg();
extern Fparam NextFErg();
extern Typ Typ_Of_Fparam();
extern bool Is_SynTTyp();
extern bool Is_SemTTyp();
extern Prodpos FirstOcc();
extern Prodpos NextOcc();
#endif /* ! __STDC__ */
