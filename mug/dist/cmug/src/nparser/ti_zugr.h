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
/* ti_zugr.h :                                                            */
/* LR(k)-Parser-Tabellen-Interpreter                                      */
/* Deklarationen Zugriffe auf die Tabelle                                 */
/* ---------------------------------------------------------------------- */
/* Aenderung :12.08.89, Zugriffsfunktionen getTab?()                     */
/* Aenderung : 23.07.89, unbedingt()                                      */
/* erstellt  : 09.07.89                                                   */
/* ********************************************************************** */

#ifndef TI_ZUGR_H
#define TI_ZUGR_H

#define GETTAB(tab,len,ind) getTab((char *)(tab),(Typlen)(len),(Uint32)(ind))
#define DECTERM(t) decTerm((Term)(t))
#define DECNONT(n) decNont((Nont)(n))

/* ===================================================================== */
/* Zugriff auf 8-Bit-Tabelle                                             */
/* ===================================================================== */
ZFN_DEKL(getTab1);

/* ===================================================================== */
/* Zugriff auf 16-Bit-Tabelle                                            */
/* ===================================================================== */
ZFN_DEKL(getTab2);

/* ===================================================================== */
/* Zugriff auf 32-Bit-Tabelle                                            */
/* ===================================================================== */
ZFN_DEKL(getTab4);

/* ===================================================================== */
/* liefert passende Zugriffsfunktion ab                                  */
/* ===================================================================== */
#ifdef __STDC__
ZFN_TYPE(getTabfunkt(Typlen) );
char *getTabfunktname(ZFN_TYPE(fkt) );
Typlen getTabfunktlen(ZFN_TYPE(fkt) );
#else
ZFN_TYPE(getTabfunkt() );
char *getTabfunktname();
Typlen getTabfunktlen();
#endif

/* ============================================================= */
/* Berechnung der Zugriffsmasken fuer die Tabelle                */
/* ============================================================= */
#ifdef __STDC__
void zugrMask(Ueb *uebmsk,Ueb *infmsk,Ueb *shiftueb,
              Ueb *redueb,Ueb *spontueb);
#else
void zugrMask();
#endif

/* ===================================================================== */
/* berechnet den shift-count fuer Uebergangs-Zugriffe                    */
/* ===================================================================== */
#ifdef __STDC__
int getUebshift(Typlen);
#else
int getUebshift();
#endif

/* ===================================================================== */
/* Zugriff auf eine der Tabellen                                         */
/* ===================================================================== */
#ifdef __STDC__
Tabindex  getTab(Tabelle,Typlen,Tabindex);
#else
Tabindex  getTab();
#endif
/* ===================================================================== */
/* Dekodieren eines Terminalzeichens                                     */
/* ===================================================================== */
#ifdef __STDC__
char *decTerm(Term);
#else
char *decTerm();
#endif
/* ===================================================================== */
/* Dekodieren eines Nonterminalzeichens                                  */
/* ===================================================================== */
#ifdef __STDC__
char *decNont(Nont);
#else
char *decNont();
#endif

/* ===================================================================== */
/* terminalen Uebergang bestimmen                                        */
/* Rueckgabe : gefundenen Uebergang, 0 falls kein Uebergang moeglich     */
/* ===================================================================== */
#ifdef __STDC__
Ueb getTueb(Zust,Term);
#else
Ueb getTueb();
#endif
/* ===================================================================== */
/* nonterminalen Uebergang bestimmen                                     */
/* Rueckgabe : gefundenen Uebergang, 0 falls kein Uebergang moeglich     */
/* ===================================================================== */
#ifdef __STDC__
Ueb getNueb(Zust,Nont);
#else
Ueb getNueb();
#endif

/* ============================================================= */
/* stellt fest, ob im Zustand zust nur ein Terminalzeichen term  */
/* gelesen werden kann                                           */
/* dann Rueckgabe TRUE                                           */
/* ============================================================= */
#ifdef __STDC__
int unbedingt(Zust,Term *,Ueb *);
#else
int unbedingt();
#endif

#endif /* TI_ZUGR_H */
