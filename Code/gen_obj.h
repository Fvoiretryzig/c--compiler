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
typedef struct Register Reg ;
struct Register {
	reg_kind kind;
	int is_used;
	int farthest_nouse;	//选择最久没有使用的
	Operand op;	//reg存的是哪个变量
};
typedef struct localList_ localList
struct localList_ {
	Operand op;
	int offset;
	struct localList_* next;
}
void init_gen();	//还要初始化文件
void print_reg(char* dest, Reg r)
void choose_instr(InterCodes ir);
//void choose_reg(InterCodes ir);	//感觉这个函数作用怪怪的，不如直接生成代码
Register ensure(Operand x);
Register allocate(Operand x);
void spill(Reg r);


