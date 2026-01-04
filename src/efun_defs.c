#ifndef EFUN_DEFS_C__
#define EFUN_DEFS_C__ 1

/* DO NOT EDIT!
 *
 * This file is created automatically by make_func from
 * the specifications in func_spec.
 * It is meant to be included in lex.c
 */

#include "exec.h"       /* struct instr_s == instr_t */
#include "stdstructs.h" /* lpctype_* definitions     */
#include "types.h"      /* lpctype_* definitions     */
#include "prolang.h"    /* Some aggregate types      */

/*----------------------------------------------------------------------*/

/* The table of all instructions
 */

instr_t instrs[] = {

  /* --- codes --- */

  /*   0 */ { 0, F_ILLEGAL-CODE_OFFSET, 0, 0, -1, NULL , -1, -1, false, false, "illegal", NULL },
  /*   1 */ { 0, F_UNDEF-CODE_OFFSET, 0, 0, -1, NULL , -1, -1, false, false, "undef", NULL },
  /*   2 */ { 0, F_EFUN0-CODE_OFFSET, 0, 0, -1, NULL , -1, -1, false, false, "efun0", NULL },
  /*   3 */ { 0, F_EFUN1-CODE_OFFSET, 0, 0, -1, NULL , -1, -1, false, false, "efun1", NULL },
  /*   4 */ { 0, F_EFUN2-CODE_OFFSET, 0, 0, -1, NULL , -1, -1, false, false, "efun2", NULL },
  /*   5 */ { 0, F_EFUN3-CODE_OFFSET, 0, 0, -1, NULL , -1, -1, false, false, "efun3", NULL },
  /*   6 */ { 0, F_EFUN4-CODE_OFFSET, 0, 0, -1, NULL , -1, -1, false, false, "efun4", NULL },
  /*   7 */ { 0, F_EFUNV-CODE_OFFSET, 0, 0, -1, NULL , -1, -1, false, false, "efunv", NULL },
  /*   8 */ { 0, F_IDENTIFIER-CODE_OFFSET, 0, 0, -1, NULL , -1, -1, false, false, "identifier", NULL },
  /*   9 */ { 0, F_STRING-CODE_OFFSET, 0, 0, -1, NULL , -1, -1, false, false, "string", NULL },
  /*  10 */ { 0, F_CSTRING0-CODE_OFFSET, 0, 0, -1, NULL , -1, -1, false, false, "cstring0", NULL },
  /*  11 */ { 0, F_CSTRING1-CODE_OFFSET, 0, 0, -1, NULL , -1, -1, false, false, "cstring1", NULL },
  /*  12 */ { 0, F_CSTRING2-CODE_OFFSET, 0, 0, -1, NULL , -1, -1, false, false, "cstring2", NULL },
  /*  13 */ { 0, F_CSTRING3-CODE_OFFSET, 0, 0, -1, NULL , -1, -1, false, false, "cstring3", NULL },
  /*  14 */ { 0, F_NUMBER-CODE_OFFSET, 0, 0, -1, NULL , -1, -1, false, false, "number", NULL },
  /*  15 */ { 0, F_CONST0-CODE_OFFSET, 0, 0, -1, NULL , -1, -1, false, false, "const0", NULL },
  /*  16 */ { 0, F_CONST1-CODE_OFFSET, 0, 0, -1, NULL , -1, -1, false, false, "const1", NULL },
  /*  17 */ { 0, F_NCONST1-CODE_OFFSET, 0, 0, -1, NULL , -1, -1, false, false, "nconst1", NULL },
  /*  18 */ { 0, F_CLIT-CODE_OFFSET, 0, 0, -1, NULL , -1, -1, false, false, "clit", NULL },
  /*  19 */ { 0, F_NCLIT-CODE_OFFSET, 0, 0, -1, NULL , -1, -1, false, false, "nclit", NULL },
  /*  20 */ { 0, F_FCONST0-CODE_OFFSET, 0, 0, -1, NULL , -1, -1, false, false, "fconst0", NULL },
  /*  21 */ { 0, F_FLOAT-CODE_OFFSET, 0, 0, -1, NULL , -1, -1, false, false, "float", NULL },
  /*  22 */ { 0, F_CLOSURE-CODE_OFFSET, 0, 0, -1, NULL , -1, -1, false, false, "closure", NULL },
  /*  23 */ { 0, F_SYMBOL-CODE_OFFSET, 0, 0, -1, NULL , -1, -1, false, false, "symbol", NULL },
  /*  24 */ { 0, F_RETURN-CODE_OFFSET, 0, 0, -1, NULL , -1, -1, false, false, "return", NULL },
  /*  25 */ { 0, F_RETURN0-CODE_OFFSET, 0, 0, -1, NULL , -1, -1, false, false, "return0", NULL },
  /*  26 */ { 0, F_DEFAULT_RETURN-CODE_OFFSET, 0, 0, -1, NULL , -1, -1, false, false, "default_return", NULL },
  /*  27 */ { 0, F_BREAK-CODE_OFFSET, 0, 0, -1, NULL , -1, -1, false, false, "break", NULL },
  /*  28 */ { 0, F_SWITCH-CODE_OFFSET, 0, 0, -1, NULL , -1, -1, false, false, "switch", NULL },
  /*  29 */ { 0, F_LOCAL-CODE_OFFSET, 0, 0, -1, NULL , -1, -1, false, false, "local", NULL },
  /*  30 */ { 0, F_CATCH-CODE_OFFSET, 0, 0, -1, NULL , -1, -1, false, false, "catch", NULL },
  /*  31 */ { 0, F_INC-CODE_OFFSET, 0, 0, -1, NULL , -1, -1, false, false, "++", NULL },
  /*  32 */ { 0, F_DEC-CODE_OFFSET, 0, 0, -1, NULL , -1, -1, false, false, "--", NULL },
  /*  33 */ { 0, F_POST_INC-CODE_OFFSET, 0, 0, -1, NULL , -1, -1, false, false, "x++", NULL },
  /*  34 */ { 0, F_POST_DEC-CODE_OFFSET, 0, 0, -1, NULL , -1, -1, false, false, "x--", NULL },
  /*  35 */ { 0, F_PRE_INC-CODE_OFFSET, 0, 0, -1, NULL , -1, -1, false, false, "++x", NULL },
  /*  36 */ { 0, F_PRE_DEC-CODE_OFFSET, 0, 0, -1, NULL , -1, -1, false, false, "--x", NULL },
  /*  37 */ { 0, F_LAND-CODE_OFFSET, 0, 0, -1, NULL , -1, -1, false, false, "&&", NULL },
  /*  38 */ { 0, F_LOR-CODE_OFFSET, 0, 0, -1, NULL , -1, -1, false, false, "||", NULL },
  /*  39 */ { 0, F_ASSIGN-CODE_OFFSET, 0, 0, -1, NULL , -1, -1, false, false, "=", NULL },
  /*  40 */ { 0, F_VOID_ASSIGN-CODE_OFFSET, 0, 0, -1, NULL , -1, -1, false, false, "(void)=", NULL },
  /*  41 */ { 0, F_ADD-CODE_OFFSET, 2, 2, 0, &_lpctype_mixed, -1, -1, false, false, "+", NULL },
  /*  42 */ { 0, F_SUBTRACT-CODE_OFFSET, 2, 2, 0, &_lpctype_mixed, -1, -1, false, false, "-", NULL },
  /*  43 */ { 0, F_MULTIPLY-CODE_OFFSET, 2, 2, 0, &_lpctype_mixed, -1, -1, false, false, "*", NULL },
  /*  44 */ { 0, F_DIVIDE-CODE_OFFSET, 2, 2, 0, &_lpctype_mixed, -1, -1, false, false, "/", NULL },
  /*  45 */ { 0, F_MOD-CODE_OFFSET, 2, 2, 0, &_lpctype_mixed, -1, -1, false, false, "%", NULL },
  /*  46 */ { 0, F_GT-CODE_OFFSET, 2, 2, 0, &_lpctype_mixed, -1, -1, false, false, ">", NULL },
  /*  47 */ { 0, F_GE-CODE_OFFSET, 2, 2, 0, &_lpctype_mixed, -1, -1, false, false, ">=", NULL },
  /*  48 */ { 0, F_LT-CODE_OFFSET, 2, 2, 0, &_lpctype_mixed, -1, -1, false, false, "<", NULL },
  /*  49 */ { 0, F_LE-CODE_OFFSET, 2, 2, 0, &_lpctype_mixed, -1, -1, false, false, "<=", NULL },
  /*  50 */ { 0, F_EQ-CODE_OFFSET, 2, 2, 0, &_lpctype_mixed, -1, -1, false, false, "==", NULL },
  /*  51 */ { 0, F_NE-CODE_OFFSET, 2, 2, 0, &_lpctype_mixed, -1, -1, false, false, "!=", NULL },
  /*  52 */ { 0, F_IN-CODE_OFFSET, 2, 2, 0, &_lpctype_mixed, -1, -1, false, false, "in", NULL },
  /*  53 */ { 0, F_COMPL-CODE_OFFSET, 1, 1, 0, &_lpctype_mixed, -1, -1, false, false, "~", NULL },
  /*  54 */ { 0, F_AND-CODE_OFFSET, 2, 2, 0, &_lpctype_mixed, -1, -1, false, false, "&", NULL },
  /*  55 */ { 0, F_OR-CODE_OFFSET, 2, 2, 0, &_lpctype_mixed, -1, -1, false, false, "|", NULL },
  /*  56 */ { 0, F_XOR-CODE_OFFSET, 2, 2, 0, &_lpctype_mixed, -1, -1, false, false, "^", NULL },
  /*  57 */ { 0, F_LSH-CODE_OFFSET, 2, 2, 0, &_lpctype_mixed, -1, -1, false, false, "<<", NULL },
  /*  58 */ { 0, F_RSH-CODE_OFFSET, 2, 2, 0, &_lpctype_mixed, -1, -1, false, false, ">>", NULL },
  /*  59 */ { 0, F_RSHL-CODE_OFFSET, 2, 2, 0, &_lpctype_mixed, -1, -1, false, false, ">>>", NULL },
  /*  60 */ { 0, F_NOT-CODE_OFFSET, 1, 1, 0, &_lpctype_mixed, -1, -1, false, false, "!", NULL },
  /*  61 */ { 0, F_INDEX-CODE_OFFSET, 2, 2, 0, &_lpctype_mixed, -1, -1, false, false, "[", NULL },
  /*  62 */ { 0, F_RINDEX-CODE_OFFSET, 2, 2, 0, &_lpctype_mixed, -1, -1, false, false, "[<", NULL },
  /*  63 */ { 0, F_AINDEX-CODE_OFFSET, 2, 2, 0, &_lpctype_mixed, -1, -1, false, false, "[>", NULL },
  /*  64 */ { 0, F_MAP_INDEX-CODE_OFFSET, 3, 3, 0, &_lpctype_mixed, -1, -1, false, false, "[,]", NULL },
  /*  65 */ { 0, F_MAP_RINDEX-CODE_OFFSET, 3, 3, 0, &_lpctype_mixed, -1, -1, false, false, "[,<]", NULL },
  /*  66 */ { 0, F_MAP_AINDEX-CODE_OFFSET, 3, 3, 0, &_lpctype_mixed, -1, -1, false, false, "[,>]", NULL },
  /*  67 */ { 0, F_S_INDEX-CODE_OFFSET, 2, 2, 0, &_lpctype_mixed, -1, -1, false, false, ".", NULL },
  /*  68 */ { 0, F_SX_INDEX-CODE_OFFSET, 2, 2, 0, &_lpctype_mixed, -1, -1, false, false, "->", NULL },
  /*  69 */ { 0, F_RANGE-CODE_OFFSET, 3, 3, 0, &_lpctype_mixed, -1, -1, false, false, "[..]", NULL },
  /*  70 */ { 0, F_NR_RANGE-CODE_OFFSET, 3, 3, 0, &_lpctype_mixed, -1, -1, false, false, "[..<]", NULL },
  /*  71 */ { 0, F_RN_RANGE-CODE_OFFSET, 3, 3, 0, &_lpctype_mixed, -1, -1, false, false, "[<..]", NULL },
  /*  72 */ { 0, F_RR_RANGE-CODE_OFFSET, 3, 3, 0, &_lpctype_mixed, -1, -1, false, false, "[<..<]", NULL },
  /*  73 */ { 0, F_NA_RANGE-CODE_OFFSET, 3, 3, 0, &_lpctype_mixed, -1, -1, false, false, "[..>]", NULL },
  /*  74 */ { 0, F_RA_RANGE-CODE_OFFSET, 3, 3, 0, &_lpctype_mixed, -1, -1, false, false, "[<..>]", NULL },
  /*  75 */ { 0, F_AN_RANGE-CODE_OFFSET, 3, 3, 0, &_lpctype_mixed, -1, -1, false, false, "[>..]", NULL },
  /*  76 */ { 0, F_AR_RANGE-CODE_OFFSET, 3, 3, 0, &_lpctype_mixed, -1, -1, false, false, "[>..<]", NULL },
  /*  77 */ { 0, F_AA_RANGE-CODE_OFFSET, 3, 3, 0, &_lpctype_mixed, -1, -1, false, false, "[>..>]", NULL },
  /*  78 */ { 0, F_NX_RANGE-CODE_OFFSET, 2, 2, 0, &_lpctype_mixed, -1, -1, false, false, "[..", NULL },
  /*  79 */ { 0, F_RX_RANGE-CODE_OFFSET, 2, 2, 0, &_lpctype_mixed, -1, -1, false, false, "[<..", NULL },
  /*  80 */ { 0, F_AX_RANGE-CODE_OFFSET, 2, 2, 0, &_lpctype_mixed, -1, -1, false, false, "[>..", NULL },
  /*  81 */ { 0, F_MAP_RANGE-CODE_OFFSET, 4, 4, 0, &_lpctype_mixed, -1, -1, false, false, "[,..]", NULL },
  /*  82 */ { 0, F_MAP_NR_RANGE-CODE_OFFSET, 4, 4, 0, &_lpctype_mixed, -1, -1, false, false, "[,..<]", NULL },
  /*  83 */ { 0, F_MAP_RN_RANGE-CODE_OFFSET, 4, 4, 0, &_lpctype_mixed, -1, -1, false, false, "[,<..]", NULL },
  /*  84 */ { 0, F_MAP_RR_RANGE-CODE_OFFSET, 4, 4, 0, &_lpctype_mixed, -1, -1, false, false, "[,<..<]", NULL },
  /*  85 */ { 0, F_MAP_NA_RANGE-CODE_OFFSET, 4, 4, 0, &_lpctype_mixed, -1, -1, false, false, "[,..>]", NULL },
  /*  86 */ { 0, F_MAP_RA_RANGE-CODE_OFFSET, 4, 4, 0, &_lpctype_mixed, -1, -1, false, false, "[,<..>]", NULL },
  /*  87 */ { 0, F_MAP_AN_RANGE-CODE_OFFSET, 4, 4, 0, &_lpctype_mixed, -1, -1, false, false, "[,>..]", NULL },
  /*  88 */ { 0, F_MAP_AR_RANGE-CODE_OFFSET, 4, 4, 0, &_lpctype_mixed, -1, -1, false, false, "[,>..<]", NULL },
  /*  89 */ { 0, F_MAP_AA_RANGE-CODE_OFFSET, 4, 4, 0, &_lpctype_mixed, -1, -1, false, false, "[,>..>]", NULL },
  /*  90 */ { 0, F_MAP_NX_RANGE-CODE_OFFSET, 3, 3, 0, &_lpctype_mixed, -1, -1, false, false, "[,..", NULL },
  /*  91 */ { 0, F_MAP_RX_RANGE-CODE_OFFSET, 3, 3, 0, &_lpctype_mixed, -1, -1, false, false, "[,<..", NULL },
  /*  92 */ { 0, F_MAP_AX_RANGE-CODE_OFFSET, 3, 3, 0, &_lpctype_mixed, -1, -1, false, false, "[,>..", NULL },
  /*  93 */ { 0, F_VOID_ADD_EQ-CODE_OFFSET, 0, 0, -1, NULL , -1, -1, false, false, "(void)+=", NULL },
  /*  94 */ { 0, F_ADD_EQ-CODE_OFFSET, 0, 0, -1, NULL , -1, -1, false, false, "+=", NULL },
  /*  95 */ { 0, F_SUB_EQ-CODE_OFFSET, 0, 0, -1, NULL , -1, -1, false, false, "-=", NULL },
  /*  96 */ { 0, F_DIV_EQ-CODE_OFFSET, 0, 0, -1, NULL , -1, -1, false, false, "/=", NULL },
  /*  97 */ { 0, F_MULT_EQ-CODE_OFFSET, 0, 0, -1, NULL , -1, -1, false, false, "*=", NULL },
  /*  98 */ { 0, F_MOD_EQ-CODE_OFFSET, 0, 0, -1, NULL , -1, -1, false, false, "%=", NULL },
  /*  99 */ { 0, F_AND_EQ-CODE_OFFSET, 0, 0, -1, NULL , -1, -1, false, false, "&=", NULL },
  /* 100 */ { 0, F_OR_EQ-CODE_OFFSET, 0, 0, -1, NULL , -1, -1, false, false, "|=", NULL },
  /* 101 */ { 0, F_XOR_EQ-CODE_OFFSET, 0, 0, -1, NULL , -1, -1, false, false, "^=", NULL },
  /* 102 */ { 0, F_LSH_EQ-CODE_OFFSET, 0, 0, -1, NULL , -1, -1, false, false, "<<=", NULL },
  /* 103 */ { 0, F_RSH_EQ-CODE_OFFSET, 0, 0, -1, NULL , -1, -1, false, false, ">>=", NULL },
  /* 104 */ { 0, F_RSHL_EQ-CODE_OFFSET, 0, 0, -1, NULL , -1, -1, false, false, ">>>=", NULL },
  /* 105 */ { 0, F_LAND_EQ-CODE_OFFSET, 0, 0, -1, NULL , -1, -1, false, false, "&&=", NULL },
  /* 106 */ { 0, F_LOR_EQ-CODE_OFFSET, 0, 0, -1, NULL , -1, -1, false, false, "||=", NULL },
  /* 107 */ { 0, F_POP_VALUE-CODE_OFFSET, 0, 0, -1, NULL , -1, -1, false, false, ",", NULL },
  /* 108 */ { 0, F_POP_SECOND-CODE_OFFSET, 0, 0, -1, NULL , -1, -1, false, false, "pop_second", NULL },
  /* 109 */ { 0, F_DUP-CODE_OFFSET, 0, 0, -1, NULL , -1, -1, false, false, "dup", NULL },
  /* 110 */ { 0, F_LDUP-CODE_OFFSET, 0, 0, -1, NULL , -1, -1, false, false, "ldup", NULL },
  /* 111 */ { 0, F_SWAP_VALUES-CODE_OFFSET, 0, 0, -1, NULL , -1, -1, false, false, "swap_values", NULL },
  /* 112 */ { 0, F_CLEAR_LOCALS-CODE_OFFSET, 0, 0, -1, NULL , -1, -1, false, false, "clear_locals", NULL },
  /* 113 */ { 0, F_SAVE_ARG_FRAME-CODE_OFFSET, 0, 0, -1, NULL , -1, -1, false, false, "save_arg_frame", NULL },
  /* 114 */ { 0, F_RESTORE_ARG_FRAME-CODE_OFFSET, 0, 0, -1, NULL , -1, -1, false, false, "restore_arg_frame", NULL },
  /* 115 */ { 0, F_USE_ARG_FRAME-CODE_OFFSET, 0, 0, -1, NULL , -1, -1, false, false, "use_arg_frame", NULL },
  /* 116 */ { 0, F_FLATTEN_XARG-CODE_OFFSET, 0, 0, -1, NULL , -1, -1, false, false, "flatten_xarg", NULL },
  /* 117 */ { 0, F_FBRANCH-CODE_OFFSET, 0, 0, -1, NULL , -1, -1, false, false, "fbranch", NULL },
  /* 118 */ { 0, F_LBRANCH-CODE_OFFSET, 0, 0, -1, NULL , -1, -1, false, false, "lbranch", NULL },
  /* 119 */ { 0, F_LBRANCH_WHEN_ZERO-CODE_OFFSET, 0, 0, -1, NULL , -1, -1, false, false, "lbranch_when_zero", NULL },
  /* 120 */ { 0, F_LBRANCH_WHEN_NON_ZERO-CODE_OFFSET, 0, 0, -1, NULL , -1, -1, false, false, "lbranch_when_non_zero", NULL },
  /* 121 */ { 0, F_BRANCH-CODE_OFFSET, 0, 0, -1, NULL , -1, -1, false, false, "branch", NULL },
  /* 122 */ { 0, F_BRANCH_WHEN_ZERO-CODE_OFFSET, 0, 0, -1, NULL , -1, -1, false, false, "?", NULL },
  /* 123 */ { 0, F_BRANCH_WHEN_NON_ZERO-CODE_OFFSET, 0, 0, -1, NULL , -1, -1, false, false, "?!", NULL },
  /* 124 */ { 0, F_BBRANCH_WHEN_ZERO-CODE_OFFSET, 0, 0, -1, NULL , -1, -1, false, false, "bbranch_when_zero", NULL },
  /* 125 */ { 0, F_BBRANCH_WHEN_NON_ZERO-CODE_OFFSET, 0, 0, -1, NULL , -1, -1, false, false, "bbranch_when_non_zero", NULL },
  /* 126 */ { 0, F_CALL_FUNCTION-CODE_OFFSET, 0, 0, -1, NULL , -1, -1, false, false, "call_function", NULL },
  /* 127 */ { 0, F_CALL_INHERITED-CODE_OFFSET, 0, 0, -1, NULL , -1, -1, false, false, "call_inherited", NULL },
  /* 128 */ { 0, F_CALL_INHERITED_NOARGS-CODE_OFFSET, 0, 0, -1, NULL , -1, -1, false, false, "call_inherited_noargs", NULL },
  /* 129 */ { 0, F_CALL_CLOSURE-CODE_OFFSET, 0, 0, -1, NULL , -1, -1, false, false, "call_closure", NULL },
  /* 130 */ { 0, F_CONTEXT_CLOSURE-CODE_OFFSET, 0, 0, -1, NULL , -1, -1, false, false, "context_closure", NULL },
  /* 131 */ { 0, F_CONTEXT_LAMBDA-CODE_OFFSET, 0, 0, -1, NULL , -1, -1, false, false, "context_lambda", NULL },
  /* 132 */ { 0, F_CONTEXT_IDENTIFIER-CODE_OFFSET, 0, 0, -1, NULL , -1, -1, false, false, "context_identifier", NULL },
  /* 133 */ { 0, F_TRANSFORM_TO_COROUTINE-CODE_OFFSET, 0, 0, -1, NULL , -1, -1, false, false, "transform_to_coroutine", NULL },
  /* 134 */ { 0, F_AWAIT-CODE_OFFSET, 0, 0, -1, NULL , -1, -1, false, false, "await", NULL },
  /* 135 */ { 0, F_YIELD_TO_COROUTINE-CODE_OFFSET, 0, 0, -1, NULL , -1, -1, false, false, "yield_to_coroutine", NULL },
  /* 136 */ { 0, F_YIELD_RETURN-CODE_OFFSET, 0, 0, -1, NULL , -1, -1, false, false, "yield_return", NULL },
  /* 137 */ { 0, F_PUSH_CONTEXT_LVALUE-CODE_OFFSET, 0, 0, -1, NULL , -1, -1, false, false, "push_context_lvalue", NULL },
  /* 138 */ { 0, F_CONTEXT_IDENTIFIER16-CODE_OFFSET, 0, 0, -1, NULL , -1, -1, false, false, "context_identifier16", NULL },
  /* 139 */ { 0, F_PUSH_CONTEXT16_LVALUE-CODE_OFFSET, 0, 0, -1, NULL , -1, -1, false, false, "push_context16_lvalue", NULL },
  /* 140 */ { 0, F_PUSH_IDENTIFIER_LVALUE-CODE_OFFSET, 0, 0, -1, NULL , -1, -1, false, false, "push_identifier_lvalue", NULL },
  /* 141 */ { 0, F_VIRTUAL_VARIABLE-CODE_OFFSET, 0, 0, -1, NULL , -1, -1, false, false, "virtual_variable", NULL },
  /* 142 */ { 0, F_PUSH_VIRTUAL_VARIABLE_LVALUE-CODE_OFFSET, 0, 0, -1, NULL , -1, -1, false, false, "push_virtual_variable_lvalue", NULL },
  /* 143 */ { 0, F_IDENTIFIER16-CODE_OFFSET, 0, 0, -1, NULL , -1, -1, false, false, "identifier16", NULL },
  /* 144 */ { 0, F_PUSH_IDENTIFIER16_LVALUE-CODE_OFFSET, 0, 0, -1, NULL , -1, -1, false, false, "push_identifier16_lvalue", NULL },
  /* 145 */ { 0, F_PUSH_LOCAL_VARIABLE_LVALUE-CODE_OFFSET, 0, 0, -1, NULL , -1, -1, false, false, "push_local_variable_lvalue", NULL },
  /* 146 */ { 0, F_INDEX_LVALUE-CODE_OFFSET, 0, 0, -1, NULL , -1, -1, false, false, "index_lvalue", NULL },
  /* 147 */ { 0, F_RINDEX_LVALUE-CODE_OFFSET, 0, 0, -1, NULL , -1, -1, false, false, "rindex_lvalue", NULL },
  /* 148 */ { 0, F_AINDEX_LVALUE-CODE_OFFSET, 0, 0, -1, NULL , -1, -1, false, false, "aindex_lvalue", NULL },
  /* 149 */ { 0, F_S_INDEX_LVALUE-CODE_OFFSET, 0, 0, -1, NULL , -1, -1, false, false, "s_index_lvalue", NULL },
  /* 150 */ { 0, F_SX_INDEX_LVALUE-CODE_OFFSET, 0, 0, -1, NULL , -1, -1, false, false, "sx_index_lvalue", NULL },
  /* 151 */ { 0, F_RANGE_LVALUE-CODE_OFFSET, 0, 0, -1, NULL , -1, -1, false, false, "range_lvalue", NULL },
  /* 152 */ { 0, F_NR_RANGE_LVALUE-CODE_OFFSET, 0, 0, -1, NULL , -1, -1, false, false, "nr_range_lvalue", NULL },
  /* 153 */ { 0, F_RN_RANGE_LVALUE-CODE_OFFSET, 0, 0, -1, NULL , -1, -1, false, false, "rn_range_lvalue", NULL },
  /* 154 */ { 0, F_RR_RANGE_LVALUE-CODE_OFFSET, 0, 0, -1, NULL , -1, -1, false, false, "rr_range_lvalue", NULL },
  /* 155 */ { 0, F_NA_RANGE_LVALUE-CODE_OFFSET, 0, 0, -1, NULL , -1, -1, false, false, "na_range_lvalue", NULL },
  /* 156 */ { 0, F_RA_RANGE_LVALUE-CODE_OFFSET, 0, 0, -1, NULL , -1, -1, false, false, "ra_range_lvalue", NULL },
  /* 157 */ { 0, F_AN_RANGE_LVALUE-CODE_OFFSET, 0, 0, -1, NULL , -1, -1, false, false, "an_range_lvalue", NULL },
  /* 158 */ { 0, F_AR_RANGE_LVALUE-CODE_OFFSET, 0, 0, -1, NULL , -1, -1, false, false, "ar_range_lvalue", NULL },
  /* 159 */ { 0, F_AA_RANGE_LVALUE-CODE_OFFSET, 0, 0, -1, NULL , -1, -1, false, false, "aa_range_lvalue", NULL },
  /* 160 */ { 0, F_NX_RANGE_LVALUE-CODE_OFFSET, 0, 0, -1, NULL , -1, -1, false, false, "nx_range_lvalue", NULL },
  /* 161 */ { 0, F_RX_RANGE_LVALUE-CODE_OFFSET, 0, 0, -1, NULL , -1, -1, false, false, "rx_range_lvalue", NULL },
  /* 162 */ { 0, F_AX_RANGE_LVALUE-CODE_OFFSET, 0, 0, -1, NULL , -1, -1, false, false, "ax_range_lvalue", NULL },
  /* 163 */ { 0, F_MAP_INDEX_LVALUE-CODE_OFFSET, 0, 0, -1, NULL , -1, -1, false, false, "map_index_lvalue", NULL },
  /* 164 */ { 0, F_MAP_RINDEX_LVALUE-CODE_OFFSET, 0, 0, -1, NULL , -1, -1, false, false, "map_rindex_lvalue", NULL },
  /* 165 */ { 0, F_MAP_AINDEX_LVALUE-CODE_OFFSET, 0, 0, -1, NULL , -1, -1, false, false, "map_aindex_lvalue", NULL },
  /* 166 */ { 0, F_MAP_RANGE_LVALUE-CODE_OFFSET, 0, 0, -1, NULL , -1, -1, false, false, "map_range_lvalue", NULL },
  /* 167 */ { 0, F_MAP_NR_RANGE_LVALUE-CODE_OFFSET, 0, 0, -1, NULL , -1, -1, false, false, "map_nr_range_lvalue", NULL },
  /* 168 */ { 0, F_MAP_RN_RANGE_LVALUE-CODE_OFFSET, 0, 0, -1, NULL , -1, -1, false, false, "map_rn_range_lvalue", NULL },
  /* 169 */ { 0, F_MAP_RR_RANGE_LVALUE-CODE_OFFSET, 0, 0, -1, NULL , -1, -1, false, false, "map_rr_range_lvalue", NULL },
  /* 170 */ { 0, F_MAP_NA_RANGE_LVALUE-CODE_OFFSET, 0, 0, -1, NULL , -1, -1, false, false, "map_na_range_lvalue", NULL },
  /* 171 */ { 0, F_MAP_RA_RANGE_LVALUE-CODE_OFFSET, 0, 0, -1, NULL , -1, -1, false, false, "map_ra_range_lvalue", NULL },
  /* 172 */ { 0, F_MAP_AN_RANGE_LVALUE-CODE_OFFSET, 0, 0, -1, NULL , -1, -1, false, false, "map_an_range_lvalue", NULL },
  /* 173 */ { 0, F_MAP_AR_RANGE_LVALUE-CODE_OFFSET, 0, 0, -1, NULL , -1, -1, false, false, "map_ar_range_lvalue", NULL },
  /* 174 */ { 0, F_MAP_AA_RANGE_LVALUE-CODE_OFFSET, 0, 0, -1, NULL , -1, -1, false, false, "map_aa_range_lvalue", NULL },
  /* 175 */ { 0, F_MAP_NX_RANGE_LVALUE-CODE_OFFSET, 0, 0, -1, NULL , -1, -1, false, false, "map_nx_range_lvalue", NULL },
  /* 176 */ { 0, F_MAP_RX_RANGE_LVALUE-CODE_OFFSET, 0, 0, -1, NULL , -1, -1, false, false, "map_rx_range_lvalue", NULL },
  /* 177 */ { 0, F_MAP_AX_RANGE_LVALUE-CODE_OFFSET, 0, 0, -1, NULL , -1, -1, false, false, "map_ax_range_lvalue", NULL },
  /* 178 */ { 0, F_MAKE_PROTECTED-CODE_OFFSET, 0, 0, -1, NULL , -1, -1, false, false, "make_protected", NULL },
  /* 179 */ { 0, F_MAKE_RVALUE-CODE_OFFSET, 0, 0, -1, NULL , -1, -1, false, false, "make_rvalue", NULL },
  /* 180 */ { 0, F_PUSH_VIRTUAL_VARIABLE_VLVALUE-CODE_OFFSET, 0, 0, -1, NULL , -1, -1, false, false, "push_virtual_variable_vlvalue", NULL },
  /* 181 */ { 0, F_PUSH_IDENTIFIER_VLVALUE-CODE_OFFSET, 0, 0, -1, NULL , -1, -1, false, false, "push_identifier_vlvalue", NULL },
  /* 182 */ { 0, F_PUSH_IDENTIFIER16_VLVALUE-CODE_OFFSET, 0, 0, -1, NULL , -1, -1, false, false, "push_identifier16_vlvalue", NULL },
  /* 183 */ { 0, F_PUSH_CONTEXT_VLVALUE-CODE_OFFSET, 0, 0, -1, NULL , -1, -1, false, false, "push_context_vlvalue", NULL },
  /* 184 */ { 0, F_PUSH_LOCAL_VARIABLE_VLVALUE-CODE_OFFSET, 0, 0, -1, NULL , -1, -1, false, false, "push_local_variable_vlvalue", NULL },
  /* 185 */ { 0, F_INDEX_VLVALUE-CODE_OFFSET, 0, 0, -1, NULL , -1, -1, false, false, "index_vlvalue", NULL },
  /* 186 */ { 0, F_RINDEX_VLVALUE-CODE_OFFSET, 0, 0, -1, NULL , -1, -1, false, false, "rindex_vlvalue", NULL },
  /* 187 */ { 0, F_AINDEX_VLVALUE-CODE_OFFSET, 0, 0, -1, NULL , -1, -1, false, false, "aindex_vlvalue", NULL },
  /* 188 */ { 0, F_S_INDEX_VLVALUE-CODE_OFFSET, 0, 0, -1, NULL , -1, -1, false, false, "s_index_vlvalue", NULL },
  /* 189 */ { 0, F_SX_INDEX_VLVALUE-CODE_OFFSET, 0, 0, -1, NULL , -1, -1, false, false, "sx_index_vlvalue", NULL },
  /* 190 */ { 0, F_MAP_INDEX_VLVALUE-CODE_OFFSET, 0, 0, -1, NULL , -1, -1, false, false, "map_index_vlvalue", NULL },
  /* 191 */ { 0, F_MAP_RINDEX_VLVALUE-CODE_OFFSET, 0, 0, -1, NULL , -1, -1, false, false, "map_rindex_vlvalue", NULL },
  /* 192 */ { 0, F_MAP_AINDEX_VLVALUE-CODE_OFFSET, 0, 0, -1, NULL , -1, -1, false, false, "map_aindex_vlvalue", NULL },
  /* 193 */ { 0, F_SIMUL_EFUN-CODE_OFFSET, 0, 0, -1, NULL , -1, -1, false, false, "simul_efun", NULL },
  /* 194 */ { 0, F_AGGREGATE-CODE_OFFSET, 0, 0, -1, NULL , -1, -1, false, false, "({", NULL },
  /* 195 */ { 0, F_M_AGGREGATE-CODE_OFFSET, 0, 0, -1, NULL , -1, -1, false, false, "m_aggregate", NULL },
  /* 196 */ { 0, F_M_CAGGREGATE-CODE_OFFSET, 0, 0, -1, NULL , -1, -1, false, false, "([", NULL },
  /* 197 */ { 0, F_S_AGGREGATE-CODE_OFFSET, 0, 0, -1, NULL , -1, -1, false, false, "(<", NULL },
  /* 198 */ { 0, F_S_M_AGGREGATE-CODE_OFFSET, 0, 0, -1, NULL , -1, -1, false, false, "s_m_aggregate", NULL },
  /* 199 */ { 0, F_PREVIOUS_OBJECT0-CODE_OFFSET, 0, 0, -1, NULL , -1, -1, false, false, "previous_object0", NULL },
  /* 200 */ { 0, F_LAMBDA_CCONSTANT-CODE_OFFSET, 0, 0, -1, NULL , -1, -1, false, false, "lambda_cconstant", NULL },
  /* 201 */ { 0, F_LAMBDA_CONSTANT-CODE_OFFSET, 0, 0, -1, NULL , -1, -1, false, false, "lambda_constant", NULL },
  /* 202 */ { 0, F_FOREACH-CODE_OFFSET, 0, 0, -1, NULL , -1, -1, false, false, "foreach", NULL },
  /* 203 */ { 0, F_FOREACH_REF-CODE_OFFSET, 0, 0, -1, NULL , -1, -1, false, false, "foreach_ref", NULL },
  /* 204 */ { 0, F_FOREACH_RANGE-CODE_OFFSET, 0, 0, -1, NULL , -1, -1, false, false, "foreach_range", NULL },
  /* 205 */ { 0, F_FOREACH_NEXT-CODE_OFFSET, 0, 0, -1, NULL , -1, -1, false, false, "foreach_next", NULL },
  /* 206 */ { 0, F_FOREACH_END-CODE_OFFSET, 0, 0, -1, NULL , -1, -1, false, false, "foreach_end", NULL },
  /* 207 */ { 0, F_END_CATCH-CODE_OFFSET, 0, 0, -1, NULL , -1, -1, false, false, "end_catch", NULL },
  /* 208 */ { 0, F_BREAK_CONTINUE-CODE_OFFSET, 0, 0, -1, NULL , -1, -1, false, false, "break_continue", NULL },
  /* 209 */ { 0, F_BREAKN_CONTINUE-CODE_OFFSET, 0, 0, -1, NULL , -1, -1, false, false, "breakn_continue", NULL },
  /* 210 */ { 0, F_JUMP-CODE_OFFSET, 0, 0, -1, NULL , -1, -1, false, false, "jump", NULL },
  /* 211 */ { 0, F_NO_WARN_DEPRECATED-CODE_OFFSET, 0, 0, -1, NULL , -1, -1, false, false, "no_warn_deprecated", NULL },
  /* 212 */ { 0, F_ARRAY_RANGE_CHECK-CODE_OFFSET, 0, 0, -1, NULL , -1, -1, false, false, "array_range_check", NULL },
  /* 213 */ { 0, F_ARRAY0-CODE_OFFSET, 0, 0, -1, NULL , -1, -1, false, false, "array0", NULL },
  /* 214 */ { 0, F_MOVE_VALUE-CODE_OFFSET, 0, 0, -1, NULL , -1, -1, false, false, "move_value", NULL },
  /* 215 */ { 0, F_DUP_N-CODE_OFFSET, 0, 0, -1, NULL , -1, -1, false, false, "dup_n", NULL },
  /* 216 */ { 0, F_POP_N-CODE_OFFSET, 0, 0, -1, NULL , -1, -1, false, false, "pop_n", NULL },
  /* 217 */ { 0, F_PUT_ARRAY_ELEMENT-CODE_OFFSET, 0, 0, -1, NULL , -1, -1, false, false, "put_array_element", NULL },
  /* 218 */ { 0, F_TYPE_CHECK-CODE_OFFSET, 0, 0, -1, NULL , -1, -1, false, false, "type_check", NULL },
  /* 219 */ { 0, F_LAMBDA_TYPE_CHECK-CODE_OFFSET, 0, 0, -1, NULL , -1, -1, false, false, "lambda_type_check", NULL },
  /* 220 */ { 0, F_PUSH_TYPE-CODE_OFFSET, 0, 0, -1, NULL , -1, -1, false, false, "push_type", NULL },
  /* 221 */ { 0, F_CALL_OTHER_CACHED-CODE_OFFSET, 0, 0, -1, NULL , -1, -1, false, false, "call_other_cached", NULL },
  /* 222 */ { 0, F_CALL_STRICT_CACHED-CODE_OFFSET, 0, 0, -1, NULL , -1, -1, false, false, "call_strict_cached", NULL },

  /* --- efuns --- */

  /* 223 */ { 0, F_BYTESP-CODE_OFFSET, 1, 1, 0, &_lpctype_int, 0, 0, false, false, "bytesp", NULL },
  /* 224 */ { 0, F_CLONEP-CODE_OFFSET, 1, 1, F_THIS_OBJECT, &_lpctype_int, 0, 0, false, false, "clonep", NULL },
  /* 225 */ { 0, F_CLOSUREP-CODE_OFFSET, 1, 1, 0, &_lpctype_int, 0, 0, false, false, "closurep", NULL },
  /* 226 */ { 0, F_COROUTINEP-CODE_OFFSET, 1, 1, 0, &_lpctype_int, 0, 0, false, false, "coroutinep", NULL },
  /* 227 */ { 0, F_EXTERN_CALL-CODE_OFFSET, 0, 0, 0, &_lpctype_int, 0, 0, false, false, "extern_call", NULL },
  /* 228 */ { 0, F_FLOATP-CODE_OFFSET, 1, 1, 0, &_lpctype_int, 0, 0, false, false, "floatp", NULL },
  /* 229 */ { 0, F_INTP-CODE_OFFSET, 1, 1, 0, &_lpctype_int, 0, 0, false, false, "intp", NULL },
  /* 230 */ { 0, F_LPCTYPEP-CODE_OFFSET, 1, 1, 0, &_lpctype_int, 0, 0, false, false, "lpctypep", NULL },
  /* 231 */ { 0, F_LWOBJECTP-CODE_OFFSET, 1, 1, 0, &_lpctype_int, 0, 0, false, false, "lwobjectp", NULL },
  /* 232 */ { 0, F_MAPPINGP-CODE_OFFSET, 1, 1, 0, &_lpctype_int, 0, 0, false, false, "mappingp", NULL },
  /* 233 */ { 0, F_MASTER-CODE_OFFSET, 1, 1, F_CONST0, &_lpctype_any_object, 19, 6, false, false, "master", NULL },
  /* 234 */ { 0, F_NEGATE-CODE_OFFSET, 1, 1, 0, &_lpctype_mixed, 7, 3, false, false, "negate", NULL },
  /* 235 */ { 0, F_OBJECTP-CODE_OFFSET, 1, 1, 0, &_lpctype_int, 0, 0, false, false, "objectp", NULL },
  /* 236 */ { 0, F_POINTERP-CODE_OFFSET, 1, 1, 0, &_lpctype_int, 0, 0, false, false, "pointerp", NULL },
  /* 237 */ { 0, F_RAISE_ERROR-CODE_OFFSET, 1, 1, 0, &_lpctype_void, 10, 4, false, false, "raise_error", NULL },
  /* 238 */ { 0, F_REFERENCEP-CODE_OFFSET, 1, 1, 0, &_lpctype_int, 2, 1, false, false, "referencep", NULL },
  /* 239 */ { 0, F_SIZEOF-CODE_OFFSET, 1, 1, 0, &_lpctype_int, 12, 5, false, false, "sizeof", NULL },
  /* 240 */ { 0, F_STRINGP-CODE_OFFSET, 1, 1, 0, &_lpctype_int, 0, 0, false, false, "stringp", NULL },
  /* 241 */ { 0, F_STRUCTP-CODE_OFFSET, 1, 1, 0, &_lpctype_int, 0, 0, false, false, "structp", NULL },
  /* 242 */ { 0, F_SYMBOLP-CODE_OFFSET, 1, 1, 0, &_lpctype_int, 0, 0, false, false, "symbolp", NULL },
  /* 243 */ { 0, F_THIS_COROUTINE-CODE_OFFSET, 0, 0, 0, &_lpctype_coroutine, 0, 0, false, false, "this_coroutine", NULL },
  /* 244 */ { 0, F_THIS_INTERACTIVE-CODE_OFFSET, 0, 0, 0, &_lpctype_any_object, 0, 0, false, false, "this_interactive", NULL },
  /* 245 */ { 0, F_THIS_OBJECT-CODE_OFFSET, 0, 0, 0, &_lpctype_any_object_or_lwobject, 0, 0, false, false, "this_object", NULL },
  /* 246 */ { 0, F_THIS_PLAYER-CODE_OFFSET, 0, 0, 0, &_lpctype_any_object, 0, 0, false, false, "this_player", NULL },
  /* 247 */ { 0, F_THROW-CODE_OFFSET, 1, 1, 0, &_lpctype_void, 0, 0, false, false, "throw", NULL },
  /* 248 */ { 0, F_TYPEOF-CODE_OFFSET, 1, 1, 0, &_lpctype_int, 4, 2, false, false, "typeof", NULL },

  /* --- 0-arg efuns --- */

  /* 249 */ { F_EFUN0, F_CALL_OUT_INFO-EFUN0_OFFSET, 0, 0, 0, &_lpctype_any_array, 0, 0, false, false, "call_out_info", NULL },
  /* 250 */ { F_EFUN0, F_CALLER_STACK_DEPTH-EFUN0_OFFSET, 0, 0, 0, &_lpctype_int, 0, 0, false, false, "caller_stack_depth", NULL },
  /* 251 */ { F_EFUN0, F_COMMAND_STACK-EFUN0_OFFSET, 0, 0, 0, &_lpctype_any_array, 0, 0, false, false, "command_stack", NULL },
  /* 252 */ { F_EFUN0, F_COMMAND_STACK_DEPTH-EFUN0_OFFSET, 0, 0, 0, &_lpctype_int, 0, 0, false, false, "command_stack_depth", NULL },
  /* 253 */ { F_EFUN0, F_GET_EVAL_COST-EFUN0_OFFSET, 0, 0, 0, &_lpctype_int, 0, 0, false, false, "get_eval_cost", NULL },
  /* 254 */ { F_EFUN0, F_HEART_BEAT_INFO-EFUN0_OFFSET, 0, 0, 0, &_lpctype_any_array, 0, 0, false, false, "heart_beat_info", NULL },
  /* 255 */ { F_EFUN0, F_QUERY_COMMAND-EFUN0_OFFSET, 0, 0, 0, &_lpctype_string, 0, 0, false, false, "query_command", NULL },
  /* 256 */ { F_EFUN0, F_REGEXP_PACKAGE-EFUN0_OFFSET, 0, 0, 0, &_lpctype_int, 0, 0, false, false, "regexp_package", NULL },
  /* 257 */ { F_EFUN0, F_RUSAGE-EFUN0_OFFSET, 0, 0, 0, &_lpctype_any_array, 0, 0, false, false, "rusage", NULL },
  /* 258 */ { F_EFUN0, F_TIME-EFUN0_OFFSET, 0, 0, 0, &_lpctype_int, 0, 0, false, false, "time", NULL },
  /* 259 */ { F_EFUN0, F_UNSHADOW-EFUN0_OFFSET, 0, 0, 0, &_lpctype_void, 0, 0, false, true, "unshadow", NULL },
  /* 260 */ { F_EFUN0, F_USERS-EFUN0_OFFSET, 0, 0, 0, &_lpctype_object_array, 0, 0, false, false, "users", NULL },
  /* 261 */ { F_EFUN0, F_UTIME-EFUN0_OFFSET, 0, 0, 0, &_lpctype_int_array, 0, 0, false, false, "utime", NULL },
  /* 262 */ { F_EFUN0, F_WIZLIST_INFO-EFUN0_OFFSET, 0, 0, 0, &_lpctype_any_array, 0, 0, false, false, "wizlist_info", NULL },

  /* --- 1-arg efuns --- */

  /* 263 */ { F_EFUN1, F_ABS-EFUN1_OFFSET, 1, 1, 0, &_lpctype_mixed, 7, 3, false, false, "abs", NULL },
  /* 264 */ { F_EFUN1, F_ACOS-EFUN1_OFFSET, 1, 1, 0, &_lpctype_float, 8, 7, false, false, "acos", NULL },
  /* 265 */ { F_EFUN1, F_ALL_INVENTORY-EFUN1_OFFSET, 1, 1, F_THIS_OBJECT, &_lpctype_object_array, 413, 174, false, false, "all_inventory", NULL },
  /* 266 */ { F_EFUN1, F_ASIN-EFUN1_OFFSET, 1, 1, 0, &_lpctype_float, 8, 7, false, false, "asin", NULL },
  /* 267 */ { F_EFUN1, F_ATAN-EFUN1_OFFSET, 1, 1, 0, &_lpctype_float, 7, 3, false, false, "atan", NULL },
  /* 268 */ { F_EFUN1, F_BLUEPRINT-EFUN1_OFFSET, 1, 1, F_THIS_OBJECT, &_lpctype_any_object, 371, 165, false, false, "blueprint", NULL },
  /* 269 */ { F_EFUN1, F_CALLER_STACK-EFUN1_OFFSET, 1, 1, F_CONST0, &_lpctype_any_object_or_lwobject_array, 19, 6, false, false, "caller_stack", NULL },
  /* 270 */ { F_EFUN1, F_CAPITALIZE-EFUN1_OFFSET, 1, 1, 0, &_lpctype_string, 10, 4, false, false, "capitalize", NULL },
  /* 271 */ { F_EFUN1, F_CEIL-EFUN1_OFFSET, 1, 1, 0, &_lpctype_float, 7, 3, false, false, "ceil", NULL },
  /* 272 */ { F_EFUN1, F_COPY-EFUN1_OFFSET, 1, 1, 0, &_lpctype_mixed, 0, 0, false, false, "copy", NULL },
  /* 273 */ { F_EFUN1, F_COS-EFUN1_OFFSET, 1, 1, 0, &_lpctype_float, 7, 3, false, false, "cos", NULL },
  /* 274 */ { F_EFUN1, F_COUNT_BITS-EFUN1_OFFSET, 1, 1, 0, &_lpctype_int, 10, 4, false, false, "count_bits", NULL },
  /* 275 */ { F_EFUN1, F_CTIME-EFUN1_OFFSET, 1, 1, F_TIME, &_lpctype_string, 97, 35, false, false, "ctime", NULL },
  /* 276 */ { F_EFUN1, F_DEEP_COPY-EFUN1_OFFSET, 1, 1, 0, &_lpctype_mixed, 0, 0, false, false, "deep_copy", NULL },
  /* 277 */ { F_EFUN1, F_DESTRUCT-EFUN1_OFFSET, 1, 1, 0, &_lpctype_void, 413, 171, false, false, "destruct", NULL },
  /* 278 */ { F_EFUN1, F_DRIVER_INFO-EFUN1_OFFSET, 1, 1, 0, &_lpctype_mixed, 19, 6, false, false, "driver_info", NULL },
  /* 279 */ { F_EFUN1, F_EXP-EFUN1_OFFSET, 1, 1, 0, &_lpctype_float, 7, 3, false, false, "exp", NULL },
  /* 280 */ { F_EFUN1, F_FILE_SIZE-EFUN1_OFFSET, 1, 1, 0, &_lpctype_int, 10, 4, false, false, "file_size", NULL },
  /* 281 */ { F_EFUN1, F_FIND_CALL_OUT-EFUN1_OFFSET, 1, 1, 0, &_lpctype_int, 66, 62, false, false, "find_call_out", NULL },
  /* 282 */ { F_EFUN1, F_FIND_OBJECT-EFUN1_OFFSET, 1, 1, 0, &_lpctype_any_object, 10, 4, false, false, "find_object", NULL },
  /* 283 */ { F_EFUN1, F_FIRST_INVENTORY-EFUN1_OFFSET, 1, 1, F_THIS_OBJECT, &_lpctype_any_object, 458, 166, false, false, "first_inventory", NULL },
  /* 284 */ { F_EFUN1, F_FLOOR-EFUN1_OFFSET, 1, 1, 0, &_lpctype_float, 7, 3, false, false, "floor", NULL },
  /* 285 */ { F_EFUN1, F_GET_EXTRA_WIZINFO-EFUN1_OFFSET, 1, 1, 0, &_lpctype_mixed, 107, 40, false, false, "get_extra_wizinfo", NULL },
  /* 286 */ { F_EFUN1, F_GETEUID-EFUN1_OFFSET, 1, 1, F_THIS_OBJECT, &_lpctype_string, 361, 142, false, false, "geteuid", NULL },
  /* 287 */ { F_EFUN1, F_GETUID-EFUN1_OFFSET, 1, 1, F_THIS_OBJECT, &_lpctype_string, 361, 142, false, false, "getuid", NULL },
  /* 288 */ { F_EFUN1, F_GMTIME-EFUN1_OFFSET, 1, 1, F_TIME, &_lpctype_any_array, 97, 35, false, false, "gmtime", NULL },
  /* 289 */ { F_EFUN1, F_INPUT_TO_INFO-EFUN1_OFFSET, 1, 1, 0, &_lpctype_any_array, 413, 174, false, false, "input_to_info", NULL },
  /* 290 */ { F_EFUN1, F_INTERACTIVE-EFUN1_OFFSET, 1, 1, F_THIS_OBJECT, &_lpctype_int, 413, 174, false, false, "interactive", NULL },
  /* 291 */ { F_EFUN1, F_INVERT_BITS-EFUN1_OFFSET, 1, 1, 0, &_lpctype_string, 10, 4, false, false, "invert_bits", NULL },
  /* 292 */ { F_EFUN1, F_LAST_BIT-EFUN1_OFFSET, 1, 1, 0, &_lpctype_int, 10, 4, false, false, "last_bit", NULL },
  /* 293 */ { F_EFUN1, F_LIVING-EFUN1_OFFSET, 1, 1, 0, &_lpctype_int, 413, 171, false, false, "living", NULL },
  /* 294 */ { F_EFUN1, F_LOAD_NAME-EFUN1_OFFSET, 1, 1, F_THIS_OBJECT, &_lpctype_string, 371, 40, false, false, "load_name", NULL },
  /* 295 */ { F_EFUN1, F_LOAD_OBJECT-EFUN1_OFFSET, 1, 1, 0, &_lpctype_any_object, 10, 4, false, false, "load_object", NULL },
  /* 296 */ { F_EFUN1, F_LOCALTIME-EFUN1_OFFSET, 1, 1, F_TIME, &_lpctype_any_array, 97, 35, false, false, "localtime", NULL },
  /* 297 */ { F_EFUN1, F_LOG-EFUN1_OFFSET, 1, 1, 0, &_lpctype_float, 7, 3, false, false, "log", NULL },
  /* 298 */ { F_EFUN1, F_LOWER_CASE-EFUN1_OFFSET, 1, 1, 0, &_lpctype_string, 10, 4, false, false, "lower_case", NULL },
  /* 299 */ { F_EFUN1, F_M_INDICES-EFUN1_OFFSET, 1, 1, 0, &_lpctype_any_array, 273, 108, false, false, "m_indices", NULL },
  /* 300 */ { F_EFUN1, F_MAKE_SHARED_STRING-EFUN1_OFFSET, 1, 1, 0, &_lpctype_string_bytes, 117, 42, false, false, "make_shared_string", "no longer useful" },
  /* 301 */ { F_EFUN1, F_MKDIR-EFUN1_OFFSET, 1, 1, 0, &_lpctype_int, 10, 4, false, false, "mkdir", NULL },
  /* 302 */ { F_EFUN1, F_MKTIME-EFUN1_OFFSET, 1, 1, 0, &_lpctype_int, 77, 39, false, false, "mktime", NULL },
  /* 303 */ { F_EFUN1, F_NEXT_INVENTORY-EFUN1_OFFSET, 1, 1, F_THIS_OBJECT, &_lpctype_any_object, 413, 174, false, false, "next_inventory", NULL },
  /* 304 */ { F_EFUN1, F_NOTIFY_FAIL-EFUN1_OFFSET, 1, 1, 0, &_lpctype_int, 66, 62, false, true, "notify_fail", NULL },
  /* 305 */ { F_EFUN1, F_OBJECT_NAME-EFUN1_OFFSET, 1, 1, F_THIS_OBJECT, &_lpctype_string, 413, 171, false, false, "object_name", NULL },
  /* 306 */ { F_EFUN1, F_OBJECT_TIME-EFUN1_OFFSET, 1, 1, F_THIS_OBJECT, &_lpctype_int, 413, 174, false, false, "object_time", NULL },
  /* 307 */ { F_EFUN1, F_PREVIOUS_OBJECT-EFUN1_OFFSET, 1, 1, 0, &_lpctype_any_object_or_lwobject, 19, 6, false, false, "previous_object", NULL },
  /* 308 */ { F_EFUN1, F_PROCESS_STRING-EFUN1_OFFSET, 1, 1, 0, &_lpctype_string, 10, 4, false, false, "process_string", NULL },
  /* 309 */ { F_EFUN1, F_PROGRAM_NAME-EFUN1_OFFSET, 1, 1, F_THIS_OBJECT, &_lpctype_string, 361, 190, false, false, "program_name", NULL },
  /* 310 */ { F_EFUN1, F_PROGRAM_TIME-EFUN1_OFFSET, 1, 1, F_THIS_OBJECT, &_lpctype_int, 361, 142, false, false, "program_time", NULL },
  /* 311 */ { F_EFUN1, F_QUERY_NOTIFY_FAIL-EFUN1_OFFSET, 1, 1, F_CONST0, &_lpctype_mixed, 19, 6, false, false, "query_notify_fail", NULL },
  /* 312 */ { F_EFUN1, F_QUERY_VERB-EFUN1_OFFSET, 1, 1, F_CONST0, &_lpctype_string, 19, 6, false, false, "query_verb", NULL },
  /* 313 */ { F_EFUN1, F_QUOTE-EFUN1_OFFSET, 1, 1, 0, &_lpctype_mixed, 89, 33, false, false, "quote", NULL },
  /* 314 */ { F_EFUN1, F_RANDOM-EFUN1_OFFSET, 1, 1, 0, &_lpctype_int, 19, 6, false, false, "random", NULL },
  /* 315 */ { F_EFUN1, F_REMOVE_CALL_OUT-EFUN1_OFFSET, 1, 1, 0, &_lpctype_int, 66, 62, false, false, "remove_call_out", NULL },
  /* 316 */ { F_EFUN1, F_REMOVE_INTERACTIVE-EFUN1_OFFSET, 1, 1, 0, &_lpctype_void, 413, 174, false, false, "remove_interactive", NULL },
  /* 317 */ { F_EFUN1, F_RESTORE_OBJECT-EFUN1_OFFSET, 1, 1, 0, &_lpctype_int, 10, 4, false, true, "restore_object", NULL },
  /* 318 */ { F_EFUN1, F_RESTORE_VALUE-EFUN1_OFFSET, 1, 1, 0, &_lpctype_mixed, 10, 4, false, false, "restore_value", NULL },
  /* 319 */ { F_EFUN1, F_REVERSE-EFUN1_OFFSET, 1, 1, 0, &_lpctype_mixed, 27, 10, true, false, "reverse", NULL },
  /* 320 */ { F_EFUN1, F_RM-EFUN1_OFFSET, 1, 1, 0, &_lpctype_int, 10, 4, false, false, "rm", NULL },
  /* 321 */ { F_EFUN1, F_RMDIR-EFUN1_OFFSET, 1, 1, 0, &_lpctype_int, 10, 4, false, false, "rmdir", NULL },
  /* 322 */ { F_EFUN1, F_SET_NEXT_RESET-EFUN1_OFFSET, 1, 1, 0, &_lpctype_int, 19, 6, false, true, "set_next_reset", NULL },
  /* 323 */ { F_EFUN1, F_SET_THIS_OBJECT-EFUN1_OFFSET, 1, 1, 0, &_lpctype_void, 361, 142, false, false, "set_this_object", NULL },
  /* 324 */ { F_EFUN1, F_SET_THIS_PLAYER-EFUN1_OFFSET, 1, 1, 0, &_lpctype_void, 413, 171, false, false, "set_this_player", NULL },
  /* 325 */ { F_EFUN1, F_SGN-EFUN1_OFFSET, 1, 1, 0, &_lpctype_int, 7, 3, false, false, "sgn", NULL },
  /* 326 */ { F_EFUN1, F_SHADOW-EFUN1_OFFSET, 1, 1, 0, &_lpctype_int, 413, 174, false, true, "shadow", NULL },
  /* 327 */ { F_EFUN1, F_SHUTDOWN-EFUN1_OFFSET, 1, 1, F_CONST0, &_lpctype_void, 19, 6, false, false, "shutdown", NULL },
  /* 328 */ { F_EFUN1, F_SIN-EFUN1_OFFSET, 1, 1, 0, &_lpctype_float, 7, 3, false, false, "sin", NULL },
  /* 329 */ { F_EFUN1, F_SQRT-EFUN1_OFFSET, 1, 1, 0, &_lpctype_float, 7, 3, false, false, "sqrt", NULL },
  /* 330 */ { F_EFUN1, F_SYMBOL_VARIABLE-EFUN1_OFFSET, 1, 1, 0, &_lpctype_closure, 375, 147, false, false, "symbol_variable", NULL },
  /* 331 */ { F_EFUN1, F_TAN-EFUN1_OFFSET, 1, 1, 0, &_lpctype_float, 7, 3, false, false, "tan", NULL },
  /* 332 */ { F_EFUN1, F_TEXT_WIDTH-EFUN1_OFFSET, 1, 1, 0, &_lpctype_int, 10, 4, false, false, "text_width", NULL },
  /* 333 */ { F_EFUN1, F_TO_ARRAY-EFUN1_OFFSET, 1, 1, 0, &_lpctype_any_array, 51, 16, false, false, "to_array", NULL },
  /* 334 */ { F_EFUN1, F_TO_FLOAT-EFUN1_OFFSET, 1, 1, 0, &_lpctype_float, 47, 15, false, false, "to_float", NULL },
  /* 335 */ { F_EFUN1, F_TO_INT-EFUN1_OFFSET, 1, 1, 0, &_lpctype_int, 42, 14, false, false, "to_int", NULL },
  /* 336 */ { F_EFUN1, F_TO_LPCTYPE-EFUN1_OFFSET, 1, 1, 0, &_lpctype_lpctype, 10, 4, false, false, "to_lpctype", NULL },
  /* 337 */ { F_EFUN1, F_TO_OBJECT-EFUN1_OFFSET, 1, 1, 0, &_lpctype_any_object, 65, 19, false, false, "to_object", NULL },
  /* 338 */ { F_EFUN1, F_TO_STRING-EFUN1_OFFSET, 1, 1, 0, &_lpctype_string, 0, 0, false, false, "to_string", NULL },
  /* 339 */ { F_EFUN1, F_TRACE-EFUN1_OFFSET, 1, 1, 0, &_lpctype_int, 19, 6, false, false, "trace", NULL },
  /* 340 */ { F_EFUN1, F_TRACEPREFIX-EFUN1_OFFSET, 1, 1, 0, &_lpctype_string, 48, 36, false, false, "traceprefix", NULL },
  /* 341 */ { F_EFUN1, F_TRANSPOSE_ARRAY-EFUN1_OFFSET, 1, 1, 0, &_lpctype_any_array, 36, 39, false, false, "transpose_array", NULL },
  /* 342 */ { F_EFUN1, F_UNMKMAPPING-EFUN1_OFFSET, 1, 1, 0, &_lpctype_any_array, 273, 108, false, false, "unmkmapping", NULL },
  /* 343 */ { F_EFUN1, F_UNQUOTE-EFUN1_OFFSET, 1, 1, 0, &_lpctype_mixed, 94, 34, false, false, "unquote", NULL },
  /* 344 */ { F_EFUN1, F_UPPER_CASE-EFUN1_OFFSET, 1, 1, 0, &_lpctype_string, 10, 4, false, false, "upper_case", NULL },
  /* 345 */ { F_EFUN1, F_WIDTHOF-EFUN1_OFFSET, 1, 1, 0, &_lpctype_int, 273, 135, false, false, "widthof", NULL },
  /* 346 */ { F_EFUN1, F_WRITE-EFUN1_OFFSET, 1, 1, 0, &_lpctype_void, 0, 0, false, false, "write", NULL },

  /* --- 2-arg efuns --- */

  /* 347 */ { F_EFUN2, F_AND_BITS-EFUN2_OFFSET, 2, 2, 0, &_lpctype_string, 79, 57, false, false, "and_bits", NULL },
  /* 348 */ { F_EFUN2, F_ATAN2-EFUN2_OFFSET, 2, 2, 0, &_lpctype_float, 21, 8, false, false, "atan2", NULL },
  /* 349 */ { F_EFUN2, F_ATTACH_ERQ_DEMON-EFUN2_OFFSET, 2, 2, F_CONST0, &_lpctype_int, 506, 206, false, false, "attach_erq_demon", NULL },
  /* 350 */ { F_EFUN2, F_BASEOF-EFUN2_OFFSET, 2, 2, 0, &_lpctype_int, 61, 27, false, false, "baseof", NULL },
  /* 351 */ { F_EFUN2, F_BINARY_MESSAGE-EFUN2_OFFSET, 2, 2, F_CONST0, &_lpctype_int, 494, 201, false, false, "binary_message", NULL },
  /* 352 */ { F_EFUN2, F_CALL_COROUTINE-EFUN2_OFFSET, 2, 2, F_CONST0, &_lpctype_mixed, 355, 139, true, false, "call_coroutine", NULL },
  /* 353 */ { F_EFUN2, F_CHECK_TYPE-EFUN2_OFFSET, 2, 2, 0, &_lpctype_int, 69, 20, false, false, "check_type", NULL },
  /* 354 */ { F_EFUN2, F_CLEAR_BIT-EFUN2_OFFSET, 2, 2, 0, &_lpctype_string, 160, 55, false, false, "clear_bit", NULL },
  /* 355 */ { F_EFUN2, F_CONFIGURE_DRIVER-EFUN2_OFFSET, 2, 2, 0, &_lpctype_void, 389, 152, false, false, "configure_driver", NULL },
  /* 356 */ { F_EFUN2, F_COPY_FILE-EFUN2_OFFSET, 2, 2, 0, &_lpctype_int, 79, 57, false, false, "copy_file", NULL },
  /* 357 */ { F_EFUN2, F_CRYPT-EFUN2_OFFSET, 2, 2, F_CONST0, &_lpctype_string, 117, 42, false, false, "crypt", NULL },
  /* 358 */ { F_EFUN2, F_DEBUG_MESSAGE-EFUN2_OFFSET, 2, 2, F_CONST0, &_lpctype_void, 160, 55, false, false, "debug_message", NULL },
  /* 359 */ { F_EFUN2, F_DUMP_DRIVER_INFO-EFUN2_OFFSET, 2, 2, F_CONST0, &_lpctype_int, 162, 213, false, false, "dump_driver_info", NULL },
  /* 360 */ { F_EFUN2, F_EXEC-EFUN2_OFFSET, 2, 2, 0, &_lpctype_int, 431, 174, false, false, "exec", NULL },
  /* 361 */ { F_EFUN2, F_EXPAND_DEFINE-EFUN2_OFFSET, 2, 2, F_CONST0, &_lpctype_string, 79, 29, false, false, "expand_define", NULL },
  /* 362 */ { F_EFUN2, F_EXPLODE-EFUN2_OFFSET, 2, 2, 0, &_lpctype_string_or_bytes_array, 123, 44, false, false, "explode", NULL },
  /* 363 */ { F_EFUN2, F_FUNCTIONLIST-EFUN2_OFFSET, 2, 2, F_CONST1, &_lpctype_any_array, 435, 176, false, false, "functionlist", NULL },
  /* 364 */ { F_EFUN2, F_GET_DIR-EFUN2_OFFSET, 2, 2, F_CONST1, &_lpctype_any_array, 160, 55, false, false, "get_dir", NULL },
  /* 365 */ { F_EFUN2, F_GET_ERROR_FILE-EFUN2_OFFSET, 2, 2, F_CONST1, &_lpctype_any_array, 160, 55, false, false, "get_error_file", NULL },
  /* 366 */ { F_EFUN2, F_IMPLODE-EFUN2_OFFSET, 2, 2, 0, &_lpctype_string_bytes, 129, 46, false, false, "implode", NULL },
  /* 367 */ { F_EFUN2, F_INTERACTIVE_INFO-EFUN2_OFFSET, 2, 2, 0, &_lpctype_mixed, 421, 171, false, false, "interactive_info", NULL },
  /* 368 */ { F_EFUN2, F_LAMBDA-EFUN2_OFFSET, 2, 2, 0, &_lpctype_closure, 364, 143, false, false, "lambda", NULL },
  /* 369 */ { F_EFUN2, F_LAST_INSTRUCTIONS-EFUN2_OFFSET, 2, 2, F_CONST1, &_lpctype_string_array, 101, 37, false, false, "last_instructions", NULL },
  /* 370 */ { F_EFUN2, F_LWOBJECT_INFO-EFUN2_OFFSET, 2, 2, 0, &_lpctype_mixed, 445, 198, false, false, "lwobject_info", NULL },
  /* 371 */ { F_EFUN2, F_M_ALLOCATE-EFUN2_OFFSET, 2, 2, F_CONST1, &_lpctype_mapping, 101, 37, false, false, "m_allocate", NULL },
  /* 372 */ { F_EFUN2, F_M_DELETE-EFUN2_OFFSET, 2, 2, 0, &_lpctype_mapping, 312, 120, false, false, "m_delete", NULL },
  /* 373 */ { F_EFUN2, F_M_ENTRY-EFUN2_OFFSET, 2, 2, 0, &_lpctype_any_array, 312, 120, false, false, "m_entry", NULL },
  /* 374 */ { F_EFUN2, F_M_REALLOCATE-EFUN2_OFFSET, 2, 2, 0, &_lpctype_mapping, 320, 124, false, false, "m_reallocate", NULL },
  /* 375 */ { F_EFUN2, F_M_VALUES-EFUN2_OFFSET, 2, 2, F_CONST0, &_lpctype_any_array, 320, 124, false, false, "m_values", NULL },
  /* 376 */ { F_EFUN2, F_MATCH_COMMAND-EFUN2_OFFSET, 2, 2, 0, &_lpctype_any_array, 472, 193, false, false, "match_command", NULL },
  /* 377 */ { F_EFUN2, F_MD5_CRYPT-EFUN2_OFFSET, 2, 2, F_CONST0, &_lpctype_string, 117, 42, false, false, "md5_crypt", NULL },
  /* 378 */ { F_EFUN2, F_MOVE_OBJECT-EFUN2_OFFSET, 2, 2, 0, &_lpctype_void, 532, 222, false, false, "move_object", NULL },
  /* 379 */ { F_EFUN2, F_NET_CONNECT-EFUN2_OFFSET, 2, 2, 0, &_lpctype_int, 160, 55, false, true, "net_connect", NULL },
  /* 380 */ { F_EFUN2, F_OBJECT_INFO-EFUN2_OFFSET, 2, 2, 0, &_lpctype_mixed, 421, 171, false, false, "object_info", NULL },
  /* 381 */ { F_EFUN2, F_OR_BITS-EFUN2_OFFSET, 2, 2, 0, &_lpctype_string, 79, 57, false, false, "or_bits", NULL },
  /* 382 */ { F_EFUN2, F_POW-EFUN2_OFFSET, 2, 2, 0, &_lpctype_float, 21, 8, false, false, "pow", NULL },
  /* 383 */ { F_EFUN2, F_QUERY_ACTIONS-EFUN2_OFFSET, 2, 2, F_CONST1, &_lpctype_any_array, 581, 239, false, false, "query_actions", NULL },
  /* 384 */ { F_EFUN2, F_REMOVE_ACTION-EFUN2_OFFSET, 2, 2, F_THIS_PLAYER, &_lpctype_int, 588, 241, false, true, "remove_action", NULL },
  /* 385 */ { F_EFUN2, F_RENAME-EFUN2_OFFSET, 2, 2, 0, &_lpctype_int, 79, 57, false, false, "rename", NULL },
  /* 386 */ { F_EFUN2, F_RENAME_OBJECT-EFUN2_OFFSET, 2, 2, 0, &_lpctype_void, 474, 194, false, false, "rename_object", NULL },
  /* 387 */ { F_EFUN2, F_SET_BIT-EFUN2_OFFSET, 2, 2, 0, &_lpctype_string, 160, 55, false, false, "set_bit", NULL },
  /* 388 */ { F_EFUN2, F_SET_DRIVER_HOOK-EFUN2_OFFSET, 2, 2, 0, &_lpctype_void, 524, 218, false, false, "set_driver_hook", NULL },
  /* 389 */ { F_EFUN2, F_SET_ENVIRONMENT-EFUN2_OFFSET, 2, 2, 0, &_lpctype_void, 431, 228, false, false, "set_environment", NULL },
  /* 390 */ { F_EFUN2, F_SET_EXTRA_WIZINFO-EFUN2_OFFSET, 2, 2, 0, &_lpctype_void, 111, 40, false, false, "set_extra_wizinfo", NULL },
  /* 391 */ { F_EFUN2, F_STRUCT_INFO-EFUN2_OFFSET, 2, 2, 0, &_lpctype_any_array, 17, 25, false, false, "struct_info", NULL },
  /* 392 */ { F_EFUN2, F_SYMBOL_FUNCTION-EFUN2_OFFSET, 2, 2, F_CONST0, &_lpctype_closure, 368, 145, false, false, "symbol_function", NULL },
  /* 393 */ { F_EFUN2, F_TELL_OBJECT-EFUN2_OFFSET, 2, 2, 0, &_lpctype_void, 478, 196, false, false, "tell_object", NULL },
  /* 394 */ { F_EFUN2, F_TEST_BIT-EFUN2_OFFSET, 2, 2, 0, &_lpctype_int, 160, 55, false, false, "test_bit", NULL },
  /* 395 */ { F_EFUN2, F_TRANSFER-EFUN2_OFFSET, 2, 2, 0, &_lpctype_int, 579, 238, false, false, "transfer", "replace by a simul-efun" },
  /* 396 */ { F_EFUN2, F_UNBOUND_LAMBDA-EFUN2_OFFSET, 2, 2, 0, &_lpctype_closure, 364, 143, false, false, "unbound_lambda", NULL },
  /* 397 */ { F_EFUN2, F_VARIABLE_LIST-EFUN2_OFFSET, 2, 2, F_CONST1, &_lpctype_any_array, 435, 176, false, false, "variable_list", NULL },
  /* 398 */ { F_EFUN2, F_XOR_BITS-EFUN2_OFFSET, 2, 2, 0, &_lpctype_string, 79, 57, false, false, "xor_bits", NULL },

  /* --- 3-arg efuns --- */

  /* 399 */ { F_EFUN3, F_CONFIGURE_INTERACTIVE-EFUN3_OFFSET, 3, 3, 0, &_lpctype_void, 425, 171, false, false, "configure_interactive", NULL },
  /* 400 */ { F_EFUN3, F_CONFIGURE_LWOBJECT-EFUN3_OFFSET, 3, 3, 0, &_lpctype_void, 488, 198, false, false, "configure_lwobject", NULL },
  /* 401 */ { F_EFUN3, F_CONFIGURE_OBJECT-EFUN3_OFFSET, 3, 3, 0, &_lpctype_void, 425, 171, false, false, "configure_object", NULL },
  /* 402 */ { F_EFUN3, F_EXECUTE_COMMAND-EFUN3_OFFSET, 3, 3, 0, &_lpctype_int, 575, 236, false, false, "execute_command", NULL },
  /* 403 */ { F_EFUN3, F_HMAC-EFUN3_OFFSET, 3, 3, 0, &_lpctype_string, 149, 51, false, false, "hmac", NULL },
  /* 404 */ { F_EFUN3, F_NEXT_BIT-EFUN3_OFFSET, 3, 3, F_CONST0, &_lpctype_int, 181, 65, false, false, "next_bit", NULL },
  /* 405 */ { F_EFUN3, F_REGEXP-EFUN3_OFFSET, 3, 3, F_CONST0, &_lpctype_string_array, 158, 54, false, false, "regexp", NULL },
  /* 406 */ { F_EFUN3, F_REGEXPLODE-EFUN3_OFFSET, 3, 3, F_CONST0, &_lpctype_string_array, 164, 57, false, false, "regexplode", NULL },
  /* 407 */ { F_EFUN3, F_SEND_ERQ-EFUN3_OFFSET, 3, 3, F_CONST0, &_lpctype_int, 511, 207, false, false, "send_erq", NULL },
  /* 408 */ { F_EFUN3, F_SEND_UDP-EFUN3_OFFSET, 3, 3, 0, &_lpctype_int, 499, 203, false, false, "send_udp", NULL },
  /* 409 */ { F_EFUN3, F_STRRSTR-EFUN3_OFFSET, 3, 3, F_NCONST1, &_lpctype_int, 200, 75, false, false, "strrstr", NULL },
  /* 410 */ { F_EFUN3, F_STRSTR-EFUN3_OFFSET, 3, 3, F_CONST0, &_lpctype_int, 200, 75, false, false, "strstr", NULL },
  /* 411 */ { F_EFUN3, F_WRITE_BYTES-EFUN3_OFFSET, 3, 3, 0, &_lpctype_int, 518, 210, false, false, "write_bytes", NULL },

  /* --- 4-arg efuns --- */

  /* 412 */ { F_EFUN4, F_REGREPLACE-EFUN4_OFFSET, 4, 4, 0, &_lpctype_string, 170, 60, false, false, "regreplace", NULL },

  /* --- vararg efuns --- */

  /* 413 */ { F_EFUNV, F_ADD_ACTION-EFUNV_OFFSET, 3, 2, 0, &_lpctype_void, 568, 233, false, true, "add_action", NULL },
  /* 414 */ { F_EFUNV, F_ALL_ENVIRONMENT-EFUNV_OFFSET, 1, 0, 0, &_lpctype_object_array, 413, 171, false, false, "all_environment", NULL },
  /* 415 */ { F_EFUNV, F_ALLOCATE-EFUNV_OFFSET, 2, 1, 0, &_lpctype_any_array, 234, 90, false, false, "allocate", NULL },
  /* 416 */ { F_EFUNV, F_APPLY-EFUNV_OFFSET, -1, 1, 0, &_lpctype_mixed, 348, 136, true, false, "apply", NULL },
  /* 417 */ { F_EFUNV, F_BIND_LAMBDA-EFUNV_OFFSET, 2, 1, 0, &_lpctype_closure, 359, 141, false, false, "bind_lambda", NULL },
  /* 418 */ { F_EFUNV, F_CALL_DIRECT-EFUNV_OFFSET, -1, 2, 0, &_lpctype_unknown, 399, 161, true, false, "call_direct", NULL },
  /* 419 */ { F_EFUNV, F_CALL_DIRECT_RESOLVED-EFUNV_OFFSET, -1, 3, 0, &_lpctype_int, 397, 156, false, false, "call_direct_resolved", NULL },
  /* 420 */ { F_EFUNV, F_CALL_DIRECT_STRICT-EFUNV_OFFSET, -1, 2, 0, &_lpctype_unknown, 399, 161, true, false, "call_direct_strict", NULL },
  /* 421 */ { F_EFUNV, F_CALL_OTHER-EFUNV_OFFSET, -1, 2, 0, &_lpctype_unknown, 399, 161, true, false, "call_other", NULL },
  /* 422 */ { F_EFUNV, F_CALL_OUT-EFUNV_OFFSET, -1, 2, 0, &_lpctype_void, 386, 151, false, false, "call_out", NULL },
  /* 423 */ { F_EFUNV, F_CALL_RESOLVED-EFUNV_OFFSET, -1, 3, 0, &_lpctype_int, 397, 156, false, false, "call_resolved", NULL },
  /* 424 */ { F_EFUNV, F_CALL_STRICT-EFUNV_OFFSET, -1, 2, 0, &_lpctype_unknown, 399, 161, true, false, "call_strict", NULL },
  /* 425 */ { F_EFUNV, F_CLONE_OBJECT-EFUNV_OFFSET, -1, 1, 0, &_lpctype_any_object, 412, 166, false, false, "clone_object", NULL },
  /* 426 */ { F_EFUNV, F_CLONES-EFUNV_OFFSET, 2, 0, 0, &_lpctype_object_array, 419, 169, false, false, "clones", NULL },
  /* 427 */ { F_EFUNV, F_COMMAND-EFUNV_OFFSET, 2, 1, 0, &_lpctype_int, 472, 193, false, false, "command", NULL },
  /* 428 */ { F_EFUNV, F_COMPILE_STRING-EFUNV_OFFSET, 3, 2, 0, &_lpctype_closure, 379, 148, false, false, "compile_string", NULL },
  /* 429 */ { F_EFUNV, F_COPY_BITS-EFUNV_OFFSET, 5, 2, 0, &_lpctype_string, 224, 85, false, false, "copy_bits", NULL },
  /* 430 */ { F_EFUNV, F_DEEP_INVENTORY-EFUNV_OFFSET, 2, 0, 0, &_lpctype_object_array, 421, 220, false, false, "deep_inventory", NULL },
  /* 431 */ { F_EFUNV, F_ED-EFUNV_OFFSET, 2, 0, 0, &_lpctype_int, 81, 29, false, true, "ed", NULL },
  /* 432 */ { F_EFUNV, F_ENVIRONMENT-EFUNV_OFFSET, 1, 0, 0, &_lpctype_any_object, 458, 166, false, false, "environment", NULL },
  /* 433 */ { F_EFUNV, F_FILTER-EFUNV_OFFSET, -1, 2, 0, &_lpctype_mixed, 266, 104, false, false, "filter", NULL },
  /* 434 */ { F_EFUNV, F_FILTER_INDICES-EFUNV_OFFSET, -1, 2, 0, &_lpctype_mapping, 279, 108, false, false, "filter_indices", NULL },
  /* 435 */ { F_EFUNV, F_FILTER_OBJECTS-EFUNV_OFFSET, -1, 2, 0, &_lpctype_any_array, 239, 92, false, false, "filter_objects", NULL },
  /* 436 */ { F_EFUNV, F_FIND_INPUT_TO-EFUNV_OFFSET, 3, 2, 0, &_lpctype_int, 466, 191, false, false, "find_input_to", NULL },
  /* 437 */ { F_EFUNV, F_FUNCALL-EFUNV_OFFSET, -1, 1, 0, &_lpctype_mixed, 348, 136, true, false, "funcall", NULL },
  /* 438 */ { F_EFUNV, F_FUNCTION_EXISTS-EFUNV_OFFSET, 3, 1, 0, &_lpctype_mixed, 441, 178, false, false, "function_exists", NULL },
  /* 439 */ { F_EFUNV, F_GARBAGE_COLLECTION-EFUNV_OFFSET, 2, 0, 0, &_lpctype_void, 160, 55, false, false, "garbage_collection", NULL },
  /* 440 */ { F_EFUNV, F_GET_TYPE_INFO-EFUNV_OFFSET, 2, 1, 0, &_lpctype_mixed, 85, 31, false, false, "get_type_info", NULL },
  /* 441 */ { F_EFUNV, F_HASH-EFUNV_OFFSET, 3, 2, 0, &_lpctype_string, 141, 49, false, false, "hash", NULL },
  /* 442 */ { F_EFUNV, F_INCLUDE_LIST-EFUNV_OFFSET, 2, 0, 0, &_lpctype_string_array, 444, 181, false, false, "include_list", NULL },
  /* 443 */ { F_EFUNV, F_INHERIT_LIST-EFUNV_OFFSET, 2, 0, 0, &_lpctype_string_array, 444, 181, false, false, "inherit_list", NULL },
  /* 444 */ { F_EFUNV, F_INPUT_TO-EFUNV_OFFSET, -1, 1, 0, &_lpctype_int, 449, 183, false, false, "input_to", NULL },
  /* 445 */ { F_EFUNV, F_LIMITED-EFUNV_OFFSET, -1, 1, 0, &_lpctype_mixed, 251, 215, true, false, "limited", NULL },
  /* 446 */ { F_EFUNV, F_M_ADD-EFUNV_OFFSET, -1, 2, 0, &_lpctype_mapping, 312, 120, false, false, "m_add", NULL },
  /* 447 */ { F_EFUNV, F_M_CONTAINS-EFUNV_OFFSET, -1, 2, 0, &_lpctype_int, 302, 116, false, false, "m_contains", NULL },
  /* 448 */ { F_EFUNV, F_MAP-EFUNV_OFFSET, -1, 2, 0, &_lpctype_mixed, 288, 112, false, false, "map", NULL },
  /* 449 */ { F_EFUNV, F_MAP_INDICES-EFUNV_OFFSET, -1, 2, 0, &_lpctype_mapping, 279, 108, false, false, "map_indices", NULL },
  /* 450 */ { F_EFUNV, F_MAP_OBJECTS-EFUNV_OFFSET, -1, 2, 0, &_lpctype_any_array, 239, 92, false, false, "map_objects", NULL },
  /* 451 */ { F_EFUNV, F_MAX-EFUNV_OFFSET, -1, 1, 0, &_lpctype_mixed, 35, 11, false, false, "max", NULL },
  /* 452 */ { F_EFUNV, F_MD5-EFUNV_OFFSET, 2, 1, 0, &_lpctype_string, 135, 48, false, false, "md5", "obsoleted by hash" },
  /* 453 */ { F_EFUNV, F_MEMBER-EFUNV_OFFSET, 3, 2, 0, &_lpctype_int, 331, 129, false, false, "member", NULL },
  /* 454 */ { F_EFUNV, F_MIN-EFUNV_OFFSET, -1, 1, 0, &_lpctype_mixed, 35, 11, false, false, "min", NULL },
  /* 455 */ { F_EFUNV, F_MKMAPPING-EFUNV_OFFSET, -1, 1, 0, &_lpctype_mapping, 324, 126, false, false, "mkmapping", NULL },
  /* 456 */ { F_EFUNV, F_NEW_LWOBJECT-EFUNV_OFFSET, -1, 1, 0, &_lpctype_any_lwobject, 187, 68, false, false, "new_lwobject", NULL },
  /* 457 */ { F_EFUNV, F_OBJECTS-EFUNV_OFFSET, -1, 0, 0, &_lpctype_object_array, 38, 12, false, false, "objects", NULL },
  /* 458 */ { F_EFUNV, F_PARSE_COMMAND-EFUNV_OFFSET, -1, 3, 0, &_lpctype_int, 593, 243, false, false, "parse_command", NULL },
  /* 459 */ { F_EFUNV, F_PRESENT-EFUNV_OFFSET, 3, 1, 0, &_lpctype_any_object, 538, 223, false, false, "present", NULL },
  /* 460 */ { F_EFUNV, F_PRESENT_CLONE-EFUNV_OFFSET, 3, 1, 0, &_lpctype_any_object, 458, 187, false, false, "present_clone", NULL },
  /* 461 */ { F_EFUNV, F_PRINTF-EFUNV_OFFSET, -1, 1, 0, &_lpctype_void, 187, 68, false, false, "printf", NULL },
  /* 462 */ { F_EFUNV, F_READ_BYTES-EFUNV_OFFSET, 3, 1, 0, &_lpctype_bytes, 181, 65, false, false, "read_bytes", NULL },
  /* 463 */ { F_EFUNV, F_READ_FILE-EFUNV_OFFSET, 4, 1, 0, &_lpctype_string, 181, 65, false, false, "read_file", NULL },
  /* 464 */ { F_EFUNV, F_REGMATCH-EFUNV_OFFSET, 4, 2, 0, &_lpctype_mixed, 179, 64, false, false, "regmatch", NULL },
  /* 465 */ { F_EFUNV, F_REMOVE_INPUT_TO-EFUNV_OFFSET, 3, 1, 0, &_lpctype_int, 466, 191, false, false, "remove_input_to", NULL },
  /* 466 */ { F_EFUNV, F_REPLACE_PROGRAM-EFUNV_OFFSET, 1, 0, 0, &_lpctype_void, 10, 4, false, true, "replace_program", NULL },
  /* 467 */ { F_EFUNV, F_RMEMBER-EFUNV_OFFSET, 3, 2, 0, &_lpctype_int, 340, 132, false, false, "rmember", NULL },
  /* 468 */ { F_EFUNV, F_SAVE_OBJECT-EFUNV_OFFSET, 2, 0, 0, &_lpctype_mixed, 100, 36, false, true, "save_object", NULL },
  /* 469 */ { F_EFUNV, F_SAVE_VALUE-EFUNV_OFFSET, 2, 1, 0, &_lpctype_string, 85, 31, false, false, "save_value", NULL },
  /* 470 */ { F_EFUNV, F_SAY-EFUNV_OFFSET, 2, 1, 0, &_lpctype_void, 546, 226, false, true, "say", NULL },
  /* 471 */ { F_EFUNV, F_SHA1-EFUNV_OFFSET, 2, 1, 0, &_lpctype_string, 135, 48, false, false, "sha1", "obsoleted by hash" },
  /* 472 */ { F_EFUNV, F_SNOOP-EFUNV_OFFSET, 2, 1, 0, &_lpctype_int, 431, 174, false, false, "snoop", NULL },
  /* 473 */ { F_EFUNV, F_SORT_ARRAY-EFUNV_OFFSET, -1, 2, 0, &_lpctype_any_array, 247, 96, false, false, "sort_array", NULL },
  /* 474 */ { F_EFUNV, F_SPRINTF-EFUNV_OFFSET, -1, 1, 0, &_lpctype_string, 187, 68, false, false, "sprintf", NULL },
  /* 475 */ { F_EFUNV, F_SSCANF-EFUNV_OFFSET, -1, 2, 0, &_lpctype_int, 193, 71, false, false, "sscanf", NULL },
  /* 476 */ { F_EFUNV, F_STRFTIME-EFUNV_OFFSET, 3, 0, 0, &_lpctype_string, 100, 36, false, false, "strftime", NULL },
  /* 477 */ { F_EFUNV, F_TELL_ROOM-EFUNV_OFFSET, 3, 2, 0, &_lpctype_void, 556, 230, false, false, "tell_room", NULL },
  /* 478 */ { F_EFUNV, F_TERMINAL_COLOUR-EFUNV_OFFSET, 4, 2, 0, &_lpctype_string, 208, 78, false, false, "terminal_colour", NULL },
  /* 479 */ { F_EFUNV, F_TO_BYTES-EFUNV_OFFSET, 2, 1, 0, &_lpctype_bytes, 75, 23, false, false, "to_bytes", NULL },
  /* 480 */ { F_EFUNV, F_TO_STRUCT-EFUNV_OFFSET, 2, 1, 0, &_lpctype_mixed, 59, 17, false, false, "to_struct", NULL },
  /* 481 */ { F_EFUNV, F_TO_TEXT-EFUNV_OFFSET, 2, 1, 0, &_lpctype_string, 75, 23, false, false, "to_text", NULL },
  /* 482 */ { F_EFUNV, F_TO_TYPE-EFUNV_OFFSET, 3, 2, 0, &_lpctype_mixed, 69, 20, false, false, "to_type", NULL },
  /* 483 */ { F_EFUNV, F_TRIM-EFUNV_OFFSET, 3, 1, 0, &_lpctype_string, 217, 82, false, false, "trim", NULL },
  /* 484 */ { F_EFUNV, F_UNIQUE_ARRAY-EFUNV_OFFSET, -1, 2, 0, &_lpctype_any_object_or_lwobject_array_array, 257, 100, false, false, "unique_array", NULL },
  /* 485 */ { F_EFUNV, F_VARIABLE_EXISTS-EFUNV_OFFSET, 3, 1, 0, &_lpctype_string, 441, 178, false, false, "variable_exists", NULL },
  /* 486 */ { F_EFUNV, F_WALK_MAPPING-EFUNV_OFFSET, -1, 2, 0, &_lpctype_void, 279, 108, false, false, "walk_mapping", NULL },
  /* 487 */ { F_EFUNV, F_WRITE_FILE-EFUNV_OFFSET, 4, 2, 0, &_lpctype_int, 164, 57, false, false, "write_file", NULL },

  /* --- aliased efuns --- */

  /* 488 */ { 0, 0, 1, 1, 0, &_lpctype_string, 361, 142, false, false, "creator", NULL },
};


/* Aliased efuns.
 * Index it with <code>-F_LAST_INSTRUCTION-1 to retrieve
 * the real instruction code.
 */

short efun_aliases[] = {
    F_GETUID,
};


/* Table of function argument signatures (compiler).
 * The internal structure is that of arg_types[] in make_func.
 */

fulltype_t efun_arg_types[] = {
    /*   0 */ { &_lpctype_mixed, 0 }, { NULL, 0 },
    /*   2 */ { &_lpctype_mixed, TYPE_MOD_REFERENCE }, { NULL, 0 },
    /*   4 */ { &_lpctype_mixed, 0 }, { &_lpctype_mixed, TYPE_MOD_REFERENCE }, { NULL, 0 },
    /*   7 */ { &_lpctype_int, 0 }, { &_lpctype_float, 0 }, { NULL, 0 },
    /*  10 */ { &_lpctype_string, 0 }, { NULL, 0 },
    /*  12 */ { &_lpctype_string, 0 }, { &_lpctype_bytes, 0 }, { &_lpctype_mixed, 0 }, { &_lpctype_any_array, 0 }, { &_lpctype_mapping, 0 }, { &_lpctype_any_struct, 0 }, { NULL, 0 },
    /*  19 */ { &_lpctype_int, 0 }, { NULL, 0 },
    /*  21 */ { &_lpctype_int, 0 }, { &_lpctype_float, 0 }, { NULL, 0 },
    /*  24 */ { &_lpctype_int, 0 }, { &_lpctype_float, 0 }, { NULL, 0 },
    /*  27 */ { &_lpctype_int, 0 }, { &_lpctype_string, 0 }, { &_lpctype_bytes, 0 }, { &_lpctype_string, TYPE_MOD_REFERENCE }, { &_lpctype_bytes, TYPE_MOD_REFERENCE }, { &_lpctype_any_array, 0 }, { &_lpctype_any_array, TYPE_MOD_REFERENCE }, { NULL, 0 },
    /*  35 */ { &_lpctype_mixed, 0 }, { &_lpctype_any_array, 0 }, { NULL, 0 },
    /*  38 */ { &_lpctype_mixed, 0 }, { &_lpctype_mixed, TYPE_MOD_REFERENCE }, { NULL, 0 },
    /*  41 */ { NULL, 0 },
    /*  42 */ { &_lpctype_int, 0 }, { &_lpctype_string, 0 }, { &_lpctype_float, 0 }, { &_lpctype_closure, 0 }, { NULL, 0 },
    /*  47 */ { &_lpctype_float, 0 }, { &_lpctype_string, 0 }, { &_lpctype_int, 0 }, { NULL, 0 },
    /*  51 */ { &_lpctype_string, 0 }, { &_lpctype_bytes, 0 }, { &_lpctype_any_array, 0 }, { &_lpctype_symbol, 0 }, { &_lpctype_quoted_array, 0 }, { &_lpctype_any_struct, 0 }, { &_lpctype_lpctype, 0 }, { NULL, 0 },
    /*  59 */ { &_lpctype_mapping, 0 }, { &_lpctype_any_array, 0 }, { &_lpctype_any_struct, 0 }, { NULL, 0 },
    /*  63 */ { &_lpctype_any_struct, 0 }, { NULL, 0 },
    /*  65 */ { &_lpctype_any_object, 0 }, { &_lpctype_string, 0 }, { &_lpctype_closure, 0 }, { NULL, 0 },
    /*  69 */ { &_lpctype_mixed, 0 }, { NULL, 0 },
    /*  71 */ { &_lpctype_lpctype, 0 }, { NULL, 0 },
    /*  73 */ { &_lpctype_struct_to_type_options, 0 }, { NULL, 0 },
    /*  75 */ { &_lpctype_string, 0 }, { &_lpctype_bytes, 0 }, { &_lpctype_int_array, 0 }, { NULL, 0 },
    /*  79 */ { &_lpctype_string, 0 }, { NULL, 0 },
    /*  81 */ { &_lpctype_string, 0 }, { NULL, 0 },
    /*  83 */ { &_lpctype_string, 0 }, { NULL, 0 },
    /*  85 */ { &_lpctype_mixed, 0 }, { NULL, 0 },
    /*  87 */ { &_lpctype_int, 0 }, { NULL, 0 },
    /*  89 */ { &_lpctype_any_array, 0 }, { &_lpctype_quoted_array, 0 }, { &_lpctype_symbol, 0 }, { &_lpctype_string, 0 }, { NULL, 0 },
    /*  94 */ { &_lpctype_quoted_array, 0 }, { &_lpctype_symbol, 0 }, { NULL, 0 },
    /*  97 */ { &_lpctype_int_array, 0 }, { &_lpctype_int, 0 }, { NULL, 0 },
    /* 100 */ { &_lpctype_string, 0 }, { &_lpctype_int, 0 }, { NULL, 0 },
    /* 103 */ { &_lpctype_int, 0 }, { NULL, 0 },
    /* 105 */ { &_lpctype_int, 0 }, { NULL, 0 },
    /* 107 */ { &_lpctype_any_object, 0 }, { &_lpctype_any_lwobject, 0 }, { &_lpctype_string, 0 }, { NULL, 0 },
    /* 111 */ { &_lpctype_any_object, 0 }, { &_lpctype_any_lwobject, 0 }, { &_lpctype_string, 0 }, { NULL, 0 },
    /* 115 */ { &_lpctype_mixed, 0 }, { NULL, 0 },
    /* 117 */ { &_lpctype_string, 0 }, { &_lpctype_bytes, 0 }, { NULL, 0 },
    /* 120 */ { &_lpctype_string, 0 }, { &_lpctype_int, 0 }, { NULL, 0 },
    /* 123 */ { &_lpctype_string, 0 }, { &_lpctype_bytes, 0 }, { NULL, 0 },
    /* 126 */ { &_lpctype_string, 0 }, { &_lpctype_bytes, 0 }, { NULL, 0 },
    /* 129 */ { &_lpctype_string_array, 0 }, { &_lpctype_bytes_array, 0 }, { NULL, 0 },
    /* 132 */ { &_lpctype_string, 0 }, { &_lpctype_bytes, 0 }, { NULL, 0 },
    /* 135 */ { &_lpctype_int_array, 0 }, { &_lpctype_string, 0 }, { &_lpctype_bytes, 0 }, { NULL, 0 },
    /* 139 */ { &_lpctype_int, 0 }, { NULL, 0 },
    /* 141 */ { &_lpctype_int, 0 }, { NULL, 0 },
    /* 143 */ { &_lpctype_string, 0 }, { &_lpctype_bytes, 0 }, { &_lpctype_int_array, 0 }, { NULL, 0 },
    /* 147 */ { &_lpctype_int, 0 }, { NULL, 0 },
    /* 149 */ { &_lpctype_int, 0 }, { NULL, 0 },
    /* 151 */ { &_lpctype_string, 0 }, { &_lpctype_bytes, 0 }, { NULL, 0 },
    /* 154 */ { &_lpctype_string, 0 }, { &_lpctype_bytes, 0 }, { &_lpctype_int_array, 0 }, { NULL, 0 },
    /* 158 */ { &_lpctype_string_array, 0 }, { NULL, 0 },
    /* 160 */ { &_lpctype_string, 0 }, { NULL, 0 },
    /* 162 */ { &_lpctype_int, 0 }, { NULL, 0 },
    /* 164 */ { &_lpctype_string, 0 }, { NULL, 0 },
    /* 166 */ { &_lpctype_string, 0 }, { NULL, 0 },
    /* 168 */ { &_lpctype_int, 0 }, { NULL, 0 },
    /* 170 */ { &_lpctype_string, 0 }, { NULL, 0 },
    /* 172 */ { &_lpctype_string, 0 }, { NULL, 0 },
    /* 174 */ { &_lpctype_closure, 0 }, { &_lpctype_string, 0 }, { NULL, 0 },
    /* 177 */ { &_lpctype_int, 0 }, { NULL, 0 },
    /* 179 */ { &_lpctype_string, 0 }, { NULL, 0 },
    /* 181 */ { &_lpctype_string, 0 }, { NULL, 0 },
    /* 183 */ { &_lpctype_int, 0 }, { NULL, 0 },
    /* 185 */ { &_lpctype_int, 0 }, { NULL, 0 },
    /* 187 */ { &_lpctype_string, 0 }, { NULL, 0 },
    /* 189 */ { &_lpctype_mixed, 0 }, { &_lpctype_mixed, TYPE_MOD_REFERENCE }, { NULL, 0 },
    /* 192 */ { NULL, 0 },
    /* 193 */ { &_lpctype_string, 0 }, { NULL, 0 },
    /* 195 */ { &_lpctype_string, 0 }, { NULL, 0 },
    /* 197 */ { &_lpctype_mixed, TYPE_MOD_LVALUE }, { NULL, 0 },
    /* 199 */ { NULL, 0 },
    /* 200 */ { &_lpctype_string, 0 }, { &_lpctype_bytes, 0 }, { NULL, 0 },
    /* 203 */ { &_lpctype_string, 0 }, { &_lpctype_bytes, 0 }, { NULL, 0 },
    /* 206 */ { &_lpctype_int, 0 }, { NULL, 0 },
    /* 208 */ { &_lpctype_string, 0 }, { NULL, 0 },
    /* 210 */ { &_lpctype_mapping, 0 }, { &_lpctype_closure, 0 }, { NULL, 0 },
    /* 213 */ { &_lpctype_int, 0 }, { NULL, 0 },
    /* 215 */ { &_lpctype_int, 0 }, { NULL, 0 },
    /* 217 */ { &_lpctype_string, 0 }, { NULL, 0 },
    /* 219 */ { &_lpctype_int, 0 }, { NULL, 0 },
    /* 221 */ { &_lpctype_int, 0 }, { &_lpctype_string, 0 }, { NULL, 0 },
    /* 224 */ { &_lpctype_string, 0 }, { NULL, 0 },
    /* 226 */ { &_lpctype_string, 0 }, { NULL, 0 },
    /* 228 */ { &_lpctype_int, 0 }, { NULL, 0 },
    /* 230 */ { &_lpctype_int, 0 }, { NULL, 0 },
    /* 232 */ { &_lpctype_int, 0 }, { NULL, 0 },
    /* 234 */ { &_lpctype_int, 0 }, { &_lpctype_int_array, 0 }, { NULL, 0 },
    /* 237 */ { &_lpctype_mixed, 0 }, { NULL, 0 },
    /* 239 */ { &_lpctype_any_array, 0 }, { NULL, 0 },
    /* 241 */ { &_lpctype_string, 0 }, { NULL, 0 },
    /* 243 */ { &_lpctype_mixed, 0 }, { &_lpctype_mixed, TYPE_MOD_REFERENCE }, { NULL, 0 },
    /* 246 */ { NULL, 0 },
    /* 247 */ { &_lpctype_any_array, 0 }, { &_lpctype_any_array, TYPE_MOD_REFERENCE }, { NULL, 0 },
    /* 250 */ { &_lpctype_string, 0 }, { &_lpctype_closure, 0 }, { NULL, 0 },
    /* 253 */ { &_lpctype_mixed, 0 }, { &_lpctype_mixed, TYPE_MOD_REFERENCE }, { NULL, 0 },
    /* 256 */ { NULL, 0 },
    /* 257 */ { &_lpctype_any_array, 0 }, { NULL, 0 },
    /* 259 */ { &_lpctype_string, 0 }, { &_lpctype_closure, 0 }, { NULL, 0 },
    /* 262 */ { &_lpctype_mixed, 0 }, { &_lpctype_mixed, TYPE_MOD_REFERENCE }, { NULL, 0 },
    /* 265 */ { NULL, 0 },
    /* 266 */ { &_lpctype_mapping, 0 }, { &_lpctype_any_array, 0 }, { &_lpctype_string, 0 }, { &_lpctype_bytes, 0 }, { NULL, 0 },
    /* 271 */ { &_lpctype_string, 0 }, { &_lpctype_closure, 0 }, { &_lpctype_mapping, 0 }, { NULL, 0 },
    /* 275 */ { &_lpctype_mixed, 0 }, { &_lpctype_mixed, TYPE_MOD_REFERENCE }, { NULL, 0 },
    /* 278 */ { NULL, 0 },
    /* 279 */ { &_lpctype_mapping, 0 }, { NULL, 0 },
    /* 281 */ { &_lpctype_string, 0 }, { &_lpctype_closure, 0 }, { NULL, 0 },
    /* 284 */ { &_lpctype_mixed, 0 }, { &_lpctype_mixed, TYPE_MOD_REFERENCE }, { NULL, 0 },
    /* 287 */ { NULL, 0 },
    /* 288 */ { &_lpctype_any_array, 0 }, { &_lpctype_mapping, 0 }, { &_lpctype_any_struct, 0 }, { &_lpctype_string, 0 }, { &_lpctype_bytes, 0 }, { NULL, 0 },
    /* 294 */ { &_lpctype_mapping, 0 }, { &_lpctype_string, 0 }, { &_lpctype_closure, 0 }, { NULL, 0 },
    /* 298 */ { &_lpctype_mixed, 0 }, { &_lpctype_mixed, TYPE_MOD_REFERENCE }, { NULL, 0 },
    /* 301 */ { NULL, 0 },
    /* 302 */ { &_lpctype_mixed, TYPE_MOD_REFERENCE }, { &_lpctype_mapping, 0 }, { NULL, 0 },
    /* 305 */ { &_lpctype_mixed, TYPE_MOD_REFERENCE }, { &_lpctype_mixed, 0 }, { NULL, 0 },
    /* 308 */ { &_lpctype_mixed, 0 }, { &_lpctype_mixed, TYPE_MOD_REFERENCE }, { NULL, 0 },
    /* 311 */ { NULL, 0 },
    /* 312 */ { &_lpctype_mapping, 0 }, { NULL, 0 },
    /* 314 */ { &_lpctype_mixed, 0 }, { NULL, 0 },
    /* 316 */ { &_lpctype_mixed, 0 }, { &_lpctype_mixed, TYPE_MOD_REFERENCE }, { NULL, 0 },
    /* 319 */ { NULL, 0 },
    /* 320 */ { &_lpctype_mapping, 0 }, { NULL, 0 },
    /* 322 */ { &_lpctype_int, 0 }, { NULL, 0 },
    /* 324 */ { &_lpctype_any_array, 0 }, { &_lpctype_any_struct, 0 }, { NULL, 0 },
    /* 327 */ { &_lpctype_mixed, 0 }, { &_lpctype_mixed, TYPE_MOD_REFERENCE }, { NULL, 0 },
    /* 330 */ { NULL, 0 },
    /* 331 */ { &_lpctype_any_array, 0 }, { &_lpctype_string, 0 }, { &_lpctype_bytes, 0 }, { &_lpctype_mapping, 0 }, { NULL, 0 },
    /* 336 */ { &_lpctype_mixed, 0 }, { NULL, 0 },
    /* 338 */ { &_lpctype_int, 0 }, { NULL, 0 },
    /* 340 */ { &_lpctype_any_array, 0 }, { &_lpctype_string, 0 }, { &_lpctype_bytes, 0 }, { NULL, 0 },
    /* 344 */ { &_lpctype_mixed, 0 }, { NULL, 0 },
    /* 346 */ { &_lpctype_int, 0 }, { NULL, 0 },
    /* 348 */ { &_lpctype_mixed, 0 }, { &_lpctype_closure, 0 }, { NULL, 0 },
    /* 351 */ { &_lpctype_mixed, 0 }, { &_lpctype_mixed, TYPE_MOD_REFERENCE }, { NULL, 0 },
    /* 354 */ { NULL, 0 },
    /* 355 */ { &_lpctype_coroutine, 0 }, { NULL, 0 },
    /* 357 */ { &_lpctype_mixed, 0 }, { NULL, 0 },
    /* 359 */ { &_lpctype_closure, 0 }, { NULL, 0 },
    /* 361 */ { &_lpctype_any_object, 0 }, { &_lpctype_any_lwobject, 0 }, { NULL, 0 },
    /* 364 */ { &_lpctype_any_array, 0 }, { NULL, 0 },
    /* 366 */ { &_lpctype_mixed, 0 }, { NULL, 0 },
    /* 368 */ { &_lpctype_symbol, 0 }, { &_lpctype_string, 0 }, { NULL, 0 },
    /* 371 */ { &_lpctype_string, 0 }, { &_lpctype_any_object, 0 }, { &_lpctype_any_lwobject, 0 }, { NULL, 0 },
    /* 375 */ { &_lpctype_symbol, 0 }, { &_lpctype_string, 0 }, { &_lpctype_int, 0 }, { NULL, 0 },
    /* 379 */ { &_lpctype_symbol_array, 0 }, { NULL, 0 },
    /* 381 */ { &_lpctype_string, 0 }, { &_lpctype_string, TYPE_MOD_REFERENCE }, { NULL, 0 },
    /* 384 */ { &_lpctype_struct_compile_string_options, 0 }, { NULL, 0 },
    /* 386 */ { &_lpctype_string, 0 }, { &_lpctype_closure, 0 }, { NULL, 0 },
    /* 389 */ { &_lpctype_int, 0 }, { NULL, 0 },
    /* 391 */ { &_lpctype_mixed, 0 }, { NULL, 0 },
    /* 393 */ { &_lpctype_mixed, 0 }, { &_lpctype_mixed, TYPE_MOD_REFERENCE }, { NULL, 0 },
    /* 396 */ { NULL, 0 },
    /* 397 */ { &_lpctype_mixed, TYPE_MOD_REFERENCE }, { NULL, 0 },
    /* 399 */ { &_lpctype_any_object, 0 }, { &_lpctype_any_lwobject, 0 }, { &_lpctype_string, 0 }, { &_lpctype_object_array, 0 }, { &_lpctype_lwobject_array, 0 }, { &_lpctype_string_array, 0 }, { NULL, 0 },
    /* 406 */ { &_lpctype_string, 0 }, { NULL, 0 },
    /* 408 */ { &_lpctype_mixed, 0 }, { &_lpctype_mixed, TYPE_MOD_REFERENCE }, { NULL, 0 },
    /* 411 */ { NULL, 0 },
    /* 412 */ { &_lpctype_string, 0 }, { &_lpctype_any_object, 0 }, { NULL, 0 },
    /* 415 */ { &_lpctype_mixed, 0 }, { &_lpctype_mixed, TYPE_MOD_REFERENCE }, { NULL, 0 },
    /* 418 */ { NULL, 0 },
    /* 419 */ { &_lpctype_int, 0 }, { &_lpctype_string, 0 }, { &_lpctype_any_object, 0 }, { NULL, 0 },
    /* 423 */ { &_lpctype_int, 0 }, { NULL, 0 },
    /* 425 */ { &_lpctype_any_object, 0 }, { NULL, 0 },
    /* 427 */ { &_lpctype_int, 0 }, { NULL, 0 },
    /* 429 */ { &_lpctype_mixed, 0 }, { NULL, 0 },
    /* 431 */ { &_lpctype_any_object, 0 }, { NULL, 0 },
    /* 433 */ { &_lpctype_any_object, 0 }, { NULL, 0 },
    /* 435 */ { &_lpctype_any_object, 0 }, { &_lpctype_any_lwobject, 0 }, { &_lpctype_string, 0 }, { NULL, 0 },
    /* 439 */ { &_lpctype_int, 0 }, { NULL, 0 },
    /* 441 */ { &_lpctype_string, 0 }, { NULL, 0 },
    /* 443 */ { &_lpctype_int, 0 }, { &_lpctype_any_object, 0 }, { &_lpctype_any_lwobject, 0 }, { NULL, 0 },
    /* 447 */ { &_lpctype_int, 0 }, { NULL, 0 },
    /* 449 */ { &_lpctype_string, 0 }, { &_lpctype_closure, 0 }, { NULL, 0 },
    /* 452 */ { &_lpctype_int, 0 }, { NULL, 0 },
    /* 454 */ { &_lpctype_mixed, 0 }, { &_lpctype_mixed, TYPE_MOD_REFERENCE }, { NULL, 0 },
    /* 457 */ { NULL, 0 },
    /* 458 */ { &_lpctype_any_object, 0 }, { &_lpctype_string, 0 }, { NULL, 0 },
    /* 461 */ { &_lpctype_any_object, 0 }, { &_lpctype_int, 0 }, { NULL, 0 },
    /* 464 */ { &_lpctype_int, 0 }, { NULL, 0 },
    /* 466 */ { &_lpctype_any_object, 0 }, { NULL, 0 },
    /* 468 */ { &_lpctype_any_object, 0 }, { &_lpctype_string, 0 }, { &_lpctype_closure, 0 }, { NULL, 0 },
    /* 472 */ { &_lpctype_string, 0 }, { NULL, 0 },
    /* 474 */ { &_lpctype_any_object, 0 }, { NULL, 0 },
    /* 476 */ { &_lpctype_string, 0 }, { NULL, 0 },
    /* 478 */ { &_lpctype_any_object, 0 }, { &_lpctype_string, 0 }, { NULL, 0 },
    /* 481 */ { &_lpctype_string, 0 }, { &_lpctype_any_array, 0 }, { &_lpctype_mapping, 0 }, { &_lpctype_any_struct, 0 }, { &_lpctype_any_object, 0 }, { &_lpctype_any_lwobject, 0 }, { NULL, 0 },
    /* 488 */ { &_lpctype_any_lwobject, 0 }, { NULL, 0 },
    /* 490 */ { &_lpctype_int, 0 }, { NULL, 0 },
    /* 492 */ { &_lpctype_mixed, 0 }, { NULL, 0 },
    /* 494 */ { &_lpctype_int_array, 0 }, { &_lpctype_bytes, 0 }, { NULL, 0 },
    /* 497 */ { &_lpctype_int, 0 }, { NULL, 0 },
    /* 499 */ { &_lpctype_string, 0 }, { NULL, 0 },
    /* 501 */ { &_lpctype_int, 0 }, { NULL, 0 },
    /* 503 */ { &_lpctype_bytes, 0 }, { &_lpctype_int_array, 0 }, { NULL, 0 },
    /* 506 */ { &_lpctype_any_object, 0 }, { &_lpctype_string, 0 }, { NULL, 0 },
    /* 509 */ { &_lpctype_int, 0 }, { NULL, 0 },
    /* 511 */ { &_lpctype_int, 0 }, { NULL, 0 },
    /* 513 */ { &_lpctype_int_array, 0 }, { &_lpctype_bytes, 0 }, { NULL, 0 },
    /* 516 */ { &_lpctype_closure, 0 }, { NULL, 0 },
    /* 518 */ { &_lpctype_string, 0 }, { NULL, 0 },
    /* 520 */ { &_lpctype_int, 0 }, { NULL, 0 },
    /* 522 */ { &_lpctype_bytes, 0 }, { NULL, 0 },
    /* 524 */ { &_lpctype_int, 0 }, { NULL, 0 },
    /* 526 */ { &_lpctype_closure, 0 }, { &_lpctype_int, 0 }, { &_lpctype_string, 0 }, { &_lpctype_mapping, 0 }, { &_lpctype_string_array, 0 }, { NULL, 0 },
    /* 532 */ { &_lpctype_any_object, 0 }, { &_lpctype_string, 0 }, { NULL, 0 },
    /* 535 */ { &_lpctype_any_object, 0 }, { &_lpctype_string, 0 }, { NULL, 0 },
    /* 538 */ { &_lpctype_any_object, 0 }, { &_lpctype_string, 0 }, { NULL, 0 },
    /* 541 */ { &_lpctype_int, 0 }, { &_lpctype_any_object, 0 }, { NULL, 0 },
    /* 544 */ { &_lpctype_any_object, 0 }, { NULL, 0 },
    /* 546 */ { &_lpctype_string, 0 }, { &_lpctype_any_array, 0 }, { &_lpctype_any_object, 0 }, { &_lpctype_any_lwobject, 0 }, { &_lpctype_mapping, 0 }, { &_lpctype_any_struct, 0 }, { NULL, 0 },
    /* 553 */ { &_lpctype_any_object, 0 }, { &_lpctype_object_array, 0 }, { NULL, 0 },
    /* 556 */ { &_lpctype_any_object, 0 }, { &_lpctype_string, 0 }, { NULL, 0 },
    /* 559 */ { &_lpctype_string, 0 }, { &_lpctype_any_array, 0 }, { &_lpctype_any_object, 0 }, { &_lpctype_any_lwobject, 0 }, { &_lpctype_mapping, 0 }, { &_lpctype_any_struct, 0 }, { NULL, 0 },
    /* 566 */ { &_lpctype_object_array, 0 }, { NULL, 0 },
    /* 568 */ { &_lpctype_string, 0 }, { &_lpctype_closure, 0 }, { NULL, 0 },
    /* 571 */ { &_lpctype_string, 0 }, { NULL, 0 },
    /* 573 */ { &_lpctype_int, 0 }, { NULL, 0 },
    /* 575 */ { &_lpctype_string, 0 }, { NULL, 0 },
    /* 577 */ { &_lpctype_any_object, 0 }, { NULL, 0 },
    /* 579 */ { &_lpctype_any_object, 0 }, { NULL, 0 },
    /* 581 */ { &_lpctype_any_object, 0 }, { &_lpctype_string, 0 }, { NULL, 0 },
    /* 584 */ { &_lpctype_int, 0 }, { &_lpctype_any_object, 0 }, { &_lpctype_string, 0 }, { NULL, 0 },
    /* 588 */ { &_lpctype_int, 0 }, { &_lpctype_string, 0 }, { NULL, 0 },
    /* 591 */ { &_lpctype_any_object, 0 }, { NULL, 0 },
    /* 593 */ { &_lpctype_string, 0 }, { NULL, 0 },
    /* 595 */ { &_lpctype_any_object, 0 }, { &_lpctype_object_array, 0 }, { NULL, 0 },
    /* 598 */ { &_lpctype_string, 0 }, { NULL, 0 },
    /* 600 */ { &_lpctype_mixed, TYPE_MOD_LVALUE }, { NULL, 0 },
    /* 602 */ { NULL, 0 },
};


/* Table of function argument signatures (runtime).
 * The internal structure is that of lpc_types[] in make_func.
 */

long efun_lpc_types[] = {
     /*   0 */ TF_ANYTYPE,
    /*   1 */ TF_LVALUE,
    /*   2 */ TF_ANYTYPE,
    /*   3 */ TF_NUMBER|TF_FLOAT,
    /*   4 */ TF_STRING,
    /*   5 */ TF_ANYTYPE,
    /*   6 */ TF_NUMBER,
    /*   7 */ TF_FLOAT,
    /*   8 */ TF_NUMBER|TF_FLOAT,
    /*   9 */ TF_NUMBER|TF_FLOAT,
    /*  10 */ TF_LVALUE|TF_POINTER|TF_NUMBER|TF_STRING|TF_BYTES,
    /*  11 */ TF_ANYTYPE,
    /*  12 */ TF_ANYTYPE,
    /*  13 */ 0,
    /*  14 */ TF_NUMBER|TF_STRING|TF_FLOAT|TF_CLOSURE,
    /*  15 */ TF_NUMBER|TF_STRING|TF_FLOAT,
    /*  16 */ TF_POINTER|TF_STRING|TF_BYTES|TF_SYMBOL|TF_QUOTED_ARRAY|TF_STRUCT|TF_LPCTYPE,
    /*  17 */ TF_POINTER|TF_MAPPING|TF_STRUCT,
    /*  18 */ TF_STRUCT,
    /*  19 */ TF_STRING|TF_OBJECT|TF_CLOSURE|TF_NULL,
    /*  20 */ TF_ANYTYPE,
    /*  21 */ TF_LPCTYPE,
    /*  22 */ TF_STRUCT,
    /*  23 */ TF_POINTER|TF_STRING|TF_BYTES,
    /*  24 */ TF_STRING,
    /*  25 */ TF_STRUCT,
    /*  26 */ TF_NUMBER,
    /*  27 */ TF_STRUCT,
    /*  28 */ TF_STRUCT,
    /*  29 */ TF_STRING,
    /*  30 */ TF_STRING|TF_NULL,
    /*  31 */ TF_ANYTYPE,
    /*  32 */ TF_NUMBER,
    /*  33 */ TF_POINTER|TF_STRING|TF_SYMBOL|TF_QUOTED_ARRAY,
    /*  34 */ TF_SYMBOL|TF_QUOTED_ARRAY,
    /*  35 */ TF_POINTER|TF_NUMBER,
    /*  36 */ TF_NUMBER|TF_STRING,
    /*  37 */ TF_NUMBER,
    /*  38 */ TF_NUMBER,
    /*  39 */ TF_POINTER,
    /*  40 */ TF_STRING|TF_OBJECT|TF_NULL|TF_LWOBJECT,
    /*  41 */ TF_ANYTYPE,
    /*  42 */ TF_STRING|TF_BYTES,
    /*  43 */ TF_NUMBER|TF_STRING,
    /*  44 */ TF_STRING|TF_BYTES,
    /*  45 */ TF_STRING|TF_BYTES,
    /*  46 */ TF_POINTER,
    /*  47 */ TF_STRING|TF_BYTES,
    /*  48 */ TF_POINTER|TF_STRING|TF_BYTES,
    /*  49 */ TF_NUMBER,
    /*  50 */ TF_POINTER|TF_STRING|TF_BYTES,
    /*  51 */ TF_NUMBER,
    /*  52 */ TF_STRING|TF_BYTES,
    /*  53 */ TF_POINTER|TF_STRING|TF_BYTES,
    /*  54 */ TF_POINTER,
    /*  55 */ TF_STRING,
    /*  56 */ TF_NUMBER,
    /*  57 */ TF_STRING,
    /*  58 */ TF_STRING,
    /*  59 */ TF_NUMBER,
    /*  60 */ TF_STRING,
    /*  61 */ TF_STRING,
    /*  62 */ TF_STRING|TF_CLOSURE,
    /*  63 */ TF_NUMBER,
    /*  64 */ TF_STRING,
    /*  65 */ TF_STRING,
    /*  66 */ TF_NUMBER,
    /*  67 */ TF_NUMBER,
    /*  68 */ TF_STRING,
    /*  69 */ TF_ANYTYPE,
    /*  70 */ 0,
    /*  71 */ TF_STRING,
    /*  72 */ TF_STRING,
    /*  73 */ TF_ANYTYPE,
    /*  74 */ 0,
    /*  75 */ TF_STRING|TF_BYTES,
    /*  76 */ TF_STRING|TF_BYTES,
    /*  77 */ TF_NUMBER,
    /*  78 */ TF_STRING,
    /*  79 */ TF_MAPPING|TF_CLOSURE|TF_NULL,
    /*  80 */ TF_NUMBER,
    /*  81 */ TF_NUMBER,
    /*  82 */ TF_STRING,
    /*  83 */ TF_NUMBER,
    /*  84 */ TF_NUMBER|TF_STRING,
    /*  85 */ TF_STRING,
    /*  86 */ TF_STRING,
    /*  87 */ TF_NUMBER,
    /*  88 */ TF_NUMBER,
    /*  89 */ TF_NUMBER,
    /*  90 */ TF_POINTER|TF_NUMBER,
    /*  91 */ TF_ANYTYPE,
    /*  92 */ TF_POINTER,
    /*  93 */ TF_STRING,
    /*  94 */ TF_ANYTYPE,
    /*  95 */ 0,
    /*  96 */ TF_LVALUE|TF_POINTER,
    /*  97 */ TF_STRING|TF_CLOSURE,
    /*  98 */ TF_ANYTYPE,
    /*  99 */ 0,
    /* 100 */ TF_POINTER,
    /* 101 */ TF_STRING|TF_CLOSURE,
    /* 102 */ TF_ANYTYPE,
    /* 103 */ 0,
    /* 104 */ TF_POINTER|TF_STRING|TF_BYTES|TF_MAPPING,
    /* 105 */ TF_STRING|TF_MAPPING|TF_CLOSURE,
    /* 106 */ TF_ANYTYPE,
    /* 107 */ 0,
    /* 108 */ TF_MAPPING,
    /* 109 */ TF_STRING|TF_CLOSURE,
    /* 110 */ TF_ANYTYPE,
    /* 111 */ 0,
    /* 112 */ TF_POINTER|TF_STRING|TF_BYTES|TF_MAPPING|TF_STRUCT,
    /* 113 */ TF_STRING|TF_MAPPING|TF_CLOSURE,
    /* 114 */ TF_ANYTYPE,
    /* 115 */ 0,
    /* 116 */ TF_LVALUE|TF_MAPPING,
    /* 117 */ TF_ANYTYPE,
    /* 118 */ TF_ANYTYPE,
    /* 119 */ 0,
    /* 120 */ TF_MAPPING,
    /* 121 */ TF_ANYTYPE,
    /* 122 */ TF_ANYTYPE,
    /* 123 */ 0,
    /* 124 */ TF_MAPPING,
    /* 125 */ TF_NUMBER,
    /* 126 */ TF_POINTER|TF_STRUCT,
    /* 127 */ TF_ANYTYPE,
    /* 128 */ 0,
    /* 129 */ TF_POINTER|TF_STRING|TF_BYTES|TF_MAPPING,
    /* 130 */ TF_ANYTYPE,
    /* 131 */ TF_NUMBER,
    /* 132 */ TF_POINTER|TF_STRING|TF_BYTES,
    /* 133 */ TF_ANYTYPE,
    /* 134 */ TF_NUMBER,
    /* 135 */ TF_MAPPING|TF_NULL,
    /* 136 */ TF_ANYTYPE,
    /* 137 */ TF_ANYTYPE,
    /* 138 */ 0,
    /* 139 */ TF_COROUTINE,
    /* 140 */ TF_ANYTYPE,
    /* 141 */ TF_CLOSURE,
    /* 142 */ TF_OBJECT|TF_LWOBJECT,
    /* 143 */ TF_POINTER|TF_NULL,
    /* 144 */ TF_ANYTYPE,
    /* 145 */ TF_STRING|TF_SYMBOL,
    /* 146 */ TF_STRING|TF_OBJECT|TF_NULL|TF_LWOBJECT,
    /* 147 */ TF_NUMBER|TF_STRING|TF_SYMBOL,
    /* 148 */ TF_POINTER|TF_NULL,
    /* 149 */ TF_LVALUE|TF_STRING,
    /* 150 */ TF_STRUCT,
    /* 151 */ TF_STRING|TF_CLOSURE,
    /* 152 */ TF_NUMBER,
    /* 153 */ TF_ANYTYPE,
    /* 154 */ TF_ANYTYPE,
    /* 155 */ 0,
    /* 156 */ TF_LVALUE,
    /* 157 */ TF_POINTER|TF_STRING|TF_OBJECT|TF_NULL|TF_LWOBJECT,
    /* 158 */ TF_STRING,
    /* 159 */ TF_ANYTYPE,
    /* 160 */ 0,
    /* 161 */ TF_POINTER|TF_STRING|TF_OBJECT|TF_LWOBJECT,
    /* 162 */ TF_STRING,
    /* 163 */ TF_ANYTYPE,
    /* 164 */ 0,
    /* 165 */ TF_STRING|TF_OBJECT|TF_LWOBJECT,
    /* 166 */ TF_STRING|TF_OBJECT,
    /* 167 */ TF_ANYTYPE,
    /* 168 */ 0,
    /* 169 */ TF_NUMBER|TF_STRING|TF_OBJECT,
    /* 170 */ TF_NUMBER,
    /* 171 */ TF_OBJECT|TF_NULL,
    /* 172 */ TF_NUMBER,
    /* 173 */ TF_ANYTYPE,
    /* 174 */ TF_OBJECT,
    /* 175 */ TF_OBJECT,
    /* 176 */ TF_STRING|TF_OBJECT|TF_LWOBJECT,
    /* 177 */ TF_NUMBER,
    /* 178 */ TF_STRING,
    /* 179 */ TF_NUMBER|TF_OBJECT|TF_LWOBJECT,
    /* 180 */ TF_NUMBER,
    /* 181 */ TF_OBJECT|TF_LWOBJECT,
    /* 182 */ TF_NUMBER,
    /* 183 */ TF_STRING|TF_CLOSURE,
    /* 184 */ TF_NUMBER,
    /* 185 */ TF_ANYTYPE,
    /* 186 */ 0,
    /* 187 */ TF_STRING|TF_OBJECT,
    /* 188 */ TF_NUMBER|TF_OBJECT,
    /* 189 */ TF_NUMBER,
    /* 190 */ TF_OBJECT|TF_NULL|TF_LWOBJECT,
    /* 191 */ TF_OBJECT,
    /* 192 */ TF_STRING|TF_OBJECT|TF_CLOSURE,
    /* 193 */ TF_STRING,
    /* 194 */ TF_OBJECT,
    /* 195 */ TF_STRING,
    /* 196 */ TF_STRING|TF_OBJECT,
    /* 197 */ TF_POINTER|TF_STRING|TF_OBJECT|TF_MAPPING|TF_STRUCT|TF_LWOBJECT,
    /* 198 */ TF_NULL|TF_LWOBJECT,
    /* 199 */ TF_NUMBER,
    /* 200 */ TF_ANYTYPE,
    /* 201 */ TF_POINTER|TF_BYTES,
    /* 202 */ TF_NUMBER,
    /* 203 */ TF_STRING,
    /* 204 */ TF_NUMBER,
    /* 205 */ TF_POINTER|TF_BYTES,
    /* 206 */ TF_STRING|TF_OBJECT,
    /* 207 */ TF_NUMBER,
    /* 208 */ TF_POINTER|TF_BYTES,
    /* 209 */ TF_CLOSURE|TF_NULL,
    /* 210 */ TF_STRING,
    /* 211 */ TF_NUMBER,
    /* 212 */ TF_BYTES,
    /* 213 */ TF_NUMBER,
    /* 214 */ TF_STRING|TF_NULL,
    /* 215 */ TF_CLOSURE,
    /* 216 */ TF_ANYTYPE,
    /* 217 */ 0,
    /* 218 */ TF_NUMBER,
    /* 219 */ TF_POINTER|TF_NUMBER|TF_STRING|TF_MAPPING|TF_CLOSURE,
    /* 220 */ TF_OBJECT,
    /* 221 */ TF_NUMBER,
    /* 222 */ TF_STRING|TF_OBJECT,
    /* 223 */ TF_STRING|TF_OBJECT,
    /* 224 */ TF_NUMBER|TF_OBJECT,
    /* 225 */ TF_OBJECT,
    /* 226 */ TF_POINTER|TF_STRING|TF_OBJECT|TF_MAPPING|TF_STRUCT|TF_LWOBJECT,
    /* 227 */ TF_POINTER|TF_OBJECT,
    /* 228 */ TF_OBJECT,
    /* 229 */ TF_OBJECT|TF_NULL,
    /* 230 */ TF_STRING|TF_OBJECT,
    /* 231 */ TF_POINTER|TF_STRING|TF_OBJECT|TF_MAPPING|TF_STRUCT|TF_LWOBJECT,
    /* 232 */ TF_POINTER,
    /* 233 */ TF_STRING|TF_CLOSURE,
    /* 234 */ TF_STRING,
    /* 235 */ TF_NUMBER,
    /* 236 */ TF_STRING,
    /* 237 */ TF_OBJECT,
    /* 238 */ TF_OBJECT,
    /* 239 */ TF_STRING|TF_OBJECT,
    /* 240 */ TF_NUMBER|TF_STRING|TF_OBJECT,
    /* 241 */ TF_NUMBER|TF_STRING,
    /* 242 */ TF_OBJECT,
    /* 243 */ TF_STRING,
    /* 244 */ TF_POINTER|TF_OBJECT,
    /* 245 */ TF_STRING,
    /* 246 */ TF_ANYTYPE,
    /* 247 */ 0,
};


/* Prototypes of the tabled efuns
 */

extern svalue_t *f_call_out_info(svalue_t *);
extern svalue_t *f_caller_stack_depth(svalue_t *);
extern svalue_t *f_command_stack(svalue_t *);
extern svalue_t *f_command_stack_depth(svalue_t *);
extern svalue_t *f_get_eval_cost(svalue_t *);
extern svalue_t *f_heart_beat_info(svalue_t *);
extern svalue_t *f_query_command(svalue_t *);
extern svalue_t *f_regexp_package(svalue_t *);
extern svalue_t *f_rusage(svalue_t *);
extern svalue_t *f_time(svalue_t *);
extern svalue_t *f_unshadow(svalue_t *);
extern svalue_t *f_users(svalue_t *);
extern svalue_t *f_utime(svalue_t *);
extern svalue_t *f_wizlist_info(svalue_t *);


extern svalue_t *f_abs(svalue_t *);
extern svalue_t *f_acos(svalue_t *);
extern svalue_t *f_all_inventory(svalue_t *);
extern svalue_t *f_asin(svalue_t *);
extern svalue_t *f_atan(svalue_t *);
extern svalue_t *f_blueprint(svalue_t *);
extern svalue_t *f_caller_stack(svalue_t *);
extern svalue_t *f_capitalize(svalue_t *);
extern svalue_t *f_ceil(svalue_t *);
extern svalue_t *f_copy(svalue_t *);
extern svalue_t *f_cos(svalue_t *);
extern svalue_t *f_count_bits(svalue_t *);
extern svalue_t *f_ctime(svalue_t *);
extern svalue_t *f_deep_copy(svalue_t *);
extern svalue_t *f_destruct(svalue_t *);
extern svalue_t *f_driver_info(svalue_t *);
extern svalue_t *f_exp(svalue_t *);
extern svalue_t *f_file_size(svalue_t *);
extern svalue_t *f_find_call_out(svalue_t *);
extern svalue_t *f_find_object(svalue_t *);
extern svalue_t *f_first_inventory(svalue_t *);
extern svalue_t *f_floor(svalue_t *);
extern svalue_t *f_get_extra_wizinfo(svalue_t *);
extern svalue_t *f_geteuid(svalue_t *);
extern svalue_t *f_getuid(svalue_t *);
extern svalue_t *f_gmtime(svalue_t *);
extern svalue_t *f_input_to_info(svalue_t *);
extern svalue_t *f_interactive(svalue_t *);
extern svalue_t *f_invert_bits(svalue_t *);
extern svalue_t *f_last_bit(svalue_t *);
extern svalue_t *f_living(svalue_t *);
extern svalue_t *f_load_name(svalue_t *);
extern svalue_t *f_load_object(svalue_t *);
extern svalue_t *f_localtime(svalue_t *);
extern svalue_t *f_log(svalue_t *);
extern svalue_t *f_lower_case(svalue_t *);
extern svalue_t *f_m_indices(svalue_t *);
extern svalue_t *f_make_shared_string(svalue_t *);
extern svalue_t *f_mkdir(svalue_t *);
extern svalue_t *f_mktime(svalue_t *);
extern svalue_t *f_next_inventory(svalue_t *);
extern svalue_t *f_notify_fail(svalue_t *);
extern svalue_t *f_object_name(svalue_t *);
extern svalue_t *f_object_time(svalue_t *);
extern svalue_t *f_previous_object(svalue_t *);
extern svalue_t *f_process_string(svalue_t *);
extern svalue_t *f_program_name(svalue_t *);
extern svalue_t *f_program_time(svalue_t *);
extern svalue_t *f_query_notify_fail(svalue_t *);
extern svalue_t *f_query_verb(svalue_t *);
extern svalue_t *f_quote(svalue_t *);
extern svalue_t *f_random(svalue_t *);
extern svalue_t *f_remove_call_out(svalue_t *);
extern svalue_t *f_remove_interactive(svalue_t *);
extern svalue_t *f_restore_object(svalue_t *);
extern svalue_t *f_restore_value(svalue_t *);
extern svalue_t *f_reverse(svalue_t *);
extern svalue_t *f_rm(svalue_t *);
extern svalue_t *f_rmdir(svalue_t *);
extern svalue_t *f_set_next_reset(svalue_t *);
extern svalue_t *f_set_this_object(svalue_t *);
extern svalue_t *f_set_this_player(svalue_t *);
extern svalue_t *f_sgn(svalue_t *);
extern svalue_t *f_shadow(svalue_t *);
extern svalue_t *f_shutdown(svalue_t *);
extern svalue_t *f_sin(svalue_t *);
extern svalue_t *f_sqrt(svalue_t *);
extern svalue_t *f_symbol_variable(svalue_t *);
extern svalue_t *f_tan(svalue_t *);
extern svalue_t *f_text_width(svalue_t *);
extern svalue_t *f_to_array(svalue_t *);
extern svalue_t *f_to_float(svalue_t *);
extern svalue_t *f_to_int(svalue_t *);
extern svalue_t *f_to_lpctype(svalue_t *);
extern svalue_t *f_to_object(svalue_t *);
extern svalue_t *f_to_string(svalue_t *);
extern svalue_t *f_trace(svalue_t *);
extern svalue_t *f_traceprefix(svalue_t *);
extern svalue_t *f_transpose_array(svalue_t *);
extern svalue_t *f_unmkmapping(svalue_t *);
extern svalue_t *f_unquote(svalue_t *);
extern svalue_t *f_upper_case(svalue_t *);
extern svalue_t *f_widthof(svalue_t *);
extern svalue_t *f_write(svalue_t *);


extern svalue_t *f_and_bits(svalue_t *);
extern svalue_t *f_atan2(svalue_t *);
extern svalue_t *f_attach_erq_demon(svalue_t *);
extern svalue_t *f_baseof(svalue_t *);
extern svalue_t *f_binary_message(svalue_t *);
extern svalue_t *f_call_coroutine(svalue_t *);
extern svalue_t *f_check_type(svalue_t *);
extern svalue_t *f_clear_bit(svalue_t *);
extern svalue_t *f_configure_driver(svalue_t *);
extern svalue_t *f_copy_file(svalue_t *);
extern svalue_t *f_crypt(svalue_t *);
extern svalue_t *f_debug_message(svalue_t *);
extern svalue_t *f_dump_driver_info(svalue_t *);
extern svalue_t *f_exec(svalue_t *);
extern svalue_t *f_expand_define(svalue_t *);
extern svalue_t *f_explode(svalue_t *);
extern svalue_t *f_functionlist(svalue_t *);
extern svalue_t *f_get_dir(svalue_t *);
extern svalue_t *f_get_error_file(svalue_t *);
extern svalue_t *f_implode(svalue_t *);
extern svalue_t *f_interactive_info(svalue_t *);
extern svalue_t *f_lambda(svalue_t *);
extern svalue_t *f_last_instructions(svalue_t *);
extern svalue_t *f_lwobject_info(svalue_t *);
extern svalue_t *f_m_allocate(svalue_t *);
extern svalue_t *f_m_delete(svalue_t *);
extern svalue_t *f_m_entry(svalue_t *);
extern svalue_t *f_m_reallocate(svalue_t *);
extern svalue_t *f_m_values(svalue_t *);
extern svalue_t *f_match_command(svalue_t *);
extern svalue_t *f_md5_crypt(svalue_t *);
extern svalue_t *f_move_object(svalue_t *);
extern svalue_t *f_net_connect(svalue_t *);
extern svalue_t *f_object_info(svalue_t *);
extern svalue_t *f_or_bits(svalue_t *);
extern svalue_t *f_pow(svalue_t *);
extern svalue_t *f_query_actions(svalue_t *);
extern svalue_t *f_remove_action(svalue_t *);
extern svalue_t *f_rename(svalue_t *);
extern svalue_t *f_rename_object(svalue_t *);
extern svalue_t *f_set_bit(svalue_t *);
extern svalue_t *f_set_driver_hook(svalue_t *);
extern svalue_t *f_set_environment(svalue_t *);
extern svalue_t *f_set_extra_wizinfo(svalue_t *);
extern svalue_t *f_struct_info(svalue_t *);
extern svalue_t *f_symbol_function(svalue_t *);
extern svalue_t *f_tell_object(svalue_t *);
extern svalue_t *f_test_bit(svalue_t *);
extern svalue_t *f_transfer(svalue_t *);
extern svalue_t *f_unbound_lambda(svalue_t *);
extern svalue_t *f_variable_list(svalue_t *);
extern svalue_t *f_xor_bits(svalue_t *);


extern svalue_t *f_configure_interactive(svalue_t *);
extern svalue_t *f_configure_lwobject(svalue_t *);
extern svalue_t *f_configure_object(svalue_t *);
extern svalue_t *f_execute_command(svalue_t *);
extern svalue_t *f_hmac(svalue_t *);
extern svalue_t *f_next_bit(svalue_t *);
extern svalue_t *f_regexp(svalue_t *);
extern svalue_t *f_regexplode(svalue_t *);
extern svalue_t *f_send_erq(svalue_t *);
extern svalue_t *f_send_udp(svalue_t *);
extern svalue_t *f_strrstr(svalue_t *);
extern svalue_t *f_strstr(svalue_t *);
extern svalue_t *f_write_bytes(svalue_t *);


extern svalue_t *f_regreplace(svalue_t *);


/* Prototypes of the tabled vararg efuns
 */

extern svalue_t *v_add_action(svalue_t *, int);
extern svalue_t *v_all_environment(svalue_t *, int);
extern svalue_t *v_allocate(svalue_t *, int);
extern svalue_t *v_apply(svalue_t *, int);
extern svalue_t *v_bind_lambda(svalue_t *, int);
extern svalue_t *v_call_direct(svalue_t *, int);
extern svalue_t *v_call_direct_resolved(svalue_t *, int);
extern svalue_t *v_call_direct_strict(svalue_t *, int);
extern svalue_t *v_call_other(svalue_t *, int);
extern svalue_t *v_call_out(svalue_t *, int);
extern svalue_t *v_call_resolved(svalue_t *, int);
extern svalue_t *v_call_strict(svalue_t *, int);
extern svalue_t *v_clone_object(svalue_t *, int);
extern svalue_t *v_clones(svalue_t *, int);
extern svalue_t *v_command(svalue_t *, int);
extern svalue_t *v_compile_string(svalue_t *, int);
extern svalue_t *v_copy_bits(svalue_t *, int);
extern svalue_t *v_deep_inventory(svalue_t *, int);
extern svalue_t *v_ed(svalue_t *, int);
extern svalue_t *v_environment(svalue_t *, int);
extern svalue_t *v_filter(svalue_t *, int);
extern svalue_t *v_filter_indices(svalue_t *, int);
extern svalue_t *v_filter_objects(svalue_t *, int);
extern svalue_t *v_find_input_to(svalue_t *, int);
extern svalue_t *v_funcall(svalue_t *, int);
extern svalue_t *v_function_exists(svalue_t *, int);
extern svalue_t *v_garbage_collection(svalue_t *, int);
extern svalue_t *v_get_type_info(svalue_t *, int);
extern svalue_t *v_hash(svalue_t *, int);
extern svalue_t *v_include_list(svalue_t *, int);
extern svalue_t *v_inherit_list(svalue_t *, int);
extern svalue_t *v_input_to(svalue_t *, int);
extern svalue_t *v_limited(svalue_t *, int);
extern svalue_t *v_m_add(svalue_t *, int);
extern svalue_t *v_m_contains(svalue_t *, int);
extern svalue_t *v_map(svalue_t *, int);
extern svalue_t *v_map_indices(svalue_t *, int);
extern svalue_t *v_map_objects(svalue_t *, int);
extern svalue_t *v_max(svalue_t *, int);
extern svalue_t *v_md5(svalue_t *, int);
extern svalue_t *v_member(svalue_t *, int);
extern svalue_t *v_min(svalue_t *, int);
extern svalue_t *v_mkmapping(svalue_t *, int);
extern svalue_t *v_new_lwobject(svalue_t *, int);
extern svalue_t *v_objects(svalue_t *, int);
extern svalue_t *v_parse_command(svalue_t *, int);
extern svalue_t *v_present(svalue_t *, int);
extern svalue_t *v_present_clone(svalue_t *, int);
extern svalue_t *v_printf(svalue_t *, int);
extern svalue_t *v_read_bytes(svalue_t *, int);
extern svalue_t *v_read_file(svalue_t *, int);
extern svalue_t *v_regmatch(svalue_t *, int);
extern svalue_t *v_remove_input_to(svalue_t *, int);
extern svalue_t *v_replace_program(svalue_t *, int);
extern svalue_t *v_rmember(svalue_t *, int);
extern svalue_t *v_save_object(svalue_t *, int);
extern svalue_t *v_save_value(svalue_t *, int);
extern svalue_t *v_say(svalue_t *, int);
extern svalue_t *v_sha1(svalue_t *, int);
extern svalue_t *v_snoop(svalue_t *, int);
extern svalue_t *v_sort_array(svalue_t *, int);
extern svalue_t *v_sprintf(svalue_t *, int);
extern svalue_t *v_sscanf(svalue_t *, int);
extern svalue_t *v_strftime(svalue_t *, int);
extern svalue_t *v_tell_room(svalue_t *, int);
extern svalue_t *v_terminal_colour(svalue_t *, int);
extern svalue_t *v_to_bytes(svalue_t *, int);
extern svalue_t *v_to_struct(svalue_t *, int);
extern svalue_t *v_to_text(svalue_t *, int);
extern svalue_t *v_to_type(svalue_t *, int);
extern svalue_t *v_trim(svalue_t *, int);
extern svalue_t *v_unique_array(svalue_t *, int);
extern svalue_t *v_variable_exists(svalue_t *, int);
extern svalue_t *v_walk_mapping(svalue_t *, int);
extern svalue_t *v_write_file(svalue_t *, int);


/* The table of tabled efuns
 */

svalue_t *(*efun_table[]) (svalue_t *) = {
    /* 249 */ f_call_out_info,
    /* 250 */ f_caller_stack_depth,
    /* 251 */ f_command_stack,
    /* 252 */ f_command_stack_depth,
    /* 253 */ f_get_eval_cost,
    /* 254 */ f_heart_beat_info,
    /* 255 */ f_query_command,
    /* 256 */ f_regexp_package,
    /* 257 */ f_rusage,
    /* 258 */ f_time,
    /* 259 */ f_unshadow,
    /* 260 */ f_users,
    /* 261 */ f_utime,
    /* 262 */ f_wizlist_info,
    /* 263 */ f_abs,
    /* 264 */ f_acos,
    /* 265 */ f_all_inventory,
    /* 266 */ f_asin,
    /* 267 */ f_atan,
    /* 268 */ f_blueprint,
    /* 269 */ f_caller_stack,
    /* 270 */ f_capitalize,
    /* 271 */ f_ceil,
    /* 272 */ f_copy,
    /* 273 */ f_cos,
    /* 274 */ f_count_bits,
    /* 275 */ f_ctime,
    /* 276 */ f_deep_copy,
    /* 277 */ f_destruct,
    /* 278 */ f_driver_info,
    /* 279 */ f_exp,
    /* 280 */ f_file_size,
    /* 281 */ f_find_call_out,
    /* 282 */ f_find_object,
    /* 283 */ f_first_inventory,
    /* 284 */ f_floor,
    /* 285 */ f_get_extra_wizinfo,
    /* 286 */ f_geteuid,
    /* 287 */ f_getuid,
    /* 288 */ f_gmtime,
    /* 289 */ f_input_to_info,
    /* 290 */ f_interactive,
    /* 291 */ f_invert_bits,
    /* 292 */ f_last_bit,
    /* 293 */ f_living,
    /* 294 */ f_load_name,
    /* 295 */ f_load_object,
    /* 296 */ f_localtime,
    /* 297 */ f_log,
    /* 298 */ f_lower_case,
    /* 299 */ f_m_indices,
    /* 300 */ f_make_shared_string,
    /* 301 */ f_mkdir,
    /* 302 */ f_mktime,
    /* 303 */ f_next_inventory,
    /* 304 */ f_notify_fail,
    /* 305 */ f_object_name,
    /* 306 */ f_object_time,
    /* 307 */ f_previous_object,
    /* 308 */ f_process_string,
    /* 309 */ f_program_name,
    /* 310 */ f_program_time,
    /* 311 */ f_query_notify_fail,
    /* 312 */ f_query_verb,
    /* 313 */ f_quote,
    /* 314 */ f_random,
    /* 315 */ f_remove_call_out,
    /* 316 */ f_remove_interactive,
    /* 317 */ f_restore_object,
    /* 318 */ f_restore_value,
    /* 319 */ f_reverse,
    /* 320 */ f_rm,
    /* 321 */ f_rmdir,
    /* 322 */ f_set_next_reset,
    /* 323 */ f_set_this_object,
    /* 324 */ f_set_this_player,
    /* 325 */ f_sgn,
    /* 326 */ f_shadow,
    /* 327 */ f_shutdown,
    /* 328 */ f_sin,
    /* 329 */ f_sqrt,
    /* 330 */ f_symbol_variable,
    /* 331 */ f_tan,
    /* 332 */ f_text_width,
    /* 333 */ f_to_array,
    /* 334 */ f_to_float,
    /* 335 */ f_to_int,
    /* 336 */ f_to_lpctype,
    /* 337 */ f_to_object,
    /* 338 */ f_to_string,
    /* 339 */ f_trace,
    /* 340 */ f_traceprefix,
    /* 341 */ f_transpose_array,
    /* 342 */ f_unmkmapping,
    /* 343 */ f_unquote,
    /* 344 */ f_upper_case,
    /* 345 */ f_widthof,
    /* 346 */ f_write,
    /* 347 */ f_and_bits,
    /* 348 */ f_atan2,
    /* 349 */ f_attach_erq_demon,
    /* 350 */ f_baseof,
    /* 351 */ f_binary_message,
    /* 352 */ f_call_coroutine,
    /* 353 */ f_check_type,
    /* 354 */ f_clear_bit,
    /* 355 */ f_configure_driver,
    /* 356 */ f_copy_file,
    /* 357 */ f_crypt,
    /* 358 */ f_debug_message,
    /* 359 */ f_dump_driver_info,
    /* 360 */ f_exec,
    /* 361 */ f_expand_define,
    /* 362 */ f_explode,
    /* 363 */ f_functionlist,
    /* 364 */ f_get_dir,
    /* 365 */ f_get_error_file,
    /* 366 */ f_implode,
    /* 367 */ f_interactive_info,
    /* 368 */ f_lambda,
    /* 369 */ f_last_instructions,
    /* 370 */ f_lwobject_info,
    /* 371 */ f_m_allocate,
    /* 372 */ f_m_delete,
    /* 373 */ f_m_entry,
    /* 374 */ f_m_reallocate,
    /* 375 */ f_m_values,
    /* 376 */ f_match_command,
    /* 377 */ f_md5_crypt,
    /* 378 */ f_move_object,
    /* 379 */ f_net_connect,
    /* 380 */ f_object_info,
    /* 381 */ f_or_bits,
    /* 382 */ f_pow,
    /* 383 */ f_query_actions,
    /* 384 */ f_remove_action,
    /* 385 */ f_rename,
    /* 386 */ f_rename_object,
    /* 387 */ f_set_bit,
    /* 388 */ f_set_driver_hook,
    /* 389 */ f_set_environment,
    /* 390 */ f_set_extra_wizinfo,
    /* 391 */ f_struct_info,
    /* 392 */ f_symbol_function,
    /* 393 */ f_tell_object,
    /* 394 */ f_test_bit,
    /* 395 */ f_transfer,
    /* 396 */ f_unbound_lambda,
    /* 397 */ f_variable_list,
    /* 398 */ f_xor_bits,
    /* 399 */ f_configure_interactive,
    /* 400 */ f_configure_lwobject,
    /* 401 */ f_configure_object,
    /* 402 */ f_execute_command,
    /* 403 */ f_hmac,
    /* 404 */ f_next_bit,
    /* 405 */ f_regexp,
    /* 406 */ f_regexplode,
    /* 407 */ f_send_erq,
    /* 408 */ f_send_udp,
    /* 409 */ f_strrstr,
    /* 410 */ f_strstr,
    /* 411 */ f_write_bytes,
    /* 412 */ f_regreplace,
};


/* The table of tabled vararg efuns
 */

svalue_t *(*vefun_table[]) (svalue_t *, int) = {
    /* 413 */ v_add_action,
    /* 414 */ v_all_environment,
    /* 415 */ v_allocate,
    /* 416 */ v_apply,
    /* 417 */ v_bind_lambda,
    /* 418 */ v_call_direct,
    /* 419 */ v_call_direct_resolved,
    /* 420 */ v_call_direct_strict,
    /* 421 */ v_call_other,
    /* 422 */ v_call_out,
    /* 423 */ v_call_resolved,
    /* 424 */ v_call_strict,
    /* 425 */ v_clone_object,
    /* 426 */ v_clones,
    /* 427 */ v_command,
    /* 428 */ v_compile_string,
    /* 429 */ v_copy_bits,
    /* 430 */ v_deep_inventory,
    /* 431 */ v_ed,
    /* 432 */ v_environment,
    /* 433 */ v_filter,
    /* 434 */ v_filter_indices,
    /* 435 */ v_filter_objects,
    /* 436 */ v_find_input_to,
    /* 437 */ v_funcall,
    /* 438 */ v_function_exists,
    /* 439 */ v_garbage_collection,
    /* 440 */ v_get_type_info,
    /* 441 */ v_hash,
    /* 442 */ v_include_list,
    /* 443 */ v_inherit_list,
    /* 444 */ v_input_to,
    /* 445 */ v_limited,
    /* 446 */ v_m_add,
    /* 447 */ v_m_contains,
    /* 448 */ v_map,
    /* 449 */ v_map_indices,
    /* 450 */ v_map_objects,
    /* 451 */ v_max,
    /* 452 */ v_md5,
    /* 453 */ v_member,
    /* 454 */ v_min,
    /* 455 */ v_mkmapping,
    /* 456 */ v_new_lwobject,
    /* 457 */ v_objects,
    /* 458 */ v_parse_command,
    /* 459 */ v_present,
    /* 460 */ v_present_clone,
    /* 461 */ v_printf,
    /* 462 */ v_read_bytes,
    /* 463 */ v_read_file,
    /* 464 */ v_regmatch,
    /* 465 */ v_remove_input_to,
    /* 466 */ v_replace_program,
    /* 467 */ v_rmember,
    /* 468 */ v_save_object,
    /* 469 */ v_save_value,
    /* 470 */ v_say,
    /* 471 */ v_sha1,
    /* 472 */ v_snoop,
    /* 473 */ v_sort_array,
    /* 474 */ v_sprintf,
    /* 475 */ v_sscanf,
    /* 476 */ v_strftime,
    /* 477 */ v_tell_room,
    /* 478 */ v_terminal_colour,
    /* 479 */ v_to_bytes,
    /* 480 */ v_to_struct,
    /* 481 */ v_to_text,
    /* 482 */ v_to_type,
    /* 483 */ v_trim,
    /* 484 */ v_unique_array,
    /* 485 */ v_variable_exists,
    /* 486 */ v_walk_mapping,
    /* 487 */ v_write_file,
};


/*----------------------------------------------------------------------*/

/* Our own ctype implementation. This way we can be sure that
 *   (a) we won't choke on non-ASCII characters
 *   (b) we are fast
 *   (c) we get the non-standard classifications we need anyway
 */

#define lexwhite(c) (_my_ctype[(unsigned char)(c)]&16)
#define leXdigit(c) (_my_ctype[(unsigned char)(c)]&64)

unsigned char _my_ctype[] = {
    0,0,0,0,0,0,0,1,1,17,5,17,17,17,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    16,0,1,0,0,0,0,0,0,0,0,0,4,0,0,0,
    194,194,194,194,194,194,194,194,194,194,4,4,0,0,0,0,
    0,192,192,192,192,192,192,128,128,128,128,128,128,128,128,128,
    128,128,128,128,128,128,128,128,128,128,128,0,1,0,0,128,
    0,192,192,192,192,192,192,128,128,128,128,128,128,128,128,128,
    128,128,128,128,128,128,128,128,128,128,128,0,4,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,
    128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,
    128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,
    128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,
};

/************************************************************************/

#endif /* EFUN_DEFS_C__ */
