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
    INT = 262,                     /* INT  */
    BOOL = 263,                    /* BOOL  */
    CHAR = 264,                    /* CHAR  */
    IF = 265,                      /* IF  */
    THEN = 266,                    /* THEN  */
    ELSE = 267,                    /* ELSE  */
    WHILE = 268,                   /* WHILE  */
    DO = 269,                      /* DO  */
    FOR = 270,                     /* FOR  */
    TO = 271,                      /* TO  */
    BY = 272,                      /* BY  */
    RETURN = 273,                  /* RETURN  */
    BREAK = 274,                   /* BREAK  */
    STATIC = 275,                  /* STATIC  */
    NOT = 276,                     /* NOT  */
    AND = 277,                     /* AND  */
    OR = 278,                      /* OR  */
    TRUE = 279,                    /* TRUE  */
    FALSE = 280,                   /* FALSE  */
    OPEN_BRACE = 281,              /* OPEN_BRACE  */
    CLOSE_BRACE = 282,             /* CLOSE_BRACE  */
    OPEN_PAREN = 283,              /* OPEN_PAREN  */
    CLOSE_PAREN = 284,             /* CLOSE_PAREN  */
    SEMI = 285,                    /* SEMI  */
    COMMA = 286,                   /* COMMA  */
    LESS = 287,                    /* LESS  */
    GREATER = 288,                 /* GREATER  */
    LEQ = 289,                     /* LEQ  */
    GEQ = 290,                     /* GEQ  */
    COLON = 291,                   /* COLON  */
    EQ = 292,                      /* EQ  */
    DIV = 293,                     /* DIV  */
    MULT = 294,                    /* MULT  */
    MOD = 295,                     /* MOD  */
    ADDASS = 296,                  /* ADDASS  */
    ASS = 297,                     /* ASS  */
    OPEN_BRACK = 298,              /* OPEN_BRACK  */
    CLOSE_BRACK = 299,             /* CLOSE_BRACK  */
    DEC = 300,                     /* DEC  */
    INC = 301,                     /* INC  */
    PLUS = 302,                    /* PLUS  */
    NEQ = 303,                     /* NEQ  */
    MIN = 304,                     /* MIN  */
    MAX = 305,                     /* MAX  */
    QUESTION = 306,                /* QUESTION  */
    SUBASS = 307,                  /* SUBASS  */
    MULASS = 308,                  /* MULASS  */
    DIVASS = 309,                  /* DIVASS  */
    MINUS = 310,                   /* MINUS  */
    CHSIGN = 311,                  /* CHSIGN  */
    SIZEOF = 312                   /* SIZEOF  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 48 "parser.y"

    ExpType expType;
    TokenData *tokenData;
    TreeNode *treenode;

#line 127 "parser.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_TAB_H_INCLUDED  */
