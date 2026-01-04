/* DO NOT EDIT!
 *
 * This file is created automatically by make_func from the specification
 * in applied_spec.
 */

#include "applied_decl.h"
#include "prolang.h"
#include "types.h"
#include "../mudlib/sys/driver_hook.h"

/*----------------------------------------------------------------------*/

/* The applied lfuns for the master object.
 */

applied_decl_t applied_decl_master[] = {
    { &_lpctype_any_object, { .cname = "compile_object" }, "protected", TYPE_MOD_PRIVATE, 1, 0, false, false, false, NULL, NULL },
    { &_lpctype_any_object, { .cname = "connect" }, "protected", TYPE_MOD_PRIVATE, 0, 0, false, false, false, NULL, NULL },
    { &_lpctype_void, { .cname = "dangling_lfun_closure" }, "protected", TYPE_MOD_PRIVATE, 0, 0, false, false, false, NULL, NULL },
    { &_lpctype_void, { .cname = "disconnect" }, "protected", TYPE_MOD_PRIVATE, 2, 1, false, false, false, NULL, NULL },
    { &_lpctype_string_array, { .cname = "epilog" }, "protected", TYPE_MOD_PRIVATE, 1, 3, false, false, false, NULL, NULL },
    { &_lpctype_void, { .cname = "external_master_reload" }, "protected", TYPE_MOD_PRIVATE, 0, 0, false, false, false, NULL, NULL },
    { &_lpctype_void, { .cname = "flag" }, "protected", TYPE_MOD_PRIVATE, 1, 0, false, false, false, NULL, NULL },
    { &_lpctype_string, { .cname = "get_bb_uid" }, "protected", TYPE_MOD_PRIVATE, 0, 0, false, false, false, NULL, NULL },
    { &_lpctype_string, { .cname = "get_ed_buffer_save_file_name" }, "protected", TYPE_MOD_PRIVATE, 1, 0, false, false, false, NULL, NULL },
    { &_lpctype_string, { .cname = "get_master_uid" }, "protected", TYPE_MOD_PRIVATE, 0, 0, false, false, false, NULL, NULL },
    { &_lpctype_string_or_string_array, { .cname = "get_simul_efun" }, "protected", TYPE_MOD_PRIVATE, 0, 0, false, false, false, NULL, NULL },
    { &_lpctype_string, { .cname = "get_wiz_name" }, "protected", TYPE_MOD_PRIVATE, 1, 0, false, false, false, NULL, NULL },
    { &_lpctype_int, { .cname = "handle_external_signal" }, "protected", TYPE_MOD_PRIVATE, 1, 3, false, false, false, NULL, NULL },
    { &_lpctype_mixed, { .cname = "heart_beat_error" }, "protected", TYPE_MOD_PRIVATE, 6, 4, false, false, false, NULL, NULL },
    { &_lpctype_void, { .cname = "inaugurate_master" }, "protected", TYPE_MOD_PRIVATE, 1, 3, false, false, false, NULL, NULL },
    { &_lpctype_mixed, { .cname = "include_file" }, "protected", TYPE_MOD_PRIVATE, 3, 6, false, false, false, NULL, NULL },
    { &_lpctype_mixed, { .cname = "inherit_file" }, "protected", TYPE_MOD_PRIVATE, 2, 5, false, false, false, NULL, NULL },
    { &_lpctype_void, { .cname = "log_error" }, "protected", TYPE_MOD_PRIVATE, 4, 6, false, false, false, NULL, NULL },
    { &_lpctype_void, { .cname = "low_memory" }, "protected", TYPE_MOD_PRIVATE, 4, 10, false, false, false, NULL, NULL },
    { &_lpctype_string, { .cname = "make_path_absolute" }, "protected", TYPE_MOD_PRIVATE, 1, 0, false, false, false, NULL, NULL },
    { &_lpctype_void, { .cname = "notify_shutdown" }, "protected", TYPE_MOD_PRIVATE, 1, 0, true, false, false, NULL, NULL },
    { &_lpctype_string_array, { .cname = "parse_command_adjectiv_id_list" }, "protected", TYPE_MOD_PRIVATE, 0, 0, false, false, false, NULL, NULL },
    { &_lpctype_string, { .cname = "parse_command_all_word" }, "protected", TYPE_MOD_PRIVATE, 0, 0, false, false, false, NULL, NULL },
    { &_lpctype_string_array, { .cname = "parse_command_id_list" }, "protected", TYPE_MOD_PRIVATE, 0, 0, false, false, false, NULL, NULL },
    { &_lpctype_string_array, { .cname = "parse_command_plural_id_list" }, "protected", TYPE_MOD_PRIVATE, 0, 0, false, false, false, NULL, NULL },
    { &_lpctype_string_array, { .cname = "parse_command_prepos_list" }, "protected", TYPE_MOD_PRIVATE, 0, 0, false, false, false, NULL, NULL },
    { &_lpctype_void, { .cname = "preload" }, "protected", TYPE_MOD_PRIVATE, 1, 0, false, false, false, NULL, NULL },
    { &_lpctype_mixed, { .cname = "prepare_destruct" }, "protected", TYPE_MOD_PRIVATE, 1, 1, false, false, false, NULL, NULL },
    { &_lpctype_string, { .cname = "printf_obj_name" }, "protected", TYPE_MOD_PRIVATE, 1, 1, false, false, false, NULL, NULL },
    { &_lpctype_int, { .cname = "privilege_violation" }, "protected", TYPE_MOD_PRIVATE, 5, 14, false, false, false, NULL, NULL },
    { &_lpctype_int, { .cname = "query_allow_shadow" }, "protected", TYPE_MOD_PRIVATE, 1, 1, false, false, false, NULL, NULL },
    { &_lpctype_void, { .cname = "quota_demon" }, "protected", TYPE_MOD_PRIVATE, 0, 0, false, false, false, NULL, NULL },
    { &_lpctype_void, { .cname = "reactivate_destructed_master" }, "protected", TYPE_MOD_PRIVATE, 1, 3, false, false, false, NULL, NULL },
    { &_lpctype_void, { .cname = "receive_udp" }, "protected", TYPE_MOD_PRIVATE, 3, 19, false, false, false, NULL, NULL },
    { &_lpctype_void, { .cname = "remove_player" }, "protected", TYPE_MOD_PRIVATE, 1, 1, false, false, false, NULL, NULL },
    { &_lpctype_int, { .cname = "retrieve_ed_setup" }, "protected", TYPE_MOD_PRIVATE, 1, 1, false, false, false, NULL, NULL },
    { &_lpctype_void, { .cname = "runtime_error" }, "protected", TYPE_MOD_PRIVATE, 6, 22, false, false, false, NULL, NULL },
    { &_lpctype_void, { .cname = "runtime_warning" }, "protected", TYPE_MOD_PRIVATE, 5, 5, false, false, false, NULL, NULL },
    { &_lpctype_int, { .cname = "save_ed_setup" }, "protected", TYPE_MOD_PRIVATE, 2, 28, false, false, false, NULL, NULL },
    { &_lpctype_void, { .cname = "slow_shut_down" }, "protected", TYPE_MOD_PRIVATE, 1, 3, false, false, false, NULL, NULL },
    { &_lpctype_void, { .cname = "stale_erq" }, "protected", TYPE_MOD_PRIVATE, 1, 30, false, false, false, NULL, NULL },
    { &_lpctype_int, { .cname = "valid_exec" }, "protected", TYPE_MOD_PRIVATE, 3, 31, false, false, false, NULL, NULL },
    { &_lpctype_int, { .cname = "valid_query_snoop" }, "protected", TYPE_MOD_PRIVATE, 1, 1, false, false, false, NULL, NULL },
    { &_lpctype_string, { .cname = "valid_read" }, "protected", TYPE_MOD_PRIVATE, 4, 34, false, false, false, NULL, NULL },
    { &_lpctype_int, { .cname = "valid_snoop" }, "protected", TYPE_MOD_PRIVATE, 2, 32, false, false, false, NULL, NULL },
    { &_lpctype_int, { .cname = "valid_trace" }, "protected", TYPE_MOD_PRIVATE, 2, 38, false, false, false, NULL, NULL },
    { &_lpctype_string, { .cname = "valid_write" }, "protected", TYPE_MOD_PRIVATE, 4, 34, false, false, false, NULL, NULL },
    { NULL }
};

/*----------------------------------------------------------------------*/

/* The applied lfuns for regular objects.
 */

applied_decl_t applied_decl_regular[] = {
    { &_lpctype_void, { .cname = "catch_msg" }, "visible", TYPE_MOD_PRIVATE | TYPE_MOD_PROTECTED | TYPE_MOD_STATIC, 2, 40, false, false, false, NULL, NULL },
    { &_lpctype_void, { .cname = "catch_tell" }, "visible", TYPE_MOD_PRIVATE | TYPE_MOD_PROTECTED | TYPE_MOD_STATIC, 1, 0, false, false, false, NULL, NULL },
    { &_lpctype_void, { .cname = "heart_beat" }, "private", 0, 0, 0, false, false, false, NULL, NULL },
    { &_lpctype_int, { .cname = "id" }, "visible", TYPE_MOD_PRIVATE | TYPE_MOD_PROTECTED | TYPE_MOD_STATIC, 1, 0, false, false, false, NULL, NULL },
    { &_lpctype_int, { .cname = "logon" }, "static", TYPE_MOD_PRIVATE | TYPE_MOD_PROTECTED, 1, 3, true, false, false, NULL, NULL },
    { &_lpctype_string_array, { .cname = "parse_command_adjectiv_id_list" }, "visible", TYPE_MOD_PRIVATE | TYPE_MOD_PROTECTED | TYPE_MOD_STATIC, 0, 0, false, false, false, NULL, NULL },
    { &_lpctype_string_array, { .cname = "parse_command_id_list" }, "visible", TYPE_MOD_PRIVATE | TYPE_MOD_PROTECTED | TYPE_MOD_STATIC, 0, 0, false, false, false, NULL, NULL },
    { &_lpctype_string_array, { .cname = "parse_command_plural_id_list" }, "visible", TYPE_MOD_PRIVATE | TYPE_MOD_PROTECTED | TYPE_MOD_STATIC, 0, 0, false, false, false, NULL, NULL },
    { &_lpctype_int, { .cname = "add_weight" }, "visible", TYPE_MOD_PRIVATE | TYPE_MOD_PROTECTED | TYPE_MOD_STATIC, 1, 3, false, false, false, NULL, NULL },
    { &_lpctype_int, { .cname = "can_put_and_get" }, "visible", TYPE_MOD_PRIVATE | TYPE_MOD_PROTECTED | TYPE_MOD_STATIC, 0, 0, false, false, false, NULL, NULL },
    { &_lpctype_int, { .cname = "drop" }, "visible", TYPE_MOD_PRIVATE | TYPE_MOD_PROTECTED | TYPE_MOD_STATIC, 1, 3, true, false, false, NULL, NULL },
    { &_lpctype_int, { .cname = "get" }, "visible", TYPE_MOD_PRIVATE | TYPE_MOD_PROTECTED | TYPE_MOD_STATIC, 0, 0, false, false, false, NULL, NULL },
    { &_lpctype_int, { .cname = "prevent_insert" }, "visible", TYPE_MOD_PRIVATE | TYPE_MOD_PROTECTED | TYPE_MOD_STATIC, 0, 0, false, false, false, NULL, NULL },
    { &_lpctype_int, { .cname = "query_weight" }, "visible", TYPE_MOD_PRIVATE | TYPE_MOD_PROTECTED | TYPE_MOD_STATIC, 0, 0, false, false, false, NULL, NULL },
    { NULL }
};

/*----------------------------------------------------------------------*/

/* The applied lfuns for driver hooks.
 */

applied_decl_t applied_decl_hook[] = {
    { &_lpctype_int, { .hook = H_CLEAN_UP }, "static", TYPE_MOD_PRIVATE | TYPE_MOD_PROTECTED, 1, 3, false, false, true, NULL, NULL },
    { &_lpctype_int, { .hook = H_COMMAND }, "protected", TYPE_MOD_PRIVATE, 2, 0, false, false, false, NULL, NULL },
    { &_lpctype_void, { .hook = H_CREATE_CLONE }, "protected", TYPE_MOD_PRIVATE, 0, 0, false, true, false, NULL, NULL },
    { &_lpctype_void, { .hook = H_CREATE_LWOBJECT }, "protected", TYPE_MOD_PRIVATE, 0, 0, false, true, false, NULL, NULL },
    { &_lpctype_void, { .hook = H_CREATE_LWOBJECT_COPY }, "protected", TYPE_MOD_PRIVATE, 0, 0, true, false, false, NULL, NULL },
    { &_lpctype_void, { .hook = H_CREATE_LWOBJECT_RESTORE }, "protected", TYPE_MOD_PRIVATE, 0, 0, true, false, false, NULL, NULL },
    { &_lpctype_void, { .hook = H_CREATE_OB }, "protected", TYPE_MOD_PRIVATE, 0, 0, true, false, false, NULL, NULL },
    { &_lpctype_void, { .hook = H_CREATE_SUPER }, "protected", TYPE_MOD_PRIVATE, 0, 0, true, false, false, NULL, NULL },
    { &_lpctype_int, { .hook = H_DEFAULT_METHOD }, "protected", TYPE_MOD_PRIVATE, 2, 18, false, true, false, NULL, NULL },
    { &_lpctype_int_or_string, { .hook = H_MODIFY_COMMAND }, "static", TYPE_MOD_PRIVATE | TYPE_MOD_PROTECTED, 1, 0, false, false, false, NULL, NULL },
    { &_lpctype_int_or_string, { .hook = H_MODIFY_COMMAND_FNAME }, "static", TYPE_MOD_PRIVATE | TYPE_MOD_PROTECTED, 1, 0, false, false, false, NULL, NULL },
    { &_lpctype_void, { .hook = H_NOECHO }, "visible", TYPE_MOD_PRIVATE | TYPE_MOD_PROTECTED | TYPE_MOD_STATIC, 3, 27, false, false, false, NULL, NULL },
    { &_lpctype_void, { .hook = H_PRINT_PROMPT }, "visible", TYPE_MOD_PRIVATE | TYPE_MOD_PROTECTED | TYPE_MOD_STATIC, 1, 0, false, false, false, NULL, NULL },
    { &_lpctype_void, { .hook = H_RESET }, "protected", TYPE_MOD_PRIVATE, 0, 0, false, false, false, NULL, NULL },
    { &_lpctype_void, { .hook = H_SEND_NOTIFY_FAIL }, "protected", TYPE_MOD_PRIVATE, 3, 31, false, false, false, NULL, NULL },
    { &_lpctype_mixed, { .hook = H_TELNET_NEG }, "visible", TYPE_MOD_PRIVATE | TYPE_MOD_PROTECTED | TYPE_MOD_STATIC, 3, 42, false, false, true, NULL, NULL },
    { NULL }
};

/*----------------------------------------------------------------------*/

/* List of function argument types.
 * These are referenced by .arg_index from the declarations.
 */

lpctype_t* applied_decl_args[] = {
    /* 0 */ &_lpctype_string,
    /* 1 */ &_lpctype_any_object,
    /* 2 */ &_lpctype_string,
    /* 3 */ &_lpctype_int,
    /* 4 */ &_lpctype_any_object,
    /* 5 */ &_lpctype_string,
    /* 6 */ &_lpctype_string,
    /* 7 */ &_lpctype_string,
    /* 8 */ &_lpctype_int,
    /* 9 */ &_lpctype_int,
    /* 10 */ &_lpctype_int,
    /* 11 */ &_lpctype_int,
    /* 12 */ &_lpctype_int,
    /* 13 */ &_lpctype_int,
    /* 14 */ &_lpctype_string,
    /* 15 */ &_lpctype_mixed,
    /* 16 */ &_lpctype_mixed,
    /* 17 */ &_lpctype_mixed,
    /* 18 */ &_lpctype_mixed,
    /* 19 */ &_lpctype_string,
    /* 20 */ &_lpctype_bytes,
    /* 21 */ &_lpctype_int,
    /* 22 */ &_lpctype_string,
    /* 23 */ &_lpctype_string,
    /* 24 */ &_lpctype_string,
    /* 25 */ &_lpctype_int,
    /* 26 */ &_lpctype_mixed,
    /* 27 */ &_lpctype_int,
    /* 28 */ &_lpctype_any_object,
    /* 29 */ &_lpctype_int,
    /* 30 */ &_lpctype_closure,
    /* 31 */ &_lpctype_string,
    /* 32 */ &_lpctype_any_object,
    /* 33 */ &_lpctype_any_object,
    /* 34 */ &_lpctype_string,
    /* 35 */ &_lpctype_string,
    /* 36 */ &_lpctype_string,
    /* 37 */ &_lpctype_any_object_or_lwobject,
    /* 38 */ &_lpctype_string,
    /* 39 */ &_lpctype_int_or_string,
    /* 40 */ &_lpctype_catch_msg_arg,
    /* 41 */ &_lpctype_any_object,
    /* 42 */ &_lpctype_int,
    /* 43 */ &_lpctype_int,
    /* 44 */ &_lpctype_int_array,
};

/*----------------------------------------------------------------------*/

/* Uninitialized hash table for use by the compiler.
 */

applied_decl_t* applied_decl_hash_table[128];
int applied_decl_hash_table_mask = 127;

