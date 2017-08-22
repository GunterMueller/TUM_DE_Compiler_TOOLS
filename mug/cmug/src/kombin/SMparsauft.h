 
/* Parseraufruf mit  outterm(Token) -Schnittstelle fuer einen MUG-generierten *
 * Uebersetzer                                                                *
 * ========================================================================== */

MUGANALYSATOR (argc,argv,Quelldatei)
int argc;
char **argv;
char *Quelldatei;
{ parser (argc,argv,Quelldatei); }

outred (Prodnr,Leftpart,Laenge)
long Prodnr, Leftpart, Laenge;
{
 MUGProdCons (Prodnr);
 }

outterm (tok)
Token tok;
{
 MUGToken = tok;  MUGTermCons (SYM(tok));
 }

