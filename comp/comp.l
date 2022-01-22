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

[0-9]+	{number = atoi(yytext); yylval = makeLeafNode(number); return NUM;}
"+"	{return *yytext;}
"-"	{return *yytext;}
"*"	{return *yytext;}
"/"	{return *yytext;}
[ \t]	{}
[()]	{return *yytext;}
[\n]	{return *yytext;}
.	{yyerror("unknown character\n");exit(1);}

%%

int yywrap(void) {
	return 1;
}
