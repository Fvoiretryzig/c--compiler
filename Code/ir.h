#define IR_H

#ifdef IR_H
typedef struct Operand_* Operand;
typedef struct InterCodes_* InterCodes;
struct Operand_ {
	enum { VARIABLE, CONSTANT, ADDRESS, LABEL, FUNCTION, TMP_VARIABLE, IMM_NUMBER, ADDRESS_CONTENT } kind;
	union {
		int var_no;
		int value_int;
		float value_float;
		char var_name[60];
		...
	} u;
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
		struct {Operand x, y, z;} if_jump;
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
int insert_ircode(InterCodes ir_code);
void print_ir(InterCodes ir_list);

#endif
