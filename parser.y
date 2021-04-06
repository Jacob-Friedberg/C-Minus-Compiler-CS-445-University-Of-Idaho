%{
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include "scanType.h"
#include "Tree.h"
#include "ourgetopt.h"
#include "symbolTable.h"
#include "semantic.h"
#include "yyerror.h"




extern int yylex();
extern FILE *yyin;
extern int yydebug;

#define YYERROR_VERBOSE

// void yyerror(const char *msg)
// {
//     printf("ERROR: %s\n", msg);
// }

// static char *toUpperString(char *str)
// {
//     int i = 0;
//     while(str[i])
//     {
//         str[i]=toupper(str[i]);
//         i++;
//     }
//     return str;
// }

TreeNode *syntaxTree;


%}
/*


*/
%define parse.error detailed
// this is included in the tab.h file
// so scanType.h must be included before the tab.h file!!!!
%union {
    ExpType expType;
    TokenData *tokenData;
    TreeNode *treenode;
}

/*tokens are our terminals*/ 
%token <tokenData> ID NUMCONST CHARCONST STRINGCONST 
%token <tokenData> INT BOOL CHAR IF THEN ELSE WHILE DO FOR TO 
%token <tokenData> BY RETURN BREAK STATIC NOT AND OR TRUE FALSE
%token <tokenData> OPEN_BRACE CLOSE_BRACE OPEN_PAREN CLOSE_PAREN
%token <tokenData> SEMI COMMA LESS GREATER LEQ GEQ
%token <tokenData> COLON EQ DIV MULT MOD ADDASS ASS
%token <tokenData> OPEN_BRACK CLOSE_BRACK DEC INC PLUS NEQ
%token <tokenData> MIN MAX QUESTION SUBASS MULASS DIVASS
%token <tokenData> MINUS CHSIGN SIZEOF


/*types are our nonTerminals. */
/*each new line of non terminals represents a new section in the grammar spec */
%type <treenode> program declList decl 

%type <treenode> varDecl scopedVarDecl varDeclList varDeclInit varDeclId

%type <treenode> funDecl params paramList paramTypeList paramIdList paramId

%type <treenode> stmt expStmt compoundStmt localDecls stmtList
%type <treenode> iterRange returnStmt breakStmt

%type <treenode> exp simpleExp andExp unaryRelExp relExp  minMaxExp  
%type <treenode> sumExp  mulExp unaryExp factor mutable immutable 
%type <treenode> call args argList constant matched unmatched 
%type <treenode> unmatchedSelectStmt matchedSelectStmt matchedIterStmt unmatchedIterStmt 

%type <tokenData> unaryOp relOp sumOp mulOp minMaxOp assignop

%type <expType> typeSpec




%%
/*------------------------START OF GRAMMER-------------------------------*/
/*------------------------1-3-------------------------------*/
program         : declList {syntaxTree = $1;}
                | error {$$ = NULL;}
                ;

declList        : declList decl  { //printf("In DeclList Processing\n");
                                   if($2 != NULL) $$ = addSibling($1,$2);else $$=$1;
                                   //printf("OUT OF DECLLIST PROCESSING\n");
                                   }            
                | decl {$$ = $1;}
                | error {$$ = NULL;}
                ;

decl            : varDecl {$$ = $1;}
                | funDecl {$$ = $1;}
                | error {$$ = NULL;}
                ;  
/*------------------------4-9-------------------------------*/
varDecl         : typeSpec varDeclList SEMI { setType($2,$1,false); $$ = $2;}
                | error varDeclList SEMI {$$ = NULL; /*yyerrok;*/}
                | typeSpec error SEMI {$$ = NULL; /*yyerrok;*/ /*yyerrok;*/}
                ;
                /*FIX STATIC LATER*/
scopedVarDecl   : STATIC typeSpec varDeclList SEMI  { setType($3,$2,true);
                                                    $$=$3;
                                                    /*yyerrok;*/
                                                    }
                | typeSpec varDeclList SEMI {   setType($2,$1,false);
                                                $$ = $2;
                                                /*yyerrok;*/
                                            } 
                ;

varDeclList     : varDeclList COMMA varDeclInit   { //printf("In VarDeclList Processing\n");
                                                  if($3 != NULL) $$ = addSibling($1,$3);else $$=$1; /*yyerrok;*/ }
                | varDeclInit { $$ = $1; }
                | varDeclList COMMA error {$$ = NULL;}
                | error {$$ = NULL;}
                ;

varDeclInit     : varDeclId {$$ = $1;}
                | varDeclId COLON simpleExp     {$$ = $1;
                                                 $$->child[0] = $3;}
                | error COLON simpleExp {$$ = NULL; /*yyerrok;*/}
                ;

varDeclId       : ID                                    {$$ = newDeclNode(VarK,UndefinedType,$1);
                                                         $$->attr.name = $1->tokenStr;
                                                         $$->isArray = false;
                                                         $$->attrSet = true;

                                                        }
                | ID OPEN_BRACK NUMCONST CLOSE_BRACK    {$$ = newDeclNode(VarK,UndefinedType,$1);
                                                         $$->attr.name = $1->tokenStr;
                                                         $$->attrSet = true;
                                                         $$->isArray = true;
                                                         $$->arraySize = $3->nValue;
                                                        }
                | ID OPEN_BRACK error {$$ = NULL;}
                | error CLOSE_BRACK {$$ = NULL; /*yyerrok;*/}                                        
                ;

typeSpec        : INT {$$ = Integer;}
                | BOOL {$$ = Boolean;}
                | CHAR {$$ = Char;}
                ;
/*------------------------10-16-------------------------------*/

funDecl         : typeSpec ID OPEN_PAREN params CLOSE_PAREN stmt    {$$ = newDeclNode(FuncK,$1,$2,$4,$6);
                                                                    $$->attr.name = $2->tokenStr;
                                                                    $$->attrSet = true;                                                                      
                                                                     
                                                                    }
                | ID OPEN_PAREN params CLOSE_PAREN stmt             {$$ = newDeclNode(FuncK,Void,$1,$3,$5);
                                                                    $$->attr.name = $1->tokenStr;
                                                                    $$->attrSet = true;                                                                     
                                                                    }
                | typeSpec error {$$ = NULL;} 
                | typeSpec ID OPEN_PAREN error {$$ = NULL;}
                | ID OPEN_PAREN error {$$ = NULL;} 
                | ID OPEN_PAREN params CLOSE_PAREN error {$$ = NULL;}                                                 
                ;

params          : paramList {$$ = $1;}
                |  {$$ = NULL;} /*EMPTY*/
                ;

paramList       : paramList SEMI paramTypeList {//printf("In ParamList Processing\n");
                                                if($3 != NULL) $$ = addSibling($1,$3);
                                                else
                                                  $$ = $1;
                                                }
                | paramTypeList {$$ = $1;}
                | paramList SEMI error {$$ = NULL;}
                | error {$$ = NULL;}
                ;

paramTypeList   : typeSpec paramIdList  {setType($2,$1,false); $$ = $2;}
                | typeSpec error  {$$ = NULL;}
                ;

paramIdList     : paramIdList COMMA paramId { 
                                              if($3 != NULL) $$ = addSibling($1,$3);
                                              else
                                              $$ = $1;
                                              /*yyerrok;*/
                                              }
                | paramId {$$ = $1;}
                | paramId COMMA error {$$ = NULL;}
                | error {$$ = NULL;}
                ;

paramId         : ID                        {$$ = newDeclNode(ParamK,UndefinedType,$1);
                                            $$->attr.name = $1->tokenStr;
                                            $$->attrSet = true;
                                            $$->isArray = false;                                                
                                            }
                | ID OPEN_BRACK CLOSE_BRACK {$$ = newDeclNode(ParamK,UndefinedType,$1);
                                            $$->attr.name = $1->tokenStr;
                                            $$->attrSet = true; 
                                            $$->isArray = true;                                              
                                            }
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

/* DO THESE!!!!!!! TOODOOO*/

stmt            : matched   {$$ = $1;}
                | unmatched {$$ = $1;}
                ;

matched         : expStmt           {$$ = $1;}
                | compoundStmt      {$$ = $1;}
                | matchedSelectStmt {$$ = $1;}
                | matchedIterStmt   {$$ = $1;}
                | returnStmt        {$$ = $1;}
                | breakStmt         {$$ = $1;}
                ;

unmatched       : unmatchedSelectStmt   {$$ = $1;}
                | unmatchedIterStmt     {$$ = $1;}
                ;
/* DO THESE!!!!!!! TOODOOO*/

expStmt         : exp SEMI {$$ = $1;}
                | SEMI {$$ = NULL;}
                | error SEMI {$$ = NULL; yyerrok;}
                ;

compoundStmt    : OPEN_BRACE localDecls stmtList CLOSE_BRACE    { $$ = newStmtNode(CompoundK,$1,$2,$3);
                                                                  $$->attr.string = $1->tokenStr;
                                                                  $$->attrSet = true;
                                                                  yyerrok;
                                                                }
                ;

localDecls      : localDecls scopedVarDecl {//printf("In Local Decls Processing\n");
                                            if($2 != NULL)$$ = addSibling($1,$2);else $$=$1;}
                | {$$ = NULL;}/*EMPTY*/
                ;

stmtList        : stmtList stmt         {//printf("In stmtList Processing\n");
                                        if($2 != NULL)$$ = addSibling($1,$2);else $$=$1; /*yyerrok;*/}
                | {$$ = NULL;} /*EMPTY*/
                ;
/*
selectStmt      : IF simpleExp THEN stmt
                | IF simpleExp THEN stmt ELSE stmt
                ;
*/

/* DO THESE!!!!!!! TOODOOO*/
matchedSelectStmt   : IF simpleExp THEN matched ELSE matched    { $$ = newStmtNode(IfK,$1,$2,$4,$6);
                                                                  $$->attr.string = $1->tokenStr;
                                                                  $$->attrSet = true;
                                                                }
                    ;

unmatchedSelectStmt : IF simpleExp THEN matched ELSE unmatched  { $$ = newStmtNode(IfK,$1,$2,$4,$6);
                                                                  $$->attr.string = $1->tokenStr;
                                                                  $$->attrSet = true;
                                                                }
                    | IF simpleExp THEN stmt                    { $$ = newStmtNode(IfK,$1,$2,$4);
                                                                  $$->attr.string = $1->tokenStr;
                                                                  $$->attrSet = true;
                                                                }
                    ;

unmatchedIterStmt   : WHILE simpleExp DO unmatched              { $$ = newStmtNode(WhileK,$1,$2,$4);
                                                                  $$->attr.string = $1->tokenStr;
                                                                  $$->attrSet = true;
                                                                }
                    | FOR ID ASS iterRange DO unmatched         { 
                                                                  treeNode *node = newDeclNode(VarK,Integer,$2);
                                                                  node->attr.string = $2->tokenStr;
                                                                  node->attrSet = true;

                                                                  $$ = newStmtNode(ForK,$1,node,$4,$6);
                                                                  $$->attr.string = $1->tokenStr;
                                                                  $$->attrSet = true;
                                                                }
                    ;

matchedIterStmt     : WHILE simpleExp DO matched                { $$ = newStmtNode(WhileK,$1,$2,$4);
                                                                  $$->attr.string = $1->tokenStr;
                                                                  $$->attrSet = true;
                                                                }
                                                                
                    | FOR ID ASS iterRange DO matched           { 
                                                                  treeNode *node = newDeclNode(VarK,Integer,$2);
                                                                  node->attr.string = $2->tokenStr;
                                                                  node->attrSet = true;
                        
                                                                  $$ = newStmtNode(ForK,$1,node,$4,$6);
                                                                  $$->attr.string = $1->tokenStr;
                                                                  $$->attrSet = true;
                                                                }
                    ;      
/* DO THESE!!!!!!! TOODOOO*/

/*
iterStmt        : WHILE simpleExp DO stmt
                | FOR ID ASS iterRange DO stmt
                ;
*/
iterRange       : simpleExp TO simpleExp                        { $$ = newStmtNode(RangeK,$2,$1,$3);
                                                                  $$->attr.string = $2->tokenStr;
                                                                  $$->attrSet = true;
                                                                }
                                                                /*PROB WRONG*/
                | simpleExp TO simpleExp BY simpleExp           { $$ = newStmtNode(RangeK,$4,$1,$3,$5);
                                                                  $$->attr.string = $4->tokenStr;
                                                                  $$->attrSet = true;
                                                                }
                | simpleExp TO error { $$ = NULL; }
                | error BY error  { $$ = NULL; /*yyerrok;*/ }
                | simpleExp TO simpleExp BY error { $$ = NULL; }
                ;

returnStmt      : RETURN SEMI                                   { $$ = newStmtNode(ReturnK,$1);
                                                                  $$->attr.string = $1->tokenStr;
                                                                  $$->attrSet = true;
                                                                }
                | RETURN exp SEMI                               { $$ = newStmtNode(ReturnK,$1,$2);
                                                                  $$->attr.string = $1->tokenStr;
                                                                  $$->attrSet = true;
                                                                  /*yyerrok;*/
                                                                }
                | RETURN error { $$ = NULL; /*yyerrok;*/ }
                ;

breakStmt       : BREAK SEMI                                    { $$ = newStmtNode(BreakK,$1);
                                                                  $$->attr.string = $1->tokenStr;
                                                                  $$->attrSet = true;
                                                                  /*yyerrok;*/
                                                                }
                ;

/*------------------------26-46-------------------------------*/
exp             : mutable assignop exp                          { $$ = newExpNode(AssignK,$2,$1,$3);
                                                                  $$->attr.string = $2->tokenStr;
                                                                  $$->attrSet = true;
                                                                }
                | mutable INC                                   { $$ = newExpNode(AssignK,$2,$1);
                                                                  $$->attr.string = $2->tokenStr;
                                                                  $$->attrSet = true;
                                                                }
                | mutable DEC                                   { $$ = newExpNode(AssignK,$2,$1);
                                                                  $$->attr.string = $2->tokenStr;
                                                                  $$->attrSet = true;
                                                                }
                | simpleExp  {$$ = $1;}
                
                | error assignop exp                      { $$ = NULL; /*yyerrok;*/ }
                | mutable assignop error                  { $$ = NULL; }
                | error INC                               { $$=NULL; /*yyerrok;*/ }
                | error DEC                               { $$=NULL; /*yyerrok;*/ }
                ;

assignop        : ASS {$$ = $1;}
                | ADDASS {$$ = $1;}
                | SUBASS {$$ = $1;}
                | MULASS {$$ = $1;}
                | DIVASS {$$ = $1;}
                ;

simpleExp       : simpleExp OR andExp                           { $$ = newExpNode(OpK,$2,$1,$3);
                                                                  $$->attr.string = $2->tokenStr;
                                                                  $$->attrSet = true;
                                                                  
                                                                }
                | andExp   {$$ = $1;}
                | simpleExp OR error                      { $$=NULL; yyerrok;};
                ;

andExp          : andExp AND unaryRelExp                        { $$ = newExpNode(OpK,$2,$1,$3);
                                                                  $$->attr.string = $2->tokenStr;
                                                                  $$->attrSet = true;
                                                                  
                                                                }
                | unaryRelExp   {$$ = $1;}
                | andExp AND error { $$ = NULL; }
                ;
                
unaryRelExp     : NOT unaryRelExp                               { $$ = newExpNode(OpK,$1,$2);
                                                                  $$->attr.string = $1->tokenStr;
                                                                  $$->attrSet = true;
                                                                  
                                                                }
                | relExp {$$ = $1;}
                | NOT error                               { $$ = NULL; }
                ;

relExp          : minMaxExp relOp minMaxExp                     { $$ = newExpNode(OpK,$2,$1,$3);
                                                                  $$->attr.string = $2->tokenStr;
                                                                  $$->attrSet = true;
                                                                  
                                                                }
                | minMaxExp {$$ = $1;}
                | minMaxExp relOp error                   { $$ = NULL; }
                | error relOp minMaxExp                  { $$ = NULL; }
                ;

relOp           : LEQ                   {$$ = $1;}
                | LESS                  {$$ = $1;}
                | GREATER               {$$ = $1;}
                | GEQ                   {$$ = $1;}
                | EQ                    {$$ = $1;}
                | NEQ                   {$$ = $1;}
                ;

minMaxExp       : minMaxExp minMaxOp sumExp                      {$$ = newExpNode(OpK,$2,$1,$3);
                                                                  $$->attr.string = $2->tokenStr;
                                                                  $$->attrSet = true;
                                                                  
                                                                 }
                | sumExp {$$ = $1;}
                | error {$$ = NULL;}
                ;

minMaxOp        : MAX  {$$ = $1;}
                | MIN  {$$ = $1;}
                ;

sumExp          : sumExp sumOp mulExp                            {$$ = newExpNode(OpK,$2,$1,$3);
                                                                  $$->attr.string = $2->tokenStr;
                                                                  $$->attrSet = true;
                                                                  
                                                                 }
                | mulExp   {$$ = $1;}
                | sumExp sumOp error                      { $$ = NULL; }
                ;

sumOp           : PLUS {$$ = $1;}
                | MINUS {$$ = $1;}
                ;

mulExp          : mulExp mulOp unaryExp                         { $$ = newExpNode(OpK,$2,$1,$3);
                                                                  $$->attr.string = $2->tokenStr;
                                                                  $$->attrSet = true;
                                                                  
                                                                }
                | unaryExp {$$ = $1;}
                | mulExp mulOp error                      { $$ = NULL; }
                ;

mulOp           : MULT {$$ = $1;}
                | DIV {$$ = $1;}
                | MOD {$$ = $1;}
                ;

unaryExp        : unaryOp unaryExp                              { $$ = newExpNode(OpK,$1,$2);
                                                                  $$->attr.string = $1->tokenStr;
                                                                  $$->attrSet = true;
                                                                  
                                                                }
                | factor {$$ = $1;}
                | unaryOp error                           { $$ = NULL; }
                ;

unaryOp         : MINUS {$$ = $1; $$->tokenClass = CHSIGN;}
                | MULT  {$$ = $1; $$->tokenClass = SIZEOF;}
                | QUESTION {$$ = $1;}
                ;

factor          : immutable {$$ = $1;}
                | mutable   {$$ = $1;}
                ;

mutable         : ID                                            { $$ = newExpNode(IdK,$1);
                                                                  $$->attr.name = $1->tokenStr;
                                                                  $$->attrSet = true;
                                                                  $$->isArray = false;  
                                                                  
                                                                }
                | ID OPEN_BRACK exp CLOSE_BRACK                 { 
                                                                  TreeNode * node = newExpNode(IdK,$1); 
                                                                  node->attr.name = $1->tokenStr;
                                                                  node->attrSet = true;
                                                                  node->isArray = true;
                                                                  $$ = newExpNode(OpK,$2,node,$3);
                                                                  $$->attr.name = $2->tokenStr;
                                                                  $$->attrSet = true;
                                                                  $$->isArray = true;
                                                                  
                                                                }
                ;

immutable       : OPEN_PAREN exp CLOSE_PAREN  { $$ = $2; yyerrok;} 
                | call  {$$ = $1;}
                | constant {$$ = $1;}
                ;

call            : ID OPEN_PAREN args CLOSE_PAREN    { $$ = newExpNode(CallK,$1,$3);
                                                      $$->attr.name = $1->tokenStr;
                                                      $$->attrSet = true;
                                                    }
                | error OPEN_PAREN                  { $$ = NULL; yyerrok; }                                    
                ;

args            : argList   {$$ = $1;}
                | {$$ = NULL;}/*EMPTY*/
                ;

argList         : argList COMMA exp     {//printf("In ArgList Processing\n");
                                        if($3 != NULL)$$ = addSibling($1,$3); else$$=$1; yyerrok;}
                | exp                   {$$ = $1;}
                | argList ',' error                       { $$=NULL; }
                ;

constant        : NUMCONST      { $$ = newExpNode(ConstantK,$1);
                                  $$->attr.value = $1->nValue;
                                  $$->attrSet = true;
                                  $$->expType = Integer;
                                  $$->unionType = value;
                                }
                | CHARCONST     { $$ = newExpNode(ConstantK,$1);
                                  $$->attr.cvalue = $1->cValue;
                                  $$->attrSet = true;
                                  $$->expType = Char;
                                  $$->unionType = cvalue;
                                }
                | STRINGCONST   { $$ = newExpNode(ConstantK,$1);
                                  $$->attr.string = $1->sValue; /*Shallow Cop*/
                                  $$->attrSet = true;
                                  $$->expType = Char;
                                  $$->isArray = true; 
                                  $$->unionType = string;
                                }
                | TRUE          { $$ = newExpNode(ConstantK,$1);
                                  $$->attr.value = $1->nValue;
                                  $$->attrSet = true;
                                  $$->expType = Boolean; 
                                  $$->unionType = value;
                                }
                | FALSE         { $$ = newExpNode(ConstantK,$1);
                                  $$->attr.value = $1->nValue;
                                  $$->attrSet = true;
                                  $$->expType = Boolean;
                                  $$->unionType = value; 
                                }
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
    extern int NUM_WARNINGS;
    extern int NUM_ERRORS;

    initErrorProcessing();
    while(1)
    {
        //Picking off the options we want. p
        while((c = ourGetopt(argc,argv,(char*)"Ppd")) != -1)
        {
            switch(c)
            {
                case 'd':
                    errorflag = true;
                    break;
                case 'p':
                    printflag = true;
                    break;
                case 'P':
                    printflag = true;
                    break;
                default:
                    fprintf(stderr,"Usage: -p(print tree) -d(yydebug enable) are the only supported options\n./c- -[p|d] -[d|p] [FILENAME]\n");
                    exit(-1);
            }
        }

        if(optind < argc)
        {
            //printf("file found as %s\nTesting grammar. Nothing is good\n",argv[optind]);

            if ((yyin = fopen(argv[optind], "r"))) {
            // file open successful
            }
            else 
            {
                // failed to open file
                printf("ERROR(ARGLIST): source file \"%s\" could not be opened.\n", argv[optind]);
                NUM_ERRORS++;
                printf("Number of warnings: %d\n",NUM_WARNINGS);
                printf("Number of errors: %d\n",NUM_ERRORS);

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
    if(errorflag)
        yydebug = 1;

    // do the parsing
    yyparse();
    SymbolTable *symTab; 
    symTab = new SymbolTable();
    if(printflag && NUM_ERRORS == 0)
    {
      checkTree2(symTab,syntaxTree,false,NULL);
      
      treeNode *tmpLookupNode = (treeNode *) symTab->lookupGlobal(std::string("main"));
      //Child 0 is our params. This means main() child 0 is NULL and main(params a) child 0 is non null
      //We also need to make sure its a function
      if( (tmpLookupNode == NULL || tmpLookupNode->child[0] != NULL) || !tmpLookupNode->isFunc)
      {
        
        printf("ERROR(LINKER): A function named 'main' with no parameters must be defined.\n");
        NUM_ERRORS++;
      }

        if(NUM_ERRORS == 0)
          printTypedTree(syntaxTree,0);

      printf("Number of warnings: %d\n",NUM_WARNINGS);
      printf("Number of errors: %d\n",NUM_ERRORS);

    }
    else
    {
        printf("Number of warnings: %d\n",NUM_WARNINGS);
        printf("Number of errors: %d\n",NUM_ERRORS);
    }

    return 0;
}

