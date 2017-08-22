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


/* ********************************************************************** */
/* ti_defs.h :                                                            */
/* LR(k)-Parser-Tabellen-Interpreter                                      */
/* globale Deklarationen                                                  */
/* ---------------------------------------------------------------------- */
/* Aenderung : 13.08.89, vollstaediges 'typeing'                          */
/* Aenderung :10.08.89, Unterstuetzung von Zugriffsfunktionen            */
/* Aenderung : 22.07.89, FOR_EACHTERMUEB ergaenzt                         */
/* erstellt  : 08.07.89                                                   */
/* ********************************************************************** */

#ifndef TI_DEFS_H
#define TI_DEFS_H

#include "site.h"
#ifdef KNOWN_SIZES
#include "ti_sizes.h"
#endif

typedef char   Tabel;       /* Element in einer Tabelle                     */
typedef Tabel  *Tabelle;    /* beliebige Tabelle                            */  
typedef Uint32 Tabindex;    /* Index fuer Tabellenzugriff                   */

typedef Uint8  Typlen;      /* Laenge eines Typen in Byte (1,2, oder 4)     */
typedef Uint32 Term;        /* Typ fuer Terminalzeichen                     */
typedef Uint32 Nont;        /* Typ fuer Nonterminalzeichen                  */
typedef Uint32 Zust;        /* Typ fuer Zustaende                           */
typedef Uint32 Prod;        /* Typ fuer Produktionen                        */
typedef Uint32 Ueb;         /* Typ fuer Uebergaenge                         */
typedef Uint32 Tind;        /* Index in Tabellen der terminalen Uebergaenge */
typedef Uint32 Nind;        /* Index in Tabellen der nonterm. Uebergaenge   */
typedef Uint32 Plen;        /* Laenge von Produktionen                      */
typedef Uint32 Tnam;        /* Index eines Terminalsymbolnamens             */
typedef Uint32 Nnam;        /* Index eines Nonterminalsymbolnamens          */

/* ----------------------------------------------------------- */
/* Typ fuer Zugriffsfunktionen                                 */
/* eigentlich                                                  */
/* typedef Tabindex (*) (Tabelle, Tabindex) Zugrfunkt;         */
/* ----------------------------------------------------------- */
#ifdef __STDC__
#define ZFN_TYPE(name)  Tabindex (* name) (Tabelle, Tabindex)
#define ZFN_DEKL(name)  Tabindex  name (Tabelle, Tabindex)
#else
#define ZFN_TYPE(name)  Tabindex (* name) ()
#define ZFN_DEKL(name)  Tabindex  name ()
#endif

/* Anzahl der Bits, in denen die Uebergangsart kodiert ist */
#define UEBARTBITS   2
#define UEBARTMSK    3L
#define UEBARTSHIFT  2L
#define UEBARTRED    3L
#define UEBARTSPONT  1L

typedef struct
     { 
      /* --------------------------------------- */
      /* Einzel-Tabellen der Uebergangstabelle   */
      /* --------------------------------------- */
      Tabelle   tuebsyms;   /* Terminaltabelle :Symbole        Term[ttabmax] */
      Tabelle   tuebs;      /* Terminaltabelle : Uebergaenge    Ueb [ttabmax] */
      Tabelle   tdefs;      /* Default-Terminaluebergaenge      Ueb [zmax]    */   
      Tabelle   tinds;      /* Indices der Terminaluebergaenge  Tind[2*zmax]  */
      Tabelle   nuebzust;   /* Nontermtabelle : Ausgangszustand Zust[ntabmax] */
      Tabelle   nuebs;      /* Nontermtabelle : Uebergang       Ueb [ntabmax] */
      Tabelle   ndefs;      /* Default-Nontermuebergaenge       Ueb [nmax]    */
      Tabelle   ninds;      /* Indices der Nontermuebergaenge   Nind[2*nmax]  */
      Tabelle   prlhs;      /* linke Seiten der Produktionen    Nont[pmax]    */
      Tabelle   prlen;      /* Laenge der Produktionen          Plen[pmax]    */
      Tabelle   tninds;     /* Indices Namen Terminalsymbole    Tnam[tmax]    */
      Tabelle   tnames;     /* Tabelle der Terminalnamen        char[tnmax]   */
      Tabelle   nninds;     /* Indices Namen Nonterminale       Nnam[nmax]    */
      Tabelle   nnames;     /* Tabelle der Nonterminalnamen     char[nnmax]   */
      /* --------------------------------------- */
      /* Zugriffe auf die Tabellen               */ 
      /* --------------------------------------- */
      ZFN_TYPE(term_zfn);   /* Zugriff auf Tabellen                 Term[..]  */
      ZFN_TYPE(nont_zfn);   /* Zugriff auf Tabellen                 Nont[..]  */
      ZFN_TYPE(zust_zfn);   /* Zugriff auf Tabellen                 Zust[..]  */
      ZFN_TYPE(prod_zfn);   /* Zugriff auf Tabellen                 Prod[..]  */
      ZFN_TYPE(ueb_zfn);    /* Zugriff auf Tabellen                 Ueb [..]  */
      ZFN_TYPE(tind_zfn);   /* Zugriff auf Terminalindextabellen    Tind[..]  */
      ZFN_TYPE(nind_zfn);   /* Zugriff auf Nonterminalidextabellen  Nind[..]  */
      ZFN_TYPE(plen_zfn);   /* Zugriff auf Produktionslaengen       Plen[..]  */
      ZFN_TYPE(tnam_zfn);   /* Zugriff auf Namen Terminalzeichen    Tnam[..]  */
      ZFN_TYPE(nnam_zfn);   /* Zugriff auf Namen Nonterminalsymbole Nnam[..]  */
      /* --------------------------------------- */
      /* Groessen der Tabellen                   */
      /* --------------------------------------- */
      Tabindex  ttabmax;    /* maximaler Index in Terminaltabellen            */
      Tabindex  ntabmax;    /* maximaler Index in Nonterminaltabellen         */
      Tabindex  tnmax;      /* groesster Index in Terminalnamentabelle        */
      Tabindex  nnmax;      /* groesster Index in Nonterminalnamentabelle     */
      Term      tmax;       /* groesstes verwendetes Terminalsymbol           */
      Nont      nmax;       /* groesstes verwendetes Nonterminalsymbol        */
      Zust      zmax;       /* groesster verwendeter Zustand                  */
      Prod      pmax;       /* groesste verwendete Produktion                 */
      int       ushift;     /* shift-Count fuer Zugriffe auf Uebergaenge      */
     } Ptab;

/* =========================================================== */
/* Zugriffsmakros                                              */
/* des erste Argument tab ist die jeweilige Uebergangstabelle  */
/* =========================================================== */
#ifdef TERM_IS_8BIT
#define TERMUEBSYM(tab,i) ((Tabindex)((Uint8 *)(tab).tuebsyms)[i])
#else
#ifdef TERM_IS_16BIT
#define TERMUEBSYM(tab,i) ((Tabindex)((Uint16 *)(tab).tuebsyms)[i])
#else
#ifdef TERM_IS_32BIT
#define TERMUEBSYM(tab,i) ((Tabindex)((Uint32 *)(tab).tuebsyms)[i])
#else
#define TERMUEBSYM(tab,i) (tab).term_zfn((tab).tuebsyms,(Tabindex)(i))
#endif
#endif
#endif

#ifdef UEB_IS_8BIT
#define TERMUEB(tab,i) ((Tabindex)((Uint8 *)(tab).tuebs)[i])
#define TDEF(tab,z) ((Tabindex)((Uint8 *)(tab).tdefs)[z])
#define NUEB(tab,i) ((Tabindex)((Uint8 *)(tab).nuebs)[i])
#define NDEF(tab,n) ((Tabindex)((Uint8 *)(tab).ndefs)[n])
#else
#ifdef UEB_IS_16BIT
#define TERMUEB(tab,i) ((Tabindex)((Uint16 *)(tab).tuebs)[i])
#define TDEF(tab,z) ((Tabindex)((Uint16 *)(tab).tdefs)[z])
#define NUEB(tab,i) ((Tabindex)((Uint16 *)(tab).nuebs)[i])
#define NDEF(tab,n) ((Tabindex)((Uint16 *)(tab).ndefs)[n])
#else
#ifdef UEB_IS_32BIT
#define TERMUEB(tab,i) ((Tabindex)((Uint32 *)(tab).tuebs)[i])
#define TDEF(tab,z) ((Tabindex)((Uint32 *)(tab).tdefs)[z])
#define NUEB(tab,i) ((Tabindex)((Uint32 *)(tab).nuebs)[i])
#define NDEF(tab,n) ((Tabindex)((Uint32 *)(tab).ndefs)[n])
#else
#define TERMUEB(tab,i)    (tab).ueb_zfn((tab).tuebs,(Tabindex)(i))
#define TDEF(tab,z)       (tab).ueb_zfn((tab).tdefs,(Tabindex)(z))
#define NUEB(tab,i)       (tab).ueb_zfn((tab).nuebs,(Tabindex)(i))
#define NDEF(tab,n)       (tab).ueb_zfn((tab).ndefs,(Tabindex)(n))
#endif
#endif
#endif


#ifdef TIND_IS_8BIT
#define TINDVON(tab,z) ((Tabindex)((Uint8 *)(tab).tinds)\
				  [(Tabindex)((Tabindex)(z)<<1)])
#define TINDBIS(tab,z) ((Tabindex)((Uint8 *)(tab).tinds)\
				  [(Tabindex)(1+(Tabindex)(z)<<1)])
#else
#ifdef TIND_IS_16BIT
#define TINDVON(tab,z) ((Tabindex)((Uint16 *)(tab).tinds)\
				  [(Tabindex)((Tabindex)(z)<<1)])
#define TINDBIS(tab,z) ((Tabindex)((Uint16 *)(tab).tinds)\
				  [(Tabindex)(1+(Tabindex)(z)<<1)])
#else
#ifdef TIND_IS_32BIT
#define TINDVON(tab,z) ((Tabindex)((Uint32 *)(tab).tinds)\
				  [(Tabindex)((Tabindex)(z)<<1)])
#define TINDBIS(tab,z) ((Tabindex)((Uint32 *)(tab).tinds)\
				  [(Tabindex)(1+(Tabindex)(z)<<1)])
#else
#define TINDVON(tab,z)    (tab).tind_zfn((tab).tinds,\
                               (Tabindex)((Tabindex)(z)<<1)  )
#define TINDBIS(tab,z)    (tab).tind_zfn((tab).tinds,\
                               (Tabindex)(1+((Tabindex)(z)<<1)) )
#endif
#endif
#endif

#ifdef ZUST_IS_8BIT
#define NUEBZUST(tab,i) ((Tabindex)((Uint8 *)(tab).nuebzust)[(Tabindex)i])
#else
#ifdef ZUST_IS_16BIT
#define NUEBZUST(tab,i) ((Tabindex)((Uint16 *)(tab).nuebzust)[(Tabindex)i])
#else
#ifdef ZUST_IS_32BIT
#define NUEBZUST(tab,i) ((Tabindex)((Uint32 *)(tab).nuebzust)[(Tabindex)i])
#else
#define NUEBZUST(tab,i)   (tab).zust_zfn((tab).nuebzust,(Tabindex)(i))
#endif
#endif
#endif

#ifdef NIND_IS_8BIT
#define NINDVON(tab,n) ((Tabindex)((Uint8 *)(tab).ninds)\
				  [(Tabindex)((Tabindex)(n)<<1)])
#define NINDBIS(tab,n) ((Tabindex)((Uint8 *)(tab).ninds)\
				  [(Tabindex)(1+(Tabindex)(n)<<1)])
#else
#ifdef NIND_IS_16BIT
#define NINDVON(tab,n) ((Tabindex)((Uint16 *)(tab).ninds)\
				  [(Tabindex)((Tabindex)(n)<<1)])
#define NINDBIS(tab,n) ((Tabindex)((Uint16 *)(tab).ninds)\
				  [(Tabindex)(1+(Tabindex)(n)<<1)])
#else
#ifdef NIND_IS_32BIT
#define NINDVON(tab,n) ((Tabindex)((Uint32 *)(tab).ninds)\
				  [(Tabindex)((Tabindex)(n)<<1)])
#define NINDBIS(tab,n) ((Tabindex)((Uint32 *)(tab).ninds)\
				  [(Tabindex)(1+(Tabindex)(n)<<1)])
#else
#define NINDVON(tab,n)    (tab).nind_zfn((tab).ninds,\
                               (Tabindex)((Tabindex)(n)<<1)  )
#define NINDBIS(tab,n)    (tab).nind_zfn((tab).ninds,\
                               (Tabindex)(1+((Tabindex)(n)<<1)) )
#endif
#endif
#endif

#ifdef NONT_IS_8BIT
#define PRLHS(tab,p) ((Tabindex)((Uint8 *)(tab).prlhs)[(Tabindex)(p)])
#else
#ifdef NONT_IS_16BIT
#define PRLHS(tab,p) ((Tabindex)((Uint16 *)(tab).prlhs)[(Tabindex)(p)])
#else
#ifdef NONT_IS_32BIT
#define PRLHS(tab,p) ((Tabindex)((Uint32 *)(tab).prlhs)[(Tabindex)(p)])
#else
#define PRLHS(tab,p)      /*prod?*/(tab).nont_zfn((tab).prlhs,(Tabindex)(p))
#endif
#endif
#endif

#ifdef PLEN_IS_8BIT
#define PRLEN(tab,p) ((Tabindex)((Uint8 *)(tab).prlen)[(Tabindex)(p)])
#else
#ifdef PLEN_IS_16BIT
#define PRLEN(tab,p) ((Tabindex)((Uint16 *)(tab).prlen)[(Tabindex)(p)])
#else
#ifdef PLEN_IS_32BIT
#define PRLEN(tab,p) ((Tabindex)((Uint32 *)(tab).prlen)[(Tabindex)(p)])
#else
#define PRLEN(tab,p)      (tab).plen_zfn((tab).prlen,(Tabindex)(p))
#endif
#endif
#endif

#ifdef TNAM_IS_8BIT
#define TNAM(tab,t) &((tab).tnames[(Tabindex)((Uint8 *)(tab).tninds)\
			[(Tabindex)(t)]])
#else
#ifdef TNAM_IS_16BIT
#define TNAM(tab,t) &((tab).tnames[(Tabindex)((Uint16 *)(tab).tninds)\
			[(Tabindex)(t)]])
#else
#ifdef TNAM_IS_32BIT
#define TNAM(tab,t) &((tab).tnames[(Tabindex)((Uint32 *)(tab).tninds)\
			[(Tabindex)(t)]])
#else
#define TNAM(tab,t)  &((tab).tnames[(tab).tnam_zfn((tab).tninds,(Tabindex)(t))])
#endif
#endif
#endif

#ifdef NNAM_IS_8BIT
#define NNAM(tab,n) &((tab).nnames[(Tabindex)((Uint8 *)(tab).nninds)\
			[(Tabindex)(n)]])
#else
#ifdef NNAM_IS_16BIT
#define NNAM(tab,n) &((tab).nnames[(Tabindex)((Uint16 *)(tab).nninds)\
			[(Tabindex)(n)]])
#else
#ifdef NNAM_IS_32BIT
#define NNAM(tab,n) &((tab).nnames[(Tabindex)((Uint32 *)(tab).nninds)\
			[(Tabindex)(n)]])
#else
#define NNAM(tab,n)  &((tab).nnames[(tab).nnam_zfn((tab).nninds,(Tabindex)(n))])
#endif
#endif
#endif

#define USHIFT(tab)       (tab).ushift

/* ------------------------------------------------------------- */
/* Schleife ueber alle Terminalsymbole der Grammatik             */
/*-------------------------------------------------------------- */
#define FOR_EACHTERM(tab,term) {for (term = 0; term <= (tab).tmax;term++){
#define END_EACHTERM }}

/* ------------------------------------------------------------- */
/* Schleife ueber alle terminalen Uebergaenge aus einem Zustand  */
/* startet einen neuen Anweisungsblock                           */
/*-------------------------------------------------------------- */
#define FOR_EACHTERMUEB(tab,zust,term,ueb) {Tabindex ind,maxind;\
        maxind = TINDBIS(tab,zust);\
        for (ind = TINDVON(tab,zust);ind < maxind; ind++){\
        term = TERMUEBSYM(tab,ind); ueb  = TERMUEB(tab,ind);

/* ------------------------------------------------------------- */
/* Ende der Schleife ueber alle terminalen Uebergaenge           */
/*------------------------------------------------------------- */
#define END_EACHTERMUEB }}

#ifdef DEBUG
#define DBGPRT(args) printf args
#define IFDEBUG(stmts) stmts
#else
#define DBGPRT(args)
#define IFDEBUG(stmts)
#endif
#define ERRPRT(args) printf args

        
#endif /* TI_DEFS_H */
