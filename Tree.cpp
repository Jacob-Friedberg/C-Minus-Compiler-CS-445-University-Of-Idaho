#include "Tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// save TokenData block!!

void convertExpTypeToString(ExpType type, char *string);
TreeNode *newDeclNode(DeclKind kind, ExpType type, TokenData *token, TreeNode *c0, TreeNode *c1, TreeNode *c2)
{
    //allocate space for the node
    TreeNode *treeNode = new TreeNode;

    treeNode->child[0] = c0;
    treeNode->child[1] = c1;
    treeNode->child[2] = c2;
    treeNode->sibling = NULL;

    treeNode->lineno = token->lineNum;

    treeNode->nodekind = DeclK;

    treeNode->subkind.decl = kind;

    treeNode->expType = type;

    treeNode->attrSet = false;

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

    treeNode->lineno = token->lineNum;

    treeNode->nodekind = StmtK;

    treeNode->subkind.stmt = kind;

    treeNode->expType = UndefinedType;

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

    treeNode->lineno = token->lineNum;

    treeNode->nodekind = ExpK;

    treeNode->subkind.exp = kind;

    treeNode->expType = UndefinedType;

    treeNode->attrSet = false;

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
                printf("If [line: %d]\n",node->lineno);
                break;
            case WhileK:
                printf("While\n");
                break;
            case ForK:
                printf("For [line: %d]\n",node->lineno);
                break;
            case CompoundK:
                printf("Compound [line: %d]\n",node->lineno);
                break;
            case ReturnK:
                printf("Return [line: %d]\n",node->lineno);
                break;
            case BreakK:
                printf("Break [line: %d]\n",node->lineno);
                break;
            case RangeK:
                printf("Range [line: %d]\n",node->lineno);
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
                printf("Op: %s [line: %d]\n",node->attr.string,node->lineno);
                break;
            case ConstantK:
                if(strcmp(typing,"char") == 0)
                {
                printf("Const of type %s: %c [line: %d]\n",typing,node->attr.value,node->lineno);     
                }
                else
                    printf("Const of type %s: %d [line: %d]\n",typing,node->attr.value,node->lineno);
                break;
            case IdK:
                printf("Id: %s [line: %d]\n", node->attr.name, node->lineno);
                break;
            case AssignK:
                printf("Assign: %s [line: %d]\n",node->attr.string,node->lineno);
                break;
            case InitK:
                printf("Init:\n");
                break;
            case CallK:
                printf("Call: %s [line: %d]\n",node->attr.name,node->lineno);
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
                    printf("internal error NULL REACHED in attrName funck\n");
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

void dumpNode(TreeNode *node)
{
    printf("---Node Information---\n");
    for (size_t i = 0; i < MAXCHILDREN; i++)
    {
        if (node->child[i] != NULL)
        {

            printf("Child[%ld]: Exists\n", i);
        }
    }

    printf("Linenumber is:%d\n", node->lineno);

    printf("NodeKind is: %d\n", node->nodekind);

    printf("the subkind is: %d\n", node->subkind.decl);

    printf("the EXP type is: %d\n", node->expType);
}

// add a TreeNode to a list of siblings.
// Adding a NULL to the list is probably a programming error!
TreeNode *addSibling(TreeNode *t, TreeNode *s)
{
    if (s == NULL)
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