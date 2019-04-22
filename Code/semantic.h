#include "symbol_table.h"

#define SEMANTIC_H

#ifdef SEMANTIC_H
#define helper(Rule) void Rule(struct node* n)

void semantic_analysis(struct node* n);
#endif
