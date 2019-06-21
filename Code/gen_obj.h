
#ifndef GEN_OBJ_H
#define GEN_OBJ_H

#include "ir.h"
typedef enum {
	zero, 
	at, 
	v0, v1, 
	a0, a1, a2, a3, 
	t0, t1, t2, t3, t4, t5, t6, t7, 
	s0, s1, s2, s3, s4, s5, s6, s7,
	t8, t9,
	k0, k1,
	gp,
	sp, fp, 
	ra
}reg_kind;
/*这个结构真是丑爆了*/
typedef struct Register Reg ;
struct Register {
	reg_kind kind;
	int is_used;
	int farthest_nouse;	//选择最久没有使用的
	int in_mem;
	Operand op;	//reg存的是哪个变量
};
typedef struct localList_* localList;
struct localList_ {
	Operand op;
	int offset;
	struct localList_* next;
	int if_store;
};
void init_gen();	//还要初始化文件
void print_reg(char* dest, Reg r);
void choose_instr(InterCodes ir);
int ensure(Operand x);
int allocate(Operand x);
void spill(Reg r);
void gen_obj();
int op_equal(Operand a, Operand b);
localList if_inlocal(Operand x);
#endif

