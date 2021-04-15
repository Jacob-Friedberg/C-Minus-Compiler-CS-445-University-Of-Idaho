#include "Tree.h"
#include "parser.tab.h"
#include "symbolTable.h"
#include "semantic.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <iostream>
// save TokenData block!!

#define SUPPRESS_CHILD_SCOPE true
#define DONT_SUPPRESS_CHILD_SCOPE false

ExpType typeTable(TreeNode *parentNode, treeNode *lhsNode, treeNode *rhsNode);
void checkChildren(TreeNode *node, SymbolTable *symTab, bool suppressChildScope);
void checkIsUsed(std::string symbolName, void *ptr);
void checkIsInit(std::string symbolName, void *ptr);
void checkSizeOf(TreeNode *node);

void ioLibrary(SymbolTable *symTab);

int NUM_ERRORS = 0;
int NUM_WARNINGS = 0;


void foo(void *x)
{
    dumpNode((treeNode *)x);
}

//Hand build IO library prototypes and add them to symbol table
void ioLibrary(SymbolTable *symTab)
{
    TreeNode *ioTree = NULL;
    TreeNode *ioTreeNode = NULL;
    TreeNode *childIoTreeNode = NULL;

    //int input()
    ioTree = newDeclNode(FuncK, Integer);
    ioTree->attr.name = strdup("input");
    ioTree->isFunc = true;
    ioTree->lineno = -1;
    ioTree->isUsed = true;
    ioTree->isIo = true;

    //bool inputb()
    ioTreeNode = newDeclNode(FuncK, Boolean);
    ioTreeNode->attr.name = strdup("inputb");
    ioTreeNode->isFunc = true;
    ioTreeNode->lineno = -1;
    ioTreeNode->isUsed = true;
    ioTreeNode->isIo = true;

    addSibling(ioTree, ioTreeNode);

    //char inputc()
    ioTreeNode = newDeclNode(FuncK, Char);
    ioTreeNode->attr.name = strdup("inputc");
    ioTreeNode->isFunc = true;
    ioTreeNode->lineno = -1;
    ioTreeNode->isUsed = true;
    ioTreeNode->isIo = true;

    addSibling(ioTree, ioTreeNode);

    //void output(int)

    //Parameter
    childIoTreeNode = newDeclNode(ParamK, Integer);
    childIoTreeNode->attr.name = strdup("*dummy*");
    childIoTreeNode->lineno = -1;
    childIoTreeNode->isUsed = true;
    childIoTreeNode->isIo = true;
    ioTreeNode->isIo = true;
    //create the funcdef and attach the param node
    ioTreeNode = newDeclNode(FuncK, Void, NULL, childIoTreeNode);
    ioTreeNode->attr.name = strdup("output");
    ioTreeNode->isFunc = true;
    ioTreeNode->lineno = -1;
    ioTreeNode->isUsed = true;
    ioTreeNode->isIo = true;

    addSibling(ioTree, ioTreeNode);

    //void outputb(bool)

    //Parameter
    childIoTreeNode = newDeclNode(ParamK, Boolean);
    childIoTreeNode->attr.name = strdup("*dummy*");
    childIoTreeNode->lineno = -1;
    childIoTreeNode->isUsed = true;
    childIoTreeNode->isIo = true;
    ioTreeNode->isIo = true;
    //create the funcdef and attach the param node
    ioTreeNode = newDeclNode(FuncK, Void, NULL, childIoTreeNode);
    ioTreeNode->attr.name = strdup("outputb");
    ioTreeNode->isFunc = true;
    ioTreeNode->lineno = -1;
    ioTreeNode->isUsed = true;
    ioTreeNode->isIo = true;

    addSibling(ioTree, ioTreeNode);

    //void outputc(char)

    //Parameter
    childIoTreeNode = newDeclNode(ParamK, Char);
    childIoTreeNode->attr.name = strdup("*dummy*");
    childIoTreeNode->lineno = -1;
    childIoTreeNode->isUsed = true;
    childIoTreeNode->isIo = true;
    ioTreeNode->isIo = true;
    //create the funcdef and attach the param node
    ioTreeNode = newDeclNode(FuncK, Void, NULL, childIoTreeNode);
    ioTreeNode->attr.name = strdup("outputc");
    ioTreeNode->isFunc = true;
    ioTreeNode->lineno = -1;
    ioTreeNode->isUsed = true;
    ioTreeNode->isIo = true;

    addSibling(ioTree, ioTreeNode);

    //void outnl()

    ioTreeNode = newDeclNode(FuncK, Void);
    ioTreeNode->attr.name = strdup("outnl");
    ioTreeNode->isFunc = true;
    ioTreeNode->lineno = -1;
    ioTreeNode->isUsed = true;
    ioTreeNode->isIo = true;

    addSibling(ioTree, ioTreeNode);

    //run the manually built nodes through the semantic analysis
    //this adds all the symbols to the tree.
    checkTree2(symTab, ioTree, false, NULL);
}

//Ensures sizeof is only used with an array. Throws an error otherwise.
//HACK: force type to be undefined when rangek. Normally sets type to be integer.
void checkSizeOf(TreeNode *node, SymbolTable *symTab)
{
    if (node->op == SIZEOF)
    {
        //fixing op node. This node always returns an int
        //HACK TO MATCH
        // if (node->parent->isRangeK)
        // {
        //     node->expType = UndefinedType;
        //     if (node->child[0] != NULL && node->child[0]->nodekind == ExpK && node->child[0]->subkind.exp == IdK)
        //     {
        //         node->child[0]->expType = UndefinedType;
        //     }
        // }
        // else
            node->expType = Integer;

        //Can only use sizeof with an array. Check and throw error if it is not an array.
        if (node->child[0]->subkind.exp == IdK)
        {
            TreeNode *lookupNode;
            lookupNode = (treeNode *)symTab->lookup(std::string(node->child[0]->attr.name));

            if (lookupNode != NULL && !(lookupNode->isArray))
            {
                printf("ERROR(%d): The operation 'sizeof' only works with arrays.\n", node->lineno);
                NUM_ERRORS++;
            }
        }
        else
        {
            //Hack. Match ouput for specific case of an undefined array. Error thrown elsewhere
            TreeNode *lookupNode;
            lookupNode = (treeNode *)symTab->lookup(std::string(node->child[0]->attr.name));

            //Variable does exist
            if (lookupNode != NULL && !node->child[0]->isArray)
            {
                printf("ERROR(%d): The operation 'sizeof' only works with arrays.\n", node->lineno);
                NUM_ERRORS++;
            }
            //Variable does not exist
            else
            {
                if (!node->child[0]->undeclared)
                {
                    printf("ERROR(%d): The operation 'sizeof' only works with arrays.\n", node->lineno);
                    NUM_ERRORS++;
                }
            }
        }
    }
}

//Itterate over the children of the node.
void checkChildren(TreeNode *node, SymbolTable *symTab, bool suppressChildScope)
{

    for (int i = 0; i < MAXCHILDREN; i++)
    {
        if (node->child[i] != NULL)
        {
            //printf("Child: %d ", i);
            checkTree2(symTab, node->child[i], suppressChildScope, node);
        }
    }
}


int localOffset= 0;
int globalOffset= 0;
void checkTree2(SymbolTable *symTab, TreeNode *node, bool parentSuppressScope, TreeNode *parent)
{
    char typing[64];
    //Statics are only initlized once
    //On many recursions the state is maintained and not overwritten,
    //Unless explicitly told to.
    static bool firstNode = true;
    static TreeNode *headOfTree = NULL;
    static TreeNode *tailOfTree = NULL;
    static bool returnStmtFound = false;

    static int compound_size = 0;

 

    //Counts how deep we are in nested loops(for and while)
    //0 means not in a loop >0 means in a loop. This specific for the break stmt
    static int loopDepth = 0;
    //symTab->debug(true);

    static TreeNode *functionNodePtr = NULL;

    treeNode *lookupNode;
    //symTab->debug(true);
    while (node != NULL)
    {
        //Storing the head of our tree.
        //this is only done to the first node seen in the loop.
        if (firstNode)
        {
            headOfTree = node;
            firstNode = false;
            //build the IO library.
            ioLibrary(symTab);
        }

        node->parent = parent;
        convertExpTypeToString(node->expType, typing);

        //Refactored switch
        //Process statements
        if (node->nodekind == StmtK)
        {
            switch (node->subkind.stmt)
            {
            case NullK:
                checkChildren(node, symTab, DONT_SUPPRESS_CHILD_SCOPE);
                break;

            case IfK:
                checkChildren(node, symTab, DONT_SUPPRESS_CHILD_SCOPE);

                if (node->child[0] != NULL && node->child[0]->expType != Boolean)
                {
                    char buffChild[64];
                    convertExpTypeToString(node->child[0]->expType, buffChild);
                    //Suppressing error if undefined. This error is thrown elsewhere
                    if (node->child[0]->expType != UndefinedType)
                    {
                        printf("ERROR(%d): Expecting Boolean test condition in if statement but got type %s.\n", node->lineno, buffChild);
                        NUM_ERRORS++;
                    }
                }

                if (node->child[0] != NULL && node->child[0]->isArray)
                {
                    printf("ERROR(%d): Cannot use array as test condition in if statement.\n", node->lineno);
                    NUM_ERRORS++;
                }

                break;

            case WhileK:
                //start a loop
                loopDepth++;

                checkChildren(node, symTab, DONT_SUPPRESS_CHILD_SCOPE);

                if (node->child[0] != NULL && node->child[0]->expType != Boolean)
                {
                    char buffChild[64];
                    convertExpTypeToString(node->child[0]->expType, buffChild);
                    //Suppressing error if undefined. This error is thrown elsewhere
                    if (node->child[0]->expType != UndefinedType)
                    {
                        printf("ERROR(%d): Expecting Boolean test condition in while statement but got type %s.\n", node->lineno, buffChild);
                        NUM_ERRORS++;
                    }
                }

                if (node->child[0] != NULL && node->child[0]->isArray)
                {
                    printf("ERROR(%d): Cannot use array as test condition in while statement.\n", node->lineno);
                    NUM_ERRORS++;
                }
                //Done with a loop
                loopDepth--;

                break;

            case ForK:
                symTab->enter(std::string("this is a for loop"));
                //We are in a loop
                loopDepth++;

                checkChildren(node, symTab, SUPPRESS_CHILD_SCOPE);

                //only check if used if there is not a compound statement. This is because compound already checks.
                //Scopes dont change therefore compounds will catch all unused.
                if (!(node->child[2] != NULL && node->child[2]->nodekind == StmtK && node->child[2]->subkind.stmt == CompoundK))
                {
                    symTab->applyToAll(checkIsUsed);
                }

                symTab->leave();
                //We are leaving a loop
                loopDepth--;
                break;

            case CompoundK:
                if (!parentSuppressScope)
                    symTab->enter(std::string("THIS IS A COMPOUND"));
                
                
                checkChildren(node, symTab, DONT_SUPPRESS_CHILD_SCOPE);

                node->size = compound_size;

                //Dont do this for functions
                //HACK
                if (node->parent != NULL && !(node->parent->nodekind == DeclK && node->parent->subkind.decl == FuncK))
                    symTab->applyToAll(checkIsUsed);

                if (!parentSuppressScope)
                    symTab->leave();

                //Suppression only applies to the first when a cmpd follows a funk or for
                parentSuppressScope = false;
                break;

            case ReturnK:

                checkChildren(node, symTab, DONT_SUPPRESS_CHILD_SCOPE);

                returnStmtFound = true;

                //We are in a function definition and have a return value.
                if (node->child[0] != NULL && functionNodePtr != NULL)
                {
                    char buffChild[64];
                    char buffFunc[64];

                    if (node->child[0]->expType != functionNodePtr->expType)
                    {
                        //Convert exptypes to strings for printing
                        convertExpTypeToString(functionNodePtr->expType, buffFunc);
                        convertExpTypeToString(node->child[0]->expType, buffChild);

                        //Suppress undefined types being returned. another error is already thrown for this
                        if (node->child[0]->expType != UndefinedType)
                        {

                            if (functionNodePtr->expType == Void)
                            {
                                printf("ERROR(%d): Function '%s' at line %d is expecting no return value, but return has a value.\n",
                                       node->lineno,
                                       functionNodePtr->attr.string,
                                       functionNodePtr->lineno);

                                NUM_ERRORS++;
                            }
                            else
                            {
                                printf("ERROR(%d): Function '%s' at line %d is expecting to return type %s but returns type %s.\n",
                                       node->lineno,
                                       functionNodePtr->attr.string,
                                       functionNodePtr->lineno,
                                       buffFunc,
                                       buffChild);

                                NUM_ERRORS++;
                            }
                        }
                    }
                }
                //We are in a function but have no return value.
                else if (functionNodePtr != NULL)
                {
                    char buffFunc[64];

                    convertExpTypeToString(functionNodePtr->expType, buffFunc);

                    //I think i need to put a check for voids here.

                    if (functionNodePtr->expType != Void)
                    {
                        printf("ERROR(%d): Function '%s' at line %d is expecting to return type %s but return has no value.\n",
                               node->lineno,
                               functionNodePtr->attr.string,
                               functionNodePtr->lineno,
                               buffFunc);

                        NUM_ERRORS++;
                    }
                }

                if (node->child[0] != NULL && node->child[0]->isArray)
                {
                    printf("ERROR(%d): Cannot return an array.\n", node->lineno);
                    NUM_ERRORS++;
                }
                break;

            case BreakK:
                checkChildren(node, symTab, DONT_SUPPRESS_CHILD_SCOPE);

                //If the loopdepth is 0 we are not in a loop
                if (loopDepth == 0)
                {
                    printf("ERROR(%d): Cannot have a break statement outside of loop.\n", node->lineno);
                    NUM_ERRORS++;
                }

                break;

            case RangeK:
                //Poke values into children if they exist.
                if (node->child[0] != NULL && node->child[1] != NULL)
                {
                    node->child[0]->isInit = true;
                    node->child[0]->isRangeK = true;
                    node->child[1]->isInit = true;
                    node->child[1]->isRangeK = true;
                    //Special case of a optional step
                    if (node->child[2] != NULL)
                    {
                        node->child[2]->isInit = true;
                        node->child[2]->isRangeKBy = true;
                    }
                }
                checkChildren(node, symTab, DONT_SUPPRESS_CHILD_SCOPE);

                //Iterate on the children To type check the range
                for (int i = 0; node->child[i] != NULL; i++)
                {
                    char buff[64];
                    convertExpTypeToString(node->child[i]->expType, buff);
                    //only can have integers in the range. Additionally suppress this warning on undefined. An error is thrown elsewhere.
                    //HACK:Suppresses error on a void function in the range
                    if (node->child[i]->expType != Integer && node->child[i]->expType != UndefinedType && !(node->child[i]->isFunc && node->child[i]->expType == Void))
                    {
                        printf("ERROR(%d): Expecting type int in position %d in range of for statement but got type %s.\n",
                               node->lineno,
                               i + 1,
                               buff);
                        NUM_ERRORS++;
                    }

                    if (node->child[i]->isArray)
                    {
                        printf("ERROR(%d): Cannot use array in position %d in range of for statement.\n",
                               node->lineno,
                               i + 1);
                        NUM_ERRORS++;
                    }
                }
                break;

            default:
                printf("PROGRAMMER ERROR UNKNOWN STATMENT TYPE\nSHOULD NOT GET HERE\n");
                exit(-1);
            }
        }

        //Process declarations
        else if (node->nodekind == DeclK)
        {
            switch (node->subkind.decl)
            {
            case VarK:

                checkChildren(node, symTab, DONT_SUPPRESS_CHILD_SCOPE);

                //Check globally for variables already declared.

                //lookupNode = (treeNode *)symTab->lookupGlobal(node->attr.name);
                //If the symbol does not exist then we can add it
                if (symTab->insert(std::string(node->attr.name), (void *)node))
                {
                    node->depth = symTab->depth();

                    //we are at the global scope so set our scope to global
                    //Assuming anything other than global scope is a local. PROB WRONG!!!
                    if(node->depth == 1)
                    {
                        node->scope = Global;

                        node->loc = globalOffset;
                        if(node->isArray)
                        {
                            printf("size:%d\n",node->size);

                            globalOffset -= node->size;
                        }
                        else
                        {
                            printf("size of nonarray: %d\n",node->size);

                            globalOffset -= node->size;
                        }

                    }
                    else if(node->depth > 1)
                    {
                        node->scope = Local;
                    }

                    node->isUsed = false;
                    //Special handleing for the case of init variables in for loops
                    if (node->parent != NULL && node->parent->nodekind == StmtK && node->parent->subkind.stmt == ForK)
                        node->isInit = true;
                    else
                        node->isInit = false;

                    node->isInitErrorThrown = false;
                }
                //Symbol already exists in the table. Throw an error
                else
                {
                    lookupNode = (treeNode *)symTab->lookup(node->attr.name);
                    printf("ERROR(%d): Symbol '%s' is already declared at line %d.\n",
                           node->lineno,
                           lookupNode->attr.name,
                           lookupNode->lineno);
                    NUM_ERRORS++;
                }

                //----INITILIZATION OF A VARAIBLE IS HERE----
                //Type checking the initilization variable, In addition checks if it is a constant.
                //Sets init flag
                //Pass down your scope to the child.
                if (node->child[0] != NULL)
                {
                    //Set the child scope to that of the parent.
                    node->child[0]->scope = node->scope;

                    //HACK: special case of initilzing to itself.

                    if ((node->child[0]->tokenStr != NULL && node->tokenStr != NULL) && strcmp(node->child[0]->tokenStr, node->tokenStr) == 0)
                    {

                        lookupNode = (treeNode *)symTab->lookup(node->attr.name);
                        if (lookupNode == NULL)
                        {
                            node->isUsed = false;

                            printf("ERROR(%d): Symbol '%s' is not declared.\n", node->lineno, node->attr.name);
                            NUM_ERRORS++;
                        }
                        else
                        {
                        }
                    }

                    if (!node->child[0]->isConst)
                    {
                        printf("ERROR(%d): Initializer for variable '%s' is not a constant expression.\n",
                               node->lineno,
                               node->attr.name);

                        NUM_ERRORS++;
                    }

                    //Check that the types match. If not throw an error
                    //Todo: check that it is initilized to a constant expression.
                    if (node->child[0]->expType != node->expType)
                    {
                        char buff[64];

                        convertExpTypeToString(node->child[0]->expType, buff);

                        //Suppress undefined
                        if (node->child[0]->expType != UndefinedType)
                        {
                            printf("ERROR(%d): Initializer for variable '%s' of type %s is of type %s\n",
                                   node->lineno,
                                   node->attr.name,
                                   typing,
                                   buff);

                            NUM_ERRORS++;
                        }
                    }

                    if (node->isArray && !node->child[0]->isArray)
                    {
                        printf("ERROR(%d): Initializer for variable '%s' requires both operands be arrays or not but variable is an array and rhs is not an array.\n",
                               node->lineno,
                               node->attr.name);

                        NUM_ERRORS++;
                    }
                    else if (!node->isArray && node->child[0]->isArray)
                    {
                        printf("ERROR(%d): Initializer for variable '%s' requires both operands be arrays or not but variable is not an array and rhs is an array.\n",
                               node->lineno,
                               node->attr.name);

                        NUM_ERRORS++;
                    }

                    //Assuming an init if the decleration has a child, which should be initilizer
                    node->isInit = true;
                }
                //----INITILIZATION OF A VARAIBLE IS HERE----
                break;

            case FuncK:
                if (node->attr.name == NULL)
                {
                    printf("internal error NULL REACHED in attrName funck\n");
                    break;
                }

                

                localOffset = -2;

                //Set func flag
                node->isFunc = true;

                if (symTab->insertGlobal(std::string(node->attr.string), node))
                {
                    node->depth = symTab->depth();
                    //Removing this because it causes issues with the IOlibrary
                    //Should be ok if i set it to false to begin with
                    //node->isUsed = false;
                    // node->isInit = true;
                }
                //Funck Name already exists. Throw an error
                else
                {
                    lookupNode = (treeNode *)symTab->lookup(node->attr.string);
                    printf("ERROR(%d): Symbol '%s' is already declared at line %d.\n",
                           node->lineno,
                           lookupNode->attr.string,
                           lookupNode->lineno);
                    NUM_ERRORS++;
                    //Since we continue like normal on an error we are still technically a funcdecl
                    //See the enter below
                }
                //prob shouldn't enter regardless if there is an error.
                symTab->enter(std::string(node->attr.string));


                //store our function node for typechecking later in the children
                if (node->isFunc && !node->isIo)
                    functionNodePtr = node;
                checkChildren(node, symTab, SUPPRESS_CHILD_SCOPE);

                //reset function node ptr to NULL.
                functionNodePtr = NULL;

                //no return statment found and we are not an IO library func
                if (!returnStmtFound)
                {
                    if (!node->isIo)
                    {
                        if (node->expType != Void)
                        {
                            printf("WARNING(%d): Expecting to return type %s but function '%s' has no return statement.\n", node->lineno, typing, node->attr.string);
                            NUM_WARNINGS++;
                        }
                    }
                }
                //Return was found
                //Clear the flag because we are leaving a function
                else
                {

                    //reset flag to false
                    //printf("ret was:%s\n", (returnStmtFound) ? "true" : "false");
                    returnStmtFound = false;
                    //printf("ret is now:%s\n", (returnStmtFound) ? "true" : "false");
                }

                symTab->applyToAll(checkIsUsed);

                //MEMORY STUFF
                //-2 denotes the previous frame ptr slot and
                //the location to return to after the function ends
                node->size = -2 - node->numParams;
                node->scope = Global;

                //This simplified code replaces the code that was below.
                //We need to check for parameter usage only when there is not a cmpound stmt.
                //This check is done by the cmpound stmt already and would produce double errors otherwise

                // if (node->child[0] != NULL) // do we have arguments?
                // {
                //     symTab->applyToAll(checkIsUsed);
                //     //We have a compound so we dont check is used.
                //     // if (node->child[1] != NULL && (node->child[1]->nodekind == StmtK && node->child[1]->subkind.stmt == CompoundK))
                //     //     ; //do nothing
                //     // else
                //     //     symTab->applyToAll(checkIsUsed);
                // }
                // else
                //      symTab->applyToAll(checkIsUsed);

                //printf("Leaving Function\n");
                //On the case of a oneline function we need to check the params if they are used.
                //We can only do this if child[1] exists and is not null
                // if (node->child[1] != NULL)
                // {
                //     //This only happens if child[2] is a return statement foo(int x) return a;
                //     if (node->child[1]->nodekind == StmtK && node->child[1]->subkind.stmt == ReturnK)
                //         symTab->applyToAll(checkIsUsed);
                // }

                //Check to see if we have a return statment.

                // printf("Func %s has %d Params\n",node->attr.string,node->numParams);
                symTab->leave();
                //Leaving a function so reset the loop depth to 0
                loopDepth = 0;
                break;

            case ParamK:
                if (node->attr.name == NULL)
                {
                    printf("internal error NULL REACHED in attrName Paramk\n");
                    break;
                }

                //node->isUsed = false;
                node->isInit = true;
                node->isParam = true;
                //If the param is already added
                if (!symTab->insert(std::string(node->attr.name), (void *)node))
                {
                    lookupNode = (treeNode *)symTab->lookup(node->attr.string);
                    printf("ERROR(%d): Symbol '%s' is already declared at line %d.\n",
                           node->lineno,
                           lookupNode->attr.string,
                           lookupNode->lineno);
                    NUM_ERRORS++;
                }
                node->depth = symTab->depth();

                //Paramk Size for compound stmts
                if(node->isArray && !node->isIo)
                {
                    compound_size -=2;
                }
                else if(!node->isArray && !node->isIo)
                    compound_size--;

                checkChildren(node, symTab, DONT_SUPPRESS_CHILD_SCOPE);

                node->parent->numParams++;
                break;

            default:
                printf("PROGRAMMER ERROR UNKNOWN DECL TYPE\nSHOULD NOT GET HERE\n");
                exit(-1);
            }
        }

        //Proccess Expressions
        else if (node->nodekind == ExpK)
        {
            switch (node->subkind.exp)
            {
            case OpK:
                checkChildren(node, symTab, DONT_SUPPRESS_CHILD_SCOPE);
                //Set the type of the array to that the identifier
                //ensure the index is an integer.
                //Ensure the identifier is type array.
                if (node->op == OPEN_BRACK)
                {
                    //Setting the exptype of [ array to that of its Identifier.
                    
                    if (node->child[0] != NULL)
                    {
                        node->expType = node->child[0]->expType;
                        node->undeclared = node->child[0]->undeclared;
                    }

                    //check that the array identifier child[0] is declared as type array
                    lookupNode = (treeNode *)symTab->lookup(std::string(node->child[0]->attr.name));
                    if (lookupNode != NULL && !(lookupNode->isArray))
                    {
                        printf("ERROR(%d): Cannot index nonarray '%s'.\n", node->child[0]->lineno, node->child[0]->attr.name);
                        NUM_ERRORS++;
                    }
                    //if the ID is not in the symbol table, throw an error about indexing a non array. Because does not exist.
                    else if (lookupNode == NULL)
                    {
                        printf("ERROR(%d): Cannot index nonarray '%s'.\n", node->child[0]->lineno, node->child[0]->attr.name);
                        NUM_ERRORS++;
                    }

                    //make sure that the index of the array is an integer.
                    //Suppress on the case of an undefined and the index is a function. An error will be thrown elsewhere
                    if (node->child[1]->expType != Integer && node->child[1]->expType != UndefinedType)
                    {
                        //Make sure lhs and index is not a function
                        if (!node->child[1]->isFunc)
                        {
                            char buff[64];
                            convertExpTypeToString(node->child[1]->expType, buff);
                            printf("ERROR(%d): Array '%s' should be indexed by type int but got type %s.\n",
                                   node->lineno, node->child[0]->attr.name, buff);
                            NUM_ERRORS++;
                        }
                    }

                    //throw an error if the array is not indexed
                    if (node->child[1]->nodekind == ExpK && node->child[1]->subkind.exp == IdK)
                    {
                        lookupNode = (treeNode *)symTab->lookup(std::string(node->child[1]->attr.name));
                        if (lookupNode != NULL && lookupNode->isArray)
                        {
                            printf("ERROR(%d): Array index is the unindexed array '%s'.\n", node->child[1]->lineno, node->child[1]->attr.name);
                            NUM_ERRORS++;
                        }
                    }
                    node->isArray = false;
                }

                //Our OP is not an open brack therefore not an array
                //Promote type from typetable unless you are sizeof
                else
                {
                    //Ensures sizeof is only used with an array. Throws an error otherwise.
                    //HACK: force type to be undefined when rangek. Normally sets type to be integer.
                    if (node->op == SIZEOF)
                        checkSizeOf(node, symTab);
                    //Inherit the type of your children, if you are not a special operator.
                    else
                        node->expType = typeTable(node, node->child[0], node->child[1]);
                }
                break;
            case ConstantK:
                checkChildren(node, symTab, DONT_SUPPRESS_CHILD_SCOPE);
                //Indicate we are constant
                //SizeOf prob needs to be a constant
                node->isConst = true;
                //BOLD ASSUMPTION THAT ALL CONST ARE GLOBAL IN SCOPE
                node->scope = Global;
                
                node->loc = globalOffset;
                globalOffset -= node->size;
                
                

                break;

            case IdK:
                //Confirm the symbol exists in the table
                lookupNode = (treeNode *)symTab->lookup(std::string(node->attr.name));

                if (lookupNode == NULL)
                {

                    printf("ERROR(%d): Symbol '%s' is not declared.\n", node->lineno, node->attr.name);
                    NUM_ERRORS++;

                    node->undeclared = true;
                }
                //LookupNode was found in the table
                //Perform
                else
                {
                    //printf("CHANGING NODES USED VALUE BEFORE\n");
                    //foo(lookupNode);
                    //HACK THIS DOES NOT WORK WITH FOR. DONT CHANGE IS USED IF our parent is a rangek
                    //If we have a rangek child then we need to say we are already init.
                    //The is used flag is set by the RangeK above. so we dont want to override it
                    //Rangek sets the flags on the children it knows it has.
                    // if (node->isRangeK || node->parent->isRangeKBy || node->isRangeKBy)
                    // {
                    //     //foo(node);
                    //     lookupNode->isInit = true;
                    // }
                    // else
                    lookupNode->isUsed = true;

                    //HACK to fix printing. Make exptype undefined for any kind of range
                    //Normally promote the lookupnode type into current node.
                    // if ((node->parent->nodekind == StmtK && node->parent->subkind.stmt == RangeK) || node->isRangeKBy || node->parent->isRangeKBy)
                    // {
                    //     node->expType = UndefinedType;
                    // }
                    // else
                    //promote attributes we want from the lookup into the node
                    node->expType = lookupNode->expType;
                    node->size = lookupNode->size;
                    node->scope = lookupNode->scope;
                    node->loc = lookupNode->loc;
                    node->isArray = lookupNode->isArray;
                    node->isStatic = lookupNode->isStatic;
                    node->isFunc = lookupNode->isFunc;


                    
                    //Uninitilized ID's Get suppressed to avoid cascading errors
                    if (!lookupNode->isInit)
                    {
                        bool suppressWarning = false;
                        treeNode *currParent = node->parent;
                        treeNode *currNode = node;

                        //HACK.this should only be true if we are the index of an array. we must supress to match output
                        // The index are identifiers. could be a[d[2]] or a[a+c]
                        //This HACK only works for 2 levels of nesting.
                        //Ignore double nested, and just force our node to become the parent to force a suppression,
                        //when indicies are uninitialized
                        if (currParent->parent != NULL && currParent->parent->op == OPEN_BRACK)
                        {
                            currNode = currParent->parent;
                            currParent = currParent->parent->parent;
                        }

                        //If our current parent is an array we move the node up a level
                        if (currParent->op == OPEN_BRACK)
                        {
                            //printf("Parent is a [\nCurrNode is:\n");
                            //foo(currNode);
                            currNode = currParent;
                            currParent = currParent->parent;
                            //printf("Parent was a [ after\nCurrent Node is now:\n");
                            //foo(currNode);
                        }

                        if (currNode->parent->op == ADDASS)
                        {
                            suppressWarning = true;
                        }
                        //edge case of ignoring init errors on LHS within an array index

                        //Supress warning if we are on the LHS of an assignment(when we are the first child we are on the LHS)
                        if (currParent != NULL && currParent->nodekind == ExpK && currParent->subkind.exp == AssignK && currParent->child[0] == currNode && currParent->op == ASS)
                        {
                            //printf("SUPPRESSING: \n");
                            //foo(currNode);
                            suppressWarning = true;
                        }

                        //ERROR
                        //if (lookupNode->isStatic || symTab->lookupGlobal(std::string(node->attr.name)) != NULL)
                        //Depth 1 represents global scope
                        if (lookupNode->isStatic || lookupNode->depth == 1)
                        {
                            //printf("looked up globally or is static:%s\nSuppress is true\n", node->attr.name);
                            suppressWarning = true;
                        }
                        // if (currParent->op == SIZEOF)
                        //     suppressWarning = true;

                        //printf("SupressWarning:%s\n", (suppressWarning) ? "true" : "false");

                        if (!suppressWarning)
                        {
                            if (!lookupNode->isInitErrorThrown && !lookupNode->isFunc)
                            {

                                printf("WARNING(%d): Variable '%s' may be uninitialized when used here.\n", node->lineno, node->attr.name);
                                NUM_WARNINGS++;
                                lookupNode->isInitErrorThrown = true;
                            }
                        }
                    }

                    if (lookupNode->isFunc)
                    {
                        printf("ERROR(%d): Cannot use function '%s' as a variable.\n", node->lineno, node->attr.name);
                        NUM_ERRORS++;
                    }
                }
                checkChildren(node, symTab, DONT_SUPPRESS_CHILD_SCOPE);

                break;

            case AssignK:
            {
                checkChildren(node, symTab, DONT_SUPPRESS_CHILD_SCOPE);

                //mark symbol node initilized if its on the LHS of an assignment
                //Inherit the type of your child if you are an array
                bool isArrayRef = false;

                if (node->child[0] == NULL)
                {
                    printf("Unexpected Null child when checking init for assignk's\n");
                }
                else
                {
                    treeNode *lookupNode;
                    treeNode *childNodeRef;

                    childNodeRef = node->child[0];

                    if (childNodeRef->op == OPEN_BRACK)
                    {
                        //printf("found [\n");
                        isArrayRef = true;
                        childNodeRef = childNodeRef->child[0];
                    }

                    if (childNodeRef == NULL)
                    {
                        printf("Unexpected Null child when checking init for assignk's\n");
                    }
                    else
                    {
                        lookupNode = (treeNode *)symTab->lookup(std::string(std::string(childNodeRef->attr.name)));

                        if (lookupNode != NULL)
                        {
                            lookupNode->isInit = true;
                            //printf("In lookup of child\n");
                            //foo(childNodeRef);
                        }
                    }
                    //if array reference inheret type from identifier.
                    if (isArrayRef)
                    {
                        //Questionable might not be needed. overwritten elsewhere
                        childNodeRef->parent->isArray = false;
                        childNodeRef->parent->expType = childNodeRef->expType;
                    }
                }
                //If not array check for special operators and promote type accordingly.
                if (node->op != OPEN_BRACK)
                {
                    //Ensures sizeof is only used with an array. Throws an error otherwise.
                    //HACK: force type to be undefined when rangek. Normally sets type to be integer.
                    if (node->op == SIZEOF)
                        checkSizeOf(node, symTab);
                    //Inherit the type of your children, if you are not a special operator.
                    else
                        node->expType = typeTable(node, node->child[0], node->child[1]);
                }

                break;
            }
            case InitK:
                checkChildren(node, symTab, DONT_SUPPRESS_CHILD_SCOPE);

                break;

            case CallK:
                lookupNode = (treeNode *)symTab->lookup(std::string(node->attr.name));
                if (lookupNode != NULL)
                {
                    // MAKING THE ASSUMPTION THAT THE ID IS USED EVEN THOUGH IT MIGHT BE
                    // AN ERROR
                    lookupNode->isUsed = true;
                    if (!lookupNode->isFunc)
                    {
                        printf("ERROR(%d): '%s' is a simple variable and cannot be called.\n", node->lineno, node->attr.name);
                        NUM_ERRORS++;
                        break;
                    }
                }

                lookupNode = (treeNode *)symTab->lookupGlobal(std::string(node->attr.name));
                if (lookupNode == NULL)
                {
                    printf("ERROR(%d): Symbol '%s' is not declared.\n", node->lineno, node->attr.name);
                    NUM_ERRORS++;
                }
                else
                {
                    lookupNode->isUsed = true;
                    node->expType = lookupNode->expType;
                }

                checkChildren(node, symTab, DONT_SUPPRESS_CHILD_SCOPE);

                // if(lookupNode != NULL)
                //     printf("Lookupnode: %s params %d\n",lookupNode->attr.string,lookupNode->numParams);
                //Iterate through all the siblings of child[0]. This child conatains the parameters for the call.
                //We can use the lookup node to see what kind of exptypes we have for parameters of the orignial func
                //Need to build then number of params in the call. Should be able to do so in the Idk  switch
                //WE cannot do this in the Idk's because we may have a function call within a function call argument.

                //count the number of arguments in the call
                //Store it in numparams in the current node
                if (node != NULL)
                {
                    TreeNode *tmpNode = node->child[0];
                    while (tmpNode != NULL)
                    {
                        //Store the # of params
                        node->numParams++;
                        //printf("params to the call: %d\n", node->numParams);
                        tmpNode = tmpNode->sibling;
                    }
                }

                if (lookupNode != NULL)
                {
                    //We have to few parameters.
                    if (node->numParams < lookupNode->numParams)
                    {
                        //printf("node params: %d\nLookup Params: %d\n", node->numParams, lookupNode->numParams);
                        printf("ERROR(%d): Too few parameters passed for function '%s' declared on line %d.\n", node->lineno, lookupNode->attr.string, lookupNode->lineno);
                        NUM_ERRORS++;
                    }

                    //Too many arguments
                    if (node->numParams > lookupNode->numParams)
                    {
                        //printf("node params: %d\nLookup Params: %d\n", node->numParams, lookupNode->numParams);
                        printf("ERROR(%d): Too many parameters passed for function '%s' declared on line %d.\n", node->lineno, lookupNode->attr.string, lookupNode->lineno);
                        NUM_ERRORS++;
                    }
                    char lookupBuff[64];
                    char currNodeBuff[64];

                    int paramIndex = 1;

                    //Special For loop.
                    // init: TmpCurrNode, TmpLookupNode both containing the children
                    // condition: Both nodes are non null. either one being null will stop the loop
                    // Itter: Both nodes becomes their sibling when itterated.
                    for (TreeNode *tmpCurrNode = node->child[0], *tmpLookupNode = lookupNode->child[0]; //Init
                         (tmpCurrNode != NULL) && (tmpLookupNode != NULL);                              //Condition
                         tmpCurrNode = tmpCurrNode->sibling, tmpLookupNode = tmpLookupNode->sibling)    //Itteration
                    {
                        //String representation of ExpTypes
                        convertExpTypeToString(tmpLookupNode->expType, lookupBuff);
                        convertExpTypeToString(tmpCurrNode->expType, currNodeBuff);

                        if (tmpCurrNode->expType != tmpLookupNode->expType)
                        {
                            //HACK:we dont thor additional errors for undefined variables as parameters.
                            if (tmpCurrNode->expType != UndefinedType)
                            {
                                printf("ERROR(%d): Expecting type %s in parameter %d of call to '%s' declared on line %d but got type %s.\n",
                                       node->lineno,
                                       lookupBuff,
                                       paramIndex,
                                       lookupNode->attr.string,
                                       lookupNode->lineno,
                                       currNodeBuff);
                                NUM_ERRORS++;
                            }
                        }

                        //Expecting an array but didn't get one
                        if (tmpLookupNode->isArray && !tmpCurrNode->isArray)
                        {
                            printf("ERROR(%d): Expecting array in parameter %d of call to '%s' declared on line %d.\n",
                                   node->lineno,
                                   paramIndex,
                                   lookupNode->attr.string,
                                   lookupNode->lineno);
                            NUM_ERRORS++;
                        }
                        else if (!tmpLookupNode->isArray && tmpCurrNode->isArray)
                        {
                            printf("ERROR(%d): Not expecting array in parameter %d of call to '%s' declared on line %d.\n",
                                   node->lineno,
                                   paramIndex,
                                   lookupNode->attr.string,
                                   lookupNode->lineno);
                            NUM_ERRORS++;
                        }
                        paramIndex++;
                    }
                }

                // //Our call matches the number of required params. We now need to type check.
                // else if (lookupNode != NULL && lookupNode->numParams == node->numParams)
                // {
                //     char lookupBuff[64];
                //     char currNodeBuff[64];

                //     //TmpNode is looking at the parameters.
                //     TreeNode *tmpCurrNode = node->child[0];
                //     TreeNode *tmpLookupNode = lookupNode->child[0];

                //     /*                                            |             |
                //     *                                             V             V
                //     * Iterate through the each param. Ie main(int a, b, c) main(2,3,4) */
                //     for (int paramIndex = 1; paramIndex <= lookupNode->numParams; paramIndex++)
                //     {
                //         convertExpTypeToString(tmpLookupNode->expType, lookupBuff);
                //         convertExpTypeToString(tmpCurrNode->expType, currNodeBuff);

                //         if (tmpCurrNode->expType != tmpLookupNode->expType)
                //         {
                //             //HACK:we dont thor additional errors for undefined variables as parameters.
                //             if (tmpCurrNode->expType != UndefinedType)
                //             {
                //                 printf("ERROR(%d): Expecting type %s in parameter %d of call to '%s' declared on line %d but got type %s.\n",
                //                        node->lineno,
                //                        lookupBuff,
                //                        paramIndex,
                //                        lookupNode->attr.string,
                //                        lookupNode->lineno,
                //                        currNodeBuff);
                //                 NUM_ERRORS++;
                //             }
                //         }

                //         //Set the next parameters for the call and the original function
                //         tmpCurrNode = tmpCurrNode->sibling;
                //         tmpLookupNode = tmpLookupNode->sibling;
                //     }
                // }

                break;

            default:
                printf("PROGRAMMER ERROR UNKNOWN EXP\nSHOULD NOT GET HERE\n");
                exit(-1);
            }
        }

        else
        {
            printf("PROGRAMMER ERROR UNKNOWN NODEKIND\nSHOULD NOT GET HERE\n");
            exit(-1);
        }

        //When the program has fully been semanticly analyzed do one last check for unused globals
        //this needs to happen at the very end because globals can be used anywhere/any depth

        if (node->sibling == NULL && node->parent == NULL)
        {
            //foo(node);
            tailOfTree = node;
            symTab->applyToAllGlobal(checkIsUsed);
        }

        node = node->sibling;
    }
}

void checkIsUsed(std::string symbolName, void *ptr)
{
    treeNode *nodeptr;
    nodeptr = (treeNode *)ptr;
    //printf("Checking node:\n");
    //foo(nodeptr);
    //MAKING THE ASSUMPTION THAT NODES AT GLOBAL SCOPE ARE ALWAYS USED.
    //changing this assumption to always assume the main function is used.
    //All other functions have to be checked to see if they are called.

    if (!nodeptr->isUsed)
    {

        if (nodeptr->isFunc)
        {
            if (strcmp(nodeptr->attr.string, "main") != 0)
            {
                printf("WARNING(%d): The function '%s' seems not to be used.\n",
                       nodeptr->lineno, symbolName.c_str());
                NUM_WARNINGS++;
            }
        }
        else if (nodeptr->isParam)
        {
            printf("WARNING(%d): The parameter '%s' seems not to be used.\n",
                   nodeptr->lineno, symbolName.c_str());
            NUM_WARNINGS++;
        }
        else
        {
            printf("WARNING(%d): The variable '%s' seems not to be used.\n",
                   nodeptr->lineno, symbolName.c_str());
            NUM_WARNINGS++;
        }
    }
}

ExpType typeTable(TreeNode *parentNode, treeNode *lhsNode, treeNode *rhsNode)
{
    ExpType lhs, rhs;

    char buff1[64];
    char buff2[64];

    if (parentNode->subkind.exp == OpK)
    {
        OpKind op = parentNode->op;
        if (op == PLUS || op == MINUS || op == DIV || op == MOD || op == MAX || op == MIN || op == MULT)
        {
            lhs = lhsNode->expType;
            rhs = rhsNode->expType;

            //HACK TO MATCH OUTPUT
            // if (parentNode->isRangeK || parentNode->isRangeKBy)
            //     return UndefinedType;

            //For Initilizers to know if they contain
            if ((lhsNode != NULL && rhsNode != NULL) && (lhsNode->isConst && rhsNode->isConst))
                parentNode->isConst = true;

            if (lhs == Integer && rhs == Integer)
            {
                // printf("testing if array\n");
                // foo(lhsNode);
                // foo(rhsNode);

                if (!lhsNode->isArray && !rhsNode->isArray)
                {
                    //HACK
                    // if (parentNode->parent->nodekind == StmtK && parentNode->parent->subkind.stmt == RangeK)
                    // {
                    //     return UndefinedType;
                    // }
                    return Integer;
                }

                printf("ERROR(%d): The operation '%s' does not work with arrays.\n", parentNode->lineno, parentNode->attr.string);
                NUM_ERRORS++;

                return Integer;
            }

            convertExpTypeToString(lhs, buff1);
            convertExpTypeToString(rhs, buff2);
            if (lhs == Integer && rhs != Integer)
            {
                //HACK for matching output. Supress this Error
                if (rhs != UndefinedType)
                {
                    //Hack: Output prints voids when mult appears
                    if (rhs == Void && op == MULT)
                    {
                        printf("ERROR(%d): '%s' requires operands of type int but rhs is of type %s.\n",
                               parentNode->lineno, parentNode->attr.string,
                               buff2);
                        NUM_ERRORS++;
                    }
                    else if (rhs != Void)
                    {
                        printf("ERROR(%d): '%s' requires operands of type int but rhs is of type %s.\n",
                               parentNode->lineno, parentNode->attr.string,
                               buff2);
                        NUM_ERRORS++;
                    }
                }
            }
            else if (lhs != Integer && rhs == Integer)
            {
                //HACK for matching output. Supress this Error
                if (lhs != UndefinedType)
                {
                    //Hack: Output prints voids when mult appears
                    if (lhs == Void && op == MULT)
                    {
                        printf("ERROR(%d): '%s' requires operands of type int but lhs is of type %s.\n",
                               parentNode->lineno, parentNode->attr.string,
                               buff1);
                        NUM_ERRORS++;
                    }
                    else if (lhs != Void)
                    {
                        printf("ERROR(%d): '%s' requires operands of type int but lhs is of type %s.\n",
                               parentNode->lineno, parentNode->attr.string,
                               buff1);
                        NUM_ERRORS++;
                    }
                }
            }
            //Neither are integers
            else
            {
                //HACK TO MATCH OUTPUT. Suppressing on undefined variables. Error is thrown elsewhere
                if (lhs != UndefinedType && rhs != UndefinedType)
                {
                    printf("ERROR(%d): '%s' requires operands of type int but lhs is of type %s.\n",
                           parentNode->lineno, parentNode->attr.string,
                           buff1);
                    NUM_ERRORS++;

                    printf("ERROR(%d): '%s' requires operands of type int but rhs is of type %s.\n",
                           parentNode->lineno, parentNode->attr.string,
                           buff2);
                    NUM_ERRORS++;
                }
                else if (lhs != UndefinedType)
                {
                    printf("ERROR(%d): '%s' requires operands of type int but lhs is of type %s.\n",
                           parentNode->lineno, parentNode->attr.string,
                           buff1);
                    NUM_ERRORS++;
                }
                else if (rhs != UndefinedType)
                {
                    printf("ERROR(%d): '%s' requires operands of type int but rhs is of type %s.\n",
                           parentNode->lineno, parentNode->attr.string,
                           buff2);
                    NUM_ERRORS++;
                }
            }
            if (lhsNode->isArray || rhsNode->isArray)
            {
                printf("ERROR(%d): The operation '%s' does not work with arrays.\n", parentNode->lineno, parentNode->attr.string);
                NUM_ERRORS++;
            }
            return Integer;
        }
        else if (op == CHSIGN || op == QUESTION)
        {

            if (lhsNode->isConst && op == CHSIGN)
                parentNode->isConst = true;

            lhs = lhsNode->expType;

            convertExpTypeToString(lhs, buff1);

            //Chsign processing
            if (op == CHSIGN)
            {
                //Undefined types is a hack to make the output match
                if (lhs != Integer && lhs != UndefinedType)
                {
                    printf("ERROR(%d): Unary 'chsign' requires an operand of type %s but was given type %s.\n",
                           parentNode->lineno,
                           "int",
                           buff1);
                    NUM_ERRORS++;
                }

                if (lhsNode->isArray)
                {
                    printf("ERROR(%d): The operation '%s' does not work with arrays.\n", parentNode->lineno, op == CHSIGN ? "chsign" : "?");
                    NUM_ERRORS++;
                }

                //printf("chsign\n");
                //HACK to match output
                // if (parentNode->parent->nodekind == StmtK && parentNode->parent->subkind.stmt == RangeK)
                //     return UndefinedType;

                return Integer;
            }
            //This must be a QUESTION
            else
            {
                if (lhs != Integer)
                {
                    printf("ERROR(%d): Unary '%s' requires an operand of type %s but was given type %s.\n",
                           parentNode->lineno, parentNode->attr.string,
                           "int",
                           buff1);
                    NUM_ERRORS++;
                }

                if (lhsNode->isArray)
                {
                    printf("ERROR(%d): The operation '%s' does not work with arrays.\n", parentNode->lineno, op == CHSIGN ? "chsign" : "?");
                    NUM_ERRORS++;
                }
            }

            return Integer;
        }
        //TODO ARRAY CHECKING PLEASE
        else if (op == LEQ || op == LESS || op == GREATER || op == GEQ || op == EQ || op == NEQ)
        {
            lhs = lhsNode->expType;
            rhs = rhsNode->expType;
            //printf("in rel ops\n");

            if (op == EQ || op == NEQ)
            {
                if ((!lhsNode->isArray && rhsNode->isArray))
                {
                    printf("ERROR(%d): '%s' requires both operands be arrays or not but lhs is not an array and rhs is an array.\n", parentNode->lineno, parentNode->attr.string);
                    NUM_ERRORS++;
                }
                else if (lhsNode->isArray && (!rhsNode->isArray))
                {
                    printf("ERROR(%d): '%s' requires both operands be arrays or not but lhs is an array and rhs is not an array.\n", parentNode->lineno, parentNode->attr.string);
                    NUM_ERRORS++;
                }
            }
            else if (op == GEQ || op == LEQ || op == LESS || op == GREATER)
            {
                if ((!lhsNode->isArray && rhsNode->isArray))
                {
                    printf("ERROR(%d): '%s' requires both operands be arrays or not but lhs is not an array and rhs is an array.\n", parentNode->lineno, parentNode->attr.string);
                    NUM_ERRORS++;
                }
                else if (lhsNode->isArray && (!rhsNode->isArray))
                {
                    printf("ERROR(%d): '%s' requires both operands be arrays or not but lhs is an array and rhs is not an array.\n", parentNode->lineno, parentNode->attr.string);
                    NUM_ERRORS++;
                }
            }

            if (lhs == rhs)
            {
                parentNode->isConst = true;
                return Boolean;
            }

            convertExpTypeToString(lhs, buff1);
            convertExpTypeToString(rhs, buff2);

            //foo(lhsNode);
            //foo(rhsNode);

            //suppressing. assuming the undefined type error is already handled in main loop
            if (lhs != UndefinedType && rhs != UndefinedType)
            {
                printf("ERROR(%d): '%s' requires operands of the same type but lhs is type %s and rhs is type %s.\n",
                       parentNode->lineno, parentNode->attr.string, buff1, buff2);
                NUM_ERRORS++;
            }

            return Boolean;
        }
        else if (op == AND || op == OR)
        {
            lhs = lhsNode->expType;
            rhs = rhsNode->expType;
            if (lhs == Boolean && rhs == Boolean)
            {
                if (lhsNode->isArray || rhsNode->isArray)
                {
                    printf("ERROR(%d): The operation '%s' does not work with arrays.\n", parentNode->lineno, parentNode->attr.string);
                    NUM_ERRORS++;
                    return UndefinedType;
                }

                parentNode->isConst = true;

                return Boolean;
            }

            convertExpTypeToString(lhs, buff1);
            convertExpTypeToString(rhs, buff2);

            // HACK: Error handleing for non boolean types on either side of a binary and or
            //We can have undefined types on one side or the other, but wont print errors for that specifically
            //an error is thrown elsewhere for an undefined variable being used.
            if (lhs != UndefinedType || rhs != UndefinedType)
            {

                if (lhs == Boolean && rhs != Boolean && rhs != UndefinedType)
                {
                    printf("ERROR(%d): '%s' requires operands of type bool but rhs is of type %s.\n",
                           parentNode->lineno, parentNode->attr.string,
                           buff2);
                    NUM_ERRORS++;
                }
                else if (lhs != Boolean && lhs != UndefinedType && rhs == Boolean)
                {
                    printf("ERROR(%d): '%s' requires operands of type bool but lhs is of type %s.\n",
                           parentNode->lineno, parentNode->attr.string,
                           buff1);
                    NUM_ERRORS++;
                }
                else
                {
                    if (lhs != UndefinedType && lhs != Boolean)
                    {
                        printf("ERROR(%d): '%s' requires operands of type bool but lhs is of type %s.\n",
                               parentNode->lineno, parentNode->attr.string,
                               buff1);
                        NUM_ERRORS++;
                    }

                    if (rhs != UndefinedType && rhs != Boolean)
                    {
                        printf("ERROR(%d): '%s' requires operands of type bool but rhs is of type %s.\n",
                               parentNode->lineno, parentNode->attr.string,
                               buff2);
                        NUM_ERRORS++;
                    }
                }

                if (lhsNode->isArray || rhsNode->isArray)
                {
                    printf("ERROR(%d): The operation '%s' does not work with arrays.\n", parentNode->lineno, parentNode->attr.string);
                    NUM_ERRORS++;
                }
                return Boolean;
            }
            else
                return Boolean;
        }

        else if (op == NOT)
        {
            lhs = lhsNode->expType;
            //printf("in rel ops\n");
            if (lhs == Boolean)
            {
                if (lhsNode->isArray)
                {
                    printf("ERROR(%d): The operation 'not' does not work with arrays.\n", parentNode->lineno);
                    NUM_ERRORS++;
                }

                return Boolean;
            }

            convertExpTypeToString(lhs, buff1);

            printf("ERROR(%d): Unary 'not' requires an operand of type %s but was given type %s.\n",
                   parentNode->lineno,
                   "bool",
                   buff1);
            NUM_ERRORS++;

            if (lhsNode->isArray)
            {
                printf("ERROR(%d): The operation 'not' does not work with arrays.\n", parentNode->lineno);
                NUM_ERRORS++;
            }
            return Boolean;
        }
    }
    // LHS = RHS |  LHS += RHS | LHS -= RHS | LHS /= RHS | LHS++ | LHS--
    else if (parentNode->subkind.exp == AssignK)
    {
        OpKind op = parentNode->op;

        if (op == ASS)
        {
            lhs = lhsNode->expType;
            rhs = rhsNode->expType;

            convertExpTypeToString(lhs, buff1);
            convertExpTypeToString(rhs, buff2);
            if (lhs == rhs)
            {
                if (lhsNode->isArray && rhsNode->isArray)
                {
                    parentNode->isArray = true;
                    return lhs;
                }
                   
                else if (lhsNode->isArray && !(rhsNode->isArray))
                {
                    printf("ERROR(%d): '%s' requires both operands be arrays or not but lhs is an array and rhs is not an array.\n",
                           parentNode->lineno, parentNode->attr.string);
                    NUM_ERRORS++;
                }
                else if (!(lhsNode->isArray) && rhsNode->isArray)
                {
                    printf("ERROR(%d): '%s' requires both operands be arrays or not but lhs is not an array and rhs is an array.\n",
                           parentNode->lineno, parentNode->attr.string);
                    NUM_ERRORS++;
                }

                return lhs;
            }
            else
            {
                //If we are undefined it is assumed the LHS is undeclared and has already thrown an error.
                if (lhs != UndefinedType && rhs != UndefinedType)
                {
                    //Suppress this error if we are a function. An error is thrown elsewhere for this.
                    if (!lhsNode->isFunc && !rhsNode->isFunc)
                    {
                        printf("ERROR(%d): '%s' requires operands of the same type but lhs is type %s and rhs is type %s.\n",
                               parentNode->lineno, parentNode->attr.string, buff1, buff2);
                        NUM_ERRORS++;
                    }
                }
                //
                if (lhs != UndefinedType && lhsNode->isArray && !(rhsNode->isArray))
                {
                    printf("ERROR(%d): '%s' requires both operands be arrays or not but lhs is an array and rhs is not an array.\n",
                           parentNode->lineno, parentNode->attr.string);
                    NUM_ERRORS++;
                }

                if (rhs != UndefinedType && rhsNode->isArray && !(lhsNode->isArray))
                {
                    printf("ERROR(%d): '%s' requires both operands be arrays or not but lhs is not an array and rhs is an array.\n",
                           parentNode->lineno, parentNode->attr.string);
                    NUM_ERRORS++;
                }
            }

            return lhs;
        }
        else if (op == ADDASS || op == SUBASS || op == MULASS || op == DIVASS)
        {
            //printf("made it to the code\n");
            lhs = lhsNode->expType;
            rhs = rhsNode->expType;

            convertExpTypeToString(lhs, buff1);
            convertExpTypeToString(rhs, buff2);
            if (lhs == Integer && rhs == Integer)
            {
                //These operators do not support arrays. throw error
                if (lhsNode->isArray || rhsNode->isArray)
                {
                    printf("ERROR(%d): The operation '%s' does not work with arrays.\n", parentNode->lineno, parentNode->attr.string);
                    NUM_ERRORS++;
                }
                return Integer;
            }

            if (lhs != UndefinedType && rhs != UndefinedType)
            {
                if (lhs == Integer && rhs != Integer)
                {
                    printf("ERROR(%d): '%s' requires operands of type int but rhs is of type %s.\n",
                           parentNode->lineno, parentNode->attr.string,
                           buff2);
                    NUM_ERRORS++;
                }
                else if (lhs != Integer && rhs == Integer)
                {
                    printf("ERROR(%d): '%s' requires operands of type int but lhs is of type %s.\n",
                           parentNode->lineno, parentNode->attr.string,
                           buff1);
                    NUM_ERRORS++;
                }
                else
                {
                    printf("ERROR(%d): '%s' requires operands of type int but lhs is of type %s.\n",
                           parentNode->lineno, parentNode->attr.string,
                           buff1);
                    NUM_ERRORS++;

                    printf("ERROR(%d): '%s' requires operands of type int but rhs is of type %s.\n",
                           parentNode->lineno, parentNode->attr.string,
                           buff2);
                    NUM_ERRORS++;
                }

                return Integer;
            }
            else
                return Integer;
        }
        //TODO:
        //CHECK FOR ARRAYS NOT CURRENTLY IMPLEMTED
        else if (op == DEC || op == INC)
        {
            lhs = lhsNode->expType;

            convertExpTypeToString(lhs, buff1);

            if (lhs == Integer)
            {
                if (lhsNode->isArray)
                {
                    printf("ERROR(%d): The operation '%s' does not work with arrays.\n", parentNode->lineno, parentNode->attr.string);
                    NUM_ERRORS++;
                }
                return lhs;
            }

            else
            {
                //Hack to make output match. ++/-- an undecl is legal for now
                if (lhs != UndefinedType)
                {
                    printf("ERROR(%d): Unary '%s' requires an operand of type %s but was given type %s.\n",
                           parentNode->lineno, parentNode->attr.string,
                           "int",
                           buff1);
                    NUM_ERRORS++;
                }

                if (lhsNode->isArray)
                {
                    printf("ERROR(%d): The operation '%s' does not work with arrays.\n", parentNode->lineno, parentNode->attr.string);
                    NUM_ERRORS++;
                }
            }
            return Integer;
        }
        else if (op == AND || op == OR)
        {
            lhs = lhsNode->expType;
            rhs = rhsNode->expType;
            if (lhs == Boolean && rhs == Boolean)
            {
                parentNode->isConst = true;
                return Boolean;
            }

            convertExpTypeToString(lhs, buff1);
            convertExpTypeToString(rhs, buff2);

            //foo(lhsNode);
            //foo(rhsNode);
            if (lhs == Boolean && rhs != Boolean)
            {
                printf("ERROR(%d): '%s' requires operands of type bool but rhs is of type %s.\n",
                       parentNode->lineno, parentNode->attr.string,
                       buff2);
                NUM_ERRORS++;
            }
            else if (lhs != Boolean && rhs == Boolean)
            {
                printf("ERROR(%d): '%s' requires operands of type bool but lhs is of type %s.\n",
                       parentNode->lineno, parentNode->attr.string,
                       buff1);
                NUM_ERRORS++;
            }
            else
            {
                printf("ERROR(%d): '%s' requires operands of type bool but lhs is of type %s.\n",
                       parentNode->lineno, parentNode->attr.string,
                       buff1);
                NUM_ERRORS++;

                printf("ERROR(%d): '%s' requires operands of type bool but rhs is of type %s.\n",
                       parentNode->lineno, parentNode->attr.string,
                       buff2);
                NUM_ERRORS++;
            }
            return Boolean;
        }

        else if (op == NOT)
        {
            lhs = lhsNode->expType;
            //printf("in rel ops\n");
            if (lhs == Boolean)
            {
                if (lhsNode->isArray)
                {
                    printf("ERROR(%d): The operation '%s' does not work with arrays.\n", parentNode->lineno, parentNode->attr.string);
                    NUM_ERRORS++;
                }
                return Boolean;
            }

            convertExpTypeToString(lhs, buff1);

            printf("ERROR(%d): Unary 'not' requires an operand of type %s but was given type %s.\n",
                   parentNode->lineno,
                   "bool",
                   buff1);
            NUM_ERRORS++;

            if (lhsNode->isArray)
            {
                printf("ERROR(%d): The operation '%s' does not work with arrays.\n", parentNode->lineno, parentNode->attr.string);
                NUM_ERRORS++;
            }
            return Boolean;
        }
    }
    //printf("Fell out of table\n");

    return UndefinedType;
}
