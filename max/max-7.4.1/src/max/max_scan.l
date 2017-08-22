%{
#include <string.h>
#define TABLENGTH 8

int   line   =  1 ;
char *file   =  "unknown";
static int   column =  0 ;

/*
  The following function scan_idpos scans identifiers (or other symbols
  containing no $-character) with optional tags attached specifying the
  original source code position.  The tags follow the syntax
  $<linenr>,<columnnr>,"<filename>"$ and no space is allowed between
  identifier and the tag and within the tag.  The information is stored in
  the global variables V,L,C and F and in the yylval structure.  The syntax
  is checked by the lex-scanner using the regexp definition SCP, not by the
  scan_idpos function.
*/

ELEMENT V, L, C, F;

void scan_idpos (char text[])
{
  int l, c;
  char buffer[1024]; /* up to 1023 characters of a filename are used.
                        Should be enough. */
  int i,j;

  for (i=0;  text[i]!='$' && text[i]!='\0'; i++) ;

  if (text[i] == '\0') {
    /* no source code position tag appended */
    V = stoid(atoe(text));
    L = itoe(line); C = itoe(column+1); F = atoe(file);
    yylval.vlcf.v=V; yylval.vlcf.l=L; yylval.vlcf.c=C; yylval.vlcf.f=F;
    return;
  }

  /* $ found. So process source code position tag */

  text[i] = '\0';
  V = stoid(atoe(text));

  ++i; /* skip '\0' */

  l=0;
  for (; *(text+i)!=','; i++) {
    l *=10; l += (text[i]-'0');
  }

  ++i; /* skip ',' */

  c=0;
  for (; text[i]!=','; i++) {
    c *=10; c += (text[i]-'0');
  }
 
  i+=2; /* skip ',"' */
  j=0;
  for (; text[i]!='"' && j<1023; i++) buffer[j++]=text[i];

  buffer[j]='\0';

  L = itoe(l); C = itoe(c); F=atoe(buffer); yylval.vlcf.v=V;
  yylval.vlcf.l=L; yylval.vlcf.c=C; yylval.vlcf.f=F;
}

%}

NR  [0-9]+
DOLLAR [$]
COMMA [,]
QU ["]
FN [^"]*
SCP {DOLLAR}{NR}{COMMA}{NR}{COMMA}{QU}{FN}{QU}{DOLLAR}

%%

^#(line)?[ \t]+[0-9]+[ \t]+\"[^"]+\".*\n { 
    char *cp;
	char *n;
	char *f;

	for (cp = yytext+1; *cp == ' ' || *cp == '\t'; cp++)
		;
	n = cp;
	for ( ; *cp != ' ' && *cp != '\t'; cp++)
		;
	*cp++ = '\0';
	for ( ; *cp == ' ' || *cp == '\t'; cp++)
		;
	f = ++cp;
	for ( ; *cp != '"'; cp++)
		;
	*cp++ = '\0';
	line = atoi(n);
	file = strdup(f);
    column = 0;
}

[ ]*		{ column += yyleng; }
\n		{ line++; column = 0; }
\t		{ column += TABLENGTH; }
"PRD"		{ column += yyleng;  return(PRD); }
"FCT"		{ column += yyleng;  return(FCT); }
"ATT"		{ column += yyleng;  return(ATT); }
"STRUC"		{ column += yyleng;  return(STRUC); }
"CND"		{ column += yyleng;  return(CND); }
"LET"		{ column += yyleng;  return(LET); }
"IF"{SCP}?	{ column += yyleng;  scan_idpos(yytext); return(IF); }
"ELSE"		{ column += yyleng;  return(ELSE); }
"RULES"		{ column += yyleng;  return(RULES); }
"DYN"		{ column += yyleng;  return(DYN); }
"IN"		{ column += yyleng;  return(IN); }
"THEN"		{ column += yyleng;  return(THEN); }
"FI"		{ column += yyleng;  return(FI); }
"CASE"		{ column += yyleng;  return(CASE); }
"IS"		{ column += yyleng;  return(IS); }
"END"		{ column += yyleng;  return(END); }
"??"		{ column += yyleng;  return(UNDEF); }
":="		{ column += yyleng;  return(ASSIGN); }
"||"		{ column += yyleng;  return(ORSYM); }
"&&"		{ column += yyleng;  return(ANDSYM); }
"->"		{ column += yyleng;  return(IMPLSYM); }
"=="		{ column += yyleng;  return(EQSYM); }
"--"[-]*	{ column += yyleng;  return(SEPSYM); }
"["		{ column += yyleng;  return('['); }
"]"		{ column += yyleng;  return(']'); }
"("		{ column += yyleng;  return('('); }
")"		{ column += yyleng;  return(')'); }
"{"		{ column += yyleng;  return('{'); }
"}"		{ column += yyleng;  return('}'); }
"<"		{ column += yyleng;  return('<'); }
">"		{ column += yyleng;  return('>'); }
"*"		{ column += yyleng;  return('*'); }
"_"		{ column += yyleng;  return('_'); }
"="		{ column += yyleng;  return('='); }
"#"		{ column += yyleng;  return('#'); }
"|"		{ column += yyleng;  return('|'); }
"."		{ column += yyleng;  return('.'); }
","		{ column += yyleng;  return(','); }
":"		{ column += yyleng;  return(':'); }
"!"		{ column += yyleng;  return('!'); }
"-"		{ column += yyleng;  return('-'); }
"'"		{ column += yyleng;  return(APC); }
"`"{SCP}?	{ column += yyleng;  scan_idpos(yytext); return(APO); }
"@"		{ column += yyleng;  return(AT);  }
"+"		{ column += yyleng;  return('+'); }
"?"		{ column += yyleng;  return('?'); }

#[0-9][0-9]* { yylval.vlcf.v = atoi((char*)yytext+1); column += yyleng; return(PARSnr); }

#prio        { column += yyleng; return(PARSprio); }

#yacc        { column += yyleng; return(PARSrule); }

#line        { column += yyleng; return(PARSline); }

#col         { column += yyleng; return(PARScol); }

#ignore      { column += yyleng; return(PARSno); }

#left        { column += yyleng; return(PARSleft); }

#right       { column += yyleng; return(PARSright); }

#aux         { column += yyleng; return(PARSaux); }

#yaccadd     { column += yyleng; return(PARSaddrule); }

#mark        { column += yyleng; return(PARSpos); }

'[a-zA-Z0-9 !@#$%^&*\[\]\\{}|()_\-+=~`":;<>,.?/]'{SCP}? {
				  scan_idpos(yytext+2);
				    /* works even if character is $,but
				       character has to be read
				       separately */  
				  yylval.vlcf.v = ctoe((char)yytext[1]);
				  column += yyleng;
				  return(CHARCONST); }
-?[0-9][0-9]*{SCP}?		{ 
				  scan_idpos(yytext);  
				  yylval.vlcf.v = itoe(atoi((char*)yytext));
				  column += yyleng;
				  return(INTCONST); }
\"([a-zA-Z0-9 !@#$%^&*\[\]{}|()_\-+=~`':;<>,.?/]|\\n|\\\"|\\\\)*\"{SCP}?  {
			char *c = (char*)yytext;
/*
	while( *(c++) != '\0' );
	c[-2] = '\0';
*/
			++c; /* skip first " */
			while ( *c != '"' || *(c-1)=='\\' ) ++c;
			*c = '\0';
			scan_idpos(c+1); 
			yylval.vlcf.v = atoe((char*)yytext+1);
			column += yyleng; 
			return(STRINGCONST); }


[a-zA-Z][a-zA-Z0-9_]*{SCP}?	{ scan_idpos(yytext);
				  column += yyleng;  
				  return(IDENT); }
_[a-zA-Z][a-zA-Z0-9_]*{SCP}?	{ scan_idpos(yytext+1);
				  column += yyleng;  
				  return(SORTCONST); }

"/*"	{	char c1, c2 = '+';
			column += yyleng;
			while( 1 ){
				c1 = c2;
				c2 = input();
				if( c2 == '\0' ){
					unput(c2);
					fprintf(stderr,"max: input file ends with unterminated comment\n");
					break;
				}
				if( c1 == '*' && c2 == '/' ){
					column++;
					break;
				}
				if( c2 == '\n' ){
					line++; column = 0;
				} else {
					column++;
				}
			}
		}
"//"	{	char c1, c2 = '+';
			column += yyleng;
			while( 1 ){
				c1 = c2;
				c2 = input();
				if( c2 == '\0' ){
					unput(c2);
					fprintf(stderr,"max: input file ends with unterminated comment\n");
					break;
				}
				if( c2 == '\n' ){
					line++; column = 0;
					break;
				} else {
					column++;
				}
			}
		}

.							 { return(ERRORSYM); }


