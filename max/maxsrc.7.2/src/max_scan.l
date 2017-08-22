%{
#define TABLENGTH 8

int   line   =  1 ;
static int   column =  0 ;

%}
%%

[ ]*		{ column += yyleng; }
\n		{ line++; column = 0; }
\t		{ column += TABLENGTH; }
"PRD"		{ column += yyleng;  return(PRD); }
"FCT"		{ column += yyleng;  return(FCT); }
"ATT"		{ column += yyleng;  return(ATT); }
"STRUC"		{ column += yyleng;  return(STRUC); }
"CND"		{ column += yyleng;  return(CND); }
"LET"		{ column += yyleng;  return(LET); }
"IF"		{ column += yyleng;  return(IF); }
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
"`"		{ column += yyleng;  return(APO); }
"@"		{ column += yyleng;  return(AT);  }
"+"		{ column += yyleng;  return('+'); }
"?"		{ column += yyleng;  return('?'); }

#[0-9][0-9]* { yylval.vlc.v = atoi((char*)yytext+1); column += yyleng; return(PARSnr); }

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

'[a-zA-Z0-9 !@#$%^&*\[\]\\{}|()_\-+=~`":;<>,.?/]' {
						  yylval.vlc.v = ctoe((char)yytext[1]);
						  yylval.vlc.l = itoe(line);
						  yylval.vlc.c = itoe(column+1);
						  column += yyleng;  
						  return(CHARCONST); }
-?[0-9][0-9]*					{ yylval.vlc.v = itoe(atoi((char*)yytext));
						  yylval.vlc.l = itoe(line);
						  yylval.vlc.c = itoe(column+1);
						  column += yyleng;  
						  return(INTCONST); }
\"([a-zA-Z0-9 !@#$%^&*\[\]{}|()_\-+=~`':;<>,.?/]|\\n|\\\"|\\\\)*\"	{
							  char *c = (char*)yytext;
                              while( *(c++) != '\0' );
                              c[-2] = '\0';
						  yylval.vlc.v = atoe((char*)yytext+1);
						  yylval.vlc.l = itoe(line);
						  yylval.vlc.c = itoe(column+1);
						  column += yyleng;  
						  return(STRINGCONST); }
[a-zA-Z][a-zA-Z0-9_]*		{ yylval.vlc.v = stoid(atoe((char*)yytext));
				  yylval.vlc.l = itoe(line);
				  yylval.vlc.c = itoe(column+1);
				  column += yyleng;  
				  return(IDENT); }
_[a-zA-Z][a-zA-Z0-9_]*		{ yylval.vlc.v = stoid(atoe((char*)yytext+1));
				  yylval.vlc.l = itoe(line);
				  yylval.vlc.c = itoe(column+1);
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


