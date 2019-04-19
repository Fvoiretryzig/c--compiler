#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include "syntax.tab.h"

struct node {
	char name[20];
	int lineno;
	union {
		char str[53];
		int type_int;
		float type_float;
	};
	//struct node* gparent;
	int child_cnt;
	struct node* gchild[10];
};
 
struct node* CreateIntGNode(int int_num, int lineno);
struct node* CreateFloatGNode(float float_num, int lineno);
struct node* CreateIdGNode(char* id, int lineno);
struct node* CreateTypeGNode(char* type, int lineno);
struct node* CreateGNode(char* name, int lineno, int child_cnt, ...);
int tran(struct node* r, int layer);

int OcttoDec(char* s);
int HextoDec(char* s);
