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
#define EXTERN 
#include "globals.h"
EXTERN long semerrors;

/* Haupt-Prozedur, die vom Einleser aufgerufen wird, nachdem die Grammatik
	vollstaendig eingelesen wurde. */
/* Das geschieht in der semantischen Aktion GramReturn des Grammatikeinlesers */

#ifdef __STDC__
void AGuser(void)
#else /* ! __STDC__ */
void AGuser()
#endif /* ! __STDC__ */
{
extern int druckekeller;
Funct f;
int   anzfalsch;

/* Abpruefung, ob eine Grammatik ohne Mehrfachergebnisse vorliegt */
anzfalsch = 0;
for (f = FirstFunct(); f != NIL; f = NextFunct(f))
 {
  Fparam erg;
  if ((erg = FirstFErg(f)) != NIL && NextFErg(erg) != NIL)
   {
    if (!anzfalsch) /* erster Fehler */
      wErrorf(NULL,
    "folgende Funktionen besitzen Mehrfachergebnisse (nicht implementiert):");
    if (!(anzfalsch++ % 4))
      wErrorf(NULL,"\n");
    wErrorf(NULL,"\t%s",SymString(Funkt_Name(f)));
    semerrors++;
   }
 }
if (anzfalsch)
 {
  wErrorf(NULL,"\nGenerierung abgebrochen\n");
  exit(20);
 }
if(druckekeller)
{
	outglob = fopen("outglob.out", "w");      /* Oeffnen der Files */
	outprod = fopen("outprod.out", "w");
   outcopy = fopen("outcopy.out", "w");
}

printf(" MINIMUG: Grammatiktransformation \t (c) TU Muenchen %s\n",__DATE__);

maintrans();

if(druckekeller)
{
	fclose(outglob);                    /* Schliessen der Files */
	fclose(outprod);
	fclose(outcopy);
}
}
