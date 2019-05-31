#include "ir.h"
typedef enum {
	zero, 
	at, 
	v0, v1, 
	a0, a1, a2, a3, 
	t0, t1, t2, t3, t4, t5, t6, t7, 
	s0, s1, s2, s3, s4, s5, s6, s7,
	k0, k1,
	gp,
	sp, fp, 
	ra
}reg_kind;
typedef struct Reg Register;
struct Reg {
	reg_kind kind;
	int is_used;
	Operand op;	//reg存的是哪个变量
};
typedef struct block_* block;
struct block_ {
	int start;
	int end;
	struct block_* next;
};

void init_gen();	//还要初始化文件
void print_reg(Register r);
void choose_instr(InterCodes ir);
void div_block();	//直接从head开始
void choose_reg(InterCodes ir);	//传入的参数待定
Register ensure(Operand x);
Register allocate(Operand x);
void spill(Register r);		//怎么放到栈上啊？？？？


