/* A Bison parser, made by GNU Bison 3.7.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.7"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "parser.y"

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

TreeNode *syntaxTree;



#line 113 "parser.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "parser.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_ID = 3,                         /* ID  */
  YYSYMBOL_NUMCONST = 4,                   /* NUMCONST  */
  YYSYMBOL_CHARCONST = 5,                  /* CHARCONST  */
  YYSYMBOL_STRINGCONST = 6,                /* STRINGCONST  */
  YYSYMBOL_INT = 7,                        /* INT  */
  YYSYMBOL_BOOL = 8,                       /* BOOL  */
  YYSYMBOL_CHAR = 9,                       /* CHAR  */
  YYSYMBOL_IF = 10,                        /* IF  */
  YYSYMBOL_THEN = 11,                      /* THEN  */
  YYSYMBOL_ELSE = 12,                      /* ELSE  */
  YYSYMBOL_WHILE = 13,                     /* WHILE  */
  YYSYMBOL_DO = 14,                        /* DO  */
  YYSYMBOL_FOR = 15,                       /* FOR  */
  YYSYMBOL_TO = 16,                        /* TO  */
  YYSYMBOL_BY = 17,                        /* BY  */
  YYSYMBOL_RETURN = 18,                    /* RETURN  */
  YYSYMBOL_BREAK = 19,                     /* BREAK  */
  YYSYMBOL_STATIC = 20,                    /* STATIC  */
  YYSYMBOL_NOT = 21,                       /* NOT  */
  YYSYMBOL_AND = 22,                       /* AND  */
  YYSYMBOL_OR = 23,                        /* OR  */
  YYSYMBOL_TRUE = 24,                      /* TRUE  */
  YYSYMBOL_FALSE = 25,                     /* FALSE  */
  YYSYMBOL_OPEN_BRACE = 26,                /* OPEN_BRACE  */
  YYSYMBOL_CLOSE_BRACE = 27,               /* CLOSE_BRACE  */
  YYSYMBOL_OPEN_PAREN = 28,                /* OPEN_PAREN  */
  YYSYMBOL_CLOSE_PAREN = 29,               /* CLOSE_PAREN  */
  YYSYMBOL_SEMI = 30,                      /* SEMI  */
  YYSYMBOL_COMMA = 31,                     /* COMMA  */
  YYSYMBOL_LESS = 32,                      /* LESS  */
  YYSYMBOL_GREATER = 33,                   /* GREATER  */
  YYSYMBOL_LEQ = 34,                       /* LEQ  */
  YYSYMBOL_GEQ = 35,                       /* GEQ  */
  YYSYMBOL_COLON = 36,                     /* COLON  */
  YYSYMBOL_EQ = 37,                        /* EQ  */
  YYSYMBOL_DIV = 38,                       /* DIV  */
  YYSYMBOL_MULT = 39,                      /* MULT  */
  YYSYMBOL_MOD = 40,                       /* MOD  */
  YYSYMBOL_ADDASS = 41,                    /* ADDASS  */
  YYSYMBOL_ASS = 42,                       /* ASS  */
  YYSYMBOL_OPEN_BRACK = 43,                /* OPEN_BRACK  */
  YYSYMBOL_CLOSE_BRACK = 44,               /* CLOSE_BRACK  */
  YYSYMBOL_DEC = 45,                       /* DEC  */
  YYSYMBOL_INC = 46,                       /* INC  */
  YYSYMBOL_PLUS = 47,                      /* PLUS  */
  YYSYMBOL_NEQ = 48,                       /* NEQ  */
  YYSYMBOL_MIN = 49,                       /* MIN  */
  YYSYMBOL_MAX = 50,                       /* MAX  */
  YYSYMBOL_QUESTION = 51,                  /* QUESTION  */
  YYSYMBOL_SUBASS = 52,                    /* SUBASS  */
  YYSYMBOL_MULASS = 53,                    /* MULASS  */
  YYSYMBOL_DIVASS = 54,                    /* DIVASS  */
  YYSYMBOL_MINUS = 55,                     /* MINUS  */
  YYSYMBOL_CHSIGN = 56,                    /* CHSIGN  */
  YYSYMBOL_SIZEOF = 57,                    /* SIZEOF  */
  YYSYMBOL_YYACCEPT = 58,                  /* $accept  */
  YYSYMBOL_program = 59,                   /* program  */
  YYSYMBOL_declList = 60,                  /* declList  */
  YYSYMBOL_decl = 61,                      /* decl  */
  YYSYMBOL_varDecl = 62,                   /* varDecl  */
  YYSYMBOL_scopedVarDecl = 63,             /* scopedVarDecl  */
  YYSYMBOL_varDeclList = 64,               /* varDeclList  */
  YYSYMBOL_varDeclInit = 65,               /* varDeclInit  */
  YYSYMBOL_varDeclId = 66,                 /* varDeclId  */
  YYSYMBOL_typeSpec = 67,                  /* typeSpec  */
  YYSYMBOL_funDecl = 68,                   /* funDecl  */
  YYSYMBOL_params = 69,                    /* params  */
  YYSYMBOL_paramList = 70,                 /* paramList  */
  YYSYMBOL_paramTypeList = 71,             /* paramTypeList  */
  YYSYMBOL_paramIdList = 72,               /* paramIdList  */
  YYSYMBOL_paramId = 73,                   /* paramId  */
  YYSYMBOL_stmt = 74,                      /* stmt  */
  YYSYMBOL_matched = 75,                   /* matched  */
  YYSYMBOL_unmatched = 76,                 /* unmatched  */
  YYSYMBOL_expStmt = 77,                   /* expStmt  */
  YYSYMBOL_compoundStmt = 78,              /* compoundStmt  */
  YYSYMBOL_localDecls = 79,                /* localDecls  */
  YYSYMBOL_stmtList = 80,                  /* stmtList  */
  YYSYMBOL_matchedSelectStmt = 81,         /* matchedSelectStmt  */
  YYSYMBOL_unmatchedSelectStmt = 82,       /* unmatchedSelectStmt  */
  YYSYMBOL_unmatchedIterStmt = 83,         /* unmatchedIterStmt  */
  YYSYMBOL_matchedIterStmt = 84,           /* matchedIterStmt  */
  YYSYMBOL_iterRange = 85,                 /* iterRange  */
  YYSYMBOL_returnStmt = 86,                /* returnStmt  */
  YYSYMBOL_breakStmt = 87,                 /* breakStmt  */
  YYSYMBOL_exp = 88,                       /* exp  */
  YYSYMBOL_simpleExp = 89,                 /* simpleExp  */
  YYSYMBOL_andExp = 90,                    /* andExp  */
  YYSYMBOL_unaryRelExp = 91,               /* unaryRelExp  */
  YYSYMBOL_relExp = 92,                    /* relExp  */
  YYSYMBOL_relOp = 93,                     /* relOp  */
  YYSYMBOL_minMaxExp = 94,                 /* minMaxExp  */
  YYSYMBOL_minMaxOp = 95,                  /* minMaxOp  */
  YYSYMBOL_sumExp = 96,                    /* sumExp  */
  YYSYMBOL_sumOp = 97,                     /* sumOp  */
  YYSYMBOL_mulExp = 98,                    /* mulExp  */
  YYSYMBOL_mulOp = 99,                     /* mulOp  */
  YYSYMBOL_unaryExp = 100,                 /* unaryExp  */
  YYSYMBOL_unaryOp = 101,                  /* unaryOp  */
  YYSYMBOL_factor = 102,                   /* factor  */
  YYSYMBOL_mutable = 103,                  /* mutable  */
  YYSYMBOL_immutable = 104,                /* immutable  */
  YYSYMBOL_call = 105,                     /* call  */
  YYSYMBOL_args = 106,                     /* args  */
  YYSYMBOL_argList = 107,                  /* argList  */
  YYSYMBOL_constant = 108                  /* constant  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  12
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   237

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  58
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  51
/* YYNRULES -- Number of rules.  */
#define YYNRULES  115
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  180

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   312


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    92,    92,    95,    96,    99,   100,   103,   106,   109,
     116,   117,   120,   121,   125,   131,   139,   140,   141,   145,
     150,   156,   157,   160,   161,   164,   167,   168,   171,   176,
     193,   194,   197,   198,   199,   200,   201,   202,   205,   206,
     210,   211,   214,   220,   221,   224,   225,   233,   239,   243,
     249,   253,   264,   269,   285,   290,   296,   300,   306,   313,
     317,   321,   325,   329,   333,   337,   341,   344,   348,   351,
     355,   358,   362,   365,   369,   372,   373,   374,   375,   376,
     377,   380,   384,   387,   388,   391,   395,   398,   399,   402,
     406,   409,   410,   411,   414,   418,   421,   422,   423,   426,
     427,   430,   435,   447,   448,   449,   452,   458,   459,   462,
     463,   466,   472,   478,   485,   491
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "ID", "NUMCONST",
  "CHARCONST", "STRINGCONST", "INT", "BOOL", "CHAR", "IF", "THEN", "ELSE",
  "WHILE", "DO", "FOR", "TO", "BY", "RETURN", "BREAK", "STATIC", "NOT",
  "AND", "OR", "TRUE", "FALSE", "OPEN_BRACE", "CLOSE_BRACE", "OPEN_PAREN",
  "CLOSE_PAREN", "SEMI", "COMMA", "LESS", "GREATER", "LEQ", "GEQ", "COLON",
  "EQ", "DIV", "MULT", "MOD", "ADDASS", "ASS", "OPEN_BRACK", "CLOSE_BRACK",
  "DEC", "INC", "PLUS", "NEQ", "MIN", "MAX", "QUESTION", "SUBASS",
  "MULASS", "DIVASS", "MINUS", "CHSIGN", "SIZEOF", "$accept", "program",
  "declList", "decl", "varDecl", "scopedVarDecl", "varDeclList",
  "varDeclInit", "varDeclId", "typeSpec", "funDecl", "params", "paramList",
  "paramTypeList", "paramIdList", "paramId", "stmt", "matched",
  "unmatched", "expStmt", "compoundStmt", "localDecls", "stmtList",
  "matchedSelectStmt", "unmatchedSelectStmt", "unmatchedIterStmt",
  "matchedIterStmt", "iterRange", "returnStmt", "breakStmt", "exp",
  "simpleExp", "andExp", "unaryRelExp", "relExp", "relOp", "minMaxExp",
  "minMaxOp", "sumExp", "sumOp", "mulExp", "mulOp", "unaryExp", "unaryOp",
  "factor", "mutable", "immutable", "call", "args", "argList", "constant", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312
};
#endif

#define YYPACT_NINF (-137)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     128,   -17,  -137,  -137,  -137,    45,   128,  -137,  -137,    48,
    -137,    53,  -137,  -137,   -16,    39,  -137,    18,    69,    59,
      44,  -137,    53,    85,  -137,    90,   173,    14,    68,  -137,
     145,    53,    74,    60,    66,  -137,   -15,  -137,  -137,  -137,
     173,  -137,  -137,   173,  -137,  -137,  -137,    87,    89,  -137,
    -137,   -14,   -25,    57,  -137,   182,  -137,  -137,  -137,  -137,
    -137,    70,    69,   173,   173,   121,    43,    95,  -137,  -137,
    -137,  -137,  -137,  -137,  -137,  -137,  -137,  -137,  -137,  -137,
    -137,   103,    87,   163,  -137,   145,  -137,   173,   173,  -137,
     105,   173,   173,  -137,  -137,  -137,  -137,  -137,  -137,  -137,
    -137,   182,   182,  -137,  -137,   182,  -137,  -137,  -137,   182,
    -137,  -137,  -137,    32,     2,    96,  -137,   109,  -137,    93,
    -137,   173,   173,  -137,  -137,   173,   173,   173,  -137,  -137,
     111,   113,    98,  -137,    89,  -137,    28,   -25,    57,  -137,
     145,   145,   173,  -137,    53,  -137,    90,   102,  -137,  -137,
    -137,  -137,  -137,  -137,   173,  -137,  -137,   134,  -137,  -137,
     142,     1,    90,    50,  -137,  -137,  -137,   145,   145,   173,
      54,  -137,  -137,  -137,  -137,  -137,    27,  -137,   173,    87
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,    16,    17,    18,     0,     2,     4,     5,     0,
       6,    22,     1,     3,    14,     0,    11,    12,     0,     0,
      21,    24,    22,     0,     7,     0,     0,    28,    25,    27,
       0,     0,     0,     0,    14,    10,   101,   111,   112,   113,
       0,   114,   115,     0,    97,    98,    96,    13,    68,    70,
      72,    74,    82,    86,    90,     0,    95,   100,    99,   104,
     105,     0,     0,     0,     0,     0,     0,     0,    44,    41,
      20,    30,    31,    32,    33,    34,    38,    39,    35,    36,
      37,     0,    66,   100,    23,     0,    15,   108,     0,    71,
       0,     0,     0,    76,    77,    75,    78,    79,    80,    84,
      83,     0,     0,    87,    88,     0,    92,    91,    93,     0,
      94,    29,    26,     0,     0,     0,    56,     0,    58,    46,
      40,     0,     0,    65,    64,     0,     0,     0,    19,   110,
       0,   107,     0,   103,    67,    69,    73,    81,    85,    89,
       0,     0,     0,    57,     0,    43,     0,     0,    60,    59,
      61,    62,    63,   106,     0,   102,    49,    30,    52,    50,
       0,     0,     0,     0,    42,    45,   109,     0,     0,     0,
       0,     9,    47,    48,    53,    51,    54,     8,     0,    55
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -137,  -137,  -137,   153,  -137,  -137,  -136,   136,  -137,     3,
    -137,   140,  -137,   137,  -137,   110,   -84,  -135,  -126,  -137,
    -137,  -137,  -137,  -137,  -137,  -137,  -137,  -137,  -137,  -137,
     -35,   -24,    76,   -33,  -137,  -137,    64,  -137,    72,  -137,
      75,  -137,   -51,  -137,  -137,   -26,  -137,  -137,  -137,  -137,
    -137
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     5,     6,     7,     8,   145,    15,    16,    17,    18,
      10,    19,    20,    21,    28,    29,    70,    71,    72,    73,
      74,   119,   147,    75,    76,    77,    78,   160,    79,    80,
      81,    82,    48,    49,    50,   101,    51,   102,    52,   105,
      53,   109,    54,    55,    56,    83,    58,    59,   130,   131,
      60
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      57,   128,    47,     9,   110,   157,   158,    89,    90,     9,
     163,    11,    22,    87,    57,   159,   141,   169,    93,    94,
      95,    96,   103,    97,    91,    91,   170,    23,    88,    57,
     104,   117,   172,   174,    98,    99,   100,    57,    57,   113,
     114,   173,   175,   140,   178,    12,    36,    37,    38,    39,
      91,    14,   129,   132,    26,    91,   156,    61,   139,   135,
       2,     3,     4,   165,    40,    57,    57,    41,    42,    24,
      25,    43,    27,   116,    31,    57,    57,    99,   100,    57,
     171,    25,    44,    57,   177,    25,   148,   149,    30,    33,
     150,   151,   152,    34,    45,   106,   107,   108,    46,    62,
       2,     3,     4,    85,    86,    36,    37,    38,    39,    23,
      91,    92,    63,   144,   111,    64,    57,    65,   161,   166,
      66,    67,   146,    40,   115,   118,    41,    42,    68,   164,
      43,     1,    69,   120,   133,     2,     3,     4,   142,   143,
     153,    44,   155,    57,   154,   176,   167,   162,    36,    37,
      38,    39,    57,    45,   179,    63,   168,    46,    64,    13,
      65,    35,    32,    66,    67,   136,    40,   134,    84,    41,
      42,    68,   112,    43,   137,    69,    36,    37,    38,    39,
     138,     0,     0,     0,    44,    36,    37,    38,    39,     0,
       0,     0,     0,     0,    40,     0,    45,    41,    42,     0,
      46,    43,     0,     0,   121,   122,    41,    42,   123,   124,
      43,     0,    44,     0,     0,   125,   126,   127,     0,     0,
       0,    44,     0,     0,    45,     0,     0,     0,    46,     0,
       0,     0,     0,    45,     0,     0,     0,    46
};

static const yytype_int16 yycheck[] =
{
      26,    85,    26,     0,    55,   140,   141,    40,    43,     6,
     146,    28,    28,    28,    40,   141,    14,    16,    32,    33,
      34,    35,    47,    37,    23,    23,   162,    43,    43,    55,
      55,    66,   167,   168,    48,    49,    50,    63,    64,    63,
      64,   167,   168,    11,    17,     0,     3,     4,     5,     6,
      23,     3,    87,    88,    36,    23,   140,    43,   109,    92,
       7,     8,     9,   147,    21,    91,    92,    24,    25,    30,
      31,    28,     3,    30,    30,   101,   102,    49,    50,   105,
      30,    31,    39,   109,    30,    31,   121,   122,    29,     4,
     125,   126,   127,     3,    51,    38,    39,    40,    55,    31,
       7,     8,     9,    29,    44,     3,     4,     5,     6,    43,
      23,    22,    10,    20,    44,    13,   142,    15,   142,   154,
      18,    19,   119,    21,     3,    30,    24,    25,    26,    27,
      28,     3,    30,    30,    29,     7,     8,     9,    42,    30,
      29,    39,    44,   169,    31,   169,    12,   144,     3,     4,
       5,     6,   178,    51,   178,    10,    14,    55,    13,     6,
      15,    25,    22,    18,    19,   101,    21,    91,    31,    24,
      25,    26,    62,    28,   102,    30,     3,     4,     5,     6,
     105,    -1,    -1,    -1,    39,     3,     4,     5,     6,    -1,
      -1,    -1,    -1,    -1,    21,    -1,    51,    24,    25,    -1,
      55,    28,    -1,    -1,    41,    42,    24,    25,    45,    46,
      28,    -1,    39,    -1,    -1,    52,    53,    54,    -1,    -1,
      -1,    39,    -1,    -1,    51,    -1,    -1,    -1,    55,    -1,
      -1,    -1,    -1,    51,    -1,    -1,    -1,    55
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,     7,     8,     9,    59,    60,    61,    62,    67,
      68,    28,     0,    61,     3,    64,    65,    66,    67,    69,
      70,    71,    28,    43,    30,    31,    36,     3,    72,    73,
      29,    30,    69,     4,     3,    65,     3,     4,     5,     6,
      21,    24,    25,    28,    39,    51,    55,    89,    90,    91,
      92,    94,    96,    98,   100,   101,   102,   103,   104,   105,
     108,    43,    31,    10,    13,    15,    18,    19,    26,    30,
      74,    75,    76,    77,    78,    81,    82,    83,    84,    86,
      87,    88,    89,   103,    71,    29,    44,    28,    43,    91,
      88,    23,    22,    32,    33,    34,    35,    37,    48,    49,
      50,    93,    95,    47,    55,    97,    38,    39,    40,    99,
     100,    44,    73,    89,    89,     3,    30,    88,    30,    79,
      30,    41,    42,    45,    46,    52,    53,    54,    74,    88,
     106,   107,    88,    29,    90,    91,    94,    96,    98,   100,
      11,    14,    42,    30,    20,    63,    67,    80,    88,    88,
      88,    88,    88,    29,    31,    44,    74,    75,    75,    76,
      85,    89,    67,    64,    27,    74,    88,    12,    14,    16,
      64,    30,    75,    76,    75,    76,    89,    30,    17,    89
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    58,    59,    60,    60,    61,    61,    62,    63,    63,
      64,    64,    65,    65,    66,    66,    67,    67,    67,    68,
      68,    69,    69,    70,    70,    71,    72,    72,    73,    73,
      74,    74,    75,    75,    75,    75,    75,    75,    76,    76,
      77,    77,    78,    79,    79,    80,    80,    81,    82,    82,
      83,    83,    84,    84,    85,    85,    86,    86,    87,    88,
      88,    88,    88,    88,    88,    88,    88,    89,    89,    90,
      90,    91,    91,    92,    92,    93,    93,    93,    93,    93,
      93,    94,    94,    95,    95,    96,    96,    97,    97,    98,
      98,    99,    99,    99,   100,   100,   101,   101,   101,   102,
     102,   103,   103,   104,   104,   104,   105,   106,   106,   107,
     107,   108,   108,   108,   108,   108
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     1,     1,     1,     3,     4,     3,
       3,     1,     1,     3,     1,     4,     1,     1,     1,     6,
       5,     1,     0,     3,     1,     2,     3,     1,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       2,     1,     4,     2,     0,     2,     0,     6,     6,     4,
       4,     6,     4,     6,     3,     5,     2,     3,     2,     3,
       3,     3,     3,     3,     2,     2,     1,     3,     1,     3,
       1,     2,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     3,     1,     1,     1,     3,     1,     1,     1,     3,
       1,     1,     1,     1,     2,     1,     1,     1,     1,     1,
       1,     1,     4,     3,     1,     1,     4,     1,     0,     3,
       1,     1,     1,     1,     1,     1
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
# ifndef YY_LOCATION_PRINT
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif


# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yykind < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yykind], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* program: declList  */
#line 92 "parser.y"
                           {syntaxTree = (yyvsp[0].treenode);}
#line 1355 "parser.tab.c"
    break;

  case 3: /* declList: declList decl  */
#line 95 "parser.y"
                                 {(yyval.treenode) = addSibling((yyvsp[-1].treenode),(yyvsp[0].treenode));}
#line 1361 "parser.tab.c"
    break;

  case 4: /* declList: decl  */
#line 96 "parser.y"
                       {(yyval.treenode) = (yyvsp[0].treenode);}
#line 1367 "parser.tab.c"
    break;

  case 5: /* decl: varDecl  */
#line 99 "parser.y"
                          {(yyval.treenode) = (yyvsp[0].treenode);}
#line 1373 "parser.tab.c"
    break;

  case 6: /* decl: funDecl  */
#line 100 "parser.y"
                          {(yyval.treenode) = (yyvsp[0].treenode);}
#line 1379 "parser.tab.c"
    break;

  case 7: /* varDecl: typeSpec varDeclList SEMI  */
#line 103 "parser.y"
                                            { setType((yyvsp[-1].treenode),(yyvsp[-2].expType),false); (yyval.treenode) = (yyvsp[-1].treenode);}
#line 1385 "parser.tab.c"
    break;

  case 8: /* scopedVarDecl: STATIC typeSpec varDeclList SEMI  */
#line 106 "parser.y"
                                                    { setType((yyvsp[-1].treenode),(yyvsp[-2].expType),true);
                                                    (yyval.treenode)=(yyvsp[-1].treenode);
                                                    }
#line 1393 "parser.tab.c"
    break;

  case 9: /* scopedVarDecl: typeSpec varDeclList SEMI  */
#line 109 "parser.y"
                                            {   setType((yyvsp[-1].treenode),(yyvsp[-2].expType),false);
                                                (yyval.treenode) = (yyvsp[-1].treenode);
                                            }
#line 1401 "parser.tab.c"
    break;

  case 10: /* varDeclList: varDeclList COMMA varDeclInit  */
#line 116 "parser.y"
                                                  { (yyval.treenode) = addSibling((yyvsp[-2].treenode),(yyvsp[0].treenode)); }
#line 1407 "parser.tab.c"
    break;

  case 11: /* varDeclList: varDeclInit  */
#line 117 "parser.y"
                              { (yyval.treenode) = (yyvsp[0].treenode); }
#line 1413 "parser.tab.c"
    break;

  case 12: /* varDeclInit: varDeclId  */
#line 120 "parser.y"
                            {(yyval.treenode) = (yyvsp[0].treenode);}
#line 1419 "parser.tab.c"
    break;

  case 13: /* varDeclInit: varDeclId COLON simpleExp  */
#line 121 "parser.y"
                                                {(yyval.treenode) = (yyvsp[-2].treenode);
                                                 (yyval.treenode)->child[0] = (yyvsp[0].treenode);}
#line 1426 "parser.tab.c"
    break;

  case 14: /* varDeclId: ID  */
#line 125 "parser.y"
                                                        {(yyval.treenode) = newDeclNode(VarK,UndefinedType,(yyvsp[0].tokenData));
                                                         (yyval.treenode)->attr.name = (yyvsp[0].tokenData)->tokenStr;
                                                         (yyval.treenode)->isArray = false;
                                                         (yyval.treenode)->attrSet = true;

                                                        }
#line 1437 "parser.tab.c"
    break;

  case 15: /* varDeclId: ID OPEN_BRACK NUMCONST CLOSE_BRACK  */
#line 131 "parser.y"
                                                        {(yyval.treenode) = newDeclNode(VarK,UndefinedType,(yyvsp[-3].tokenData));
                                                         (yyval.treenode)->attr.name = (yyvsp[-3].tokenData)->tokenStr;
                                                         (yyval.treenode)->attrSet = true;
                                                         (yyval.treenode)->isArray = true;
                                                         (yyval.treenode)->arraySize = (yyvsp[-1].tokenData)->nValue;
                                                        }
#line 1448 "parser.tab.c"
    break;

  case 16: /* typeSpec: INT  */
#line 139 "parser.y"
                      {(yyval.expType) = Integer;}
#line 1454 "parser.tab.c"
    break;

  case 17: /* typeSpec: BOOL  */
#line 140 "parser.y"
                       {(yyval.expType) = Boolean;}
#line 1460 "parser.tab.c"
    break;

  case 18: /* typeSpec: CHAR  */
#line 141 "parser.y"
                       {(yyval.expType) = Char;}
#line 1466 "parser.tab.c"
    break;

  case 19: /* funDecl: typeSpec ID OPEN_PAREN params CLOSE_PAREN stmt  */
#line 145 "parser.y"
                                                                    {(yyval.treenode) = newDeclNode(FuncK,(yyvsp[-5].expType),(yyvsp[-4].tokenData),(yyvsp[-2].treenode),(yyvsp[0].treenode));
                                                                    (yyval.treenode)->attr.name = (yyvsp[-4].tokenData)->tokenStr;
                                                                    (yyval.treenode)->attrSet = true;                                                                      
                                                                     
                                                                    }
#line 1476 "parser.tab.c"
    break;

  case 20: /* funDecl: ID OPEN_PAREN params CLOSE_PAREN stmt  */
#line 150 "parser.y"
                                                                    {(yyval.treenode) = newDeclNode(FuncK,Void,(yyvsp[-4].tokenData),(yyvsp[-2].treenode),(yyvsp[0].treenode));
                                                                    (yyval.treenode)->attr.name = (yyvsp[-4].tokenData)->tokenStr;
                                                                    (yyval.treenode)->attrSet = true;                                                                     
                                                                    }
#line 1485 "parser.tab.c"
    break;

  case 21: /* params: paramList  */
#line 156 "parser.y"
                            {(yyval.treenode) = (yyvsp[0].treenode);}
#line 1491 "parser.tab.c"
    break;

  case 22: /* params: %empty  */
#line 157 "parser.y"
                   {(yyval.treenode) = NULL;}
#line 1497 "parser.tab.c"
    break;

  case 23: /* paramList: paramList SEMI paramTypeList  */
#line 160 "parser.y"
                                               {(yyval.treenode) = addSibling((yyvsp[-2].treenode),(yyvsp[0].treenode));}
#line 1503 "parser.tab.c"
    break;

  case 24: /* paramList: paramTypeList  */
#line 161 "parser.y"
                                {(yyval.treenode) = (yyvsp[0].treenode);}
#line 1509 "parser.tab.c"
    break;

  case 25: /* paramTypeList: typeSpec paramIdList  */
#line 164 "parser.y"
                                        {setType((yyvsp[0].treenode),(yyvsp[-1].expType),false); (yyval.treenode) = (yyvsp[0].treenode);}
#line 1515 "parser.tab.c"
    break;

  case 26: /* paramIdList: paramIdList COMMA paramId  */
#line 167 "parser.y"
                                            {(yyval.treenode) = addSibling((yyvsp[-2].treenode),(yyvsp[0].treenode));}
#line 1521 "parser.tab.c"
    break;

  case 27: /* paramIdList: paramId  */
#line 168 "parser.y"
                          {(yyval.treenode) = (yyvsp[0].treenode);}
#line 1527 "parser.tab.c"
    break;

  case 28: /* paramId: ID  */
#line 171 "parser.y"
                                            {(yyval.treenode) = newDeclNode(ParamK,UndefinedType,(yyvsp[0].tokenData));
                                            (yyval.treenode)->attr.name = (yyvsp[0].tokenData)->tokenStr;
                                            (yyval.treenode)->attrSet = true;
                                            (yyval.treenode)->isArray = false;                                                
                                            }
#line 1537 "parser.tab.c"
    break;

  case 29: /* paramId: ID OPEN_BRACK CLOSE_BRACK  */
#line 176 "parser.y"
                                            {(yyval.treenode) = newDeclNode(ParamK,UndefinedType,(yyvsp[-2].tokenData));
                                            (yyval.treenode)->attr.name = (yyvsp[-2].tokenData)->tokenStr;
                                            (yyval.treenode)->attrSet = true; 
                                            (yyval.treenode)->isArray = true;                                              
                                            }
#line 1547 "parser.tab.c"
    break;

  case 30: /* stmt: matched  */
#line 193 "parser.y"
                            {(yyval.treenode) = (yyvsp[0].treenode);}
#line 1553 "parser.tab.c"
    break;

  case 31: /* stmt: unmatched  */
#line 194 "parser.y"
                            {(yyval.treenode) = (yyvsp[0].treenode);}
#line 1559 "parser.tab.c"
    break;

  case 32: /* matched: expStmt  */
#line 197 "parser.y"
                                    {(yyval.treenode) = (yyvsp[0].treenode);}
#line 1565 "parser.tab.c"
    break;

  case 33: /* matched: compoundStmt  */
#line 198 "parser.y"
                                    {(yyval.treenode) = (yyvsp[0].treenode);}
#line 1571 "parser.tab.c"
    break;

  case 34: /* matched: matchedSelectStmt  */
#line 199 "parser.y"
                                    {(yyval.treenode) = (yyvsp[0].treenode);}
#line 1577 "parser.tab.c"
    break;

  case 35: /* matched: matchedIterStmt  */
#line 200 "parser.y"
                                    {(yyval.treenode) = (yyvsp[0].treenode);}
#line 1583 "parser.tab.c"
    break;

  case 36: /* matched: returnStmt  */
#line 201 "parser.y"
                                    {(yyval.treenode) = (yyvsp[0].treenode);}
#line 1589 "parser.tab.c"
    break;

  case 37: /* matched: breakStmt  */
#line 202 "parser.y"
                                    {(yyval.treenode) = (yyvsp[0].treenode);}
#line 1595 "parser.tab.c"
    break;

  case 38: /* unmatched: unmatchedSelectStmt  */
#line 205 "parser.y"
                                        {(yyval.treenode) = (yyvsp[0].treenode);}
#line 1601 "parser.tab.c"
    break;

  case 39: /* unmatched: unmatchedIterStmt  */
#line 206 "parser.y"
                                        {(yyval.treenode) = (yyvsp[0].treenode);}
#line 1607 "parser.tab.c"
    break;

  case 40: /* expStmt: exp SEMI  */
#line 210 "parser.y"
                           {(yyval.treenode) = (yyvsp[-1].treenode);}
#line 1613 "parser.tab.c"
    break;

  case 41: /* expStmt: SEMI  */
#line 211 "parser.y"
                       {(yyval.treenode) = NULL;}
#line 1619 "parser.tab.c"
    break;

  case 42: /* compoundStmt: OPEN_BRACE localDecls stmtList CLOSE_BRACE  */
#line 214 "parser.y"
                                                                { (yyval.treenode) = newStmtNode(CompoundK,(yyvsp[-3].tokenData),(yyvsp[-2].treenode),(yyvsp[-1].treenode));
                                                                  (yyval.treenode)->attr.string = (yyvsp[-3].tokenData)->tokenStr;
                                                                  (yyval.treenode)->attrSet = true;
                                                                }
#line 1628 "parser.tab.c"
    break;

  case 43: /* localDecls: localDecls scopedVarDecl  */
#line 220 "parser.y"
                                           {(yyval.treenode) = addSibling((yyvsp[-1].treenode),(yyvsp[0].treenode));}
#line 1634 "parser.tab.c"
    break;

  case 44: /* localDecls: %empty  */
#line 221 "parser.y"
                  {(yyval.treenode) = NULL;}
#line 1640 "parser.tab.c"
    break;

  case 45: /* stmtList: stmtList stmt  */
#line 224 "parser.y"
                                        {(yyval.treenode) = addSibling((yyvsp[-1].treenode),(yyvsp[0].treenode));}
#line 1646 "parser.tab.c"
    break;

  case 46: /* stmtList: %empty  */
#line 225 "parser.y"
                  {(yyval.treenode) = NULL;}
#line 1652 "parser.tab.c"
    break;

  case 47: /* matchedSelectStmt: IF simpleExp THEN matched ELSE matched  */
#line 233 "parser.y"
                                                                { (yyval.treenode) = newStmtNode(IfK,(yyvsp[-5].tokenData),(yyvsp[-4].treenode),(yyvsp[-2].treenode),(yyvsp[0].treenode));
                                                                  (yyval.treenode)->attr.string = (yyvsp[-5].tokenData)->tokenStr;
                                                                  (yyval.treenode)->attrSet = true;
                                                                }
#line 1661 "parser.tab.c"
    break;

  case 48: /* unmatchedSelectStmt: IF simpleExp THEN matched ELSE unmatched  */
#line 239 "parser.y"
                                                                { (yyval.treenode) = newStmtNode(IfK,(yyvsp[-5].tokenData),(yyvsp[-4].treenode),(yyvsp[-2].treenode),(yyvsp[0].treenode));
                                                                  (yyval.treenode)->attr.string = (yyvsp[-5].tokenData)->tokenStr;
                                                                  (yyval.treenode)->attrSet = true;
                                                                }
#line 1670 "parser.tab.c"
    break;

  case 49: /* unmatchedSelectStmt: IF simpleExp THEN stmt  */
#line 243 "parser.y"
                                                                { (yyval.treenode) = newStmtNode(IfK,(yyvsp[-3].tokenData),(yyvsp[-2].treenode),(yyvsp[0].treenode));
                                                                  (yyval.treenode)->attr.string = (yyvsp[-3].tokenData)->tokenStr;
                                                                  (yyval.treenode)->attrSet = true;
                                                                }
#line 1679 "parser.tab.c"
    break;

  case 50: /* unmatchedIterStmt: WHILE simpleExp DO unmatched  */
#line 249 "parser.y"
                                                                { (yyval.treenode) = newStmtNode(WhileK,(yyvsp[-3].tokenData),(yyvsp[-2].treenode),(yyvsp[0].treenode));
                                                                  (yyval.treenode)->attr.string = (yyvsp[-3].tokenData)->tokenStr;
                                                                  (yyval.treenode)->attrSet = true;
                                                                }
#line 1688 "parser.tab.c"
    break;

  case 51: /* unmatchedIterStmt: FOR ID ASS iterRange DO unmatched  */
#line 253 "parser.y"
                                                                { 
                                                                  treeNode *node = newDeclNode(VarK,Integer,(yyvsp[-4].tokenData));
                                                                  node->attr.string = (yyvsp[-4].tokenData)->tokenStr;
                                                                  node->attrSet = true;

                                                                  (yyval.treenode) = newStmtNode(ForK,(yyvsp[-5].tokenData),node,(yyvsp[-2].treenode),(yyvsp[0].treenode));
                                                                  (yyval.treenode)->attr.string = (yyvsp[-5].tokenData)->tokenStr;
                                                                  (yyval.treenode)->attrSet = true;
                                                                }
#line 1702 "parser.tab.c"
    break;

  case 52: /* matchedIterStmt: WHILE simpleExp DO matched  */
#line 264 "parser.y"
                                                                { (yyval.treenode) = newStmtNode(WhileK,(yyvsp[-3].tokenData),(yyvsp[-2].treenode),(yyvsp[0].treenode));
                                                                  (yyval.treenode)->attr.string = (yyvsp[-3].tokenData)->tokenStr;
                                                                  (yyval.treenode)->attrSet = true;
                                                                }
#line 1711 "parser.tab.c"
    break;

  case 53: /* matchedIterStmt: FOR ID ASS iterRange DO matched  */
#line 269 "parser.y"
                                                                { 
                                                                  treeNode *node = newDeclNode(VarK,Integer,(yyvsp[-4].tokenData));
                                                                  node->attr.string = (yyvsp[-4].tokenData)->tokenStr;
                                                                  node->attrSet = true;
                        
                                                                  (yyval.treenode) = newStmtNode(ForK,(yyvsp[-5].tokenData),node,(yyvsp[-2].treenode),(yyvsp[0].treenode));
                                                                  (yyval.treenode)->attr.string = (yyvsp[-5].tokenData)->tokenStr;
                                                                  (yyval.treenode)->attrSet = true;
                                                                }
#line 1725 "parser.tab.c"
    break;

  case 54: /* iterRange: simpleExp TO simpleExp  */
#line 285 "parser.y"
                                                                { (yyval.treenode) = newStmtNode(RangeK,(yyvsp[-1].tokenData),(yyvsp[-2].treenode),(yyvsp[0].treenode));
                                                                  (yyval.treenode)->attr.string = (yyvsp[-1].tokenData)->tokenStr;
                                                                  (yyval.treenode)->attrSet = true;
                                                                }
#line 1734 "parser.tab.c"
    break;

  case 55: /* iterRange: simpleExp TO simpleExp BY simpleExp  */
#line 290 "parser.y"
                                                                { (yyval.treenode) = newStmtNode(RangeK,(yyvsp[-1].tokenData),(yyvsp[-4].treenode),(yyvsp[-2].treenode),(yyvsp[0].treenode));
                                                                  (yyval.treenode)->attr.string = (yyvsp[-1].tokenData)->tokenStr;
                                                                  (yyval.treenode)->attrSet = true;
                                                                }
#line 1743 "parser.tab.c"
    break;

  case 56: /* returnStmt: RETURN SEMI  */
#line 296 "parser.y"
                                                                { (yyval.treenode) = newStmtNode(ReturnK,(yyvsp[-1].tokenData));
                                                                  (yyval.treenode)->attr.string = (yyvsp[-1].tokenData)->tokenStr;
                                                                  (yyval.treenode)->attrSet = true;
                                                                }
#line 1752 "parser.tab.c"
    break;

  case 57: /* returnStmt: RETURN exp SEMI  */
#line 300 "parser.y"
                                                                { (yyval.treenode) = newStmtNode(ReturnK,(yyvsp[-2].tokenData),(yyvsp[-1].treenode));
                                                                  (yyval.treenode)->attr.string = (yyvsp[-2].tokenData)->tokenStr;
                                                                  (yyval.treenode)->attrSet = true;
                                                                }
#line 1761 "parser.tab.c"
    break;

  case 58: /* breakStmt: BREAK SEMI  */
#line 306 "parser.y"
                                                                { (yyval.treenode) = newStmtNode(BreakK,(yyvsp[-1].tokenData));
                                                                  (yyval.treenode)->attr.string = (yyvsp[-1].tokenData)->tokenStr;
                                                                  (yyval.treenode)->attrSet = true;
                                                                }
#line 1770 "parser.tab.c"
    break;

  case 59: /* exp: mutable ASS exp  */
#line 313 "parser.y"
                                                                { (yyval.treenode) = newExpNode(AssignK,(yyvsp[-1].tokenData),(yyvsp[-2].treenode),(yyvsp[0].treenode));
                                                                  (yyval.treenode)->attr.string = (yyvsp[-1].tokenData)->tokenStr;
                                                                  (yyval.treenode)->attrSet = true;
                                                                }
#line 1779 "parser.tab.c"
    break;

  case 60: /* exp: mutable ADDASS exp  */
#line 317 "parser.y"
                                                                { (yyval.treenode) = newExpNode(AssignK,(yyvsp[-1].tokenData),(yyvsp[-2].treenode),(yyvsp[0].treenode));
                                                                  (yyval.treenode)->attr.string = (yyvsp[-1].tokenData)->tokenStr;
                                                                  (yyval.treenode)->attrSet = true;
                                                                }
#line 1788 "parser.tab.c"
    break;

  case 61: /* exp: mutable SUBASS exp  */
#line 321 "parser.y"
                                                                { (yyval.treenode) = newExpNode(AssignK,(yyvsp[-1].tokenData),(yyvsp[-2].treenode),(yyvsp[0].treenode));
                                                                  (yyval.treenode)->attr.string = (yyvsp[-1].tokenData)->tokenStr;
                                                                  (yyval.treenode)->attrSet = true;
                                                                }
#line 1797 "parser.tab.c"
    break;

  case 62: /* exp: mutable MULASS exp  */
#line 325 "parser.y"
                                                                { (yyval.treenode) = newExpNode(AssignK,(yyvsp[-1].tokenData),(yyvsp[-2].treenode),(yyvsp[0].treenode));
                                                                  (yyval.treenode)->attr.string = (yyvsp[-1].tokenData)->tokenStr;
                                                                  (yyval.treenode)->attrSet = true;
                                                                }
#line 1806 "parser.tab.c"
    break;

  case 63: /* exp: mutable DIVASS exp  */
#line 329 "parser.y"
                                                                { (yyval.treenode) = newExpNode(AssignK,(yyvsp[-1].tokenData),(yyvsp[-2].treenode),(yyvsp[0].treenode));
                                                                  (yyval.treenode)->attr.string = (yyvsp[-1].tokenData)->tokenStr;
                                                                  (yyval.treenode)->attrSet = true;
                                                                }
#line 1815 "parser.tab.c"
    break;

  case 64: /* exp: mutable INC  */
#line 333 "parser.y"
                                                                { (yyval.treenode) = newExpNode(AssignK,(yyvsp[0].tokenData),(yyvsp[-1].treenode));
                                                                  (yyval.treenode)->attr.string = (yyvsp[0].tokenData)->tokenStr;
                                                                  (yyval.treenode)->attrSet = true;
                                                                }
#line 1824 "parser.tab.c"
    break;

  case 65: /* exp: mutable DEC  */
#line 337 "parser.y"
                                                                { (yyval.treenode) = newExpNode(AssignK,(yyvsp[0].tokenData),(yyvsp[-1].treenode));
                                                                  (yyval.treenode)->attr.string = (yyvsp[0].tokenData)->tokenStr;
                                                                  (yyval.treenode)->attrSet = true;
                                                                }
#line 1833 "parser.tab.c"
    break;

  case 66: /* exp: simpleExp  */
#line 341 "parser.y"
                             {(yyval.treenode) = (yyvsp[0].treenode);}
#line 1839 "parser.tab.c"
    break;

  case 67: /* simpleExp: simpleExp OR andExp  */
#line 344 "parser.y"
                                                                { (yyval.treenode) = newExpNode(OpK,(yyvsp[-1].tokenData),(yyvsp[-2].treenode),(yyvsp[0].treenode));
                                                                  (yyval.treenode)->attr.string = (yyvsp[-1].tokenData)->tokenStr;
                                                                  (yyval.treenode)->attrSet = true;
                                                                }
#line 1848 "parser.tab.c"
    break;

  case 68: /* simpleExp: andExp  */
#line 348 "parser.y"
                           {(yyval.treenode) = (yyvsp[0].treenode);}
#line 1854 "parser.tab.c"
    break;

  case 69: /* andExp: andExp AND unaryRelExp  */
#line 351 "parser.y"
                                                                { (yyval.treenode) = newExpNode(OpK,(yyvsp[-1].tokenData),(yyvsp[-2].treenode),(yyvsp[0].treenode));
                                                                  (yyval.treenode)->attr.string = (yyvsp[-1].tokenData)->tokenStr;
                                                                  (yyval.treenode)->attrSet = true;
                                                                }
#line 1863 "parser.tab.c"
    break;

  case 70: /* andExp: unaryRelExp  */
#line 355 "parser.y"
                                {(yyval.treenode) = (yyvsp[0].treenode);}
#line 1869 "parser.tab.c"
    break;

  case 71: /* unaryRelExp: NOT unaryRelExp  */
#line 358 "parser.y"
                                                                { (yyval.treenode) = newExpNode(OpK,(yyvsp[-1].tokenData),(yyvsp[0].treenode));
                                                                  (yyval.treenode)->attr.string = (yyvsp[-1].tokenData)->tokenStr;
                                                                  (yyval.treenode)->attrSet = true;
                                                                }
#line 1878 "parser.tab.c"
    break;

  case 72: /* unaryRelExp: relExp  */
#line 362 "parser.y"
                         {(yyval.treenode) = (yyvsp[0].treenode);}
#line 1884 "parser.tab.c"
    break;

  case 73: /* relExp: minMaxExp relOp minMaxExp  */
#line 365 "parser.y"
                                                                { (yyval.treenode) = newExpNode(OpK,(yyvsp[-1].tokenData),(yyvsp[-2].treenode),(yyvsp[0].treenode));
                                                                  (yyval.treenode)->attr.string = (yyvsp[-1].tokenData)->tokenStr;
                                                                  (yyval.treenode)->attrSet = true;
                                                                }
#line 1893 "parser.tab.c"
    break;

  case 74: /* relExp: minMaxExp  */
#line 369 "parser.y"
                            {(yyval.treenode) = (yyvsp[0].treenode);}
#line 1899 "parser.tab.c"
    break;

  case 75: /* relOp: LEQ  */
#line 372 "parser.y"
                                        {(yyval.tokenData) = (yyvsp[0].tokenData);}
#line 1905 "parser.tab.c"
    break;

  case 76: /* relOp: LESS  */
#line 373 "parser.y"
                                        {(yyval.tokenData) = (yyvsp[0].tokenData);}
#line 1911 "parser.tab.c"
    break;

  case 77: /* relOp: GREATER  */
#line 374 "parser.y"
                                        {(yyval.tokenData) = (yyvsp[0].tokenData);}
#line 1917 "parser.tab.c"
    break;

  case 78: /* relOp: GEQ  */
#line 375 "parser.y"
                                        {(yyval.tokenData) = (yyvsp[0].tokenData);}
#line 1923 "parser.tab.c"
    break;

  case 79: /* relOp: EQ  */
#line 376 "parser.y"
                                        {(yyval.tokenData) = (yyvsp[0].tokenData);}
#line 1929 "parser.tab.c"
    break;

  case 80: /* relOp: NEQ  */
#line 377 "parser.y"
                                        {(yyval.tokenData) = (yyvsp[0].tokenData);}
#line 1935 "parser.tab.c"
    break;

  case 81: /* minMaxExp: minMaxExp minMaxOp sumExp  */
#line 380 "parser.y"
                                                                 {(yyval.treenode) = newExpNode(OpK,(yyvsp[-1].tokenData),(yyvsp[-2].treenode),(yyvsp[0].treenode));
                                                                  (yyval.treenode)->attr.string = (yyvsp[-1].tokenData)->tokenStr;
                                                                  (yyval.treenode)->attrSet = true;
                                                                 }
#line 1944 "parser.tab.c"
    break;

  case 82: /* minMaxExp: sumExp  */
#line 384 "parser.y"
                         {(yyval.treenode) = (yyvsp[0].treenode);}
#line 1950 "parser.tab.c"
    break;

  case 83: /* minMaxOp: MAX  */
#line 387 "parser.y"
                       {(yyval.tokenData) = (yyvsp[0].tokenData);}
#line 1956 "parser.tab.c"
    break;

  case 84: /* minMaxOp: MIN  */
#line 388 "parser.y"
                       {(yyval.tokenData) = (yyvsp[0].tokenData);}
#line 1962 "parser.tab.c"
    break;

  case 85: /* sumExp: sumExp sumOp mulExp  */
#line 391 "parser.y"
                                                                 {(yyval.treenode) = newExpNode(OpK,(yyvsp[-1].tokenData),(yyvsp[-2].treenode),(yyvsp[0].treenode));
                                                                  (yyval.treenode)->attr.string = (yyvsp[-1].tokenData)->tokenStr;
                                                                  (yyval.treenode)->attrSet = true;
                                                                 }
#line 1971 "parser.tab.c"
    break;

  case 86: /* sumExp: mulExp  */
#line 395 "parser.y"
                           {(yyval.treenode) = (yyvsp[0].treenode);}
#line 1977 "parser.tab.c"
    break;

  case 87: /* sumOp: PLUS  */
#line 398 "parser.y"
                       {(yyval.tokenData) = (yyvsp[0].tokenData);}
#line 1983 "parser.tab.c"
    break;

  case 88: /* sumOp: MINUS  */
#line 399 "parser.y"
                        {(yyval.tokenData) = (yyvsp[0].tokenData);}
#line 1989 "parser.tab.c"
    break;

  case 89: /* mulExp: mulExp mulOp unaryExp  */
#line 402 "parser.y"
                                                                { (yyval.treenode) = newExpNode(OpK,(yyvsp[-1].tokenData),(yyvsp[-2].treenode),(yyvsp[0].treenode));
                                                                  (yyval.treenode)->attr.string = (yyvsp[-1].tokenData)->tokenStr;
                                                                  (yyval.treenode)->attrSet = true;
                                                                }
#line 1998 "parser.tab.c"
    break;

  case 90: /* mulExp: unaryExp  */
#line 406 "parser.y"
                           {(yyval.treenode) = (yyvsp[0].treenode);}
#line 2004 "parser.tab.c"
    break;

  case 91: /* mulOp: MULT  */
#line 409 "parser.y"
                       {(yyval.tokenData) = (yyvsp[0].tokenData);}
#line 2010 "parser.tab.c"
    break;

  case 92: /* mulOp: DIV  */
#line 410 "parser.y"
                      {(yyval.tokenData) = (yyvsp[0].tokenData);}
#line 2016 "parser.tab.c"
    break;

  case 93: /* mulOp: MOD  */
#line 411 "parser.y"
                      {(yyval.tokenData) = (yyvsp[0].tokenData);}
#line 2022 "parser.tab.c"
    break;

  case 94: /* unaryExp: unaryOp unaryExp  */
#line 414 "parser.y"
                                                                { (yyval.treenode) = newExpNode(OpK,(yyvsp[-1].tokenData),(yyvsp[0].treenode));
                                                                  (yyval.treenode)->attr.string = (yyvsp[-1].tokenData)->tokenStr;
                                                                  (yyval.treenode)->attrSet = true;
                                                                }
#line 2031 "parser.tab.c"
    break;

  case 95: /* unaryExp: factor  */
#line 418 "parser.y"
                         {(yyval.treenode) = (yyvsp[0].treenode);}
#line 2037 "parser.tab.c"
    break;

  case 96: /* unaryOp: MINUS  */
#line 421 "parser.y"
                        {(yyval.tokenData) = (yyvsp[0].tokenData); (yyval.tokenData)->tokenClass = CHSIGN;}
#line 2043 "parser.tab.c"
    break;

  case 97: /* unaryOp: MULT  */
#line 422 "parser.y"
                        {(yyval.tokenData) = (yyvsp[0].tokenData); (yyval.tokenData)->tokenClass = SIZEOF;}
#line 2049 "parser.tab.c"
    break;

  case 98: /* unaryOp: QUESTION  */
#line 423 "parser.y"
                           {(yyval.tokenData) = (yyvsp[0].tokenData);}
#line 2055 "parser.tab.c"
    break;

  case 99: /* factor: immutable  */
#line 426 "parser.y"
                            {(yyval.treenode) = (yyvsp[0].treenode);}
#line 2061 "parser.tab.c"
    break;

  case 100: /* factor: mutable  */
#line 427 "parser.y"
                            {(yyval.treenode) = (yyvsp[0].treenode);}
#line 2067 "parser.tab.c"
    break;

  case 101: /* mutable: ID  */
#line 430 "parser.y"
                                                                { (yyval.treenode) = newExpNode(IdK,(yyvsp[0].tokenData));
                                                                  (yyval.treenode)->attr.name = (yyvsp[0].tokenData)->tokenStr;
                                                                  (yyval.treenode)->attrSet = true;
                                                                  (yyval.treenode)->isArray = false;  
                                                                }
#line 2077 "parser.tab.c"
    break;

  case 102: /* mutable: ID OPEN_BRACK exp CLOSE_BRACK  */
#line 435 "parser.y"
                                                                { 
                                                                  TreeNode * node = newExpNode(IdK,(yyvsp[-3].tokenData)); 
                                                                  node->attr.name = (yyvsp[-3].tokenData)->tokenStr;
                                                                  node->attrSet = true;
                                                                  node->isArray = true;
                                                                  (yyval.treenode) = newExpNode(OpK,(yyvsp[-2].tokenData),node,(yyvsp[-1].treenode));
                                                                  (yyval.treenode)->attr.name = (yyvsp[-2].tokenData)->tokenStr;
                                                                  (yyval.treenode)->attrSet = true;
                                                                  (yyval.treenode)->isArray = true;
                                                                }
#line 2092 "parser.tab.c"
    break;

  case 103: /* immutable: OPEN_PAREN exp CLOSE_PAREN  */
#line 447 "parser.y"
                                              { (yyval.treenode) = (yyvsp[-1].treenode);}
#line 2098 "parser.tab.c"
    break;

  case 104: /* immutable: call  */
#line 448 "parser.y"
                        {(yyval.treenode) = (yyvsp[0].treenode);}
#line 2104 "parser.tab.c"
    break;

  case 105: /* immutable: constant  */
#line 449 "parser.y"
                           {(yyval.treenode) = (yyvsp[0].treenode);}
#line 2110 "parser.tab.c"
    break;

  case 106: /* call: ID OPEN_PAREN args CLOSE_PAREN  */
#line 452 "parser.y"
                                                    { (yyval.treenode) = newExpNode(CallK,(yyvsp[-3].tokenData),(yyvsp[-1].treenode));
                                                      (yyval.treenode)->attr.name = (yyvsp[-3].tokenData)->tokenStr;
                                                      (yyval.treenode)->attrSet = true;
                                                    }
#line 2119 "parser.tab.c"
    break;

  case 107: /* args: argList  */
#line 458 "parser.y"
                            {(yyval.treenode) = (yyvsp[0].treenode);}
#line 2125 "parser.tab.c"
    break;

  case 108: /* args: %empty  */
#line 459 "parser.y"
                  {(yyval.treenode) = NULL;}
#line 2131 "parser.tab.c"
    break;

  case 109: /* argList: argList COMMA exp  */
#line 462 "parser.y"
                                        {(yyval.treenode) = addSibling((yyvsp[-2].treenode),(yyvsp[0].treenode));}
#line 2137 "parser.tab.c"
    break;

  case 110: /* argList: exp  */
#line 463 "parser.y"
                                        {(yyval.treenode) = (yyvsp[0].treenode);}
#line 2143 "parser.tab.c"
    break;

  case 111: /* constant: NUMCONST  */
#line 466 "parser.y"
                                { (yyval.treenode) = newExpNode(ConstantK,(yyvsp[0].tokenData));
                                  (yyval.treenode)->attr.value = (yyvsp[0].tokenData)->nValue;
                                  (yyval.treenode)->attrSet = true;
                                  (yyval.treenode)->expType = Integer;
                                  (yyval.treenode)->unionType = value;
                                }
#line 2154 "parser.tab.c"
    break;

  case 112: /* constant: CHARCONST  */
#line 472 "parser.y"
                                { (yyval.treenode) = newExpNode(ConstantK,(yyvsp[0].tokenData));
                                  (yyval.treenode)->attr.cvalue = (yyvsp[0].tokenData)->cValue;
                                  (yyval.treenode)->attrSet = true;
                                  (yyval.treenode)->expType = Char;
                                  (yyval.treenode)->unionType = cvalue;
                                }
#line 2165 "parser.tab.c"
    break;

  case 113: /* constant: STRINGCONST  */
#line 478 "parser.y"
                                { (yyval.treenode) = newExpNode(ConstantK,(yyvsp[0].tokenData));
                                  (yyval.treenode)->attr.string = (yyvsp[0].tokenData)->sValue; /*Shallow Cop*/
                                  (yyval.treenode)->attrSet = true;
                                  (yyval.treenode)->expType = Char;
                                  (yyval.treenode)->isArray = true; 
                                  (yyval.treenode)->unionType = string;
                                }
#line 2177 "parser.tab.c"
    break;

  case 114: /* constant: TRUE  */
#line 485 "parser.y"
                                { (yyval.treenode) = newExpNode(ConstantK,(yyvsp[0].tokenData));
                                  (yyval.treenode)->attr.value = (yyvsp[0].tokenData)->nValue;
                                  (yyval.treenode)->attrSet = true;
                                  (yyval.treenode)->expType = Boolean; 
                                  (yyval.treenode)->unionType = value;
                                }
#line 2188 "parser.tab.c"
    break;

  case 115: /* constant: FALSE  */
#line 491 "parser.y"
                                { (yyval.treenode) = newExpNode(ConstantK,(yyvsp[0].tokenData));
                                  (yyval.treenode)->attr.value = (yyvsp[0].tokenData)->nValue;
                                  (yyval.treenode)->attrSet = true;
                                  (yyval.treenode)->expType = Boolean;
                                  (yyval.treenode)->unionType = value; 
                                }
#line 2199 "parser.tab.c"
    break;


#line 2203 "parser.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;


#if !defined yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturn;
#endif


/*-------------------------------------------------------.
| yyreturn -- parsing is finished, clean up and return.  |
`-------------------------------------------------------*/
yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 588 "parser.y"

extern int yydebug;



int main(int argc, char *argv[])
{
    char c;
    bool printflag = false;
    bool errorflag = false;
    extern int optind;
    extern int NUM_WARNINGS;
    extern int NUM_ERRORS;
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
            else {
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
    if(printflag)
    {
      checkTree(symTab,syntaxTree,0,false,NULL);

      if(symTab->lookupGlobal(std::string("main")) == NULL)
      {
        printf("ERROR(LINKER): A function named 'main()' must be defined.\n");
        NUM_ERRORS++;
      }

      printf("Number of warnings: %d\n",NUM_WARNINGS);
      printf("Number of errors: %d\n",NUM_ERRORS);

      //printTree(syntaxTree,0);

      

    }
    return 0;
}

