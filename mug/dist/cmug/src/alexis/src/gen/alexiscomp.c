#include <stdio.h>
#include "AttrGlob.h"
extern long scanerrors,parseerrors,semerrors;

Token MUGToken;


#include "alexis_DummyPN.c"

#include "alexis_NNTypen.c"

#include "alexis_ATyp.c"
#include "alexis_STyp.c"

#include "alexis_AKonstr.c"
#include "SMparsauft.h"
#include "alexis_SKonstr.c"

#include "alexis_AVar.c"
#include "alexis_SVar.c"

#include "alexis_Auswert.c"




main(argc,argv)
int argc; char **argv;
{
    int i;
    if (argc==1) return(1);


    if (alexisBAUMAUFBAU(argc,argv,argv[1],&alexisAOUT)==0)
    {
#ifdef BROWSER
          alexisCOMPILER(alexisAOUT,&alexisOUT, argv[1]);
#else
          alexisCOMPILER(alexisAOUT,&alexisOUT);
#endif
    }
    else
        { printf("Baum wurde nicht aufgebaut !\n");
          return(1); }
    return(scanerrors+parseerrors+semerrors);
}

