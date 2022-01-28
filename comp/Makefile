CC = gcc
CFLAGS = -g -fcommon
LEX = lex
YACC = yacc

default: comp

comp: lex.yy.c y.tab
		$(CC) lex.yy.c y.tab.c -o comp

lex.yy.c: y.tab
		$(LEX) comp.l

y.tab: comp.y
		$(YACC) -d comp.y
