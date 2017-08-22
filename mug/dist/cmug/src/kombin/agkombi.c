
/* Letzte Aenderungen:
*  Mai 91 lahner : Verlagerung der Compiler-Eingabe in die Include-Files SM~~.h,
*                  Steuerung mit Modusangabe.
*
*  August 94 Peter Mueller:
*		   Weitergabe des Filenamens an den Compiler
*********************************************************************/

#include <stdio.h>

typedef int bool;
#define TRUE 1
#define FALSE 0


/*************************************************************
 * Hilfsstring und globale ERROR- und Modus-Variable         *
 *************************************************************/
char hstring[200];
bool ERROR;
int PARSAUF, OUTTERMTOK, READPRDEF;


/*************************************************************
 *                                                           *
 *    Datenstrukur zur Beschreibung der Phasen               *
 *    ========================================               *
 *                                                           *
 *************************************************************/
int AnzPhase;       /* Enthaelt die Anzahl der im Aufruf von agkombi
                       uebergebenen Phasennamen                         */

struct GramDesk {   /* Array in dem alle Phasennamen und alle           */
    char *Phase;    /* Ein- bzw. Ausgabegrammatiknamen enthalten sind   */
    char *InGram;
    char *OutGram;
    } *GramDesk;


/*************************************************************
 *                                                           *
 *         Hilfsfunktionen                                   *
 *         ===============                                   *
 *                                                           *
 *                                                           *
 *************************************************************/

Fehlermeldung(progname)
    char *progname;
    {
        printf(
	"Usage %s <Modus> <Projektname> <Phase 1 Name> <Phase 2 Name> u.s.w\n",
	progname);
        printf("   wobei    <Modus> : sm, gtok, gint\n");
        printf("      sm    ~  Lesen der Parserausgabe von Datei\n");
        printf("      gtok  ~  Parseraufruf mit outterm(Token) -Schnittstelle\n");
        printf("      gint  ~  Parseraufruf mit outterm(long,long,..) -Schnittstelle\n");
	exit(1);
    }


Moduseinst(argv)
/*************************************************************
 * Einstellen des Modus                                      *
 *************************************************************/
char **argv;
{
    if (strcmp(argv[1],"sm")==0)
    { PARSAUF = 0;  OUTTERMTOK = 0; READPRDEF = 1; }
    else if (strcmp(argv[1],"gtok")==0)
    { PARSAUF = 1;  OUTTERMTOK = 1; READPRDEF = 0; }
    else if (strcmp(argv[1],"gint")==0)
    { PARSAUF = 1;  OUTTERMTOK = 0; READPRDEF = 1; }
    else  Fehlermeldung(argv[0]);
}

int *alloc(size)
/*************************************************************
 * Allokieren von Speicher und Test auf NULL                 *
 *************************************************************/
int size;
{
    int *mem;

    mem=(int *)malloc(size);
    if (mem==NULL)
        printf("Zuwenig Speicher !\n"),exit(1);
    return(mem);
}

ReadPhasenDesk(PhasenNr,Phase)
/*************************************************************
 * Initialisiert Arrayposition PhasenNR von GramDesk.        *
 * Phasenname , Eingabegrammatikname und Ausgabegrammatikname*
 * werden aus dem File <Phase>.Desk gelesen.                 *
 *************************************************************/
int PhasenNr;
char *Phase;
{
    FILE *Desk;

    sprintf(hstring,"%s.Desk\0",Phase);        /* FILE oeffnen */
    Desk=(FILE *)fopen(hstring,"r");
    if (Desk==NULL) 
    {
        printf("Fehler : %s existiert nicht !\n",hstring);
        ERROR=TRUE;
        return;
    }
    fscanf(Desk,"%s ",hstring); 
    GramDesk[PhasenNr].Phase=(char *)alloc(strlen(hstring)+1);
    strcpy(GramDesk[PhasenNr].Phase,hstring);

    fscanf(Desk,"%s ",hstring);
    GramDesk[PhasenNr].InGram=(char *)alloc(strlen(hstring)+1);
    strcpy(GramDesk[PhasenNr].InGram,hstring);

    fscanf(Desk,"%s ",hstring);
    GramDesk[PhasenNr].OutGram=(char *)alloc(strlen(hstring)+1);
    strcpy(GramDesk[PhasenNr].OutGram,hstring);

    fclose(Desk);
}


TestePhasenZykl()
/*************************************************************
 * Testet, ob Ausgabegrammatikname mit Eingabegrammatikname  *
 * der drauffolgenden Phase|bereinstimmt.                   *
 *************************************************************/
{
    int i;
    bool error;    

    error=FALSE;
    for (i=0;i<AnzPhase-1;i++)
        if (strcmp(GramDesk[i].OutGram,GramDesk[i+1].InGram)!=0)
        {
            printf("Konflikt Aus- und Eingabegrammatiknamen zwischen Phase %s und %s\n"
                 ,GramDesk[i].Phase,GramDesk[i+1].Phase);
            error=TRUE;
        }        

    if (error) exit(1);
}

TesteGleichePhasen()
/*************************************************************
 * Testet, ob Phasennamen paarweise verschieden              *
 *************************************************************/
{
    int i,j;
    bool error;    

    error=FALSE;
    for (i=0;i<AnzPhase-1;i++)
        for (j=i+1;j<AnzPhase-1;j++)
            if (strcmp(GramDesk[i].Phase,GramDesk[j].Phase)==0)
            {
                printf("Phasennamen nicht paarweise verschieden !\n");
                error=TRUE;
            }        

    if (error) exit(1);
}    


/*************************************************************
 *                                                           *
 *    Generierung des Hauptprogramms                         *
 *    ==============================                         *
 *                                                           *
 *************************************************************/
main(argc,argv)
int argc;
char **argv;
{
    int i;
    FILE *file;

    if (argc<=3)  Fehlermeldung(argv[0]);
    Moduseinst(argv);
    AnzPhase=argc-3;          /* Phasenanzahl init */
                              /* Speicher fuer Phasenbeschreibung allok.*/
    GramDesk=(struct GramDesk *)alloc(sizeof(struct GramDesk)*AnzPhase);
    for (i=0;i<AnzPhase;i++)  /* Einlesen der Phasen und Gram. Namen */
        ReadPhasenDesk(i,argv[i+3]);
    if (ERROR) exit(1);       /* Falls Fehler, exit */

    TestePhasenZykl();        /* Teste, ob Phasen zusammenpassen */
    TesteGleichePhasen();     /* und ob gleiche Phasennamen exist. */
    sprintf(hstring,"%scomp.c",argv[2]); /* FILE <Projekt>comp.c oeffnen */
    file=(FILE *)fopen(hstring,"w");
    if (file==NULL) 
    {
        printf("Kann File %s nicht oeffnen !\n",hstring);
        exit(1);
    }

    /*************************************************************
     * Beginn der Ausgabe                                        *
     *************************************************************/

    fprintf(file,"#include <stdio.h>\n");
    fprintf(file,"#include \"AttrGlob.h\"\n");
/*  fprintf(file,"#include \"%stype.h\"\n\n",argv[2]); */
   
    if (OUTTERMTOK)  
    {
        fprintf(file,"extern long scanerrors,parseerrors,semerrors;\n\n");
        fprintf(file,"Token MUGToken;\n\n");
    }
       
    if (! PARSAUF)
    {   fprintf(file,"extern void decinit();\n");
        fprintf(file,"extern void decode();\n");
    }
    fprintf(file,"\n");

    for (i=1;i<AnzPhase;i++)
        fprintf(file,"#include \"%s_Prodnum.c\"\n",GramDesk[i].Phase);
    fprintf(file,"#include \"%s_DummyPN.c\"\n",GramDesk[AnzPhase-1].Phase);

    fprintf(file,"\n");
    for (i=0;i<AnzPhase;i++)
        fprintf(file,"#include \"%s_NNTypen.c\"\n",GramDesk[i].Phase);

    fprintf(file,"\n");
    fprintf(file,"#include \"%s_ATyp.c\"\n",GramDesk[0].Phase);
    for (i=0;i<AnzPhase;i++)
        fprintf(file,"#include \"%s_STyp.c\"\n",GramDesk[i].Phase);

    fprintf(file,"\n");
    if (READPRDEF)  fprintf(file,"#define READpr\n");
    fprintf(file,"#include \"%s_AKonstr.c\"\n",GramDesk[0].Phase);

    if (PARSAUF)  
       if (OUTTERMTOK)  fprintf(file,"#include \"SMparsauft.h\"\n");
       else  fprintf(file,"#include \"SMparsaufl.h\"\n");
    else  fprintf(file,"#include \"SMbaumeing.h\"\n");
    
    for (i=0;i<AnzPhase;i++)
        fprintf(file,"#include \"%s_SKonstr.c\"\n",GramDesk[i].Phase);

    fprintf(file,"\n");
    fprintf(file,"#include \"%s_AVar.c\"\n",GramDesk[0].Phase);
    for (i=0;i<AnzPhase;i++)
        fprintf(file,"#include \"%s_SVar.c\"\n",GramDesk[i].Phase);

    fprintf(file,"\n");
    for (i=0;i<AnzPhase;i++)
        fprintf(file,"#include \"%s_Auswert.c\"\n",GramDesk[i].Phase);

    fprintf(file,"\n\n\n\n");
    fprintf(file,"main(argc,argv)\n");
    fprintf(file,"int argc; char **argv;\n");
    fprintf(file,"{\n");
    fprintf(file,"    int i;\n");
    fprintf(file,"    if (argc==1) return(1);\n");
    fprintf(file,"\n");
    fprintf(file,"\n");

    fprintf(file,"    if (%sBAUMAUFBAU(argc,argv,argv[1],&%sAOUT)==0)\n"
        ,GramDesk[0].Phase,GramDesk[0].Phase);
    fprintf(file,"    {\n");

/* CHANGE for MUGbrowser */
    fprintf(file,"#ifdef BROWSER\n");
    fprintf(file,"          %sCOMPILER(%sAOUT,&%sOUT, argv[1]);\n"
        ,GramDesk[0].Phase,GramDesk[0].Phase,GramDesk[0].Phase);
    fprintf(file,"#else\n");
    fprintf(file,"          %sCOMPILER(%sAOUT,&%sOUT);\n"
        ,GramDesk[0].Phase,GramDesk[0].Phase,GramDesk[0].Phase);
    fprintf(file,"#endif\n");
/* End of Change */

    for (i=1;i<AnzPhase;i++)
        fprintf(file,"        %sCOMPILER(%sOUT,&%sOUT);\n"
            ,GramDesk[i].Phase,GramDesk[i-1].Phase,GramDesk[i].Phase);
    fprintf(file,"    }\n");
    fprintf(file,"    else\n");
    fprintf(file,"        { printf(\"Baum wurde nicht aufgebaut !\\n\");\n");
    fprintf(file,"          return(1); }\n");
    if (OUTTERMTOK)
         fprintf(file,"    return(scanerrors+parseerrors+semerrors);\n");
    else fprintf(file,"    return(0);\n");
    fprintf(file,"}\n\n");
    return(0);
}

