#include "Tree.h"
#include "parser.tab.h"
#include "symbolTable.h"
#include "emitcode.h"
#include "codegen.h"
#include <string.h>
#include <string>

void code_gen_traverse(SymbolTable *symTab, TreeNode *node, TraverseState state);

extern int globalOffset;

int tOffset = 0;
int foffset = 0;

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

void code_gen_traverse(SymbolTable *symTab, TreeNode *node, TraverseState state)
{
    int ghostFrameToff = 0;
    char typing[64];
    char scoping[64];

    static bool hasPushed = false;
    static bool hasPushedOpArray = false;
    static bool isUnary = false;
    static bool isBoolKeyword = false;
    static bool suppressPrint = false;
    static bool assignWithArray = false;
    static bool arrayInOp = false;
    static bool suppressCompoundBody = false;
    static bool moreThanOneArrayInCall = false;

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
                    emitComment((char *)"Compound Body");

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
                    emitComment("");
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

                if (node->op == QUESTION || node->op == CHSIGN)
                {
                    isUnary = true;
                }

                if (node->op == OPEN_BRACK && state == OpInCall)
                {
                    arrayInOp = true;

                    checkChildren(node, symTab, ArrayInCall);

                    emitRO((char *)"SUB", 3, 4, 3, (char *)"compute location from index");
                    emitRM((char *)"LD", 3, 0, 3, (char *)"Load array element");

                    if (hasPushedOpArray == false && moreThanOneArrayInCall)
                    {
                        emitRM((char *)"ST", 3, tOffset, 1, (char *)"Push left side");
                        hasPushedOpArray = true;
                        decrement_toffset(1);
                    }
                    else if (hasPushedOpArray && moreThanOneArrayInCall)
                    {
                        increment_toffset(1);
                        emitRM((char *)"LD", 4, tOffset, 1, (char *)"Pop left into ac1");
                        hasPushedOpArray = false;
                    }
                }
                //we have a INC or DEC in the functionCall with an array
                //HACK going to skip const traversal and doing it here.
                else if (node->op == OPEN_BRACK && state == OddAssignments)
                {
                    arrayInOp = true;

                    emitRM((char *)"LDC", 3, node->child[1]->attr.value, 6, (char *)"Load integer constant");

                    if (node->child[0]->scope == Local)
                        emitRM((char *)"LDA", 5, (node->child[0]->loc) - 1, 1, (char *)"Load address of base of array", node->child[0]->attr.string);
                    else if (node->child[0]->scope == Global)
                        emitRM((char *)"LDA", 5, (node->child[0]->loc) - 1, 0, (char *)"Load address of base of array", node->child[0]->attr.string);
                    else if (node->child[0]->scope == Parameter)
                        emitRM((char *)"LD", 5, (node->child[0]->loc), 1, (char *)"Load address of base of array", node->child[0]->attr.string);

                    emitRO((char *)"SUB", 5, 5, 3, (char *)"Compute offset of value");

                    checkChildren(node, symTab, OddAssignments);
                }
                else
                    checkChildren(node, symTab, state);

                //array processing, both children have been done already
                //so now to get the proper registers

                //is a bool keyword with 2+ expressions
                if (node->parent != NULL && (node->parent->op == AND || node->parent->op == OR) && !arrayInOp)
                {
                    isBoolKeyword = true;
                }

                //need to pop
                //We dont pop for arrays since we do that for them elsewhere specifically
                if ((node->op == AND || node->op == OR) && isBoolKeyword)
                {

                    increment_toffset(1);
                    emitRM((char *)"LD", 4, tOffset, 1, (char *)"Pop leftss into ac1");
                }

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

                break;

            case ConstantK:

                checkChildren(node, symTab, Normal);
                //Lone integer constants
                if (state == Normal)
                {
                    if (suppressPrint == false)
                        emitComment((char *)"EXPRESSION");

                    if (node->expType == Integer)
                    {
                        emitRM((char *)"LDC", 3, node->attr.value, 6, (char *)"Load integer constant");

                        //Array Processing for the index of the array
                        if (node->parent->op == OPEN_BRACK)
                        {
                            emitRM((char *)"ST", 3, tOffset, 1, (char *)"Push index");
                            decrement_toffset(1);
                            suppressPrint = true;
                        }
                        else if (node->parent->op != OPEN_BRACK && assignWithArray)
                        {
                            increment_toffset(1);
                        }
                    }
                    else if (node->expType == Boolean)
                    {
                        emitRM((char *)"LDC", 3, node->attr.value, 6, (char *)"Load Boolean constant");

                        //Array Processing for the index of the array
                        if (node->parent->op == OPEN_BRACK)
                        {
                            emitRM((char *)"ST", 3, tOffset, 1, (char *)"Push index");
                            decrement_toffset(1);
                            suppressPrint = true;
                        }
                        else if (node->parent->op != OPEN_BRACK && assignWithArray)
                        {
                            increment_toffset(1);
                        }
                    }
                    else if (node->expType == Char)
                    {
                        emitRM((char *)"LDC", 3, node->attr.value, 6, (char *)"Load char constant");
                    }
                }
                //our parent is an OP
                else if (state == OpInCall)
                {
                    if (node->expType == Integer)
                    {
                        if (isBoolKeyword)
                        {
                            emitRM((char *)"ST", 3, tOffset, 1, (char *)"Push left side");
                            decrement_toffset(1);
                            isBoolKeyword = false;
                        }

                        if (isUnary)
                        {
                            emitRM((char *)"LDC", 3, node->attr.value, 6, (char *)"Load integer constant");
                            isUnary = false;
                        }
                        else if (hasPushed == false && node->parent->op != CHSIGN)
                        {
                            emitRM((char *)"ST", 3, tOffset, 1, (char *)"Push left side");
                            decrement_toffset(1);

                            if (isUnary == false)
                                emitRM((char *)"LDC", 3, node->attr.value, 6, (char *)"Load integer constant");
                            hasPushed = true;
                        }
                        else if (hasPushed == true && node->parent->op != CHSIGN)
                        {
                            if (isUnary == false)
                                emitRM((char *)"LDC", 3, node->attr.value, 6, (char *)"Load integer constant");

                            increment_toffset(1);
                            emitRM((char *)"LD", 4, tOffset, 1, (char *)"Pop left into ac1");
                            hasPushed = false;
                        }

                        //If we have any hanging pushed we need to pop them left.
                        if (hasPushed == true && node->parent->op != CHSIGN)
                        {
                            increment_toffset(1);
                            emitRM((char *)"LD", 4, tOffset, 1, (char *)"Pop left into ac1");
                            hasPushed = false;
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

                        if (hasPushed == false)
                        {
                            emitRM((char *)"ST", 3, tOffset, 1, (char *)"Push left side");
                            decrement_toffset(1);
                            hasPushed = true;
                        }
                        else
                        {
                            increment_toffset(1);
                            emitRM((char *)"LD", 4, tOffset, 1, (char *)"Pop left into ac1");
                            hasPushed = false;
                        }
                    }
                }
                else if (state == ArrayInCall)
                {
                    emitRM((char *)"LDC", 3, node->attr.value, 6, (char *)"Load integer constant");

                    if (hasPushed == false)
                    {
                        emitRM((char *)"ST", 3, tOffset, 1, (char *)"Push left side");
                        decrement_toffset(1);
                        hasPushed = true;
                    }
                    else
                    {
                        increment_toffset(1);
                        emitRM((char *)"LD", 4, tOffset, 1, (char *)"Pop left into ac1");
                        hasPushed = false;
                    }
                }

                break;

            case IdK:

                checkChildren(node, symTab, Normal);

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
                    }

                    //Dont want to do this twice, if we are an array we have code gen elsewhere
                    if (hasPushed == false && !node->isArray /*&& node->parent->op == OPEN_BRACK*/)
                    {
                        emitRM((char *)"ST", 3, tOffset, 1, (char *)"Push left side");
                        decrement_toffset(1);
                        hasPushed = true;
                    }
                    else if(hasPushed && !node->isArray/*&& node->parent->op == OPEN_BRACK*/)
                    {
                        increment_toffset(1);
                        emitRM((char *)"LD", 4, tOffset, 1, (char *)"Pop left into ac1");
                        hasPushed = false;
                    }
                }
                else if (state == ArrayInCall)
                {
                    if (node->scope == Local)
                        emitRM((char *)"LDA", 3, node->loc - 1, 1, (char *)"Load address of base of array", node->attr.string);
                    else if (node->scope == Global)
                        emitRM((char *)"LDA", 3, node->loc - 1, 0, (char *)"Load address of base of array", node->attr.string);
                    else if (node->scope == Parameter)
                        emitRM((char *)"LD", 3, node->loc , 1, (char *)"Load address of base of array", node->attr.string);

                    if (hasPushed == false)
                    {
                        emitRM((char *)"ST", 3, tOffset, 1, (char *)"Push left side");
                        decrement_toffset(1);
                        hasPushed = true;
                    }
                    else
                    {
                        increment_toffset(1);
                        emitRM((char *)"LD", 4, tOffset, 1, (char *)"Pop left into ac1");
                        hasPushed = false;
                    }
                }
                //Assignment += -= /= etc.
                else if (state == OddAssignments && !arrayInOp)
                {
                    //Unary inc or dec
                    if (node->lhsAssign)
                    {
                        if (node->scope == Local)
                            emitRM((char *)"LD", 3, node->loc, 1, (char *)"load lhs variable", node->attr.string);
                        else if (node->scope == Global)
                            emitRM((char *)"LD", 3, node->loc, 0, (char *)"load lhs variable", node->attr.string);
                        else if (node->scope == LocalStatic)
                            emitRM((char *)"LD", 3, node->loc, 0, (char *)"load lhs variable", node->attr.string);

                        //Might have to wrap this in scope again.
                        if (node->parent->op == INC)
                            emitRM((char *)"LDA", 3, 1, 3, (char *)"increment value of", node->attr.string);
                        else
                            emitRM((char *)"LDA", 3, -1, 3, (char *)"decrement value of", node->attr.string);
                    }

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
                //Arrays with INC and DEC
                else if (state == OddAssignments && arrayInOp)
                {
                    emitRM((char *)"LD", 3, 0, 5, (char *)"load lhs variable", node->attr.string);

                    //2 levels of for the assign ++ or --
                    if (node->parent->parent->op == INC)
                        emitRM((char *)"LDA", 3, 1, 3, (char *)"increment value of", node->attr.string);
                    else
                        emitRM((char *)"LDA", 3, -1, 3, (char *)"decrement value of", node->attr.string);

                    emitRM((char *)"ST", 3, 0, 5, (char *)"Store variable", node->attr.string);
                }

                

                break;

            case AssignK:
            {
                if (node->child[0]->op == OPEN_BRACK)
                {
                    assignWithArray = true;
                }

                if (node->op == INC || node->op == DEC)
                {
                    node->child[0]->lhsAssign = true;
                    checkChildren(node, symTab, OddAssignments);
                }
                else if (node->op == ADDASS || node->op == MULASS || node->op == SUBASS || node->op == DIVASS)
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
                else
                    checkChildren(node, symTab, Normal);

                if (node->child[0]->op == OPEN_BRACK && node->op != INC && node->op != DEC)
                {
                    emitRM((char *)"LD", 4, tOffset, 1, (char *)"Pop index");

                    if (node->child[0]->scope == Local)
                        emitRM((char *)"LDA", 5, (node->child[0]->loc) - 1, 1, (char *)"Load address of base of array", node->child[0]->arrayIdentf);
                    else if (node->child[0]->scope == Global)
                        emitRM((char *)"LDA", 5, (node->child[0]->loc) - 1, 0, (char *)"Load address of base of array", node->child[0]->arrayIdentf);

                    emitRO((char *)"SUB", 5, 5, 4, (char *)"Compute offset of value");
                    emitRM((char *)"ST", 3, 0, 5, (char *)"Store variable", node->child[0]->arrayIdentf);
                }

                //Special assignments -= += *= /=
                if (node->op == ADDASS)
                {
                    emitRO((char *)"ADD", 3, 4, 3, (char *)"op +=");
                }
                else if (node->op == SUBASS)
                {
                    emitRO((char *)"SUB", 3, 4, 3, (char *)"op -=");
                }

                //check the scoping, this will determine the register to use
                if (node->child[0]->scope == Local && node->child[0]->op != OPEN_BRACK)
                    emitRM((char *)"ST", 3, node->child[0]->loc, 1, (char *)"Store variable", node->child[0]->attr.string);
                else if (node->child[0]->scope == Global && node->child[0]->op != OPEN_BRACK)
                    emitRM((char *)"ST", 3, node->child[0]->loc, 0, (char *)"Store variable", node->child[0]->attr.string);
                else if (node->child[0]->scope == LocalStatic && node->child[0]->op != OPEN_BRACK)
                    emitRM((char *)"ST", 3, node->child[0]->loc, 0, (char *)"Store variable", node->child[0]->attr.string);

                //reset flag
                assignWithArray = false;
                suppressPrint = false;

                break;
            }
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

                for (int i = 1; i <= node->numParams; i++)
                {
                    emitComment((char *)"Param", i);
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
                            //Push parameter into reg
                            emitRM((char *)"ST", 3, tOffset, 1, (char *)"Push parameter");
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

                            //Push parameter into reg
                            emitRM((char *)"ST", 3, tOffset, 1, (char *)"Push parameter");
                        }
                    }
                    //we have an op
                    else
                    {
                        //send the nodes through the check children to
                        //be handled in the switchcase

                        //we have some kind of Op in the call
                        if (node->child[0]->isOp && node->child[0]->op != OPEN_BRACK)
                            moreThanOneArrayInCall = true;

                        checkChildren(node, symTab, OpInCall);
                        emitRM((char *)"ST", 3, tOffset, 1, (char *)"Push parameter");
                        moreThanOneArrayInCall = false;
                    }

                    //Decrement for each parameter.
                    decrement_toffset(1);
                }
                emitComment((char *)"Param end", node->attr.name);

                lookupNode = sym_lookup(node->attr.name, (char *)"CallK", symTab);

                emitRM((char *)"LDA", 1, ghostFrameToff, 1, (char *)"Ghost frame becomes new active frame");
                emitRM((char *)"LDA", 3, 1, 7, (char *)"Return address in ac");
                if(lookupNode->isIo)
                    emitGotoAbs(lookupNode->loc, (char *)"CALL", node->attr.name);
                //39 is magic, because it is the number in the global space after the IO library is loaded.
                //all other functions sit after.
                else
                    emitGotoAbs(lookupNode->loc+39, (char *)"CALL", node->attr.name);
                    
                emitRM((char *)"LDA", 3, 0, 2, (char *)"Save the result in ac");

                emitComment((char *)"Call end", node->attr.name);

                //Set the tOffset to -2
                tOffset = ghostFrameToff;
                emitComment((char *)"TOFF set:", tOffset);

                //SPECIAL CASE!
                //For loop above is dealing with children
                isBoolKeyword = false;

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