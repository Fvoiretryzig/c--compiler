#include "gen_obj.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define GEN_DEBUG

Reg reg[32];
FILE* objFile;
localList localHead[210];	//在函数的时候初始化,最多支持200个函数嵌套
int func_in = -1;	//记录当前是第几个局部变量
int stack_offset = 0;
int arg_cnt = 0;
int para_cnt = 0;
int stack_size = 2048;
InterCodes curr_ir;
Operand argList[100];
extern InterCodes irlist;
extern char filename[100];
int is_main;

void init_gen()	//read write函数还没有写
{
	objFile = fopen(filename, "w+");
	for(int i = 0; i<32; i++) {
		reg[i].kind = i;
		reg[i].is_used = 0;
		reg[i].op = NULL;
		reg[i].farthest_nouse = 0;
		reg[i].in_mem = 0;
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
	fputs("\n", objFile);
	fputs("write:\n", objFile);
	fputs("\tli $v0, 1\n", objFile);
	fputs("\tsyscall\n", objFile);
	fputs("\tli $v0, 4\n", objFile);
	fputs("\tla $a0, _ret\n", objFile);
	fputs("\tsyscall\n", objFile);
	fputs("\tmove $v0, $0\n", objFile);
	fputs("\tjr $ra\n", objFile);
	return;
}
void gen_obj()
{
	printf("\n\n");
	curr_ir = irlist;
	while(curr_ir) {
		printf("ir kind: %d\n", curr_ir->code.kind);
		choose_instr(curr_ir);
		curr_ir = curr_ir->next;
		printf("\n");
	}
}

int op_equal(Operand a, Operand b)
{
	int ret = 0;
	if(a && b) {
		switch(a->kind) {
			case VARIABLE:	
				if(b->kind == VARIABLE && b->u.var_no == a->u.var_no)
					ret = 1;
				break;
			case ADDRESS:
				if(b->kind == ADDRESS && b->u.var_no == a->u.var_no)
					ret = 1;
				break;
			case TMP:
				if(b->kind == TMP && b->u.tmp_no == a->u.tmp_no)
					ret = 1;
				break;
		}
		return ret;
	}
}
localList if_inlocal(Operand x)
{
	localList curr = localHead[func_in];
	while(curr) {
		if(curr->op)
		//printf("curr op: kind: %d name:%s var_no: %d\n", curr->op->kind, curr->op->v_name, curr->op->u.var_no);
		if(op_equal(curr->op, x))
			return curr;
		curr = curr->next;
	}
	return NULL;
}
/*把a0 a1 a2 a3要加到局部变量判断里面去*/
int ensure(Operand x)
{
	Reg result;
	int pos = -1;
	result.kind = -1; result.is_used = 0; result.farthest_nouse = 0;result.op = NULL;
	int is_find = 0;
	localList curr = localHead[func_in];
	//printf("func_in: %d localHead: %p\n", func_in, localHead[func_in]);
	
	printf("in ensure x->kind: %d\n", x->kind);
	if(x->kind == IMM_NUMBER) {
		if(!x->u.value_int) {
			printf("ensure return zero\n");
			return 0;
		}
	}
	for(int i = 8; i<26; i++) {
		//if(x->kind == TMP && reg[i].op) {
		//	printf("tmppppppppppppppppppppppppppppp_no: %d %d\n", reg[i].op->u.tmp_no, x->u.tmp_no);
		//}
		if(op_equal(reg[i].op, x)) {
			is_find = 1;
			pos = i;
			printf("in ensure exist: %d\n", pos);
			reg[pos].in_mem = 0;
			return pos;
		}
	}
	for(int i = 4; i<8; i++) {	//给参数用的
		if(op_equal(reg[i].op, x)) {
			printf("arg reg: %d\n", i);
			reg[i].in_mem = 0;
			return i;
		}
	}
	if(x->kind == IMM_NUMBER) {	//对立即数特判
		if(pos == -1)
			pos = allocate(x);
		char tmp[32]; memset(tmp, 0, 32); 
		sprintf(tmp, "\tli "); print_reg(tmp, reg[pos]); sprintf(tmp, "%s, %d\n", tmp, x->u.value_int);
		fputs(tmp, objFile);
		printf("in ensure imm: %d\n", pos);
		reg[pos].in_mem = 0;
		return pos;
	}
	
	if(!is_find) {	//立即数应该就不用放内存了8？
		localList curr_before = NULL;
		//printf("curr in !is_find: %p\n", curr);
		while(curr) {
			curr_before = curr;
			if(curr->op != NULL && op_equal(curr->op, x)) {
				break;
			}
			curr = curr->next; 
		}
		int alloc_mem = 0;
		if(!curr && (x->kind == TMP || x->kind == VARIABLE)) {	//临时变量和变量为了除法乘法跳转还有立即数
																//（其他应该不用吧）还未分配在栈上的位置
			stack_offset += 4;
			localList tmp_locallist = (localList)malloc(sizeof(struct localList_));
			tmp_locallist->offset = stack_offset;
			tmp_locallist->op = x;
			tmp_locallist->if_store = 0;
			tmp_locallist->next = NULL;
			curr_before->next = tmp_locallist;
			curr = tmp_locallist;	//复用一下curr
			alloc_mem = 1;
		}
		else if(!curr) {	//这里的情况还存在什么啊
			printf("xkind: %d error when find op in ensure\n", x->kind);
			return -1;
		}
		pos = allocate(x);
		if(x->kind == ADDRESS) {	//对地址特殊处理，存地址的位置
			int ofs = curr->offset;
			char tmp[32]; memset(tmp, 0, 32);
			sprintf(tmp, "\tsubu $v1, $fp, %d\n", ofs);
			fputs(tmp, objFile);
			memset(tmp, 0, 32);
			sprintf(tmp, "\tmove "); print_reg(tmp, reg[pos]); sprintf(tmp, "%s, $v1\n", tmp);
			fputs(tmp, objFile);
			//要不要把数组也位置也存进去啊
		}
		else if(curr->offset > 0 && !alloc_mem) {	//在栈中有位置了
			char tmp[32];
			memset(tmp, 0, 32);
			sprintf(tmp, "\tlw "); print_reg(tmp, reg[pos]); sprintf(tmp, "%s, -%d($fp)\n", tmp, curr->offset);
			fputs(tmp, objFile);
		}
	}
	printf("in ensure: return reg: %d\n", pos);
	reg[pos].in_mem = 0;
	return pos;
}
int allocate(Operand x)
{
	int pos = -1;
	int is_find = 0;
	for(int i = 8; i<26; i++) {
		
		if(!reg[i].is_used) {
			if(!is_find) {
				is_find = 1;
				pos = i;
				reg[i].op = x;
				reg[i].is_used = 1;
				reg[i].farthest_nouse = 0;
				//break;
			}
		}
		else 
			reg[i].farthest_nouse++;
	}
	if(!is_find) {
		int reg_no = -1;
		int farthest = 0;
		for(int i = 8; i<26; i++) {
			if(farthest < reg[i].farthest_nouse) {
				farthest = reg[i].farthest_nouse;
				reg_no = i;
			}
		}
		spill(reg[reg_no]);
		//result = reg[reg_no];
		pos = reg_no;
		reg[reg_no].op = x;
		reg[reg_no].farthest_nouse = 0;
	}
	reg[pos].in_mem = 0;
	return pos;
}
void spill(Reg r)
{
	Operand op = 0;
	localList curr = localHead[func_in];
	if(r.op->kind == IMM_NUMBER) {	//还不知道有没有没考虑到的情况
		printf("IMM_NUMBER spill\n");
		return;
	}
	while(curr) {
		int flag = op_equal(curr->op, r.op);
		if(flag)
			break;
		curr = curr->next;
	}
	if(curr->offset > 0 && !r.in_mem) {	//spill的时候不会还没在内存（栈）中，前面ensure要分配的
		char tmp[32];
		memset(tmp, 0, 32);
		sprintf(tmp, "\tsw "); print_reg(tmp, r); sprintf(tmp, "%s, -%d($fp)\n", tmp, curr->offset);
		fputs(tmp, objFile);
		r.in_mem = 1;
	}
}
void print_reg(char* dest, Reg r)
{
	switch(r.kind) {
		case zero: sprintf(dest, "%s$zero", dest); break;
		case at: sprintf(dest, "%s$at", dest); break;
		case v0: sprintf(dest, "%s$v0", dest); break;
		case v1: sprintf(dest, "%s$v1", dest); break;
		case a0: sprintf(dest, "%s$a0", dest); break;
		case a1: sprintf(dest, "%s$a1", dest); break;
		case a2: sprintf(dest, "%s$a2", dest); break;
		case a3: sprintf(dest, "%s$a3", dest); break;
		case t0: sprintf(dest, "%s$t0", dest); break;
		case t1: sprintf(dest, "%s$t1", dest); break;
		case t2: sprintf(dest, "%s$t2", dest); break;
		case t3: sprintf(dest, "%s$t3", dest); break;
		case t4: sprintf(dest, "%s$t4", dest); break;
		case t5: sprintf(dest, "%s$t5", dest); break;
		case t6: sprintf(dest, "%s$t6", dest); break;
		case t7: sprintf(dest, "%s$t7", dest); break;
		case s0: sprintf(dest, "%s$s0", dest); break;
		case s1: sprintf(dest, "%s$s1", dest); break;
		case s2: sprintf(dest, "%s$s2", dest); break;
		case s3: sprintf(dest, "%s$s3", dest); break;
		case s4: sprintf(dest, "%s$s4", dest); break;
		case s5: sprintf(dest, "%s$s5", dest); break;
		case s6: sprintf(dest, "%s$s6", dest); break;
		case s7: sprintf(dest, "%s$s7", dest); break;
		case k0: sprintf(dest, "%s$k0", dest); break;
		case k1: sprintf(dest, "%s$k1", dest); break;
		case gp: sprintf(dest, "%s$gp", dest); break;
		case sp: sprintf(dest, "%s$sp", dest); break;
		case fp: sprintf(dest, "%s$fp", dest); break;
		case ra: sprintf(dest, "%s$ra", dest); break;
	}
}
void choose_instr(InterCodes ir) {
	printf("in choose_instr func_in: %d\n", func_in);
	if(ir->code.kind == D_LABEL) {	//基本块开始，需要把寄存器都存回内存去吧(jump的跳转)
		for(int i = 8; i<26; i++) {		//把里面有东西的寄存器全部存回去
			if(reg[i].is_used) {
				spill(reg[i]);
				reg[i].in_mem = 1;
				//reg[i].is_used = 0;
				//reg[i].op = NULL;
				//reg[i].farthest_nouse = 0;
			}
		}
		char tmp[32];
		memset(tmp, 0, 32);
		sprintf(tmp, "label%d:\n", ir->code.u.label.x->u.label_no);
		fputs(tmp, objFile);
		return;
	}
	else if(ir->code.kind == ASSIGN) {
		Operand left = ir->code.u.assign.x; Operand right = ir->code.u.assign.y;
		int reg_left;
		if(right->kind == IMM_NUMBER) {
			reg_left = ensure(left);
			char tmp[32];
			memset(tmp, 0, 32);
			sprintf(tmp, "\tli "); print_reg(tmp, reg[reg_left]); sprintf(tmp, "%s, %d\n", tmp, right->u.value_int);
			fputs(tmp, objFile);
		}
		else if(right->kind == TMP || right->kind == VARIABLE)  {
			reg_left = ensure(left); int reg_right = ensure(right);
			char tmp[32];
			memset(tmp, 0, 32);
			sprintf(tmp, "\tmove "); print_reg(tmp, reg[reg_left]); sprintf(tmp, "%s, ", tmp); print_reg(tmp, reg[reg_right]); sprintf(tmp, "%s\n", tmp);
			fputs(tmp, objFile);
		}
		localList curr = if_inlocal(left);
		if(curr && !reg[reg_left].in_mem && !left->is_address) {	//还没存入内存要先存入内存,在局部变量没存的话肯定要先放内存？
			char tmp[32]; memset(tmp, 0, 32);
			sprintf(tmp, "\tsw "); print_reg(tmp, reg[reg_left]); sprintf(tmp, "%s, -%d($fp)\n", tmp, curr->offset);
			fputs(tmp, objFile);
			curr->if_store = 1;
			reg[reg_left].in_mem = 1;
		}
	}
	else if(ir->code.kind == ADD) {
		Operand x = ir->code.u.arithmetic.x; Operand y = ir->code.u.arithmetic.y; Operand z = ir->code.u.arithmetic.z;
		int reg_x;
		if(z->kind == IMM_NUMBER) {
			reg_x = ensure(x); int reg_y = ensure(y);
			int k = z->u.value_int;
			char tmp[32];
			memset(tmp, 0, 32);
			sprintf(tmp, "\taddi "); print_reg(tmp, reg[reg_x]); sprintf(tmp, "%s, ", tmp); print_reg(tmp, reg[reg_y]); sprintf(tmp, "%s, %d\n", tmp, k);
			fputs(tmp, objFile);
		}
		else if(z->kind == TMP || z->kind == VARIABLE) {
			reg_x = ensure(x); int reg_y = ensure(y); int reg_z = ensure(z);
			char tmp[32];
			memset(tmp, 0, 32);
			sprintf(tmp, "\tadd "); print_reg(tmp, reg[reg_x]); sprintf(tmp, "%s, ", tmp); print_reg(tmp, reg[reg_y]); sprintf(tmp, "%s, ", tmp); print_reg(tmp, reg[reg_z]); sprintf(tmp, "%s\n", tmp);
			fputs(tmp, objFile);
		}
		
		localList curr = if_inlocal(x);
		//if(curr && !curr->if_store) {	//还没存入内存要先存入内存
		if(curr && !reg[reg_x].in_mem && !x->is_address) {
			char tmp[32]; memset(tmp, 0, 32);
			sprintf(tmp, "\tsw "); print_reg(tmp, reg[reg_x]); sprintf(tmp, "%s, -%d($fp)\n", tmp, curr->offset);
			fputs(tmp, objFile);
			curr->if_store = 1;
			reg[reg_x].in_mem = 1;
		}
	}
	else if(ir->code.kind == SUB) {
		Operand x = ir->code.u.arithmetic.x; Operand y = ir->code.u.arithmetic.y; Operand z = ir->code.u.arithmetic.z;
		int reg_x;
		if(z->kind == IMM_NUMBER) {
			reg_x = ensure(x); int reg_y = ensure(y);
			int k = z->u.value_int;
			char tmp[32];
			memset(tmp, 0, 32);
			sprintf(tmp, "\taddi "); print_reg(tmp, reg[reg_x]); sprintf(tmp, "%s, ", tmp); print_reg(tmp, reg[reg_y]); sprintf(tmp, "%s, -%d\n", tmp, k);
			fputs(tmp, objFile);
		}
		else if(z->kind == TMP || z->kind == VARIABLE) {
			reg_x = ensure(x); int reg_y = ensure(y); int reg_z = ensure(z);
			char tmp[32];
			memset(tmp, 0, 32);
			//sprintf(tmp, "\tsub "); print_reg(tmp, reg_x); sprintf(tmp, ", "); print_reg(tmp, reg_y); sprintf(tmp, ", "); print_reg(tmp, reg_z); sprintf(tmp, "\n");
			sprintf(tmp, "\tsub "); print_reg(tmp, reg[reg_x]); sprintf(tmp, "%s, ", tmp); print_reg(tmp, reg[reg_y]); sprintf(tmp, "%s, ", tmp); print_reg(tmp, reg[reg_z]); sprintf(tmp, "%s\n", tmp);
			fputs(tmp, objFile);
		}
		
		localList curr = if_inlocal(x); 
		//if(curr && !curr->if_store) {	//还没存入内存要先存入内存
		if(curr && !reg[reg_x].in_mem && !x->is_address) {
			printf("curr op no: %d reg op_no: %d\n", curr->op->u.tmp_no, reg[reg_x].op->u.tmp_no);
			char tmp[32]; memset(tmp, 0, 32);
			sprintf(tmp, "\tsw "); print_reg(tmp, reg[reg_x]); sprintf(tmp, "%s, -%d($fp)\n", tmp, curr->offset);
			fputs(tmp, objFile);
			curr->if_store = 1;
			reg[reg_x].in_mem = 1;
		}
	}
	else if(ir->code.kind == MUL) {
		Operand x = ir->code.u.arithmetic.x; Operand y = ir->code.u.arithmetic.y; Operand z = ir->code.u.arithmetic.z;
		int reg_x = ensure(x); int reg_y = ensure(y); int reg_z = ensure(z);
		char tmp[32];
		memset(tmp, 0, 32);
		sprintf(tmp, "\tmul "); print_reg(tmp, reg[reg_x]); sprintf(tmp, "%s, ", tmp); print_reg(tmp, reg[reg_y]); sprintf(tmp, "%s, ", tmp); print_reg(tmp, reg[reg_z]); sprintf(tmp, "%s\n", tmp);
		fputs(tmp, objFile);
		
		localList curr = if_inlocal(x);
		//if(curr && !curr->if_store) {	//还没存入内存要先存入内存
		if(curr && !reg[reg_x].in_mem && !x->is_address) {
			char tmp[32]; memset(tmp, 0, 32);
			sprintf(tmp, "\tsw "); print_reg(tmp, reg[reg_x]); sprintf(tmp, "%s, -%d($fp)\n", tmp, curr->offset);
			fputs(tmp, objFile);
			curr->if_store = 1;
			reg[reg_x].in_mem = 1;
		}
	}
	else if(ir->code.kind == IR_DIV) {
		Operand x = ir->code.u.arithmetic.x; Operand y = ir->code.u.arithmetic.y; Operand z = ir->code.u.arithmetic.z;
		int reg_x = ensure(x); int reg_y = ensure(y); int reg_z = ensure(z);
		char tmp[32];
		memset(tmp, 0, 32);
		sprintf(tmp, "\tdiv "); print_reg(tmp, reg[reg_y]); sprintf(tmp, "%s, ", tmp); print_reg(tmp, reg[reg_z]); sprintf(tmp, "%s\n", tmp);
		fputs(tmp, objFile);
		memset(tmp, 0, 32);
		sprintf(tmp, "\tmflo "); print_reg(tmp, reg[reg_x]); sprintf(tmp, "%s\n", tmp);
		fputs(tmp, objFile);
		
		localList curr = if_inlocal(x);
		//if(curr && !curr->if_store) {	//还没存入内存要先存入内存
		if(curr && !reg[reg_x].in_mem && !x->is_address) {
			char tmp[32]; memset(tmp, 0, 32);
			sprintf(tmp, "\tsw "); print_reg(tmp, reg[reg_x]); sprintf(tmp, "%s, -%d($fp)\n", tmp, curr->offset);
			fputs(tmp, objFile);
			curr->if_store = 1;
			reg[reg_x].in_mem = 1;
		}
	}
	else if(ir->code.kind == JUMP) {	//代码块的结束，下一个指令就是新的开始了
		Operand label = ir->code.u.jump.x;
		if(!label) {
			printf("ERROR when jump!!!!\n");
			return;
		}
		for(int i = 8; i<26; i++) {		//把里面有东西的寄存器全部存回去
			if(reg[i].is_used) {
				//printf("reg: %d\n", i);
				spill(reg[i]);reg[i].in_mem = 1;
				//reg[i].is_used = 0;
				//reg[i].op = NULL;
				//reg[i].farthest_nouse = 0;
			}
		}
		char tmp[32]; memset(tmp, 0, 32);
		sprintf(tmp, "\tj label%d\n", label->u.label_no);
		fputs(tmp, objFile);
	}
	else if(ir->code.kind == IF_JUMP) { //代码块的结束，下一个指令就是新的开始了
		for(int i = 8; i<26; i++) {		//把里面有东西的寄存器全部存回去, 不知道要不要管这些啊！！！
			if(reg[i].is_used) {
				spill(reg[i]);reg[i].in_mem = 1;
				//reg[i].is_used = 0;
				//reg[i].op = NULL;
				//reg[i].farthest_nouse = 0;
			}
		}
		Operand x = ir->code.u.if_jump.x; Operand y = ir->code.u.if_jump.y;
		Operand label = ir->code.u.if_jump.z;
		int op = ir->code.u.if_jump.op;
		int reg_x = ensure(x); int reg_y = ensure(y);
		char tmp[32]; memset(tmp, 0, 32);
		printf("op: %d\n", op);
		if(op == 0) { 
			sprintf(tmp, "\tbgt ");
		}
		else if(op == 1) {
			sprintf(tmp, "\tblt ");
		}
		else if(op == 2) {
			sprintf(tmp, "\tbge ");
		}
		else if(op == 3) {
			sprintf(tmp, "\tble ");
		}
		else if(op == 4) {
			sprintf(tmp, "\tbeq ");
		}
		else if(op == 5) {
			sprintf(tmp, "\tbne ");
		}
		print_reg(tmp, reg[reg_x]); sprintf(tmp, "%s, ", tmp); print_reg(tmp, reg[reg_y]); sprintf(tmp, "%s, label%d\n", tmp, label->u.label_no); 
		fputs(tmp, objFile);
		
	}
	else if(ir->code.kind == D_FUNCTION) {	//新的函数新的栈所有都清空，局部变量也是
		for(int i = 8; i<26; i++) {	//不用生成指令因为call的时候都存内存了 每个函数要重新清空一下？？？？
			reg[i].is_used = 0;
			reg[i].farthest_nouse = 0;
			reg[i].op = NULL;
		}
		
		char* name = ir->code.u.function.f->u.f_name;

		char tmp[32];
		memset(tmp, 0, 32);
		sprintf(tmp, "\n%s:\n", ir->code.u.function.f->u.f_name);
		fputs(tmp, objFile);
		if(func_in>=0)
			func_in--;
		func_in++;	//好像确实没什么用
		localHead[func_in] = (localList)malloc(sizeof(struct localList_));
		localHead[func_in]->next = NULL; localHead[func_in]->offset = 0; localHead[func_in]->op = NULL;
		localHead[func_in]->if_store = 0;
		stack_offset = 0;
		
		memset(tmp, 0, 32);
		sprintf(tmp, "\tsubu $sp, $sp, %d\n", stack_size);
		fputs(tmp, objFile);
		
		if(strcmp(name, "main")) {
			is_main = 0;
		}
		else {
			is_main = 1;
		}
		memset(tmp, 0, 32);
		sprintf(tmp, "\taddi $fp, $sp, %d\n", stack_size);
		fputs(tmp, objFile);
		/*其他寄存器有必要保存吗？*/
		//剩下的给param做吧
		return;
	}
	else if(ir->code.kind == RET) {
		Operand x = ir->code.u.ret.x;
		char tmp[32]; memset(tmp, 0, 32);
		
		
		printf("x kind in ret: %d\n", x->kind);
		if(x->kind == IMM_NUMBER) {
			if(!x->u.value_int) {
				sprintf(tmp, "\tmove $v0, $0\n");
				fputs(tmp, objFile);
			}
			else {
				sprintf(tmp, "\tli $v1, %d\n", x->u.value_int);
				fputs(tmp, objFile);
				sprintf(tmp, "\tmove $v0, $v1\n");
				fputs(tmp, objFile);
			}
		}
		else {
			int reg_x = ensure(x);		
			//if(x->is_address) {
			//	sprintf(tmp, "\tlw "); print_reg(tmp, reg[reg_x]); sprintf(tmp, "%s, 0(", tmp); print_reg(tmp, reg[reg_x]); sprintf(tmp, "%s)\n", tmp);
			//	fputs(tmp, objFile);
			//}
			memset(tmp, 0, 32);
			sprintf(tmp, "\tmove $v0, "); print_reg(tmp, reg[reg_x]); sprintf(tmp, "%s\n", tmp);
			fputs(tmp, objFile);
		}
		if(!ir->next || ir->next->code.kind == D_FUNCTION) {
			localList curr = localHead[func_in];
			while(curr) {
				localHead[func_in] = localHead[func_in]->next;
				free(curr);
				curr = localHead[func_in];
			}
		}
		//if(!is_main) {
		//printf("func_in: %d\n", func_in);
		if(!is_main) {
			
			memset(tmp, 0, 32);
			sprintf(tmp, "\taddi $sp, $sp, %d\n", stack_size);
			fputs(tmp, objFile);
			memset(tmp, 0, 32);
		}
		
		sprintf(tmp, "\tjr $ra\n");
		fputs(tmp, objFile);	
		
	}
	else if(ir->code.kind == CALL) {
		Operand x = ir->code.u.call.x; Operand f = ir->code.u.call.f;

		int t_offset[10];
		memset(t_offset, -1, sizeof(t_offset));
		printf("function name: %s\n", f->u.f_name);
		//-------------------------保存活跃变量, 我用fp寻址应该不会影响吧！！---------------------------//
		for(int i = 8; i<16; i++) {		//把里面有东西的寄存器全部存回去,但不清空？？？
			if(reg[i].is_used) {
				Operand op = reg[i].op;
				localList curr = localHead[func_in];
				while(curr) {
					if(op_equal(curr->op, op)) {
						t_offset[i-8] = curr->offset;
						break;
					}
					curr = curr->next;
				}
				spill(reg[i]); reg[i].in_mem = 1;
				//reg[i].is_used = 0;
				//reg[i].op = NULL;
				//reg[i].farthest_nouse = 0;
			}
		}
		if(reg[24].is_used) {
			Operand op = reg[24].op;
			localList curr = localHead[func_in];
			while(curr) {
				if(op_equal(curr->op, op)) {
					t_offset[8] = curr->offset;
					break;
				}
				curr = curr->next;
			}
			spill(reg[24]);
			//reg[24].is_used = 0; reg[24].op = NULL; reg[24].farthest_nouse = 0;
		}
		if(reg[25].is_used) {
			Operand op = reg[25].op;
			localList curr = localHead[func_in];
			while(curr) {
				if(op_equal(curr->op, op)) {
					t_offset[9] = curr->offset;
					break;
				}
				curr = curr->next;
			}
			spill(reg[25]);
			//reg[25].is_used = 0; reg[25].op = NULL; reg[25].farthest_nouse = 0;
		}
		char tmp[32];
		memset(tmp, 0, 32);
		int reg_x = ensure(x);	//放这里吧？
		//-------------------------------传参------------------------------//
		//int arg_offset[4];
		
		for(int i = arg_cnt-1, j = 0; i>=0 && j<4; i--, j++) {
			int tmp_reg = ensure(argList[i]);
			memset(tmp, 0, 32);
			//保存当前参数
			localList this_arg = if_inlocal(reg[j+4].op);
			printf("iiiiiiiiiiiiiiiiiiiiii: %d\n", i);
			if(this_arg) {
				printf("when save arg: %p\n", this_arg);
				memset(tmp, 0, 32);
				sprintf(tmp, "\tsw $a%d, %d($sp)\n", j, stack_size - this_arg->offset);
			}
			else {
				printf("when save arg error!!!!!\n");	//主函数的a0a1这些应该不用管嘛
			}
			fputs(tmp, objFile);
			memset(tmp, 0, 32);
			printf("!!!!!!!!ttttttttttttttttmp_reg: %d j: %d\n", tmp_reg, j+4);
			if(tmp_reg >=4 && tmp_reg<=7 && tmp_reg != j+4) {//要从a0这些里面取，要取之前保存的值，因为新的可能已经是被赋成其他值了
				//printf("!!!!!!!!ttttttttttttttttmp_reg: %d j: %d\n", tmp_reg, j+4);
				//printf("tmp reg tmp no: %d\n", reg[tmp_reg].op->u.tmp_no);
				this_arg = if_inlocal(reg[tmp_reg].op);
				//printf("tttttttttttttttttttttttthis this_argoffset: %d\n", this_arg->offset);
				//printf("reg[j] tmp no: %d\n", reg[4+j].op->u.tmp_no);
				sprintf(tmp, "\tlw $a%d, %d($sp)\n", j, stack_size - this_arg->offset);
			}
			else if(tmp_reg != j+4){
				sprintf(tmp, "\tmove $a%d, ", j); print_reg(tmp, reg[tmp_reg]); sprintf(tmp, "%s\n", tmp);
			}
			fputs(tmp, objFile);printf("staaaaaaaaaaaaaack offset : %d\n", stack_offset);
		} 
		if(arg_cnt > 4) {
			if(4*(arg_cnt-5) != 0) {
				sprintf(tmp, "\tsubu $sp, $sp, %d\n", 4*(arg_cnt-5));
				fputs(tmp, objFile);
			}
			memset(tmp, 0, 32);
			for(int i = arg_cnt-5, j=5; i>=0; i--, j++) {
				int tmp_reg = ensure(argList[i]);
				sprintf(tmp, "\tsw "); print_reg(tmp, reg[tmp_reg]); sprintf(tmp, "%s, %d($sp)\n", tmp, 4*(j-5));
				fputs(tmp, objFile);
			}
			
		}
		//int old_offset = stack_offset;
		//保存fp和ra
		printf("staaaaaaaaaaaaaack offset : %d\n", stack_offset);
		stack_offset += 4;
		sprintf(tmp, "\tsw $ra, %d($sp)\n", stack_size - stack_offset);
		fputs(tmp, objFile);
		memset(tmp, 0, 32);
		stack_offset += 4;
		sprintf(tmp, "\tsw $fp, %d($sp)\n", stack_size - stack_offset);
		fputs(tmp, objFile);
		
		sprintf(tmp, "\tjal %s\n", f->u.f_name);
		fputs(tmp, objFile);
		
		//恢复fp和ra
		memset(tmp, 0, 32);
		sprintf(tmp, "\tlw $fp, %d($sp)\n", stack_size - stack_offset);
		fputs(tmp, objFile);
		stack_offset -=4;
		memset(tmp, 0, 32);
		sprintf(tmp, "\tlw $ra, %d($sp)\n", stack_size - stack_offset);
		fputs(tmp, objFile);
		stack_offset -=4;
		//恢复参数
		for(int j = (arg_cnt<=4)?arg_cnt-1:3;  j>=0; j--) {
			memset(tmp, 0, 32);
			//printf("which reg: %d op kind: %d v_name: %s\n", 4+j, reg[4+j].op->kind, reg[4+j].op->v_name);
			//printf("in recover arggggggggggggggggggggg j: %d\n", j);
			//localList this_arg = if_inlocal(argList[j]);
			localList this_arg = NULL;
			if(reg[j+4].op)
				this_arg = if_inlocal(reg[j+4].op);	//应该是这样吗？？？
			//localList this_argg = if_inlocal(reg[4].op);
			//printf("thisarg offset: %d\n", this_arg->offset);
			//printf("reg[4].op kind: %d tmp_no: %d\n", reg[4].op->kind, reg[3].op->u.tmp_no);
			//printf("arglist[j] kind: %d tmp_no: %d\n")
			//if(this_argg->op)
			//	printf("this argg offset: %d\n", this_argg->offset);
			if(this_arg) {
				sprintf(tmp, "\tlw $a%d, %d($sp)\n", j, stack_size - this_arg->offset);
			}
			fputs(tmp, objFile);
			//stack_offset -= 4;
		}
		if(arg_cnt > 4) {//应该没判断错吧
			memset(tmp, 0, 32);
			sprintf(tmp, "\taddi $sp, $sp, %d\n", 4*(arg_cnt-5));
			fputs(tmp, objFile);
		}
		for(int i = 0; i<10; i++) {
			if(t_offset[i] != -1) {
				memset(tmp, 0, 32);
				sprintf(tmp, "\tlw $t%d, -%d($fp)\n", i, t_offset[i]);
				fputs(tmp, objFile);
			}
		}
		for(int i = 0; i<arg_cnt; i++) {
			argList[i] = NULL;
		}
		arg_cnt = 0;
		memset(tmp, 0, 32);
		sprintf(tmp, "\tmove "); print_reg(tmp, reg[reg_x]); sprintf(tmp, "%s, $v0\n", tmp);
		fputs(tmp, objFile);
	}
	else if(ir->code.kind == ARG) {
		
		argList[arg_cnt++] = ir->code.u.arg.x;
		localList try = if_inlocal(argList[arg_cnt-1]);
		printf("try:::::::::::::::%p tmp_no: %d\n", try, argList[arg_cnt-1]->u.tmp_no);
	}
	else if(ir->code.kind == PARA) {
		Operand x = ir->code.u.para.x;
		if(para_cnt < 4) {
			int pos = 4+para_cnt;
			printf("the x(kind: %d tmp_no: %d) save in the reg[%d]\n", x->kind, x->u.tmp_no, pos);
			reg[pos].is_used = 1;
			reg[pos].in_mem = 1;
			reg[pos].op = x;
			stack_offset += 4;
			localList tmp_list = (localList)malloc(sizeof(struct localList_));
			tmp_list->op = x; tmp_list->offset = stack_offset; tmp_list->next = NULL;tmp_list->if_store = 1;
			printf("tmp_list op name: %s\n", tmp_list->op->v_name);
			localList curr = localHead[func_in];
			while(curr->next)
				curr = curr->next;
			curr->next = tmp_list;
			
			char tmp[32]; memset(tmp, 0, 32);
			sprintf(tmp, "\tsw $a%d, -%d($fp)\n", para_cnt, stack_offset);
			fputs(tmp, objFile);
			printf("reg[%d] op: %p offset: %d\n", pos, reg[pos].op, if_inlocal(reg[pos].op)->offset);
		}
		para_cnt++;	
		if(para_cnt > 4) {
			int reg_para = ensure(x);
			char tmp[32]; memset(tmp, 0, 32);
			sprintf(tmp, "\tlw "); print_reg(tmp, reg[reg_para]); sprintf(tmp, "%s, %d($fp)\n", tmp, 4*(para_cnt-5));
			fputs(tmp, objFile);
		}
		if(!ir->next || ir->next->code.kind != PARA) {
			para_cnt = 0;
		}
	}
	else if(ir->code.kind == ASSIGN_ADDR) {
		//x=&y
		Operand x = ir->code.u.assign_address.x; Operand y = ir->code.u.assign_address.y;
		int reg_x = ensure(x); int reg_y = ensure(y);
		
		char tmp[32]; memset(tmp, 0, 32);
		sprintf(tmp, "\tmove "); print_reg(tmp, reg[reg_x]); sprintf(tmp, "%s, ", tmp); print_reg(tmp, reg[reg_y]); sprintf(tmp, "%s\n", tmp);
		fputs(tmp, objFile);
		//不知道对不对 先放着吧
		localList curr = if_inlocal(x);
		//if(curr && !curr->if_store) {	//还没存入内存要先存入内存
		if(curr && !reg[reg_x].in_mem && !x->is_address) {
			char tmp[32]; memset(tmp, 0, 32);
			sprintf(tmp, "\tsw "); print_reg(tmp, reg[reg_x]); sprintf(tmp, "%s, -%d($fp)\n", tmp, curr->offset);
			fputs(tmp, objFile);
			curr->if_store = 1;
			reg[reg_x].in_mem = 1;
		}
	}
	else if(ir->code.kind == ASSIGN_CONTENT) {
		//x=*y,不记得这两边的变量是什么了，先暂时默认是tmp直接分配寄存器吧。。。
		Operand x = ir->code.u.assign_content.x; Operand y = ir->code.u.assign_content.y;
		int reg_x = ensure(x); int reg_y = ensure(y);
		
		char tmp[32]; memset(tmp, 0, 32);
		sprintf(tmp, "\tlw "); print_reg(tmp, reg[reg_x]); sprintf(tmp, "%s, 0(", tmp); print_reg(tmp, reg[reg_y]); sprintf(tmp, "%s)\n", tmp);
		fputs(tmp, objFile);
		//数组先不写
		localList curr = if_inlocal(x);
		//if(curr && !curr->if_store) {	//还没存入内存要先存入内存
		if(curr && !reg[reg_x].in_mem) {
			char tmp[32]; memset(tmp, 0, 32);
			sprintf(tmp, "\tsw "); print_reg(tmp, reg[reg_x]); sprintf(tmp, "%s, -%d($fp)\n", tmp, curr->offset);
			fputs(tmp, objFile);
			curr->if_store = 1;
			reg[reg_x].in_mem = 1;
		}
	}
	else if(ir->code.kind == CONTENT_ASSIGNED) {
		//也不知道对不对，好像前面就不支持数组在左侧
		Operand x = ir->code.u.assign_content.x; Operand y = ir->code.u.assign_content.y;
		int reg_x = ensure(x); int reg_y = ensure(y);
		
		char tmp[32]; memset(tmp, 0, 32);
		sprintf(tmp, "\tsw "); print_reg(tmp, reg[reg_y]); sprintf(tmp, "%s, 0(", tmp); print_reg(tmp, reg[reg_x]); sprintf(tmp, "%s)\n", tmp);
		fputs(tmp, objFile);

	}
	else if(ir->code.kind == DEC) {
		Operand x = ir->code.u.dec.x;
		int size = ir->code.u.dec.size;
		
		stack_offset += size;	//应该存一个变量就好了吧
		localList curr = localHead[func_in];
		while(curr->next)
			curr = curr->next;
		localList tmp_locallist = (localList)malloc(sizeof(struct localList_));
		tmp_locallist->if_store = 0;
		tmp_locallist->offset = stack_offset;
		tmp_locallist->op = x;
		tmp_locallist->next = NULL;
		curr->next = tmp_locallist;
	}
	else if(ir->code.kind == READ) {
		Operand x = ir->code.u.read.x;
		int reg_x = ensure(x);
		
		localList try = if_inlocal(reg[reg_x].op);
		char tmp[32]; memset(tmp, 0, 32);
		stack_offset += 4;
		sprintf(tmp, "\tsw $ra, -%d($fp)\n", stack_offset);
		fputs(tmp, objFile);
		memset(tmp, 0, 32);
		sprintf(tmp, "\tjal read\n");
		fputs(tmp, objFile);
		memset(tmp, 0, 32);
		sprintf(tmp, "\tlw $ra, -%d($fp)\n", stack_offset);
		fputs(tmp, objFile);
		stack_offset -=4;
		memset(tmp, 0, 32);
		sprintf(tmp, "\tmove "); print_reg(tmp, reg[reg_x]); sprintf(tmp, "%s, $v0\n", tmp);
		fputs(tmp, objFile);
	}
	else if(ir->code.kind == WRITE) {
		Operand x = ir->code.u.write.x;
		int reg_x = ensure(x);
		
		char tmp[32]; memset(tmp, 0, 32);
		stack_offset += 4;
		sprintf(tmp, "\tsw $ra, -%d($fp)\n", stack_offset);
		fputs(tmp, objFile);
		memset(tmp, 0, 32);
		sprintf(tmp, "\tmove $a0, "); print_reg(tmp, reg[reg_x]); sprintf(tmp, "%s\n", tmp);
		fputs(tmp, objFile);
		fputs("\tjal write\n", objFile);
		memset(tmp, 0, 32);
		sprintf(tmp, "\tlw $ra, -%d($fp)\n", stack_offset);
		fputs(tmp, objFile);
		stack_offset -=4;
		memset(tmp, 0, 32);
		
	}
	return;
}
