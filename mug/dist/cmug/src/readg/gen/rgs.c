/* Datei : gen/rgs.c , generiert : Tue Jan 16 16:06:49 1996 */
#include <stdio.h>
#include "ps_token.h"
#include "ps_tab.h"
static Keywddef keywds[] = {
{"empty",5L,0L,0L},
{"rules",4L,0L,0L},
{"start",3L,0L,0L},
{"axiom",3L,0L,0L},
{"actions",2L,0L,0L},
{"terminals",1L,0L,0L},
{NULL,0L,0L,0L}}; /* keywds */
static Specdef specs[] = {
{"->",8L,0L,0L,NULL},
{".",9L,0L,0L,NULL},
{"/*",10L,0L,1L,psCcomments},
{":",8L,0L,0L,NULL},
{"::=",8L,0L,0L,NULL},
{";",10L,0L,0L,NULL},
{"{",10L,0L,1L,psComments},
{"|",10L,0L,0L,NULL},
{NULL,0L,0L,0L}}; /* specs */
Pscantab scantab = {
keywds,specs,
psScanspecials,
2L,
0,0,6L,1L,0L,psIdents,
7L,0L,0L,0L,psNumbers,
0,
0,
NULL,
}; /* scantab */
