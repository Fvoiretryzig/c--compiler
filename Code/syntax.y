%{
	#include <stdio.h>
	#include <string.h>
	#include "gtree.h"
	#include "lex.yy.c"
	
	void yyerror(const char *s);
	#define YYERROR_VERBOSE
	//#define DEBUG_MSG
	
	 int is_error;

%}
%locations

%union {
	struct node* gnode;
}

%token <gnode> INT
%token <gnode> FLOAT
%token <gnode> ID
%token <gnode> SEMI COMMA
%token <gnode> ASSIGNOP RELOP
%token <gnode> STAR DIV PLUS MINUS 
%token <gnode> AND OR DOT NOT
%token <gnode> TYPE
%token <gnode> LP RP LB RB LC RC
%token <gnode> STRUCT RETURN IF ELSE WHILE
%type <gnode> Program ExtDefList ExtDef ExtDecList Specifier StructSpecifier OptTag Tag VarDec FunDec VarList ParamDec CompSt StmtList Stmt DefList Def DecList Dec Exp Args

%right ASSIGNOP
%left OR
%left AND
%left RELOP 
%left PLUS MINUS
%left STAR DIV
%right NOT
%left DOT
%left LP RP LB RB

%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE
%%
/*High-level Definitions*/
Program		:	ExtDefList {
					#ifdef DEBUG_MSG
					printf("\033[46;37mProgram: ExtDefList(%d)\033[0m\n", @$.first_line);
					#endif
					$$ = CreateGNode("Program", @$.first_line, 1, $1);
					if(!is_error)
						tran($$, 0);

				}
			;
ExtDefList	:	ExtDef ExtDefList {
					#ifdef DEBUG_MSG
					printf("in ExtDefList: child:name1:%s name2:%s\n", $$->gchild[0]->name, $$->gchild[1]->name);
					
					printf("\033[46;37mExtDefList: ExtDef ExtDefList(%d)\033[0m\n", @$.first_line);
					#endif
					$$ = CreateGNode("ExtDefList", @$.first_line, 2, $1, $2);
					
				}
			|	{
					#ifdef DEBUG_MSG
					printf("\033[46;37mExtDefList: EMPTY(%d)\033[0m\n", @$.first_line);
					#endif
					$$ = CreateGNode("ExtDefList", @$.first_line, -1);
				}
			;
ExtDef		:	Specifier ExtDecList SEMI {
					#ifdef DEBUG_MSG
					printf("\033[46;37mExtDef: Specifier ExtDecList SEMI(%d)\033[0m\n", @$.first_line);
					#endif
					$$ = CreateGNode("ExtDef", @$.first_line, 3, $1, $2, $3);
				}
			|	Specifier SEMI {
					#ifdef DEBUG_MSG
					printf("\033[46;37mExtDef: Specifier ExtDeclist(%d)\033[0m\n", @$.first_line);
					#endif
					$$ = CreateGNode("ExtDef", @$.first_line, 2, $1, $2);
				}
			|	Specifier FunDec CompSt {
					#ifdef DEBUG_MSG
					printf("\033[46;37mExtDef: Specifier FunDec CompSt(%d)\033[0m\n", @$.first_line);
					#endif
					$$ = CreateGNode("ExtDef", @$.first_line, 3, $1, $2, $3);
				}
			;
/*error*/
ExtDef		:	error SEMI	{
					is_error = 1;
					#ifdef DEBUG_MSG
					printf("ExtDef: error SEMI\n");
					#endif
				}
			;
ExtDecList	:	VarDec {
					#ifdef DEBUG_MSG
					printf("\033[46;37mExtDecList: VarDec(%d)\033[0m\n", @$.first_line);
					#endif
					$$ = CreateGNode("ExtDecList", @$.first_line, 1, $1);
				}
			|	VarDec COMMA ExtDecList {
					#ifdef DEBUG_MSG
					printf("\033[46;37mExtDecList: VarDec COMMA ExtDecList(%d)\033[0m\n", @$.first_line);
					#endif
					$$ = CreateGNode("ExtDecList", @$.first_line, 3, $1, $2, $3);
				}
			;
/*Specifier*/
Specifier	:	TYPE {
					#ifdef DEBUG_MSG
					printf("\033[46;37mSpecifier: TYPE	(%d)\033[0m\n", @$.first_line);
					#endif
					$$ = CreateGNode("Specifier", @$.first_line, 1, $1);
				}
			|	StructSpecifier {
					#ifdef DEBUG_MSG
					printf("\033[46;37mSpecifier: StructSpecifier(%d)\033[0m\n", @$.first_line);
					#endif
					$$ = CreateGNode("Specifier", @$.first_line, 1, $1);
				}
			;
StructSpecifier	:	STRUCT OptTag LC DefList RC {
						#ifdef DEBUG_MSG
						printf("\033[46;37mStructSpecifier: STRUCT OptTag LC DefList RC(%d)\033[0m\n", @$.first_line);
						#endif
						$$ = CreateGNode("StructSpecifier", @$.first_line, 5, $1, $2, $3, $4, $5);
					}
				|	STRUCT Tag {
						#ifdef DEBUG_MSG
						printf("\033[46;37mStructSpecifier: STRUCT Tag(%d)\033[0m\n", @$.first_line);
						#endif
						$$ = CreateGNode("StructSpecifier", @$.first_line, 2, $1, $2);
					}
				;
OptTag		:	ID {
					#ifdef DEBUG_MSG
					printf("\033[46;37mOptTag: ID:(%d)\033[0m\n", @$.first_line);
					#endif
					$$ = CreateGNode("OptTag", @$.first_line, 1, $1);
				}
			|	{
					#ifdef DEBUG_MSG
					printf("\033[46;37mOptTag: EMPTY(%d)\033[0m\n", @$.first_line);
					#endif
					$$ = CreateGNode("OptTag", @$.first_line, -1);
				}
			;
Tag			:	ID {
					#ifdef DEBUG_MSG
					printf("\033[46;37mTag: ID:(%d)\033[0m\n", @$.first_line);
					#endif
					$$ = CreateGNode("Tag", @$.first_line, 1, $1);
				}
			;
/*Declarators*/
VarDec	:	ID {
				#ifdef DEBUG_MSG
				printf("\033[46;37mVarDec: ID:(%d)\033[0m\n", @$.first_line);
				#endif
				$$ = CreateGNode("VarDec", @$.first_line, 1, $1);
			}
		|	VarDec LB INT RB {
				#ifdef DEBUG_MSG				
				printf("\033[46;37mVarDec: VarDec LB INT RB(%d)\033[0m\n", @$.first_line);
				#endif
				$$ = CreateGNode("VarDec", @$.first_line, 4, $1, $2, $3, $4);
			}
		;
FunDec	:	ID LP VarList RP {
				#ifdef DEBUG_MSG
				printf("\033[46;37mFunDec: ID LP VarList RP(%d)\033[0m\n", @$.first_line);
				#endif
				$$ = CreateGNode("FunDec", @$.first_line, 4, $1, $2, $3, $4);
			}
		|	ID LP RP {
				#ifdef DEBUG_MSG
				printf("\033[46;37mFunDec: ID LP RP(%d)\033[0m\n", @$.first_line);
				#endif
				$$ = CreateGNode("FunDec", @$.first_line, 3, $1, $2, $3);
			}
		;
VarList	:	ParamDec COMMA VarList {
				#ifdef DEBUG_MSG
				printf("\033[46;37mVarList: ParamDec COMMA VarList(%d)\033[0m\n", @$.first_line);
				#endif
				$$ = CreateGNode("VarList", @$.first_line, 3, $1, $2, $3);
			}
		|	ParamDec {
				#ifdef DEBUG_MSG
				printf("\033[46;37mVarList: ParaDec(%d)\033[0m\n", @$.first_line);
				#endif
				$$ = CreateGNode("VarList", @$.first_line, 1, $1);
			}
		;
ParamDec:	Specifier VarDec {
				#ifdef DEBUG_MSG
				printf("\033[46;37mParamDec: Specifier VarDec(%d)\033[0m\n", @$.first_line);
				#endif
				$$ = CreateGNode("ParamDec", @$.first_line, 2, $1, $2);
			}
		;
/*Statements*/
CompSt	:	LC DefList StmtList RC {
				#ifdef DEBUG_MSG
				printf("\033[46;37mCompSt: LC DefList StmtList RC(%d)\033[0m\n", @$.first_line);
				#endif
				$$ = CreateGNode("CompSt", @$.first_line, 4, $1, $2, $3, $4);
			}
		;
/*error*/
CompSt	:	error RC {
				#ifdef DEBUG_MSG
				printf("\033[46;37mCompSt: error RC(%d)\033[0m\n", @$.first_line);
				#endif
				is_error = 1;
			}
StmtList:	Stmt StmtList {
				#ifdef DEBUG_MSG
				printf("\033[46;37mStmtList: Stmt StmtList(%d)\033[0m\n", @$.first_line);
				#endif
				$$ = CreateGNode("StmtList", @$.first_line, 2, $1, $2);
			}
		|	{
				#ifdef DEBUG_MSG
				printf("\033[46;37mStmtList: EMPTY(%d)\033[0m\n", @$.first_line);
				#endif
				$$ = CreateGNode("StmtList", @$.first_line, -1);
			}
		;
Stmt	:	Exp SEMI {
				#ifdef DEBUG_MSG
				printf("\033[46;37mStmt: Exp SEMI(%d)\033[0m\n", @$.first_line);
				#endif
				$$ = CreateGNode("Stmt", @$.first_line, 2, $1, $2);
			}
		|	CompSt {
				#ifdef DEBUG_MSG
				printf("\033[46;37mStmt: CompSt(%d)\033[0m\n", @$.first_line);
				#endif
				$$ = CreateGNode("Stmt",@$.first_line, 1, $1);
			}
		|	RETURN Exp SEMI {
				#ifdef DEBUG_MSG
				printf("\033[46;37mStmt: RETURN Exp SEMI(%d)\033[0m\n", @$.first_line);
				#endif
				$$ = CreateGNode("Stmt", @$.first_line, 3, $1, $2, $3);
			}
		/*|	IF LP Exp RP Stmt {
				printf("\033[46;37mStmt: IF LP Exp RP Stmt(%d)\033[0m\n", @$.first_line);
				$$ = CreateGNode("Stmt", @$.first_line, 5, $1, $2, $3, $4, $5);
			}*/
		|	IF LP Exp RP Stmt %prec LOWER_THAN_ELSE {
				#ifdef DEBUG_MSG
				printf("\033[46;37mStmt: IF LP Exp RP Stmt prec LOWER_THAN_ELSE(%d)\033[0m\n", @$.first_line);
				#endif
				$$ = CreateGNode("Stmt", @$.first_line, 5, $1, $2, $3, $4, $5);
			}
		|	IF LP Exp RP Stmt ELSE Stmt {
				#ifdef DEBUG_MSG
				printf("\033[46;37mStmt: IF LP Exp RP Stmt ELSE Stmt(%d)\033[0m\n", @$.first_line);
				#endif
				$$ = CreateGNode("Stmt", @$.first_line, 7, $1, $2, $3, $4, $5, $6, $7);
			}
		|	WHILE LP Exp RP Stmt {
				#ifdef DEBUG_MSG
				printf("\033[46;37mStmt: WHILE LP Exp RP Stmt(%d)\033[0m\n", @$.first_line);
				#endif
				$$ = CreateGNode("Stmt", @$.first_line, 5, $1, $2, $3, $4, $5);
			}
		;
/*error*/
Stmt	:	error SEMI	{
				#ifdef DEBUG_MSG
				printf("\033[47;32mERROR: stmt: error SEMI in line %d\033[0m \n", @$.first_line-1);
				#endif
				is_error = 1;
			}
		|	Exp error	{
				#ifdef DEBUG_MSG
				printf("\033[47;32mERROR: stmt: Exp error in line %d\033[0m \n", @$.first_line);
				#endif
				is_error = 1;
				#ifdef DEBUG_MSG
				printf("\033[47;32mis_error in line %d\033[0m \n", @$.first_line);
				#endif
			}
		;
/*Local definitions*/
DefList	:	Def DefList	{
				#ifdef DEBUG_MSG
				printf("\033[46;37mDefList: Def DefList(%d)\033[0m\n", @$.first_line);
				#endif
				$$ = CreateGNode("DefList", @$.first_line, 2, $1, $2);
			}
		|	{
				#ifdef DEBUG_MSG
				printf("\033[46;37mDefList: EMPTY(%d)\033[0m\n", @$.first_line);
				#endif
				$$ = CreateGNode("DefList", @$.first_line, -1);
			}
		;	
Def		:	Specifier DecList SEMI {
				#ifdef DEBUG_MSG
				printf("\033[46;37mDef: Specifier DecList SEMI(%d)\033[0m\n", @$.first_line);
				#endif
				$$ = CreateGNode("Def", @$.first_line, 3, $1, $2, $3);
			}
		;
/*error*/
Def		:	Specifier DecList error SEMI	{
				#ifdef DEBUG_MSG
				printf("D\n");
				#endif
				is_error = 1;
			}
		;
DecList	:	Dec	{
				#ifdef DEBUG_MSG
				printf("\033[46;37mDecList: Dec(%d)\033[0m\n", @$.first_line);
				#endif
				$$ = CreateGNode("DecList", @$.first_line, 1, $1);
			}
		|	Dec COMMA DecList {
				#ifdef DEBUG_MSG
				printf("\033[46;37mDecList: Dec COMMA DecList(%d)\033[0m\n", @$.first_line);
				#endif
				$$ = CreateGNode("DecList", @$.first_line, 3, $1, $2, $3);
			}
		;
Dec		:	VarDec {
				#ifdef DEBUG_MSG
				printf("\033[46;37mDec: VarDec(%d)\033[0m\n", @$.first_line);
				#endif
				$$ = CreateGNode("Dec", @$.first_line, 1, $1);
			}
		|	VarDec ASSIGNOP Exp{
				#ifdef DEBUG_MSG
				printf("\033[46;37mDec: VarDec ASSIGNOP Exp(%d)\033[0m\n", @$.first_line);
				#endif
				$$ = CreateGNode("Dec", @$.first_line, 3, $1, $2, $3);
			}
		;

/*Expressions*/
Exp	:	Exp ASSIGNOP Exp {
			#ifdef DEBUG_MSG
			printf("\033[46;37mExp: Exp ASSIGNOP Exp(%d)\033[0m\n", @$.first_line);
			#endif
			$$ = CreateGNode("Exp", @$.first_line, 3, $1, $2, $3);
		}
	|	Exp AND	Exp {
			#ifdef DEBUG_MSG
			printf("\033[46;37mExp: Exp AND Exp(%d)\033[0m\n", @$.first_line);
			#endif
			$$ = CreateGNode("Exp", @$.first_line, 3, $1, $2, $3);
		}
	|	Exp OR Exp {
			#ifdef DEBUG_MSG
			printf("\033[46;37mExp: Exp OR Exp(%d)\033[0m\n", @$.first_line);
			#endif
			$$ = CreateGNode("Exp", @$.first_line, 3, $1, $2, $3);
		}
	|	Exp RELOP Exp {
			#ifdef DEBUG_MSG
			printf("\033[46;37mExp: Exp RELOP Exp(%d)\033[0m\n", @$.first_line);
			#endif
			$$ = CreateGNode("Exp", @$.first_line, 3, $1, $2, $3);
		}
	|	Exp PLUS Exp {
			#ifdef DEBUG_MSG
			printf("\033[46;37mExp: Exp PLUS Exp(%d)\033[0m\n", @$.first_line);
			#endif
			$$ = CreateGNode("Exp", @$.first_line, 3, $1, $2, $3);
		}
	|	Exp MINUS Exp {
			#ifdef DEBUG_MSG
			printf("\033[46;37mExp: Exp MINUS Exp(%d)\033[0m\n", @$.first_line);
			#endif
			$$ = CreateGNode("Exp", @$.first_line, 3, $1, $2, $3);
		}
	|	Exp STAR Exp {
			#ifdef DEBUG_MSG
			printf("\033[46;37mExp: Exp STAR Exp(%d)\033[0m\n", @$.first_line);
			#endif
			$$ = CreateGNode("Exp", @$.first_line, 3, $1, $2, $3);
		}
	|	Exp DIV Exp {
			#ifdef DEBUG_MSG
			printf("\033[46;37mExp: Exp DIV Exp(%d)\033[0m\n", @$.first_line);
			#endif
			$$ = CreateGNode("Exp", @$.first_line, 3, $1, $2, $3);
		}
	|	LP Exp RP {
			#ifdef DEBUG_MSG
			printf("\033[46;37mExp: LP Exp RP(%d)\033[0m\n", @$.first_line);
			#endif
			$$ = CreateGNode("Exp", @$.first_line, 3, $1, $2, $3);
		}
	|	MINUS Exp {
			#ifdef DEBUG_MSG
			printf("\033[46;37mExp: MINUS Exp(%d)\033[0m\n", @$.first_line);
			#endif
			$$ = CreateGNode("Exp", @$.first_line, 2, $1, $2);
		}
	|	NOT Exp {
			#ifdef DEBUG_MSG
			printf("\033[46;37mExp: NOT Exp(%d)\033[0m\n", @$.first_line);
			#endif
			$$ = CreateGNode("Exp", @$.first_line, 2, $1, $2);
		}
	|	ID LP Args RP {
			#ifdef DEBUG_MSG
			printf("\033[46;37mExp: ID LP Args RP(%d)\033[0m\n", @$.first_line);
			#endif
			$$ = CreateGNode("Exp", @$.first_line, 4, $1, $2, $3, $4);
		}
	|	ID LP RP {
			#ifdef DEBUG_MSG
			printf("\033[46;37mExp: ID LP RP(%d)\033[0m\n", @$.first_line);
			#endif
			$$ = CreateGNode("Exp", @$.first_line, 3, $1, $2, $3);
		}
	|	Exp LB Exp RB {
			#ifdef DEBUG_MSG
			printf("\033[46;37mExp: Exp LB Exp RB(%d)\033[0m\n", @$.first_line);
			#endif
			$$ = CreateGNode("Exp", @$.first_line, 4, $1, $2, $3, $4);
		}
	|	Exp DOT ID {
			#ifdef DEBUG_MSG
			printf("\033[46;37mExp: Exp DOT ID	(%d)\033[0m\n", @$.first_line);
			#endif
			$$ = CreateGNode("Exp", @$.first_line, 3, $1, $2, $3);
		}
	|	ID {
			#ifdef DEBUG_MSG
			printf("\033[46;37mExp: ID	(%d)\033[0m\n", @$.first_line);
			#endif
			$$ = CreateGNode("Exp", @$.first_line, 1, $1);
		}
	|	INT {	
			#ifdef DEBUG_MSG
			printf("\033[46;37mExp: INT (%d)\033[0m\n", @$.first_line);
			#endif
			$$ = CreateGNode("Exp", @$.first_line, 1, $1);
		}
	|	FLOAT {
			#ifdef DEBUG_MSG
			printf("\033[46;37mExp: FLOAT (%d)\033[0m\n", @$.first_line);
			#endif
			$$ = CreateGNode("Exp", @$.first_line, 1, $1);
		}
	;
/*error*/
Exp		:	/*error Exp{
				#ifdef DEBUG_MSG
				printf("\033[46;37mExp: error exp (%d)\033[0m\n", @$.first_line);
				#endif
				is_error = 1;
			}*/	
			Exp LB error RB {
				#ifdef DEBUG_MSG
				printf("\033[46;37mExp: exp LB error RB (%d)\033[0m\n", @$.first_line);
				#endif
				is_error = 1;
				//yyerror("unexpected ']'");
			}
Args:	Exp COMMA Args {
			#ifdef DEBUG_MSG
			printf("\033[46;37mArgs: Exp COMMA Args(%d)\033[0m\n", @$.first_line);
			#endif
			$$ = CreateGNode("Args", @$.first_line, 3, $1, $2, $3);
		}
	|	Exp {
			#ifdef DEBUG_MSG
			printf("\033[46;37mArgs: Exp(%d)\033[0m\n", @$.first_line);
			#endif
			$$ = CreateGNode("Args", @$.first_line, 1, $1);
		}
	;
%%
void yyerror(const char *s)
{
	//fprintf (stderr, "\033[47;31mError type B at Line %d %s\033[0m\n", yylineno, s);
	fprintf (stderr, "Error type B at Line %d: %s.\n", yylineno, s);
}
