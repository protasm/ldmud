#ifndef STDSTRUCTS_H__
#define STDSTRUCTS_H__ 1

/* DO NOT EDIT!
 *
 * This file is created automatically by make_func from
 * the specifications in struct_spec.
 */

#include "structs.h"

/* --- Global LPC structs definitions. --- */

enum std_struct_index
{
    STRUCT_IDX_COMPILE_STRING_OPTIONS,
    STRUCT_IDX_TO_TYPE_OPTIONS,

    STD_STRUCT_COUNT,
    STD_STRUCT_OFFSET = USHRT_MAX - STD_STRUCT_COUNT /* Offset in bytecodes. */
};

extern struct_type_t *std_struct[STD_STRUCT_COUNT];

#define STRUCT_COMPILE_STRING_OPTIONS   std_struct[STRUCT_IDX_COMPILE_STRING_OPTIONS]
#define STRUCT_TO_TYPE_OPTIONS          std_struct[STRUCT_IDX_TO_TYPE_OPTIONS]

/* --- Member indices --- */

enum struct_compile_string_options_enum
{
    STRUCT_COMPILE_STRING_OPTIONS_FUNCTIONS,
    STRUCT_COMPILE_STRING_OPTIONS_VARIABLES,
    STRUCT_COMPILE_STRING_OPTIONS_STRUCTS,
    STRUCT_COMPILE_STRING_OPTIONS_USE_OBJECT_FUNCTIONS,
    STRUCT_COMPILE_STRING_OPTIONS_USE_OBJECT_VARIABLES,
    STRUCT_COMPILE_STRING_OPTIONS_USE_OBJECT_STRUCTS,
    STRUCT_COMPILE_STRING_OPTIONS_COMPILE_EXPRESSION,
    STRUCT_COMPILE_STRING_OPTIONS_COMPILE_BLOCK,
    STRUCT_COMPILE_STRING_OPTIONS_AS_ASYNC,
    STRUCT_COMPILE_STRING_OPTIONS_DETECT_END,
};

enum struct_to_type_options_enum
{
    STRUCT_TO_TYPE_OPTIONS_SOURCE_ENCODING,
    STRUCT_TO_TYPE_OPTIONS_TARGET_ENCODING,
    STRUCT_TO_TYPE_OPTIONS_KEEP_ZERO,
};

/* --- Corresponding LPC types. --- */

extern lpctype_t _lpctype_struct_compile_string_options;
extern lpctype_t _lpctype_struct_to_type_options;

extern lpctype_t *lpctype_struct_compile_string_options;
extern lpctype_t *lpctype_struct_to_type_options;

/* --- Prototypes. --- */

extern void init_std_structs();

#endif /* STDSTRUCTS_H__ */
