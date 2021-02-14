%{
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include "scanType.h"
#include "ourgetopt.h"


extern int yylex();
extern FILE *yyin;
extern int yydebug;

#define YYERROR_VERBOSE
void yyerror(const char *msg)
{
    printf("ERROR: %s\n", msg);
}

static char *toUpperString(char *str)
{
    int i = 0;
    while(str[i])
    {
        str[i]=toupper(str[i]);
        i++;
    }
    return str;
}


%}

%define parse.lac full
%define parse.error detailed


// this is included in the tab.h file
// so scanType.h must be included before the tab.h file!!!!
%union {
    TokenData *tokenData;
    void *treenode;
}

/*tokens are our terminals*/ 
%token <tokenData> ID NUMCONST CHARCONST STRINGCONST 
%token <tokenData> INT BOOL CHAR IF THEN ELSE WHILE DO FOR TO 
%token <tokenData> BY RETURN BREAK STATIC NOT AND OR TRUE FALSE
%token <tokenData> OPEN_BRACE CLOSE_BRACE OPEN_PAREN CLOSE_PAREN
%token <tokenData> SEMI COMMA LESS GREATER LEQ GEQ
%token <tokenData> COLON EQ MINUS DIV MULT MOD ADDASS ASS
%token <tokenData> OPEN_BRACK CLOSE_BRACK DEC INC PLUS NEQ
%token <tokenData> MIN MAX QUESTION SUBASS MULASS DIVASS


/*types are our nonTerminals. */
/*each new line of non terminals represents a new section in the grammar spec */
%type <treenode> program declList decl 

%type <treenode> varDecl scopedVarDecl varDeclList varDeclInit varDeclId typeSpec

%type <treenode> funDecl params paramList paramTypeList paramIdList paramId

%type <treenode> stmt expStmt compoundStmt localDecls stmtList
%type <treenode> iterRange returnStmt breakStmt

%type <treenode> exp simpleExp andExp unaryRelExp relExp relOp minMaxExp minMaxOp 
%type <treenode> sumExp sumOp mulExp mulOp unaryExp unaryOp factor mutable immutable 
%type <treenode> call args argList constant matched unmatched 
%type <treenode> unmatchedSelectStmt matchedSelectStmt matchedIterStmt unmatchedIterStmt 





%%
/*------------------------START OF GRAMMER-------------------------------*/
/*------------------------1-3-------------------------------*/
program         : declList
                ;

declList        : declList decl
                | decl
                ;

decl            : varDecl
                | funDecl 
                ;  
/*------------------------4-9-------------------------------*/
varDecl         : typeSpec varDeclList SEMI
                ;
                
scopedVarDecl   : STATIC typeSpec varDeclList SEMI
                | typeSpec varDeclList SEMI
                ;

varDeclList     : varDeclList COMMA varDeclInit
                | varDeclInit 
                ;

varDeclInit     : varDeclId
                | varDeclId COLON simpleExp
                ;

varDeclId       : ID
                | ID OPEN_BRACK NUMCONST CLOSE_BRACK
                ;

typeSpec        : INT
                | BOOL
                | CHAR
                ;
/*------------------------10-15-------------------------------*/

funDecl         : typeSpec ID OPEN_PAREN params CLOSE_PAREN stmt
                | ID OPEN_PAREN params CLOSE_PAREN stmt
                ;

params          : paramList
                | /*EMPTY*/
                ;

paramList       : paramList SEMI paramTypeList
                | paramTypeList
                ;

paramTypeList   : typeSpec paramIdList
                ;

paramIdList     : paramIdList COMMA paramId 
                | paramId
                ;

paramId         : ID
                | ID OPEN_BRACK CLOSE_BRACK
                ;
/*------------------------16-25-------------------------------*/
/*
stmt            : expStmt
                | compoundStmt
                | selectStmt
                | iterStmt
                | returnStmt
                | breakStmt
                ;
*/

stmt            : matched
                | unmatched
                ;

matched         : expStmt
                | compoundStmt
                | matchedSelectStmt
                | matchedIterStmt
                | returnStmt
                | breakStmt
                ;

unmatched       : unmatchedSelectStmt
                | unmatchedIterStmt
                ;


expStmt         : exp SEMI
                | SEMI
                ;

compoundStmt    : OPEN_BRACE localDecls stmtList CLOSE_BRACE
                ;

localDecls      : localDecls scopedVarDecl
                | /*EMPTY*/
                ;

stmtList        : stmtList stmt
                | /*EMPTY*/
                ;
/*
selectStmt      : IF simpleExp THEN stmt
                | IF simpleExp THEN stmt ELSE stmt
                ;
*/

matchedSelectStmt   : IF simpleExp THEN matched ELSE matched
                    ;

unmatchedSelectStmt : IF simpleExp THEN matched ELSE unmatched
                    | IF simpleExp THEN stmt
                    ;

unmatchedIterStmt   : WHILE simpleExp DO unmatched
                    | FOR ID ASS iterRange DO unmatched
                    ;

matchedIterStmt     : WHILE simpleExp DO matched
                    | FOR ID ASS iterRange DO matched
                    ;      

/*
iterStmt        : WHILE simpleExp DO stmt
                | FOR ID ASS iterRange DO stmt
                ;
*/
iterRange       : simpleExp TO simpleExp
                | simpleExp TO simpleExp BY simpleExp
                ;

returnStmt      : RETURN SEMI
                | RETURN exp SEMI
                ;

breakStmt       : BREAK SEMI
                ;

/*------------------------26-46-------------------------------*/
exp             : mutable ASS exp
                | mutable ADDASS exp
                | mutable SUBASS exp
                | mutable MULASS exp
                | mutable DIVASS exp
                | mutable INC
                | mutable DEC
                | simpleExp
                ;

simpleExp       : simpleExp OR andExp
                | andExp
                ;

andExp          : andExp AND unaryRelExp
                | unaryRelExp
                ;
                
unaryRelExp     : NOT unaryRelExp
                | relExp
                ;

relExp          : minMaxExp relOp minMaxExp 
                | minMaxExp
                ;

relOp           : LEQ
                | LESS
                | GREATER
                | GEQ
                | EQ
                | NEQ
                ;

minMaxExp       : minMaxExp minMaxOp sumExp
                | sumExp
                ;

minMaxOp        : MAX
                | MIN
                ;

sumExp          : sumExp sumOp mulExp
                | mulExp
                ;

sumOp           : PLUS
                | MINUS
                ;

mulExp          : mulExp mulOp unaryExp
                | unaryExp
                ;

mulOp           : MULT
                | DIV
                | MOD
                ;

unaryExp        : unaryOp unaryExp
                | factor
                ;

unaryOp         : MINUS
                | MULT
                | QUESTION
                ;

factor          : immutable
                | mutable
                ;

mutable         : ID
                | ID OPEN_BRACK exp CLOSE_BRACK
                ;

immutable       : OPEN_PAREN exp CLOSE_PAREN
                | call
                | constant
                ;

call            : ID OPEN_PAREN args CLOSE_PAREN
                ;

args            : argList
                | /*EMPTY*/
                ;

argList         : argList COMMA exp
                | exp
                ;

constant        : NUMCONST
                | CHARCONST
                | STRINGCONST
                | TRUE
                | FALSE
                ;

/*------------------------END OF GRAMMER--------------------------------*/

/* OLD TOKEN TESTING CODE
tokenlist       : tokenlist token
                | token 
                ;

token           : ID            {printf("Line %d Token: ID Value: %s\n",$1->lineNum,$1->tokenStr);}
                | NUMCONST      {printf("Line %d Token: NUMCONST Value: %d  Input: %s\n",   $1->lineNum,
                                                                                            $1->nValue,$1->tokenStr);}
                | CHARCONST     {
                                    if(strlen($1->sValue) > 1)
                                    {
                                        printf("WARNING(%d): character is %d characters long and not a single character: '%s'.  The first char will be used.\n",
                                                                                            $1->lineNum,
                                                                                            (int)strlen($1->sValue),
                                                                                            $1->tokenStr);
                                    }
                                    
                                    printf("Line %d Token: CHARCONST Value: '%c'  Input: %s\n",$1->lineNum,
                                                                                            $1->cValue,$1->tokenStr);
                                                                                            
                                }
                | STRINGCONST   {printf("Line %d Token: STRINGCONST Value: \"%s\"  Len: %d  Input: %s\n",$1->lineNum,
                                                                                            $1->sValue,
                                                                                            ((int)strlen($1->sValue)),
                                                                                            $1->tokenStr);}
                | INT           {printf("Line %d Token: %s\n",$1->lineNum,toUpperString($1->tokenStr));}

                | CHAR          {printf("Line %d Token: %s\n",$1->lineNum,toUpperString($1->tokenStr));}

                | IF            {printf("Line %d Token: %s\n",$1->lineNum,toUpperString($1->tokenStr));} 

                | THEN          {printf("Line %d Token: %s\n",$1->lineNum,toUpperString($1->tokenStr));}   
                
                | ELSE          {printf("Line %d Token: %s\n",$1->lineNum,toUpperString($1->tokenStr));} 
                | WHILE         {printf("Line %d Token: %s\n",$1->lineNum,toUpperString($1->tokenStr));} 
                | DO            {printf("Line %d Token: %s\n",$1->lineNum,toUpperString($1->tokenStr));} 
                | FOR           {printf("Line %d Token: %s\n",$1->lineNum,toUpperString($1->tokenStr));} 
                | TO            {printf("Line %d Token: %s\n",$1->lineNum,toUpperString($1->tokenStr));} 
                | BY            {printf("Line %d Token: %s\n",$1->lineNum,toUpperString($1->tokenStr));} 
                | RETURN        {printf("Line %d Token: %s\n",$1->lineNum,toUpperString($1->tokenStr));} 
                | BREAK         {printf("Line %d Token: %s\n",$1->lineNum,toUpperString($1->tokenStr));} 
                | STATIC        {printf("Line %d Token: %s\n",$1->lineNum,toUpperString($1->tokenStr));} 
                | NOT           {printf("Line %d Token: %s\n",$1->lineNum,toUpperString($1->tokenStr));} 
                | AND           {printf("Line %d Token: %s\n",$1->lineNum,toUpperString($1->tokenStr));} 
                | OR            {printf("Line %d Token: %s\n",$1->lineNum,toUpperString($1->tokenStr));}
                | BOOL          {printf("Line %d Token: %s\n",$1->lineNum,toUpperString($1->tokenStr));}
                | TRUE          {printf("Line %d Token: BOOLCONST Value: %d  Input: %s\n",$1->lineNum,
                                                                                        $1->nValue,
                                                                                        $1->tokenStr);} 
                
                | FALSE         {printf("Line %d Token: BOOLCONST Value: %d  Input: %s\n",$1->lineNum,
                                                                                        $1->nValue,
                                                                                        $1->tokenStr);}

                | OPEN_BRACE    {printf("Line %d Token: %s\n",$1->lineNum,toUpperString($1->tokenStr));}
                | CLOSE_BRACE   {printf("Line %d Token: %s\n",$1->lineNum,toUpperString($1->tokenStr));}
                | OPEN_PAREN    {printf("Line %d Token: %s\n",$1->lineNum,toUpperString($1->tokenStr));}
                | CLOSE_PAREN   {printf("Line %d Token: %s\n",$1->lineNum,toUpperString($1->tokenStr));}
                | COMMA         {printf("Line %d Token: %s\n",$1->lineNum,toUpperString($1->tokenStr));}
                | COLON         {printf("Line %d Token: %s\n",$1->lineNum,toUpperString($1->tokenStr));}                                                                         
                | ASS           {printf("Line %d Token: %s\n",$1->lineNum,toUpperString($1->tokenStr));}
                | MINUS         {printf("Line %d Token: %s\n",$1->lineNum,toUpperString($1->tokenStr));}
                | DIV           {printf("Line %d Token: %s\n",$1->lineNum,toUpperString($1->tokenStr));}
                | MULT          {printf("Line %d Token: %s\n",$1->lineNum,toUpperString($1->tokenStr));}
                | MOD           {printf("Line %d Token: %s\n",$1->lineNum,toUpperString($1->tokenStr));}
                | EQ            {printf("Line %d Token: %s\n",$1->lineNum,"EQ");}
                | OPEN_BRACK    {printf("Line %d Token: %s\n",$1->lineNum,toUpperString($1->tokenStr));}
                | CLOSE_BRACK   {printf("Line %d Token: %s\n",$1->lineNum,toUpperString($1->tokenStr));}
                | LESS          {printf("Line %d Token: %s\n",$1->lineNum,toUpperString($1->tokenStr));}
                | GREATER       {printf("Line %d Token: %s\n",$1->lineNum,toUpperString($1->tokenStr));}
                | ADDASS        {printf("Line %d Token: %s\n",$1->lineNum,"ADDASS");}
                | SUBASS        {printf("Line %d Token: %s\n",$1->lineNum,"SUBASS");}
                | MULASS        {printf("Line %d Token: %s\n",$1->lineNum,"MULASS");}
                | DIVASS        {printf("Line %d Token: %s\n",$1->lineNum,"DIVASS");}
                | DEC           {printf("Line %d Token: %s\n",$1->lineNum,"DEC");}
                | INC           {printf("Line %d Token: %s\n",$1->lineNum,"INC");}
                | NEQ           {printf("Line %d Token: %s\n",$1->lineNum,"NEQ");}
                | PLUS          {printf("Line %d Token: %s\n",$1->lineNum,toUpperString($1->tokenStr));}
                | MIN           {printf("Line %d Token: %s\n",$1->lineNum,"MIN");}
                | MAX           {printf("Line %d Token: %s\n",$1->lineNum,"MAX");}
                | QUESTION      {printf("Line %d Token: %s\n",$1->lineNum,toUpperString($1->tokenStr));}
                | GEQ           {printf("Line %d Token: %s\n",$1->lineNum,"GEQ");}
                | LEQ           {printf("Line %d Token: %s\n",$1->lineNum,"LEQ");}
                | SEMI          {printf("Line %d Token: %s\n",$1->lineNum,toUpperString($1->tokenStr));}
                
                ;
*/
%%
extern int yydebug;
int main(int argc, char *argv[])
{
    char c;
    bool printflag = false;
    bool errorflag = false;
    extern int optind;
    while(1)
    {
        //Picking off the options we want. p
        while((c = ourGetopt(argc,argv,(char*)"pd")) != -1)
        {
            switch(c)
            {
                case 'd':
                    errorflag = true;
                    break;
                case 'p':
                    printflag = true;
                    break;
                default:
                    fprintf(stderr,"Usage: -p(print tree) -d(yydebug enable) are the only supported options\n./c- -[p|d] -[d|p] [FILENAME]\n");
                    exit(-1);
            }
        }

        if(optind < argc)
        {
            printf("file found as %s\nTesting grammar. Nothing is good\n",argv[optind]);

            if ((yyin = fopen(argv[optind], "r"))) {
            // file open successful
            }
            else {
                // failed to open file
                printf("ERROR: failed to open \'%s\'\n", argv[optind]);
                exit(1);
            }
            optind++;
        }
        //no more arguments   
        else
        {
            break;
        }
    }

    // do the parsing
    yyparse();

    return 0;
}
