#ifndef _codegen_
#define _codegen_

typedef enum TraverseState
{
    Normal,
    OpInCall,
}TraverseState;



void gen_code(SymbolTable *symTab,TreeNode *tree);

#endif