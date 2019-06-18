#include "gen_obj.h"
#include <stdio.h>

Reg reg[32];
FILE* fp;
block BlkHead;
localList localHead;	//在函数的时候初始化
int stack_offset = 0;

void init_gen()	//read write函数还没有写
{
	fp = fopen("a.s", w+);
	for(int i = 0; i<32; i++) {
		reg.kind = i;
		reg.is_used = 0;
		reg.op = NULL;
		reg.farthest_nouse = 0;
	}
	
	localList = (localList)malloc(sizeof(struct localList_));
	localList->next = NULL; localList->offset = 0;
	
	return;
}

/* d choose_reg(InterCodes ir)
{
	
}*/
Reg ensure(Operand x) {
	Reg result = NULL;
	int is_find = 0;
	localList curr = localHead;
	
	for(int i = 8; i<24; i++) {
		if(reg[i]->op == x) {
			is_find = 1;
			result = reg[i];
			break;
		}
	}
	if(!is_find) {
		localList curr_before = NULL;
		while(curr) {
			curr_before = curr;
			curr = curr->next;
			if(x->kind == IMM_NUMBER && curr->op->kind == IMM_NUMBER) {	//对立即数特判，立即数相同的存一次就好了
				if(x->u.value_int == curr->op->u.value_int)
					break;
			}
			if(curr->op == x) 
				break;
		}
		if(!curr && (x->kind == TMP || x->kind == VARIABLE || x->kind == IMM_NUMBER)) {	//临时变量和变量为了除法乘法跳转还有立即数
																						//（其他应该不用吧）还未分配在栈上的位置
			offset += 4;
			localList tmp = (localList)malloc(sizeof(localList_));
			tmp->offset = offset;
			tmp->op = x;
			curr_before->next = tmp;
			curr = tmp;	//复用一下curr
			tmp->next = NULL;
		}
		result = allocate(x);
		if(curr->offset > 0) {	//在栈中有位置了
			//lw reg(x), offset($fp);
			fprintf(fp, "lw "); print_reg(result); fprintf(fp, ", %d($fp)\n", curr->offset);
		}
	}
	return result;
}
Reg allocate(Operand x)
{
	Reg result = NULL;
	int is_find = 0;
	for(int i = 8; i<24; i++) {
		if(!reg[i].is_used) {
			if(!is_find) {
				is_find = 1;
				result = reg[i];
				reg[i].op = x;
				reg[i],is_used = 1;
				break;
			}
		}
		else 
			reg[i].farthest_nouse++;
	}
	if(!result) {
		int reg_no = -1;
		int farthest = 0;
		for(int i = 8; i<24; i++) {
			if(farthest < reg[i].farthest_nouse) {
				farthest = reg[i].farthest_nouse;
				reg_no = i;
			}
		}
		spill(reg[reg_no]);
		result = reg[reg_no];
		reg[reg_no].op = x;
		reg[reg_no].farthest_nouse = 0;
	}
	return result;
}
void spill(Reg r)
{
	Operand op = r.op;
	if(x->offset > 0) {	//spill的时候不会还没在内存（栈）中，前面ensure要分配的
		fprintf(fp, "sw ");
		print_reg(r);
		fprintf(fp, ", %d($fp)\n", op->offset);
	}
}
void print_reg(Reg r)
{
	switch(r->kind) {
		case zero: fprintf(fp, "$zero"); break;
		case at: fprintf(fp, "$at"); break;
		case v0: fprintf(fp, "$v0"); break;
		case v1: fprintf(fp, "$v1"); break;
		case a0: fprintf(fp, "$a0"); break;
		case a1: fprintf(fp, "$a1"); break;
		case a2: fprintf(fp, "$a2"); break;
		case a3: fprintf(fp, "$a3"); break;
		case t0: fprintf(fp, "$t0"); break;
		case t1: fprintf(fp, "$t1"); break;
		case t2: fprintf(fp, "$t2"); break;
		case t3: fprintf(fp, "$t3"); break;
		case t4: fprintf(fp, "$t4"); break;
		case t5: fprintf(fp, "$t5"); break;
		case t6: fprintf(fp, "$t6"); break;
		case t7: fprintf(fp, "$t7"); break;
		case s0: fprintf(fp, "$s0"); break;
		case s1: fprintf(fp, "$s1"); break;
		case s2: fprintf(fp, "$s2"); break;
		case s3: fprintf(fp, "$s3"); break;
		case s4: fprintf(fp, "$s4"); break;
		case s5: fprintf(fp, "$s5"); break;
		case s6: fprintf(fp, "$s6"); break;
		case s7: fprintf(fp, "$s7"); break;
		case k0: fprintf(fp, "$k0"); break;
		case k1: fprintf(fp, "$k1"); break;
		case gp: fprintf(fp, "$gp"); break;
		case sp: fprintf(fp, "$sp"); break;
		case fp: fprintf(fp, "$fp"); break;
		case ra: fprintf(fp, "$ra"); break;
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
		Reg left_r = choose_reg(ir);
		if(right->kind == IMM_NUMBER)  {
			
		}
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
