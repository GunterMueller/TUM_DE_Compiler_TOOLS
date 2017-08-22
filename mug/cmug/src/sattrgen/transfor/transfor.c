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

/* transfor */
/* Aktueller Stand vom 6.11.89 */
/* Aenderungen: */
/* malloc() durch getMem() ersetzt */
/* cpos wird gefreet: in maintrans */
/* maintrans: Umbenennung der Aux-Copy's und Copy-Identifizierung */

/********************************************************************/
/* enthaelt die prozedur zur steuerung des ablaufs der              */
/* transformation einer L-attributierten GRAMMATIK in eine          */
/* S-attributierten GRAMMATIK :                                     */
/*                       - maintrans                                */
/*------------------------------------------------------------------*/
/* enthaelt die prozedur zum transformieren der lokaldatenstruktur: */
/*                       - loktrans                                 */
/********************************************************************/

#define EXTERN extern
#include "globals.h"

typedef struct merkepos * ptmerkepos; /* zum Merken der prodpos, die      */
typedef struct merkepos {             /* noch ein zweites mal bearbeitet  */
   ptmerkepos  nachfpos;              /* werden, da vor ihnen ein         */
   Product   mpro;                    /* copy-symbol benoetigt wird       */
   Prodpos   mpos;
}  merkepos;

lokdat   Ll_lokstrukt2;                /* letzte aktuelle lokdat */
integer  l_length;
integer  l_deranf;
Prodpos  Ll_aktpropos;
Product  l_aktprod;
integer  l_derend;
boolean  *l_first;
ptcopy   *l_copyinfo;
lokdat   *l_lokstrukt1;

#ifdef __STDC__
extern void globtolok(Product production,
                      Prodpos position,
                      boolean freemtmenge);
extern void loktoglob(void);
extern void copygen(int zaehler);
extern void einlesen(ptglobdat *glob);
extern void newprodprint(FILE *out, FILE *out1);
extern void globprint(FILE *out);
extern boolean cp_test_aux(ptcopy cp);
extern ptcopy copyproof(Product pprod, Prodpos pprodpos);
#else /* ! __STDC__ */
extern void globtolok();
extern void loktoglob();
extern void copygen();
extern void einlesen();
extern void newprodprint();
extern void globprint();
extern boolean cp_test_aux();
extern ptcopy copyproof();
#endif /* ! __STDC__ */

#ifdef __STDC__
void maintrans(void);
void eltausch(integer i, integer k, integer tmanf, lok *Xlok);
void neutm(integer tmanf, integer neuanf, lok *Xlok);
void identtm(integer tm1, integer tm2, lok *Xlok);
boolean isrek(integer tmanf1, integer tmanf2, lok *Xlok);
#else /* ! __STDC__ */
void maintrans();
void eltausch();
void neutm();
void identtm();
boolean isrek();
#endif /* ! __STDC__ */

 void
#ifdef __STDC__
eltausch(integer i, integer k, integer tmanf, lok *Xlok)
                        
                 
#else /* ! __STDC__ */
eltausch(i, k, tmanf, Xlok)
   integer  i, k, tmanf;
   lokdat   Xlok;
#endif /* ! __STDC__ */
/********************************************************************/
/* tauscht die komponenten 'attr' und 'attpos' von 2 elementen      */
/* einer teilmenge und aller identifizierten teilmengen der lokal-  */
/* datenstruktur  (die komponente 'index' wird nicht getauscht)     */
/*------------------------------------------------------------------*/
/* eingangsparameter : i,k   index der auszutauschenden elemente    */
/*                     tmanf index des tm-anfangs                   */
/*                     Xlok   lokaldatenstruktur                     */
/* wird aufgerufen von :  loktrans                                  */
/*                        coptrans in segment identcop              */
/********************************************************************/
{
   Attr  hilfatt;
   Attrpos hilfapo;
   integer  iabst, kabst, anf;

   if (i != k) {                        /* falls 2 verschiedene elt.      */
      anf = tmanf;                      /* index des tm-anfang            */
      iabst = i - tmanf;                /* abstand zw. element i,k        */
      kabst = k - tmanf;                /* und tm-anfang                  */
      do {
         {
            hilfatt = Xlok[i - 1].attr; /*         austausch der beiden */
            hilfapo = Xlok[i - 1].attpos; /*                komponenten */
            Xlok[i - 1].attr = Xlok[k - 1].attr; /* und 'attpos' eines*/
            Xlok[i - 1].attpos = Xlok[k - 1].attpos; /*elt's in einer */
            Xlok[k - 1].attpos = hilfapo; /*                  teilmenge */
            Xlok[k - 1].attr = hilfatt;

            anf = Xlok[anf - 1].index; /* tm.-anfang der ident. tm      */
            i = anf + iabst;            /* index der zu tauschenden       */
            k = anf + kabst;            /* elt der ident. tm.             */
         }
      } while (!((anf == tmanf)));      /* bis wieder am anfang           */
   }
}

 void
#ifdef __STDC__
neutm(integer tmanf, integer neuanf, lok *Xlok)
                          
                 
#else /* ! __STDC__ */
neutm(tmanf, neuanf, Xlok)
   integer  tmanf, neuanf;
   lokdat   Xlok;
#endif /* ! __STDC__ */
/********************************************************************/
/* Teilt eine teilmenge und alle identifizierten teilmengen in zwei */
/* teilmengen.                                                      */
/*------------------------------------------------------------------*/
/* eingangsparameter : tmanf  index des tm-anfangs                  */
/*                     neuanf index des neuen tm-anfangs            */
/*                     Xlok    lokaldatenstruktur                   */
/* wird aufgerufen von :  loktrans                                  */
/*                        coptrans in segment identcop              */
/********************************************************************/
{
   integer  alt, neu, abst;

   if (tmanf != neuanf) {               /* ueberhaupt neue tm ?           */
      alt = tmanf;                      /* alten und neuen tm-anf.        */
      neu = neuanf;                     /* kopieren                       */
      abst = neu - alt;                 /* abstand zw. den beiden ident.  */
      do {                              /* tm der mneuen tm eintragen     */
         {
            Xlok[neu - 1].index = Xlok[alt - 1].index + abst;
            alt = Xlok[alt - 1].index; /* tm-anf der ident. tm der      */
            neu = alt + abst;           /* alten und neuen tm             */
         }
      } while (!((alt == tmanf)));      /* bis wieder an anfang           */
   }
}

 void
#ifdef __STDC__
identtm(integer tm1, integer tm2, lok *Xlok)
                     
                 
#else /* ! __STDC__ */
identtm(tm1, tm2, Xlok)
   integer  tm1, tm2;
   lokdat   Xlok;
#endif /* ! __STDC__ */
/********************************************************************/
/* identifiziert zwei teilmengen miteinander und verbindet die      */
/* identitaetsketten.                                               */
/*------------------------------------------------------------------*/
/* eingangsparameter : tm1,tm2  tm-anfang der zu ident. tm          */
/*                     Xlok      lokaldatenstruktur                  */
/* wird aufgerufen von :  loktrans                                  */
/*                        coptrans in segment identcop              */
/********************************************************************/
{
   integer  minimum, min, max, m;

   minimum = tm1;
   min = tm2;
   while (Xlok[minimum - 1].index < minimum) /* berechnung der beiden   */
      minimum = Xlok[minimum - 1].index; /* tm der identitaetsketten mit*/
   while (Xlok[min - 1].index < min)  /* mit dem kleinsten tm-anfang    */
      min = Xlok[min - 1].index;
   if (min < minimum) {
      m = minimum;                      /* das absolute minimum der beiden*/
      minimum = min;                    /* ketten steht jetzt in 'minimum */
      min = m;
   }
   if (Xlok[minimum - 1].index < Xlok[min - 1].index) {
      m = Xlok[minimum - 1].index;
      Xlok[minimum - 1].index = Xlok[min - 1].index;
      Xlok[min - 1].index = m;        /* die vorderste tm zeigt nun     */
   }                                    /* auf die am weitest hinten      */
                                        /* stehende tm.                   */
   max = Xlok[minimum - 1].index;     /* absolutes maxinum              */
   if (max != min) {                    /* falls nicht schon verkettet    */
      do {
         {
            if (Xlok[min - 1].index > Xlok[max - 1].index) {
               m = Xlok[min - 1].index; /* falls min auf den naechst-   */
                                          /* groesste zeigt, dann tausche */
               Xlok[min - 1].index = Xlok[max - 1].index;
               Xlok[max - 1].index = m;
            }
            max = Xlok[max - 1].index; /* naechstgroesster index        */
         }
      } while (!((Xlok[min - 1].index == minimum) || (max == min)));
                                        /* bis neue kette geschlossen     */
   }
}

 boolean
#ifdef __STDC__
isrek(integer tmanf1, integer tmanf2, lok *Xlok)
                           
                 
#else /* ! __STDC__ */
isrek(tmanf1, tmanf2, Xlok)
   integer  tmanf1, tmanf2;
   lokdat   Xlok;
#endif /* ! __STDC__ */
/********************************************************************/
/* Ueberprueft ob zwei teilmengen schon miteinander identifiziert   */
/* sind.                                                            */
/*------------------------------------------------------------------*/
/* eingangsparameter : tmanf1,tmanf2 indizes der tm-anfaenge        */
/*                     Xlok           lokaldatenstruktur             */
/* wird aufgerufen von :  loktrans                                  */
/*                        coptrans in segment identcop              */
/********************************************************************/
{
   integer  merkanf;

   merkanf = tmanf1;                                 /*  tm-anf. kopieren */
   while (   (Xlok[tmanf1 - 1].index != tmanf2)     /*   identifiziert ? */
          && (Xlok[tmanf1 - 1].index != merkanf)    /*  wieder am anfang */
         )
      tmanf1 = Xlok[tmanf1 - 1].index;                      /* ident.-tm */
   if (Xlok[tmanf1 - 1].index == tmanf2)       /* falls identifiziert    */
      return(true);
   else
      return(false);
}

#ifdef __STDC__
void loktrans(lok *lokstrukt1,
              ptcopy *copyinfo,
              boolean *first,
              integer derend,
              integer inhend,
              Product aktprod,
              Prodpos aktpropos);
#else /* ! __STDC__ */
void loktrans();
#endif /* ! __STDC__ */

 integer
#ifdef __STDC__
suchmax(integer m, lok *Xlok)
              
                 
#else /* ! __STDC__ */
suchmax(m, Xlok)
   integer  m;
   lokdat   Xlok;
#endif /* ! __STDC__ */
/********************************************************************/
/* Sucht im inhereted teil der letzten aktuellen lokalstruktur das  */
/* (lokstrukt2) element, das diesselbe attpos (berechnungsregel)    */
/* hat, wie das element m in der veraenderten lokaldatenstruktur    */
/* (lokstrukt1) und am weitesten hinten steht (hoher index).        */
/*------------------------------------------------------------------*/
/* eingangsparameter : m  index des gesuchten elements              */
/* wird aufgerufen von :  copyeintrag                               */
/********************************************************************/
{
   register integer  hilf_k;
   register integer  k;

   hilf_k = 0;                               /* ergebnis vorbesetzen   */
   for (k = beranfang; k <= l_length ; k++)  /* schleife ueber inh.teil*/
      if (Xlok[k - 1].attpos == (*l_lokstrukt1)[m - 1].attpos)
                                             /* elt gefunden ?         */
         hilf_k = k;                         /* ergebnis = index       */
   return(hilf_k);
}

 void
#ifdef __STDC__
copyeintrag(integer inhend4, integer copyanz)
                             
#else /* ! __STDC__ */
copyeintrag(inhend4, copyanz)
   integer  inhend4, copyanz;
#endif /* ! __STDC__ */
/********************************************************************/
/* Prueft zuerst, ob die behandelte produktionsposition zum ersten  */
/* mal in bearbeitung ist. Falls ja, so wird die bearbeitung        */
/* abgebrochen und zu einem spaeteren zeitpunkt wiederholt.         */
/* Ansonsten werden die attpos (berechnungsregeln) der zu kopieren- */
/* den elemente in der originalen lokaldatenstruktur (lokstrukt2)   */
/* moeglichst weit hinten (hoher index) gesucht, damit so wenig wie */
/* moeglich elemente kopiert werden muessen.                        */
/* Traegt das zugehoerige copy-symbol in die copyliste ein.         */
/*------------------------------------------------------------------*/
/* eingangsparameter : inhend4 index des inh. tm-endes              */
/*                     inhanf4 index des inh. tm-anfangs            */
/*                     copyanz anzahl der zu kopierenden elemente   */
/* wird aufgerufen von :  loktrans                                  */
/* ruft auf :  suchmax, eltausch, neutm                             */
/********************************************************************/
{
   lokdat   merklok;
   integer  tmanf, tmend, max, merkanf;
   register integer  i;
   ptcopy   copy1, copyhilf;

   if (*l_first) {                      /* prodpos wird zum 1. mal        */
      (*l_first) = false;               /* bearbeitet                     */
      l_length = 0;                     /* abbruchkriterium               */
   } else {                             /* copysymbol berechnen und       */
                                        /* eintragen                      */
     /*********************************************************************/
     /* die zu kopierenden elemente sind:                                 */
     /* lokstrukt1(.inhend4 + 1.)...lokstrukt1(.inhend4 + copyanz)        */
     /*********************************************************************/
      merkanf = 201;                    /* vorbesetzung                   */
      LDCOPY(Ll_lokstrukt2, merklok);   /* merklok = Ll_lokstrukt2;       */
      for (i = 1; i <= copyanz; i++) {       
         max = suchmax(inhend4 + i, merklok); /* elt mit gleicher   */
                                        /* attpos (berechn.-regel) das am */
                                        /* weitesten hinten steht         */
         merklok[max - 1].attpos = (Attrpos)NIL;
         tmanf = max;
         while (Ll_lokstrukt2[tmanf - 1].index == 0)
                                        /* berechnung d.tm-anfangs der tm */
            tmanf = tmanf - 1;          /* die max enthaelt               */
         if (tmanf < merkanf) {         /* falls geaendert werden muss    */
            tmend = max;                /* uns tm-ende unbekannt.         */
            while ((Ll_lokstrukt2[tmend + 1 - 1].index == 0) 
                   && (tmend < loklength) && (tmend < l_length)
                  )               
               tmend = tmend + 1;       /* berechnung des tm-endes:       */
         }                              /* length ist in lokstrukt2       */
                                        /* kein teilmengenende !!         */
         /*****************************************************************/
         /* das element wird ans ende der teilmenge gestellt, falls noetig*/
         /*****************************************************************/
         if (tmanf <= merkanf) {  /* falls geaendert werden muss    */
            eltausch(max, tmend, tmanf, Ll_lokstrukt2);
            eltausch(max, tmend, tmanf, merklok); /* elt ans tm-ende*/
            merkanf = tmanf;      /* tm-anfang merken               */
            tmend = tmend - 1;    /* tm-ende erniedrigen            */
         }
      } /* for */                             /* neue zubearbeitende             */
      LDCOPY(Ll_lokstrukt2, (*l_lokstrukt1)); /* *l_lokstrukt1 = Ll_lokstrukt2; */
                                       /* lokaldatenstruktur              */
      l_length = tmend;                /* laenge der lokalstruktur        */
                                       /* ohne zu kopierende elt'e        */
      neutm(tmanf, tmend + 1, l_lokstrukt1); /* neue tm-einteilung, */
                                       /* aber nur in lokstrukt1 !!       */
     /* lokstrukt2 ist wieder letzte aktuelle Lokaldatenstruktur          */
 
     /*********************************************************************/
     /* nun muss noch dass neue copysymbol eingefuehrt werden, bzw. wenn  */
     /* schon eines existiert, die 'inhnumb'-komponente erhoeht werden    */
     /*********************************************************************/
      if (*l_copyinfo == (struct copy *)NIL) { 
         (*l_copyinfo) = (struct copy *)
                           getMem((unsigned)(sizeof(*(*l_copyinfo))));
                                        /*                  copyinfo init */
         (*l_copyinfo)->nextcopy = (struct copy *)NIL;
         (*l_copyinfo)->name = copyname; /*     eindeutige laufende nr. */
         (*l_copyinfo)->inhnumb = loklength - l_length;
                                        /*         anz zu kopierender elt */
         (*l_copyinfo)->prod = l_aktprod; /*       einfuegestelle         */
         (*l_copyinfo)->propos = Ll_aktpropos;
         copyname = copyname + 1;       /* laufende nr. um 1 erhoehen     */
      } else {
         copyhilf = *l_copyinfo;    /* copystruktur kopieren          */
         while (copyhilf->nextcopy != (struct copy *)NIL)
            copyhilf = copyhilf->nextcopy;
         if ((copyhilf->prod != l_aktprod) 
             || (copyhilf->propos != Ll_aktpropos)
            ) {                         /*    falls noch kein copysymbol */
                                        /*       fuer diese prodpos ex., */
                                        /*         dann neues copysymbol */
            copy1 = (struct copy *)getMem((unsigned)(sizeof(*copy1)));
            copy1->nextcopy = (struct copy *)NIL;
            copy1->name = copyname;
            copy1->inhnumb = loklength - l_length;
            copy1->prod = l_aktprod;
            copy1->propos = Ll_aktpropos;

            copyhilf->nextcopy = copy1; /* ans kettenende haengen         */
            copyname = copyname + 1;    /* laufende nr. um 1 erhoehen     */
         } else
            copyhilf->inhnumb = loklength - l_length; /*  sonst anz */
      }                                 /* der zu kopierenden attr.       */
   }                                    /* veraendern                     */
}

 integer
#ifdef __STDC__
attpossuch(integer tmanf, integer tmend, integer el, lok *Xlok)
                             
                 
#else /* ! __STDC__ */
attpossuch(tmanf, tmend, el, Xlok)
   integer  tmanf, tmend, el;
   lokdat   Xlok;
#endif /* ! __STDC__ */
/********************************************************************/
/* Sucht eine gegebene attpos einem vorgegebenen abschnitt der lokal*/
/* struktur und liefert als ergebnis den index des gefundenen el. . */
/* Falls die attributposition nicht gefunden wird, liefert die      */
/* Funktion als ergebnis 0.                                         */
/*------------------------------------------------------------------*/
/* eingangsparameter : tmanf4 index ab dem gesucht wird             */
/*                     tmend4 index bis zu dem gesucht wird         */
/*                     el     index des gesuchten elements          */
/*                     Xlok    lokaldatenstruktur                    */
/* wird aufgerufen von :  rek                                       */
/********************************************************************/
{
   integer  tmlauf;

   tmlauf = tmanf;                      /* laufvariable                   */
   while ((Xlok[tmlauf - 1].attpos != Xlok[el - 1].attpos) /*   solange */ 
          && (tmlauf < tmend)           /* attpos nicht gefunden und nicht*/
         )                              /* am ende                        */
      tmlauf = tmlauf + 1;
   if ((Xlok[tmlauf - 1].attpos == Xlok[el - 1].attpos))/*falls gefunden*/
      return(tmlauf);                     /* ergebnis = index               */
   else
      return(0);                          /* ergebnis = 0                   */
}

 void
#ifdef __STDC__
rek(integer deranf2, integer derend2, integer inhanf2, integer *inhend2)
                                      
                     
#else /* ! __STDC__ */
rek(deranf2, derend2, inhanf2, inhend2)
   integer  deranf2, derend2, inhanf2;
   integer  *inhend2;
#endif /* ! __STDC__ */
/********************************************************************/
/* Vorraussetzung: die zu vergleichenden teilmengen sind total      */
/* rekursiv, d. h. sie sind bereits identifiziert und werden noch   */
/* einmal vollstaendig aufeinander abgebildet.                      */
/* Fall 1: die neue abbildung ist gleich der alten                  */
/*         dann passiert nichts                                     */
/* Fall 2: die neue abbildung ist ungleich der alten                */
/*         dann werden die verschiedenen zyklen (mind. einer)       */
/*         durchlaufen und abwechselnd ein inhereted element an     */
/*         den anfang  bzw. ans ende der teilmenge gestellt und     */
/*         anfang  bzw. ende um 1 erhoeht bzw. erniedrigt.          */
/*------------------------------------------------------------------*/
/* eingangsparameter : deranf2,derend2,inhanf2,inhend2              */
/*                            index des der./inh. tm-anfangs/endes  */
/* wird aufgerufen von : loktrans                                   */
/* ruft auf :            eltausch, attpossuch                       */
/********************************************************************/
{
   integer  imerkanf, imerkend, inh, der1, der2, idinh,
      i, j;

   imerkanf = inhanf2;                  /* tm-anf und -ende merken        */
   imerkend = (*inhend2);
   inh = inhanf2;                       /* 1, inh. elt                    */
   i = 1;
   do {
      {
         der1 = attpossuch(deranf2, derend2, inh, *l_lokstrukt1);
                                        /* suche attpos (ber.-regel) v.inh*/
         idinh = imerkanf + der1 - deranf2; /* suche ident. inh.elt v. der*/

         if ((inhanf2 <= idinh) && (idinh <= (*inhend2)) && (idinh != inh)) {
            eltausch(inhanf2, inh, imerkanf, l_lokstrukt1);
                                        /* stelle inh an den anfang       */
            if ((inhanf2 == idinh))     /* stelle idinh an das ende       */
               eltausch((*inhend2), inh, imerkanf, l_lokstrukt1);
            else
               eltausch((*inhend2), idinh, imerkanf, l_lokstrukt1);
            der2 = attpossuch(l_deranf, l_derend,
                              (*inhend2), *l_lokstrukt1);
                                        /* suche attpos von inh           */
            inhanf2 = inhanf2 + 1;      /* tm-anfang und -ende um 1       */
            (*inhend2) = (*inhend2) - 1;/* erhoehen bzw. erniedrigen      */
            inh = imerkanf + der2 - deranf2;
            if ((inhanf2 > inh) || (inh > (*inhend2)))
               inh = inhanf2;           
                          /* neues inh ist ident. von apo oder, falls     */
                          /* ausserhalb zulaessiger bereich, neuer tm-anf.*/
            i = 0;                      /* zaehler ruecksetzen            */
         } else {                       /* zyklusende oder alte identitaet*/
            inh = inhanf2 + i;          /* nimm naechste inh. elt         */
            i = i + 1;                  /* zaehler erhoehen               */
         }
      }
   } while (!((inhanf2 >= (*inhend2)) || (inh > (*inhend2))));
      /********************************************************************/
      /* falls die neue abbildung ungleich der alten ist, dann stehen     */
      /* die elemente ab inhend2+1 bis imerkend leider in falscher        */
      /* reihenfolge und muessen umgedreht werden                         */
      /********************************************************************/
   if ((*inhend2) < imerkend) {         /* falls neue identifikation      */
                                        /* ungleich der alten             */
      i = (*inhend2) + 1;               /* tausche die elt'e von inhend   */
      j = imerkend;                     /* bis tm-ende aus                */
      while ((i < j)) {
         eltausch(i, j, imerkanf, l_lokstrukt1);
         i = i + 1;
         j = j - 1;
      }                                 /* die zu kopierenden elt'e stehen*/
      (*inhend2) = inhanf2 - 1;         /* ab inhend2, sollen aber ab     */
   }                                    /* inhend2-1 stehen               */
}

 void
#ifdef __STDC__
schnitt(integer deranf3, integer derend3, integer inhanf3, integer *inhend3)
                                      
                     
#else /* ! __STDC__ */
schnitt(deranf3, derend3, inhanf3, inhend3)
   integer  deranf3, derend3, inhanf3;
   integer  *inhend3;
#endif /* ! __STDC__ */
/********************************************************************/
/* Ueberprueft, ob alle in der inhereted teilmenge auftretenden     */
/* attpos (berechnungsregeln) in der derived tm vorhanden sind.     */
/* Alle, in der der. tm nicht auftretenden attpos, werden in der    */
/* inh. tm ans ende gestellt und das tm-ende um 1 erniedrigt.       */
/*------------------------------------------------------------------*/
/* eingangsparameter : deranf3,derend3,inhanf3,inhend3 anfang und   */
/*                            ende der inh./der. teilmenge          */
/* wird aufgerufen von : loktrans                                   */
/* ruft auf : eltausch                                              */
/********************************************************************/
{
   lokdat   lok2;
   integer  derlauf, imerkanf;

   LDCOPY((*l_lokstrukt1), lok2);       /*  lok2 = *l_lokstrukt1;         */
   imerkanf = inhanf3;
   while ((inhanf3 <= (*inhend3))) {    /* bis ende                       */
      derlauf = deranf3;                /* laufvariable besetzen          */
      while ((lok2[derlauf - 1].attpos 
             != (*l_lokstrukt1)[inhanf3 - 1].attpos) 
             && (derlauf < derend3)     /* solange attpos nicht gefunden  */
            )                           /* und nicht am ende              */
         derlauf = derlauf + 1;
      if ((lok2[derlauf - 1].attpos 
          == (*l_lokstrukt1)[inhanf3 - 1].attpos)
         ) {                            /* falls gefunden                 */
         lok2[derlauf - 1].attpos = (Attrpos)NIL;
         inhanf3 = inhanf3 + 1;         /* tm-anfang um 1 erhoehen        */
      } else {
         eltausch((*inhend3), inhanf3, imerkanf, l_lokstrukt1);
                                        /* elt an tm-ende                 */
         (*inhend3) = (*inhend3) - 1;   /* inh. tm-ende erniedrigen       */
      }
   }
}

 void
#ifdef __STDC__
tmvergleich(integer deranf1,
            integer inhanf1,
            integer *derend1,
            integer *inhend1)
                             
                               
#else /* ! __STDC__ */
tmvergleich(deranf1, inhanf1, derend1, inhend1)
   integer  deranf1, inhanf1;
   integer  *derend1, *inhend1;
#endif /* ! __STDC__ */
/********************************************************************/
/* Ueberprueft, ob die zu berechnenden inh. attribute einer         */
/* teilmenge aus kopien der der. attribute der zu vergleichenden    */
/* teilmenge hervorgehen, d. h. ob die attpos (berechnungsregeln)   */
/* der inhereted tm in der derived tm vorkommen.                    */
/* Ggf. werden die teilmengen umgeordnet                            */
/*------------------------------------------------------------------*/
/* eingangsparameter : deranf1,inhanf1 index des der/inh tm-anfang  */
/*                     derend1,inhend1 index des der/inh tm-ende    */
/* wird aufgerufen von :  loktrans                                  */
/* ruft auf :  eltausch                                             */
/********************************************************************/
{
   integer  lauf;
   boolean  tworest;

   integer  *ptanfgross, *ptanfklein, *ptendgross, *ptendklein;

   tworest = false;                     /* true, falls 2 rest-tm    */
   if ( ((*inhend1) - inhanf1 + 1) >=   /* inh.tm >= der. tm ?      */ 
        ((*derend1) - deranf1 + 1)){
      ptanfgross = &inhanf1;
      ptendgross = inhend1;
      ptanfklein = &deranf1;
      ptendklein = derend1;
   } else {
      ptanfgross = &deranf1;
      ptendgross = derend1;
      ptanfklein = &inhanf1;
      ptendklein = inhend1;
   }

   while ((*ptanfklein <= *ptendklein) && !tworest) {
                 /* kleinere tm noch nicht am ende und keine 2 rest-tm */
      lauf = *ptanfgross;                /* tm-ende kopieren               */
      while (((*l_lokstrukt1)[lauf - 1].attpos /* derived attr bis   */
             != (*l_lokstrukt1)[(*ptendklein) - 1].attpos) /* am anfang   */
             && (lauf != *ptendgross)
            )
         lauf = lauf + 1;
      if ((*l_lokstrukt1)[lauf - 1].attpos 
          == (*l_lokstrukt1)[(*ptendklein) - 1].attpos
         ) {                         /* falls attr gefunden, tausche   */
         eltausch(lauf, *ptendgross, *ptanfgross, l_lokstrukt1);
         *derend1 = (*derend1) - 1;/* tm-ende um 1 erniedrigen       */
         *inhend1 = (*inhend1) - 1;
      } else
         tworest = true;             /* sonst 2 rest-tm                */
   }
}

 void
#ifdef __STDC__
loktrans(lok *lokstrukt1,
         ptcopy *copyinfo,
         boolean *first,
         integer derend,
         integer inhend,
         Product aktprod,
         Prodpos aktpropos)
                       
                      
                   
                           
                     
                       
#else /* ! __STDC__ */
loktrans(lokstrukt1, copyinfo, first, derend, inhend, aktprod, aktpropos)
   lokdat   lokstrukt1;
   ptcopy   *copyinfo;
   boolean  *first;
   integer  derend, inhend;
   Product   aktprod;
   Prodpos   aktpropos;
#endif /* ! __STDC__ */
/********************************************************************/
/* Bearbeitet die lokaldatenstruktur zu einer produktions-position  */
/* Untersucht ob die zu behandelnden teilmengen schon identifiziert */
/* sind und ob die behandelten teilmengen neu eingeteilt und        */
/* identifiziert werden muessen, oder ob ein copysymbol eingefuehrt */
/* werden muss.                                                     */
/* ( nur, falls die prodpos schon zum 2.mal bearbeitet wird,        */
/*   ansonsten wird die bearbeitung abgebrochen ).                  */
/*------------------------------------------------------------------*/
/* wird aufgerufen von :  maintrans                                 */
/*------------------------------------------------------------------*/
/* enthaelt aufrufe der prozeduren:  - eltausch                     */
/*                                   - identtm                      */
/*                                   - neutm                        */
/* enthaelt aufrufe der funktionen:  - isrek                        */
/*------------------------------------------------------------------*/
/* enthaelt die unterprozeduren:  - rek                             */
/*                                - copyeintrag                     */
/*                                - schnitt                         */
/*                                - tmvergleich                     */
/* enthaelt die funktionen :      - suchmax                         */
/*                                - attpossuch                      */
/*------------------------------------------------------------------*/
/* eingangsparameter : lokstrukt1      aktuelle lokaldatenstruktur  */
/*                     copyinfo        information ueber copysymbol */
/*                     first           = true, falls prodpos zum    */
/*                                     1.mal in bearbeitung         */
/*                     derend ,inhend  index des der/inh tm-endes   */
/*                     aktprod         aktuelle produktion          */
/*                     aktprodpos      aktuelle produktionsposition */
/********************************************************************/
{
   integer  copyanz, inhanf, imerkend, dmerkend;

   Ll_aktpropos = aktpropos;
   l_aktprod   = aktprod;
   l_derend    = derend;
   l_first     = first;
   l_copyinfo  = copyinfo;
   l_lokstrukt1 = (lokdat *)lokstrukt1;

   LDCOPY((*l_lokstrukt1), Ll_lokstrukt2);/* Ll_lokstrukt2 = *l_lokstrukt1; */        /* lokdat kopieren           */
   l_length = inhend;                   /* laenge der lokdat              */
   while ((inhend >= beranfang)) {      /* mind. 1 inh. vorhanden         */
      if (l_derend < 1) {               /* kein derived                   */
         copyanz = inhend - beranfang + 1;
         inhend = beranfang - 1;       
         copyeintrag(inhend, copyanz);
         l_derend = beranfang - 1;/* wieder von vorn                */
         inhend = l_length;       /* den nicht kopierten rest       */
      }
      while ((inhend >= beranfang) && (l_derend >= 1)) {
         dmerkend = l_derend;     /* deranf und derend merken       */
         imerkend = inhend;
         l_deranf = l_derend;
         inhanf = inhend;
         while ((*l_lokstrukt1)[l_deranf - 1].index == 0)
                                        /* berechnung des inh. tm-anfang  */
            l_deranf = l_deranf - 1;
         while ((*l_lokstrukt1)[inhanf - 1].index == 0)
                                        /* berechnung des derived tm-anf. */
            inhanf = inhanf - 1;
         if (isrek(l_deranf, inhanf, *l_lokstrukt1)) {
                                        /* schon identifiziert            */
            schnitt(l_deranf, l_derend, inhanf, &inhend);
                                     /* die zu kopierenden elt'e ans ende */
            if (imerkend == inhend)  
               rek(l_deranf, l_derend, inhanf, &inhend);
                             /* total rekursiv, dann rekursionsbehandlung */
            if (imerkend != inhend) {/* falls nicht total rekursiv        */
               copyanz = imerkend - inhend; /* oder nicht alte identif.   */
               copyeintrag(inhend, copyanz);
               l_derend = beranfang - 1;
               inhend = l_length;
            } else {
               inhend = inhanf - 1;
               l_derend = l_deranf - 1;
            }
         } else {
            tmvergleich(l_deranf, inhanf, &l_derend, &inhend);
                                        /* vergleiche die 2 letzten tm    */
            if ((l_deranf <= l_derend) && (inhanf <= inhend)) {
                                        /* 2 rest-tm                      */
               inhend = imerkend;
               schnitt(l_deranf, dmerkend, inhanf, &inhend);
                                        /* zu kopierende elt ans ende     */
               copyanz = imerkend - inhend;
               copyeintrag(inhend, copyanz);
               l_derend = beranfang - 1;
               inhend = l_length;
            } else {
               if ((l_deranf > l_derend) && (inhanf <= inhend)) {
                                        /* 1 inh. rest-tm                 */
                  neutm(inhanf, inhend + 1, l_lokstrukt1);
                  identtm(inhend + 1, l_deranf, l_lokstrukt1);
                                        /* tm-neueinteilung und identif.  */
               }
               if ((l_deranf <= l_derend) && (inhanf > inhend)) {
                                        /* 1 derived rest-tm              */
                  neutm(l_deranf, l_derend + 1, l_lokstrukt1);
                  identtm(l_derend + 1, inhanf, l_lokstrukt1);
                                        /* tm-neueinteilung und identif.  */
               }                        /* falls kein rest-tm             */
               if ((l_deranf > l_derend) && (inhanf > inhend))
                  identtm(l_deranf, inhanf, l_lokstrukt1);
                                        /* tm-identif.                    */
            }
         }
      }
   }
}

#ifdef __STDC__
void maintrans(void);
#else /* ! __STDC__ */
void maintrans();
#endif /* ! __STDC__ */

 void
#ifdef __STDC__
merkeintrag(ptmerkepos *merk, Product pro, Prodpos pos)
                     
                 
                 
#else /* ! __STDC__ */
merkeintrag(merk, pro, pos)
   ptmerkepos  *merk;
   Product   pro;
   Prodpos   pos;
#endif /* ! __STDC__ */
/********************************************************************/
/* Traegt die produktionspositionen, die gemerkt werden muessen in  */
/* eine liste ein.                                                  */
/*------------------------------------------------------------------*/
/* eingangsvariable : merk   pointer auf liste der gemerkten prodpos*/
/* wird aufgerufen von : maintrans                                  */
/********************************************************************/
{
   ptmerkepos  merk1, neumerk;

   neumerk = (struct merkepos *)getMem((unsigned)(sizeof(*neumerk)));
   neumerk->mpos = pos;                 /* zu merkende prodpos eintr.     */
   neumerk->mpro = pro;                 /* zu merk. produktion eintr.     */
   neumerk->nachfpos = (struct merkepos *)NIL; /* listenende              */
   if ((*merk) == (struct merkepos *)NIL)
      (*merk) = neumerk;
   else {
      merk1 = (*merk);                  /* liste kopieren                 */
      while (merk1->nachfpos != (struct merkepos *)NIL)
         merk1 = merk1->nachfpos;
      merk1->nachfpos = neumerk;        /* neumerk wird listenende        */
   }
}

 void
#ifdef __STDC__
maintrans(void)
#else /* ! __STDC__ */
maintrans()
#endif /* ! __STDC__ */
/********************************************************************/
/* Steuert den ablauf der transformation :                          */
/* Als erstes werden die ersten produktionspositionen der rechten   */
/* seite bearbeitet. Falls ein copysymbol eingefuehrt werden muss,  */
/* wird die bearbeitung abgebrochen, die produktionsposition gemerkt*/
/* und mit der bearbeitung der naechsten ersten prodpos fortgesetzt.*/
/* Dann werden dann die gemerkten ersten prodpos abgearbeitet.      */
/* Nun werden der reihe nach die produktionspositionen der einzelnen*/
/* produktionen von links nach rechts soweit abgearbeitet bis ein   */
/* copysymbol eingefuehrt eingefuehrt werden muss.                  */
/* Diese positionen werden wieder gemerkt und die bearbeitung mit   */
/* naechsten produktion fortgesetzt. Erst wenn alle produktionen    */
/* ohne copysymbol ganz und alle mit copysymbol bis zur positionen  */
/* vor dem copysymbol transformiert sind, werden die copy-symbole   */
/* eingefuehrt und die restlichen positionen von links nach rechts  */
/* bis zum naechsten copysymbol abgearbeitet.                       */
/* Dies wird solange durchgefuehrt bis alle positionen transfor-    */
/* miert sind.                                                      */
/*------------------------------------------------------------------*/
/* wird aufgerufen von : AGuser                                     */
/* ruft auf : initzug, einlesen, globtolok, loktrans, loktoglob     */
/********************************************************************/
{
   boolean  firsttime;                  /* = true, falls propos zum 1.mal */
                                        /*         in bearbeitung         */
   Vocabel aktsym;                      /* aktuelles symbol               */
   Product   aktprodukt;                /* aktuell bearbeitete produktion */
   Prodpos   aktprodpos;                /* aktuell bearbeitete prodpos    */
   ptmerkepos  cpos, cpos1;             /* gemerkte positionen            */
	ptmerkepos hcpos;                    /* hilfszeiger fuer free      */

   int zaehler;                         /* Namen der Aux-Copy's >= zaehler*/
   ptcopy pcp;                          /* Zeiger auf eine Copy-Info      */

   globstrukt = (struct globdat *)NIL;
   einlesen(&globstrukt);          /* einlesen der globaldatenstruktur */
   copyinfo = (struct copy *)NIL;    /* variablenvorbesetzung          */
   copyname = 1;
   forcopy = false;
   foroutput = false;
   mregel = (struct merkeregel *)NIL;
   cpos = (struct merkepos *)NIL;
   nofehler = true;

       /****************************************************************/
       /* Nun werden alle ersten prodpos der rechten seite abgearbeitet*/
       /****************************************************************/

   aktsym = FirstSym();              /* 1.symbol laden                 */
   while (aktsym != (Vocabel)NIL) {  /* noch kein symbol vorhanden     */
      aktprodukt = FirstProd(aktsym);/* 1.produktion des symbols       */
      while (aktprodukt != (Product)NIL) { /* noch produktionen da     */
         aktprodpos = NextPPos(FirstPPos(aktprodukt));
                                     /* 1.pos rechte seite             */
         firsttime = true;           /* wird zum 1.mal bearbeitet      */
         if ((aktprodpos != (Prodpos)NIL) && firsttime) {
                                     /* prodpos vorhanden und zum      */
                                     /* ersten mal bearbeitet          */
            globtolok(aktprodukt, aktprodpos, TRUE); /* lokalstr. gen.       */

            if (loklength >= beranfang) { /* inh. attr. vorhanden      */
               loktrans(lokstrukt, &copyinfo, &firsttime, beranfang - 1,
                        loklength, aktprodukt, aktprodpos);
               if (firsttime) {      /* kein copysymbol eingefuehrt,   */
                  loktoglob();       /* dann .. und zurueckschreiben   */
               } else                /* sonst prodpos merken           */
                  merkeintrag(&cpos, aktprodukt, aktprodpos);
            }
         }
         aktprodukt = NextProd(aktprodukt); /* naechste produktion     */
      }
      aktsym = NextSym(aktsym);
   }

       /****************************************************************/
       /* Nun werden die gemerkten ersten prodpos bearbeitet           */
       /* ( copy-symbole werden eingefuehrt )                          */
       /****************************************************************/

   firsttime = false;                /* wird zum 2.mal bearbeitet      */
   while (cpos != (struct merkepos *)NIL) { /* gemerkte 1.prodpos      */
      globtolok(cpos->mpro, cpos->mpos, TRUE); /* lokstrukt gen.             */
      loktrans(lokstrukt, &copyinfo, &firsttime, 
               beranfang - 1, loklength, cpos->mpro, cpos->mpos);
      loktoglob();
		hcpos = cpos;
      cpos = cpos->nachfpos;         /* naechste erste prodpos         */
		free(hcpos);
   }

       /****************************************************************/
       /* Nun werden die restlichen prodpos der produktionen von       */
       /* links nach rechts bearbeitet                                 */
       /****************************************************************/

   cpos = (struct merkepos *)NIL;    /* variablenvorbesetzung          */
   cpos1 = (struct merkepos *)NIL;
   aktsym = FirstSym();              /* erstes symbol laden            */
   while (aktsym != (Vocabel)NIL) {  /* noch symbol vorhanden          */
      aktprodukt = FirstProd(aktsym);/* 1.produktion des symbols       */
      while (aktprodukt != (Product)NIL) { /* noch produktionen da     */
         aktprodpos = NextPPos(FirstPPos(aktprodukt));
                                     /* 1. pos. rechte seite           */
         if (aktprodpos != (Prodpos)NIL) {
            aktprodpos = NextPPos(aktprodpos);
            firsttime = true;        /* wird zum ersten mal bearbeitet */
            while ((aktprodpos != (Prodpos)NIL) && firsttime) {
                                     /* prodpos vorhanden und wird zum */
                                     /* ersten mal bearbeitet          */
               globtolok(aktprodukt, aktprodpos, TRUE);
               if (loklength >= beranfang) { /* inh. attr da           */
                  loktrans(lokstrukt, &copyinfo, &firsttime, 
                           beranfang - 1, loklength, aktprodukt, aktprodpos);
                  if (firsttime) {
                     loktoglob();    /* und rueckschreiben             */
                  } else             /* sonst prodpos merken           */
                     merkeintrag(&cpos, aktprodukt, aktprodpos);
               }
               aktprodpos = NextPPos(aktprodpos);
            }
         }
         aktprodukt = NextProd(aktprodukt);
      }
      aktsym = NextSym(aktsym);
   }

 /****************************************************************/
 /* Und wieder die gemerkten prodpos                             */
 /* ( copy-symbole werden eingefuehrt )                          */
 /****************************************************************/

   while (cpos != (struct merkepos *)NIL) {
      while (cpos != (struct merkepos *)NIL) { /* gemerkte prodpos     */
         firsttime = false;          /* zum 2.mal bearbeitet           */
         globtolok(cpos->mpro, cpos->mpos, TRUE);
         loktrans(lokstrukt, &copyinfo, &firsttime, beranfang - 1,
                  loklength, cpos->mpro, cpos->mpos);
         loktoglob();

         /********************************************************/
         /* Und nun die prodpos nach dem copy-symbol von links   */
         /* nach rechts.                                         */
         /********************************************************/

         firsttime = true;
         aktprodpos = NextPPos(cpos->mpos);
         while ((aktprodpos != (Prodpos)NIL) && firsttime) {
            globtolok(cpos->mpro, aktprodpos, TRUE);

            if (loklength >= beranfang) { /* inh. attr vorhanden       */
               loktrans(lokstrukt, &copyinfo, &firsttime,
                        beranfang - 1, loklength, cpos->mpro,
                        aktprodpos);
               if (firsttime) {
                  loktoglob();
               } else
                  merkeintrag(&cpos1, cpos->mpro, aktprodpos);
            }                        /* in neue liste eintragen        */
            aktprodpos = NextPPos(aktprodpos);
         }
			hcpos = cpos;
         cpos = cpos->nachfpos;      /* naechste gemerkte prodpos      */
			free(hcpos);
      }
      cpos = cpos1;                  /* mit neuer liste vorn von vorn  */
      cpos1 = (struct merkepos *)NIL;/* neu initialisieren             */
   }

   /********************************************************************/
   /* Die eigentliche Transformation ist damit beendet.                */
   /* Jetzt wollen wir noch die Anzahl der Copy-Symbole reduzieren,    */
   /* indem funktional gleiche Produktionen identifiziert, d.h         */
   /* denselben Namen bekommen                                         */
   /********************************************************************/


   /**********************************************************************/
	/* zum Kennzeichnen der CP, in denen Auxiliary-Berechnungen stattfinden, 
	      bekommen sie einen Namen >= copyname, damit sie in copygen nicht
	      identifiziert werden koennen. 
   */
   /**********************************************************************/
  
   zaehler = copyname;

   forcopy = TRUE;
   foroutput = FALSE;

	aktsym=FirstSym();
	while (aktsym != (Vocabel)NIL){
		aktprodukt = FirstProd(aktsym);
		while (aktprodukt != ((Product)NIL)) {
			if (FirstAuxPos(aktprodukt) != (Attrpos)NIL){ /* Eine Aux-Produktion */
				aktprodpos = NextPPos(FirstPPos(aktprodukt));
				while (aktprodpos != (Prodpos)NIL){
					if ((pcp = copyproof(aktprodukt, aktprodpos)) != (ptcopy)NIL){
						if (cp_test_aux(pcp)){       /* Testet auf Aux-Verwendung.*/
							pcp->name = zaehler++;    /* Nicht mehr identifizierbar*/
							                          /* machen                    */
						}
					}
					aktprodpos = NextPPos(aktprodpos);
				}
			}
			aktprodukt = NextProd(aktprodukt);
		}
		aktsym = NextSym(aktsym);
	}

   auxcopyanz = zaehler - copyname;  /* Anzahl der Aux-Copy's */

   forcopy = FALSE;
   foroutput = FALSE;

	printf("          Identifizieren von Copysymbolen\n");
	copygen(zaehler);            /* identifiz. der copy-symbole    */

	ausgabe(); /* Erledigt die gesamte Ausgabe */

}


