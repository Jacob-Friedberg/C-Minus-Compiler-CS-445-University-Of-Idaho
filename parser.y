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

// this is included in the tab.h file
// so scanType.h must be included before the tab.h file!!!!
%union {
    TokenData *tokenData;
    void *treenode;
}

/*tokens are terminals*/ 
%token <tokenData> ID NUMCONST CHARCONST STRINGCONST 
%token <tokenData> INT BOOL CHAR IF THEN ELSE WHILE DO FOR TO 
%token <tokenData> BY RETURN BREAK STATIC NOT AND OR TRUE FALSE
%token <tokenData> OPEN_BRACE CLOSE_BRACE OPEN_PAREN CLOSE_PAREN
%token <tokenData> SEMI COMMA LESS GREATER LEQ GEQ
%token <tokenData> COLON EQ MINUS DIV MULT PERC ADDASS ASS
%token <tokenData> OPEN_BRACK CLOSE_BRACK DEC INC PLUS NEQ
%token <tokenData> MIN MAX QUESTION

/*types are our nonTerminals. */
%type <treenode> 


%%
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
                | PERC          {printf("Line %d Token: %s\n",$1->lineNum,toUpperString($1->tokenStr));}
                | EQ            {printf("Line %d Token: %s\n",$1->lineNum,"EQ");}
                | OPEN_BRACK    {printf("Line %d Token: %s\n",$1->lineNum,toUpperString($1->tokenStr));}
                | CLOSE_BRACK   {printf("Line %d Token: %s\n",$1->lineNum,toUpperString($1->tokenStr));}
                | LESS          {printf("Line %d Token: %s\n",$1->lineNum,toUpperString($1->tokenStr));}
                | GREATER       {printf("Line %d Token: %s\n",$1->lineNum,toUpperString($1->tokenStr));}
                | ADDASS        {printf("Line %d Token: %s\n",$1->lineNum,"ADDASS");}
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
            printf("file found as %s\n",argv[optind]);

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
