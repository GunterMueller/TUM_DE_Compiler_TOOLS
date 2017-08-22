#include <stdio.h>
#include "scan.h"                    /* Bekanntmachen des Typs Token */

main(argc,argv)
int argc;
char *argv[];
  {
  TokenRec tok,tok1,tok2,tok3;
  FILE *out;
  char *text;
  int i,ident;

  if( argc!=3 )
   { printf("%s infile outfile\n",argv[0]);
     exit(-1); }

  scanInit();
  scanOpen(argv[1]);                   /* Oeffnen der Scannereingabe */
  out = fopen(argv[2],"w");
  fprintf(out,"scanner name\noptions\n  ignorecase minimize\noptionend\n\ninclude '/usr/proj/cmug/include/mugdefs.sci'\n\nlexmakros\n   string  = '''' (not(.''''.)| '''''')+ '''';\nmakroend\n\nlexemes\n\n  ignore Ws+         -> { White Space }  ;\n");

  ident = -1; 

    scanNext(&tok);  
  do{
    if (tok.kc != 1) 
      { printf("Fehler\n");   /* kein #-Statement */
        exit(-1); }    
    switch(tok.rcode) {
      case 1:  /* #comments */
               scanNext(&tok);  
               break;

      case 2:  /* #specials */
         for(;;) {
               scanNext(&tok);  
               if (tok.kc != 3) break;
               scanNext(&tok2);  
               scanNext(&tok3);
               if(tok3.kc!=2) {
                 fprintf(out,"'%s'",scanDecode( (char*)0,&tok3));
                 for(i=0; i<(20-strlen(scanDecode( (char*)0,&tok3)));i++,fprintf(out," "));
                 fprintf(out,"->  Code(%d,%d);\n",tok.rcode,tok2.rcode);
                  }
               else switch(tok3.rcode) {
                   case 1: ident = tok.rcode;
                           break;
                   case 2: fprintf(out,"digit+                ->  RetInt(%d);\n",tok.rcode);
                           break;
                   case 3: fprintf(out,"string                ->  RetStr(%d);\n",tok.rcode);
                           break;

                  }
               }  

      case 3:  /* #keywords */
         for(;;) {
               scanNext(&tok);  
               if (tok.kc != 3) break;
               scanNext(&tok2);  
               scanNext(&tok3);
               fprintf(out,"'%s'",scanDecode( (char*)0,&tok3));
               for(i=0; i<(20-strlen(scanDecode( (char*)0,&tok3)));i++,fprintf(out," "));
               fprintf(out,"->  Code(%d,%d);\n",tok.rcode,tok2.rcode);
               }      


      }   
     } while( tok.kc!=0 || tok.rcode!=0 );              /* Dateiende */

  if (ident!=-1) fprintf(out,"ident                 ->  RetId(%d);\n",ident);

fprintf(out,"lexemesend\n");

  scanClose();                             /* Schliessen der Eingabe */
  fclose(out);

  exit(0);
  }  


