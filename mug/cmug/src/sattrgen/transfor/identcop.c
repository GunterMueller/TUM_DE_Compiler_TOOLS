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

/* identcop */
/* Aktueller Stand vom 3.12.89 */
/* Aenderungen: */
/* In copygen zaehler eingefuehrt, der die Copys mit laufender Nummer versorgt */
/* malloc() durch getMem() ersetzt */
/* Test noetig !!! */
/* in copygen werden nur noch CP, die in Nicht-Aux-Prods identifiziert */
/* Die parlist wird gefreet: in searchpar und in coptrans */

#define EXTERN extern
#include "globals.h"

typedef struct parlist * ptparlist; /* liste der attributpositonen der */
typedef struct parlist {            /* parameter der berechnungsfktn.  */
   ptparlist   nextpar;             /* fuer die derived attribute der  */
   Attrpos     par[2];              /* copy-symbole                    */
}  parlist;


boolean   l_findpar;
ptparlist l_param = (ptparlist)NIL;
lokdat    *l_coplok;


#ifdef __STDC__
void copygen(int zaehler);
#else /* ! __STDC__ */
void copygen();
#endif /* ! __STDC__ */

#ifdef __STDC__
extern void loktoglob(void);
extern void dercopybau(ptcopy cone, ptcopy ctwo);
extern void attcopybau(ptcopy cone,
                       ptcopy ctwo,
                       integer *doneend,
                       integer *dtwoend,
                       integer *ioneend,
                       integer *itwoend);
extern void eltausch(integer i, integer k, integer tmanf, lok *Xlok);
extern void neutm(integer tmanf, integer neuanf, lok *Xlok);
extern void identtm(integer tm1, integer tm2, lok *Xlok);
extern boolean isrek(integer tmanf1, integer tmanf2, lok *Xlok);
#else /* ! __STDC__ */
extern void loktoglob();
extern void dercopybau();
extern void attcopybau();
extern void eltausch();
extern void neutm();
extern void identtm();
extern boolean isrek();
#endif /* ! __STDC__ */


/********************************************************************/
/* enthaelt die prozeduren zur steuerung des strategie der          */
/* identifizierung der copy-symbole :                               */
/*                       - copygen                                  */
/*                       - samecopy                                 */
/*------------------------------------------------------------------*/
/* enthaelt die prozedur zum transformieren der lokaldatenstruktur  */
/* zweier copy-symbole :                                            */
/*                       - coptrans                                 */
/********************************************************************/

#ifdef __STDC__
void coptrans(integer derend1,
              integer derend2,
              integer inhend1,
              integer inhend2,
              lok *coplok,
              boolean *ident);
#else /* ! __STDC__ */
void coptrans();
#endif /* ! __STDC__ */

 void
#ifdef __STDC__
pareintrag(ptparlist *parmerk, Attrpos apo1, Attrpos apo2)
                        
                      
#else /* ! __STDC__ */
pareintrag(parmerk, apo1, apo2)
   ptparlist   *parmerk;
   Attrpos apo1, apo2;
#endif /* ! __STDC__ */

/********************************************************************/
/* Traegt 2 attributpositionen eines parameter der berechnungsfkt.  */
/* zweier identifizierter derived attribut der copysymbole in die   */
/* parameterliste ein, falls sie nicht schon vorhanden sind.        */
/*------------------------------------------------------------------*/
/* eingangsparameter : parmerk    parameterliste                    */
/*                     apo1,apo2  einzutragende attributpositionen  */
/* wird aufgerufen von :  coptrans                                  */
/********************************************************************/

{
   ptparlist   neupar, merk;
   boolean  found;

   neupar = (struct parlist *)getMem((unsigned)(sizeof(*neupar))); /* neues elt. init. */
   neupar->par[0] = apo1;           /* attr.positionen            */ 
   neupar->par[1] = apo2;           /* eintragen                  */
   neupar->nextpar = (struct parlist *)NIL;
   found = false;
   if ((*parmerk) == (struct parlist *)NIL)
      (*parmerk) = neupar;
   else {
      merk = (*parmerk);              /* suche Listenende           */
      while ((merk->nextpar != (struct parlist *)NIL) && !found) {
         if ((merk->par[0] == apo1) && (merk->par[1] == apo2))
            found = true;
         else
            merk = merk->nextpar;
      }
      if ((merk->par[0] != apo1) || (merk->par[1] != apo2))
         merk->nextpar = neupar;      /* neues elt ans listenende */
   }
}

 boolean
#ifdef __STDC__
ispar(ptparlist params, Attrpos apo, integer k)
                      
               
              
#else /* ! __STDC__ */
ispar(params, apo, k)
   ptparlist   params;
   Attrpos apo;
   integer  k;
#endif /* ! __STDC__ */

/********************************************************************/
/* Sucht eine gegebene attributposition des k-ten copy-symbols      */
/* in der parameterliste.                                           */
/*------------------------------------------------------------------*/
/* eingangsparameter : params parameterliste                        */
/*                     apo    gesuchte attributposition             */
/*                     k      index                                 */
/* wird aufgerufen von :  inhtmv                                    */
/********************************************************************/

{
   register boolean  ergebnis;
   ptparlist   parhilf;

   ergebnis = false;                              /* Vorbesetzung          */
   parhilf = params;
   while (parhilf != (struct parlist *)NIL) {
      if (parhilf->par[k - 1] == apo) {    /* apo gefunden ?        */
         ergebnis = true;
         parhilf = (struct parlist *)NIL;    /* Abbruchkriterium      */
      } else
         parhilf = parhilf->nextpar;         /* sonst naechstes Elt.  */
   }
   return ergebnis;
}

 void
#ifdef __STDC__
searchpar(ptparlist *params, boolean *find, Attrpos apo1, Attrpos apo2)
                       
                  
                      
#else /* ! __STDC__ */
searchpar(params, find, apo1, apo2)
   ptparlist   *params;
   boolean  *find;
   Attrpos apo1, apo2;
#endif /* ! __STDC__ */

 
/********************************************************************/
/* Sucht zwei gegebene attributposition der copysymbols in einem    */
/* element der parameterliste, liefert als ergebnis einen wahrheits-*/
/* wert und kettet das element aus der liste aus.                   */
/*------------------------------------------------------------------*/
/* eingangsparameter : params parameterliste                        */
/*                     find   ergebnisparameter                     */
/*                     apo    gesuchte attributposition             */
/*                     i      index                                 */
/* wird aufgerufen von :  inhtmv, altinhid                          */
/********************************************************************/

{
   ptparlist   lauf1, lauf2, hpt;

   lauf1 = (*params);
   lauf2 = (*params);
   (*find) = false;
   while ((lauf1 != (struct parlist *)NIL) && !(*find)) {
                            /* solange nicht am Ende und apo nicht gefunden */

      if ((lauf1->par[0] == apo1) && (lauf1->par[1] == apo2)) {
                            /* beide parameter gefunden                   */
         (*find) = true;    /* ergebnisparameter besetzen                 */
         if (lauf1 == (*params)){ /* listenelement ausketten */
				hpt = (*params);
            (*params) = (*params)->nextpar;
				free(hpt);
			}
         else{
            lauf2->nextpar = lauf1->nextpar; 
				free(lauf1);
			}
      } else {
         lauf2 = lauf1;
         lauf1 = lauf1->nextpar;  /* naechstes listenelement              */
      }
   }
}

 boolean
#ifdef __STDC__
altderid(integer anf3, integer end3, integer end4)
                             
#else /* ! __STDC__ */
altderid(anf3, end3, end4)
   integer  anf3, end3, end4;
#endif /* ! __STDC__ */
/********************************************************************/
/* Vorraussetzung : die 2 zu vergleichenden derived teilmengen sind */
/* schon einmal identifiziert, d.h. es koennen keine elemente mehr  */
/* umgeordnet werden und die typen stimmen ueberein.                */
/* Ueberprueft, ob berechnungsfkt. der beiden teilmengen ueberein-  */
/* einstimmen .                                                     */
/*------------------------------------------------------------------*/
/* eingangsparameter : anf3,end3,anf4,end4                          */
/*                         anfang/ende der der. tm der copy-symbole */
/* wird aufgerufen von : coptrans                                   */
/********************************************************************/
{
   boolean  result;

   result = true;                           /* vorbesetzung              */
   while ((anf3 <= end3) && result) {       /* solange nicht am ende     */
                                            /* und ergebnis 'TRUE'       */
      if ((Funkt_Name(Funkt_Of_Aufruf(Ber_Aufruf
              ((*l_coplok)[end3 - 1].attpos))) 
           == Funkt_Name(Funkt_Of_Aufruf(Ber_Aufruf
              ((*l_coplok)[end4 - 1].attpos))))) {
                                            /* und ber.-fkt. gleich      */
         end3 = end3 - 1;                   /* beide Enden um eins       */
         end4 = end4 - 1;                   /* erniedrigen               */
      } else
         result = false;                    /* ergebnis 'FALSE'          */
   }
   return(result);
}

 void
#ifdef __STDC__
altinhid(integer anf3, integer *end3, integer *end4)
                 
                         
#else /* ! __STDC__ */
altinhid(anf3, end3, end4)
   integer  anf3;
   integer  *end3, *end4;
#endif /* ! __STDC__ */
/********************************************************************/
/* Vorraussetzung : die 2 zu vergl. inhereted teilmengen sind       */
/* schon einmal identifiziert, d.h. es koennen keine elemente mehr  */
/* umgeordnet werden und die Typen stimmen ueberein.                */
/* Ueberprueft, ob die attpos als parameter fuer eine berechnungs-  */
/* funktion benoetigt werden.                                       */
/*------------------------------------------------------------------*/
/* eingangsparameter : anf3,end3,anf4,end4                          */
/*                         anfang/ende der inh. tm der copy-symbole */
/* wird aufgerufen von : coptrans                                   */
/* ruft auf : searchpar                                             */
/********************************************************************/
{
   while ((anf3 <= (*end3))) {           /* solange nicht am ende         */
      searchpar(&(l_param), &(l_findpar), 
         (*l_coplok)[*end3 - 1].attpos, (*l_coplok)[*end4 - 1].attpos);
                                         /* attpos 2 fkt.-parameter???    */
      (*end3) = (*end3) - 1;             /* beide Enden um 1 erniedrigen  */
      (*end4) = (*end4) - 1;
   }
}

 void
#ifdef __STDC__
dertmv(integer anf1, integer anf2, integer *end1, integer *end2)
                       
                         
#else /* ! __STDC__ */
dertmv(anf1, anf2, end1, end2)
   integer  anf1, anf2;
   integer  *end1, *end2;
#endif /* ! __STDC__ */
/********************************************************************/
/* Ueberprueft, ob die elemente 2er der. tm den selben typ und die  */
/* selben berechnungsregeln haben und ordnet sie ggf. passend um.   */
/* (aus selber berechnungsregel folgt nicht selber typ (wg. Kopie ))*/
/*------------------------------------------------------------------*/
/* eingangsparameter : anf3,end3,anf4,end4                          */
/*                         anfang/ende der der. tm der copy-symbole */
/* wird aufgerufen von : coptrans                                   */
/* ruft auf : eltausch                                              */
/********************************************************************/
{
   integer  lauf;
   boolean  tworest;

   integer  *ptanfgross, *ptanfklein, *ptendgross, *ptendklein;
 
   tworest = false;                     /* TRUE, falls 2 rest-tm          */
   if ( ((*end1) - anf1 + 1) >=         /* maechtigkeit der 1. derived tm */
        ((*end2) - anf2 + 1)) {         /* >= der 2. derived tm. ?        */
        ptanfgross = &anf1;
        ptendgross = end1;
        ptanfklein = &anf2;
        ptendklein = end2;
   } else {
        ptanfgross = &anf2;
        ptendgross = end2;
        ptanfklein = &anf1;
        ptendklein = end1;
   }
   while ((*ptanfklein <= *ptendklein) && !tworest) {
                 /* kleinere tm noch nicht am ende und keine 2 rest-tm */
      lauf = *ptanfgross;                   /* laufvariable                   */
      while (((Typ_Name(Typ_Of_Attr((*l_coplok)[lauf - 1].attr)) 
               != Typ_Name(Typ_Of_Attr((*l_coplok)[(*ptendklein) - 1].attr))) 
                                     /* typ ungleich       oder        */
              || (Funkt_Name(Funkt_Of_Aufruf(Ber_Aufruf
                     ((*l_coplok)[lauf - 1].attpos))) 
                  != Funkt_Name(Funkt_Of_Aufruf(Ber_Aufruf
                     ((*l_coplok)[(*ptendklein) - 1].attpos)))))
                                     /* fkt ungleich       und         */ 
             && (lauf < (*ptendgross)))    /* nicht am ende                  */
         lauf = lauf + 1;
      if ((Typ_Name(Typ_Of_Attr((*l_coplok)[lauf - 1].attr)) 
           == Typ_Name(Typ_Of_Attr((*l_coplok)[(*ptendklein) - 1].attr))) 
                                     /* falls typ gleich               */
          && (Funkt_Name(Funkt_Of_Aufruf(Ber_Aufruf
                 ((*l_coplok)[lauf - 1].attpos))) 
              == Funkt_Name(Funkt_Of_Aufruf(Ber_Aufruf
                 ((*l_coplok)[(*ptendklein) - 1].attpos))))) {
                                     /* und fkt. gleich                */
         eltausch(lauf, (*ptendgross), (*ptanfgross), l_coplok);
                                     /* elt an das tn-ende             */
         (*end1) = (*end1) - 1;      /* tm ende um 1 erniedrigen       */
         (*end2) = (*end2) - 1;
      } else
         tworest = true;             /* sonst 2 rest-tm                */
   }
}

 void
#ifdef __STDC__
inhtmv(integer anf1, integer anf2, integer *end1, integer *end2)
                       
                         
#else /* ! __STDC__ */
inhtmv(anf1, anf2, end1, end2)
   integer  anf1, anf2;
   integer  *end1, *end2;
#endif /* ! __STDC__ */
/********************************************************************/
/* Untersucht zuerst, welche attpos der beiden teilmengen als       */
/* zusammenpassende parameter verwendet werden koennen und stellt   */
/* sie an den tm-anfang.                                            */
/* Stellt dann die attpos der groesseren teilmenge, die spaeter als */
/* parameter evtl. noch gebraucht werden koennen an den tm-anfang,  */
/* damit sie nicht unnoetig fuer den typvergleich benutzt werden.   */
/* Ueberprueft, ob die elemente der beiden teilmengen den selben    */
/* typ haben und ordnet sie ggf. passend um.                        */
/*------------------------------------------------------------------*/
/* eingangsparameter : anf3,end3,anf4,end4                          */
/*                         anfang/ende der inh. tm der copy-symbole */
/* wird aufgerufen von : coptrans                                   */
/* ruft auf : eltausch                                              */
/********************************************************************/
{
   integer  lauf1, lauf2;
   integer  merkanf;
   boolean  tworest;

   integer  *ptanfgross, *ptanfklein, *ptendgross, *ptendklein;
   integer  *ptlaufgross, *ptlaufklein;
   integer  platzklein, platzgross;
 
   if ( ((*end1) - anf1 + 1) >=         /* maechtigkeit der 1. derived tm */
        ((*end2) - anf2 + 1)) {         /* >= der 2. derived tm. ?        */
        ptanfgross = &anf1;
        ptendgross = end1;
        ptanfklein = &anf2;
        ptendklein = end2;
        platzklein = 2;
        platzgross = 1;
        ptlaufgross = &lauf1;
        ptlaufklein = &lauf2;
   } else {
        ptanfgross = &anf2;
        ptendgross = end2;
        ptanfklein = &anf1;
        ptendklein = end1;
        platzklein = 1;
        platzgross = 2;
        ptlaufgross = &lauf2;
        ptlaufklein = &lauf1;
   }
   tworest = false;                    /* true, falls 2 rest-tm           */
   *ptlaufklein = (*ptendklein);                 /* tm-ende kopieren                */
   while ((*ptlaufklein >= *ptanfklein)) {
      if (ispar(l_param, (*l_coplok)[(*ptlaufklein) - 1].attpos, platzklein)) {
         *ptlaufgross = *ptanfgross;              /* laufvariable                    */
         l_findpar = false;   /* vorbesetzung                    */
         while ((*ptlaufgross <= *ptendgross) && !(l_findpar)) {
            searchpar(&(l_param), &(l_findpar),
                      (*l_coplok)[lauf1 - 1].attpos, 
                      (*l_coplok)[lauf2 - 1].attpos);
            *ptlaufgross = (*ptlaufgross) + 1;
         }
         if (l_findpar) {     /* falls attpos2 parameter         */
                                    /* falls parameter gefunden, dann  */
                                    /* tausche                         */
            eltausch((*ptlaufgross) - 1, *ptendgross, *ptanfgross, l_coplok);
            eltausch(*ptlaufklein, *ptendklein, *ptanfklein, l_coplok);
            (*end1) = (*end1) - 1;  /* tm-ende um 1 erniedrigen        */
            (*end2) = (*end2) - 1;
         }
      }
      *ptlaufklein = (*ptlaufklein) - 1;
   }
   /********************************************************************/
   /* Nun stehen die als zusammengehoerende parameter brauchbaren      */
   /* attpos der beiden teilmengen am teilmengenende.                  */
   /********************************************************************/
   if (*ptanfklein <= *ptendklein) {           /* kleinere tm noch nicht am ende  */
      merkanf = *ptanfgross;
      *ptlaufgross = *ptanfgross;
      while ((*ptlaufgross <= *ptendgross)) {  /* solange nicht am ende           */
         if (ispar(l_param, (*l_coplok)[(*ptlaufgross) - 1].attpos, platzgross)) {
                                    /* falls attpos parameter          */
            eltausch(merkanf, *ptlaufgross, *ptanfgross, l_coplok);
                                    /* tausche an den Anfang und       */
            merkanf = merkanf + 1;  /* erhoehe                         */
         }
         *ptlaufgross = (*ptlaufgross) + 1;         /* naechstes element               */
      }
      merkanf = merkanf - 1;        /* letztes als parameter           */
   }                                /* verwendbares elt                */
   /********************************************************************/
   /* Nun stehen die restlichen als parameter brauchbaren attpos der   */
   /* groesseren teilmenge am teilmengenanfang.                        */
   /********************************************************************/
     while ((*ptanfklein <= *ptendklein) && !tworest) {
                 /* kleinere tm noch nicht am ende und keine 2 rest-tm */
      *ptlaufgross = *ptendgross;
      while ((Typ_Name(Typ_Of_Attr((*l_coplok)[(*ptlaufgross) - 1].attr)) 
              != Typ_Name(Typ_Of_Attr((*l_coplok)[(*ptendklein) - 1].attr))) 
             && (*ptlaufgross > *ptanfgross))
      *ptlaufgross = (*ptlaufgross) - 1;
      if ((Typ_Name(Typ_Of_Attr((*l_coplok)[(*ptlaufgross) - 1].attr)) 
           == Typ_Name(Typ_Of_Attr((*l_coplok)[(*ptendklein) - 1].attr)))) {
                                    /* falls Typ gleich                */
         eltausch(*ptlaufgross, *ptendgross, *ptanfgross, l_coplok);
                                    /* tausche ans ende                */
         if (*ptlaufgross < merkanf) {
            eltausch(*ptlaufgross, merkanf, *ptanfgross, l_coplok);
            merkanf = merkanf - 1;  /* letztes als parameter verwend-  */
         }                          /* bares elt                       */
         (*end1) = (*end1) - 1;     /* tm-ende um 1 erniedrigen        */
         (*end2) = (*end2) - 1;
      } else
         tworest = true;            /* sonst 2 rest-tm                 */
   }
}


 void
#ifdef __STDC__
coptrans(integer derend1,
         integer derend2,
         integer inhend1,
         integer inhend2,
         lok *coplok,
         boolean *ident)
                                               
                   
                   
#else /* ! __STDC__ */
coptrans(derend1, derend2, inhend1, inhend2, coplok, ident)
   integer  derend1, derend2, inhend1, inhend2;
   lokdat   coplok;
   boolean  *ident;
#endif /* ! __STDC__ */
/********************************************************************/
/* Bearbeitet die lokaldatenstruktur zweier copy-symbole.           */
/* Untersucht ob die zu behandelnden teilmengen schon identifiziert */
/* sind und ob die behandelten teilmengen neu eingeteilt und        */
/* identifiziert werden koennen, und ob die 2 copysymbole total     */
/* identifiziert werden koennen.                                    */
/*------------------------------------------------------------------*/
/* wird aufgerufen von :                                            */
/*------------------------------------------------------------------*/
/* enthaelt aufrufe der prozeduren:  - eltausch                     */
/*                                   - identtm                      */
/*                                   - neutm                        */
/* enthaelt aufrufe der funktionen:  - isrek                        */
/*------------------------------------------------------------------*/
/* enthaelt die unterprozeduren:  - pareintrag                      */
/*                                - searchpar                       */
/*                                - altinhid                        */
/*                                - inhtmv                          */
/*                                - dertmv                          */
/* enthaelt die funktionen :      - ispar                           */
/*                                - altderid                        */
/*------------------------------------------------------------------*/
/* eingangsparameter : derend1,derend1,inhend1,inhend2              */
/*                           der/inh tm-ende des 1./2. copy-symbols */
/*                     coplok  aktuelle lokaldatenstruktur          */
/*                     ident   bool'sche var. fuer die copy-ident.  */
/* wird aufgerufen von :  maintrans                                 */
/********************************************************************/

{
   integer  deranf1, deranf2, inhanf1, inhanf2, dmerk1, dmerk2,
      danf1, danf2;
   Aparam   quelle1, quelle2;
	ptparlist hpt;

   l_coplok = (lokdat *)coplok;

   dmerk1 = derend1;
   dmerk2 = derend2;
   while ((derend1 > inhend1) && (derend2 > inhend2) && (*ident)) {
      deranf1 = derend1;
      deranf2 = derend2;
      while ((*l_coplok)[deranf1 - 1].index == 0)
         deranf1 = deranf1 - 1;        /* berechnung des 1.tm-anf.        */
      while ((*l_coplok)[deranf2 - 1].index == 0)
         deranf2 = deranf2 - 1;        /* berechnung des 2.tm-anf.        */
      if (isrek(deranf1, deranf2, (*l_coplok))) {
                                       /* schon identifiziert             */
         if (altderid(deranf1, derend1, derend2)) {
            derend1 = deranf1 - 1;     /* falls alte identifikation gilt  */
            derend2 = deranf2 - 1;
         } else
            (*ident) = false;          /* keine identifikation            */
      } else {
         dertmv(deranf1, deranf2, &derend1, &derend2);
                                      /* vergl. der 2 letzten tm          */
         if ((deranf1 <= derend1) && (deranf2 <= derend2))
                                      /* falls 2 rest-tm                  */
            (*ident) = false;         /* keine identifikation             */
         else {
            if ((deranf1 > derend1) && (deranf2 <= derend2)) {
                                      /* rest bei 2.tm                    */
               neutm(deranf2, derend2 + 1, l_coplok);
               identtm(derend2 + 1, deranf1, l_coplok);
            }
            if ((deranf1 <= derend1) && (deranf2 > derend2)) {
                                      /* rest bei 1.tm                    */
               neutm(deranf1, derend1 + 1, l_coplok);
               identtm(derend1 + 1, deranf2, l_coplok);
                                 /* tm-neueinteilung und -identifizierung */
            }
            if ((deranf1 > derend1) && (deranf2 > derend2))
               identtm(deranf1, deranf2, l_coplok);
                                 /* falls keine rest-tm,tm-identifizierung*/
         }
      }
   }
   /********************************************************************/
   /* Jetzt sind die derived attribute der copy-symbole identifiziert, */
   /* falls moeglich.                                                  */
   /********************************************************************/
 
   if ((inhend1 > 0) && (inhend2 > dmerk1) && (*ident)) {
                /* falls inh. el. vorhanden und der. el. identifiziert    */
      danf1 = inhend1 + 1;
      danf2 = inhend2 + 1;

		while(l_param != (ptparlist)NIL){
			hpt = l_param;
			l_param = l_param->nextpar;
			free(hpt);
		}
      /* l_param = (struct parlist *)NIL; */

      while ((danf1 <= dmerk1) && (danf2 <= dmerk2)) {
                                        /* solange derived elt vorhanden  */
         quelle1 = FirstArg(Ber_Aufruf((*l_coplok)[danf1 - 1].attpos));
         quelle2 = FirstArg(Ber_Aufruf((*l_coplok)[danf2 - 1].attpos));
                                        /* 1.parameter der fkt            */
         while ((quelle1 != (Aparam)NIL) && (quelle2 != (Aparam)NIL)) {
                                        /* solange parameter vorhanden    */
            pareintrag(&(l_param), AttPos_Of_Param(quelle1),
                       AttPos_Of_Param(quelle2));
                                        /* trage in parameterliste ein    */
            quelle1 = NextArg(quelle1);
            quelle2 = NextArg(quelle2); /* naechste parameter           */
         }
         danf1 = danf1 + 1;
         danf2 = danf2 + 1;             /* naechste elemente              */
      }
      /********************************************************************/         
      /* Jetzt stehen die als parameter der berechnungsfunktionen der     */
      /* derived attribute benoetigten attributpositionen in der          */
      /* parameterliste. Gleiche parameter der berechnungsfunktionen von  */
      /* identifizierten attributen stehen in einem parameterfeld.        */
      /********************************************************************/

      l_findpar = false;                /* initialisierung                */
      while ((inhend1 > 0) && (inhend2 > dmerk1) && (*ident)) {
                                        /* noch inherited elt und identif.*/
         inhanf1 = inhend1;
         inhanf2 = inhend2;
         while ((*l_coplok)[inhanf1 - 1].index == 0)
            inhanf1 = inhanf1 - 1;      /* berechnung des 1.tm-anf        */
         while ((*l_coplok)[inhanf2 - 1].index == 0)
            inhanf2 = inhanf2 - 1;
         if (isrek(inhanf1, inhanf2, (*l_coplok))) /* schon identif.    */
            altinhid(inhanf1, &inhend1, &inhend2);
         else {
            inhtmv(inhanf1, inhanf2, &inhend1, &inhend2); /* vergleiche   */
                                        /* die 2 letzten tm               */
            if ((inhanf1 <= inhend1) && (inhanf2 <= inhend2))
                                        /* 2 rest-tm                      */
               if ((l_param) == (struct parlist *)NIL) {
                                        /* falls keine parameter mehr     */
                  neutm(inhanf1, inhend1 + 1, l_coplok);
                  neutm(inhanf2, inhend2 + 1, l_coplok);
                  identtm(inhend1 + 1, inhanf2 + 1, l_coplok);
                                        /* tm-neueinteilung und identif.  */
                  inhend1 = 0;          /* abbruchkriterium               */
               } else
                  (*ident) = false;
            else {
               if ((inhanf1 > inhend1) && (inhanf2 <= inhend2)) {
                                        /* rest bei 2.tm                  */
                  neutm(inhanf2, inhend2 + 1, l_coplok);
                  identtm(inhend2 + 1, inhanf1, l_coplok);
                                        /* tm-neueinteilung u. identif.   */
               }
               if ((inhanf1 <= inhend1) && (inhanf2 > inhend2)) {
                                        /* rest bei 1.tm                  */
                  neutm(inhanf1, inhend1 + 1, l_coplok);
                  identtm(inhend1 + 1, inhanf2, l_coplok);
                                        /* tm-neueinteilung u. identif.   */
               }
                                        /* falls kein rest-tm             */
               if ((inhanf1 > inhend1) && (inhanf2 > inhend2))
                  identtm(inhanf1, inhanf2, l_coplok);
                                        /* tm-identif.                    */
            }
         }
      }
      /*********************************************************************/
      /* Moeglicherweise konnten alle attribute identifiziert werden, aber */
      /* nicht fuer alle parameter konnten die passenden attpos identifi-  */
      /* ziert werden.                                                     */
      /*********************************************************************/

      if ((l_param) != (struct parlist *)NIL)
         (*ident) = false;              /* nicht alle param. passen       */
   }
}

 void
#ifdef __STDC__
samecopy(ptcopy cone, ptcopy ctwo)
                 
                 
#else /* ! __STDC__ */
samecopy(cone, ctwo)
   ptcopy   cone;
   ptcopy   ctwo;
#endif /* ! __STDC__ */
/**********************************************************************/
/**********************************************************************/
/*   Prozedur 'SAMECOPY' steuert den Attrubutvergleich zwischen den   */
/*   beiden angegenenen COPY-Symbolen . Sie vergleicht zunaechst die  */
/* derived Attribute und erst bei Erfolg die gesamte Attributstruktur */
/**********************************************************************/
/**********************************************************************/
{
   integer  ioneend, itwoend, doneend, dtwoend;
   boolean  sameatt;

   sameatt = true;
   
   dercopybau(cone, ctwo);            /* vergleichbare derived Attribute ?*/
   doneend = loklength / 2;
   dtwoend = loklength;
   ioneend = 0;
   itwoend = doneend;
   coptrans(doneend, dtwoend, ioneend, itwoend, lokstrukt, &sameatt);
          /* derived Attribute vergleichbar => alle Attribute vergleichen */
   if (sameatt) {
      attcopybau(cone, ctwo, &doneend, &dtwoend, &ioneend, &itwoend);
      coptrans(doneend, dtwoend, ioneend, itwoend, lokstrukt, &sameatt);
      if (sameatt) {
         loktoglob();
         ctwo->name = cone->name;
      }
   }
}

 void
#ifdef __STDC__
copygen(int zaehler)
            
#else /* ! __STDC__ */
copygen(zaehler)
int zaehler;
#endif /* ! __STDC__ */

/* zaehler >= copyname; Alle Copynamen, die noch identifiziert werden
   koennen(da sie noch nicht ausgegeben wurden) sind < copyname !*/
/* Alle Copy's, die Auxiliaries benuetzen haben bereits eine Namen 
   >= copyname und < zaehler bekommen */
/******************************************************************/
/******************************************************************/
/* Prozedur 'COPYGEN' steuert den Attributvergleich zwischen den  */
/*   eingefuehrten COPY-Symbolen . Sie vergleicht paarweise alle  */
/*    COPYSymbole mit derselben Anzahl von derived Attributen .   */
/******************************************************************/
/******************************************************************/
{
   ptcopy   anf, search, nextanf, nextsearch;
   integer  maxcder;
   register integer  loop;

   forcopy = true;

   /* maximale Anzahl von derived Attributen eines copy-Symbols */
   maxcder = 0;
   search = copyinfo;
   while (search != (struct copy *)NIL) {
      if (search->inhnumb > maxcder)
         maxcder = search->inhnumb;
      search = search->nextcopy;
   }

         for (loop = 1; loop <= maxcder ; loop++) { /* Ablaufsteuerung    */
            anf = (struct copy *)NIL;   /* anf und search besetzen        */
            search = (struct copy *)NIL;
            nextanf = copyinfo;
            while (nextanf != (struct copy *)NIL) {
               if (((nextanf->inhnumb == loop) 
                    && (nextanf->name < copyname))) {
                  anf = nextanf;
                  anf->name = zaehler++;
                  nextanf = (struct copy *)NIL;
               } else
                  nextanf = nextanf->nextcopy;
            }
            if (anf != (struct copy *)NIL)
               nextanf = anf->nextcopy;
            while (nextanf != (struct copy *)NIL) {
               if (((nextanf->inhnumb == loop) 
                    && (nextanf->name < copyname))) {
                  search = nextanf;
                  nextanf = (struct copy *)NIL;
               } else
                  nextanf = nextanf->nextcopy;
            }
            while (((search != (struct copy *)NIL) 
                    && (anf != (struct copy *)NIL))) {
               nextanf = (struct copy *)NIL;
               nextsearch = (struct copy *)NIL;
               while (search != (struct copy *)NIL) {
                  if (((search->inhnumb == loop) 
                       && (search->name < copyname))) {
                     samecopy(anf, search);
                     if (((nextanf == (struct copy *)NIL)
                          && (copyname > search->name)))
                        nextanf = search;
                     if (((nextsearch == (struct copy *)NIL) 
                          && (nextanf != search) 
                          && (nextanf != (struct copy *)NIL) 
                          && (copyname > search->name)))
                        nextsearch = search;
                  }
                  search = search->nextcopy;
               }
               anf = nextanf;
               if (anf != (struct copy *)NIL)
                  anf->name = zaehler++;
               search = nextsearch;
            }
         }

   copyanz = zaehler-copyname;
   anf = copyinfo;                      
   while (anf != (ptcopy)NIL) {             /* Copy-Namen von 1 ..copyanz */
      anf->name = anf->name - copyname + 1; /* mit laufender Nummer       */
      anf = anf->nextcopy;
   }

   forcopy = false;
}


