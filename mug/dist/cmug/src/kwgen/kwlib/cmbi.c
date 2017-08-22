
/* Letzte Aenderungen:  mai 91 lahner : Abtrennung der Eingabe fuer die
*                                       verschiedenen Compiler-Versionen.
/*                   :  nov 91 lahner : Behandlung der syntaktischen Attribute
**********************************************************************/

#include <stdio.h>
#include "zufunc.h"

char hstring[100],*PhasenName;

#define CMaxStack 10000
#define CMinT 0
#define CMinP 1

/* #define shift 'T'
   #define reduce 'R'
   #define entry 'E'
   #define error 'F'
   #define fterror 'D'
   #define accept 'A'
   #define LCshift 't'
   #define LCreduce 'r'
   #define LCentry 'e'
   #define LCerror 'f'
   #define LCfterror 'd'
   #define LCaccept 'a'
*/

/**********************************************************************
 *                                                                    *
 * Hilfsfunktionen fuer die Ausgabe von Typen und Variable            *
 * ======================================================             *
 *                                                                    *
 **********************************************************************/

GenEinType(file,Par)
/**********************************************************************
 * Typ der Eingabegrammatik wird generiert                            * 
 **********************************************************************/
FILE *file;
Entry Par;
{    fprintf(file,"%s%s",SymString(GetInGName()),SymString(Par));   }

GenEinNNType(file,Par)
/**********************************************************************
 * NN-Typ der Eingabegrammatik wird generiert                         *
 **********************************************************************/
FILE *file;
Entry Par;
{    fprintf(file,"%s%sNN",SymString(GetInGName()),SymString(Par)); }

GenAusType(file,Par)
/**********************************************************************
 * Typ der Ausgabegrammatik wird generiert                            *
 **********************************************************************/
FILE *file;
Entry Par;
{    fprintf(file,"%s%s",SymString(GetOutGName()),SymString(Par));  }

GenAusNNType(file,Par)
/**********************************************************************
 * NN-Typ der Ausgabegramatik wird generiert                          *
 **********************************************************************/
FILE *file;
Entry Par;
{    fprintf(file,"%s%sNN",SymString(GetOutGName()),SymString(Par));}

/**********************************************************************
 *                                                                    *
 * Sonstige Hilfsfunktionen                                           *
 * ========================                                           *
 *                                                                    *
 **********************************************************************/

Is_SynFunct( F)
  Funct F;
/**********************************************************************
 * Liefert zurueck, ob Funktion F syntaktisch ist                     * 
 **********************************************************************/
{
    return(FirstFErg(F) > 0 && Is_SynTTyp(Typ_Of_Fparam(FirstFErg(F))));
}

FILE *FOpen(filename,status)
char *filename,*status;
/**********************************************************************
 * Oeffnen eines Files zum schreiben                                  *
 **********************************************************************/
{
    FILE *file;

    file=fopen(filename,status);
    if (file==NULL)
    {
        printf("Kann File %s nicht oeffnen !\n",filename);
        exit(1);
    }
    else 
        return(file);
}

/*************************************************************************
 *                                                                       *
 *                 E I N G A B E B A U M R E P                           *
 *                 ===========================                           *
 *                                                                       *
 *************************************************************************/

GenAnalyseTypen(file)
FILE *file;
/**********************************************************************
 * Generiert die Analysetypen                                         *
 **********************************************************************/
{
    Vocabel V,VPP;
    Product P;
    Prodpos PP;
    bool unionexists;
    bool structexists;

    for (V=FirstSym();V!=NIL && ! Is_Terminal(V);V=NextSym(V))
    {
        fprintf(file,"struct ");
        GenEinType(file,Sym_Name(V));
        fprintf(file,"{\n");
        fprintf(file,"\tshort prodnum;\n");
        fprintf(file,"\tstruct ");
        GenEinNNType(file,Sym_Name(V));
        fprintf(file," NN;\n");

        unionexists=FALSE;
        for (P=FirstProd(V);P!=NIL;P=NextProd(P))
        {
            structexists=FALSE;
            for (PP=NextPPos(FirstPPos(P));PP!=NIL;PP=NextPPos(PP))
            {
                if (!Is_Terminal(VPP=Grm_Symbol(PP)))
                {
                    if (!unionexists) fprintf(file,"\tunion {\n"),unionexists=TRUE;
                    if (!structexists) fprintf(file,"\t\tstruct {\n"),structexists=TRUE;
                    fprintf(file,"\t\t\tstruct ");
                    GenEinType(file,Sym_Name(VPP));
                    fprintf(file," *%s%d;\n",SymString(Prod_Name(P)),PPos_Nummer(PP));
                }
                else 
                if (Is_Semantisch(VPP))
                {
                    if (!unionexists) fprintf(file,"\tunion {\n"),unionexists=TRUE;
                    if (!structexists) fprintf(file,"\t\tstruct {\n"),structexists=TRUE;
                    fprintf(file,"\t\t\t%s",SymString(Sym_Name(VPP)));
                    fprintf(file," *%s%d;\n",SymString(Prod_Name(P)),PPos_Nummer(PP));
                }
            }
            if (structexists) fprintf(file,"\t\t} %s;\n",SymString(Prod_Name(P)));
        }
        if (unionexists) fprintf(file,"\t} C;\n");
        fprintf(file,"};\n");
    }
}

GenAnalyseVariable(file)
  FILE *file;
/**********************************************************************
 * Generiert Analysevariable                                          *
 **********************************************************************/
{
    fprintf(file,"struct ",PhasenName);
    GenEinType(file,Sym_Name(FirstSym()));
    fprintf(file," *%sAOUT;\n",PhasenName);
}

GenStDekl(file)
  FILE *file;
/**********************************************************************
 * Generiert Analyse Deklarationen                                    *
 **********************************************************************/
{
    fprintf(file,"#define MUGCMaxSt %d\n",CMaxStack);
    fprintf(file,"#define MUGAnzT %d\n",CardTerm());
    fprintf(file,"#define MUGCMinT %d\n",CMinT);
    fprintf(file,"#define MUGCMinP %d\n",CMinP);
    fprintf(file,"\n");
    fprintf(file,"struct MUGStEntry {\n");
    fprintf(file,"\tint MUGElem;\n");
    fprintf(file,"\tint *MUGEntry;\n");
    fprintf(file,"};\n\n");
    fprintf(file,"struct MUGStEntry *MUGSt,MUGHStEntry;\n");
    fprintf(file,"int MUGStTop;\n");
    fprintf(file,"char MUGAccepted;\n");
    fprintf(file,"int MUGErrNum;\n");
    fprintf(file,"int MUGRCode,MUGCode,MUGZl,MUGSp;\n\n");
}


GenStProc(file)
  FILE *file;
/**********************************************************************
 * Generiert Analyse Prozeduren                                       *
 **********************************************************************/
{
    fprintf(file,"int *ALLOC(size)\n");
    fprintf(file,"int size;\n");
    fprintf(file,"{\n");
    fprintf(file,"\tint *p;\n");
    fprintf(file,"\tif ((p=(int *)calloc(size,1))==NULL)\n");
    fprintf(file,"\t\tprintf(\"Speicher ist voll !\\n\"),exit(1);\n");
    fprintf(file,"\telse return(p);\n");
    fprintf(file,"}\n\n");

    fprintf(file,"MUGPop(MUGOut)\n");
    fprintf(file,"struct MUGStEntry *MUGOut;\n");
    fprintf(file,"{\n");
    fprintf(file,"\tif (MUGStTop>=0)\n");
    fprintf(file,"\t\t*MUGOut=MUGSt[MUGStTop--];\n");
    fprintf(file,"}\n\n");

    fprintf(file,"MUGInitSt()\n");
    fprintf(file,"{\n\tMUGStTop=0;\n");
    fprintf(file,"\tMUGSt=(struct MUGStEntry *)ALLOC(MUGCMaxSt*sizeof(struct MUGStEntry));\n");
    fprintf(file,"}\n\n");

    fprintf(file,"MUGPush(MUGIn)\n");
    fprintf(file,"struct MUGStEntry *MUGIn;\n");
    fprintf(file,"{\n");
    fprintf(file,"\tif (MUGStTop<MUGCMaxSt)\n");
    fprintf(file,"\t\tMUGSt[++MUGStTop]=(*MUGIn);\n");
    fprintf(file,"\telse MUGErrNum=2;\n");
    fprintf(file,"}\n\n");

}

GenTProc(file,V)
  FILE *file;
  Vocabel V;
/**********************************************************************
 * Generiert zu Terminal einen Konstruktor                            *
 **********************************************************************/
{
    int Vh;
    char *TermName;

    Vh=V-CardNonterm();
    TermName=SymString(Sym_Name(V));

    fprintf(file,"MUGT%d(MUGHStEntry)\n",Vh);
    fprintf(file,"struct MUGStEntry *MUGHStEntry;\n");
    fprintf(file,"{\n");
    fprintf(file,"\t%s *MUGEntry;\n",TermName);
    fprintf(file,"\tMUGHStEntry->MUGElem=%d;\n",Vh);
    fprintf(file,"\tMUGEntry=(%s *)ALLOC(sizeof(%s));\n",TermName,TermName);
    fprintf(file,"#ifdef READpr\n");
    fprintf(file,"\tREAD%s(MUGRCode,MUGCode,MUGZl,MUGSp,MUGEntry);\n",TermName);
    fprintf(file,"#else\n");
    fprintf(file,"\tread%s(MUGToken,MUGEntry);\n",TermName);
    fprintf(file,"#endif\n");
    fprintf(file,"\tMUGHStEntry->MUGEntry=(int *)MUGEntry;\n");
    fprintf(file,"\tMUGPush(MUGHStEntry);\n");
    fprintf(file,"}\n");
}


GenPopPP(file,PP,prodname)
  FILE *file;
  Prodpos PP;
  char *prodname;
/**********************************************************************
 * Generiert ein Pop vom Stack fuer einen Unterbaum                   *
 **********************************************************************/
{
    if (PP==NIL) return;

    GenPopPP(file,NextPPos(PP),prodname);

    if (! Is_Terminal(Grm_Symbol(PP)))
    {
        fprintf(file,"\tMUGPop(&MUGHStEntry);\n");
        fprintf(file,"\tMUGOut->C.%s.%s%d=(struct ",prodname,prodname
            ,PPos_Nummer(PP));
        GenEinType(file,Sym_Name(Grm_Symbol(PP)));
        fprintf(file," *)MUGHStEntry.MUGEntry;\n");
    }
    else 
    if (Is_Semantisch(Grm_Symbol(PP)))
    {
        fprintf(file,"\tMUGPop(&MUGHStEntry);\n");
        fprintf(file,"\tMUGOut->C.%s.%s%d=",prodname,prodname,PPos_Nummer(PP));
        fprintf(file,"(%s *)MUGHStEntry.MUGEntry;\n"
            ,SymString(Sym_Name(Grm_Symbol(PP))));
    }
}


GenPProc(file,P)
  FILE *file;
  Product P;
/**********************************************************************
 * Generiert eine Einleseprozedur fuer eine Produktion                *
 **********************************************************************/
{
    int AnzTerm;
    Prodpos PP;
    char *prodname;
    Entry prod;

    AnzTerm=CardTerm();
    prodname=SymString(Prod_Name(P));
    prod=Sym_Name(Grm_Symbol(FirstPPos(P)));

    fprintf(file,"MUGP%d()\n",P);
    fprintf(file,"{\n");
    fprintf(file,"\tstruct ");
    GenEinType(file,prod);
    fprintf(file," *MUGOut;\n");
    fprintf(file,"\tstruct MUGStEntry MUGHStEntry;\n");
    fprintf(file,"\n");
    fprintf(file,"\tMUGOut=(struct ");
    GenEinType(file,prod);
    fprintf(file," *)ALLOC(sizeof(struct ");
    GenEinType(file,prod);
    fprintf(file,"));\n");
    fprintf(file,"\tMUGOut->prodnum=%d;\n",P);
    
    GenPopPP(file,NextPPos(FirstPPos(P)),prodname);

    fprintf(file,"\tMUGHStEntry.MUGElem=%d;\n",P+AnzTerm+1);
    fprintf(file,"\tMUGHStEntry.MUGEntry=(int *)MUGOut;\n");
    fprintf(file,"\tMUGPush(&MUGHStEntry);\n");
    fprintf(file,"}\n");
}

GenTrProc(file)
  FILE *file;
/**********************************************************************
 * Generiert alle Terminal und Produktionseinleseprozeduren           *
 **********************************************************************/
{
    Vocabel V;
    Product P;

    for    (V=FirstSym();V!=NIL;V=NextSym(V))
        if (Is_Terminal(V))
            if (Is_Semantisch(V))
                GenTProc(file,V),fprintf(file,"\n");

    for    (V=FirstSym();V!=NIL && !Is_Terminal(V);V=NextSym(V))
        for (P=FirstProd(V);P!=NIL;P=NextProd(P))
            GenPProc(file,P),fprintf(file,"\n");
}


GenPTCons(file)
  FILE *file;
/**********************************************************************
 * Generiert die Aufrufprozeduren fuer die Produktions- und Terminal- *
 * Konstruktoren                                                      *
 **********************************************************************/
{
    Vocabel V,Vh;
    int AnzNonterm;
    int AnzTerm;
    Product P;

    fprintf(file,"MUGProdCons (ProdNum)\n");
    fprintf(file,"int ProdNum;\n");
    fprintf(file,"{\n");
    fprintf(file,"\tswitch (ProdNum)\n");
    fprintf(file,"\t{\n");

    for (P=FirstProduct();P!=NIL;P=NextProduct(P))
        fprintf(file,"\t\tcase  %d : MUGP%d(); break;\n",P,P);

    fprintf(file,"\t}\n");
    fprintf(file,"}\n\n");

    fprintf(file,"MUGTermCons (Terminal)\n");
    fprintf(file,"int Terminal;\n");
    fprintf(file,"{\n");
    fprintf(file,"\tswitch (Terminal)\n");
    fprintf(file,"\t{\n");

    AnzNonterm=CardNonterm();
    AnzTerm=CardTerm();

    /* Erstes Terminal suchen */
    for (V=FirstSym();V!=NIL && !Is_Terminal(V);V=NextSym(V));

    for (;V!=NIL;V=NextSym(V))
    {
        Vh=V-AnzNonterm;
        fprintf(file,"\t\tcase  %d :",Vh);
        if (Is_Semantisch(V))
            fprintf(file," MUGT%d(&MUGHStEntry);",Vh);
        fprintf(file," break;\n");
    }

    fprintf(file,"\t}\n");
    fprintf(file,"}\n\n");
}


GenBaumbau(file)
  FILE *file;
/**********************************************************************
 * Generiert Hauptprozedur, die den zu attributierenden Baum erstellt *
 **********************************************************************/
{
    fprintf(file,"int %sBAUMAUFBAU(argc,argv,input,MUGOut)\n",PhasenName);
    fprintf(file,"int argc; char *argv[];");
    fprintf(file,"char *input;struct ");
    GenEinType(file,Sym_Name(FirstSym()));
    fprintf(file," **MUGOut;\n");
    fprintf(file,"{\n");
    fprintf(file,"\tMUGInitSt();\n");
    fprintf(file,"\tMUGANALYSATOR(argc,argv,input);\n");
    fprintf(file,"\tif (MUGErrNum==0)\n");
    fprintf(file,"\t{\n");
    fprintf(file,"\t\tMUGPop(&MUGHStEntry);\n");
    fprintf(file,"\t\t*MUGOut=(struct ");
    GenEinType(file,Sym_Name(FirstSym()));
    fprintf(file," *)MUGHStEntry.MUGEntry;\n");
    fprintf(file,"\t}\n");
    fprintf(file,"\tfree(MUGSt);\n");
    fprintf(file,"\treturn(MUGErrNum);\n");
    fprintf(file,"}\n\n");
}

/*
GenAnalysator(file)
  FILE *file;
 **********************************************************************
 * Generiert Analysator, der aus vom Parser gelieferten File eine     *
 * Baumstruktur erstellt.                                             * 
 * (durch Aufrufe von MUGTermCons und MUGProdCons)                    *
 **********************************************************************
{

    fprintf(file,"MUGCtrl(input,s)\n");
    fprintf(file,"FILE *input;char s[];\n");
    fprintf(file,"{ char hc; int i;\n");
    fprintf(file,"\tfscanf(input,\"%cc\\n\",&hc);\n",37);
    fprintf(file,"\ti=0;\n");
    fprintf(file,"\tdo  if (s[i]==hc) return(0);\n");
    fprintf(file,"\twhile (s[++i]!=\'\\0\');\n");
    fprintf(file,"\treturn(1);\n");
    fprintf(file,"}\n\n");
    
    fprintf(file,"MUGANALYSATOR(MUGRFolge)\n");
    fprintf(file,"FILE *MUGRFolge;\n");
    fprintf(file,"{\n");
    fprintf(file,"\tchar MUGC;\n");
    fprintf(file,"\tint  MUGI;\n");
    fprintf(file,"\tMUGAccepted=  0;\n");
    fprintf(file,"\tMUGErrNum = MUGCtrl(MUGRFolge,\"Bb\");\n");
    fprintf(file,"\twhile (! (MUGAccepted || MUGErrNum!=0))\n");
    fprintf(file,"\t{\n");
    fprintf(file,"\t\tfscanf(MUGRFolge,\"%cc\\n\",&MUGC);\n",37);
    fprintf(file,"\t\tswitch (MUGC)\n");
    fprintf(file,"\t\t{\n");
    fprintf(file,"\t\t\tcase \' \' : continue;\n");
    fprintf(file,"\t\t\tcase \'%c\' :\n",LCentry); 
    fprintf(file,"\t\t\tcase \'%c\' :\n",entry); 
    fprintf(file,"\t\t\tcase \'%c\' :\n",LCerror); 
    fprintf(file,"\t\t\tcase \'%c\' :\n",error); 
    fprintf(file,"\t\t\tcase \'%c\' :\n",LCfterror);
    fprintf(file,"\t\t\tcase \'%c\' : MUGErrNum=1; break;\n",fterror);
    fprintf(file,"\t\t\tcase \'%c\' :\n",LCaccept);
    fprintf(file,"\t\t\tcase \'%c\' : MUGAccepted=1; break;\n",accept);
    fprintf(file,"\t\t\tcase \'%c\' :\n",LCreduce);
    fprintf(file,"\t\t\tcase \'%c\' : fscanf(MUGRFolge,\"%cd\\n\",&MUGI);\n",reduce,37);
    fprintf(file,"\t\t\t              MUGProdCons(MUGI); break;\n");
    fprintf(file,"\t\t\tcase \'%c\' :\n",LCshift);
    fprintf(file,"\t\t\tcase \'%c\' : fscanf(MUGRFolge,\"%cd\\n\",&MUGI);\n",shift,37);
    fprintf(file,"\t\t\t           fscanf(MUGRFolge,\"%cd\\n\",&MUGRCode);\n",37);
    fprintf(file,"\t\t\t           fscanf(MUGRFolge,\"%cd\\n\",&MUGCode);\n",37);
    fprintf(file,"\t\t\t           fscanf(MUGRFolge,\"%cd\\n\",&MUGZl);\n",37);
    fprintf(file,"\t\t\t           fscanf(MUGRFolge,\"%cd\\n\",&MUGSp);\n",37);
    fprintf(file,"\t\t\t           MUGTermCons(MUGI-MUGCMinT); break;\n");
    fprintf(file,"\t\t\tdefault : MUGErrNum=1;\n");
    fprintf(file,"\t\t}\n");
    fprintf(file,"\t}\n");
    fprintf(file,"}\n");
}
*/

GenAnalyseKonstruktoren(file)
  FILE *file;
/**********************************************************************
 * Generiert Analyse-Konstruktoren                                    *
 **********************************************************************/
{
    GenStDekl(file);
    GenStProc(file);
    GenTrProc(file);
    GenPTCons(file);
    GenBaumbau(file);
}


GenProdnum(file)
  FILE *file;
/**********************************************************************
 * Generiert ein fuer (evtl.) Vorgaenger notwendiges File mit Produktions
 * nummern. Dies ist notwendig, da dieser aus den syntaktischen Funktionen
 * nicht auf die Produktionsnummer schliessen kann.                   *
 **********************************************************************/
{
    Vocabel V;
    Product P;

    for (V=FirstSym();V!=NIL;V=NextSym(V))
        for (P=FirstProd(V);P!=NIL;P=NextProd(P))
        {
            fprintf(file,"#define ");
            GenEinType(file,Prod_Name(P));
            fprintf(file,"pn %d\n",Prod_Nummer(P));
        }
}
        

Gen_Desk(file)
  FILE *file;
/**********************************************************************
 * Phasenname,Ein- und Ausgabegrammatikname in ein File schreiben     *
 **********************************************************************/
{
    fprintf(file,"%s %s %s \0",SymString(GetPhasenId())
        ,SymString(GetInGName()),SymString(GetOutGName()));
}

EingabeBaumRep()
/**********************************************************************
 * Files fuer Aufbau des Baumes generieren                            *
 **********************************************************************/
{
    FILE *AnalyseTypen;
    FILE *AnalyseVariable;
    FILE *AnalyseKonstruktoren;
 /* FILE *BaumEingabe; */
 /* FILE *QuellEingabe; */
    FILE *prodnum;
    FILE *desk_file;/* Fuer Kombinator */

    PhasenName=SymString(GetPhasenId());

    /* File AnalyseTypen.c oeffen */
    sprintf(hstring,"%s_ATyp.c",PhasenName);
    AnalyseTypen=(FILE *)FOpen(hstring,"w");

    /* File AnalyseVariable.c oeffnen */
    sprintf(hstring,"%s_AVar.c",PhasenName);
    AnalyseVariable=(FILE *)FOpen(hstring,"w");

    /* File AnalyseKonstruktoren.c oeffnen */
    sprintf(hstring,"%s_AKonstr.c",PhasenName);
    AnalyseKonstruktoren=(FILE *)FOpen(hstring,"w");

    /* File BaumEingabe.c oeffnen */
 /* sprintf(hstring,"%s_BEing.c",PhasenName); */
 /* BaumEingabe=(FILE *)FOpen(hstring,"w"); */

    /* File QuellEingabe.c oeffnen */
 /* sprintf(hstring,"%s_QEing.c",PhasenName); */
 /* QuellEingabe=(FILE *)FOpen(hstring,"w"); */

    /* File fuer Vorangehende phase, die Produktionsnummern braucht, oeffnen */
    sprintf(hstring,"%s_Prodnum.c",PhasenName);
    prodnum=(FILE *)FOpen(hstring,"w");

    /*Hilfsfile in dem Phasenname, Ein- und Ausgabegram.name eingetragen werden */
    sprintf(hstring,"%s.Desk",PhasenName);
    desk_file=(FILE *) fopen (hstring,"w");

    fprintf(AnalyseTypen,"          /* Analyse Typen der Phase %s */\n",PhasenName);
    fprintf(AnalyseTypen,"          /* ======================= */\n\n");

    GenAnalyseTypen(AnalyseTypen);

    fprintf(AnalyseVariable,"          /* Analyse Variable der Phase %s */\n"
        ,PhasenName);
    fprintf(AnalyseVariable,"          /* ========================== */\n\n");

    GenAnalyseVariable(AnalyseVariable);

    fprintf(AnalyseKonstruktoren,"          /* Analyse Konstruktoren der Phase %s */\n"
        ,PhasenName);
    fprintf(AnalyseKonstruktoren,"          /* =============================== */\n\n");

    GenAnalyseKonstruktoren(AnalyseKonstruktoren);

 /* GenAnalysator(BaumEingabe); */

    fprintf(prodnum,"          /* Produktionsnummer der Phase %s */\n",PhasenName);
    fprintf(prodnum,"          /* =========================== */\n\n");

    GenProdnum(prodnum);

    Gen_Desk(desk_file);    

    fclose(AnalyseTypen);
    fclose(AnalyseVariable);
    fclose(AnalyseKonstruktoren);
    fclose(prodnum);
    fclose(desk_file);
}


/*********************************************************************
 *                                                                   *
 *                 A U S G A B E B A U M R E P                       *
 *                 ===========================                       *
 *                                                                   *
 *********************************************************************/

bool *TypesDone;

GenSyntaktTypen(file)
  FILE *file;
{
    Funct F,Fh;
    Fparam Fp;
    int i;    
    Typ T,Th;

    if ((TypesDone=(bool *)calloc(CardTyp()+1,sizeof(bool)))==NULL)
        printf("Zuwenig Speicher !\n"),exit(1);

    for (F=FirstFunct();F!=NIL ;F=NextFunct(F))
    {
	if (FirstFErg(F) == 0) continue;
        if (Is_SynTTyp(T=Typ_Of_Fparam(FirstFErg(F))))
            if (!TypesDone[T]) 
            {    
                TypesDone[T]=TRUE;
                fprintf(file,"struct ");
                GenAusType(file,Typ_Name(T));
                fprintf(file,"{\n");
                fprintf(file,"\tshort prodnum;\n");
                fprintf(file,"\tstruct ");
                GenAusNNType(file,Typ_Name(T));
                fprintf(file," NN;\n");

                fprintf(file,"\tunion {\n");
                for (Fh=FirstFunct();Fh!=NIL;Fh=NextFunct(Fh))
                {
                    if (FirstFPar(Fh)!=NIL) 
                    /* leere struct erzeugt Fehlermeldung des C-Compilers */
                    /* und m_ nicht aufgefuehrt werden,da es nie addressiert */
                    /* werden darf ! */
                    {
                        if (T==Typ_Of_Fparam(FirstFErg(Fh)))
                        {
                            fprintf(file,"\t\tstruct {\n");
                            for (Fp=FirstFPar(Fh),i=1;Fp!=NIL;Fp=NextFPar(Fp),i++)
                            {    
                                if (Is_SynTTyp(Th=Typ_Of_Fparam(Fp)))
                                {
                                    fprintf(file,"\t\t\tstruct ");
                                    GenAusType(file,Typ_Name(Th));
                                    fprintf(file," *%s%d;\n"
                                        ,SymString(Funkt_Name(Fh)),i);
                                }
                                else
                                {
                                    fprintf(file,"\t\t\t%s"
                                        ,SymString(Typ_Name(Th)));
                                    fprintf(file," *%s%d;\n"
                                        ,SymString(Funkt_Name(Fh)),i);
                                }
                            }    
                            fprintf(file,"\t\t} %s;\n"
                                ,SymString(Funkt_Name(Fh)));
                        }
                    }    
                }    
                fprintf(file,"\t} C;\n");
                fprintf(file,"};\n");
            }    
    }    
    free(TypesDone);
}    
    
/*********************************************************************/
GenAusgabeVariable(file)
  FILE *file;
{
    Typ T;

    if (Is_SynTTyp(T=Typ_Of_Attr(FirstAttr(FirstSym()))))
    {
        fprintf(file,"struct ");
        GenAusType(file,Typ_Name(T));
    }
    else 
    if (Is_SemTTyp(T))
        fprintf(file,"%s",SymString(Typ_Name(T)));
    else /* CTYP */
        fprintf(file,"%s",SymString(Typ_Name(T)));

    fprintf(file," *%sOUT;\n",PhasenName);

}

/*********************************************************************/

    
GenFparamsDekl(file,SynFunct)
  FILE *file;
  Funct SynFunct;
{    
        Fparam par;    
        int parnr;    
    
        for (par=FirstFPar(SynFunct),parnr=1;par!=NIL;par=NextFPar(par),parnr++)
                    fprintf(file," INO%d,",parnr);
}

/*********************************************************************/

GenFErgDekl(file,SynFunct)
  FILE *file;
  Funct SynFunct;
{
        fprintf(file," OUT1");
}

/*********************************************************************/

    
GenFparamsSpez(file,SynFunct)
  FILE *file;
  Funct SynFunct;
{    
        Fparam par;    
        int parnr;    
	Typ T;
    
        for (par=FirstFPar(SynFunct),parnr=1;par!=NIL;par=NextFPar(par),parnr++)
        {
                if (Is_SynTTyp(T=Typ_Of_Fparam(par)))
                {   fprintf(file,"struct ",parnr);
                    GenAusType(file,Typ_Name(T));
                    fprintf(file," *INO%d;\n",parnr);
                }
                else
		{   DruckeSym(file,Typ_Name(T));
                    fprintf(file," INO%d;\n",parnr);
                }
        }
}

/*********************************************************************/

GenFErgSpez(file,SynFunct)
  FILE *file;
  Funct SynFunct;
{
        fprintf(file,"struct ");
        GenAusType(file,Typ_Name(Typ_Of_Fparam(FirstFErg(SynFunct))));
        fprintf(file," **OUT1;\n");
}

/*********************************************************************/

GenFBody(file,SynFunct)
  FILE *file;
  Funct SynFunct;
{
        Fparam par;
        int parnr;
        Entry hEnt;

        fprintf(file,"{\n\tstruct ");
        GenAusType(file,hEnt=Typ_Name(Typ_Of_Fparam(FirstFErg(SynFunct))));
        fprintf(file," *OUTVar;\n");
        fprintf(file,"\tOUTVar=(struct ");
        GenAusType(file,hEnt);
        fprintf(file," *)ALLOC(sizeof(struct ");
        GenAusType(file,hEnt);
        fprintf(file,"));\n");
        fprintf(file,"\tOUTVar->prodnum=");
        GenAusType(file,Funkt_Name(SynFunct));
        fprintf(file,"pn;\n");
        
        for (par=FirstFPar(SynFunct),parnr=1;par!=NIL;par=NextFPar(par),++parnr)
        {
                if (Is_SynTTyp(Typ_Of_Fparam(par)))
                        fprintf(file,"\tOUTVar->C.");
                else
                {
                        fprintf(file,"\tOUTVar->C.");
                        DruckeSym(file,hEnt=Funkt_Name(SynFunct));
                        fprintf(file,".");
                        DruckeSym(file,hEnt);
                        fprintf(file,"%d=(",parnr);
                        DruckeSym(file,hEnt=Typ_Name(Typ_Of_Fparam(par)));
                        fprintf(file," *)ALLOC(sizeof(");
                        DruckeSym(file,hEnt);
                        fprintf(file,"));\n");
                        fprintf(file,"\t*OUTVar->C.");
                }
                DruckeSym(file,hEnt=Funkt_Name(SynFunct));
                fprintf(file,".");
                DruckeSym(file,hEnt);
                fprintf(file,"%d=INO%d;\n",parnr,parnr);
        }
        fprintf(file,"\t*OUT1=OUTVar;\n");        
        fprintf(file,"}\n\n");
}                                                       

/*********************************************************************/

GenFHead(file,SynFunct)
  FILE *file;
  Funct SynFunct;
{
        DruckeSym(file,Funkt_Name(SynFunct));

        fprintf(file,"(");
        GenFparamsDekl(file,SynFunct);
        GenFErgDekl(file,SynFunct);
        fprintf(file,")\n");

        GenFparamsSpez(file,SynFunct);
        GenFErgSpez(file,SynFunct);
}

/*********************************************************************/
        
GenSyntaktKonstruktoren(file)
  FILE *file;
{
        Funct SynFunct;

        for (SynFunct=FirstFunct();SynFunct!=NIL;SynFunct=NextFunct(SynFunct))
                if (Is_SynFunct(SynFunct))
                {
                        GenFHead(file,SynFunct);
                        GenFBody(file,SynFunct);
                }
}

/*****************************************************************/

GenDummyProdnum(file)
  FILE *file;
{
    Funct F;
    int i;

    i=0;
    for (F=FirstFunct();F!=NIL;F=NextFunct(F))
        if (Is_SynFunct(F))
        {
            fprintf(file,"#define ");
            GenAusType(file,Funkt_Name(F));
            fprintf(file,"pn %d\n",i++);
        }
}
        


/********************************************************************/
AusgabeBaumRep()
{
    FILE *SyntaktTypen;
    FILE *SyntaktVariable;
    FILE *SyntaktKonstruktoren;
    FILE *dummyprodnum;

    PhasenName=SymString(GetPhasenId());

    /* File SyntTypen.c oeffen */
    sprintf(hstring,"%s_STyp.c",PhasenName);
    SyntaktTypen=(FILE *)FOpen(hstring,"w");

    /* File SyntVariable.c oeffnen */
    sprintf(hstring,"%s_SVar.c",PhasenName);
    SyntaktVariable=(FILE *)FOpen(hstring,"w");

    /* File SyntKonstruktoren.c oeffnen */
    sprintf(hstring,"%s_SKonstr.c",PhasenName);
    SyntaktKonstruktoren=(FILE *)FOpen(hstring,"w");

    /* File fuer Produktionsnummern oeffnen */
    sprintf(hstring,"%s_DummyPN.c",PhasenName);
    dummyprodnum=(FILE *)FOpen(hstring,"w");

    fprintf(SyntaktTypen,"          /* Syntaktische Typen der Phase %s */\n",PhasenName);
    fprintf(SyntaktTypen,"          /* ============================ */\n\n");

    GenSyntaktTypen(SyntaktTypen);

    fprintf(SyntaktVariable,"          /* Ausgabe Variable der Phase %s */\n",PhasenName);
    fprintf(SyntaktVariable,"          /* =============================== */\n\n");

    GenAusgabeVariable(SyntaktVariable);

    fprintf(SyntaktKonstruktoren,"          /* Syntaktische Konstruktoren der Phase %s */\n"
        ,PhasenName);
    fprintf(SyntaktKonstruktoren,"          /* ==================================== */\n\n");

    GenSyntaktKonstruktoren(SyntaktKonstruktoren);

    fprintf(dummyprodnum,"          /* Dummy Produktionsnummern der Phase %s */\n",PhasenName);
    fprintf(dummyprodnum,"          /* fuer syntaktische Funkt.,falls diese Phase die letzte ist. */\n");
    fprintf(dummyprodnum,"          /* ========================================================= */\n\n");

    GenDummyProdnum(dummyprodnum);

    fclose(SyntaktTypen);
    fclose(SyntaktVariable);
    fclose(SyntaktKonstruktoren);
    fclose(dummyprodnum);
}
