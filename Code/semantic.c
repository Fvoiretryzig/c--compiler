#include "semantic.h"

int top = -1;
void semantic_analysis(struct node* n) {
	if(n == NULL)
		return;
	helper(n->rule);
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
		if(!isEqual(a->u.structure->type))
			return 0;
	}
	return 1;
}
helper(Program_Extdeflist) {
	
}
helper(Extdeflist_ExtdefExtdeflist) {

}
helper(Extdeflist_Null) {

}
helper(Extdef_SpecifierExtdeclistSemi) {
	struct node* Specifier = n->gchild[0];
	struct node* Extdeclist = n->gchild[1];
	
	semantic_analysis(Specifier);
	Extdeclist->u.type = Specifier->u.type;
	semantic_analysis(Extdeclist);
	
	//TODO()?????
	return;
}
helper(Extdef_SpecifierSemi) {
	struct node* Specifier = n->gchild[0];
	
	semantic_analysis(Specifier);
	
	//TODO()
}
helper(Extdef_SpcifierFundecCompst) {
	struct node* Specifier = n->child[0];
	struct node* Fundec = n->child[1];
	struct node* Compst = n->child[2];
	
	semantic_analysis(Specifier);
	Fundec->u.func.retType = Specifier->u.type;
	semantic_analysis(Fundec);
	semantic_analysis(Compst);
	
	//TODO()
}
helper(Extdeclist_Vardec) {
	struct node* Vardec = n->child[0];
	
	semantic_analysis(Vardec);
	//TODO();
}
helper(Extdeclist_VardecCommaExtdeclist) {
	struct node* Vardec = n->child[0];
	struct node* Extdeclist = n->child[2];
	
	semantic_analysis(Vardec);
	semantic_analysis(Extdeclist);
	
	//TODO();
}
helper(Specifier_Type) {
	struct node* ttype = n->child[0];
	char* basic_type = ttype->str;
	
	if(!strcmp(basic_type, "int")) {
		n->u.type = (Type)malloc(sizeof(Type_));
		n->u.type->kind = BASIC;
		n->u.type->u.basic = 1;
	}
	else if(!strcmp(basic_type, "float")) {
		n->u.type = (Type)malloc(sizeof(Type_));
		n->u.type->kind = BASIC;
		n->u.type->u.basic = 0;
	}
	
	return;
}
helper(Specifier_Structspecifier) {
	struct node* Structspecifier = n->child[0];
	
	semantic_analysis(Structspecifier);
	n->u.type = Structspecifier->u.type;
	
	return;
}
helper(StructSpecifier_StructOpttagLcDeflistRc) {
	//两种情况判断
	struct node* Opttag = n->child[1];
	//还没处理没有名字的情况 //TODO()
	struct node* Deflist = n->child[3];
	
	semantic_analysis(Opttag);
	char* name = Opttag->str;
	
	strcpy(n->str, name);
	n->u.type = (Type)malloc(sizeof(Type_));
	n->u.type->kind = STRUCTURE;
	n->n_type = _STRUCTURE_;
	n->u.type->u.structure = tmp_table[++top];
	tmp_table[top] = NULL;
	
	symbol* sym = find_symbol(name);
	if(sym != NULL) {	//类型和变量重名?
		printf("Error type 16 at Line %d: Duplicated name \"%s\".\n", n->lineno, name);
		return;
	}
	semantic_analysis(Deflist);
	
	//不知道内存分配这些问题对不对//TODO();
	n->u.type->u.structure = (FieldList)malloc(sizeof(FieldList_));
	memcpy(n->u.type->u.structure, tmp_table[top]);
	free(tmp_table[top]);
	add_symbol(n, name);
	
	top--;
	return;
}
helper(StructSpecifier_StructTag) {
	struct node* tag = n->child[1];
	
	semantic_analysis(tag);
	char* name = tag->str;
	
	Symbol* sym = find_symbol(name);
	if((sym == NULL) || sym->idkind != _STRUCT) {
		printf("Error type 17 at Line %d: Undefined structure \"%s\".\n", n->lineno, name);
	}
	
	n->u.type = tag->u.type;
	//TODO();
}
helper(Opttag_Id) {
	struct node* id = n->child[0];
	char* name = id->str;
	
	strcpy(n->str, name);
	
	return;
}
helper(Opttag_Null) {
	//no name
}
helper(Tag_Id) {
	struct node* id = n->child[0];
	char* name = id->str;
	
	strcpy(n->str, name);
	
	return;
}
helper(Vardec_Id) {
	struct node* id = n->child[0];
	char* name = id->str;
	
	id->u.type = n->u.type;
	id->n_type = _VAR_;
	
	if(top == -1) {
		Symbol* sym = find_symbol(name);
		if(sym != NULL && sym->idkind == _VAR) {
			printf("Error type 3 at Line %d: Redefined variable \"%s\".\n", n->lineno, name);
			return;
		}
		else {
			int ret = add_symbol(id, name);
			if(ret) {
				printf("add to symbol table error!\n");
				return;
			}
		}	
	}
	else {
		if(tmp_table[top] == NULL) {
			FieldList new_field = (FieldList)malloc(sizeof(FieldList_));
			strcpy(new_field->name, name);
			new_field->type = id->u.type;
			new_field->tail = NULL;
			tmp_table[top] = new_field;
		}
		else {
			FieldList field = tpm_table[top];
			while(field->tail != NULL) {
				if(!strcmp(name, field->name)) {
					printf("Error type 15 at Line %d: Redefined field \"%s\".", n->lineno, name);
					return;
				}
			}
			FieldList new_field = (FieldList)malloc(sizeof(FieldList_));
			strcpy(new_field->name, name);
			new_field->type = id->u.type;
			new_field->tail = NULL;
			field->tail = new_field;
		}
	}
	return;
}
helper(Vardec_VardecLbIntRb) {
	struct node* Vardec = n->child[0];
	struct node* Int = n->child[1];
	int size = Int->type_int;
	
	Vardec->type = n->type;
		
}
helper(Fundec_IdLpVarlistRp) {
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
	
	SymbolF* symF = find_symbolF(name);
	if(symF != NULL) {
		printf("Error type 4 at Line %d: Redefined function \"%s\".\n", n->lineno, name);
		return;
	}
	int ret = add_symbolF(n, name);
	if(ret) {
		printf("error when add func %s\n", name);
		return;
	}
	return;
}
helper(Fundec_IdLpRp) {
	struct node* id = n->gchild[0];
	char* name = id->str;
	
	id->u.n_type = _FUNC_;
	id->u.func.retType = n->u.func.retType;
	id->u.func.argc = 0;
	
	SymbolF* symF = find_symbolF(name);
	if(symF != NULL) {
		printf("Error type 4 at Line %d: Redefined function \"%s\".\n", n->lineno, name);
		return;
	}
	int ret = add_symbolF(n, name);
	if(ret) {
		printf("error when add func %s\n", name);
		return;
	}
	return;
}
helper(Varlist_ParamdecCommaVarlist) {
	struct node* Paramdec = n->gchild[0];
	struct node* Varlist = n->gchild[2];
	
	Paramdec->u.func.argc = n->u.func.argc;
	Paramdec->u.func.argv = n->u.func->argv;
	semantic_analysis(Paramdec);
	
	n->u.func.argc = Paramdec->u.func.argc;
	
	Varlist->u.func.argc = n->u.func.argc;
	varlist->u.func.argv = n->u.func->argv;
	semantic_analysis(Varlist);
	
	n->u.func.argc = Varlist->u.func.argc;
	
	return;
}
helper(Varlist_Paramdec) {
	struct node* Paramdec = n->gchild[0];
	
	Paramdec->u.func.argc = n->u.func.argc;
	Paramdec->u.func.argv = n->u.func->argv;
	semantic_analysis(Paramdec);
	
	n->u.func.argc = Paramdec->u.func.argc;
	
	return;
}
helper(Paramdec_SpecifierVardec) {
	struct node* Specifier = n->gchild[0];
	struct node* Vardec = n->gchild[1];
	
	semantic_analysis(Specifier);
	Vardec->u.type = Specifier->u.type;
	
	semantic_analysis(Vardec);	//是否要特判加入符号表?
	
	n->u.func.argv[n->u.func.argc++] = Vardec->u.type;
	
	return;
}
helper(Compst_LcDeflistStmtlistRc) {

}
helper(Stmtlist_StmtStmtlist) {

}
helper(Stmtlist_Null) {

}
helper(Stmt_ExpSemi) {

}
helper(Stmt_Compst) {

}
helper(Stmt_ReturnExpSemi) {

}
helper(Stmt_IfLpExpRpStmtElse) {

}
helper(Stmt_IfLpExpRpStmtElseStmt) {

}
helper(Stmt_WhileLpExpRpStmt) {

}
helper(Deflist_DefDeflist) {
	struct node* Def = n->gchild[0];
	struct node* Deflist = n->gchild[1];
	
	semantic_analysis(Def);
	if(Deflist != NULL)
		semantic_analysis(Deflist);
	return;
}
helper(Deflist_Null) {

}
helper(Def_SpecifierDeclistSemi) {
	struct node* Specifier = n->gchild[0];
	struct node* Declist = n->gchild[1];
	
	semantic_analysis(Specifier);
	Declist->u.type = Specifier->u.type;
	semantic_analysis(Declist);
}
helper(Declist_Dec) {
	struct node* Dec = n->gchild[0];
	
	Dec->u.type = n->u.type;
	semantic_analysis(Dec);
}
helper(Declist_DecCommaDeclist) {
	struct node* Dec = n->gchild[0];
	struct node* Declist = n->gchild[2];
	
	Dec->u.type = n->u.type;
	semantic_analysis(Dec);
	
	semantic_analysis(Declist);
}
helper(Dec_Vardec) {
	struct node* Vardec = n->gchild[0];
	
	Vardec->u.type = n->u.type;
	semantic_analysis(Vardec);
}
helper(Dec_VardecAssignopExp) {
	struct node* Vardec = n->gchild[0];
	struct node* Exp = n->gchild[2];
	
	Vardec->u.type = n->u.type;
	semantic_analysis(Vardec);
	semantic_analysis(Exp);
}
helper(Exp_ExpAssignopExp) {
	struct node* E1 = n->gchild[0];
	struct node* E2 = n->gchild[2];
	
	semantic_analysis(E1);
	semantic_analysis(E2);
	
	if(!isEqual(E1->u.type, E2->y.type)) {
		printf("Error type 5 at Line %d: Type mismatched for assignment.\n", n->lineno);
		return;
	}
	Exp->u.type = E1->u.type;	//??????????
	//TODO()根据类型进行判断再把E2的值赋给E1
}
helper(Exp_ExpAndExp) {
	struct node* E1 = n->gchild[0];
	struct node* E2 = n->gchild[2];
	
	semantic_analysis(E1);
	semantic_analysis(E2);
	
	if(E1->u.type->kind != BASIC || E2->u.type->kind != BASIC) {
		printf("Error type 7 at Line %d: Type mismatched for operands.\n", n->lineno);
		return;
	}
	else if(E1->u.type->basic != 1 || E2->u.type->basic != 1) {
		printf("Error type 7 at Line %d: Type mismatched for operands.\n", n->lineno);
		return;
	}
	n->u.type = E1->u.type;
	E->type_int = E1->type_int && E2->type_int;
	n->n_type = _BASIC_;
	return;
}
helper(Exp_ExpOrExp) {
	struct node* E1 = n->gchild[0];
	struct node* E2 = n->gchild[2];
	
	semantic_analysis(E1);
	semantic_analysis(E2);
	
	if(E1->u.type->kind != BASIC || E2->u.type->kind != BASIC) {
		printf("Error type 7 at Line %d: Type mismatched for operands.\n", n->lineno);
		return;
	}
	else if(E1->u.type->basic != 1 || E2->u.type->basic != 1) {
		printf("Error type 7 at Line %d: Type mismatched for operands.\n", n->lineno);
		return;
	}
	n->u.type = E1->u.type;
	E->type_int = E1->type_int || E2->type_int;
	n->n_type = _BASIC_;
	return;
}
helper(Exp_ExpRelopExp) {
	struct node* E1 = n->gchild[0];
	struct node* Relop = n->gchild[1];
	struct node* E2 = n->gchild[2];
	int is_float = 0;
	
	semantic_analysis(E1);
	semantic_analysis(E2);

	if(E1->u.type->kind != BASIC || E2->u.type->kind != BASIC) {
		printf("Error type 7 at Line %d: Type mismatched for operands.\n", n->lineno);
		return;
	}
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
	switch(op) {
		case ">":
			if(is_float)
				n->type_int = (E1->type_float > E2->type_float);
			else
				n->type_int = (E1->type_int > E2->type_int);
			break;
		case "<":
			if(is_float)
				n->type_int = (E1->type_flaot < E2->type_float);
			else
				n->type_int = (E1->type_int < E2->type_int);
			break;
		case ">=":
			if(is_float)
				n->type_int = (E1->type_flaot >= E2->type_float);
			else
				n->type_int = (E1->type_int >= E2->type_int);
			break;
		case "<=":
			if(is_float)
				n->type_int = (E1->type_flaot <= E2->type_float);
			else
				n->type_int = (E1->type_int <= E2->type_int);
			break;
		case "==":
			if(is_float)
				n->type_int = (E1->type_flaot == E2->type_float);
			else
				n->type_int = (E1->type_int == E2->type_int);
			break;
		case "!=":
			if(is_float)
				n->type_int = (E1->type_flaot != E2->type_float);
			else
				n->type_int = (E1->type_int != E2->type_int);
			break;
	}
	return;
}
helper(Exp_ExpPlusExp) {
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
			E->type_float = E1->type_float + E2->type_float;
		}
		else if(E1->u.type->u.basic == 0) {
			E->type_float = E1->type_float + E2->type_float;
		}
		else if(E1->u.type->u.basic == 1) {
			E->type_int = E1->type_int + E2->type_int;
		}
		n->u.type = E1->u.type;
		n->n_type = _BASIC_;
	}
	else {
		printf("Error type 7 at Line %d: Type mismatched for operands.\n", n->lineno);
		return;
	}
	return;
}
helper(Exp_ExpMinusExp) {
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
			E->type_float = E1->type_float - E2->type_float;
		}
		else if(E1->u.type->u.basic == 0) {
			E->type_float = E1->type_float - E2->type_float;
		}
		else if(E1->u.type->u.basic == 1) {
			E->type_int = E1->type_int - E2->type_int;
		}
		n->u.type = E1->u.type;
		n->n_type = _BASIC_;
	}
	else {
		printf("Error type 7 at Line %d: Type mismatched for operands.\n", n->lineno);
		return;
	}
	return;
}
helper(Exp_ExpStarExp) {
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
			E->type_float = E1->type_float * E2->type_float;
		}
		else if(E1->u.type->u.basic == 0) {
			E->type_float = E1->type_float * E2->type_float;
		}
		else if(E1->u.type->u.basic == 1) {
			E->type_int = E1->type_int * E2->type_int;
		}
		n->u.type = E1->u.type;
		n->n_type = _BASIC_;
	}
	else {
		printf("Error type 7 at Line %d: Type mismatched for operands.\n", n->lineno);
		return;
	}
	return;
}
helper(Exp_ExpDivExp) {
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
			E->type_float = E1->type_float / E2->type_float;
		}
		else if(E1->u.type->u.basic == 0) {
			E->type_float = E1->type_float / E2->type_float;
		}
		else if(E1->u.type->u.basic == 1) {
			E->type_int = E1->type_int / E2->type_int;
		}
		n->u.type = E1->u.type;
		n->n_type = _BASIC_;
	}
	else {
		printf("Error type 7 at Line %d: Type mismatched for operands.\n", n->lineno);
		return;
	}
	return;
	
}
helper(Exp_LpExpRp) {
	struct node* E1 = n->gchild[0];
	semantic_analysis(E1);
	n->u.type = E1->u.type;
	/*n_type???*/
	return;
}
helper(Exp_MinusExp) {
	struct node* E1 = n->gchild[0];
	semantic_analysis(E1);
	
	if(E1->u.type->kind != BASIC) {
		printf("Error type 7 at Line %d: Type mismatched for operands.\n", n->lineno);
		return;
	}
	
	n->u.type = E1->u.type;
	n->n_type = _BASIC_;
	
	if(E1->u.type->u.basic) {
		E->type_int = -E1->type_int;
	}
	else {
		E->type_float = -E1->type_float;
	}
	return;
}
helper(Exp_NotExp) {
	struct node* E1 = n->gchild[0];
	semantic_analysis(E1);
	
	if(E1->u.type->kind != BASIC) {
		printf("Error type 7 at Line %d: Type mismatched for operands.\n", n->lineno);
		return;
	}
	else if(E1->u.type->u.basic != 1) {
		printf("Error type 7 at Line %d: Type mismatched for operands.\n", n->lineno);
		return;
	}
	
	n->u.type = E1.u->type;
	n->n_type = _BASIC_;
	E->type_int = !(E1->type_int);
	
	return;
}
helper(Exp_IdLpArgsRp) {
	struct node* id = n->gchild[0];
	struct node* args = n->gchild[2];
	char* name = id->str;
	
}
helper(Exp_IdLpRp) {

}
helper(Exp_ExpLbExpRb) {

}
helper(Exp_ExpDotId) {
	
}
helper(Exp_Id) {
	struct node* id = n->child[0];
	char* name = id->str;
	
	Symbol* sym = find_symbol(name);
	if(sym == NULL) {
		printf("Error type 1 at Line %d: Undefined variable \"%s\".", n->lineno, name);
		return;
	}
	strcpy(n->str, name);
	n->u.type = id->u.type;
	n->n_type = _ID_;
	
	return;
}
helper(Exp_Int) {
	n->n_type = _BASIC_;
	
	n->u.type = (Type)malloc(sizeof(struct Type_));
	n->u.type->basic = 1;
	n->u.type->kind = BASIC;
	n->type_int = n->gchild[0]->type_int;
	
	return;
}
helper(Exp_Float) {
	n->n_type = _BASIC_;
	
	n->u.type = (Type)malloc(sizeof(struct Type_));
	n->u.type->basic = 0;
	n->u.type->kind = BASIC;
	n->type_float = n->gchild[0]->type_float;
	
	return;
}

helper(Args_ExpCommaArgs) {

}
helper(Args_Exp) {

}


