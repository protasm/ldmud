/* A Bison parser, made by GNU Bison 3.7.4.  */

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

#ifndef YY_YY_LANG_H_INCLUDED
# define YY_YY_LANG_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
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
    L_ARROW = 258,                 /* L_ARROW  */
    L_ASSIGN = 259,                /* L_ASSIGN  */
    L_ASYNC = 260,                 /* L_ASYNC  */
    L_AWAIT = 261,                 /* L_AWAIT  */
    L_BEGIN_INLINE = 262,          /* L_BEGIN_INLINE  */
    L_BREAK = 263,                 /* L_BREAK  */
    L_BYTES = 264,                 /* L_BYTES  */
    L_BYTES_DECL = 265,            /* L_BYTES_DECL  */
    L_CASE = 266,                  /* L_CASE  */
    L_CATCH = 267,                 /* L_CATCH  */
    L_CLOSURE = 268,               /* L_CLOSURE  */
    L_CLOSURE_DECL = 269,          /* L_CLOSURE_DECL  */
    L_COLON_COLON = 270,           /* L_COLON_COLON  */
    L_CONTINUE = 271,              /* L_CONTINUE  */
    L_COROUTINE = 272,             /* L_COROUTINE  */
    L_DEC = 273,                   /* L_DEC  */
    L_DECLTYPE = 274,              /* L_DECLTYPE  */
    L_DEFAULT = 275,               /* L_DEFAULT  */
    L_DEPRECATED = 276,            /* L_DEPRECATED  */
    L_DO = 277,                    /* L_DO  */
    L_DUMMY = 278,                 /* L_DUMMY  */
    L_ELLIPSIS = 279,              /* L_ELLIPSIS  */
    L_ELSE = 280,                  /* L_ELSE  */
    L_END_INLINE = 281,            /* L_END_INLINE  */
    L_EQ = 282,                    /* L_EQ  */
    L_EOF = 283,                   /* L_EOF  */
    L_FLOAT = 284,                 /* L_FLOAT  */
    L_FLOAT_DECL = 285,            /* L_FLOAT_DECL  */
    L_FOR = 286,                   /* L_FOR  */
    L_FOREACH = 287,               /* L_FOREACH  */
    L_FUNC = 288,                  /* L_FUNC  */
    L_GE = 289,                    /* L_GE  */
    L_IDENTIFIER = 290,            /* L_IDENTIFIER  */
    L_IF = 291,                    /* L_IF  */
    L_ILLEGAL_CHAR = 292,          /* L_ILLEGAL_CHAR  */
    L_INC = 293,                   /* L_INC  */
    L_INHERIT = 294,               /* L_INHERIT  */
    L_INT = 295,                   /* L_INT  */
    L_LAMBDA_CLOSURE_VALUE = 296,  /* L_LAMBDA_CLOSURE_VALUE  */
    L_LAND = 297,                  /* L_LAND  */
    L_LE = 298,                    /* L_LE  */
    L_LOR = 299,                   /* L_LOR  */
    L_LPCTYPE = 300,               /* L_LPCTYPE  */
    L_LSH = 301,                   /* L_LSH  */
    L_LWOBJECT = 302,              /* L_LWOBJECT  */
    L_MAPPING = 303,               /* L_MAPPING  */
    L_MIXED = 304,                 /* L_MIXED  */
    L_NE = 305,                    /* L_NE  */
    L_NO_MASK = 306,               /* L_NO_MASK  */
    L_NOSAVE = 307,                /* L_NOSAVE  */
    L_NOT = 308,                   /* L_NOT  */
    L_NUMBER = 309,                /* L_NUMBER  */
    L_OBJECT = 310,                /* L_OBJECT  */
    L_PRIVATE = 311,               /* L_PRIVATE  */
    L_PROTECTED = 312,             /* L_PROTECTED  */
    L_PUBLIC = 313,                /* L_PUBLIC  */
    L_QUOTED_AGGREGATE = 314,      /* L_QUOTED_AGGREGATE  */
    L_RANGE = 315,                 /* L_RANGE  */
    L_RETURN = 316,                /* L_RETURN  */
    L_RSH = 317,                   /* L_RSH  */
    L_RSHL = 318,                  /* L_RSHL  */
    L_SIMUL_EFUN_CLOSURE = 319,    /* L_SIMUL_EFUN_CLOSURE  */
    L_START_BLOCK = 320,           /* L_START_BLOCK  */
    L_START_BLOCK_END_DETECTION = 321, /* L_START_BLOCK_END_DETECTION  */
    L_START_EXPR = 322,            /* L_START_EXPR  */
    L_START_EXPR_END_DETECTION = 323, /* L_START_EXPR_END_DETECTION  */
    L_START_PROG = 324,            /* L_START_PROG  */
    L_STATIC = 325,                /* L_STATIC  */
    L_STATUS = 326,                /* L_STATUS  */
    L_STRING = 327,                /* L_STRING  */
    L_STRING_DECL = 328,           /* L_STRING_DECL  */
    L_STRUCT = 329,                /* L_STRUCT  */
    L_SWITCH = 330,                /* L_SWITCH  */
    L_SYMBOL = 331,                /* L_SYMBOL  */
    L_SYMBOL_DECL = 332,           /* L_SYMBOL_DECL  */
    L_VARARGS = 333,               /* L_VARARGS  */
    L_VIRTUAL = 334,               /* L_VIRTUAL  */
    L_VISIBLE = 335,               /* L_VISIBLE  */
    L_VOID = 336,                  /* L_VOID  */
    L_WHILE = 337,                 /* L_WHILE  */
    L_YIELD = 338,                 /* L_YIELD  */
    LOWER_THAN_ELSE = 339          /* LOWER_THAN_ELSE  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 9157 "prolang.y"

#line 9159 "prolang.y"
    p_int number;
      /* Literal numbers, or whereever a number is required.
       */

    double float_number;
      /* Literal floats */

    struct {
        p_int number;
        unsigned short inhIndex;
    } closure;
      /* A closure (#'xxx). The .number determines the exact
       * nature of the closure.
       * For lfun closures, an inhIndex > 0 determines the
       * (inheritance index + 1) of a direct reference to an
       * inherited closure.
       */

    struct {
        string_t *name;  /* The tabled string with the name */
        int   quotes;    /* Number of quotes */
    } symbol;
      /* A literal symbol.
       */

    ident_t *ident;
      /* L_IDENTIFIER: The recognized identifier
       */

    typeflags_t typeflags;
      /* Just the typeflags (reference, pointer, visibility).
       */

    fulltype_t fulltype;
      /* The fulltype (datatype plus visibility) of entities.
       */

    lpctype_t *lpctype;
      /* An LPC type without modifiers.
       */

    struct
#line 9201 "prolang.y"
    {
        funflag_t funmod;       /* Function inheritance modifiers. */
        funflag_t varmod;       /* Variable inheritance modifiers. */
        funflag_t structmod;    /* Struct inheritance modifiers.   */
    } inh_flags;

    svalue_t *initialized;
      /* Position where to store the variable initializer.
       */

    p_int numbers[2];
      /* Often used to save the current break/continue address.
       */

    p_uint address;
      /* Address of an instruction. */

    struct statement_s statement;
      /* Information about a statement or block of statements.
       */

    struct
#line 9223 "prolang.y"
    {
        struct statement_s statements;
        bool has_default;
    } switch_block;
      /* Information about a switch label and its statements.
       */

    struct
#line 9231 "prolang.y"
    {
        p_uint address;          /* Address of the code for the else block. */
        struct statement_s statements; /* Information about the statements. */
    } else_block;
      /* Information about an else block.
       */

    struct
#line 9239 "prolang.y"
    {
        struct statement_s statements; /* Information about the statements. */
        p_uint address;                /* Starting address. */
        bool has_code;                 /* false for a declaration. */
    } function_block;
      /* Information about a function body.
       */

    struct {
        bytecode_p     p;       /* The condition code */
        unsigned short length;  /* Length of the condition code */
        unsigned short line;    /* Last source line of the condition code */
    } expression;
      /* Expressions are used to save the code for a loop-condition
       * while the body is compiled.
       */

    struct rvalue_s
#line 9257 "prolang.y"
    {
        ident_t *  name;   /* A corresponding variable to be marked. */
        fulltype_t type;   /* Type of the expression */
        uint32     start;  /* Startaddress of the expression */
        bool       needs_use; /* Warn, when not used. */
    } rvalue;
      /* Just a simple expression. */

    struct lrvalue_s
#line 9266 "prolang.y"
    {
        ident_t *      name;     /* A corresponding variable to be marked. */
        fulltype_t     type;     /* Type of the expression */
        uint32         start;    /* Startaddress of the instruction */
        bool           needs_use;/* Warn, when not used. */
        lvalue_block_t lvalue;   /* Code of the expression as an lvalue */
    }
    lrvalue;
      /* Used for expressions which may return a rvalue or lvalues.
       * This happens when this expression is followed by an
       * index or range expression to yield an lvalue.
       * Then the indexed expression should be converted to an lvalue, too.
       * (Because for strings, the string itself must be replaced,
       * when a single character changes. For arrays and strings
       * an assignment to a range expression might replace the whole
       * array/string.)
       *
       * Lvalue generation in places where either a r- or an lvalue
       * is acceptible first generates the rvalue code, but stores
       * the entire code for the lvalue generation in the LVALUE_BLOCK.
       * .lvalue contains the pointers therein.
       *
       * If .lvalue.size == 0, then the expression cannot be an lvalue.
       */

    struct
#line 9292 "prolang.y"
    {
        fulltype_t type;         /* Type of the expression         */
        uint32     start;        /* Startaddress of the expression */
        bool       might_lvalue; /* Might be an lvalue reference.  */
        bool       needs_use;    /* Warn, when not used.           */
    } function_call_result;
      /* A function call expression. */

    struct incdec_s
#line 9301 "prolang.y"
    {
        uint32     start;  /* Current programm pointer */
        short      code;   /* The opcode (F_PRE_INC or F_PRE_DEC) */
    }
    incdec;
      /* For pre-increment or -decrement remembers which opcode to use,
       * because it must be issued after the following expression has
       * been compiled.
       */

    struct s_index
#line 9312 "prolang.y"
    {
        short      rvalue_inst;  /* Index opcode for rvalues */
        short      lvalue_inst;  /* Index opcode for lvalues */
        short      vlvalue_inst; /* Index opcode for reseating lvalues
                                    This is not used for ranges. */
        uint32     start;        /* Startaddress of the index */
        uint32     end;          /* Endaddress+1 of the index */
        fulltype_t type1;        /* Type of index, resp. lower bound */
        fulltype_t type2;        /* Type of other index, resp. upper bound */
    }
    index;
      /* This is used to parse and return the indexing operation
       * of an array or mapping.
       * .rvalue_inst gives the type of the operation:
       *   F_INDEX:     [x]
       *   F_RINDEX:    [<x]
       *   F_AINDEX:    [>x]
       *   F_RANGE:     [ x.. y]
       *   F_RN_RANGE:  [<x.. y]
       *   F_NR_RANGE:  [ x..<y]
       *   F_RR_RANGE:  [<x..<y]
       *   F_AN_RANGE:  [>x.. y]
       *   F_AR_RANGE:  [>x..<y]
       *   F_NA_RANGE:  [ x..>y]
       *   F_RA_RANGE:  [<x..>y]
       *   F_AA_RANGE:  [>x..>y]
       *   F_NX_RANGE:  [ x..  ]
       *   F_RX_RANGE:  [<x..  ]
       *   F_AX_RANGE:  [>x..  ]
       * .lvalue_inst contains the corresponding opcode for
       * lvalue generation.
       * .start and .end are the bytecode limits of the whole
       * operation.
       * .type1 and optionally .type2 are the types of the
       * index values.
       */

    struct lvalue_s {
        lpctype_t *    type;
        ident_t *      name;
        lvalue_block_t lvalue;
        short          vlvalue_inst;
        short          num_arg;
    } lvalue;
      /* Used in assigns to communicate how an lvalue has to be accessed
       * (by passing on the bytecode to create) and what type it is.
       *
       * An lvalue expression is not put directly in the program code,
       * because it will be evaluated after the right hand side of the
       * assignment (eg. a = b = c; will be evaluated from right to
       * left). The compiled bytecodes for the lvalue are stored in the
       * LVALUE_BLOCK and should be freed using free_lvalue_block().
       *
       * If this lvalue expression can be used for reseating assignments,
       * then vlvalue_inst (if != 0) will contain the instruction that
       * must replace the last instruction in the lvalue block.
       * (The last instruction will have .num_arg bytes following it.)
       *
       * If the lvalue directly refers to a variable, name points to
       * the identifier, otherwise it's NULL.
       */

    struct {
        p_int key;     /* shared string ptr, or a number */
        Bool numeric;  /* TRUE: .key is a number */
    } case_label;
      /* Used to return the value of a 'case' label.
       */

    struct
#line 9382 "prolang.y"
    {
        unsigned short num_vars; /* Number of lvalues in foreach clause. */
        unsigned short type_idx; /* Index into A_ARGUMENT_TYPES of the first variable. */
    } foreach_variables;
      /* Used for the lvalue declaration in a foreach clause. */

    struct
#line 9389 "prolang.y"
    {
        lpctype_t* expr_type; /* Type of the expression.       */
        enum
#line 9392 "prolang.y"
        {
            FOREACH_LOOP,     /* Normal foreach loop value     */
            FOREACH_REF,      /* Referenced foreach loop value */
            FOREACH_RANGE     /* Integer range as loop value   */
        } foreach_type;
    } foreach_expression;
      /* Used for the expressions to iterate over in a foreach clause. */

    char *string;
      /* An allocated string */

    string_t *sh_string;
      /* A shared string */

    struct {
        char    *super; /* NULL, or the allocated qualifier */
        ident_t *real;  /* The function identifier */
    } function_name;
      /* A qualified function name: "<super>::<func>" */

    struct {
        int    simul_efun;    /* -1, or index of the simul_efun */
        p_int  start;         /* Address of the function call */
        efun_override_t efun_override; /* set on (s)efun:: prefix. */
    } function_call_head;
      /* Used to save address and possible sefun-index over
       * the argument parsing in a function call.
       */

    struct
#line 9422 "prolang.y"
    {
        ident_t *name;           /* Identifier for argument. */
        uint32   default_expr;   /* Startaddress of the expression for the
                                  * default value (or UINT32_MAX if none).
                                  */
    } function_argument;
      /* A single formal argument of a function.
       */

    struct
#line 9432 "prolang.y"
    {
        p_int start;          /* Starting position in A_DEFAULT_VALUES. */
        short num;            /* Number of arguments. */
        short num_opt;        /* Number of arguments with default values. */
    } function_arguments;
      /* Keeps track of formal arguments of a function.
       */

    struct {
        efun_override_t override; /* Qualifier for name lookup. */
        ident_t *real;            /* The struct identifier */
    } struct_name;
      /* A qualified struct name: "<super>::<name>" */

    struct {
        int length;            /* Number of initializers parsed */
        /* Description of initializers parsed: */
        struct struct_init_s * list;  /* Head of list */
        struct struct_init_s * last;  /* Tail of list */
    } struct_init_list;
      /* For runtime struct literals: head of the list describing
       * the encountered member initializers.
       */

    struct {
        string_t * name;  /* Member name, or NULL if unnamed */
        fulltype_t type;  /* Member expr type */
    } struct_init_member;
      /* For runtime struct literals: information about a single
       * member initializer.
       */

    struct
#line 9465 "prolang.y"
    {
        bool strict_member; /* true, if we have ob.fun(),
                             * false for ob->fun().
                             */
    } struct_member_operator;


#line 479 "lang.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
typedef code_location_t YYLTYPE;


extern YYSTYPE yylval;
extern YYLTYPE yylloc;
int yyparse (void);

#endif /* !YY_YY_LANG_H_INCLUDED  */
