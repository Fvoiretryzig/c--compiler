#include "gen_obj.h"
#include <stdio.h>

Reg reg[32];
FILE* fp;
block BlkHead;
localList localHead;	//在函数的时候初始化
int stack_offset = 0;
int para_cnt = 0;

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
	localList->next = NULL; localList->offset = 0; localList->op = NULL;
	
	return;
}

/* d choose_reg(InterCodes ir)
{
	
}*/
Reg ensure(Operand x) {
	Reg result = NULL;
	int is_find = 0;
	localList curr = localHead;
	
	for(int i = 8; i<26; i++) {
		if(reg[i].op == x) {
			is_find = 1;
			result = reg[i];
			break;
		}
	}
	if(x->kind == IMM_NUMBER) {	//对立即数特判
		char tmp[32]; memset(tmp, 0, 32);
		if(is_find) {
			sprintf(tmp, "\tli "); print_reg(tmp, result); sprintf(tmp, " %d\n", x->u.value_int);
			fputs(tmp, fp);
		}
		else {
			result = allocate(x);
			sprintf(tmp, "\tli "); print_reg(tmp, result); sprintf(tmp, " %d\n", x->u.value_int);
			fputs(tmp, fp);
		}
	}
	if(!is_find) {	//立即数应该就不用放内存了8？
		localList curr_before = NULL;
		while(curr) {
			curr_before = curr;
			curr = curr->next;
			if(curr->op == x) 
				break;
		}
		if(!curr && (x->kind == TMP || x->kind == VARIABLE)) {	//临时变量和变量为了除法乘法跳转还有立即数
																//（其他应该不用吧）还未分配在栈上的位置
			stack_offset += 4;
			fputs("\taddi $sp, $sp, -4\n", fp);	//sp扩大4
			localList tmp_locallist = (localList)malloc(sizeof(localList_));
			tmp_locallist->offset = stack_offset;
			tmp_locallist->op = x;
			curr_before->next = tmp_locallist;
			curr = tmp_locallist;	//复用一下curr
			tmp_locallist->next = NULL;
		}
		result = allocate(x);
		if(curr->offset > 0) {	//在栈中有位置了
			//lw reg(x), offset($fp);
			char tmp[32];
			memset(tmp, 0, 32);
			sprintf(tmp, "\tlw "); print_reg(tmp, result); sprintf(tmp, ", -%d($fp)\n", curr->offset);
			fputs(tmp, fp);
		}
	}
	return result;
}
Reg allocate(Operand x)
{
	Reg result = NULL;
	int is_find = 0;
	for(int i = 8; i<26; i++) {
		if(!reg[i].is_used) {
			if(!is_find) {
				is_find = 1;
				result = reg[i];
				reg[i].op = x;
				reg[i].is_used = 1;
				break;
			}
		}
		else 
			reg[i].farthest_nouse++;
	}
	if(!result) {
		int reg_no = -1;
		int farthest = 0;
		for(int i = 8; i<26; i++) {
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
	Operand op = 0;
	curr = localHead;
	while(curr) {
		if(curr->op == r.op)
			break;
		curr = curr->next;
	}
	if(curr->offset > 0) {	//spill的时候不会还没在内存（栈）中，前面ensure要分配的
		char tmp[32];
		memset(tmp, 0, 32);
		sprintf(tmp, "sw "); print_reg(tmp, r); sprintf(", -%d($fp)\n", curr->offset);
		fputs(tmp, fp);
	}
}
void print_reg(char* dest, Reg r)
{
	switch(r.kind) {
		case zero: sprintf(dest, "$zero"); break;
		case at: sprintf(dest, "$at"); break;
		case v0: sprintf(dest, "$v0"); break;
		case v1: sprintf(dest, "$v1"); break;
		case a0: sprintf(dest, "$a0"); break;
		case a1: sprintf(dest, "$a1"); break;
		case a2: sprintf(dest, "$a2"); break;
		case a3: sprintf(dest, "$a3"); break;
		case t0: sprintf(dest, "$t0"); break;
		case t1: sprintf(dest, "$t1"); break;
		case t2: sprintf(dest, "$t2"); break;
		case t3: sprintf(dest, "$t3"); break;
		case t4: sprintf(dest, "$t4"); break;
		case t5: sprintf(dest, "$t5"); break;
		case t6: sprintf(dest, "$t6"); break;
		case t7: sprintf(dest, "$t7"); break;
		case s0: sprintf(dest, "$s0"); break;
		case s1: sprintf(dest, "$s1"); break;
		case s2: sprintf(dest, "$s2"); break;
		case s3: sprintf(dest, "$s3"); break;
		case s4: sprintf(dest, "$s4"); break;
		case s5: sprintf(dest, "$s5"); break;
		case s6: sprintf(dest, "$s6"); break;
		case s7: sprintf(dest, "$s7"); break;
		case k0: sprintf(dest, "$k0"); break;
		case k1: sprintf(dest, "$k1"); break;
		case gp: sprintf(dest, "$gp"); break;
		case sp: sprintf(dest, "$sp"); break;
		case fp: sprintf(dest, "$fp"); break;
		case ra: sprintf(dest, "$ra"); break;
	}
}
void choose_instr(InterCodes ir) {
	if(ir->kind == D_LABEL) {	//基本块开始，需要把寄存器都存回内存去吧(jump的跳转)
		char tmp[32];
		memset(tmp, 0, 32);
		sprintf(tmp, "label%d:\n", ir->u.label.x->u.label_no);
		fputs(tmp, fp);
		for(int i = 8; i<26; i++) {		//把里面有东西的寄存器全部存回去
			if(reg[i]->is_used) {
				spill(reg[i]);
				reg[i]->is_used = 0;
				reg[i]->op = NULL;
				reg[i]->farthest_nouse = 0;
			}
		}
		return;
	}
	else if(ir->kind == D_FUNCTION) {	//新的函数新的栈所有都清空，局部变量也是
		char tmp[32];
		memset(tmp, 0, 32);
		sprintf(tmp, "\n%s:\n", ir->u.function.f->u.f_name);
		fputs(tmp, fp);
		curr = localHead;
		while(curr) {		//全部释放完再重新分配，不知道释放得有没有问题……一直踩free的坑
			localHead = localHead->next;
			free(curr);
			curr = localHead;
		}
		localHead = (localList)malloc(sizeof(struct localList_));
		localHead->next = NULL; localHead->op = NULL; localHead->offset = 0;
		para_cnt = 0;
		// offset = 0;	是在call设置还是这里啊
		return;
	}
	else if(ir->kind == ASSIGN) {
		Operand left = ir->u.assign.x; Operand right = ir->u.assign.y;
		Reg left_r = choose_reg(ir);
		if(right->kind == IMM_NUMBER) {
			Reg reg_left = ensure(left);
			char tmp[32];
			memset(tmp, 0, 32);
			sprintf(tmp, "\tli "); print_reg(tmp, reg_left); sprintf(tmp, ", %d\n", right->u.value_int);
			fputs(tmp, fp);
		}
		else if(right->kind == TMP || right->kind == VARIABLE)  {
			Reg reg_left = ensure(left); Reg reg_rigt = ensure(right);
			char tmp[32];
			memset(tmp, 0, 32);
			sprintf(tmp, "\tmove "); print_reg(tmp, reg_left); sprintf(tmp, ", "); print_reg(tmp, reg_right); sprintf("\n");
			fputs(tmp, fp);
		}
	}
	else if(ir->kind == ADD) {
		Operand x = ir->u.arithmetic.x; Operand y = ir->u.arithmetic.y; Operand z = ir->u.arithmetic.z;
		if(z->kind == IMM_NUMBER) {
			Reg reg_x = ensure(x); Reg reg_y = ensure(y);
			int k = z->u.value_int;
			char tmp[32];
			memset(tmp, 0, 32);
			sprintf(tmp, "\taddi "); print_reg(tmp, reg_x); sprintf(tmp, ", "); print_reg(tmp, reg_x); sprintf(tmp, ", %d\n", k);
			fputs(tmp, fp);
		}
		else if(z->kind == TMP || z->kind == VARIABLE) {
			Reg reg_x = ensure(x); Reg reg_y = ensure(y); Reg reg_z = ensure(z);
			char tmp[32];
			memset(tmp, 0, 32);
			sprintf(tmp, "\add "); print_reg(tmp, reg_x); sprintf(tmp, ", "); print_reg(tmp, reg_y); sprintf(tmp, ", "); print_reg(tmp, reg_z); sprintf(tmp, "\n");
			fputs(tmp, fp);
		}
	}
	else if(ir->kind == SUB) {
		Operand x = ir->u.arithmetic.x; Operand y = ir->u.arithmetic.y; Operand z = ir->u.arithmetic.z;
		if(z->kind == IMM_NUMBER) {
			Reg reg_x = ensure(x); Reg reg_y = ensure(y);
			int k = z->u.value_int;
			char tmp[32];
			memset(tmp, 0, 32);
			sprintf(tmp, "\taddi "); print_reg(tmp, reg_x); sprintf(tmp, ", "); print_reg(tmp, reg_x); sprintf(tmp, ", -%d\n", k);
			fputs(tmp, fp);
		}
		else if(z->kind == TMP || z->kind == VARIABLE) {
			Reg reg_x = ensure(x); Reg reg_y = ensure(y); Reg reg_z = ensure(z);
			char tmp[32];
			memset(tmp, 0, 32);
			sprintf(tmp, "\tsub "); print_reg(tmp, reg_x); sprintf(tmp, ", "); print_reg(tmp, reg_y); sprintf(tmp, ", "); print_reg(tmp, reg_z); sprintf(tmp, "\n");
			fputs(tmp, fp);
		}
	}
	else if(ir->kind == MUL) {
		Operand x = ir->u.arithmetic.x; Operand y = ir->u.arithmetic.y; Operand z = ir->u.arithmetic.z;
		Reg reg_x = ensure(x); Reg reg_y = ensure(y); Reg reg_z = ensure(z);
		char tmp[32];
		memset(tmp, 0, 32);
		sprintf(tmp, "\tmul "); print_reg(tmp, reg_x); sprintf(tmp, ", "); print_reg(tmp, reg_y); sprintf(tmp, ", "); print_reg(tmp, reg_z); sprintf(tmp, "\n");
		fputs(tmp, fp);
	}
	else if(ir->kind == IR_DIV) {
		Operand x = ir->u.arithmetic.x; Operand y = ir->u.arithmetic.y; Operand z = ir->u.arithmetic.z;
		Reg reg_x = ensure(x); Reg reg_y = ensure(y); Reg reg_z = ensure(z);
		char tmp[32];
		memset(tmp, 0, 32);
		sprintf(tmp, "\tdiv "); print_reg(tmp, reg_y); sprintf(tmp, ", "); print_reg(tmp, reg_z); sprintf(tmp, "\n");
		fputs(tmp, fp);
		memset(tmp, 0, 32);
		sprintf(tmp, "\tmflo "); print_reg(tmp, reg_x); sprintf(tmp, "\n");
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
