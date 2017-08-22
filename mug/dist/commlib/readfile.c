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


/* ************************************************************* */
/* readfile.c:                                                   */
/* Routinen zum Einlesen kompletter Dateien in den Hauptspeicher */
/* erstellt: 25.10.90                                            */
/* ************************************************************* */
#ifdef __STDC__
#include <stddef.h>
#include <stdlib.h>
#endif
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "readfile.h"
/* ==================================================== */
/* Datei mit Namen  <name> komplett in Puffer einlesen  */
/* Rueckgabe : Adresse des verwendeten Puffers          */
/* ==================================================== */
#ifdef __STDC__
char *readFile(char *name,unsigned long *file_len)
#else
char *readFile(name,file_len)
 char *name;
 unsigned long *file_len;
#endif
 {
  FILE *file;
  char *bf;

  file = fopen (name, "r");
  if (file == (FILE *)NULL)
    {
     perror ("Can't read file");
     return(NULL);
    } 
   {
    struct stat stat_buf;

    if (fstat (fileno(file), &stat_buf) == -1)
     {
      perror("freadFile: fstat() failed");
      return(NULL);
     }
    *file_len=stat_buf.st_size;
   }
  if ((bf = (char *)malloc((unsigned)*file_len))==NULL)
   {
    fprintf(stderr,"no memory for file buffer\n");
    return(NULL);
   }
  if (*file_len != fread(bf,1,(int)*file_len,file))
   {
    perror("read failed");
    return(NULL);
   }
  fclose(file);
  return(bf);
 } /* readFile */


/* ==================================================== */
/* Dateirest von <file> komplett in Puffer einlesen     */
/* Rueckgabe : Adresse des verwendeten Puffers          */
/* ==================================================== */
#ifdef __STDC__
char *freadFile(FILE *file,unsigned long *file_len)
#else
char *freadFile(file,file_len)
 FILE *file;
 unsigned long *file_len;
#endif
 {
  char *bf;
  int efile;

  if (file == (FILE *)NULL)
    {
     fputs("freadFile: NULL file handle",stderr);
     return(NULL);
    } 
  efile = fileno(file);
#if !defined(unix) && !defined(amiga)
  if ( (*file_len = lseek(efile,0L,2)) == -1 ||
       lseek(efile,-*file_len,2)       == -1 )
   {
    perror("freadFile: lseek() failed");
    return(NULL);
   }
#else
   {
    struct stat stat_buf;
    long cur_pos;

    if (fstat (efile, &stat_buf) == -1)
     {
      perror("freadFile: fstat() failed");
      return(NULL);
     }
    if ((cur_pos = ftell(file)) == -1)
     {
      perror("freadFile: ftell() failed");
      return(NULL);
     }
    *file_len = stat_buf.st_size - cur_pos;
   }
#endif
  if ((bf = (char *)malloc((unsigned)*file_len))==NULL)
   {
    fprintf(stderr,"no memory for file buffer\n");
    return(NULL);
   }
  if (*file_len != read(efile,bf,(unsigned)*file_len))
   {
    perror("freadFile: read() failed");
    return(NULL);
   }
  return(bf);
 } /* freadFile */


