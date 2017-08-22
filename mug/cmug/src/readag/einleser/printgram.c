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

/*************************************************************************
*
*  printgram.c
*
*  Hilfsprogramm zum drucken der Grammatik
*  a) direkt ueber printgram(g)
*  b) ueber die Zugriffsfunktionen ueber zufunc_gram
*
*  06.07.89  letzte Aenderung 
*************************************************************************/

#include <stdio.h>
#include "gramtyp.h"

extern gramptr gr;


/****************************************/
/* ueber Zugriffsfunktionen */
/****************************************/
void
DruckeCard(),
DruckeSyms(),
DruckeAttrs(),
DruckeProds(),
DruckeAuxs(),
DruckePpos(),
DruckeBers(),
DruckeApos(),
DruckeBerechnung(),
DruckeArgs(),
DruckeErgs();

int InitZug();
entryIndex GetPhasenId();
identifier SymString();
void DruckeSym();
vocabelIndex NextSym();
vocabelIndex FirstSym();
bool Is_Terminal();
bool Is_Semantisch();
entryIndex Sym_Name();
attrIndex FirstAttr();
attrIndex NextAttr();
bool Is_Inherited();
bool Is_SynTyp();
entryIndex Attr_Name();
entryIndex Attr_Typ();
typIndex Typ_Of_Attr();
entryIndex Typ_Name();
productIndex FirstProd();
productIndex NextProd();
entryIndex Prod_Name();
attrposIndex FirstAuxPos();
attrposIndex NextAuxPos();
prodposIndex FirstPPos();
prodposIndex NextPPos();
vocabelIndex Grm_Symbol();
attrIndex PPos_Of_AttPos();
attrIndex Attr_Of_AttPos();
bool Is_Auxiliary();
attrposIndex FirstAPos();
attrposIndex NextAPos();
aufrufIndex Ber_Aufruf();
bool Is_Copy();
entryIndex B_Funktion();
functIndex Funkt_Of_Aufruf();
entryIndex Funkt_Name();
aparamIndex FirstArg();
aparamIndex NextArg();
aparamIndex FirstErg();
aparamIndex NextArg();
attrposIndex AttPos_Of_Param();
entryAnz CardEntry();
vocabelAnz CardVocabel();
nontermAnz CardNonterm();
termAnz CardTerm();
attributAnz CardAttr();
typAnz CardTyp();
productAnz CardProd();
prodposAnz CardProdpos();
attrposAnz CardAttrpos();
functAnz CardFunct();
aufrufAnz CardAufruf();
aparamAnz CardAparam();
fparamAnz CardFparam();


FILE *ofile;

#ifdef __STDC__
void zufunc_gram(void)
#else /* ! __STDC__ */
void zufunc_gram()
#endif /* ! __STDC__ */
{
	ofile = fopen("zufunc.file","w");
	fprintf(ofile,"*** ZUGRIFFSFUNKTIONEN ***\n");
	fprintf(ofile,"PhasenId=%s\n",SymString(GetPhasenId()) );
	fprintf(ofile,"InGName=%s\n",SymString(GetInGName()) );
	fprintf(ofile,"OutGName=%s\n",SymString(GetOutGName()) );
	DruckeCard();
	DruckeSyms();
	fclose(ofile);
}

#ifdef __STDC__
void DruckeCard(void)
#else /* ! __STDC__ */
void DruckeCard()
#endif /* ! __STDC__ */
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

#ifdef __STDC__
void DruckeSyms(void)
#else /* ! __STDC__ */
void DruckeSyms()
#endif /* ! __STDC__ */
{
vocabelIndex voc;
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

#ifdef __STDC__
void DruckeAttrs(vocabelIndex voc)
#else /* ! __STDC__ */
void DruckeAttrs(voc)
vocabelIndex voc;
#endif /* ! __STDC__ */
{
attrIndex attr;
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

#ifdef __STDC__
void DruckeProds(vocabelIndex voc)
#else /* ! __STDC__ */
void DruckeProds(voc)
vocabelIndex voc;
#endif /* ! __STDC__ */
{
productIndex prod;
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

#ifdef __STDC__
void DruckeAuxs(productIndex prod)
#else /* ! __STDC__ */
void DruckeAuxs(prod)
productIndex prod;
#endif /* ! __STDC__ */
{
attrposIndex apos;
	apos = FirstAuxPos(prod);
	while(apos) {
		fprintf(ofile,"   AUX %s : %s\n",
			SymString(Attr_Name(Attr_Of_AttPos(apos))),
			SymString(Typ_Name(Typ_Of_Attr(Attr_Of_AttPos(apos)))) );
		apos = NextAuxPos(apos);
	}
}

#ifdef __STDC__
void DruckePpos(productIndex prod)
#else /* ! __STDC__ */
void DruckePpos(prod)
productIndex prod;
#endif /* ! __STDC__ */
{
prodposIndex ppos;
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

#ifdef __STDC__
void DruckeBers(productIndex prod)
#else /* ! __STDC__ */
void DruckeBers(prod)
productIndex prod;
#endif /* ! __STDC__ */
{
prodposIndex ppos;
attrposIndex apos;
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

#ifdef __STDC__
void DruckeApos(prodposIndex ppos)
#else /* ! __STDC__ */
void DruckeApos(ppos)
prodposIndex ppos;
#endif /* ! __STDC__ */
{
attrposIndex apos;
	apos = FirstAPos(ppos);
	while(apos) {
		/*fprintf(ofile,"   .%s",
			SymString(Attr_Name(Attr_Of_AttPos(apos))) );*/
		DruckeBerechnung(apos);
		apos = NextAPos(apos);
	}
}

#ifdef __STDC__
void DruckeBerechnung(attrposIndex apos)
#else /* ! __STDC__ */
void DruckeBerechnung(apos)
attrposIndex apos;
#endif /* ! __STDC__ */
{
aufrufIndex aufr;
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

#ifdef __STDC__
void DruckeArgs(aufrufIndex aufr)
#else /* ! __STDC__ */
void DruckeArgs(aufr)
aufrufIndex aufr;
#endif /* ! __STDC__ */
{
aparamIndex apar;
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

#ifdef __STDC__
void DruckeErgs(aufrufIndex aufr)
#else /* ! __STDC__ */
void DruckeErgs(aufr)
aufrufIndex aufr;
#endif /* ! __STDC__ */
{
aparamIndex apar;
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

#ifdef __STDC__
identifier gnam(gramptr g, entryIndex e)
#else /* ! __STDC__ */
identifier gnam(g, e)
gramptr g;
entryIndex e;
#endif /* ! __STDC__ */
{
	return (g->entrytab[e].name);
}

#ifdef __STDC__
identifier gbool(bool b)
#else /* ! __STDC__ */
identifier gbool(b)
bool b;
#endif /* ! __STDC__ */
{
	return (b ? "TRUE " : "FALSE");
}

/****************************************/
/* Direkter Zugriff */
/****************************************/

void printgram();
#ifdef __STDC__
void printentry(gramptr g);
void printterm(gramptr g);
void printnonterm(gramptr g);
void printfunct(gramptr g);
void printattribut(gramptr g);
void printproduct(gramptr g);
void printtyp(gramptr g);
void printprodpos(gramptr g);
void printattrpos(gramptr g);
void printaufruf(gramptr g);
void printfparam(gramptr g);
void printaparam(gramptr g);
#else /* ! __STDC__ */
void printentry();
void printterm();
void printnonterm();
void printfunct();
void printattribut();
void printproduct();
void printtyp();
void printprodpos();
void printattrpos();
void printaufruf();
void printfparam();
void printaparam();
#endif /* ! __STDC__ */

FILE *pfile;

#ifdef __STDC__
void print_gram(gramptr g)
#else /* ! __STDC__ */
void print_gram(g)
gramptr g;
#endif /* ! __STDC__ */
{
	pfile = fopen("printgram.file","w");
	fprintf(pfile,"phasenid = '%-12.12s'  ingname = '%-12.12s'  outgname = '%-12.12s'\n",
		gnam(g,g->phasenid), gnam(g,g->ingname), gnam(g,g->outgname) );
	fprintf(pfile,"axiom = nonterm[%d]\n", g->axiom);

	printentry(g);
	printterm(g);
	printnonterm(g);
	printfunct(g);
	printattribut(g);
	printtyp(g);
	printproduct(g);
	printprodpos(g);
	printattrpos(g);
	printaufruf(g);
	printfparam(g);
	printaparam(g);
	fclose(pfile);
}

#ifdef __STDC__
void printentry(gramptr g)
#else /* ! __STDC__ */
void printentry(g)
gramptr g;
#endif /* ! __STDC__ */
{
int i;
entry *e;

	fprintf(pfile,"****** entrytab *******\n");
	e = &g->entrytab[1];

	for(i=1; i <= g->anzentries; i++) {
		fprintf(pfile,"%3d  '%-12.12s'  otherclass=%3d  ",
			i, e->name, e->otherclass);
		switch(e->class) {
			case GRAM:     fprintf(pfile,"GRAM"); break;
			case TERM:     fprintf(pfile,"TERM"); break;
			case NONTERM:  fprintf(pfile,"NONTERM"); break;
			case FUNCT:    fprintf(pfile,"FUNCT"); break;
			case SFUNCT:   fprintf(pfile,"SFUNCT"); break;
			case ATTRIBUT: fprintf(pfile,"ATTRIBUT"); break;
			case PRODUCT:  fprintf(pfile,"PRODUCT"); break;
			case TYP:      fprintf(pfile,"TYP"); break;
			default:  fprintf(pfile,"unbekannt ");
		}
		fprintf(pfile,"[%d]\n",e->index.term);
		e++;
	}
}


#ifdef __STDC__
void printterm(gramptr g)
#else /* ! __STDC__ */
void printterm(g)
gramptr g;
#endif /* ! __STDC__ */
{
int i;
terminal *t;

	fprintf(pfile,"****** termtab *******\n");
	t = &g->termtab[1];

	for(i=1; i <= g->anzterm; i++) {
		fprintf(pfile,"%3d  '%-12.12s'  issemantic=%s  attr=%d\n",
			i, gnam(g,t->name), gbool(t->issemantic), t->attr);
		t++;
	}
}


#ifdef __STDC__
void printnonterm(gramptr g)
#else /* ! __STDC__ */
void printnonterm(g)
gramptr g;
#endif /* ! __STDC__ */
{
int i;
nonterminal *nt;

	fprintf(pfile,"****** nontermtab *******\n");
	nt = &g->nontermtab[1];

	for(i=1; i <= g->anznonterm; i++) {
		fprintf(pfile,"%3d  '%-12.12s'  firstattr=%3d  firstproduct=%3d\n",
			i, gnam(g,nt->name), nt->firstattr, nt->firstproduct);
		nt++;
	}
}


#ifdef __STDC__
void printfunct(gramptr g)
#else /* ! __STDC__ */
void printfunct(g)
gramptr g;
#endif /* ! __STDC__ */
{
int i;
funct *f;

	fprintf(pfile,"****** functtab *******\n");
	f = &g->functtab[1];

	for(i=1; i <= g->anzfunct; i++) {
		fprintf(pfile,"%3d  '%-12.12s'  iscopy=%s  ",
			i, gnam(g,f->name), gbool(f->iscopy));
		fprintf(pfile,"firstarg=%3d  firsterg=%d\n",
			f->firstarg, f->firsterg);
		f++;
	}
}


#ifdef __STDC__
void printattribut(gramptr g)
#else /* ! __STDC__ */
void printattribut(g)
gramptr g;
#endif /* ! __STDC__ */
{
int i;
attribut *a;

	fprintf(pfile,"****** attrtab *******\n");
	a = &g->attrtab[1];

	for(i=1; i <= g->anzattr; i++) {
		fprintf(pfile,"%3d  '%-12.12s'  voc=%3d  ",
			i, gnam(g,a->name), a->voc);
		switch(a->akenn) {
			case INHERITED  :     fprintf(pfile,"INH"); break;
			case SYNTHESIZED:     fprintf(pfile,"SYN"); break;
			case SEMTERM    :     fprintf(pfile,"SEM"); break;
			case AUXILIARY  :     fprintf(pfile,"AUX"); break;
			default    :     fprintf(pfile,"unb"); break;
		}
		fprintf(pfile,"  typ[%3d]'%-12.12s'  ende=%s\n",
			a->typ, gnam(g,g->typtab[a->typ].name), gbool(a->ende));
		a++;
	}
}


#ifdef __STDC__
void printproduct(gramptr g)
#else /* ! __STDC__ */
void printproduct(g)
gramptr g;
#endif /* ! __STDC__ */
{
int i;
product *p;

	fprintf(pfile,"****** prodtab *******\n");
	p = &g->prodtab[1];

	for(i=1; i <= g->anzprod; i++) {
		fprintf(pfile,"%3d  '%-12.12s'  firstpp=%3d  firstaufr=%3d  ",
			i, gnam(g,p->prodname), p->firstprodpos, p->firstaufruf);
		fprintf(pfile,"firstaux=%3d  nextprod=%3d\n",
			p->firstauxattrpos, p->nextprod);
		p++;
	}
}


#ifdef __STDC__
void printtyp(gramptr g)
#else /* ! __STDC__ */
void printtyp(g)
gramptr g;
#endif /* ! __STDC__ */
{
int i;
typ *t;

	fprintf(pfile,"****** typtab *******\n");
	t = &g->typtab[1];

	for(i=1; i <= g->anztyp; i++) {
		fprintf(pfile,"%3d  '%-12.12s'  ",
			i, gnam(g,t->name));
		switch(t->tkenn) {
			case CTYP   :     fprintf(pfile,"CTYP  \n"); break;
			case SEMTYP :     fprintf(pfile,"SEMTYP\n"); break;
			case SYNTYP :     fprintf(pfile,"SYNTYP\n"); break;
			default:     fprintf(pfile,"unbek.\n"); break;
		}
		t++;
	}
}


#ifdef __STDC__
void printprodpos(gramptr g)
#else /* ! __STDC__ */
void printprodpos(g)
gramptr g;
#endif /* ! __STDC__ */
{
int i;
prodpos *pp;
vocabelIndex tnum;
int term;
entryIndex name;

	fprintf(pfile,"****** prodpostab *******\n");
	pp = &g->prodpostab[1];

	for(i=1; i <= g->anzprodpos; i++) {
		fprintf(pfile,"%3d  ",i);
		tnum = pp->vocabel;
		term = tnum > g->anznonterm;
		if (term)
			name = g->termtab[tnum - g->anznonterm].name;
		else
			name = g->nontermtab[tnum].name;

		fprintf(pfile,"'%-12.12s' ",
			gnam(g,name));
		fprintf(pfile,"num=%3d  pos=%2d  voc=%3d  prod=%3d  ",
			pp->num, pp->pos, pp->vocabel, pp->product);
		fprintf(pfile,"firstap=%3d  e=%s\n",
			pp->firstattrpos, gbool(pp->ende));
		pp++;
	}
}


#ifdef __STDC__
void printattrpos(gramptr g)
#else /* ! __STDC__ */
void printattrpos(g)
gramptr g;
#endif /* ! __STDC__ */
{
int i;
attrpos *ap;
attrIndex anum;
vocabelIndex tnum;
int term;
entryIndex name;

	fprintf(pfile,"****** attrpostab *******\n");
	ap = &g->attrpostab[1];

	for(i=1; i <= g->anzattrpos; i++) {
		fprintf(pfile,"%3d  ",i);
		anum = g->attrpostab[i].attr;
		tnum = g->attrtab[anum].voc;
		term = tnum > g->anznonterm;
		if (term)
			name = g->termtab[tnum - g->anznonterm].name;
		else
			name = g->nontermtab[tnum].name;

		fprintf(pfile,"'%-12.12s'.'%-12.12s' ",
			gnam(g,name), gnam(g,g->attrtab[anum].name));
		fprintf(pfile,"attr=%3d  prodp=%3d  aufr=%3d  ",
			ap->attr, ap->prodpos, ap->aufruf);
		fprintf(pfile,"end=%s\n",
			gbool(ap->ende));
		ap++;
	}
}


#ifdef __STDC__
void printaufruf(gramptr g)
#else /* ! __STDC__ */
void printaufruf(g)
gramptr g;
#endif /* ! __STDC__ */
{
int i;
aufruf *au;

	fprintf(pfile,"****** aufruftab *******\n");
	au = &g->aufruftab[1];

	for(i=1; i <= g->anzaufruf; i++) {
		fprintf(pfile,"%3d  '%-12.12s'  funct=%3d  firstarg=%3d  firsterg=%3d  ",
			i, gnam(g, g->functtab[au->funct].name),
			au->funct, au->firstarg, au->firsterg);
		fprintf(pfile,"ende=%s\n",
			gbool(au->ende));
		au++;
	}
}


#ifdef __STDC__
void printfparam(gramptr g)
#else /* ! __STDC__ */
void printfparam(g)
gramptr g;
#endif /* ! __STDC__ */
{
int i;
fparam *fp;

	fprintf(pfile,"****** fparamtab *******\n");
	fp = &g->fparamtab[1];

	for(i=1; i <= g->anzfparam; i++) {
		fprintf(pfile,"%3d  '%-12.12s'  typ[%3d]  ",
			i, gnam(g,g->typtab[fp->typ].name), fp->typ);
		fprintf(pfile,"ende=%s\n",
			gbool(fp->ende));
		fp++;
	}
}


#ifdef __STDC__
void printaparam(gramptr g)
#else /* ! __STDC__ */
void printaparam(g)
gramptr g;
#endif /* ! __STDC__ */
{
int i;
aparam *ap;
attrposIndex apos;
attrIndex anum;
vocabelIndex tnum;
int term;
entryIndex name;
	fprintf(pfile,"****** aparamtab *******\n");
	ap = &g->aparamtab[1];

	for(i=1; i <= g->anzaparam; i++) {
		fprintf(pfile,"%3d  ",i);
		apos = ap->aktparam;
		anum = g->attrpostab[apos].attr;
		tnum = g->attrtab[anum].voc;
		term = tnum > g->anznonterm;
		if (term)
			name = g->termtab[tnum - g->anznonterm].name;
		else
			name = g->nontermtab[tnum].name;

		fprintf(pfile,"'%-12.12s'.'%-12.12s' ",
			gnam(g,name), gnam(g,g->attrtab[anum].name));
		fprintf(pfile,"attrpos=%3d  ",apos);
		fprintf(pfile,"ende=%s\n",
			gbool(ap->ende));
		ap++;
	}
}



