#include "ir.h"
#include <stdlib.h>

#define IR_DEBUG
InterCodes IRhead;
static int lable_cnt;
static int var_cnt;
static int tmp_cnt;
Operand imm_num0;
Operand imm_num1;

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
void init_operand()
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
	
	return;
}
void print_ir(InterCodes ir_list) 
{
	//TODO();
}
Operand new_Operand(struct node* gnode, int kind, float n, int if_float)
{
	Operand op = (Operand)malloc(sizeof(struct Operand_));
	switch(kind) {
		case VARIABLE:
			op->kind = VARIABLE;
			op->u.val_no = var_cnt++;
			break;
		case CONSTANT
		case ADDRESS
		case LABEL
		case FUNCTION
		case TMP
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
		case ADDRESS_CONTENT
	}
	
	return op;
}
Operand new_temp()
{
	Operand temp = (Operand)malloc(sizeof(struct Operand_));
	temp->kind = TMP;
	temp->u.tmp_no = tmp_cnt++;
	return temp;
}
Operand new_label()
{
	Operand label = (Operand)malloc(sizeof(struct Operand_));
	label->kind = LABEL;
	label->u.label_no = label_cnt++;
	return label;
}
InterCodes new_InterCodes(Operand op1, Operand op2, Operand op3, int kind, int op)
{
	InterCodes ir = (InterCodes)malloc(sizeof(struct InterCodes_));
	switch(kind) {
		case D_LABEL
		case D_FUNCTION
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
		case ASSIGN_ADDR
		case ADDR_ASSIGNED
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
		case DEC
		case ARG
		case CALL
		case PARA
		case READ
		case WRITE
	}
	return ir;
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
			
			ir1->next = ir2_1; ir2_1->prev = ir1;
			ir2_1->next = ir2_2; ir2_2->prev = ir2_1;
			return ir1;
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
			
			ir0->next = ir1; ir1->prev = ir0;
			ir1->next = ir2_1; ir2_1->prev = ir1;
			ir2_1->next = ir2_2; ir2_2->prev = ir2_1;
			ir2_2->next = ir3; ir3->prev = ir2_2;
			return ir0;
		case Exp_ExpPlusExp:
			Operand t1 = new_temp();
			Operand t2 = new_temp();
			
			InterCodes ir1 = translate_exp(exp->gchild[0], t1);
			InterCodes ir2 = translate_exp(exp->gchild[2], t2);
			InterCodes ir3 = new_InterCodes(place, t1, t2, ADD, -1);
			
			ir1->next = ir2; ir2->prev = ir1;
			ir2->next = ir3; ir3->prev = ir2;
			return ir1;
		case Exp_ExpMinusExp:
			Operand t1 = new_temp();
			Operand t2 = new_temp();
			
			InterCodes ir1 = translate_exp(exp->gchild[0], t1);
			InterCodes ir2 = translate_exp(exp->gchild[2], t2);
			InterCodes ir3 = new_InterCodes(place, t1, t2, SUB, -1);
			
			ir1->next = ir2; ir2->prev = ir1;
			ir2->next = ir3; ir3->prev = ir2;
			return ir1;
		case Exp_ExpStarExp:
			Operand t1 = new_temp();
			Operand t2 = new_temp();
			
			InterCodes ir1 = translate_exp(exp->gchild[0], t1);
			InterCodes ir2 = translate_exp(exp->gchild[2], t2);
			InterCodes ir3 = new_InterCodes(place, t1, t2, MUL, -1);
			
			ir1->next = ir2; ir2->prev = ir1;
			ir2->next = ir3; ir3->prev = ir2;
			return ir1;
		case Exp_ExpDivExp:
			Operand t1 = new_temp();
			Operand t2 = new_temp();
			
			InterCodes ir1 = translate_exp(exp->gchild[0], t1);
			InterCodes ir2 = translate_exp(exp->gchild[2], t2);
			InterCodes ir3 = new_InterCodes(place, t1, t2, DIV, -1);
			
			ir1->next = ir2; ir2->prev = ir1;
			ir2->next = ir3; ir3->prev = ir2;
			return ir1;
		case Exp_LpExpRp
		case Exp_MinusExp:
			Operand t1 = new_temp();
			
			InterCodes ir1 = translate_exp(exp->gchild[2], t1);
			InterCodes ir2 = new_InterCodes(place, imm_num0, t1, -1);
			
			ir1->next = ir2; ir2->prev = ir1;
			return ir1;
		case Exp_IdLpArgsRp
		case Exp_IdLpRp
		case Exp_ExpLbExpRb
		case Exp_ExpDotId
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
		case Exp_Float
			float val = exp->type_float;
			Operand value = new_Operand(exp, IMM_NUMBER, -1, 1);
			
			InterCodes ir = new_InterCodes(place, value, NULL, ASSIGN, -1);
			return ir;
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
			InterCodes ir2 = new_InterCodes(t1, NULL, NULL, RET);
			
			ir1->next = ir2; ir2->prev = ir1;
			return ir1;
		case Stmt_IfLpExpRpStmt:
			Operand label1 = new_label();
			Operand label2 = new_label();
			
			InterCodes ir1 = translate_cond(stmt->gchild[2], label1, label2);
			InterCodes label1_code = new_InterCodes(label1, NULL, NULL, D_LABEL);
			InterCodes ir2 = translate_stmt(stmt->gchild[4]);
			InterCodes label2_code = new_InterCodes(label2, NULL, NULL, D_LABEL);
			
			ir1->next = label1_code; label1_code->prev = ir1;
			label1_code->next = ir2; ir2->prev = label1_code;
			ir2->next = label2_code; label2_code->prev = ir2;
			return ir1;
		case Stmt_IfLpExpRpStmtElseStmt:
			Operand label1 = new_label();
			Opearnd label2 = new_label();
			Operand label3 = new_label();
			
			InterCodes ir1 = translate_cond(stmt->gchild[2], label1, label2);
			InterCodes label1_code = new_InterCodes(label1, NULL, NULL, D_LABEL);
			InterCodes ir2 = translate_stmt(stmt->gchild[4]);
			InterCodes goto3_code = new_InterCodes(label3, NULL, NULL, JUMP);
			InterCodes label2_code = new_InterCodes(label2, NULL, NULL, D_LABEL);
			InterCodes ir3 = translate_stmt(stmt->gchild[6]);
			InterCOdes label3_code = new_InterCodes(label3, NULL, NULL, D_LABEL);
			
			ir1->next = label1_code; label1_code->prev = ir1;
			label1_code->next = ir2; ir2->prev = label1_code;
			ir2->next = goto3_code; goto3_code->prev = ir2;
			goto3_code->next = label2_code; label2_code->prev = goto3_code;
			label2_code->next = ir3; ir3->prev = label2_code;
			ir3->next = label3_code; label3_code->prev = ir3;
			return ir1;
		case Stmt_WhileLpExpRpStmt:
			Operand label1 = new_label();
			Operand label2 = new_label();
			Operand label3 = new_label();
			
			InterCodes label1_code = new_InterCodes(label1, NULL, NULL, D_LABEL);
			InterCodes ir1 = translate_cond(stmt->gchild[2], label2, label3);
			InterCodes label2_code = new_InterCodes(label2, NULL, NULL, D_LABEL);
			InterCodes ir2 = translate_stmt(stmt->gchild[4]);
			InterCodes goto1_code = new_InterCodes(label1, NULL, NULL, JUMP);
			InterCodes label3_code = new_InterCodes(label3, NULL, NULL, D_LABEL);
			
			label1_code->next = ir1; ir1->prev = label1_code;
			ir1->next = label2_code; label2_code->prev = ir1;
			label2_code->next = ir2; ir2->prev = label2_code;
			ir2->next = goto1_code; goto1_code->prev = ir2;
			goto1_code->next = label3_code; label3_code->prev = goto1_code;
			
			return ir1;
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
			
			ir1->next = label_code; label_code->prev = ir1;
			label_code->next = ir2; ir2->prev = label_code;
			return ir1;
		case Exp_ExpOrExp:
			Operand label1 = new_label();
			
			InterCodes ir1 = translate_cond(exp->gchild[0], label_true, label1);
			InterCodes label_code = new_InterCodes(label1, NULL, NULL, D_LABEL, -1);
			InterCodes ir2 = translate_cond(exp->gchild[1], label_true, label_false);
			
			ir1->next = label_code; label_code->prev = ir1;
			label_code->next = ir2; ir2->prev = label_code;
			return ir1;
		case Exp_ExpRelopExp:
			Operand	t1 = new_temp();
			Operand t2 = new_temp();
			
			InterCodes ir1 = translate_exp(exp->gchild[0], t1);
			InterCodes ir2 = translate_exp(exp->gchild[2], t2);
			int op = get_relop(exp->gchild[1]);
			InterCodes ir3 = new_InterCodes(t1, t2, label_true, IF_JUMP, op);
			InterCodes ir4 = new_InterCodes(t1, NULL, NULL, JUMP, -1);
			
			ir1->next = ir2; ir2->prev = ir1;
			ir2->next = ir3; ir3->prev = ir2;
			ir3->next = ir4; ir4->prev = ir3;
			return ir1;
		default: 
			t1 = new_temp();
			
			InterCodes ir1 = translate_exp(exp, t1);
			int op = 5;
			InterCodes ir2 = new_InterCodes(t1, imm_num0, label_true, IF_JUMP, op);
			InterCodes label_code = new_InterCodes(label_false, D_label);
			
			ir1->next = ir2; ir2->prev = ir1;
			ir2->next = label_code; label_code->prev = ir2;
			return ir1;
	}
}
