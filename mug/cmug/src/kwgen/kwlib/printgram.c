/*************************************************************************
*
*  printgram.c
*
*  Hilfsprogramm zum drucken der Grammatik
*  direkt aus der Internform
*
*  28.03.90  letzte Aenderung 
*************************************************************************/

#include <stdio.h>
#include "gramtyp.h"

extern gramptr gr;


identifier gnam(g, e)
gramptr g;
entryIndex e;
{
	return (g->entrytab[e].name);
}

identifier gbool(b)
bool b;
{
	return (b ? "TRUE " : "FALSE");
}

void printgram();
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

FILE *pfile;

void printgram()
{
	gramptr g=gr;

	pfile = fopen("aginternform","w");
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

void printentry(g)
gramptr g;
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


void printterm(g)
gramptr g;
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


void printnonterm(g)
gramptr g;
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


void printfunct(g)
gramptr g;
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


void printattribut(g)
gramptr g;
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


void printproduct(g)
gramptr g;
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


void printtyp(g)
gramptr g;
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


void printprodpos(g)
gramptr g;
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


void printattrpos(g)
gramptr g;
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


void printaufruf(g)
gramptr g;
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


void printfparam(g)
gramptr g;
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


void printaparam(g)
gramptr g;
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



