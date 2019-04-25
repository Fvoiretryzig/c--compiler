#include "semantic.h"

#define DEBUG_SEMANTIC

int top = -1;
void semantic_analysis(struct node* n) {
	if(n == NULL)
		return;
	switch(n->rule) {
		case Program_Extdeflist: F_Program_Extdeflist(n); break;
		case Extdeflist_ExtdefExtdeflist: F_Extdeflist_ExtdefExtdeflist(n); break;
		case Extdeflist_Null: F_Extdeflist_Null(n); break;
		case Extdef_SpecifierExtdeclistSemi: F_Extdef_SpecifierExtdeclistSemi(n); break;
		case Extdef_SpecifierSemi: F_Extdef_SpecifierSemi(n); break;
		case Extdef_SpcifierFundecCompst: F_Extdef_SpcifierFundecCompst(n); break;
		case Extdeclist_Vardec: F_Extdeclist_Vardec(n); break;
		case Extdeclist_VardecCommaExtdeclist: F_Extdeclist_VardecCommaExtdeclist(n); break;
		case Specifier_Type: F_Specifier_Type(n); break;
		case Specifier_Structspecifier: F_Specifier_Structspecifier(n); break;
		case StructSpecifier_StructOpttagLcDeflistRc: F_StructSpecifier_StructOpttagLcDeflistRc(n); break;
		case StructSpecifier_StructTag: F_StructSpecifier_StructTag(n); break;
		case Opttag_Id: F_Opttag_Id(n); break;
		case Opttag_Null: F_Opttag_Null(n); break;
		case Tag_Id: F_Tag_Id(n); break;
		case Vardec_Id: F_Vardec_Id(n); break;
		case Vardec_VardecLbIntRb: F_Vardec_VardecLbIntRb(n); break;
		case Fundec_IdLpVarlistRp: F_Fundec_IdLpVarlistRp(n); break;
		case Fundec_IdLpRp: F_Fundec_IdLpRp(n); break;
		case Varlist_ParamdecCommaVarlist: F_Varlist_ParamdecCommaVarlist(n); break;
		case Varlist_Paramdec: F_Varlist_Paramdec(n); break;
		case Paramdec_SpecifierVardec: F_Paramdec_SpecifierVardec(n); break;
		case Compst_LcDeflistStmtlistRc: F_Compst_LcDeflistStmtlistRc(n); break;
		case Stmtlist_StmtStmtlist: F_Stmtlist_StmtStmtlist(n); break;
		case Stmtlist_Null: F_Stmtlist_Null(n); break;
		case Stmt_ExpSemi: F_Stmt_ExpSemi(n); break;
		case Stmt_Compst: F_Stmt_Compst(n); break;
		case Stmt_ReturnExpSemi: F_Stmt_ReturnExpSemi(n); break;
		case Stmt_IfLpExpRpStmt: F_Stmt_IfLpExpRpStmt(n); break;
		case Stmt_IfLpExpRpStmtElseStmt: F_Stmt_IfLpExpRpStmtElseStmt(n); break;
		case Stmt_WhileLpExpRpStmt: F_Stmt_WhileLpExpRpStmt(n); break;
		case Deflist_DefDeflist: F_Deflist_DefDeflist(n); break;
		case Deflist_Null: F_Deflist_Null(n); break;
		case Def_SpecifierDeclistSemi: F_Def_SpecifierDeclistSemi(n); break;
		case Declist_Dec: F_Declist_Dec(n); break;
		case Declist_DecCommaDeclist: F_Declist_DecCommaDeclist(n); break;
		case Dec_Vardec: F_Dec_Vardec(n); break;
		case Dec_VardecAssignopExp: F_Dec_VardecAssignopExp(n); break;
		case Exp_ExpAssignopExp: F_Exp_ExpAssignopExp(n); break;
		case Exp_ExpAndExp: F_Exp_ExpAndExp(n); break;
		case Exp_ExpOrExp: F_Exp_ExpOrExp(n); break;
		case Exp_ExpRelopExp: F_Exp_ExpRelopExp(n); break;
		case Exp_ExpPlusExp: F_Exp_ExpPlusExp(n); break;
		case Exp_ExpMinusExp: F_Exp_ExpMinusExp(n); break;
		case Exp_ExpStarExp: F_Exp_ExpStarExp(n); break;	
		case Exp_ExpDivExp: F_Exp_ExpDivExp(n); break;
		case Exp_LpExpRp: F_Exp_LpExpRp(n); break;
		case Exp_MinusExp: F_Exp_MinusExp(n); break;
		case Exp_NotExp: F_Exp_NotExp(n); break;
		case Exp_IdLpArgsRp: F_Exp_IdLpArgsRp(n); break;
		case Exp_IdLpRp: F_Exp_IdLpRp(n); break;
		case Exp_ExpLbExpRb: F_Exp_ExpLbExpRb(n); break;
		case Exp_ExpDotId: F_Exp_ExpDotId(n); break;
		case Exp_Id: F_Exp_Id(n); break;
		case Exp_Int: F_Exp_Int(n); break;
		case Exp_Float: F_Exp_Float(n); break;
		case Args_ExpCommaArgs: F_Args_ExpCommaArgs(n); break;
		case Args_Exp: F_Args_Exp(n); break;
	}
	return;
}
int isEqual(Type a, Type b) {
	//数组判断不太对
	if(a->kind != b->kind && (a->kind != ARRAY || b->kind != ARRAY)) { 
		if(a->kind == ARRAY) {
			Type tmp = a->u.array.elem;
			while(tmp->kind == ARRAY) {
				tmp = tmp->u.array.elem;
			}
			if(tmp->kind != b->kind) 
				return 0;
		}
		else if(b->kind = ARRAY) {
			Type tmp = a->u.array.elem;
			while(tmp->kind == ARRAY) {
				tmp = tmp->u.array.elem;
			}
			if(tmp->kind != a->kind)
				return 0;
		}
		else {
			printf("a->kind: %d b->kind:%d\n", a->kind, b->kind);
			return 0;
		}
	}
	else {
		if(a->kind == BASIC) {
			if(a->u.basic != b->u.basic)
				return 0;
		}
		else if(a->kind == ARRAY) {
			if(!isEqual(a->u.array.elem, b->u.array.elem))
				return 0;
			/*if(a->u.array.size != b->u.array.size)
				return 0;*/
		}
		else if(a->kind == STRUCTURE) {
			if(!isEqual(a->u.structure->type, b->u.structure->type))
				return 0;
		}
	}
	return 1;
}
void F_Program_Extdeflist(struct node* n){
	#ifdef DEBUG_SEMANTIC
	printf("this is F_Program_Extdeflist\n");
	#endif

	struct node* Extdeflist = n->gchild[0];
	
	semantic_analysis(Extdeflist);
	
	return;
}
void F_Extdeflist_ExtdefExtdeflist(struct node* n){
	#ifdef DEBUG_SEMANTIC
	printf("this is F_Extdeflist_ExtdefExtdeflist\n");
	#endif

	struct node* Extdef = n->gchild[0];
	struct node* Extdeflist = n->gchild[1];
	
	semantic_analysis(Extdef);
	if(Extdeflist != NULL)
		semantic_analysis(Extdeflist);
	
	return;
}
void F_Extdeflist_Null(struct node* n){
	//No Extdef
}
void F_Extdef_SpecifierExtdeclistSemi(struct node* n){
	#ifdef DEBUG_SEMANTIC
	printf("this is F_Extdef_SpecifierExtdeclistSemi\n");
	#endif

	struct node* Specifier = n->gchild[0];
	struct node* Extdeclist = n->gchild[1];
	
	semantic_analysis(Specifier);
	Extdeclist->type = Specifier->type;
	semantic_analysis(Extdeclist);
	
	return;
}
void F_Extdef_SpecifierSemi(struct node* n){
	#ifdef DEBUG_SEMANTIC
	printf("this is F_Extdef_SpecifierSemi\n");
	#endif

	struct node* Specifier = n->gchild[0];
	
	semantic_analysis(Specifier);
	
	return;
}
void F_Extdef_SpcifierFundecCompst(struct node* n){
	#ifdef DEBUG_SEMANTIC
	printf("this is F_Extdef_SpcifierFundecCompst\n");
	#endif

	struct node* Specifier = n->gchild[0];
	struct node* Fundec = n->gchild[1];
	struct node* Compst = n->gchild[2];
	
	semantic_analysis(Specifier);
	Fundec->func.retType = Specifier->type;
	semantic_analysis(Fundec);
	Compst->func.retType = Specifier->type;
	semantic_analysis(Compst);
	
	return;
}
void F_Extdeclist_Vardec(struct node* n){
	#ifdef DEBUG_SEMANTIC
	printf("this is F_Extdeclist_Vardec\n");
	#endif

	struct node* Vardec = n->gchild[0];
	
//	Vardec->type = n->type;
	semantic_analysis(Vardec);
	return;
}
void F_Extdeclist_VardecCommaExtdeclist(struct node* n){
	#ifdef DEBUG_SEMANTIC
	printf("this is F_Extdeclist_VardecCommaExtdeclist\n");
	#endif

	struct node* Vardec = n->gchild[0];
	struct node* Extdeclist = n->gchild[2];
	
	semantic_analysis(Vardec);
	semantic_analysis(Extdeclist);
	
	return;
}
void F_Specifier_Type(struct node* n){
	#ifdef DEBUG_SEMANTIC
	printf("this is F_Specifier_Type\n");
	#endif
	struct node* ttype = n->gchild[0];
	char* basic_type = ttype->str;
	
	if(!strcmp(basic_type, "int")) {
		n->type = (Type)malloc(sizeof(struct Type_));
		n->type->kind = BASIC;
		n->type->u.basic = 1;
	}
	else if(!strcmp(basic_type, "float")) {
		n->type = (Type)malloc(sizeof(struct Type_));
		n->type->kind = BASIC;
		n->type->u.basic = 0;
	}
	return;
}
void F_Specifier_Structspecifier(struct node* n){
	#ifdef DEBUG_SEMANTIC
	printf("this is F_Specifier_Structspecifier\n");
	#endif
	struct node* Structspecifier = n->gchild[0];
	
	semantic_analysis(Structspecifier);
	n->type = Structspecifier->type;
	
	return;
}
void F_StructSpecifier_StructOpttagLcDeflistRc(struct node* n){
	#ifdef DEBUG_SEMANTIC
	printf("this is F_StructSpecifier_StructOpttagLcDeflistRc\n");
	#endif
	//两种情况判断
	struct node* Opttag = n->gchild[1];
	struct node* Deflist = n->gchild[3];
	int no_name = 0;
	char name[60];
	if(Opttag != NULL) {
		semantic_analysis(Opttag);
		strcpy(name, Opttag->str);
	}
	else { 
		no_name = 1;
	}
	if(!no_name)
		strcpy(n->str, name);
	Type t = (Type) malloc(sizeof(struct Type_));
	t->kind = STRUCTURE;
	t->u.structure = tmp_table[++top];
	n->type = t;
	n->n_type = _STRUCTURE_;
	tmp_table[top] = NULL;
	
	if(!no_name) {
		Symbol sym = find_symbol(name);
		if(sym != (Symbol)NULL) {	//类型和变量重名?
			printf("Error type 16 at Line %d: Duplicated name \"%s\".\n", n->lineno, name);
			return;
		}
	}
	semantic_analysis(Deflist);
	
	//不知道内存分配这些问题对不对//TODO();
	n->type->u.structure = (FieldList)malloc(sizeof(struct FieldList_));
	memcpy(n->type->u.structure, tmp_table[top], sizeof(tmp_table[top]));
	free(tmp_table[top]);
	if(!no_name)
		add_symbol(n, name);
	Symbol sym = find_symbol(name);
	top--;
	return;
}
void F_StructSpecifier_StructTag(struct node* n){
	#ifdef DEBUG_SEMANTIC
	printf("this is F_StructSpecifier_StructTag\n");
	#endif
	struct node* tag = n->gchild[1];
	
	semantic_analysis(tag);
	char* name = tag->str;
	
	Symbol sym = find_symbol(name);
	if((sym == NULL) || sym->idkind != _STRUCT)
		printf("Error type 17 at Line %d: Undefined structure \"%s\".\n", n->lineno, name);
	else if(sym != NULL) {
		tag->type = sym->type;
	}
	n->type = tag->type;
	
	return;
}
void F_Opttag_Id(struct node* n){
	#ifdef DEBUG_SEMANTIC
	printf("this is F_Opttag_Id\n");
	#endif

	struct node* id = n->gchild[0];
	char* name = id->str;
	
	strcpy(n->str, name);
	
	return;
}
void F_Opttag_Null(struct node* n){
	//no name
}
void F_Tag_Id(struct node* n){
	#ifdef DEBUG_SEMANTIC
	printf("this is F_Tag_Id\n");
	#endif

	struct node* id = n->gchild[0];
	char* name = id->str;
	strcpy(n->str, name);
	return;
}
void F_Vardec_Id(struct node* n){
	#ifdef DEBUG_SEMANTIC
	printf("this is F_Vardec_Id\n");
	#endif

	struct node* id = n->gchild[0];
	char* name = id->str;
	
	id->type = n->type;
	id->n_type = _VAR_;
	
	if(top == -1) {	
		Symbol sym = find_symbol(name);
		if(sym != NULL && sym->idkind == _VAR)
			printf("Error type 3 at Line %d: Redefined variable \"%s\".\n", n->lineno, name);
		else {
			int ret = add_symbol(id, name);
			if(ret)
				printf("add to symbol table error!\n");
		}	
	}
	else {
		if(tmp_table[top] == NULL) {
			FieldList new_field = (FieldList)malloc(sizeof(struct FieldList_));
			strcpy(new_field->name, name);
			new_field->type = id->type;
			new_field->tail = NULL;
			tmp_table[top] = new_field;
		}
		else {
			FieldList field = tmp_table[top];
			while(field->tail != NULL) {
				if(!strcmp(name, field->name))
					printf("Error type 15 at Line %d: Redefined field \"%s\".\n", n->lineno, name);
				field = field->tail;
			}
			FieldList new_field = (FieldList)malloc(sizeof(struct FieldList_));
			strcpy(new_field->name, name);
			new_field->type = id->type;
			new_field->tail = NULL;
			field->tail = new_field;
		}
	}
	return;
}
void F_Vardec_VardecLbIntRb(struct node* n){
	#ifdef DEBUG_SEMANTIC
	printf("this is F_Vardec_VardecLbIntRb\n");
	#endif

	struct node* Vardec = n->gchild[0];
	struct node* Int = n->gchild[1];
	int size = Int->type_int;
	Vardec->type = (Type)malloc(sizeof(struct Type_));
	Vardec->type->kind = ARRAY;
	Vardec->type->u.array.elem = n->type;
	Vardec->type->u.array.size = size;	//大小不知道怎么测
	//Vardec->type = n->type;
	semantic_analysis(Vardec);
	printf("vardec->type in vardecLBINTRB: %p\n", Vardec->type);
	//n->type->kind = ARRAY;
	//n->type->u.array.elem = Vardec->type;
	//n->type->u.array.size = size;
	return;
}
void F_Fundec_IdLpVarlistRp(struct node* n){
	#ifdef DEBUG_SEMANTIC
	printf("this is F_Fundec_IdLpVarlistRp\n");
	#endif

	struct node* id = n->gchild[0];
	struct node* Varlist = n->gchild[2];
	char* name = id->str;
	
	id->n_type = _FUNC_;
	id->func.retType = n->func.retType;
	
	Varlist->func.argc = 0;
	Varlist->func.argv = (Type*)malloc(sizeof(Type)*MAX_ARGC);
	semantic_analysis(Varlist);
	
	id->func.argc = Varlist->func.argc;
	id->func.argv = Varlist->func.argv;
	SymbolF symF = find_symbolF(name);
	if(symF != NULL)
		printf("Error type 4 at Line %d: Redefined function \"%s\".\n", n->lineno, name);
	else {
		//BUG FIXED: no n but ID!!!!
		int ret = add_symbolF(id, name);
		if(ret)
			printf("error when add func %s\n", name);
	}
	return;
}
void F_Fundec_IdLpRp(struct node* n){
	#ifdef DEBUG_SEMANTIC
	printf("this is F_Fundec_IdLpRp\n");
	#endif

	struct node* id = n->gchild[0];
	char* name = id->str;
	
	id->n_type = _FUNC_;
	id->func.retType = n->func.retType;
	id->func.argc = 0;
	
	SymbolF symF = find_symbolF(name);
	if(symF != NULL)
		printf("Error type 4 at Line %d: Redefined function \"%s\".\n", n->lineno, name);
	int ret = add_symbolF(n, name);
	if(ret)
		printf("error when add func %s\n", name);
	return;
}
void F_Varlist_ParamdecCommaVarlist(struct node* n){
	#ifdef DEBUG_SEMANTIC
	printf("this is F_Varlist_ParamdecCommaVarlist\n");
	#endif

	struct node* Paramdec = n->gchild[0];
	struct node* Varlist = n->gchild[2];
	
	Paramdec->func.argc = n->func.argc;
	Paramdec->func.argv = n->func.argv;
	semantic_analysis(Paramdec);
	
	n->func.argc = Paramdec->func.argc;
	
	Varlist->func.argc = n->func.argc;
	Varlist->func.argv = n->func.argv;
	semantic_analysis(Varlist);
	
	n->func.argc = Varlist->func.argc;
	
	return;
}
void F_Varlist_Paramdec(struct node* n){
	#ifdef DEBUG_SEMANTIC
	printf("this is F_Varlist_Paramdec\n");
	#endif
	
	struct node* Paramdec = n->gchild[0];
	
	Paramdec->func.argc = n->func.argc;
	Paramdec->func.argv = n->func.argv;
	semantic_analysis(Paramdec);
	
	n->func.argc = Paramdec->func.argc;
	
	return;
}
void F_Paramdec_SpecifierVardec(struct node* n){
	#ifdef DEBUG_SEMANTIC
	printf("this is F_Paramdec_SpecifierVardec\n");
	#endif

	struct node* Specifier = n->gchild[0];
	struct node* Vardec = n->gchild[1];
	
	semantic_analysis(Specifier);
	Vardec->type = Specifier->type;
	
	semantic_analysis(Vardec);	//是否要特判加入符号表?先不管
	
	n->func.argv[n->func.argc++] = Vardec->type;
	
	return;
}
void F_Compst_LcDeflistStmtlistRc(struct node* n){
	#ifdef DEBUG_SEMANTIC
	printf("this is F_Compst_LcDeflistStmtlistRc\n");
	#endif
	struct node* Deflist = n->gchild[1];
	struct node* Stmtlist = n->gchild[2];
	
	semantic_analysis(Deflist);
	Stmtlist->func.retType = n->func.retType;
	semantic_analysis(Stmtlist);
	
	return;
}
void F_Stmtlist_StmtStmtlist(struct node* n){
	#ifdef DEBUG_SEMANTIC
	printf("this is F_Stmtlist_StmtStmtlist\n");
	#endif

	struct node* Stmt = n->gchild[0];
	struct node* Stmtlist = n->gchild[1];
	
	Stmt->func.retType = n->func.retType;
	semantic_analysis(Stmt);
	
	if(Stmtlist != NULL) {
		Stmtlist->func.retType = n->func.retType;
		semantic_analysis(Stmtlist);
		
	}
	return;
}
void F_Stmtlist_Null(struct node* n){
	//No stmt
}
void F_Stmt_ExpSemi(struct node* n){
	#ifdef DEBUG_SEMANTIC
	printf("this is F_Stmt_ExpSemi\n");
	#endif

	struct node* Exp = n->gchild[0];
	
	semantic_analysis(Exp);

	return;
}
void F_Stmt_Compst(struct node* n){
	#ifdef DEBUG_SEMANTIC
	printf("this is F_Stmt_Compst\n");
	#endif

	struct node* Compst = n->gchild[0];
	
	Compst->func.retType = n->func.retType;
	semantic_analysis(Compst);
	
	return;
}
void F_Stmt_ReturnExpSemi(struct node* n){
	#ifdef DEBUG_SEMANTIC
	printf("this is F_Stmt_ReturnExpSemi\n");
	#endif

	struct node* Exp = n->gchild[1];
	
	semantic_analysis(Exp);
	
	if(!isEqual(Exp->type, n->func.retType)) {
		printf("Error type 8 at Line %d: Type mismatched for return.\n", n->lineno);
	}
	return;
}
void F_Stmt_IfLpExpRpStmt(struct node* n) {
	#ifdef DEBUG_SEMANTIC
	printf("this is F_Stmt_IfLpExpRpStmt\n");
	#endif	
	
	struct node* Exp = n->gchild[2];
	struct node* Stmt = n->gchild[4];
	
	semantic_analysis(Exp);
	if(Exp->type != NULL) {
		if(Exp->type->kind != BASIC)
			printf("Error type 7 at Line %d: Type mismatched for operands.\n", n->lineno);
		else if(Exp->type->u.basic != 1)
			printf("Error type 7 at Line %d: Type mismatched for operands.\n", n->lineno);		
	}	
	Stmt->func.retType = n->func.retType;
	semantic_analysis(Stmt);			
	
	return;
}
void F_Stmt_IfLpExpRpStmtElseStmt(struct node* n){
	#ifdef DEBUG_SEMANTIC
	printf("this is F_Stmt_IfLpExpRpStmtElseStmt\n");
	#endif

	struct node* Exp = n->gchild[2];
	struct node* Stmt1 = n->gchild[4];
	struct node* Stmt2 = n->gchild[6];
	
	semantic_analysis(Exp);	
	
	if(Exp->type != NULL) {
		if(Exp->type->kind != BASIC)
			printf("Error type 7 at Line %d: Type mismatched for operands.\n", n->lineno);
		else if(Exp->type->u.basic != 1)
			printf("Error type 7 at Line %d: Type mismatched for operands.\n", n->lineno);
	}
	Stmt1->func.retType = n->func.retType;
	semantic_analysis(Stmt1);
	printf("\033[41;35mStmt2: %p\033[0m\n", Stmt2);printf("!!!!!!!!!!!\n");
	Stmt2->func.retType = n->func.retType;
	semantic_analysis(Stmt2);
	return;
}
void F_Stmt_WhileLpExpRpStmt(struct node* n){
	#ifdef DEBUG_SEMANTIC
	printf("this is F_Stmt_WhileLpExpRpStmt\n");
	#endif

	struct node* Exp = n->gchild[2];
	struct node* Stmt = n->gchild[4];
	
	semantic_analysis(Exp);
	if(Exp->type->kind != BASIC)
		printf("Error type 7 at Line %d: Type mismatched for operands.\n", n->lineno);
	else if(Exp->type->u.basic != 1)
		printf("Error type 7 at Line %d: Type mismatched for operands.\n", n->lineno);
	
	Stmt->func.retType = n->func.retType;
	semantic_analysis(Stmt);
	
	return;
}
void F_Deflist_DefDeflist(struct node* n){
	#ifdef DEBUG_SEMANTIC
	printf("this is F_Deflist_DefDeflist\n");
	#endif

	struct node* Def = n->gchild[0];
	struct node* Deflist = n->gchild[1];
	
	semantic_analysis(Def);
	if(Deflist != NULL)
		semantic_analysis(Deflist);
	return;
}
void F_Deflist_Null(struct node* n){
	//No Def
}
void F_Def_SpecifierDeclistSemi(struct node* n){
	#ifdef DEBUG_SEMANTIC
	printf("this is F_Def_SpecifierDeclistSemi\n");
	#endif

	struct node* Specifier = n->gchild[0];
	struct node* Declist = n->gchild[1];
	
	semantic_analysis(Specifier);
	Declist->type = Specifier->type;
	semantic_analysis(Declist);
}
void F_Declist_Dec(struct node* n){
	#ifdef DEBUG_SEMANTIC
	printf("this is F_Declist_Dec\n");
	#endif

	struct node* Dec = n->gchild[0];
	Dec->type = n->type;
	semantic_analysis(Dec);
	
	return;
}
void F_Declist_DecCommaDeclist(struct node* n){
	#ifdef DEBUG_SEMANTIC
	printf("this is F_Declist_DecCommaDeclist\n");
	#endif

	struct node* Dec = n->gchild[0];
	struct node* Declist = n->gchild[2];
	
	Dec->type = n->type;
	semantic_analysis(Dec);
	
	semantic_analysis(Declist);
}
void F_Dec_Vardec(struct node* n){
	#ifdef DEBUG_SEMANTIC
	printf("this is F_Dec_Vardec\n");
	#endif

	struct node* Vardec = n->gchild[0];
	
	Vardec->type = n->type;
	semantic_analysis(Vardec);
}
void F_Dec_VardecAssignopExp(struct node* n){
	#ifdef DEBUG_SEMANTIC
	printf("this is F_Dec_VardecAssignopExp\n");
	#endif

	struct node* Vardec = n->gchild[0];
	struct node* Exp = n->gchild[2];
	
	Vardec->type = n->type;
	semantic_analysis(Vardec);
	semantic_analysis(Exp);
	//TODO 是否要加两个类型相等判断？？？
	
	return;
}
void F_Exp_ExpAssignopExp(struct node* n){
	#ifdef DEBUG_SEMANTIC
	printf("this is F_Exp_ExpAssignopExp\n");
	#endif

	struct node* E1 = n->gchild[0];
	struct node* E2 = n->gchild[2];
	
	
	semantic_analysis(E1);
	semantic_analysis(E2);
	if(E1->type != NULL && E2->type != NULL) {
		if(!isEqual(E1->type, E2->type)) 
			printf("Error type 5 at Line %d: Type mismatched for assignment.\n", n->lineno);
		if(!E1->is_left)
			printf("Error type 6 at Line %d: The left-hand side of an assignment must be a variable.\n", n->lineno);
		n->type = E1->type;
	}
	else 
		printf("//E1: %p E2: %p\n", E1->type, E2->type);

	n->is_left = 0;
	//TODO()根据类型进行判断再把E2的值赋给E1
		
	return;
}
void F_Exp_ExpAndExp(struct node* n){
	#ifdef DEBUG_SEMANTIC
	printf("this is F_Exp_ExpAndExp\n");
	#endif

	struct node* E1 = n->gchild[0];
	struct node* E2 = n->gchild[2];
	
	semantic_analysis(E1);
	semantic_analysis(E2);
	
	if(E1->type->kind != BASIC || E2->type->kind != BASIC)
		printf("Error type 7 at Line %d: Type mismatched for operands.\n", n->lineno);
	else if(E1->type->u.basic != 1 || E2->type->u.basic != 1)
		printf("Error type 7 at Line %d: Type mismatched for operands.\n", n->lineno);
	n->type = E1->type;
	n->type_int = E1->type_int && E2->type_int;
	n->n_type = _BASIC_;
	n->is_left = 0;
	
	return;
}
void F_Exp_ExpOrExp(struct node* n){
	#ifdef DEBUG_SEMANTIC
	printf("this is F_Exp_ExpOrExp\n");
	#endif

	struct node* E1 = n->gchild[0];
	struct node* E2 = n->gchild[2];
	
	semantic_analysis(E1);
	semantic_analysis(E2);
	
	if(E1->type->kind != BASIC || E2->type->kind != BASIC)
		printf("Error type 7 at Line %d: Type mismatched for operands.\n", n->lineno);
	else if(E1->type->u.basic != 1 || E2->type->u.basic != 1)
		printf("Error type 7 at Line %d: Type mismatched for operands.\n", n->lineno);
	n->type = E1->type;
	n->type_int = E1->type_int || E2->type_int;
	n->n_type = _BASIC_;
	n->is_left = 0;
	
	return;
}
void F_Exp_ExpRelopExp(struct node* n){
	#ifdef DEBUG_SEMANTIC
	printf("this is F_Exp_ExpRelopExp\n");
	#endif

	struct node* E1 = n->gchild[0];
	struct node* Relop = n->gchild[1];
	struct node* E2 = n->gchild[2];
	int is_float = 0;
	
	semantic_analysis(E1);
	semantic_analysis(E2);
	//printf("relop: E1:%p E2: %p\n", E1->type, E2->type);
	if(E1->type && E2->type){
		if(E1->type->kind != BASIC || E2->type->kind != BASIC)
			printf("Error type 7 at Line %d: Type mismatched for operands.\n", n->lineno);
		if(E1->type->u.basic != E2->type->u.basic) {
			if(E1->type->u.basic == 1) {
				E1->type->u.basic = 0;
				E1->type_float = E1->type_int;
			}
			else {
				E2->type->u.basic = 0;
				E2->type_float = E1->type_int;
			}
			is_float = 1;
		}
		if(E1->type->u.basic == 0) {
			is_float = 1;
		}
		n->type->kind = BASIC;
		n->type->u.basic = 1;
		n->n_type = _BASIC_;
		char* op = Relop->relop;
		int cas = -1;
		if(!strcmp(op, ">"))
			cas = 0;
		else if(!strcmp(op, "<"))
			cas = 1;
		else if(!strcmp(op, ">="))
			cas = 2;
		else if(!strcmp(op, "<="))
			cas = 3;
		else if(!strcmp(op, "=="))
			cas = 4;
		else if(!strcmp(op, "!="))
			cas = 5;
		switch(cas) {
			case 0:
				if(is_float)
					n->type_int = (E1->type_float > E2->type_float);
				else
					n->type_int = (E1->type_int > E2->type_int);
				break;
			case 1:
				if(is_float)
					n->type_int = (E1->type_float < E2->type_float);
				else
					n->type_int = (E1->type_int < E2->type_int);
				break;
			case 2:
				if(is_float)
					n->type_int = (E1->type_float >= E2->type_float);
				else
					n->type_int = (E1->type_int >= E2->type_int);
				break;
			case 3:
				if(is_float)
					n->type_int = (E1->type_float <= E2->type_float);
				else
					n->type_int = (E1->type_int <= E2->type_int);
				break;
			case 4:
				if(is_float)
					n->type_int = (E1->type_float == E2->type_float);
				else
					n->type_int = (E1->type_int == E2->type_int);
				break;
			case 5:
				if(is_float)
					n->type_int = (E1->type_float != E2->type_float);
				else
					n->type_int = (E1->type_int != E2->type_int);
				break;
		}
	}
	return;
}
void F_Exp_ExpPlusExp(struct node* n){
	#ifdef DEBUG_SEMANTIC
	printf("this is F_Exp_ExpPlusExp\n");
	#endif


	struct node* E1 = n->gchild[0];
	struct node* E2 = n->gchild[2];
	
	semantic_analysis(E1);	
	semantic_analysis(E2);

	if(E1->type->kind == BASIC && E2->type->kind == BASIC) {
		if(E1->type->u.basic != E2->type->u.basic) {
			printf("Error type 7 at Line %d: Type mismatched for operands.\n", n->lineno);
			if(E1->type->u.basic == 1) {
				E1->type->u.basic = 0;
				E1->type_float = E1->type_int;
			}
			else {
				E2->type->u.basic = 0;
				E2->type_float = E2->type_int;
			}
			n->type_float = E1->type_float + E2->type_float;
		}
		else if(E1->type->u.basic == 0) {
			n->type_float = E1->type_float + E2->type_float;
		}
		else if(E1->type->u.basic == 1) {
			
			n->type_int = E1->type_int + E2->type_int;
		}
		
		n->type = E1->type;
		n->n_type = _BASIC_;
	}
	else
		printf("Error type 7 at Line %d: Type mismatched for operands.\n", n->lineno);
	n->is_left = 0;
	
	return;
}
void F_Exp_ExpMinusExp(struct node* n){
	#ifdef DEBUG_SEMANTIC
	printf("this is F_Exp_ExpMinusExp\n");
	#endif

	struct node* E1 = n->gchild[0];
	struct node* E2 = n->gchild[2];
	
	semantic_analysis(E1);
	semantic_analysis(E2);
	
	if(E1->type->kind == BASIC && E2->type->kind == BASIC) {
		if(E1->type->u.basic != E2->type->u.basic) {
			printf("Error type 7 at Line %d: Type mismatched for operands.\n", n->lineno);
			if(E1->type->u.basic == 1) {
				E1->type->u.basic = 0;
				E1->type_float = E1->type_int;
			}
			else {
				E2->type->u.basic = 0;
				E2->type_float = E2->type_int;
			}
			n->type_float = E1->type_float - E2->type_float;
		}
		else if(E1->type->u.basic == 0) {
			n->type_float = E1->type_float - E2->type_float;
		}
		else if(E1->type->u.basic == 1) {
			n->type_int = E1->type_int - E2->type_int;
		}
		n->type = E1->type;
		n->n_type = _BASIC_;
	}
	else
		printf("Error type 7 at Line %d: Type mismatched for operands.\n", n->lineno);
	n->is_left = 0;
	
	return;
}
void F_Exp_ExpStarExp(struct node* n){
	#ifdef DEBUG_SEMANTIC
	printf("this is F_Exp_ExpStarExp\n");
	#endif

	struct node* E1 = n->gchild[0];
	struct node* E2 = n->gchild[2];
	
	semantic_analysis(E1);
	semantic_analysis(E2);
	
	if(E1->type->kind == BASIC && E2->type->kind == BASIC) {
		if(E1->type->u.basic != E2->type->u.basic) {
			printf("Error type 7 at Line %d: Type mismatched for operands.\n", n->lineno);
			if(E1->type->u.basic == 1) {
				E1->type->u.basic = 0;
				E1->type_float = E1->type_int;
			}
			else {
				E2->type->u.basic = 0;
				E2->type_float = E2->type_int;
			}
			n->type_float = E1->type_float * E2->type_float;
		}
		else if(E1->type->u.basic == 0) {
			n->type_float = E1->type_float * E2->type_float;
		}
		else if(E1->type->u.basic == 1) {
			n->type_int = E1->type_int * E2->type_int;
		}
		n->type = E1->type;
		n->n_type = _BASIC_;
	}
	else
		printf("Error type 7 at Line %d: Type mismatched for operands.\n", n->lineno);
	n->is_left = 0;
	
	return;
}
void F_Exp_ExpDivExp(struct node* n){
	#ifdef DEBUG_SEMANTIC
	printf("this is F_Exp_ExpDivExp\n");
	#endif

	struct node* E1 = n->gchild[0];
	struct node* E2 = n->gchild[2];
	
	semantic_analysis(E1);
	semantic_analysis(E2);
	
	if(E1->type->kind == BASIC && E2->type->kind == BASIC) {
		if(E1->type->u.basic != E2->type->u.basic) {
			printf("Error type 7 at Line %d: Type mismatched for operands.\n", n->lineno);
			if(E1->type->u.basic == 1) {
				E1->type->u.basic = 0;
				E1->type_float = E1->type_int;
			}
			else {
				E2->type->u.basic = 0;
				E2->type_float = E2->type_int;
			}
			n->type_float = E1->type_float / E2->type_float;
		}
		else if(E1->type->u.basic == 0) {
			n->type_float = E1->type_float / E2->type_float;
		}
		else if(E1->type->u.basic == 1) {
			n->type_int = E1->type_int / E2->type_int;
		}
		n->type = E1->type;
		n->n_type = _BASIC_;
	}
	else
		printf("Error type 7 at Line %d: Type mismatched for operands.\n", n->lineno);
	n->is_left = 0;
	
	return;
}
void F_Exp_LpExpRp(struct node* n){
	#ifdef DEBUG_SEMANTIC
	printf("this is F_Exp_LpExpRp\n");
	#endif
	struct node* E1 = n->gchild[0];
	
	semantic_analysis(E1);
	n->type = E1->type;
	n->is_left = 0;
	
	return;
}
void F_Exp_MinusExp(struct node* n){
	#ifdef DEBUG_SEMANTIC
	printf("this is F_Exp_MinusExp\n");
	#endif

	struct node* E1 = n->gchild[0];
	semantic_analysis(E1);
	
	if(E1->type->kind != BASIC)
		printf("Error type 7 at Line %d: Type mismatched for operands.\n", n->lineno);
	
	n->type = E1->type;
	n->n_type = _BASIC_;
	
	if(E1->type->u.basic) {
		n->type_int = -E1->type_int;
	}
	else {
		n->type_float = -E1->type_float;
	}
	n->is_left = 0;
	
	return;
}
void F_Exp_NotExp(struct node* n){
	#ifdef DEBUG_SEMANTIC
	printf("this is F_Exp_NotExp\n");
	#endif

	struct node* E1 = n->gchild[0];
	semantic_analysis(E1);
	
	if(E1->type->kind != BASIC)
		printf("Error type 7 at Line %d: Type mismatched for operands.\n", n->lineno);
	else if(E1->type->u.basic != 1)
		printf("Error type 7 at Line %d: Type mismatched for operands.\n", n->lineno);
	
	n->type = E1->type;
	n->n_type = _BASIC_;
	n->type_int = !(E1->type_int);
	n->is_left = 0;
	
	return;
}
void F_Exp_IdLpArgsRp(struct node* n){
	#ifdef DEBUG_SEMANTIC
	printf("this is F_Exp_IdLpArgsRp\n");
	#endif
	struct node* id = n->gchild[0];
	struct node* args = n->gchild[2];
	char* name = id->str;
	
	args->func.argc = 0;
	args->func.argv = (Type*)malloc(sizeof(Type)*MAX_ARGC);
	semantic_analysis(args);
	
	strcpy(n->str, name);
	
	
	SymbolF symF = find_symbolF(name);
	Symbol sym = find_symbol(name);
	if(symF == NULL) {	
		if(sym != NULL) {
			printf("Error type 11 at Line %d: \"%s\" is not a function.\n", n->lineno, n->str);
		}
		else {
			strcat(n->str, "\(");
			strcat(args->str, ")");
			strcat(n->str, args->str);
			printf("arg->str:%s\n", n->str);
			printf("Error type 2 at Line %d: Undefined function \"%s\".\n", n->lineno, n->str);
		}
	}
	char nargv_type[100];
	int n_cnt = args->func.argc;
	strcpy(nargv_type, "(");
	for(int i = 0; i<n_cnt; i++) {
		int tp = -1; // 0:float 1:int 2:array 3:structure
		Type tmp = args->func.argv[i];
		if(tmp->kind == BASIC) {
			if(!tmp->u.basic)
				tp = 0;
			else
				tp = 1;
		}
		else if(tmp->kind == BASIC) {
			tp = 2;
		}
		else if(tmp->kind == STRUCTURE) {
			tp = 3;
		}
		switch(tp) {
			case 0: strcat(nargv_type, "float"); break;
			case 1: strcat(nargv_type, "int"); break;
			case 2: strcat(nargv_type, "array"); break;
			case 3: strcat(nargv_type, "structure"); strcat(nargv_type, tmp->u.structure->name); break;
		}
		if(i != n_cnt-1)
			strcat(nargv_type, ", ");
		else
			strcat(nargv_type, ")");
	}
	if(symF != NULL) {
		char Fargv_type[100];
		int F_cnt = symF->argc;
		strcpy(Fargv_type, "(");
		for(int i = 0; i<F_cnt; i++) {
			int tp = -1; // 0:float 1:int 2:array 3:structure
			Type tmp = symF->argv[i];
			if(tmp->kind == BASIC) {
				if(!tmp->u.basic)
					tp = 0;
				else
					tp = 1;
			}
			else if(tmp->kind == BASIC) {
				tp = 2;
			}
			else if(tmp->kind == STRUCTURE) {
				tp = 3;
			}
			switch(tp) {
				case 0: strcat(Fargv_type, "float"); break;
				case 1: strcat(Fargv_type, "int"); break;
				case 2: strcat(Fargv_type, "array"); break;
				case 3: strcat(Fargv_type, "structure"); strcat(Fargv_type, tmp->u.structure->name); break;
			}
			if(i != F_cnt-1)
				strcat(Fargv_type, ", ");
			else
				strcat(Fargv_type, ")");
		}
		int is_argfault = 0;
		if(args->func.argc != symF->argc) {
			char print_tmp[160];
			strcpy(print_tmp, symF->name);
			strcat(print_tmp, Fargv_type);
			printf("Error type 9 at Line %d: Function \"%s\" is not applicable for arguments \"%s\".\n", n->lineno, print_tmp, 	nargv_type);//TODO()!!!!!!
			is_argfault = 1;
		}

		int i = 0;
		while(symF->argv[i] != NULL && args->func.argv[i] != NULL) {
			if(!isEqual(symF->argv[i], args->func.argv[i])) {
				printf("type 9 error");	//TODO()!!!!!!!
				is_argfault = 1;
				break;
			}
			i++;
		}
		if(!is_argfault) {
			n->func.retType = symF->retType;
			n->func.argc = symF->argc;
			n->func.argv = symF->argv;
		}
		else {
			n->func.argc = -1;
			n->func.argv = NULL;
		}
	}
	n->is_left = 0;
	
	return;
}
void F_Exp_IdLpRp(struct node* n){
	#ifdef DEBUG_SEMANTIC
	printf("this is F_Exp_IdLpRp\n");
	#endif
	struct node* id = n->gchild[0];
	char* name = id->str;
	
	strcpy(n->str, name);
	strcat(n->str, "()");
	SymbolF symF = find_symbolF(name);
	
	if(symF == NULL)
		printf("Error type 2 at Line %d: Undefined function \"%s\".\n", n->lineno, name);
	if(symF->argc != 0)
		printf("Error type 9 at Line %d: Function \"%s\" is not applicable for arguments \"()\".\n", n->lineno, n->str);
	n->func.retType = symF->retType;
	n->is_left = 0;
	
	return;
}
void F_Exp_ExpLbExpRb(struct node* n){
	#ifdef DEBUG_SEMANTIC
	printf("this is F_Exp_ExpLbExpRb\n");
	#endif
	struct node* Exp1 = n->gchild[0];
	struct node* Exp2 = n->gchild[2];
	
	semantic_analysis(Exp1);
	semantic_analysis(Exp2);
	
	char* name = Exp1->str;
	Symbol sym = find_symbol(name);
	if(sym == NULL)
		printf("Error type 1 at Line %d: Undefined variable \"%s\".\n", n->lineno, name);
	if(Exp1->type->kind != ARRAY)
		printf("Error type 10 at Line %d: \"%s\" is not an array.\n", n->lineno, name);
	if(Exp2->type->kind != BASIC) {
		printf("Error type 12 at Line %d: \"%s\" is not an integer.\n", n->lineno, Exp2->str);
	}
	else if(Exp2->type->u.basic != 1) {
		printf("Error type 12 at Line %d: \"%g\" is not an integer.\n", n->lineno, Exp2->type_float);
	}
	n->type = Exp1->type; //???
	n->is_left = 1;
	
	return;
}
void F_Exp_ExpDotId(struct node* n){
	#ifdef DEBUG_SEMANTIC
	printf("this is F_Exp_ExpDotId\n");
	#endif
	struct node* Exp = n->gchild[0];
	struct node* id = n->gchild[2];
	
	semantic_analysis(Exp);
	
	if(Exp->type->kind != STRUCTURE) {
		printf("Error type 13 at Line %d: Illegal use of \".\".\n", n->lineno);		
	}
	char* name = Exp->str;
	Symbol sym = find_symbol(name);
	if(sym == NULL)
		printf("Error type 13 at Line %d: Illegal use of \".\".\n", n->lineno);
	if(sym && sym->type->kind == STRUCTURE) {
		char* id_name = id->str;
		FieldList p = sym->type->u.structure;
		int is_matched = 0; 
		while(p != NULL) {
			if(!strcmp(p->name, id_name)) {
				is_matched = 1;
				break;			
			}
			p = p->tail;
		}
		if(!is_matched)
			printf("Error type 14 at Line %d: Non-existent field \"%s\".", n->lineno, id_name);
		//else
		//	n->type = id->type;
		}
	n->is_left = 1;
	n->type = id->type;
	return;
}
void F_Exp_Id(struct node* n){
	#ifdef DEBUG_SEMANTIC
	printf("this is F_Exp_Id\n");
	#endif

	struct node* id = n->gchild[0];
	char* name = id->str;
	
	Symbol sym = find_symbol(name);
	if(sym == NULL) {
		printf("Error type 1 at Line %d: Undefined variable \"%s\".\n", n->lineno, name);
	}
	strcpy(n->str, name);
	//BUG FIXED: ID with null pointer;
	if(sym != NULL) {
		id->type = sym->type;
		n->type = id->type;
	}
	n->n_type = _ID_;
	n->is_left = 1;
	return;
}
void F_Exp_Int(struct node* n){
	#ifdef DEBUG_SEMANTIC
	printf("this is F_Exp_Int\n");
	#endif
	
	struct node* Int = n->gchild[0];
	
	n->n_type = _BASIC_;
	
	Type t = (Type)malloc(sizeof(struct Type_));
	t->u.basic = 1;
	t->kind = BASIC;
	n->type = t;
	n->type_int = Int->type_int;
	n->is_left = 0;
	
	return;
}
void F_Exp_Float(struct node* n){
	#ifdef DEBUG_SEMANTIC
	printf("this is F_Exp_Float\n");
	#endif

	n->n_type = _BASIC_;
	
	n->type = (Type)malloc(sizeof(struct Type_));
	n->type->u.basic = 0;
	n->type->kind = BASIC;
	n->type_float = n->gchild[0]->type_float;
	n->is_left = 0;

	return;
}
void F_Args_ExpCommaArgs(struct node* n){
	#ifdef DEBUG_SEMANTIC
	printf("this is F_Args_ExpCommaArgs\n");
	#endif

	struct node* Exp = n->gchild[0];
	struct node* Args = n->gchild[2];
	
	semantic_analysis(Exp);
	if(n->str) 
		strcat(n->str, Exp->str);
	else 
		strcpy(n->str, Exp->str);
	n->func.argv[n->func.argc++] = Exp->type;
	
	Args->func.argc = n->func.argc;
	Args->func.argv = n->func.argv;
	
	semantic_analysis(Args);
	strcat(n->str, ", ");
	strcat(n->str, Args->str);
	n->func.argc = Args->func.argc;
	
	return;
}
void F_Args_Exp(struct node* n) {
	#ifdef DEBUG_SEMANTIC
	printf("this is F_Args_Exp\n");
	#endif

	struct node* Exp = n->gchild[0];
	
	semantic_analysis(Exp);
	strcpy(n->str, Exp->str);
	if(Exp->type)
		n->func.argv[n->func.argc++] = Exp->type;
	
	return;
}


