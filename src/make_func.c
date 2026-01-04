/* A Bison parser, made by GNU Bison 3.7.4.  */

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

/* Identify Bison output, and Bison version.  */
#define YYBISON 30704

/* Bison version string.  */
#define YYBISON_VERSION "3.7.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "make_func.y"

/*---------------------------------------------------------------------------
 * make_func: Generation of the parser description and other tables
 *
 *---------------------------------------------------------------------------
 * make_func is an essential part of build process, as it creates the
 * actual LPC compiler description from a template, as well as some
 * internal tables from a list of code and efun specs.
 *
 * make_func takes one commandline argument which determines what it
 * should create:
 *
 *   make_func instrs
 *     creates efun_defs.c and instrs.h, reads machine.h, config.h and func_spec.
 *
 *   make_func lang
 *     creates lang.y from prolang.y, reads machine.h and config.h.
 *
 *   make_func strings
 *     creates stdstrings.[ch], reads machine.h, config.h and string_spec.
 *
 *   make_func structs
 *     creates stdstructs.[ch], reads machine.h, config.h and struct_spec.
 *
 * The calls are described in detail below.
 *---------------------------------------------------------------------------
 * make_func instrs
 * ----------------
 *
 * make_func reads the specifications of all interpreter bytecodes from
 * the file func_spec and creates the source files needed to compile
 * the driver.
 *
 * The bytecodes both cover interpreter internal instructions as well
 * as efuns. A complication is that every bytecode can occupy only one
 * byte, but there are more than 256 codes and functions. This is solved
 * by the use of multi-byte instructions, where the first byte is
 * one of a set of prefix bytes, followed by the instruction's opcode
 * byte. The prefix bytes divide the instructions into several classes:
 * efuns with no argument, efuns with one argument, etc. The translation
 * from instruction code to prefix/opcode is written down in the
 * instrs[] table created by make_func.
 *
 * The instructions and their prefix/opcode encodings follow the
 * following rules:
 *   - all non-efun instructions do not need a prefix byte and start
 *     at instruction code 0.
 *   - the instruction codes for the tabled efuns are consecutive
 *   - the instruction codes for all tabled varargs efuns are consecutive.
 *
 * When make_func is run, it first reads the files 'machine.h' and
 * 'config.h' to determine which defines are used in the compilation of the
 * driver. For this make_func implements a simple C preprocessor, capable
 * of numeric expressions and simple macro expansions (no function macros),
 * which also allows the use of C-like block comments. With the knowledge
 * of the defines, make_func then reads the file 'func_spec' with the
 * information about the codes and efuns.
 *
 * From this information, make_func generates these files:
 *   efun_defs.c
 *     This file contains the table of all instructions, instrs[].
 *     The table defines for every machine instruction if it is an
 *     internal code or efun, what arguments of what type it takes, etc.
 *     The file also contains the tables for the driver-specific ctype
 *     implementation.
 *     It is included into the lexer lex.c and compiled there.
 *
 *  instrs.h
 *     This file defines the bytecodes representing all the efuns
 *     and non-efun instructions which are not compiler tokens.
 *
 *
 * func_spec is divided into several sections, each introduced with its
 * own %-keyword. The required order and meaning of the sections is this:
 *
 *     %codes
 *         Internal machine codes used by the compiler to generate code.
 *
 *     %efuns
 *         The efuns which are represented by one bytecode.
 *
 *     %tefuns
 *         The tabled efuns. make_func will sort the efuns into
 *         various classes depending on the number of arguments.
 *         Each class is assigned it's own 'efun<n>' prefix code, with
 *         <n> being the number of arguments. Efuns with a variable number
 *         or arguments will be prefixed by 'efunv'.
 *
 * The entries in the sections are separated by whitespace.
 *
 * A token or code entry follows this syntax:
 *
 *    [ "name" ] id [op-type]
 *
 *        <id> is the name used in the compiler source, the generated token
 *        will be called F_<ID>. If <name> is specified, it will be used
 *        in tracedumps instead of the plain <id>.
 *
 *        If the instruction is an operator which can be used as a efun
 *        closure (like +), the optional <op-type> specifies how many operands
 *        the operator takes. <op-type> must be one of the keywords 'unary',
 *        'binary', 'ternary' and 'quaternary'.
 *
 *
 * An efun is defined this way:
 *
 *    ret-type name [ alias ] ([argtype-1, ... , argtype-n]) [ "msg" ];
 *
 *        This is the efun <name>, with the compiler source name F_<NAME>,
 *        which returns a value of type <ret-type> and takes n >= 0
 *        arguments of type <argtype-x>. If <alias> is given, it must
 *        be the source name (F_FOO) of another efun this one is an
 *        alias for.
 *
 *        The types are given in the usual LPC syntax, with the additional
 *        type of 'unknown' for return types.
 *
 *        The return type can contain a  '&' to indicate, that it might
 *        put an lvalue reference on the stack.
 *
 *        Argument types can be the combination of several types in
 *        the form 'type|type|...', e.g. 'string|object'. If one of the
 *        types is 'void', the argument is optional (but then only optional
 *        arguments may follow).
 *
 *        The last argument can take a default value, which is then specified
 *        as 'default: F_FOO' with F_FOO being the source name of an efun
 *        yielding the desired value. Example:
 *            ..(object default: F_THIS_OBJECT)
 *
 *        Alternatively, the last argument can be given as '...' if the
 *        efun can handle arbitrarily many arguments. It can optionally
 *        take also a type definition (mixed ...) and/or lvalue specifier
 *        (&...).
 *
 *        If the efun is deprecated, <msg> is the warning message to
 *        print when the efun is used and pragma warn_deprecated is in
 *        effect. The message will be prefixed by the compiler
 *        with "<name> is deprecated: ".
 *
 *        The following types are recognized:
 *           void, int, string, object, mapping, float, closure, symbol
 *           quoted_array, mixed, null, unknown
 *        'null' is to be used as alternate type when the efun accepts
 *        the number 0 instead of the actual type.
 *---------------------------------------------------------------------------
 * make_func applied
 * ----------------
 *
 * make_func reads the specifications of all applied lfuns from the file
 * applied_spec and creates the file applied_decl.c needed to compile
 * the driver.
 *
 * Similar to 'make_func instr', it reads the files 'machine.h' and
 * 'config.h' to determine active defines. Then reads the file
 * 'applied_spec' to read the applied lfun specifications.
 *
 * applied_spec is divided into several sections, each introduced with its
 * own %-keyword. The required order and meaning of the sections is this:
 *
 *     %master
 *         Applied lfuns of the master object.
 *
 *     %regular
 *         Applied lfuns for regular objects.
 *
 *     %hooks
 *         Applied lfuns via driver hooks.
 *
 * Each section contains a list of function declarations. They follow this
 * syntax:
 *
 *    [visibility] [varargs] return-type lfun-or-hook-name
 *                                  (argtype-1, ..., argtype-n [, ...] ) ;
 *
 *---------------------------------------------------------------------------
 * make_func lang
 * --------------
 *
 * make_func implements a preprocessor used to generate the LPC compiler
 * lang.y from the file prolang.y . This step is necessary because
 * no known yacc allows to enable or disable rules conditinally.
 *
 * When make_func is run, it first reads the files 'machine.h' and
 * 'config.h' to determine which defines are used in the compilation of the
 * driver. For this make_func implements a simple C preprocessor, capable
 * of numeric expressions and simple macro expansions (no function macros),
 * which also allows the use of C-like block comments.
 *
 * From this information, make_func generates this file:
 *  lang.y
 *     This is the LPC compiler, which is created by reading and
 *     modifying the template prolang.y . During this process, these
 *     keywords are recognized and replaced:
 *       %line:  generates a #line statement to synchronize the C compiler.
 *       %typemap: generates a lookup table using types as indices
 *                 (see handle_map()).
 *       %hookmap: generates a lookup table using driverhooks as indices.
 *     In addition, the keywords %if, %elif, %else and %endif can be
 *     used in a preprocessor fashion to control which parts of prolang.y
 *     end up in lang.y and which don't.
 *---------------------------------------------------------------------------
 * make_func strings
 * -----------------
 *
 * make_func reads from the file string_spec the definition of all strings
 * which the driver shall predefine as shared strings. It creates the
 * source files stdstrings.[ch] with the implementation.
 *
 * The strings are mostly the names of lfuns called by the interpreter.
 * Predefining them as shared strings and using the resulting pointers
 * speeds up the function calls.
 *
 * string_spec is read line by line, each line defining one string:
 *
 *    id "string"
 *
 *    <id> is the symbolic name used in the compiler source, for the
 *    string <string>. The symbolic name will be made upper case and
 *    is used in two forms:
 *       STR_<id>: the pointer to the shared string
 *       SHX_<id>: the index of the shared string in the table of
 *                 all predefined strings.
 *---------------------------------------------------------------------------
 * make_func structs
 * -----------------
 *
 * make_func reads from the file struct_spec the definition of structs which
 * shall be globally available. It creates the source files stdstructs.[ch]
 * with the implementation.
 *
 * struct_spec is parsed as a list of struct declarations:
 *
 *    'struct' name
 *    {
 *        type member_name;
 *    };
 *
 *    <name> is the name this struct will have in LPC. In driver sources
 *    the definition get's the name 'struct_' + name. The corresponding
 *    LPC type object is named 'lpctype_struct_' + name.
 *
 * And that's it.
 *---------------------------------------------------------------------------
 */

#undef lint  /* undef so that precompiled headers can be used */

#include "driver.h"

#include "my-alloca.h"
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <fcntl.h>

#include "exec.h"
#include "hash.h"

#include "../mudlib/sys/driver_hook.h"

#define lint  /* redef again to prevent spurious warnings */

/* driver.h defines its own memory management functions,
 * which we don't need.
 */
#undef malloc
#undef realloc
#undef free

/*-------------------------------------------------------------------------*/

/* Filenames used by make_func */

#define FUNC_SPEC    "func_spec"
  /* The input file with the description of all machine instructions
   * and efuns.
   */

#define APPLIED_SPEC  "applied_spec"
  /* The input file with the definition of applied lfuns.
   */

#define STRING_SPEC  "string_spec"
  /* The input file with the definition of all standard
   * shared strings.
   */

#define STRUCT_SPEC  "struct_spec"
  /* The input file with the definition of all global structs.
   */

#define CONFIG       "config.h"
  /* The configuration file.
   */

#define FILE_MACHINE "machine.h"
  /* The machine configuration file.
   */

#define PRO_LANG     "prolang.y"
  /* The LPC parser template.
   */

#define THE_LANG     "lang.y"
  /* The LPC parser to generate.
   */

#define THE_INSTRS   "instrs.h"
  /* The instruction and ctype table declarations to generate.
   */

#define EFUN_DEFS    "efun_defs.c"
  /* The instruction and ctype table definitions to generate.
   */

#define APPLIED_DEFS "applied_decl.c"
  /* The applied lfun specification to generate.
   */

#define STDSTRINGS   "stdstrings"
  /* The basename (without extension) of the standard shared
   * string implementation files to generate.
   */

#define STDSTRUCTS   "stdstructs"
  /* The basename (without extension) of the standard global
   * struct implementation files to generate.
   */

/*-------------------------------------------------------------------------*/

#define MAKE_FUNC_MAXLINE    4096
  /* Maximum length of an input line and other buffers.
   */

#define MAX_FUNC      2048
#define MAX_TOKENS    2048
  /* Maximum number of functions and tokens we care to handle.
   */

#define MAX_ARGTYPES  1000
  /* Size of the arg_types[] array.
   */

#define MAX_STRUCTS    256
  /* Maximum number of structs.
   */

#define MAX_STRUCT_MEMBERS 256
  /* Maximum number of members per struct.
   */

#define MF_TYPE_MOD_POINTER         0x10000
#define MF_TYPE_MOD_POINTER_POINTER 0x20000
#define MF_TYPE_MOD_REFERENCE       0x40000
#define MF_TYPE_MOD_LVALUE          0x80000
  /* Type modifier for array and reference types.
   * These values are bitflags which are |'ed onto the type values
   * produced by the parser (INT, STRING, etc).
   */

/*-------------------------------------------------------------------------*/

#undef isalunum
#define isalunum(c) (isascii((unsigned char)c) && (isalnum((unsigned char)c) || (c) == '_'))

#define lexwhite(c) (isascii((unsigned char)c) && isspace((unsigned char)c) && (c) != '\n')

#undef lexdigit
#define lexdigit(c) (isascii((unsigned char)c) && isdigit((unsigned char)c))
  /* Our own char classification predicates.
   */

#define NELEMS(arr)    (sizeof arr / sizeof arr[0])
  /* Handy macro to statically determine the number of elements in
   * an array.
   */

/*-------------------------------------------------------------------------*/

typedef struct
{
    int token;                  /* The type token.           */
    int flags;                  /* MF_TYPE_MOD_* flags.      */
    char* struct_name;          /* If id == STRUCT the name. */
} lpc_type_t;

/*-------------------------------------------------------------------------*/

/* Parsed functions and instructions are put into different classes.
 * These are the class type definitions and associated predicate macros.
 */

enum ClassCodes {
    C_CODE  = 0  /* Internal machine instructions */
  , C_EFUN       /* Efuns with own instruction codes */
  , C_EFUN0      /* Tabled efuns with 0 arguments */
  , C_EFUN1      /* Tabled efuns with 1 argument */
  , C_EFUN2      /* Tabled efuns with 2 argument */
  , C_EFUN3      /* Tabled efuns with 3 argument */
  , C_EFUN4      /* Tabled efuns with 4 argument */
  , C_EFUNV      /* Tabled efuns with more than 4 or variable arguments */
  , C_ALIAS      /* Aliased efuns. This must come right after
                  * the last C_EFUN*.
                  */
  , C_SEFUN      /* Virtual class used by the lexer when parsing
                  * the classes C_EFUN*.
                  */
  , C_TOTAL      /* Number of different classes */
};

#define C_IS_CODE(x) \
 ((x) == C_CODE)
#define C_IS_EFUN(x) \
 ((x) != C_CODE && (x) != C_ALIAS)

/*-------------------------------------------------------------------------*/

static char * classtag[]
 = { /* C_CODE */ "CODE"
   , /* C_EFUN */ "EFUN"
   , /* C_EFUN0 */ "EFUN0"
   , /* C_EFUN1 */ "EFUN1"
   , /* C_EFUN2 */ "EFUN2"
   , /* C_EFUN3 */ "EFUN3"
   , /* C_EFUN4 */ "EFUN4"
   , /* C_EFUNV */ "EFUNV"
   };
  /* Tag names of the code classes, used to create the '<class>_OFFSET'
   * values in efun_defs.c:instrs[].
   */

static char * classprefix[]
 = { /* C_CODE */ "0"
   , /* C_EFUN */ "0"
   , /* C_EFUN0 */ "F_EFUN0"
   , /* C_EFUN1 */ "F_EFUN1"
   , /* C_EFUN2 */ "F_EFUN2"
   , /* C_EFUN3 */ "F_EFUN3"
   , /* C_EFUN4 */ "F_EFUN4"
   , /* C_EFUNV */ "F_EFUNV"
   };
  /* Instruction names of the prefixes used for the various code classes.
   */

static int num_buff = 0;
  /* Total number of instructions encountered so far.
   */

static int num_instr[C_TOTAL];
  /* Number of instructions encountered, counted separately for
   * every type.
   */

static int instr_offset[C_TOTAL];
  /* Derived from num_instrs, the offset of the instruction classes
   * within the whole table.
   */

struct instrdata_s {
    char *f_name;      /* 'F-'-name of code/efun */
    char *key;         /* internal name of code/efun */
    char *buf;         /* instrs[] entry for code/efun */
    int   code_class;  /* code class of code/efun */
} instr[MAX_FUNC];
  /* Array describing all codes and efuns encountered in FUNC_SPEC.
   * The array is built in the order found in func_spec and later
   * sorted by code_class and key.
   *
   * Also used to hold all string definitions found in STRING_SPEC:
   *   .key is (in upper case) the symbolic name of the string;
   *   .buf is the actual string text.
   */

static lpc_type_t arg_types[MAX_ARGTYPES];
  /* All distinct function argument signatures encountered so far.
   * One signature is simply a list of all argument types, identified
   * by the starting index of the first argument's type.
   * The description of one argument's type is itself a list of the
   * typecodes, terminated by 0.
   * Different signatures may overlap, e.g. a (STRING) signature
   * could be embedded in a (POINTER, STRING) signature.
   *
   * The content of this array is later written as efun_arg_types[]
   * into EFUN_DEFS and indexed by the instrs[].arg_index entries.
   */

static long lpc_types[MAX_ARGTYPES];
  /* The table of distinct function argument signatures again, this
   * time expressed in svalue runtime types.
   * One signature is a list of all arguments' types, identified
   * by the starting index of the first argument's type. The length
   * of the signature is stored in the instr structure for the function.
   * The description of one argument's type is a bitword, where
   * a 1 is set when the associated type is accepted.
   * For example, if an argument can be string or object, the
   * word in the table is set to (1<<T_STRING)|(1<<T_OBJECT).
   *
   * The content of this array is later written as efun_lpc_types[]
   * into EFUN_DEFS and indexed by the instrs[].lpc_arg_index entries.
   *
   * The recognized bitflags are:
   */

#    define LPC_T_ANY           (1 << 0)
#    define LPC_T_LVALUE        (1 << 1)
#    define LPC_T_POINTER       (1 << 2)
#    define LPC_T_NUMBER        (1 << 3)
#    define LPC_T_OBJECT        (1 << 4)
#    define LPC_T_STRING        (1 << 5)
#    define LPC_T_MAPPING       (1 << 6)
#    define LPC_T_FLOAT         (1 << 7)
#    define LPC_T_CLOSURE       (1 << 8)
#    define LPC_T_SYMBOL        (1 << 9)
#    define LPC_T_QUOTED_ARRAY  (1 << 10)
#    define LPC_T_STRUCT        (1 << 11)
#    define LPC_T_NULL          (1 << 12)
#    define LPC_T_BYTES         (1 << 13)
#    define LPC_T_LWOBJECT      (1 << 14)
#    define LPC_T_COROUTINE     (1 << 15)
#    define LPC_T_LPCTYPE       (1 << 16)


static int last_current_type = 0;
  /* Index of the first unused entry in arg_types[].
   */

static int last_current_lpc_type = 0;
  /* Index of the first unused entry in lpc_types[].
   */

/*-------------------------------------------------------------------------*/

/* Variables used when parsing the lines of FUNC_SPEC */

static int got_error = 0;
  /* Set to TRUE if an error was found.
   */

static int min_arg = -1;
  /* Minimum number of arguments for this function if there
   * are optional arguments, or -1 if all arguments are needed.
   */

static Bool unlimit_max = MY_FALSE;
  /* True when the last argument for a function is the '...'
   */

static int current_code_class;
  /* The current code class (C_CODE, C_EFUN, ...) a parsed identifier
   * shall be assigned to.
   */

static lpc_type_t curr_arg_types[MAX_LOCAL];
  /* The function argument signature of the current function.
   * The signature is a list of all argument types, which themselves
   * are lists of typecodes, each argument's list terminated by 0.
   */

static int curr_lpc_types[MAX_LOCAL];
  /* The function argument signature of the current function expressed
   * in svalue types.
   * The signature is a list of all argument's types, each a word
   * denoting by set bits which bytes are accepted.
   */

static int curr_arg_type_size = 0;
  /* Index of the first unused entry in curr_arg_types[].
   */

static int curr_lpc_type_size = 0;
  /* Index of the first unused entry in curr_lpc_types[].
   */

/*-------------------------------------------------------------------------*/

/* Variables used when parsing the lines of APPLIED_SPEC */

static char* master_decl_line[MAX_FUNC];
static char* regular_decl_line[MAX_FUNC];
static char* hook_decl_line[MAX_FUNC];
    /* One entry already formatted as a applied_decl_t initializer.
     */

static int master_decl_num;
static int regular_decl_num;
static int hook_decl_num;
    /* Number of entries for each category.
     */

static char** next_decl_line = NULL;
    /* Next entry to be filled.
     */

static int* current_decl_num = NULL;
    /* Points to the number of the current category.
     */

static bool current_decl_is_hook = false;
    /* True, when we are parsing driver hooks.
     */

static const char* current_default_visibility_name = NULL;
static const char* current_default_visibility_flags = NULL;
    /* The default visibility in the current category.
     */

/*-------------------------------------------------------------------------*/

/* Variables used when parsing the lines of STRUCT_SPEC */

static char* struct_names[MAX_STRUCTS];
    /* Just the names of defined structs.
     */

static char* struct_defs[MAX_STRUCTS];
    /* The full definition for a struct.
     */

static char* struct_enums[MAX_STRUCTS];
    /* Enum definition for a struct.
     */

static lpc_type_t struct_member_types[MAX_STRUCT_MEMBERS];
    /* Member type for the current parsed struct.
     */

static char* struct_member_names[MAX_STRUCT_MEMBERS];
    /* Member name for the current parsed struct.
     */

static int current_struct;
    /* Index of currently parsed struct.
     * (And at the end the number of parsed structs.)
     */

static int current_struct_member;
    /* Index of currently parsed member.
     * (And at the end the number of parsed members.)
     */

/*-------------------------------------------------------------------------*/

/* Forward declarations */

static void yyerror(const char *) NORETURN;
static int yylex(void);
int yyparse(void);
int ungetc(int c, FILE *f);
static INLINE const char *type_str(int);
static long type2flag (lpc_type_t t);
static const char *etype(long);
static const char *lpctypestr(lpc_type_t t);
#ifndef toupper
int toupper(int);
#endif
static void fatal(const char *str) NORETURN;
static int cond_get_exp(int);

/*-------------------------------------------------------------------------*/
static char *
mystrdup (const char *str)

/* Copy <str> into a freshly allocated memory block and return that one.
 *
 * This function is needed on Ultrix 4.2 which doesn't seem to know strdup().
 */

{
    char *copy = malloc(strlen(str)+1);
    if (!copy)
        fatal("strdup failed\n");
    strcpy(copy, str);
    return copy;
}

/*-------------------------------------------------------------------------*/
static void
fatal (const char *str)

/* Print <str> on stderr, flush stdout and exit the program with
 * exitcode 1.
 */

{
    fprintf(stderr, "%s", str);
    fflush(stdout);
    exit(1);
}

/*-------------------------------------------------------------------------*/
static void
make_upper_case (char *str)

/* Change all letters in str to upper case.
 */

{
    for (int i = 0; str[i] != 0; i++)
        str[i] = (char)toupper(str[i]);
}

/*-------------------------------------------------------------------------*/
static void
make_upper_case_buf (char *buf, const char *src, size_t len)

/* Change all letters in str to upper case.
 */

{
    strncpy(buf, src, len-1);
    buf[len-1] = 0;
    make_upper_case(buf);
}

/*-------------------------------------------------------------------------*/
static char *
make_f_name (char *str)

/* Take <str> and return a string 'F_<STR>' in its own memory block.
 */

{
    char f_name[500];

    if (strlen(str) + 1 + 2 > sizeof f_name)
        fatal("A local buffer was too small!(1)\n");
    sprintf(f_name, "F_%s", str);
    make_upper_case(f_name);
    return mystrdup(f_name);
}

/*-------------------------------------------------------------------------*/
static int
check_for_duplicate_instr (const char *f_name, const char *key, int redef_ok)

/* Check if either <f_name> or <key> already appear in instr[], and print
 * appropriate diagnostics. If <redef_ok> is true, a new <key> for an existing
 * <f_name> is allowed.
 * Return true if there is a duplicate for <f_name>, false if not.
 */

{
    size_t i;
    int rc;

    rc = 0;

    for (i = 0; i < (size_t)num_buff; i++)
    {
        if (!strcmp(f_name, instr[i].f_name))
        {
            if (!strcmp(key, instr[i].key))
            {
                rc = 1;
                got_error = 1;
                fprintf(stderr, "Error: Entry '%s':'%s' duplicated.\n"
                              , f_name, key);
            }
            else if (!redef_ok)
            {
                rc = 1;
                got_error = 1;
                fprintf(stderr, "Error: Entry '%s':'%s' redefined to '%s'.\n"
                              , f_name, instr[i].key, key);
            }
        }
        else if (!strcmp(key, instr[i].key))
        {
             fprintf(stderr, "Entry '%s':'%s' duplicated as '%s':... .\n"
                           , instr[i].f_name, instr[i].key, f_name);
        }

    }
    return rc;
}

/*-------------------------------------------------------------------------*/
static int
check_for_duplicate_string (const char *key, const char *buf)

/* Check if either <key> or <buf> already appear in instr[], and print
 * appropriate diagnostics.
 * Return true if there is a duplicate for <key>, false if not.
 */

{
    size_t i;
    int rc;

    rc = 0;

    for (i = 0; i < (size_t)num_buff; i++)
    {
        if (!strcmp(key, instr[i].key))
        {
            rc = 1;
            got_error = 1;
            if (!strcmp(buf, instr[i].buf))
            {
                fprintf(stderr, "Error: Entry '%s':'%s' duplicated.\n"
                              , key, buf);
            }
            else
            {
                fprintf(stderr, "Error: Entry '%s':'%s' redefined to '%s'.\n"
                              , key, instr[i].buf, buf);
            }
        }
        else if (!strcmp(buf, instr[i].buf))
        {
             fprintf(stderr, "Warning: Entry '%s':'%s' duplicated as '%s':... .\n"
                           , instr[i].key, instr[i].buf, key);
        }

    }
    return rc;
}

/*-------------------------------------------------------------------------*/
static bool
lpc_type_equal (lpc_type_t t1, lpc_type_t t2)

/* Return true, if both types are equal */

{
    return t1.token == t2.token
        && t1.flags == t2.flags
        && !strcmp(t1.struct_name ? t1.struct_name : "<NULL>"
                 , t2.struct_name ? t2.struct_name : "<NULL>");
} /* lpc_type_equal() */

/*-------------------------------------------------------------------------*/
static int
move_to_arg_types ()

/* Moves the types from curr_arg_types to arg_types.
 * Returns the index into arg_types.
 */

{
    int i;
    for (i = 0; i < last_current_type; i++)
    {
        int j;
        for (j = 0; j+i < last_current_type && j < curr_arg_type_size; j++)
        {
            if (!lpc_type_equal(curr_arg_types[j], arg_types[i+j]))
                break;
        }
        if (j == curr_arg_type_size)
            break;
    }

    if (i == last_current_type)
    {
        /* It's a new signature, put it into arg_types[] */
        for (int j = 0; j < curr_arg_type_size; j++)
        {
            arg_types[last_current_type++] = curr_arg_types[j];
            if (last_current_type == NELEMS(arg_types))
                yyerror("Array 'arg_types' is too small");
        }
    }

    return i;
} /* move_to_arg_types() */

#if defined(__MWERKS__) && !defined(WARN_ALL)
#    pragma warn_possunwant off
#    pragma warn_implicitconv off
#endif

#line 946 "make_func.c"

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
    PARSE_FUNC_SPEC = 258,         /* PARSE_FUNC_SPEC  */
    PARSE_APPLIED_SPEC = 259,      /* PARSE_APPLIED_SPEC  */
    PARSE_STRING_SPEC = 260,       /* PARSE_STRING_SPEC  */
    PARSE_STRUCT_SPEC = 261,       /* PARSE_STRUCT_SPEC  */
    NAME = 262,                    /* NAME  */
    ID = 263,                      /* ID  */
    VOID = 264,                    /* VOID  */
    INT = 265,                     /* INT  */
    STRING = 266,                  /* STRING  */
    BYTES = 267,                   /* BYTES  */
    BYTES_OR_STRING = 268,         /* BYTES_OR_STRING  */
    OBJECT = 269,                  /* OBJECT  */
    MAPPING = 270,                 /* MAPPING  */
    FLOAT = 271,                   /* FLOAT  */
    CLOSURE = 272,                 /* CLOSURE  */
    SYMBOL = 273,                  /* SYMBOL  */
    QUOTED_ARRAY = 274,            /* QUOTED_ARRAY  */
    MIXED = 275,                   /* MIXED  */
    UNKNOWN = 276,                 /* UNKNOWN  */
    NUL = 277,                     /* NUL  */
    STRUCT = 278,                  /* STRUCT  */
    LWOBJECT = 279,                /* LWOBJECT  */
    OBJECT_OR_LWOBJECT = 280,      /* OBJECT_OR_LWOBJECT  */
    COROUTINE = 281,               /* COROUTINE  */
    LPCTYPE = 282,                 /* LPCTYPE  */
    MAPPING_OR_CLOSURE = 283,      /* MAPPING_OR_CLOSURE  */
    INT_OR_STRING = 284,           /* INT_OR_STRING  */
    STRING_OR_STRING_ARRAY = 285,  /* STRING_OR_STRING_ARRAY  */
    CATCH_MSG_ARG = 286,           /* CATCH_MSG_ARG  */
    DEFAULT = 287,                 /* DEFAULT  */
    NO_LIGHTWEIGHT = 288,          /* NO_LIGHTWEIGHT  */
    CODES = 289,                   /* CODES  */
    EFUNS = 290,                   /* EFUNS  */
    TEFUNS = 291,                  /* TEFUNS  */
    END = 292,                     /* END  */
    APPLIED_MASTER = 293,          /* APPLIED_MASTER  */
    APPLIED_REGULAR = 294,         /* APPLIED_REGULAR  */
    APPLIED_HOOKS = 295,           /* APPLIED_HOOKS  */
    VARARGS = 296,                 /* VARARGS  */
    PRIVATE = 297,                 /* PRIVATE  */
    PROTECTED = 298,               /* PROTECTED  */
    STATIC = 299,                  /* STATIC  */
    VISIBLE = 300,                 /* VISIBLE  */
    UN_OP = 301,                   /* UN_OP  */
    BIN_OP = 302,                  /* BIN_OP  */
    TRI_OP = 303,                  /* TRI_OP  */
    QUAT_OP = 304,                 /* QUAT_OP  */
    LVALUE = 305                   /* LVALUE  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 882 "make_func.y"

    int number;
    char *string;

    struct
    {
        lpc_type_t type;        /* The type token number.        */
        bool void_allowed;      /* Whether void is also allowed. */
    } returntype;

    struct
    {
        const char *name;
        const char *flags;
    } visibility;

    lpc_type_t type;

#line 1062 "make_func.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);


/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_PARSE_FUNC_SPEC = 3,            /* PARSE_FUNC_SPEC  */
  YYSYMBOL_PARSE_APPLIED_SPEC = 4,         /* PARSE_APPLIED_SPEC  */
  YYSYMBOL_PARSE_STRING_SPEC = 5,          /* PARSE_STRING_SPEC  */
  YYSYMBOL_PARSE_STRUCT_SPEC = 6,          /* PARSE_STRUCT_SPEC  */
  YYSYMBOL_NAME = 7,                       /* NAME  */
  YYSYMBOL_ID = 8,                         /* ID  */
  YYSYMBOL_VOID = 9,                       /* VOID  */
  YYSYMBOL_INT = 10,                       /* INT  */
  YYSYMBOL_STRING = 11,                    /* STRING  */
  YYSYMBOL_BYTES = 12,                     /* BYTES  */
  YYSYMBOL_BYTES_OR_STRING = 13,           /* BYTES_OR_STRING  */
  YYSYMBOL_OBJECT = 14,                    /* OBJECT  */
  YYSYMBOL_MAPPING = 15,                   /* MAPPING  */
  YYSYMBOL_FLOAT = 16,                     /* FLOAT  */
  YYSYMBOL_CLOSURE = 17,                   /* CLOSURE  */
  YYSYMBOL_SYMBOL = 18,                    /* SYMBOL  */
  YYSYMBOL_QUOTED_ARRAY = 19,              /* QUOTED_ARRAY  */
  YYSYMBOL_MIXED = 20,                     /* MIXED  */
  YYSYMBOL_UNKNOWN = 21,                   /* UNKNOWN  */
  YYSYMBOL_NUL = 22,                       /* NUL  */
  YYSYMBOL_STRUCT = 23,                    /* STRUCT  */
  YYSYMBOL_LWOBJECT = 24,                  /* LWOBJECT  */
  YYSYMBOL_OBJECT_OR_LWOBJECT = 25,        /* OBJECT_OR_LWOBJECT  */
  YYSYMBOL_COROUTINE = 26,                 /* COROUTINE  */
  YYSYMBOL_LPCTYPE = 27,                   /* LPCTYPE  */
  YYSYMBOL_MAPPING_OR_CLOSURE = 28,        /* MAPPING_OR_CLOSURE  */
  YYSYMBOL_INT_OR_STRING = 29,             /* INT_OR_STRING  */
  YYSYMBOL_STRING_OR_STRING_ARRAY = 30,    /* STRING_OR_STRING_ARRAY  */
  YYSYMBOL_CATCH_MSG_ARG = 31,             /* CATCH_MSG_ARG  */
  YYSYMBOL_DEFAULT = 32,                   /* DEFAULT  */
  YYSYMBOL_NO_LIGHTWEIGHT = 33,            /* NO_LIGHTWEIGHT  */
  YYSYMBOL_CODES = 34,                     /* CODES  */
  YYSYMBOL_EFUNS = 35,                     /* EFUNS  */
  YYSYMBOL_TEFUNS = 36,                    /* TEFUNS  */
  YYSYMBOL_END = 37,                       /* END  */
  YYSYMBOL_APPLIED_MASTER = 38,            /* APPLIED_MASTER  */
  YYSYMBOL_APPLIED_REGULAR = 39,           /* APPLIED_REGULAR  */
  YYSYMBOL_APPLIED_HOOKS = 40,             /* APPLIED_HOOKS  */
  YYSYMBOL_VARARGS = 41,                   /* VARARGS  */
  YYSYMBOL_PRIVATE = 42,                   /* PRIVATE  */
  YYSYMBOL_PROTECTED = 43,                 /* PROTECTED  */
  YYSYMBOL_STATIC = 44,                    /* STATIC  */
  YYSYMBOL_VISIBLE = 45,                   /* VISIBLE  */
  YYSYMBOL_UN_OP = 46,                     /* UN_OP  */
  YYSYMBOL_BIN_OP = 47,                    /* BIN_OP  */
  YYSYMBOL_TRI_OP = 48,                    /* TRI_OP  */
  YYSYMBOL_QUAT_OP = 49,                   /* QUAT_OP  */
  YYSYMBOL_LVALUE = 50,                    /* LVALUE  */
  YYSYMBOL_51_ = 51,                       /* ':'  */
  YYSYMBOL_52_ = 52,                       /* '('  */
  YYSYMBOL_53_ = 53,                       /* ')'  */
  YYSYMBOL_54_ = 54,                       /* ';'  */
  YYSYMBOL_55_ = 55,                       /* '*'  */
  YYSYMBOL_56_ = 56,                       /* '&'  */
  YYSYMBOL_57_ = 57,                       /* ','  */
  YYSYMBOL_58_ = 58,                       /* '|'  */
  YYSYMBOL_59_ = 59,                       /* '.'  */
  YYSYMBOL_60_ = 60,                       /* '{'  */
  YYSYMBOL_61_ = 61,                       /* '}'  */
  YYSYMBOL_YYACCEPT = 62,                  /* $accept  */
  YYSYMBOL_all = 63,                       /* all  */
  YYSYMBOL_func_spec = 64,                 /* func_spec  */
  YYSYMBOL_codes = 65,                     /* codes  */
  YYSYMBOL_efuns = 66,                     /* efuns  */
  YYSYMBOL_tefuns = 67,                    /* tefuns  */
  YYSYMBOL_optional_name = 68,             /* optional_name  */
  YYSYMBOL_optional_optype = 69,           /* optional_optype  */
  YYSYMBOL_code = 70,                      /* code  */
  YYSYMBOL_funcs = 71,                     /* funcs  */
  YYSYMBOL_optional_ID = 72,               /* optional_ID  */
  YYSYMBOL_optional_default = 73,          /* optional_default  */
  YYSYMBOL_optional_no_lightweight = 74,   /* optional_no_lightweight  */
  YYSYMBOL_func = 75,                      /* func  */
  YYSYMBOL_type = 76,                      /* type  */
  YYSYMBOL_basic = 77,                     /* basic  */
  YYSYMBOL_opt_star = 78,                  /* opt_star  */
  YYSYMBOL_opt_ref = 79,                   /* opt_ref  */
  YYSYMBOL_arg_list = 80,                  /* arg_list  */
  YYSYMBOL_basic_utype = 81,               /* basic_utype  */
  YYSYMBOL_utype = 82,                     /* utype  */
  YYSYMBOL_typel2 = 83,                    /* typel2  */
  YYSYMBOL_arg_type = 84,                  /* arg_type  */
  YYSYMBOL_typel = 85,                     /* typel  */
  YYSYMBOL_applied_spec = 86,              /* applied_spec  */
  YYSYMBOL_applied_lfuns = 87,             /* applied_lfuns  */
  YYSYMBOL_applied_lfun = 88,              /* applied_lfun  */
  YYSYMBOL_opt_visibility = 89,            /* opt_visibility  */
  YYSYMBOL_opt_varargs = 90,               /* opt_varargs  */
  YYSYMBOL_applied_rettype = 91,           /* applied_rettype  */
  YYSYMBOL_applied_args = 92,              /* applied_args  */
  YYSYMBOL_applied_args2 = 93,             /* applied_args2  */
  YYSYMBOL_applied_arg = 94,               /* applied_arg  */
  YYSYMBOL_applied_argtype = 95,           /* applied_argtype  */
  YYSYMBOL_string_spec = 96,               /* string_spec  */
  YYSYMBOL_stringdefs = 97,                /* stringdefs  */
  YYSYMBOL_stringdef = 98,                 /* stringdef  */
  YYSYMBOL_struct_spec = 99,               /* struct_spec  */
  YYSYMBOL_struct_defs = 100,              /* struct_defs  */
  YYSYMBOL_struct_def = 101,               /* struct_def  */
  YYSYMBOL_struct_members = 102,           /* struct_members  */
  YYSYMBOL_struct_member = 103,            /* struct_member  */
  YYSYMBOL_struct_member_type = 104        /* struct_member_type  */
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
#define YYFINAL  15
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   296

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  62
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  43
/* YYNRULES -- Number of rules.  */
#define YYNRULES  112
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  198

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   305


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
       2,     2,     2,     2,     2,     2,     2,     2,    56,     2,
      52,    53,    55,     2,    57,     2,    59,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    51,    54,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    60,    58,    61,     2,     2,     2,     2,
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
      45,    46,    47,    48,    49,    50
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   973,   973,   974,   975,   976,   981,   983,   984,   986,
     988,   992,   993,   995,   996,   997,   998,   999,  1002,  1039,
    1040,  1042,  1043,  1045,  1046,  1048,  1049,  1051,  1238,  1239,
    1242,  1242,  1242,  1242,  1242,  1242,  1242,  1242,  1242,  1243,
    1243,  1243,  1243,  1243,  1243,  1243,  1243,  1245,  1246,  1247,
    1249,  1250,  1251,  1253,  1254,  1255,  1257,  1258,  1259,  1260,
    1261,  1262,  1263,  1265,  1267,  1279,  1295,  1296,  1297,  1298,
    1326,  1330,  1332,  1336,  1368,  1370,  1372,  1374,  1376,  1381,
    1382,  1386,  1387,  1388,  1389,  1390,  1391,  1395,  1396,  1397,
    1398,  1402,  1403,  1407,  1417,  1418,  1419,  1420,  1421,  1422,
    1423,  1429,  1431,  1432,  1434,  1461,  1463,  1464,  1467,  1509,
    1510,  1513,  1521
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
  "\"end of file\"", "error", "\"invalid token\"", "PARSE_FUNC_SPEC",
  "PARSE_APPLIED_SPEC", "PARSE_STRING_SPEC", "PARSE_STRUCT_SPEC", "NAME",
  "ID", "VOID", "INT", "STRING", "BYTES", "BYTES_OR_STRING", "OBJECT",
  "MAPPING", "FLOAT", "CLOSURE", "SYMBOL", "QUOTED_ARRAY", "MIXED",
  "UNKNOWN", "NUL", "STRUCT", "LWOBJECT", "OBJECT_OR_LWOBJECT",
  "COROUTINE", "LPCTYPE", "MAPPING_OR_CLOSURE", "INT_OR_STRING",
  "STRING_OR_STRING_ARRAY", "CATCH_MSG_ARG", "DEFAULT", "NO_LIGHTWEIGHT",
  "CODES", "EFUNS", "TEFUNS", "END", "APPLIED_MASTER", "APPLIED_REGULAR",
  "APPLIED_HOOKS", "VARARGS", "PRIVATE", "PROTECTED", "STATIC", "VISIBLE",
  "UN_OP", "BIN_OP", "TRI_OP", "QUAT_OP", "LVALUE", "':'", "'('", "')'",
  "';'", "'*'", "'&'", "','", "'|'", "'.'", "'{'", "'}'", "$accept", "all",
  "func_spec", "codes", "efuns", "tefuns", "optional_name",
  "optional_optype", "code", "funcs", "optional_ID", "optional_default",
  "optional_no_lightweight", "func", "type", "basic", "opt_star",
  "opt_ref", "arg_list", "basic_utype", "utype", "typel2", "arg_type",
  "typel", "applied_spec", "applied_lfuns", "applied_lfun",
  "opt_visibility", "opt_varargs", "applied_rettype", "applied_args",
  "applied_args2", "applied_arg", "applied_argtype", "string_spec",
  "stringdefs", "stringdef", "struct_spec", "struct_defs", "struct_def",
  "struct_members", "struct_member", "struct_member_type", YY_NULLPTR
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
     305,    58,    40,    41,    59,    42,    38,    44,   124,    46,
     123,   125
};
#endif

#define YYPACT_NINF (-92)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-71)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      57,    -6,     5,   -92,   -92,    45,   -92,   -92,    13,   -92,
     -92,   -92,    41,   -92,    43,   -92,   -92,    32,    61,   -92,
      10,    63,   -92,    64,   -92,   -92,    36,    74,    37,   -92,
     -92,   -92,   -92,   -92,    38,   -92,    17,   181,    44,   -92,
     -92,   -92,   -92,   -92,   -92,   -92,   200,   181,   -92,   -92,
      28,    40,    48,    50,   -92,    51,   -92,   -92,   -92,   -92,
     -92,   -92,    52,   -92,   -92,   -92,   -92,    62,    97,   -92,
     -92,    70,    60,    66,    67,   -92,   -92,   -92,   -92,   -92,
      71,   136,    62,    -5,   -92,   143,   115,   152,   142,   150,
     153,   155,   116,   -10,   162,   181,   132,   219,   163,    47,
     -92,   121,   -92,   122,   -92,   123,   -92,   -92,   -92,   -92,
     -92,   -92,   -92,   -92,   -92,   -92,   -92,   127,   -92,   -92,
     -92,   -92,   -92,   120,    73,   -92,   -92,    15,    59,   -92,
     124,   125,   126,   128,   129,   130,   151,   160,   168,   -92,
     -92,   172,   -92,    62,   173,    -9,   -92,   185,   193,   170,
     175,   239,   251,   253,   209,   -92,   215,   119,   -92,   -10,
     211,   220,   138,   221,   213,   238,   -92,   -92,   -92,   217,
     -92,   -92,   -92,   214,   -92,   -92,   218,   268,   -92,   245,
     222,   -92,   265,   223,   -92,   -92,   -92,   273,   -92,   225,
     -92,   230,   261,   -92,   228,   267,   233,   -92
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     0,   102,   106,     0,     7,     2,    11,    71,
       3,     4,   101,     5,   105,     1,    12,     0,     0,     8,
      74,     0,   103,     0,   107,    19,     0,    13,     0,    75,
      76,    77,    78,    72,    79,   104,     0,     9,     0,    14,
      15,    16,    17,    18,    71,    80,     0,     0,    30,    31,
      32,    33,    37,    34,    35,    38,    40,    41,    36,    39,
      46,    42,    43,    44,    45,    20,    56,    49,     0,    19,
       6,    74,    30,    31,    32,    33,    37,    34,    38,    43,
      81,     0,    49,     0,   109,     0,     0,     0,     0,     0,
       0,     0,    47,    52,    22,    10,     0,     0,     0,     0,
      82,     0,   112,     0,   110,     0,    57,    58,    59,    61,
      62,    60,    48,    51,    50,    63,    21,     0,    71,    32,
      86,    85,    84,     0,    87,   108,   111,    53,    74,    83,
      31,    32,    37,    42,    43,     0,    94,     0,    89,    91,
      93,    42,    65,    49,     0,    24,    54,    66,    64,     0,
       0,     0,     0,     0,     0,    95,     0,     0,    29,    52,
       0,     0,    52,     0,     0,     0,    98,    99,    96,     0,
      97,    88,    73,     0,    92,    28,     0,     0,    55,    26,
       0,    67,     0,     0,    69,    23,    25,    11,    68,     0,
      90,     0,     0,    27,     0,     0,     0,   100
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -92,   -92,   -92,   -92,   -92,   -92,   102,   -92,   -92,   224,
     -92,   -92,   -92,   -92,   -92,   -46,   -79,   -91,   -92,   -39,
     -92,   133,   131,   -92,   -92,   -43,   -92,   -92,   -92,   -92,
     -92,   -92,   134,   -92,   -92,   -92,   -92,   -92,   -92,   -92,
     -92,   207,   -92
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     5,     7,     8,    26,    70,    18,    43,    19,    37,
     117,   163,   187,    65,   142,    66,    93,   144,   145,    67,
      68,   146,   147,   148,    10,    20,    33,    34,    46,    81,
     137,   138,   139,   140,    11,    12,    22,    13,    14,    24,
      83,    84,    85
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      80,    71,   115,   102,    48,    49,    50,    51,    82,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      16,    63,    64,   161,    48,    49,   119,    75,     6,    76,
      77,    54,    78,    56,    57,    58,    59,    60,   141,    79,
     113,    63,    64,     9,    82,    15,   114,    28,   162,    21,
      17,   120,    29,    30,    31,    32,   103,   122,   123,   -70,
       1,     2,     3,     4,   159,   113,    23,    25,   175,    27,
      35,   114,    36,    38,   -52,   128,    44,    47,   136,    45,
      69,   143,    48,   130,   131,    75,    86,   132,    77,    54,
      78,    56,    57,    58,    59,    60,   133,   134,    87,    63,
      64,    29,    30,    31,    32,    94,    88,    96,    89,    90,
      91,   136,    29,    30,    31,    32,   143,    92,    97,   143,
      39,    40,    41,    42,    98,    99,   100,   106,    48,   130,
     131,    75,   135,   132,    77,    54,    78,    56,    57,    58,
      59,    60,   133,   134,   101,    63,    64,    48,    49,   119,
      75,   105,    76,    77,    54,    78,    56,    57,    58,    59,
      60,   141,    79,   107,    63,    64,   108,   109,   110,   111,
     116,   112,   118,   124,   121,   129,   125,   126,   173,   127,
     158,   166,   149,   150,   151,   167,   152,   153,   113,   154,
      48,    49,    50,    51,   114,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,   155,    63,    64,    72,
      73,    74,    75,   156,    76,    77,    54,    78,    56,    57,
      58,    59,    60,    61,    79,   157,    63,    64,    48,    49,
     119,    75,   160,    76,    77,    54,    78,    56,    57,    58,
      59,    60,    61,    79,   164,    63,    64,    48,    49,   119,
      75,   165,    76,    77,    54,    78,    56,    57,    58,    59,
      60,   141,    79,   168,    63,    64,   169,   170,   171,   172,
     176,   177,   180,   183,   179,   182,   185,   184,   186,   189,
      16,   188,   190,   192,   193,   194,   195,   196,   197,   191,
     104,   174,     0,    95,     0,   178,   181
};

static const yytype_int16 yycheck[] =
{
      46,    44,    93,    82,     9,    10,    11,    12,    47,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
       7,    26,    27,    32,     9,    10,    11,    12,    34,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      50,    26,    27,    38,    83,     0,    56,    37,    57,     8,
      37,    97,    42,    43,    44,    45,    61,    10,    11,     0,
       3,     4,     5,     6,   143,    50,    23,    35,   159,     8,
       7,    56,     8,    37,    59,   118,    39,    60,   124,    41,
      36,   127,     9,    10,    11,    12,    58,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    58,    26,
      27,    42,    43,    44,    45,     8,    58,    37,    58,    58,
      58,   157,    42,    43,    44,    45,   162,    55,    58,   165,
      46,    47,    48,    49,    58,    58,    55,    12,     9,    10,
      11,    12,    59,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,     8,    26,    27,     9,    10,    11,
      12,     8,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    11,    26,    27,    24,    17,    15,    14,
       8,    55,    40,    52,    11,    55,    54,    54,    59,    52,
       8,    11,    58,    58,    58,    10,    58,    58,    50,    59,
       9,    10,    11,    12,    56,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    55,    26,    27,     9,
      10,    11,    12,    53,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    57,    26,    27,     9,    10,
      11,    12,    59,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    59,    26,    27,     9,    10,    11,
      12,    58,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    24,    26,    27,    15,    14,    59,    54,
      59,    51,    59,    59,    53,    58,     8,    59,    33,    14,
       7,    59,    59,    58,    54,    24,    58,    20,    55,   187,
      83,   157,    -1,    69,    -1,   162,   165
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,     4,     5,     6,    63,    34,    64,    65,    38,
      86,    96,    97,    99,   100,     0,     7,    37,    68,    70,
      87,     8,    98,    23,   101,    35,    66,     8,    37,    42,
      43,    44,    45,    88,    89,     7,     8,    71,    37,    46,
      47,    48,    49,    69,    39,    41,    90,    60,     9,    10,
      11,    12,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    26,    27,    75,    77,    81,    82,    36,
      67,    87,     9,    10,    11,    12,    14,    15,    17,    24,
      77,    91,    81,   102,   103,   104,    58,    58,    58,    58,
      58,    58,    55,    78,     8,    71,    37,    58,    58,    58,
      55,     8,    78,    61,   103,     8,    12,    11,    24,    17,
      15,    14,    55,    50,    56,    79,     8,    72,    40,    11,
      77,    11,    10,    11,    52,    54,    54,    52,    87,    55,
      10,    11,    14,    23,    24,    59,    77,    92,    93,    94,
      95,    23,    76,    77,    79,    80,    83,    84,    85,    58,
      58,    58,    58,    58,    59,    55,    53,    57,     8,    78,
      59,    32,    57,    73,    59,    58,    11,    10,    24,    15,
      14,    59,    54,    59,    94,    79,    59,    51,    83,    53,
      59,    84,    58,    59,    59,     8,    33,    74,    59,    14,
      59,    68,    58,    54,    24,    58,    20,    55
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    62,    63,    63,    63,    63,    64,    65,    65,    66,
      67,    68,    68,    69,    69,    69,    69,    69,    70,    71,
      71,    72,    72,    73,    73,    74,    74,    75,    76,    76,
      77,    77,    77,    77,    77,    77,    77,    77,    77,    77,
      77,    77,    77,    77,    77,    77,    77,    78,    78,    78,
      79,    79,    79,    80,    80,    80,    81,    81,    81,    81,
      81,    81,    81,    82,    83,    84,    85,    85,    85,    85,
      86,    87,    87,    88,    89,    89,    89,    89,    89,    90,
      90,    91,    91,    91,    91,    91,    91,    92,    92,    92,
      92,    93,    93,    94,    95,    95,    95,    95,    95,    95,
      95,    96,    97,    97,    98,    99,   100,   100,   101,   102,
     102,   103,   104
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     2,     2,     2,     5,     1,     2,     2,
       2,     0,     1,     0,     1,     1,     1,     1,     3,     0,
       2,     1,     0,     3,     0,     1,     0,    10,     3,     2,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     2,     0,
       1,     1,     0,     0,     1,     3,     1,     3,     3,     3,
       3,     3,     3,     3,     1,     1,     1,     3,     4,     4,
       8,     0,     2,     8,     0,     1,     1,     1,     1,     0,
       1,     1,     2,     4,     3,     3,     3,     0,     3,     1,
       5,     1,     3,     1,     1,     2,     3,     3,     3,     3,
      10,     1,     0,     2,     2,     1,     0,     2,     6,     1,
       2,     3,     2
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
  case 11: /* optional_name: %empty  */
#line 992 "make_func.y"
                           { (yyval.string) = NULL; }
#line 2309 "make_func.c"
    break;

  case 13: /* optional_optype: %empty  */
#line 995 "make_func.y"
                             { (yyval.number) = 0; }
#line 2315 "make_func.c"
    break;

  case 14: /* optional_optype: UN_OP  */
#line 996 "make_func.y"
                             { (yyval.number) = 1; }
#line 2321 "make_func.c"
    break;

  case 15: /* optional_optype: BIN_OP  */
#line 997 "make_func.y"
                             { (yyval.number) = 2; }
#line 2327 "make_func.c"
    break;

  case 16: /* optional_optype: TRI_OP  */
#line 998 "make_func.y"
                             { (yyval.number) = 3; }
#line 2333 "make_func.c"
    break;

  case 17: /* optional_optype: QUAT_OP  */
#line 999 "make_func.y"
                             { (yyval.number) = 4; }
#line 2339 "make_func.c"
    break;

  case 18: /* code: optional_name ID optional_optype  */
#line 1003 "make_func.y"
    {
        char *f_name, buff[500];

        if (num_buff >= MAX_FUNC)
            yyerror("Too many codes and efuns in total!\n");
        if (!(yyvsp[-2].string))
            (yyvsp[-2].string) = mystrdup((yyvsp[-1].string));
        f_name = make_f_name((yyvsp[-1].string));
        check_for_duplicate_instr(f_name, (yyvsp[-1].string), 0);
        instr[num_buff].code_class = current_code_class;
        num_instr[current_code_class]++;

        if ((yyvsp[0].number) == 0)
            sprintf(buff, "{ %s, %s-%s_OFFSET, 0, 0, -1, NULL , -1, -1, false, false, \"%s\", NULL },\n"
                        , classprefix[instr[num_buff].code_class]
                        , f_name, classtag[instr[num_buff].code_class]
                        , (yyvsp[-2].string));
        else
            sprintf(buff, "{ %s, %s-%s_OFFSET, %d, %d, 0, &_lpctype_mixed, -1, -1, false, false, \"%s\", NULL },\n"
                        , classprefix[instr[num_buff].code_class]
                        , f_name, classtag[instr[num_buff].code_class]
                        , (yyvsp[0].number), (yyvsp[0].number)
                        , (yyvsp[-2].string));

        if (strlen(buff) > sizeof buff)
            fatal("Local buffer overflow!\n");
        instr[num_buff].f_name = f_name;
        instr[num_buff].key = mystrdup((yyvsp[-1].string));
        instr[num_buff].buf = mystrdup(buff);
        num_buff++;
        free((yyvsp[-2].string));
    }
#line 2376 "make_func.c"
    break;

  case 22: /* optional_ID: %empty  */
#line 1043 "make_func.y"
                           { (yyval.string) = ""; }
#line 2382 "make_func.c"
    break;

  case 23: /* optional_default: DEFAULT ':' ID  */
#line 1045 "make_func.y"
                                   { (yyval.string) = (yyvsp[0].string); }
#line 2388 "make_func.c"
    break;

  case 24: /* optional_default: %empty  */
#line 1046 "make_func.y"
                                   { (yyval.string) = "0"; }
#line 2394 "make_func.c"
    break;

  case 25: /* optional_no_lightweight: NO_LIGHTWEIGHT  */
#line 1048 "make_func.y"
                                        { (yyval.number) = 1; }
#line 2400 "make_func.c"
    break;

  case 26: /* optional_no_lightweight: %empty  */
#line 1049 "make_func.y"
                                        { (yyval.number) = 0; }
#line 2406 "make_func.c"
    break;

  case 27: /* func: utype ID optional_ID '(' arg_list optional_default ')' optional_no_lightweight optional_name ';'  */
#line 1052 "make_func.y"
    {
        char buff[500];
        char *f_name;
        char *f_prefix;
        int  code_class;
        int i;
        int max_arg, arg_index, lpc_index;
        bool return_ref;

        if (num_buff >= MAX_FUNC)
            yyerror("Too many codes and efuns in total!\n");

        if (min_arg == -1)
            min_arg = (yyvsp[-5].number);

        max_arg = (yyvsp[-5].number);

        if (unlimit_max)
        {
            /* Add an additional NULL entry to mark
             * the end of the argument list.
             */
            curr_arg_types[curr_arg_type_size++] = (lpc_type_t){0, 0, NULL};
            if (curr_arg_type_size == NELEMS(curr_arg_types))
                yyerror("Too many arguments");
            curr_lpc_type_size++;
        }

        /* Make the correct f_name and determine the code class
         */
        if ((yyvsp[-7].string)[0] == '\0')
        {
            code_class = current_code_class;
            if (current_code_class == C_SEFUN)
            {
                if (!unlimit_max && min_arg == max_arg)
                {
                    if (max_arg < 5)
                        code_class = C_EFUN0 + min_arg;
                    else
                    {
                        code_class = C_EFUNV;
                        fprintf(stderr
                               , "Efun '%s' has %d arguments and will be "
                                 "considered a 'varargs' efun.\n"
                               , (yyvsp[-8].string), min_arg);
                    }
                }

                if (unlimit_max || min_arg != max_arg)
                {
                    code_class = C_EFUNV;
                }

                if (code_class == C_SEFUN)
                {
                    char buf[100];
                    sprintf(buf, "Efun '%s' can't be classified.\n", (yyvsp[-8].string));
                    fatal(buf);
                }
            }

            f_name = make_f_name((yyvsp[-8].string));
            check_for_duplicate_instr(f_name, (yyvsp[-8].string), 0);
            instr[num_buff].code_class = code_class;
            num_instr[code_class]++;
            f_prefix = classprefix[code_class];
        }
        else
        {
            f_name = mystrdup((yyvsp[-7].string));
            check_for_duplicate_instr(f_name, (yyvsp[-7].string), 1);
            instr[num_buff].code_class = code_class = C_ALIAS;
            num_instr[C_ALIAS]++;
            f_prefix = NULL;
        }

        /* Search the function's signature in arg_types[] */
        arg_index = move_to_arg_types();

        /* Search the function's signature in lpc_types[].
         * For efuns using a (...) argument the last listed lpc_type is 0,
         * which doesn't need to be compared or stored.
         */

        for (i = 0; i < last_current_lpc_type; i++)
        {
            int j;
            Bool mismatch = MY_FALSE;

            for ( j = 0
                ; j+i < last_current_lpc_type && j < curr_lpc_type_size
                ; j++)
            {
                if (curr_lpc_types[j] != lpc_types[i+j])
                {
                    mismatch = MY_TRUE;
                    break;
                }
            }
            if (!mismatch)
                break;
        }

        if (i + curr_lpc_type_size > last_current_lpc_type)
        {
            /* It's a new signature, its first (last_current_lpc_type - i)
             * args matching the last entries in lpc_types.
             * TODO: An even better strategy would be to sort the signatures
             * TODO:: by size and then do the overlapping store with the
             * TODO:: longest one first.
             */

            int j;

            for (j = last_current_lpc_type - i; j < curr_lpc_type_size; j++)
            {
                lpc_types[last_current_lpc_type++] = curr_lpc_types[j];

                if (last_current_lpc_type == NELEMS(lpc_types))
                    yyerror("Array 'lpc_types' is too small");
            }
        }

        lpc_index = i;
        return_ref = (yyvsp[-9].type).flags & MF_TYPE_MOD_REFERENCE;
        if (return_ref)
            (yyvsp[-9].type).flags &= ~MF_TYPE_MOD_REFERENCE;

        /* Store the data */

        if (code_class != C_ALIAS && code_class != C_SEFUN)
        {
            char * tag;

            tag = (code_class == C_EFUN) ? classtag[C_CODE] : classtag[code_class];

            sprintf(buff, "{ %s, %s-%s_OFFSET, %d, %d, %s, %s, %d, %d, %s, %s, \"%s\""
                        , f_prefix, f_name, tag
                        , unlimit_max ? -1 : max_arg, min_arg
                        , (yyvsp[-4].string), lpctypestr((yyvsp[-9].type))
                        , arg_index, lpc_index
                        , return_ref ? "true" : "false"
                        , (yyvsp[-2].number) ? "true" : "false"
                        , (yyvsp[-8].string)
                   );

        }
        else
        {
            sprintf(buff, "{ 0, 0, %d, %d, %s, %s, %d, %d, %s, %s, \"%s\""
                        , unlimit_max ? -1 : max_arg, min_arg
                        , (yyvsp[-4].string), lpctypestr((yyvsp[-9].type))
                        , arg_index, lpc_index
                        , return_ref ? "true" : "false"
                        , (yyvsp[-2].number) ? "true" : "false"
                        , (yyvsp[-8].string)
                   );
        }

        if ((yyvsp[-1].string) != NULL)
            sprintf(buff+strlen(buff), ", \"%s\"", (yyvsp[-1].string));
        else
            strcat(buff, ", NULL");

        strcat(buff, " },\n");

        if (strlen(buff) > sizeof buff)
             fatal("Local buffer overwritten !\n");

        instr[num_buff].f_name = f_name;
        instr[num_buff].key = mystrdup((yyvsp[-8].string));
        instr[num_buff].buf = mystrdup(buff);
        num_buff++;

        /* Reset for next function */

        min_arg = -1;
        unlimit_max = MY_FALSE;
        curr_arg_type_size = 0;
        curr_lpc_type_size = 0;
        curr_lpc_types[0] = 0;
    }
#line 2594 "make_func.c"
    break;

  case 28: /* type: basic opt_star opt_ref  */
#line 1238 "make_func.y"
                             { (yyval.type) = (lpc_type_t){(yyvsp[-2].number), (yyvsp[-1].number) | (yyvsp[0].number), NULL}; }
#line 2600 "make_func.c"
    break;

  case 29: /* type: STRUCT ID  */
#line 1239 "make_func.y"
                             { (yyval.type) = (lpc_type_t){(yyvsp[-1].number), 0, mystrdup((yyvsp[0].string))}; }
#line 2606 "make_func.c"
    break;

  case 47: /* opt_star: '*'  */
#line 1245 "make_func.y"
                   { (yyval.number) = MF_TYPE_MOD_POINTER;         }
#line 2612 "make_func.c"
    break;

  case 48: /* opt_star: '*' '*'  */
#line 1246 "make_func.y"
                   { (yyval.number) = MF_TYPE_MOD_POINTER_POINTER; }
#line 2618 "make_func.c"
    break;

  case 49: /* opt_star: %empty  */
#line 1247 "make_func.y"
                   { (yyval.number) = 0;                           }
#line 2624 "make_func.c"
    break;

  case 50: /* opt_ref: '&'  */
#line 1249 "make_func.y"
                 { (yyval.number) = MF_TYPE_MOD_REFERENCE; }
#line 2630 "make_func.c"
    break;

  case 51: /* opt_ref: LVALUE  */
#line 1250 "make_func.y"
                 { (yyval.number) = MF_TYPE_MOD_LVALUE;    }
#line 2636 "make_func.c"
    break;

  case 52: /* opt_ref: %empty  */
#line 1251 "make_func.y"
                 { (yyval.number) = 0;                     }
#line 2642 "make_func.c"
    break;

  case 53: /* arg_list: %empty  */
#line 1253 "make_func.y"
                                  { (yyval.number) = 0; }
#line 2648 "make_func.c"
    break;

  case 54: /* arg_list: typel2  */
#line 1254 "make_func.y"
                                  { (yyval.number) = 1; if ((yyvsp[0].number)) min_arg = 0; }
#line 2654 "make_func.c"
    break;

  case 55: /* arg_list: arg_list ',' typel2  */
#line 1255 "make_func.y"
                                  { (yyval.number) = (yyvsp[-2].number) + 1; if ((yyvsp[0].number)) min_arg = (yyval.number) - 1; }
#line 2660 "make_func.c"
    break;

  case 57: /* basic_utype: STRING '|' BYTES  */
#line 1258 "make_func.y"
                                  { (yyval.number) = BYTES_OR_STRING; }
#line 2666 "make_func.c"
    break;

  case 58: /* basic_utype: BYTES '|' STRING  */
#line 1259 "make_func.y"
                                  { (yyval.number) = BYTES_OR_STRING; }
#line 2672 "make_func.c"
    break;

  case 59: /* basic_utype: OBJECT '|' LWOBJECT  */
#line 1260 "make_func.y"
                                  { (yyval.number) = OBJECT_OR_LWOBJECT; }
#line 2678 "make_func.c"
    break;

  case 60: /* basic_utype: LWOBJECT '|' OBJECT  */
#line 1261 "make_func.y"
                                  { (yyval.number) = OBJECT_OR_LWOBJECT; }
#line 2684 "make_func.c"
    break;

  case 61: /* basic_utype: MAPPING '|' CLOSURE  */
#line 1262 "make_func.y"
                                  { (yyval.number) = MAPPING_OR_CLOSURE; }
#line 2690 "make_func.c"
    break;

  case 62: /* basic_utype: CLOSURE '|' MAPPING  */
#line 1263 "make_func.y"
                                  { (yyval.number) = MAPPING_OR_CLOSURE; }
#line 2696 "make_func.c"
    break;

  case 63: /* utype: basic_utype opt_star opt_ref  */
#line 1265 "make_func.y"
                                     { (yyval.type) = (lpc_type_t){(yyvsp[-2].number), (yyvsp[-1].number) | (yyvsp[0].number), NULL}; }
#line 2702 "make_func.c"
    break;

  case 64: /* typel2: typel  */
#line 1268 "make_func.y"
    {
        (yyval.number) = (yyvsp[0].number);
        curr_arg_types[curr_arg_type_size++] = (lpc_type_t){0, 0, NULL};
        if (curr_arg_type_size == NELEMS(curr_arg_types))
            yyerror("Too many arguments");
        curr_lpc_type_size++;
        if (curr_lpc_type_size == NELEMS(curr_lpc_types))
            yyerror("Too many arguments");
        curr_lpc_types[curr_lpc_type_size] = 0;
    }
#line 2717 "make_func.c"
    break;

  case 65: /* arg_type: type  */
#line 1280 "make_func.y"
    {
        if ((yyvsp[0].type).token != VOID)
        {
            if ((yyvsp[0].type).token != NUL)
            {
                curr_arg_types[curr_arg_type_size] = (yyvsp[0].type);
                curr_arg_type_size++;
            }
            if (curr_arg_type_size == NELEMS(curr_arg_types))
                yyerror("Too many arguments");
            curr_lpc_types[curr_lpc_type_size] |= type2flag((yyvsp[0].type));
        }
        (yyval.type) = (yyvsp[0].type);
    }
#line 2736 "make_func.c"
    break;

  case 66: /* typel: arg_type  */
#line 1295 "make_func.y"
                             { (yyval.number) = (min_arg == -1 && (yyvsp[0].type).token == VOID); }
#line 2742 "make_func.c"
    break;

  case 67: /* typel: typel '|' arg_type  */
#line 1296 "make_func.y"
                             { (yyval.number) = (min_arg == -1 && ((yyvsp[-2].number) || (yyvsp[0].type).token == VOID));}
#line 2748 "make_func.c"
    break;

  case 68: /* typel: arg_type '.' '.' '.'  */
#line 1297 "make_func.y"
                             { (yyval.number) = min_arg == -1 ; unlimit_max = MY_TRUE; }
#line 2754 "make_func.c"
    break;

  case 69: /* typel: opt_ref '.' '.' '.'  */
#line 1299 "make_func.y"
        {
            (yyval.number) = min_arg == -1 ; unlimit_max = MY_TRUE;

            if (!(yyvsp[-3].number))
            {
                /* This is the same as 'mixed|mixed& ...' */
                if (curr_arg_type_size+2 >= NELEMS(curr_arg_types))
                    yyerror("Too many arguments");
                else
                {
                    curr_arg_types[curr_arg_type_size++] = (lpc_type_t){ MIXED, 0, NULL};
                    curr_arg_types[curr_arg_type_size++] = (lpc_type_t){ MIXED, MF_TYPE_MOD_REFERENCE, NULL};
                }
            }
            else
            {
                curr_arg_types[curr_arg_type_size++] =  (lpc_type_t){ MIXED, (yyvsp[-3].number), NULL};
                if (curr_arg_type_size == NELEMS(curr_arg_types))
                    yyerror("Too many arguments");
            }

            curr_lpc_types[curr_lpc_type_size] |= type2flag((lpc_type_t){ MIXED, 0, NULL});
        }
#line 2782 "make_func.c"
    break;

  case 73: /* applied_lfun: opt_visibility opt_varargs applied_rettype ID '(' applied_args ')' ';'  */
#line 1337 "make_func.y"
    {
        if (*current_decl_num >= MAX_FUNC)
            yyerror("Too many functions");
        else
        {
            char buf[1024];
            ++*current_decl_num;

            snprintf(buf, sizeof(buf), "    { %s, { .%s%s%s }, \"%s\", %s, %d, %d, %s, %s, %s, NULL, NULL },\n"
                    , lpctypestr((yyvsp[-5].returntype).type)
                    , current_decl_is_hook ? "hook = " : "cname = \""
                    , (yyvsp[-4].string)
                    , current_decl_is_hook ? "" : "\""
                    , (yyvsp[-7].visibility).name
                    , (yyvsp[-7].visibility).flags
                    , curr_arg_type_size
                    , move_to_arg_types()
                    , (yyvsp[-6].number) ? "true" : "false"
                    , (yyvsp[-2].number) ? "true" : "false"
                    , (yyvsp[-5].returntype).void_allowed ? "true" : "false");

            *next_decl_line = mystrdup(buf);
            ++next_decl_line;

            curr_arg_type_size = 0;
        }
    }
#line 2814 "make_func.c"
    break;

  case 74: /* opt_visibility: %empty  */
#line 1368 "make_func.y"
                  { (yyval.visibility).name  = current_default_visibility_name;
                    (yyval.visibility).flags = current_default_visibility_flags;                          }
#line 2821 "make_func.c"
    break;

  case 75: /* opt_visibility: PRIVATE  */
#line 1370 "make_func.y"
                  { (yyval.visibility).name  = "private";
                    (yyval.visibility).flags = "0";                                                       }
#line 2828 "make_func.c"
    break;

  case 76: /* opt_visibility: PROTECTED  */
#line 1372 "make_func.y"
                  { (yyval.visibility).name  = "protected";
                    (yyval.visibility).flags = "TYPE_MOD_PRIVATE";                                        }
#line 2835 "make_func.c"
    break;

  case 77: /* opt_visibility: STATIC  */
#line 1374 "make_func.y"
                  { (yyval.visibility).name  = "static";
                    (yyval.visibility).flags = "TYPE_MOD_PRIVATE | TYPE_MOD_PROTECTED";                   }
#line 2842 "make_func.c"
    break;

  case 78: /* opt_visibility: VISIBLE  */
#line 1376 "make_func.y"
                  { (yyval.visibility).name  = "visible";
                    (yyval.visibility).flags = "TYPE_MOD_PRIVATE | TYPE_MOD_PROTECTED | TYPE_MOD_STATIC"; }
#line 2849 "make_func.c"
    break;

  case 79: /* opt_varargs: %empty  */
#line 1381 "make_func.y"
                 { (yyval.number) = 0; }
#line 2855 "make_func.c"
    break;

  case 80: /* opt_varargs: VARARGS  */
#line 1382 "make_func.y"
                 { (yyval.number) = 1; }
#line 2861 "make_func.c"
    break;

  case 81: /* applied_rettype: basic  */
#line 1386 "make_func.y"
                                { (yyval.returntype).void_allowed = false; (yyval.returntype).type = (lpc_type_t){(yyvsp[0].number), 0, NULL};}
#line 2867 "make_func.c"
    break;

  case 82: /* applied_rettype: basic '*'  */
#line 1387 "make_func.y"
                                { (yyval.returntype).void_allowed = false; (yyval.returntype).type = (lpc_type_t){(yyvsp[-1].number), MF_TYPE_MOD_POINTER, NULL}; }
#line 2873 "make_func.c"
    break;

  case 83: /* applied_rettype: STRING '|' STRING '*'  */
#line 1388 "make_func.y"
                                { (yyval.returntype).void_allowed = false; (yyval.returntype).type = (lpc_type_t){STRING_OR_STRING_ARRAY, 0, NULL}; }
#line 2879 "make_func.c"
    break;

  case 84: /* applied_rettype: STRING '|' INT  */
#line 1389 "make_func.y"
                                { (yyval.returntype).void_allowed = false; (yyval.returntype).type = (lpc_type_t){INT_OR_STRING, 0, NULL}; }
#line 2885 "make_func.c"
    break;

  case 85: /* applied_rettype: INT '|' STRING  */
#line 1390 "make_func.y"
                                { (yyval.returntype).void_allowed = false; (yyval.returntype).type = (lpc_type_t){INT_OR_STRING, 0, NULL}; }
#line 2891 "make_func.c"
    break;

  case 86: /* applied_rettype: VOID '|' basic  */
#line 1391 "make_func.y"
                                { (yyval.returntype).void_allowed = true;  (yyval.returntype).type = (lpc_type_t){(yyvsp[0].number), 0, NULL};}
#line 2897 "make_func.c"
    break;

  case 87: /* applied_args: %empty  */
#line 1395 "make_func.y"
                                        { (yyval.number) = 0; }
#line 2903 "make_func.c"
    break;

  case 88: /* applied_args: '.' '.' '.'  */
#line 1396 "make_func.y"
                                        { (yyval.number) = 1; }
#line 2909 "make_func.c"
    break;

  case 89: /* applied_args: applied_args2  */
#line 1397 "make_func.y"
                                        { (yyval.number) = 0; }
#line 2915 "make_func.c"
    break;

  case 90: /* applied_args: applied_args2 ',' '.' '.' '.'  */
#line 1398 "make_func.y"
                                        { (yyval.number) = 1; }
#line 2921 "make_func.c"
    break;

  case 93: /* applied_arg: applied_argtype  */
#line 1408 "make_func.y"
    {
        if (curr_arg_type_size == NELEMS(curr_arg_types))
            yyerror("Too many arguments");
        else
            curr_arg_types[curr_arg_type_size++] = (yyvsp[0].type);
    }
#line 2932 "make_func.c"
    break;

  case 94: /* applied_argtype: basic  */
#line 1417 "make_func.y"
                                { (yyval.type) = (lpc_type_t){(yyvsp[0].number), 0, NULL}; }
#line 2938 "make_func.c"
    break;

  case 95: /* applied_argtype: basic '*'  */
#line 1418 "make_func.y"
                                { (yyval.type) = (lpc_type_t){(yyvsp[-1].number), MF_TYPE_MOD_POINTER, NULL}; }
#line 2944 "make_func.c"
    break;

  case 96: /* applied_argtype: OBJECT '|' LWOBJECT  */
#line 1419 "make_func.y"
                                { (yyval.type) = (lpc_type_t){OBJECT_OR_LWOBJECT, 0, NULL}; }
#line 2950 "make_func.c"
    break;

  case 97: /* applied_argtype: LWOBJECT '|' OBJECT  */
#line 1420 "make_func.y"
                                { (yyval.type) = (lpc_type_t){OBJECT_OR_LWOBJECT, 0, NULL}; }
#line 2956 "make_func.c"
    break;

  case 98: /* applied_argtype: INT '|' STRING  */
#line 1421 "make_func.y"
                                { (yyval.type) = (lpc_type_t){INT_OR_STRING, 0, NULL}; }
#line 2962 "make_func.c"
    break;

  case 99: /* applied_argtype: STRING '|' INT  */
#line 1422 "make_func.y"
                                { (yyval.type) = (lpc_type_t){INT_OR_STRING, 0, NULL}; }
#line 2968 "make_func.c"
    break;

  case 100: /* applied_argtype: STRUCT '|' MAPPING '|' OBJECT '|' LWOBJECT '|' MIXED '*'  */
#line 1424 "make_func.y"
                                { (yyval.type) = (lpc_type_t){CATCH_MSG_ARG, 0, NULL}; }
#line 2974 "make_func.c"
    break;

  case 104: /* stringdef: ID NAME  */
#line 1435 "make_func.y"
    {
        char *cp;

        if (num_buff >= MAX_FUNC)
            yyerror("Too many string definitions!\n");

        /* Copy the data parsed into the instr[] array */
        /* Make the correct f_name and determine the code class
         */
        check_for_duplicate_string((yyvsp[-1].string), (yyvsp[0].string));
        instr[num_buff].key = mystrdup((yyvsp[-1].string));
        instr[num_buff].buf = mystrdup((yyvsp[0].string));

        /* Make sure that the .key is all uppercase */
        for (cp = instr[num_buff].key; *cp != '\0'; cp++)
            if (isalpha((unsigned char)*cp) && islower((unsigned char)*cp))
                *cp = toupper(*cp);

        /* Prepare for next string */

        num_buff++;
    }
#line 3001 "make_func.c"
    break;

  case 108: /* struct_def: STRUCT ID '{' struct_members '}' ';'  */
#line 1468 "make_func.y"
    {
        char buf[2048];
        char uname[512];
        int pos;

        make_upper_case_buf(uname, (yyvsp[-4].string), sizeof(uname));
        pos = snprintf(buf, sizeof(buf),
            "    STRUCT_%s = create_std_struct_type(STRUCT_IDX_%s,\n"
            "        &_lpctype_struct_%s, \"%s\",\n"
            "        (lpctype_t*[]){ "
            , uname, uname, (yyvsp[-4].string), (yyvsp[-4].string));

        for (int i = 0; i < current_struct_member; i++)
            pos += snprintf(buf + pos, sizeof(buf) - pos, "%s, ", lpctypestr(struct_member_types[i]));
        pos += snprintf(buf + pos, sizeof(buf) - pos, "NULL },\n        (const char*[]){ ");
        for (int i = 0; i < current_struct_member; i++)
            pos += snprintf(buf + pos, sizeof(buf) - pos, "\"%s\", ", struct_member_names[i]);
        pos += snprintf(buf + pos, sizeof(buf) - pos, "NULL });\n");

        struct_names[current_struct] = mystrdup((yyvsp[-4].string));
        struct_defs[current_struct]  = mystrdup(buf);

        pos = snprintf(buf, sizeof(buf), "enum struct_%s_enum\n{\n", (yyvsp[-4].string));
        for (int i = 0; i < current_struct_member; i++)
        {
            char umember[512];
            make_upper_case_buf(umember, struct_member_names[i], sizeof(umember));
            pos += snprintf(buf + pos, sizeof(buf) - pos, "    STRUCT_%s_%s,\n", uname, umember);
        }
        pos += snprintf(buf + pos, sizeof(buf) - pos, "};\n");

        struct_enums[current_struct]  = mystrdup(buf);
        current_struct++;

        for (int i = 0; i < current_struct_member; i++)
            free(struct_member_names[i]);
        current_struct_member = 0;
    }
#line 3044 "make_func.c"
    break;

  case 111: /* struct_member: struct_member_type ID ';'  */
#line 1514 "make_func.y"
    {
        struct_member_names[current_struct_member] = mystrdup((yyvsp[-1].string));
        struct_member_types[current_struct_member] = (yyvsp[-2].type);
        current_struct_member++;
    }
#line 3054 "make_func.c"
    break;

  case 112: /* struct_member_type: basic_utype opt_star  */
#line 1521 "make_func.y"
                                         { (yyval.type) = (lpc_type_t){(yyvsp[-1].number), (yyvsp[0].number), NULL}; }
#line 3060 "make_func.c"
    break;


#line 3064 "make_func.c"

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

#line 1525 "make_func.y"


#ifdef __MWERKS__
#    pragma warn_possunwant reset
#    pragma warn_implicitconv reset
#endif

/*=========================================================================*/

/*                            L E X E R                                    */

/* The Lexer is used to parse CONFIG, FILE_MACHINE, FUNC_SPEC and STRING_SPEC,
 * and to create THE_LANG from PRO_LANG.
 */

/*-------------------------------------------------------------------------*/

/* The recognized type names */

struct type {
    const char *name;  /* name of the type */
    int         num;   /* the type's parser code */
};

static struct type types[]
  = { { "void",         VOID }
    , { "int",          INT }
    , { "string",       STRING }
    , { "bytes",        BYTES }
    , { "object",       OBJECT }
    , { "mapping",      MAPPING }
    , { "float",        FLOAT }
    , { "closure",      CLOSURE }
    , { "symbol",       SYMBOL }
    , { "quoted_array", QUOTED_ARRAY }
    , { "mixed",        MIXED }
    , { "null",         NUL }
    , { "unknown",      UNKNOWN }
    , { "struct",       STRUCT }
    , { "lwobject",     LWOBJECT }
    , { "coroutine",    COROUTINE }
    , { "lpctype",      LPCTYPE }
    };

static struct type visibility[]
  = { { "visible",      VISIBLE }
    , { "static",       STATIC }
    , { "protected",    PROTECTED }
    , { "private",      PRIVATE }
    };

/*-------------------------------------------------------------------------*/

/* Defined macros.
 *
 * The macros are kept in the usual hashtable.
 */
#define MAKE_FUNC_DEFHASHBITS 7
#define MAKE_FUNC_DEFHASH (1 << MAKE_FUNC_DEFHASHBITS)
static INLINE hash16_t defhash(const char *str)
{
    size_t len = strlen(str);
    if (len > 12)
        len = 12;
    return hashmem32(str, len) & hashmask(MAKE_FUNC_DEFHASHBITS);
}

struct defn {
    char *name;         /* Macro name */
    char *exps;         /* Expanded macro text */
    int  num_arg;       /* Number of arguments or -1 for plain macros */
    struct defn *next;  /* Next entry in the hash chain */
};

static struct defn *deftab[MAKE_FUNC_DEFHASH];

/*-------------------------------------------------------------------------*/

/* The stack to handle pending #ifs.
 */

static struct ifstate {
    struct ifstate *next;
    int state;
} *iftop = NULL;

/* Values of ifstate.state: */

#define EXPECT_ELSE   1
#define EXPECT_ENDIF  2

/*-------------------------------------------------------------------------*/

static FILE *fpr, *fpw;
  /* Input and output file.
   */

static int current_line;
  /* Number of the current line.
   */

static const char *current_file;
  /* Name of the current file.
   */

static int last_line;
  /* Last line outside an %if-block.
   */

static char *outp;
  /* Next unprocessed character in the input buffer
   */

static int parsetype;
  /* Either PARSE_FUNC_SPEC or PARSE_STRING_SPEC, sent as first token back
   * to the parser.
   */

static Bool parsetype_sent = MY_FALSE;
  /* Set to TRUE after parsetype was sent to the parser.
   */

/*-------------------------------------------------------------------------*/

/* The definitions and tables for the preprocessor expression evaluator.
 * For a detailed explanation look into lex.c - it uses slightly
 * different tables, but the basic structure is the same.
 */


#define BNOT   1
#define LNOT   2
#define UMINUS 3
#define UPLUS  4

#define MULT   1
#define DIV    2
#define MOD    3
#define BPLUS  4
#define BMINUS 5
#define LSHIFT 6
#define RSHIFT 7
#define LESS   8
#define LEQ    9
#define GREAT 10
#define GEQ   11
#define EQ    12
#define NEQ   13
#define BAND  14
#define XOR   15
#define BOR   16
#define LAND  17
#define LOR   18
#define QMARK 19

static char _optab[]=
{0,4,0,0,0,26,56,0,0,0,18,14,0,10,0,22,0,0,0,0,0,0,0,0,0,0,0,0,30,50,40,74,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,70,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,63,0,1};
static char optab2[]=
{BNOT,0,0,LNOT,'=',NEQ,7,0,0,UMINUS,0,BMINUS,10,UPLUS,0,BPLUS,10,
0,0,MULT,11,0,0,DIV,11,0,0,MOD,11,
0,'<',LSHIFT,9,'=',LEQ,8,0,LESS,8,0,'>',RSHIFT,9,'=',GEQ,8,0,GREAT,8,
0,'=',EQ,7,0,0,0,'&',LAND,3,0,BAND,6,0,'|',LOR,2,0,BOR,4,
0,0,XOR,5,0,0,QMARK,1};
#define optab1(c) (_optab[(c)-' '])

/*-------------------------------------------------------------------------*/
static char
mygetc (void)

/* Return the next character from the input buffer.
 */

{
    return *outp++;
}

/*-------------------------------------------------------------------------*/
static void
myungetc (char c)

/* Unput character <c> so that the next mygetc() returns it.
 */

{
    *--outp = c;
}

/*-------------------------------------------------------------------------*/
static void
add_input (const char *p)

/* Insert text <p> at the current point in the input stream so that
 * the next mygetc()s will read it.
 */

{
    size_t l;

    l = strlen(p);
    outp -= l;
    memcpy(outp, p, l);
}

/*-------------------------------------------------------------------------*/
static void
add_define (const char * name, int num_arg, const char *exps)

/* Add the definition for the macro <name> with <num_arg> arguments
 * and replacement text <exps> to the table of macros.
 */

{
    hash16_t i;
    struct defn *ndef;

    i = defhash(name);
    ndef = malloc(sizeof(struct defn));
    if (!ndef)
    {
        abort();
    }
    ndef->next    = deftab[i];
    ndef->exps    = mystrdup(exps);
    ndef->num_arg = num_arg;
    ndef->name    = mystrdup(name);
    deftab[i]     = ndef;
}

/*-------------------------------------------------------------------------*/
static struct defn *
lookup_define (const char *s)

/* Lookup the macro <s> and return a pointer to its defn structure.
 * Return NULL if the macro is not defined.
 */

{
    struct defn *curr, *prev;
    hash16_t h;

    h = defhash(s);

    curr = deftab[h];
    prev = 0;
    while (curr)
    {
        if (!strcmp(curr->name, s)) /* found it */
        {
            if (prev) /* not at head of list */
            {
                prev->next = curr->next;
                curr->next = deftab[h];
                deftab[h] = curr;
            }
            return curr;
        }
        prev = curr;
        curr = curr->next;
    }

    /* not found */
    return NULL;
}

/*-------------------------------------------------------------------------*/
static int
expand_define (char *s)

/* Try to expand macro <s>.
 * If it is not defined, just return 0.
 * If it is a plain macro, add it to the input stream and return 1.
 * If it is a function macro, just return -1.
 */

{
    struct defn *p;

    p = lookup_define(s);
    if (!p)
        return 0;
    if (p->num_arg < 0)
    {
        add_input(p->exps);
    }
    else
    {
        return -1;
    }
    return 1;
}

/*-------------------------------------------------------------------------*/
static char *
nextword (char *str)

/* Find the next word in the input stream starting with <str> and
 * return a pointer to its first character. The end of the word
 * is marked with a '\0'.
 */

{
    char *cp;

    while (!lexwhite(*str)) str++;
    while ( lexwhite(*str)) str++;
    for (cp = str; isalunum(*cp); ) cp++;
    *cp = '\0';
    return str;
}

/*-------------------------------------------------------------------------*/
static Bool
skip_to (char mark, const char *token, const char *atoken)

/* Skip the file fpr linewise until one of the following control statements
 * is encountered:
 *   <mark>token:  returns true
 *   <mark>atoken: returns false (only if <atoken> is not NULL).
 *
 * An end of file aborts the program.
 * Nested <mark>if...<mark>endif blocks are skipped altogether.
 */

{
    char  b[20]; /* The word after <mark> */
    char *p;
    int   c;     /* Current character */
    int   nest;  /* <mark>if nesting depth */
    FILE *fp = fpr;

    for (nest = 0;;)
    {
        current_line++;
        c = fgetc(fp);

        if (c == mark)
        {
            /* Get the statement word into b[] */

            do {
                c = fgetc(fp);
            } while(lexwhite(c));

            for (p = b; c != '\n' && c != EOF; )
            {
                if (p < b+sizeof b-1)
                    *p++ = (char)c;
                c = fgetc(fp);
            }
            *p++ = '\0';
            for(p = b; *p && !lexwhite(*p); p++) NOOP;
            *p = '\0';

            if (strcmp(b, "if") == 0
             || strcmp(b, "ifdef") == 0
             || strcmp(b, "ifndef") == 0)
            {
                nest++;
            }
            else if (nest > 0)
            {
                if (strcmp(b, "endif") == 0)
                    nest--;
            }
            else
            {
                if (strcmp(b, token) == 0)
                    return MY_TRUE;
                else if (atoken && strcmp(b, atoken) == 0)
                    return MY_FALSE;
            }
        }
        else
        {
            /* Skip the line altogether */

            while (c != '\n' && c != EOF)
            {
                c = fgetc(fp);
            }
            if (c == EOF)
            {
                fprintf(stderr, "Unexpected end of file while skipping");
                abort();
            }
        }
    } /* for() */

    /* NOTREACHED */
} /* skip_to() */

/*-------------------------------------------------------------------------*/
static void
compensate_lines (void)

/* To compensate for skipped blocks, print as many \n to fpw as
 * the difference between last_line and current_line determines.
 * last_line is current_line+1 at the end.
 */
{
    for (; last_line <= current_line; last_line++)
        fputc('\n', fpw);
}

/*-------------------------------------------------------------------------*/
static void
handle_cond (char mark, int c)

/* Evaluate the boolean condition <c> of a preprocessor #if statement.
 * If necessary, skip to the condition branch to read next, and/or
 * push a new state onto the ifstate-stack.
 * If <mark> is '%', the number of skipped lines is compensated.
 */

{
    struct ifstate *p;

    if (c || skip_to(mark, "else", "endif"))
    {
        p = (struct ifstate *)malloc(sizeof(struct ifstate));
        p->next = iftop;
        iftop = p;
        p->state = c ? EXPECT_ELSE : EXPECT_ENDIF;
    }
    if (mark == '%')
        compensate_lines();
}

/*-------------------------------------------------------------------------*/
static void
handle_if (char mark, const char *str)

/* Evaluate the <mark>if condition <str>
 */

{
    int cond;

    add_input(str);
    cond = cond_get_exp(0);
    if (mygetc() != '\n')
    {
        yyerror("Condition too complex in #/%if");
        fflush(stdout);
        if (mark == '%')
            exit(1);
        while(mygetc() != '\n') NOOP;
    }
    else
        handle_cond(mark, cond);
}

/*-------------------------------------------------------------------------*/
static void
handle_else (char mark)

/* Handle an <mark>else statement.
 */

{
    if (iftop && iftop->state == EXPECT_ELSE)
    {
        struct ifstate *p = iftop;

        iftop = p->next;
        free((char *)p);
        skip_to(mark, "endif", (const char *)0);
    }
    else
    {
        fprintf(stderr, "Unexpected #/%%else line %d\n", current_line);
        abort();
    }
}

/*-------------------------------------------------------------------------*/
static void
handle_endif (void)

/* Handle an <mark>else statement.
 */

{
    if (iftop
     && (   iftop->state == EXPECT_ENDIF
         || iftop->state == EXPECT_ELSE))
    {
        struct ifstate *p = iftop;

        iftop = p->next;
        free((char *)p);
    }
    else
    {
        fprintf(stderr, "Unexpected #/%%endif line %d\n", current_line);
        abort();
    }
}

/*-------------------------------------------------------------------------*/
static int
name_to_hook(char *name)

/* Return the proper H_ value for the driverhook <name> which must
 * start with 'H_'
 * Return -1 if the name was not recognized.
 */

{
    while (isspace((unsigned char)*name))
        name++;
    if ( strncmp(name, "H_", (size_t)2) )
        return -1;
    name += 2;
    if ( !strcmp(name, "MOVE_OBJECT0") )
        return H_MOVE_OBJECT0;
    if ( !strcmp(name, "MOVE_OBJECT1") )
        return H_MOVE_OBJECT1;
    if ( !strcmp(name, "LOAD_UIDS") )
        return H_LOAD_UIDS;
    if ( !strcmp(name, "CLONE_UIDS") )
        return H_CLONE_UIDS;
    if ( !strcmp(name, "LWOBJECT_UIDS") )
        return H_LWOBJECT_UIDS;
    if ( !strcmp(name, "CREATE_SUPER") )
        return H_CREATE_SUPER;
    if ( !strcmp(name, "CREATE_OB") )
        return H_CREATE_OB;
    if ( !strcmp(name, "CREATE_CLONE") )
        return H_CREATE_CLONE;
    if ( !strcmp(name, "CREATE_LWOBJECT") )
        return H_CREATE_LWOBJECT;
    if ( !strcmp(name, "CREATE_LWOBJECT_COPY") )
        return H_CREATE_LWOBJECT_COPY;
    if ( !strcmp(name, "CREATE_LWOBJECT_RESTORE") )
        return H_CREATE_LWOBJECT_RESTORE;
    if ( !strcmp(name, "RESET") )
        return H_RESET;
    if ( !strcmp(name, "CLEAN_UP") )
        return H_CLEAN_UP;
    if ( !strcmp(name, "MODIFY_COMMAND") )
        return H_MODIFY_COMMAND;
    if ( !strcmp(name, "NOTIFY_FAIL") )
        return H_NOTIFY_FAIL;
    if ( !strcmp(name, "NO_IPC_SLOT") )
        return H_NO_IPC_SLOT;
    if ( !strcmp(name, "INCLUDE_DIRS") )
        return H_INCLUDE_DIRS;
    if ( !strcmp(name, "TELNET_NEG") )
        return H_TELNET_NEG;
    if ( !strcmp(name, "NOECHO") )
        return H_NOECHO;
    if ( !strcmp(name, "ERQ_STOP") )
        return H_ERQ_STOP;
    if ( !strcmp(name, "MODIFY_COMMAND_FNAME") )
        return H_MODIFY_COMMAND_FNAME;
    if ( !strcmp(name, "COMMAND") )
        return H_COMMAND;
    if ( !strcmp(name, "SEND_NOTIFY_FAIL") )
        return H_SEND_NOTIFY_FAIL;
    if ( !strcmp(name, "AUTO_INCLUDE") )
        return H_AUTO_INCLUDE;
    if ( !strcmp(name, "AUTO_INCLUDE_EXPRESSION") )
        return H_AUTO_INCLUDE_EXPRESSION;
    if ( !strcmp(name, "AUTO_INCLUDE_BLOCK") )
        return H_AUTO_INCLUDE_BLOCK;
    if ( !strcmp(name, "FILE_ENCODING") )
        return H_FILE_ENCODING;
    if ( !strcmp(name, "DEFAULT_METHOD") )
        return H_DEFAULT_METHOD;
    if ( !strcmp(name, "DEFAULT_PROMPT") )
        return H_DEFAULT_PROMPT;
    if ( !strcmp(name, "PRINT_PROMPT") )
        return H_PRINT_PROMPT;
    if ( !strcmp(name, "REGEXP_PACKAGE") )
        return H_REGEXP_PACKAGE;
    if ( !strcmp(name, "MSG_DISCARDED") )
        return H_MSG_DISCARDED;
    return -1;
}

/*-------------------------------------------------------------------------*/
static void
handle_map (char *str, int size, int (* name_to_index)(char *) )

/* Create a lookup table with <size> elements from the input
 * text <str> (and possibly more lines read from fpr if <str>
 * ends in \<newline>).
 *
 * The input text is supposed to be a comma separated list
 * of <index>:<value> pairs: the text "<index>" is parsed
 * and translated into a number by <name_to_index>().
 * <value> is the assigned to the table element indexed
 * by this number.
 *
 * Unassigned table elements default to the text '0' or
 * to the value set with a 'default:<value>' pair.
 *
 * After the list of pairs is read, the text for the table
 * is written as '{ <value>, ... , <value> }' to fpw.
 */

{
    char **map;        /* The map */
    char deflt[256];   /* Default table entry text */
    char *del = NULL;  /* Position of the current ':' or ',' */
    char *val;         /* Position of the current <value> */
    int i;
    char *output_del = "";  /* How to separate table entries */

    /* Initialize the map */

    map = (char **)alloca(size * sizeof *map);
    strcpy(deflt, "0");
    for (i = 0; i < size; i++) {
        map[i] = deflt;
    }

    /* Process the input list */

    do {

        /* Set str to the next non-blank character,
         * reading a new line if necessary
         */
        while (isspace((unsigned char)*str))
            str++;
        if (*str == '\\')
        {
            str = alloca((size_t)MAKE_FUNC_MAXLINE + 1);
            if (!fgets(str, MAKE_FUNC_MAXLINE, fpr))
                break;
            current_line++;
            if (del)
            {
                output_del = "\n";
            }
        }

        /* Find and mark the elements of the next pair */

        del = strchr(str, ':');
        if (!del)
            break;
        *del = '\0';
        val = del+1;
        del = strchr(val, ',');

        if (!del)
        {
            del = strchr(val, '\n');
            if (del)
            {
                *del = '\0';
                del = NULL;
            }
        }
        else
        {
            *del = '\0';
        }

        /* Evaluate the current pair */
        if ( !strcmp(str, "default") )
        {
            strncpy(deflt, val, sizeof(deflt)-1);
            deflt[sizeof deflt - 1] = '\0';
        }
        else
        {
            i = (*name_to_index)(str);
            if (i < 0)
            {
                fprintf(stderr, "Can't translate '%s' into an index.\n", str);
                exit(-1);
            }
            map[i] = val;
        }
        str = del+1;
    } while (del);

    /* Write the generated map */

    fprintf(fpw, "{");
    fputs(output_del, fpw);
    for (i = 0; i < size; i++)
    {
        fprintf(fpw, "%s,", map[i]);
        fputs(output_del, fpw);
    }
    fprintf(fpw, "};\n");
} /* handle_map() */

/*-------------------------------------------------------------------------*/
static int
exgetc(void)

/* Get the first character of the next element of a condition
 * and return it, leaving the input pointing to the rest of it.
 * Comments are skipped, identifiers not defined as macros are
 * replaced with ' 0 ', the predicate 'defined(<name>)' is
 * replaced with ' 0 ' or ' 1 ' depending on the result.
 */

{
    char c;

    c = mygetc();
    while (isalpha((unsigned char)c) || c == '_' )
    {
        char word[512], *p;
        int space_left;

        p = word;
        space_left = sizeof(word);
        do {
            *p++ = c;
            c = mygetc();
        } while (isalunum(c) && --space_left);
        if (!space_left)
             fatal("Too long word.\n");
        myungetc(c);
        *p = '\0';
        if (strcmp(word, "defined") == 0)
        {
            /* handle the defined "function" in #if */
            do c = mygetc(); while(lexwhite(c));
            if (c == '(')
            {
                // skip whitespaces between '(' and keyword.
                do c = mygetc(); while(lexwhite(c));
            }

            p = word;
            space_left = sizeof(word);
            while ( isalunum(c) && --space_left) {
                *p++ = c;
                c = mygetc();
            }
            *p = '\0';
            // skip all whitespaces following the keyword
            while(lexwhite(c)) c = mygetc();
            // if this is already the end of the line, we have to go back, so
            // that it is read again on next mygetc().
            if (c == '\n')
                myungetc((char)c);
            // if the keywords was enclose in '()', we are now at ')'. If not,
            // we may be at the next expression and have to go back one as
            // well.
            if (c != ')')
                myungetc((char)c);

            if (lookup_define(word))
                add_input(" 1 ");
            else
                add_input(" 0 ");
        }
        else
        {
            int res;

            res = expand_define(word);
            if (res < 0)
            {
                yyerror("Unimplemented macro expansion");
                return 0;
            }
            if (!res) add_input(" 0 ");
        }
        c = mygetc();
    }
    return c;
}

/*-------------------------------------------------------------------------*/
static int
cond_get_exp (int priority)

/* Evaluate the expression in the input buffer at a priority of at least
 * <priority> and return the result.
 *
 * The function assumes to be called at the proper beginning of
 * an expression, i.e. if it encounters an operator even before a value,
 * it must be unary.
 */

{
    int c;
    int value,value2,x;

    do c = exgetc(); while ( lexwhite(c) );

    /* Evaluate the first value */

    if (c == '(')
    {

        /* It's a parenthesized subexpression */

        value = cond_get_exp(0);
        do c = exgetc(); while ( lexwhite(c) );
        if (c != ')' )
        {
            yyerror("bracket not paired in #if");
            if (!c)
                myungetc('\0');
        }
    }
    else if ( ispunct(c) )
    {
        /* It is an unary operator */

        x = optab1(c);
        if (!x)
        {
            yyerror("illegal character in #if");
            return 0;
        }

        /* Get the value for this unary operator */
        value = cond_get_exp(12);

        /* Evaluate the operator */
        switch ( optab2[x-1] )
        {
        case BNOT  : value = ~value; break;
        case LNOT  : value = !value; break;
        case UMINUS: value = -value; break;
        case UPLUS : break; // nothing to be done
        default :
            yyerror("illegal unary operator in #if");
            return 0;
        }
    }
    else
    {
        /* It must be a number */

        int base;

        if ( !lexdigit(c) )
        {
            if (!c)
            {
                yyerror("missing expression in #if");
                myungetc('\0');
            }
            else
                yyerror("illegal character in #if");
            return 0;
        }
        value = 0;

        /* Determine the base of the number */
        if (c != '0')
            base=10;
        else
        {
            c = mygetc();
            if (c == 'x' || c == 'X' )
            {
                base = 16;
                c = mygetc();
            }
            else
                base = 8;
        }

        /* Now parse the number */
        for(;;)
        {
            if ( isdigit(c) )      x = -'0';
            else if ( isupper(c) ) x = -'A'+10;
            else if ( islower(c) ) x = -'a'+10;
            else break;
            x += c;
            if (x > base)
                break;
            value = value * base + x;
            c = mygetc();
        }
        myungetc((char)c);
    }

    /* Now evaluate the following <binop> <expr> pairs (if any) */

    for (;;)
    {
        do c = exgetc(); while ( lexwhite(c) );

        /* An operator must come next */
        if ( !ispunct(c) )
            break;

        /* Can it be an operator at all? */
        x = optab1(c);
        if (!x)
            break;

        /* See if the optab[] defines an operator for these characters
         */
        value2 = mygetc();
        for (;; x += 3)
        {
            if (!optab2[x])
            {
                myungetc((char)value2);
                if ( !optab2[x+1] )
                {
                    yyerror("illegal operator use in #if");
                    return 0;
                }
                break;
            }
            if (value2 == optab2[x])
                break;
        }

        /* If the priority of the operator is too low, we are done
         * with this (sub)expression.
         */
        if (priority >= optab2[x+2])
        {
            if (optab2[x])
                myungetc((char)value2);
            break;
        }

        /* Get the second operand and perform the operation */
        value2 = cond_get_exp(optab2[x+2]);

        switch ( optab2[x+1] )
        {
        case MULT   : value *= value2;          break;
        case DIV    : value /= value2;          break;
        case MOD    : value %= value2;          break;
        case BPLUS  : value += value2;          break;
        case BMINUS : value -= value2;          break;
        case LSHIFT : value <<= value2;         break;
        case RSHIFT : value >>= value2;         break;
        case LESS   : value = value <  value2;  break;
        case LEQ    : value = value <= value2;  break;
        case GREAT  : value = value >  value2;  break;
        case GEQ    : value = value >= value2;  break;
        case EQ     : value = value == value2;  break;
        case NEQ    : value = value != value2;  break;
        case BAND   : value &= value2;          break;
        case XOR    : value ^= value2;          break;
        case BOR    : value |= value2;          break;
        case LAND   : value = value && value2;  break;
        case LOR    : value = value || value2;  break;
        case QMARK  :
            do c=exgetc(); while( lexwhite(c) );
            if ( c!=':' )
            {
                yyerror("'?' without ':' in #if");
                myungetc((char)c);
                return 0;
            }
            if ( value )
            {
                cond_get_exp(1);
                value = value2;
            }
            else
                value = cond_get_exp(1);
            break;
        } /* switch() */
  } /* for() */

  myungetc((char)c);
  return value;
} /* cond_get_expr() */

/*-------------------------------------------------------------------------*/
static Bool
make_func_isescaped (char c)

/* Return true if <c> is one of the escapable characters (e.g. \r or \"),
 * false if not.
 */

{
    switch(c) {
      case '\007':
      case '\b'  :
      case '\t'  :
      case '\n'  :
      case '\013':
      case '\014':
      case '\r'  :
        return MY_TRUE;
    }
    if (c == '\\' || c == '\"')
        return MY_TRUE;
    return MY_FALSE;
}

/*-------------------------------------------------------------------------*/
static Bool
make_func_issavedel (char c)

/* Return true if <c> is a delimiter in save/restore object (e.g. ',' or ';'),
 * false if not.
 */

{
    switch(c) {
      case ',' : /* in Arrays   */
      case ';' : /* in Mappings */
      case ':' : /* in Mappings */
      case '|' : /* in Closures */
      case '\n':
        return MY_TRUE;
    }
    return MY_FALSE;
}

/*-------------------------------------------------------------------------*/
static int
ident (char c)

/* Parse an identifier (first character is <c>) from fpr and classify it.
 *
 * The typenames in types[] return the associated type code, the
 * string "default" returns DEFAULT (both only when currently parsing
 * for EFUN class identifiers in FUNC_SPEC).
 *
 * When parsing CODEs in FUNC_SPEC, the strings "unary", "binary", "ternary"
 * and "quaternary" return UN_OP, BIN_OP, TRI_OP and QUAT_OP respectively.
 *
 * Other identifiers are stored in yylval.string and return ID.
 */

{
    char buff[100];
    size_t len, i;

    for (len = 0; isalunum(c); c = (char)getc(fpr))
    {
        if (len == sizeof buff - 1)
        {
            yyerror("Too long indentifier");
            do c = (char)getc(fpr); while (isalunum(c));
            break;
        }
        buff[len++] = c;
    }
    (void)ungetc(c, fpr);

    buff[len] = '\0';

    if ( parsetype == PARSE_FUNC_SPEC && C_IS_EFUN(current_code_class) )
    {
        for (i=0; i < NELEMS(types); i++)
        {
            if (strcmp(buff, types[i].name) == 0)
            {
                yylval.number = types[i].num;
                return types[i].num;
            }
        }
        if (strcmp(buff, "default") == 0)
            return DEFAULT;
        if (strcmp(buff, "no_lightweight") == 0)
            return NO_LIGHTWEIGHT;
    }

    if ( parsetype == PARSE_FUNC_SPEC && C_IS_CODE(current_code_class) )
    {
        if (strcmp(buff, "unary") == 0)
            return UN_OP;
        if (strcmp(buff, "binary") == 0)
            return BIN_OP;
        if (strcmp(buff, "ternary") == 0)
            return TRI_OP;
        if (strcmp(buff, "quaternary") == 0)
            return QUAT_OP;
    }

    if ( parsetype == PARSE_APPLIED_SPEC )
    {
        for (i=0; i < NELEMS(types); i++)
        {
            if (strcmp(buff, types[i].name) == 0)
            {
                yylval.number = types[i].num;
                return types[i].num;
            }
        }
        for (i=0; i < NELEMS(visibility); i++)
        {
            if (strcmp(buff, visibility[i].name) == 0)
            {
                yylval.number = visibility[i].num;
                return visibility[i].num;
            }
        }
        if (strcmp(buff, "varargs") == 0)
            return VARARGS;
    }

    if ( parsetype == PARSE_STRUCT_SPEC )
    {
        for (i=0; i < NELEMS(types); i++)
        {
            if (strcmp(buff, types[i].name) == 0)
            {
                yylval.number = types[i].num;
                return types[i].num;
            }
        }
    }

    yylval.string = mystrdup(buff);
    return ID;
} /* ident() */

/*-------------------------------------------------------------------------*/
static INLINE const char *
type_str (int n)

/* Create a string representation of type <n> in a static buffer
 * and return it. Unknown types return 'What?'.
 */

{
    int type = n & 0xffff;
    size_t i;

    for (i = 0; i < NELEMS(types); i++)
    {
        if (types[i].num == type)
        {
            if (n & (MF_TYPE_MOD_REFERENCE|MF_TYPE_MOD_LVALUE))
            {
                static char buff[100];
                const char *str;

                str = type_str(n & ~(MF_TYPE_MOD_REFERENCE|MF_TYPE_MOD_LVALUE));
                if (strlen(str) + 3 > sizeof buff)
                    fatal("Local buffer too small in type_str()!\n");
                sprintf(buff, (n & MF_TYPE_MOD_LVALUE) ? "%s &&" : "%s &", str);
                return buff;
            }
            if (n & MF_TYPE_MOD_POINTER)
            {
                static char buff[100];

                if (strlen(types[i].name) + 3 > sizeof buff)
                    fatal("Local buffer too small in type_str()!\n");
                sprintf(buff, "%s *", types[i].name);
                return buff;
            }

            if (n & MF_TYPE_MOD_POINTER_POINTER)
            {
                static char buff[100];

                if (strlen(types[i].name) + 4 > sizeof buff)
                    fatal("Local buffer too small in type_str()!\n");
                sprintf(buff, "%s **", types[i].name);
                return buff;
            }
            return types[i].name;
        }
    }
    return "What?";
} /* type_str() */

/*-------------------------------------------------------------------------*/
static void
skip_comment (void)

/* Skip a block comment on the input stream fpr. It is assumed that
 * the begin marker was already read.
 */

{
    int c;

    for(;;) {
        while((c = getc(fpr)) != '*')
        {
            if (c == EOF)
            {
                yyerror("End of file in a comment");
                return;
            }
            if (c == '\n') {
                current_line++;
            }
        }
        do {
            if ((c = getc(fpr)) == '/')
                return;
            if (c == '\n') {
                current_line++;
            }
        } while(c == '*');
    }
} /* skip_comment() */

/*-------------------------------------------------------------------------*/
static int
yylex1 (void)

/* Parse the next lexical element from the input file and return
 * its token value and -1 on end of file.
 */

{
    register int c;

    for(;;)
    {
        size_t match_tmp;
#define MATCH(str) (isspace((unsigned char)line_buffer[match_tmp=strlen(str)]) &&\
                        strncmp(str, line_buffer, match_tmp) == 0)

        char line_buffer[MAKE_FUNC_MAXLINE+1];
        char defbuf[MAKE_FUNC_MAXLINE + 1];

        outp = defbuf + sizeof(defbuf) - 1;

        line_buffer[MAKE_FUNC_MAXLINE] = '\0';

        switch(c = getc(fpr))
        {
        case ' ':
        case '\t':
        case '\r':
            continue;

        case '#':
        {
            int line;
            char file[MAXPATHLEN+1];

            fgets(line_buffer, MAKE_FUNC_MAXLINE, fpr);
            if ( sscanf(line_buffer, "%d \"%s\"",&line,file ) == 2 )
            {
                current_line = line+1;
                continue;
            }
            current_line++;
            if MATCH("if") {
                handle_if('#', line_buffer+3);
            } else if MATCH("ifdef") {
                handle_cond('#', lookup_define(nextword(line_buffer)) != 0);
            } else if MATCH("ifndef") {
                handle_cond('#', lookup_define(nextword(line_buffer)) == 0);
                continue;
            } else if MATCH("else") {
                handle_else('#');
            } else if MATCH("endif") {
                handle_endif();
            } else {
                yyerror("unrecognised '#' directive\n");
            }
            continue;
        }

        case '%':
        {
            static int send_end = 0;

            if (send_end)
            {
                send_end = 0;
                ungetc('%', fpr);
                return END;
            }
            send_end = 1;
            fgets(line_buffer, MAKE_FUNC_MAXLINE, fpr);
            current_line++;
            if (parsetype == PARSE_FUNC_SPEC)
            {
                if (MATCH("codes"))  { current_code_class=C_CODE;  return CODES;  }
                if (MATCH("efuns"))  { current_code_class=C_EFUN;  return EFUNS;  }
                if (MATCH("tefuns")) { current_code_class=C_SEFUN; return TEFUNS; }
            }
            if (parsetype == PARSE_APPLIED_SPEC)
            {
                if (MATCH("master"))
                {
                    next_decl_line = master_decl_line;
                    current_decl_num = &master_decl_num;
                    current_decl_is_hook = false;
                    current_default_visibility_name = "protected";
                    current_default_visibility_flags = "TYPE_MOD_PRIVATE";
                    return APPLIED_MASTER;
                }
                if (MATCH("regular"))
                {
                    next_decl_line = regular_decl_line;
                    current_decl_num = &regular_decl_num;
                    current_decl_is_hook = false;
                    current_default_visibility_name = "visible";
                    current_default_visibility_flags = "TYPE_MOD_PRIVATE | TYPE_MOD_PROTECTED | TYPE_MOD_STATIC";
                    return APPLIED_REGULAR;
                }
                if (MATCH("hooks"))
                {
                    next_decl_line = hook_decl_line;
                    current_decl_num = &hook_decl_num;
                    current_decl_is_hook = true;
                    current_default_visibility_name = "visible";
                    current_default_visibility_flags = "TYPE_MOD_PRIVATE | TYPE_MOD_PROTECTED | TYPE_MOD_STATIC";
                    return APPLIED_HOOKS;
                }
            }
            return '%';

#undef MATCH
        }

        case '\"':
        {
            char buff[100];
            int len;

            for (len=0; c = getc(fpr),c != '\"';)
            {
                if (len == sizeof buff - 1)
                {
                    yyerror("Too long name");
                    do
                        c = getc(fpr);
                    while (c != '\"' && c != '\n' && c != EOF);
                    (void)ungetc(c, fpr);
                    break;
                }
                if (c == '\n' || c == EOF)
                {
                    yyerror("unterminated name");
                    (void)ungetc(c, fpr);
                    break;
                }
                buff[len++] = (char)c;
            }
            buff[len] = '\0';
            yylval.string = mystrdup(buff);
            return NAME;
        }

        case '\n':
          current_line++;
          continue;

        case EOF:
            return -1;

        case '/':
            if ( (c=getc(fpr)) == '*') {
                skip_comment();
                continue;
            } else {
                (void)ungetc(c, fpr);
                return '/';
            }
        case '&':
            if ((c=getc(fpr)) == '&')
                return LVALUE;
            ungetc(c, fpr);
            return '&';

        default:
            if (isalpha(c))
                return ident((char)c);
            return c;
        }
    } /* for() */
} /* yylex1() */

/*-------------------------------------------------------------------------*/
static int
yylex (void)

/* Parse the next lexical element from the input file and return
 * its token value and -1 on end of file.
 * This just calls yylex1().
 */

{
    int res;

    if (!parsetype_sent)
    {
        parsetype_sent = MY_TRUE;
        return parsetype;
    }

    res = yylex1();
#if 0
    fprintf(stderr,"yylex returns %d '%c'\n",res,res);
#endif
    return res;
}

/*-------------------------------------------------------------------------*/
static void
yyerror (const char *str)

/* Print the error message <str> with information about the current
 * parsing position and exit.
 */

{
    fprintf(stderr, "%s:%d: %s\n", current_file, current_line, str);
    exit(1);
}

/*=========================================================================*/

/*-------------------------------------------------------------------------*/
static const char *
etype (long n)

/* Express type <n> (in bitfield encoding) in the runtime type symbols
 * of interpret.h.
 * Return a pointer to a constant string.
 */

{
    static char str[200];

    if (n & LPC_T_ANY)
        return "TF_ANYTYPE";

    if (!n)
        return "0";

    str[0] = '\0';

#   define CONVERT(type, string) \
    if (n & type) \
    { \
        if (str[0] != '\0') \
            strcat(str, "|"); \
        strcat(str, string); \
        n ^= type; \
    }

    CONVERT(LPC_T_LVALUE, "TF_LVALUE");
    CONVERT(LPC_T_POINTER, "TF_POINTER");
    CONVERT(LPC_T_NUMBER, "TF_NUMBER");
    CONVERT(LPC_T_STRING, "TF_STRING");
    CONVERT(LPC_T_BYTES, "TF_BYTES");
    CONVERT(LPC_T_OBJECT, "TF_OBJECT");
    CONVERT(LPC_T_MAPPING, "TF_MAPPING");
    CONVERT(LPC_T_FLOAT, "TF_FLOAT");
    CONVERT(LPC_T_CLOSURE, "TF_CLOSURE");
    CONVERT(LPC_T_SYMBOL, "TF_SYMBOL");
    CONVERT(LPC_T_QUOTED_ARRAY, "TF_QUOTED_ARRAY");
    CONVERT(LPC_T_NULL, "TF_NULL");
    CONVERT(LPC_T_STRUCT, "TF_STRUCT");
    CONVERT(LPC_T_LWOBJECT, "TF_LWOBJECT");
    CONVERT(LPC_T_COROUTINE, "TF_COROUTINE");
    CONVERT(LPC_T_LPCTYPE, "TF_LPCTYPE");

#   undef CONVERT

    if (n != 0)
    {
        printf("Error: Can't convert bit-flags %lx to LPC runtime type.\n"
              , (long)n);
        yyerror("Illegal type for argument");
        return "What ?";
    }

    return str;
} /* etype() */

/*-------------------------------------------------------------------------*/
static long
type2flag (lpc_type_t t)

/* Convert type <t> into the bitfield value needed to create the LPC
 * argument types.
 */

{
    if (t.flags & MF_TYPE_MOD_REFERENCE)
        return LPC_T_LVALUE;

    if (t.flags & (MF_TYPE_MOD_POINTER|MF_TYPE_MOD_POINTER_POINTER))
        return LPC_T_POINTER;

    switch(t.token) {
      case VOID:    return 0;            break;
      case STRING:  return LPC_T_STRING; break;
      case BYTES:   return LPC_T_BYTES; break;
      case INT:     return LPC_T_NUMBER; break;
      case OBJECT:  return LPC_T_OBJECT; break;
      case MAPPING: return LPC_T_MAPPING; break;
      case FLOAT:   return LPC_T_FLOAT;   break;
      case CLOSURE: return LPC_T_CLOSURE; break;
      case SYMBOL:  return LPC_T_SYMBOL;  break;
      case MIXED:   return LPC_T_ANY;     break;
      case NUL:     return LPC_T_NULL;     break;
      case UNKNOWN: return LPC_T_ANY;     break;
      case QUOTED_ARRAY:
        return LPC_T_QUOTED_ARRAY; break;
      case STRUCT:  return LPC_T_STRUCT;  break;
      case LWOBJECT:return LPC_T_LWOBJECT; break;
      case COROUTINE: return LPC_T_COROUTINE; break;
      case LPCTYPE: return LPC_T_LPCTYPE; break;
    default: yyerror("(type2flag) Bad type!"); return 0;
    }
} /* type2flag() */

/*-------------------------------------------------------------------------*/
static const char *
lpctypestr (lpc_type_t t)

/* Express type <t> in the compiler type symbols of exec.h.
 * Return a pointer to a constant string.
 */

{
    const char *p = NULL;

    switch(t.token | t.flags)
    {
      case VOID:    p = "&_lpctype_void";         break;
      case STRING:  p = "&_lpctype_string";       break;
      case BYTES:   p = "&_lpctype_bytes";        break;
      case BYTES_OR_STRING:
                    p = "&_lpctype_string_bytes"; break;
      case INT:     p = "&_lpctype_int";          break;
      case OBJECT:  p = "&_lpctype_any_object";   break;
      case LWOBJECT:p = "&_lpctype_any_lwobject"; break;
      case MAPPING: p = "&_lpctype_mapping";      break;
      case STRUCT:
                if (t.struct_name == NULL)
                    p = "&_lpctype_any_struct";
                else
                {
                    char buf[100];
                    snprintf(buf, sizeof(buf), "&_lpctype_struct_%s", t.struct_name);
                    p = mystrdup(buf);
                }
                break;
      case FLOAT:   p = "&_lpctype_float";        break;
      case CLOSURE: p = "&_lpctype_closure";      break;
      case COROUTINE: p="&_lpctype_coroutine";    break;
      case LPCTYPE: p = "&_lpctype_lpctype";      break;
      case SYMBOL:  p = "&_lpctype_symbol";       break;
      case MIXED:   p = "&_lpctype_mixed";        break;
      case UNKNOWN: p = "&_lpctype_unknown";      break;
      case NUL:     p = "NULL";                   break;
      case QUOTED_ARRAY:
                    p = "&_lpctype_quoted_array"; break;
      case OBJECT_OR_LWOBJECT:
                    p = "&_lpctype_any_object_or_lwobject";
                                                  break;
      case MAPPING_OR_CLOSURE:
                    p = "&_lpctype_mapping_or_closure";
                                                  break;
      case INT_OR_STRING:
                    p = "&_lpctype_int_or_string";
                                                  break;
      case STRING_OR_STRING_ARRAY:
                    p = "&_lpctype_string_or_string_array";
                                                  break;
      case CATCH_MSG_ARG:
                    p = "&_lpctype_catch_msg_arg";
                                                  break;

      case MF_TYPE_MOD_POINTER|MIXED:
                    p = "&_lpctype_any_array";    break;
      case MF_TYPE_MOD_POINTER|INT:
                    p = "&_lpctype_int_array";    break;
      case MF_TYPE_MOD_POINTER|STRING:
                    p = "&_lpctype_string_array"; break;
      case MF_TYPE_MOD_POINTER|BYTES:
                    p = "&_lpctype_bytes_array";  break;
      case MF_TYPE_MOD_POINTER|BYTES_OR_STRING:
                    p = "&_lpctype_string_or_bytes_array";
                                                  break;
      case MF_TYPE_MOD_POINTER|SYMBOL:
                    p = "&_lpctype_symbol_array"; break;
      case MF_TYPE_MOD_POINTER|OBJECT:
                    p = "&_lpctype_object_array"; break;
      case MF_TYPE_MOD_POINTER|LWOBJECT:
                    p = "&_lpctype_lwobject_array";
                                                  break;
      case MF_TYPE_MOD_POINTER|OBJECT_OR_LWOBJECT:
                    p = "&_lpctype_any_object_or_lwobject_array";
                                                  break;

      case MF_TYPE_MOD_POINTER_POINTER|OBJECT_OR_LWOBJECT:
                    p = "&_lpctype_any_object_or_lwobject_array_array";
                                                  break;
      default: yyerror("(lpctypestr) Bad type!"); return 0;
    }

    return p;
} /* lpctypestr() */

/*-------------------------------------------------------------------------*/
static const char *
fulltypestr (lpc_type_t t)

/* Express type <t> in the compiler type symbols of exec.h.
 * Return a pointer to a constant string.
 */

{
    static char buff[100];        /* 100 is such a comfortable size :-) */

    int flags = t.flags;
    t.flags &= ~(MF_TYPE_MOD_REFERENCE|MF_TYPE_MOD_LVALUE);

    if (snprintf(buff, sizeof(buff), "{ %s, %s }",
        lpctypestr(t),
        (flags & MF_TYPE_MOD_LVALUE) ? "TYPE_MOD_LVALUE" :
        (flags & MF_TYPE_MOD_REFERENCE) ? "TYPE_MOD_REFERENCE" : "0") >= sizeof(buff))
            fatal("Local buffer overwritten in fulltypestr()");

    return buff;
} /* fulltypestr() */

/*-------------------------------------------------------------------------*/
static int
efuncmp (int i, int j)

/* Compare the function entries <i> and <j>.
 * Return 1 if <i> is greater than <j>, 0 if equal, <j> if lesser.
 *
 * This predicate is used to sort the function/code tables read
 * from FUNC_SPEC.
 */

{
    int result;

    result = instr[i].code_class - instr[j].code_class;
    if ( result )
        return result;
    if (C_IS_CODE(instr[i].code_class))
        return 0;
    return strcmp(instr[i].key, instr[j].key);
}

/*-------------------------------------------------------------------------*/
static void
read_config_file (char *fname)

/* Read the config file <fname> to learn about the defines used by the
 * gamedriver.
 */

{
    size_t match_tmp;
    char line_buffer[MAKE_FUNC_MAXLINE + 1];
    char defbuf[MAKE_FUNC_MAXLINE + 1];

    /* --- Read in the file to see what defines are used by the gamedriver ---
     */

    outp = defbuf + sizeof(defbuf) - 1;
    if ((fpr = fopen(fname, "r")) == 0)
    {
       perror(fname);
       fflush(stdout);
       exit(1);
    }
    current_line = 0;
    current_file = fname;

#define MATCH(str) (isspace((unsigned char)line_buffer[1+(match_tmp=strlen(str))]) &&\
                        strncmp(str, line_buffer+1, match_tmp) == 0)

    while (fgets(line_buffer, MAKE_FUNC_MAXLINE, fpr)) {
        char *name;

        current_line++;
        if ( *line_buffer != '#' )
            continue;
        if MATCH("if") {
            handle_if('#', line_buffer+4);
            continue;
        }
        if MATCH("ifdef") {
            handle_cond('#', lookup_define(nextword(line_buffer)) != 0);
            continue;
        }
        if MATCH("ifndef") {
            handle_cond('#', lookup_define(nextword(line_buffer)) == 0);
            continue;
        }
        if MATCH("else") {
            handle_else('#');
            continue;
        }
        if MATCH("endif") {
            handle_endif();
            continue;
        }
        if MATCH("undef") {
            struct defn *old_def;
            old_def = lookup_define(nextword(line_buffer));
            if (old_def)
                old_def->name[0] = '\0';
            continue;
        }
        if ( !MATCH("define") ) {
            continue;
        }
        /* <name> is trusted to be syntactically correct. After all, it was
         * included by the source of this program.
         */
        {
            char *cp, *exps;
            int num_arg;

            cp = line_buffer+8;
            while( isspace((unsigned char)*cp)) cp++;
            name = cp;
            while(isalunum((unsigned char)*cp)) cp++;
            num_arg = *cp == '(' ? 0 : -1;
            if (*cp == '\n') {
                exps = cp;
                *cp = '\0';
            } else {
                *cp++ = '\0';
                while( isspace((unsigned char)*cp)) cp++;
                exps = cp;
                while(*cp != '\n') cp++;
                *cp = '\0';
            }
            add_define(name, num_arg, exps);
        }
    }
    fclose(fpr);

#undef MATCH

} /* read_config_file() */

/*-------------------------------------------------------------------------*/
static void
read_config (void)

/* Read the file CONFIG to learn about the defines used by the gamedriver.
 */

{
    /* --- Read in CONFIG to see what defines are used by the gamedriver ---
     */

    read_config_file(CONFIG);

    /* Sanity check on some of those USE_ defines: undefine
     * those which are not supported on the host system.
     */
    {
        const char * defnames[] = {
#ifndef HAS_IPV6
                             "USE_IPV6",
#endif
#ifndef HAS_MYSQL
                             "USE_MYSQL",
#endif
                             NULL };
        int i;

        for (i = 0; defnames[i] != NULL; i++)
        {
            struct defn *old_def;
            old_def = lookup_define(defnames[i]);
            if (old_def)
            {
                old_def->name[0] = '\0';
            }
        }
    }
} /* read_config() */

/*-------------------------------------------------------------------------*/
static void
read_machine (void)

/* Read the file FILE_MACHINE to learn about the defines used by the machine.
 */

{
    /* Some predefined macros */

#ifdef DEBUG
    add_define("DEBUG", -1, "");
#endif
#ifdef HAVE_GETRUSAGE
    add_define("HAVE_GETRUSAGE",-1,"");
#endif
#ifdef TRACE_CODE
    add_define("TRACE_CODE",-1,"");
#endif

    /* --- Read in FILE_MACHINE to see what defines are used by the gamedriver ---
     */
    read_config_file(FILE_MACHINE);

} /* read_machine() */

/*-------------------------------------------------------------------------*/
static void
read_func_spec (void)

/* Read the file FUNC_SPEC and create the instruction tables.
 */

{
    int i, j;

    for (i = 0; i < C_TOTAL; i++)
        num_instr[i] = 0;

    if ((fpr = fopen(FUNC_SPEC, "r")) == NULL)
    {
        perror(FUNC_SPEC);
        exit(1);
    }
    got_error = 0;
    current_line = 1;
    current_file = FUNC_SPEC;
    parsetype = PARSE_FUNC_SPEC;
    parsetype_sent = MY_FALSE;
    num_buff = 0;
    min_arg = -1;
    unlimit_max = MY_FALSE;
    curr_arg_type_size = 0;
    curr_lpc_type_size = 0;
    curr_lpc_types[0] = 0;
    yyparse();
    fclose(fpr);

    /* Print code usage statistics */

    fprintf(stderr,
"Primary codes:        %3d\n"
"Primary efuns:        %3d\n"
"Tabled efuns:         %3d (%d + %d + %d + %d + %d)\n"
           , num_instr[C_CODE]
           , num_instr[C_EFUN]
           , num_instr[C_EFUN0]+num_instr[C_EFUN1]+num_instr[C_EFUN2]
                               +num_instr[C_EFUN3]+num_instr[C_EFUN4]
           , num_instr[C_EFUN0], num_instr[C_EFUN1], num_instr[C_EFUN2]
           , num_instr[C_EFUN3], num_instr[C_EFUN4]
        );
    fprintf(stderr,
"Tabled vararg efuns:  %3d\n"
           , num_instr[C_EFUNV]
        );
        /* Combining the two print statements into one triggers bugs on
         * AIX 5.2:
         *   Visual Age C 6.0 compiles the for() assignment 'i = C_CODE+1'
         *     such that i is assigned a large number (12298).
         *   gcc 2.9 generates code for the same assignment which causes
         *     the mkfunc program to segfault.
         * The bugs could not be reproduced with a simple test program.
         */

    /* Compute the code offsets.
     * This means that instr_offset[C_ALIAS] is also the
     * the number of real instructions.
     */
    instr_offset[C_CODE] = 0;
    for (i = C_CODE+1; i < C_TOTAL; i++)
    {
        instr_offset[i] = instr_offset[i-1] + num_instr[i-1];
    }

    /* Check if the code ranges has been exhausted
     */
    if ( (num_instr[C_CODE] + num_instr[C_EFUN]) > 255 )
        fatal("Codes exhausted!");

    for (i = C_EFUN+1; i < C_ALIAS; i++)
        if (num_instr[i] > 255)
            fatal("Codes exhausted!\n");

    if (num_instr[C_SEFUN])
    {
        printf("Sefuns: %d\n", num_instr[C_SEFUN]);
        fatal("Unclassified sefuns encountered.\n");
    }

    /* Now sort the table of functions and codes (eeek, bubblesort!)
     * This sort makes sure that functions of the same class
     * are consecutive within the instr[] array, and therefore
     * really are at the places where instr_offset[] says they are.
     * It therefore estables that the index in instr[] is the
     * instruction code.
     */

    for (i = num_buff; --i >= 0; )
    {
        for (j = 0; j < i; j++)
            if (efuncmp(i,j) < 0)
            {
                struct instrdata_s tmp;

                tmp = instr[i]; instr[i] = instr[j]; instr[j] = tmp;
            }
    }

} /* read_func_spec() */

/*-------------------------------------------------------------------------*/
static void
read_applied_spec ()

/* Read the file APPLIED_SPEC.
 */

{
    fpr = fopen(APPLIED_SPEC, "rt");
    if (fpr == NULL)
    {
        perror(APPLIED_SPEC);
        exit(1);
    }

    got_error = 0;
    current_line = 1;
    current_file = APPLIED_SPEC;
    parsetype = PARSE_APPLIED_SPEC;
    parsetype_sent = MY_FALSE;
    curr_lpc_type_size = 0;
    yyparse();
    fclose(fpr);
} /* read_applied_spec() */

/*-------------------------------------------------------------------------*/
static void
read_string_spec (void)

/* Read the file STRING_SPEC.
 */

{
    if ((fpr = fopen(STRING_SPEC, "r")) == NULL)
    {
        perror(STRING_SPEC);
        exit(1);
    }
    got_error = 0;
    current_line = 1;
    current_file = STRING_SPEC;
    parsetype = PARSE_STRING_SPEC;
    parsetype_sent = MY_FALSE;
    num_buff = 0;
    yyparse();
    fclose(fpr);

} /* read_string_spec() */

/*-------------------------------------------------------------------------*/
static void
read_struct_spec (void)

/* Read the file STRUCT_SPEC.
 */

{
    fpr = fopen(STRUCT_SPEC, "rt");
    if (fpr == NULL)
    {
        perror(STRUCT_SPEC);
        exit(1);
    }

    got_error = 0;
    current_line = 1;
    current_file = STRUCT_SPEC;
    parsetype = PARSE_STRUCT_SPEC;
    parsetype_sent = MY_FALSE;
    current_struct = 0;
    current_struct_member = 0;
    yyparse();
    fclose(fpr);

} /* read_struct_spec() */

/*-------------------------------------------------------------------------*/
static void
create_efun_defs (void)

/* Create the file EFUN_DEFS
 */

{
    int i, j, k;
    unsigned char c;
    char * pattern;

    if ((fpw = fopen(EFUN_DEFS, "w")) == NULL)
    {
       perror(EFUN_DEFS);
       exit(1);
    }

    fprintf(fpw,
"#ifndef EFUN_DEFS_C__\n"
"#define EFUN_DEFS_C__ 1\n"
"\n"
"/* DO NOT EDIT!\n"
" *\n"
" * This file is created automatically by make_func from\n"
" * the specifications in " FUNC_SPEC ".\n"
" * It is meant to be included in lex.c\n"
" */\n"
"\n"
"#include \"exec.h\"       /* struct instr_s == instr_t */\n"
"#include \"stdstructs.h\" /* lpctype_* definitions     */\n"
"#include \"types.h\"      /* lpctype_* definitions     */\n"
"#include \"prolang.h\"    /* Some aggregate types      */\n"
"\n"
           );

    fprintf(fpw,
"/*----------------------------------------------------------------------*/\n"
"\n"
"/* The table of all instructions\n"
" */\n"
"\n"
"instr_t instrs[] = {\n"
           );

    for (k = C_CODE, i = 0; k <= C_ALIAS; k++)
    {
        switch(k)
        {
        case C_CODE:  fprintf(fpw, "\n  /* --- codes --- */\n\n");
                      break;
        case C_EFUN:  fprintf(fpw, "\n  /* --- efuns --- */\n\n");
                      break;
        case C_EFUN0: fprintf(fpw, "\n  /* --- 0-arg efuns --- */\n\n");
                      break;
        case C_EFUN1: fprintf(fpw, "\n  /* --- 1-arg efuns --- */\n\n");
                      break;
        case C_EFUN2: fprintf(fpw, "\n  /* --- 2-arg efuns --- */\n\n");
                      break;
        case C_EFUN3: fprintf(fpw, "\n  /* --- 3-arg efuns --- */\n\n");
                      break;
        case C_EFUN4: fprintf(fpw, "\n  /* --- 4-arg efuns --- */\n\n");
                      break;
        case C_EFUNV: fprintf(fpw, "\n  /* --- vararg efuns --- */\n\n");
                      break;
        case C_ALIAS: fprintf(fpw, "\n  /* --- aliased efuns --- */\n\n");
                      break;
        }

        j = instr_offset[k] + num_instr[k];
        for (; i < j; i++) {
            fprintf(fpw, "  /* %3d */ %s", i, instr[i].buf);
        }
    }
    fprintf(fpw, "};\n\n\n");

    fprintf(fpw, "/* Aliased efuns.\n"
                 " * Index it with <code>-F_LAST_INSTRUCTION-1 to retrieve\n"
                 " * the real instruction code.\n"
                 " */\n\n");
    fprintf(fpw, "short efun_aliases[] = {\n");
    {
        Bool gotone = MY_FALSE;

        for (i = 0; i < num_buff; i++) {
            if (instr[i].code_class == C_ALIAS)
            {
                fprintf(fpw, "    %s,\n", instr[i].f_name);
                gotone = MY_TRUE;
            }
        }
        if (!gotone)
            fprintf(fpw, "    0 /* dummy to keep the compilers happy */\n");
    }
    fprintf(fpw, "};\n\n\n");

    fprintf(fpw,
"/* Table of function argument signatures (compiler).\n"
" * The internal structure is that of arg_types[] in make_func.\n"
" */\n\n"
          );
    fprintf(fpw, "fulltype_t efun_arg_types[] = {\n    /*   0 */ ");
    for (i = 0; i < last_current_type; i++)
    {
        if (arg_types[i].token == 0)
        {
            fprintf(fpw, "{ NULL, 0 },\n");

            if (i < last_current_type - 1)
                fprintf(fpw, "    /* %3d */ ", i+1);
        }
        else
            fprintf(fpw, "%s, ", fulltypestr(arg_types[i]));
    }
    fprintf(fpw, "};\n\n\n");

    fprintf(fpw,
"/* Table of function argument signatures (runtime).\n"
" * The internal structure is that of lpc_types[] in make_func.\n"
" */\n\n"
          );
    fprintf(fpw, "long efun_lpc_types[] = {\n ");
    for (i = 0; i < last_current_lpc_type; i++) {
        fprintf(fpw, "    /* %3d */ %s,\n", i, etype(lpc_types[i]));
    }
    fprintf(fpw, "};\n\n\n");

    pattern = "Variable 'pattern' not initialized.";
    for (k = C_EFUN0; k < C_ALIAS; k++)
    {

        switch(k)
        {
        case C_EFUN0:
            fprintf(fpw, "/* Prototypes of the tabled efuns\n */\n\n");
            pattern = "extern svalue_t *f_%s(svalue_t *);\n";
            break;
        case C_EFUNV:
            fprintf(fpw, "/* Prototypes of the tabled vararg efuns\n */\n\n");
            pattern = "extern svalue_t *v_%s(svalue_t *, int);\n";
            break;
        }

        i = instr_offset[k];
        j = i + num_instr[k];
        for (; i < j; i++)
        {
            fprintf(fpw, pattern, instr[i].key);
        }

        if (num_instr[k])
            fprintf(fpw, "\n\n");
    }

    {
        char * prefix = NULL;
        for (k = C_EFUN0; k < C_ALIAS; k++)
        {

            switch(k)
            {
            case C_EFUN0:
                fprintf(fpw, "/* The table of tabled efuns\n */\n\n");
                fprintf(fpw, "svalue_t *(*efun_table[]) (svalue_t *) = {\n");
                prefix = "f_";
                break;
            case C_EFUNV:
                fprintf(fpw, "/* The table of tabled vararg efuns\n */\n\n");
                fprintf(fpw, "svalue_t *(*vefun_table[]) (svalue_t *, int) = {\n");
                prefix = "v_";
                break;
            }

            i = instr_offset[k];
            j = i + num_instr[k];
            for(; i < j; i++)
            {
                fprintf(fpw, "    /* %3d */ %s%s,\n", i, prefix, instr[i].key);
            }

            if (k == C_EFUNV-1 || k == C_ALIAS-1)
                fprintf(fpw, "};\n\n\n");
        }
    }

    /* TODO: create a my-ctype.[ch] and a utility program to create
     * TODO:: these two files once and for all.
     */
    fprintf(fpw,
"/*----------------------------------------------------------------------*/\n"
"\n"
"/* Our own ctype implementation. This way we can be sure that\n"
" *   (a) we won't choke on non-ASCII characters\n"
" *   (b) we are fast\n"
" *   (c) we get the non-standard classifications we need anyway\n"
" */\n"
"\n"
           );

    fprintf(fpw, "#define lexwhite(c) (_my_ctype[(unsigned char)(c)]&%d)\n",_MCTs);
    fprintf(fpw, "#define leXdigit(c) (_my_ctype[(unsigned char)(c)]&%d)\n",_MCTx);

    fprintf(fpw, "\n" "unsigned char _my_ctype[] = {");
    c = '\0';
    do {
        if (!(c & 0xf))
            fprintf(fpw, "\n    ");
        fprintf(fpw, "%d,"
               ,  ( (isascii(c) && make_func_isescaped(c)) ? _MCTe : 0 )
                | ( (isascii(c) && make_func_issavedel(c)) ? _MCTt : 0 )
                | ( (isascii(c) && isdigit ((unsigned char)c))  ? _MCTd : 0 )
                | ( (isascii(c) && isspace ((unsigned char)c) && c != '\n')
                    ? _MCTs : 0 )
                | ( (isascii(c) && isxdigit((unsigned char)c))  ? _MCTx : 0 )
                | ( ((isascii(c) && (isalnum ((unsigned char)c) || c == '_'))
                   || (((unsigned char)c) >= 0xC0))
                    ? _MCTa : 0 )
               );
        c++;
    } while (c != '\0');
    fprintf(fpw, "\n};\n");


    fprintf(fpw,
"\n"
"/************************************************************************/\n"
"\n"
"#endif /* EFUN_DEFS_C__ */\n"
           );

    fclose(fpw);

} /* create_efun_defs() */

/*-------------------------------------------------------------------------*/
static void
create_instrs (void)

/* Create the file THE_INSTRS
 */

{
    int i, j, k;
    int last_instr;

    if ((fpw = fopen(THE_INSTRS, "w")) == NULL)
    {
       perror(THE_INSTRS);
       exit(1);
    }

    fprintf(fpw,
"#ifndef INSTRS_H__\n"
"#define INSTRS_H__ 1\n"
"\n"
"/* DO NOT EDIT!\n"
" *\n"
" * This file is created automatically by make_func from\n"
" * the specifications in " FUNC_SPEC ".\n"
" *\n"
" * It holds the bytecode values for all machine instructions, plus\n"
" * declarations of the tables holding information about the instructions.\n"
" */\n"
"\n"
"#include \"exec.h\"  /* struct instr_s == instr_t */\n"
"\n"
           );

    last_instr = instr_offset[C_ALIAS] - 1;

    for (k = C_CODE; k < C_ALIAS; k++)
    {
        char * str;

        switch (k)
        {
        case C_CODE:  str = "internal"; break;
        case C_EFUN:  str = "efun"; break;
        case C_EFUN0: str = "efun0"; break;
        case C_EFUN1: str = "efun1"; break;
        case C_EFUN2: str = "efun2"; break;
        case C_EFUN3: str = "efun3"; break;
        case C_EFUN4: str = "efun4"; break;
        case C_EFUNV: str = "efunv"; break;
        default:
          {
            char buf[100];
            sprintf(buf, "create_instrs(): Invalid value %ld for loop index.\n", (long)k);
            fatal(buf);
            str = NULL; /* To keep the compiler happy */
            break;
          }
        }

        fprintf(fpw,
"#define %s_OFFSET  (%d)\n"
"#define %s_COUNT   (%d)\n"
"  /* First offset and number of %s opcodes.\n"
"   */\n\n"
                , classtag[k], instr_offset[k]
                , classtag[k], num_instr[k]
                , str
                );
    }

    fprintf(fpw,
"#define LAST_INSTRUCTION_CODE (%d)\n"
"  /* The highest token value in use.\n"
"   */\n\n"
           , last_instr
    );

    fprintf(fpw,
"#define TEFUN_OFFSET EFUN0_OFFSET\n"
"  /* Offset of the first tabled efun.\n"
"   */\n\n"
    );

    fprintf(fpw, "extern instr_t instrs[];\n"
                 "extern short efun_aliases[];\n"
                 "extern fulltype_t efun_arg_types[];\n"
                 "extern long efun_lpc_types[];\n"
                 "extern svalue_t *(*efun_table[])(svalue_t *);\n"
                 "extern svalue_t *(*vefun_table[])(svalue_t *, int);\n"
    );

    fprintf(fpw,
"  /* All tables are defined in " EFUN_DEFS " and compiled into lex.c\n"
"   * TODO: We might as well create efun_defs.h and compile it separately.\n"
"   */\n"
           );

    for (k = C_CODE; k < C_ALIAS; k++)
    {
        if (!num_instr[k])
            continue;

        switch(k)
        {
        case C_CODE:  fprintf(fpw,"\n/* --- codes --- */\n\n");
                      break;
        case C_EFUN:  fprintf(fpw,"\n/* --- efuns --- */\n\n");
                      break;
        case C_EFUN0: fprintf(fpw,"\n/* --- efun0s --- */\n\n");
                      break;
        case C_EFUN1: fprintf(fpw,"\n/* --- efun1s --- */\n\n");
                      break;
        case C_EFUN2: fprintf(fpw,"\n/* --- efun2s --- */\n\n");
                      break;
        case C_EFUN3: fprintf(fpw,"\n/* --- efun3s --- */\n\n");
                      break;
        case C_EFUN4: fprintf(fpw,"\n/* --- efun4s --- */\n\n");
                      break;
        case C_EFUNV: fprintf(fpw,"\n/* --- vefuns --- */\n\n");
                      break;
        }

        i = instr_offset[k];
        j = i + num_instr[k];
        for ( ; i < j; i++)
        {
           fprintf(fpw, "#define %-30s (%d)\n"
                       , make_f_name(instr[i].key), i);
        }
    }

    fprintf(fpw,
"\n"
"/************************************************************************/\n"
"\n"
"#endif /* INSTRS_H__ */\n"
           );

    fclose(fpw);
} /* create_instrs() */

/*-------------------------------------------------------------------------*/
static void
create_applied_defs ()

/* Create the file APPLIED_DEFS.
 */

{
    int tbl_size;

    fpw = fopen(APPLIED_DEFS, "wt");
    if (fpw == NULL)
    {
        perror(APPLIED_DEFS);
        exit(1);
    }

    fprintf(fpw,
"/* DO NOT EDIT!\n"
" *\n"
" * This file is created automatically by make_func from the specification\n"
" * in " APPLIED_SPEC ".\n"
" */\n"
"\n"
"#include \"applied_decl.h\"\n"
"#include \"prolang.h\"\n"
"#include \"types.h\"\n"
"#include \"../mudlib/sys/driver_hook.h\"\n"
"\n"
"/*----------------------------------------------------------------------*/\n"
"\n"
"/* The applied lfuns for the master object.\n"
" */\n"
"\n"
"applied_decl_t applied_decl_master[] = {\n"
    );

    for (int i = 0; i < master_decl_num; i++)
        fprintf(fpw, "%s", master_decl_line[i]);

    fprintf(fpw,
"    { NULL }\n"
"};\n"
"\n"
"/*----------------------------------------------------------------------*/\n"
"\n"
"/* The applied lfuns for regular objects.\n"
" */\n"
"\n"
"applied_decl_t applied_decl_regular[] = {\n"
    );

    for (int i = 0; i < regular_decl_num; i++)
        fprintf(fpw, "%s", regular_decl_line[i]);

    fprintf(fpw,
"    { NULL }\n"
"};\n"
"\n"
"/*----------------------------------------------------------------------*/\n"
"\n"
"/* The applied lfuns for driver hooks.\n"
" */\n"
"\n"
"applied_decl_t applied_decl_hook[] = {\n"
    );

    for (int i = 0; i < hook_decl_num; i++)
        fprintf(fpw, "%s", hook_decl_line[i]);

    fprintf(fpw,
"    { NULL }\n"
"};\n"
"\n"
"/*----------------------------------------------------------------------*/\n"
"\n"
"/* List of function argument types.\n"
" * These are referenced by .arg_index from the declarations.\n"
" */\n"
"\n"
"lpctype_t* applied_decl_args[] = {\n"
    );

    for (int i = 0; i < last_current_type; i++)
        fprintf(fpw, "    /* %d */ %s,\n", i, lpctypestr(arg_types[i]));
    fprintf(fpw, "};\n");

    tbl_size = 1;
    while (tbl_size < (master_decl_num + regular_decl_num + hook_decl_num))
        tbl_size <<= 1;

    fprintf(fpw, "\n"
"/*----------------------------------------------------------------------*/\n"
"\n"
"/* Uninitialized hash table for use by the compiler.\n"
" */\n"
"\n"
"applied_decl_t* applied_decl_hash_table[%d];\n"
"int applied_decl_hash_table_mask = %d;\n"
"\n", tbl_size, tbl_size - 1
    );

    fclose(fpw);
} /* create_applied_defs() */

/*-------------------------------------------------------------------------*/
static void
create_lang (void)

/* Create the file THE_LANG from PRO_LANG,
 */

{
    size_t match_tmp;
    char line_buffer[MAKE_FUNC_MAXLINE + 1];
    Bool bPrintedNotice;

#define MATCH(str) (isspace((unsigned char)line_buffer[1+(match_tmp=strlen(str))]) &&\
                        strncmp(str, line_buffer+1, match_tmp) == 0)

    if ((fpr = fopen(PRO_LANG, "r")) == NULL)
    {
       perror(PRO_LANG);
       exit(1);
    }

    if ((fpw = fopen(THE_LANG, "w")) == NULL)
    {
       perror(THE_LANG);
       exit(1);
    }
    current_line = 0;
    bPrintedNotice = MY_FALSE;
    while (fgets(line_buffer, MAKE_FUNC_MAXLINE, fpr))
    {
        current_line++;
        if (*line_buffer == '%') {
            last_line = current_line;
            if MATCH("if") {
                handle_if('%', line_buffer+4);
                continue;
            }
            if MATCH("ifdef") {
                handle_cond('%', lookup_define(nextword(line_buffer)) != 0);
                continue;
            }
            if MATCH("ifndef") {
                handle_cond('%', lookup_define(nextword(line_buffer)) == 0);
                continue;
            }
            if MATCH("else") {
                handle_else('%');
                compensate_lines();
                continue;
            }
            if MATCH("endif") {
                handle_endif();
                compensate_lines();
                continue;
            }
            if MATCH("line") {
                fprintf(fpw, "#line %d \"%s\"\n", current_line+1, PRO_LANG);
                continue;
            }
            if MATCH("hookmap") {
                handle_map(line_buffer+9, NUM_DRIVER_HOOKS, name_to_hook);
                continue;
            }
            if MATCH("//") {
                /* c++ - resembling comment */
                fputs("\n", fpw);
                continue;
            }
            if (!bPrintedNotice) {
                if MATCH("{") {
                    bPrintedNotice = MY_TRUE;
                    fputs(
"%{\n"
"\n"
"/* DO NOT EDIT!\n"
" *\n"
" * This file is created automatically by make_func from\n"
" * the template " PRO_LANG " according to the specs in " FUNC_SPEC ".\n"
" */\n"
"\n"
                         , fpw);
                    fprintf(fpw, "#line %d \"%s\"\n", current_line+1, PRO_LANG);
                    continue;
                }
            }
        }
        else if(strspn(line_buffer, " \t{\n") == strlen(line_buffer) && strchr(line_buffer, '{'))
        {
             /* Add a #line pragma for each block. */
            fprintf(fpw, "#line %d \"%s\"\n", current_line, PRO_LANG);
        }
        fputs(line_buffer, fpw);
    }
    fclose(fpr), fclose(fpw);

#undef MATCH

} /* create_lang() */

/*-------------------------------------------------------------------------*/
static void
create_stdstrings (void)

/* Create the files STDSTRINGS.[ch].
 */

{
    int i;

    /* Create stdstrings.h */

    if ((fpw = fopen(STDSTRINGS ".h", "w")) == NULL)
    {
       perror(STDSTRINGS ".h");
       exit(1);
    }

    fputs(
"#ifndef STDSTRINGS_H__\n"
"#define STDSTRINGS_H__ 1\n"
"\n"
"/* DO NOT EDIT!\n"
" *\n"
" * This file is created automatically by make_func from\n"
" * the specifications in " STRING_SPEC ".\n"
" */\n"
"\n"
"#include \"driver.h\"\n"
"#include \"typedefs.h\"\n"
"\n"
"/* --- Common used shared strings. --- */\n"
"/* The most common strings, including all the predefined applies,\n"
" * are kept in shstrings[] for faster usage.\n"
" * The indices are SHX_xxx, the defines STR_xxx expand to shstring[SHX_xxx]\n"
" */\n"
"\n"
"enum StandardStrings {\n"
         , fpw);

    for (i = 0; i < num_buff; i++)
    {
        if (!i)
            fprintf(fpw, "    SHX_%-12s = 0 /* \"%s\" */\n"
                       , instr[i].key, instr[i].buf);
        else
            fprintf(fpw, "  , SHX_%-16s /* \"%s\" */\n"
                       , instr[i].key, instr[i].buf);
    }

    fputs(
"\n"
"  , SHSTR_NOSTRINGS /* The number of strings */\n"
"};\n"
"\n"
"extern string_t *shstring[SHSTR_NOSTRINGS];\n"
"\n"
         , fpw);

     for (i = 0; i < num_buff; i++)
     {
          fprintf(fpw, "#define STR_%-16s  shstring[SHX_%s]\n"
                     , instr[i].key, instr[i].key);
     }

    fputs(
"\n"
"/* --- Prototypes --- */\n"
"extern void init_standard_strings(void);\n"
"\n"
"#endif /* STDSTRINGS_H__ */\n"
         , fpw);

    fclose(fpw);

    /* Create stdstrings.c */

    if ((fpw = fopen(STDSTRINGS ".c", "w")) == NULL)
    {
       perror(STDSTRINGS ".c");
       exit(1);
    }

    fputs(
"/* DO NOT EDIT!\n"
" *\n"
" * This file is created automatically by make_func from\n"
" * the specifications in " STRING_SPEC ".\n"
" *\n"
" * It's purpose is to define and initialize the standard shared string\n"
" * table shstring[].\n"
" */\n"
"\n"
"#include \"driver.h\"\n"
"#include \"typedefs.h\"\n"
"\n"
"#include \"" STDSTRINGS ".h\"\n"
"#include \"mstrings.h\"\n"
"\n"
"/*-------------------------------------------------------------------------*/\n"
"\n"
"string_t *shstring[SHSTR_NOSTRINGS];\n"
"  /* Table of common used and therefore shared strings.\n"
"   */\n"
"\n"
"/*-------------------------------------------------------------------------*/\n"
"void\n"
"init_standard_strings (void)\n"
"\n"
"/* Initialize the common string table.\n"
" */\n"
"\n"
"{\n"
"#   define INIT(x,s) shstring[x] = mstring_new_tabled(s, STRING_ASCII MTRACE_ARG);\n"
"\n"
         , fpw);

    for (i = 0; i < num_buff; i++)
        fprintf(fpw, "    INIT(SHX_%s, \"%s\");\n"
                   , instr[i].key, instr[i].buf);

    fputs(
"\n"
"#   undef INIT\n"
"} /* init_standard_strings() */\n"
"\n"
"/************************************************************************/\n"
         , fpw);

    fclose(fpw);

} /* create_stdstrings() */

/*-------------------------------------------------------------------------*/
static void
create_stdstructs (void)

/* Create the files STDSTRUCTS.[ch].
 */

{
    /* Create stdstructs.h */

    fpw = fopen(STDSTRUCTS ".h", "wt");
    if (fpw == NULL)
    {
       perror(STDSTRUCTS ".h");
       exit(1);
    }

    fprintf(fpw,
"#ifndef STDSTRUCTS_H__\n"
"#define STDSTRUCTS_H__ 1\n"
"\n"
"/* DO NOT EDIT!\n"
" *\n"
" * This file is created automatically by make_func from\n"
" * the specifications in " STRUCT_SPEC ".\n"
" */\n"
"\n"
"#include \"structs.h\"\n"
"\n"
"/* --- Global LPC structs definitions. --- */\n"
"\n"
"enum std_struct_index\n"
"{\n");

    for (int i = 0; i < current_struct; i++)
    {
        char buf[512];
        snprintf(buf, sizeof(buf), "STRUCT_IDX_%s", struct_names[i]);
        make_upper_case(buf);
        fprintf(fpw, "    %s,\n", buf);
    }

    fprintf(fpw,
"\n"
"    STD_STRUCT_COUNT,\n"
"    STD_STRUCT_OFFSET = USHRT_MAX - STD_STRUCT_COUNT /* Offset in bytecodes. */\n"
"};\n"
"\n"
"extern struct_type_t *std_struct[STD_STRUCT_COUNT];\n"
"\n");

    for (int i = 0; i < current_struct; i++)
    {
        char buf[512];
        make_upper_case_buf(buf, struct_names[i], sizeof(buf));
        fprintf(fpw, "#define STRUCT_%-24s std_struct[STRUCT_IDX_%s]\n", buf, buf);
    }

    fprintf(fpw,
"\n"
"/* --- Member indices --- */\n"
"\n");

    for (int i = 0; i < current_struct; i++)
        fprintf(fpw, "%s\n", struct_enums[i]);

    fprintf(fpw,
"/* --- Corresponding LPC types. --- */\n"
"\n");

    for (int i = 0; i < current_struct; i++)
        fprintf(fpw, "extern lpctype_t _lpctype_struct_%s;\n", struct_names[i]);
    fprintf(fpw, "\n");
    for (int i = 0; i < current_struct; i++)
        fprintf(fpw, "extern lpctype_t *lpctype_struct_%s;\n", struct_names[i]);

    fprintf(fpw,
"\n"
"/* --- Prototypes. --- */\n"
"\n"
"extern void init_std_structs();\n"
"\n"
"#endif /* STDSTRUCTS_H__ */\n");
    fclose(fpw);

    /* Create stdstructs.c */

    fpw = fopen(STDSTRUCTS ".c", "wt");
    if (fpw == NULL)
    {
       perror(STDSTRUCTS ".c");
       exit(1);
    }

    fprintf(fpw,
"/* DO NOT EDIT!\n"
" *\n"
" * This file is created automatically by make_func from\n"
" * the specifications in " STRUCT_SPEC ".\n"
" *\n"
" * It's purpose is to define global struct definitions.\n"
" */\n"
"\n"
"#include \"driver.h\"\n"
"#include \"prolang.h\"\n"
"#include \"" STDSTRUCTS ".h\"\n"
"\n"
"/*-------------------------------------------------------------------------*/\n"
"\n"
"struct_type_t *std_struct[STD_STRUCT_COUNT];\n"
"  /* All global struct definitions.\n"
"   */\n"
"\n");

    for (int i = 0; i < current_struct; i++)
        fprintf(fpw, "lpctype_t _lpctype_struct_%s;\n", struct_names[i]);
    fprintf(fpw,
"  /* Static type definitions of global structs.\n"
"   */\n"
"\n");
    for (int i = 0; i < current_struct; i++)
        fprintf(fpw, "lpctype_t *lpctype_struct_%-23s = &_lpctype_struct_%s;\n", struct_names[i], struct_names[i]);

    fprintf(fpw,
"  /* Pointer to type definitions of global structs.\n"
"   */\n"
"\n"
"/*-------------------------------------------------------------------------*/\n"
"void\n"
"init_std_structs ()\n"
"\n"
"/* Create global struct definitions.\n"
" */\n"
"\n"
"{\n");

    for (int i = 0; i < current_struct; i++)
        fprintf(fpw, "%s\n", struct_defs[i]);

    fprintf(fpw,
"} /* init_std_structs() */\n"
"\n"
"/*-------------------------------------------------------------------------*/\n");

    fclose(fpw);

} /* create_stdstructs() */

/*-------------------------------------------------------------------------*/
int
main (int argc, char ** argv)

/* The main program.
 */

{
    enum { NONE = 0, MakeInstrs, MakeApplied, MakeLang, MakeStrings, MakeStructs } action = NONE;

    /* --- Check what we have to do --- */
    if (argc == 2)
    {
        if (!strcasecmp(argv[1], "instrs")) action = MakeInstrs;
        else if (!strcasecmp(argv[1], "applied")) action = MakeApplied;
        else if (!strcasecmp(argv[1], "lang")) action = MakeLang;
        else if (!strcasecmp(argv[1], "strings")) action = MakeStrings;
        else if (!strcasecmp(argv[1], "structs")) action = MakeStructs;
    }

    if (action == NONE)
    {
        fputs(
"Usage: make_func instrs|applied|lang|strings\n"
"\n"
"  make_func instrs\n"
"    creates " EFUN_DEFS " and " THE_INSTRS ", reads " CONFIG " and " FUNC_SPEC ".\n"
"\n"
"  make_func applied\n"
"    creates " APPLIED_DEFS ", reads " CONFIG " and " APPLIED_SPEC ".\n"
"\n"
"  make_func lang\n"
"    creates " THE_LANG " from " PRO_LANG ", reads " CONFIG ".\n"
"\n"
"  make_func strings\n"
"    creates " STDSTRINGS ".[ch], reads " CONFIG " and " STRING_SPEC ".\n"
"\n"
"  make_func stricts\n"
"    creates " STDSTRUCTS ".[ch], reads " CONFIG " and " STRUCT_SPEC ".\n"
             , stderr);
        return 1; /* TODO: There are constants for this */
    }

    /* --- Read the config files --- */
    read_machine();
    read_config();
    if (action == MakeInstrs)
        read_func_spec();

    if (action == MakeApplied)
        read_applied_spec();

    if (action == MakeStrings)
        read_string_spec();

    if (action == MakeStructs)
        read_struct_spec();

    if (got_error)
        return 1;

    /* --- Create the output files --- */
    if (action == MakeInstrs)
    {
        create_efun_defs();
        create_instrs();
    }
    if (action == MakeApplied)
        create_applied_defs();

    if (action == MakeLang)
        create_lang();

    if (action == MakeStrings)
        create_stdstrings();

    if (action == MakeStructs)
        create_stdstructs();

    /* --- That's it --- */

    return 0;

} /* main() */

#if defined(__MWERKS__) && !defined(WARN_ALL)
#    pragma warn_possunwant off
#    pragma warn_implicitconv off
#endif

/***************************************************************************/

