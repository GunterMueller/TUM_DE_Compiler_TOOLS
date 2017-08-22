#include <stdio.h>
#include "global.h"

/* Ueberall globale Variablen : */

/* Bauernfeind: 16.06.93; ehemalige defines als Variablen */
/*                        (siehe ./include/global.h)      */

int MaxState;
int MaxAction;
int MaxKomprState;
int MaxKomprKanten; 
int MAX_ID_NO;

UebergangsTabelle Delta;
instflags         flags;
StackTyp          Stack;
/* Bauernfeind: statisch->dynamisch: 14.06.93 */
/* Action            ActionTable[MaxState+1]; */
Action            *ActionTable;
MakroTable         MakTable;
