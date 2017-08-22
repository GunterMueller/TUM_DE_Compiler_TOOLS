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


/* ********************************************* */
/* ps_token.h:                                   */
/* Tokendefinition fuer paramatrisierten Scanner */
/* erstellt  Ulrich Vollath, 10.01.91            */
/* ********************************************* */
#ifndef PS_TOKEN_H
#define PS_TOKEN_H
typedef long Klasscode;               /* Symbolklasse, fuer den Parser */
typedef struct QuellortR {
                long      zeile;      /* Zeile in der Quelldatei       */
                long      spalte;     /* Spalte in der Quelldatei      */
		char      *fname;     /* Name der Quelldatei           */
		} Quellort;

typedef struct TokenR {
                Klasscode kc;         /* Symbolklasse                  */
		long      rcode;      /* Relativcode (semant.Wert)     */
		/* ------------------------------------------- */
                /* private !! subjext to change without notice */
		/* ------------------------------------------- */
		Quellort  ort;        /* Quellortinformation           */
                char      *decinf;    /* Dekoderinformation            */
		char      **semptr;   /* Gummipointer fuer Semantik    */
               } TokenRec,*Token;

#define SYM(tok)    (*(tok)).kc
#define SEMVAL(tok) (*(tok)).rcode
#define SEMPTR(tok) *((*(tok)).semptr)
#define QUELL_ORT(tok) (&((*tok).ort))

#endif /* PS_TOKEN_H */
