%{
#include <stdio.h>
#include <stdlib.h>
    int lastReg = 0;
    FILE* tar_file;
#include "exptree.h"
#include "exptree.c"
#define YYSTYPE tnode*
    int yylex(void);
    void yyerror(char const*);
    %}

%token NUM
%left '+' '-'
%left '*' '/'

%%

program : expr '\n' { int k = generateCode($1); printf("COMPLETED\n");};
expr : expr '+' expr { $$ = makeOperatorNode('+',$1,$3);}
| expr '-' expr { $$ = makeOperatorNode('-',$1,$3);}
| expr '*' expr { $$ = makeOperatorNode('*',$1,$3);}
| expr '/' expr { $$ = makeOperatorNode('/',$1,$3);}
| '(' expr ')' { $$ = $2; }
| NUM { $$ = $1; }
;

%%

void yyerror(char const *s){
    printf("Error parsing : %s\n", s);
}

int main(void){
    tar_file = fopen("output.xsm", "w");
    int *ptr;
    fprintf(tar_file, "0\n");
    fprintf(tar_file, "2056\n");
    ptr = (int*)malloc(sizeof(int));
    *ptr = 0;
    while((*ptr)++ < 6)
	fprintf(tar_file, "0\n");
    free(ptr);
    yyparse();
    fprintf(tar_file, "INT 10\n");
    return 1;
}
