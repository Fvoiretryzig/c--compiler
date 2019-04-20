#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include "syntax.tab.h"

typedef enum {
	Program_T, ExtDefList_T, ExtDef_T,
	ExtDecList_T, Specifier_T, StructSpecifier_T, 
	OptTag_T, Tag_T, VarDec_T,
	FunDec_T, VarList_T, ParamDec_T,
	CompSt_T, StmtList_T, Stmt_T,
	DefList_T, Def_T, DecList_T, Dec_T, Exp_T, Args_T,
	
	INT_T,
	FLOAT_T,
	ID_T,
	SEMI_T, COMMA_T,
	ASSIGNOP_T, RELOP_T,
	STAR_T, DIV, PLUS, MINUS, 
	AND_T, OR, DOT, NOT,
	TYPE_T,
	LP_T, RP_T, LB_T, RB_T, LC_T, RC_T,
	STRUCT_T, RETURN_T, IF_T, ELSE_T, WHILE_T,	
} NodeType;

typedef enum {
	Program_Extdeflist,
	Extdeflist_ExtdefExtdeflist,
	Extdeflist_Null,
	Extdef_SpecifierExtdeclistSemi, Extdef_SpecifierSemi, Extdef_SpcifierFundecCompst, Extdef_ErrorSemi,
	Extdeclist_Vardec, Extdeclist_VardecCommaExtdeclist,
	Specifier_Type, Specifier_Structspecifier, 
	StructSpecifier_StructOpttagLcDeflistRc, StructSpecifier_StructTag,
	Opttag_Id, Opttag_Null,
	Tag_Id,
	Vardec_Id, Vardec_VardecLbIntRb,
	Fundec_IdLpVarlistRp, IdLpRp,
	Varlist_ParamdecCommaVarlist, Varlist_Paramdec,
	Paramdec_SpecifierVardec,
	Compst_LcDeflistStmtlistRc, Compst_ErrorRc,
	Stmtlist_StmtStmtlist, Stmtlist_Null,
	Stmt_ExpSemi, Stmt_Compst, Stmt_ReturnExpSemi, Stmt_IfLpExpRpStmtElse, Stmt_IfLpExpRpStmtElseStmt, Stmt_WhileLpExpRpStmt, Stmt_ErrorSemi, Stmt_ExpError,
	Deflist_DefDeflist, Deflist_Null, Def_SpecifierDeclistSemi, 
	Def_SpecifierDeclistErrorSemi,
	Declist_Dec, Declist_DecCommaDeclist,
	Dec_Vardec, Dec_VardecAssignopExp,
	Exp_ExpAssignopExp, Exp_ExpAndExp, Exp_ExpOrExp, Exp_ExpRelopExop, Exp_ExpPlusExp, Exp_ExpMinusExp, Exp_ExpStarExp, Exp_ExpDivExp, Exp_LpExpRp, Exp_MinusExp, Exp_NotExp, Exp_IdLpArgsRp, Exp_IdLpRp, Exp_ExpLbExpRb, Exp_ExpDotId, Exp_Id, Exp_Int, Exp_Float, Exp_ExpLbErrorRb,
	Args_ExpCommaArgs, Args_Exp,
	Terminal
} Rule;


struct node {
	char name[20];
	int lineno;
	NodeType type;
	Rule rule;
	union {
		char str[53];
		int type_int;
		float type_float;
	};
	//struct node* gparent;
	int child_cnt;
	struct node* gchild[10];
};
 
struct node* CreateIntGNode(int int_num, int lineno);
struct node* CreateFloatGNode(float float_num, int lineno);
struct node* CreateIdGNode(char* id, int lineno);
struct node* CreateTypeGNode(char* type, int lineno);
struct node* CreateGNode(char* name, int lineno, NodeType node_t, Rule rule_t, int child_cnt, ...);
int tran(struct node* r, int layer);

int OcttoDec(char* s);
int HextoDec(char* s);
