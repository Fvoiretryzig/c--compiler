/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

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

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "syntax.y" /* yacc.c:339  */

	#include <stdio.h>
	#include <string.h>
	#include "gtree.h"
	#include "lex.yy.c"
	//#include "semantic.h"
	
	void yyerror(const char *s);
	#define YYERROR_VERBOSE
	//#define DEBUG_MSG
	
	int is_error;
	struct node* root;

#line 81 "syntax.tab.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "syntax.tab.h".  */
#ifndef YY_YY_SYNTAX_TAB_H_INCLUDED
# define YY_YY_SYNTAX_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    INT = 258,
    FLOAT = 259,
    ID = 260,
    SEMI = 261,
    COMMA = 262,
    ASSIGNOP = 263,
    RELOP = 264,
    STAR = 265,
    DIV = 266,
    PLUS = 267,
    MINUS = 268,
    AND = 269,
    OR = 270,
    DOT = 271,
    NOT = 272,
    TYPE = 273,
    LP = 274,
    RP = 275,
    LB = 276,
    RB = 277,
    LC = 278,
    RC = 279,
    STRUCT = 280,
    RETURN = 281,
    IF = 282,
    ELSE = 283,
    WHILE = 284,
    LOWER_THAN_ELSE = 285
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 17 "syntax.y" /* yacc.c:355  */

	struct node* gnode;

#line 156 "syntax.tab.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


extern YYSTYPE yylval;
extern YYLTYPE yylloc;
int yyparse (void);

#endif /* !YY_YY_SYNTAX_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 187 "syntax.tab.c" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

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

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
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


#if ! defined yyoverflow || YYERROR_VERBOSE

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
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
             && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE) + sizeof (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  13
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   265

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  31
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  22
/* YYNRULES -- Number of rules.  */
#define YYNRULES  65
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  122

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   285

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
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
      25,    26,    27,    28,    29,    30
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    47,    47,    57,    66,    73,    79,    85,    93,   100,
     106,   114,   120,   127,   133,   140,   146,   153,   161,   167,
     174,   180,   187,   193,   200,   208,   216,   223,   229,   236,
     242,   248,   258,   265,   271,   279,   285,   296,   302,   309,
     317,   324,   330,   337,   343,   352,   358,   364,   370,   376,
     382,   388,   394,   400,   406,   412,   418,   424,   430,   436,
     442,   449,   456,   471,   479,   485
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "INT", "FLOAT", "ID", "SEMI", "COMMA",
  "ASSIGNOP", "RELOP", "STAR", "DIV", "PLUS", "MINUS", "AND", "OR", "DOT",
  "NOT", "TYPE", "LP", "RP", "LB", "RB", "LC", "RC", "STRUCT", "RETURN",
  "IF", "ELSE", "WHILE", "LOWER_THAN_ELSE", "$accept", "Program",
  "ExtDefList", "ExtDef", "ExtDecList", "Specifier", "StructSpecifier",
  "OptTag", "Tag", "VarDec", "FunDec", "VarList", "ParamDec", "CompSt",
  "StmtList", "Stmt", "DefList", "Def", "DecList", "Dec", "Exp", "Args", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285
};
# endif

#define YYPACT_NINF -71

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-71)))

#define YYTABLE_NINF -29

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      56,     9,   -71,    13,    17,   -71,    56,    42,   -71,   -71,
      31,    38,   -71,   -71,   -71,     6,   -71,    69,     2,    12,
      20,    -6,   -71,    67,    74,    60,    20,   -71,    67,    70,
      20,   -71,    67,    92,   108,   -71,   -71,    91,   -71,    36,
      -1,    45,   109,   -71,   -71,    96,   -71,    20,   -71,     0,
     -71,   -71,   103,    66,    66,    66,    66,   116,   117,   -71,
     113,    36,    87,    66,   132,   -71,    67,   -71,   -71,   101,
     244,    57,   162,   118,    66,    66,   -71,   -71,   -71,   -71,
      66,    66,    66,    66,    66,    66,    66,    66,   145,   106,
     204,   -71,   -71,   -71,   133,   131,   -71,   -71,   176,   190,
     204,   237,    57,    57,   244,   244,   230,   217,   -71,   130,
     147,    66,   -71,    63,    63,   -71,   -71,   -71,   125,   -71,
      63,   -71
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,    11,    16,     0,     2,     0,     0,    12,     8,
      17,     0,    14,     1,     3,    18,     6,     0,     9,     0,
      38,     0,     5,     0,     0,     0,    38,     7,     0,     0,
      38,    21,     0,     0,    23,    18,    10,     0,    26,     0,
      43,     0,    41,    13,    37,    24,    20,     0,    19,     0,
      61,    62,    60,     0,     0,     0,     0,     0,     0,    30,
       0,     0,     0,     0,     0,    39,     0,    22,    35,     0,
      54,    55,     0,     0,     0,     0,    25,    27,    36,    29,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      44,    40,    42,    57,    65,     0,    53,    31,     0,     0,
      45,    48,    51,    52,    49,    50,    46,    47,    59,     0,
       0,     0,    56,     0,     0,    63,    58,    64,    32,    34,
       0,    33
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -71,   -71,   158,   -71,   142,     5,   -71,   -71,   -71,   -24,
     -71,   119,   -71,   148,   120,   -70,    61,   -71,   114,   -71,
     -53,    68
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     4,     5,     6,    17,    28,     8,    11,    12,    18,
      19,    33,    34,    59,    60,    61,    29,    30,    41,    42,
      62,    95
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      70,    71,    72,    73,    40,     7,    68,    63,    45,    23,
      90,     7,     2,    25,    31,     9,    94,    13,    10,     3,
      24,    98,    99,    24,    38,    21,    32,   100,   101,   102,
     103,   104,   105,   106,   107,    26,   110,    49,     2,    50,
      51,    52,    40,   118,   119,     3,    64,    15,    16,    53,
     121,    65,    32,    54,   -15,    55,    -4,     1,    94,    26,
     -28,    20,    56,    57,    49,    58,    50,    51,    52,    50,
      51,    52,    35,    88,     2,    22,    53,    37,    89,    53,
      54,     3,    55,    54,    38,    55,    26,    39,    78,    56,
      57,    44,    58,    79,    43,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    50,    51,    52,   109,    89,    50,
      51,    52,    46,    48,    53,    47,    66,    24,    54,    53,
      55,    93,    69,    54,    97,    55,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    74,    75,    76,    91,    89,
     111,    80,    81,    82,    83,    84,    85,    86,    87,    88,
     108,   112,   115,   120,    89,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    14,    36,    67,    27,    89,   116,
      80,    81,    82,    83,    84,    85,    86,    87,    88,   117,
      92,    77,    96,    89,    80,    81,    82,    83,    84,    85,
      86,    87,    88,     0,     0,     0,   113,    89,    80,    81,
      82,    83,    84,    85,    86,    87,    88,     0,     0,     0,
     114,    89,    80,    81,    82,    83,    84,    85,    86,    87,
      88,     0,     0,     0,     0,    89,    81,    82,    83,    84,
      85,    86,     0,    88,     0,     0,     0,     0,    89,    81,
      82,    83,    84,    85,     0,     0,    88,    82,    83,    84,
      85,    89,     0,    88,    82,    83,     0,     0,    89,     0,
      88,     0,     0,     0,     0,    89
};

static const yytype_int8 yycheck[] =
{
      53,    54,    55,    56,    28,     0,     6,     8,    32,     7,
      63,     6,    18,     1,    20,     6,    69,     0,     5,    25,
      21,    74,    75,    21,    24,    19,    21,    80,    81,    82,
      83,    84,    85,    86,    87,    23,    89,     1,    18,     3,
       4,     5,    66,   113,   114,    25,     1,     5,     6,    13,
     120,     6,    47,    17,    23,    19,     0,     1,   111,    23,
      24,    23,    26,    27,     1,    29,     3,     4,     5,     3,
       4,     5,     5,    16,    18,     6,    13,     3,    21,    13,
      17,    25,    19,    17,    24,    19,    23,    26,     1,    26,
      27,    30,    29,     6,    24,     8,     9,    10,    11,    12,
      13,    14,    15,    16,     3,     4,     5,     1,    21,     3,
       4,     5,    20,    22,    13,     7,     7,    21,    17,    13,
      19,    20,    19,    17,     6,    19,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    19,    19,    24,     6,    21,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    16,
       5,    20,    22,    28,    21,     8,     9,    10,    11,    12,
      13,    14,    15,    16,     6,    23,    47,    19,    21,    22,
       8,     9,    10,    11,    12,    13,    14,    15,    16,   111,
      66,    61,    20,    21,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    -1,    -1,    -1,    20,    21,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    -1,    -1,    -1,
      20,    21,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    -1,    -1,    -1,    -1,    21,     9,    10,    11,    12,
      13,    14,    -1,    16,    -1,    -1,    -1,    -1,    21,     9,
      10,    11,    12,    13,    -1,    -1,    16,    10,    11,    12,
      13,    21,    -1,    16,    10,    11,    -1,    -1,    21,    -1,
      16,    -1,    -1,    -1,    -1,    21
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     1,    18,    25,    32,    33,    34,    36,    37,     6,
       5,    38,    39,     0,    33,     5,     6,    35,    40,    41,
      23,    19,     6,     7,    21,     1,    23,    44,    36,    47,
      48,    20,    36,    42,    43,     5,    35,     3,    24,    47,
      40,    49,    50,    24,    47,    40,    20,     7,    22,     1,
       3,     4,     5,    13,    17,    19,    26,    27,    29,    44,
      45,    46,    51,     8,     1,     6,     7,    42,     6,    19,
      51,    51,    51,    51,    19,    19,    24,    45,     1,     6,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    21,
      51,     6,    49,    20,    51,    52,    20,     6,    51,    51,
      51,    51,    51,    51,    51,    51,    51,    51,     5,     1,
      51,     7,    20,    20,    20,    22,    22,    52,    46,    46,
      28,    46
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    31,    32,    33,    33,    34,    34,    34,    34,    35,
      35,    36,    36,    37,    37,    38,    38,    39,    40,    40,
      41,    41,    42,    42,    43,    44,    44,    45,    45,    46,
      46,    46,    46,    46,    46,    46,    46,    47,    47,    48,
      48,    49,    49,    50,    50,    51,    51,    51,    51,    51,
      51,    51,    51,    51,    51,    51,    51,    51,    51,    51,
      51,    51,    51,    51,    52,    52
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     0,     3,     2,     3,     2,     1,
       3,     1,     1,     5,     2,     1,     0,     1,     1,     4,
       4,     3,     3,     1,     2,     4,     2,     2,     0,     2,
       1,     3,     5,     7,     5,     2,     2,     2,     0,     3,
       4,     1,     3,     1,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     2,     2,     4,     3,     4,     3,
       1,     1,     1,     4,     3,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
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

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (0)
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


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


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static unsigned
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  unsigned res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += YYFPRINTF (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += YYFPRINTF (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += YYFPRINTF (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += YYFPRINTF (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += YYFPRINTF (yyo, "-%d", end_col);
    }
  return res;
 }

#  define YY_LOCATION_PRINT(File, Loc)          \
  yy_location_print_ (File, &(Loc))

# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value, Location); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  YYUSE (yylocationp);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  YY_LOCATION_PRINT (yyoutput, *yylocationp);
  YYFPRINTF (yyoutput, ": ");
  yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
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
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                       , &(yylsp[(yyi + 1) - (yynrhs)])                       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
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


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            /* Fall through.  */
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Location data for the lookahead symbol.  */
YYLTYPE yylloc
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.
       'yyls': related to locations.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    /* The location stack.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls;
    YYLTYPE *yylsp;

    /* The locations where the error started and ended.  */
    YYLTYPE yyerror_range[3];

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yylsp = yyls = yylsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  yylsp[0] = yylloc;
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;
        YYLTYPE *yyls1 = yyls;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yyls1, yysize * sizeof (*yylsp),
                    &yystacksize);

        yyls = yyls1;
        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
        YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

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

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
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

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END
  *++yylsp = yylloc;
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
| yyreduce -- Do a reduction.  |
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

  /* Default location.  */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 47 "syntax.y" /* yacc.c:1646  */
    {
					#ifdef DEBUG_MSG
					printf("\033[46;37mProgram: ExtDefList(%d)\033[0m\n", (yyloc).first_line);
					#endif
					(yyval.gnode) = CreateGNode("Program", (yyloc).first_line, _INIT_, Program_Extdeflist, 1, (yyvsp[0].gnode));
					//if(!is_error)
						tran((yyval.gnode), 0);
					root = (yyval.gnode);
				}
#line 1476 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 57 "syntax.y" /* yacc.c:1646  */
    {
					#ifdef DEBUG_MSG
					//printf("in ExtDefList: child:name1:%s name2:%s\n", $$->gchild[0]->name, $$->gchild[1]->name);
					
					printf("\033[46;37mExtDefList: ExtDef ExtDefList(%d)\033[0m\n", (yyloc).first_line);
					#endif
					(yyval.gnode) = CreateGNode("ExtDefList", (yyloc).first_line, _INIT_, Extdeflist_ExtdefExtdeflist, 2, (yyvsp[-1].gnode), (yyvsp[0].gnode));
					
				}
#line 1490 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 66 "syntax.y" /* yacc.c:1646  */
    {
					#ifdef DEBUG_MSG
					printf("\033[46;37mExtDefList: EMPTY(%d)\033[0m\n", (yyloc).first_line);
					#endif
					(yyval.gnode) = CreateGNode("ExtDefList", (yyloc).first_line, _INIT_, Extdeflist_Null, -1);
				}
#line 1501 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 73 "syntax.y" /* yacc.c:1646  */
    {
					#ifdef DEBUG_MSG
					printf("\033[46;37mExtDef: Specifier ExtDecList SEMI(%d)\033[0m\n", (yyloc).first_line);
					#endif
					(yyval.gnode) = CreateGNode("ExtDef", (yyloc).first_line, _INIT_, Extdef_SpecifierExtdeclistSemi, 3, (yyvsp[-2].gnode), (yyvsp[-1].gnode), (yyvsp[0].gnode));
				}
#line 1512 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 79 "syntax.y" /* yacc.c:1646  */
    {
					#ifdef DEBUG_MSG
					printf("\033[46;37mExtDef: Specifier ExtDeclist(%d)\033[0m\n", (yyloc).first_line);
					#endif
					(yyval.gnode) = CreateGNode("ExtDef", (yyloc).first_line, _INIT_, Extdef_SpecifierSemi, 2, (yyvsp[-1].gnode), (yyvsp[0].gnode));
				}
#line 1523 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 85 "syntax.y" /* yacc.c:1646  */
    {
					#ifdef DEBUG_MSG
					printf("\033[46;37mExtDef: Specifier FunDec CompSt(%d)\033[0m\n", (yyloc).first_line);
					#endif
					(yyval.gnode) = CreateGNode("ExtDef", (yyloc).first_line, _INIT_, Extdef_SpcifierFundecCompst, 3, (yyvsp[-2].gnode), (yyvsp[-1].gnode), (yyvsp[0].gnode));
				}
#line 1534 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 93 "syntax.y" /* yacc.c:1646  */
    {
					is_error = 1;
					#ifdef DEBUG_MSG
					printf("ExtDef: error SEMI\n");
					#endif
				}
#line 1545 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 100 "syntax.y" /* yacc.c:1646  */
    {
					#ifdef DEBUG_MSG
					printf("\033[46;37mExtDecList: VarDec(%d)\033[0m\n", (yyloc).first_line);
					#endif
					(yyval.gnode) = CreateGNode("ExtDecList", (yyloc).first_line, _INIT_, Extdeclist_Vardec, 1, (yyvsp[0].gnode));
				}
#line 1556 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 106 "syntax.y" /* yacc.c:1646  */
    {
					#ifdef DEBUG_MSG
					printf("\033[46;37mExtDecList: VarDec COMMA ExtDecList(%d)\033[0m\n", (yyloc).first_line);
					#endif
					(yyval.gnode) = CreateGNode("ExtDecList", (yyloc).first_line, _INIT_, Extdeclist_VardecCommaExtdeclist, 3, (yyvsp[-2].gnode), (yyvsp[-1].gnode), (yyvsp[0].gnode));
				}
#line 1567 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 114 "syntax.y" /* yacc.c:1646  */
    {
					#ifdef DEBUG_MSG
					printf("\033[46;37mSpecifier: TYPE	(%d)\033[0m\n", (yyloc).first_line);
					#endif
					(yyval.gnode) = CreateGNode("Specifier", (yyloc).first_line, _INIT_, Specifier_Type, 1, (yyvsp[0].gnode));
				}
#line 1578 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 120 "syntax.y" /* yacc.c:1646  */
    {
					#ifdef DEBUG_MSG
					printf("\033[46;37mSpecifier: StructSpecifier(%d)\033[0m\n", (yyloc).first_line);
					#endif
					(yyval.gnode) = CreateGNode("Specifier", (yyloc).first_line, _INIT_, Specifier_Structspecifier, 1, (yyvsp[0].gnode));
				}
#line 1589 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 127 "syntax.y" /* yacc.c:1646  */
    {
						#ifdef DEBUG_MSG
						printf("\033[46;37mStructSpecifier: STRUCT OptTag LC DefList RC(%d)\033[0m\n", (yyloc).first_line);
						#endif
						(yyval.gnode) = CreateGNode("StructSpecifier", (yyloc).first_line, _INIT_, StructSpecifier_StructOpttagLcDeflistRc,  5, (yyvsp[-4].gnode), (yyvsp[-3].gnode), (yyvsp[-2].gnode), (yyvsp[-1].gnode), (yyvsp[0].gnode));
					}
#line 1600 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 133 "syntax.y" /* yacc.c:1646  */
    {
						#ifdef DEBUG_MSG
						printf("\033[46;37mStructSpecifier: STRUCT Tag(%d)\033[0m\n", (yyloc).first_line);
						#endif
						(yyval.gnode) = CreateGNode("StructSpecifier", (yyloc).first_line, _INIT_, StructSpecifier_StructTag, 2, (yyvsp[-1].gnode), (yyvsp[0].gnode));
					}
#line 1611 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 140 "syntax.y" /* yacc.c:1646  */
    {
					#ifdef DEBUG_MSG
					printf("\033[46;37mOptTag: ID:(%d)\033[0m\n", (yyloc).first_line);
					#endif
					(yyval.gnode) = CreateGNode("OptTag", (yyloc).first_line, _INIT_, Opttag_Id, 1, (yyvsp[0].gnode));
				}
#line 1622 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 146 "syntax.y" /* yacc.c:1646  */
    {
					#ifdef DEBUG_MSG
					printf("\033[46;37mOptTag: EMPTY(%d)\033[0m\n", (yyloc).first_line);
					#endif
					(yyval.gnode) = CreateGNode("OptTag", (yyloc).first_line, _INIT_, Opttag_Null, -1);
				}
#line 1633 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 153 "syntax.y" /* yacc.c:1646  */
    {
					#ifdef DEBUG_MSG
					printf("\033[46;37mTag: ID:(%d)\033[0m\n", (yyloc).first_line);
					#endif
					(yyval.gnode) = CreateGNode("Tag", (yyloc).first_line, _INIT_, Tag_Id, 1, (yyvsp[0].gnode));
				}
#line 1644 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 161 "syntax.y" /* yacc.c:1646  */
    {
				#ifdef DEBUG_MSG
				printf("\033[46;37mVarDec: ID:(%d)\033[0m\n", (yyloc).first_line);
				#endif
				(yyval.gnode) = CreateGNode("VarDec", (yyloc).first_line, _INIT_, Vardec_Id, 1, (yyvsp[0].gnode));
			}
#line 1655 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 167 "syntax.y" /* yacc.c:1646  */
    {
				#ifdef DEBUG_MSG				
				printf("\033[46;37mVarDec: VarDec LB INT RB(%d)\033[0m\n", (yyloc).first_line);
				#endif
				(yyval.gnode) = CreateGNode("VarDec", (yyloc).first_line, _INIT_, Vardec_VardecLbIntRb, 4, (yyvsp[-3].gnode), (yyvsp[-2].gnode), (yyvsp[-1].gnode), (yyvsp[0].gnode));
			}
#line 1666 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 174 "syntax.y" /* yacc.c:1646  */
    {
				#ifdef DEBUG_MSG
				printf("\033[46;37mFunDec: ID LP VarList RP(%d)\033[0m\n", (yyloc).first_line);
				#endif
				(yyval.gnode) = CreateGNode("FunDec", (yyloc).first_line, _INIT_, Fundec_IdLpVarlistRp, 4, (yyvsp[-3].gnode), (yyvsp[-2].gnode), (yyvsp[-1].gnode), (yyvsp[0].gnode));
			}
#line 1677 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 180 "syntax.y" /* yacc.c:1646  */
    {
				#ifdef DEBUG_MSG
				printf("\033[46;37mFunDec: ID LP RP(%d)\033[0m\n", (yyloc).first_line);
				#endif
				(yyval.gnode) = CreateGNode("FunDec", (yyloc).first_line, _INIT_, Fundec_IdLpRp, 3, (yyvsp[-2].gnode), (yyvsp[-1].gnode), (yyvsp[0].gnode));
			}
#line 1688 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 187 "syntax.y" /* yacc.c:1646  */
    {
				#ifdef DEBUG_MSG
				printf("\033[46;37mVarList: ParamDec COMMA VarList(%d)\033[0m\n", (yyloc).first_line);
				#endif
				(yyval.gnode) = CreateGNode("VarList", (yyloc).first_line, _INIT_, Varlist_ParamdecCommaVarlist, 3, (yyvsp[-2].gnode), (yyvsp[-1].gnode), (yyvsp[0].gnode));
			}
#line 1699 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 193 "syntax.y" /* yacc.c:1646  */
    {
				#ifdef DEBUG_MSG
				printf("\033[46;37mVarList: ParaDec(%d)\033[0m\n", (yyloc).first_line);
				#endif
				(yyval.gnode) = CreateGNode("VarList", (yyloc).first_line, _INIT_, Varlist_Paramdec, 1, (yyvsp[0].gnode));
			}
#line 1710 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 200 "syntax.y" /* yacc.c:1646  */
    {
				#ifdef DEBUG_MSG
				printf("\033[46;37mParamDec: Specifier VarDec(%d)\033[0m\n", (yyloc).first_line);
				#endif
				(yyval.gnode) = CreateGNode("ParamDec", (yyloc).first_line, _INIT_, Paramdec_SpecifierVardec, 2, (yyvsp[-1].gnode), (yyvsp[0].gnode));
			}
#line 1721 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 208 "syntax.y" /* yacc.c:1646  */
    {
				#ifdef DEBUG_MSG
				printf("\033[46;37mCompSt: LC DefList StmtList RC(%d)\033[0m\n", (yyloc).first_line);
				#endif
				(yyval.gnode) = CreateGNode("CompSt", (yyloc).first_line, _INIT_, Compst_LcDeflistStmtlistRc, 4, (yyvsp[-3].gnode), (yyvsp[-2].gnode), (yyvsp[-1].gnode), (yyvsp[0].gnode));
			}
#line 1732 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 216 "syntax.y" /* yacc.c:1646  */
    {
				#ifdef DEBUG_MSG
				printf("\033[46;37mCompSt: error RC(%d)\033[0m\n", (yyloc).first_line);
				#endif
				is_error = 1;
			}
#line 1743 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 223 "syntax.y" /* yacc.c:1646  */
    {
				#ifdef DEBUG_MSG
				printf("\033[46;37mStmtList: Stmt StmtList(%d)\033[0m\n", (yyloc).first_line);
				#endif
				(yyval.gnode) = CreateGNode("StmtList", (yyloc).first_line, _INIT_, Stmtlist_StmtStmtlist, 2, (yyvsp[-1].gnode), (yyvsp[0].gnode));
			}
#line 1754 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 229 "syntax.y" /* yacc.c:1646  */
    {
				#ifdef DEBUG_MSG
				printf("\033[46;37mStmtList: EMPTY(%d)\033[0m\n", (yyloc).first_line);
				#endif
				(yyval.gnode) = CreateGNode("StmtList", (yyloc).first_line, _INIT_, Stmtlist_Null, -1);
			}
#line 1765 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 236 "syntax.y" /* yacc.c:1646  */
    {
				#ifdef DEBUG_MSG
				printf("\033[46;37mStmt: Exp SEMI(%d)\033[0m\n", (yyloc).first_line);
				#endif
				(yyval.gnode) = CreateGNode("Stmt", (yyloc).first_line, _INIT_, Stmt_ExpSemi, 2, (yyvsp[-1].gnode), (yyvsp[0].gnode));
			}
#line 1776 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 242 "syntax.y" /* yacc.c:1646  */
    {
				#ifdef DEBUG_MSG
				printf("\033[46;37mStmt: CompSt(%d)\033[0m\n", (yyloc).first_line);
				#endif
				(yyval.gnode) = CreateGNode("Stmt",(yyloc).first_line, _INIT_, Stmt_Compst, 1, (yyvsp[0].gnode));
			}
#line 1787 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 248 "syntax.y" /* yacc.c:1646  */
    {
				#ifdef DEBUG_MSG
				printf("\033[46;37mStmt: RETURN Exp SEMI(%d)\033[0m\n", (yyloc).first_line);
				#endif
				(yyval.gnode) = CreateGNode("Stmt", (yyloc).first_line, _INIT_, Stmt_ReturnExpSemi, 3, (yyvsp[-2].gnode), (yyvsp[-1].gnode), (yyvsp[0].gnode));
			}
#line 1798 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 258 "syntax.y" /* yacc.c:1646  */
    {
				#ifdef DEBUG_MSG
				printf("\033[46;37mStmt: IF LP Exp RP Stmt prec LOWER_THAN_ELSE(%d)\033[0m\n", (yyloc).first_line);
				#endif
				//BUG FIXED: wrong rule!!!!!
				(yyval.gnode) = CreateGNode("Stmt", (yyloc).first_line, _INIT_, Stmt_IfLpExpRpStmt, 5, (yyvsp[-4].gnode), (yyvsp[-3].gnode), (yyvsp[-2].gnode), (yyvsp[-1].gnode), (yyvsp[0].gnode));
			}
#line 1810 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 265 "syntax.y" /* yacc.c:1646  */
    {
				#ifdef DEBUG_MSG
				printf("\033[46;37mStmt: IF LP Exp RP Stmt ELSE Stmt(%d)\033[0m\n", (yyloc).first_line);
				#endif
				(yyval.gnode) = CreateGNode("Stmt", (yyloc).first_line, _INIT_, Stmt_IfLpExpRpStmtElseStmt, 7, (yyvsp[-6].gnode), (yyvsp[-5].gnode), (yyvsp[-4].gnode), (yyvsp[-3].gnode), (yyvsp[-2].gnode), (yyvsp[-1].gnode), (yyvsp[0].gnode));
			}
#line 1821 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 271 "syntax.y" /* yacc.c:1646  */
    {
				#ifdef DEBUG_MSG
				printf("\033[46;37mStmt: WHILE LP Exp RP Stmt(%d)\033[0m\n", (yyloc).first_line);
				#endif
				(yyval.gnode) = CreateGNode("Stmt", (yyloc).first_line, _INIT_, Stmt_WhileLpExpRpStmt, 5, (yyvsp[-4].gnode), (yyvsp[-3].gnode), (yyvsp[-2].gnode), (yyvsp[-1].gnode), (yyvsp[0].gnode));
			}
#line 1832 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 279 "syntax.y" /* yacc.c:1646  */
    {
				#ifdef DEBUG_MSG
				printf("\033[47;32mERROR: stmt: error SEMI in line %d\033[0m \n", (yyloc).first_line-1);
				#endif
				is_error = 1;
			}
#line 1843 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 285 "syntax.y" /* yacc.c:1646  */
    {
				#ifdef DEBUG_MSG
				printf("\033[47;32mERROR: stmt: Exp error in line %d\033[0m \n", (yyloc).first_line);
				#endif
				is_error = 1;
				#ifdef DEBUG_MSG
				printf("\033[47;32mis_error in line %d\033[0m \n", (yyloc).first_line);
				#endif
			}
#line 1857 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 296 "syntax.y" /* yacc.c:1646  */
    {
				#ifdef DEBUG_MSG
				printf("\033[46;37mDefList: Def DefList(%d)\033[0m\n", (yyloc).first_line);
				#endif
				(yyval.gnode) = CreateGNode("DefList", (yyloc).first_line, _INIT_, Deflist_DefDeflist, 2, (yyvsp[-1].gnode), (yyvsp[0].gnode));
			}
#line 1868 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 302 "syntax.y" /* yacc.c:1646  */
    {
				#ifdef DEBUG_MSG
				printf("\033[46;37mDefList: EMPTY(%d)\033[0m\n", (yyloc).first_line);
				#endif
				(yyval.gnode) = CreateGNode("DefList", (yyloc).first_line, _INIT_, Deflist_Null, -1);
			}
#line 1879 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 309 "syntax.y" /* yacc.c:1646  */
    {
				#ifdef DEBUG_MSG
				printf("\033[46;37mDef: Specifier DecList SEMI(%d)\033[0m\n", (yyloc).first_line);
				#endif
				(yyval.gnode) = CreateGNode("Def", (yyloc).first_line, _INIT_, Def_SpecifierDeclistSemi, 3, (yyvsp[-2].gnode), (yyvsp[-1].gnode), (yyvsp[0].gnode));
			}
#line 1890 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 317 "syntax.y" /* yacc.c:1646  */
    {
				#ifdef DEBUG_MSG
				printf("D\n");
				#endif
				is_error = 1;
			}
#line 1901 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 324 "syntax.y" /* yacc.c:1646  */
    {
				#ifdef DEBUG_MSG
				printf("\033[46;37mDecList: Dec(%d)\033[0m\n", (yyloc).first_line);
				#endif
				(yyval.gnode) = CreateGNode("DecList", (yyloc).first_line, _INIT_, Declist_Dec, 1, (yyvsp[0].gnode));
			}
#line 1912 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 330 "syntax.y" /* yacc.c:1646  */
    {
				#ifdef DEBUG_MSG
				printf("\033[46;37mDecList: Dec COMMA DecList(%d)\033[0m\n", (yyloc).first_line);
				#endif
				(yyval.gnode) = CreateGNode("DecList", (yyloc).first_line, _INIT_, Declist_DecCommaDeclist, 3, (yyvsp[-2].gnode), (yyvsp[-1].gnode), (yyvsp[0].gnode));
			}
#line 1923 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 337 "syntax.y" /* yacc.c:1646  */
    {
				#ifdef DEBUG_MSG
				printf("\033[46;37mDec: VarDec(%d)\033[0m\n", (yyloc).first_line);
				#endif
				(yyval.gnode) = CreateGNode("Dec", (yyloc).first_line, _INIT_, Dec_Vardec, 1, (yyvsp[0].gnode));
			}
#line 1934 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 343 "syntax.y" /* yacc.c:1646  */
    {
				#ifdef DEBUG_MSG
				printf("\033[46;37mDec: VarDec ASSIGNOP Exp(%d)\033[0m\n", (yyloc).first_line);
				#endif
				(yyval.gnode) = CreateGNode("Dec", (yyloc).first_line, _INIT_, Dec_VardecAssignopExp, 3, (yyvsp[-2].gnode), (yyvsp[-1].gnode), (yyvsp[0].gnode));
			}
#line 1945 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 352 "syntax.y" /* yacc.c:1646  */
    {
			#ifdef DEBUG_MSG
			printf("\033[46;37mExp: Exp ASSIGNOP Exp(%d)\033[0m\n", (yyloc).first_line);
			#endif
			(yyval.gnode) = CreateGNode("Exp", (yyloc).first_line, _INIT_, Exp_ExpAssignopExp, 3, (yyvsp[-2].gnode), (yyvsp[-1].gnode), (yyvsp[0].gnode));
		}
#line 1956 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 358 "syntax.y" /* yacc.c:1646  */
    {
			#ifdef DEBUG_MSG
			printf("\033[46;37mExp: Exp AND Exp(%d)\033[0m\n", (yyloc).first_line);
			#endif
			(yyval.gnode) = CreateGNode("Exp", (yyloc).first_line, _INIT_, Exp_ExpAndExp, 3, (yyvsp[-2].gnode), (yyvsp[-1].gnode), (yyvsp[0].gnode));
		}
#line 1967 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 364 "syntax.y" /* yacc.c:1646  */
    {
			#ifdef DEBUG_MSG
			printf("\033[46;37mExp: Exp OR Exp(%d)\033[0m\n", (yyloc).first_line);
			#endif
			(yyval.gnode) = CreateGNode("Exp", (yyloc).first_line, _INIT_, Exp_ExpOrExp, 3, (yyvsp[-2].gnode), (yyvsp[-1].gnode), (yyvsp[0].gnode));
		}
#line 1978 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 370 "syntax.y" /* yacc.c:1646  */
    {
			#ifdef DEBUG_MSG
			printf("\033[46;37mExp: Exp RELOP Exp(%d)\033[0m\n", (yyloc).first_line);
			#endif
			(yyval.gnode) = CreateGNode("Exp", (yyloc).first_line, _INIT_, Exp_ExpRelopExp, 3, (yyvsp[-2].gnode), (yyvsp[-1].gnode), (yyvsp[0].gnode));
		}
#line 1989 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 376 "syntax.y" /* yacc.c:1646  */
    {
			#ifdef DEBUG_MSG
			printf("\033[46;37mExp: Exp PLUS Exp(%d)\033[0m\n", (yyloc).first_line);
			#endif
			(yyval.gnode) = CreateGNode("Exp", (yyloc).first_line, _INIT_, Exp_ExpPlusExp, 3, (yyvsp[-2].gnode), (yyvsp[-1].gnode), (yyvsp[0].gnode));
		}
#line 2000 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 382 "syntax.y" /* yacc.c:1646  */
    {
			#ifdef DEBUG_MSG
			printf("\033[46;37mExp: Exp MINUS Exp(%d)\033[0m\n", (yyloc).first_line);
			#endif
			(yyval.gnode) = CreateGNode("Exp", (yyloc).first_line, _INIT_, Exp_ExpMinusExp, 3, (yyvsp[-2].gnode), (yyvsp[-1].gnode), (yyvsp[0].gnode));
		}
#line 2011 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 388 "syntax.y" /* yacc.c:1646  */
    {
			#ifdef DEBUG_MSG
			printf("\033[46;37mExp: Exp STAR Exp(%d)\033[0m\n", (yyloc).first_line);
			#endif
			(yyval.gnode) = CreateGNode("Exp", (yyloc).first_line, _INIT_, Exp_ExpStarExp, 3, (yyvsp[-2].gnode), (yyvsp[-1].gnode), (yyvsp[0].gnode));
		}
#line 2022 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 394 "syntax.y" /* yacc.c:1646  */
    {
			#ifdef DEBUG_MSG
			printf("\033[46;37mExp: Exp DIV Exp(%d)\033[0m\n", (yyloc).first_line);
			#endif
			(yyval.gnode) = CreateGNode("Exp", (yyloc).first_line, _INIT_, Exp_ExpDivExp, 3, (yyvsp[-2].gnode), (yyvsp[-1].gnode), (yyvsp[0].gnode));
		}
#line 2033 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 400 "syntax.y" /* yacc.c:1646  */
    {
			#ifdef DEBUG_MSG
			printf("\033[46;37mExp: LP Exp RP(%d)\033[0m\n", (yyloc).first_line);
			#endif
			(yyval.gnode) = CreateGNode("Exp", (yyloc).first_line, _INIT_, Exp_LpExpRp, 3, (yyvsp[-2].gnode), (yyvsp[-1].gnode), (yyvsp[0].gnode));
		}
#line 2044 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 406 "syntax.y" /* yacc.c:1646  */
    {
			#ifdef DEBUG_MSG
			printf("\033[46;37mExp: MINUS Exp(%d)\033[0m\n", (yyloc).first_line);
			#endif
			(yyval.gnode) = CreateGNode("Exp", (yyloc).first_line, _INIT_, Exp_MinusExp, 2, (yyvsp[-1].gnode), (yyvsp[0].gnode));
		}
#line 2055 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 412 "syntax.y" /* yacc.c:1646  */
    {
			#ifdef DEBUG_MSG
			printf("\033[46;37mExp: NOT Exp(%d)\033[0m\n", (yyloc).first_line);
			#endif
			(yyval.gnode) = CreateGNode("Exp", (yyloc).first_line, _INIT_, Exp_NotExp, 2, (yyvsp[-1].gnode), (yyvsp[0].gnode));
		}
#line 2066 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 418 "syntax.y" /* yacc.c:1646  */
    {
			#ifdef DEBUG_MSG
			printf("\033[46;37mExp: ID LP Args RP(%d)\033[0m\n", (yyloc).first_line);
			#endif
			(yyval.gnode) = CreateGNode("Exp", (yyloc).first_line, _INIT_, Exp_IdLpArgsRp, 4, (yyvsp[-3].gnode), (yyvsp[-2].gnode), (yyvsp[-1].gnode), (yyvsp[0].gnode));
		}
#line 2077 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 424 "syntax.y" /* yacc.c:1646  */
    {
			#ifdef DEBUG_MSG
			printf("\033[46;37mExp: ID LP RP(%d)\033[0m\n", (yyloc).first_line);
			#endif
			(yyval.gnode) = CreateGNode("Exp", (yyloc).first_line, _INIT_, Exp_IdLpRp, 3, (yyvsp[-2].gnode), (yyvsp[-1].gnode), (yyvsp[0].gnode));
		}
#line 2088 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 430 "syntax.y" /* yacc.c:1646  */
    {
			#ifdef DEBUG_MSG
			printf("\033[46;37mExp: Exp LB Exp RB(%d)\033[0m\n", (yyloc).first_line);
			#endif
			(yyval.gnode) = CreateGNode("Exp", (yyloc).first_line, _INIT_, Exp_ExpLbExpRb, 4, (yyvsp[-3].gnode), (yyvsp[-2].gnode), (yyvsp[-1].gnode), (yyvsp[0].gnode));
		}
#line 2099 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 436 "syntax.y" /* yacc.c:1646  */
    {
			#ifdef DEBUG_MSG
			printf("\033[46;37mExp: Exp DOT ID	(%d)\033[0m\n", (yyloc).first_line);
			#endif
			(yyval.gnode) = CreateGNode("Exp", (yyloc).first_line, _INIT_, Exp_ExpDotId, 3, (yyvsp[-2].gnode), (yyvsp[-1].gnode), (yyvsp[0].gnode));
		}
#line 2110 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 442 "syntax.y" /* yacc.c:1646  */
    {
			#ifdef DEBUG_MSG
			printf("\033[46;37mExp: ID	(%d)\033[0m\n", (yyloc).first_line);
			#endif
			(yyval.gnode) = CreateGNode("Exp", (yyloc).first_line, _INIT_, Exp_Id, 1, (yyvsp[0].gnode));
			//$$ = CreateIdGNode(yytext, @$.first_line);
		}
#line 2122 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 449 "syntax.y" /* yacc.c:1646  */
    {	
			#ifdef DEBUG_MSG
			printf("\033[46;37mExp: INT (%d)\033[0m\n", (yyloc).first_line);
			#endif
			(yyval.gnode) = CreateGNode("Exp", (yyloc).first_line, _INIT_, Exp_Int, 1, (yyvsp[0].gnode));
			//$$ = CreateIntGNode(atoi(yytext), @$.first_line);
		}
#line 2134 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 456 "syntax.y" /* yacc.c:1646  */
    {
			#ifdef DEBUG_MSG
			printf("\033[46;37mExp: FLOAT (%d)\033[0m\n", (yyloc).first_line);
			#endif
			(yyval.gnode) = CreateGNode("Exp", (yyloc).first_line, _INIT_, Exp_Float, 1, (yyvsp[0].gnode));
			//$$ - CreateFloatGNode(atof(yytext), @$.first_line);
		}
#line 2146 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 471 "syntax.y" /* yacc.c:1646  */
    {
				#ifdef DEBUG_MSG
				printf("\033[46;37mExp: exp LB error RB (%d)\033[0m\n", (yyloc).first_line);
				#endif
				is_error = 1;
				//yyerror("unexpected ']'");
			}
#line 2158 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 479 "syntax.y" /* yacc.c:1646  */
    {
			#ifdef DEBUG_MSG
			printf("\033[46;37mArgs: Exp COMMA Args(%d)\033[0m\n", (yyloc).first_line);
			#endif
			(yyval.gnode) = CreateGNode("Args", (yyloc).first_line, _INIT_, Args_ExpCommaArgs, 3, (yyvsp[-2].gnode), (yyvsp[-1].gnode), (yyvsp[0].gnode));
		}
#line 2169 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 485 "syntax.y" /* yacc.c:1646  */
    {
			#ifdef DEBUG_MSG
			printf("\033[46;37mArgs: Exp(%d)\033[0m\n", (yyloc).first_line);
			#endif
			(yyval.gnode) = CreateGNode("Args", (yyloc).first_line, _INIT_, Args_Exp, 1, (yyvsp[0].gnode));
		}
#line 2180 "syntax.tab.c" /* yacc.c:1646  */
    break;


#line 2184 "syntax.tab.c" /* yacc.c:1646  */
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
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;
  *++yylsp = yyloc;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }

  yyerror_range[1] = yylloc;

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
                      yytoken, &yylval, &yylloc);
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

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  yyerror_range[1] = yylsp[1-yylen];
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

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp, yylsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  /* Using YYLLOC is tempting, but would change the location of
     the lookahead.  YYLOC is available though.  */
  YYLLOC_DEFAULT (yyloc, yyerror_range, 2);
  *++yylsp = yyloc;

  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

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

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, &yylloc);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp, yylsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 492 "syntax.y" /* yacc.c:1906  */

void yyerror(const char *s)
{
	//fprintf (stderr, "\033[47;31mError type B at Line %d %s\033[0m\n", yylineno, s);
	fprintf (stderr, "Error type B at Line %d: %s.\n", yylineno, s);
}
