#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "syntax.tab.h"
#include "gtree.h"

#define SYMBOL_TABLE_H
#ifdef SYMBOL_TABLE_H
typedef struct Type_* Type;
typedef struct FieldList_* FieldList;
typedef enum idkind {_VAR, _STRUCT} IDKind;

struct Type_ {
	enum { BASIC, ARRAY, STRUCTURE } kind;
	union {
		int basic;	//int = 1; float = 0
		struct { 
			Type elem; int size; 
		} array;
		FieldList structure;
	} u;
};
struct FieldList_ {
	char name[55]; // 域的名字
	Type type; // 域的类型
	FieldList tail; // 下一个域
};

typedef struct SymbolEntity_ {
	IDkind idkind;
	char name[55];
	Type type;	
	
	int is_left;
	
	Symbol* next;
} Symbol;
typedef struct SymbolEntityFunc_ {
	char name[55];
	Type retType;
	int argc;
	Type* argv;
	
	SymbolF* next;
} SymbolF;

void init_table();
int add_symbol(struct node* n, char* name);
int add_symbolF(struct node* n, char* name);
Symbol* find_symbol(char* name);
SymbolF* find_symbolF(char* name)
#endif
