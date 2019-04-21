#include <symbol_table.h>


Symbol* head;
SymbolF* headF;
void init_table()
{
	head = (Symbol*)malloc(sizeof(Symbol));
	if(head == NULL) {
		printf("ERROR when malloc head\n");
		return; 
	}
	head->next = NULL;
	
	headF = (SymbolF*)malloc(siezof(SymbolF));
	if(headF == NULL) {
		printf("ERROR when malloc headF\n");
		return;
	}
	headF->next = NULL;
	
	printf("malloc head and headF successful!!\n");
	return;
}

int add_symbol(struct node* n, char* name) {
	Symbol* new_sym = (Symbol*)malloc(sizeof(Symbol));
	if(new_sym == NULL) {
		printf("ERROR when malloc a new symbol\n");
		return 1;
	}
	switch(node->n_type) {
		case _BASIC_ :
			new_sym->idkind = BASIC;
			new_sym->u.type = n->u.type;
			break;
		case _ARRAY_ :
			new_sym->idkind = ARRAY;
			new_sym->u.type = n->u.type;
			break;
		case _STRUCTURE_ :
			new_sym->idkind = STRUCTURE;
			new_sym->u.type = n->u.type;
			break;
	}
	strcpy(new_sym->name, name);
	new_sym->next = NULL;
	Symbol* curr = head;
	while(curr->next != NULL) {
		 curr = curr->next;
	}
	curr->next = new_sym;
	return 0;
}
int add_symbolF(struct node* n, char* name) {
	SymbolF* new_sym = (SymbolF*)malloc(sizeof(SymbolF));
	if(new_sym == NULL) {
		printf("ERROR when malloc a new symbolF\n");
		return 1;
	}
	new_sym->retType = n->u.retType;
	new_sym->argc = n->u.argc;
	new_sym->argv = n->u.argv;
	strcpy(new_sym->name, name);
	new_sym->next = NULL;
	
	SymbolF* curr = headF;
	while(curr->next != NULL) {
		curr = curr->next;
	}
	curr->next = new_sym;
	return 0;
}
Symbol* find_symbol(char* name) {
	Symbol* curr = head;
	int if_find = 0;
	while(curr) {
		if(!strcmp(curr->name, name)) {
			if_find = 1;
			break;
		}
		curr = curr->next;
	}
	if(!if_find) {
		print("%s not in symbol table!!\n", name);
		return NULL;
	}
	printf("%s find in symbol table!!\n", name);
	return curr;
}
