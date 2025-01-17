

#ifndef IR_H
#define IR_H
#include "gtree.h"
#include "semantic.h"
typedef struct Operand_* Operand;
typedef struct InterCodes_* InterCodes;
typedef enum {
	VARIABLE, ADDRESS, LABEL, FUNCTION, TMP, IMM_NUMBER, ADDRESS_CONTENT
}op_kind;
typedef enum {
	D_LABEL, D_FUNCTION, //0, 1
	ASSIGN, //2
	ADD, SUB, MUL, IR_DIV, //3, 4, 5, 6
	ASSIGN_ADDR/*x=&y*/, ASSIGN_CONTENT/*x=*y*/, CONTENT_ASSIGNED/**x=y*/, //7, 8, 9
	JUMP, IF_JUMP, //10, 11
	RET, DEC, ARG, CALL, PARA, //12, 13, 14, 15, 16
	READ, WRITE	//  17, 18
}ir_kind;
struct Operand_ {
	op_kind kind;
	union {
		int var_no;
		int label_no;
		int tmp_no;
		int value_int;
		float value_float;
		char f_name[60];
	} u; 
	char v_name[60];
	int is_address; 	//for tmp -1: nothing 0: address_content 1: address
	struct Operand_* next; //????????
	//TODO();
};
struct InterCode {
	ir_kind kind;
	union {
		struct {Operand x;} label;
		struct {Operand f;} function;
		struct {Operand x, y;} assign;
		struct {Operand x, y, z;} arithmetic;
		struct {Operand x, y;} assign_address;
		struct {Operand x, y;} assign_content;
		struct {Operand x, y;} content_assigned;
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
};
struct InterCodes_ { 
	struct InterCode code; 
	struct InterCodes_ *prev, *next; 
};

void init_translate();
void init_irlist();
void init_oplist();
void init_irtranslate();

int insert_ircode(InterCodes ir_code);
int insert_op(Operand op);
Operand find_op(char* name);
InterCodes concat(InterCodes ir1, InterCodes ir2);
Operand new_Operand(struct node* gnode, int kind, float n, int if_float);
Operand new_temp();
//sOperand remove_temp(Operand op);
Operand new_label();
InterCodes new_InterCodes(Operand op1, Operand op2, Operand op3, int kind, int op);

void print(struct node* root);
void print_op(Operand op);
void print_ir(InterCodes ir);

int get_array_size(Type t);
int get_struct_size(Type t);
int get_struct_offset(Type t, char* name);

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
InterCodes translate_dec(struct node* dec, Type specifier);
InterCodes translate_stmtlist(struct node* stmtlist);
InterCodes translate_stmt(struct node* stmt);
InterCodes translate_cond(struct node* exp, Operand label_true, Operand label_faluse);
InterCodes translate_exp(struct node* exp, Operand place);
InterCodes translate_args(struct node* args, Operand* arg_list, int* cnt);


#endif
