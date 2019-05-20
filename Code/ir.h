#include "gtree.h"

#define IR_H

#ifdef IR_H
typedef struct Operand_* Operand;
typedef struct InterCodes_* InterCodes;
struct Operand_ {
	enum { VARIABLE, CONSTANT, ADDRESS, LABEL, FUNCTION, TMP, IMM_NUMBER, ADDRESS_CONTENT } kind;
	union {
		int var_no;
		int label_no;
		int tmp_no;
		int value_int;
		float value_float;
		char f_name[60];
	} u; 
	char v_name[60];
	struct Operand_* next; //????????
	//TODO();
};
struct InterCode {
	enum { D_LABEL, D_FUNCTION, ASSIGN, ADD, SUB, MUL, DIV, ASSIGN_ADDR, ADDR_ASSIGNED, JUMP, IF_JUMP, RET, DEC, ARG, CALL, PARA, READ, WRITE} kind;
	union {
		struct {Operand x;} label;
		struct {Operand f;} function;
		struct {Operand x, y;} assign;
		struct {Operand x, y, z;} arithmetic;
		struct {Operand x, y;} assign_address;
		struct {Operand x, y;} address_assigned;
		struct {Operand x;} jump;
		struct {Operand x, y, z; int op;} if_jump;
		struct {Operand x;} ret;
		struct {Operand x; int size;} dec;
		struct {Operand x;} arg;
		struct {Operand x, f;} call;
		struct {Operand x;} para;
		struct {Operand x;} read;
		struct {Operand x;} write;
	} u;
}
struct InterCodes_ { 
	struct InterCode code; 
	struct InterCodes_ *prev, *next; 
};

void init_irlist();
void init_oplist();
void init_translate();

int insert_ircode(InterCodes ir_code);
int insert_op(Operand op);
Operand find_op(char* name)
void print_ir(InterCodes ir_list);
InterCodes concat(InterCodes ir1, InterCodes ir2);
Operand new_Operand(struct node* gnode, int kind, int n, float f);
Operand new_temp();
Operand new_label();
InterCodes new_InterCodes(Operand op1, Operand op2, Operand op3, int kind, int op);

int get_array_size(Type t);
int get_struct_size(Type t);

int get_relop(struct node* gnode);
InterCodes translate_program(struct node* program);
InterCodes translate_extdeflist(struct node* extdeflist);
InterCodes translate_extdef(struct node* extdef);
InterCodes translate_funcdec(struct node* funcdec);
InterCodes translate_varlist(struct node* varlist);
InterCodes translate_paradec(struct node* paradec);
InterCodes translate_compst(struct node* compst);
InterCodes translate_deflist(struct node* deflist);
InterCodes translate_def(struct node* def);
InterCodes translate_declist(struct node* declist, Type specifier);
InterCOdes translate_dec(struct node* dec, Type specifier);
InterCodes translate_stmtlist(struct node* stmtlist);
InterCode translate_stmt(struct node* stmt);
InterCodes translate_cond(struct node* exp, Operand label_true, Operand label_faluse);
InterCodes translate_exp(struct node* exp, Operand place);
InterCodes translate_args(struct node* args, Operand* arg_list);


#endif
