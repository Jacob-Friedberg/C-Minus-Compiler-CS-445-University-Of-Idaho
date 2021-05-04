#include "Tree.h"
#include "parser.tab.h"
#include "symbolTable.h"
#include "emitcode.h"
#include "codegen.h"

extern int globalOffset;

int tOffset = globalOffset;
int foffset = 0;

extern char srcFilename[256];


void line_sep()
{
    emitComment((char *)"** ** ** ** ** ** ** ** ** ** ** **");
}

void func_label_top(char *funcName)
{
    line_sep();
    emitComment((char *)"FUNCTION",funcName);
}

void func_label_bottom(char *funcName)
{
    emitComment((char *)"END FUNCTION",funcName);
    emitComment((char *)"");
}

void init_IO(SymbolTable *symtab,treeNode *tree)
{
    emitComment((char *)"C- Compiler Spring 2021");
    emitComment((char *)"Author: Jacob Friedberg");
    emitComment((char *)"File Compiled: ",srcFilename);
    emitComment((char *)"");

    func_label_top((char *)"input");

    emitRM((char *)"ST",3,-1,1,(char *)"Store return address");
    emitRO((char*)"IN",2,2,2,(char *)"Grab int input");
    emitRM((char *)"LD",3,-1,1,(char *)"Load return address");
    emitRM((char *)"LD",1,0,1,(char *)"Adjust fp");
    emitGoto(0,3,(char *)"Return");

    func_label_bottom((char *)"input");

    func_label_top((char *)"output");

    emitRM((char *)"ST",3,-1,1,(char *)"Store return address");
    emitRM((char *)"LD",3,-2,1,(char *)"Load parameter");
    emitRO((char *)"OUT",3,3,3,(char *)"Output integer");
    emitRM((char *)"LD",3,-1,1,(char *)"Load return address");
    emitRM((char *)"LD",1,0,1,(char *)"Adjust fp");
    emitGoto(0,3,(char *)"Return");

    func_label_bottom((char *)"output");

    func_label_top((char *)"inputb");

    emitRM((char *)"ST",3,-1,1,(char *)"Store return address");
    emitRO((char*)"INB",2,2,2,(char *)"Grab bool input");
    emitRM((char *)"LD",3,-1,1,(char *)"Load return address");
    emitRM((char *)"LD",1,0,1,(char *)"Adjust fp");
    emitGoto(0,3,(char *)"Return");

    func_label_bottom((char *)"inputb");

    func_label_top((char *)"outputb");

    emitRM((char *)"ST",3,-1,1,(char *)"Store return address");
    emitRM((char *)"LD",3,-2,1,(char *)"Load parameter");
    emitRO((char *)"OUTB",3,3,3,(char *)"Output bool");
    emitRM((char *)"LD",3,-1,1,(char *)"Load return address");
    emitRM((char *)"LD",1,0,1,(char *)"Adjust fp");
    emitGoto(0,3,(char *)"Return");

    func_label_bottom((char *)"outputb");

    func_label_top((char *)"inputc");

    emitRM((char *)"ST",3,-1,1,(char *)"Store return address");
    emitRO((char*)"INC",2,2,2,(char *)"Grab char input");
    emitRM((char *)"LD",3,-1,1,(char *)"Load return address");
    emitRM((char *)"LD",1,0,1,(char *)"Adjust fp");
    emitGoto(0,3,(char *)"Return");

    func_label_bottom((char *)"inputc");

    func_label_top((char *)"outputc");

    emitRM((char *)"ST",3,-1,1,(char *)"Store return address");
    emitRM((char *)"LD",3,-2,1,(char *)"Load parameter");
    emitRO((char *)"OUTC",3,3,3,(char *)"Output char");
    emitRM((char *)"LD",3,-1,1,(char *)"Load return address");
    emitRM((char *)"LD",1,0,1,(char *)"Adjust fp");
    emitGoto(0,3,(char *)"Return");

    func_label_bottom((char *)"outputc");

    func_label_top((char *)"outnl");

    emitRM((char *)"ST",3,-1,1,(char *)"Store return address");
    emitRO((char *)"OUTNL",3,3,3,(char *)"Output a newline");
    emitRM((char *)"LD",3,-1,1,(char *)"Load return address");
    emitRM((char *)"LD",1,0,1,(char *)"Adjust fp");
    emitGoto(0,3,(char *)"Return");

    func_label_bottom((char *)"outnl");
}


void gen_code(SymbolTable *symTab,TreeNode *tree)
{
    emitSkip(1);

    printf("goffset:%d\n",globalOffset);

    init_IO(symTab,tree);

}