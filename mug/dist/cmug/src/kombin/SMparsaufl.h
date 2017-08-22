 
/* Parseraufruf mit  outterm(long,long,..) -Schnittstelle fuer einen          *
 * MUG-generierten Uebersetzer                                                *
 * ========================================================================== */

MUGANALYSATOR (argc,argv,Quelldatei)
int argc;
char **argv;
char *Quelldatei;
{ parser (argc,argv,Quelldatei); }

outred (Prodnr,Leftpart,Laenge)
int Prodnr, Leftpart, Laenge;
{ MUGProdCons (Prodnr); }

outterm (kc,rc,pos,zl,sp)
long kc,rc,pos,zl,sp;
{ MUGRCode=rc; MUGCode=pos; MUGZl=zl; MUGSp=sp; MUGTermCons(kc); }

