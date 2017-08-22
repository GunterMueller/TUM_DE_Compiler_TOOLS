
%{
	#include "bim.tab.h"
	
%}

%%

"%SORTS"	{ return SORTSECT;}
"%ATTRIBUTES"	{ return ATTRSECT;}
"%TUPLES"	{ return TUPLESECT;}
"%LISTS"	{ return LISTSECT;}

[a-zA-Z_][a-zA-Z@_0-9]* { return IDENT; }
" "		{}
"("		{ return LBRACE; }
")"		{ return RBRACE; }
^"\n"		{}
"\n"		{ return NL;}
    