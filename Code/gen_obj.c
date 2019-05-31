#include "gen_obj.h"
#include <stdio.h>

Register reg[32];
FILE* fp;
block BlkHead;

void init_gen()	//read write函数还没有写
{
	fp = fopen("a.s", w+);
	for(int i = 0; i<32; i++) {
		reg.kind = i;
		reg.is_used = 0;
		reg.op = NULL;
	}
	BlkHead = (block)malloc(sizeof(struct block_));
	BlkHead->start = -1; BlkHead->end = -1; BlkHead->next = NULL;
	
	return;
}
void print_reg(Register r)
{
	switch(r->kind) {
		case zero: fprintf(fp, "$zero"); break;
		case at: 
		case v0: 
		case v1:
		case a0:
		case a1:
		case a2: 
		case a3:
		case t0:
		case t1:
		case t2:
		case t3:
		case t4:
		case t5:
		case t6:
		case t7: 
		case s0:
		case s1:
		case s2:
		case s3:
		case s4:
		case s5:
		case s6:
		case s7:
		case k0:
		case k1:
		case gp:
		case sp: 
		case fp: 
		case ra:
	}
}
void choose_instr(InterCodes ir) {

	if(ir->kind == D_LABEL) {
		fprintf(fp, "label%d:\n", ir->u.label.x->u.label_no);
		return;
	}
	else if(ir->kind == D_FUNCTION) {
		fprintf(fp, "%s:\n", ir->u.function.f->u.f_name);
		return;
	}
	else if(ir->kind == ASSIGN) {
		Operand left = ir->u.assign.x; Operand right = ir->u.assign.y;
		
	}
	else if(ir->kind == ADD) {
	
	}
	else if(ir->kind == SUB) {
	
	}
	else if(ir->kind == MUL) {
	
	}
	else if(ir->kind == IR_DIV) {
	
	}
	else if(ir->kind == ASSIGN_ADDR) {
	
	}
	else if(ir->kind == ASSIGN_CONTENT) {
	
	}
	else if(ir->kind == CONTENT_ASSIGNED) {
	
	}
	else if(ir->kind == JUMP) {
	
	}
	else if(ir->kind == IF_JUMP) {
	
	}
	else if(ir->kind == RET) {
	
	}
	else if(ir->kind == DEC) {
	
	}
	else if(ir->kind == ARG) {
	
	}
	else if(ir->kind == CALL) {
	
	}
	else if(ir->kind == PARA) {
	
	}
	
	return;
}
void div_block();
void choose_reg(InterCodes ir);
Register ensure(Operand x);
Register allocate(Operand x);
void spill(Register r);
