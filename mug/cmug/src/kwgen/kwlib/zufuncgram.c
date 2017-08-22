/*************************************************************************
*
*  zufuncgram.c
*
*  Hilfsprogramm zum drucken der Grammatik
*  ueber die Zugriffsfunktionen
*
*  28.03.90  letzte Aenderung 
*************************************************************************/

#include <stdio.h>
#include "zufunc.h"

FILE *ofile;

zufuncgram()
{
	ofile = fopen("internform.zufunc","w");
	fprintf(ofile,"*** ZUGRIFFSFUNKTIONEN ***\n");
	fprintf(ofile,"PhasenId=%s\n",SymString(GetPhasenId()) );
	fprintf(ofile,"InGName=%s\n",SymString(GetInGName()) );
	fprintf(ofile,"OutGName=%s\n",SymString(GetOutGName()) );
	DruckeCard();
	DruckeSyms();
	fclose(ofile);
}

DruckeCard()
{
fprintf(ofile,
"Entry:%d  Vocabel:%d  Nonterm:%d  Term:%d  Attr:%d\nTyp:%d  Prod:%d  Prodpos:%d  Attrpos:%d  Funct:%d\nAufruf:%d  Aparam:%d  Fparam:%d\n",
CardEntry(),
CardVocabel(),
CardNonterm(),
CardTerm(),
CardAttr(),
CardTyp(),
CardProd(),
CardProdpos(),
CardAttrpos(),
CardFunct(),
CardAufruf(),
CardAparam(),
CardFparam());
}

DruckeSyms()
{
Vocabel voc;
	voc = FirstSym();
	while(voc) {
		fprintf(ofile," %s ",
			SymString(Sym_Name(voc)) );
		if(Is_Terminal(voc)) {
			fprintf(ofile,"TERM");
			if(Is_Semantisch(voc)) fprintf(ofile," SEM\n");
			else fprintf(ofile,"\n");
		} else fprintf(ofile,"\n");
		DruckeAttrs(voc);
		fprintf(ofile,"  -----------------------\n");
		DruckeProds(voc);
		fprintf(ofile,"\n");
		voc = NextSym(voc);
	}
}

DruckeAttrs(voc)
Vocabel voc;
{
Attr attr;
	attr = FirstAttr(voc);
	fprintf(ofile,"  attributes:\n");
	while(attr) {
		fprintf(ofile,"  %s : %s ",
			SymString(Attr_Name(attr)),
			SymString(Typ_Name(Typ_Of_Attr(attr))) );
		if(Is_Inherited(attr))fprintf(ofile,"INH");else fprintf(ofile,"SYN");
		if(Is_SynTyp(attr))fprintf(ofile," syntactic\n"); else fprintf(ofile,"\n"); 
		attr = NextAttr(attr);
	}
}

DruckeProds(voc)
Vocabel voc;
{
Product prod;
	prod = FirstProd(voc);
	while(prod) {
		fprintf(ofile,"  %s<%d> : ",
			SymString(Prod_Name(prod)),
			Prod_Nummer(prod) );
		DruckePpos(prod);
		DruckeAuxs(prod);
		DruckeBers(prod);
		prod = NextProd(prod);
	}
}

DruckeAuxs(prod)
Product prod;
{
Attrpos apos;
	apos = FirstAuxPos(prod);
	while(apos) {
		fprintf(ofile,"   AUX %s : %s\n",
			SymString(Attr_Name(Attr_Of_AttPos(apos))),
			SymString(Typ_Name(Typ_Of_Attr(Attr_Of_AttPos(apos)))) );
		apos = NextAuxPos(apos);
	}
}

DruckePpos(prod)
Product prod;
{
Prodpos ppos;
	ppos = FirstPPos(prod);
	fprintf(ofile,"%s<0> ->",
		SymString(Sym_Name(Grm_Symbol(ppos))) );
	ppos = NextPPos(ppos);
	while(ppos) {
		fprintf(ofile," %s<%d>",
			SymString(Sym_Name(Grm_Symbol(ppos))),
			PPos_Nummer(ppos) );
		ppos = NextPPos(ppos);
	}
	fprintf(ofile,"\n");
}

DruckeBers(prod)
Product prod;
{
Prodpos ppos;
Attrpos apos;
	apos = FirstAuxPos(prod);
	while(apos) {
		DruckeBerechnung(apos);
		apos = NextAuxPos(apos);
	}
	ppos = FirstPPos(prod);
	while(ppos) {
		DruckeApos(ppos);
		ppos = NextPPos(ppos);
	}
}

DruckeApos(ppos)
Prodpos ppos;
{
Attrpos apos;
	apos = FirstAPos(ppos);
	while(apos) {
		/*fprintf(ofile,"   .%s",
			SymString(Attr_Name(Attr_Of_AttPos(apos))) );*/
		DruckeBerechnung(apos);
		apos = NextAPos(apos);
	}
}

DruckeBerechnung(apos)
Attrpos apos;
{
Aufruf aufr;
	aufr = Ber_Aufruf(apos);
	if(aufr) {
		fprintf(ofile,"    (");
		DruckeErgs(aufr);
		fprintf(ofile,")=");
		if(Is_Copy(aufr))
			fprintf(ofile,"(");
		else fprintf(ofile,"%s(",
			SymString(Funkt_Name(Funkt_Of_Aufruf(aufr))) );
		DruckeArgs(aufr);
		fprintf(ofile,")\n");
	}
}

DruckeArgs(aufr)
Aufruf aufr;
{
Aparam apar;
	apar = FirstArg(aufr);
	while(apar) {
		fprintf(ofile,"%s<%d>.%s%s",
	SymString(Sym_Name(Grm_Symbol(PPos_Of_AttPos(AttPos_Of_Param(apar))))) ,
		PPos_Nummer(PPos_Of_AttPos(AttPos_Of_Param(apar))),
		(Is_Auxiliary(AttPos_Of_Param(apar)) ? "[AUX]" : ""),
		SymString(Attr_Name(Attr_Of_AttPos(AttPos_Of_Param(apar)))) );
		apar = NextArg(apar);
		if(apar)fprintf(ofile,",");
	}
}

DruckeErgs(aufr)
Aufruf aufr;
{
Aparam apar;
	apar = FirstErg(aufr);
	while(apar) {
		fprintf(ofile,"%s<%d>.%s%s",
	SymString(Sym_Name(Grm_Symbol(PPos_Of_AttPos(AttPos_Of_Param(apar))))) ,
		PPos_Nummer(PPos_Of_AttPos(AttPos_Of_Param(apar))),
		(Is_Auxiliary(AttPos_Of_Param(apar)) ? "[AUX]" : ""),
		SymString(Attr_Name(Attr_Of_AttPos(AttPos_Of_Param(apar)))) );
		apar = NextErg(apar);
		if(apar)fprintf(ofile,",");
	}
}

