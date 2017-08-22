

                 /* KWAUSWERTER */
                 /* =========== */


#ifndef VOIDPTR_T
#ifdef __STDC__
 typedef void *voidptr;
#else
 typedef char *voidptr;
#endif
#define VOIDPTR_T
#endif

#include "alexis_Automat.c"
#include "alexis_Wandere.c"
#ifdef BROWSER
#include "alexis_Browse.c"
#include "alexis_BrowseWandere.c"
#endif


#ifdef BROWSER
alexisCOMPILER(EINGABEBAUM,AUSGABEBAUM, filename)
#else
alexisCOMPILER(EINGABEBAUM,AUSGABEBAUM)
#endif
struct g1scanner *EINGABEBAUM;
BOOL **AUSGABEBAUM;
#ifdef BROWSER
char *filename;
#endif
{
	alexisMUGEXPORT=0;
	alexisMUGWANDERE((void *)EINGABEBAUM);
	*AUSGABEBAUM= &EINGABEBAUM->NN.dscan;
#ifdef BROWSER
	BROWSE_printinit(filename);
	(*alexisBrowseTab[EINGABEBAUM->prodnum])(EINGABEBAUM);
	BROWSE_printend();
#endif
}
