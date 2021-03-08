#ifndef _SEMANTIC_H
#define _SEMANTIC_H

extern int NUM_ERRORS;
extern int NUM_WARNINGS;

void checkTree(SymbolTable *symTab,TreeNode *node, int indentLevel,bool supressScope, TreeNode *parent);




#endif