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

void checkTree(SymbolTable *symTab, TreeNode *node, int indentLevel, bool suppressScope, TreeNode *parent)
{
    char typing[64];
    int sibling_count = 1;
    bool isCompound = false;
    bool isFor = false;
    bool isAssign = false;
    treeNode *lookupNode;
    //symTab->debug(true);
    while (node != NULL)
    {
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
                //printf("For [line: %d]\n", node->lineno);
                break;
            case CompoundK:
                //printf("Compound [line: %d]\n", node->lineno);
                if (!suppressScope)
                {
                    symTab->enter(std::string("THIS IS A COMPOUND"));
                }
                suppressScope = false;
                isCompound = true;
                break;
            case ReturnK:
                //printf("Return [line: %d]\n", node->lineno);
                break;
            case BreakK:
                //printf("Break [line: %d]\n", node->lineno);
                break;
            case RangeK:
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
                if (node->isOp && node->op == CHSIGN)
                {
                    ; //printf("Op: CHSIGN [line: %d]\n", node->lineno);
                }
                else if (node->isOp && node->op == SIZEOF)
                {
                    ; //printf("Op: SIZEOF [line: %d]\n", node->lineno);
                }
                else
                    ; //printf("Op: %s [line: %d]\n", node->attr.string, node->lineno);
                break;
            case ConstantK:
                if (strcmp(typing, "char") == 0)
                {
                    if (node->isArray)
                    {
                        ; //printf("Const is array of type %s: \"%s\" [line: %d]\n", typing, node->attr.string, node->lineno);
                    }
                    else
                        ; //printf("Const of type %s: '%c' [line: %d]\n", typing, node->attr.value, node->lineno);
                }
                else if (strcmp(typing, "bool") == 0)
                {
                    ; //printf("Const of type %s: %s [line: %d]\n", typing, node->attr.value ? "true" : "false", node->lineno);
                }
                else
                    ; //printf("Const of type %s: %d [line: %d]\n", typing, node->attr.value, node->lineno);
                break;
            case IdK:
                lookupNode = (treeNode *)symTab->lookup(std::string(node->attr.name));
                //foo(lookupNode);
                //symTab->print(foo);
                if (lookupNode == NULL)
                {

                    printf("ERROR(%d): Symbol '%s' is not declared.\n", node->lineno, node->attr.name);
                    NUM_ERRORS++;
                }
                else
                {
                    lookupNode->isUsed = true;
                    node->expType = lookupNode->expType;
                    node->isArray = lookupNode->isArray;
                    node->isStatic = lookupNode->isStatic;
                    node->isFunc = lookupNode->isFunc;

                    if (!lookupNode->isInit)
                    {
                        bool suppressWarning = false;
                        treeNode *currParent = node->parent;
                        treeNode *currNode = node;

                        if (currParent->op == OPEN_BRACK)
                        {
                            currNode = currParent;
                            currParent = currParent->parent;
                        }
                        //Supress warning if we are on the LHS of an assignment(when we are the first child we are on the LHS)
                        if (currParent != NULL && currParent->nodekind == ExpK && currParent->subkind.exp == AssignK && currParent->child[0] == currNode && currParent->op == ASS)
                            suppressWarning = true;

                        if (lookupNode->isStatic || symTab->lookupGlobal(std::string(node->attr.name)) != NULL)
                            suppressWarning = true;

                        // if (currParent->op == SIZEOF)
                        //     suppressWarning = true;
                        if (!suppressWarning)
                        {
                            if (!lookupNode->isInitErrorThrown)
                            {
                                printf("WARNING(%d): Variable '%s' may be uninitialized when used here.\n", node->lineno, node->attr.name);
                                NUM_WARNINGS++;
                                lookupNode->isInitErrorThrown = true;
                            }
                            //printf("Parent\n");
                            //foo(currParent);
                            //printf("id Node\n");
                            //foo(node);
                            //foo(lookupNode);
                        }
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

                if (lookupNode != NULL && !(lookupNode->isFunc))
                {
                    printf("ERROR(%d): '%s' is a simple variable and cannot be called.\n", node->lineno, node->attr.name);
                    NUM_ERRORS++;
                    break;
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
                lookupNode = (treeNode *)symTab->lookupGlobal(node->attr.name);
                //If the symbol does not exist then we can add it
                if (lookupNode == NULL)
                {
                    if (symTab->insert(std::string(node->attr.name), (void *)node))
                    {

                        node->isUsed = false;
                        //Special handleing for the case of init variables in for loops
                        if(node->parent != NULL && node->parent->nodekind == StmtK && node->parent->subkind.stmt == ForK)
                            node->isInit = true;
                        else
                            node->isInit = false;

                        node->isInitErrorThrown = false;
                        
                        
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
                }
                //throw error on already declared variable
                else
                {
                    printf("ERROR(%d): Symbol '%s' is already declared at line %d.\n",
                           node->lineno,
                           lookupNode->attr.name,
                           lookupNode->lineno);
                    NUM_ERRORS++;
                }

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
                    node->isUsed = false;
                    // node->isInit = true;
                    node->isFunc = true;
                }
                else
                {
                    lookupNode = (treeNode *)symTab->lookup(node->attr.string);
                    printf("ERROR(%d): Symbol '%s' is already declared at line %d.\n",
                           node->lineno,
                           lookupNode->attr.string,
                           lookupNode->lineno);
                    NUM_ERRORS++;
                }
                symTab->enter(std::string(node->attr.string));
                suppressScope = true;
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
                    symTab->insert(std::string(node->attr.name), (void *)node);
                }

                //printf("Parm: %s is array of type %s [line: %d]\n", node->attr.name, typing, node->lineno);
                else
                {
                    node->isUsed = false;
                    symTab->insert(std::string(node->attr.name), (void *)node);
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
                checkTree(symTab, node->child[i], indentLevel + 1, suppressScope, node);
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
            symTab->leave();
            isCompound = false;
        }
        if (isFor)
        {
            //symTab->print(foo);
            symTab->applyToAll(checkIsUsed);
            symTab->leave();
            isFor = false;
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

    if (!nodeptr->isUsed)
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
            if (lhs == Integer && rhs == Integer)
            {
                // printf("testing if array\n");
                // foo(lhsNode);
                // foo(rhsNode);
                if (!lhsNode->isArray && !rhsNode->isArray)
                    return Integer;

                printf("ERROR(%d): The operation '%s' does not work with arrays.\n", parentNode->lineno, parentNode->attr.string);
                NUM_ERRORS++;

                return Integer;
            }

            convertExpTypeToString(lhs, buff1);
            convertExpTypeToString(rhs, buff2);
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

            if (lhs == Integer)
            {
                if (lhsNode->isArray)
                {
                    printf("ERROR(%d): The operation '%s' does not work with arrays.\n", parentNode->lineno, op == CHSIGN ? "chsign" : "?");
                    NUM_ERRORS++;
                }
                return lhs;
            }

            convertExpTypeToString(lhs, buff1);

            if (op == CHSIGN)
            {
                printf("ERROR(%d): Unary 'chsign' requires an operand of type %s but was given type %s.\n",
                       parentNode->lineno,
                       "int",
                       buff1);
                NUM_ERRORS++;

                if (lhsNode->isArray)
                {
                    printf("ERROR(%d): The operation 'chsign' does not work with arrays.\n", parentNode->lineno);
                    NUM_ERRORS++;
                }
            }
            else
            {

                printf("ERROR(%d): Unary '%s' requires an operand of type %s but was given type %s.\n",
                       parentNode->lineno, parentNode->attr.string,
                       "int",
                       buff1);
                NUM_ERRORS++;
            }

            return lhs;
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

            printf("ERROR(%d): '%s' requires operands of the same type but lhs is type %s and rhs is type %s.\n",
                   parentNode->lineno, parentNode->attr.string, buff1, buff2);
            NUM_ERRORS++;

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
                if (lhs != UndefinedType)
                {
                    printf("ERROR(%d): '%s' requires operands of the same type but lhs is type %s and rhs is type %s.\n",
                           parentNode->lineno, parentNode->attr.string, buff1, buff2);
                    NUM_ERRORS++;
                }
            }

            return lhs;
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
                printf("ERROR(%d): Unary '%s' requires an operand of type %s but was given type %s.\n",
                       parentNode->lineno, parentNode->attr.string,
                       "int",
                       buff1);
                NUM_ERRORS++;

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
