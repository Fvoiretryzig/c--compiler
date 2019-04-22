#include "semantic.h"

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

}
helper(Extdef_SpecifierSemi) {

}
helper(Extdef_SpcifierFundecCompst) {

}
helper(Extdeclist_Vardec) {

}
helper(Extdeclist_VardecCommaExtdeclist) {

}
helper(Specifier_Type) {

}
helper(Specifier_Structspecifier) {

}
helper(StructSpecifier_StructOpttagLcDeflistRc) {

}
helper(StructSpecifier_StructTag) {

}
helper(Opttag_Id) {

}
helper(Opttag_Null) {

}
helper(Tag_Id) {

}
helper(Vardec_Id) {

}
helper(Vardec_VardecLbIntRb) {

}
helper(Fundec_IdLpVarlistRp) {

}
helper(Fundec_IdLpRp) {

}
helper(Varlist_ParamdecCommaVarlist) {

}
helper(Varlist_Paramdec) {

}
helper(Paramdec_SpecifierVardec) {

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

}
helper(Deflist_Null) {

}
helper(Def_SpecifierDeclistSemi) {

}
helper(Declist_Dec) {

}
helper(Declist_DecCommaDeclist) {

}
helper(Dec_Vardec) {

}
helper(Dec_VardecAssignopExp) {

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
	
	SymbolF* symF = find_symbolF(name);
	Symbol* sym = find_symbol(name);
	if(sym != NULL) {
		printf("Error type 11 at Line %d: \"%s\" is not a function.\n", n->lineno, name);
		return;
	}
	if(symF == NULL) {
		printf("Error type 2 at Line %d: Undefined function \"%s\".\n", n->lineno, name);
		return;
	}
	semantic_analysis(args);
	
	if(args->u.func.argc != symF->argc) {
		printf("Error type 9 at Line %d: Function \"%s\" is not applicable for arguments \"%s\".\n", n->lineno, name, args->str);//TODO()输出内容有问题
	}
	else {
		
	}
	strcpy(n->str, name);
	//TODO() 函数参数怎么存
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


