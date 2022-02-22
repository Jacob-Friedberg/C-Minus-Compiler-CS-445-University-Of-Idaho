#ifndef _SEMANTIC_H
#define _SEMANTIC_H

extern int NUM_ERRORS;
extern int NUM_WARNINGS;

void checkTree2(SymbolTable *symTab,TreeNode *node,bool supressScope, TreeNode *parent);




#endif