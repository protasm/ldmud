/* DO NOT EDIT!
 *
 * This file is created automatically by make_func from
 * the specifications in struct_spec.
 *
 * It's purpose is to define global struct definitions.
 */

#include "driver.h"
#include "prolang.h"
#include "stdstructs.h"

/*-------------------------------------------------------------------------*/

struct_type_t *std_struct[STD_STRUCT_COUNT];
  /* All global struct definitions.
   */

lpctype_t _lpctype_struct_compile_string_options;
lpctype_t _lpctype_struct_to_type_options;
  /* Static type definitions of global structs.
   */

lpctype_t *lpctype_struct_compile_string_options  = &_lpctype_struct_compile_string_options;
lpctype_t *lpctype_struct_to_type_options         = &_lpctype_struct_to_type_options;
  /* Pointer to type definitions of global structs.
   */

/*-------------------------------------------------------------------------*/
void
init_std_structs ()

/* Create global struct definitions.
 */

{
    STRUCT_COMPILE_STRING_OPTIONS = create_std_struct_type(STRUCT_IDX_COMPILE_STRING_OPTIONS,
        &_lpctype_struct_compile_string_options, "compile_string_options",
        (lpctype_t*[]){ &_lpctype_mapping_or_closure, &_lpctype_mapping_or_closure, &_lpctype_mapping_or_closure, &_lpctype_int, &_lpctype_int, &_lpctype_int, &_lpctype_int, &_lpctype_int, &_lpctype_int, &_lpctype_int, NULL },
        (const char*[]){ "functions", "variables", "structs", "use_object_functions", "use_object_variables", "use_object_structs", "compile_expression", "compile_block", "as_async", "detect_end", NULL });

    STRUCT_TO_TYPE_OPTIONS = create_std_struct_type(STRUCT_IDX_TO_TYPE_OPTIONS,
        &_lpctype_struct_to_type_options, "to_type_options",
        (lpctype_t*[]){ &_lpctype_string, &_lpctype_string, &_lpctype_int, NULL },
        (const char*[]){ "source_encoding", "target_encoding", "keep_zero", NULL });

} /* init_std_structs() */

/*-------------------------------------------------------------------------*/
