#include "semantic.h"

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
	if(a->kind != b->kind) 
		return 0;
	if(a->kind == BASIC) {
		if(a->u.basic != b->u.basic)
			return 0;
	}
	else if(a->kind == ARRAY) {
		if(a->u.array.elem != b->u.array.elem)
			return 0;
		if(a->u.array.size != b->u.array.size)
			return 0;
	}
	else if(a->kind == STRUCTURE) {
		if(!isEqual(a->u.structure->type, b->u.structure->type))
			return 0;
	}
	return 1;
}
void F_Program_Extdeflist(struct node* n){
	struct node* Extdeflist = n->gchild[0];
	
	semantic_analysis(Extdeflist);
	
	return;
}
void F_Extdeflist_ExtdefExtdeflist(struct node* n){
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
	struct node* Specifier = n->gchild[0];
	struct node* Extdeclist = n->gchild[1];
	
	semantic_analysis(Specifier);
	Extdeclist->u.type = Specifier->u.type;
	semantic_analysis(Extdeclist);
	
	return;
}
void F_Extdef_SpecifierSemi(struct node* n){
	struct node* Specifier = n->gchild[0];
	
	semantic_analysis(Specifier);
	
	return;
}
void F_Extdef_SpcifierFundecCompst(struct node* n){
	struct node* Specifier = n->gchild[0];
	struct node* Fundec = n->gchild[1];
	struct node* Compst = n->gchild[2];
	
	semantic_analysis(Specifier);
	Fundec->u.func.retType = Specifier->u.type;
	semantic_analysis(Fundec);
	Compst->u.func.retType = Specifier->u.type;
	semantic_analysis(Compst);
	
	return;
}
void F_Extdeclist_Vardec(struct node* n){
	struct node* Vardec = n->gchild[0];
	
	semantic_analysis(Vardec);
	return;
}
void F_Extdeclist_VardecCommaExtdeclist(struct node* n){
	struct node* Vardec = n->gchild[0];
	struct node* Extdeclist = n->gchild[2];
	
	semantic_analysis(Vardec);
	semantic_analysis(Extdeclist);
	
	return;
}
void F_Specifier_Type(struct node* n){
	struct node* ttype = n->gchild[0];
	char* basic_type = ttype->str;
	
	if(!strcmp(basic_type, "int")) {
		n->u.type = (Type)malloc(sizeof(struct Type_));
		n->u.type->kind = BASIC;
		n->u.type->u.basic = 1;
	}
	else if(!strcmp(basic_type, "float")) {
		n->u.type = (Type)malloc(sizeof(struct Type_));
		n->u.type->kind = BASIC;
		n->u.type->u.basic = 0;
	}
	
	return;
}
void F_Specifier_Structspecifier(struct node* n){
	struct node* Structspecifier = n->gchild[0];
	
	semantic_analysis(Structspecifier);
	n->u.type = Structspecifier->u.type;
	
	return;
}
void F_StructSpecifier_StructOpttagLcDeflistRc(struct node* n){
	//两种情况判断
	struct node* Opttag = n->gchild[1];
	//还没处理没有名字的情况 //TODO()
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
	n->u.type = (Type)malloc(sizeof(struct Type_));
	n->u.type->kind = STRUCTURE;
	n->n_type = _STRUCTURE_;
	n->u.type->u.structure = tmp_table[++top];
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
	n->u.type->u.structure = (FieldList)malloc(sizeof(struct FieldList_));
	memcpy(n->u.type->u.structure, tmp_table[top], sizeof(tmp_table[top]));
	free(tmp_table[top]);
	if(!no_name)
		add_symbol(n, name);
	top--;
	return;
}
void F_StructSpecifier_StructTag(struct node* n){
	struct node* tag = n->gchild[1];
	
	semantic_analysis(tag);
	char* name = tag->str;
	
	Symbol sym = find_symbol(name);
	if((sym == NULL) || sym->idkind != _STRUCT)
		printf("Error type 17 at Line %d: Undefined structure \"%s\".\n", n->lineno, name);
	
	n->u.type = tag->u.type;
	
	return;
}
void F_Opttag_Id(struct node* n){
	struct node* id = n->gchild[0];
	char* name = id->str;
	
	strcpy(n->str, name);
	
	return;
}
void F_Opttag_Null(struct node* n){
	//no name
}
void F_Tag_Id(struct node* n){
	struct node* id = n->gchild[0];
	char* name = id->str;
	
	strcpy(n->str, name);
	
	return;
}
void F_Vardec_Id(struct node* n){
	struct node* id = n->gchild[0];
	char* name = id->str;
	
	id->u.type = n->u.type;
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
			new_field->type = id->u.type;
			new_field->tail = NULL;
			tmp_table[top] = new_field;
		}
		else {
			FieldList field = tmp_table[top];
			while(field->tail != NULL) {
				if(!strcmp(name, field->name))
					printf("Error type 15 at Line %d: Redefined field \"%s\".", n->lineno, name);
			}
			FieldList new_field = (FieldList)malloc(sizeof(struct FieldList_));
			strcpy(new_field->name, name);
			new_field->type = id->u.type;
			new_field->tail = NULL;
			field->tail = new_field;
		}
	}
	return;
}
void F_Vardec_VardecLbIntRb(struct node* n){
	struct node* Vardec = n->gchild[0];
	struct node* Int = n->gchild[1];
	int size = Int->type_int;
	
	Vardec->u.type->kind = ARRAY;
	Vardec->u.type->u.array.elem = n->u.type;
	Vardec->u.type->u.array.size = size;	//大小不知道怎么测
	
	semantic_analysis(Vardec);
	
	return;
}
void F_Fundec_IdLpVarlistRp(struct node* n){
	struct node* id = n->gchild[0];
	struct node* Varlist = n->gchild[2];
	char* name = id->str;
	
	id->n_type = _FUNC_;
	id->u.func.retType = n->u.func.retType;
	
	Varlist->u.func.argc = 0;
	Varlist->u.func.argv = (Type*)malloc(sizeof(Type)*MAX_ARGC);
	semantic_analysis(Varlist);
	
	id->u.func.argc = Varlist->u.func.argc;
	id->u.func.argv = Varlist->u.func.argv;
	
	SymbolF symF = find_symbolF(name);
	if(symF != NULL)
		printf("Error type 4 at Line %d: Redefined function \"%s\".\n", n->lineno, name);
	int ret = add_symbolF(n, name);
	if(ret)
		printf("error when add func %s\n", name);
	return;
}
void F_Fundec_IdLpRp(struct node* n){
	struct node* id = n->gchild[0];
	char* name = id->str;
	
	id->n_type = _FUNC_;
	id->u.func.retType = n->u.func.retType;
	id->u.func.argc = 0;
	
	SymbolF symF = find_symbolF(name);
	if(symF != NULL)
		printf("Error type 4 at Line %d: Redefined function \"%s\".\n", n->lineno, name);
	int ret = add_symbolF(n, name);
	if(ret)
		printf("error when add func %s\n", name);
	return;
}
void F_Varlist_ParamdecCommaVarlist(struct node* n){
	struct node* Paramdec = n->gchild[0];
	struct node* Varlist = n->gchild[2];
	
	Paramdec->u.func.argc = n->u.func.argc;
	Paramdec->u.func.argv = n->u.func.argv;
	semantic_analysis(Paramdec);
	
	n->u.func.argc = Paramdec->u.func.argc;
	
	Varlist->u.func.argc = n->u.func.argc;
	Varlist->u.func.argv = n->u.func.argv;
	semantic_analysis(Varlist);
	
	n->u.func.argc = Varlist->u.func.argc;
	
	return;
}
void F_Varlist_Paramdec(struct node* n){
	struct node* Paramdec = n->gchild[0];
	
	Paramdec->u.func.argc = n->u.func.argc;
	Paramdec->u.func.argv = n->u.func.argv;
	semantic_analysis(Paramdec);
	
	n->u.func.argc = Paramdec->u.func.argc;
	
	return;
}
void F_Paramdec_SpecifierVardec(struct node* n){
	struct node* Specifier = n->gchild[0];
	struct node* Vardec = n->gchild[1];
	
	semantic_analysis(Specifier);
	Vardec->u.type = Specifier->u.type;
	
	semantic_analysis(Vardec);	//是否要特判加入符号表?先不管
	
	n->u.func.argv[n->u.func.argc++] = Vardec->u.type;
	
	return;
}
void F_Compst_LcDeflistStmtlistRc(struct node* n){
	struct node* Deflist = n->gchild[1];
	struct node* Stmtlist = n->gchild[2];
	
	semantic_analysis(Deflist);
	Stmtlist->u.func.retType = n->u.func.retType;
	semantic_analysis(Stmtlist);
	
	return;
}
void F_Stmtlist_StmtStmtlist(struct node* n){
	struct node* Stmt = n->gchild[0];
	struct node* Stmtlist = n->gchild[1];
	
	Stmt->u.func.retType = n->u.func.retType;
	semantic_analysis(Stmt);
	
	if(Stmtlist != NULL) {
		Stmtlist->u.func.retType = n->u.func.retType;
		semantic_analysis(Stmtlist);
	}
	return;
}
void F_Stmtlist_Null(struct node* n){
	//No stmt
}
void F_Stmt_ExpSemi(struct node* n){
	struct node* Exp = n->gchild[0];
	
	semantic_analysis(Exp);
	
	return;
}
void F_Stmt_Compst(struct node* n){
	struct node* Compst = n->gchild[0];
	
	Compst->u.func.retType = n->u.func.retType;
	semantic_analysis(Compst);
	
	return;
}
void F_Stmt_ReturnExpSemi(struct node* n){
	struct node* Exp = n->gchild[1];
	
	semantic_analysis(Exp);
	
	if(!isEqual(Exp->u.type, n->u.func.retType)) {
		printf("Error type 8 at Line %d: Type mismatched for return.\n", n->lineno);
		return;
	}
	return;
}
void F_Stmt_IfLpExpRpStmtElseStmt(struct node* n){
	struct node* Exp = n->gchild[2];
	struct node* Stmt1 = n->gchild[4];
	struct node* Stmt2 = n->gchild[6];
	
	semantic_analysis(Exp);	
	if(Exp->u.type->kind != BASIC)
		printf("Error type 7 at Line %d: Type mismatched for operands.\n", n->lineno);
	else if(Exp->u.type->u.basic != 1)
		printf("Error type 7 at Line %d: Type mismatched for operands.\n", n->lineno);
	
	Stmt1->u.func.retType = n->u.func.retType;
	semantic_analysis(Stmt1);
	Stmt2->u.func.retType = n->u.func.retType;
	semantic_analysis(Stmt2);
	
	return;
}
void F_Stmt_WhileLpExpRpStmt(struct node* n){
	struct node* Exp = n->gchild[2];
	struct node* Stmt = n->gchild[4];
	
	semantic_analysis(Exp);
	if(Exp->u.type->kind != BASIC)
		printf("Error type 7 at Line %d: Type mismatched for operands.\n", n->lineno);
	else if(Exp->u.type->u.basic != 1)
		printf("Error type 7 at Line %d: Type mismatched for operands.\n", n->lineno);
	
	Stmt->u.func.retType = n->u.func.retType;
	semantic_analysis(Stmt);
	
	return;
}
void F_Deflist_DefDeflist(struct node* n){
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
	struct node* Specifier = n->gchild[0];
	struct node* Declist = n->gchild[1];
	
	semantic_analysis(Specifier);
	Declist->u.type = Specifier->u.type;
	semantic_analysis(Declist);
}
void F_Declist_Dec(struct node* n){
	struct node* Dec = n->gchild[0];
	
	Dec->u.type = n->u.type;
	semantic_analysis(Dec);
}
void F_Declist_DecCommaDeclist(struct node* n){
	struct node* Dec = n->gchild[0];
	struct node* Declist = n->gchild[2];
	
	Dec->u.type = n->u.type;
	semantic_analysis(Dec);
	
	semantic_analysis(Declist);
}
void F_Dec_Vardec(struct node* n){
	struct node* Vardec = n->gchild[0];
	
	Vardec->u.type = n->u.type;
	semantic_analysis(Vardec);
}
void F_Dec_VardecAssignopExp(struct node* n){
	struct node* Vardec = n->gchild[0];
	struct node* Exp = n->gchild[2];
	
	Vardec->u.type = n->u.type;
	semantic_analysis(Vardec);
	semantic_analysis(Exp);
	
	return;
}
void F_Exp_ExpAssignopExp(struct node* n){
	struct node* E1 = n->gchild[0];
	struct node* E2 = n->gchild[2];
	
	semantic_analysis(E1);
	semantic_analysis(E2);
	
	if(!isEqual(E1->u.type, E2->u.type)) 
		printf("Error type 5 at Line %d: Type mismatched for assignment.\n", n->lineno);
	if(!E1->is_left)
		printf("Error type 6 at Line %d: The left-hand side of an assignment must be a variable.\n", n->lineno);
	n->u.type = E1->u.type;	//??????????
	n->is_left = 0;
	//TODO()根据类型进行判断再把E2的值赋给E1
	return;
}
void F_Exp_ExpAndExp(struct node* n){
	struct node* E1 = n->gchild[0];
	struct node* E2 = n->gchild[2];
	
	semantic_analysis(E1);
	semantic_analysis(E2);
	
	if(E1->u.type->kind != BASIC || E2->u.type->kind != BASIC)
		printf("Error type 7 at Line %d: Type mismatched for operands.\n", n->lineno);
	else if(E1->u.type->u.basic != 1 || E2->u.type->u.basic != 1)
		printf("Error type 7 at Line %d: Type mismatched for operands.\n", n->lineno);
	n->u.type = E1->u.type;
	n->type_int = E1->type_int && E2->type_int;
	n->n_type = _BASIC_;
	n->is_left = 0;
	
	return;
}
void F_Exp_ExpOrExp(struct node* n){
	struct node* E1 = n->gchild[0];
	struct node* E2 = n->gchild[2];
	
	semantic_analysis(E1);
	semantic_analysis(E2);
	
	if(E1->u.type->kind != BASIC || E2->u.type->kind != BASIC)
		printf("Error type 7 at Line %d: Type mismatched for operands.\n", n->lineno);
	else if(E1->u.type->u.basic != 1 || E2->u.type->u.basic != 1)
		printf("Error type 7 at Line %d: Type mismatched for operands.\n", n->lineno);
	n->u.type = E1->u.type;
	n->type_int = E1->type_int || E2->type_int;
	n->n_type = _BASIC_;
	n->is_left = 0;
	
	return;
}
void F_Exp_ExpRelopExp(struct node* n){
	struct node* E1 = n->gchild[0];
	struct node* Relop = n->gchild[1];
	struct node* E2 = n->gchild[2];
	int is_float = 0;
	
	semantic_analysis(E1);
	semantic_analysis(E2);

	if(E1->u.type->kind != BASIC || E2->u.type->kind != BASIC)
		printf("Error type 7 at Line %d: Type mismatched for operands.\n", n->lineno);
	if(E1->u.type->u.basic != E2->u.type->u.basic) {
		if(E1->u.type->u.basic == 1) {
			E1->u.type->u.basic = 0;
			E1->type_float = E1->type_int;
		}
		else {
			E2->u.type->u.basic = 0;
			E2->type_float = E1->type_int;
		}
		is_float = 1;
	}
	if(E1->u.type->u.basic == 0) {
		is_float = 1;
	}
	n->u.type->kind = BASIC;
	n->u.type->u.basic = 1;
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
	return;
}
void F_Exp_ExpPlusExp(struct node* n){
	struct node* E1 = n->gchild[0];
	struct node* E2 = n->gchild[2];
	
	semantic_analysis(E1);
	semantic_analysis(E2);
	
	if(E1->u.type->kind == BASIC && E2->u.type->kind == BASIC) {
		if(E1->u.type->u.basic != E2->u.type->u.basic) {
			printf("float and int calculate!!\n");
			if(E1->u.type->u.basic == 1) {
				E1->u.type->u.basic = 0;
				E1->type_float = E1->type_int;
			}
			else {
				E2->u.type->u.basic = 0;
				E2->type_float = E2->type_int;
			}
			n->type_float = E1->type_float + E2->type_float;
		}
		else if(E1->u.type->u.basic == 0) {
			n->type_float = E1->type_float + E2->type_float;
		}
		else if(E1->u.type->u.basic == 1) {
			n->type_int = E1->type_int + E2->type_int;
		}
		n->u.type = E1->u.type;
		n->n_type = _BASIC_;
	}
	else
		printf("Error type 7 at Line %d: Type mismatched for operands.\n", n->lineno);
	n->is_left = 0;
	
	return;
}
void F_Exp_ExpMinusExp(struct node* n){
	struct node* E1 = n->gchild[0];
	struct node* E2 = n->gchild[2];
	
	semantic_analysis(E1);
	semantic_analysis(E2);
	
	if(E1->u.type->kind == BASIC && E2->u.type->kind == BASIC) {
		if(E1->u.type->u.basic != E2->u.type->u.basic) {
			printf("float and int calculate!!\n");
			if(E1->u.type->u.basic == 1) {
				E1->u.type->u.basic = 0;
				E1->type_float = E1->type_int;
			}
			else {
				E2->u.type->u.basic = 0;
				E2->type_float = E2->type_int;
			}
			n->type_float = E1->type_float - E2->type_float;
		}
		else if(E1->u.type->u.basic == 0) {
			n->type_float = E1->type_float - E2->type_float;
		}
		else if(E1->u.type->u.basic == 1) {
			n->type_int = E1->type_int - E2->type_int;
		}
		n->u.type = E1->u.type;
		n->n_type = _BASIC_;
	}
	else
		printf("Error type 7 at Line %d: Type mismatched for operands.\n", n->lineno);
	n->is_left = 0;
	
	return;
}
void F_Exp_ExpStarExp(struct node* n){
	struct node* E1 = n->gchild[0];
	struct node* E2 = n->gchild[2];
	
	semantic_analysis(E1);
	semantic_analysis(E2);
	
	if(E1->u.type->kind == BASIC && E2->u.type->kind == BASIC) {
		if(E1->u.type->u.basic != E2->u.type->u.basic) {
			printf("float and int calculate!!\n");
			if(E1->u.type->u.basic == 1) {
				E1->u.type->u.basic = 0;
				E1->type_float = E1->type_int;
			}
			else {
				E2->u.type->u.basic = 0;
				E2->type_float = E2->type_int;
			}
			n->type_float = E1->type_float * E2->type_float;
		}
		else if(E1->u.type->u.basic == 0) {
			n->type_float = E1->type_float * E2->type_float;
		}
		else if(E1->u.type->u.basic == 1) {
			n->type_int = E1->type_int * E2->type_int;
		}
		n->u.type = E1->u.type;
		n->n_type = _BASIC_;
	}
	else
		printf("Error type 7 at Line %d: Type mismatched for operands.\n", n->lineno);
	n->is_left = 0;
	
	return;
}
void F_Exp_ExpDivExp(struct node* n){
	struct node* E1 = n->gchild[0];
	struct node* E2 = n->gchild[2];
	
	semantic_analysis(E1);
	semantic_analysis(E2);
	
	if(E1->u.type->kind == BASIC && E2->u.type->kind == BASIC) {
		if(E1->u.type->u.basic != E2->u.type->u.basic) {
			printf("float and int calculate!!\n");
			if(E1->u.type->u.basic == 1) {
				E1->u.type->u.basic = 0;
				E1->type_float = E1->type_int;
			}
			else {
				E2->u.type->u.basic = 0;
				E2->type_float = E2->type_int;
			}
			n->type_float = E1->type_float / E2->type_float;
		}
		else if(E1->u.type->u.basic == 0) {
			n->type_float = E1->type_float / E2->type_float;
		}
		else if(E1->u.type->u.basic == 1) {
			n->type_int = E1->type_int / E2->type_int;
		}
		n->u.type = E1->u.type;
		n->n_type = _BASIC_;
	}
	else
		printf("Error type 7 at Line %d: Type mismatched for operands.\n", n->lineno);
	n->is_left = 0;
	
	return;
}
void F_Exp_LpExpRp(struct node* n){
	struct node* E1 = n->gchild[0];
	
	semantic_analysis(E1);
	n->u.type = E1->u.type;
	n->is_left = 0;
	
	return;
}
void F_Exp_MinusExp(struct node* n){
	struct node* E1 = n->gchild[0];
	semantic_analysis(E1);
	
	if(E1->u.type->kind != BASIC)
		printf("Error type 7 at Line %d: Type mismatched for operands.\n", n->lineno);
	
	n->u.type = E1->u.type;
	n->n_type = _BASIC_;
	
	if(E1->u.type->u.basic) {
		n->type_int = -E1->type_int;
	}
	else {
		n->type_float = -E1->type_float;
	}
	n->is_left = 0;
	
	return;
}
void F_Exp_NotExp(struct node* n){
	struct node* E1 = n->gchild[0];
	semantic_analysis(E1);
	
	if(E1->u.type->kind != BASIC)
		printf("Error type 7 at Line %d: Type mismatched for operands.\n", n->lineno);
	else if(E1->u.type->u.basic != 1)
		printf("Error type 7 at Line %d: Type mismatched for operands.\n", n->lineno);
	
	n->u.type = E1->u.type;
	n->n_type = _BASIC_;
	n->type_int = !(E1->type_int);
	n->is_left = 0;
	
	return;
}
void F_Exp_IdLpArgsRp(struct node* n){
	struct node* id = n->gchild[0];
	struct node* args = n->gchild[2];
	char* name = id->str;
	
	args->u.func.argc = 0;
	args->u.func.argv = (Type*)malloc(sizeof(Type)*MAX_ARGC);
	semantic_analysis(args);
	
	SymbolF symF = find_symbolF(name);
	if(symF == NULL) {
		printf("Error type 2 at Line %d: Undefined function \"%s\".\n", n->lineno, name);
	}
	
	strcpy(n->str, name);
	char tmp_argv[55];
	strcat(tmp_argv, "(");
	int cnt = symF->argc;
	for(int i = 0; i<cnt; i++) {
		Type t = symF->argv[i];
		if(t->kind == BASIC) {
			if(t->u.basic)
				strcat(tmp_argv, "int");
			else if(!t->u.basic)
				strcat(tmp_argv, "float");
		}
		else if(t->kind == ARRAY) {
			strcat(tmp_argv, "array");
		}
		else if(t->kind == STRUCTURE) {
			char* s_name = t->u.structure->name;
			strcat(tmp_argv, s_name);
		}
		if(i != cnt-1)
			strcat(tmp_argv, ", ");
	}
	strcat(tmp_argv, ")");
	//strcat(tmp_argv, '\0');
	strcat(n->str, tmp_argv);
	if(args->u.func.argc != symF->argc)
		printf("Error type 9 at Line %d: Function \"%s\" is not applicable for arguments \"%s\".\n", n->lineno, n->str, tmp_argv);
	int i = 0;
	int is_argfault = 0;
	while(symF->argv[i] != NULL && args->u.func.argv[i] != NULL) {
		if(!isEqual(symF->argv[i], args->u.func.argv[i])) {
			printf("type 9 error");
			is_argfault = 1;
			break;
		}
		i++;
	}
	n->u.func.retType = symF->retType;
	if(!is_argfault) {
		n->u.func.retType = symF->retType;
		n->u.func.argc = symF->argc;
		n->u.func.argv = symF->argv;
	}
	else {
		n->u.func.argc = -1;
		n->u.func.argv = NULL;
	}
	n->is_left = 0;
	
	return;
}
void F_Exp_IdLpRp(struct node* n){
	struct node* id = n->gchild[0];
	char* name = id->str;
	
	strcpy(n->str, name);
	strcat(n->str, "()");
	SymbolF symF = find_symbolF(name);
	
	if(symF == NULL)
		printf("Error type 2 at Line %d: Undefined function \"%s\".\n", n->lineno, name);
	if(symF->argc != 0)
		printf("Error type 9 at Line %d: Function \"%s\" is not applicable for arguments \"()\".\n", n->lineno, n->str);
	n->u.func.retType = symF->retType;
	n->is_left = 0;
	
	return;
}
void F_Exp_ExpLbExpRb(struct node* n){
	struct node* Exp1 = n->gchild[0];
	struct node* Exp2 = n->gchild[2];
	
	semantic_analysis(Exp1);
	semantic_analysis(Exp2);
	
	char* name = Exp1->str;
	Symbol sym = find_symbol(name);
	if(sym == NULL)
		printf("Error type 1 at Line %d: Undefined variable \"%s\".\n", n->lineno, name);
	if(Exp1->u.type->kind != ARRAY)
		printf("Error type 10 at Line %d: \"%s\" is not an array.\n", n->lineno, name);
	if(Exp2->u.type->kind != BASIC)
		printf("Error type 12 at Line %d: \"%s\" is not an integer.", n->lineno, Exp2->str);
	else if(Exp2->u.type->u.basic != 1)
		printf("Error type 12 at Line %d: \"%f\" is not an integer.", n->lineno, Exp2->type_float);
	n->u.type = Exp1->u.type; //???
	n->is_left = 1;
	
	return;
}
void F_Exp_ExpDotId(struct node* n){
	struct node* Exp = n->gchild[0];
	struct node* id = n->gchild[2];
	
	semantic_analysis(Exp);
	
	if(Exp->u.type->kind != STRUCTURE)
		printf("Error type 13 at Line %d: Illegal use of \".\".\n", n->lineno);
	char* name = Exp->str;
	Symbol sym = find_symbol(name);
	if(sym == NULL)
		printf("Error type 13 at Line %d: Illegal use of \".\".\n", n->lineno);
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
	else
		n->u.type = id->u.type;
	n->is_left = 1;
	
	return;
}
void F_Exp_Id(struct node* n){
	struct node* id = n->gchild[0];
	char* name = id->str;
	
	Symbol sym = find_symbol(name);
	if(sym == NULL) {
		printf("Error type 1 at Line %d: Undefined variable \"%s\".", n->lineno, name);
		return;
	}
	strcpy(n->str, name);
	n->u.type = id->u.type;
	n->n_type = _ID_;
	n->is_left = 1;
	
	return;
}
void F_Exp_Int(struct node* n){
	n->n_type = _BASIC_;
	
	n->u.type = (Type)malloc(sizeof(struct Type_));
	n->u.type->u.basic = 1;
	n->u.type->kind = BASIC;
	n->type_int = n->gchild[0]->type_int;
	n->is_left = 0;
	
	return;
}
void F_Exp_Float(struct node* n){
	n->n_type = _BASIC_;
	
	n->u.type = (Type)malloc(sizeof(struct Type_));
	n->u.type->u.basic = 0;
	n->u.type->kind = BASIC;
	n->type_float = n->gchild[0]->type_float;
	n->is_left = 0;
	
	return;
}
void F_Args_ExpCommaArgs(struct node* n){
	struct node* Exp = n->gchild[0];
	struct node* Args = n->gchild[2];
	
	semantic_analysis(Exp);
	n->u.func.argv[n->u.func.argc++] = Exp->u.type;
	
	Args->u.func.argc = n->u.func.argc;
	Args->u.func.argv = n->u.func.argv;
	semantic_analysis(Args);
	n->u.func.argc = Args->u.func.argc;
	
	return;
}
void F_Args_Exp(struct node* n)
{
	struct node* Exp = n->gchild[0];
	
	semantic_analysis(Exp);
	n->u.func.argv[n->u.func.argc++] = Exp->u.type;
	
	return;
}


