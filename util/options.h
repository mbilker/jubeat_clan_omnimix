#ifndef UTIL_OPTIONS_H
#define UTIL_OPTIONS_H

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#include "defs.h"

/**
 * Value types support by option values
 */
enum util_options_type {
    UTIL_OPTIONS_TYPE_INT,
    UTIL_OPTIONS_TYPE_STR,
    UTIL_OPTIONS_TYPE_BOOL,
    UTIL_OPTIONS_TYPE_BIN,
};

/**
 * Single option definition element. Use this to define possible option
 * key-value tuples to parse from an argument list
 */
struct util_options_def {
    const char* name;
    const char* description;
    const char param;
    enum util_options_type type;
    union {
        int i;
        const char* str;
        bool b;
        struct {
            const uint8_t* data;
            size_t len;
        } bin;
    } default_value;
};

/**
 * Option definitions. A list of key-value elements defining option values
 * as well as usage information for the application
 */
struct util_options_defs {
    const char* usage_header;
    char usage_param;
    const struct util_options_def** defs;
    uint32_t ndefs;
};

/**
 * A single option value as part of the key-value tuple
 */
struct util_options_value {
    bool avail;
    union {
        int i;
        char* str;
        bool b;
        struct {
            uint8_t* data;
            size_t len;
        } bin;
    } value;
};

/**
 * Parsed option values based on an options definition
 */
struct util_options_opts {
    const struct util_options_defs* defs;
    struct util_options_value* values;
    uint32_t entries;
};

/**
 * Set the output stream (stdout, stderr) to print any usage information to.
 *
 * If this is not called to set a stream, OutputDebugString is set as default.
 *
 * @param out Output stream to print to. Set to NULL to print using
 * OutputDebugString.
 */
void util_options_set_usage_output(FILE* out);

/**
 * Get options from the initial argument list
 *
 * @param argc Argc from main
 * @param argv Argv from main
 * @param option_defs A list of option definitions. The arguments are parsed
 *        using this list. If NULL, usage information with the definition
 *        is printed and this call also returns NULL.
 * @return A list of parsed options based on the specified definitions or
 *         NULL if usage information was printed.
 */
struct util_options_opts* util_options_init(int argc, char** argv,
        const struct util_options_defs* option_defs);

/**
 * Get options from the command line arguments.
 *
 * Use this if you don't have access to argc and argv.
 *
 * @param option_defs A list of option definitions. The arguments are parsed
 *        using this list. If NULL, usage information with the definition
 *        is printed and this call also returns NULL.
 * @return A list of parsed options based on the specified definitions or
 *         NULL if usage information was printed.
 */
struct util_options_opts* util_options_init_from_cmdline(
        const struct util_options_defs* option_defs);

/**
 * Get an integer value from an options list
 *
 * @param opts Parsed options list received from util_options_get
 * @param name Name of the options key
 * @return Value of the options key converted to an integer value. If the type
 *         of the options key is not matching, 0 is returned
 */
int util_options_get_int(const struct util_options_opts* opts,
    const char* name);

/**
 * Get a string from an options list
 *
 * @param opts Parsed options list received from util_options_get
 * @param name Name of the options key
 * @return Value of the options key converted to a string. If the type
 *         of the options key is not matching, NULL is returned
 */
const char* util_options_get_str(const struct util_options_opts* opts,
    const char* name);

/**
 * Get a bool value from an options list
 *
 * @param opts Parsed options list received from util_options_get
 * @param name Name of the options key
 * @return Value of the options key converted to a bool value. If the type
 *         of the options key is not matching, false is returned
 */
bool util_options_get_bool(const struct util_options_opts* opts,
    const char* name);

/**
 * Get binary data from an options list
 *
 * @param opts Parsed options list received from util_options_get
 * @param name Name of the options key
 * @param length Pointer to return the length of the binary data to
 *         (set to NULL if not required)
 * @return Value of the options key converted to a binary array. If the type
 *         of the options key is not matching, NULL is returned
 */
const uint8_t* util_options_get_bin(const struct util_options_opts* opts,
    const char* name, size_t* length);

/**
 * Print usage information
 *
 * @param option_defs A list of option definitions.
 */
void util_options_print_usage(const struct util_options_defs* opts);

/**
 * Free an options list
 *
 * @param option_defs A list of option definitions.
 */
void util_options_free(struct util_options_opts* opts);

#endif
