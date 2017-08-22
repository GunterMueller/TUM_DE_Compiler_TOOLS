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


/* ************************************************************************ */
/* pstokenP.h: private Tokendefinitionen fuer den parametrisierten Scanner */
/* erstellt: 10.01.91, Ulrich Vollath                                       */
/* ************************************************************************ */

#ifndef PSTOKENP_H
#define PSTOKENP_H
/* ------------------------------------------------- */
/* Zugriff auf die privaten Teile eines Tokens       */
/* ------------------------------------------------- */
#define RPOS(tok)     (*tok).decinf
#define QUELL_ZL(ort) (*ort).zeile
#define QUELL_SP(ort) (*ort).spalte
#define QUELL_FN(ort) (*ort).fname
#endif
