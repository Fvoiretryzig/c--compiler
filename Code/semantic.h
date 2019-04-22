#include "symbol_table.h"

#define SEMANTIC_H

#ifdef SEMANTIC_H

#define helper(Rule) void Rule(struct node* n)
#define MAX_ARGC 40

void semantic_analysis(struct node* n);

struct FieldList tmp_table[55];
#endif
