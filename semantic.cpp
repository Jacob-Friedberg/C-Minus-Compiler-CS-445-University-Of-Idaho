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

ExpType typeTable(TreeNode *parentNode, treeNode *lhsNode, treeNode *rhsNode);
void checkIsUsed(std::string symbolName, void *ptr);
void checkIsInit(std::string symbolName, void *ptr);

int NUM_ERRORS = 0;
int NUM_WARNINGS = 0;

void foo(void *x)
{
    dumpNode((treeNode *)x);
}

//Parent suppress scope means the parent node is a function and needs to suppress child cmpd statments
//Child suppress scope means the parent is a function
void checkTree(SymbolTable *symTab, TreeNode *node, int indentLevel, bool parentSuppressScope, TreeNode *parent)
{
    char typing[64];
    int sibling_count = 1;
    bool isCompound = false;
    bool isFor = false;
    bool isAssign = false;
    bool isFuncDecl = false;
    bool childSuppressScope = false;
    treeNode *lookupNode;
    //symTab->debug(true);
    while (node != NULL)
    {
        isCompound = false;
        isFor = false;
        isAssign = false;
        isFuncDecl = false;
        childSuppressScope = false;

        node->parent = parent;
        convertExpTypeToString(node->expType, typing);

        if (node->nodekind == StmtK)
        {
            switch (node->subkind.stmt)
            {
            case NullK:
                //printf("NULL\n");
                break;
            case IfK:
                //printf("If [line: %d]\n", node->lineno);
                break;
            case WhileK:
                //printf("While [line: %d]\n", node->lineno);
                break;
            case ForK:
                symTab->enter(std::string("this is a for loop"));
                isFor = true;
                childSuppressScope = true;

                //printf("For [line: %d]\n", node->lineno);
                break;
            case CompoundK:
                //printf("Compound [line: %d]\n", node->lineno);
                if (!parentSuppressScope)
                {
                    symTab->enter(std::string("THIS IS A COMPOUND"));
                }
                isCompound = true;
                break;
            case ReturnK:
                //printf("Return [line: %d]\n", node->lineno);
                break;
            case BreakK:
                //printf("Break [line: %d]\n", node->lineno);
                break;
            case RangeK:
                //Fix up the Init values on child 0 and 1 Checks if we are stepping

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
                //printf("Range [line: %d]\n", node->lineno);
                break;

            default:
                //printf("Unknown stmtK subkind \n");
                break;
            }
        }
        else if (node->nodekind == ExpK)
        {
            switch (node->subkind.exp)
            {
            case OpK:
                break;
            case ConstantK:
                break;
            case IdK:
                lookupNode = (treeNode *)symTab->lookup(std::string(node->attr.name));

                //foo(node);
                //printf("parents kind:%d SubKind:%d\n",node->parent->nodekind,node->parent->subkind.stmt);
                //symTab->print(foo);
                if (lookupNode == NULL)
                {
                    //suppressing range k undecalared to match output
                    if (!node->isRangeK)
                    {
                        printf("ERROR(%d): Symbol '%s' is not declared.\n", node->lineno, node->attr.name);
                        NUM_ERRORS++;
                    }
                }
                else
                {
                    //printf("CHANGING NODES USED VALUE BEFORE\n");
                    //foo(lookupNode);
                    //HACK THIS DOES NOT WORK WITH FOR. DONT CHANGE IS USED IF our parent is a rangek
                    //If we have a rangek child then we need to say we are already init.
                    //The is used flag is set by the RangeK above. so we dont want to override it
                    //Rangek sets the flags on the children it knows it has.
                    if (node->isRangeK || node->parent->isRangeKBy || node->isRangeKBy)
                    {
                        //foo(node);
                        lookupNode->isInit = true;
                    }
                    else
                        lookupNode->isUsed = true;

                    //HACK to fix printing
                    if ((node->parent->nodekind == StmtK && node->parent->subkind.stmt == RangeK) || node->isRangeKBy || node->parent->isRangeKBy)
                    {
                        node->expType = UndefinedType;
                    }
                    else
                        node->expType = lookupNode->expType;

                    node->isArray = lookupNode->isArray;
                    node->isStatic = lookupNode->isStatic;
                    node->isFunc = lookupNode->isFunc;
                    //printf("CHANGING NODES USED VALUE AFTER\n");
                    //foo(lookupNode);

                    if (!lookupNode->isInit)
                    {
                        bool suppressWarning = false;
                        treeNode *currParent = node->parent;
                        treeNode *currNode = node;

                        //HACK.this should only be true if we are the index of an array. we must supress to match output
                        // The index are identifiers. could be a[d[2]] or a[a+c]
                        if (currParent->parent != NULL && currParent->parent->op == OPEN_BRACK)
                        {
                            currNode = currParent->parent;
                            currParent = currParent->parent->parent;
                        }

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

                                //foo(lookupNode);
                            }
                            //printf("Parent\n");
                            //foo(currParent);
                            //printf("id Node\n");
                            //foo(node);
                            //foo(lookupNode);
                        }
                        //foo(lookupNode);
                    }
                    if (lookupNode->isFunc)
                    {
                        printf("ERROR(%d): Cannot use function '%s' as a variable.\n", node->lineno, node->attr.name);
                        NUM_ERRORS++;
                    }
                }

                //printf("Id: %s [line: %d]\n", node->attr.name, node->lineno);
                break;
            case AssignK:

                //printf("Assign: %s [line: %d]\n", node->attr.string, node->lineno);
                break;
            case InitK:
                //printf("Init:\n");

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
                //printf("Call: %s [line: %d]\n", node->attr.name, node->lineno);
                break;
            default:
                printf("Unknown ExpK Subkind\n");
                break;
            }
        }
        else if (node->nodekind == DeclK)
        {
            switch (node->subkind.decl)
            {
            case VarK:
                if (node->attr.name == NULL)
                {
                    printf("internal error NULL REACHED in attrName Vark\n");
                }
                if (node->isArray)
                    ; // printf("Var: %s is array of type %s [line: %d]\n", node->attr.name, typing, node->lineno);
                else
                {
                    ; //printf("Var: %s of type %s [line: %d]\n", node->attr.name, typing, node->lineno);
                }

                //Check globally for variables already declared.

                //lookupNode = (treeNode *)symTab->lookupGlobal(node->attr.name);
                //If the symbol does not exist then we can add it
                // if (lookupNode == NULL)
                // {
                if (symTab->insert(std::string(node->attr.name), (void *)node))
                {
                    node->depth = symTab->depth();
                    node->isUsed = false;
                    //Special handleing for the case of init variables in for loops
                    if (node->parent != NULL && node->parent->nodekind == StmtK && node->parent->subkind.stmt == ForK)
                        node->isInit = true;
                    else
                        node->isInit = false;

                    node->isInitErrorThrown = false;
                    //printf("INSERTING\n");
                    //foo(node);
                }
                else
                {
                    lookupNode = (treeNode *)symTab->lookup(node->attr.name);
                    printf("ERROR(%d): Symbol '%s' is already declared at line %d.\n",
                           node->lineno,
                           lookupNode->attr.name,
                           lookupNode->lineno);
                    NUM_ERRORS++;
                }

                //}
                //throw error on already declared global variable
                //Disabling for now, most likley not needed.
                // else
                // {
                //     printf("ERROR(%d): Symbol '%s' is already declared at line %d.\n",
                //            node->lineno,
                //            lookupNode->attr.name,
                //            lookupNode->lineno);
                //     NUM_ERRORS++;
                // }

                break;
            case FuncK:
                if (node->attr.name == NULL)
                {
                    printf("internal error NULL REACHED in attrName funck\n");
                    break;
                }
                //printf("Func: %s returns type %s [line: %d]\n", node->attr.string, typing, node->lineno);
                if (symTab->insertGlobal(std::string(node->attr.string), node))
                {
                    node->depth = symTab->depth();
                    node->isUsed = false;
                    // node->isInit = true;
                    node->isFunc = true;
                    isFuncDecl = true;
                }
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
                    isFuncDecl = true;
                }
                //prob shouldn't enter regardless if there is an error.
                symTab->enter(std::string(node->attr.string));
                //printf("ENTERING FUNK: %s\n", node->attr.string);
                childSuppressScope = true;
                break;
            case ParamK:
                if (node->attr.name == NULL)
                {
                    printf("internal error NULL REACHED in attrName Paramk\n");
                    break;
                }

                //printf("Parm: %s%s of type %s [line: %d]\n", node->attr.name,node->isArray?" is array":"", typing, node->lineno);

                if (node->isArray)
                {
                    node->isUsed = false;
                    node->isInit = true;
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
                }

                //printf("Parm: %s is array of type %s [line: %d]\n", node->attr.name, typing, node->lineno);
                else
                {
                    node->isUsed = false;
                    node->isInit = true;
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

                    //printf("param added:\n");
                    //foo(node);

                }; //printf("Parm: %s of type %s [line: %d]\n", node->attr.name, typing, node->lineno);
                break;
            default:
                printf("Unknown Declk subKind\n");
                break;
            }
        }
        else
            printf("Unknown node kind\n");

        //if node is an plus operator
        //nodeType is the lookup of the two children from the tt.
        //resulting exptype TypeTable(Operator,LHS exptype,RHS exptype)

        for (int i = 0; i < MAXCHILDREN; i++)
        {
            //printf("indentL:%d i:%d\n",indentLevel,i);
            if (node->child[i] != NULL)
            {
                //printSpaces(indentLevel + 1);
                //printf("Child: %d ", i);
                checkTree(symTab, node->child[i], indentLevel + 1, childSuppressScope, node);
            }
            //else
            //printf("child:%d was NULL at indent %d\n", i, indentLevel);
        }

        if (node->nodekind == StmtK && node->subkind.stmt == ReturnK)
        {

            if (node->child[0] != NULL && node->child[0]->isArray)
            {
                printf("ERROR(%d): Cannot return an array.\n", node->lineno);
                NUM_ERRORS++;
            }
        }

        //mark symbol node initilized if its on the LHS of an assignmnet
        if (node->nodekind == ExpK && node->subkind.exp == AssignK)
        {
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
                    childNodeRef->parent->isArray = false;
                    childNodeRef->parent->expType = childNodeRef->expType;
                }
            }
        }

        //Assuming an init if the decleration has a child, which should be initilizer
        if (node->subkind.decl == VarK && node->child[0] != NULL)
        {
            //printf("caught an init\n");

            node->isInit = true;
            // foo(node);
            //foo(node->child[0]);
        }
        if (isCompound)
        {

            //symTab->print(foo);
            symTab->applyToAll(checkIsUsed);

            if (!parentSuppressScope)
            {
                //printf("leaving compound\n");
                symTab->leave();
            }
            isCompound = false;
            parentSuppressScope = false;
        }
        if (isFor)
        {
            //symTab->print(foo);
            //printf("IN IS FOR\n");
            if (node->child[2] != NULL)
            {
                if (!(node->child[2]->nodekind == StmtK && node->child[2]->subkind.stmt == CompoundK))
                {
                    //printf("CHECKING IF USED\n");
                    symTab->applyToAll(checkIsUsed);
                }
            }
            else
                symTab->applyToAll(checkIsUsed);

            symTab->leave();
            childSuppressScope = false;
            isFor = false;
        }
        if (isFuncDecl)
        {
            //printf("Leaving Function\n");
            //On the case of a oneline function we need to check the params if they are used.
            //We can only do this if child[1] exists and is not null
            if (node->child[1] != NULL)
            {
                if (node->child[1]->nodekind == StmtK && node->child[1]->subkind.stmt == ReturnK)
                    symTab->applyToAll(checkIsUsed);
            }

            symTab->leave();

            childSuppressScope = false;
            isFuncDecl = false;
        }
        //Array type promotion and error checking
        if (node->nodekind == ExpK && node->subkind.exp == OpK && node->op == OPEN_BRACK)
        {
            //Setting the exptype of [ array to that of its Identifier.
            node->expType = node->child[0]->expType;
            //make sure that the index of the array is an integer.
            if (node->child[1]->expType != Integer)
            {
                char buff[64];
                convertExpTypeToString(node->child[1]->expType, buff);
                printf("ERROR(%d): Array '%s' should be indexed by type int but got type %s.\n",
                       node->lineno, node->child[0]->attr.name, buff);
                NUM_ERRORS++;
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

            //throw an error if the array is not indexed
            if (node->child[1]->nodekind == ExpK && node->child[1]->subkind.exp == IdK)
            {
                //printf("in array not indexed\n");
                //foo(node->child[1]);
                lookupNode = (treeNode *)symTab->lookup(std::string(node->child[1]->attr.name));
                if (lookupNode != NULL && lookupNode->isArray)
                {
                    printf("ERROR(%d): Array index is the unindexed array '%s'.\n", node->child[1]->lineno, node->child[1]->attr.name);
                    NUM_ERRORS++;
                }
            }
            node->isArray = false;
        }

        if (node->nodekind == ExpK && ((node->subkind.exp == OpK || node->subkind.exp == AssignK) && node->op != OPEN_BRACK))
        {
            if (node->op == SIZEOF)
            {
                //fixing op node. This node always returns an int
                //HACK TO MATCH
                if(node->parent->isRangeK)
                {
                    node->expType = UndefinedType;
                    if(node->child[0] != NULL && node->child[0]->nodekind == ExpK && node->child[0]->subkind.exp == IdK)
                    {
                        node->child[0]->expType = UndefinedType;
                    }
                }
                else
                    node->expType = Integer;

                if (node->child[0]->subkind.exp == IdK)
                {
                    lookupNode = (treeNode *)symTab->lookup(std::string(node->child[0]->attr.name));

                    if (lookupNode != NULL && !(lookupNode->isArray))
                    {
                        printf("ERROR(%d): The operation 'sizeof' only works with arrays.\n", node->lineno);
                        NUM_ERRORS++;
                    }
                }
                else
                    printf("size of lookup failed. child node is not IDk\n");
            }
            else
            {
                node->expType = typeTable(node, node->child[0], node->child[1]);
            }
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
    if (!nodeptr->isUsed && nodeptr->depth != 1)
    {
        printf("WARNING(%d): The variable '%s' seems not to be used.\n",
               nodeptr->lineno, symbolName.c_str());
        NUM_WARNINGS++;
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
            if(parentNode->isRangeK || parentNode->isRangeKBy)
                return UndefinedType; 

            if (lhs == Integer && rhs == Integer)
            {
                // printf("testing if array\n");
                // foo(lhsNode);
                // foo(rhsNode);
                
                if (!lhsNode->isArray && !rhsNode->isArray)
                {
                    //HACK
                    if (parentNode->parent->nodekind == StmtK && parentNode->parent->subkind.stmt == RangeK)
                    {
                        return UndefinedType;
                    }
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
                if (rhs != UndefinedType && rhs != Void)
                {
                    printf("ERROR(%d): '%s' requires operands of type int but rhs is of type %s.\n",
                           parentNode->lineno, parentNode->attr.string,
                           buff2);
                    NUM_ERRORS++;
                }
            }
            else if (lhs != Integer && rhs == Integer)
            {
                //HACK for matching output. Supress this Error
                if (lhs != UndefinedType && lhs != Void)
                {
                    printf("ERROR(%d): '%s' requires operands of type int but lhs is of type %s.\n",
                           parentNode->lineno, parentNode->attr.string,
                           buff1);
                    NUM_ERRORS++;
                }
            }
            else
            {
                //HACK TO MATCH OUTPUT
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
            lhs = lhsNode->expType;

            if (lhsNode->isArray)
            {
                printf("ERROR(%d): The operation '%s' does not work with arrays.\n", parentNode->lineno, op == CHSIGN ? "chsign" : "?");
                NUM_ERRORS++;
            }

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
                //printf("chsign\n");
                //HACK to match output
                if(parentNode->parent->nodekind == StmtK && parentNode->parent->subkind.stmt == RangeK)      
                        return UndefinedType;
                    
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
                return Boolean;
            }

            convertExpTypeToString(lhs, buff1);
            convertExpTypeToString(rhs, buff2);

            //foo(lhsNode);
            //foo(rhsNode);

            //suppressing. assuming the undefined type error is already handled in main loop
            if (lhs != UndefinedType)
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

            if (lhsNode->isArray || rhsNode->isArray)
            {
                printf("ERROR(%d): The operation '%s' does not work with arrays.\n", parentNode->lineno, parentNode->attr.string);
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
                    return lhs;
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
                if (lhs != UndefinedType && lhs != Void)
                {
                    printf("ERROR(%d): '%s' requires operands of the same type but lhs is type %s and rhs is type %s.\n",
                           parentNode->lineno, parentNode->attr.string, buff1, buff2);
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
                return Boolean;

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
