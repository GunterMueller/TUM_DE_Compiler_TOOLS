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

/* datengen */
/* Aktueller Stand vom 3.12.89 */
/* Aenderungen: */
/* malloc() durch getMem() ersetzt */
/* optattpos: Auxiliarys werden wie inherited Attr behandelt */
/* mtmenge wird gefreet: in dercopybau, globtolok(neuer Parameter!) */

#define EXTERN extern
#include "globals.h"

Vocabel l_sym;

ptmerketm   mtmenge = (ptmerketm)NIL;
integer  i, imerk;


#ifdef __STDC__
void einlesen(ptglobdat *glob);
void globtolok(Product production, Prodpos position, boolean freemtmenge);
void loktoglob(void);
void dercopybau(ptcopy cone, ptcopy ctwo);
void attcopybau(ptcopy cone,
                ptcopy ctwo,
                integer *doneend,
                integer *dtwoend,
                integer *ioneend,
                integer *itwoend);
#else /* ! __STDC__ */
void einlesen();
void globtolok();
void loktoglob();
void dercopybau();
void attcopybau();
#endif /* ! __STDC__ */

#ifdef __STDC__
extern void newprodprint(FILE *out, FILE *out1);
extern void globprint(FILE *out);
#else /* ! __STDC__ */
extern void newprodprint();
extern void globprint();
#endif /* ! __STDC__ */
 
#ifdef __STDC__
void free_mtmenge(void)
#else /* ! __STDC__ */
void free_mtmenge()
#endif /* ! __STDC__ */
{
	ptmerketm hpt;

	while(mtmenge != (ptmerketm)NIL){
		hpt = mtmenge;
		mtmenge = mtmenge->ntm;
		free(hpt);
	}
}
	
/***********************************************************/
/***********************************************************/
/* Prozeduren zum Einlesen der Globaldatenstruktur:        */
/*          einlesen, anfuegen, attein                     */
/*     Globaldatenstruktur wird  k e i n e  Ringliste      */
/***********************************************************/
/***********************************************************/

/**********************************************************************/
/* wirkung von rotiere :                                              */
/* 1.fall : atm1,atm2 zeigen auf die selbe attributringliste          */
/*          1.1.: atm1,atm2 zeigen auf dasselbe element.              */
/*                es bleibt alles beim alten.                         */
/*          1.2.: atm1,atm2 zeigen auf benachbarte elemente.          */
/*                das hintere wird aus dem ring ausgehaengt.          */
/*          1.3.: sonst : es enstehen 2 ringlisten.                   */
/* 2.fall : atm1,atm2 zeigen auf verschiedene attributringliste       */
/*          die beiden ringlisten werden verkettet                    */
/*          ( VORSICHT: REIHENFOLGE |||| )                            */
/* spezialfall : 2 elemente a,b sollen vertauscht werden              */
/*               1. rotiere (vorgaenger von a, vorgaenger von b)      */
/*               2. rotiere ( a, b)                                   */
/*--------------------------------------------------------------------*/
/* eingansvariable : atm1,atm2   pointer auf attributringliste        */
/* wird aufgerufen von : attein                                       */
/**********************************************************************/
 
 void
#ifdef __STDC__
rotiere(ptattmenge *atm1, ptattmenge *atm2)
#else /* ! __STDC__ */
rotiere(atm1, atm2)
   ptattmenge  *atm1, *atm2;
#endif /* ! __STDC__ */
{
   ptattmenge  hilf;

   if (((*atm1) != (struct attmenge *)NIL) && ((*atm2) != (struct attmenge *)NIL)) {
                                           /* zwei nichtleere ringlisten */
      hilf = (*atm1)->nachatt;             /* nachfolge-attr. v. atm1    */
      (*atm1)->nachatt = (*atm2)->nachatt; /* := nachf.-attr. v. atm2    */
      (*atm2)->nachatt = hilf;             /* und umgekehrt              */
   } else {
      if ((*atm1) == (struct attmenge *)NIL)
         (*atm1) = (*atm2);
      else
         (*atm2) = (*atm1);
   }
}
/**********************************************************************/
/* liest die attribute eines symbols ein                              */
/*--------------------------------------------------------------------*/
/* eingangsvariable : inhatm1   pointer auf inhereted teilmenge       */
/*                    deratm1   pointer auf derived teilmenge         */
/* wird aufgerufen von : anfuegen                                     */
/* ruft auf : rotiere                                                 */
/**********************************************************************/

 void
#ifdef __STDC__
attein(ptattmenge *inhatm1, ptattmenge *deratm1)
#else /* ! __STDC__ */
attein(inhatm1, deratm1)
   ptattmenge  *inhatm1, *deratm1;
#endif /* ! __STDC__ */
{
   ptattmenge  inhatm2;
   ptattmenge  deratm2;
   Attr  attr;

   attr = FirstAttr(l_sym);
   while (attr != (Attr)NIL) {           /* attr vorhanden          */
      if (Is_Inherited(attr)) {          /* inherited attr ??       */
         inhatm2 = (struct attmenge *)getMem((unsigned)(sizeof(*inhatm2)));
         inhatm2->attname = attr;        /* attr.namen besetzen     */
         inhatm2->nachatt = inhatm2;     /* ringliste schliessen    */
         rotiere(inhatm1, &inhatm2); /* verknuepft beide listen */
      } else {
         if (!Is_Inherited(attr)) {
            deratm2 = (struct attmenge *)getMem((unsigned)(sizeof(*deratm2)));
            deratm2->attname = attr;
            deratm2->nachatt = deratm2;
            rotiere(deratm1, &deratm2);
         } else
            printf(" hilfsattribute \n");
      }
      attr = NextAttr(attr);
   }
}

/**********************************************************************/
/* fuegt ein neues symbol mit attributen an die globalstruktur an     */
/*--------------------------------------------------------------------*/
/* eingangsvariable : glob2   pointer auf die globaldatenstruktur     */
/*                    sym1    anzufuegendes symbol                    */
/* wird aufgerufen von : einlesen                                     */
/* ruft auf : attein                                                  */
/**********************************************************************/

 void
#ifdef __STDC__
anfuegen(ptglobdat *glob2, Vocabel sym1)
#else /* ! __STDC__ */
anfuegen(glob2, sym1)
   ptglobdat   *glob2;
   Vocabel sym1;
#endif /* ! __STDC__ */
{
   ptattmenge  inhatm;
   ptattmenge  deratm;
   ptteilmenge inhtm;
   ptteilmenge dertm;

   if ((*glob2) == (struct globdat *)NIL) {     /* Ende der Kette ? */
      (*glob2) = (struct globdat *)getMem((unsigned)(sizeof(*(*glob2))));
      inhatm = (struct attmenge *)NIL;         /* Initialisieren     */
      deratm = (struct attmenge *)NIL;
      attein(&inhatm, &deratm);                /* attribute einlesen */
      if (deratm == (struct attmenge *)NIL)    /* keine derived attr */
         dertm = (struct teilmenge *)NIL;
      else {
         dertm = (struct teilmenge *)getMem((unsigned)(sizeof(*dertm)));
         dertm->nachftm = (struct teilmenge *)NIL; /* nachfolgeteilmenge   */
                                                   /* derived              */
         dertm->attring = deratm;                  /* attr.menge derived   */
         dertm->identtm = dertm;                   /* identifiz. teilmenge */
      }
      if (inhatm == (struct attmenge *)NIL)   /* keine inh. attr           */
         inhtm = (struct teilmenge *)NIL;
      else {
         inhtm = (struct teilmenge *)getMem((unsigned)(sizeof(*inhtm)));
         inhtm->nachftm = (struct teilmenge *)NIL; /* nachfolgeteilmenge  */
                                                   /* inherited           */
         inhtm->attring = inhatm;                  /* attr.menge inherited*/
         inhtm->identtm = inhtm;                   /* identifiz. teilmge  */
      }
      (*glob2)->symbname = sym1;                   /* symbol eintragen    */
      (*glob2)->nachfsymb = (struct globdat *)NIL; /* nachf. symbol       */
      (*glob2)->inherettm = inhtm;                 /* inh. teilmge        */
      (*glob2)->derivedtm = dertm;                 /* derived teilmge     */
   } else
      anfuegen(&((*glob2)->nachfsymb), sym1);
}

/**********************************************************************/
/* einlesen der Globalstruktur                                        */
/*--------------------------------------------------------------------*/
/* eingangsvariable : globstrukt  pointer auf die globaldatenstruktur */
/* wird aufgerufen von : maintrans aus segment hptransf               */
/* enthaelt aufrufe von : rotiere                                     */
/* enthaelt die unterprozeduren : anfuegen, attein                    */
/**********************************************************************/


 void
#ifdef __STDC__
einlesen(ptglobdat *glob)
#else /* ! __STDC__ */
einlesen(glob)
   ptglobdat   *glob;
#endif /* ! __STDC__ */
{
   l_sym = FirstSym();
   while (l_sym != (Vocabel)NIL) {
      anfuegen(glob, l_sym);
      if (FirstSym() != (*glob)->symbname)
         printf("falsch eingelesen\n");
      l_sym = NextSym(l_sym);
   }
}

 
/*******************************************************************/
/*******************************************************************/
/* Programmteil zur Erzeugung der zur Abarbeitung einer bestimmten */
/*    Produktionsposition benoetigten Lokaldatenstruktur aus der   */
/*                       Globaldatenstruktur.                      */
/*******************************************************************/
/*******************************************************************/
 

 
/******************************************************************/
/* Die Procedur 'AUFFUELLEN' belegt die Lokaldatenstruktur ab der */
/*  angegebenen Adresse mit Index := 0 und Attr/Attrpos := NIL .  */
/******************************************************************/
 
 void
#ifdef __STDC__
auffuellen(integer abadr)
#else /* ! __STDC__ */
auffuellen(abadr)
   integer  abadr;
#endif /* ! __STDC__ */
{
   register integer  loop;

   for (loop = abadr; loop <= maxloklength ; loop++) {
      lokstrukt[loop - 1].index = 0;
      lokstrukt[loop - 1].attr = (Attr)NIL;
      lokstrukt[loop - 1].attpos = (Attrpos)NIL;
      }
}


/**********************************************************/
/* Das Ergebnis der Funktion 'Findsymbol' ist der Verweis */
/*  auf die Daten des Symbols in der Globaldatenstruktur. */
/**********************************************************/

 ptglobdat
#ifdef __STDC__
findsymbol(Vocabel ps)
#else /* ! __STDC__ */
findsymbol(ps)
   Vocabel ps;
#endif /* ! __STDC__ */
{
   ptglobdat   gd;

   gd = globstrukt;
   while (((gd != (struct globdat *)NIL) && (gd->symbname != ps)))
      gd = gd->nachfsymb;
   return(gd);
}

 
/******************************************************************/
/* Die Prozedur 'merktm' baut die Einwegliste 'mtmenge' auf , die */
/*  die Verweise auf Attributteilmengen in der Reihenfolge ihres  */
/*         Eintrags in die Lokaldatenstruktur enthaelt .          */
/******************************************************************/

 void
#ifdef __STDC__
merktm(ptteilmenge pt)
#else /* ! __STDC__ */
merktm(pt)
   ptteilmenge pt;
#endif /* ! __STDC__ */
{
   ptmerketm   ltm, tm;

   tm = (struct merketm *)getMem((unsigned)(sizeof(*tm)));
                                       /* Erzeugen des anzufuegende Elt's */
   tm->ntm = (struct merketm *)NIL;
   tm->ptm = pt;
   tm->adresse = i;
   if (mtmenge == (struct merketm *)NIL)
      mtmenge = tm;                                    /* Eintrag am Ende */
   else {
      ltm = mtmenge;
      while (ltm->ntm != (struct merketm *)NIL)
         ltm = ltm->ntm;
      ltm->ntm = tm;
   }
}

 
/*********************************************************************/
/* Die Prozedur 'lattein' schreibt Attribute des Attributrings einer */
/*  Teilmenge der Globaldatenstruktur in die Lokaldatenstruktur und  */
/* setzt den Index auf die naechste nichtbelegte Zelle von lokstrukt.*/
/*********************************************************************/
 
 void
#ifdef __STDC__
lattein(ptteilmenge pt)
#else /* ! __STDC__ */
lattein(pt)
   ptteilmenge pt;
#endif /* ! __STDC__ */
{
   ptattmenge  pam;

   lokstrukt[i - 1].attr = pt->attring->attname;
   pam = pt->attring->nachatt;
   i = i + 1;
   while ((pam != pt->attring)) {
      lokstrukt[i - 1].attr = pam->attname;
      pam = pam->nachatt;
      i = i + 1;
   }
}

 
/******************************************************************/
/* Die Prozedur 'latteintrag' uebertraegt gestuetzt auf 'lattein' */
/*  und 'mertm' alle Attribute der angegebenen Attributteilmenge  */
/*  sowie der Nachfolgeteilmengen aus der Globaldatenstruktur in  */
/*   die Lokaldatenstruktur ein und belegt die Indizes der Teil-  */
/*            mengenanfaenge mit der "eigenen" Adresse .          */
/******************************************************************/

 void
#ifdef __STDC__
latteintrag(ptteilmenge pt)
#else /* ! __STDC__ */
latteintrag(pt)
   ptteilmenge pt;
#endif /* ! __STDC__ */
{
   ptteilmenge tm;

   tm = pt;
   while (tm != (struct teilmenge *)NIL) {
      merktm(tm);
      lattein(tm);
      tm = tm->nachftm;
   }
}

 
/****************************************************/
/* Traegt "die eigenen" Attributpositionen zu allen */
/*   Attributen der Lokaldatenstruktur ein , die    */
/*   zwischen Index "imerk" und Index "i" liegen .  */
/****************************************************/

 void
#ifdef __STDC__
attposeintrag(Prodpos pprodpos)
#else /* ! __STDC__ */
attposeintrag(pprodpos)
   Prodpos   pprodpos;
#endif /* ! __STDC__ */
{
   Attrpos eap;

   while (imerk < i) {
      eap = FirstAPos(pprodpos);
      while (((Attr_Of_AttPos(eap) != lokstrukt[imerk - 1].attr) 
             && (eap != (Attrpos)NIL)))
         eap = NextAPos(eap);
      lokstrukt[imerk - 1].attpos = eap;
      imerk = imerk + 1;
   }
}

/***************************************************************/
/* Liefert den Verweis auf das Copy-Symbol vor der aktuellen   */
/*  Produktionsposition . Ist das Ergebnis = nil , so steht    */
/* kein Copy-Symbol an dieser Stelle des Produktionensystems . */
/***************************************************************/

 ptcopy
#ifdef __STDC__
copyproof(Product pprod, Prodpos pprodpos)
#else /* ! __STDC__ */
copyproof(pprod, pprodpos)
   Product   pprod;
   Prodpos   pprodpos;
#endif /* ! __STDC__ */
{
   ptcopy   cp;

   cp = copyinfo;
   while (((cp != (struct copy *)NIL) 
           && ((cp->prod != pprod) || (cp->propos != pprodpos))))
      cp = cp->nextcopy;
   return(cp);
}

/******************************************************/
/*  Liefert den Verweis auf die inhereted-Teilmenge   */
/*  der Produktionsposition , ab der die Attribut-    */
/*  berechnung mit Hilfe eines "copy"-Symbols erfolgt */
/******************************************************/

 ptteilmenge
#ifdef __STDC__
copyattrtm(Vocabel ps, integer inh)
#else /* ! __STDC__ */
copyattrtm(ps, inh)
   Vocabel ps;
   integer  inh;
#endif /* ! __STDC__ */
{
   ptteilmenge pt, ptm;
   ptglobdat   pgd;
   ptattmenge  pam, pamerke;
   integer  k;
   register integer  h;

   pgd = findsymbol(ps);
   ptm = pgd->inherettm;
   pt = ptm;
   k = 0;
   while (pt != (struct teilmenge *)NIL) {
      pamerke = pt->attring;
      pam = pamerke->nachatt;
      k = k + 1;
      while (pam != pamerke) {
         k = k + 1;
         pam = pam->nachatt;
      }
      pt = pt->nachftm;
   }
   pt = ptm;
   if (k > inh) {
      pamerke = pt->attring;
      pam = pamerke->nachatt;
      for (h = 1; h <= (k - inh) ; h++) {
         if (pam == pamerke) {
            pt = pt->nachftm;
            pamerke = pt->attring;
            pam = pamerke->nachatt;
         } else
            pam = pam->nachatt;
      }
   }
   return(pt);
}

 
/*********************************************/
/*   Die Prozedur 'regelmerk' traegt neu     */
/* eingefuehrte Rechenregeln in mregel ein . */
/*********************************************/

 void
#ifdef __STDC__
regelmerk(Product pp, Attrpos z, Attrpos q)
#else /* ! __STDC__ */
regelmerk(pp, z, q)
   Product   pp;
   Attrpos z;
   Attrpos q;
#endif /* ! __STDC__ */
{
   ptmerkeregel   reg, lreg;

   reg = (struct merkeregel *)getMem((unsigned)(sizeof(*reg)));
   reg->pmr = (struct merkeregel *)NIL;
   reg->mrprod = pp;
   reg->mrziel = z;
   reg->mrquelle = q;
   if (mregel == (struct merkeregel *)NIL)
      mregel = reg;
   else {
      lreg = mregel;
      while (lreg->pmr != (struct merkeregel *)NIL)
         lreg = lreg->pmr;
      lreg->pmr = reg;
   }
}

/**************************************************/
/* PROCEDUR ' ISREGEL ' LIEFERT DAS KOPIERTE ATT- */
/*  RIBUT , FALLS ZUM ATTRIBUT EINE NEUE BERECH-  */
/*  NUNGSREGEL EINGEFUEHRT WURDE , SONST >NIL< .  */
/**************************************************/

 Attrpos
#ifdef __STDC__
isregel(Product pp, Attrpos ap)
#else /* ! __STDC__ */
isregel(pp, ap)
   Product   pp;
   Attrpos ap;
#endif /* ! __STDC__ */
{
   ptmerkeregel   reg;

   reg = mregel;
   while ((reg != (struct merkeregel *)NIL) 
           && ((reg->mrprod != pp) || (reg->mrziel != ap)))
      reg = reg->pmr; 
   if (reg != (struct merkeregel *)NIL)
      return(reg->mrquelle);
   else
      return((Attrpos)NIL);
}

 
/****************************************************/
/* Traegt Attributpositionen zu den mit Hilfe eines */
/*  copy-symbols berechneten inhereted Attributen   */
/*     zwischen Index "imerk" und Index "i" ein     */
/****************************************************/

 void
#ifdef __STDC__
copyattposein(Product pprod, Prodpos pprodpos)
#else /* ! __STDC__ */
copyattposein(pprod, pprodpos)
   Product   pprod;
   Prodpos   pprodpos;
#endif /* ! __STDC__ */
{
   Attrpos eap, aap;

   while (imerk < i) {
      eap = FirstAPos(pprodpos);
      while (((Attr_Of_AttPos(eap) != lokstrukt[imerk - 1].attr) 
             && (eap != (Attrpos)NIL)))
         eap = NextAPos(eap);
      if (Attr_Of_AttPos(eap) == lokstrukt[imerk - 1].attr) {
         aap = isregel(pprod, eap);
         if (aap == (Attrpos)NIL) {
            if (Is_Copy(Ber_Aufruf(eap)))
               aap = AttPos_Of_Param(FirstArg(Ber_Aufruf(eap)));
            else
               aap = eap;
         }
         lokstrukt[imerk - 1].attpos = aap;
         imerk = imerk + 1;
      } else {
         imerk = i;
      }
   }
}

/**********************************************************************/
/* Funktion ' Optattpos ' liefert zur angegebenen inhereted Attribut- */
/* position , die durch Kopie berechnet wird , die Attributposition,  */
/* fuer die der benoetigte Wert zum ersten Mal berechnet wurde.       */
/* (Also das optimale Ende einer 'Kopie-Kette')                       */
/**********************************************************************/

 Attrpos
#ifdef __STDC__
optattpos(Product pp, Attrpos ap)
#else /* ! __STDC__ */
optattpos(pp, ap)
   Product   pp;
   Attrpos ap;
#endif /* ! __STDC__ */
{
   Attrpos optap, loptap, ergebnis;

   ergebnis = (Attrpos)NIL;
	loptap = (Attrpos)NIL; /* attpos des letzten nicht Auxiliary-Attributs */
   optap = AttPos_Of_Param(FirstArg(Ber_Aufruf(ap)));
   while (ergebnis == (Attrpos)NIL) {
		if (!Is_Auxiliary(optap)) loptap = optap;
      if (((PPos_Of_AttPos(optap) != FirstPPos(pp)) 
     	  	  		|| Is_Auxiliary(optap))
           && ((Is_Inherited(Attr_Of_AttPos(optap)))
     	  	  		|| Is_Auxiliary(optap)) 
           && (Is_Copy(Ber_Aufruf(optap))))
         optap = AttPos_Of_Param(FirstArg(Ber_Aufruf(optap)));
      else
         ergebnis = optap;
   }
	if (Is_Auxiliary(ergebnis) && (loptap != (Attrpos)NIL))
		ergebnis = loptap;
   if (ergebnis != AttPos_Of_Param(FirstArg(Ber_Aufruf(ap))))
      regelmerk(pp, ap, ergebnis);
   return(ergebnis);
}

 
/*****************************************************/
/* Traegt Attributpositionen zu den zu berechnenden  */
/* inhereted Attributen zwischen Index "imerk" und   */
/* Index "i" ein und erzeugt neue Berechnungsregeln. */
/*****************************************************/
 
 void
#ifdef __STDC__
berattposeintrag(Product pprod, Prodpos pprodpos)
#else /* ! __STDC__ */
berattposeintrag(pprod, pprodpos)
   Product   pprod;
   Prodpos   pprodpos;
#endif /* ! __STDC__ */
{
   Attrpos eap, aap;

   aap = (Attrpos)NIL;
   while (imerk < i) {
      eap = FirstAPos(pprodpos);
      while (((Attr_Of_AttPos(eap) != lokstrukt[imerk - 1].attr) 
             && (eap != (Attrpos)NIL)))
         eap = NextAPos(eap);
      if (Attr_Of_AttPos(eap) == lokstrukt[imerk - 1].attr) {
         aap = isregel(pprod, eap);
         if (aap == (Attrpos)NIL) {
            if (Is_Copy(Ber_Aufruf(eap)))
               aap = optattpos(pprod, eap);
            else
               aap = eap;                   /* kein Aufruf von berapos */
                                            /* da optimize = false     */
         }
         lokstrukt[imerk - 1].attpos = aap;
         imerk = imerk + 1;
      } else
         imerk = i;
   }
}

 
/******************************************************/
/*  Ueberprueft in der Globaldatenstruktur , ob die   */
/*     Teilmengen von a und b bereits miteinander     */
/*              identifiziert wurden .                */
/******************************************************/
 
 boolean
#ifdef __STDC__
isrek2(ptmerketm a, ptmerketm b)
#else /* ! __STDC__ */
isrek2(a, b)
   ptmerketm   a;
   ptmerketm   b;
#endif /* ! __STDC__ */
{
   ptteilmenge atm, btm, pttm;
   boolean  ergebnis;

   atm = a->ptm;
   btm = b->ptm;
   ergebnis = false;

   if (((Typ_Name(Typ_Of_Attr(atm->attring->attname)) 
         == Typ_Name(Typ_Of_Attr(btm->attring->attname))) 
        && (Is_Inherited(atm->attring->attname) 
            == Is_Inherited(btm->attring->attname)))) {
      if (atm == btm)
         ergebnis = true;
      else {
         pttm = atm->identtm;
         while (pttm != atm) {
            if (pttm == btm) {
               pttm = atm;
               ergebnis = true;
            } else
               pttm = pttm->identtm;
         }
      }
   }

   return(ergebnis);
}

 
/****************************************************/
/* UEBERTRAEGT BEREITS BESTEHENDE IDENTIFIKATIONEN  */
/*  VON TEILMENGEN AUF DIE LOKALDATENSTRUKTUR UND   */
/*  AENDERT ' MTMENGE ' SO AB , DASS DORT NUR NOCH  */
/* ANFANGSTEILMENGEN VON LOKALEN IDENTITAETSKETTEN  */
/* ( ADRESSE > INDEX ) SOWIE LOKAL UNIDENTIFIZIERTE */
/*  TEILMENGEN ( ADRESSE = INDEX ) ENTHALTEN SIND . */
/****************************************************/

 void
#ifdef __STDC__
rekeintrag(void)
#else /* ! __STDC__ */
rekeintrag()
#endif /* ! __STDC__ */
{
   ptmerketm   anfang, vmerke, merke, vsuche, suche;

   anfang = mtmenge;
   while (anfang != (struct merketm *)NIL) {
      vmerke = anfang;
      merke = anfang;
      vsuche = anfang;
      suche = anfang->ntm;
      while (suche != (struct merketm *)NIL) {
         if (isrek2(merke, suche)) {
            lokstrukt[suche->adresse - 1].index = merke->adresse;
            if (merke != anfang) {
               vmerke->ntm = merke->ntm;
               free(merke);
            }
            if (vmerke->ntm != suche)
               vmerke = vsuche;
            merke = suche;
         }
         vsuche = suche;
         suche = suche->ntm;
      }
      lokstrukt[anfang->adresse - 1].index = merke->adresse;
      if (merke != anfang) {
         vmerke->ntm = merke->ntm;
         free(merke);
      }
      anfang = anfang->ntm;
   }
}

 
/**************************************************/
/*  Baut mit Hilfe der vorangegangenen Programme  */
/*  die Lokaldatenstuktur auf und speichert sie   */
/*  in der Variable "lokstrukt" ab .              */
/**************************************************/

 void
#ifdef __STDC__
globtolok(Product production, Prodpos position, boolean freemtmenge)
#else /* ! __STDC__ */
globtolok(production, position, freemtmenge)
   Product   production;
   Prodpos   position;
	boolean freemtmenge;
#endif /* ! __STDC__ */
{
   ptteilmenge ptm;
   ptglobdat   pgd;
   Prodpos   pp;
   ptcopy   cp;
   Vocabel ps;
   integer  laenge;
   boolean  stop;

  /* Initialisierung */

   auffuellen(1);
   i = 1;
   imerk = 1;
   loklength = 0;
   beranfang = 0;

	if (freemtmenge)
		free_mtmenge(); /* Letzte mtmenge wird nicht mehr benoetigt */
	else
   	mtmenge = (ptmerketm)NIL; /* Letzte mtmenge wird noch gebraucht */

   pp = FirstPPos(production);
   ps = Grm_Symbol(pp);
   pgd = findsymbol(ps);
   ptm = pgd->inherettm;

  /* Inherited- Attribute der linken Seite */

   latteintrag(ptm);
   attposeintrag(pp);
   pp = NextPPos(pp);

  /* Derived- und copy-Attribute der rechten Seite */

   if (pp != (Prodpos)NIL) {
      stop = false;
      while (((!stop) && ((PPos_Nummer(pp) < PPos_Nummer(position)) 
                          || (foroutput && (pp == position))))) {
         ps = Grm_Symbol(pp);
         pgd = findsymbol(ps);
         ptm = pgd->derivedtm;
         cp = copyproof(production, pp);
         if (cp != (struct copy *)NIL) {
            laenge = cp->inhnumb;
            latteintrag(copyattrtm(ps, laenge));
            if ((foroutput || forcopy)) 
               attposeintrag(pp);
            else
               copyattposein(production, pp);
         }
         latteintrag(ptm);
         attposeintrag(pp);
         if ((PPos_Nummer(pp) < PPos_Nummer(position)))
            pp = NextPPos(pp);
         else
            stop = true;
      }
      beranfang = i;

  /* Inherited- Attribute der zu berechnenden Produktionsposition */

      if (!foroutput) {
         ps = Grm_Symbol(pp);
         pgd = findsymbol(ps);
         ptm = pgd->inherettm;
         if (forcopy) {
            cp = copyproof(production, pp);
            laenge = cp->inhnumb;
            latteintrag(copyattrtm(ps, laenge));
            attposeintrag(pp);
         } else {
            latteintrag(ptm);
            berattposeintrag(production, pp);
            rekeintrag();
         }
      } else
         rekeintrag();
   } else {
      rekeintrag();
      beranfang = i;                              /* 13.11.89 geaendert */

   }
   loklength = i - 1;
}

 
/*******************************************************************/
/* PROZEDUR 'DERCOPYBAU' BAUT DIE LOKALDATENSTRUKTUR ZUM DERIVED-  */
/*                           VERGLEICH AUF ;                       */
/*******************************************************************/

 void
#ifdef __STDC__
dercopybau(ptcopy cone, ptcopy ctwo)
#else /* ! __STDC__ */
dercopybau(cone, ctwo)
   ptcopy   cone;
   ptcopy   ctwo;
#endif /* ! __STDC__ */
{
  /* initialisieren */

   auffuellen(1);
   i = 1;
   imerk = 1;
   loklength = 0;
   beranfang = 0;
	free_mtmenge();

  /* Eintrag der derived Attribute von 'cone' */

   latteintrag(copyattrtm(Grm_Symbol(cone->propos), cone->inhnumb));
#ifdef FALSCH
   attposeintrag(cone->prod, cone->propos); 
#else
   attposeintrag(cone->propos); 
#endif

  /* Eintrag der derived Attribute von 'ctwo' */
   latteintrag(copyattrtm(Grm_Symbol(ctwo->propos), ctwo->inhnumb));
#ifdef FALSCH
   attposeintrag(ctwo->prod, ctwo->propos); 
#else
   attposeintrag(ctwo->propos); 
#endif
   loklength = i - 1;
   rekeintrag();
}

 
/*********************************************************************/
/*  PROZEDUR 'LOKCONC' VERSCHMILZT DIE ANGEGEBENEN LOKALDATENSTRUK-  */
/* TUREN UND LISTEN ZU EINER LOKALDATENSTRUKTUR UND ZU EINER LISTE . */
/*********************************************************************/

 void
#ifdef __STDC__
lokconc(lok *lone, lok *ltwo, ptmerketm mone, ptmerketm mtwo, integer loneend)
                             /* Array ! , also VAR-Parameter*/
                             /* Array ! */
                    
                    
                    
#else /* ! __STDC__ */
lokconc(lone, ltwo, mone, mtwo, loneend)
   lokdat   lone;            /* Array ! , also VAR-Parameter*/
   lokdat   ltwo;            /* Array ! */
   ptmerketm   mone;
   ptmerketm   mtwo;
   integer  loneend;
#endif /* ! __STDC__ */
{
   integer  adr;
   ptmerketm   m;

  /* 'lokstrukt' herstellen */

   LDCOPY(lone, lokstrukt);                  /* lokstrukt = lone; */
   adr = 1;
   while (ltwo[adr - 1].attr != (Attr)NIL) {
      if (ltwo[adr - 1].index != 0)
         lokstrukt[loneend + adr - 1].index = loneend + adr;
      lokstrukt[loneend + adr - 1].attr = ltwo[adr - 1].attr;
      lokstrukt[loneend + adr - 1].attpos = ltwo[adr - 1].attpos;
      adr = adr + 1;
   }

  /* 'mtmenge' herstellen */

   m = mone;
   while (m->ntm != (struct merketm *)NIL)
      m = m->ntm;
   m->ntm = mtwo;
   m = m->ntm;
   while (m != (struct merketm *)NIL) {
      m->adresse = m->adresse + loneend;
      m = m->ntm;
   }
   mtmenge = mone;
}

/*******************************************************************/
/* PROZEDUR 'ATTCOPYBAU' BAUT DIE LOKALDATENSTRUKTUR ZUM ATTRIBUT- */
/*                 VERGLEICH FUER COPY-SYMBOLE AUF .               */
/*******************************************************************/

 void
#ifdef __STDC__
attcopybau(ptcopy cone,
           ptcopy ctwo,
           integer *doneend,
           integer *dtwoend,
           integer *ioneend,
           integer *itwoend)
#else /* ! __STDC__ */
attcopybau(cone, ctwo, doneend, dtwoend, ioneend, itwoend)
   ptcopy   cone;
   ptcopy   ctwo;
   integer  *doneend;
   integer  *dtwoend;
   integer  *ioneend;
   integer  *itwoend;
#endif /* ! __STDC__ */
{
   lokdat   lokone, loktwo;
   ptmerketm   mtone, mttwo;

   globtolok(cone->prod, cone->propos, TRUE);
   LDCOPY(lokstrukt, lokone);                   /* lokone = lokstrukt; */
   mtone = mtmenge;
   (*doneend) = loklength;
   (*ioneend) = (*doneend) - cone->inhnumb;
   globtolok(ctwo->prod, ctwo->propos, FALSE);
   LDCOPY(lokstrukt, loktwo);                   /* loktwo = lokstrukt; */
   mttwo = mtmenge;
   (*dtwoend) = (*doneend) + loklength;
   (*itwoend) = (*dtwoend) - ctwo->inhnumb;
   lokconc(lokone, loktwo, mtone, mttwo, (*doneend));
   loklength = (*dtwoend);
   rekeintrag();
}

/*********************************************************/
/*********************************************************/
/*  PROGRAMMTEIL ZUR UEBERTRAGUNG DER ERRECHNETEN DATEN  */
/* AUS DER LOKALDATENSTRUKTUR IN DIE GLOBALDATENSTRUKTUR */
/*********************************************************/
/*********************************************************/
 
 
 
 
/**************************************************/
/* DIE PROZEDUR 'SPALTE' SPALTET DIE ANGEGEBENE   */
/*        TEILMENGE NACH 'NUMB' ATTRIBUTEN        */
/**************************************************/

 ptteilmenge
#ifdef __STDC__
spalt(ptteilmenge pttm, integer numb)
#else /* ! __STDC__ */
spalt(pttm, numb)
   ptteilmenge pttm;
   integer  numb;
#endif /* ! __STDC__ */
{
   ptteilmenge ptm;
   ptattmenge  attm1;
   ptattmenge  attm2;
   ptattmenge  attm3;
   register integer  loop;

  /* SUCHE NACH DEM 'NUMB'-TEN ATTRIBUT */

   attm1 = pttm->attring;
   attm2 = attm1;
   if (numb > 1) 
            for (loop = 1; loop <= (numb - 1) ; loop++)
                attm2 = attm2->nachatt;

  /* SPALTUNG NACH DIESER STELLE */

   attm3 = attm2->nachatt;
   attm2->nachatt = attm1;
   attm2 = attm3;
   while (attm2->nachatt != attm1)
      attm2 = attm2->nachatt;
   attm2->nachatt = attm3;

  /* NEUE TEILMENGE EINFUEHREN */
   ptm = (struct teilmenge *)getMem((unsigned)(sizeof(*ptm)));
   ptm->nachftm = pttm->nachftm;
   ptm->attring = attm3;
   pttm->nachftm = ptm;
   return(ptm);
}

 void
#ifdef __STDC__
spalte(ptteilmenge *pttm, integer numb)
#else /* ! __STDC__ */
spalte(pttm, numb)
   ptteilmenge *pttm;
   integer  numb;
#endif /* ! __STDC__ */
{
   ptteilmenge idpttm, neuetm, idneuetm;

   neuetm = spalt((*pttm), numb);
   idneuetm = neuetm;
   idpttm = (*pttm)->identtm;
   while (idpttm != (*pttm)) {
      idneuetm->identtm = spalt(idpttm, numb);
      idneuetm = idneuetm->identtm;
      idpttm = idpttm->identtm;
   }
   idneuetm->identtm = neuetm;
   (*pttm) = neuetm;
}

 
/****************************************************************/
/* DIE PROZEDUR 'TAUSCHE' VERTAUSCHT IN DER ANGEGEBENEN TEIL -  */
/* MENGE DIE ANGEGEBENEN ATTRIBUTE (FEHLERMELDUNG , FALLS NICHT */
/* VORHANDEN ) UND IM ZUGEHOERIGEN IDENTITAETSRING ALLE MIT     */
/*         DIESEN ATTRIBUTEN IDENTIFIZIERTEN ATTRIBUTE .        */
/****************************************************************/

 void
#ifdef __STDC__
vertausche(ptteilmenge inteilm, integer ist, integer soll)
#else /* ! __STDC__ */
vertausche(inteilm, ist, soll)
   ptteilmenge inteilm;
   integer  ist;
   integer  soll;
#endif /* ! __STDC__ */
{
   ptattmenge  istattm, sollattm;
   Attr  merkatt;
   register integer  loop;

   istattm = inteilm->attring;      /* Suche des 'ist'-ten attr       */
   if (ist > 1) 
      for (loop = 2; loop <= ist ; loop++) 
          istattm = istattm->nachatt;
   
   sollattm = istattm;               /* Suche des 'soll'-ten attr     */
   if (soll > ist)
      for (loop = ist + 1; loop <= soll ; loop++) 
          sollattm = sollattm->nachatt;

   merkatt = istattm->attname;                /* vertauschen */
   istattm->attname = sollattm->attname;
   sollattm->attname = merkatt;
}

 void
#ifdef __STDC__
tausche(ptteilmenge teilm, Attr att1, Attr att2)
#else /* ! __STDC__ */
tausche(teilm, att1, att2)
   ptteilmenge teilm;
   Attr  att1;
   Attr  att2;
#endif /* ! __STDC__ */
{
   ptteilmenge idteilm;
   ptattmenge  anfang, suchattm;
   integer  i, s;
   Attr  att;

  /* SUCHE NACH DER STELLE DES ERSTEN ATTRIBUTES */
   anfang = teilm->attring;
   if ((anfang->attname == att1) || (anfang->attname == att2)) {
      i = 1;
      suchattm = anfang;
   } else {
      i = 2;
      suchattm = anfang->nachatt;
   }
   while (((suchattm->attname != att1) && (suchattm->attname != att2) 
           && (i < 1000))) {
      i = i + 1;
      suchattm = suchattm->nachatt;
   }

  /* SUCHE NACH DER STELLE DES ZWEITEN ATTRIBUTES */
   s = i;
   if (suchattm->attname == att1)
      att = att2;
   else
      att = att1;
   while (((suchattm->attname != att) && (s < 1000))) {
      s = s + 1;
      suchattm = suchattm->nachatt;
   }

  /* VERTAUSCHEN IM IDENTRING */
   vertausche(teilm, i, s);
   idteilm = teilm->identtm;
   while (idteilm != teilm) {
      vertausche(idteilm, i, s);
      idteilm = idteilm->identtm;
   }
}

 
/*********************************************************************/
/* DIE PROZEDUR 'TMLOKTOGLOB'BRINGT ALLE TEILMENGEN DER GLOBALDATEN- */
/*  STRUKTUR , DIE IN MTMENGE GESPEICHERT SIND , UND DIE TEILMENGEN  */
/*  IHRER IDENTITAETSRINGE IN DIE ERRECHNETE FORM DER LOKALDATEN .   */
/*    MTMENGE ENTHAELT ANSCHLIESSEND DIE BRUCHSTUECKE DER VORHER     */
/*                   ENTHALTENEN TEILMENGEN .                        */
/*********************************************************************/

 void
#ifdef __STDC__
checkloktm(integer *adress, ptteilmenge pteilm)
#else /* ! __STDC__ */
checkloktm(adress, pteilm)
   integer  *adress;
   ptteilmenge pteilm;
#endif /* ! __STDC__ */
{
   ptattmenge  pattm;

   pattm = pteilm->attring;
   if (lokstrukt[*adress - 1].attr != pattm->attname)
      tausche(pteilm, pattm->attname, lokstrukt[*adress - 1].attr);
   (*adress) = (*adress) + 1;
   pattm = pattm->nachatt;
   while (((lokstrukt[*adress - 1].index == 0) 
           && (lokstrukt[*adress - 1].attr != (Attr)NIL))) {
      if (lokstrukt[*adress - 1].attr != pattm->attname)
         tausche(pteilm, pattm->attname, lokstrukt[*adress - 1].attr);
      (*adress) = (*adress) + 1;
      pattm = pattm->nachatt;
   }
}

 void
#ifdef __STDC__
checkglobtm(ptmerketm pmtm)
#else /* ! __STDC__ */
checkglobtm(pmtm)
   ptmerketm   pmtm;
#endif /* ! __STDC__ */
{
   integer  stop, adr, madr;
   ptattmenge  mpam, pam;
   ptteilmenge pteilmenge;
   ptmerketm   mtm, mmtm;

   mmtm = pmtm;
   adr = mmtm->adresse;
   madr = adr;
   pteilmenge = mmtm->ptm;

  /* ZAHL DER ATTRIBUTE DER TEILMENGE => OBERE GRENZE */
   stop = 1;
   mpam = pteilmenge->attring;
   pam = mpam->nachatt;
   while (pam != mpam) {
      stop = stop + 1;
      pam = pam->nachatt;
   }
   stop = stop + madr;

  /* ATTRIBUTE ORDNEN UND IDENTITAETSRINGE SPALTEN */
   checkloktm(&adr, pteilmenge);
   while (adr < stop) {
      spalte(&pteilmenge, adr - madr);
      madr = adr;
      mtm = (struct merketm *)getMem((unsigned)(sizeof(*mtm)));
      mtm->ptm = pteilmenge;
      mtm->adresse = adr;
      mtm->ntm = mmtm->ntm;
      mmtm->ntm = mtm;
      mmtm = mtm;
      checkloktm(&adr, pteilmenge);
   }
}

 void
#ifdef __STDC__
tmloktoglob(void)
#else /* ! __STDC__ */
tmloktoglob()
#endif /* ! __STDC__ */
{
   ptmerketm   mt;

   mt = mtmenge;
   while (mt != (struct merketm *)NIL) {
      checkglobtm(mt);
      mt = mt->ntm;
   }
}

/*****************************************************************/
/* DIE PROZEDUR ' IDLOKTOGLOB ' STELLT NEU EINGEFUEHRTE IDENTI - */
/* FIKATIONEN IN DER LOKALDATENSTRUKTUR FEST UND UEBERTRAEGT SIE */
/*                 AUF DIE GLOBALDATENSTRUKTUR .                 */
/*****************************************************************/

 void
#ifdef __STDC__
globidconc(ptteilmenge idtm1, ptteilmenge idtm2)
#else /* ! __STDC__ */
globidconc(idtm1, idtm2)
   ptteilmenge idtm1;
   ptteilmenge idtm2;
#endif /* ! __STDC__ */
{
   ptteilmenge tmspeicher;

   tmspeicher = idtm1->identtm;
   idtm1->identtm = idtm2->identtm;
   idtm2->identtm = tmspeicher;
}

 ptteilmenge
#ifdef __STDC__
searchtm(Attr pat, ptmerketm mtm)
#else /* ! __STDC__ */
searchtm(pat, mtm)
   Attr  pat;
   ptmerketm   mtm;
#endif /* ! __STDC__ */
{
   ptmerketm   ptmtm;
   ptteilmenge anftm, idtm, ergebnis;

   ergebnis = (struct teilmenge *)NIL;
   ptmtm = mtm;
   while (((ptmtm != (struct merketm *)NIL) && (ergebnis == (struct teilmenge *)NIL))) {
      anftm = ptmtm->ptm;
      if (anftm->attring->attname == pat)
         ergebnis = anftm;
      else {
         idtm = anftm->identtm;
         while (((idtm != anftm) && (ergebnis == (struct teilmenge *)NIL))) {
            if (idtm->attring->attname == pat)
               ergebnis = idtm;
            else
               idtm = idtm->identtm;
         }
      }
      ptmtm = ptmtm->ntm;
   }
   return(ergebnis);
}

 void
#ifdef __STDC__
checkid(ptmerketm mtm)
#else /* ! __STDC__ */
checkid(mtm)
   ptmerketm   mtm;
#endif /* ! __STDC__ */
{
   Attr  idatt, suchatt;
   ptteilmenge anftm, idtm;
   integer  idlokadr;

   anftm = mtm->ptm;
   idlokadr = lokstrukt[mtm->adresse - 1].index;
   while (idlokadr != mtm->adresse) {
      idtm = anftm->identtm;
      suchatt = lokstrukt[idlokadr - 1].attr;
      while (anftm != idtm) {
         idatt = idtm->attring->attname;
         if (idatt == suchatt)
            idtm = anftm;
         else
            idtm = idtm->identtm;
      }
      if (((idatt != suchatt) && (anftm->attring->attname != suchatt)))
         globidconc(anftm, searchtm(suchatt, mtm));
      idlokadr = lokstrukt[idlokadr - 1].index;
   }
}

 void
#ifdef __STDC__
idloktoglob(void)
#else /* ! __STDC__ */
idloktoglob()
#endif /* ! __STDC__ */
{
   ptmerketm   mtm;

   mtm = mtmenge;
   while (mtm != (struct merketm *)NIL) {
      if (((lokstrukt[mtm->adresse - 1].index > mtm->adresse)
          && (mtm->ptm->attring != mtm->ptm->attring->nachatt)))
         checkid(mtm);
      mtm = mtm->ntm;
   }
}

/**************************************************************/
/* DIE PROZEDUR ' LOKTOGLOB ' UEBERTRAEGT DIE NEU ERRECHNETEN */
/*  TEILMENGENSTRUKTUREN UND -IDENTIFIKATIONEN VON DER LOKAL- */
/*          DATENSTRUKTUR AUF DIE GLOBALDATENSTRUKTUR .       */
/**************************************************************/

 void
#ifdef __STDC__
loktoglob(void)
#else /* ! __STDC__ */
loktoglob()
#endif /* ! __STDC__ */
{
   tmloktoglob();       /* Uebertrag der Teilmengenstruktur */
   idloktoglob();       /* Uebertrag der Identitaetsstruktur*/
}

