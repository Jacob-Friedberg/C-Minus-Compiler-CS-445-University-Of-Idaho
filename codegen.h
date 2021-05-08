#ifndef _codegen_
#define _codegen_

typedef enum TraverseState
{
    Normal,
    OpInCall,
    ArrayInCall,
    OddAssignments,
    SimpleArrayAssignment,
    SimpleArrayIncDec,
    StandardAssignment,
}TraverseState;



void gen_code(SymbolTable *symTab,TreeNode *tree);

#endif