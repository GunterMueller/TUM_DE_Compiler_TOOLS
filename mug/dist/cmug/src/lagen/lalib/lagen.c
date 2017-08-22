/************************************************************************************************
 *												*
 *		LAttribut-Auswerter-Generator  fuer das MUG-System				*
 *												*
 *			von VS-Pascal nach C uebertragen ,	(PMLRGEN)			*
 *												*
 ************************************************************************************************/

#define MaxAttr   255
/* Max. Anzahl verschiedener Attribute    */
#define MaxPLength 1000
/* Max Anzahl der Vokabeln der rechten Seiten einer Produktion */

#define EVREFERENZ   1  /* wird uebergeben, wenn evtl. die Adresse (des Attributs) gebraucht wird */
#define EVDEREFERENZ 2  /* wird uebergeben, wenn evtl. der *-Operator angewendet werden muss */
#define REFERENZ     3  /* wird uebergeben, wenn die Adresse (des Attributs) gebraucht wird */
#define DEREFERENZ   4  /* wird uebergeben, wenn der *-Operator angewendet werden muss */

#include <stdio.h>
#include "zufunc.h"	  /* Zugriffsfunktionen auf die Internform der Grammatik */

/*********************************************************************************/
#define  PLength  int				  /* modul-lokale Vereinbarungen */
#define  PHASENID INPAR 
/* typedef int attrs; */
static int 	FehlerNr;
/**********************************************************************************
  zur Compilierung eingefuerte Konstanten 			*/

static char  *mug	= "MUG";
static char  *Intree 	= "Knoten";
static char  *RecCase	= "PA";		

/* Globale Variablenvereinbarungen */
int          ErrorNum,ErrorTop;
Attrpos      ErrorAttr,ErrorStack[MaxAttr];
Product	     ErrorProd;
static FILE *ErrProt=NULL;
static FILE *Scratch;
Entry        PhasenId;

static char String[20000];      /* Zwischenspeicher fuer den erzeugten Code: um laestige Aenderungen
				   im Algorithmus zu vermeiden, wird der Code fuer jedes Nonterminal
				   in diesen String geschrieben, da die lokalen Variablen durch den
				   Algorithmus erst danach erzeugt, im fertigen Programmtext aber
				   natuerlich zuvor benoetigt werden. Sind die Variablen erzeugt,
				   wird der Inhalt von String geschrieben. */


typedef struct AffixListe {
  Entry              AttrName;
  Entry              Name;
  PLength            Index;
  Attr               AttrTyp;
  bool               Generiert;
  bool               SemEingetragen;
  struct AffixListe *Next;
} *AffixPtr;


typedef struct LocVarList {
  Entry              Variable;
  int                VarInd;
  Attr               VarTyp;
  struct LocVarList *NextVar;
} *VarList;


typedef struct ProdInf {
  AffixPtr P;
  Attr	   AnzAttr;
  Attr     AnzOutAttr;
  Attr     AnzAffix;
} ProdInform[MaxPLength+1];


typedef struct SemInf  {
  Attrpos Regel;
  bool    Bearbeitet;
  Attr    Inkarn;
} SemInform[MaxAttr+1];


#if defined(__STDC__) || defined(__cplusplus)
# define P_(s) s
#else
# define P_(s) ()
#endif

bool InVarList P_((VarList FirstVarList, int AnzVar, Entry Affix, int Index));
void LAuswerterGen P_((void));

#undef P_



#ifdef __STDC__
static void PushErrRule(Attrpos Rule)
#else /* ! __STDC__ */
static void PushErrRule(Rule)
  Attrpos  Rule;	
#endif /* ! __STDC__ */
{
  ErrorStack[++ErrorTop]=Rule;
}



#ifdef __STDC__
static void NewErrorStack(void)
#else /* ! __STDC__ */
static void NewErrorStack()
#endif /* ! __STDC__ */
{
  ErrorTop=0;
}



#ifdef __STDC__
static void PutErrAttr(FILE *ErrProt, Attrpos ErrAttr)
#else /* ! __STDC__ */
static void PutErrAttr(ErrProt,ErrAttr)
  FILE    *ErrProt;
  Attrpos  ErrAttr;	 
#endif /* ! __STDC__ */
{
  DruckeSym(ErrProt,Sym_Name(Grm_Symbol (PPos_Of_AttPos (ErrAttr)))); 
  fprintf(ErrProt,"<%d>.",PPos_Nummer(PPos_Of_AttPos(ErrAttr))); 
  DruckeSym(ErrProt,Attr_Name(Attr_Of_AttPos(ErrAttr))); 
}



#ifdef __STDC__
static void PutErrRule(FILE *ErrProt, Attrpos ErrRule)
#else /* ! __STDC__ */
static void PutErrRule(ErrProt,ErrRule)
  FILE    *ErrProt;
  Attrpos  ErrRule;
#endif /* ! __STDC__ */
{
  Aparam ErrList;
  int    FormInd;
  bool   mehrfach;
  
  ErrList=FirstErg(Ber_Aufruf(ErrRule));
  mehrfach=(bool)NextErg(ErrList);
  if (mehrfach)
    fprintf(ErrProt,"(");
  PutErrAttr(ErrProt,AttPos_Of_Param(ErrList));
  for (ErrList=NextErg(ErrList),FormInd=1;ErrList;ErrList=NextErg(ErrList))
  { 
    fprintf(ErrProt,",");                     
    if (FormInd>6)
    {
      fprintf(ErrProt,"\n");
      FormInd=1;
    }
    else
      FormInd++;
    PutErrAttr(ErrProt,AttPos_Of_Param(ErrList));
  }
  if (mehrfach)
    fprintf(ErrProt,") = ");
  else 
    fprintf(ErrProt," = ");
  DruckeSym(ErrProt,B_Funktion(Ber_Aufruf(ErrRule)));
  fprintf(ErrProt,"(");                            
  ErrList=FirstArg(Ber_Aufruf(ErrRule));
  FormInd=1;
  while (ErrList)
  {
    if (FormInd>6)
    {
      fprintf(ErrProt,"\n");
      FormInd=1;
    }
    else
      FormInd++;
    PutErrAttr(ErrProt,AttPos_Of_Param(ErrList));
    ErrList=NextErg(ErrList);
    if (ErrList)
      fprintf (ErrProt, "," );                    
  }
  fprintf(ErrProt,")");
}



#ifdef __STDC__
static void PutErrProd(FILE *ErrProt, Product ErrProd)
#else /* ! __STDC__ */
static void PutErrProd(ErrProt,ErrProd)
  FILE    *ErrProt;
  Product  ErrProd;
#endif /* ! __STDC__ */
{
  Prodpos ErrPos;
  int     FormInd;

  ErrPos=FirstPPos(ErrProd);
  DruckeSym(ErrProt,Sym_Name(Grm_Symbol(ErrPos)));
  fprintf(ErrProt,"<0> -> ");
  for (ErrPos=NextPPos(ErrPos),FormInd=1;ErrPos;ErrPos=NextPPos(ErrPos))
  {
    if (FormInd>6)
    {
      fprintf(ErrProt,"\n");
      FormInd=1;
    }
    else
      FormInd++;
    DruckeSym(ErrProt,Sym_Name(Grm_Symbol(ErrPos)));
    fprintf(ErrProt,"<%d> ",PPos_Nummer(ErrPos));     
  }
  fprintf(ErrProt,".");
}



#ifdef __STDC__
static void ErrorHandling(void)
#else /* ! __STDC__ */
static void ErrorHandling()
#endif /* ! __STDC__ */
{
  if (!ErrProt)
  {
    char filenamen[100];

    strcpy(filenamen,SymString(PhasenId));
    strcat(filenamen,"L.ERR");
    ErrProt=fopen(filenamen,"w");
  }

  switch(ErrorNum)
  {
  case 1 :
    fprintf(ErrProt,"Unzulaessige Abhaengigkeit des Attributes : ");
    PutErrAttr(ErrProt,ErrorAttr);
    fprintf(ErrProt," in der Regel\n");
    PutErrRule(ErrProt,ErrorStack[ErrorTop]);
    fprintf(ErrProt,"\nin der Produktion ");    
    PutErrProd(ErrProt,ErrorProd);
    fprintf(ErrProt,"\n-----------------------\n"); 
    break;

  case 2:
    fprintf(ErrProt,"Zyklische Abhaengigkeit des Attributes : ");
    PutErrAttr(ErrProt,ErrorAttr);
    fprintf(ErrProt," in den Regeln\n");
    for (;ErrorTop;ErrorTop--)
    {
      PutErrRule(ErrProt,ErrorStack[ErrorTop]);
      fprintf(ErrProt,"\n");
     }
    fprintf(ErrProt,"in der Produktion ");    
    PutErrProd(ErrProt,ErrorProd);
    fprintf(ErrProt,"\n-----------------------\n"); 
  }
  FehlerNr=1;
  ErrorNum=0;
  NewErrorStack();
}



#ifdef __STDC__
static char *LastStringPosition(void)
#else /* ! __STDC__ */
static char *LastStringPosition()
#endif /* ! __STDC__ */
{
  char *p;

  for (p=String;*p;p++);
  return(p);
}


#ifdef __STDC__
static void GENEINTYPE(FILE *file, Entry Par)
#else /* ! __STDC__ */
static void GENEINTYPE(file,Par)
FILE *file;
Entry Par;
#endif /* ! __STDC__ */
{	fprintf(file,"%s%s",SymString(GetInGName()),SymString(Par));  	}
 
#ifdef __STDC__
static GENAUSTYPE(FILE *file, Entry Par)
#else /* ! __STDC__ */
static GENAUSTYPE(file,Par)
FILE *file;
Entry Par;
#endif /* ! __STDC__ */
{	fprintf(file,"%s%s",SymString(GetOutGName()),SymString(Par));	}
 

#ifdef __STDC__
static void GenCompProc(void)
#else /* ! __STDC__ */
static void GenCompProc()
#endif /* ! __STDC__ */
{ Typ T;

    fprintf(Scratch,"\n\n\nvoid %sCOMPILER(EINGABEBAUM,AUSGABEBAUM)\n",
		    SymString(GetPhasenId()));
    fprintf(Scratch,"struct ");
    GENEINTYPE(Scratch,Sym_Name(FirstSym()));
    fprintf(Scratch," *EINGABEBAUM;\n");

    if (Is_SynTTyp(T=Typ_Of_Attr(FirstAttr(FirstSym()))))
    {
        fprintf(Scratch,"struct ");
        GENAUSTYPE(Scratch,Typ_Name(T));
    }
    else
    if (Is_SemTTyp(T))
        fprintf(Scratch,"%s",SymString(Typ_Name(T)));
    else /* CTYP */
        fprintf(Scratch,"%s",SymString(Typ_Name(T)));

    fprintf(Scratch," **AUSGABEBAUM;\n");
  fprintf(Scratch,"{\n   %s%s",mug,SymString(Sym_Name(FirstSym())));
  fprintf(Scratch,"(EINGABEBAUM,AUSGABEBAUM);\n}\n");
}



#ifdef __STDC__
static void GenPrototypes(void)
#else /* ! __STDC__ */
static void GenPrototypes()
#endif /* ! __STDC__ */
{
  Vocabel Nt;

  for (Nt=FirstSym();Nt;Nt=NextSym(Nt))
    if (!Is_Terminal(Nt))
      fprintf(Scratch,"void %s%s();\n",mug,SymString(Sym_Name(Nt)));
  fprintf(Scratch,"\n");
}



#ifdef __STDC__
static void GenNNTypen(void)
#else /* ! __STDC__ */
static void GenNNTypen()
#endif /* ! __STDC__ */
{
  FILE   *NNTypen;
  char    filenamen[100];
  Vocabel OutNt;

  strcpy(filenamen,SymString(PhasenId));
  strcat(filenamen,"_NNTypen.c");
  NNTypen=fopen(filenamen,"w");
  for (OutNt=FirstSym();OutNt;OutNt=NextSym(OutNt))
    if (!Is_Terminal(OutNt))
      fprintf(NNTypen,"struct %s%sNN {char   Dummy; };\n",SymString(GetInGName()),SymString(Sym_Name(OutNt)));
  fclose(NNTypen);
}



#ifdef __STDC__
static void VarListFirst(VarList *PtrFirstVarList, VarList *PtrLastVarList)
#else /* ! __STDC__ */
static void VarListFirst(PtrFirstVarList,PtrLastVarList)
  VarList *PtrFirstVarList;
  VarList *PtrLastVarList;
#endif /* ! __STDC__ */
{
  (*PtrFirstVarList) = (VarList)malloc(sizeof(struct LocVarList));
  (*PtrFirstVarList)->NextVar = NULL;
  *PtrLastVarList = *PtrFirstVarList;
}



#ifdef __STDC__
static void VarListNext(VarList *PtrLastVarList,
                        Entry Affix,
                        int index,
                        Attr type)
#else /* ! __STDC__ */
static void VarListNext(PtrLastVarList,Affix,index,type)
  VarList *PtrLastVarList;
  Entry    Affix;
  int      index;
  Attr     type;
#endif /* ! __STDC__ */
{
  VarList ListElem;

  if ((*PtrLastVarList)->NextVar==NULL)
  {
    ListElem=(VarList)malloc((unsigned)sizeof(struct LocVarList));
    ListElem->NextVar=NULL;
    (*PtrLastVarList)->NextVar=ListElem;
  }
  *PtrLastVarList=(*PtrLastVarList)->NextVar;
  (*PtrLastVarList)->Variable=Affix;
  (*PtrLastVarList)->VarInd=index;
  (*PtrLastVarList)->VarTyp=type;
}



#ifdef __STDC__
static void NewVarList(VarList *PtrLastVarList,
                       int *PtrAnzVar,
                       VarList FirstVarList)
#else /* ! __STDC__ */
static void NewVarList(PtrLastVarList,PtrAnzVar,FirstVarList)
  VarList *PtrLastVarList,FirstVarList;
  int     *PtrAnzVar;
#endif /* ! __STDC__ */
{
  *PtrLastVarList=FirstVarList;
  *PtrAnzVar=0;
}



#ifdef __STDC__
static void GenRecHead(Vocabel Name)
#else /* ! __STDC__ */
static void GenRecHead(Name)
  Vocabel Name;
#endif /* ! __STDC__ */
{
  Attr	Attribut  ;		
  Typ T;
  
  fprintf(Scratch,"void %s%s",mug,SymString(Sym_Name(Name)));
  fprintf(Scratch,"(%s",Intree);
  for (Attribut=FirstAttr(Name);Attribut;Attribut=NextAttr(Attribut))
    fprintf(Scratch,",%s0",SymString(Attr_Name(Attribut)));
  fprintf (Scratch,")\n");
  fprintf (Scratch, "  struct %s%s\t*%s;\n",SymString(GetInGName()),SymString(Sym_Name(Name)),Intree);
  for (Attribut=FirstAttr(Name);Attribut;Attribut=NextAttr(Attribut))
  {
    if (Is_SynTTyp(T=Typ_Of_Attr(Attribut)))
    {
        fprintf(Scratch,"  struct ");
        GENAUSTYPE(Scratch,Typ_Name(T));
	fprintf(Scratch," *");
    }
    else
        fprintf(Scratch,"  %s ",SymString(Typ_Name(T)));
    if (! Is_Inherited(Attribut))
        fprintf(Scratch,"*");
    fprintf(Scratch,"%s0;\n",SymString(Attr_Name(Attribut)));
  }
}



#ifdef __STDC__
static void PutRecVar (VarList FirstVarList, int AnzVar)
#else /* ! __STDC__ */
static void PutRecVar (FirstVarList, AnzVar)
     VarList   FirstVarList;
     int	    AnzVar;
#endif /* ! __STDC__ */
{
  int 	l;
  Typ   T;
  
  for (l=1;l<=AnzVar;l++)
  {
    FirstVarList=FirstVarList->NextVar;
    if (Is_SynTTyp(T=Typ_Of_Attr(FirstVarList->VarTyp)))
    {
        fprintf(Scratch,"            struct ");
        GENAUSTYPE(Scratch,Typ_Name(T));
    }
    else
        fprintf(Scratch,"            %s",SymString(Typ_Name(T)));
    if (!Is_SynTTyp(T))
      fprintf(Scratch,"  ");
    else fprintf(Scratch," *");
    fprintf(Scratch,"%s%d",SymString(FirstVarList->Variable),FirstVarList->VarInd);
    fprintf(Scratch,";\n");
  }
}



#ifdef __STDC__
static void GenRecVar (int Iteration,
                       int AnzVar,
                       bool Simple,
                       VarList FirstVarList,
                       Product Prod)
#else /* ! __STDC__ */
static void GenRecVar (Iteration, AnzVar, Simple, FirstVarList, Prod)
     int		Iteration, AnzVar;
     bool		Simple;
     VarList	FirstVarList;
     Product	Prod;
     
#endif /* ! __STDC__ */
{
  bool NoVar;
  static bool  unionset;
  NoVar = (AnzVar == 0);
  if (Simple)
  {
    if (!NoVar)
    {
      fprintf(Scratch,"  struct {\n" );
      PutRecVar(FirstVarList,AnzVar);	/* lok. Var. einer Prod.Altern. */
      fprintf(Scratch,"         } %s;\n\n",SymString(Prod_Name(Prod)));
    }
  }
  else 
  {
    if ( (Iteration == 1) && (!NoVar ) || ((!unionset) && (Iteration >1) && (!NoVar)))
    {
      fprintf(Scratch,"  union  {\n");
      unionset=TRUE;
    }
    if (!NoVar)
    {
      if (unionset)
	fprintf(Scratch,"  ");
      fprintf(Scratch,"  struct {\n");
      PutRecVar(FirstVarList,AnzVar);
      if (unionset)
	fprintf(Scratch,"  ");
      fprintf(Scratch,"         } %s",SymString(Prod_Name(Prod)));
      fprintf(Scratch,";\n");
    } 
    if (unionset && NextProd(Prod) == NULL)
    {
      fprintf(Scratch,"         } %s;\n\n",RecCase);
      unionset = FALSE;
    }
  }
}



#ifdef __STDC__
bool InVarList(VarList FirstVarList, int AnzVar, Entry Affix, int index)
#else /* ! __STDC__ */
bool InVarList(FirstVarList, AnzVar, Affix, index)
     VarList	FirstVarList;
     int	AnzVar, index;
     Entry	Affix;
#endif /* ! __STDC__ */
{
  VarList	SearchVar;
  int		L;
  
  SearchVar=FirstVarList->NextVar;
  for (L=1;L<=AnzVar;L++)
  {
    if (((SearchVar->Variable)==Affix) && ((SearchVar->VarInd)==index))
      return(TRUE);
    SearchVar=SearchVar->NextVar;
  }
  return(FALSE);
}



#ifdef __STDC__
static void PutActAttr(AffixPtr Affix,
                       Entry PName,
                       bool Simple,
                       VarList FirstVarList,
                       VarList *PtrLastVarList,
                       int *PtrAnzVar,
                       int Modus)
#else /* ! __STDC__ */
static void PutActAttr(Affix,PName,Simple,FirstVarList,PtrLastVarList,PtrAnzVar,Modus)
  AffixPtr Affix;
  Entry    PName;
  bool     Simple;
  VarList  FirstVarList, *PtrLastVarList;
  int     *PtrAnzVar;
  int      Modus;
#endif /* ! __STDC__ */
{
  if (InVarList(FirstVarList,*PtrAnzVar,Affix->Name,Affix->Index))
  {
    if (Modus==REFERENZ)
      sprintf(LastStringPosition(),"&");
    if (!Simple)
      sprintf(LastStringPosition(),"%s.",RecCase);
    sprintf(LastStringPosition(),"%s.%s",SymString(PName),SymString(Affix->Name));
    sprintf(LastStringPosition(),"%d",Affix->Index); 
  }
  else
  {
    if (Affix->Index != 0)
    {
      if (Modus==REFERENZ)
	sprintf(LastStringPosition(),"&");
      if (!Simple)
	sprintf (LastStringPosition(), "%s.", RecCase);
      sprintf (LastStringPosition(), "%s.%s", SymString(PName), SymString(Affix->Name) );
      sprintf (LastStringPosition(), "%d", Affix->Index);
      (*PtrAnzVar)++;
      VarListNext (PtrLastVarList, Affix->Name, Affix->Index, Affix->AttrTyp);
    }
    else
    {
      if (Modus==REFERENZ && Is_Inherited(Affix->AttrTyp))
	sprintf(LastStringPosition(),"&");
      else if (Modus==EVDEREFERENZ && !Is_Inherited(Affix->AttrTyp))
	sprintf(LastStringPosition(),"*");
      sprintf(LastStringPosition(),"%s",SymString(Affix->Name));
      sprintf(LastStringPosition(),"%d",Affix->Index);
    }
  }
}



#ifdef __STDC__
static void SucheAffix(Attrpos AttPos,
                       AffixPtr *PtrAffix,
                       struct ProdInf *ProdInfo)
#else /* ! __STDC__ */
static void SucheAffix(AttPos, PtrAffix, ProdInfo)
     Attrpos	AttPos;
     AffixPtr	*PtrAffix;
     ProdInform 	ProdInfo;
#endif /* ! __STDC__ */
{
  bool gefunden;
  
  *PtrAffix = ProdInfo[PPos_Nummer(PPos_Of_AttPos(AttPos))].P;
  gefunden = FALSE;
  while ( (!gefunden) && ( (*PtrAffix) != NULL) )
  {
    if ( (*PtrAffix)->AttrName == Attr_Name(Attr_Of_AttPos(AttPos)) )
      gefunden = TRUE;
    else   *PtrAffix = (*PtrAffix)->Next;
  }
  if (!gefunden)
  {
    printf ("\n Attribut ");
    printf ("%s",SymString(Attr_Name(Attr_Of_AttPos(AttPos))) );
    printf (" in Affixliste nicht gefunden \n");
    exit(1);
  }
}



#ifdef __STDC__
static void Initialisierung(Product Prod,
                            int *PtrAnzVar,
                            struct ProdInf *ProdInfo,
                            int *PtrAnzSemRules,
                            VarList *PtrLastVarList,
                            struct SemInf *SemInfo)
#else /* ! __STDC__ */
static void Initialisierung(Prod,PtrAnzVar,ProdInfo,PtrAnzSemRules,PtrLastVarList,SemInfo)
  Product	Prod;
  int		*PtrAnzVar, *PtrAnzSemRules;
  ProdInform  	ProdInfo;
  VarList	*PtrLastVarList;
  SemInform	SemInfo;
#endif /* ! __STDC__ */
{
  Prodpos  Pos;
  Attrpos  Sem;
  Aufruf   Rule;
  Aparam   Ziel;
  bool     TuNix;
  int      i,j;
  AffixPtr Affix, LastAffix;
  
  for (Pos=FirstPPos(Prod);Pos;Pos=NextPPos(Pos))
  {
    i=PPos_Nummer(Pos);
    ProdInfo[i].AnzOutAttr=0;
    ProdInfo[i].AnzAttr = 0;
    Affix=ProdInfo[i].P;
    LastAffix=NULL;
    for (Sem=FirstAPos(Pos);Sem;Sem=NextAPos(Sem))
    {
      ProdInfo[i].AnzAttr++;
      if (ProdInfo[i].AnzAttr>ProdInfo[i].AnzAffix)
      {
	Affix=(AffixPtr)malloc((unsigned)sizeof(struct AffixListe));
	Affix->Next=NULL;
	if (LastAffix) 
	  LastAffix->Next=Affix;
	else
	  ProdInfo[i].P=Affix;
	ProdInfo[i].AnzAffix++;
      }
      Affix->Index=i;
      Affix->AttrName=Attr_Name(Attr_Of_AttPos(Sem));
      Affix->Name=Affix->AttrName;
      Affix->AttrTyp=Attr_Of_AttPos(Sem);
      Affix->SemEingetragen=FALSE;
      Affix->Generiert=( (i==0) && (Is_Inherited(Attr_Of_AttPos(Sem))) );
      if ( (!i && !Is_Inherited(Attr_Of_AttPos(Sem))) ||
	  (i && Is_Inherited(Attr_Of_AttPos(Sem))) )
	ProdInfo[i].AnzOutAttr++;
      LastAffix=Affix;
      Affix=Affix->Next;
    }
    if (i==0)
    {
      for (Sem=FirstAuxPos(Prod);Sem;Sem=NextAuxPos(Sem))
      {
	ProdInfo[i].AnzAttr++;
	if (ProdInfo[i].AnzAttr>ProdInfo[i].AnzAffix)
	{
	  Affix=(AffixPtr)malloc((unsigned)sizeof(struct AffixListe));
	  Affix->Next=NULL;
	  if (LastAffix)
	    LastAffix->Next=Affix;
	  else
	    ProdInfo[i].P=Affix;
	  ProdInfo[i].AnzAffix++;
	}
	Affix->Index=0;
	Affix->AttrName=Attr_Name(Attr_Of_AttPos(Sem));
	Affix->Name=Affix->AttrName;
	Affix->AttrTyp=Attr_Of_AttPos(Sem);
	Affix->SemEingetragen=FALSE;
	Affix->Generiert=FALSE;
	ProdInfo[i].AnzOutAttr++;
	VarListNext(PtrLastVarList,Affix->AttrName,0,Affix->AttrTyp);
	(*PtrAnzVar)++;
	LastAffix=Affix;
	Affix=Affix->Next;
      }
    }
  }

  j=1;
  for (Pos=FirstPPos(Prod);Pos;Pos=NextPPos(Pos))
  {
    for (Sem=FirstAPos(Pos);Sem;Sem=NextAPos(Sem))
    {
      Rule=Ber_Aufruf(Sem);
      if (Rule)
      {
	Ziel=FirstErg(Rule);
	TuNix=FALSE;
	while (Ziel)
	{
	  SucheAffix(AttPos_Of_Param(Ziel),&Affix,ProdInfo);
	  if (Affix->SemEingetragen)
	    TuNix=TRUE;
	  else
	    Affix->SemEingetragen=TRUE;
	  Ziel=NextErg(Ziel);
	}
	if (!TuNix)
	{
	  SemInfo[j].Regel=Sem;
	  SemInfo[j].Bearbeitet=FALSE;
	  SemInfo[j].Inkarn=0;
	  j++;
	}
      }
    }
  }

  for (Sem=FirstAuxPos(Prod);Sem;Sem=NextAuxPos(Sem))
  {
    Rule=Ber_Aufruf(Sem);
    if (Rule)
    {
      Ziel=FirstErg(Rule);
      TuNix=FALSE;
      while (Ziel)
      {
	SucheAffix(AttPos_Of_Param(Ziel),&Affix,ProdInfo);
	if (Affix->SemEingetragen)
	  TuNix=TRUE;
	else
	  Affix->SemEingetragen=TRUE;
	Ziel=NextErg(Ziel);
      }  
      if (!TuNix)
      {
	SemInfo[j].Regel=Sem;
	SemInfo[j].Bearbeitet=FALSE;
	SemInfo[j].Inkarn=0;
	j++;
      }
    }
  }
  
  SemInfo[j].Regel=NULL;
  *PtrAnzSemRules=j-1;
}



#ifdef __STDC__
static void SucheRegel (Attrpos AttPos,
                        Attr *PtrRegelNr,
                        struct SemInf *SemInfo,
                        int AnzSemRules)
#else /* ! __STDC__ */
static void SucheRegel (AttPos, PtrRegelNr, SemInfo, AnzSemRules)
  Attrpos	AttPos;
  Attr		*PtrRegelNr;
  SemInform 	SemInfo;
  int		AnzSemRules;
#endif /* ! __STDC__ */
{
  bool   Gefunden;
  Aparam ErgAttr;

  Gefunden=FALSE;
  *PtrRegelNr=0;

  do 
  {
    (*PtrRegelNr)++;
    ErgAttr = FirstErg (Ber_Aufruf(SemInfo[*PtrRegelNr].Regel));
    while ( (!Gefunden) && (ErgAttr != NULL) )
    {
      Gefunden = (AttPos == AttPos_Of_Param(ErgAttr));
      ErgAttr = NextErg (ErgAttr);
    }
  }
  while ( !(Gefunden || (*PtrRegelNr > AnzSemRules)) );
  if (!Gefunden)
  {
    printf ("\nFehler: Regel fuer Attribut ");
    DruckeSym (stdout, Attr_Name(Attr_Of_AttPos(AttPos)) );
    printf (" von Grammatiksymbol ");
    DruckeSym (stdout, Sym_Name(Grm_Symbol(PPos_Of_AttPos(AttPos))) );
    printf (" nicht gefunden.\n");
    exit(1);
  }
}



#ifdef __STDC__
static void SetAffixGen (AffixPtr Affix,
                         Attrpos ErgAttr,
                         struct ProdInf *ProdInfo)
#else /* ! __STDC__ */
static void SetAffixGen (Affix, ErgAttr, ProdInfo)
     AffixPtr	    Affix;
     Attrpos	    ErgAttr;
     ProdInform        ProdInfo;
#endif /* ! __STDC__ */
{
  Attr	Pos;
  Entry	AffixName;
  
  Affix->Generiert = TRUE;
  Pos = PPos_Nummer (PPos_Of_AttPos(ErgAttr));
  ProdInfo[Pos].AnzOutAttr --;
  if ((Affix->Index == 0) && (Pos > 0))
  {
    AffixName = Affix->Name;
    Affix = ProdInfo[0].P;
    while (Affix->AttrName != AffixName)
      Affix->Generiert = TRUE;
  }
}



#ifdef __STDC__
static void PutSemAkt (Attrpos Rule,
                       Entry PName,
                       bool Simple,
                       VarList FirstVarList,
                       VarList *PtrLastVarList,
                       int *PtrAnzVar,
                       struct ProdInf *ProdInfo)
#else /* ! __STDC__ */
static void PutSemAkt (Rule, PName, Simple, FirstVarList, PtrLastVarList, PtrAnzVar, ProdInfo)
     Attrpos	Rule;
     Entry		PName;
     bool		Simple;
     VarList	FirstVarList, *PtrLastVarList;
     int		*PtrAnzVar;
     ProdInform 	ProdInfo;
#endif /* ! __STDC__ */
{
  Aparam		ErgAttr, QuAttr;
  AffixPtr	Affix;
  
  if (!Simple)
    sprintf(LastStringPosition(),"      ");
  else
    sprintf(LastStringPosition(),"  ");
  sprintf(LastStringPosition(),"%s(",SymString(B_Funktion(Ber_Aufruf(Rule))));
  for (QuAttr=FirstArg(Ber_Aufruf(Rule));QuAttr;QuAttr=NextArg(QuAttr))
  {
    SucheAffix(AttPos_Of_Param(QuAttr),&Affix,ProdInfo);
    PutActAttr(Affix,PName,Simple,FirstVarList,PtrLastVarList,PtrAnzVar,EVDEREFERENZ);
    sprintf(LastStringPosition(),",");
  }
  ErgAttr=FirstErg(Ber_Aufruf(Rule));
  while (ErgAttr)
  {
    SucheAffix(AttPos_Of_Param(ErgAttr),&Affix,ProdInfo);
    PutActAttr(Affix,PName,Simple,FirstVarList,PtrLastVarList,PtrAnzVar,REFERENZ);
    SetAffixGen(Affix,AttPos_Of_Param(ErgAttr),ProdInfo);
    ErgAttr=NextArg(ErgAttr);
    if (ErgAttr)
      sprintf(LastStringPosition(),",");
  }
  sprintf(LastStringPosition(),");\n");
}



#ifdef __STDC__
static void Assign(AffixPtr ErgAffix,
                   AffixPtr QuAffix,
                   Attrpos ErgAttr,
                   bool Simple,
                   Entry PName,
                   VarList FirstVarList,
                   VarList *PtrLastVarList,
                   int *PtrAnzVar,
                   struct ProdInf *ProdInfo)
#else /* ! __STDC__ */
static void Assign(ErgAffix,QuAffix,ErgAttr,Simple,PName,FirstVarList,PtrLastVarList,PtrAnzVar,ProdInfo)
     AffixPtr	ErgAffix,QuAffix;
     Attrpos	ErgAttr;
     bool	Simple;
     Entry	PName;
     VarList	FirstVarList,*PtrLastVarList;
     int       *PtrAnzVar;
     ProdInform ProdInfo;
#endif /* ! __STDC__ */
{
  if (Simple)
    sprintf(LastStringPosition(),"  ");
  else
    sprintf(LastStringPosition(),"      ");
  PutActAttr(ErgAffix,PName,Simple,FirstVarList,PtrLastVarList,PtrAnzVar,EVDEREFERENZ);
  sprintf(LastStringPosition(), "=" );
  PutActAttr(QuAffix,PName,Simple,FirstVarList,PtrLastVarList,PtrAnzVar,EVDEREFERENZ);
  sprintf(LastStringPosition(),";\n" );
  SetAffixGen(ErgAffix,ErgAttr,ProdInfo);
}



#ifdef __STDC__
static void PutCopies (Attrpos Rule,
                       Entry PName,
                       bool Simple,
                       VarList FirstVarList,
                       VarList *PtrLastVarList,
                       int *PtrAnzVar,
                       struct ProdInf *ProdInfo)
#else /* ! __STDC__ */
static void PutCopies (Rule, PName, Simple, FirstVarList, PtrLastVarList, PtrAnzVar, ProdInfo)
     Attrpos	Rule;
     Entry		PName;
     bool		Simple;
     VarList	FirstVarList, *PtrLastVarList;
     int		*PtrAnzVar;
     ProdInform 	ProdInfo;
#endif /* ! __STDC__ */
{
  Aparam 		ErgAttr;
  AffixPtr	ErgAffix, QuAffix;
  
  ErgAttr = FirstErg (Ber_Aufruf(Rule));
  while (ErgAttr != NULL)
  {
    SucheAffix (AttPos_Of_Param(ErgAttr), &ErgAffix, ProdInfo);
    SucheAffix ( AttPos_Of_Param(FirstArg(Ber_Aufruf(Rule))), &QuAffix, ProdInfo);
    if ( PPos_Nummer (PPos_Of_AttPos(AttPos_Of_Param(ErgAttr))) > 0 )
    {
      ErgAffix->Generiert = TRUE;
      ErgAffix->Name = QuAffix->Name;
      ErgAffix->Index = QuAffix->Index;
    }
    else 
      if ( (QuAffix->Index != 0) || (QuAffix->Name != ErgAffix->Name) )
	Assign (ErgAffix, QuAffix, AttPos_Of_Param(ErgAttr), Simple, PName, 
		FirstVarList, PtrLastVarList, PtrAnzVar, ProdInfo);   
    ErgAttr = NextErg (ErgAttr);
  }
}



#ifdef __STDC__
static void PutSemRule (Attr RegelNr,
                        Entry PName,
                        bool Simple,
                        struct SemInf *SemInfo,
                        VarList FirstVarList,
                        VarList *PtrLastVarList,
                        int *PtrAnzVar,
                        struct ProdInf *ProdInfo)
#else /* ! __STDC__ */
static void PutSemRule (RegelNr, PName, Simple, SemInfo, FirstVarList, PtrLastVarList, PtrAnzVar, ProdInfo)
     Attr		RegelNr;
     Entry		PName;
     bool		Simple;
     SemInform 	SemInfo;
     VarList	FirstVarList, *PtrLastVarList;
     int		*PtrAnzVar;
     ProdInform 	ProdInfo;
#endif /* ! __STDC__ */
{
  if ( Is_Copy (Ber_Aufruf(SemInfo[RegelNr].Regel)) )
    PutCopies (SemInfo[RegelNr].Regel, PName, Simple, FirstVarList, PtrLastVarList, PtrAnzVar, ProdInfo);
  else
    PutSemAkt (SemInfo[RegelNr].Regel, PName, Simple, FirstVarList, PtrLastVarList, PtrAnzVar, ProdInfo);
  SemInfo[RegelNr].Bearbeitet = TRUE;
  SemInfo[RegelNr].Inkarn = 0;
}



#ifdef __STDC__
static void OptimiereRegeln (struct SemInf *SemInfo,
                             int AnzSemRules,
                             struct ProdInf *ProdInfo)
#else /* ! __STDC__ */
static void OptimiereRegeln (SemInfo, AnzSemRules, ProdInfo)
     SemInform	SemInfo;
     int		AnzSemRules;
     ProdInform	ProdInfo;
#endif /* ! __STDC__ */
{
  int 		RegelNr, K;
  bool		Gefunden, Abbruch;
  Attrpos		Regel, R, HAttr, Kopierziel;
  AffixPtr	Affix;
  
  RegelNr = 1;
  Regel = SemInfo[1].Regel;
  while (Regel != NULL)
  {
    if ( Is_Copy (Ber_Aufruf(Regel)) && (PPos_Nummer(PPos_Of_AttPos(Regel))==0) )
    {
      K = 1;
      R = Regel;
      Gefunden = FALSE;
      Abbruch = FALSE;
      do 
      {
	if (Is_Copy(Ber_Aufruf(R)))
	{
	  if ( PPos_Nummer(PPos_Of_AttPos(AttPos_Of_Param(FirstArg(Ber_Aufruf(R))))) != 0 )
	    if ( !Is_Inherited(Attr_Of_AttPos(AttPos_Of_Param(FirstArg(Ber_Aufruf(R))))) )
	    {
	      Kopierziel = AttPos_Of_Param(FirstArg(Ber_Aufruf(R)));
	      Gefunden = TRUE;
	    }
	    else
	    {
	      K++;
	      HAttr = AttPos_Of_Param(FirstArg(Ber_Aufruf(R)));
	      R = HAttr;
	    }
	  else Abbruch = TRUE;
	}
	else
	{
	  Kopierziel = HAttr;
	  Gefunden = TRUE;
	}
      }
      while ( !(Gefunden || Abbruch || (K>AnzSemRules)) );
      if (Gefunden)
      {
	SucheAffix (Kopierziel, &Affix, ProdInfo);
	if ( Affix->Index != 0)
	{
	  Affix->Index = 0;
	  Affix->Name = Attr_Name(Attr_Of_AttPos(Regel));
	}
      }
    }			/* if Is_Copy  */
    RegelNr++;
    Regel = SemInfo[RegelNr].Regel;
  }			/* while  */
}



#ifdef __STDC__
static void CheckQuellAttr1(int K,
                            Attr RegelNr,
                            Attr Inkarnation,
                            Entry PName,
                            bool Simple,
                            Attr *PtrZyklusbeginn,
                            struct SemInf *SemInfo,
                            VarList FirstVarList,
                            VarList *PtrLastVarList,
                            Attr *PtrAnzVar,
                            struct ProdInf *ProdInfo,
                            Attr AnzSemRules)
#else /* ! __STDC__ */
static void CheckQuellAttr1(K,RegelNr,Inkarnation,PName,Simple,PtrZyklusbeginn,SemInfo,
		      FirstVarList,PtrLastVarList,PtrAnzVar,ProdInfo,AnzSemRules)
   PLength    K;
   Attr       RegelNr,Inkarnation;
   Entry      PName;
   bool       Simple;	
   Attr      *PtrZyklusbeginn,*PtrAnzVar,AnzSemRules;
   SemInform  SemInfo;
   VarList    FirstVarList,*PtrLastVarList;
   ProdInform ProdInfo;
#endif /* ! __STDC__ */
{
  Aparam   Quattr;
  AffixPtr Affix;
  int      QuPosNr,Nr;
  bool     QuInh,KritischesAttr;
  bool     Abbruch;
  
  for (Quattr=FirstArg(Ber_Aufruf(SemInfo[RegelNr].Regel)),Abbruch=0;Quattr && !ErrorNum && !Abbruch;Quattr=NextArg(Quattr))
  {
    QuPosNr = PPos_Nummer (PPos_Of_AttPos(AttPos_Of_Param(Quattr)));
    QuInh = Is_Inherited (Attr_Of_AttPos(AttPos_Of_Param(Quattr)));
    if ( QuPosNr == 0 )
      KritischesAttr = !QuInh;
    else
      KritischesAttr = (QuPosNr >= K);
    if (KritischesAttr)
    {
      if ( ((QuPosNr==K) && (!QuInh)) || (QuPosNr > K) )
      {
	ErrorNum = 1;
	ErrorAttr = AttPos_Of_Param(Quattr);
	PushErrRule (SemInfo[RegelNr].Regel);
	Abbruch=1;
      }
      if (!Abbruch)
      {
	SucheAffix (AttPos_Of_Param(Quattr), &Affix, ProdInfo);
	if ( !Affix->Generiert )
	{
	  SucheRegel (AttPos_Of_Param(Quattr), &Nr, SemInfo, AnzSemRules);
	  if ( SemInfo[Nr].Inkarn > 0 )
	  {
	    ErrorNum = 2;
	    ErrorAttr = AttPos_Of_Param(Quattr);
	    PushErrRule (SemInfo[RegelNr].Regel);
	    *PtrZyklusbeginn = SemInfo[Nr].Inkarn;
	  }
	  else
	  {
	    SemInfo[Nr].Inkarn = Inkarnation + 1;
	    CheckQuellAttr1 (K, Nr, Inkarnation+1, PName, Simple, PtrZyklusbeginn, SemInfo, 
			     FirstVarList, PtrLastVarList, PtrAnzVar, ProdInfo, AnzSemRules);
	    if ( (ErrorNum==1) || (ErrorNum==2) && (*PtrZyklusbeginn<=Inkarnation) )
	      PushErrRule (SemInfo[RegelNr].Regel);
	  }
	}
      }
    }
  }
 PutSemRule (RegelNr, PName, Simple, SemInfo, FirstVarList, PtrLastVarList, PtrAnzVar, ProdInfo);
}



#ifdef __STDC__
static void GenInheritedAffixe (int K,
                                Entry PName,
                                bool Simple,
                                int AnzSemRules,
                                struct SemInf *SemInfo,
                                VarList FirstVarList,
                                VarList *PtrLastVarList,
                                int *PtrAnzVar,
                                struct ProdInf *ProdInfo)
#else /* ! __STDC__ */
static void GenInheritedAffixe (K, PName, Simple, AnzSemRules, SemInfo, 
			 FirstVarList, PtrLastVarList, PtrAnzVar, ProdInfo)
     PLength	K;
     Entry		PName;
     bool 		Simple;
     int		AnzSemRules,*PtrAnzVar;
     SemInform 	SemInfo;
     VarList	FirstVarList, *PtrLastVarList;
     ProdInform 	ProdInfo;
#endif /* ! __STDC__ */
{
  int 	RegelNr, Zyklusbeginn;
  
  RegelNr = 1;
  while ( (RegelNr <= AnzSemRules) && (ProdInfo[K].AnzOutAttr > 0) )
  {
    if (!SemInfo[RegelNr].Bearbeitet)
    {
      if ( PPos_Nummer(PPos_Of_AttPos(SemInfo[RegelNr].Regel)) == K )
      {
	SemInfo[RegelNr].Inkarn = 1;
	ErrorNum = 0;
	Zyklusbeginn = 0;
	CheckQuellAttr1 (K, RegelNr, 1, PName, Simple, &Zyklusbeginn, SemInfo, 
			 FirstVarList, PtrLastVarList, PtrAnzVar, ProdInfo, AnzSemRules);
	if ( (ErrorNum == 1) || (ErrorNum == 2) )
	  ErrorHandling();
      }
    }
    RegelNr++;
  }
}



#ifdef __STDC__
static void CheckQuellAttr2 (Attr RegelNr,
                             Attr Inkarnation,
                             Entry PName,
                             bool Simple,
                             Attr *PtrZyklusbeginn,
                             struct SemInf *SemInfo,
                             VarList FirstVarList,
                             VarList *PtrLastVarList,
                             Attr *PtrAnzVar,
                             struct ProdInf *ProdInfo,
                             Attr AnzSemRules)
#else /* ! __STDC__ */
static void CheckQuellAttr2 (RegelNr, Inkarnation, PName, Simple, PtrZyklusbeginn, SemInfo, 
		      FirstVarList, PtrLastVarList, PtrAnzVar, ProdInfo, AnzSemRules)
     Attr		RegelNr, Inkarnation;
     Entry		PName;
     bool 		Simple;
     Attr		*PtrZyklusbeginn, *PtrAnzVar, AnzSemRules;
     SemInform 	SemInfo;
     VarList	FirstVarList, *PtrLastVarList;
     ProdInform 	ProdInfo;
#endif /* ! __STDC__ */
{
  Aparam	Quattr;
  AffixPtr	Affix;
  int		QuPosNr, Nr;
  bool		QuInh;
  
  Quattr = FirstArg (Ber_Aufruf(SemInfo[RegelNr].Regel));
  while ( (Quattr != NULL) && (ErrorNum == 0) )
  {
    QuPosNr = PPos_Nummer (PPos_Of_AttPos(AttPos_Of_Param(Quattr)));
    QuInh = Is_Inherited (Attr_Of_AttPos(AttPos_Of_Param(Quattr)));
    if ( (QuPosNr==0) && (!QuInh) ) 
    {
      SucheAffix (AttPos_Of_Param(Quattr), &Affix, ProdInfo);
      if ( !Affix->Generiert )
      {
	SucheRegel (AttPos_Of_Param(Quattr), &Nr, SemInfo, AnzSemRules);
	if ( SemInfo[Nr].Inkarn > 0 )
	{
	  ErrorNum = 2;
	  ErrorAttr = AttPos_Of_Param(Quattr);
	  PushErrRule (SemInfo[RegelNr].Regel);
	  *PtrZyklusbeginn = SemInfo[Nr].Inkarn;
	}
	else
	{
	  SemInfo[Nr].Inkarn=Inkarnation+1;
	  CheckQuellAttr2 (Nr, Inkarnation+1, PName, Simple, PtrZyklusbeginn, SemInfo, 
			   FirstVarList, PtrLastVarList, PtrAnzVar, ProdInfo, AnzSemRules);
	  if ( (ErrorNum==2) && (*PtrZyklusbeginn<=Inkarnation) )
	    PushErrRule (SemInfo[RegelNr].Regel);
	}
      }
    }
    Quattr = NextArg (Quattr);
  }
  PutSemRule (RegelNr, PName, Simple, SemInfo, FirstVarList, PtrLastVarList, PtrAnzVar, ProdInfo);
}



#ifdef __STDC__
static void GenDerivedAffixe (Entry PName,
                              bool Simple,
                              int AnzSemRules,
                              struct ProdInf *ProdInfo,
                              struct SemInf *SemInfo,
                              VarList FirstVarList,
                              VarList *PtrLastVarList,
                              int *PtrAnzVar)
#else /* ! __STDC__ */
static void GenDerivedAffixe (PName, Simple, AnzSemRules, ProdInfo, SemInfo, FirstVarList, PtrLastVarList, PtrAnzVar )
     Entry		PName;
     bool		Simple;
     int 		AnzSemRules, *PtrAnzVar;
     ProdInform 	ProdInfo;
     SemInform 	SemInfo;
     VarList	FirstVarList, *PtrLastVarList;
#endif /* ! __STDC__ */
{
  Attr	RegelNr, Zyklusbeginn;
  
  RegelNr = 1;
  while ( (RegelNr <= AnzSemRules) && (ProdInfo[0].AnzOutAttr > 0) )
  {
    if (!SemInfo[RegelNr].Bearbeitet)
    {
      if ( PPos_Nummer(PPos_Of_AttPos(SemInfo[RegelNr].Regel)) == 0 )
      {
	SemInfo[RegelNr].Inkarn = 1;
	ErrorNum = 0;
	Zyklusbeginn = 0;
	CheckQuellAttr2 (RegelNr, 1, PName, Simple, &Zyklusbeginn, SemInfo, 
			 FirstVarList, PtrLastVarList, PtrAnzVar, ProdInfo, AnzSemRules);
	if (ErrorNum == 2)
	  ErrorHandling();
      }
    }
    RegelNr++; 
  }
}



#ifdef __STDC__
static void OutGen (AffixPtr Affix, struct ProdInf *ProdInfo)
#else /* ! __STDC__ */
static void OutGen (Affix, ProdInfo)
     AffixPtr	Affix;
     ProdInform  	ProdInfo;
#endif /* ! __STDC__ */
{
  AffixPtr	A;
  
  Affix->Generiert=TRUE;
  if (!Affix->Index)
  {
    for (A=ProdInfo[0].P;A->AttrName!=Affix->Name;A=A->Next) ;
    A->Generiert=TRUE;
  }
}



#ifdef __STDC__
static void PutRhsAttr(Entry PName,
                       AffixPtr Affix,
                       int Anz,
                       bool Simple,
                       struct ProdInf *ProdInfo,
                       VarList FirstVarList,
                       VarList *PtrLastVarList,
                       int *PtrAnzVar,
                       Attr Attribut,
                       int Modus)
#else /* ! __STDC__ */
static void PutRhsAttr(PName,Affix,Anz,Simple,ProdInfo,FirstVarList,PtrLastVarList,PtrAnzVar,Attribut,Modus)
  Entry		PName;
  AffixPtr	Affix;
  int		Anz, *PtrAnzVar;
  bool		Simple;
  ProdInform 	ProdInfo;
  VarList	FirstVarList, *PtrLastVarList;
  Attr          Attribut;
  int           Modus;
#endif /* ! __STDC__ */
{
  int alter_modus;
  while (Anz--)
  {
    if (!Is_Inherited(Affix->AttrTyp))
      OutGen(Affix,ProdInfo);
    alter_modus=Modus;
    if (Modus==EVREFERENZ && !Is_Inherited(Attribut))  /* Adresse muss uebergeben werden */
      Modus=REFERENZ;
    PutActAttr(Affix,PName,Simple,FirstVarList,PtrLastVarList,PtrAnzVar,Modus);
    Affix=Affix->Next;
    Attribut=NextAttr(Attribut);
    Modus=alter_modus;
    if (Anz)
      sprintf(LastStringPosition(),",");
  }
}



#ifdef __STDC__
static void GenRhsSymbol(Prodpos RhsElem,
                         int *PtrProdIndex,
                         Entry PName,
                         bool Simple,
                         struct ProdInf *ProdInfo,
                         VarList FirstVarList,
                         VarList *PtrLastVarList,
                         int *PtrAnzVar)
#else /* ! __STDC__ */
static void GenRhsSymbol(RhsElem,PtrProdIndex,PName,Simple,ProdInfo,FirstVarList,PtrLastVarList,PtrAnzVar)
  Prodpos    RhsElem;
  int       *PtrProdIndex,*PtrAnzVar;
  Entry      PName;
  bool       Simple;
  ProdInform ProdInfo;
  VarList    FirstVarList,*PtrLastVarList;
#endif /* ! __STDC__ */
{
  AffixPtr Affix;
  int      Anz;
  
  Affix=ProdInfo[PPos_Nummer(RhsElem)].P;
  Anz=ProdInfo[PPos_Nummer(RhsElem)].AnzAttr;
  if (Is_Terminal(Grm_Symbol(RhsElem)))
  {
    if (Is_Semantisch(Grm_Symbol(RhsElem)))
    {
      if (!Simple)
	sprintf(LastStringPosition(),"      ");
      else
	sprintf(LastStringPosition(),"  ");
      PutRhsAttr(PName,Affix,Anz,Simple,ProdInfo,FirstVarList,PtrLastVarList,PtrAnzVar,FirstAttr(Grm_Symbol(RhsElem)),EVDEREFERENZ);
      sprintf(LastStringPosition()," = *%s->C.",Intree);
      sprintf(LastStringPosition(),"%s.%s%d;\n",SymString(PName),SymString(PName),*PtrProdIndex);
    }
    (*PtrProdIndex)++;
  }
  else
  {
    /* Eine weitere MUGFunktion wird aufgerufen */

    
    if (!Simple)
      sprintf(LastStringPosition(),"      ");
    else
      sprintf(LastStringPosition(),"  ");
    sprintf(LastStringPosition(),"%s%s",mug,SymString(Sym_Name(Grm_Symbol(RhsElem))));
    sprintf(LastStringPosition(),"(%s->C.",Intree);
    sprintf(LastStringPosition(),"%s.%s%d",SymString(PName),SymString(PName),*PtrProdIndex);
    if (Anz>0)
      sprintf(LastStringPosition(),",");
    (*PtrProdIndex)++;
    PutRhsAttr(PName,Affix,Anz,Simple,ProdInfo,FirstVarList,PtrLastVarList,PtrAnzVar,FirstAttr(Grm_Symbol(RhsElem)),EVREFERENZ);
    sprintf(LastStringPosition(),");\n");
  }
}



#ifdef __STDC__
static void GenRecAlt(Product Prod,
                      bool Simple,
                      VarList *PtrLastVarList,
                      int *PtrAnzVar,
                      struct ProdInf *ProdInfo,
                      struct SemInf *SemInfo,
                      VarList FirstVarList)
#else /* ! __STDC__ */
static void GenRecAlt(Prod,Simple,PtrLastVarList,PtrAnzVar,ProdInfo,SemInfo,FirstVarList)
   Product     Prod;
   bool        Simple;	 
   VarList    *PtrLastVarList,FirstVarList;
   int        *PtrAnzVar;
   ProdInform  ProdInfo;
   SemInform   SemInfo;
#endif /* ! __STDC__ */
{
  Prodpos RhsElem;
  PLength K;
  int     ProdIndex,AnzSemRules;
  
  NewErrorStack();
  NewVarList(PtrLastVarList,PtrAnzVar,FirstVarList);
  Initialisierung(Prod,PtrAnzVar,ProdInfo,&AnzSemRules,PtrLastVarList,SemInfo);
  OptimiereRegeln(SemInfo,AnzSemRules,ProdInfo);
  ErrorProd=Prod;
  RhsElem=NextPPos(FirstPPos(Prod));
  ProdIndex=1;
  K=1;
  while (RhsElem)
  {
    GenInheritedAffixe(K,Prod_Name(Prod),Simple,AnzSemRules,SemInfo,
			FirstVarList,PtrLastVarList,PtrAnzVar,ProdInfo);
    GenRhsSymbol(RhsElem,&ProdIndex,Prod_Name(Prod),Simple,ProdInfo,FirstVarList,PtrLastVarList,PtrAnzVar);
    RhsElem=NextPPos(RhsElem);
    K++;
  }
  GenDerivedAffixe(Prod_Name(Prod),Simple,AnzSemRules,ProdInfo,SemInfo,FirstVarList,PtrLastVarList,PtrAnzVar);
}



#ifdef __STDC__
static void GenRecProc(void)
#else /* ! __STDC__ */
static void GenRecProc()
#endif /* ! __STDC__ */
{
  ProdInform ProdInfo;
  SemInform  SemInfo;
  Product    P;
  Vocabel    Nt;
  PLength    i;
  VarList    FirstVarList,LastVarList;
  int        AnzVar;
  bool       Simple;

  for (i=0;i<=MaxPLength;i++)
  {
    ProdInfo[i].P=NULL;
    ProdInfo[i].AnzAffix=0;
  }
  VarListFirst(&FirstVarList,&LastVarList);
  for (Nt=FirstSym();Nt;Nt=NextSym(Nt))
  {
    if (!Is_Terminal(Nt) && (P=FirstProd(Nt))!=NULL)
    {
      fprintf(Scratch,"\n\n");
      GenRecHead(Nt);
      fprintf(Scratch,"{\n");
      Simple=(NextProd(P)==NULL);
      if (!Simple) 
	sprintf(String,"  switch (%s->prodnum)\n  {\n",Intree);
      else
	*String=0;
      i=1;
      do 
      {
	/* Der Anweisungsteil wird erst in einen String geschrieben, dann werden erst die lokalen
	   Variablen erzeugt und in den Stream geschrieben, danach kann der String geschrieben werden */

	if (!Simple)
	  sprintf(LastStringPosition(),"    case %3d:\n",Prod_Nummer(P));
	GenRecAlt(P,Simple,&LastVarList,&AnzVar,ProdInfo,SemInfo,FirstVarList);
	if (!Simple)
	  sprintf(LastStringPosition(),"      break;\n");
	GenRecVar(i,AnzVar,Simple,FirstVarList,P);
	i++;
	P=NextProd(P);
      }
      while (P);
      fprintf(Scratch,"%s",String);
      if (!Simple)
	fprintf (Scratch, "  }\n" );
      fprintf (Scratch, "}\n" );
    }
  }
}



#ifdef __STDC__
void LAuswerterGen(void)
#else /* ! __STDC__ */
void LAuswerterGen()
#endif /* ! __STDC__ */
{
  char file[100];

  PhasenId=GetPhasenId();
  strcpy(file,SymString(PhasenId));
  strcat(file,"_Auswert.c");
  Scratch=fopen(file,"w");

  GenNNTypen();
  GenPrototypes();
  GenRecProc();
  GenCompProc();

  fclose(Scratch);
  if (ErrProt)
  {
    fclose(ErrProt);
    fprintf(stderr,"Fehler aufgetreten! Siehe Datei %sL.ERR\n",SymString(PhasenId));
    exit(1);
  }
}
