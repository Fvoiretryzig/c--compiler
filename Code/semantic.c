#include "semantic.h"

void semantic_analysis(struct node* n) {
	if(n == NULL)
		return;
	helper(n->rule);
	
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

}
helper(Exp_ExpAndExp) {

}
helper(Exp_ExpOrExp) {

}
helper(Exp_ExpRelopExp) {

}
helper(Exp_ExpPlusExp) {

}
helper(Exp_ExpMinusExp) {

}
helper(Exp_ExpStarExp) {

}
helper(Exp_ExpDivExp) {

}
helper(Exp_LpExpRp) {

}
helper(Exp_MinusExp) {

}
helper(Exp_NotExp) {

}
helper(Exp_IdLpArgsRp) {

}
helper(Exp_IdLpRp) {

}
helper(Exp_ExpLbExpRb) {

}
helper(Exp_ExpDotId) {
	
}
helper(Exp_Id) {
	char* name = n->child[0]->str;
	n->str = name;
	
	Symbol* sym = find_symbol(name);
	if(sym == NULL) {
		printf("Error type 1 at Line %d: Undefined variable \"%s\".", n->lineno, name);
		return;
	}
	n->u.type = n->child[0]->u.type;
	
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


helper(Terminal) {

}

