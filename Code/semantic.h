

#ifndef SEMANTIC_H
#define SEMANTIC_H
#include "symbol_table.h"
#define MAX_ARGC 40

void semantic_analysis(struct node* n);
int isEqual(Type a, Type b);

void F_Program_Extdeflist(struct node* n);
void F_Extdeflist_ExtdefExtdeflist(struct node* n);
void F_Extdeflist_Null(struct node* n);
void F_Extdef_SpecifierExtdeclistSemi(struct node* n);
void F_Extdef_SpecifierSemi(struct node* n);
void F_Extdef_SpcifierFundecCompst(struct node* n);
void F_Extdeclist_Vardec(struct node* n);
void F_Extdeclist_VardecCommaExtdeclist(struct node* n);
void F_Specifier_Type(struct node* n);
void F_Specifier_Structspecifier(struct node* n);
void F_StructSpecifier_StructOpttagLcDeflistRc(struct node* n);
void F_StructSpecifier_StructTag(struct node* n);
void F_Opttag_Id(struct node* n);
void F_Opttag_Null(struct node* n);
void F_Tag_Id(struct node* n);
void F_Vardec_Id(struct node* n);
void F_Vardec_VardecLbIntRb(struct node* n);
void F_Fundec_IdLpVarlistRp(struct node* n);
void F_Fundec_IdLpRp(struct node* n);
void F_Varlist_ParamdecCommaVarlist(struct node* n);
void F_Varlist_Paramdec(struct node* n);
void F_Paramdec_SpecifierVardec(struct node* n);
void F_Compst_LcDeflistStmtlistRc(struct node* n);
void F_Stmtlist_StmtStmtlist(struct node* n);
void F_Stmtlist_Null(struct node* n);
void F_Stmt_ExpSemi(struct node* n);
void F_Stmt_Compst(struct node* n);
void F_Stmt_ReturnExpSemi(struct node* n);
void F_Stmt_IfLpExpRpStmt(struct node* n);
void F_Stmt_IfLpExpRpStmtElseStmt(struct node* n);
void F_Stmt_WhileLpExpRpStmt(struct node* n);
void F_Deflist_DefDeflist(struct node* n);
void F_Deflist_Null(struct node* n);
void F_Def_SpecifierDeclistSemi(struct node* n);
void F_Declist_Dec(struct node* n);
void F_Declist_DecCommaDeclist(struct node* n);
void F_Dec_Vardec(struct node* n);
void F_Dec_VardecAssignopExp(struct node* n);
void F_Exp_ExpAssignopExp(struct node* n);
void F_Exp_ExpAndExp(struct node* n);
void F_Exp_ExpOrExp(struct node* n);
void F_Exp_ExpRelopExp(struct node* n);
void F_Exp_ExpPlusExp(struct node* n);
void F_Exp_ExpMinusExp(struct node* n);
void F_Exp_ExpStarExp(struct node* n);
void F_Exp_ExpDivExp(struct node* n);
void F_Exp_LpExpRp(struct node* n);
void F_Exp_MinusExp(struct node* n);
void F_Exp_NotExp(struct node* n);
void F_Exp_IdLpArgsRp(struct node* n);
void F_Exp_IdLpRp(struct node* n);
void F_Exp_ExpLbExpRb(struct node* n);
void F_Exp_ExpDotId(struct node* n);
void F_Exp_Id(struct node* n);
void F_Exp_Int(struct node* n);
void F_Exp_Float(struct node* n);
void F_Args_ExpCommaArgs(struct node* n);
void F_Args_Exp(struct node* n);


FieldList tmp_table[55];
#endif
