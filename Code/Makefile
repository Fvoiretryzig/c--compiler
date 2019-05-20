nodebug:lexical.l syntax.y 
	bison -d syntax.y
	flex lexical.l
	gcc gtree.c symbol_table.c semantic.c syntax.tab.c ir.c main.c -lfl -ly -o parser
debug:lexical.l syntax.y
	bison -d -t -v syntax.y
	flex lexical.l
	gcc gtree.c symbol_table.c semantic.c syntax.tab.c ir.c main.c -lfl -ly -o ../parser
clean:
	rm syntax.tab.c lex.yy.c syntax.tab.h
