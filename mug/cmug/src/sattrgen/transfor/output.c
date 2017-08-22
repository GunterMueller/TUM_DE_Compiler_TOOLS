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

/* Aktueller Stand : 13.11.89 */
/* Aenderungen:  */
/* Aufruf von rekeintrag in printcpatt gestrichen */ 
/* output.c jetzt ein Modul !                     */
/* maxprodnr jetzt durch CardProd() Aufruf belegt */

/*****************************************************/
/* Programmteil zur Ausgabe der Daten und Ergebnisse */
/*****************************************************/

#define maxpartlength 6  /* maxlaenge eines Identifier-Teiles */
#define EXTERN extern
#include "globals.h"
EXTERN long semerrors;

extern ptmerketm mtmenge;
extern FILE *errordatei;
/* Oh je, oh je aber sonst werden die Ausgaben von drucke.. nicht */
/* auch auf die Fehlerdatei geschrieben !!!                       */
#ifdef __STDC__
ptcopy copyproof(Product pprod, Prodpos pprodpos);

integer kdsym (FILE *out, Entry s)
          
#else /* ! __STDC__ */
ptcopy copyproof();
#endif /* ! __STDC__ */
        
#ifndef __STDC__
integer kdsym (out, s)
FILE *out;
Entry s;
#endif /* ! __STDC__ */
/* druckt symbol und liefert laenge des namens */
{
	DruckeSym(out, s);
	return((integer) strlen(SymString(s)));
}

#ifdef __STDC__
void kdrusym(FILE *out, Entry s, integer l)
          
        
          
#else /* ! __STDC__ */
void kdrusym(out, s, l)
FILE *out;
Entry s;
integer l;
#endif /* ! __STDC__ */
/* druckt symbolnamen in der angegebenen laenge */
{
	l -= kdsym(out, s);
	while(l > 0){ 
		fprintf(out," "); 
		l--;
	}
}

#ifdef __STDC__
void druckeapos(FILE *out, Attrpos x)
          
          
#else /* ! __STDC__ */
void druckeapos(out, x)
FILE *out;
Attrpos x;
#endif /* ! __STDC__ */
/* name und position einer Attributposition */
{
	DruckeSym(out, Sym_Name(Grm_Symbol(PPos_Of_AttPos(x))));
	fprintf(out,"<%1d>",PPos_Nummer(PPos_Of_AttPos(x)));
	DruckeSym(out, Attr_Name(Attr_Of_AttPos(x)));
}

#ifdef __STDC__
void drucpnam(FILE *out, integer numb)
          
             
#else /* ! __STDC__ */
void drucpnam(out, numb)
FILE *out;
integer numb;
#endif /* ! __STDC__ */
/* druckt copy-namen */
{
	fprintf(out,"CP%1d",numb);
}

/* Ausgabe aller Attribute, die in teilm enthalten sind mit der
   Information, welche teilmengen identifiziert,
	d.h in ihrer Attributreihenfolge korreliert sind. */
#ifdef __STDC__
void druckeatt(FILE *out, ptteilmenge teilm)
#else /* ! __STDC__ */
void druckeatt(out, teilm)
FILE *out;
ptteilmenge teilm;
#endif /* ! __STDC__ */
{
	ptteilmenge pteilm,idptm,pt;
	ptattmenge  patt;
	ptglobdat   glob;

	pteilm = teilm;
	while(pteilm != ((ptteilmenge)NIL)){
		fprintf(out,"          ---- \n");
		fprintf(out,"         | ");
		DruckeSym(out, Attr_Name(pteilm->attring->attname));
		if ((pteilm->identtm != pteilm) &&
		    (pteilm->attring != pteilm->attring->nachatt )){
			fprintf(out, " identifiziert mit : ");
			idptm = pteilm->identtm;
			while (idptm != pteilm){
				if (idptm != pteilm->identtm)
					fprintf(out, " , \n           ");
				DruckeSym(out, Attr_Name(idptm->attring->attname));
				glob = globstrukt;
				while (glob != ((ptglobdat)NIL)){
					if (Is_Inherited(idptm->attring->attname))
						pt = glob->inherettm;
					else 
					    pt = glob->derivedtm;
					while ((pt != ((ptteilmenge)NIL)) && (pt != idptm))
						pt = pt->nachftm;
					if (pt == ((ptteilmenge)NIL))
						glob = glob->nachfsymb;
					else {
						fprintf(out, " of ");
						DruckeSym(out, Sym_Name(glob->symbname));
						glob = ((ptglobdat)NIL);
					}
				}
				idptm = idptm->identtm;
			}
			fprintf(out, " .");
		}
		fprintf(out,"\n");

		patt = pteilm->attring->nachatt;
		while (patt != pteilm->attring){
			fprintf(out, "         | ");
			DruckeSym(out, Attr_Name(patt->attname));
			fprintf(out, "\n");
			patt = patt->nachatt;
		}
		pteilm = pteilm->nachftm;
	}
	if (teilm != ((ptteilmenge)NIL)) fprintf(out, "          ----\n");
}


/* Ausgabe der Globaldatenstruktur */
/* Also alle Symbole mit ihren Attributen in der berechneten  optimalen
   Reihenfolge */

#ifdef __STDC__
void globprint (FILE *out)
#else /* ! __STDC__ */
void globprint (out)
FILE *out;
#endif /* ! __STDC__ */
{
	ptglobdat pglob;

	pglob = globstrukt;
	fprintf(out, "\n\n");
	while(pglob !=((ptglobdat)NIL)){
		fprintf(out, "\n");
		DruckeSym(out, Sym_Name(pglob->symbname));
		fprintf(out, " : \n");
		if (pglob->inherettm != ((ptteilmenge)NIL)){
			fprintf(out, "      inherited Attribute :\n");
			druckeatt(out, pglob->inherettm);
			fprintf(out, "\n");
		}
		if (pglob->derivedtm != ((ptteilmenge)NIL)){
			fprintf(out, "        derived Attribute :\n");
			druckeatt(out, pglob->derivedtm);
			fprintf(out, "\n");
		}
		pglob = pglob->nachfsymb;
	}
}

/*******************************************************************/
/* Ausgabe der Produktionen und Berechnungsregeln der Copy-Symbole */
/*******************************************************************/

#ifdef __STDC__
integer suche (Aparam q)
         
#else /* ! __STDC__ */
integer suche (q)
Aparam q;
#endif /* ! __STDC__ */
/* liefert die Zell-Nr. der Zelle der Lokdat, die die attrpos zur */
/* angegebenen quelle enthaelt                 */
{
	integer ergebnis, zahl;
	Attrpos atp;

	ergebnis = 0;
	atp = AttPos_Of_Param(q);
	zahl = beranfang - 1;
	while (zahl >= 1){
		if (lokstrukt[zahl - 1].attpos == atp){
			ergebnis = zahl;
			zahl = 0;
		}
		else
			zahl -= 1;
	}
	return(ergebnis);
}


#ifdef __STDC__
boolean printcpatt (FILE *o, FILE *o1, ptcopy cp)
            
          
#else /* ! __STDC__ */
boolean printcpatt (o, o1, cp)
FILE *o,*o1;
ptcopy cp;
#endif /* ! __STDC__ */
/* steuert die Ausgabe der Cop-Attribute.             */
/* wird eines der inherited attr von 'suche' nicht gefunden */
/* so ist die Eingabegrammatik nicht LR-attributiert und    */
/* die weitere Ausgabe wird durch das Funktionsergebnis '0' */
/* gestoppt                    */
{
	integer loop,zelle,is,ds,j;
	Attrpos atp, hatp;
	Aparam ptq;
	ptmerketm mtm;
	Prodpos ptp;

	j = 2*maxpartlength;

	globtolok(cp->prod, cp->propos, TRUE);
	is = loklength - cp->inhnumb + 1;
	zelle = beranfang;
	beranfang = is;
	/* anschrift des ersten inherited Attributes */

	/* Test auf LR-Attributiertheit */
	/* Suchen des linkesten(oder tiefsten) Attributs im Keller */
	for (loop = beranfang; loop <= loklength; loop++){
		if (zelle > 0){
			atp = lokstrukt[loop-1].attpos;
			ptq = FirstArg(Ber_Aufruf(atp));
			while (ptq != ((Aparam)NIL)){
				hatp = optargpos(cp->prod, AttPos_Of_Param(ptq));
				if (!Is_Auxiliary(hatp)){ /* Die Urquelle muss im Keller sein */
					zelle = atpsuche(hatp);
					if (is > zelle) is = zelle;
 				}
				/* Echte Aux, die berechnet werden muessen sind im AUX-Keller */
				ptq = NextArg(ptq);
			}
		}
	}
	if (zelle > 0){
		if (mtmenge->adresse <= is) /**/
			while ((mtmenge->ntm != NIL) /**/
			    && (mtmenge->ntm->adresse <= is)) mtmenge = mtmenge->ntm;

		is = mtmenge->adresse;
		/* kuerzen der Lokaldatenstruktur */

		loklength = loklength - is + 1;
		beranfang = loklength - cp->inhnumb + 1;
		mtm = mtmenge;
		while (mtm != ((ptmerketm)NIL)){
			mtm->adresse = mtm->adresse - is + 1;
			mtm = mtm->ntm;
		}
		for (loop = 1; loop <= loklength; loop++){
			lokstrukt[loop - 1].attr = lokstrukt[loop + is - 2].attr;
			lokstrukt[loop - 1].attpos = lokstrukt[loop + is - 2].attpos;
		}

		 auffuellen(loklength+1);

		/* Ausdruck der inherited Attribute */
		/* das sind alle Attribute des Kellers, die ueber dem tiefsten
			gebrauchten Attribut im Keller stehen (inkl.) */
		for (loop = 1; loop < beranfang; loop++){
			fprintf(o1, "I");
			is = fprintf(o1,"%1d",loop);
			kdrusym(o1, Typ_Name(Typ_Of_Attr(lokstrukt[loop - 1].attr)), (j+3-is));
			fprintf(o1, " : ");
			kdrusym(o1, Typ_Name(Typ_Of_Attr(lokstrukt[loop - 1].attr)), j);
			fprintf(o1, " INHERITED \n");
			fprintf(o1, "                            ");
		}


		fprintf(o, "          SEM     ");

		/* Ausdruck der derived Attribute sowie der Berechnungsregeln */
		for (loop = 1; loop <= cp->inhnumb; loop++){
			drucpnam(o, cp->name);
			atp = lokstrukt[loop + beranfang - 2].attpos;
			fprintf(o, ".D");
			if (cp->inhnumb <= 99)
				ds = fprintf(o, "%1d", loop);
			else {
				ds = 3;
				fprintf(o, "%3d", loop);
			}
			kdrusym(o, Typ_Name(Typ_Of_Attr(Attr_Of_AttPos(atp))), (j+3-ds));
			fprintf(o, " = ");
			ptq = FirstArg(Ber_Aufruf(atp));
			if (Is_Copy(Ber_Aufruf(atp))){
				hatp = optargpos(cp->prod, AttPos_Of_Param(ptq));
				if(Is_Auxiliary(hatp)){
					fprintf(o, "AUX(");
					DruckeSym(o, Attr_Name(Attr_Of_AttPos(AttPos_Of_Param(ptq))));
					fprintf(o, ") $\n");
 				}
				else {
					drucpnam(o, cp->name);
					zelle = atpsuche(hatp);
					fprintf(o, ".I");
					is = fprintf(o, "%1d", zelle);
					DruckeSym(o, Typ_Name(Typ_Of_Attr(lokstrukt[zelle-1].attr)));
					fprintf(o, "   $\n");
				}
			}
			else {
				DruckeSym(o, Funkt_Name(Funkt_Of_Aufruf(Ber_Aufruf(atp))));
				if (ptq != ((Aparam)NIL)){
					fprintf(o, "(");
					while (ptq != ((Aparam)NIL)){
				hatp = optargpos(cp->prod, AttPos_Of_Param(ptq));
				if(Is_Auxiliary(hatp)){
					fprintf(o, "AUX(");
					DruckeSym(o, Attr_Name(Attr_Of_AttPos(AttPos_Of_Param(ptq))));
					fprintf(o, ") ");
 				}
				else {
						drucpnam(o, cp->name);
						zelle = atpsuche(hatp);
						fprintf(o, ".I");
						is = fprintf(o, "%1d", zelle);
						DruckeSym(o, Typ_Name(Typ_Of_Attr(lokstrukt[zelle-1].attr)));
				}
						ptq = NextArg(ptq);
						if (ptq != ((Aparam)NIL)) fprintf(o, ",");
					}
					fprintf(o, ")");
				}
				fprintf(o, "   $\n");
			}
			fprintf(o1, "D%1d", loop);
			kdrusym(o1, Typ_Name(Typ_Of_Attr(lokstrukt[loop+beranfang-2].attr)),
			(j+3-ds));
			fprintf(o1, " : ");
			kdrusym(o1,Typ_Name(Typ_Of_Attr(lokstrukt[loop+beranfang-2].attr)), j);
			fprintf(o1, " SYNTHESIZED ");
			if (loop == cp->inhnumb){
				fprintf(o1, "; \n");
				fprintf(o, "          SEMEND \n");
			}
			else {
				fprintf(o1, "\n                            ");
				fprintf(o, "             ");
			}
		}  

		return(true);
	}
	else {
		semerrors++;
		wErrorf(NULL, "\n *** Eingabegrammatik ist nicht L-attributiert ***\n");
		wErrorf(NULL, " Klartext-Ausgabe abgebrochen.\n");
		wErrorf(NULL, " Fehler in Produktion :\n ");
		ptp = druckelokprod(stderr, cp->prod);
		if (errordatei != NULL)
		  ptp = druckelokprod(errordatei, cp->prod);
		wErrorf(NULL, "Regelverletzung bei Berechnung des Attributs : ");
		druckeapos(stderr, atp);
		if (errordatei != NULL)
		  druckeapos(errordatei, atp);
		wErrorf(NULL, "\n");
	}
}


#ifdef __STDC__
void printcopy (FILE *out, FILE *out1)
                
#else /* ! __STDC__ */
void printcopy (out, out1)
FILE *out,*out1;
#endif /* ! __STDC__ */
/* steuert die Copy-Ausgabe */
{
	integer loop, maxname, maxprodnr;
	ptcopy cp, cp1;
	boolean l_att;

	forcopy = true;
	foroutput = false;
	l_att = true;

	/* Anzahl der Copy-Symbole feststellen */

	maxname = 0;
	cp = copyinfo;
	while (cp != ((ptcopy)NIL)){
		if (maxname < cp->name) maxname = cp->name;
		cp = cp->nextcopy;
	}

	/* Anzahl der bisherigen Produktionen feststellen */

	maxprodnr = CardProd();   

	/* Eigentliche Ausgabesteuerung */

	for (loop = 1; loop <= maxname; loop++){
		if (l_att){
			cp = copyinfo;
			cp1 = ((ptcopy)NIL);
			while (cp != ((ptcopy)NIL)){
				if (cp->name == loop){
					cp1 = cp;
					cp = ((ptcopy)NIL);
				}
				else
					cp = cp->nextcopy;
			}
			if (cp1 != ((ptcopy)NIL)){
				maxprodnr++;
				fprintf(out, "\nSYN P%3d : ", maxprodnr);
				fprintf(out1, "\n");
				drucpnam(out, loop);
				fprintf(out, " -> .\n");
				drucpnam(out1, loop);
				fprintf(out1, "        ATTRIBUTES     ");
				l_att = printcpatt(out, out1, cp1);
			}
		}
	}
	fprintf(out1,"\n");
	forcopy = false;
}

/******************************************************************/ 
/* Ausgabe der errechneten Daten: Produktionen, Berechnungsregeln */
/******************************************************************/

/* Ausgabe der Berechnungsregeln der prodpos p derived Attribute */
#ifdef __STDC__
void lokpr (FILE *out, Prodpos p)
#else /* ! __STDC__ */
void lokpr (out, p)
FILE *out;
Prodpos p;
#endif /* ! __STDC__ */
{
	integer loop,h,j,n;
	Aparam ptq;
	Attrpos pap, ptap;

	j = 3*maxpartlength;

	pap = FirstAPos(p);
	while ((pap != ((Attrpos)NIL)) && (Is_Inherited(Attr_Of_AttPos(pap))))
		pap = NextAPos(pap);

	if (pap != ((Attrpos)NIL))
		fprintf(out, "\n     SEM      ");

	/* Ausdruck der Berechnungsregeln */
	while (pap != ((Attrpos)NIL)){
		h = kdsym(out, Sym_Name(Grm_Symbol(PPos_Of_AttPos(pap)))) + 1;
		fprintf(out, "<0>.");
		kdrusym(out, Attr_Name(Attr_Of_AttPos(pap)), (j-h));
		fprintf(out, " = ");
		ptq = FirstArg(Ber_Aufruf(pap));
		if (Is_Copy(Ber_Aufruf(pap))){
			ptap = AttPos_Of_Param(ptq);
			DruckeSym(out, Sym_Name(Grm_Symbol(PPos_Of_AttPos(ptap))));
			n = PPos_Nummer(PPos_Of_AttPos(ptap));
			fprintf(out, "<%1d>.", n);
			DruckeSym(out, Attr_Name(Attr_Of_AttPos(ptap)));
		}
		else {
			DruckeSym(out, Funkt_Name(Funkt_Of_Aufruf(Ber_Aufruf(pap))));
			if (ptq != ((Aparam)NIL)){
				fprintf(out,"(");
				while (ptq != ((Aparam)NIL)){
					ptap = AttPos_Of_Param(ptq);
					DruckeSym(out, Sym_Name(Grm_Symbol(PPos_Of_AttPos(ptap))));
					n = PPos_Nummer(PPos_Of_AttPos(ptap));
					fprintf(out,"<%1d>.", n);
					DruckeSym(out, Attr_Name(Attr_Of_AttPos(ptap)));
					ptq = NextArg(ptq);
					if (ptq != ((Aparam)NIL)) fprintf(out, ",");
				}
				fprintf(out, ")");
			}
		}
		fprintf(out, "   $\n");
		pap = NextAPos(pap);
		while((pap != ((Attrpos)NIL)) && (Is_Inherited(Attr_Of_AttPos(pap))))
			pap = NextAPos(pap);
		if (pap != ((Attrpos)NIL)) fprintf(out, "           ");
	}
	if (FirstAPos(p) != ((Attrpos)NIL))
		fprintf(out, "     SEMEND  \n");

	/* Ausgabe des Kellerinhalts */
	fprintf(out, "\n      (*      \n");
	fprintf(out, "      Kellerinhalt  \n");
	for (loop = 1; loop <= loklength; loop++){
		if (lokstrukt[loop-1].index != 0)
			fprintf(out, "      ------------------------\n");
		fprintf(out, "     | ");
		druckeapos(out, lokstrukt[loop-1].attpos);
		fprintf(out, "\n");
	}
	fprintf(out, "      ------------------------\n");
	fprintf(out, "      *)    \n\n");
}


/* Ausdruck einer Produktion (Nur sie selber, ohne Berechnungsregeln) */
#ifdef __STDC__
Prodpos druckelokprod (FILE *out, Product x)
#else /* ! __STDC__ */
Prodpos druckelokprod (out, x)
FILE *out;
Product x;
#endif /* ! __STDC__ */
{
	Vocabel t;
	Prodpos h,e;
	Entry  ch;
	ptcopy cp;
   int n;

	fprintf(out, "\nSYN ");
	kdrusym(out,Prod_Name(x),4);
	fprintf(out, " : ");
	h = FirstPPos(x);
	e = h;
	t = Grm_Symbol(h);
	ch = Sym_Name(t);
	DruckeSym(out, ch);
	n = PPos_Nummer(h);
	fprintf(out, "<%1d>  ->  ",n);
	h = NextPPos(h);
	while (h != ((Prodpos)NIL)){
		e = h;
		cp = copyproof(x, h);
		if (cp != ((ptcopy)NIL)){
			drucpnam(out, cp->name);
			fprintf(out, " ");
		}
		t = Grm_Symbol(h);
		ch = Sym_Name(t);
		DruckeSym(out, ch);
		n = PPos_Nummer(h);
		fprintf(out, "<%1d> ",n);
		h = NextPPos(h);
	}
	fprintf(out, ".\n");
	return(e);
}

/* Drucke alle Produktionen samt Kellerinhalt usw. */
#ifdef __STDC__
void newprodprint (FILE *out, FILE *out1)
#else /* ! __STDC__ */
void newprodprint (out, out1)
FILE *out,*out1;
#endif /* ! __STDC__ */
{
	Product pro;
	Vocabel aktsym;

	foroutput = true;

	aktsym = FirstSym();
	while(aktsym != (Vocabel)NIL){
	pro = FirstProd(aktsym);
	while (pro != ((Product)NIL)) {
		globtolok(pro, druckelokprod(out, pro), TRUE);
		lokpr (out, FirstPPos(pro));
		pro = NextProd(pro);
	}
	aktsym = NextSym(aktsym);
	}
	foroutput = false;
	printcopy(out, out1);
}
