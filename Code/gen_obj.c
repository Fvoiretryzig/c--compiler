#include "gen_obj.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Reg reg[32];
FILE* objFile;
localList localHead[210];	//在函数的时候初始化,最多支持200个函数嵌套
int func_in = -1;	//记录当前是第几个局部变量
int stack_offset = 0;
int para_cnt = 0;
int stack_size = 1024;
InterCodes curr_ir;
Operand argList[100];
extern InterCodes IRhead;

void init_gen()	//read write函数还没有写
{
	objFile = fopen("a.s", "w+");
	for(int i = 0; i<32; i++) {
		reg[i].kind = i;
		reg[i].is_used = 0;
		reg[i].op = NULL;
		reg[i].farthest_nouse = 0;
	}
	
	fputs(".data\n", objFile);
	fputs("_prompt: .asciiz \"Enter an interger:\"\n", objFile);
	fputs("_ret: .asciiz \"\\n\"\n", objFile);
	fputs(".globl main\n", objFile);
	fputs(".text\n", objFile);
	
	fputs("read:\n", objFile);
	fputs("\tli $v0, 4\n", objFile);
	fputs("\tla $a0, _prompt\n", objFile);
	fputs("\tsyscall\n", objFile);
	fputs("\tli $v0, 5\n", objFile);
	fputs("\tsyscall\n", objFile);
	fputs("\tjr $ra\n", objFile);
	fputs("\n\n", objFile);
	fputs("write:\n", objFile);
	fputs("\tli $v0, 1", objFile);
	fputs("\tsyscall\n", objFile);
	fputs("\tli $v0, 4", objFile);
	fputs("\tla $a0, _ret\n", objFile);
	fputs("\tsyscall\n", objFile);
	fputs("\tmove $v0, $0\n", objFile);
	fputs("\tjr $ra\n", objFile);
	
	return;
}
void gen_obj()
{
	curr_ir = IRhead;
	while(curr_ir->next) {
		curr_ir = curr_ir->next;
		choose_instr(curr_ir);
	}
}
/*把a0 a1 a2 a3要加到局部变量判断里面去*/
Reg ensure(Operand x)
{
	Reg result;
	result.kind = -1; result.is_used = 0; result.farthest_nouse = 0;result.op = NULL;
	int is_find = 0;
	localList curr = localHead[func_in];
	
	for(int i = 8; i<26; i++) {
		if(reg[i].op == x) {
			is_find = 1;
			result = reg[i];
			break;
		}
	}
	for(int i = 4; i<8; i++) {	//给参数用的
		if(reg[i].op == x) 
			return reg[i];
	}
	if(x->kind == IMM_NUMBER) {	//对立即数特判
		char tmp[32]; memset(tmp, 0, 32);
		if(is_find) {
			sprintf(tmp, "\tli "); print_reg(tmp, result); sprintf(tmp, " %d\n", x->u.value_int);
			fputs(tmp, objFile);
		}
		else {
			result = allocate(x);
			sprintf(tmp, "\tli "); print_reg(tmp, result); sprintf(tmp, " %d\n", x->u.value_int);
			fputs(tmp, objFile);
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
			fputs("\tsubu $sp, $sp, 4\n", objFile);	//sp扩大4
			localList tmp_locallist = (localList)malloc(sizeof(struct localList_));
			tmp_locallist->offset = stack_offset;
			tmp_locallist->op = x;
			tmp_locallist->next = NULL;
			curr_before->next = tmp_locallist;
			curr = tmp_locallist;	//复用一下curr
		}
		else if(!curr) {
			printf("error when find op in ensure\n");
			return result;
		}
		result = allocate(x);
		if(x->kind == ADDRESS) {	//对地址特殊处理，存地址的位置
			int ofs = curr->offset;
			char tmp[32]; memset(tmp, 0, 32);
			sprintf(tmp, "\tsubu $v1, $fp, %d\n", ofs);
			fputs(tmp, objFile);
			memset(tmp, 0, 32);
			sprintf(tmp, "\tmove "); print_reg(tmp, result); sprintf(tmp, ", $v1\n");
			fputs(tmp, objFile);
		}
		else if(curr->offset > 0) {	//在栈中有位置了
			char tmp[32];
			memset(tmp, 0, 32);
			sprintf(tmp, "\tlw "); print_reg(tmp, result); sprintf(tmp, ", -%d($fp)\n", curr->offset);
			fputs(tmp, objFile);
		}
	}
	return result;
}
Reg allocate(Operand x)
{
	Reg result;
	result.kind = -1; result.is_used = 0; result.farthest_nouse = 0;result.op = NULL;
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
	if(result.kind == -1) {
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
	localList curr = localHead[func_in];
	while(curr) {
		if(curr->op == r.op)
			break;
		curr = curr->next;
	}
	if(curr->offset > 0) {	//spill的时候不会还没在内存（栈）中，前面ensure要分配的
		char tmp[32];
		memset(tmp, 0, 32);
		sprintf(tmp, "sw "); print_reg(tmp, r); sprintf(tmp, ", -%d($fp)\n", curr->offset);
		fputs(tmp, objFile);
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
	printf("in choose_instr\n");
	if(ir->code.kind == D_LABEL) {	//基本块开始，需要把寄存器都存回内存去吧(jump的跳转)
		char tmp[32];
		memset(tmp, 0, 32);
		sprintf(tmp, "label%d:\n", ir->code.u.label.x->u.label_no);
		fputs(tmp, objFile);
		for(int i = 8; i<26; i++) {		//把里面有东西的寄存器全部存回去
			if(reg[i].is_used) {
				spill(reg[i]);
				reg[i].is_used = 0;
				reg[i].op = NULL;
				reg[i].farthest_nouse = 0;
			}
		}
		return;
	}
	else if(ir->code.kind == ASSIGN) {
		Operand left = ir->code.u.assign.x; Operand right = ir->code.u.assign.y;
		if(right->kind == IMM_NUMBER) {
			Reg reg_left = ensure(left);
			char tmp[32];
			memset(tmp, 0, 32);
			sprintf(tmp, "\tli "); print_reg(tmp, reg_left); sprintf(tmp, ", %d\n", right->u.value_int);
			fputs(tmp, objFile);
		}
		else if(right->kind == TMP || right->kind == VARIABLE)  {
			Reg reg_left = ensure(left); Reg reg_right = ensure(right);
			char tmp[32];
			memset(tmp, 0, 32);
			sprintf(tmp, "\tmove "); print_reg(tmp, reg_left); sprintf(tmp, ", "); print_reg(tmp, reg_right); sprintf(tmp, "\n");
			fputs(tmp, objFile);
		}
	}
	else if(ir->code.kind == ADD) {
		Operand x = ir->code.u.arithmetic.x; Operand y = ir->code.u.arithmetic.y; Operand z = ir->code.u.arithmetic.z;
		if(z->kind == IMM_NUMBER) {
			Reg reg_x = ensure(x); Reg reg_y = ensure(y);
			int k = z->u.value_int;
			char tmp[32];
			memset(tmp, 0, 32);
			sprintf(tmp, "\taddi "); print_reg(tmp, reg_x); sprintf(tmp, ", "); print_reg(tmp, reg_x); sprintf(tmp, ", %d\n", k);
			fputs(tmp, objFile);
		}
		else if(z->kind == TMP || z->kind == VARIABLE) {
			Reg reg_x = ensure(x); Reg reg_y = ensure(y); Reg reg_z = ensure(z);
			char tmp[32];
			memset(tmp, 0, 32);
			sprintf(tmp, "\add "); print_reg(tmp, reg_x); sprintf(tmp, ", "); print_reg(tmp, reg_y); sprintf(tmp, ", "); print_reg(tmp, reg_z); sprintf(tmp, "\n");
			fputs(tmp, objFile);
		}
	}
	else if(ir->code.kind == SUB) {
		Operand x = ir->code.u.arithmetic.x; Operand y = ir->code.u.arithmetic.y; Operand z = ir->code.u.arithmetic.z;
		if(z->kind == IMM_NUMBER) {
			Reg reg_x = ensure(x); Reg reg_y = ensure(y);
			int k = z->u.value_int;
			char tmp[32];
			memset(tmp, 0, 32);
			sprintf(tmp, "\taddi "); print_reg(tmp, reg_x); sprintf(tmp, ", "); print_reg(tmp, reg_x); sprintf(tmp, ", -%d\n", k);
			fputs(tmp, objFile);
		}
		else if(z->kind == TMP || z->kind == VARIABLE) {
			Reg reg_x = ensure(x); Reg reg_y = ensure(y); Reg reg_z = ensure(z);
			char tmp[32];
			memset(tmp, 0, 32);
			sprintf(tmp, "\tsub "); print_reg(tmp, reg_x); sprintf(tmp, ", "); print_reg(tmp, reg_y); sprintf(tmp, ", "); print_reg(tmp, reg_z); sprintf(tmp, "\n");
			fputs(tmp, objFile);
		}
	}
	else if(ir->code.kind == MUL) {
		Operand x = ir->code.u.arithmetic.x; Operand y = ir->code.u.arithmetic.y; Operand z = ir->code.u.arithmetic.z;
		Reg reg_x = ensure(x); Reg reg_y = ensure(y); Reg reg_z = ensure(z);
		char tmp[32];
		memset(tmp, 0, 32);
		sprintf(tmp, "\tmul "); print_reg(tmp, reg_x); sprintf(tmp, ", "); print_reg(tmp, reg_y); sprintf(tmp, ", "); print_reg(tmp, reg_z); sprintf(tmp, "\n");
		fputs(tmp, objFile);
	}
	else if(ir->code.kind == IR_DIV) {
		Operand x = ir->code.u.arithmetic.x; Operand y = ir->code.u.arithmetic.y; Operand z = ir->code.u.arithmetic.z;
		Reg reg_x = ensure(x); Reg reg_y = ensure(y); Reg reg_z = ensure(z);
		char tmp[32];
		memset(tmp, 0, 32);
		sprintf(tmp, "\tdiv "); print_reg(tmp, reg_y); sprintf(tmp, ", "); print_reg(tmp, reg_z); sprintf(tmp, "\n");
		fputs(tmp, objFile);
		memset(tmp, 0, 32);
		sprintf(tmp, "\tmflo "); print_reg(tmp, reg_x); sprintf(tmp, "\n");
		fputs(tmp, objFile);
	}
	else if(ir->code.kind == JUMP) {	//代码块的结束，下一个指令就是新的开始了
		Operand label = ir->code.u.jump.x;
		if(!label) {
			printf("ERROR when jump!!!!\n");
			return;
		}
		char tmp[32]; memset(tmp, 0, 32);
		sprintf(tmp, "\tj label%d\n", label->u.label_no);
		fputs(tmp, objFile);
		for(int i = 8; i<26; i++) {		//把里面有东西的寄存器全部存回去
			if(reg[i].is_used) {
				spill(reg[i]);
				reg[i].is_used = 0;
				reg[i].op = NULL;
				reg[i].farthest_nouse = 0;
			}
		}
	}
	else if(ir->code.kind == IF_JUMP) { //代码块的结束，下一个指令就是新的开始了
		Operand x = ir->code.u.if_jump.x; Operand y = ir->code.u.if_jump.y;
		Operand label = ir->code.u.if_jump.z;
		int op = ir->code.u.if_jump.op;
		/*case 0:	printf(" > "); break;
			case 1: printf(" < "); break;
			case 2: printf(" >= "); break;
			case 3: printf(" <= "); break;
			case 4: printf(" == "); break;
			case 5: printf(" != "); break;*/
		Reg reg_x = ensure(x); Reg reg_y = ensure(y);
		char tmp[32]; memset(tmp, 0, 32);
		if(op == 0) { 
			sprintf(tmp, "\tbeq ");
			fputs(tmp, objFile);
		}
		else if(op == 1) {
			sprintf(tmp, "\tbne ");
			fputs(tmp, objFile);
		}
		else if(op == 2) {
			sprintf(tmp, "\tbgt ");
			fputs(tmp, objFile);
		}
		else if(op == 3) {
			sprintf(tmp, "\tblt ");
			fputs(tmp, objFile);
		}
		else if(op == 4) {
			sprintf(tmp, "\tbge ");
			fputs(tmp, objFile);
		}
		else if(op == 5) {
			sprintf(tmp, "\tble ");
			fputs(tmp, objFile);
		}
		print_reg(tmp, reg_x); sprintf(tmp, ", "); print_reg(tmp, reg_y); sprintf(tmp, ", label%d\n", label->u.label_no); 
		fputs(tmp, objFile);
		for(int i = 8; i<26; i++) {		//把里面有东西的寄存器全部存回去
			if(reg[i].is_used) {
				spill(reg[i]);
				reg[i].is_used = 0;
				reg[i].op = NULL;
				reg[i].farthest_nouse = 0;
			}
		}
	}
	else if(ir->code.kind == D_FUNCTION) {	//新的函数新的栈所有都清空，局部变量也是
		char tmp[32];
		memset(tmp, 0, 32);
		sprintf(tmp, "\n%s:\n", ir->code.u.function.f->u.f_name);
		fputs(tmp, objFile);
		func_in++;	//return的时候释放
		localHead[func_in] = (localList)malloc(sizeof(struct localList_));
		localHead[func_in]->next = NULL; localHead[func_in]->offset = 0; localHead[func_in]->op = NULL;
		stack_offset = 0;
		
		memset(tmp, 0, 32);
		sprintf(tmp, "\tsubu $sp, $sp, %d\n", stack_size);
		fputs(tmp, objFile);
		memset(tmp, 0, 32);
		sprintf(tmp, "\tsw $ra, %d($sp)\n", stack_size-4);
		fputs(tmp, objFile);
		memset(tmp, 0, 32);
		sprintf(tmp, "\tsw $fp, %d($sp)\n", stack_size-8);
		fputs(tmp, objFile);
		memset(tmp, 0, 32);
		sprintf(tmp, "\taddi $fp, $sp, %d\n", stack_size);
		fputs(tmp, objFile);
		//======================lw para========================
		//curr_ir = ir->next;
		for(int i = 0; i<para_cnt-4; i++) {
			Operand x = curr_ir->code.u.para.x;
			Reg tmp_reg = ensure(x);
			memset(tmp, 0, 32);
			sprintf(tmp, "lw "); print_reg(tmp, tmp_reg); sprintf(tmp, ", %d($fp)", 4*(para_cnt-i-5)); //和讲义上反的，好奇怪啊讲义上的，arg和para是反的啊
			fputs(tmp, objFile);
			curr_ir = curr_ir->next;
		}
		//对剩下的处理a0, a1, a2, a3
		for(int i = 0; i<4; i++) {
			reg[4+i].op = curr_ir->code.u.para.x;
			curr_ir = curr_ir->next;
		}
		curr_ir = curr_ir->prev;	//回退一位，免得上面出错
		stack_offset += 8;
		/*其他寄存器有必要保存吗？*/
		//剩下的给param做吧
		
		return;
	}
	else if(ir->code.kind == RET) {
		Operand x = ir->code.u.ret.x;
		char tmp[32]; memset(tmp, 0, 32);
		
		if(x->kind == IMM_NUMBER) {
			sprintf(tmp, "\tmove $v0, %d\n", x->u.value_int);
			fputs(tmp, objFile);
		}
		else {
			Reg reg_x = ensure(x);		
			sprintf(tmp, "\tmove $v0, "); print_reg(tmp, reg_x); sprintf(tmp, "\n");
			fputs(tmp, objFile);
		}
		
		localList curr = localHead[func_in];
		while(curr) {
			localHead[func_in] = localHead[func_in]->next;
			free(curr);
			curr = localHead[func_in];
		}
		func_in--;
		memset(tmp, 0, 32);
		sprintf(tmp, "\tlw $ra, %d($sp)\n", stack_size-4);
		fputs(tmp, objFile);
		memset(tmp, 0, 32);
		sprintf(tmp, "\tlw $fp, %d($sp)\n", stack_size-8);
		fputs(tmp, objFile);
		memset(tmp, 0, 32);
		sprintf(tmp, "\taddi $sp, $sp, %d\n", stack_size);
		fputs(tmp, objFile);
		memset(tmp, 0, 32);
		sprintf(tmp, "\tjr $ra\n");
		fputs(tmp, objFile);	
		
	}
	else if(ir->code.kind == CALL) {
		Operand x = ir->code.u.call.x; Operand f = ir->code.u.call.f;

		int t_offset[10];
		memset(t_offset, -1, sizeof(t_offset));
		//-------------------------保存活跃变量, 我用fp寻址应该不会影响吧！！---------------------------//
		for(int i = 8; i<16; i++) {		//把里面有东西的寄存器全部存回去
			if(reg[i].is_used) {
				Operand op = reg[i].op;
				localList curr = localHead[func_in];
				while(curr) {
					if(curr->op == op) {
						t_offset[i] = curr->offset;
						break;
					}
				}
				spill(reg[i]);
				reg[i].is_used = 0;
				reg[i].op = NULL;
				reg[i].farthest_nouse = 0;
			}
		}
		if(reg[24].is_used) {
			Operand op = reg[24].op;
			localList curr = localHead[func_in];
			while(curr) {
				if(curr->op == op) {
					t_offset[8] = curr->offset;
					break;
				}
			}
			spill(reg[24]);
			reg[24].is_used = 0; reg[24].op = NULL; reg[24].farthest_nouse = 0;
		}
		if(reg[25].is_used) {
			Operand op = reg[25].op;
			localList curr = localHead[func_in];
			while(curr) {
				if(curr->op == op) {
					t_offset[9] = curr->offset;
					break;
				}
			}
			spill(reg[25]);
			reg[25].is_used = 0; reg[25].op = NULL; reg[25].farthest_nouse = 0;
		}
		//-------------------------------传参------------------------------//
		char tmp[32]; memset(tmp, 0, 32);
		for(int i = 0; i<para_cnt && i<4; i++) {
			Reg tmp_reg = ensure(argList[i]);
			sprintf(tmp, "\tmove $a%d, ", i); print_reg(tmp, tmp_reg); sprintf(tmp, "\n");
			//把a0 a1 a2 a3要加到局部变量判断里面去
			fputs(tmp, objFile);
			memset(tmp, 0, 32);
		}
		if(para_cnt > 4) {
			if(4*(para_cnt-5) != 0) {
				sprintf(tmp, "\tsubu $sp, $sp, %d\n", 4*(para_cnt-5));
				fputs(tmp, objFile);
			}
			memset(tmp, 0, 32);
			for(int i = 4; i<para_cnt; i++) {
				Reg tmp_reg = ensure(argList[i]);
				sprintf(tmp, "\tsw "); print_reg(tmp, tmp_reg); sprintf(tmp, ", %d($sp)\n", 4*(para_cnt-5));
				fputs(tmp, objFile);
			}
		}
		
		Reg reg_x = ensure(x);
		sprintf(tmp, "\tjal %s\n", f->u.f_name);
		fputs(tmp, objFile);
		memset(tmp, 0, 32);
		sprintf(tmp, "\tmove "); print_reg(tmp, reg_x); sprintf(tmp, ", $v0\n");
		fputs(tmp, objFile);
		
		if(para_cnt > 4) {//应该没判断错吧
			memset(tmp, 0, 32);
			sprintf(tmp, "\taddi $sp, $sp, %d\n", 4*(para_cnt-5));
			fputs(tmp, objFile);
		}
		for(int i = 0; i<10; i++) {
			if(t_offset[i] != -1) {
				memset(tmp, 0, 32);
				sprintf(tmp, "\tlw t%d, -%d($fp)\n", i, t_offset[i]);
				fputs(tmp, objFile);
			}
		}
		for(int i = 0; i<para_cnt; i++) {
			argList[i] = NULL;
		}
		para_cnt = 0;
	}
	else if(ir->code.kind == ARG) {
		argList[para_cnt++] = ir->code.u.arg.x;
	}
	else if(ir->code.kind == PARA) {
		/*好像放在func也可以*/
	}
	else if(ir->code.kind == ASSIGN_ADDR) {
		//x=&y
		Operand x = ir->code.u.assign_address.x; Operand y = ir->code.u.assign_address.y;
		Reg reg_x = ensure(x); Reg reg_y = ensure(y);
		
		char tmp[32]; memset(tmp, 0, 32);
		sprintf(tmp, "\tmove "); print_reg(tmp, reg_x); sprintf(tmp, "\t, "); print_reg(tmp, reg_y); sprintf(tmp, "\n");
		fputs(tmp, objFile);
	}
	else if(ir->code.kind == ASSIGN_CONTENT) {
		//x=*y,不记得这两边的变量是什么了，先暂时默认是tmp直接分配寄存器吧。。。
		Operand x = ir->code.u.assign_content.x; Operand y = ir->code.u.assign_content.y;
		Reg reg_x = ensure(x); Reg reg_y = ensure(y);
		
		char tmp[32]; memset(tmp, 0, 32);
		sprintf(tmp, "\tlw "); print_reg(tmp, reg_x); sprintf(tmp, ", 0("); print_reg(tmp, reg_y); sprintf(tmp, ")\n");
		fputs(tmp, objFile);
		//数组先不写
	}
	else if(ir->code.kind == CONTENT_ASSIGNED) {
		//也不知道对不对，好像前面就不支持数组在左侧
		Operand x = ir->code.u.assign_content.x; Operand y = ir->code.u.assign_content.y;
		Reg reg_x = ensure(x); Reg reg_y = ensure(y);
		
		char tmp[32]; memset(tmp, 0, 32);
		sprintf(tmp, "\tsw "); print_reg(tmp, reg_y); sprintf(tmp, ", 0("); print_reg(tmp, reg_x); sprintf(tmp, ")\n");
		fputs(tmp, objFile);
	}
	else if(ir->code.kind == DEC) {
		Operand x = ir->code.u.dec.x;
		int size = ir->code.u.dec.size;
		
		stack_offset -= size;	//应该存一个变量就好了吧
		localList curr = localHead[func_in];
		while(curr->next)
			curr = curr->next;
		localList tmp_locallist = (localList)malloc(sizeof(struct localList_));
		tmp_locallist->offset = stack_offset;
		tmp_locallist->op = x;
		tmp_locallist->next = NULL;
		curr->next = tmp_locallist;
	}
	else if(ir->code.kind == READ) {
		Operand x = ir->code.u.read.x;
		Reg reg_x = ensure(x);
		
		char tmp[32]; memset(tmp, 0, 32);
		stack_offset -= 4;
		sprintf(tmp, "\tsw $ra, -%d($fp)\n", stack_offset);
		fputs(tmp, objFile);
		memset(tmp, 0, 32);
		sprintf(tmp, "\tjal read\n");
		fputs(tmp, objFile);
		memset(tmp, 0, 32);
		sprintf(tmp, "\tlw $ra, -%d($fp)\n", stack_offset);
		fputs(tmp, objFile);
		stack_offset +=4;
		fputs(tmp, objFile);
		memset(tmp, 0, 32);
		sprintf(tmp, "\tmove "); print_reg(tmp, reg_x); sprintf(tmp, ", $v0\n");
		fputs(tmp, objFile);
	}
	else if(ir->code.kind == WRITE) {
		Operand x = ir->code.u.write.x;
		Reg reg_x = ensure(x);
		
		char tmp[32]; memset(tmp, 0, 32);
		stack_offset -= 4;
		sprintf(tmp, "\tsw $ra, -%d($fp)\n", stack_offset);
		fputs(tmp, objFile);
		memset(tmp, 0, 32);
		sprintf(tmp, "\tmove $a0, "); print_reg(tmp, reg_x); sprintf(tmp, "\n");
		fputs(tmp, objFile);
		fputs("\tjal write\n", objFile);
		memset(tmp, 0, 32);
		sprintf(tmp, "\tlw $ra, -%d($fp)\n", stack_offset);
		memset(tmp, 0, 32);
		
	}
	return;
}
