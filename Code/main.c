#include <stdio.h>

#include "syntax.tab.h"
#include "semantic.h"
#include "gen_obj.h"

//#define DEBUG
extern FILE* yyin;
extern int yydebug;
extern void yyrestart(FILE * file);

extern int yylineno;

extern int is_error;

char filename[100];
extern struct node* root;
int main(int argc, char** argv) {
	if(argc > 1) {
		if(!(yyin = fopen(argv[1], "r"))) {
			perror(argv[1]);
			return 1;	
		}	
	}
	if(argv[2])
		strcpy(filename, argv[2]);
	//printf("filename: %s\n", filename);
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
	init_gen();
	gen_obj();
	//printf("\033[43;37mafter semantic analysis\033[0m\n");
	return 0;
}
