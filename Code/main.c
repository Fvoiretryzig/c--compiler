#include <stdio.h>

#include "syntax.tab.h"
#include "semantic.h"
#include "ir.h"
//#define DEBUG
extern FILE* yyin;
extern int yydebug;
extern void yyrestart(FILE * file);

extern int yylineno;

extern int is_error;

extern struct node* root;
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
	
	init_table();
	semantic_analysis(root);
	init_irtranslate();
	print(root);
	//printf("\033[43;37mafter semantic analysis\033[0m\n");
	return 0;
}
