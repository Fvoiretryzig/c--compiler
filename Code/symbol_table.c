#include "symbol_table.h"


Symbol head;
SymbolF headF;
void init_table() 
{
	head = (Symbol)malloc(sizeof(struct Symbol_));
	if(head == NULL) {
		printf("\033[47;31mERROR when malloc head\033[0m\n");
		return; 
	}
	head->next = NULL;
	
	headF = (SymbolF)malloc(sizeof(struct SymbolF_));
	if(headF == NULL) {
		printf("\033[47;31mERROR when malloc headF\033[0m\n");
		return;
	}
	headF->next = NULL;
	
	printf("\033[46;37mmalloc head and headF successful!!\033[0m\n");
	return;
}

int add_symbol(struct node* n, char* name) 
{
	Symbol new_sym = (Symbol)malloc(sizeof(struct Symbol_));
	if(new_sym == NULL) {
		printf("\033[47;31mERROR when malloc a new symbol\033[0m\n");
		return 1;
	}
	printf("\033[46;37min addsymbol name: %s type: %p\033[0m\n", name, n->type);
	switch(n->n_type) {
		case _VAR_ :	
			new_sym->idkind = _VAR;
			new_sym->type = n->type;
			break;
		case _STRUCTURE_ :
			new_sym->idkind = _STRUCT;
			new_sym->type = n->type;
			break;
		case _FUNC_:
			free(new_sym);
			return 0;
			break;
	}
	strcpy(new_sym->name, name);
	new_sym->next = NULL;
	Symbol curr = head;
	while(curr->next != NULL) {
		 curr = curr->next;
	}
	curr->next = new_sym;
	return 0;
}
int add_symbolF(struct node* n, char* name) {
	SymbolF new_sym = (SymbolF)malloc(sizeof(struct SymbolF_));
	if(new_sym == NULL) {
		printf("\033[47;31mERROR when malloc a new symbolF\033[0m\n");
		return 1;
	}
	new_sym->retType = n->func.retType;
	new_sym->argc = n->func.argc;
	new_sym->argv = n->func.argv;
	strcpy(new_sym->name, name);
	new_sym->next = NULL;
	
	
	SymbolF curr = headF;
	while(curr->next != NULL) {
		curr = curr->next;
	}
	
	curr->next = new_sym;
	return 0;
}
Symbol find_symbol(char* name) {
	printf("\033[46;37min findsymbol name: %s\033[0m\n",name);
	Symbol curr = head;
	int if_find = 0;
	while(curr) {
		if(!strcmp(curr->name, name)) {
			if_find = 1;
			break;
		}
		curr = curr->next;
	}
	if(!if_find) {
		printf("\033[46;37m%s not in symbol table!!\033[0m\n", name);
		return NULL;
	}
	printf("\033[46;37m%s find in symbol table!!\033[0m\n", name);
	return curr;
}
SymbolF find_symbolF(char* name) {
	printf("\033[46;37mthis is find_symbolF\033[0m\n");
	SymbolF curr = headF;
	int if_find = 0;
	while(curr) {
		if(!strcmp(curr->name, name)) {
			if_find = 1;
			break;
		}
		curr = curr->next;
	}
	if(!if_find) {
		printf("\033[46;37m%s not in symbolF table!!\033[0m\n", name);
		return NULL;
	}
	printf("\033[46;37m%s find in symbolF table!!\033[0m\n", name);
	return curr;
}
