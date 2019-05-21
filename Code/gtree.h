#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include "syntax.tab.h"

typedef enum {
	_INIT_, _STRUCTURE_, _VAR_, _FUNC_
} NodeType;

typedef struct Type_* Type;
typedef struct FieldList_* FieldList;

struct Type_ {
	enum { BASIC, ARRAY, STRUCTURE } kind;
	union {
		int basic;	//int = 1; float = 0
		struct { 
			Type elem; int size; 
		} array;
		FieldList structure;
	} u;
	int arr_dim;
};
struct FieldList_ {
	char name[55]; // 域的名字
	Type type; // 域的类型
	FieldList tail; // 下一个域
};
typedef enum {
	Program_Extdeflist,	//1
	Extdeflist_ExtdefExtdeflist, Extdeflist_Null,	//2, 3
	Extdef_SpecifierExtdeclistSemi, Extdef_SpecifierSemi, Extdef_SpcifierFundecCompst,	//4, 5, 6
	Extdeclist_Vardec, Extdeclist_VardecCommaExtdeclist,	//7, 8
	Specifier_Type, Specifier_Structspecifier, 	//9, 10
	StructSpecifier_StructOpttagLcDeflistRc, StructSpecifier_StructTag,	//11, 12
	Opttag_Id, Opttag_Null,	//13, 14
	Tag_Id,	//15
	Vardec_Id, Vardec_VardecLbIntRb,	//16, 17
	Fundec_IdLpVarlistRp, Fundec_IdLpRp,	//18, 19
	Varlist_ParamdecCommaVarlist, Varlist_Paramdec,	//20, 21
	Paramdec_SpecifierVardec,	//22
	Compst_LcDeflistStmtlistRc,	//23
	Stmtlist_StmtStmtlist, Stmtlist_Null,	//24, 25
	Stmt_ExpSemi, Stmt_Compst, Stmt_ReturnExpSemi, Stmt_IfLpExpRpStmt, Stmt_IfLpExpRpStmtElseStmt, Stmt_WhileLpExpRpStmt,
	//26, 27, 28, 29, 30, 31
	Deflist_DefDeflist, Deflist_Null, 	//32, 33
	Def_SpecifierDeclistSemi,	//34
	Declist_Dec, Declist_DecCommaDeclist,	//35, 36
	Dec_Vardec, Dec_VardecAssignopExp,	//37, 38
	Exp_ExpAssignopExp, 	//39
	Exp_ExpAndExp, Exp_ExpOrExp, Exp_ExpRelopExp, //40, 41, 42
	Exp_ExpPlusExp, Exp_ExpMinusExp, Exp_ExpStarExp, Exp_ExpDivExp, //43, 44, 45, 46
	Exp_LpExpRp, 	//47
	Exp_MinusExp, Exp_NotExp, 	//48, 49
	Exp_IdLpArgsRp, Exp_IdLpRp, 	//50, 51
	Exp_ExpLbExpRb, Exp_ExpDotId,	//52, 53
	Exp_Id, Exp_Int, Exp_Float,		//54, 55, 56
	Args_ExpCommaArgs, Args_Exp,	//57, 58
	Terminal
} Rule;


struct node {
	char name[20];
	int lineno;
	union {
		Type type;
		struct {
			Type retType;
			int argc;
			Type* argv;
		}func;
	};
	NodeType n_type;
	Rule rule;
	union {
		char str[100];
		int type_int;
		float type_float;
		char relop[4];
	};
	//struct node* gparent;
	int child_cnt;
	int is_left;
	int arr_dim;
	
	struct node* gchild[10];
};
 
struct node* CreateIntGNode(int int_num, int lineno);
struct node* CreateFloatGNode(float float_num, int lineno);
struct node* CreateIdGNode(char* id, int lineno);
struct node* CreateTypeGNode(char* type, int lineno);
struct node* CreateRelopGNode(int lineno, char* op);
struct node* CreateGNode(char* name, int lineno, NodeType node_t, Rule rule_t, int child_cnt, ...);
int tran(struct node* r, int layer);

int OcttoDec(char* s);
int HextoDec(char* s);
