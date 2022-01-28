%{
	#include <stdlib.h>
	#include <stdio.h>
	#include "exptree.h"
#define YYSTYPE tnode*
	#include "y.tab.h"
void yyerror(char const*);
	int number;
%}

%%

"begin"  {return BEGINN;}
"end"  {return END;}
"read"  {return READ;}
"write" {return WRITE;}
[0-9]+	{number = atoi(yytext); yylval = makeNode(0, NULL, number, 0, NULL, NULL); return NUM;}
[a-z]   {yylval = makeNode(0, yytext, 0, 0, NULL, NULL); return ID;}
"+"	{return *yytext;}
"-"	{return *yytext;}
"*"	{return *yytext;}
"/"	{return *yytext;}
"="	{return *yytext;}
";"	{return *yytext;}
[ \t]	{}
[()]	{return *yytext;}
[\n]	{}
.	{yyerror("unknown character\n");exit(1);}

%%

int yywrap(void) {
	return 1;
}
