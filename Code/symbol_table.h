#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "syntax.tab.h"
#include "gtree.h"

typedef struct Type_* Type;
typedef struct FieldList_* FieldList;
typedef enum idkind {_VAR, _STRUCT} IDKind;
struct Type_ {
	enum { BASIC, ARRAY, STRUCTURE } kind;
	union {
		// 基本类型
		int basic;	//int = 1; float = 0
		// 数组类型信息包括元素类型与数组大小构成
		struct { 
			Type elem; int size; 
		} array;
		// 结构体类型信息是一个链表
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
} Symbol;
typedef struct SymbolEntityFunc_ {
	char name[55];
	Type retType;
	int argc;
	Type* argv;
} SymbolF;
void init_table();
int add_symbol(struct node n);
Symbol* find_symbol(char* name);

