#include "Tree.h"
#include "parser.tab.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// save TokenData block!!

void convertExpTypeToString(ExpType type, char *string);
void convertScopeKindToString(ScopeKind scope, char *string);
TreeNode *newDeclNode(DeclKind kind, ExpType type, TokenData *token, TreeNode *c0, TreeNode *c1, TreeNode *c2)
{
    //allocate space for the node
    TreeNode *treeNode = new TreeNode;

    treeNode->child[0] = c0;
    treeNode->child[1] = c1;
    treeNode->child[2] = c2;
    treeNode->sibling = NULL;

    if (token != NULL)
        treeNode->lineno = token->lineNum;

    treeNode->nodekind = DeclK;

    treeNode->subkind.decl = kind;

    treeNode->expType = type;

    if (token != NULL)
        treeNode->tokenStr = token->tokenStr;
    treeNode->isFunc = false;
    treeNode->isConst = false;
    treeNode->isParam = false;
    treeNode->numParams = 0;
    treeNode->isUsed = false;
    treeNode->isIo = false;
    treeNode->scope = None;
    treeNode->size = -99;
    treeNode->attrSet = false;
    //treeNode->sideOfAssignment = unknownSide;

    return treeNode;
}
TreeNode *newStmtNode(StmtKind kind, TokenData *token, TreeNode *c0, TreeNode *c1, TreeNode *c2)
{
    //allocate space for the node
    TreeNode *treeNode = new TreeNode;

    treeNode->child[0] = c0;
    treeNode->child[1] = c1;
    treeNode->child[2] = c2;
    treeNode->sibling = NULL;

    if (token != NULL)
        treeNode->lineno = token->lineNum;

    treeNode->nodekind = StmtK;

    if (token != NULL)
        treeNode->tokenStr = token->tokenStr;
    treeNode->subkind.stmt = kind;
    treeNode->isRangeK = false;
    treeNode->isRangeKBy = false;
    treeNode->expType = UndefinedType;
    treeNode->isFunc = false;
    treeNode->isConst = false;
    treeNode->isParam = false;
    treeNode->numParams = 0;
    treeNode->isUsed = false;
    treeNode->isIo = false;
    //treeNode->sideOfAssignment = unknownSide;

    treeNode->attrSet = false;

    return treeNode;
}
TreeNode *newExpNode(ExpKind kind, TokenData *token, TreeNode *c0, TreeNode *c1, TreeNode *c2)
{
    TreeNode *treeNode = new TreeNode;

    treeNode->child[0] = c0;
    treeNode->child[1] = c1;
    treeNode->child[2] = c2;
    treeNode->sibling = NULL;

    if (token != NULL)
        treeNode->lineno = token->lineNum;

    treeNode->nodekind = ExpK;

    if (token != NULL)
        treeNode->tokenStr = token->tokenStr;
    treeNode->subkind.exp = kind;
    treeNode->isFunc = false;
    treeNode->isConst = false;
    treeNode->isParam = false;
    treeNode->numParams = 0;
    treeNode->isUsed = false;
    treeNode->isIo = false;
    treeNode->expType = UndefinedType;
    treeNode->sideOfAssignment = unknownSide;

    treeNode->attrSet = false;

    treeNode->isOp = false;

    if (kind == OpK)
    {
        if (token != NULL)
            treeNode->op = token->tokenClass;
        treeNode->isOp = true;
    }
    if (kind == AssignK)
        if (token != NULL)
            treeNode->op = token->tokenClass;

    return treeNode;
}

void printSpaces(int indentLevel)
{
    if (indentLevel != 0)
    {
        for (int i = 0; i < indentLevel; i++)
        {
            printf(".");
            printf("   ");
        }
    }
    //Do nothing
}

void printTree(TreeNode *node, int indentLevel)
{
    char typing[64];
    int sibling_count = 1;
    while (node != NULL)
    {
        convertExpTypeToString(node->expType, typing);

        if (node->nodekind == StmtK)
        {
            switch (node->subkind.stmt)
            {
            case NullK:
                printf("NULL\n");
                break;
            case IfK:
                printf("If [line: %d]\n", node->lineno);
                break;
            case WhileK:
                printf("While [line: %d]\n", node->lineno);
                break;
            case ForK:
                printf("For [line: %d]\n", node->lineno);
                break;
            case CompoundK:
                printf("Compound [line: %d]\n", node->lineno);
                break;
            case ReturnK:
                printf("Return [line: %d]\n", node->lineno);
                break;
            case BreakK:
                printf("Break [line: %d]\n", node->lineno);
                break;
            case RangeK:
                printf("Range [line: %d]\n", node->lineno);
                break;

            default:
                printf("Unknown stmtK subkind \n");
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
                    printf("Op: CHSIGN [line: %d]\n", node->lineno);
                }
                else if (node->isOp && node->op == SIZEOF)
                {
                    printf("Op: SIZEOF [line: %d]\n", node->lineno);
                }
                else
                    printf("Op: %s [line: %d]\n", node->attr.string, node->lineno);
                break;
            case ConstantK:
                if (strcmp(typing, "char") == 0)
                {
                    if (node->isArray)
                    {
                        printf("Const is array of type %s: \"%s\" [line: %d]\n", typing, node->attr.string, node->lineno);
                    }
                    else
                        printf("Const of type %s: '%c' [line: %d]\n", typing, node->attr.value, node->lineno);
                }
                else if (strcmp(typing, "bool") == 0)
                {
                    printf("Const of type %s: %s [line: %d]\n", typing, node->attr.value ? "true" : "false", node->lineno);
                }
                else
                    printf("Const of type %s: %d [line: %d]\n", typing, node->attr.value, node->lineno);
                break;
            case IdK:
                printf("Id: %s [line: %d]\n", node->attr.name, node->lineno);
                break;
            case AssignK:
                printf("Assign: %s [line: %d]\n", node->attr.string, node->lineno);
                break;
            case InitK:
                printf("Init:\n");
                break;
            case CallK:
                printf("Call: %s [line: %d]\n", node->attr.name, node->lineno);
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
                    printf("Var: %s is array of type %s [line: %d]\n", node->attr.name, typing, node->lineno);
                else
                    printf("Var: %s of type %s [line: %d]\n", node->attr.name, typing, node->lineno);
                break;
            case FuncK:
                if (node->attr.name == NULL)
                {
                    printf("internal error NULL REACHED in attrName funck\n");
                    break;
                }
                printf("Func: %s returns type %s [line: %d]\n", node->attr.string, typing, node->lineno);
                break;
            case ParamK:
                if (node->attr.name == NULL)
                {
                    printf("internal error NULL REACHED in attrName Paramk\n");
                    break;
                }

                //printf("Parm: %s%s of type %s [line: %d]\n", node->attr.name,node->isArray?" is array":"", typing, node->lineno);

                if (node->isArray)
                    printf("Parm: %s is array of type %s [line: %d]\n", node->attr.name, typing, node->lineno);
                else
                    printf("Parm: %s of type %s [line: %d]\n", node->attr.name, typing, node->lineno);
                break;
            default:
                printf("Unknown Declk subKind\n");
                break;
            }
        }
        else
            printf("Unknown node kind\n");

        for (int i = 0; i < MAXCHILDREN; i++)
        {
            //printf("indentL:%d i:%d\n",indentLevel,i);
            if (node->child[i] != NULL)
            {
                printSpaces(indentLevel + 1);
                printf("Child: %d ", i);
                printTree(node->child[i], indentLevel + 1);
            }
            //else
            //printf("child:%d was NULL at indent %d\n", i, indentLevel);
        }

        if (node->sibling != NULL)
        {
            printSpaces(indentLevel);
            printf("Sibling: %d ", sibling_count++);
            node = node->sibling;
        }
        else
            node = node->sibling;
    }
}

void printTypedTree(TreeNode *node, int indentLevel, bool memPrintFlag)
{
    char typing[64];
    char scoping[64];
    int sibling_count = 1;
    while (node != NULL)
    {

        // if(node->op == MULT || node->op == PLUS || node->op == MOD)
        // {
        //     convertExpTypeToString(UndefinedType, typing);
        // }
        // else
        convertExpTypeToString(node->expType, typing);
        convertScopeKindToString(node->scope, scoping);

        if (node->nodekind == StmtK)
        {
            switch (node->subkind.stmt)
            {
            case NullK:
                printf("NULL\n");
                break;
            case IfK:
                printf("If [line: %d]\n", node->lineno);
                break;
            case WhileK:
                printf("While [line: %d]\n", node->lineno);
                break;
            case ForK:
                if (memPrintFlag)
                {
                    printf("For [mem: %s loc: %d size: %d] [line: %d]\n",
                           scoping,
                           node->loc,
                           node->size,
                           node->lineno);
                }
                else
                    printf("For [line: %d]\n", node->lineno);
                break;
            case CompoundK:
                if (memPrintFlag)
                {
                    printf("Compound [mem: %s loc: %d size: %d] [line: %d]\n",
                           scoping,
                           node->loc,
                           node->size,
                           node->lineno);
                }
                else
                {
                    printf("Compound [line: %d]\n",
                           node->lineno);
                }

                break;
            case ReturnK:
                printf("Return [line: %d]\n", node->lineno);
                break;
            case BreakK:
                printf("Break [line: %d]\n", node->lineno);
                break;
            case RangeK:
                printf("Range [line: %d]\n", node->lineno);
                break;

            default:
                printf("Unknown stmtK subkind \n");
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
                    if (node->expType == UndefinedType)
                    {
                        printf("Op: chsign of undefined type [line: %d]\n", node->lineno);
                    }
                    else
                        printf("Op: chsign of type %s [line: %d]\n", typing, node->lineno);
                }
                else if (node->isOp && node->op == SIZEOF)
                {
                    if (node->expType == UndefinedType)
                    {
                        printf("Op: sizeof of undefined type [line: %d]\n", node->lineno);
                    }
                    else
                        printf("Op: sizeof of type %s [line: %d]\n", typing, node->lineno);
                }
                else
                {
                    if (node->expType == UndefinedType)
                    {
                        printf("Op: %s of undefined type [line: %d]\n", node->attr.string, node->lineno);
                    }
                    else
                        printf("Op: %s of type %s [line: %d]\n", node->attr.string, typing, node->lineno);
                }
                break;
            case ConstantK:
                if (strcmp(typing, "char") == 0)
                {
                    if (memPrintFlag)
                    {
                        if (node->isArray)
                        {
                            printf("Const \"%s\" of array of type %s [mem: %s loc: %d size: %d] [line: %d]\n",
                                   node->attr.string,
                                   typing,
                                   scoping,
                                   node->loc - 1,
                                   node->size,
                                   node->lineno);
                        }
                        else
                            printf("Const '%c' of type %s [line: %d]\n", node->attr.value, typing, node->lineno);
                    }
                    else
                    {
                        if (node->isArray)
                        {
                            printf("Const is array \"%s\" of type %s [line: %d]\n", node->attr.string, typing, node->lineno);
                        }
                        else
                            printf("Const '%c' of type %s [line: %d]\n", node->attr.value, typing, node->lineno);
                    }
                }
                else if (strcmp(typing, "bool") == 0)
                {
                    printf("Const %s of type %s [line: %d]\n", node->attr.value ? "true" : "false", typing, node->lineno);
                }
                else
                    printf("Const %d of type %s [line: %d]\n", node->attr.value, typing, node->lineno);
                break;
            case IdK:
                if (memPrintFlag)
                {
                    //we are not an array
                    if (!node->isArray)
                    {
                        if (node->expType == UndefinedType)
                        {
                            printf("Id: %s of undefined type [line: %d]\n", node->attr.name, node->lineno);
                        }
                        else if (node->scope == LocalStatic)
                        {
                            printf("Id: %s of static type %s [mem: %s loc: %d size: %d] [line: %d]\n",
                                   node->attr.name,
                                   typing,
                                   scoping,
                                   node->loc,
                                   node->size,
                                   node->lineno);
                        }
                        else
                            printf("Id: %s of type %s [mem: %s loc: %d size: %d] [line: %d]\n",
                                   node->attr.name,
                                   typing,
                                   scoping,
                                   node->loc,
                                   node->size,
                                   node->lineno);
                    }
                    //we are an array
                    else
                    {
                        if (node->scope == LocalStatic)
                        {
                            printf("Id: %s of static array of type %s [mem: %s loc: %d size: %d] [line: %d]\n",
                                   node->attr.name,
                                   typing,
                                   scoping,
                                   node->loc - 1,
                                   node->size,
                                   node->lineno);
                        }
                        else if (node->scope == Parameter)
                        {
                            printf("Id: %s of array of type %s [mem: %s loc: %d size: %d] [line: %d]\n",
                                   node->attr.name,
                                   typing,
                                   scoping,
                                   node->loc,
                                   node->size,
                                   node->lineno);
                        }
                        else
                        {
                            printf("Id: %s of array of type %s [mem: %s loc: %d size: %d] [line: %d]\n",
                                   node->attr.name,
                                   typing,
                                   scoping,
                                   node->loc - 1,
                                   node->size,
                                   node->lineno);
                        }
                    }
                }
                else
                {
                    if (node->expType == UndefinedType)
                    {
                        printf("Id: %s of undefined type [line: %d]\n", node->attr.name, node->lineno);
                    }
                    else
                        printf("Id: %s of type %s [line: %d]\n", node->attr.name, typing, node->lineno);
                }

                break;
            case AssignK:
                if (memPrintFlag)
                {
                    if (node->isArray)
                    {
                        printf("Assign: %s of array of type %s [line: %d]\n",
                               node->attr.string,
                               typing,
                               node->lineno);
                    }
                    else
                    {
                        printf("Assign: %s of type %s [line: %d]\n",
                               node->attr.string,
                               typing,
                               node->lineno);
                    }
                }
                else
                {
                    printf("Assign: %s of type %s [line: %d]\n", node->attr.string, typing, node->lineno);
                }
                break;
            case InitK:
                printf("Init:\n");
                break;
            case CallK:
                printf("Call: %s of type %s [line: %d]\n", node->attr.name, typing, node->lineno);
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

                if (memPrintFlag)
                {
                    if (node->attr.name == NULL)
                    {
                        printf("internal error NULL REACHED in attrName Vark\n");
                    }

                    if (node->scope == LocalStatic)
                    {
                        if (node->isArray)
                            printf("Var: %s of static array of type %s [mem: %s loc: %d size: %d] [line: %d]\n",
                                   node->attr.name,
                                   typing,
                                   scoping,
                                   node->loc - 1,
                                   node->size,
                                   node->lineno);
                        else
                            printf("Var: %s of static type %s [mem: %s loc: %d size: %d] [line: %d]\n",
                                   node->attr.name,
                                   typing,
                                   scoping,
                                   node->loc,
                                   node->size,
                                   node->lineno);
                    }
                    else
                    {
                        if (node->isArray)
                            printf("Var: %s of array of type %s [mem: %s loc: %d size: %d] [line: %d]\n",
                                   node->attr.name,
                                   typing,
                                   scoping,
                                   node->loc - 1,
                                   node->size,
                                   node->lineno);
                        else
                            printf("Var: %s of type %s [mem: %s loc: %d size: %d] [line: %d]\n",
                                   node->attr.name,
                                   typing,
                                   scoping,
                                   node->loc,
                                   node->size,
                                   node->lineno);
                    }
                }
                else
                {
                    if (node->attr.name == NULL)
                    {
                        printf("internal error NULL REACHED in attrName Vark\n");
                    }

                    if (node->isArray)
                        printf("Var: %s is array of type %s [line: %d]\n", node->attr.name, typing, node->lineno);
                    else
                        printf("Var: %s of type %s [line: %d]\n", node->attr.name, typing, node->lineno);
                }
                break;
            case FuncK:
                if (memPrintFlag)
                {
                    if (node->attr.name == NULL)
                    {
                        printf("internal error NULL REACHED in attrName funck\n");
                        break;
                    }
                    printf("Func: %s returns type %s [mem: %s loc: %d size: %d] [line: %d]\n",
                           node->attr.string,
                           typing,
                           scoping,
                           node->loc,
                           node->size,
                           node->lineno);
                }
                else
                {
                    if (node->attr.name == NULL)
                    {
                        printf("internal error NULL REACHED in attrName funck\n");
                        break;
                    }
                    printf("Func: %s returns type %s [line: %d]\n", node->attr.string, typing, node->lineno);
                }

                break;
            case ParamK:
                if (node->attr.name == NULL)
                {
                    printf("internal error NULL REACHED in attrName Paramk\n");
                    break;
                }

                //printf("Parm: %s%s of type %s [line: %d]\n", node->attr.name,node->isArray?" is array":"", typing, node->lineno);

                if (memPrintFlag)
                {
                    if (node->isArray)
                        printf("Parm: %s of array of type %s [mem: %s loc: %d size: %d] [line: %d]\n",
                               node->attr.name,
                               typing,
                               scoping,
                               node->loc,
                               node->size,
                               node->lineno);
                    else
                        printf("Parm: %s of type %s [mem: %s loc: %d size: %d] [line: %d]\n",
                               node->attr.name,
                               typing,
                               scoping,
                               node->loc,
                               node->size,
                               node->lineno);
                }
                else
                {
                    if (node->isArray)
                        printf("Parm: %s is array of type %s [line: %d]\n", node->attr.name, typing, node->lineno);
                    else
                        printf("Parm: %s of type %s [line: %d]\n", node->attr.name, typing, node->lineno);
                }

                break;
            default:
                printf("Unknown Declk subKind\n");
                break;
            }
        }
        else
            printf("Unknown node kind\n");

        for (int i = 0; i < MAXCHILDREN; i++)
        {
            //printf("indentL:%d i:%d\n",indentLevel,i);
            if (node->child[i] != NULL)
            {
                printSpaces(indentLevel + 1);
                printf("Child: %d  ", i);
                printTypedTree(node->child[i], indentLevel + 1, memPrintFlag);
            }
            //else
            //printf("child:%d was NULL at indent %d\n", i, indentLevel);
        }

        if (node->sibling != NULL)
        {
            printSpaces(indentLevel);
            printf("Sibling: %d  ", sibling_count++);
            node = node->sibling;
        }
        else
            node = node->sibling;
    }
}

extern int NUM_ERRORS;
// add a TreeNode to a list of siblings.
// Adding a NULL to the list is probably a programming error!
TreeNode *addSibling(TreeNode *t, TreeNode *s)
{
    if (s == NULL && NUM_ERRORS == 0)
    {
        printf("ERROR(SYSTEM): never add a NULL to a sibling list.\n");
        exit(1);
    }
    if (t != NULL)
    {
        TreeNode *tmp;

        tmp = t;
        while (tmp->sibling != NULL)
            tmp = tmp->sibling;
        tmp->sibling = s;
        return t;
    }
    return s;
}

// pass the static and type attribute down the sibling list
void setType(TreeNode *t, ExpType type, bool isStatic)
{
    while (t)
    {
        t->expType = type;
        t->isStatic = isStatic;

        t = t->sibling;
    }
}
//Destructive to string
void convertExpTypeToString(ExpType type, char *string)
{
    switch (type)
    {
    case Void:
        strcpy(string, "void");
        break;
    case Integer:
        strcpy(string, "int");
        break;
    case Boolean:
        strcpy(string, "bool");
        break;
    case Char:
        strcpy(string, "char");
        break;
    case CharInt:
        strcpy(string, "charint");
        break;
    case Equal:
        strcpy(string, "Equal");
        break;
    case UndefinedType:
        strcpy(string, "Undefined");
        break;
    default:
        printf("Undefined EXP given to conversion function\n");
        strcpy(string, "FAILURE");
        break;
    }
}

void convertScopeKindToString(ScopeKind scope, char *string)
{
    switch (scope)
    {
    case None:
        strcpy(string, "None");
        break;
    case Local:
        strcpy(string, "Local");
        break;
    case Global:
        strcpy(string, "Global");
        break;
    case Parameter:
        strcpy(string, "Parameter");
        break;
    case LocalStatic:
        strcpy(string, "LocalStatic");
        break;
    default:
        printf("Undefined SCOPE given to conversion function\n");
        strcpy(string, "FAILURE");
        break;
    }
}

void dumpNode(treeNode *node)
{
    char buff[64];
    convertExpTypeToString(node->expType, buff);
    printf("linenumber:%d\n", node->lineno);
    printf("token number: %d\n", node->op);

    if (node->unionType == string)
    {
        printf("Token string: %s\n", node->attr.string);
    }
    else if (node->unionType == cvalue)
    {
        printf("Token char: %s\n", node->attr.string);
    }
    else if (node->unionType == value)
        printf("Token value: %d\n", node->attr.value);
    else
    {
        printf("Unknown union type\n");
    }

    if (node->isInit)
        printf("is init: true\n");
    else
        printf("is init: false\n");

    if (node->isStatic)
        printf("is static: true\n");
    else
        printf("is static: false\n");

    if (node->isArray)
        printf("is array: true\n");
    else
        printf("is array: false\n");

    if (node->isFunc)
        printf("is Func: true\n");
    else
        printf("is Func: false\n");

    if (node->isInitErrorThrown)
        printf("isInitErrorThrown: true\n");
    else
        printf("isInitErrorThrown: false\n");
    if (node->isUsed)
        printf("isUsed: true\n");
    else
        printf("IsUsed: false\n");
    if (node->isParam)
        printf("isParam: true\n");
    else
        printf("IsParam: false\n");

    printf("depth:%d\n", node->depth);

    printf("exptype: %s\n\n", buff);
}