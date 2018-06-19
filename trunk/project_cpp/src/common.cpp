#include "common.h"
#include <stdarg.h>


void write_log(const char *file, uint16 line, const char *function, const char * format, ...)
{
    char logmsg[4096] = "";

    va_list args;
    va_start(args, format);

#ifdef _WIN32
    _vsnprintf(logmsg, sizeof(logmsg) - 1, format, args);
#else
    vsnprintf(logmsg, sizeof(logmsg) - 1, format, args);
#endif

    va_end(args);

    printf("%s:%d:%s|%s \n", file, line, function, logmsg);
}
