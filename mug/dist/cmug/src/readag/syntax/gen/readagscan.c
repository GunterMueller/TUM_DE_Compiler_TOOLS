/* Datei : gen/readagscan.c , generiert : Tue Jan 16 16:10:08 1996 */
#include <stdio.h>
#include "ps_token.h"
#include "ps_tab.h"
static Keywddef keywds[] = {
{"type",33L,0L,0L},
{"terminals",32L,0L,0L},
{"synthesized",31L,0L,0L},
{"syn",30L,0L,0L},
{"sfunction",28L,0L,0L},
{"semend",27L,0L,0L},
{"sem",26L,0L,0L},
{"productions",25L,0L,0L},
{"nonterminals",24L,0L,0L},
{"inherited",23L,0L,0L},
{"grammarend",22L,0L,0L},
{"grammar",21L,0L,0L},
{"function",20L,0L,0L},
{"axiom",19L,0L,0L},
{"auxiliaries",18L,0L,0L},
{"auxiliarys",18L,0L,0L},
{"attributes",17L,0L,0L},
{"const",4L,0L,0L},
{NULL,0L,0L,0L}}; /* keywds */
static Specdef specs[] = {
{"\"",29L,0L,0L,psStrings},
{"$",5L,0L,0L,NULL},
{"\'",29L,0L,0L,psStrings},
{"(",10L,0L,0L,NULL},
{"(*",0L,0L,1L,psMcomments},
{")",15L,0L,0L,NULL},
{"+",14L,0L,0L,NULL},
{",",3L,0L,0L,NULL},
{"-",11L,0L,0L,NULL},
{"->",1L,0L,0L,NULL},
{".",13L,0L,0L,NULL},
{":",2L,0L,0L,NULL},
{";",16L,0L,0L,NULL},
{"<",9L,0L,0L,NULL},
{"=",8L,0L,0L,NULL},
{">",6L,0L,0L,NULL},
{"{",0L,0L,1L,psComments},
{NULL,0L,0L,0L}}; /* specs */
Pscantab scantab = {
keywds,specs,
psScanspecials,
1L,
0,1,7L,1L,0L,psIdents,
12L,0L,0L,0L,psNumbers,
0,
0,
NULL,
}; /* scantab */
