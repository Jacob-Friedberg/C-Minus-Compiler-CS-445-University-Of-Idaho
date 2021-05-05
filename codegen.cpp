#include "Tree.h"
#include "parser.tab.h"
#include "symbolTable.h"
#include "emitcode.h"
#include "codegen.h"
#include <string.h>

void code_gen_traverse(SymbolTable *symTab, TreeNode *node);

extern int globalOffset;

int tOffset = 0;
int foffset = 0;

int mainOffset;

extern char srcFilename[256];

void foo2(void *x)
{
    dumpNode((treeNode *)x);
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

void checkChildren(TreeNode *node, SymbolTable *symTab)
{

    for (int i = 0; i < MAXCHILDREN; i++)
    {
        if (node->child[i] != NULL)
        {
            //printf("Child: %d ", i);
            code_gen_traverse(symTab, node->child[i]);
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

void code_gen_traverse(SymbolTable *symTab, TreeNode *node)
{
    int ghostFrameToff = 0;
    char typing[64];
    char scoping[64];

    static bool hasPushed = false;

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

                checkChildren(node, symTab);
                break;

            case IfK:

                checkChildren(node, symTab);
                break;

            case WhileK:

                checkChildren(node, symTab);
                break;

            case ForK:

                checkChildren(node, symTab);
                break;

            case CompoundK:
                emitComment((char *)"COMPOUND");

                //set toffset to the open space of the compound;
                tOffset = node->size;

                emitComment((char *)"TOFF set:", tOffset);
                emitComment((char *)"Compound Body");
                checkChildren(node, symTab);

                tOffset = -2;
                emitComment((char *)"TOFF set:", tOffset);
                emitComment((char *)"END COMPOUND");
                break;

            case ReturnK:

                checkChildren(node, symTab);
                break;

            case BreakK:
                checkChildren(node, symTab);
                break;

            case RangeK:

                checkChildren(node, symTab);
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

                checkChildren(node, symTab);
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
                checkChildren(node, symTab);

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
                break;

            case ParamK:

                checkChildren(node, symTab);
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
                checkChildren(node, symTab);

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
                else if(node->op == EQ)
                {
                    emitRO((char *)"TEQ", 3, 4, 3, (char *)"Op ==");
                }

                break;

            case ConstantK:

                checkChildren(node, symTab);
                if (!node->parent->isOp)
                {
                    emitComment((char *)"EXPRESSION");
                    if (node->expType == Integer)
                    {
                        emitRM((char *)"LDC", 3, node->attr.value, 6, (char *)"Load integer constant");
                    }
                    else if (node->expType == Boolean)
                    {
                        emitRM((char *)"LDC", 3, node->attr.value, 6, (char *)"Load Boolean constant");
                    }
                    else if (node->expType == Char)
                    {
                        emitRM((char *)"LDC", 3, node->attr.value, 6, (char *)"Load char constant");
                    }
                }
                //our parent is an OP
                else
                {
                    if (node->expType == Integer)
                    {

                        emitRM((char *)"LDC", 3, node->attr.value, 6, (char *)"Load integer constant");
                        if (hasPushed == false && node->parent->op != CHSIGN)
                        {
                            emitRM((char *)"ST", 3, tOffset, 1, (char *)"Push left side");
                            decrement_toffset(1);
                            hasPushed = true;
                        }
                        else if (hasPushed == true && node->parent->op != CHSIGN)
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

                break;

            case IdK:

                checkChildren(node, symTab);
                break;

            case AssignK:
            {

                checkChildren(node, symTab);
                //check the scoping, this will determine the register to use
                if (node->child[0]->scope == Local)
                    emitRM((char *)"ST", 3, node->child[0]->loc, 1, (char *)"Store variable", node->child[0]->attr.string);
                else if (node->child[0]->scope == Global)
                    emitRM((char *)"ST", 3, node->child[0]->loc, 0, (char *)"Store variable", node->child[0]->attr.string);

                break;
            }
            case InitK:

                checkChildren(node, symTab);
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
                    if (!node->child[0]->isOp)
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
                            //Push parameter into reg
                            emitRM((char *)"ST", 3, tOffset, 1, (char *)"Push parameter");
                        }
                    }
                    //we have an op
                    else
                    {
                        //send the nodes through the check children to
                        //be handled in the switchcase
                        checkChildren(node, symTab);
                        emitRM((char *)"ST", 3, tOffset, 1, (char *)"Push parameter");
                    }

                    //Decrement for each parameter.
                    decrement_toffset(1);
                }
                emitComment((char *)"Param end", node->attr.name);

                lookupNode = sym_lookup(node->attr.name, (char *)"CallK", symTab);

                emitRM((char *)"LDA", 1, ghostFrameToff, 1, (char *)"Ghost frame becomes new active frame");
                emitRM((char *)"LDA", 3, 1, 7, (char *)"Return address in ac");
                emitGotoAbs(lookupNode->loc, (char *)"CALL", node->attr.name);
                emitRM((char *)"LDA", 3, 0, 2, (char *)"Save the result in ac");

                emitComment((char *)"Call end", node->attr.name);

                //Set the tOffset to -2
                tOffset = ghostFrameToff;
                emitComment((char *)"TOFF set:", tOffset);

                //SPECIAL CASE!
                //For loop above is dealing with children

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

void init_and_globals()
{
    emitComment((char *)"INIT");

    emitRM((char *)"LDA", 1, globalOffset, 0, (char *)"set first frame at end of globals");
    emitRM((char *)"ST", 1, 0, 1, (char *)"store old fp (point to self)");

    emitComment((char *)"INIT GLOBALS AND STATICS");
    //Function call here to do this
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
    code_gen_traverse(symTab, tree);
    init_and_globals();
}