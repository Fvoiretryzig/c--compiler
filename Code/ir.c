#include "semantic.h"
#include "ir.h"

#define IR_DEBUG
InterCodes IRhead;
Operand ophead;

Operand imm_num0;
Operand imm_num1;
int lab_cnt;
int var_cnt;
int temp_cnt;
//////////////////////////////////////////////init/////////////////////////////////////////////////////
void init_irlist()
{
	IRhead = (InterCodes)malloc(sizeof(struct InterCodes_));
	if(IRhead == NULL) {
		printf("\033[47;31mERROR when malloc irhead\033[0m\n");
		return;
	}
	IRhead->prev = NULL; IRhead->next = NULL;

	return;
}
void init_oplist()
{
	ophead = (Operand)malloc(sizeof(struct Operand_));
	if(ophead == NULL) {
		printf("\033[47;31mERROR when malloc ophead\033[0m\n");
		return;
	}
	ophead->next = NULL;
	return;
}
void init_translate()
{
	int lable_cnt = 0;
	int var_cnt = 0;
	int temp_cnt = 0;
	imm_num0 = (Operand)malloc(sizeof(struct Operand_));	
	imm_num1 = (Operand)malloc(sizeof(struct Operand_));
	imm_num0->kind = IMM_NUMBER;
	imm_num0->u.value_int = 0;
	imm_num1->kind = IMM_NUMBER;
	imm_num1->u.value_int = 1;
	
	return;
}
void init_irtranslate()
{
	init_irlist();
	init_oplist();
	init_translate();
}
///////////////////////////////////////Operation/////////////////////////////////////////////////
int insert_ircode(InterCodes ir_code)
{
	InterCodes curr = IRhead;
	while(curr->next != NULL)
		curr = curr->next;
	curr->next = ir_code;
	ir_code->prev = curr;	
	InterCodes last = ir_code;
	while(last->next != NULL)
		last = last->next;
	last->next = NULL; 	//necessary????
	
	return 0;
}
int insert_op(Operand op)
{
	Operand curr = ophead;
	while(curr->next != NULL)
		curr = curr->next;
	curr->next = op;
	op->next = NULL;
	
	return 0;
}
Operand find_op(char* name) {
	Operand curr = ophead;
	while(curr!= NULL) {
		if(curr->kind == VARIABLE && !strcmp(name, curr->v_name)) {
			return curr;
		}
		curr = curr->next;
	}
	return NULL;
}
InterCodes concat(InterCodes ir1, InterCodes ir2)
{
	//printf("ir1: %p, ir2: %p\n", ir1, ir2);
	if(!ir1 && !ir2)
		return NULL;
	if(!ir1)
		return ir2;
	if(!ir2)
		return ir1;
	InterCodes curr1 = ir1, curr2 = ir2;
	while(curr1->next) {
		//printf("curr1: %p\n", curr1);
		curr1 = curr1->next;
	}
	curr1->next = ir2; ir2->prev = curr1;
	return ir1;
}
Operand new_Operand(struct node* gnode, int kind, float n, int if_float)
{
	Operand op = (Operand)malloc(sizeof(struct Operand_));
	switch(kind) {
		case VARIABLE:
			op->kind = VARIABLE;
			op->u.var_no = ++var_cnt;
			if(gnode)
				strcpy(op->v_name, gnode->str);
			break;
		//case CONSTANT
		case ADDRESS:
			break;
			//TODO()
		//case LABEL
		case FUNCTION:
			op->kind = FUNCTION;
			strcpy(op->u.f_name, gnode->str);
			break;
		//case TMP
		case IMM_NUMBER:
			op->kind = IMM_NUMBER;
			if(gnode)
				if(!if_float)
					op->u.value_int = gnode->type_int;
				else
					op->u.value_float = gnode->type_float;
			else
				if(!if_float)
					op->u.value_int = (int)n;
				else
					op->u.value_float = n;
			break;
		case ADDRESS_CONTENT:
			break;
			//TODO();
	}
	insert_op(op);
	return op;
}
Operand new_temp()
{
	Operand temp = (Operand)malloc(sizeof(struct Operand_));
	temp->kind = TMP;
	temp->u.tmp_no = ++temp_cnt;
	insert_op(temp);
	return temp;
}
/*Operand remove_temp(Operand op)
{
	Operand curr = op;
	printf("op: %p\n", op);
	while(curr) {
		curr->u.tmp_no--;
		curr = curr->next;
	}
	temp_cnt--;
	curr = ophead;
	while(curr->next != op)
		curr = curr->next;
	curr->next = op->next;
	//op = NULL;
	free(op);
	op = NULL;
	printf("op: %p\n", op);
	return NULL; 
}*/
Operand new_label()
{
	Operand label = (Operand)malloc(sizeof(struct Operand_));
	label->kind = LABEL;
	label->u.label_no = ++lab_cnt;
	insert_op(label);
	return label;
}
InterCodes new_InterCodes(Operand op1, Operand op2, Operand op3, int kind, int op)
{
	InterCodes ir = (InterCodes)malloc(sizeof(struct InterCodes_));
	switch(kind) {
		case D_LABEL:
			ir->code.kind = D_LABEL;
			ir->code.u.label.x = op1;
			break;
		case D_FUNCTION:
			ir->code.kind = D_FUNCTION;
			ir->code.u.function.f = op1;
			break;
		case ASSIGN:
			ir->code.kind = ASSIGN;
			ir->code.u.assign.x = op1;
			ir->code.u.assign.y = op2;
			break;
		case ADD:
			ir->code.kind = ADD;
			ir->code.u.arithmetic.x = op1;
			ir->code.u.arithmetic.y = op2;
			ir->code.u.arithmetic.z = op3;
			break;
		case SUB:
			ir->code.kind = SUB;
			ir->code.u.arithmetic.x = op1;
			ir->code.u.arithmetic.y = op2;
			ir->code.u.arithmetic.z = op3;
			break;
		case MUL:
			ir->code.kind = MUL;
			ir->code.u.arithmetic.x = op1;
			ir->code.u.arithmetic.y = op2;
			ir->code.u.arithmetic.z = op3;
			break;
		case IR_DIV:
			ir->code.kind = IR_DIV;
			ir->code.u.arithmetic.x = op1;
			ir->code.u.arithmetic.y = op2;
			ir->code.u.arithmetic.z = op3;
			break;
		case ASSIGN_ADDR:
			ir->code.kind = ASSIGN_ADDR;
			ir->code.u.assign_address.x = op1;
			ir->code.u.assign_address.y = op2;
			break;
		case ADDR_ASSIGNED:
			ir->code.kind = ADDR_ASSIGNED;
			ir->code.u.address_assigned.x = op1;
			ir->code.u.address_assigned.y = op2;
			break;
		case JUMP:
			ir->code.kind = JUMP;
			ir->code.u.jump.x = op1;
			break;
		case IF_JUMP:
			ir->code.kind = IF_JUMP;
			ir->code.u.if_jump.x = op1;
			ir->code.u.if_jump.y = op2;
			ir->code.u.if_jump.z = op3;
			ir->code.u.if_jump.op = op;
			break;
		case RET:
			ir->code.kind = RET;
			ir->code.u.ret.x = op1;
			break;
		case DEC:
			ir->code.kind = DEC;
			ir->code.u.dec.x = op1;
			ir->code.u.dec.size = op;
			break;
		case ARG:
			ir->code.kind = ARG;
			ir->code.u.arg.x = op1;
			break;
		case CALL:
			ir->code.kind = CALL;
			ir->code.u.call.x = op1;
			ir->code.u.call.f = op2;
			break;
		case PARA:
			ir->code.kind = PARA;
			ir->code.u.para.x = op1;
			break;
		case READ:
			ir->code.kind = READ;
			ir->code.u.read.x = op1;
			break;
		case WRITE:
			ir->code.kind = WRITE;
			ir->code.u.write.x = op1;
			break;
	}
	return ir;
}
///////////////////////////////////////////////print////////////////////////////////////////////////////
void print(struct node* root) 
{
	InterCodes irlist = translate_program(root);
	InterCodes curr = irlist;
	while(curr) {
		#ifdef IR_DEBUG
		//printf("curr: %p kind: %d\n", curr, curr->code.kind);
		#endif
		print_ir(curr);
		curr = curr->next;
	}
	return;
}
void print_op(Operand op) 
{
	switch(op->kind) {
		case VARIABLE:
			printf("v%d", op->u.var_no);
			break;
		case ADDRESS:
			break;
			//TODO();
		case LABEL:
			if(op->u.label_no > 0)
				printf("label%d", op->u.label_no);
			break;
		case FUNCTION:
			printf("%s", op->u.f_name);
			break;
		case TMP:
			printf("t%d", op->u.tmp_no);
			break;
		case IMM_NUMBER:
			printf("#%d", op->u.value_int);
			break;
		case ADDRESS_CONTENT:
			break;
			//TODO();
	}
	return;
}
void print_ir(InterCodes ir)
{
	if(!ir)
		return;
	if(ir->code.kind == D_LABEL) {
		Operand label = ir->code.u.label.x;
		if(!label)
			return;
		if(label->u.label_no == -1)
			return;
		printf("LABEL "); print_op(label); printf(" :\n");
	}
	else if(ir->code.kind == D_FUNCTION) {
		Operand func = ir->code.u.function.f;
		if(!func)
			return;
		printf("FUNCTION "); print_op(func); printf(" :\n");
	}
	else if(ir->code.kind == ASSIGN) {
		Operand x = ir->code.u.assign.x; Operand y = ir->code.u.assign.y;
		if(!x || !y)
			return;
		/*if(y->kind == IMM_NUMBER) {
			x->kind = IMM_NUMBER; x->u.value_int = y->u.value_int;
			return;
		}*/
		print_op(x); printf(" := "); print_op(y); printf("\n");
	}
	else if(ir->code.kind == ADD) {
		Operand x = ir->code.u.arithmetic.x;
		Operand y = ir->code.u.arithmetic.y;
		Operand z = ir->code.u.arithmetic.z;
		if(!x || !y || !z)
			return;
		print_op(x); printf(" := "); print_op(y); printf(" + "); print_op(z); printf("\n");
	}
	else if(ir->code.kind == SUB) {
		Operand x = ir->code.u.arithmetic.x;
		Operand y = ir->code.u.arithmetic.y;
		Operand z = ir->code.u.arithmetic.z;
		if(!x || !y || !z)
			return;
		print_op(x); printf(" := "); print_op(y); printf(" - "); print_op(z); printf("\n");
	}			
	else if(ir->code.kind == MUL) { 
		Operand x = ir->code.u.arithmetic.x;
		Operand y = ir->code.u.arithmetic.y;
		Operand z = ir->code.u.arithmetic.z;
		if(!x || !y || !z)
			return;
		print_op(x); printf(" := "); print_op(y); printf(" * "); print_op(z); printf("\n");
	}		
	else if(ir->code.kind == IR_DIV) {
		Operand x = ir->code.u.arithmetic.x;
		Operand y = ir->code.u.arithmetic.y;
		Operand z = ir->code.u.arithmetic.z;
		if(!x || !y || !z)
			return;
		print_op(x); printf(" := "); print_op(y); printf(" / "); print_op(z); printf("\n");
	}		
	else if(ir->code.kind == ASSIGN_ADDR) {
		//TODO();
	}
	else if(ir->code.kind == ADDR_ASSIGNED) {
		//TODO();
	}
	else if(ir->code.kind == JUMP) {
		Operand label = ir->code.u.jump.x;
		if(!label)
			return;
		InterCodes p = ir->prev;
		if(p->code.kind == RET) {
			label->u.label_no = -1;
			return;
		}
		//if(label->u.label_no >0) {
			printf("GOTO "); print_op(label); printf("\n");
		//}
		//else printf("\n");
	}
	else if(ir->code.kind == IF_JUMP) {
		Operand x = ir->code.u.if_jump.x;
		Operand y = ir->code.u.if_jump.y;
		Operand z = ir->code.u.if_jump.z;
		if(!x || !y || !z)
			return;
		printf("IF "); print_op(x); 
		switch(ir->code.u.if_jump.op) {
			case 0:	printf(" > "); break;
			case 1: printf(" < "); break;
			case 2: printf(" >= "); break;
			case 3: printf(" <= "); break;
			case 4: printf(" == "); break;
			case 5: printf(" != "); break;
		}
		//if(z->u.label_no > 0) {
			print_op(y); printf(" GOTO "); print_op(z); printf("\n");
		//}
		//else printf("\n");
	}
	else if(ir->code.kind == RET) {
		Operand x = ir->code.u.ret.x;
		if(!x)
			return;
		printf("RETURN "); print_op(x); printf("\n");
	}
	else if(ir->code.kind == DEC) {
		Operand x = ir->code.u.dec.x;
		int size = ir->code.u.dec.size;
		if(!x)
			return;
		printf("DEC "); print_op(x); printf(" %d\n", size);
	}
	else if(ir->code.kind == ARG) {
		Operand x = ir->code.u.arg.x;
		if(!x)
			return;
		printf("ARG "); print_op(x); printf("\n");
	}
	else if(ir->code.kind == CALL) {
		Operand x = ir->code.u.call.x;
		Operand f = ir->code.u.call.f;
		if(!x || !f)
			return;
		print_op(x); printf(" := CALL "); print_op(f); printf("\n");
	}
	else if(ir->code.kind == PARA) {
		Operand x = ir->code.u.para.x;
		if(!x)
			return;
		printf("PARAM "); print_op(x); printf("\n");
	}
	else if(ir->code.kind == READ) {
		Operand x = ir->code.u.read.x;
		if(!x)
			return;
		printf("READ "); print_op(x); printf("\n");
	}
	else if(ir->code.kind == WRITE) {
		Operand x = ir->code.u.write.x;
		if(!x)
			return;
		printf("WRITE "); print_op(x); printf("\n");
	}
	
	return;
}
/////////////////////////////////////////helper//////////////////////////////////////////////////////////
int get_array_size(Type t)
{
	if(t->kind == BASIC)
		return 4;
	int sub_size = get_array_size(t->u.array.elem);
	return sub_size*t->u.array.size;
}
int get_struct_size(Type t)
{
	int size = 0;
	FieldList curr = t->u.structure;
	while(curr) {
		switch(curr->type->kind) {
			case BASIC:
				size += 4;
				break;
			case ARRAY:
				size += get_array_size(curr->type);
				break;
			case STRUCTURE:
				size += get_struct_size(curr->type);
				break;
		}
		curr = curr->tail;
	}
	return size;
}
/////////////////////////////////////////////translate////////////////////////////////////////////////////////
InterCodes translate_program(struct node* program)
{
	InterCodes ir = translate_extdeflist(program->gchild[0]);
	
	return ir;
}
InterCodes translate_extdeflist(struct node* extdeflist)
{
	if(extdeflist->rule == Extdeflist_ExtdefExtdeflist) {
		InterCodes ir1 = translate_extdef(extdeflist->gchild[0]);
		InterCodes ir2 = translate_extdeflist(extdeflist->gchild[1]);
		
		InterCodes ir = concat(ir1, ir2);
		return ir;
	}
	else if(extdeflist->rule == Extdeflist_Null)
		return NULL;
}
InterCodes translate_extdef(struct node* extdef)
{
	if(extdef->rule == Extdef_SpecifierExtdeclistSemi || extdef->rule == Extdef_SpecifierSemi)
		return NULL;	//TODO()应该不用生成代码吧？？？？？
	else if(extdef->rule == Extdef_SpcifierFundecCompst) {
		InterCodes ir1 = translate_funcdec(extdef->gchild[1]);
		InterCodes ir2 = translate_compst(extdef->gchild[2]);
		
		/*printf("\nthis is compst:::::::::::\n");
		InterCodes curr = ir2;
		while(curr) {
			print_ir(curr);
			curr = curr->next;
		}
		printf("\n");*/
		InterCodes ir = concat(ir1, ir2);
		return ir;
	}	
}
InterCodes translate_funcdec(struct node* funcdec)
{
	if(funcdec->rule == Fundec_IdLpVarlistRp) {
		
		Operand func;
		struct node* id = funcdec->gchild[0];
		//func = find_op(id->str);
		//if(func == NULL)
		func = new_Operand(id, FUNCTION, -1, -1);
		InterCodes ir1 = new_InterCodes(func, NULL, NULL, D_FUNCTION, -1);
		InterCodes ir2 = translate_varlist(funcdec->gchild[2]);
		
		InterCodes ir = concat(ir1, ir2);
		/*InterCodes curr = ir;
		printf("\nthis is funcdec\n");
		while(curr) {
			print_ir(curr);
			curr = curr->next;
		}
		printf("\n");*/
		return ir;
	}
	else if(funcdec->rule == Fundec_IdLpRp) {
		Operand func;
		struct node* id = funcdec->gchild[0];
		//func = find_op(id->str);
		//if(!func)
		func = new_Operand(id, FUNCTION, -1, -1);
		InterCodes ir = new_InterCodes(func, NULL, NULL, D_FUNCTION, -1);
		return ir;
	}
}
InterCodes translate_varlist(struct node* varlist)
{
	if(varlist->rule == Varlist_ParamdecCommaVarlist) {	
		InterCodes ir1 = translate_paradec(varlist->gchild[0]);
		InterCodes ir2 = translate_varlist(varlist->gchild[2]);
			
		InterCodes ir = concat(ir1, ir2);
		return ir;
	}
	else if(varlist->rule == Varlist_Paramdec) {
		InterCodes ir = translate_paradec(varlist->gchild[0]);
		return ir;
	}
}
InterCodes translate_paradec(struct node* paradec)
{
	struct node* vardec = paradec->gchild[1];
	Operand para;
	para = find_op(vardec->str);
	if(!para)
		para = new_Operand(vardec, VARIABLE, -1, -1);
	InterCodes ir = new_InterCodes(para, NULL, NULL, PARA, -1);
	return ir;
}
InterCodes translate_compst(struct node* compst)
{
	//Compst_LcDeflistStmtlistRc
	InterCodes ir1 = translate_deflist(compst->gchild[1]);
	InterCodes ir2 = translate_stmtlist(compst->gchild[2]);

	InterCodes ir = concat(ir1, ir2);
	return ir;
}
InterCodes translate_deflist(struct node* deflist)
{
	if(deflist->rule == Deflist_DefDeflist) {
		InterCodes ir1 = translate_def(deflist->gchild[0]);
		InterCodes ir2 = translate_deflist(deflist->gchild[1]);
		
		InterCodes ir = concat(ir1, ir2);
		return ir;
	}
	else if(deflist->rule == Deflist_Null)
		return NULL;
}
InterCodes translate_def(struct node* def)
{
	Type specifier = def->gchild[0]->type;
	InterCodes ir = translate_declist(def->gchild[1], specifier);
}
InterCodes translate_declist(struct node* declist, Type specifier)
{
	if(declist->rule == Declist_Dec) {
		InterCodes ir = translate_dec(declist->gchild[0], specifier);
		return ir;
	}
	else if(declist->rule == Declist_DecCommaDeclist) {
			InterCodes ir1 = translate_dec(declist->gchild[0], specifier);
			InterCodes ir2 = translate_declist(declist->gchild[2], specifier);
			
			InterCodes ir = concat(ir1, ir2);
			return ir;
	}
}
InterCodes translate_dec(struct node* dec, Type specifier)
{
	if(dec->rule == Dec_Vardec) {
		struct node* vardec = dec->gchild[0];
		if(vardec->type->kind == BASIC) {
			//printf("!!!!!not need to dec!!!!!\n");
			Operand v = new_Operand(vardec, VARIABLE, -1, -1);
			return NULL;
		}
		else if(vardec->type->kind == ARRAY) {
			Symbol sym = find_symbol(vardec->str);
			Type t = sym->type;
			int size = get_array_size(t);
			Operand v = new_Operand(NULL, VARIABLE, -1, -1);
			InterCodes ir = new_InterCodes(v, NULL, NULL, DEC, size);
			return ir;
		}
		else if(vardec->type->kind == STRUCTURE) {
			Symbol sym = find_symbol(vardec->str);
			Type t = sym->type;
			int size = get_struct_size(t);
			Operand v = new_Operand(NULL, VARIABLE, -1, -1);
			InterCodes ir = new_InterCodes(v, NULL, NULL, DEC, size);
			return ir;
		}
	}
	else if(dec->rule == Dec_VardecAssignopExp) {
		Operand v = new_Operand(dec->gchild[0], VARIABLE, -1, -1);
		Operand t1 = new_temp();
		InterCodes ir1 = translate_exp(dec->gchild[2], t1);
		InterCodes ir2 = new_InterCodes(v, t1, NULL, ASSIGN, -1);
		//printf("in vardecassign v: no: %d name: %s\n", v->u.var_no, v->v_name);
		InterCodes ir = concat(ir1, ir2);
		return ir;
	}
}
InterCodes translate_stmtlist(struct node* stmtlist)
{
	if(stmtlist->rule == Stmtlist_StmtStmtlist) {
		InterCodes ir1 = translate_stmt(stmtlist->gchild[0]);
		InterCodes ir2 = translate_stmtlist(stmtlist->gchild[1]);
		 
		InterCodes ir = concat(ir1, ir2);
		return ir;
	}
	else if(stmtlist->rule == Stmtlist_Null) {
		return NULL;
	}
}

InterCodes translate_stmt(struct node* stmt)
{
	//printf("stmt->rule: %d\n", stmt->rule);
	if(stmt->rule == Stmt_ExpSemi) {
		Operand t1 = new_temp();
		InterCodes ir = translate_exp(stmt->gchild[0], t1); 
		return ir;
	}
	else if(stmt->rule == Stmt_Compst) {
		InterCodes ir = translate_compst(stmt->gchild[0]);
		return ir;
	}
	else if(stmt->rule == Stmt_ReturnExpSemi) {	
		Operand t1 = new_temp();
		InterCodes ir1 = translate_exp(stmt->gchild[1], t1);
		InterCodes ir2 = new_InterCodes(t1, NULL, NULL, RET, -1);
		
		InterCodes ir = concat(ir1, ir2);
		return ir;
	}
	else if(stmt->rule == Stmt_IfLpExpRpStmt) {
		Operand label1 = (Operand)malloc(sizeof(struct Operand_));	//b.true = fall
		label1->kind = LABEL; label1->u.label_no = -1;	
		Operand label2 = new_label();
		
		InterCodes ir1 = translate_cond(stmt->gchild[2], label1, label2);	//b.code
		//InterCodes label1_code = new_InterCodes(label1, NULL, NULL, D_LABEL, -1);
		InterCodes ir2 = translate_stmt(stmt->gchild[4]);
		InterCodes label2_code = new_InterCodes(label2, NULL, NULL, D_LABEL, -1);
		//InterCodes ir = concat(ir1, label1_code);
		InterCodes ir = concat(ir1, ir2);
		ir = concat(ir, label2_code);
		return ir;
	}
	else if(stmt->rule == Stmt_IfLpExpRpStmtElseStmt) {
		printf("\nhahahaha\n");
		Operand label1 = (Operand)malloc(sizeof(struct Operand_));
		label1->kind = LABEL; label1->u.label_no = -1;	//b.true = fall;
		Operand label2 = new_label();
		Operand label3 = NULL;
		if(stmt->gchild[4]->rule != 27)
			label3 = new_label();
		
		InterCodes goto3_code = NULL;
		InterCodes label3_code = NULL;
		//printf("label trueeeeeee: %d\n", label1->u.label_no);
		InterCodes ir1 = translate_cond(stmt->gchild[2], label1, label2); 	//b.code 
		//InterCodes label1_code = new_InterCodes(label1, NULL, NULL, D_LABEL, -1);
		InterCodes ir2 = translate_stmt(stmt->gchild[4]);	//s1.code
		if(label3)
			goto3_code = new_InterCodes(label3, NULL, NULL, JUMP, -1);	//s1.next
		InterCodes label2_code = new_InterCodes(label2, NULL, NULL, D_LABEL, -1);	//label(b.false)
		InterCodes ir3 = translate_stmt(stmt->gchild[6]);	//s2.code
		if(label3)
			label3_code = new_InterCodes(label3, NULL, NULL, D_LABEL, -1);
		
		//InterCodes ir = concat(ir1, label1_code);
		InterCodes ir = concat(ir1, ir2);
		if(goto3_code)
			ir = concat(ir, goto3_code);
		ir = concat(ir, label2_code);
		ir = concat(ir, ir3);
		if(label3_code)
			ir = concat(ir, label3_code);
		printf("\n");
		return ir;
	}
	else if(stmt->rule == Stmt_WhileLpExpRpStmt) {
		Operand label1 = new_label();
		Operand label2 = (Operand)malloc(sizeof(struct Operand_));//B.true = fall;
		label2->kind = LABEL; label2->u.label_no = -1; 
		Operand label3 = NULL;	//false = s.next
		
		if(stmt->gchild[4]->rule != 27)		//要不要考虑return情况呢
			label3 = new_label();
		
		InterCodes label1_code = new_InterCodes(label1, NULL, NULL, D_LABEL, -1);	//label(begin)
		InterCodes ir1 = translate_cond(stmt->gchild[2], label2, label3);	//b.code
		//InterCodes label2_code = new_InterCodes(label2, NULL, NULL, D_LABEL, -1);
		InterCodes ir2 = translate_stmt(stmt->gchild[4]);	//s1.code
		InterCodes goto1_code = new_InterCodes(label1, NULL, NULL, JUMP, -1);	//goto begin
		InterCodes label3_code = NULL;
		if(label3)
			label3_code = new_InterCodes(label3, NULL, NULL, D_LABEL, -1);
		
		//printf("label1_code: %p, ir1: %p label2_code: %p ir2: %p goto1_code: %p label3_code: %p\n", label1_code, ir1, label2_code, ir2, goto1_code, label3_code);
		InterCodes ir = concat(label1_code, ir1);
		//ir = concat(ir, label2_code);
		ir = concat(ir, ir2);
		ir = concat(ir, goto1_code);
		if(label3)
			ir = concat(ir, label3_code);
		return ir;
	}
}
int get_relop(struct node* gnode)
{
	int ret = -1;
	if(!strcmp(gnode->relop, ">"))
		ret = 0;
	else if(!strcmp(gnode->relop, "<"))
		ret = 1;
	else if(!strcmp(gnode->relop, ">="))
		ret = 2;
	else if(!strcmp(gnode->relop, "<="))
		ret = 3;
	else if(!strcmp(gnode->relop, "=="))
		ret = 4;
	else if(!strcmp(gnode->relop, "!="))
		ret = 5;
	else 
		printf("get relop fault!!!!!!!\n");
	return ret;
}
InterCodes translate_cond(struct node* exp, Operand label_true, Operand label_false)
{
	if(exp->rule == Exp_NotExp) {
		printf("this is expnotexp label_true: %d label_false: %d rule: %d\n", label_true->u.label_no, label_false->u.label_no, exp->gchild[1]->rule);
		InterCodes ir = translate_cond(exp->gchild[1], label_false, label_true);
		return ir;
	}
	else if(exp->rule == Exp_LpExpRp) {
		InterCodes ir = translate_cond(exp->gchild[1], label_true, label_false);
		return ir;
	}
	else if(exp->rule == Exp_ExpAndExp) {
		printf("this is expandexp\n");
		Operand label_b1T = NULL; Operand label_b1F = NULL;
		Operand label_b2T = NULL; Operand label_b2F = NULL;
		InterCodes ir1 = NULL; InterCodes ir2 = NULL; InterCodes label_code = NULL;
		
		label_b1T = (Operand)malloc(sizeof(struct Operand_));
		label_b1T->kind = LABEL; label_b1T->u.label_no = -1;	//b1.true = fall
		if(label_false->u.label_no != -1)
			label_b1F = label_false;
		else
			label_b1F = new_label();
		label_b2T = label_true;
		label_b2F = label_false;
		
		printf("in expandexp label1T: %d label1F: %d\n", label_b1T->u.label_no, label_b1F->u.label_no);
		ir1 = translate_cond(exp->gchild[0], label_b1T, label_b1F);	
		printf("in expandexp ir1: \n");
		InterCodes curr = ir1;
		while(curr) {
			print_ir(curr); curr = curr->next;
		}
		printf("in expandexp label2T: %d label2F: %d\n", label_b2T->u.label_no, label_b2F->u.label_no);
		ir2 = translate_cond(exp->gchild[2], label_b2T, label_b2F);
		printf("in expandexp ir2: \n");
		curr = ir2;
		while(curr) {
			print_ir(curr); curr = curr->next;
		}
		//if(label_false->u.label_no == -1)
		if(label_b1F->u.label_no != -1 && label_b1F->u.label_no != label_b2F->u.label_no)
			label_code = new_InterCodes(label_b1F, NULL, NULL, D_LABEL, -1);
		InterCodes ir = concat(ir1, ir2); printf("\n");
		ir = concat(ir, label_code);
		return ir;
	}
	else if(exp->rule == Exp_ExpOrExp) {
		printf("this is exporexp label true: %d label false: %d\n", label_true->u.label_no, label_false->u.label_no);
		Operand label_b1T = NULL; Operand label_b1F = NULL;
		Operand label_b2T = NULL; Operand label_b2F = NULL;
		InterCodes ir1 = NULL; InterCodes label_code = NULL; InterCodes ir2 = NULL;
		
		if(label_true->u.label_no != -1)
			label_b1T = label_true;
		else
			label_b1T = new_label();
		label_b1F = (Operand)malloc(sizeof(struct Operand_));
		label_b1F->kind = LABEL; label_b1F->u.label_no = -1;	//b1.false = fall;
		label_b2T = label_true; label_b2F = label_false;
		
		printf("in exporexp label_b1T: no: %d\n", label_b1T->u.label_no);
		ir1 = translate_cond(exp->gchild[0], label_b1T, label_b1F);	
		printf("in exporexp label_b2T: no: %d b2F: %d\n", label_b2T->u.label_no, label_b2F->u.label_no);
		ir2 = translate_cond(exp->gchild[2], label_b2T, label_b2F);
		if(label_b1T->u.label_no != -1 && label_b2T->u.label_no != label_b1T->u.label_no) {	//不知道这样改对不对
			label_code = new_InterCodes(label_b1T, NULL, NULL, D_LABEL, -1);
		}
		InterCodes ir = concat(ir1, ir2);
		ir = concat(ir, label_code);
		printf("\n");
		return ir;
	}
	else if(exp->rule == Exp_ExpRelopExp) {
		Operand t1 = new_temp(), t2 = new_temp();
		struct node* exp1 = exp->gchild[0];
		struct node* exp2 = exp->gchild[2];
		InterCodes ir3 = NULL; InterCodes ir4 = NULL;

		InterCodes ir1 = translate_exp(exp1, t1);	//E1
		InterCodes ir2 = translate_exp(exp2, t2);	//E2
		int op = get_relop(exp->gchild[1]);
		if(label_true->u.label_no != -1 && label_false->u.label_no != -1) {
			ir3 = new_InterCodes(t1, t2, label_true, IF_JUMP, op);
			ir4 = new_InterCodes(label_false, NULL, NULL, JUMP, -1);
		}
		else if(label_true->u.label_no != -1) {
			ir3 = new_InterCodes(t1, t2, label_true, IF_JUMP, op);
		}
		else if(label_false->u.label_no != -1) {
			switch(op) {
				case 0: op = 1; break;
				case 1: op = 0; break;
				case 2: op = 3; break;
				case 3: op = 2; break;
				case 4: op = 5; break;
				case 5: op = 4; break;
			}
			ir3 = new_InterCodes(t1, t2, label_false, IF_JUMP, op);
		}
		
		InterCodes ir = concat(ir1, ir2);
		ir = concat(ir, ir3);
		ir = concat(ir, ir4);
		return ir;
	}
	else {
		Operand t1 = new_temp();
		InterCodes ir2 = NULL;
		InterCodes label_code = NULL;
		InterCodes ir1 = translate_exp(exp, t1);
		int op = 5;
		if(label_true->u.label_no != -1) {
			ir2 = new_InterCodes(t1, imm_num0, label_true, IF_JUMP, op);  
			printf("in default label_true not -1\n");print_ir(ir2);printf("endlala\n");
			if(label_false->u.label_no != -1) {
				label_code = new_InterCodes(label_false, NULL, NULL, JUMP, -1);
			}
		}
		else if(label_false->u.label_no != -1){	//应该不会两个都fall吧
			op = 4;
			ir2 = new_InterCodes(t1, imm_num0, label_false, IF_JUMP, op);
		}
		//InterCodes label_code = new_InterCodes(label_false, NULL, NULL, JUMP, -1); 
		printf("in default print label_code\n"); print_ir(label_code);printf("endxixixixi\n");
		
		InterCodes ir = concat(ir1, ir2);
		ir = concat(ir, label_code);
		return ir;
	}
}
InterCodes translate_exp(struct node* exp, Operand place)
{
	//printf("exp rule: %d\n", exp->rule);
	if(exp->rule == Exp_ExpAssignopExp)	{
		//要不要判断已经存在的变量节约空间？？？？？？？？？？好像要的
		struct node* exp1 = exp->gchild[0];
		struct node* exp2 = exp->gchild[2];
		Operand variable = NULL;
		InterCodes ir2_1 = NULL;
		InterCodes ir2_2 = NULL;
		int is_exist = 0;
		//先暂时不考虑数组和结构体了
		if(exp1->rule ==  Exp_Id) {
			variable = find_op(exp1->str);
			if(variable) {
				is_exist = 1;
				Operand curr = ophead;
				while(curr) {
					if(curr->kind == TMP && curr->u.tmp_no == place->u.tmp_no)
						break;
					curr = curr->next;
				}
				while(curr) {
					if(curr->kind == TMP)
						curr->u.tmp_no--;
					curr = curr->next;
				}
				place->kind = variable->kind; place->u.var_no = variable->u.var_no; strcpy(place->v_name, variable->v_name);
				temp_cnt--;
			}
		}
		if(!variable)
			variable = new_Operand(exp1, VARIABLE, -1, -1);
		//Operand t1 = new_temp();
		InterCodes ir1 = translate_exp(exp2, variable);
		
		if(!is_exist) {
			Operand t1 = new_temp();
			ir2_1 = new_InterCodes(variable, t1, NULL, ASSIGN, -1);
			ir2_2 = new_InterCodes(place, variable, NULL, ASSIGN, -1);
		}
		//printf("in assignop ir1: %p ir2: %p ir2_2: %p\n", ir1, ir2_1, ir2_2); print_ir(ir1); print_ir(ir2_1); print_ir(ir2_2);
		InterCodes ir2 = concat(ir2_1, ir2_2);
		InterCodes ir = concat(ir1, ir2);
		
		return ir;
	}
	else if(exp->rule == Exp_NotExp || 
		exp->rule == Exp_ExpAndExp || 
		exp->rule == Exp_ExpOrExp || 
		exp->rule == Exp_ExpRelopExp) {	
		Operand label1 = new_label();
		Operand label2 = new_label();
		InterCodes ir0 = new_InterCodes(place, imm_num0, NULL, ASSIGN, -1);
		InterCodes ir1 = translate_cond(exp, label1, label2);
		InterCodes ir2_1 = new_InterCodes(label1, NULL, NULL, D_LABEL, -1);
		InterCodes ir2_2 = new_InterCodes(place, imm_num1, NULL, ASSIGN, -1);
		InterCodes ir3 = new_InterCodes(label2, NULL, NULL, D_LABEL, -1);
		//printf("\nin relpppppppppppppp\n");
		//print_ir(ir0); print_ir(ir1); print_ir(ir2_1); print_ir(ir2_2); print_ir(ir3);
		//printf("\n");
		InterCodes ir = concat(ir0, ir1);
		ir = concat(ir, ir2_1);
		ir = concat(ir, ir2_2);
		ir = concat(ir, ir3);
		return ir;
	}
	else if(exp->rule == Exp_ExpPlusExp) {
		Operand t1 = new_temp();
		Operand t2 = new_temp();
		
		/*Operand t1 = NULL;
		Operand t2 = NULL;
		struct node* exp1 = exp->gchild[0];
		struct node* exp2 = exp->gchild[2];
		
		if(exp1->rule ==  Exp_Id)
			t1 = find_op(exp1->str);
		if(exp2->rule == Exp_Id)
			t2 = find_op(exp2->str);
		if(!t1) t1 = new_temp();
		if(!t2) t2 = new_temp();*/
		InterCodes ir1 = translate_exp(exp->gchild[0], t1);
		InterCodes ir2 = translate_exp(exp->gchild[2], t2);
		InterCodes ir3 = new_InterCodes(place, t1, t2, ADD, -1);
		
		InterCodes ir = concat(ir1, ir2);
		ir = concat(ir, ir3);
		return ir;
	}
	else if(exp->rule == Exp_ExpMinusExp) {
		Operand t1 = new_temp();
		Operand t2 = new_temp();
		
		InterCodes ir1 = translate_exp(exp->gchild[0], t1);
		InterCodes ir2 = translate_exp(exp->gchild[2], t2);
		InterCodes ir3 = new_InterCodes(place, t1, t2, SUB, -1);
		
		InterCodes ir = concat(ir1, ir2);
		ir = concat(ir, ir3);
		return ir;
	}
	else if(exp->rule == Exp_ExpStarExp) {
		Operand t1 = new_temp();
		Operand t2 = new_temp();
		InterCodes ir1 = translate_exp(exp->gchild[0], t1);
		InterCodes ir2 = translate_exp(exp->gchild[2], t2);
		InterCodes ir3 = new_InterCodes(place, t1, t2, MUL, -1);
		
		InterCodes irr = concat(ir1, ir2);
		InterCodes ir = concat(irr, ir3);
		
		return ir;
	}
	else if(exp->rule == Exp_ExpDivExp) {
		Operand t1 = new_temp();
		Operand t2 = new_temp();
		//printf("in expdivexppppppppppppp: \n");
		InterCodes ir1 = translate_exp(exp->gchild[0], t1);
		InterCodes ir2 = translate_exp(exp->gchild[2], t2);
		InterCodes ir3 = new_InterCodes(place, t1, t2, IR_DIV, -1);
		InterCodes ir = concat(ir1, ir2);
		ir = concat(ir, ir3);
		//printf("left divvvvvvvvvvvv\n");
		return ir;
	}
	else if(exp->rule == Exp_LpExpRp) {
		//TODO!!!!!!!!!!还不知道对不对
		InterCodes ir = translate_exp(exp->gchild[1], place);
		return ir;
	}
	else if(exp->rule == Exp_MinusExp) {
		Operand t1 = new_temp();
		InterCodes ir1 = translate_exp(exp->gchild[1], t1);
		InterCodes ir2 = new_InterCodes(place, imm_num0, t1, SUB, -1);
		
		InterCodes ir = concat(ir1, ir2);
		return ir;
	}
	else if(exp->rule == Exp_IdLpArgsRp) {
		char* name = exp->str;
		//printf("func call name: %s\n", name);
		Operand* arg_list = (Operand*)malloc(sizeof(Operand)*MAX_ARGC);
		int arg_cnt = 0;
		InterCodes ir1 = translate_args(exp->gchild[2], arg_list, &arg_cnt);
		if(!strcmp(name, "write")) {
			InterCodes write_code = new_InterCodes(arg_list[0], NULL, NULL, WRITE, -1);

			InterCodes ir = concat(ir1, write_code);
			return ir;
		}
		InterCodes ir2 = (InterCodes)malloc(sizeof(struct InterCodes_));
		for(int i = arg_cnt-1; i>=0; i--) {	//反着压参数
			InterCodes ir_tmp = new_InterCodes(arg_list[i], NULL, NULL, ARG, -1);	
			InterCodes curr = ir2;
			while(curr->next)
				curr = curr->next;
			curr->next = ir_tmp; ir_tmp->prev = curr;		
		}
		Operand f = new_Operand(exp->gchild[0], FUNCTION, -1, -1);
		InterCodes call_f = new_InterCodes(place, f, NULL, CALL, -1);
		
		InterCodes curr = ir1;
		if(ir1) {
			while(curr->next)
				curr = curr->next;
		}
		if(ir1 && ir2) {
			curr->next = ir2->next; 
			ir2->next->prev = ir1;
		}
		/*curr = ir1;
		while(curr->next)
			curr = curr->next;
		curr->next = call_f; call_f->prev = curr;*/
		//free(ir2); 在这里free别的地方就出事了！
		//ir2 = NULL;
		if(ir1) {
			InterCodes ir = concat(ir1, call_f);
			return ir1;
		}
		else if(!ir1) {
			if(ir2->next) {
				InterCodes ir = concat(ir2->next, call_f);
				return ir;
			}
			else {
				return call_f;
			}
		}
		//TODO()??????
	}
	else if(exp->rule == Exp_IdLpRp) {
		char* name = exp->str;
		if(!strcmp(name, "read"))
			return new_InterCodes(place, NULL, NULL, READ, -1);
		Operand function = new_Operand(exp, FUNCTION, -1, -1);
		InterCodes ir = new_InterCodes(place, function, NULL, CALL, -1);

		return ir;
	}
	else if(exp->rule == Exp_ExpLbExpRb) {	
		//TODO();
	}
	else if(exp->rule == Exp_ExpDotId) {
		//TODO();
	}
	else if(exp->rule == Exp_Id) {
		char* name = exp->str;
		//printf("in exp id name: %s\n", name);
		Operand id;
		id = find_op(name);//TODO TODO TODO TODO TODO TODO TODO !!!!!!!!!!!!!!!!!!
		if(id) {
			Operand curr = ophead;
			while(curr) {
				if(curr->kind == TMP && curr->u.tmp_no == place->u.tmp_no)
					break;
				curr = curr->next;
			}
			while(curr) {
				if(curr->kind == TMP)
					curr->u.tmp_no--;
				curr = curr->next;
			}
			temp_cnt--;
			place->kind = id->kind;	//不能直接指，只能改,不清楚怎么释放，好浪费内存啊
			place->u.var_no = id->u.var_no;
			strcpy(place->v_name, id->v_name);
			
			
			return NULL;
		}
		else {
			id = new_Operand(exp->gchild[0], VARIABLE, -1, 0);
			
			InterCodes ir = new_InterCodes(place, id, NULL, ASSIGN, -1);
			return ir;
		}
	}
	else if(exp->rule == Exp_Int) {
		int val = exp->type_int;
		Operand value = new_Operand(exp, IMM_NUMBER, -1, 0);
		if(place->kind != TMP) {
			InterCodes ir = new_InterCodes(place, value, NULL, ASSIGN, -1);
			return ir;	
		}
		else {
			//把这个tmp后面所有tmp的no都前进一位
			Operand curr = ophead;
			while(curr) {
				if(curr->kind == TMP && curr->u.tmp_no == place->u.tmp_no)
					break;
				curr = curr->next;
			}
			while(curr) {
				if(curr->kind == TMP)
					curr->u.tmp_no--;
				curr = curr->next;
			}
			temp_cnt--;
			place->kind = IMM_NUMBER;
			place->u.value_int = val;
			
			return NULL;
		}	
	}
	else if(exp->rule == Exp_Float) {	//will not be use
		float val = exp->type_float;
		Operand value = new_Operand(exp, IMM_NUMBER, -1, 1);
		
		InterCodes ir = new_InterCodes(place, value, NULL, ASSIGN, -1);
		return ir;
	}
}
InterCodes translate_args(struct node* args, Operand* arg_list, int* arg_cnt)
{
	if(args->rule == Args_ExpCommaArgs)	{	
		Operand t1 = new_temp();
		InterCodes ir1 = translate_exp(args->gchild[0], t1);
		arg_list[*arg_cnt] = t1;
		*arg_cnt = *arg_cnt + 1;
		InterCodes ir2 = translate_args(args->gchild[2], arg_list, arg_cnt); 
		
		InterCodes ir = concat(ir1, ir2);
		return ir1;
	}
	else if(args->rule == Args_Exp)	{
		Operand t1 = new_temp();
		InterCodes ir1 = translate_exp(args->gchild[0], t1);
		arg_list[*arg_cnt] = t1;
		*arg_cnt = *arg_cnt + 1;
		return ir1;
	}
}


