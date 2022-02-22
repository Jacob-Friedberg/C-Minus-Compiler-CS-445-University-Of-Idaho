%{
// this *order* of these includes is mandatory
#include "scanType.h"  // TokenData Type
#include "Tree.h"
#include "parser.tab.h"  // token definitions from the bison
#include <ctype.h>

static int lineNumber = 1;

int line;
char *lastToken;

extern int NUM_ERRORS;    // ERR err count
extern int NUM_WARNINGS;

// //Convert a string with escape sequences from:inPtr to:outPtr
// static void convertEscapeStr2(char *inPtr, char *outPtr)
// {
//     char c;

//     if(*inPtr != '"')
//     {
//         printf("INTERNAL SCANNING ERROR: A non double quoted string was allowed as a token\n");
//         exit(-1);
//     }
    
//     //Skipping over initial quote
//     inPtr++;

//     //while((c = *inPtr++))
//     while(*inPtr != '\0')
//     {   
//         c = *inPtr++;
//         //at the end of a double quoted string
//         if(c == '"')
//         {
//             *outPtr = '\0';
//             return;
//         }

//         if(c != '\\')
//         {
//             *outPtr++ = c;
//             continue;
//         }
//         //processing escape sequences
//         else
//         {
//             //read the character after the escape character
//             c = *inPtr++;
//             if(c == 'n')
//             {
//                 *outPtr++ = '\n';
//             }
//             else if(c == '0')
//             {
//                 *outPtr++ = '\0';
//             }
//             else
//             {
//                 *outPtr++ = c;
//             }
//         }
//     }

//     printf("INTERNAL SCANNING ERROR: inPtr string is not closed by a \"\n");
//     exit(-1);
// }


//Convert a string with escape sequences from:inBuff to:outBuff
static void convertEscapeStr(char *inBuff, char *outBuff)
{
    if(inBuff[0] != '"')
    {
        printf("INTERNAL SCANNING ERROR: A non double quoted string was allowed as a token\n");
        exit(-1);
    }

    int j = 0;
    size_t inBuffLen = strlen(inBuff);
    for(size_t i = 1; i < inBuffLen; i++)
    {
        
        if(inBuff[i] == '"')
        {
            outBuff[j] = '\0';
            return;
        }

        if(inBuff[i] != '\\')
        {
            outBuff[j++] = inBuff[i];
            continue; 
        }

        else
        {
            i++;
            if(inBuff[i] == 'n')
            {
                outBuff[j++] = '\n';
            }
            else if(inBuff[i] == '0')
            {
                outBuff[j++] = '\0';
            }
            else
            {
                outBuff[j++] = inBuff[i];
            }
        }
    }
    
    //Unquoted string, throw errors for all tokens.
    for(size_t i = 0; i < inBuffLen; i++)
    {
        printf("ERROR(%d): Invalid or misplaced input character: '%c'. Character Ignored.\n",
        lineNumber,
        inBuff[i]);
        
         NUM_ERRORS++;
    }
    //printf("INTERNAL SCANNING ERROR: inBuff string is not closed by a \"\n");
    //exit(-1);
}

//Convert a string with escape sequences from:inBuff to:outBuff
static void convertEscapeChar(char *inBuff, char *outBuff)
{
    //printf("INBUFF[%s] of length: %d\n",inBuff,strlen(inBuff));
    if(inBuff[0] != '\'')
    {
        printf("INTERNAL SCANNING ERROR: A non quoted character was allowed as a token\n");
        exit(-1);
    }

    int j = 0;
    size_t i = 0;
    size_t inBuffLen = strlen(inBuff);
    for(i = 1; i < inBuffLen; i++)
    {
        
        if(inBuff[i] == '\'')
        {
            outBuff[j] = '\0';
            //printf("i made it to the return \n");
            return;
        }

        if(inBuff[i] != '\\')
        {
            outBuff[j++] = inBuff[i];
            continue; 
        }

        else
        {
            i++;
            if(inBuff[i] == 'n')
            {
                outBuff[j++] = '\n';
            }
            else if(inBuff[i] == '0')
            {
                outBuff[j++] = '\0';
            }
            else
            {
                outBuff[j++] = inBuff[i];
            }
        }
    }


    printf("INTERNAL SCANNING ERROR: inBuff Character is not closed by a \'\n");
    printf("I[%d] j[%d] outBuff[%s]\n",(int)i,j,outBuff);
    exit(-1);
}

static int setValue(int lineNumber, int tokenClass, char *svalue)
{
    //set the last token to something
    lastToken = svalue;
    line = lineNumber;

    //printf("svalue[%d] Class[%d]: %s\n",lineNumber,tokenClass,svalue);
    // create the pass-back data space
    yylval.tokenData = new TokenData;

    // fill it up
    yylval.tokenData->tokenClass = tokenClass;
    yylval.tokenData->lineNum = lineNumber;
    yylval.tokenData->tokenStr = strdup(svalue);  // duplicating string!!
  
    if (tokenClass == NUMCONST) 
    {

        yylval.tokenData->nValue = atof(svalue); 
    }
    else if (tokenClass == CHARCONST)
    {
        //throw a warning ignoring all characters past the end
        //Subtract 2 from the strlen for the ' 
        if( ((int)strlen(svalue) -2) != 1)
        {
            //throw warning for everything but escape char
            if(svalue[1] != '\\')
            {
                printf("WARNING(%d): character is %d characters long and not a single character: '%s'.  The first char will be used.\n",
                    lineNumber,
                    ((int)strlen(svalue) -2),
                    svalue);

                NUM_WARNINGS++;
            }
        }
        //yylval.tokenData->cValue = svalue[1];
        yylval.tokenData->sValue = strdup(svalue);
        convertEscapeChar(yylval.tokenData->sValue,yylval.tokenData->sValue);
        yylval.tokenData->cValue = yylval.tokenData->sValue[0];
    }
    else if (tokenClass == STRINGCONST)
    {
        yylval.tokenData->sValue = strdup(svalue);
        convertEscapeStr(yylval.tokenData->sValue,yylval.tokenData->sValue);
    }
    else if (tokenClass == TRUE)
    {
        yylval.tokenData->nValue = 1; 
    }
    else if (tokenClass == FALSE)
    {
        yylval.tokenData->nValue = 0; 
    }

    return tokenClass;
}





%}
/* 1/29/21 String Regex   
stringConst \"[^\"]*\"
escapedStringConst \"(\\.|[^\\\"])*\"
charconst '[^']*'
escapedCharConst '(\\.|[^\\'])*'
*/
whitespace [ \t\r\f]

numbers [0-9]
letterDig [a-zA-Z]|[0-9] 
letters [a-zA-Z]
/*charconst2 '[^']*'*/
/*escapedCharConst2 '\\[^']'*/
charconst '[^'\n]*'
escapedCharConst '(\\.|[^\\'\n])*'
stringConst \"[^\"\n]*\"
escapedStringConst \"(\\.|[^\\\"\n])*\"
comment \/\/(.)*
ID [a-zA-Z][a-zA-Z0-9]*
/*keyword int|bool|char|if|then|else|while|do|for|to|by|return|break|static|not|and|or|true|false*/

/*{letters}|{letterDig}*    {return setValue(lineNumber,ID,yytext);} */

%option noyywrap
%option nounput
%%
int                       {return setValue(lineNumber,INT,yytext);}
char                      {return setValue(lineNumber,CHAR,yytext);}
if                        {return setValue(lineNumber,IF,yytext);}
then                      {return setValue(lineNumber,THEN,yytext);}
else                      {return setValue(lineNumber,ELSE,yytext);}  
while                     {return setValue(lineNumber,WHILE,yytext);}
do                        {return setValue(lineNumber,DO,yytext);}
for                       {return setValue(lineNumber,FOR,yytext);}
to                        {return setValue(lineNumber,TO,yytext);}
by                        {return setValue(lineNumber,BY,yytext);}
return                    {return setValue(lineNumber,RETURN,yytext);}
break                     {return setValue(lineNumber,BREAK,yytext);}
static                    {return setValue(lineNumber,STATIC,yytext);}
not                       {return setValue(lineNumber,NOT,yytext);}
and                       {return setValue(lineNumber,AND,yytext);}
or                        {return setValue(lineNumber,OR,yytext);}
bool                      {return setValue(lineNumber,BOOL,yytext);}
true                      {return setValue(lineNumber,TRUE,yytext);}
false                     {return setValue(lineNumber,FALSE,yytext);}

\{                        {return setValue(lineNumber,OPEN_BRACE,yytext);}                          
\}                        {return setValue(lineNumber,CLOSE_BRACE,yytext);}
\(                        {return setValue(lineNumber,OPEN_PAREN,yytext);}
\)                        {return setValue(lineNumber,CLOSE_PAREN,yytext);}
\,                        {return setValue(lineNumber,COMMA,yytext);}
\:                        {return setValue(lineNumber,COLON,yytext);}
\=                        {return setValue(lineNumber,ASS,yytext);}
\-                        {return setValue(lineNumber,MINUS,yytext);}
\/                        {return setValue(lineNumber,DIV,yytext);}
\*                        {return setValue(lineNumber,MULT,yytext);}
\%                        {return setValue(lineNumber,MOD,yytext);}
\+\=                      {return setValue(lineNumber,ADDASS,yytext);}
\-\=                      {return setValue(lineNumber,SUBASS,yytext);}
\*\=                      {return setValue(lineNumber,MULASS,yytext);}
\/\=                      {return setValue(lineNumber,DIVASS,yytext);}
\=\=                      {return setValue(lineNumber,EQ,yytext);}
\[                        {return setValue(lineNumber,OPEN_BRACK,yytext);}
\]                        {return setValue(lineNumber,CLOSE_BRACK,yytext);}
\>                        {return setValue(lineNumber,GREATER,yytext);}
\<                        {return setValue(lineNumber,LESS,yytext);}
\-\-                      {return setValue(lineNumber,DEC,yytext);}
\+\+                      {return setValue(lineNumber,INC,yytext);}
\!\=                      {return setValue(lineNumber,NEQ,yytext);}
\+                        {return setValue(lineNumber,PLUS,yytext);}
\:\<\:                    {return setValue(lineNumber,MIN,yytext);}
\:\>\:                    {return setValue(lineNumber,MAX,yytext);}
\?                        {return setValue(lineNumber,QUESTION,yytext);}
\>\=                      {return setValue(lineNumber,GEQ,yytext);}
\<\=                      {return setValue(lineNumber,LEQ,yytext);}
\;                        {return setValue(lineNumber,SEMI,yytext);}



[\n]                      {lineNumber++;}
{whitespace}+             {;}
{comment}                 {;}
{stringConst}             {return setValue(lineNumber,STRINGCONST,yytext);}
{escapedStringConst}      {return setValue(lineNumber,STRINGCONST,yytext);}
{charconst}               {if(((int)strlen(yytext)-2)!=0) return setValue(lineNumber,CHARCONST,yytext);else printf("ERROR(%d): Empty character ''.  Characters ignored.\n",
                                                                                                                lineNumber);
                                                                                                                NUM_ERRORS++;}
{escapedCharConst}        {return setValue(lineNumber,CHARCONST,yytext);}
{numbers}+                {return setValue(lineNumber,NUMCONST,yytext);}
{ID}                      {return setValue(lineNumber,ID,yytext);}

.                         {printf("ERROR(%d): Invalid or misplaced input character: '%c'. Character Ignored.\n",lineNumber,yytext[0]); NUM_ERRORS++;}

<INITIAL><<EOF>>         {line = lineNumber; return 0;}
%%
