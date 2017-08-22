#ifndef EXTERN
#define EXTERN        extern
#endif

EXTERN UebergangsTabelle Delta;
EXTERN instflags         flags;
EXTERN StackTyp          Stack;
/* Bauernfeind: statisch -> dynamisch: 14.06.93 */
/* EXTERN Action            ActionTable[MaxState+1]; */
EXTERN Action            *ActionTable;

#undef EXTERN
