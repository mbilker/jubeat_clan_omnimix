#define LOG_MODULE

#include "log.h"
#include "str.h"

#include <windows.h>

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static log_writer_t log_writer;
static void *log_writer_ctx;
static unsigned int log_level;

static void log_builtin_fatal(const char *module, const char *fmt, ...);
static void log_builtin_info(const char *module, const char *fmt, ...);
static void log_builtin_misc(const char *module, const char *fmt, ...);
static void log_builtin_warning(const char *module, const char *fmt, ...);
static void
log_builtin_format(unsigned int msg_level, const char *module, const char *fmt, va_list ap);

#define IMPLEMENT_SINK(name, msg_level)                                                            \
    static void name(const char *module, const char *fmt, ...)                                     \
    {                                                                                              \
        va_list ap;                                                                                \
                                                                                                   \
        va_start(ap, fmt);                                                                         \
        log_builtin_format(msg_level, module, fmt, ap);                                            \
        va_end(ap);                                                                                \
    }

IMPLEMENT_SINK(log_builtin_info, 2)
IMPLEMENT_SINK(log_builtin_misc, 3)
IMPLEMENT_SINK(log_builtin_warning, 1)

static void log_builtin_fatal(const char *module, const char *fmt, ...)
{
    va_list ap;

    va_start(ap, fmt);
    log_builtin_format(0, module, fmt, ap);
    va_end(ap);

    DebugBreak();
    ExitProcess(EXIT_FAILURE);
}

static void
log_builtin_format(unsigned int msg_level, const char *module, const char *fmt, va_list ap)
{
    static const char chars[] = "FWIM";

    /* 64k so we can log data dumps of rs232 without crashing */
    char line[65536];
    char msg[65536];
    int result;

    str_vformat(msg, sizeof(msg), fmt, ap);
    result = str_format(line, sizeof(line), "%c:%s: %s\n", chars[msg_level], module, msg);

    if (msg_level <= log_level) {
        log_writer(log_writer_ctx, line, result);
    }
}

void log_assert_body(const char *file, int line, const char *function)
{
    log_impl_fatal("assert", "%s:%d: function `%s'", file, line, function);
}

void log_to_external(
    log_formatter_t misc, log_formatter_t info, log_formatter_t warning, log_formatter_t fatal)
{
    log_impl_misc = misc;
    log_impl_info = info;
    log_impl_warning = warning;
    log_impl_fatal = fatal;
}

void log_to_writer(log_writer_t writer, void *ctx)
{
    log_impl_misc = log_builtin_misc;
    log_impl_info = log_builtin_info;
    log_impl_warning = log_builtin_warning;
    log_impl_fatal = log_builtin_fatal;

    if (writer != NULL) {
        log_writer = writer;
        log_writer_ctx = ctx;
    } else {
        log_writer = log_writer_null;
    }
}

/*
void log_set_level(unsigned int new_level)
{
    log_level = new_level;
}

void log_writer_debug(void *, const char *chars, size_t)
{
    OutputDebugStringA(chars);
}

void log_writer_console(void *, const char *chars, size_t)
{
    printf("%s", chars);
}

void log_writer_file(void *ctx, const char *chars, size_t nchars)
{
    fwrite(chars, 1, nchars, (FILE *) ctx);
    fflush((FILE*) ctx);
}
*/

void log_writer_null(void *, const char *, size_t)
{
}

log_formatter_t log_impl_misc = log_builtin_misc;
log_formatter_t log_impl_info = log_builtin_info;
log_formatter_t log_impl_warning = log_builtin_warning;
log_formatter_t log_impl_fatal = log_builtin_fatal;
static log_writer_t log_writer = log_writer_null;
static unsigned int log_level = 4;
