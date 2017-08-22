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

/******************************************************************************
*
* zufunc.c -   Implementation der Zugriffsfunktionen
*
* 01.02.89 js + fz  angelegt
*    04.89 fz  verbessert
* 30.06.89 fz  Card-Funktionen ergaenzt
* 19.03.91, Ulrich Vollath: #ifdef __STDC__ mittels protoize eingefuegt
******************************************************************************/
 
#include <stdio.h>
#include "gramtyp.h"
#include "zufunc.h"
extern gramptr gr;
typedef int ErrorNr;

#ifdef __STDC__
ErrorNr InitZug(void)
#else /* ! __STDC__ */
ErrorNr InitZug()
#endif /* ! __STDC__ */
 {
  /* aufruf-Felder besetzen */
  aufrufIndex i;
  aparamIndex j;
 
  for (i = 1; i <= gr->anzaufruf; i++) 
   {
    j = gr->aufruftab[i].firsterg;
    if (j != NIL) 
      do 
       {
        gr->attrpostab[gr->aparamtab[j].aktparam].aufruf = i;
       } while (!gr->aparamtab[j++].ende);
   }
  return 0;
 }

#ifdef __STDC__
entryIndex GetPhasenId(void)
#else /* ! __STDC__ */
entryIndex GetPhasenId()
#endif /* ! __STDC__ */
 {
  return (gr->phasenid);
 }
 
#ifdef __STDC__
entryIndex GetInGName(void)
#else /* ! __STDC__ */
entryIndex GetInGName()
#endif /* ! __STDC__ */
 {
  return (gr->ingname);
 }
 
#ifdef __STDC__
entryIndex GetOutGName(void)
#else /* ! __STDC__ */
entryIndex GetOutGName()
#endif /* ! __STDC__ */
 {
  return (gr->outgname);
 }
 
#ifdef __STDC__
identifier SymString(entryIndex hentry)
#else /* ! __STDC__ */
 identifier SymString(hentry)
 entryIndex hentry;
#endif /* ! __STDC__ */
 {
  return (gr->entrytab[hentry].name);
 }
 
#ifdef __STDC__
void DruckeSym(FILE *file, entryIndex hentry)
#else /* ! __STDC__ */
void DruckeSym(file, hentry)
 FILE *file;
 entryIndex hentry;
#endif /* ! __STDC__ */
 {
  /* ... */
  fputs(gr->entrytab[hentry].name, file);
 }
 
#ifdef __STDC__
entryAnz CardEntry(void)
#else /* ! __STDC__ */
entryAnz CardEntry()
#endif /* ! __STDC__ */
 {
  return (gr->anzentries);
 }
 
#ifdef __STDC__
vocabelAnz CardVocabel(void)
#else /* ! __STDC__ */
vocabelAnz CardVocabel()
#endif /* ! __STDC__ */
 {
  return (gr->anznonterm + gr->anzterm);
 }
 
#ifdef __STDC__
nontermAnz CardNonterm(void)
#else /* ! __STDC__ */
nontermAnz CardNonterm()
#endif /* ! __STDC__ */
 {
  return (gr->anznonterm);
 }
 
#ifdef __STDC__
termAnz CardTerm(void)
#else /* ! __STDC__ */
termAnz CardTerm()
#endif /* ! __STDC__ */
 {
  return (gr->anzterm);
 }
 
#ifdef __STDC__
attributAnz CardAttr(void)
#else /* ! __STDC__ */
attributAnz CardAttr()
#endif /* ! __STDC__ */
 {
  return (gr->anzattr);
 }
 
#ifdef __STDC__
typAnz CardTyp(void)
#else /* ! __STDC__ */
typAnz CardTyp()
#endif /* ! __STDC__ */
 {
  return (gr->anztyp);
 }
 
#ifdef __STDC__
productAnz CardProd(void)
#else /* ! __STDC__ */
productAnz CardProd()
#endif /* ! __STDC__ */
 {
  return (gr->anzprod);
 }
 
#ifdef __STDC__
prodposAnz CardProdpos(void)
#else /* ! __STDC__ */
prodposAnz CardProdpos()
#endif /* ! __STDC__ */
 {
  return (gr->anzprodpos);
 }
 
#ifdef __STDC__
attrposAnz CardAttrpos(void)
#else /* ! __STDC__ */
attrposAnz CardAttrpos()
#endif /* ! __STDC__ */
 {
  return (gr->anzattrpos);
 }
 
#ifdef __STDC__
functAnz CardFunct(void)
#else /* ! __STDC__ */
functAnz CardFunct()
#endif /* ! __STDC__ */
 {
  return (gr->anzfunct);
 }
 
#ifdef __STDC__
aufrufAnz CardAufruf(void)
#else /* ! __STDC__ */
aufrufAnz CardAufruf()
#endif /* ! __STDC__ */
 {
  return (gr->anzaufruf);
 }
 
#ifdef __STDC__
aparamAnz CardAparam(void)
#else /* ! __STDC__ */
aparamAnz CardAparam()
#endif /* ! __STDC__ */
 {
  return (gr->anzaparam);
 }
 
#ifdef __STDC__
fparamAnz CardFparam(void)
#else /* ! __STDC__ */
fparamAnz CardFparam()
#endif /* ! __STDC__ */
 {
  return (gr->anzfparam);
 }
 
#ifdef __STDC__
vocabelIndex FirstSym(void)
#else /* ! __STDC__ */
vocabelIndex FirstSym()
#endif /* ! __STDC__ */
 {
  return (gr->axiom);
 }
 
#ifdef __STDC__
vocabelIndex NextSym(vocabelIndex vocabel)
#else /* ! __STDC__ */
vocabelIndex NextSym(vocabel)
vocabelIndex vocabel;
#endif /* ! __STDC__ */
 {
vocabelIndex next;
 
        if (vocabel == gr->axiom)
                next = 1;
        else
                next = vocabel + 1;
 
        if (next == gr->axiom) next++;
 
        if (next <= (gr->anzterm + gr->anznonterm))
    return (next);
        else
    return (0);
 }
 
#ifdef __STDC__
bool Is_Terminal(vocabelIndex vocabel)
#else /* ! __STDC__ */
bool Is_Terminal(vocabel)
vocabelIndex vocabel;
#endif /* ! __STDC__ */
 {
  return (vocabel > gr->anznonterm);
 }
 
#ifdef __STDC__
bool Is_Semantisch(vocabelIndex vocabel)
#else /* ! __STDC__ */
bool Is_Semantisch(vocabel)
vocabelIndex vocabel;
#endif /* ! __STDC__ */
 {
  return (vocabel > gr->anznonterm &&
                gr->termtab[vocabel - gr->anznonterm].issemantic);
 }
 
#ifdef __STDC__
entryIndex Sym_Name(vocabelIndex vocabel)
#else /* ! __STDC__ */
entryIndex Sym_Name(vocabel)
vocabelIndex vocabel;
#endif /* ! __STDC__ */
 {
        if (vocabel > gr->anznonterm)
    return (gr->termtab[vocabel - gr->anznonterm].name);
        else
    return (gr->nontermtab[vocabel].name);
 }
 
#ifdef __STDC__
attrIndex FirstAttr(vocabelIndex vocabel)
#else /* ! __STDC__ */
attrIndex FirstAttr(vocabel)
vocabelIndex vocabel;
#endif /* ! __STDC__ */
 {
        if (vocabel > gr->anznonterm)
    return (gr->termtab[vocabel - gr->anznonterm].attr);
        else
    return (gr->nontermtab[vocabel].firstattr);
 }
 
#ifdef __STDC__
attrIndex NextAttr(attrIndex hattribut)
#else /* ! __STDC__ */
attrIndex NextAttr(hattribut)
attrIndex hattribut;
#endif /* ! __STDC__ */
 {
        if (gr->attrtab[hattribut].ende)
    return (0);
        else
    return (hattribut+1);
 }
 
#ifdef __STDC__
bool Is_Inherited(attrIndex hattribut)
#else /* ! __STDC__ */
bool Is_Inherited(hattribut)
attrIndex hattribut;
#endif /* ! __STDC__ */
 {
  return (gr->attrtab[hattribut].akenn == INHERITED);
 }
 
#ifdef __STDC__
bool Is_SynTyp(attrIndex hattribut)
#else /* ! __STDC__ */
bool Is_SynTyp(hattribut)
attrIndex hattribut;
#endif /* ! __STDC__ */
 {
  return (gr->typtab[ gr->attrtab[hattribut].typ ].tkenn == SYNTYP);
 }
 
#ifdef __STDC__
entryIndex Attr_Name(attrIndex hattribut)
#else /* ! __STDC__ */
entryIndex Attr_Name(hattribut)
attrIndex hattribut;
#endif /* ! __STDC__ */
 {
  return (gr->attrtab[hattribut].name);
 }
 
#ifdef __STDC__
entryIndex Attr_Typ(attrIndex hattribut)
#else /* ! __STDC__ */
entryIndex Attr_Typ(hattribut)
attrIndex hattribut;
#endif /* ! __STDC__ */
 {
  return (gr->typtab[gr->attrtab[hattribut].typ].name);
 }
 
#ifdef __STDC__
typIndex Typ_Of_Attr(attrIndex hattribut)
#else /* ! __STDC__ */
typIndex Typ_Of_Attr(hattribut)
attrIndex hattribut;
#endif /* ! __STDC__ */
 {
  return (gr->attrtab[hattribut].typ);
 }
 
#ifdef __STDC__
entryIndex Typ_Name(typIndex htyp)
#else /* ! __STDC__ */
entryIndex Typ_Name(htyp)
typIndex htyp;
#endif /* ! __STDC__ */
 {
  return (gr->typtab[htyp].name);
 }
 
#ifdef __STDC__
productIndex FirstProd(vocabelIndex hvocabel)
#else /* ! __STDC__ */
productIndex FirstProd(hvocabel)
vocabelIndex hvocabel;
#endif /* ! __STDC__ */
 {
        if (hvocabel > gr->anznonterm)
    return (0);
        else
    return (gr->nontermtab[hvocabel].firstproduct);
 }
 
#ifdef __STDC__
productIndex NextProd(productIndex hproduct)
#else /* ! __STDC__ */
productIndex NextProd(hproduct)
productIndex hproduct;
#endif /* ! __STDC__ */
 {
  return (gr->prodtab[hproduct].nextprod);
 }
 
#ifdef __STDC__
entryIndex Prod_Name(productIndex hproduct)
#else /* ! __STDC__ */
entryIndex Prod_Name(hproduct)
productIndex hproduct;
#endif /* ! __STDC__ */
 {
  return (gr->prodtab[hproduct].prodname);
 }
 
#ifdef __STDC__
int Prod_Nummer(productIndex hproduct)
#else /* ! __STDC__ */
int Prod_Nummer(hproduct)
productIndex hproduct;
#endif /* ! __STDC__ */
 {
  return (hproduct);
 }
 
#ifdef __STDC__
attrposIndex FirstAuxPos(productIndex hproduct)
#else /* ! __STDC__ */
attrposIndex FirstAuxPos(hproduct)
productIndex hproduct;
#endif /* ! __STDC__ */
 {
  return (gr->prodtab[hproduct].firstauxattrpos);
 }
 
#ifdef __STDC__
attrposIndex NextAuxPos(attrposIndex hattrpos)
#else /* ! __STDC__ */
attrposIndex NextAuxPos(hattrpos)
attrposIndex hattrpos;
#endif /* ! __STDC__ */
 {
        if (gr->attrpostab[hattrpos].ende)
    return(0);
        else
    return(hattrpos+1);
 }
 
#ifdef __STDC__
prodposIndex FirstPPos(productIndex hproduct)
#else /* ! __STDC__ */
prodposIndex FirstPPos(hproduct)
productIndex hproduct;
#endif /* ! __STDC__ */
 {
  return (gr->prodtab[hproduct].firstprodpos);
 }
 
#ifdef __STDC__
prodposIndex NextPPos(prodposIndex hprodpos)
#else /* ! __STDC__ */
prodposIndex NextPPos(hprodpos)
prodposIndex hprodpos;
#endif /* ! __STDC__ */
 {
        if (gr->prodpostab[hprodpos].ende)
    return(0);
        else
    return(hprodpos+1);
 }
 
#ifdef __STDC__
int PPos_Pos(prodposIndex hprodpos)
#else /* ! __STDC__ */
int PPos_Pos(hprodpos)
prodposIndex hprodpos;
#endif /* ! __STDC__ */
 {
  return (gr->prodpostab[hprodpos].pos);
 }

#ifdef __STDC__
int PPos_Nummer(prodposIndex hprodpos)
#else /* ! __STDC__ */
int PPos_Nummer(hprodpos)
prodposIndex hprodpos;
#endif /* ! __STDC__ */
 {
  return (gr->prodpostab[hprodpos].num);
 }
 
#ifdef __STDC__
vocabelIndex Grm_Symbol(prodposIndex hprodpos)
#else /* ! __STDC__ */
vocabelIndex Grm_Symbol(hprodpos)
prodposIndex hprodpos;
#endif /* ! __STDC__ */
 {
  return (gr->prodpostab[hprodpos].vocabel);
 }
 
#ifdef __STDC__
attrposIndex FirstAPos(prodposIndex hprodpos)
#else /* ! __STDC__ */
attrposIndex FirstAPos(hprodpos)
prodposIndex hprodpos;
#endif /* ! __STDC__ */
 {
  return (gr->prodpostab[hprodpos].firstattrpos);
 }
 
#ifdef __STDC__
attrposIndex NextAPos(attrposIndex hattrpos)
#else /* ! __STDC__ */
attrposIndex NextAPos(hattrpos)
attrposIndex hattrpos;
#endif /* ! __STDC__ */
 {
        if (gr->attrpostab[hattrpos].ende)
    return(0);
        else
    return(hattrpos+1);
 }
 
#ifdef __STDC__
prodposIndex PPos_Of_AttPos(attrposIndex hattrpos)
#else /* ! __STDC__ */
prodposIndex PPos_Of_AttPos(hattrpos)
attrposIndex hattrpos;
#endif /* ! __STDC__ */
 {
  return (gr->attrpostab[hattrpos].prodpos);
 }
 
#ifdef __STDC__
attrIndex Attr_Of_AttPos(attrposIndex hattrpos)
#else /* ! __STDC__ */
attrIndex Attr_Of_AttPos(hattrpos)
attrposIndex hattrpos;
#endif /* ! __STDC__ */
 {
 return (gr->attrpostab[hattrpos].attr);
 }
 
#ifdef __STDC__
bool Is_Auxiliary(attrposIndex hattrpos)
#else /* ! __STDC__ */
bool Is_Auxiliary(hattrpos)
attrposIndex hattrpos;
#endif /* ! __STDC__ */
 {
  return (gr->attrtab[gr->attrpostab[hattrpos].attr].akenn == AUXILIARY);
 }
 
 
#ifdef __STDC__
aufrufIndex Ber_Aufruf(attrposIndex hattrpos)
#else /* ! __STDC__ */
aufrufIndex Ber_Aufruf(hattrpos)
attrposIndex hattrpos;
#endif /* ! __STDC__ */
 {
  return (gr->attrpostab[hattrpos].aufruf);
 }
 
#ifdef __STDC__
bool Is_Copy(aufrufIndex haufruf)
#else /* ! __STDC__ */
bool Is_Copy(haufruf)
aufrufIndex haufruf;
#endif /* ! __STDC__ */
 {
  return (haufruf && gr->functtab[ gr->aufruftab[haufruf].funct ].iscopy);
 }
 
#ifdef __STDC__
entryIndex B_Funktion(aufrufIndex haufruf)
#else /* ! __STDC__ */
entryIndex B_Funktion(haufruf)
aufrufIndex haufruf;
#endif /* ! __STDC__ */
 {
  return (gr->functtab[ gr->aufruftab[haufruf].funct ].name);
 }
 
#ifdef __STDC__
functIndex Funkt_Of_Aufruf(aufrufIndex haufruf)
#else /* ! __STDC__ */
functIndex Funkt_Of_Aufruf(haufruf)
aufrufIndex haufruf;
#endif /* ! __STDC__ */
 {
  return (gr->aufruftab[haufruf].funct);
 }
 
#ifdef __STDC__
entryIndex Funkt_Name(functIndex hfunct)
#else /* ! __STDC__ */
entryIndex Funkt_Name(hfunct)
functIndex hfunct;
#endif /* ! __STDC__ */
 {
  return (gr->functtab[hfunct].name);
 }
 
#ifdef __STDC__
aparamIndex FirstArg(aufrufIndex haufruf)
#else /* ! __STDC__ */
aparamIndex FirstArg(haufruf)
aufrufIndex haufruf;
#endif /* ! __STDC__ */
 {
  return ( gr->aufruftab[haufruf].firstarg);
 }
 
#ifdef __STDC__
aparamIndex NextArg(aparamIndex haparam)
#else /* ! __STDC__ */
aparamIndex NextArg(haparam)
aparamIndex haparam;
#endif /* ! __STDC__ */
 {
  if (gr->aparamtab[haparam].ende)
    return(0);
  else
    return(haparam+1);
 }
 
#ifdef __STDC__
aparamIndex FirstErg(aufrufIndex haufruf)
#else /* ! __STDC__ */
aparamIndex FirstErg(haufruf)
aufrufIndex haufruf;
#endif /* ! __STDC__ */
 {
  return ( gr->aufruftab[haufruf].firsterg);
 }
 
#ifdef __STDC__
aparamIndex NextErg(aparamIndex haparam)
#else /* ! __STDC__ */
aparamIndex NextErg(haparam)
aparamIndex haparam;
#endif /* ! __STDC__ */
 {
  if (gr->aparamtab[haparam].ende)
    return(0);
  else
    return(haparam+1);
 }
 
#ifdef __STDC__
attrposIndex AttPos_Of_Param(aparamIndex haparam)
#else /* ! __STDC__ */
attrposIndex AttPos_Of_Param(haparam)
aparamIndex haparam;
#endif /* ! __STDC__ */
 {
  return (gr->aparamtab[haparam].aktparam);
 }
 
 
/* nachtdglich definerte Zugriffsfunktionen */
 
#ifdef __STDC__
functIndex FirstFunct(void)
#else /* ! __STDC__ */
functIndex FirstFunct()
#endif /* ! __STDC__ */
 {
  return( 1 );
 }
 
#ifdef __STDC__
functIndex NextFunct(functIndex X)
#else /* ! __STDC__ */
functIndex NextFunct( X)
functIndex X;
#endif /* ! __STDC__ */
 {
  if (X<CardFunct())
    return(++X);
  else return(NIL);
 }
 
#ifdef __STDC__
productIndex FirstProduct(void)
#else /* ! __STDC__ */
productIndex FirstProduct()
#endif /* ! __STDC__ */
 {
  return( 1 );
 }
 
#ifdef __STDC__
productIndex NextProduct(productIndex X)
#else /* ! __STDC__ */
productIndex NextProduct( X)
productIndex X;
#endif /* ! __STDC__ */
 {
  if (X<CardProd())
    return(++X);
  else return(NIL);
 }
 
#ifdef __STDC__
fparamIndex FirstFPar(functIndex X)
#else /* ! __STDC__ */
fparamIndex FirstFPar(X)
functIndex X;
#endif /* ! __STDC__ */
 {
  return(gr->functtab[X].firstarg);
 }
 
#ifdef __STDC__
fparamIndex NextFPar(fparamIndex X)
#else /* ! __STDC__ */
fparamIndex NextFPar(X)
fparamIndex X;
#endif /* ! __STDC__ */
 {
  if (gr->fparamtab[X].ende)
    return(NIL);
  else
    return(++X);
 }
 
#ifdef __STDC__
fparamIndex FirstFErg(functIndex X)
#else /* ! __STDC__ */
fparamIndex FirstFErg( X)
functIndex X;
#endif /* ! __STDC__ */
 {
  return(gr->functtab[X].firsterg);
 }
 
#ifdef __STDC__
fparamIndex NextFErg(fparamIndex X)
#else /* ! __STDC__ */
fparamIndex NextFErg( X)
fparamIndex X;
#endif /* ! __STDC__ */
 {
  if (gr->fparamtab[X].ende)
    return(NIL);
  else
    return(++X);
 }
 
#ifdef __STDC__
typIndex Typ_Of_Fparam(fparamIndex X)
#else /* ! __STDC__ */
typIndex Typ_Of_Fparam( X)
fparamIndex X;
#endif /* ! __STDC__ */
 {
  return(gr->fparamtab[X].typ);
 }
 
#ifdef __STDC__
bool Is_SynTTyp(typIndex X)
#else /* ! __STDC__ */
bool Is_SynTTyp( X)
typIndex X;
#endif /* ! __STDC__ */
 {
  return(gr->typtab[X].tkenn==SYNTYP);
 }
 
#ifdef __STDC__
bool Is_SemTTyp(typIndex X)
#else /* ! __STDC__ */
bool Is_SemTTyp( X)
typIndex X;
#endif /* ! __STDC__ */
 {
  return(gr->typtab[X].tkenn==SEMTYP);
 }
 
#ifdef __STDC__
prodposIndex FirstOcc(vocabelIndex X)
#else /* ! __STDC__ */
prodposIndex FirstOcc( X)
vocabelIndex X;
#endif /* ! __STDC__ */
 {
  if (X > gr->anznonterm)
    return(NIL);
  else
    return (gr->nontermtab[X].firstoccurence);
 }
 
#ifdef __STDC__
prodposIndex NextOcc(prodposIndex X)
#else /* ! __STDC__ */
prodposIndex NextOcc( X)
prodposIndex X;
#endif /* ! __STDC__ */
 {
  return(gr->prodpostab[X].nextoccur);
 }
 
 
