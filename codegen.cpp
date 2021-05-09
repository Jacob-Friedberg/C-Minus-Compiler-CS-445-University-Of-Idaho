#include "Tree.h"
#include "parser.tab.h"
#include "symbolTable.h"
#include "emitcode.h"
#include "codegen.h"
#include <string.h>
#include <string>

void code_gen_traverse(SymbolTable *symTab, TreeNode *node, TraverseState state);

extern int globalOffset;

#define DUMMY_REG_6 6
#define IS_ARRAY(node) ((node)->isOp && (node)->op == OPEN_BRACK)

int tOffset = 0;
int foffset = 0;

int pushCountArray = 0;

int mainOffset;

extern char srcFilename[256];

void foo2(void *x)
{
    dumpNode((treeNode *)x);
}

void checkInitGlobal(std::string symbolName, void *ptr)
{
    treeNode *nodeptr;
    nodeptr = (treeNode *)ptr;

    //If we are not a function we must be a global or static variable
    if (!nodeptr->isFunc)
    {

        if (nodeptr->isArray)
        {
            char *tmp = strdup(symbolName.c_str());
            emitRM((char *)"LDC", 3, nodeptr->size - 1, 6, (char *)"load size of array", tmp);
            emitRM((char *)"ST", 3, nodeptr->loc, 0, (char *)"save size of array", tmp);
        }
    }
}

void line_sep()
{
    emitComment((char *)"** ** ** ** ** ** ** ** ** ** ** **");
}

void func_label_top(char *funcName)
{
    line_sep();
    emitComment((char *)"FUNCTION", funcName);
}

void func_label_bottom(char *funcName)
{
    emitComment((char *)"END FUNCTION", funcName);
    emitComment((char *)"");
}

void init_IO(SymbolTable *symTab)
{
    TreeNode *lookupNode = NULL;

    emitComment((char *)"C- Compiler Spring 2021");
    emitComment((char *)"Author: Jacob Friedberg");
    emitComment((char *)"File Compiled: ", srcFilename);
    emitComment((char *)"");

    lookupNode = (treeNode *)symTab->lookup(std::string("input"));
    if (lookupNode == NULL)
    {
        printf("FAILED TO LOOKUP INPUT IO IN CODE GEN PHASE\nQUITTING...\n");
        exit(-1);
    }
    else
    {
        lookupNode->loc = emitWhereAmI();
        //printf("input TM location:%d\n",lookupNode->loc);
    }

    func_label_top((char *)"input");

    emitRM((char *)"ST", 3, -1, 1, (char *)"Store return address");
    emitRO((char *)"IN", 2, 2, 2, (char *)"Grab int input");
    emitRM((char *)"LD", 3, -1, 1, (char *)"Load return address");
    emitRM((char *)"LD", 1, 0, 1, (char *)"Adjust fp");
    emitGoto(0, 3, (char *)"Return");

    func_label_bottom((char *)"input");

    lookupNode = (treeNode *)symTab->lookup(std::string("output"));
    if (lookupNode == NULL)
    {
        printf("FAILED TO LOOKUP OUTPUT IO IN CODE GEN PHASE\nQUITTING...\n");
        exit(-1);
    }
    else
    {
        lookupNode->loc = emitWhereAmI();
        //printf("output TM location:%d\n",lookupNode->loc);
    }

    func_label_top((char *)"output");

    emitRM((char *)"ST", 3, -1, 1, (char *)"Store return address");
    emitRM((char *)"LD", 3, -2, 1, (char *)"Load parameter");
    emitRO((char *)"OUT", 3, 3, 3, (char *)"Output integer");
    emitRM((char *)"LD", 3, -1, 1, (char *)"Load return address");
    emitRM((char *)"LD", 1, 0, 1, (char *)"Adjust fp");
    emitGoto(0, 3, (char *)"Return");

    func_label_bottom((char *)"output");

    lookupNode = (treeNode *)symTab->lookup(std::string("inputb"));
    if (lookupNode == NULL)
    {
        printf("FAILED TO LOOKUP INPUTB IO IN CODE GEN PHASE\nQUITTING...\n");
        exit(-1);
    }
    else
    {
        lookupNode->loc = emitWhereAmI();
        //printf("inputb TM location:%d\n",lookupNode->loc);
    }

    func_label_top((char *)"inputb");

    emitRM((char *)"ST", 3, -1, 1, (char *)"Store return address");
    emitRO((char *)"INB", 2, 2, 2, (char *)"Grab bool input");
    emitRM((char *)"LD", 3, -1, 1, (char *)"Load return address");
    emitRM((char *)"LD", 1, 0, 1, (char *)"Adjust fp");
    emitGoto(0, 3, (char *)"Return");

    func_label_bottom((char *)"inputb");

    lookupNode = (treeNode *)symTab->lookup(std::string("outputb"));
    if (lookupNode == NULL)
    {
        printf("FAILED TO LOOKUP OUTPUTB IO IN CODE GEN PHASE\nQUITTING...\n");
        exit(-1);
    }
    else
    {
        lookupNode->loc = emitWhereAmI();
        //printf("outputb TM location:%d\n",lookupNode->loc);
    }

    func_label_top((char *)"outputb");

    emitRM((char *)"ST", 3, -1, 1, (char *)"Store return address");
    emitRM((char *)"LD", 3, -2, 1, (char *)"Load parameter");
    emitRO((char *)"OUTB", 3, 3, 3, (char *)"Output bool");
    emitRM((char *)"LD", 3, -1, 1, (char *)"Load return address");
    emitRM((char *)"LD", 1, 0, 1, (char *)"Adjust fp");
    emitGoto(0, 3, (char *)"Return");

    func_label_bottom((char *)"outputb");

    lookupNode = (treeNode *)symTab->lookup(std::string("inputc"));
    if (lookupNode == NULL)
    {
        printf("FAILED TO LOOKUP INPUTC IO IN CODE GEN PHASE\nQUITTING...\n");
        exit(-1);
    }
    else
    {
        lookupNode->loc = emitWhereAmI();
        //printf("inputc TM location:%d\n",lookupNode->loc);
    }

    func_label_top((char *)"inputc");

    emitRM((char *)"ST", 3, -1, 1, (char *)"Store return address");
    emitRO((char *)"INC", 2, 2, 2, (char *)"Grab char input");
    emitRM((char *)"LD", 3, -1, 1, (char *)"Load return address");
    emitRM((char *)"LD", 1, 0, 1, (char *)"Adjust fp");
    emitGoto(0, 3, (char *)"Return");

    func_label_bottom((char *)"inputc");

    lookupNode = (treeNode *)symTab->lookup(std::string("outputc"));
    if (lookupNode == NULL)
    {
        printf("FAILED TO LOOKUP OUTPUTC IO IN CODE GEN PHASE\nQUITTING...\n");
        exit(-1);
    }
    else
    {
        lookupNode->loc = emitWhereAmI();
        //printf("outputc TM location:%d\n",lookupNode->loc);
    }

    func_label_top((char *)"outputc");

    emitRM((char *)"ST", 3, -1, 1, (char *)"Store return address");
    emitRM((char *)"LD", 3, -2, 1, (char *)"Load parameter");
    emitRO((char *)"OUTC", 3, 3, 3, (char *)"Output char");
    emitRM((char *)"LD", 3, -1, 1, (char *)"Load return address");
    emitRM((char *)"LD", 1, 0, 1, (char *)"Adjust fp");
    emitGoto(0, 3, (char *)"Return");

    func_label_bottom((char *)"outputc");

    lookupNode = (treeNode *)symTab->lookup(std::string("outnl"));
    if (lookupNode == NULL)
    {
        printf("FAILED TO LOOKUP OUTNL IO IN CODE GEN PHASE\nQUITTING...\n");
        exit(-1);
    }
    else
    {
        lookupNode->loc = emitWhereAmI();
        //printf("outnl TM location:%d\n",lookupNode->loc);
    }

    func_label_top((char *)"outnl");

    emitRM((char *)"ST", 3, -1, 1, (char *)"Store return address");
    emitRO((char *)"OUTNL", 3, 3, 3, (char *)"Output a newline");
    emitRM((char *)"LD", 3, -1, 1, (char *)"Load return address");
    emitRM((char *)"LD", 1, 0, 1, (char *)"Adjust fp");
    emitGoto(0, 3, (char *)"Return");

    func_label_bottom((char *)"outnl");
}

void checkChildren(TreeNode *node, SymbolTable *symTab, TraverseState state)
{

    for (int i = 0; i < MAXCHILDREN; i++)
    {
        if (node->child[i] != NULL)
        {
            //printf("Child: %d ", i);
            code_gen_traverse(symTab, node->child[i], state);
        }
    }
}

void checkChildrenLeft(TreeNode *node, SymbolTable *symTab, TraverseState state)
{

    if (node->child[0] != NULL)
    {
        //printf("Child: %d ", i);
        code_gen_traverse(symTab, node->child[0], state);
    }
}

void checkChildrenRight(TreeNode *node, SymbolTable *symTab, TraverseState state)
{
    if (node->child[1] != NULL)
    {
        //printf("Child: %d ", i);
        code_gen_traverse(symTab, node->child[1], state);
    }
}

void checkChildrenLeftNormal(TreeNode *node, SymbolTable *symTab, TraverseState state)
{

    if (node->child[0] != NULL)
    {
        //printf("Child: %d ", i);
        checkChildren(node->child[0], symTab, state);
    }
}

void checkChildrenRightNormal(TreeNode *node, SymbolTable *symTab, TraverseState state)
{

    if (node->child[0] != NULL)
    {
        //printf("Child: %d ", i);
        checkChildren(node->child[1], symTab, state);
    }
}

void decrement_toffset(int numberOfDecrements)
{
    for (int i = 0; i < numberOfDecrements; i++)
    {
        tOffset--;
        emitComment((char *)"TOFF dec:", tOffset);
    }
}

void increment_toffset(int numberOfIncrements)
{
    for (int i = 0; i < numberOfIncrements; i++)
    {
        tOffset++;
        emitComment((char *)"TOFF inc:", tOffset);
    }
}

void push_left_side_array()
{
    emitRM((char *)"ST", 3, tOffset, 1, (char *)"Push left side");
    decrement_toffset(1);
    pushCountArray++;
}

void pop_left_array(bool looping)
{

    if (looping)
    {
        //pop as many times as we pushed.
        for (int i = 0; i < pushCountArray; i++)
        {
            increment_toffset(1);
            emitRM((char *)"LD", 4, tOffset, 1, (char *)"Pop left into ac1");
            emitRO((char *)"SUB", 3, 4, 3, (char *)"compute location from index");
            emitRM((char *)"LD", 3, 0, 3, (char *)"Load array element");
        }
    }
    else
    {
        increment_toffset(1);
        emitRM((char *)"LD", 4, tOffset, 1, (char *)"Pop left into ac1");
        emitRO((char *)"SUB", 3, 4, 3, (char *)"compute location from index");
        emitRM((char *)"LD", 3, 0, 3, (char *)"Load array element");
    }

    //reset the count
    pushCountArray = 0;
}

void emitOperator(treeNode *node)
{
    if (node->op == MULT)
    {
        emitRO((char *)"MUL", 3, 4, 3, (char *)"Op *");
    }
    else if (node->op == PLUS)
    {
        emitRO((char *)"ADD", 3, 4, 3, (char *)"Op +");
    }
    else if (node->op == MOD)
    {
        emitRO((char *)"MOD", 3, 4, 3, (char *)"Op %");
    }
    else if (node->op == DIV)
    {
        emitRO((char *)"DIV", 3, 4, 3, (char *)"Op /");
    }
    else if (node->op == MINUS)
    {
        emitRO((char *)"SUB", 3, 4, 3, (char *)"Op -");
    }
    else if (node->op == CHSIGN)
    {
        emitRO((char *)"NEG", 3, 3, 3, (char *)"Op unary -");
    }
    else if (node->op == NOT)
    {
        emitRM((char *)"LDC", 4, 1, 6, (char *)"Load 1");
        emitRO((char *)"XOR", 3, 3, 4, (char *)"Op XOR to get logical not");
    }
    else if (node->op == OR)
    {
        emitRO((char *)"OR", 3, 4, 3, (char *)"Op OR");
    }
    else if (node->op == AND)
    {
        emitRO((char *)"AND", 3, 4, 3, (char *)"Op AND");
    }
    else if (node->op == QUESTION)
    {
        emitRO((char *)"RND", 3, 3, 6, (char *)"Op ?");
    }
    else if (node->op == EQ)
    {
        emitRO((char *)"TEQ", 3, 4, 3, (char *)"Op ==");
    }
    else if (node->op == GREATER)
    {
        emitRO((char *)"TGT", 3, 4, 3, (char *)"Op >");
    }
    else if (node->op == LESS)
    {
        emitRO((char *)"TLT", 3, 4, 3, (char *)"Op <");
    }
    else if (node->op == NEQ)
    {
        emitRO((char *)"TNE", 3, 4, 3, (char *)"Op !=");
    }
    else if (node->op == GEQ)
    {
        emitRO((char *)"TGE", 3, 4, 3, (char *)"Op >=");
    }
    else if (node->op == LEQ)
    {
        emitRO((char *)"TLE", 3, 4, 3, (char *)"Op <=");
    }
    else if (node->op == ADDASS)
    {
        emitRO((char *)"ADD", 3, 4, 3, (char *)"Op +=");
    }
    else if (node->op == SUBASS)
    {
        emitRO((char *)"SUB", 3, 4, 3, (char *)"Op -=");
    }
    else if (node->op == MULASS)
    {
        emitRO((char *)"MUL", 3, 4, 3, (char *)"Op *=");
    }
    else if (node->op == DIVASS)
    {
        emitRO((char *)"DIV", 3, 4, 3, (char *)"Op /=");
    }
}

//Param1: Name of node to lookup
//Param2: where did you call this function from?
treeNode *sym_lookup(char *nodeName, char *calledFrom, SymbolTable *symTab)
{
    treeNode *tmpNode = NULL;
    tmpNode = (treeNode *)symTab->lookup(std::string(nodeName));
    if (tmpNode == NULL)
    {
        printf("FAILED TO LOOKUP %s FROM %s IN CODE GEN PHASE\nQUITTING...\n", nodeName, calledFrom);
        exit(-1);
    }

    return tmpNode;
}

//handle the case of a nested arrays from a call.
void nested_array_from_call(treeNode *node)
{
    int numOfNestedArrays = 0;
    treeNode *tmpNode;
    //itterate through the children on the left side as long as we have more arrays to go through
    //we stop this loop when we have an index at child[1] of the '[' op.
    //if its more brackets we know we have to keep itterating.
    //IMPORTANT: This loop gives us the last [ of the nest. therefore we need to repeat the
    //
    while (node->child[0] != NULL && node->child[1] != NULL)
    {

        numOfNestedArrays++;

        if (node->child[0]->scope == Local)
            emitRM((char *)"LDA", 3, (node->child[0]->loc) - 1, 1, (char *)"Load address of base of array", node->child[0]->attr.string);
        else if (node->child[0]->scope == Global)
            emitRM((char *)"LDA", 3, (node->child[0]->loc) - 1, 0, (char *)"Load address of base of array", node->child[0]->attr.string);
        else if (node->child[0]->scope == Parameter)
            emitRM((char *)"LD", 3, (node->child[0]->loc), 1, (char *)"Load address of base of array", node->child[0]->attr.string);

        emitRM((char *)"ST", 3, tOffset, 1, (char *)"Push left side");
        decrement_toffset(1);

        //go to the next child
        node = node->child[1];

        //Store the '[' node right before the end of the nest.
        //we will restore our node back to this point at the end of the loop.
        if (node->child[1] != NULL && node->child[1]->op != OPEN_BRACK)
        {
            tmpNode = node;
        }
    }

    //restore to before the end
    node = tmpNode;

    //sanity check.
    //We need to load the index of the array at the heart of the nest.
    // we should be the '[' operator
    if (node != NULL)
    {
        if (node->child[1]->scope == Local)
            emitRM((char *)"LD", 3, (node->child[1]->loc), 1, (char *)"Load variable", node->child[1]->attr.string);
        else if (node->child[1]->scope == Global)
            emitRM((char *)"LD", 3, (node->child[1]->loc), 0, (char *)"Load variable", node->child[1]->attr.string);
        else if (node->child[1]->scope == Parameter)
            emitRM((char *)"LD", 3, (node->child[1]->loc), 1, (char *)"Load variable", node->child[1]->attr.string);
    }

    //We have reached the bottom of the nest and need to pop and load elements
    //We should have node->child[0] = IdK and node->child[1] = Const or IdK
    //GLOBAL COUNTER IS KEPT SO WE DONT NEED TO.
    pop_left_array(true);
}

void code_gen_traverse(SymbolTable *symTab, TreeNode *node, TraverseState state)
{
    int ghostFrameToff = 0;
    char typing[64];
    char scoping[64];

    static bool hasPushedConst = false;
    static bool hasPushedOp = false;
    static bool isUnary = false;
    static bool isBoolKeyword = false;
    static bool suppressPrint = false;
    static bool assignWithArray = false;
    static bool suppressCompoundBody = false;
    static bool moreThanOneVariableInCall = false;
    static bool nestedArraysInAssign = false;
    static bool nestedArraysInCall = false;

    treeNode *tmpNode;

    treeNode *lookupNode;
    //symTab->debug(true);
    while (node != NULL)
    {
        convertExpTypeToString(node->expType, typing);
        convertScopeKindToString(node->scope, scoping);

        //Refactored switch
        //Process statements
        if (node->nodekind == StmtK)
        {
            switch (node->subkind.stmt)
            {
            case NullK:

                checkChildren(node, symTab, Normal);
                break;

            case IfK:

                checkChildren(node, symTab, Normal);
                break;

            case WhileK:

                checkChildren(node, symTab, Normal);
                break;

            case ForK:

                checkChildren(node, symTab, Normal);
                break;

            case CompoundK:
                emitComment((char *)"COMPOUND");

                //set toffset to the open space of the compound;
                tOffset = node->size;

                emitComment((char *)"TOFF set:", tOffset);

                if (node->child[0] != NULL && node->child[0]->nodekind == DeclK && node->child[0]->subkind.decl == VarK)
                    suppressCompoundBody = true;
                else
                    emitComment((char *)"Compound Body");

                checkChildren(node, symTab, Normal);

                tOffset = -2;
                emitComment((char *)"TOFF set:", tOffset);

                emitComment((char *)"END COMPOUND");

                suppressCompoundBody = false;
                break;

            case ReturnK:

                checkChildren(node, symTab, Normal);

                emitComment((char *)"RETURN");
                emitRM((char *)"LD", 3, -1, 1, (char *)"Load return address");
                emitRM((char *)"LD", 1, 0, 1, (char *)"Adjust fp");
                emitGoto(0, 3, (char *)"Return");
                break;

            case BreakK:
                checkChildren(node, symTab, Normal);
                break;

            case RangeK:

                checkChildren(node, symTab, Normal);
                break;

            default:

                printf("PROGRAMMER ERROR UNKNOWN STA IN CODE GENTMENT TYPE\nSHOULD NOT GET HERE\n");
                exit(-1);
            }
        }
        //Process declarations
        else if (node->nodekind == DeclK)
        {
            switch (node->subkind.decl)
            {
            case VarK:

                checkChildren(node, symTab, Normal);
                if (node->isArray && node->depth > 1)
                {
                    emitRM((char *)"LDC", 3, node->size - 1, 6, (char *)"load size of array", node->attr.name);
                    emitRM((char *)"ST", 3, node->loc, 1, (char *)"save size of array", node->attr.name);
                }

                if (node->sibling == NULL && suppressCompoundBody)
                {
                    emitComment((char *)"Compound Body");
                    emitComment((char *)"EXPRESSION");
                }

                break;

            case FuncK:

                //temp offset would be -2 to start. 0 and -1 are taken already
                //by the return ticket and instruction to execute
                tOffset = node->size;

                if (strcmp("main", node->attr.string) == 0)
                    mainOffset = emitWhereAmI();

                line_sep();
                emitComment((char *)"FUNCTION", node->attr.string);
                emitComment((char *)"TOFF set:", tOffset);

                emitRM((char *)"ST", 3, -1, 1, (char *)"Store return address");
                checkChildren(node, symTab, Normal);

                //add standard closing
                emitComment((char *)"Add standard closing in case there is no return statement");
                emitRM((char *)"LDC", 2, 0, 6, (char *)"Set return value to 0");
                emitRM((char *)"LD", 3, -1, 1, (char *)"Load return address");
                emitRM((char *)"LD", 1, 0, 1, (char *)"Adjust fp");
                emitGoto(0, 3, (char *)"Return");
                emitComment((char *)"END FUNCTION", node->attr.string);

                //If we are the main function we add the standard closing.
                if (strcmp("main", node->attr.string) == 0)
                {
                    backPatchAJumpToHere(0, (char *)"Jump to init [backpatch]");
                }
                else
                    emitComment((char *)"");
                break;

            case ParamK:

                checkChildren(node, symTab, Normal);
                break;

            default:
                printf("PROGRAMMER ERROR UNKNOWN DEC IN CODE GENL TYPE\nSHOULD NOT GET HERE\n");
                exit(-1);
            }
        }
        //Proccess Expressions
        else if (node->nodekind == ExpK)
        {

            switch (node->subkind.exp)
            {
            case OpK:

                //we are an array on the left hand side
                if (node->op == OPEN_BRACK && node->sideOfAssignment == leftSide)
                {
                    checkChildren(node, symTab, state);
                    emitRM((char *)"ST", 3, tOffset, 1, "Push index");
                    decrement_toffset(1);
                }
                else if (node->op == OPEN_BRACK && (node->parent->op == INC || node->parent->op == DEC))
                {
                    checkChildren(node, symTab, state);
                }
                //we are an array on the rhs
                else if (node->op == OPEN_BRACK)
                {

                    //Load the base address of the array into R3
                    if (node->child[0]->scope == Local)
                        emitRM((char *)"LDA", 3, (node->child[0]->loc) - 1, 1, (char *)"Load address of base of array", node->child[0]->attr.name);
                    else if (node->child[0]->scope == Global || node->child[0]->scope == LocalStatic)
                        emitRM((char *)"LDA", 3, (node->child[0]->loc) - 1, 0, (char *)"Load address of base of array", node->child[0]->attr.name);
                    else if (node->child[0]->scope == Parameter)
                        emitRM((char *)"LD", 3, (node->child[0]->loc), 1, (char *)"Load address of base of array", node->child[0]->attr.name);

                    //Push base address of array stored in r3 onto stack
                    emitRM((char *)"ST", 3, tOffset, 1, (char *)"Push left side");
                    decrement_toffset(1);

                    //process children, Determine index, result will be left in r3
                    checkChildren(node, symTab, state);

                    //Pop base address of array into R4 from stack
                    increment_toffset(1);
                    emitRM((char *)"LD", 4, tOffset, 1, (char *)"Pop left into ac1");

                    //Determine address of array element. (baseAddress - index)
                    emitRO((char *)"SUB", 3, 4, 3, (char *)"compute location from index");

                    //Load the value of the element into R3
                    emitRM((char *)"LD", 3, 0, 3, (char *)"Load array element");
                }

                //Assume binary and unary operators are left
                else
                {
                    if (node->child[0] == NULL)
                    {
                        printf("ERROR CODE GEN OPK, EXPECTING LHS IN BINARY OPERATOR, RECIEVED NULL...\nNOW QUITTING\n");
                        exit(-1);
                    }

                    //process lhs leave result in R3
                    code_gen_traverse(symTab, node->child[0], state);

                    //If there is a child on the RHS we have a binary operator
                    //Push LHS that is in R3 on the stack and place the RHS in r4
                    if (node->child[1] != NULL)
                    {
                        //Push Value LHS value in R3 on stack
                        emitRM((char *)"ST", 3, tOffset, 1, (char *)"Push left side");
                        decrement_toffset(1);

                        //Process RHS leave result in R3
                        code_gen_traverse(symTab, node->child[1], state);

                        //Pop LHS into R4 from stack
                        increment_toffset(1);
                        emitRM((char *)"LD", 4, tOffset, 1, (char *)"Pop left into ac1");
                    }

                    //Performs the operator instruction. For binary it expects r3 and r4. Unary only expects r3. Result is left in r3
                    emitOperator(node);
                }

                /*
                if (node->op == QUESTION || node->op == CHSIGN)
                {
                    isUnary = true;
                }

                //we are simple well formed array (x[2]++) that is being inc/dec
                if (state == SimpleArrayIncDec)
                {
                }

                //we are an array from the assignmnet.
                if (state == SimpleArrayAssignment && node->op == OPEN_BRACK)
                {
                    emitRM((char *)"LDC", 3, node->child[1]->attr.value, 6, "Load integer constant");
                    emitRM((char *)"ST", 3, tOffset, 1, "Push index");

                    decrement_toffset(1);
                }

                //we are the initial OP for the call and this is only for arrays Does not work with unary.
                if (state == OpInCall && (node->parent->nodekind == ExpK && node->parent->subkind.exp == CallK) && node->child[1] != NULL && (node->child[0]->op == OPEN_BRACK || node->child[1]->op == OPEN_BRACK))
                {
                    //checking the left children
                    checkChildren(node->child[0], symTab, state);

                    push_left_side_array();

                    //check right side
                    checkChildren(node->child[1], symTab, state);

                    increment_toffset(1);
                    emitRM((char *)"LD", 4, tOffset, 1, (char *)"Pop left into ac1");
                }
                //for nested operators, this wont work for arrays.
                else if (state == OpInCall && moreThanOneVariableInCall)
                {
                    checkChildren(node, symTab, state);

                    if (node->op != QUESTION && node->op != CHSIGN)
                    {
                        if ((node->parent->nodekind == ExpK && node->parent->subkind.exp == CallK))
                        {
                            emitOperator(node);
                            break;
                        }

                        emitOperator(node);
                        if (hasPushedOp == false)
                        {

                            emitRM((char *)"ST", 3, tOffset, 1, (char *)"Push left side");
                            decrement_toffset(1);

                            hasPushedOp = true;
                        }
                        else if (hasPushedOp)
                        {
                            increment_toffset(1);
                            emitRM((char *)"LD", 4, tOffset, 1, (char *)"Pop left into ac1");

                            hasPushedOp = false;
                        }

                        break;
                    }
                    else
                        break;
                }
                else
                {

                    //foo2(node);
                    
                }
                */

                break;

            case ConstantK:

                //Constants shouldn't have any children
                //checkChildren(node, symTab, Normal);

                //Lone integer constants

                if (node->expType == Integer)
                {
                    emitRM((char *)"LDC", 3, node->attr.value, DUMMY_REG_6, (char *)"Load integer constant");
                }
                else if (node->expType == Boolean)
                {
                    emitRM((char *)"LDC", 3, node->attr.value, DUMMY_REG_6, (char *)"Load Boolean constant");
                }
                else if (node->expType == Char)
                {
                    emitRM((char *)"LDC", 3, node->attr.value, DUMMY_REG_6, (char *)"Load char constant");
                }

                /*
                //our parent is an OP
                else if (state == OpInCall)
                {
                    if (node->expType == Integer)
                    {

                        if (node->parent->op == CHSIGN)
                        {
                            emitRM((char *)"LDC", 3, node->attr.value, 6, (char *)"Load integer constant");
                        }
                        //This is printing for arrays in calls
                        else if (hasPushedConst == false && node->parent->op != CHSIGN)
                        {
                            if (node->parent->op != OPEN_BRACK)
                            {
                                emitRM((char *)"LDC", 3, node->attr.value, 6, (char *)"Load integer constant");

                                //has a unary
                                if (node->parent->isOp && node->parent->op == QUESTION)
                                {
                                    emitOperator(node->parent);
                                }

                                emitRM((char *)"ST", 3, tOffset, 1, (char *)"Push left side");
                                decrement_toffset(1);
                                hasPushedConst = true;
                            }
                            //we are open brack therefore the index of an array
                            else if (node->parent->op == OPEN_BRACK)
                            {
                                emitRM((char *)"LDC", 3, node->attr.value, 6, (char *)"Load integer constant");
                                pop_left_array(false);
                            }
                            else
                                emitRM((char *)"LDC", 3, node->attr.value, 6, (char *)"Load integer constant");
                        }
                        else if (hasPushedConst == true && node->parent->op != CHSIGN)
                        {

                            emitRM((char *)"LDC", 3, node->attr.value, 6, (char *)"Load integer constant");

                            if (node->parent->op != OPEN_BRACK)
                            {
                                //has a unary
                                if (node->parent->isOp && node->parent->op == QUESTION)
                                {
                                    emitOperator(node->parent);
                                }

                                increment_toffset(1);
                                emitRM((char *)"LD", 4, tOffset, 1, (char *)"Pop left into ac1");
                                hasPushedConst = false;
                            }
                        }
                    }
                    //Assuming always Not/XOR
                    else if (node->expType == Boolean && node->parent->op == NOT)
                    {
                        emitRM((char *)"LDC", 3, node->attr.value, 6, (char *)"Load Boolean constant");
                        emitRM((char *)"LDC", 4, 1, 6, (char *)"Load 1");
                    }
                    else if (node->expType == Boolean && node->parent->op != NOT)
                    {
                        emitRM((char *)"LDC", 3, node->attr.value, 6, (char *)"Load Boolean constant");

                        if (hasPushedConst == false)
                        {
                            emitRM((char *)"ST", 3, tOffset, 1, (char *)"Push left side");
                            decrement_toffset(1);
                            hasPushedConst = true;
                        }
                        else
                        {
                            increment_toffset(1);
                            emitRM((char *)"LD", 4, tOffset, 1, (char *)"Pop left into ac1");
                            hasPushedConst = false;
                        }
                    }
                }
                else if (state == SimpleArrayAssignment)
                {
                }
                */
                break;

            case IdK:

                //Case that we are a identifier for an array
                //We let our parent Gen code since we need the index
                if (node->parent->isOp && node->parent->op == OPEN_BRACK)
                {
                    //return the value in R3 if we are the index
                    if (node->parent->child[1] == node)
                    {
                        if (node->scope == Local)
                            emitRM((char *)"LD", 3, node->loc, 1, (char *)"Load variable", node->attr.string);
                        else if (node->scope == Global || node->scope == LocalStatic)
                            emitRM((char *)"LD", 3, node->loc, 0, (char *)"Load variable", node->attr.string);
                        else if (node->scope == Parameter)
                            emitRM((char *)"LD", 3, node->loc, 1, (char *)"Load variable", node->attr.string);
                    }

                    break;
                }

                if (node->sideOfAssignment != leftSide)
                {
                    //assume identifier is not an array
                    if (!node->isArray)
                    {
                        if (node->scope == Local)
                            emitRM((char *)"LD", 3, node->loc, 1, (char *)"Load variable", node->attr.string);
                        else if (node->scope == Global || node->scope == LocalStatic)
                            emitRM((char *)"LD", 3, node->loc, 0, (char *)"Load variable", node->attr.string);
                        else if (node->scope == Parameter)
                            emitRM((char *)"LD", 3, node->loc, 1, (char *)"Load variable", node->attr.string);
                    }
                    else
                    {
                        if (node->scope == Local)
                            emitRM((char *)"LDA", 3, (node->loc - 1), 1, (char *)"Load address of base of array", node->attr.string);
                        else if (node->scope == Global || node->scope == LocalStatic)
                            emitRM((char *)"LDA", 3, (node->loc - 1), 0, (char *)"Load address of base of array", node->attr.string);
                        else if (node->scope == Parameter)
                            emitRM((char *)"LD", 3, node->loc, 1, (char *)"Load address of base of array", node->attr.string);
                    }
                }

                /*
                if (node->sideOfAssignment == leftSide)
                {
                    //assume identifier is not an array
                    if (node->child[0]->scope == Local)
                        emitRM((char *)"ST", 3, (node->child[0]->loc), 1, (char *)"Store variable", node->child[0]->attr.name);
                    else if (node->child[0]->scope == Global || node->child[0]->scope == LocalStatic)
                        emitRM((char *)"ST", 3, (node->child[0]->loc), 0, (char *)"Store variable", node->child[0]->attr.name);
                    else if (node->child[0]->scope == Parameter)
                        emitRM((char *)"ST", 3, (node->child[0]->loc), 1, (char *)"Store variable", node->child[0]->attr.name);
                }
    */
                //IdK's dont have children
                //checkChildren(node, symTab, Normal);

                /*
                //Think this is fine. Assuming IdK is only called from callK
                //We check what reg to place things in and push and pop accordingly
                if (state == OpInCall)
                {
                    if (!node->isArray)
                    {
                        if (node->scope == Local)
                            emitRM((char *)"LD", 3, node->loc, 1, (char *)"Load variable", node->attr.string);
                        else if (node->scope == Global)
                            emitRM((char *)"LD", 3, node->loc, 0, (char *)"Load variable", node->attr.string);
                    }
                    else
                    {
                        if (node->scope == Local)
                            emitRM((char *)"LDA", 3, node->loc - 1, 1, (char *)"Load address of base of array", node->attr.string);
                        else if (node->scope == Global)
                            emitRM((char *)"LDA", 3, node->loc - 1, 0, (char *)"Load address of base of array", node->attr.string);

                        push_left_side_array();
                    }

                    //Dont want to do this twice, if we are an array we have code gen elsewhere
                    if (hasPushedConst == false && !node->isArray /*&& node->parent->op == OPEN_BRACK)
                    {
                        emitRM((char *)"ST", 3, tOffset, 1, (char *)"Push left side");
                        decrement_toffset(1);
                        hasPushedConst = true;
                    }
                    else if (hasPushedConst && !node->isArray /*&& node->parent->op == OPEN_BRACK)
                    {
                        increment_toffset(1);
                        emitRM((char *)"LD", 4, tOffset, 1, (char *)"Pop left into ac1");
                        hasPushedConst = false;
                    }
                }
                //Assignment += -= /= etc.
                else if (state == OddAssignments)
                {
                    if (node->rhsAssign)
                    {
                        if (node->scope == Local)
                            emitRM((char *)"LD", 3, node->loc, 1, (char *)"Load variable", node->attr.string);
                        else if (node->scope == Global)
                            emitRM((char *)"LD", 3, node->loc, 0, (char *)"Load variable", node->attr.string);
                        else if (node->scope == LocalStatic)
                            emitRM((char *)"LD", 3, node->loc, 0, (char *)"Load variable", node->attr.string);
                    }
                }
                else if (state == StandardAssignment)
                {
                    if (node->scope == Local)
                        emitRM((char *)"LD", 3, node->loc, 1, (char *)"Load variable", node->attr.string);
                    else if (node->scope == Global)
                        emitRM((char *)"LD", 3, node->loc, 0, (char *)"Load variable", node->attr.string);
                    else if (node->scope == LocalStatic)
                        emitRM((char *)"LD", 3, node->loc, 0, (char *)"Load variable", node->attr.string);
                }
                else if (state == SimpleArrayAssignment)
                {
                }
                */

                break;

            case AssignK:

                //emitComment((char *)"EXPRESSION");

                checkChildren(node, symTab, Normal);

                if (node->op == ADDASS || node->op == SUBASS || node->op == DIVASS || node->op == MULASS || node->op == ASS)
                {

                    //Assume Array
                    if (node->child[0]->isOp && node->child[0]->op == OPEN_BRACK)
                    {
                        //Place the index into R4 from the stack.
                        increment_toffset(1);
                        emitRM((char *)"LD", 4, tOffset, 1, (char *)"Pop index");

                        //Load the base of the array into R5
                        if (node->child[0]->scope == Local)
                            emitRM((char *)"LDA", 5, (node->child[0]->loc) - 1, 1, (char *)"Load address of base of array", node->child[0]->arrayIdentf);
                        else if (node->child[0]->scope == Global || node->child[0]->scope == LocalStatic)
                            emitRM((char *)"LDA", 5, (node->child[0]->loc) - 1, 0, (char *)"Load address of base of array", node->child[0]->arrayIdentf);
                        else if (node->child[0]->scope == Parameter)
                            emitRM((char *)"LD", 5, (node->child[0]->loc), 1, (char *)"Load address of base of array", node->child[0]->arrayIdentf);

                        //bump base in R5 by index in R4
                        emitRO((char *)"SUB", 5, 5, 4, (char *)"Compute offset of value");

                        if (node->op != ASS)
                        {
                            //Load the value of the element into R4
                            emitRM((char *)"LD", 4, 0, 5, (char *)"load lhs variable of", node->child[0]->arrayIdentf);

                            //emit the operator and perform the instruction  R3 = R4 op R3
                            emitOperator(node);
                        }

                        //Store the result back at the location in R5
                        emitRM((char *)"ST", 3, 0, 5, (char *)"Store variable", node->child[0]->arrayIdentf);
                    }
                    //Assumes non array
                    else
                    {
                        if (node->op != ASS)
                        {
                            //Load into R4 the value of the LHS of variable
                            if (node->child[0]->scope == Local)
                                emitRM((char *)"LD", 4, (node->child[0]->loc), 1, (char *)"Load lhs variable", node->child[0]->attr.name);
                            else if (node->child[0]->scope == Global || node->child[0]->scope == LocalStatic)
                                emitRM((char *)"LD", 4, (node->child[0]->loc), 0, (char *)"Load lhs variable", node->child[0]->attr.name);
                            else if (node->child[0]->scope == Parameter)
                                emitRM((char *)"LD", 4, (node->child[0]->loc), 1, (char *)"Load lhs variable", node->child[0]->attr.name);

                            //emit the operator and perform the instruction  R3 = R4 op R3
                            emitOperator(node);
                        }

                        if (node->child[0]->scope == Local)
                            emitRM((char *)"ST", 3, (node->child[0]->loc), 1, (char *)"Store variable", node->child[0]->attr.name);
                        else if (node->child[0]->scope == Global || node->child[0]->scope == LocalStatic)
                            emitRM((char *)"ST", 3, (node->child[0]->loc), 0, (char *)"Store variable", node->child[0]->attr.name);
                        else if (node->child[0]->scope == Parameter)
                            emitRM((char *)"ST", 3, (node->child[0]->loc), 1, (char *)"Store variable", node->child[0]->attr.name);
                    }
                }
                else if (node->op == INC || node->op == DEC)
                {
                    //If we have an array calculate the address of the element to be incremented or decremented.
                    if (node->child[0]->isOp && node->child[0]->op == OPEN_BRACK)
                    {
                        //ASSUME R3 CONTAINS THE INDEX
                        //Load the base of the array into R5
                        if (node->child[0]->scope == Local)
                            emitRM((char *)"LDA", 5, (node->child[0]->loc) - 1, 1, (char *)"Load address of base of array", node->child[0]->arrayIdentf);
                        else if (node->child[0]->scope == Global || node->child[0]->scope == LocalStatic)
                            emitRM((char *)"LDA", 5, (node->child[0]->loc) - 1, 0, (char *)"Load address of base of array", node->child[0]->arrayIdentf);
                        else if (node->child[0]->scope == Parameter)
                            emitRM((char *)"LD", 5, (node->child[0]->loc), 1, (char *)"Load address of base of array", node->child[0]->arrayIdentf);

                        //bump base in R5 by index
                        emitRO((char *)"SUB", 5, 5, 3, (char *)"Compute offset of value");

                        //Load the value of the element into R3
                        emitRM((char *)"LD", 3, 0, 5, (char *)"load lhs variable", node->child[0]->arrayIdentf);

                        //INC/DEC the element at the computed memory location in R5.
                        if (node->op == INC)
                            emitRM((char *)"LDA", 3, 1, 3, (char *)"increment value of", node->child[0]->arrayIdentf);
                        else
                            emitRM((char *)"LDA", 3, -1, 3, (char *)"decrement value of", node->child[0]->arrayIdentf);

                        //Store the result back at the location in R5
                        emitRM((char *)"ST", 3, 0, 5, (char *)"Store variable", node->child[0]->arrayIdentf);
                    }
                    else if (node->child[0]->subkind.exp == IdK)
                    {

                        if (node->child[0]->scope == Local)
                            emitRM((char *)"LD", 3, (node->child[0]->loc), 1, (char *)"Load lhs variable", node->child[0]->attr.name);
                        else if (node->child[0]->scope == Global || node->child[0]->scope == LocalStatic)
                            emitRM((char *)"LD", 3, (node->child[0]->loc), 0, (char *)"Load lhs variable", node->child[0]->attr.name);
                        else if (node->child[0]->scope == Parameter)
                            emitRM((char *)"LD", 3, (node->child[0]->loc), 1, (char *)"Load lhs variable", node->child[0]->attr.name);

                        if (node->op == INC)
                            emitRM((char *)"LDA", 3, 1, 3, (char *)"increment value of", node->child[0]->attr.name);
                        else
                            emitRM((char *)"LDA", 3, -1, 3, (char *)"decrement value of", node->child[0]->attr.name);

                        if (node->child[0]->scope == Local)
                            emitRM((char *)"ST", 3, (node->child[0]->loc), 1, (char *)"Store variable", node->child[0]->attr.name);
                        else if (node->child[0]->scope == Global || node->child[0]->scope == LocalStatic)
                            emitRM((char *)"ST", 3, (node->child[0]->loc), 0, (char *)"Store variable", node->child[0]->attr.name);
                        else if (node->child[0]->scope == Parameter)
                            emitRM((char *)"ST", 3, (node->child[0]->loc), 1, (char *)"Store variable", node->child[0]->attr.name);
                    }
                }

                /*
                //if we are an assignment with an array on either side.
                //have not implemented complex expressions a[2] = x+2+3
                
                if (node->op == ASS && (node->child[0]->op == OPEN_BRACK && !node->child[1]->isOp))
                {
                    checkChildrenLeft(node, symTab, SimpleArrayAssignment);

                    //constant on the rhs so we can just load it
                    if (node->child[1]->isConst)
                        emitRM((char *)"LDC", 3, node->child[1]->attr.value, 6, (char *)"Load integer constant");

                    increment_toffset(1);

                    emitRM((char *)"LD", 4, tOffset, 1, (char *)"Pop index");

                    if (node->child[0]->scope == Local)
                        emitRM((char *)"LDA", 5, (node->child[0]->loc) - 1, 1, (char *)"Load address of base of array", node->child[0]->arrayIdentf);
                    else if (node->child[0]->scope == Global)
                        emitRM((char *)"LDA", 5, (node->child[0]->loc) - 1, 0, (char *)"Load address of base of array", node->child[0]->arrayIdentf);
                    else if (node->child[0]->scope == Parameter)
                        emitRM((char *)"LD", 5, (node->child[0]->loc), 1, (char *)"Load address of base of array", node->child[0]->arrayIdentf);

                    emitRO((char *)"SUB", 5, 5, 4, (char *)"Compute offset of value");

                    emitRM((char *)"ST", 3, 0, 5, (char *)"Store variable", node->child[0]->arrayIdentf);
                }
                else if (node->op == INC || node->op == DEC)
                {
                    if (node->child[0]->nodekind == ExpK && node->child[0]->subkind.exp == IdK)
                    {

                        if (node->child[0]->scope == Local)
                            emitRM((char *)"LD", 3, (node->child[0]->loc), 1, (char *)"Load lhs variable", node->child[0]->attr.name);
                        else if (node->child[0]->scope == Global)
                            emitRM((char *)"LD", 3, (node->child[0]->loc), 0, (char *)"Load lhs variable", node->child[0]->attr.name);
                        else if (node->child[0]->scope == Parameter)
                            emitRM((char *)"LD", 3, (node->child[0]->loc), 1, (char *)"Load lhs variable", node->child[0]->attr.name);

                        if (node->op == INC)
                            emitRM((char *)"LDA", 3, 1, 3, (char *)"increment value of", node->child[0]->attr.name);
                        else
                            emitRM((char *)"LDA", 3, -1, 3, (char *)"decrement value of", node->child[0]->attr.name);

                        if (node->child[0]->scope == Local)
                            emitRM((char *)"ST", 3, (node->child[0]->loc), 1, (char *)"Store variable", node->child[0]->attr.name);
                        else if (node->child[0]->scope == Global)
                            emitRM((char *)"ST", 3, (node->child[0]->loc), 0, (char *)"Store variable", node->child[0]->attr.name);
                        else if (node->child[0]->scope == Parameter)
                            emitRM((char *)"ST", 3, (node->child[0]->loc), 1, (char *)"Store variable", node->child[0]->attr.name);

                        break;
                    }

                    checkChildren(node, symTab, SimpleArrayIncDec);
                }
                //dont do this with arrays
                else if ((node->op == ADDASS || node->op == MULASS || node->op == SUBASS || node->op == DIVASS) &&
                         (node->child[0]->op != OPEN_BRACK || node->child[1]->op != OPEN_BRACK))
                {
                    //emitComment((char *)"EXPRESSION");

                    checkChildren(node, symTab, OddAssignments);

                    //2 indentifiers.
                    if (!node->child[0]->isConst && !node->child[0]->isConst)
                    {

                        if (node->child[1]->scope == Local)
                        {
                            emitRM((char *)"LD", 3, node->child[1]->loc, 1, (char *)"Load variable", node->child[1]->attr.string);
                        }
                        else if (node->child[1]->scope == Global)
                        {
                            emitRM((char *)"LD", 3, node->child[1]->loc, 0, (char *)"Load variable", node->child[1]->attr.string);
                        }

                        //LHS special comment
                        if (node->child[0]->scope == Local)
                        {
                            emitRM((char *)"LD", 4, node->child[0]->loc, 1, (char *)"load lhs variable", node->child[0]->attr.string);
                        }
                        else if (node->child[0]->scope == Global)
                        {
                            emitRM((char *)"LD", 4, node->child[0]->loc, 0, (char *)"load lhs variable", node->child[0]->attr.string);
                        }
                    }
                }
                //1 or more assignment
                else if (state == OpInCall || state == OddAssignments)
                {

                    //If we have no more assignments we can assume were done.
                    if (node->child[1] != NULL)
                    {
                        if (!(node->child[1]->nodekind == ExpK && node->child[1]->subkind.exp == AssignK))
                            node->child[1]->rhsAssign = true;
                    }

                    checkChildren(node, symTab, OddAssignments);
                }
                //if we have an identifier on the rhs
                else if (node->child[1] != NULL && (node->child[1]->nodekind == ExpK && node->child[1]->subkind.exp == IdK))
                {
                    checkChildren(node, symTab, StandardAssignment);
                }
                else
                    checkChildren(node, symTab, Normal);

                //Special assignments -= += *= /=
                if (node->op == ADDASS)
                {
                    emitRO((char *)"ADD", 3, 4, 3, (char *)"op +=");
                }
                else if (node->op == SUBASS)
                {
                    emitRO((char *)"SUB", 3, 4, 3, (char *)"op -=");
                }

                //check the scoping, this will determine the register to use Only if we are not an array
                if (node->child[0]->scope == Local && node->child[0]->op != OPEN_BRACK)
                    emitRM((char *)"ST", 3, node->child[0]->loc, 1, (char *)"Store variable", node->child[0]->attr.string);
                else if (node->child[0]->scope == Global && node->child[0]->op != OPEN_BRACK)
                    emitRM((char *)"ST", 3, node->child[0]->loc, 0, (char *)"Store variable", node->child[0]->attr.string);
                else if (node->child[0]->scope == LocalStatic && node->child[0]->op != OPEN_BRACK)
                    emitRM((char *)"ST", 3, node->child[0]->loc, 0, (char *)"Store variable", node->child[0]->attr.string);

                //reset flag
                assignWithArray = false;
                suppressPrint = false;
                */

                break;

            case InitK:

                checkChildren(node, symTab, Normal);

                break;

            case CallK:
                emitComment((char *)"EXPRESSION");
                emitComment((char *)"CALL", node->attr.name);

                //Set up up registers for ghost frame
                ghostFrameToff = tOffset;
                emitRM((char *)"ST", 1, tOffset, 1, (char *)"Store fp in ghost frame for", node->attr.name);
                //Decrement by 2 for the execution and return ticket
                decrement_toffset(2);

                //save our location in tree
                tmpNode = node;

                //Itterate over the parameters
                node = node->child[0];

                for (int i = 1; node != NULL; i++)
                {
                    emitComment((char *)"Param", i);

                    code_gen_traverse(symTab, node, Normal);

                    /*
                    //for normal constants without IdK
                    if (!node->child[0]->isOp && !node->child[0]->isArray && !(node->child[0]->nodekind == ExpK && node->child[0]->subkind.exp == AssignK))
                    {

                        if (node->child[0]->subkind.exp != IdK)
                        {
                            //Only do this if we do not have an operator.

                            if (node->child[0]->expType == Integer)
                                emitRM((char *)"LDC", 3, node->child[0]->attr.value, 6, (char *)"Load integer constant");
                            else if (node->child[0]->expType == Boolean)
                                emitRM((char *)"LDC", 3, node->child[0]->attr.value, 6, (char *)"Load Boolean constant");
                            else if (node->child[0]->expType == Char)
                                emitRM((char *)"LDC", 3, node->child[0]->attr.value, 6, (char *)"Load char constant");
                        }
                        //IdK variables
                        else if (node->child[0]->subkind.exp == IdK)
                        {
                            //check the scoping, this will determine the register to use
                            if (node->child[0]->scope == Local)
                                emitRM((char *)"LD", 3, node->child[0]->loc, 1, (char *)"Load variable", node->child[0]->attr.string);
                            else if (node->child[0]->scope == Global)
                                emitRM((char *)"LD", 3, node->child[0]->loc, 0, (char *)"Load variable", node->child[0]->attr.string);
                            else if (node->child[0]->scope == LocalStatic)
                                emitRM((char *)"LD", 3, node->child[0]->loc, 0, (char *)"Load variable", node->child[0]->attr.string);
                        }
                    }
                    //we have an op
                    else
                    {
                        //send the nodes through the check children to
                        //be handled in the switchcase

                        //we have some kind of Op in the call thats not an array or any unary operations
                        if (node->child[0]->isOp && node->child[0]->op != OPEN_BRACK && (node->child[0]->op != CHSIGN && node->child[0]->op != INC && node->child[0]->op != DEC))
                            moreThanOneVariableInCall = true;

                        checkChildren(node, symTab, OpInCall);
                        moreThanOneVariableInCall = false;
                    }
                    */

                    //Push parameter into reg
                    emitRM((char *)"ST", 3, tOffset, 1, (char *)"Push parameter");
                    //Decrement for each parameter.
                    decrement_toffset(1);

                    node = node->sibling;
                }
                //restore our position in the tree to that of
                node = tmpNode;
                emitComment((char *)"Param end", node->attr.name);

                lookupNode = sym_lookup(node->attr.name, (char *)"CallK", symTab);

                emitRM((char *)"LDA", 1, ghostFrameToff, 1, (char *)"Ghost frame becomes new active frame");
                emitRM((char *)"LDA", 3, 1, 7, (char *)"Return address in ac");
                if (lookupNode->isIo)
                    emitGotoAbs(lookupNode->loc, (char *)"CALL", node->attr.name);
                //39 is magic, because it is the number in the global space after the IO library is loaded.
                //all other functions sit after.
                else
                    emitGotoAbs(lookupNode->loc + 39, (char *)"CALL", node->attr.name);

                emitRM((char *)"LDA", 3, 0, 2, (char *)"Save the result in ac");

                emitComment((char *)"Call end", node->attr.name);

                //Set the tOffset to -2
                tOffset = ghostFrameToff;
                emitComment((char *)"TOFF set:", tOffset);

                //SPECIAL CASE!
                //For loop above is dealing with children
                isBoolKeyword = false;
                hasPushedOp = false;
                hasPushedConst = false;

                break;

            default:
                printf("PROGRAMMER ERROR UNKNOWN EXP IN CODE GEN\nSHOULD NOT GET HERE\n");
                exit(-1);
            }
        }

        else
        {
            printf("PROGRAMMER ERROR UNKNOWN NODE IN CODE GEN KIND\nSHOULD NOT GET HERE\n");
            exit(-1);
        }

        node = node->sibling;
    }
}

void init_and_globals(SymbolTable *symTab)
{
    emitComment((char *)"INIT");

    emitRM((char *)"LDA", 1, globalOffset, 0, (char *)"set first frame at end of globals");
    emitRM((char *)"ST", 1, 0, 1, (char *)"store old fp (point to self)");

    emitComment((char *)"INIT GLOBALS AND STATICS");
    //Function call here to do this
    symTab->applyToAllGlobal(checkInitGlobal);
    emitComment((char *)"END INIT GLOBALS AND STATICS");

    emitRM((char *)"LDA", 3, 1, 7, (char *)"Return address in ac");

    emitGotoAbs(mainOffset, (char *)"Jump to main");

    emitRO((char *)"HALT", 0, 0, 0, (char *)"DONE!");
    emitComment((char *)"END INIT");
}

void gen_code(SymbolTable *symTab, TreeNode *tree)
{
    //Leave space for backpatch
    emitSkip(1);
    init_IO(symTab);
    code_gen_traverse(symTab, tree, Normal);
    init_and_globals(symTab);
}