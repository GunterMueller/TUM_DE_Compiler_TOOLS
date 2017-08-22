#include <stdio.h>

#include "scan.h"

extern int abort_scan;
int ignore_case = 0; /* FALSE */

#define TOKEN Action_tok
void ACTDo_Action(Action_tok,Action_nr)
Token Action_tok;
int Action_nr;
{ switch (Action_nr) {
  case 0   : MEMugRecoverableError(6);
           break;
  case 1    : abort_scan = 0; /*FALSE*/
             
              break;
  case 2    : abort_scan = 1; /*TRUE*/
                MACRetCC(TOKEN,1,1);   
              break;
  case 3    : abort_scan = 1; /*TRUE*/
                MACRetCC(TOKEN,1,2);   
              break;
  case 4    : abort_scan = 1; /*TRUE*/
                MACRetCC(TOKEN,1,3);   
              break;
  case 5    : abort_scan = 1; /*TRUE*/
                MACRetCC(TOKEN,2,1);   
              break;
  case 6    : abort_scan = 1; /*TRUE*/
                MACRetCC(TOKEN,2,2);   
              break;
  case 7    : abort_scan = 1; /*TRUE*/
                MACRetCC(TOKEN,2,3);   
              break;
  case 8    : abort_scan = 1; /*TRUE*/
                MACRetInt(TOKEN,3);     
              break;
  case 9    : abort_scan = 1; /*TRUE*/
                MACRetId(TOKEN,4);      
              break;
  }
}

void ACTEnd_Action(Action_tok)
Token Action_tok;
{ 
  MACRetCC(TOKEN,0,0);
}

void ACTInitAction()
{ 
  printf("ALEXIS: Scanner                 (c) TU Muenchen  2. Juli 1991\n");
}

void ACTError_Action()
{ }

