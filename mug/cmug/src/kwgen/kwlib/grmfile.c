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

/************************************************************************
*
*                           G R M F I L E . C
*
*  Es wird das File  phaseproj.grm  erzeugt
*
* Letzte Aenderung:  04.06.91  Lahner
************************************************************************/
#include <stdio.h>
#include "zufunc.h"

#define MAXNAMELEN 20
#define MAXTERM 255

static char *srcname = "\0";
static char *Projekt = "\0";


#ifdef __STDC__
void write_PGint(void)
#else /* ! __STDC__ */
void write_PGint()
#endif /* ! __STDC__ */
/* Funktion: Schreibt das File phaseproj.GRM fuer den Parsergenerator.
   Eingabe:  -
   Ausgabe:  -
*/
{
        FILE *ParserOut;
        char fname[MAXNAMELEN];
        Product p;
	Prodpos pp;
	Vocabel aktsym, symbol;
	int anznonterm;
	anznonterm = CardNonterm();

        strcpy(fname, SymString(GetPhasenId()));
        strcat(fname, Projekt);
        strcat(fname, ".grm");
        if ((ParserOut = fopen(fname, "w")) ==NULL)
	 {
	  perror("Eingabe fuer Parsergenerator kann nicht geoeffnet werden");
	  exit(10);
	 }
#ifndef OLDGRMFILE
	 {
	  long zeit;

          zeit=time(0L);
          fprintf(ParserOut,"Eingelesen: %s", ctime(&zeit));
	 }
        fprintf(ParserOut,"81235431\n"); /* Dateikennung */
        fprintf(ParserOut,"1 %1d 256 %1d \n", CardTerm(),
        	256 + CardNonterm() - 1);
        fprintf(ParserOut,"%1d %1d \n", CardProd(), CardProdpos()-CardProd());
        fprintf(ParserOut,"0 -1 -2 \n"); /* Delimiter */
#endif
        fprintf(ParserOut, "%1u \n", FirstSym() + MAXTERM);
	aktsym = NIL;
	for (p = FirstProduct(); p != NIL ; p = NextProduct(p)) {
                pp = FirstPPos(p);
		if((symbol = Grm_Symbol(pp)) != aktsym) {
                	if (aktsym!=NIL)  fprintf(ParserOut, "-1 \n");
                        fprintf(ParserOut, "%1u \n", (aktsym=symbol) + MAXTERM);
                }
                while ((pp = NextPPos(pp)) != NIL)  {
                      if((symbol = Grm_Symbol(pp)) > anznonterm) {
                            symbol -= anznonterm;
                      } else {
                            symbol += MAXTERM;
                      }
                        fprintf(ParserOut, "%1u ", symbol);
                }
                fprintf(ParserOut, "0 \n");
        }
        fprintf(ParserOut, "-1 \n-2 \n");
#ifdef OLDGRMFILE
        fprintf(ParserOut, "%1u \n", CardTerm());
        fprintf(ParserOut, "%1u \n", anznonterm);
#endif
        for(symbol = anznonterm+1; symbol <= CardVocabel(); symbol++) {
                DruckeSym (ParserOut, Sym_Name(symbol));
		fprintf(ParserOut, " \n");
        }
        for(symbol = 1; symbol <= anznonterm; symbol++) {
                DruckeSym (ParserOut, Sym_Name(symbol));
                fprintf(ParserOut, " \n");
        }
        fclose(ParserOut);
        return;
}

