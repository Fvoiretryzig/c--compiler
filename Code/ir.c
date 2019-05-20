#include "ir.h"
#include <stdlib.h>

#include "symbol_table.h"

#define IR_DEBUG
InterCodes IRhead;
Operand ophead;
static int lable_cnt;
static int var_cnt;
static int tmp_cnt;
Operand imm_num0;
Operand imm_num1;
//////////////////////////////////////////////init/////////////////////////////////////////////////////
void init_irlist()
{
	IRhead = (InterCodes)malloc(sizeof(struct InterCodes_));
	if(IRhead == NULL) {
		printf("\033[47;31mERROR when malloc irhead\033[0m\n");
		return;
	}
	IRhead->prev = NULL; IRhead->next = NULL;

	return;
}
void init_oplist()
{
	ophead = (Operand)malloc(sizeof(struct Operand_));
	if(ophead == NULL) {
		printf("\033[47;31mERROR when malloc ophead\033[0m\n");
		return;
	}
	ophead->next = NULL;
	return;
}
void init_translate()
{
	int lable_cnt = 0;
	int var_cnt = 0;
	int tmp_cnt = 0;
	Operand imm_num0 = (Operand)malloc(sizeof(struct Operand_));	
	Operand imm_num1 = (Operand)malloc(sizeof(struct Operand_));
	imm_num0->kind = IMM_NUMBER;
	imm_num0->u.value_int = 0;
	imm_num1->kind = IMM_NUMBER;
	imm_num1->u.value_int = 1;
	
	return;
}
///////////////////////////////////////Operation/////////////////////////////////////////////////
int insert_ircode(InterCodes ir_code)
{
	InterCodes curr = IRhead;
	while(curr->next != NULL)
		curr = curr->next;
	curr->next = ir_code;
	ir_code->prev = curr;	
	InterCodes last = ir_code;
	while(last->next != NULL)
		last = last->next;
	last->next = NULL; 	//necessary????
	
	return 0;
}
int insert_op(Operand op)
{
	Operand curr = ophead;
	while(curr->next != NULL)
		curr = curr->next;
	curr->next = op;
	op->next = NULL
	
	return 0;
}
Operand find_op(char* name) {
	Operand curr = ophead;
	while(curr!= NULL) {
		if(!strcmp(name, curr->v_name))
			return curr;
		curr = curr->next;
	}
	return NULL;
}
void print(struct node* root) 
{
	InterCodes irlist = translate_program(root);
	InterCodes curr = irlist;
	while(curr) {
		print_ir(curr);
		curr = curr->next;
	}
	return;
}
void print_op(Operand op) 
{
	switch(op->kind) {
		case VARIABLE:
			printf("v%d", op->u.var_no);
			break;
		case ADDRESS:
			//TODO();
		case LABEL:
			printf("label%d", op->u.label_no);
			break;
		case FUNCTION:
			printf("%s", op->u.f_name);
			break;
		case TMP:
			printf("t%d", op->u.tmp_no);
			break;
		case IMM_NUMBER:
			printf("%d", op->u.value_int);
			break;
		case ADDRESS_CONTENT:
			//TODO();
	}
}
void print_ir(InterCodes ir)
{
	switch(ir->kind) {
		case D_LABEL:
			Operand label = ir->u.label.x;
			printf("LABEL "); print_op(x); printf(" :\n");
			break;
		case D_FUNCTION:
			Operand func = ir->u.function.f;
			printf("FUNCTION "); print_op(f); printf(" :\n");
			break;
		case ASSIGN:
			Operand x = ir->u.assign.x;
			Operand y = ir->u.assign.y;
			print_op(x); printf(" := "); print_op(y); printf("\n");
			break;
		case ADD:
			Operand x = ir->u.arithmetic.x;
			Operand y = ir->u.arithmetic.y;
			Operand z = ir->u.arithmetic.z;
			print_op(x); printf(" := "); print_op(y); printf(" + "); print_op(z); printf("\n");
			break;
		case SUB:
			Operand x = ir->u.arithmetic.x;
			Operand y = ir->u.arithmetic.y;
			Operand z = ir->u.arithmetic.z;
			print_op(x); printf(" := "); print_op(y); printf(" - "); print_op(z); printf("\n");
			break;			
		case MUL: 
			Operand x = ir->u.arithmetic.x;
			Operand y = ir->u.arithmetic.y;
			Operand z = ir->u.arithmetic.z;
			print_op(x); printf(" := "); print_op(y); printf(" * "); print_op(z); printf("\n");
			break;		
		case DIV:
			Operand x = ir->u.arithmetic.x;
			Operand y = ir->u.arithmetic.y;
			Operand z = ir->u.arithmetic.z;
			print_op(x); printf(" := "); print_op(y); printf(" / "); print_op(z); printf("\n");
			break;		
		case ASSIGN_ADDR:
			//TODO();
		case ADDR_ASSIGNED:
			//TODO();
		case JUMP:
			Operand label = ir->u.jump.x;
			printf("GOTO "); print_op(label); printf("\n");
			break;
		case IF_JUMP:
			Operand x = ir->u.if_jump.x;
			Operand y = ir->u.if_jump.y;
			Opearnd z = ir->u.if_jump.z;
			printf("IF "); print_op(x); 
			switch(ir->u.if_jump.op) {
				case 0:	printf(" > "); break;
				case 1: printf(" < "); break;
				case 2: printf(" >= "); break;
				case 3: printf(" <= "); break;
				case 4: printf(" == "); break;
				case 5: printf(" != "); break;
			}
			print_op(y); printf(" GOTO "); print_op(z); printf("\n");
			break;
		case RET:
			Opearnd x = ir->u.ret.x;
			printf("RETURN "); print_op(x); printf("\n");
			break;
		case DEC:
			Operand x = ir->u.dec.x;
			int size = ir->u.dec.size;
			printf("DEC "); print_op(x); printf(" %d\n", size);
			break;
		case ARG:
			Operand x = ir->u.arg.x;
			printf("ARG "); print_op(x); printf("\n");
			break;
		case CALL:
			Operand x = ir->u.call.x;
			Operand f = ir->u.call.f;
			print_op(x); printf(" := CALL "); print_op(f); printf("\n");
			break;
		case PARA:
			Operand x = ir->u.para.x;
			printf("PARAM "); print_op(x); printf("\n");
			break;
		case READ:
			Operand x = ir->u.read.x;
			printf("READ "); print_op(x); printf("\n");
			break;
		case WRITE:
			Operand x = ir->u.read.x;
			printf("WRITE "); print_op(x); printf("\n")
			break;
	}
	return;
}
InterCodes concat(InterCodes ir1, InterCodes ir2)
{
	InterCodes curr1 = ir1, curr2 = ir2;
	while(curr1->next)
		curr1 = curr1->next;
	curr1->next = ir2; ir2->prev = curr1;
	return ir1;
}
Operand new_Operand(struct node* gnode, int kind, float n, int if_float)
{
	Operand op = (Operand)malloc(sizeof(struct Operand_));
	switch(kind) {
		case VARIABLE:
			op->kind = VARIABLE;
			op->u.val_no = var_cnt++;
			if(gnode)
				strcpy(op->v_name, gnode->str);
			break;
		//case CONSTANT
		case ADDRESS:
			//TODO()
		//case LABEL
		case FUNCTION:
			op->kind = FUNCTION;
			strcpy(op->u.f_name, gnode->str);
			break;
		//case TMP
		case IMM_NUMBER:
			op->kind = IMM_NUMBER;
			if(gnode)
				if(!isfloat)
					op->u.value_int = gnode->type_int;
				else
					op->u.value_float = gnode->type_float;
			else
				if(!isfloat)
					op->u.value_int = (int)n;
				else
					op->u.value_float = n;
			break;
		case ADDRESS_CONTENT:
			//TODO();
	}
	insert_op(op);
	return op;
}
Operand new_temp()
{
	Operand temp = (Operand)malloc(sizeof(struct Operand_));
	temp->kind = TMP;
	temp->u.tmp_no = tmp_cnt++;
	insert_op(temp);
	return temp;
}
Operand new_label()
{
	Operand label = (Operand)malloc(sizeof(struct Operand_));
	label->kind = LABEL;
	label->u.label_no = label_cnt++;
	insert_op(label);
	return label;
}
InterCodes new_InterCodes(Operand op1, Operand op2, Operand op3, int kind, int op)
{
	InterCodes ir = (InterCodes)malloc(sizeof(struct InterCodes_));
	switch(kind) {
		case D_LABEL:
			ir->kind = D_LABEL;
			ir->u.label.x = op1;
			break;
		case D_FUNCTION:
			ir->kind = D_FUNCTION;
			ir->u.function.f = op1;
			break;
		case ASSIGN:
			ir->kind = ASSIGN;
			ir->u.assign.x = op1;
			ir->u.assign.y = op2;
			break;
		case ADD:
			ir->kind = ADD;
			ir->u.arithmetic.x = op1;
			ir->u.arithmetic.y = op2;
			ir->u.arithmetic.z = op3;
			break;
		case SUB:
			ir->kind = SUB;
			ir->u.arithmetic.x = op1;
			ir->u.arithmetic.y = op2;
			ir->u.arithmetic.z = op3;
			break;
		case MUL:
			ir->kind = MUL;
			ir->u.arithmetic.x = op1;
			ir->u.arithmetic.y = op2;
			ir->u.arithmetic.z = op3;
			break;
		case DIV:
			ir->kind = DIV;
			ir->u.arithmetic.x = op1;
			ir->u.arithmetic.y = op2;
			ir->u.arithmetic.z = op3;
			break;
		case ASSIGN_ADDR:
			ir->kind = ASSIGN_ADDR;
			ir->u.assign_address.x = op1;
			ir->u.assign_address.y = op2;
			break;
		case ADDR_ASSIGNED:
			ir->kind = ADDR_ASSIGNED;
			ir->u.address_assigned.x = op1;
			ir->u.address_assigned.y = op2;
			break;
		case JUMP:
			ir->kind = JUMP;
			ir->u.jump.x = op1;
			break;
		case IF_JUMP:
			ir->kind = IF_JUMP;
			ir->u.if_jump.x = op1;
			ir->u.if_jump.y = op2;
			ir->u.if_jump.z = op3;
			ir->u.if_jump.op = op;
			break;
		case RET:
			ir->kind = RET;
			ir->u.ret.x = op1;
			break;
		case DEC:
			ir->kind = DEC;
			ir->u.dec.x = op1;
			ir->u.dec.size = op;
			break;
		case ARG:
			ir->kind = ARG;
			ir->u.arg.x = op1;
			break;
		case CALL:
			ir->kind = CALL;
			ir->u.call.x = op1;
			ir->u.call.f = op2;
			break;
		case PARA:
			ir->kind = PARA;
			ir->u.para.x = po1;
			break;
		case READ:
			ir->kind = READ;
			ir->u.read.x = op1;
			break;
		case WRITE:
			ir->kind = WRITE;
			ir->u.write.x = op1;
			break;
	}
	return ir;
}
/////////////////////////////////////////helper//////////////////////////////////////////////////////////
int get_array_size(Type t)
{
	if(t->kind == BASIC)
		return 4;
	int sub_size = get_array_size(t->u.array.elem);
	return sub_size*t->u.array.size;
}
int get_struct_size(Type t)
{
	int size = 0;
	FieldList curr = t->u.structre;
	while(curr) {
		switch(curr->type->kind) {
			case BASIC:
				size += 4;
				break;
			case ARRAY:
				size += get_array_size(curr->type);
				break;
			case STRUCTURE:
				size += get_struct_size(curr->type);
				break;
		}
		curr = curr->tail;
	}
	return size;
}
/////////////////////////////////////////////translate////////////////////////////////////////////////////////
InterCodes translate_program(struct node* program)
{
	InterCodes ir = translate_extdeflist(program->gchild[0]);
	
	return ir;
}
InterCodes translate_extdeflist(struct node* extdeflist)
{
	switch(extdeflist->rule) {
		case Extdeflist_ExtdefExtdeflist:
			InterCodes ir1 = translate_extdef(extdeflist->gchild[0]);
			InterCodes ir2 = translate_extdeflist(extdeflist->gchild[1]);
			
			InterCodes ir = concat(ir1, ir2);
			return ir;
		case Extdeflist_Null:
			return NULL;
	}
}
InterCodes translate_extdef(struct node* extdef)
{
	switch(extdef->rule) {
		case Extdef_SpecifierExtdeclistSemi:
		case Extdef_SpecifierSemi:
			return NULL;	//TODO()应该不用生成代码吧？？？？？
		case Extdef_SpcifierFundecCompst:
			InterCodes ir1 = translate_funcdec(extdef->gchild[1]);
			InterCodes ir2 = translate_Compst(extdef->gchild[2]);
			
			InterCode ir = concat(ir1, ir2);
			return ir;
	}
}
InterCodes translate_funcdec(struct node* funcdec)
{
	switch(funcdec->rule) {
		case Fundec_IdLpVarlistRp:
			Operand func;
			struct node* id = funcdec->gchild[0];
			func = find_op(id->str);
			if(!func) {
				func = new_operand(id, FUNCTION, -1, -1);
			}
			InterCodes ir1 = new_InterCodes(func, NULL, NULL, D_FUNCTION, -1);
			InterCodes ir2 = translate_varlist(funcdec->gchild[2]);
			
			InterCodes ir = concat(ir1, ir2);
			return ir;
		case Fundec_IdLpRp:
			Operand func;
			struct node* id = funcdec->gchlid[0];
			func = find_op(id->str);
			if(!func) {
				func = new_operand(id, FUNCTION, -1, -1);
			}
			InterCodes ir = new_InterCodes(func, NULL, NULL, D_FUNCTION, -1);
			return ir;
	}
}
InterCodes translate_varlist(struct node* varlist)
{
	switch(varlist->rule) {
		case Varlist_ParamdecCommaVarlist:	
			InterCodes ir1 = translate_paradec(varlist->gchild[0]);
			InterCodes ir2 = translate_varlist(varlist->gchild[2]);
			
			InterCodes ir = concat(ir1, ir2);
			return ir;
		case Varlist_Paramdec:
			InterCodes ir = translate_paradec(varlist->gchild[0]);
			return ir;
	}
}
InterCodes translate_paradec(struct node* paradec)
{
	vardec = paradec->gchild[1];
	Operand para;
	para = find_op(vardec->str);
	if(!para)
		para = new_operand(vardec, VARIABLE, -1, -1);
	InterCodes ir = new_InterCodes(para, NULL, NULL, PARA, -1);
	return ir;
}
InterCodes translate_compst(struct node* compst)
{	
	InterCodes ir1 = translate_deflist(compst->gchild[1]);
	InterCodes ir2 = translate_stmtlist(compst->gchild[2]);
	
	InterCodes ir = concat(ir1, ir2);
	return ir;
}
InterCodes translate_deflist(struct node* deflist)
{
	switch(deflist->rule) {
		case Deflist_DefDeflist:
			InterCodes ir1 = translate_def(deflist->gchild[0]);
			InterCodes ir2 = translate_deflist(deflist->gchild[1]);
			
			InterCodes ir = concat(ir1, ir2);
			return ir;
		case Deflist_Null:
			return NULL;
	}
}
InterCodes translate_def(struct node* def)
{
	//def:= Specifier DecList SEMI
	Type specifier = def->gchild[0]->type;
	InterCodes ir = translate_declist(def->gchild[1], specifier);
}
InterCodes translate_declist(struct node* declist, Type specifier)
{
	switch(declist->rule) {
		case Declist_Dec:
			InterCodes ir = translate_dec(def->gchild[0], specifier);
			return ir;
		case Declist_DecCommaDeclist:
			InterCodes ir1 = translate_dec(def->gchild[0], specifier);
			InterCodes ir2 = translate_declist(def->gchild[2], specifier);
			
			InterCodes ir = concat(ir1, ir2);
			return ir;
	}
}
InterCOdes translate_dec(struct node* dec, Type specifier)
{
	switch(dec->rule) {
		case Dec_Vardec:
			struct node* vardec = dec->gchild[0];
			switch(vardec->type->kind) {
				case BASIC:
					printf("!!!!!not need to dec!!!!!\n");
					return NULL;
				case ARRAY:
					Symbol sym = find_symbol(vardec->str);
					Type t = sym->type;
					int size = get_array_size(t);
					Operand v = new_Operand(NULL, VARIABLE, -1, -1);
					InterCodes ir = new_InterCodes(v, NULL, NULL, DEC, size);
					return ir;
				case STRUCTURE:
					Symbol sym = find_symbol(vardec->str);
					Type t = sym->type;
					int size = get_struct_size(t);
					Operand v = new_Operand(NULL, VARIABLE, -1, -1);
					InterCodes ir = new_InterCodes(v, NULL, NULL, DEC, size);
					return ir;
			}
		case Dec_VardecAssignopExp:
			Operand v = new_Operand(NULL, VARIABLE, -1, -1);
			Operand t1 = new_temp();
			InterCodes ir1 = translate_exp(n->gchild[2], t1);
			InterCodes ir2 = new_InterCodes(v, t1, NULL, ASSIGN, -1);
			ir1->next = ir2; ir2->prev = ir1;
			return ir1;
	}
}
InterCodes translate_stmtlist(struct node* stmtlist)
{
	switch(stmtlist->rule) {
		case Stmtlist_StmtStmtlist:
			InterCodes ir1 = translate_stmt(stmtlist->gchild[0]);
			InterCodes ir2 = translate_stmtlist(stmtlist->gchild[1]);
			 
			InterCodes ir = concat(ir1, ir2);
			return ir;
		case Stmtlist_Null:
			return NULL;
	}
}
InterCode translate_stmt(struct node* stmt)
{
	switch(stmt->rule) {
		case Stmt_ExpSemi:
			return translate_exp(stmt->gchild[0], NULL);
		case Stmt_Compst:
			//TODO()
		case Stmt_ReturnExpSemi:
			Operand t1 = new_temp();
			
			InterCodes ir1 = translate_exp(stmt->gchild[1], t1);
			InterCodes ir2 = new_InterCodes(t1, NULL, NULL, RET, -1);
			
			InterCodes ir = concat(ir1, ir2);
			return ir;
		case Stmt_IfLpExpRpStmt:
			Operand label1 = new_label();
			Operand label2 = new_label();
			
			InterCodes ir1 = translate_cond(stmt->gchild[2], label1, label2);
			InterCodes label1_code = new_InterCodes(label1, NULL, NULL, D_LABEL, -1);
			InterCodes ir2 = translate_stmt(stmt->gchild[4]);
			InterCodes label2_code = new_InterCodes(label2, NULL, NULL, D_LABEL, -1);
			
			InterCodes ir = concat(ir, label1_code);
			ir = concat(ir, ir2);
			ir = concat(ir, label2_code);
			return ir;
		case Stmt_IfLpExpRpStmtElseStmt:
			Operand label1 = new_label();
			Opearnd label2 = new_label();
			Operand label3 = new_label();
			
			InterCodes ir1 = translate_cond(stmt->gchild[2], label1, label2);
			InterCodes label1_code = new_InterCodes(label1, NULL, NULL, D_LABEL, -1);
			InterCodes ir2 = translate_stmt(stmt->gchild[4]);
			InterCodes goto3_code = new_InterCodes(label3, NULL, NULL, JUMP);
			InterCodes label2_code = new_InterCodes(label2, NULL, NULL, D_LABEL, -1);
			InterCodes ir3 = translate_stmt(stmt->gchild[6]);
			InterCOdes label3_code = new_InterCodes(label3, NULL, NULL, D_LABEL, -1);
			
			InterCodes ir = concat(ir1, label1_code);
			ir = concat(ir, ir2);
			ir = concat(ir, goto3_code);
			ir = concat(ir, label2_code);
			ir = concat(ir, ir3);
			ir = concat(ir, label3_code);
			return ir;
		case Stmt_WhileLpExpRpStmt:
			Operand label1 = new_label();
			Operand label2 = new_label();
			Operand label3 = new_label();
			
			InterCodes label1_code = new_InterCodes(label1, NULL, NULL, D_LABEL, -1);
			InterCodes ir1 = translate_cond(stmt->gchild[2], label2, label3);
			InterCodes label2_code = new_InterCodes(label2, NULL, NULL, D_LABEL, -1);
			InterCodes ir2 = translate_stmt(stmt->gchild[4]);
			InterCodes goto1_code = new_InterCodes(label1, NULL, NULL, JUMP, -1);
			InterCodes label3_code = new_InterCodes(label3, NULL, NULL, D_LABEL, -1);
			
			InterCodes ir = concat(label1_code, ir1);
			ir = concat(ir, label2_code);
			ir = concat(ir, ir2);
			ir = concat(ir, goto1_code);
			ir = concat(ir, label3_code);
			return ir;
	}
}
int get_relop(struct node* gnode)
{
	int ret = -1;
	if(!strcmp(gnode->relop, ">"))
		ret = 0;
	else if(!strcmp(gnode->relop, "<"))
		ret = 1;
	else if(!strcmp(gnode->relop, ">="))
		ret = 2;
	else if(!strcmp(gnode->relop, "<="))
		ret = 3;
	else if(!strcmp(gnode->relop, "=="))
		ret = 4;
	else if(!strcmp(gnode->relop, "!="))
		ret = 5;
	else 
		printf("get relop fault!!!!!!!\n");
	return ret;
}
InterCodes translate_cond(struct node* exp, Operand label_true, Operand label_faluse)
{
	switch(exp->rule) {
		case Exp_NotExp:
			return translate_cond(exp->gchild[1], label_false, label_true);
		case Exp_ExpAndExp:
			Operand label1 = new_label();
			
			InterCodes ir1 = translate_cond(exp->gchild[0], label1, label_false);
			InterCodes label_code = new_InterCodes(label1, NULL, NULL, D_LABEL, -1);
			InterCodes ir2 = translate_cond(exp->gchild[2], label_true, label_faluse);
			
			InterCodes ir = concat(ir1, label_code);
			ir = concat(ir, ir2);
			return ir;
		case Exp_ExpOrExp:
			Operand label1 = new_label();
			
			InterCodes ir1 = translate_cond(exp->gchild[0], label_true, label1);
			InterCodes label_code = new_InterCodes(label1, NULL, NULL, D_LABEL, -1);
			InterCodes ir2 = translate_cond(exp->gchild[1], label_true, label_false);
			
			InterCodes ir = concat(ir1, label_code);
			ir = concat(ir, ir2);
			return ir;
		case Exp_ExpRelopExp:
			Operand	t1 = new_temp();
			Operand t2 = new_temp();
			
			InterCodes ir1 = translate_exp(exp->gchild[0], t1);
			InterCodes ir2 = translate_exp(exp->gchild[2], t2);
			int op = get_relop(exp->gchild[1]);
			InterCodes ir3 = new_InterCodes(t1, t2, label_true, IF_JUMP, op);
			InterCodes ir4 = new_InterCodes(t1, NULL, NULL, JUMP, -1);
			
			InterCodes ir = concat(ir1, ir2);
			ir = concat(ir, ir3);
			return ir;
		default: 
			t1 = new_temp();
			
			InterCodes ir1 = translate_exp(exp, t1);
			int op = 5;
			InterCodes ir2 = new_InterCodes(t1, imm_num0, label_true, IF_JUMP, op);
			InterCodes label_code = new_InterCodes(label_false, D_label);
			
			InterCodes ir = concat(ir1, ir2);
			ir = concat(ir, label_code);
			return ir;
	}
}
InterCodes translate_exp(struct node* exp, Operand place)
{
	switch(exp->rule) {
		case Exp_ExpAssignopExp:
			Operand variable = new_Operand(exp->gchild[0], VARIABLE, -1, -1);
			Operand t1 = new_temp();
			
			InterCodes ir1 = translate_exp(exp->gchild[2], t1);
			InterCodes ir2_1 = new_InterCodes(variable, t1, NULL, ASSIGN, -1);
			InterCodes ir2_2 = new_InterCodes(place, variable, NULL, ASSIGN, -1);
			
			InterCodes ir2 = concat(ir2_1, ir2_2);
			InterCodes ir = concat(ir1, ir2);
			return ir;
		case Exp_NotExp:
		case Exp_ExpAndExp:
		case Exp_ExpOrExp:
		case Exp_ExpRelopExp:
			Operand label1 = new_label();
			Operand label2 = new_label();
			
			InterCodes ir0 = new_InterCodes(place, imm_num0, NULL, ASSIGN, -1);
			InterCodes ir1 = translate_Cond(exp, label1, label2);
			InterCodes ir2_1 = new_InterCodes(label1, NULL, NULL, D_LABEL, -1);
			InterCodes ir2_2 = new_InterCodes(place, imm_num1, NULL, ASSIGN, -1);
			InterCodes ir3 = new_InterCodes(label2, NULL, NULL, D_LABEL, -1);
			
			InterCodes ir = concat(ir0, ir1);
			ir = concat(ir, ir2_1);
			ir = concat(ir, ir2_2);
			return ir;
		case Exp_ExpPlusExp:
			Operand t1 = new_temp();
			Operand t2 = new_temp();
			
			InterCodes ir1 = translate_exp(exp->gchild[0], t1);
			InterCodes ir2 = translate_exp(exp->gchild[2], t2);
			InterCodes ir3 = new_InterCodes(place, t1, t2, ADD, -1);
			
			InterCodes ir = concat(ir1, ir2);
			ir = concat(ir, ir3);
			return ir;
		case Exp_ExpMinusExp:
			Operand t1 = new_temp();
			Operand t2 = new_temp();
			
			InterCodes ir1 = translate_exp(exp->gchild[0], t1);
			InterCodes ir2 = translate_exp(exp->gchild[2], t2);
			InterCodes ir3 = new_InterCodes(place, t1, t2, SUB, -1);
			
			InterCodes ir = concat(ir1, ir2);
			ir = concat(ir, ir3);
			return ir;
		case Exp_ExpStarExp:
			Operand t1 = new_temp();
			Operand t2 = new_temp();
			
			InterCodes ir1 = translate_exp(exp->gchild[0], t1);
			InterCodes ir2 = translate_exp(exp->gchild[2], t2);
			InterCodes ir3 = new_InterCodes(place, t1, t2, MUL, -1);
			
			InterCodes ir = concat(ir1, ir2);
			ir = concat(ir, ir3);
			return ir;
		case Exp_ExpDivExp:
			Operand t1 = new_temp();
			Operand t2 = new_temp();
			
			InterCodes ir1 = translate_exp(exp->gchild[0], t1);
			InterCodes ir2 = translate_exp(exp->gchild[2], t2);
			InterCodes ir3 = new_InterCodes(place, t1, t2, DIV, -1);
			
			InterCodes ir = concat(ir1, ir2);
			ir = concat(ir, ir3);
			return ir;
		case Exp_LpExpRp:
			//TODO();
		case Exp_MinusExp:
			Operand t1 = new_temp();
			
			InterCodes ir1 = translate_exp(exp->gchild[2], t1);
			InterCodes ir2 = new_InterCodes(place, imm_num0, t1, SUB, -1);
			
			InterCodes ir = concat(ir1, ir2);
			return ir;
		case Exp_IdLpArgsRp:
			char* name = exp->str;
			Operand* arg_list = NULL;
			int arg_cnt = 0;
			InterCodes ir1 = translate_args(exp->gchild[2], arg_list, &arg_cnt);
			if(!strcmp(name, "write")) {
				InterCodes write_code = new_InterCodes(arg_list[0], NULL, NULL, WRITE, -1);
				ir1->next = write_code; write_code->prev = ir1;
				return ir1;
			}
			InterCodes ir2 = (InterCodes)malloc(sizeof(struct InterCodes_));
			for(int i = 0; i<arg_cnt; i++) {
				InterCodes ir = new_InterCodes(arg_list[i], NULL, NULL, ARG, -1);
				InterCodes curr = ir2;
				while(curr->next)
					curr = curr->next;
				curr->next = ir; ir->prev = curr;		
			}
			Operand f = new_Operand(exp->gchild[0], FUNCTION, -1, -1);
			InterCodes call_f = new_InterCodes(place, f, NULL, CALL);
			
			ir1->next = ir2->next; ir2->next->prev = ir1;
			InterCodes curr = ir1;
			while(curr->next)
				curr = curr->next;
			curr->next = call_f; call_f->prev = curr;
			free(ir2);
			//TODO()??????
			return ir1;
		case Exp_IdLpRp:
			char* name = exp->str;
			if(!strcmp(name, "read"))
				return new_InterCodes(place, NULL, NULL, READ);
			Operand function = new_Operand(exp);
			return new_InterCodes(place, function, NULL, CALL);
		case Exp_ExpLbExpRb:
			//TODO();
		case Exp_ExpDotId:
			//TODO();
		case Exp_Id:
			char* name = exp->str;
			Operand id = new_Operand(exp->gchild[0], VARIABLE, -1, 0);
			
			InterCodes ir = new_InterCodes(place, value, NULL, ASSIGN, -1);
			return ir;
		case Exp_Int:
			int val = exp->type_int;
			Operand value = new_Operand(exp, IMM_NUMBER, -1, 0);
			
			InterCodes ir = new_InterCodes(place, value, NULL, ASSIGN, -1);
			return ir;			
		case Exp_Float:
			float val = exp->type_float;
			Operand value = new_Operand(exp, IMM_NUMBER, -1, 1);
			
			InterCodes ir = new_InterCodes(place, value, NULL, ASSIGN, -1);
			return ir;
	}	
}
InterCodes translate_args(struct node* args, InterCodes* arg_list, int* arg_cnt)
{
	switch(args->rule) {
		case Args_ExpCommaArgs:
			Operand t1 = new_temp();
			InterCodes ir1 = translate_exp(args->gchild[0], t1);
			arg_list[*arg_cnt++] = t1;
			InterCodes ir2 = translate_args(args->gchild[2], arg_list, arg_cnt);
			
			InterCodes ir = concat(ir1, ir2);
			return ir1;
		case Args_Exp:
			Operand t1 = new_temp();
			InterCodes ir1 = translate_exp(args->gchild[0], t1);
			arg_list[*arg_cnt++] = t1;
			return ir1;
	}
}


