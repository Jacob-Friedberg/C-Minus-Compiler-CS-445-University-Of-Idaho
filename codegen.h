#ifndef _codegen_
#define _codegen_
typedef enum TraverseStateFlags
{
    Normal,
    OpInCall,
    ArrayInCall,
    OddAssignments,
    SimpleArrayAssignment,
    SimpleArrayIncDec,
    StandardAssignment,
}TraverseStateFlags;


typedef struct TraverseState
{
    int endOfLoopAddress;
    TraverseStateFlags flags;
}TraverseState;



void gen_code(SymbolTable *symTab,TreeNode *tree);

#endif