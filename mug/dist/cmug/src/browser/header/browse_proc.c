/************************************************************************/
/************************************************************************/
/**								       **/
/** File:	browse_proc.c					       **/
/**								       **/
/** Purpose:	Outputfunctions used by compiler		       **/
/** Author:	Peter Mueller					       **/
/** Creation:	17.8.1994					       **/
/**								       **/
/************************************************************************/
/************************************************************************/

/************************************************************************/
/*									*/
/* spezifische Includes							*/
/*									*/
/************************************************************************/
#include "browse_len.h"
#include "browse_ds.h"


/************************************************************************/
/*									*/
/* globale Variable							*/
/*									*/
/************************************************************************/
FILE *b_bfile;


/************************************************************************/
/* basename								*/
/* 									*/
/* liefert Filenamen ohne Pfad und Endung: /usr/prog.flirt --> prog	*/
/************************************************************************/
char *basename(b_filename)
char *b_filename;
{
char *b_ptr;

for (b_ptr = b_filename+strlen(b_filename); b_ptr >= b_filename; b_ptr--)
	{
	if (*b_ptr == '.')	/* Suffix gefunden 	*/
		*b_ptr = '\0';	/* abschneiden		*/
	if (*b_ptr == '/')	/* Jetzt kommt das Verzeichnis */
		return (++b_ptr);
	}
return b_filename;
}


/************************************************************************/
/* BROWSE_print_satz							*/
/* 									*/
/* Ausgabe eines Satzes in das browse-file				*/
/************************************************************************/
void BROWSE_print_satz(char b_satzart, union satz_info *b_info)
{
fputc(b_satzart, b_bfile);
fwrite((char *)b_info, sizeof(union satz_info), 1, b_bfile);
}


/************************************************************************/
/* BROWSE_print_argument						*/
/* 									*/
/* Ausgabe eines G-Satzes (Attribut oder Terminal als Argument)		*/
/************************************************************************/
void BROWSE_print_argument(b_attr, b_art, b_symbol, b_id)
char *b_attr;
char b_art;
char *b_symbol;
int b_id;
{
union satz_info b_I;

if (b_attr)
	strcpy(b_I.g.attr, b_attr);
else
	memset(b_I.g.attr, '\0', L_ATTRIBUT);

b_I.g.art=b_art;
strcpy(b_I.g.symbol, b_symbol);
b_I.g.id = b_id;

BROWSE_print_satz('G', &b_I);
}


/************************************************************************/
/* BROWSE_print_funktion						*/
/* 									*/
/* Ausgabe eines F-Satzes (Semantische Aktion)				*/
/************************************************************************/
void BROWSE_print_funktion(b_aktion, b_id)
char *b_aktion;
int b_id;
{
union satz_info b_I;

strcpy(b_I.f.aktion, b_aktion);
b_I.f.id = b_id;

BROWSE_print_satz('F', &b_I);
}


/************************************************************************/
/* BROWSE_print_header							*/
/* 									*/
/* Ausgabe eines H-Satzes (Beginn des Files)				*/
/************************************************************************/
void BROWSE_print_header(b_filename)
char *b_filename;
{
union satz_info b_I;

strcpy(b_I.h.filename, b_filename);

BROWSE_print_satz('H', &b_I);
}


/************************************************************************/
/* BROWSE_print_trailer							*/
/* 									*/
/* Ausgabe eines T-Satzes (Ende des Files)				*/
/************************************************************************/
void BROWSE_print_trailer()
{
union satz_info b_I;

b_I.t.dummy = ' ';

BROWSE_print_satz('T', &b_I);
}


/************************************************************************/
/* BROWSE_print_vater							*/
/* 									*/
/* Ausgabe eines V-Satzes (Beginn einer Produktion)			*/
/************************************************************************/
void BROWSE_print_vater(b_symbol, b_id)
char *b_symbol;
int b_id;
{
union satz_info b_I;

strcpy(b_I.v.symbol, b_symbol);
b_I.v.id = b_id;

BROWSE_print_satz('V', &b_I);
}


/************************************************************************/
/* BROWSE_print_sohn							*/
/* 									*/
/* Ausgabe eines S-Satzes (Sohn in einer Produktion)			*/
/************************************************************************/
void BROWSE_print_sohn(b_symbol, b_id, b_is_terminal)
char *b_symbol;
int b_id;
int b_is_terminal;
{
union satz_info b_I;

strcpy(b_I.s.symbol, b_symbol);
b_I.s.id = b_id;
b_I.s.is_terminal = b_is_terminal;

BROWSE_print_satz('S', &b_I);
}


/************************************************************************/
/* BROWSE_print_prod_end						*/
/* 									*/
/* Ausgabe eines P-Satzes (Ende einer Produktion)			*/
/************************************************************************/
void BROWSE_print_prod_end()
{
union satz_info b_I;

b_I.p.dummy = ' ';

BROWSE_print_satz('P', &b_I);
}


/************************************************************************/
/* BROWSE_print_attribut						*/
/* 									*/
/* Ausgabe eines A-Satzes (Attribut) mit Attributwert			*/
/************************************************************************/
void BROWSE_print_attribut(b_attr, b_art, b_typ, b_wertlen, b_is_copy, b_wert)
char *b_attr;
char b_art;
char *b_typ;
int b_wertlen;
int b_is_copy;
char *b_wert;
{
union satz_info b_I;

strcpy(b_I.a.attr, b_attr);
b_I.a.art = b_art;
strcpy(b_I.a.typ, b_typ);
b_I.a.wertlen = b_wertlen;
b_I.a.is_copy = b_is_copy;

BROWSE_print_satz('A', &b_I);

fwrite(b_wert, b_wertlen, 1, b_bfile);
}


/************************************************************************/
/* BROWSE_print_end_attr						*/
/* 									*/
/* Ausgabe eines E-Satzes (Ende einer Attributliste)			*/
/************************************************************************/
void BROWSE_print_end_attr()
{
union satz_info b_I;

b_I.e.dummy = ' ';

BROWSE_print_satz('E', &b_I);
}


/************************************************************************/
/* BROWSE_printinit							*/
/* 									*/
/* Oeffnen des browse-files						*/
/************************************************************************/
void BROWSE_printinit(b_filename)
char *b_filename;
{
char b_buffer[L_FILENAME];

sprintf(b_buffer, "%s.browse", basename(b_filename));

b_bfile = fopen(b_buffer, "w");
if (b_bfile == NULL)
	{
	printf("Can`t open outputfile %s!\n", b_buffer);
	exit(1);
	}

BROWSE_print_header(b_buffer);
}


/************************************************************************/
/* BROWSE_printend							*/
/* 									*/
/* schliessen des browse-files						*/
/************************************************************************/
void BROWSE_printend()
{
BROWSE_print_trailer();

fclose(b_bfile);
}
