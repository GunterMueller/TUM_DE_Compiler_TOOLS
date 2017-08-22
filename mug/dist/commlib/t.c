#include "parlist.h"

typedef struct {
		int val;
		int anz;
		} Int;

INSTANZ_SLIST(Intseq,Int,ziel->val - quelle->val,{},ziel->anz++,{})

int main(int argc,char *argv[])
 {
  Intseq is,s;
  Int    i;

  is = 0;
  i.anz = 1;
  i.val = 0;
  enterIntseq(&is,&i);
  i.val = 1;
  enterIntseq(&is,&i);
  enterIntseq(&is,&i);
  enterIntseq(&is,&i);
  enterIntseq(&is,&i);
  i.val = 2;
  enterIntseq(&is,&i);
  i.val = 4;
  enterIntseq(&is,&i);
  enterIntseq(&is,&i);
  i.val = 3;
  enterIntseq(&is,&i);
  for (s = is; s != NULL; s = LISTREST(s) )
    printf("(%d,%d)\n",LISTFIRST(s).val,LISTFIRST(s).anz);

  return 0;
 }
