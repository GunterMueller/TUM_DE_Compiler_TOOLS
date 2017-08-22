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
/* Gramconst.h   :                                                        */
/* LR(k)-Parser-Generator                                                 */
/* Konstanten-Definitionen der Bereiche  fuer die Grammatik               */
/* letzte Aenderung : 28.1.89                                             */
/* erstellt         : 24.1.89                                             */
/* ********************************************************************** */

#ifndef GRAMCONST_H 
#define GRAMCONST_H 

/* ======================================================================== */
/* die folgenden Definitionen sind auf die Verwendung von 16-bit-Strukturen */
/* fuer die jeweiligen Datentypen abgestimmt                                */
/* ======================================================================== */

#define CMINT      (Symb)0      /* kleinstes benutztes Terminalsymbol             */
#define CMAXT      (Symb)32000  /* groesstes benutztes Terminalsymbol             */
#define CMINN      (Symb)-32000 /* kleinstes Nonterminalsymbol                    */
#define CMAXN      (Symb)-1     /* groesstes Nonterminalsymbol                    */
#define CMINH      (Item)0      /* erste Position in der Grammatik                */
#define CMAXH      (Item)32000  /* letzte Position in der Grammatik               */
#define CMINP      (Prod)0      /* erste Produktion                               */
#define CMAXP      (Prod)32000  /* letzte Produktion                              */




#endif /* GRAMCONST_H */

