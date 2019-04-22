#include "gtree.h"


extern YYLTYPE yylloc;

struct node* CreateIntGNode(int int_num, int lineno)
{
	struct node* gnode = (struct node*)malloc(sizeof(struct node));
	strcpy(gnode->name, "INT");
	gnode->lineno = lineno;
	gnode->type_int = int_num;
	gnode->n_type = _INIT_;
	gnode->rule = Terminal;	
	gnode->child_cnt = 0;
	//printf("in CreateIntGnode %s: %d\n", gnode->name, gnode->type_int);
	return gnode;
}
struct node* CreateFloatGNode(float float_num, int lineno)
{
	struct node* gnode = (struct node*)malloc(sizeof(struct node));
	strcpy(gnode->name, "FLOAT");
	gnode->lineno = lineno;
	gnode->type_float = float_num;
	gnode->child_cnt = 0;
	gnode->n_type = _INIT_;
	gnode->rule = Terminal;
	//printf("in CreateFloatGNode %s: %f\n", gnode->name, gnode->type_float);
	return gnode;
}
struct node* CreateIdGNode(char* id, int lineno)
{
	struct node* gnode = (struct node*)malloc(sizeof(struct node));
	strcpy(gnode->name, "ID");
	gnode->lineno = lineno;
	strcpy(gnode->str, id);
	gnode->n_type = _INIT_;
	gnode->rule = Terminal;	
	gnode->child_cnt = 0;
	//printf("in CreateIdNode %s: %s\n", gnode->name, gnode->str);
	return gnode;
}
struct node* CreateTypeGNode(char* type, int lineno)
{
	struct node* gnode = (struct node*)malloc(sizeof(struct node));
	strcpy(gnode->name, "TYPE");
	gnode->lineno = lineno;
	strcpy(gnode->str, type);
	gnode->n_type = _INIT_;
	gnode->rule = Terminal;	
	gnode->child_cnt = 0;
	//printf("in CreateTypeGNode %s: %s\n", gnode->name, gnode->str);
	return gnode;
}
struct node* CreateRelopGNode(int lineno, char* op) {
	struct node* gnode = (struct node*)malloc(sizeof(struct node));
	strcpy(gnode->name, "RELOP");
	gnode->lineno = lineno;
	strcpy(gnode->relop, op);
	gnode->n_type = _INIT_;
	gnode->rule = Terminal;
	gnode->child_cnt = 0;
	
	return gnode;
}
struct node* CreateGNode(char* name, int lineno, NodeType node_t, Rule rule_t, int child_cnt, ...)
{
	//printf("in CreateGNode: name:%s child_cnt:%d\n", name, child_cnt);
	struct node* gnode = (struct node*)malloc(sizeof(struct node));
	va_list argp; 
	
	strcpy(gnode->name, name);
	gnode->lineno = lineno;
	gnode->child_cnt = child_cnt;
	gnode->n_type = node_t;
	gnode->rule = rule_t;
	
	va_start(argp, child_cnt);
	if(child_cnt > 0) {
		for(int i = 0; i<child_cnt; i++) {
			//struct node* tmp = gnode->gchild[i];
			struct node* tmp = (struct node*)malloc(sizeof(struct node));
			tmp = va_arg(argp, struct node*);
			gnode->gchild[i] = tmp;
		}
		/*for(int i = 0; i<child_cnt; i++) {
			printf("%s child%d %s\n", gnode->name, i, gnode->gchild[i]->name);
		}*/
	}

	va_end(argp);
	return gnode;
}
int tran(struct node* r, int layer)
{
	//printf("tttttttttttran::::: name:%s layer:%d child_cnt:%d\n", r->name, layer, r->child_cnt);
	if(r == NULL)
		return 0;
	else if(r->child_cnt != -1){
		for(int i = 0; i<layer; i++)
			printf("  ");
		printf("%s", r->name);
		if(!strcmp(r->name, "ID"))
			printf(": %s\n", r->str);
		else if(!strcmp(r->name, "INT"))
			printf(": %d\n", r->type_int);
		else if(!strcmp(r->name, "FLOAT"))
			printf(": %f\n", r->type_float);
		else if(!strcmp(r->name, "TYPE"))
			printf(": %s\n", r->str);
		else if(r->child_cnt > 0)
			printf(" (%d)\n", r->lineno);
		else
			printf("\n");
		for(int i = 0; i<r->child_cnt; i++)
			if(r->gchild[i] != NULL)
				tran(r->gchild[i], layer+1);
	}
}
int OcttoDec(char *s)
{
	int len = strlen(s);
	int ans = 0;
	int power = 1;
	for(int i = 0; i<len; i++) {
		int bit = 0;
		switch(s[len-1-i]) {
			case '0': bit = 0; break;
			case '1': bit = 1; break;
			case '2': bit = 2; break;
			case '3': bit = 3; break;
			case '4': bit = 4; break;
			case '5': bit = 5; break;
			case '6': bit = 6; break;
			case '7': bit = 7; break;
			case '8': bit = 8; break;
			case '9': bit = 9; break;
		}		
		ans += bit*power;
		power *= 8;
	}
	return ans;
}
int HextoDec(char *s)
{
	int len = strlen(s);
	int ans = 0;
	int power = 1;
	for(int i = 0; i<len; i++) {
		int bit = 0;
		switch(s[len-1-i]) {
			case '0': bit = 0; break;
			case '1': bit = 1; break;
			case '2': bit = 2; break;
			case '3': bit = 3; break;
			case '4': bit = 4; break;
			case '5': bit = 5; break;
			case '6': bit = 6; break;
			case '7': bit = 7; break;
			case '8': bit = 8; break;
			case '9': bit = 9; break;
			case 'a':
			case 'A':
				 bit = 10; break;
			case 'b':
			case 'B': 
				 bit = 11; break;
			case 'c':
			case 'C':
				 bit = 12; break;
			case 'd':
			case 'D': 
				 bit = 13; break;
			case 'e':
			case 'E':
				 bit = 14; break;
			case 'f':
			case 'F':
				 bit = 15; break;
		}
		ans += power*bit;
		power *= 16;
	}
	return ans;
}

