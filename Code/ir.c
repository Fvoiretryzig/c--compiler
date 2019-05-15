#include "ir.h"
#include <stdlib.h>

#define IR_DEBUG
InterCodes IRhead;

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
int insert_ircode(InterCodes ir_code)
{
	InterCodes curr = IRhead;
	while(curr->next != NULL)
		curr = curr->next;
	curr->next = ir_code;
	ir_code->prev = curr;
	ir_code->next = NULL;
	
	return;
}
void print_ir(InterCodes ir_list) 
{
	//TODO();
}
