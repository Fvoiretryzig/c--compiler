#include <stdio.h>

#include "syntax.tab.h"
#include "gtree.h"
//#define DEBUG
extern FILE* yyin;
extern int yydebug;
extern void yyrestart(FILE * file);

extern int yylineno;

extern int is_error;
int main(int argc, char** argv) {
	if(argc > 1) {
		if(!(yyin = fopen(argv[1], "r"))) {
			perror(argv[1]);
			return 1;	
		}	
	}
	yyrestart(yyin);
	#ifdef DEBUG
	yydebug = 1;
	#endif
	is_error = 0;
	yyparse();
	//yylex();
	//printf("this is the end\n");
	return 0;
}
