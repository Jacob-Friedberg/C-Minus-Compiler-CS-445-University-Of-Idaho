#ifndef _TREE_H
#define _TREE_H
#include "scanType.h"
#include <cstddef>
// the exact type of the token or node involved.  These are divided into
// various "kinds" in the enums that follow

// Kinds of Operators
// these are the token numbers for the operators same as in flex
typedef int OpKind;

// Kinds of Statements
//typedef enum {DeclK, StmtK, ExpK} NodeKind;
enum UnionType
{
    cvalue,
    value,
    string
};

enum NodeKind
{
    DeclK,
    StmtK,
    ExpK
};

// Subkinds of Declarations
enum DeclKind
{
    VarK,
    FuncK,
    ParamK
};

// Subkinds of Statements
enum StmtKind
{
    NullK,
    IfK,
    WhileK,
    ForK,
    CompoundK,
    ReturnK,
    BreakK,
    RangeK
};

// Subkinds of Expressions
enum ExpKind
{
    OpK,
    ConstantK,
    IdK,
    AssignK,
    InitK,
    CallK
};

// ExpType is used for type checking (Void means no type or value, UndefinedType means undefined)
typedef enum 
{
    Void,
    Integer,
    Boolean,
    Char,
    CharInt,
    Equal,
    UndefinedType
}ExpType;

// What kind of scoping is used?  (decided during typing)
enum ScopeKind
{
    None,
    Local,
    Global,
    Parameter,
    LocalStatic
};

#define MAXCHILDREN 3

typedef struct treeNode
{
    // connectivity in the tree
    struct treeNode *parent;    //parent of the node
    struct treeNode *child[MAXCHILDREN]; // children of the node
    struct treeNode *sibling;            // siblings for the node

    // what kind of node
    int lineno;        // linenum relevant to this node
    NodeKind nodekind; // type of this node
    union              // subtype of type
    {
        DeclKind decl; // used when DeclK
        StmtKind stmt; // used when StmtK
        ExpKind exp;   // used when ExpK
    } subkind;

    // extra properties about the node depending on type of the node
    //done in bison
    union // relevant data to type -> attr
    {
        /*OpKind op;*/          // type of token (same as in bison)
        int value;            // used when an integer constant or boolean
        unsigned char cvalue; // used when a character
        char *string;         // used when a string constant
        char *name;           // used when IdK
    } attr;
    UnionType unionType;
    //Depth of the stack of scopes when it is entered into the symbol table 
    bool isRangeKBy;
    bool isRangeK;
    int depth;
    bool isFunc;
    bool isParam;
    int numParams;
    bool undeclared;
    bool isIo;
    ScopeKind scope;
    int loc; // memory location
    char *tokenStr;
    bool isInitErrorThrown;
    OpKind op;
    bool isOp;
    //Has the attribute been set?
    bool attrSet;
    ExpType expType; // used when ExpK for type checking
    bool isArray;    // is this an array
    int size;
    bool isStatic;   // is staticly allocated?
    bool isUsed;
    bool isInit;
    bool isConst;

    // even more semantic stuff will go here in later assignments.
} TreeNode;

TreeNode *newDeclNode(DeclKind kind,
                      ExpType type,
                      TokenData *token = NULL,
                      TreeNode *c0 = NULL,
                      TreeNode *c1 = NULL,
                      TreeNode *c2 = NULL);

TreeNode *newStmtNode(StmtKind kind,
                      TokenData *token,
                      TreeNode *c0 = NULL,
                      TreeNode *c1 = NULL,
                      TreeNode *c2 = NULL);

TreeNode *newExpNode(ExpKind kind,
                     TokenData *token,
                     TreeNode *c0 = NULL,
                     TreeNode *c1 = NULL,
                     TreeNode *c2 = NULL);

void printTree(TreeNode *node,int indentLevel);
void printTypedTree(TreeNode *node, int indentLevel, bool memPrintFlag);
void dumpNode(TreeNode *node);
TreeNode *addSibling(TreeNode *t, TreeNode *s);
void setType(TreeNode *t, ExpType type, bool isStatic);
void convertExpTypeToString(ExpType type, char *string);
void printSpaces(int indentLevel);
#endif