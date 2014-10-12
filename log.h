#ifndef LOG_H
#define LOG_H

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdint.h>

#define ERROR   "ERROR  "
#define WARNING "WARNING"
#define LOADING "LOADING"
#define GAME    "GAME   "

#define MSG_BUFFER 255

void log_msg(const char* tag, const char* message, ...);

void log_version(const char* message, uint32_t version, ...);

#endif /* LOG_H */
