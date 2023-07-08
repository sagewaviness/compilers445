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
#line 1 "parser.y" /* yacc.c:339  */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include "treeNodes.h"
#include "treeUtils.h"
#include "dot.h"
#include "scanType.h"
#include "symbolTable.h"
#include "semantics.h"
#include "codegen.h"
#include "emitcode.h"

using namespace std;

int numErrors, numWarnings;
extern "C" int yylex();
extern "C" int yyparse();
extern "C" FILE *yyin;

void yyerror(const char *msg);

void printToken(TokenData myData, string tokenName, int type = 0) 
{
	cout << "Line: " << myData.linenum << " Type: " << tokenName;
	if(type==0)
  {
     cout << " Token: " << myData.tokenstr;
  }
	if(type==1)
  {
     cout << " Token: " << myData.nvalue;
  }
	if(type==2)
  {
     cout << " Token: " << myData.cvalue;
  }
		
	cout << endl;
}

TreeNode *addSibling(TreeNode *t, TreeNode *s)
{
    if (s==NULL && numErrors==0) {
        printf("ERROR(SYSTEM): never add a NULL to a sibling list.\n");
        exit(1);
    }
    if (t!=NULL) {
        TreeNode *tmp;

        tmp = t;
        while (tmp->sibling!=NULL) tmp = tmp->sibling;
        tmp->sibling = s;
        return t;
    }
    return s;
}

void setType(TreeNode *t, ExpType type, bool isStatic)
{
   while(t)
   {
      t->type = type;
      t->isStatic = isStatic;
      t = t->sibling;
   }
}

TreeNode *syntaxTree;


#line 139 "parser.tab.c" /* yacc.c:339  */

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
   by #include "parser.tab.h".  */
#ifndef YY_YY_PARSER_TAB_H_INCLUDED
# define YY_YY_PARSER_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    FIRSTOP = 258,
    ADDASS = 259,
    AND = 260,
    DEC = 261,
    DIVASS = 262,
    EQ = 263,
    GEQ = 264,
    INC = 265,
    LEQ = 266,
    MAX = 267,
    MIN = 268,
    MULASS = 269,
    NEQ = 270,
    NOT = 271,
    OR = 272,
    SUBASS = 273,
    CHSIGN = 274,
    SIZEOF = 275,
    PRECOMPILER = 276,
    LASTOP = 277,
    BOOL = 278,
    BREAK = 279,
    BY = 280,
    CHAR = 281,
    DO = 282,
    ELSE = 283,
    FOR = 284,
    IF = 285,
    INT = 286,
    RETURN = 287,
    STATIC = 288,
    THEN = 289,
    TO = 290,
    WHILE = 291,
    BOOLCONST = 292,
    CHARCONST = 293,
    ID = 294,
    NUMCONST = 295,
    STRINGCONST = 296,
    LASTTERM = 297
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 75 "parser.y" /* yacc.c:355  */

   TokenData *tokenData;
   TreeNode *tree;
   ExpType type; // for passing typespec up the tree 

#line 228 "parser.tab.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 245 "parser.tab.c" /* yacc.c:358  */

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
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
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
#define YYFINAL  4
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   236

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  61
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  49
/* YYNRULES -- Number of rules.  */
#define YYNRULES  115
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  176

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   297

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,    28,     2,     2,
      55,    56,    21,    22,    57,    23,     2,    24,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    53,    52,
      25,    26,    27,    29,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    58,     2,    59,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    51,     2,    54,     2,     2,     2,     2,
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
      15,    16,    17,    18,    19,    20,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    47,    48,    49,    50,    60
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   113,   113,   116,   117,   118,   121,   122,   125,   126,
     129,   132,   133,   135,   136,   139,   140,   143,   146,   150,
     151,   152,   154,   155,   158,   159,   162,   163,   166,   169,
     170,   173,   176,   181,   182,   185,   186,   187,   191,   192,
     193,   194,   197,   198,   201,   202,   203,   204,   211,   212,
     215,   218,   219,   222,   223,   226,   227,   230,   233,   234,
     235,   236,   237,   240,   241,   242,   243,   244,   247,   248,
     251,   252,   255,   256,   259,   260,   263,   264,   265,   266,
     267,   268,   271,   272,   276,   277,   280,   281,   284,   285,
     288,   289,   292,   293,   294,   297,   298,   301,   302,   303,
     306,   307,   310,   313,   321,   322,   323,   326,   329,   330,
     333,   334,   337,   342,   347,   352
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "FIRSTOP", "ADDASS", "AND", "DEC",
  "DIVASS", "EQ", "GEQ", "INC", "LEQ", "MAX", "MIN", "MULASS", "NEQ",
  "NOT", "OR", "SUBASS", "CHSIGN", "SIZEOF", "'*'", "'+'", "'-'", "'/'",
  "'<'", "'='", "'>'", "'%'", "'?'", "PRECOMPILER", "LASTOP", "BOOL",
  "BREAK", "BY", "CHAR", "DO", "ELSE", "FOR", "IF", "INT", "RETURN",
  "STATIC", "THEN", "TO", "WHILE", "BOOLCONST", "CHARCONST", "ID",
  "NUMCONST", "STRINGCONST", "'{'", "';'", "':'", "'}'", "'('", "')'",
  "','", "'['", "']'", "LASTTERM", "$accept", "program", "precomList",
  "declList", "decl", "varDecl", "scopedVarDecl", "varDeclList",
  "varDeclInit", "varDeclId", "typeSpec", "funDecl", "parms", "parmList",
  "parmTypeList", "parmIdList", "parmId", "stmt", "matched", "iterRange",
  "unmatched", "expstmt", "compoundstmt", "localDecls", "stmtList",
  "returnstmt", "breakstmt", "exp", "assignop", "simpleExp", "andExp",
  "unaryRelExp", "relExp", "relop", "minmaxExp", "minmaxop", "sumExp",
  "sumop", "mulExp", "mulop", "unaryExp", "unaryop", "factor", "mutable",
  "immutable", "call", "args", "argList", "constant", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,    42,    43,    45,    47,    60,    61,    62,    37,    63,
     276,   277,   278,   279,   280,   281,   282,   283,   284,   285,
     286,   287,   288,   289,   290,   291,   292,   293,   294,   295,
     296,   123,    59,    58,   125,    40,    41,    44,    91,    93,
     297
};
# endif

#define YYPACT_NINF -131

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-131)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     -15,  -131,    55,    34,  -131,  -131,  -131,  -131,  -131,     7,
     129,  -131,  -131,    -1,  -131,   -12,  -131,   -24,    15,  -131,
      18,    27,    23,    25,  -131,   -12,    38,  -131,    42,   152,
      46,    51,  -131,   105,   -12,    63,    68,    64,  -131,   152,
    -131,  -131,  -131,  -131,  -131,   -10,  -131,  -131,   152,   114,
     127,  -131,  -131,   209,    89,    -7,  -131,   164,  -131,  -131,
    -131,  -131,  -131,    74,    27,    84,    92,   152,   142,   152,
    -131,  -131,  -131,  -131,  -131,  -131,  -131,  -131,  -131,    90,
     114,    99,  -131,   105,  -131,  -131,   152,   152,    91,   152,
     152,  -131,  -131,  -131,  -131,  -131,  -131,  -131,  -131,   164,
     164,  -131,  -131,   164,  -131,  -131,  -131,   164,  -131,  -131,
    -131,  -131,   122,    -6,  -131,    97,    10,    49,  -131,  -131,
    -131,  -131,  -131,  -131,  -131,  -131,     3,  -131,  -131,   103,
     109,   108,  -131,   127,  -131,   117,    89,    -7,  -131,   152,
     105,  -131,   105,   -12,  -131,    42,    47,  -131,  -131,  -131,
     152,  -131,   126,    -8,  -131,   133,  -131,  -131,    42,    21,
    -131,  -131,  -131,   105,   152,   105,    66,  -131,  -131,  -131,
      -4,  -131,  -131,  -131,   152,   114
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       5,     4,     0,     0,     1,     3,    20,    21,    19,     0,
       2,     7,     8,     0,     9,    25,     6,    17,     0,    14,
      15,     0,     0,    24,    27,    25,     0,    10,     0,     0,
      31,    28,    30,     0,     0,     0,     0,    17,    13,     0,
      98,    97,    99,   115,   113,   102,   112,   114,     0,    16,
      69,    71,    73,    75,    83,    87,    91,     0,    96,   101,
     100,   105,   106,     0,     0,     0,     0,     0,     0,     0,
      52,    49,    23,    33,    34,    38,    39,    40,    41,     0,
      61,   101,    26,     0,    18,    72,   109,     0,     0,     0,
       0,    80,    79,    76,    84,    85,    81,    77,    78,     0,
       0,    88,    89,     0,    92,    93,    94,     0,    95,    32,
      29,    57,     0,     0,    55,     0,     0,    54,    48,    64,
      60,    67,    59,    66,    65,    63,     0,    22,   111,     0,
     108,     0,   104,    68,    70,    74,    82,    86,    90,     0,
       0,    56,     0,     0,    51,     0,     0,    62,    58,   107,
       0,   103,     0,     0,    44,    33,    36,    46,     0,     0,
      50,    53,   110,     0,     0,     0,     0,    12,    37,    47,
      42,    35,    45,    11,     0,    43
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -131,  -131,  -131,  -131,   162,  -131,  -131,  -129,   146,  -131,
      -2,  -131,   151,  -131,   144,  -131,   115,   -81,  -130,  -131,
    -124,  -131,  -131,  -131,  -131,  -131,  -131,   -43,  -131,   -29,
      93,   -36,  -131,  -131,    81,  -131,    83,  -131,   100,  -131,
     -51,  -131,  -131,   -26,  -131,  -131,  -131,  -131,  -131
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     3,    10,    11,    12,   144,    18,    19,    20,
      21,    14,    22,    23,    24,    31,    32,    72,    73,   152,
      74,    75,    76,   117,   146,    77,    78,    79,   126,    80,
      50,    51,    52,    99,    53,   100,    54,   103,    55,   107,
      56,    57,    58,    59,    60,    61,   129,   130,    62
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      49,    13,   127,    85,   147,    88,   108,    81,    13,    89,
     155,    89,   156,    89,   104,     1,   159,   105,   157,    39,
       6,   106,    81,     7,    40,   115,    41,    89,     8,   166,
     174,    25,    42,   168,    26,   171,   164,   140,   113,   169,
     116,   172,    81,   128,   131,    86,   142,    17,    87,    43,
      44,    45,    46,    47,   134,     4,   138,    81,    48,   154,
      81,    81,    15,    39,     5,   161,     6,    27,    40,     7,
      41,    29,    28,   167,     8,    30,    42,    34,    28,    33,
      65,     6,     9,   148,     7,    66,    67,    36,    68,     8,
      37,   143,    69,    43,    44,    45,    46,    47,    70,    71,
      81,   160,    48,   119,    63,   120,   121,   162,    64,   122,
     153,   101,   102,   123,    81,   145,    81,   124,   173,    83,
      81,    39,    26,    28,    81,   125,    40,    84,    41,    94,
      95,    89,    90,   109,    42,   170,   111,    81,    65,    81,
     112,   158,   118,    66,    67,   175,    68,   132,   139,   141,
      69,    43,    44,    45,    46,    47,    70,    71,    39,   149,
      48,     6,   163,    40,     7,    41,   150,   151,    39,     8,
     165,    42,    16,    40,    38,    41,    35,     9,    82,   110,
     135,    42,   133,   136,     0,    40,     0,    41,    43,    44,
      45,    46,    47,    42,   114,     0,     0,    48,    43,    44,
      45,    46,    47,   137,     0,     0,     0,    48,     0,     0,
      43,    44,    45,    46,    47,     0,     0,    91,    92,    48,
      93,    94,    95,     0,    96,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    97,     0,    98
};

static const yytype_int16 yycheck[] =
{
      29,     3,    83,    39,     1,    48,    57,    33,    10,    17,
     140,    17,   142,    17,    21,    30,   145,    24,   142,    16,
      32,    28,    48,    35,    21,    68,    23,    17,    40,   158,
      34,    55,    29,   163,    58,   165,    44,    43,    67,   163,
      69,   165,    68,    86,    87,    55,    36,    48,    58,    46,
      47,    48,    49,    50,    90,     0,   107,    83,    55,   140,
      86,    87,    55,    16,    30,   146,    32,    52,    21,    35,
      23,    53,    57,    52,    40,    48,    29,    52,    57,    56,
      33,    32,    48,   126,    35,    38,    39,    49,    41,    40,
      48,    42,    45,    46,    47,    48,    49,    50,    51,    52,
     126,    54,    55,     4,    58,     6,     7,   150,    57,    10,
     139,    22,    23,    14,   140,   117,   142,    18,    52,    56,
     146,    16,    58,    57,   150,    26,    21,    59,    23,    12,
      13,    17,     5,    59,    29,   164,    52,   163,    33,   165,
      48,   143,    52,    38,    39,   174,    41,    56,    26,    52,
      45,    46,    47,    48,    49,    50,    51,    52,    16,    56,
      55,    32,    36,    21,    35,    23,    57,    59,    16,    40,
      37,    29,    10,    21,    28,    23,    25,    48,    34,    64,
      99,    29,    89,   100,    -1,    21,    -1,    23,    46,    47,
      48,    49,    50,    29,    52,    -1,    -1,    55,    46,    47,
      48,    49,    50,   103,    -1,    -1,    -1,    55,    -1,    -1,
      46,    47,    48,    49,    50,    -1,    -1,     8,     9,    55,
      11,    12,    13,    -1,    15,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    25,    -1,    27
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    30,    62,    63,     0,    30,    32,    35,    40,    48,
      64,    65,    66,    71,    72,    55,    65,    48,    68,    69,
      70,    71,    73,    74,    75,    55,    58,    52,    57,    53,
      48,    76,    77,    56,    52,    73,    49,    48,    69,    16,
      21,    23,    29,    46,    47,    48,    49,    50,    55,    90,
      91,    92,    93,    95,    97,    99,   101,   102,   103,   104,
     105,   106,   109,    58,    57,    33,    38,    39,    41,    45,
      51,    52,    78,    79,    81,    82,    83,    86,    87,    88,
      90,   104,    75,    56,    59,    92,    55,    58,    88,    17,
       5,     8,     9,    11,    12,    13,    15,    25,    27,    94,
      96,    22,    23,    98,    21,    24,    28,   100,   101,    59,
      77,    52,    48,    90,    52,    88,    90,    84,    52,     4,
       6,     7,    10,    14,    18,    26,    89,    78,    88,   107,
     108,    88,    56,    91,    92,    95,    97,    99,   101,    26,
      43,    52,    36,    42,    67,    71,    85,     1,    88,    56,
      57,    59,    80,    90,    78,    79,    79,    81,    71,    68,
      54,    78,    88,    36,    44,    37,    68,    52,    79,    81,
      90,    79,    81,    52,    34,    90
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    61,    62,    63,    63,    63,    64,    64,    65,    65,
      66,    67,    67,    68,    68,    69,    69,    70,    70,    71,
      71,    71,    72,    72,    73,    73,    74,    74,    75,    76,
      76,    77,    77,    78,    78,    79,    79,    79,    79,    79,
      79,    79,    80,    80,    81,    81,    81,    81,    82,    82,
      83,    84,    84,    85,    85,    86,    86,    87,    88,    88,
      88,    88,    88,    89,    89,    89,    89,    89,    90,    90,
      91,    91,    92,    92,    93,    93,    94,    94,    94,    94,
      94,    94,    95,    95,    96,    96,    97,    97,    98,    98,
      99,    99,   100,   100,   100,   101,   101,   102,   102,   102,
     103,   103,   104,   104,   105,   105,   105,   106,   107,   107,
     108,   108,   109,   109,   109,   109
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     2,     1,     0,     2,     1,     1,     1,
       3,     4,     3,     3,     1,     1,     3,     1,     4,     1,
       1,     1,     6,     5,     1,     0,     3,     1,     2,     3,
       1,     1,     3,     1,     1,     6,     4,     6,     1,     1,
       1,     1,     3,     5,     4,     6,     4,     6,     2,     1,
       4,     2,     0,     2,     0,     2,     3,     2,     3,     2,
       2,     1,     3,     1,     1,     1,     1,     1,     3,     1,
       3,     1,     2,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     3,     1,     1,     1,     3,     1,     1,     1,
       3,     1,     1,     1,     1,     2,     1,     1,     1,     1,
       1,     1,     1,     4,     3,     1,     1,     4,     1,     0,
       3,     1,     1,     1,     1,     1
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
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
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
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
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
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
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
                                              );
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
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
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

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
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

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);

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
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

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


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 113 "parser.y" /* yacc.c:1646  */
    {syntaxTree = (yyvsp[0].tree);}
#line 1472 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 116 "parser.y" /* yacc.c:1646  */
    { (yyval.tree) = NULL; printf("%s\n", yylval.tokenData->tokenstr);}
#line 1478 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 117 "parser.y" /* yacc.c:1646  */
    { (yyval.tree) = NULL; printf("%s\n", yylval.tokenData->tokenstr);}
#line 1484 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 118 "parser.y" /* yacc.c:1646  */
    { (yyval.tree) = NULL;}
#line 1490 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 121 "parser.y" /* yacc.c:1646  */
    {(yyval.tree) = addSibling((yyvsp[-1].tree),(yyvsp[0].tree));}
#line 1496 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 122 "parser.y" /* yacc.c:1646  */
    {(yyval.tree) = (yyvsp[0].tree);}
#line 1502 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 125 "parser.y" /* yacc.c:1646  */
    {(yyval.tree) = (yyvsp[0].tree);}
#line 1508 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 126 "parser.y" /* yacc.c:1646  */
    {(yyval.tree) = (yyvsp[0].tree);}
#line 1514 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 129 "parser.y" /* yacc.c:1646  */
    {(yyval.tree) = (yyvsp[-1].tree); setType((yyvsp[-1].tree), (yyvsp[-2].type), false); yyerrok;}
#line 1520 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 132 "parser.y" /* yacc.c:1646  */
    {(yyval.tree) = (yyvsp[-1].tree); setType((yyvsp[-1].tree),(yyvsp[-2].type),true); yyerrok;}
#line 1526 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 133 "parser.y" /* yacc.c:1646  */
    {(yyval.tree) = (yyvsp[-1].tree); setType((yyvsp[-1].tree), (yyvsp[-2].type), false); yyerrok;}
#line 1532 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 135 "parser.y" /* yacc.c:1646  */
    {(yyval.tree) = addSibling((yyvsp[-2].tree), (yyvsp[0].tree)); yyerrok;}
#line 1538 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 136 "parser.y" /* yacc.c:1646  */
    {(yyval.tree) = (yyvsp[0].tree);}
#line 1544 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 139 "parser.y" /* yacc.c:1646  */
    {(yyval.tree) = (yyvsp[0].tree);}
#line 1550 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 140 "parser.y" /* yacc.c:1646  */
    { (yyval.tree) = (yyvsp[-2].tree); if ((yyval.tree) != NULL) (yyval.tree)->child[0] = (yyvsp[0].tree);}
#line 1556 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 143 "parser.y" /* yacc.c:1646  */
    {(yyval.tree) = newDeclNode(VarK, UndefinedType, (yyvsp[0].tokenData));
						(yyval.tree)->isArray = false;
						(yyval.tree)->size = 1;}
#line 1564 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 146 "parser.y" /* yacc.c:1646  */
    {(yyval.tree) = newDeclNode(VarK, UndefinedType,(yyvsp[-3].tokenData)); 
				                                 (yyval.tree)->isArray = true;
				                                 (yyval.tree)->size = (yyvsp[-1].tokenData)->nvalue + 1;}
#line 1572 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 150 "parser.y" /* yacc.c:1646  */
    {(yyval.type) = Integer;}
#line 1578 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 151 "parser.y" /* yacc.c:1646  */
    {(yyval.type) = Boolean;}
#line 1584 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 152 "parser.y" /* yacc.c:1646  */
    {(yyval.type) = Char;}
#line 1590 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 154 "parser.y" /* yacc.c:1646  */
    {(yyval.tree) = newDeclNode(FuncK, (yyvsp[-5].type), (yyvsp[-4].tokenData), (yyvsp[-2].tree), (yyvsp[0].tree));}
#line 1596 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 155 "parser.y" /* yacc.c:1646  */
    {(yyval.tree) = newDeclNode(FuncK, Void, (yyvsp[-4].tokenData), (yyvsp[-2].tree), (yyvsp[0].tree));}
#line 1602 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 158 "parser.y" /* yacc.c:1646  */
    {(yyval.tree) = (yyvsp[0].tree);}
#line 1608 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 159 "parser.y" /* yacc.c:1646  */
    {(yyval.tree) = NULL;}
#line 1614 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 162 "parser.y" /* yacc.c:1646  */
    {(yyval.tree) = addSibling((yyvsp[-2].tree),(yyvsp[0].tree));}
#line 1620 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 163 "parser.y" /* yacc.c:1646  */
    {(yyval.tree) = (yyvsp[0].tree);}
#line 1626 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 166 "parser.y" /* yacc.c:1646  */
    {(yyval.tree) = (yyvsp[0].tree); setType((yyvsp[0].tree), (yyvsp[-1].type), false);}
#line 1632 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 169 "parser.y" /* yacc.c:1646  */
    { (yyval.tree) = addSibling((yyvsp[-2].tree), (yyvsp[0].tree));}
#line 1638 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 170 "parser.y" /* yacc.c:1646  */
    {(yyval.tree) = (yyvsp[0].tree);}
#line 1644 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 173 "parser.y" /* yacc.c:1646  */
    {(yyval.tree) = newDeclNode(ParamK, UndefinedType, (yyvsp[0].tokenData));
                                           (yyval.tree)->isArray = false; 
    		                                    (yyval.tree)->size = 1;}
#line 1652 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 176 "parser.y" /* yacc.c:1646  */
    {(yyval.tree) = newDeclNode(ParamK, UndefinedType, (yyvsp[-2].tokenData));
          	                               (yyval.tree)->isArray = true;
                	                           (yyval.tree)->size = 1;}
#line 1660 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 181 "parser.y" /* yacc.c:1646  */
    {(yyval.tree) = (yyvsp[0].tree);}
#line 1666 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 182 "parser.y" /* yacc.c:1646  */
    {(yyval.tree) = (yyvsp[0].tree);}
#line 1672 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 185 "parser.y" /* yacc.c:1646  */
    {(yyval.tree) = newStmtNode(IfK, (yyvsp[-5].tokenData),(yyvsp[-4].tree),(yyvsp[-2].tree),(yyvsp[0].tree));}
#line 1678 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 186 "parser.y" /* yacc.c:1646  */
    {(yyval.tree) = newStmtNode(WhileK,(yyvsp[-3].tokenData),(yyvsp[-2].tree),(yyvsp[0].tree));}
#line 1684 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 187 "parser.y" /* yacc.c:1646  */
    {(yyval.tree) = newStmtNode(ForK, (yyvsp[-5].tokenData), NULL, (yyvsp[-2].tree),(yyvsp[0].tree));
                                                            (yyval.tree)->child[0] = newDeclNode(VarK,Integer,(yyvsp[-4].tokenData));
                                                            (yyval.tree)->child[0]->attr.name = (yyvsp[-4].tokenData)->svalue;
                                                            (yyval.tree)->child[0]->isArray = false;}
#line 1693 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 191 "parser.y" /* yacc.c:1646  */
    {(yyval.tree) = (yyvsp[0].tree);}
#line 1699 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 192 "parser.y" /* yacc.c:1646  */
    {(yyval.tree) = (yyvsp[0].tree);}
#line 1705 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 193 "parser.y" /* yacc.c:1646  */
    {(yyval.tree) = (yyvsp[0].tree);}
#line 1711 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 194 "parser.y" /* yacc.c:1646  */
    {(yyval.tree) = (yyvsp[0].tree);}
#line 1717 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 197 "parser.y" /* yacc.c:1646  */
    {(yyval.tree) = newStmtNode(RangeK, (yyvsp[-1].tokenData),(yyvsp[-2].tree),(yyvsp[0].tree));}
#line 1723 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 198 "parser.y" /* yacc.c:1646  */
    {(yyval.tree) = newStmtNode(RangeK, (yyvsp[-3].tokenData),(yyvsp[-4].tree),(yyvsp[-2].tree),(yyvsp[0].tree));}
#line 1729 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 201 "parser.y" /* yacc.c:1646  */
    {(yyval.tree) = newStmtNode(IfK, (yyvsp[-3].tokenData),(yyvsp[-2].tree),(yyvsp[0].tree));}
#line 1735 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 202 "parser.y" /* yacc.c:1646  */
    {(yyval.tree) = newStmtNode(IfK, (yyvsp[-5].tokenData),(yyvsp[-4].tree),(yyvsp[-2].tree),(yyvsp[0].tree));}
#line 1741 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 203 "parser.y" /* yacc.c:1646  */
    {(yyval.tree) = newStmtNode(WhileK, (yyvsp[-3].tokenData),(yyvsp[-2].tree),(yyvsp[0].tree));}
#line 1747 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 204 "parser.y" /* yacc.c:1646  */
    {(yyval.tree) = newStmtNode(ForK,(yyvsp[-5].tokenData),NULL,(yyvsp[-2].tree),(yyvsp[0].tree));
                                                            (yyval.tree)->child[0] = newDeclNode(VarK,Integer,(yyvsp[-4].tokenData));
                                                            (yyval.tree)->child[0]->attr.name = (yyvsp[-4].tokenData)->svalue;
                                                            (yyval.tree)->child[0]->isArray = false;
                                                               (yyval.tree)->child[0]->size = 1;}
#line 1757 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 211 "parser.y" /* yacc.c:1646  */
    {(yyval.tree) = (yyvsp[-1].tree);}
#line 1763 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 212 "parser.y" /* yacc.c:1646  */
    {(yyval.tree) = NULL;}
#line 1769 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 215 "parser.y" /* yacc.c:1646  */
    {(yyval.tree) = newStmtNode(CompoundK, (yyvsp[-3].tokenData), (yyvsp[-2].tree), (yyvsp[-1].tree));}
#line 1775 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 218 "parser.y" /* yacc.c:1646  */
    {(yyval.tree) = addSibling((yyvsp[-1].tree),(yyvsp[0].tree));}
#line 1781 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 219 "parser.y" /* yacc.c:1646  */
    {(yyval.tree) = NULL;}
#line 1787 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 222 "parser.y" /* yacc.c:1646  */
    {(yyval.tree) = ((yyvsp[0].tree) ==NULL? (yyvsp[-1].tree): addSibling((yyvsp[-1].tree), (yyvsp[0].tree)));}
#line 1793 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 223 "parser.y" /* yacc.c:1646  */
    {(yyval.tree) = NULL;}
#line 1799 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 226 "parser.y" /* yacc.c:1646  */
    {(yyval.tree) = newStmtNode(ReturnK, (yyvsp[-1].tokenData));}
#line 1805 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 227 "parser.y" /* yacc.c:1646  */
    {(yyval.tree) = newStmtNode(ReturnK, (yyvsp[-2].tokenData), (yyvsp[-1].tree));}
#line 1811 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 230 "parser.y" /* yacc.c:1646  */
    {(yyval.tree) = newStmtNode(BreakK, (yyvsp[-1].tokenData));}
#line 1817 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 233 "parser.y" /* yacc.c:1646  */
    {(yyval.tree) = newExpNode(AssignK, (yyvsp[-1].tokenData), (yyvsp[-2].tree), (yyvsp[0].tree));}
#line 1823 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 234 "parser.y" /* yacc.c:1646  */
    {(yyval.tree) = newExpNode(AssignK, (yyvsp[0].tokenData), (yyvsp[-1].tree));}
#line 1829 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 235 "parser.y" /* yacc.c:1646  */
    {(yyval.tree) = newExpNode(AssignK, (yyvsp[0].tokenData), (yyvsp[-1].tree));}
#line 1835 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 236 "parser.y" /* yacc.c:1646  */
    {(yyval.tree) = (yyvsp[0].tree);}
#line 1841 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 237 "parser.y" /* yacc.c:1646  */
    {(yyval.tree) = NULL;}
#line 1847 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 240 "parser.y" /* yacc.c:1646  */
    {(yyval.tokenData) = (yyvsp[0].tokenData);}
#line 1853 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 241 "parser.y" /* yacc.c:1646  */
    {(yyval.tokenData) = (yyvsp[0].tokenData);}
#line 1859 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 242 "parser.y" /* yacc.c:1646  */
    {(yyval.tokenData) = (yyvsp[0].tokenData);}
#line 1865 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 243 "parser.y" /* yacc.c:1646  */
    {(yyval.tokenData) = (yyvsp[0].tokenData);}
#line 1871 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 244 "parser.y" /* yacc.c:1646  */
    {(yyval.tokenData) = (yyvsp[0].tokenData);}
#line 1877 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 247 "parser.y" /* yacc.c:1646  */
    {(yyval.tree) = newExpNode(OpK, (yyvsp[-1].tokenData), (yyvsp[-2].tree),(yyvsp[0].tree));}
#line 1883 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 248 "parser.y" /* yacc.c:1646  */
    {(yyval.tree) = (yyvsp[0].tree);}
#line 1889 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 70:
#line 251 "parser.y" /* yacc.c:1646  */
    {(yyval.tree) = newExpNode(OpK, (yyvsp[-1].tokenData),(yyvsp[-2].tree),(yyvsp[0].tree));}
#line 1895 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 71:
#line 252 "parser.y" /* yacc.c:1646  */
    {(yyval.tree) = (yyvsp[0].tree);}
#line 1901 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 72:
#line 255 "parser.y" /* yacc.c:1646  */
    {(yyval.tree) = newExpNode(OpK, (yyvsp[-1].tokenData), (yyvsp[0].tree));}
#line 1907 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 73:
#line 256 "parser.y" /* yacc.c:1646  */
    {(yyval.tree) = (yyvsp[0].tree);}
#line 1913 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 74:
#line 259 "parser.y" /* yacc.c:1646  */
    {(yyval.tree) = newExpNode(OpK, (yyvsp[-1].tokenData),(yyvsp[-2].tree),(yyvsp[0].tree));}
#line 1919 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 75:
#line 260 "parser.y" /* yacc.c:1646  */
    {(yyval.tree) = (yyvsp[0].tree);}
#line 1925 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 76:
#line 263 "parser.y" /* yacc.c:1646  */
    {(yyval.tokenData) = (yyvsp[0].tokenData);}
#line 1931 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 77:
#line 264 "parser.y" /* yacc.c:1646  */
    {(yyval.tokenData) = (yyvsp[0].tokenData);}
#line 1937 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 78:
#line 265 "parser.y" /* yacc.c:1646  */
    {(yyval.tokenData) = (yyvsp[0].tokenData);}
#line 1943 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 79:
#line 266 "parser.y" /* yacc.c:1646  */
    {(yyval.tokenData) = (yyvsp[0].tokenData);}
#line 1949 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 80:
#line 267 "parser.y" /* yacc.c:1646  */
    {(yyval.tokenData) = (yyvsp[0].tokenData);}
#line 1955 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 81:
#line 268 "parser.y" /* yacc.c:1646  */
    {(yyval.tokenData) = (yyvsp[0].tokenData);}
#line 1961 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 82:
#line 271 "parser.y" /* yacc.c:1646  */
    {(yyval.tree) = newExpNode(OpK, (yyvsp[-1].tokenData),(yyvsp[-2].tree),(yyvsp[0].tree));}
#line 1967 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 83:
#line 272 "parser.y" /* yacc.c:1646  */
    {(yyval.tree) = (yyvsp[0].tree);}
#line 1973 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 84:
#line 276 "parser.y" /* yacc.c:1646  */
    {(yyval.tokenData) = (yyvsp[0].tokenData);}
#line 1979 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 85:
#line 277 "parser.y" /* yacc.c:1646  */
    {(yyval.tokenData) = (yyvsp[0].tokenData);}
#line 1985 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 86:
#line 280 "parser.y" /* yacc.c:1646  */
    {(yyval.tree) = newExpNode(OpK, (yyvsp[-1].tokenData),(yyvsp[-2].tree),(yyvsp[0].tree));}
#line 1991 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 87:
#line 281 "parser.y" /* yacc.c:1646  */
    {(yyval.tree) = (yyvsp[0].tree);}
#line 1997 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 88:
#line 284 "parser.y" /* yacc.c:1646  */
    {(yyval.tokenData) = (yyvsp[0].tokenData);}
#line 2003 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 89:
#line 285 "parser.y" /* yacc.c:1646  */
    {(yyval.tokenData) = (yyvsp[0].tokenData);}
#line 2009 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 90:
#line 288 "parser.y" /* yacc.c:1646  */
    {(yyval.tree) = newExpNode(OpK, (yyvsp[-1].tokenData),(yyvsp[-2].tree),(yyvsp[0].tree));}
#line 2015 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 91:
#line 289 "parser.y" /* yacc.c:1646  */
    {(yyval.tree) = (yyvsp[0].tree);}
#line 2021 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 92:
#line 292 "parser.y" /* yacc.c:1646  */
    {(yyval.tokenData) = (yyvsp[0].tokenData);}
#line 2027 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 93:
#line 293 "parser.y" /* yacc.c:1646  */
    {(yyval.tokenData) = (yyvsp[0].tokenData);}
#line 2033 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 94:
#line 294 "parser.y" /* yacc.c:1646  */
    {(yyval.tokenData) = (yyvsp[0].tokenData);}
#line 2039 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 95:
#line 297 "parser.y" /* yacc.c:1646  */
    {(yyval.tree) = newExpNode(OpK, (yyvsp[-1].tokenData),(yyvsp[0].tree));}
#line 2045 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 96:
#line 298 "parser.y" /* yacc.c:1646  */
    {(yyval.tree) = (yyvsp[0].tree);}
#line 2051 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 97:
#line 301 "parser.y" /* yacc.c:1646  */
    {(yyvsp[0].tokenData)->tokenclass = CHSIGN; (yyval.tokenData) = (yyvsp[0].tokenData);}
#line 2057 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 98:
#line 302 "parser.y" /* yacc.c:1646  */
    {(yyvsp[0].tokenData)->tokenclass = SIZEOF; (yyval.tokenData) = (yyvsp[0].tokenData);}
#line 2063 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 99:
#line 303 "parser.y" /* yacc.c:1646  */
    {(yyval.tokenData) = (yyvsp[0].tokenData);}
#line 2069 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 100:
#line 306 "parser.y" /* yacc.c:1646  */
    {(yyval.tree) = (yyvsp[0].tree);}
#line 2075 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 101:
#line 307 "parser.y" /* yacc.c:1646  */
    {(yyval.tree) =(yyvsp[0].tree);}
#line 2081 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 102:
#line 310 "parser.y" /* yacc.c:1646  */
    {(yyval.tree) = newExpNode(IdK, (yyvsp[0].tokenData)); 
                                 (yyval.tree)->attr.name = (yyvsp[0].tokenData)->svalue; 
                                 (yyval.tree)->isArray = false; }
#line 2089 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 103:
#line 313 "parser.y" /* yacc.c:1646  */
    {(yyval.tree) = newExpNode(OpK, (yyvsp[-2].tokenData), NULL, (yyvsp[-1].tree));
                                 (yyval.tree)->child[0] = newExpNode(IdK,(yyvsp[-3].tokenData));
                                 (yyval.tree)->child[0]->attr.name = (yyvsp[-3].tokenData)->svalue; 
                                 (yyval.tree)->isArray = false;
			     
				}
#line 2100 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 104:
#line 321 "parser.y" /* yacc.c:1646  */
    {(yyval.tree) = (yyvsp[-1].tree);}
#line 2106 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 105:
#line 322 "parser.y" /* yacc.c:1646  */
    {(yyval.tree) = (yyvsp[0].tree);}
#line 2112 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 106:
#line 323 "parser.y" /* yacc.c:1646  */
    {(yyval.tree) = (yyvsp[0].tree);}
#line 2118 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 107:
#line 326 "parser.y" /* yacc.c:1646  */
    {(yyval.tree) = newExpNode(CallK, (yyvsp[-3].tokenData), (yyvsp[-1].tree)); (yyval.tree)->attr.name = (yyvsp[-3].tokenData)->svalue;}
#line 2124 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 108:
#line 329 "parser.y" /* yacc.c:1646  */
    {(yyval.tree) = (yyvsp[0].tree);}
#line 2130 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 109:
#line 330 "parser.y" /* yacc.c:1646  */
    {(yyval.tree) = NULL;}
#line 2136 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 110:
#line 333 "parser.y" /* yacc.c:1646  */
    {(yyval.tree) = addSibling((yyvsp[-2].tree), (yyvsp[0].tree));}
#line 2142 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 111:
#line 334 "parser.y" /* yacc.c:1646  */
    {(yyval.tree) = (yyvsp[0].tree);}
#line 2148 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 112:
#line 337 "parser.y" /* yacc.c:1646  */
    { (yyval.tree) = newExpNode(ConstantK, (yyvsp[0].tokenData)); 
                           (yyval.tree)->attr.value = (yyvsp[0].tokenData)->nvalue;
                           (yyval.tree)->type = Integer; 
                           (yyval.tree)->isArray = false;
                           (yyval.tree)->size = 1;}
#line 2158 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 113:
#line 342 "parser.y" /* yacc.c:1646  */
    {(yyval.tree) = newExpNode(ConstantK, (yyvsp[0].tokenData)); 
                           (yyval.tree)->attr.cvalue = (yyvsp[0].tokenData)->cvalue;
                           (yyval.tree)->type = Char; 
                           (yyval.tree)->isArray = false;
                           (yyval.tree)->size = 1;}
#line 2168 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 114:
#line 347 "parser.y" /* yacc.c:1646  */
    {(yyval.tree) = newExpNode(ConstantK, (yyvsp[0].tokenData)); 
                           (yyval.tree)->attr.string = (yyvsp[0].tokenData)->svalue;
                           (yyval.tree)->type = Char; 
                           (yyval.tree)->isArray = true;
                           (yyval.tree)->size = (yyvsp[0].tokenData)->nvalue+1;/* this is probably wrong*/}
#line 2178 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 115:
#line 352 "parser.y" /* yacc.c:1646  */
    {(yyval.tree) = newExpNode(ConstantK, (yyvsp[0].tokenData)); 
                           (yyval.tree)->attr.value = (yyvsp[0].tokenData)->nvalue;
                           (yyval.tree)->type = Boolean; 
                           (yyval.tree)->isArray = false;
                           (yyval.tree)->size = 1;}
#line 2188 "parser.tab.c" /* yacc.c:1646  */
    break;


#line 2192 "parser.tab.c" /* yacc.c:1646  */
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

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

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


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


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
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp);
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
#line 359 "parser.y" /* yacc.c:1906  */

void yyerror (const char *msg)
{ 
   cout << "Error: " <<  msg << endl;
}

char *largerTokens[LASTTERM+1];
void initTokenStrings() 
{
   //const char* defaultMessage = "Unknown (or more likely unimplemented) largerTokens"; 
   //for (int q = 0; q < 512; q++) 
   //{
     //largerTokens[q] = (char*)defaultMessage; 
   //}
   largerTokens[ADDASS] = (char *)"+=";
   largerTokens[AND] = (char *)"and";
   largerTokens[BOOL] = (char *)"bool";
   largerTokens[BOOLCONST] = (char *)"boolconst";
   largerTokens[BREAK] = (char *)"break";
   largerTokens[BY] = (char *)"by";
   largerTokens[CHAR] = (char *)"char";
   largerTokens[CHARCONST] = (char *)"charconst";
   largerTokens[CHSIGN] = (char *)"chsign";
   largerTokens[DEC] = (char *)"--";
   largerTokens[DIVASS] = (char *)"/=";
   largerTokens[DO] = (char *)"do";
   largerTokens[ELSE] = (char *)"else";
   largerTokens[EQ] = (char *)"==";
   largerTokens[FOR] = (char *)"for";
   largerTokens[GEQ] = (char *)">=";
   largerTokens[ID] = (char *)"id";
   largerTokens[IF] = (char *)"if";
   largerTokens[INC] = (char *)"++";
   largerTokens[INT] = (char *)"int";
   largerTokens[LEQ] = (char *)"<=";
   largerTokens[MAX] = (char *)":>:";
   largerTokens[MIN] = (char *)":<:";
   largerTokens[MULASS] = (char *)"*=";
   largerTokens[NEQ] = (char *)"!=";
   largerTokens[NOT] = (char *)"not";
   largerTokens[NUMCONST] = (char *)"numconst";
   largerTokens[OR] = (char *)"or";
   largerTokens[RETURN] = (char *)"return";
   largerTokens[SIZEOF] = (char *)"sizeof";
   largerTokens[STATIC] = (char *)"static";
   largerTokens[STRINGCONST] = (char *)"stringconst";
   largerTokens[SUBASS] = (char *)"-=";
   largerTokens[THEN] = (char *)"then";
   largerTokens[TO] = (char *)"to";
   largerTokens[WHILE] = (char *)"while";
   largerTokens[LASTTERM] = (char *)"lastterm";
}

static char tokenBuffer[16];
char *tokenToStr(int type)
{
    if (type > LASTTERM) {
      //////////////
    // printf("int %d char %c lastterm %d\n", type,type, LASTTERM);
      return (char *)"UNKNOWN";
    }
    else if (type > 256) {
      return largerTokens[type];
    }
    else if ((type < 32) || (type > 127)) {
      sprintf(tokenBuffer, "Token#%d", type);
    } else {
      tokenBuffer[0] = type;
      tokenBuffer[1] = '\0';
    }
    return tokenBuffer;
}

int main(int argc, char **argv) {
   //yylval.tokenData->linenum = 1;
   initTokenStrings(); 
  yylval.tokenData = (TokenData*)malloc(sizeof(TokenData));
   yylval.tree = (TreeNode*)malloc(sizeof(TreeNode));
     
   numErrors = 0; 
   numWarnings = 0; 
   int index;
   char *file = NULL;
   bool dotAST = false;             // make dot file of AST
   extern FILE *yyin;

   int globalOffset = 0;
   
   int ch;
   while ((ch = getopt(argc, argv, "d")) != -1) {
      switch (ch) {
         case 'd':
                 dotAST = true;
                 break;
         case '?':
         default:
                 //usage();
               ;
      }
   }
   if ( optind == argc ) yyparse();
   for (index = optind; index < argc; index++)
   {
      yyin = fopen (argv[index], "r");
      yyparse();
      fclose (yyin);
   }

      

   if (numErrors==0) {
      //set up symboltable
      SymbolTable *symtab;
      symtab = new SymbolTable();
      symtab->debug(false);
      
      syntaxTree = semanticAnalysis(syntaxTree, true, false, symtab, globalOffset);
      codegen(stdout,strdup(argv[1]) ,syntaxTree, symtab, globalOffset, false);
	//printTree(stdout, syntaxTree, true, true);

      if(dotAST) {
         printDotTree(stdout, syntaxTree, true, false);
      }
   }
   else {
      printf("-----------\n");
      printf("Errors: %d\n", numErrors);
      printf("-----------\n");
   }
   printf("Number of warnings: %d\n", numWarnings);
   printf("Number of errors: %d\n", numErrors);
   return 0;
}

