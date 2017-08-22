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
/* ti_read.c :                                                            */
/* LR(k)-Parser-Tabellen-Interpreter                                      */
/* Modul : Einlesen der Tabelle                                           */
/* ---------------------------------------------------------------------- */
/* Aenderung : 13.08.89, Umstellung auf Zugriffsfunktionen                */
/* erstellt  : 08.07.89                                                   */
/* ********************************************************************** */
#ifdef __STDC__
#include <stddef.h>
#include <stdlib.h>
#endif
#include <stdio.h>           /* E/A-Deklarationen                         */
#include <string.h>
#include "defs.h"      /* diverse unspezifische Definitionen        */

#include "ti_defs.h" 
#include "ti_zugr.h"
#include "ti_read.h"

/* ------------------------------------------------------ */
/* Einlesen einer Typ-Laenge len aus der Datei f          */
/* ------------------------------------------------------ */
#define READLEN(f,len) {if(!fread((char *)&(len),sizeof(Typlen),1,f))\
                          {fclose(f);return(0);} }
/* ------------------------------------------------------------ */
/* Setzen der zur Typ-Laenge len passenden Zugriffsfunktion zfn */
/* ------------------------------------------------------------ */
#define SETZFN(len,zfn) zfn = getTabfunkt((Typlen)(len))

/* -------------------------------------------------------------*/
/* Name der zur Typ-Laenge len passenden Zugriffsfunktion zfn   */
/* ------------------------------------------------------------ */
#define FNNAME(zfn) getTabfunktname(zfn)

/* -------------------------------------------------------------*/
/* Laenge der zur Typ-Laenge len passenden Zugriffsfunktion zfn */
/* ------------------------------------------------------------ */
#define TABLEN(zfn) ((Typlen)getTabfunktlen(zfn))

/* ------------------------------------------------------------ */
/* Einlesen eines Tabellenindex                                 */
/* ------------------------------------------------------------ */
#define READIND(f,max,len) {if(!readInd(f,&(max),(Typlen)(len)))\
                               {fclose(f);return(0);}}
/* ------------------------------------------------------------ */
/* Speicherreservierung fuer eine Tabelle                       */
/* ------------------------------------------------------------ */
#define ALLOCTAB(f,tab,tlen,max) {if ( (tab = (char *)malloc(\
             (unsigned)((tlen)*(max+1))) ) == NULL) {fclose(f);return(0);}}
/* ------------------------------------------------------------ */
/* Freigabe des Speichers einer Tabelle                         */
/* ------------------------------------------------------------ */
#define FREETAB(tab) free(tab)
/* ------------------------------------------------------------ */
/* Einlesen einer Tabelle                                       */
/* ------------------------------------------------------------ */
#define READTAB(f,tab,tlen,max) {if (!fread(tab,(int)(tlen),(int)(max+1),f))\
                                {fclose(f);return(0);}}

/* ========================================================= */
/* Einlesen eines Tabellenindex                              */
/* ========================================================= */
#ifdef __STDC__
static int readInd(FILE *f, Tabindex *num, Typlen tlen)
{
#else
static int readInd(f,num,tlen)
 FILE     *f;
 Tabindex *num;
 Typlen   tlen;
 {
#endif
  union {
         Uint8  uint8buf;
         Uint16 uint16buf;
         Uint32 uint32buf;
        } buf;

  if (! fread((char *)&buf,(int)tlen,1,f)) return(0); 
  switch(tlen)
   {
    case 1:
           *num = buf.uint8buf;
           break;
    case 2:
           *num = buf.uint16buf;
           break;
    case 4:
           *num = buf.uint32buf;
           break;
    default:
           return(0);
   } /* switch*/
  return(1);
 } /* readInd */


/* ========================================================= */
/* Teil-Tabelle als C-String ausgeben                        */
/* ========================================================= */
#ifdef __STDC__
static void fdumpTab(FILE *dfile, Tabelle tab, Typlen typlen, Tabindex maxi, char *name)
{
#else
static void fdumpTab(dfile,tab,typlen,maxi,name)
 FILE *dfile;
 Tabelle  tab;
 Typlen   typlen;
 Tabindex maxi;
 char *name;
 {
#endif
  ZFN_TYPE(zfkt); 
  Tabindex i,j;

  switch(typlen)
   {
    case 1:
      fputs("static Uint8 ",dfile);
      break;
    case 2:
      fputs("static Uint16 ",dfile);
      break;
    case 4:
      fputs("static Uint32 ",dfile);
      break;
    default:
      fprintf(stderr,"wrong typesize %d in fdumpTab(%s)\n",
                     (int)typlen,name);
      exit(20);
   } /* switch */
  zfkt = getTabfunkt(typlen);
  fputs(name,dfile);
  fputs("[] = {\n",dfile);
  for (i = 0; i <= maxi; )
   {
    for (j = 0; j < 8 && i <= maxi; j++)
      fprintf(dfile,"%luL,",(unsigned long)zfkt(tab,i++) );
    fputc('\n',dfile);
   }
  fputs("\t};\n",dfile);
   } /* fdumpTab */

/* ========================================================= */
/* Tabelle als C-Datenstruktur ausgeben                      */
/* ========================================================= */
#ifdef __STDC__
void cDump(FILE *dfile,Ptab *tab)
#else
void cDump(dfile,tab)
 FILE *dfile;
 Ptab *tab;
#endif
 {
  /*fputs("#include \"defs.h\"\n",dfile);*/ /* uv, 21.01.91*/
  fputs("#include \"ti_defs.h\"\n",dfile);
  fputs("#include \"ti_zugr.h\"\n",dfile);
  fdumpTab(dfile,tab->tuebsyms,TABLEN(tab->term_zfn),tab->ttabmax,
           "lt_tuebsyms");
  fdumpTab(dfile,tab->tuebs,TABLEN(tab->ueb_zfn),tab->ttabmax,
           "lt_tuebs");
  fdumpTab(dfile,tab->tdefs,TABLEN(tab->ueb_zfn),tab->zmax,
           "lt_tdefs");
  fdumpTab(dfile,tab->tinds,TABLEN(tab->tind_zfn),2*tab->zmax+1,
           "lt_tinds");
  fdumpTab(dfile,tab->nuebzust,TABLEN(tab->zust_zfn),tab->ntabmax,
           "lt_nuebzust");
  fdumpTab(dfile,tab->nuebs,TABLEN(tab->ueb_zfn),tab->ntabmax,
           "lt_nuebs");
  fdumpTab(dfile,tab->ndefs,TABLEN(tab->ueb_zfn),tab->nmax,
           "lt_ndefs");
  fdumpTab(dfile,tab->ninds,TABLEN(tab->nind_zfn),2*tab->nmax+1,
           "lt_ninds");
  fdumpTab(dfile,tab->prlhs,TABLEN(tab->nont_zfn),tab->pmax,
           "lt_prlhs");
  fdumpTab(dfile,tab->prlen,TABLEN(tab->plen_zfn),tab->pmax,
           "lt_prlen");
  fdumpTab(dfile,tab->tninds,TABLEN(tab->tnam_zfn),tab->tmax,
           "lt_tninds");
  fdumpTab(dfile,tab->tnames,(Typlen)1,(tab->tnmax+1),
           "lt_tnames");
  fdumpTab(dfile,tab->nninds,TABLEN(tab->nnam_zfn),tab->nmax,
           "lt_nninds");
  fdumpTab(dfile,tab->nnames,(Typlen)1,(tab->nnmax+1),
           "lt_nnames");
  fputs("Ptab lalr_tab = {\n",dfile);
  fputs("\t(Tabelle)lt_tuebsyms,(Tabelle)lt_tuebs,\n",dfile);
  fputs("\t(Tabelle)lt_tdefs,(Tabelle)lt_tinds,\n",dfile);
  fputs("\t(Tabelle)lt_nuebzust,(Tabelle)lt_nuebs,\n",dfile);
  fputs("\t(Tabelle)lt_ndefs,(Tabelle)lt_ninds,\n",dfile);
  fputs("\t(Tabelle)lt_prlhs,(Tabelle)lt_prlen,\n",dfile);
  fputs("\t(Tabelle)lt_tninds,(Tabelle)lt_tnames,\n",dfile);
  fputs("\t(Tabelle)lt_nninds,(Tabelle)lt_nnames,\n\t",dfile);
  fputs(FNNAME(tab->term_zfn),dfile);
  fputc(',',dfile);
  fputs(FNNAME(tab->nont_zfn),dfile);
  fputc(',',dfile);
  fputs(FNNAME(tab->zust_zfn),dfile);
  fputc(',',dfile);
  fputs(FNNAME(tab->prod_zfn),dfile);
  fputc(',',dfile);
  fputs(FNNAME(tab->ueb_zfn),dfile);
  fputs(",\n\t",dfile);
  fputs(FNNAME(tab->tind_zfn),dfile);
  fputc(',',dfile);
  fputs(FNNAME(tab->nind_zfn),dfile);
  fputc(',',dfile);
  fputs(FNNAME(tab->plen_zfn),dfile);
  fputc(',',dfile);
  fputs(FNNAME(tab->tnam_zfn),dfile);
  fputc(',',dfile);
  fputs(FNNAME(tab->nnam_zfn),dfile);
  fputs(",\n",dfile);
  fprintf(dfile,"\t%luL,%luL,%luL,%luL,\n",
                (long)tab->ttabmax,(long)tab->ntabmax,
                (long)tab->tnmax,(long)tab->nnmax);
  fprintf(dfile,"\t%luL,%luL,%luL,%luL,%luL\n",
                (long)tab->tmax,(long)tab->nmax,
                (long)tab->zmax,(long)tab->pmax,(long)tab->ushift);
  fputs("};\n",dfile);
 } /* cDump */

/* ========================================================= */
/* Typlaenge als String ausgeben			     */
/* ========================================================= */
#ifdef __STDC__
static char *sTyplen(int typlen,char *name)
#else
static char *sTyplen(typlen,name)
 int  typlen;
 char *name;
#endif
 {
  switch(typlen)
   {
    case 1:
      return "8";
      break;
    case 2:
      return "16";
      break;
    case 4:
      return "32";
      break;
    default:
      fprintf(stderr,"wrong typesize %d in fdumpTab(%s)\n",
                     (int)typlen,name);
      exit(20);
   } /* switch */
  return "";
 }

/* ========================================================= */
/* Datentypgroessen als C-Defines ausgeben                   */
/* ========================================================= */
#ifdef __STDC__
void cDefines(FILE *dfile,Ptab *tab)
#else
void cDefines(dfile,tab)
 FILE *dfile;
 Ptab *tab;
#endif
 {
#ifdef __STDC__
#define DEFI(TYP,typ) 	fputs("#define " #TYP "_IS_" ,dfile);		\
               	fputs(sTyplen(TABLEN(tab->typ##_zfn),#typ),dfile);	\
		fputs("BIT 1\n",dfile);
#else
#define DEFI(TYP,typ) 	fputs("#define " ,dfile);		\
		fputs("TYP" ,dfile);		\
		fputs("_IS_" ,dfile);		\
               	fputs(sTyplen(TABLEN(tab->typ/**/_zfn),"typ"),dfile);	\
		fputs("BIT 1\n",dfile);
#endif
  DEFI(TERM,term);
  DEFI(UEB,ueb);
  DEFI(TIND,tind);
  DEFI(ZUST,zust);
  DEFI(NIND,nind);
  DEFI(NONT,nont);
  DEFI(PLEN,plen);
  DEFI(TNAM,tnam);
  DEFI(NNAM,nnam);
 } /* cDefines */

/* ========================================================= */
/* Einlesen einer Parsertabelle                              */
/* Rueckgabe : != 0, falls erfolgreich eingelesen           */
/* ========================================================= */
#ifdef __STDC__
int readPtab(char *name, Ptab *tab)
               /* vollstaendiger Dateiname der Parsertabelle */
               /* Tabelle, in die eingelesen werden soll     */
#else
int readPtab(name,tab)
 char *name;   /* vollstaendiger Dateiname der Parsertabelle */
 Ptab *tab;    /* Tabelle, in die eingelesen werden soll     */
#endif
 {
  FILE    *tfile;     /* Handle der Tabellendatei                   */
  Typlen  term_len;   /* Typ-Laenge Datentyp Term                   */
  Typlen  nont_len;   /* Typ-Laenge Datentyp Nont                   */
  Typlen  zust_len;   /* Typ-Laenge Datentyp Zust                   */
  Typlen  prod_len;   /* Typ-Laenge Datentyp Prod                   */
  Typlen  ueb_len;    /* Typ-Laenge Datentyp Ueb                    */
  Typlen  tind_len;   /* Typ-Laenge Datentyp Tind                   */
  Typlen  nind_len;   /* Typ-Laenge Datentyp Nind                   */
  Typlen  plen_len;   /* Typ-Laenge Datentyp Plen                   */
  Typlen  tnam_len;   /*Typ-Laenge Datentyp Tnam                   */
  Typlen  nnam_len;   /* Typ-Laenge Datentyp Nnam                   */

  /* -------------------------------------------- */
  /* Tabellendatei oeffnen, Kommentar ueberlesen  */
  /* -------------------------------------------- */
  if ( (tfile = fopen(name,"r") ) == NULL)
    return(0);     
  {
    register char c;

    DBGPRT(("Kommentar : \""));
    do /* Einlesen bis zum ersten Zeilenende */
     {
      if ((c = fgetc(tfile)) == EOF)
        return(0);     
      IFDEBUG
       ({
        putc(c,stdout);
       })
     }
    while (c != '\n');
    DBGPRT(("\"\n"));
  }
  
  /* ------------------------------------------ */
  /* Zugriff und Wertebereich Datentyp : Term   */
  /* ------------------------------------------ */
  READLEN(tfile,term_len);
  SETZFN(term_len,tab->term_zfn);
  READIND(tfile,tab->tmax,term_len);

  /* ------------------------------------------ */
  /* Zugriff und Wertebereich Datentyp : Nont   */
  /* ------------------------------------------ */
  READLEN(tfile,nont_len);
  SETZFN(nont_len,tab->nont_zfn);
  READIND(tfile,tab->nmax,nont_len);

  /* ------------------------------------------ */
  /* Zugriff und Wertebereich Datentyp : Zust   */
  /* ------------------------------------------ */
  READLEN(tfile,zust_len);
  SETZFN(zust_len,tab->zust_zfn);
  READIND(tfile,tab->zmax,zust_len);

  /* ------------------------------------------ */
  /* Zugriff und Wertebereich Datentyp : Prod   */
  /* ------------------------------------------ */
  READLEN(tfile,prod_len);
  SETZFN(prod_len,tab->prod_zfn);
  READIND(tfile,tab->pmax,prod_len);

  /* ------------------------------------------ */
  /* Zugriff und Wertebereich Datentyp : Ueb    */
  /* ------------------------------------------ */
  READLEN(tfile,ueb_len);
  SETZFN(ueb_len,tab->ueb_zfn);
  USHIFT(*tab) = getUebshift(ueb_len);


  /* ------------------------------------------ */
  /* Zugriff und Wertebereich Datentyp : Tind   */
  /* ------------------------------------------ */
  READLEN(tfile,tind_len);
  SETZFN(tind_len,tab->tind_zfn);
  READIND(tfile,tab->ttabmax,tind_len);


  DBGPRT(("tuebsyms lesen\n" ));

  ALLOCTAB(tfile,tab->tuebsyms,term_len,tab->ttabmax);
  READTAB(tfile,tab->tuebsyms,term_len,tab->ttabmax);


  DBGPRT(("tuebs lesen\n" ));

  ALLOCTAB(tfile,tab->tuebs,ueb_len,tab->ttabmax);
  READTAB(tfile,tab->tuebs,ueb_len,tab->ttabmax);


  DBGPRT(("tdefs lesen\n" ));

  ALLOCTAB(tfile,tab->tdefs,ueb_len,tab->zmax);
  READTAB(tfile,tab->tdefs,ueb_len,tab->zmax);


  DBGPRT(("tinds lesen\n" ));

  ALLOCTAB(tfile,tab->tinds,tind_len,2*tab->zmax+1);
  READTAB(tfile,tab->tinds,tind_len,2*tab->zmax+1);

  /* ------------------------------------------ */
  /* Zugriff und Wertebereich Datentyp : Nind   */
  /* ------------------------------------------ */
  READLEN(tfile,nind_len);
  SETZFN(nind_len,tab->nind_zfn);
  READIND(tfile,tab->ntabmax,nind_len);


  DBGPRT(("nuebzust lesen\n" ));

  ALLOCTAB(tfile,tab->nuebzust,zust_len,tab->ntabmax);
  READTAB(tfile,tab->nuebzust,zust_len,tab->ntabmax);


  DBGPRT(("nuebs lesen\n" ));

  ALLOCTAB(tfile,tab->nuebs,ueb_len,tab->ntabmax);
  READTAB(tfile,tab->nuebs,ueb_len,tab->ntabmax);


  DBGPRT(("ndefs lesen\n" ));

  ALLOCTAB(tfile,tab->ndefs,ueb_len,tab->nmax);
  READTAB(tfile,tab->ndefs,ueb_len,tab->nmax);


  DBGPRT(("ninds lesen\n" ));

  ALLOCTAB(tfile,tab->ninds,nind_len,2*tab->nmax+1);
  READTAB(tfile,tab->ninds,nind_len,2*tab->nmax+1);


  DBGPRT(("prlhs lesen\n" ));

  ALLOCTAB(tfile,tab->prlhs,nont_len,tab->pmax);
  READTAB(tfile,tab->prlhs,nont_len,tab->pmax);

  /* ------------------------------------------ */
  /* Zugriff und Wertebereich Datentyp : Plen   */
  /* ------------------------------------------ */
  READLEN(tfile,plen_len);
  SETZFN(plen_len,tab->plen_zfn);


  DBGPRT(("prlen lesen\n" ));

  ALLOCTAB(tfile,tab->prlen,plen_len,tab->pmax);
  READTAB(tfile,tab->prlen,plen_len,tab->pmax);

  /* ------------------------------------------ */
  /* Zugriff und Wertebereich Datentyp : Tnam   */
  /* ------------------------------------------ */
  READLEN(tfile,tnam_len);
  SETZFN(tnam_len,tab->tnam_zfn);
  READIND(tfile,tab->tnmax,tnam_len);


  DBGPRT(("tninds lesen\n" ));

  ALLOCTAB(tfile,tab->tninds,tnam_len,tab->tmax);
  READTAB(tfile,tab->tninds,tnam_len,tab->tmax);


  DBGPRT(("tnames lesen\n" ));

  ALLOCTAB(tfile,tab->tnames,sizeof(char),tab->tnmax);
  READTAB(tfile,tab->tnames,sizeof(char),tab->tnmax);

  /* ------------------------------------------ */
  /* Zugriff und Wertebereich Datentyp : Nnam   */
  /* ------------------------------------------ */
  READLEN(tfile,nnam_len);
  SETZFN(nnam_len,tab->nnam_zfn);
  READIND(tfile,tab->nnmax,nnam_len);


  DBGPRT(("nninds lesen\n" ));

  ALLOCTAB(tfile,tab->nninds,nnam_len,tab->nmax);
  READTAB(tfile,tab->nninds,nnam_len,tab->nmax);


  DBGPRT(("nnames lesen\n" ));

  ALLOCTAB(tfile,tab->nnames,sizeof(char),tab->nnmax);
  READTAB(tfile,tab->nnames,sizeof(char),tab->nnmax);


  fclose(tfile);
  return(1);              /* erfolgreich eingelesen */

 } /* readPtab */

/* ========================================================= */
/* Speicherfreigabe Parsertabelle                            */
/* ========================================================= */
#ifdef __STDC__
void freePtab(Ptab *tab)
               /* Tabelle, in die eingelesen werden soll     */
#else
void freePtab(tab)
 Ptab *tab;    /* Tabelle, in die eingelesen werden soll     */
#endif
 {
  FREETAB(tab->tuebsyms);
  FREETAB(tab->tuebs);
  FREETAB(tab->tdefs);
  FREETAB(tab->tinds);
  FREETAB(tab->nuebzust);
  FREETAB(tab->nuebs);
  FREETAB(tab->ndefs);
  FREETAB(tab->ninds);
  FREETAB(tab->prlhs);
  FREETAB(tab->prlen);
  FREETAB(tab->tninds);
  FREETAB(tab->tnames);
  FREETAB(tab->nninds);
  FREETAB(tab->nnames);
 } /* freePtab */
