/* Datei : gen/exprscan.c , generiert : Tue Jan 16 16:17:51 1996 */
#include <stdio.h>
#include "ps_token.h"
#include "ps_tab.h"
static Keywddef keywds[] = {
{NULL,0L,0L,0L}}; /* keywds */
static Specdef specs[] = {
{"(",4L,0L,0L,NULL},
{")",5L,0L,0L,NULL},
{"*",3L,1L,0L,NULL},
{"+",2L,1L,0L,NULL},
{"-",2L,2L,0L,NULL},
{"/",3L,2L,0L,NULL},
{NULL,0L,0L,0L}}; /* specs */
Pscantab scantab = {
keywds,specs,
psScanspecials,
0L,
0,0,0L,0L,0L,NULL,
1L,0L,0L,0L,psNumbers,
0,
0,
NULL,
}; /* scantab */
