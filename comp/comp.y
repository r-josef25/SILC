%{
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
    int lastReg = 0;
    bool in_read_asmnt = false;
    FILE* tar_file;
#include "exptree.h"
#include "exptree.c"
#define YYSTYPE tnode*
    int yylex(void);
    void yyerror(char const*);
    %}

%token NUM ID BEGINN END READ WRITE
%left '+' '-'
%left '*' '/'

%%

program : BEGINN stmts END { printf("Tree Generated\n"); int k = generateCode($2); printf("COMPLETED\n");}
|BEGINN END {printf("COMPLETED\n");}
;
stmts  : stmts stmt {$$ = makeNode(3, NULL, 0, 0, $1, $2);}
| stmt { $$ = $1; };
;
stmt : ID '=' expr ';'{ $$ = makeNode(4, NULL, 0, 0, $1, $3);}
| READ '(' ID ')' ';'{ $$ = makeNode(1, NULL, 0, 0, $3, NULL);}
| WRITE '(' expr ')' ';'{ $$ = makeNode(2, NULL, 0, 0, $3, NULL);}
;
expr : expr '+' expr { $$ = makeNode(5, NULL, 0, 0, $1, $3);}
| expr '-' expr { $$ = makeNode(6, NULL, 0, 0, $1, $3);}
| expr '*' expr { $$ = makeNode(7, NULL, 0, 0, $1, $3);}
| expr '/' expr { $$ = makeNode(8, NULL, 0, 0, $1, $3);}
| '(' expr ')' { $$ = $2; }
| NUM { $$ = $1; }
| ID { $$ = $1; }
;

%%

void yyerror(char const *s){
    printf("Error parsing : %s\n", s);
}

int main(void){
    tar_file = fopen("stg2.xsm", "w");
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
