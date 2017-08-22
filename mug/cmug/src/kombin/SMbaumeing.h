/* BaumEingabe aus Datei fuer Semantikteil eines MUG-generierten Uebersetzers */
/* ========================================================================== */

MUGCtrl(input,s)
FILE *input;char s[];
{ char hc; int i;
	fscanf(input,"%c\n",&hc);
	i=0;
	do  if (s[i]==hc) return(0);
	while (s[++i]!='\0');
	return(1);
}

MUGANALYSATOR(argc,argv,Parsefile)
int argc;
char **argv;
char *Parsefile;
{
	char MUGC;
	int  MUGI;
	FILE *MUGRFolge;
	if ( ! (MUGRFolge = fopen(Parsefile,"r")) )
	 {
		fprintf(stderr,"No Parsfile");
		exit(1);
	 }
	decinit();
	MUGAccepted=  0;
	MUGErrNum = MUGCtrl(MUGRFolge,"Bb");
	while (! (MUGAccepted || MUGErrNum!=0))
	{
		fscanf(MUGRFolge,"%c\n",&MUGC);
		switch (MUGC)
		{
			case ' ' : continue;
			case 'e' :
			case 'E' :
			case 'f' :
			case 'F' :
			case 'd' :
			case 'D' : MUGErrNum=1; break;
			case 'a' :
			case 'A' : MUGAccepted=1; break;
			case 'r' :
			case 'R' : fscanf(MUGRFolge,"%d\n",&MUGI);
			              MUGProdCons(MUGI); break;
			case 't' :
			case 'T' : fscanf(MUGRFolge,"%d\n",&MUGI);
			           fscanf(MUGRFolge,"%d\n",&MUGRCode);
			           fscanf(MUGRFolge,"%d\n",&MUGCode);
			           fscanf(MUGRFolge,"%d\n",&MUGZl);
			           fscanf(MUGRFolge,"%d\n",&MUGSp);
			           MUGTermCons(MUGI-MUGCMinT); break;
			default : MUGErrNum=1;
		}
	}
}
