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

#include <time.h>

#define MINT 1
#define MINN -32000 /* 256 */ 

#define EXTERN extern
#include "globals.h"
EXTERN long  semerrors;

#ifdef __STDC__
ptglobdat findsymbol(Vocabel ps);
ptcopy copyproof(Product pprod, Prodpos pprodpos);
void druckeapos(FILE *out, Attrpos x);
#else /* ! __STDC__ */
ptglobdat findsymbol();
ptcopy copyproof();
void druckeapos();
#endif /* ! __STDC__ */
extern FILE *errordatei;

typedef long timet; 

char *voidptr_str = "M_voidptr";        /* Variablenname fuer void pointer */

/* Druckt die Grammatik-Internform aus */
#ifdef __STDC__
void print_grm(void)
#else /* ! __STDC__ */
void print_grm()
#endif /* ! __STDC__ */
{
	FILE *outgrm;
	char buffer[100];

	char dname[D_NAME_LAENGE + D_EXT_LAENGE + 2]; /* Punkt und abschl.0 */
	timet zeit;
	integer anznonterm,anzprod;
	integer i;
	Vocabel aktsym, axiom, symbol;
	Product aktprodukt;
	Prodpos aktprodpos;
	integer name;
	ptcopy cp;

	strcpy(buffer, SymString(GetPhasenId()));
	strncpy(phasen_id, buffer, D_NAME_LAENGE);    /* noch Platz fuer '.grm*/

	strcpy(dname, phasen_id);
	strcat(dname, ".grm");
	printf("          Eingabe fuer Parsergenerator: %s\n", dname);

	outgrm = fopen(dname, "w");

	zeit=time(0L);
	anznonterm = CardNonterm();
	anzprod = CardProd();
	fprintf(outgrm,"Transformiert am %s", ctime(&zeit));
	fprintf(outgrm,"81235431\n");
	fprintf(outgrm,"%1d %1d %1d %1d \n", MINT, MINT+CardTerm()-1,
	MINN, MINN+anznonterm+copyanz-1); 
	fprintf(outgrm,"%1d %1d \n", anzprod+copyanz, CardProdpos()-anzprod+copyname-1);
	fprintf(outgrm,"0 -1 -2 \n");
	fprintf(outgrm,"%1d \n", MINN+copyanz);

	/* Die Copy-Symbole bekommen die Nummern 1 bis copyanz   */
	/* Das Axiom die Nummer copyanz + 1                      */
	/* alle uebrigen Nonterminals Nummern > Axiom-Nummer     */
	/* (Wenn MINN = 1)                                       */

	for (i=0; i<copyanz; i++)              /* Ausgabe der Copy-Produktionen */
		fprintf(outgrm,"%1d 0 -1 \n", MINN+i);

	/* Ausgabe der Produktionen      */
	axiom = aktsym = FirstSym();          
	while ((aktsym != (Vocabel)NIL) && !(Is_Terminal(aktsym))) {      
		/* Jetzt einmal Nonterminal der linken Seite drucken */
		if (aktsym == axiom) 
			name = MINN+copyanz;
		else
			if ((integer)aktsym > (integer)axiom)
				name = MINN+copyanz+(integer)aktsym-1;
			else 
			    name = MINN+copyanz+(integer)aktsym;
		fprintf(outgrm,"%1d\n",name);
		aktprodukt = FirstProd(aktsym); 
		while (aktprodukt != (Product)NIL) {
			aktprodpos = NextPPos(FirstPPos(aktprodukt));
			/* Immer mit rechter Seite anfangen */
			while (aktprodpos != (Prodpos)NIL) {
				cp = copyproof(aktprodukt, aktprodpos);
				/* Ist an der aktuellen Position ein 
								   Copy Symbol eingefuegt worden ?
								   wenn ja dann drucke es 
								*/
				if (cp != (ptcopy)NIL)
					fprintf(outgrm,"%1d ", cp->name + MINN - 1);
				symbol = Grm_Symbol(aktprodpos);
				if (symbol == axiom) 
					name = MINN+copyanz;
				else
					if ((integer)symbol <= anznonterm) 
						/* falls Nonterminal */
						if ((integer)symbol > (integer)axiom)
							name = MINN+copyanz+(integer)symbol-1;
						else 
						    name = MINN+copyanz+(integer)symbol;
					else                               /* falls Terminal    */
					name = ((integer)symbol) - anznonterm + MINT - 1; 
				fprintf(outgrm,"%1d ",name);
				aktprodpos = NextPPos(aktprodpos);
			}
			fprintf(outgrm,"0\n");
			aktprodukt = NextProd(aktprodukt); /* naechste produktion     */
		}
		fprintf(outgrm,"-1\n");
		aktsym = NextSym(aktsym);  /* Naechstes Symbol der Grammatik */
	}
	fprintf(outgrm,"-2\n");            /* End der Regeln                 */

	/* Ausgabe der Externdarstellung  */

	aktsym = FirstSym();
	while ((integer)aktsym <= anznonterm) aktsym = NextSym(aktsym);
	while (aktsym != (Vocabel)NIL) {
		fprintf(outgrm,"%s\n", SymString(Sym_Name(aktsym)));
		aktsym = NextSym(aktsym);
	}
	for (i=1; i <= copyanz; i++)
		fprintf(outgrm,"CP%1d\n", i);
	aktsym = FirstSym();
	while ((integer)aktsym <= anznonterm) {
		fprintf(outgrm,"%s\n", SymString(Sym_Name(aktsym)));
		aktsym = NextSym(aktsym);
	}

	fclose(outgrm);
}

/* Element des Auxkellers (d.h der Info ueber den realen AUX-Keller)	 */

typedef struct auxdat * ptauxdat;
typedef struct auxdat { 
	Attrpos attpos;
	ptauxdat nachf; 
} 
auxdat;

static ptauxdat auxkeller = (ptauxdat)NIL;
static ptauxdat merkeaux  = (ptauxdat)NIL;

/* Element des Auxkellerinfos der Produktionen mit Aux-Berechnung */

typedef struct prodauxkeller *ptprodauxkeller;
typedef struct prodauxkeller { 
	Product prod;
	ptauxdat keller;
	ptprodauxkeller nachf; 
} 
prodauxkeller;

ptprodauxkeller prodakeller = (ptprodauxkeller)NIL;

#ifdef __STDC__
int auxsuche(ptauxdat keller, Attrpos atp)
#else /* ! __STDC__ */
int auxsuche(keller, atp)
ptauxdat keller;
Attrpos atp;
#endif /* ! __STDC__ */
{
	int adr=0;

	while ((keller != (ptauxdat)NIL) && (keller->attpos != atp)){
		keller = keller->nachf;
		adr ++;
	}
	if(keller == (ptauxdat)NIL)
		return(0);
	else
		return(adr+1);
}

#ifdef __STDC__
int auxklaenge(ptauxdat keller)
#else /* ! __STDC__ */
int auxklaenge(keller)
ptauxdat keller;
#endif /* ! __STDC__ */
{
	int len=0;

	while (keller != (ptauxdat)NIL){
		keller = keller->nachf;
		len++;
	}
	return(len);
}

#ifdef __STDC__
void printzyklus(FILE *out, Attrpos atp)
#else /* ! __STDC__ */
void printzyklus(out, atp)
FILE *out;
Attrpos atp;
#endif /* ! __STDC__ */
{
	ptauxdat keller = merkeaux;

	fprintf(out, "\n*** Auxiliary-Berechnungs-Zyklus erkannt: ***\n");
	druckeapos(out, atp);
	while(keller != (ptauxdat)NIL){
		fprintf(out, " <- ");
		druckeapos(out, keller->attpos);
		keller = keller->nachf;
	}
	fprintf(out, " !!!\n");
}

#ifdef __STDC__
void freekeller(ptauxdat keller)
#else /* ! __STDC__ */
void freekeller(keller)
ptauxdat keller;
#endif /* ! __STDC__ */
{
	ptauxdat hkeller;

	while(keller != (ptauxdat)NIL){
		hkeller = keller->nachf;
		free(keller);
		keller = hkeller;
	}
}

#ifdef __STDC__
ptauxdat akellersuche(Product pro)
            
#else /* ! __STDC__ */
ptauxdat akellersuche(pro)
Product pro;
#endif /* ! __STDC__ */
/* Sucht die Aux-Keller-Info fuer die Produktion pro */
{
	ptprodauxkeller prodkeller;

	prodkeller = prodakeller;
	while ((prodkeller != (ptprodauxkeller)NIL) && (prodkeller->prod != pro)){
		prodkeller = prodkeller->nachf;
	}
	if(prodkeller == (ptprodauxkeller)NIL){
	  wErrorf(NULL,
                  "Interner Fehler bei Suche nach Auxiliary-Keller-Info\n");
	  exit(10);
	}
	else
		return(prodkeller->keller);
}

#ifdef __STDC__
integer atpsuche (Attrpos atp)
            
#else /* ! __STDC__ */
integer atpsuche (atp)
Attrpos atp;
#endif /* ! __STDC__ */
/* liefert die Zell-Nr. der Zelle der Lokdat, die die attrpos zur */
/* angegebenen quelle enthaelt                 */
{
	integer ergebnis, zahl;

	ergebnis = 0;
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

/* Liefert die optimale attrpos, die denselben Wert wie die gebrauchte
   enthaelt. D.h. es wird die attpos gesucht fuer die der gesuchte Wert
   bereits schon einmal berechnet wurde */
#ifdef __STDC__
Attrpos optargpos(Product prod, Attrpos patp)
#else /* ! __STDC__ */
Attrpos optargpos(prod, patp)
Product prod;
Attrpos patp;
#endif /* ! __STDC__ */
{
	Attrpos hpatp;

	if ((hpatp = isregel(prod, patp)) == (Attrpos)NIL)
		if (Is_Copy(Ber_Aufruf(patp)))
			if (Is_Auxiliary(patp))
				return(optattpos(prod, patp));
			else
				return(AttPos_Of_Param(FirstArg(Ber_Aufruf(patp))));
		else return(patp);
	else return(hpatp);
}

/* Druckt die Berechnungen aus, die noetig sind um die angegebene attpos
   zu berechnen und pusht den Wert auf den jeweiligen Stack.
   Falls ein Auxiliary zur Berechnung benoetigt wird, wird die Funktion
   rekursiv zum Ausdruck der Berechnungen diese Auxiliarys verwendet,
   bevor der aktuell zu berechnende Wert gepusht wird.
   Auxiliarys kommen auf den Auxiliary-Keller.
   Normale Attribute auf den Attribut-Keller. */

#ifdef __STDC__
void printatpber(FILE *out, Product prod, Attrpos atp, int offset)
#else /* ! __STDC__ */
void printatpber(out, prod, atp, offset)
FILE *out;
Product prod;
Attrpos atp;
int offset;
#endif /* ! __STDC__ */
{
	Aparam ptq;
	boolean fehler;
	int zelle;
	Attrpos hpatp;
	int auxadr;
	char *type_str;
	ptauxdat ptauxelt;
	boolean push = TRUE;

	if (Is_Auxiliary(atp)){
		/* Merke Auxiliarys um Aux-Berechnungs Zyklen zu vermeiden
		 	  	z.B aux1 = f(..,aux2,..); aux2 = aux1 */
		ptauxelt = (ptauxdat)getMem(sizeof(auxdat));
		ptauxelt->attpos = atp;
		ptauxelt->nachf = merkeaux;
		merkeaux = ptauxelt;
	}
	else {
		freekeller(merkeaux);
		merkeaux = (ptauxdat)NIL;
		/* Merk-Liste freimachen, da normales Attribut berechnet wird */
	}

	fehler = FALSE;

	type_str = SymString(Typ_Name(Typ_Of_Attr(Attr_Of_AttPos(atp))));
	ptq = FirstArg(Ber_Aufruf(atp));

	/* ptq ist also erstes Argument der Berechnungsvorschrift */

	if (Is_Copy(Ber_Aufruf(atp))){
		/* Ende der Copy-Kette suchen, um bei Faellen wie ATTR1 = AUX = ATTR2 ... */
		/* die Berechnung von AUX zu vermeiden                                    */
		hpatp = optargpos(prod, AttPos_Of_Param(ptq));
		if (!Is_Auxiliary(hpatp)){ /* Attr muss im Attribut-Keller sein */
			zelle = atpsuche(hpatp);
			/* Index der lokstruct in dem sich das Argument ptq  befindet  */ 

			if (zelle != 0){
				fprintf(out, "\t\t%s = getMem(sizeof(%s));\n",voidptr_str, type_str);
				fprintf(out, "\t\t*((%s *)%s) = *(%s *)getattr(%1d);\n",type_str, voidptr_str, type_str, beranfang-zelle+offset);
			}
			else { 
				fehler = TRUE;
				fprintf(out, "\t\t*((%s *)%s) = *(%s *)getattr(***???***);\n",type_str, voidptr_str, type_str);
			}
		}
		else {	/* Auxiliary !!! */
			if ((auxadr = auxsuche(auxkeller, hpatp)) == 0){ /* Aux muss erst berechnet werden */
				if (auxsuche(merkeaux, hpatp) != 0){
					printzyklus(stderr, hpatp);
					fprintf(out, "\t\tpushaux(***ZYKLUS***);\n");
				}
				else 
				    printatpber(out, prod, hpatp, offset);
				if (Is_Auxiliary(atp)){
					/* Der Auxiliary-Wert steht jetzt im Keller an erster Stelle */
					fprintf(out, "\t\t%s = getMem(sizeof(%s));\n",voidptr_str, type_str);
					fprintf(out, "\t\t*((%s *)%s) = *(%s *)getaux(1);\n",type_str, voidptr_str, type_str);
				}
				else { /* Optimierung moeglich, da sicher ist, dass 
											voidptr_str der aktuelle Zeiger ist !!
											(das ist nach einer Optimierung nicht der Fall !!)*/
					fprintf(out, "\t\t%s1 = getMem(sizeof(%s));\n",voidptr_str, type_str);
					fprintf(out, "\t\t*((%s *)%s1) = *((%s *)%s);\n",type_str, voidptr_str, type_str, voidptr_str);
					fprintf(out, "\t\tpushattr(%s1);\n", voidptr_str);
					push = FALSE;
				}
			}
			else {
				fprintf(out, "\t\t%s = getMem(sizeof(%s));\n",voidptr_str, type_str);
				fprintf(out, "\t\t*((%s *)%s) = *(%s *)getaux(%1d);\n",type_str, voidptr_str, type_str,auxadr);
			}
		}
	}
	/* KEIN copy-symbol   				 */	 
	/* d.h Berechnung 				*/
	/* jetzt alle Parameter der Funktion abarbeiten */
	else {
		while (ptq != ((Aparam)NIL)) {
			hpatp = optargpos(prod, AttPos_Of_Param(ptq));
			if (Is_Auxiliary(hpatp)){
				if ((auxadr = auxsuche(auxkeller, hpatp)) == 0)
					if (auxsuche(merkeaux, hpatp) != 0){
						printzyklus(stderr, hpatp);
						fprintf(out, "\t\tpushaux(***ZYKLUS***);\n");
					}
					else
						printatpber(out, prod, hpatp, offset);
			}
			ptq = NextArg(ptq);
		}
		ptq = FirstArg(Ber_Aufruf(atp));
		fprintf(out, "\t\t%s = getMem(sizeof(%s));\n",voidptr_str, type_str);
		fprintf(out,"\t\t");
		DruckeSym(out, Funkt_Name(Funkt_Of_Aufruf(Ber_Aufruf(atp))));
		fprintf(out,"(");
		while (ptq != ((Aparam)NIL)) {
			hpatp = optargpos(prod, AttPos_Of_Param(ptq));
			fprintf(out, "*(");
			DruckeSym(out, Typ_Name(Typ_Of_Attr(Attr_Of_AttPos(hpatp))));
			if (!Is_Auxiliary(hpatp)){
				zelle = atpsuche(hpatp);
				/* Index der lokstruct in dem sich das Argument ptq  befindet  */ 

				if (zelle != 0){
					fprintf(out, " *)getattr(%1d)", beranfang-zelle+offset);
				}
				else { 
					fehler = TRUE;
					fprintf(out, " *) ***???***");
				}
			}
			else {
				if ((auxadr = auxsuche(auxkeller, hpatp)) == 0){
					fehler = TRUE;
					fprintf(out, " *) ***AUX***");
				}
				else
					fprintf(out, " *)getaux(%1d)", auxadr);
			}
			ptq = NextArg(ptq);
			fprintf(out, ",");
		}
		fprintf(out, " (%s *)%s);\n", type_str, voidptr_str);
	}
	if (!fehler){
		if (Is_Auxiliary(atp)){
			/* auf den AUX-Stack und in auxkeller merken */
			fprintf(out, "\t\tpushaux(%s);\n", voidptr_str);
			ptauxelt = (ptauxdat)getMem(sizeof(auxdat));
			ptauxelt->attpos = atp;
			ptauxelt->nachf = auxkeller;
			auxkeller = ptauxelt;
		}
		else
			if (push)
				fprintf(out, "\t\tpushattr(%s);\n", voidptr_str);
	}
	else {
	  semerrors++;
	  wErrorf(NULL,"\n*** Eingabegrammatik nicht L-attributiert ***\n");
	  wErrorf(NULL," Fehler in Produktion :\n");
	  druckelokprod(stderr, prod);
	  if (errordatei != NULL)
	    druckelokprod(errordatei, prod);
	  wErrorf(NULL,"Regelverletzung bei Berechnung des Attributs : ");
	  druckeapos(stderr, atp);
	  if (errordatei != NULL)
	    druckeapos(errordatei, atp);
	  wErrorf(NULL,"\n");
	}
}



#ifdef __STDC__
boolean cp_test_aux (ptcopy cp)
          
#else /* ! __STDC__ */
boolean cp_test_aux (cp)
ptcopy cp;
#endif /* ! __STDC__ */
/* steuert den Test, ob in den Berechnungsregeln      */
/* Auxiliarys verwendet werden                        */
{
	integer loop;
	Attrpos atp;
	Aparam ptq;
	Attrpos hpatp;

	globtolok(cp->prod, cp->propos, TRUE);

	/* Umwandlung der Produktion cp->prod in die Lokaldatenstruktur */
	/* beranfang ist damit besetzt 			                */	

	for (loop = 0; loop < cp->inhnumb; loop++){
		atp = lokstrukt[loop + beranfang - 1].attpos;

		ptq = FirstArg(Ber_Aufruf(atp));

		/* ptq ist also erstes Argument der Berechnungsvorschrift */

		if (Is_Copy(Ber_Aufruf(atp))){
			/* Ende der Copy-Kette suchen, um bei Faellen wie ATTR1 = AUX = ATTR2 ... */
			/* die Berechnung von AUX zu vermeiden                                    */
			hpatp = optargpos(cp->prod, AttPos_Of_Param(ptq));
			if (Is_Auxiliary(hpatp)) /* Auxiliary !!! */
				return(TRUE);
		}
		/* KEIN copy-symbol   				 */	 
		/* d.h Berechnung 				*/
		/* jetzt alle Parameter der Funktion testen */
		else {
			while (ptq != ((Aparam)NIL)) {
				hpatp = optargpos(cp->prod, AttPos_Of_Param(ptq));
				if (Is_Auxiliary(hpatp))
					return(TRUE);
				ptq = NextArg(ptq);
			}
		}
	}
	return(FALSE);
}


#ifdef __STDC__
void printcpber (FILE *out, ptcopy cp)
          
          
#else /* ! __STDC__ */
void printcpber (out, cp)
FILE *out;
ptcopy cp;
#endif /* ! __STDC__ */
/* steuert die Ausgabe der Berechnungen fuer Copy-Produktionen. */
/* wird eines der inherited attr von 'suche' nicht gefunden */
/* so ist die Eingabegrammatik nicht LR-attributiert und    */
/* die weitere Ausgabe wird durch das Funktionsergebnis '0' */
/* gestoppt                    */
{
	integer loop;
	Attrpos atp;
	int offset=0;	 

	fprintf(out,"\tcase %1d: /* CP */\n", cp->name);

	globtolok(cp->prod, cp->propos, TRUE);

	/* Umwandlung der Produktion cp->prod in die Lokaldatenstruktur */
	/* beranfang ist damit besetzt 			                */	
	/* Ausdruck der derived Attribute sowie der Berechnungsregeln   */

	for (loop = 0; loop < cp->inhnumb; loop++){
		atp = lokstrukt[loop + beranfang - 1].attpos;
		/* atp = ist aktuelle Attributposition */

		/* 
				Offset wird zu der Adressierung fuer den
				Keller dazuaddiert weil nach jedem Copy explizit
				ein pushattr() kommt und sich somit top of stack erhoeht 
			*/	        
		printatpber(out, cp->prod, atp, offset);
		offset++;
	}
	fprintf(out, "\t\tbreak;\n");
}

/* Steuert die Ausgabe der Berechnungen, die am Ende einer normalen Produktion
   durchgefuehrt werden. */
#ifdef __STDC__
void printprber(FILE *out, Product p, integer prodname)
#else /* ! __STDC__ */
void printprber(out, p, prodname)
FILE *out;
Product p;
integer prodname;
#endif /* ! __STDC__ */
{
	Attrpos atp;
	ptteilmenge pttm;
	ptattmenge pattm;
	boolean weiter;
	Prodpos pp;
	integer offset=0,izeiger, dzaehler = 0 ;
	integer auxlen;

	pp = FirstPPos(p);

	/* pp ist erste Produktionsposition */ 
	/* d.h die linke Seite              */

	fprintf(out,"\tcase %1d: /* %s */\n", prodname, SymString(Prod_Name(p)));

	pttm = findsymbol(Grm_Symbol(pp))->derivedtm;


	/* Finde die derived Teilmenge fuer die linke Seite der Produktion */

	while ((pttm != (ptteilmenge)NIL) && (pttm->attring != (ptattmenge)NIL)){
		pattm = pttm->attring;
		weiter = TRUE;
		while ((pattm != pttm->attring) || weiter){
			weiter = FALSE;
			dzaehler++;
			atp = FirstAPos(pp);

			/* atp ist Attributposition */
			/* Finde nun richtiges Attribut in  pattm */	

			while ((atp != (Attrpos)NIL)
			    && (Attr_Of_AttPos(atp) != pattm->attname)) 
				atp = NextAPos(atp);
	  		/* 
					Offset wird zu der Adressierung fuer den
					Keller dazuaddiert weil nach jedem Copy explizit
					ein pushattr() kommt und sich somit top of stack erhoeht 
				*/	        
			printatpber(out, p, atp, offset);
			offset++;	 
			pattm = pattm->nachatt;
		}
		pttm = pttm->nachftm;
	}

	izeiger = 0;
	atp = FirstAPos(pp);

	/* Erste Attributposition der linken Seite der Produktion */
	/* Wieviele Inherited Attribute bleiben auf dem Stack ?   */

	while( atp != (Attrpos)NIL){
		if (Is_Inherited(Attr_Of_AttPos(atp)))
			izeiger++;
		atp = NextAPos(atp);
	}

   /* This is it */
    
	izeiger  -=  (beranfang + dzaehler - 1 );

	/* top+izaehler zeigt jetzt ueber die */ 
	/* inherited-Attribute auf dem Stack  */

	/* Um wieviel kann der Stack verkleinert werden ?                   */

	if ((-izeiger) != dzaehler) /* Keine Reduktion noetig               */
		fprintf(out, "\t\tredattr(%1d, %1d);\n",izeiger,dzaehler); 
	if ((auxlen = auxklaenge(auxkeller)) != 0)
		fprintf(out, "\t\tredaux(%1d);\n",auxlen); 

	fprintf(out, "\t\tbreak;\n");

	/* Es wird also immer relativ zum top of Stack gerechnet */
	/* top of stack zeigt auf erstes freies Element    */

}

/* Gibt die ganze outred - Funktion aus, die vom Parser u.a mit der
   jeweiligen Produktionsnummer versorgt aufgerufen wird.
   Die Produktionsnummer wird mit der Intern-Form der Grammatik, die
   der Input des Parsers ist, bestimmt. */
/* Zusaetzlich wird auch die Funktion outterm erzeugt, die vom Parser
   immer dann aufgerufen wird, wenn ein Terminal gelesen wurde.
	Falls das Terminal ein Semantisch relevantes Terminal ist,
	muss es auf den Attributkeller gepuscht werden. */

#ifdef __STDC__
void print_outred(void)
#else /* ! __STDC__ */
void print_outred()
#endif /* ! __STDC__ */
{
	integer loop, prodname;
   char *type_str;
	ptcopy pcp;
	Product pro;
	Vocabel aktsym;
	Prodpos ppos;
	FILE *out;
	ptprodauxkeller prodaux;	

	out = fopen("AttrBer.c", "w");

	fprintf(out,"\n#include \"AttrGlob.h\"\n\n");
	fprintf(out,"char *getMem();\n");
	fprintf(out,"void pushattr();\n");
	fprintf(out,"void pushaux();\n");
	fprintf(out,"char *getattr();\n");
	fprintf(out,"char *getaux();\n");
	fprintf(out,"void redattr();\n");
	fprintf(out,"void redaux();\n\n");
	fprintf(out,"int outred(prod, lseite, plen)\n");
	fprintf(out,"    long prod;\n    long lseite;\n    long plen;\n\n{\n");
	fprintf(out,"\tchar *%s;\n", voidptr_str);
	fprintf(out,"\tchar *%s1;\n\n", voidptr_str);
	fprintf(out,"\tswitch (prod) {\n");

/* zuerst werden die Copy-Berechnungen ausgegeben, die Auxiliarys benuetzen.
 	und zwar fuer jede Produktion, die Auxiliarys benuetzt, alle Copys
   von links nach rechts, damit parallel die Auxiliarykeller-Info
	aktualisiert werden kann. Die fertige Aux-Info am Ende der Produktion wird
	dann in der Liste prodakeller abgespeichert zur Verwendung in den
	Berechnungen der Aktionen der Produktion selber, die erst spaeter
	(d.h nach allen Copy's) ausgegeben wird. */


	printf("          Generierung des Attributverwaltungsmoduls \n");
	/* Zuerst alle Aux-Copy's und dann alle restliche Copys und 
      normalen Produktionen */
   /* Dann Ausgabe von outterm ()*/

	forcopy = TRUE;
	foroutput = FALSE;

	aktsym=FirstSym();
	while (aktsym != (Vocabel)NIL){
		pro = FirstProd(aktsym);
		while (pro != ((Product)NIL)) {
			if (FirstAuxPos(pro) != (Attrpos)NIL){ /* Aux-Produktion */
				auxkeller = (ptauxdat)NIL;          /* Keller-Info initialisieren */
				ppos = NextPPos(FirstPPos(pro));
				while (ppos != (Prodpos)NIL){
					if ((pcp = copyproof(pro, ppos)) != (ptcopy)NIL){
						if (pcp->name <= auxcopyanz){ /* Testet auf Aux-Verwendung.*/
							printcpber(out, pcp);      /* Attribut-Berechnungen     */
                                                /* ausgeben                  */
						}
					}
					ppos = NextPPos(ppos);
				}
				/* Initialisieren der Auxkeller-Info fuer diese Production */

				prodaux = (ptprodauxkeller)getMem(sizeof(prodauxkeller));
				prodaux->nachf = prodakeller;
				prodakeller = prodaux;
				prodaux->prod = pro;
				prodaux->keller = auxkeller;
			}
			pro = NextProd(pro);
		}
		aktsym = NextSym(aktsym);
	}


	/* Alle restlichen CPs ausdrucken                       */
	/* Loop deswegen weil gleichnamige Copysymbole moeglich */
	for (loop= auxcopyanz+1; loop <= copyanz; loop++) {
		pcp = copyinfo;
		while ((pcp != (ptcopy)NIL) && (pcp->name != loop))
			pcp = pcp->nextcopy;
		if (pcp != (ptcopy)NIL){
			printcpber(out, pcp);   
		}
	}

	forcopy = FALSE;
	foroutput = TRUE;

	prodname = copyanz+1;

/* Jetzt endlich alle Echten Produktionen */

	aktsym=FirstSym();
	while (aktsym != (Vocabel)NIL){
		pro = FirstProd(aktsym);
		if ((pro == (Product)NIL) && !Is_Terminal(aktsym))
			{
			semerrors++;
			wErrorf(NULL,"#Warnung: Keine Produktionen fuer %s gefunden !\n",
				SymString(Sym_Name(aktsym)));
			}
		while (pro != ((Product)NIL)) {
			ppos = FirstPPos(pro);
			while (NextPPos(ppos) != (Prodpos)NIL)
				ppos = NextPPos(ppos);
			globtolok(pro, ppos, TRUE);
			if (FirstAuxPos(pro) != (Attrpos)NIL) /* Falls Auxiliary-Produktion */
				auxkeller = akellersuche(pro);
			else
				auxkeller = (ptauxdat)NIL;
			printprber(out, pro, prodname);
			pro = NextProd(pro);
			prodname++;
		}
		aktsym = NextSym(aktsym);
	}
	foroutput = FALSE;

	fprintf(out,"\tdefault:\n\t\treturn(0);\n\t\tbreak; /* Fehler: Prod unbekannt */\n");
	fprintf(out,"\t}\n\treturn(1);\n}\n");

   /* outterm  generieren */
   /* Mit Optimierung falls es sich um einen 'number' handelt wird nur */
   /* der int Wert auf den Stack gespushed                             */

   loop = 1;
   aktsym = FirstSym();
   while(!Is_Terminal((aktsym=NextSym(aktsym)))) ;

/* Finde erstes Terminal ;                         sicher ist sicher */
/* aktsym = NextSym((Vocabel)CardNonterm()) hat nicht funktioniert ! */ 

   fprintf(out,"\n\n\nvoid outterm(token)\nToken token;\n{\n"); /* nicht Token *, uv, 22.01.91 */
	fprintf(out,"\tchar *%s;\n\n", voidptr_str);
   fprintf(out,"\tswitch(token->kc)  {\n");
   while(aktsym != (Vocabel)NIL)
   {
      /* printf("Current : %s\n",SymString(Sym_Name(aktsym))); */
    	if(Is_Semantisch(aktsym))
      {
          fprintf(out,"\tcase %d: /* %s */\n",loop,SymString(Sym_Name(aktsym)));
#ifdef SCHWACHSINN
			 if(strcmp(SymString(Sym_Name(aktsym)),"number")==0)
			 {
			   fprintf(out,"\t\t%s = getMem(sizeof(number));\n", voidptr_str);
			/* neues Macro: SEMVAL, uv, 22.01.91 */
			   fprintf(out,"\t\t*(number *)%s = (number)SEMVAL(token);\n\t\tpushattr(%s);\n\t\tbreak;\n", voidptr_str, voidptr_str);
			 }
			 else
#endif
			 {
   			 type_str = SymString(Typ_Name(Typ_Of_Attr(FirstAttr(aktsym))));
			 fprintf(out,"\t\t%s = getMem(sizeof(%s));\n", voidptr_str, type_str);
#if 0
 			 fprintf(out,"\t\t*(%s *)%s = *(%s *)token;\n\t\tpushattr(%s);\n\t\tbreak;\n",type_str, voidptr_str, type_str, voidptr_str);
#else
			/* read-Prozeduren, uv, 22.01.91 */
 			 fprintf(out,"\t\tread%s(token,(%s *)%s);\n\t\tpushattr(%s);\n\t\tbreak;\n",
                                 type_str, type_str, voidptr_str, voidptr_str);
#endif
          }
      }
     loop++;
     aktsym = NextSym(aktsym);
  }
  fprintf(out,"\tdefault:\n\t\treturn;\n");
  fprintf(out,"\t}\n}\n");
  fclose(out);
}

#ifdef __STDC__
void ausgabe(void)
#else /* ! __STDC__ */
void ausgabe()
#endif /* ! __STDC__ */
{
	extern int druckekeller;
	print_outred();
	printf("          Ausgabe der Produktionen in Internform\n");
	print_grm();
	if(druckekeller)
	{
		printf("          Ausgabe der Produktionen im Klartext\n");
		globprint (outglob);             
		newprodprint (outprod, outcopy);
	}
}
