#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "syntax.tab.h"
#include "gtree.h"

#define SYMBOL_TABLE_H
#ifdef SYMBOL_TABLE_H

typedef enum {_VAR, _STRUCT} IDkind;

typedef struct Symbol_* Symbol;
typedef struct SymbolF_* SymbolF;
struct Symbol_ {
	IDkind idkind;
	char name[55];
	Type type;	
	
	Symbol next;
};
struct SymbolF_ {
	char name[55];
	Type retType;
	int argc;
	Type* argv;
	
	SymbolF next;
};

void init_table();
int add_symbol(struct node* n, char* name);
int add_symbolF(struct node* n, char* name);
Symbol find_symbol(char* name);
SymbolF find_symbolF(char* name);


#endif
