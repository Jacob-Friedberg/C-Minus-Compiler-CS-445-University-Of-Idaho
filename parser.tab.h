/* A Bison parser, made by GNU Bison 3.7.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_PARSER_TAB_H_INCLUDED
# define YY_YY_PARSER_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    ID = 258,                      /* ID  */
    NUMCONST = 259,                /* NUMCONST  */
    CHARCONST = 260,               /* CHARCONST  */
    STRINGCONST = 261,             /* STRINGCONST  */
    BOOLCONST = 262,               /* BOOLCONST  */
    INT = 263,                     /* INT  */
    BOOL = 264,                    /* BOOL  */
    CHAR = 265,                    /* CHAR  */
    IF = 266,                      /* IF  */
    THEN = 267,                    /* THEN  */
    ELSE = 268,                    /* ELSE  */
    WHILE = 269,                   /* WHILE  */
    DO = 270,                      /* DO  */
    FOR = 271,                     /* FOR  */
    TO = 272,                      /* TO  */
    BY = 273,                      /* BY  */
    RETURN = 274,                  /* RETURN  */
    BREAK = 275,                   /* BREAK  */
    STATIC = 276,                  /* STATIC  */
    NOT = 277,                     /* NOT  */
    AND = 278,                     /* AND  */
    OR = 279,                      /* OR  */
    TRUE = 280,                    /* TRUE  */
    FALSE = 281,                   /* FALSE  */
    OPEN_BRACE = 282,              /* OPEN_BRACE  */
    CLOSE_BRACE = 283,             /* CLOSE_BRACE  */
    OPEN_PAREN = 284,              /* OPEN_PAREN  */
    CLOSE_PAREN = 285,             /* CLOSE_PAREN  */
    SEMI = 286,                    /* SEMI  */
    COMMA = 287,                   /* COMMA  */
    LESS = 288,                    /* LESS  */
    GREATER = 289,                 /* GREATER  */
    LEQ = 290,                     /* LEQ  */
    GEQ = 291,                     /* GEQ  */
    COLON = 292,                   /* COLON  */
    EQ = 293,                      /* EQ  */
    DIV = 294,                     /* DIV  */
    MULT = 295,                    /* MULT  */
    MOD = 296,                     /* MOD  */
    ADDASS = 297,                  /* ADDASS  */
    ASS = 298,                     /* ASS  */
    OPEN_BRACK = 299,              /* OPEN_BRACK  */
    CLOSE_BRACK = 300,             /* CLOSE_BRACK  */
    DEC = 301,                     /* DEC  */
    INC = 302,                     /* INC  */
    PLUS = 303,                    /* PLUS  */
    NEQ = 304,                     /* NEQ  */
    MIN = 305,                     /* MIN  */
    MAX = 306,                     /* MAX  */
    QUESTION = 307,                /* QUESTION  */
    SUBASS = 308,                  /* SUBASS  */
    MULASS = 309,                  /* MULASS  */
    DIVASS = 310,                  /* DIVASS  */
    MINUS = 311,                   /* MINUS  */
    CHSIGN = 312,                  /* CHSIGN  */
    SIZEOF = 313                   /* SIZEOF  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 50 "parser.y"

    ExpType expType;
    TokenData *tokenData;
    TreeNode *treenode;

#line 128 "parser.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_TAB_H_INCLUDED  */
