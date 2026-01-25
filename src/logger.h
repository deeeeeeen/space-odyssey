#ifndef LOGGER_H
#define LOGGER_H

#include "raylib.h"
#include <stdio.h>
#include <stdarg.h>

#define COLOR_RESET   "\033[0m"
#define COLOR_ERROR   "\033[1;31m"
#define COLOR_WARNING "\033[1;33m"
#define COLOR_INFO    "\033[1;32m"
#define COLOR_DEBUG   "\033[1;34m"

static inline void ColorLog(int msgType, const char *text, va_list args)
{
    const char *color = COLOR_RESET;
    const char *prefix = "";

    switch (msgType)
    {
        case LOG_INFO:    color = COLOR_INFO;    prefix = "[INFO] "; break;
        case LOG_WARNING: color = COLOR_WARNING; prefix = "[WARN] "; break;
        case LOG_ERROR:   color = COLOR_ERROR;   prefix = "[ERROR] "; break;
        case LOG_DEBUG:   color = COLOR_DEBUG;   prefix = "[DEBUG] "; break;
        default: break;
    }

    printf("%s%s", color, prefix);
    vprintf(text, args);
    printf("%s\n", COLOR_RESET);
}

#endif