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


/* ************************************************************** */
/* readfile.h:                                                    */
/* Deklarationen Einlesen kompletter Dateien in den Hauptspeicher */
/* erstellt: 25.10.90                                             */
/* ************************************************************** */
#ifndef READFILE_H
#define READFILE_H
/* ==================================================== */
/* Datei mit Namen  <name> komplett in Puffer einlesen  */
/* Rueckgabe : Adresse des verwendeten Puffers          */
/* ==================================================== */
#ifdef __STDC__
char *readFile(char *name,unsigned long *file_len);
#else
char *readFile();
#endif

/* ==================================================== */
/* Dateirest von <file> komplett in Puffer einlesen     */
/* Rueckgabe : Adresse des verwendeten Puffers          */
/* ==================================================== */
#ifdef __STDC__
char *freadFile(FILE *file, unsigned long *file_len);
#else
char *freadFile();
#endif

#endif /* READFILE_H */
