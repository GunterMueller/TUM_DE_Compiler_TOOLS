/*************************************************************************
*
*  transformag.c
*
*  Hilfsprogramm zum Eliminieren von Functionen mit Mehrfachergebnissen
*  ueber die Zugriffsfunktionen
*
*  03.07.91  Wittner
*************************************************************************/

#include <stdio.h>
#include "zufunc.h"


typedef struct lst *plst;
typedef struct lst {
		Attrpos ap;
		plst next;
		} lst;

plst AttrBerLst;
FILE *ofile;

void DruckeFunctions();
void DruckeNonterms();
void DruckeTerms();
void DruckeBerechnung();
void DruckeAuxs();

#ifdef __STDC_
int mehrfacherg_aufruf(Aufruf aufr)
#else
int mehrfacherg_aufruf(aufr)
Aufruf aufr;
#endif
{
Aparam ap;

 return((ap=FirstErg(aufr)) && NextErg(ap)) ;
}



#ifdef __STDC_
int mehrfacherg_funct(Funct f)
#else
int mehrfacherg_funct(f)
Funct f;
#endif
{
Fparam fp;

 return((fp=FirstFErg(f)) && NextFErg(fp)) ;
}


#ifdef __STDC_
void ErgTyp(Funct f)
#else
void ErgTyp(f)
Funct f;
#endif
{
fprintf(ofile,"_E_%s",SymString(Funkt_Name(f)) );
}


#ifdef __STDC_
void NewFuncName(Funct f, int n)
#else
void NewFuncName(f, n)
Funct f;
int n;
#endif
{
fprintf(ofile,"_%d_%s",n,SymString(Funkt_Name(f)) );
}


#ifdef __STDC_
void NewAuxName(Attrpos ap, Prodpos pp)
#else
void NewAuxName(ap, pp)
Attrpos ap;
Prodpos pp;
#endif
{
fprintf(ofile,"%s_%s",
	SymString(Attr_Name(Attr_Of_AttPos(ap))),
	SymString(Sym_Name(Grm_Symbol(pp))) );
}


zufuncgram()
{
	ofile = fopen("internform.zufunc","w");
	fprintf(ofile,"grammar %s: %s -> %s ;\n\n",
		SymString(GetPhasenId()),SymString(GetInGName()),
		SymString(GetOutGName()) );
	DruckeFunctions();
	DruckeNonterms();
	DruckeTerms();
	fprintf(ofile,"axiom %s\n\n",SymString(Sym_Name(FirstSym())));
	fputs("productions\n\n",ofile);
	DruckeSem();
	fputs("\ngrammarend\n",ofile);
	fclose(ofile);
}

#ifdef __STDC__
void DruckeFparam(Fparam fp)
#else /* ! __STDC__ */
void DruckeFparam(fp)
Fparam fp;
#endif
{
Fparam hfp;

if ( (hfp=fp) != NIL )
   {
   fputs("(",ofile);
   while (hfp != NIL )
      {
      fputs(SymString(Typ_Name(Typ_Of_Fparam(hfp))),ofile);
      if ( (hfp=NextFPar(hfp)) != NIL) fputs(", ",ofile);
      }
   fputs(")",ofile);
   }
fputs(": ",ofile);
}

#ifdef __STDC__
void DruckeErgparam(Fparam fp)
#else /* ! __STDC__ */
void DruckeErgparam(fp)
Fparam fp;
#endif
{
Fparam erg;

if ( (erg=fp) != NIL )
   {
   if ( NextFErg(fp) != NIL) fputs("(",ofile);
   while (erg != NIL )
      {
      fputs(SymString(Typ_Name(Typ_Of_Fparam(erg))),ofile);
      if ( (erg=NextFErg(erg)) != NIL) fputs(", ",ofile);
      }
   if ( NextFErg(fp) != NIL) fputs(")",ofile);
   }
}


#ifdef __STDC__
void DruckeNewFunctions(Funct f)
#else /* ! __STDC__ */
void DruckeNewFunctions(f)
Funct f;
#endif
{
Fparam erg;
int n = 0;

erg=FirstFErg(f);
do
  {
  fputs("function ",ofile);
  NewFuncName(f,++n);
  fputs("(",ofile);
  ErgTyp(f);
  fputs("): ",ofile);
  fputs(SymString(Typ_Name(Typ_Of_Fparam(erg))),ofile);
  fputs(";\n",ofile);
  } while ( (erg=NextFErg(erg)) != NIL);
}

void DruckeFunctions()
{
  Funct f;
  f=FirstFunct();
  while ( f != NIL )
     {
     if ( FirstFErg(f) != NIL ) /* keine Copy-Function */
        {
	fputs("function ",ofile);
	if (mehrfacherg_funct(f))
	  {
	  NewFuncName(f,0);
          DruckeFparam(FirstFPar(f));
	  ErgTyp(f);
	  fputs(";\n",ofile);
	  DruckeNewFunctions(f);
	  }
	else
	  {
          fputs(SymString(Funkt_Name(f)),ofile);
          DruckeFparam(FirstFPar(f));
	  DruckeErgparam(FirstFErg(f));
	  fputs(";\n",ofile);
	  }
        }
     f=NextFunct(f);
     }
}
     

void DruckeNonterms()
{
Vocabel Nt;

Nt=FirstSym();
if ( Nt != NIL ) fputs("\nnonterminals\n\n",ofile);
while(Nt)
   {
   if ( ! Is_Terminal(Nt))
      {
      fputs(SymString(Sym_Name(Nt)),ofile);
      DruckeAttrs(Nt);
      fputs("\n",ofile);
      }
   Nt=NextSym(Nt);
   }
}

void DruckeTerms()
{
Vocabel t;

fputs("\nterminals\n\n",ofile);
t=FirstSym();
while(t)
   {
   if ( Is_Terminal(t))
      {
      fputs(SymString(Sym_Name(t)),ofile);
      if ( Is_Semantisch(t) ) fputs("\tsem",ofile);
      fputs("\n",ofile);
      }
   t=NextSym(t);
   }
fputs("\t;\n\n",ofile);
}

DruckeSem()
{
Vocabel voc;
	voc = FirstSym();
	while(voc)
	  {
	  if(! Is_Terminal(voc)) DruckeProds(voc);
	  voc = NextSym(voc);
	  }
}

DruckeAttrs(voc)
Vocabel voc;
{
Attr attr;
   attr = FirstAttr(voc);
   if ( attr != NIL )
	{
	fprintf(ofile,"  attributes\n");
	while(attr) {
		fprintf(ofile,"\t%s : %s ",
			SymString(Attr_Name(attr)),
			SymString(Typ_Name(Typ_Of_Attr(attr))) );
		if(Is_Inherited(attr))fputs("inherited",ofile);
		else fputs("synthesized",ofile);
		if(Is_SynTyp(attr))fprintf(ofile," syntactic\n"); else fprintf(ofile,"\n"); 
		attr = NextAttr(attr);
		}
	}
	fputs("\t\t;",ofile);
}

int existiert_semantik(prod)
Product prod;
{
Prodpos ppos;
Attrpos apos;

if ( FirstAuxPos(prod) != NIL ) return TRUE;
ppos = FirstPPos(prod);
while(ppos)
   {
   apos=FirstAPos(ppos);
   while (apos != NIL)
      {
      if (Ber_Aufruf(apos) != NIL) return TRUE;
      apos=NextAPos(apos);
      }
   ppos = NextPPos(ppos);
   }
return FALSE;
}



DruckeProds(voc)
Vocabel voc;
{
Product prod;
int sem;
	prod = FirstProd(voc);
	while(prod) {
		fprintf(ofile,"\nsyn  %s: ",SymString(Prod_Name(prod)));
		DruckePpos(prod);
		if ( existiert_semantik(prod))
			{
			fputs("sem\n",ofile);
			DruckeAuxs(prod);
			DruckeBers(prod);
			fputs("\nsemend\n",ofile);
			}
		prod = NextProd(prod);
	}
}

void DruckeAuxs(prod)
Product prod;
{
Aparam apar;
Aufruf aufr;
Funct f;
Prodpos pp;
Attrpos ap;
int auxiliarys = FALSE;

AttrBerLst=NULL;
ap = FirstAuxPos(prod);
if ( ap != NIL )
   {
   fputs("  auxiliarys",ofile);
   auxiliarys=TRUE;
   }
while(ap)
	{
	fprintf(ofile,"\n\t%s : %s",
		SymString(Attr_Name(Attr_Of_AttPos(ap))),
		SymString(Typ_Name(Typ_Of_Attr(Attr_Of_AttPos(ap)))) );
	if ((aufr=Ber_Aufruf(ap)) != NIL )
	   if ( mehrfacherg_funct((f=Funkt_Of_Aufruf(aufr))))
	     if ( ! schon_berechnet(ap) )
		{
		apar=FirstErg(aufr);
		do add_ap(apar);
		while( (apar=NextErg(apar)) != NIL);
		  {
		  fputs("\n\t",ofile);
		  NewAuxName(ap,FirstPPos(prod));
		  fputs(" : ",ofile);
		  ErgTyp(f);
		  }
		}
	ap = NextAuxPos(ap);
	} /* while(ap) */

/* Auxiliarys, die durch Attributberechnung mit Funktionen mit Mehrfach-
   Ergebnissen entstehen
*/
pp=FirstPPos(prod);
while ( pp != NIL )
  {
  ap=FirstAPos(pp);
  while ( ap != NIL )
   {
   if ((aufr=Ber_Aufruf(ap)) != NIL )
      if ( mehrfacherg_funct((f=Funkt_Of_Aufruf(aufr))))
         {
         if ( ! schon_berechnet(ap) )
            {
            apar=FirstErg(aufr);
            do
                {
                add_ap(apar);
                } while ( (apar=NextErg(apar)) != NIL);
            if ( ! auxiliarys )
                {
                fputs("auxiliarys",ofile);
                auxiliarys=TRUE;
                }
            fputs("\n\t",ofile);
            NewAuxName(ap,pp);
            fputs(" : ",ofile);
            ErgTyp(f);
            }
         }
    ap=NextAPos(ap);
    }
  pp=NextPPos(pp);
  }

if (auxiliarys) fputs(";\n\n",ofile);
}

#ifdef __STDC__
void DruckePposPos(int p)
#else
void DruckePposPos(p)
int p;
#endif
{
if ( p != -1 ) fprintf(ofile,"<%d>",p);
}

DruckePpos(prod)
Product prod;
{
Prodpos ppos;
	ppos = FirstPPos(prod);
	fputs(SymString(Sym_Name(Grm_Symbol(ppos))),ofile );
	DruckePposPos(PPos_Pos(ppos));
	fputs(" -> ",ofile);
	ppos = NextPPos(ppos);
	while(ppos) {
		fputs(SymString(Sym_Name(Grm_Symbol(ppos))), ofile );
		DruckePposPos(PPos_Pos(ppos));
		fputs(" ",ofile);
		ppos = NextPPos(ppos);
	}
	fprintf(ofile,".\n");
}

DruckeBers(prod)
Product prod;
{
Prodpos ppos;
Attrpos apos;

	AttrBerLst=NULL;
	apos = FirstAuxPos(prod);
	while(apos) {
		DruckeBerechnung(apos,prod);
		apos = NextAuxPos(apos);
	}
	ppos = FirstPPos(prod);
	while(ppos) {
		DruckeApos(ppos,prod);
		ppos = NextPPos(ppos);
	}
}

DruckeApos(ppos,prod)
Prodpos ppos;
Product prod;
{
Attrpos apos;
	apos = FirstAPos(ppos);
	while(apos) {
		DruckeBerechnung(apos,prod);
		apos = NextAPos(apos);
	}
}


int schon_berechnet(ap)
Attrpos ap;
{
plst h;

h=AttrBerLst;
while (h)
  {
  if ((*h).ap == ap) return TRUE;
  h=(*h).next;
  }
return FALSE;
}



int add_ap(apar)
Aparam apar;
{
plst h;

  if ( (h=(plst)malloc(sizeof(struct lst))) == NULL)
    {
    fputs("Abbruch: Speichermangel\n",stderr);
    exit(1);
    }
  (*h).ap=AttPos_Of_Param(apar);
  (*h).next=AttrBerLst;
  AttrBerLst=h;
}


void MehrfachErg(aufr,ap,prod)
Aufruf aufr;
Attrpos ap;
Product prod;
{
int n = 0;
plst h;
Aparam apar;
Funct f;
Attrpos hap;
Prodpos hpp;
char *GrSymName;

if ( schon_berechnet(ap)) return;

hpp=FirstPPos(prod);
fputs("\n",ofile);
fputs(GrSymName=SymString(Sym_Name(Grm_Symbol(hpp))),ofile);
DruckePposPos(PPos_Pos(hpp));
fputs(".",ofile);
NewAuxName(ap,PPos_Of_AttPos(ap));
fputs(" = ",ofile);
NewFuncName(f=Funkt_Of_Aufruf(aufr),0);
DruckeArgs(aufr,TRUE);
fprintf(ofile," $\n");

apar=FirstErg(aufr);
do
  {
  add_ap(apar); 
  n++;
  hap=AttPos_Of_Param(apar);
  fputs(SymString(Sym_Name(Grm_Symbol(PPos_Of_AttPos(hap)))),ofile);
  DruckePposPos(PPos_Pos(PPos_Of_AttPos(hap)));
  fputs(".",ofile);
  fputs(SymString(Attr_Name(Attr_Of_AttPos(hap))),ofile);
  fputs(" = ",ofile);
  NewFuncName(f,n);
  fputs("(",ofile);
  fputs(GrSymName,ofile);
  DruckePposPos(PPos_Pos(hpp));
  fputs(".",ofile);
  NewAuxName(ap,PPos_Of_AttPos(hap));
  fputs(") $\n",ofile);
  } while ( (apar=NextErg(apar)) != NIL);
}


void DruckeBerechnung(apos,prod)
Attrpos apos;
Product prod;
{
Aufruf aufr;
	aufr = Ber_Aufruf(apos);
	if(aufr) {
	  if ( mehrfacherg_aufruf(aufr))
		MehrfachErg(aufr,apos,prod);
	  else
		{
		DruckeErgs(aufr);
		fprintf(ofile," = ");
		if(Is_Copy(aufr))
		  DruckeArgs(aufr,FALSE);
		else
		  {
		  fputs(SymString(Funkt_Name(Funkt_Of_Aufruf(aufr))),ofile );
		  DruckeArgs(aufr,TRUE);
		  }
		fprintf(ofile," $\n");
		}
	}
}

DruckeArgs(aufr,klammer)
Aufruf aufr;
int klammer;
{
Attrpos hap;
Aparam apar;

  if ( (apar = FirstArg(aufr)))
    {
    if (klammer) fputs("(",ofile);
    while(apar)
      {
      hap=AttPos_Of_Param(apar);
      fputs(SymString(Sym_Name(Grm_Symbol(PPos_Of_AttPos(hap)))),ofile);
      DruckePposPos(PPos_Pos(PPos_Of_AttPos(hap)));
      if  (! Is_Terminal(Grm_Symbol(PPos_Of_AttPos(hap))))
	  {
          fputs(".",ofile);
          fputs(SymString(Attr_Name(Attr_Of_AttPos(hap))),ofile);
          }
      apar = NextArg(apar);
      if(apar) fputs(",",ofile);
      }
    if ( klammer) fputs(")",ofile);
    }
}

DruckeErgs(aufr)
Aufruf aufr;
{
Aparam apar;
Attrpos hap;
int klammer = FALSE;

  apar = FirstErg(aufr);
  if ( apar != NIL && NextErg(apar) != NIL ) 
	{
        klammer = TRUE;
	fputs("(",ofile);
        }
  while(apar)
  {
  hap=AttPos_Of_Param(apar);
  fputs(SymString(Sym_Name(Grm_Symbol(PPos_Of_AttPos(hap)))),ofile);
  DruckePposPos(PPos_Pos(PPos_Of_AttPos(hap)));
  fputs(".",ofile);
  fputs(SymString(Attr_Name(Attr_Of_AttPos(hap))),ofile);
  apar = NextErg(apar);
  if(apar)fprintf(ofile,",");
  }
  if ( klammer ) fputs(")",ofile);
}
