#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include "syntax.tab.h"

typedef enum {
	_INIT_, _BASIC_, _ARRAY_, _STRUCTURE_, _VAR_, _FUNC_
} NodeType;

typedef enum {
	Program_Extdeflist,
	Extdeflist_ExtdefExtdeflist, Extdeflist_Null,
	Extdef_SpecifierExtdeclistSemi, Extdef_SpecifierSemi, Extdef_SpcifierFundecCompst,
	Extdeclist_Vardec, Extdeclist_VardecCommaExtdeclist,
	Specifier_Type, Specifier_Structspecifier, 
	StructSpecifier_StructOpttagLcDeflistRc, StructSpecifier_StructTag,
	Opttag_Id, Opttag_Null,
	Tag_Id,
	Vardec_Id, Vardec_VardecLbIntRb,
	Fundec_IdLpVarlistRp, Fundec_IdLpRp,
	Varlist_ParamdecCommaVarlist, Varlist_Paramdec,
	Paramdec_SpecifierVardec,
	Compst_LcDeflistStmtlistRc,
	Stmtlist_StmtStmtlist, Stmtlist_Null,
	Stmt_ExpSemi, Stmt_Compst, Stmt_ReturnExpSemi, Stmt_IfLpExpRpStmtElse, Stmt_IfLpExpRpStmtElseStmt, Stmt_WhileLpExpRpStmt,
	Deflist_DefDeflist, Deflist_Null, 
	Def_SpecifierDeclistSemi,
	Declist_Dec, Declist_DecCommaDeclist,
	Dec_Vardec, Dec_VardecAssignopExp,
	Exp_ExpAssignopExp, Exp_ExpAndExp, Exp_ExpOrExp, Exp_ExpRelopExp, Exp_ExpPlusExp, Exp_ExpMinusExp, Exp_ExpStarExp, Exp_ExpDivExp, Exp_LpExpRp, Exp_MinusExp, Exp_NotExp, Exp_IdLpArgsRp, Exp_IdLpRp, Exp_ExpLbExpRb, Exp_ExpDotId, Exp_Id, Exp_Int, Exp_Float,
	Args_ExpCommaArgs, Args_Exp,
	Terminal
} Rule;


struct node {
	char name[20];
	int lineno;
	union {
		Type type;
		struct func {
			Type retType;
			int argc;
			Type* argv;
		};
	} u;
	NodeType n_type;
	Rule rule;
	union {
		char str[53];
		int type_int;
		float type_float;
		char relop[4];
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
