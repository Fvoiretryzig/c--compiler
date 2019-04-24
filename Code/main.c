#include <stdio.h>

#include "syntax.tab.h"
#include "semantic.h"
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
	printf("after semantic analysis\n");
	return 0;
}
