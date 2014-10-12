#include "log.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

void log_format(const char* tag, const char* message, va_list args) {

    time_t now;
    time(&now);
    char* date = ctime(&now);
    date[strlen(date) - 1] = '\0';

    printf("%s [%s]: ", date, tag);
    vprintf(message, args);
    printf("\n");

}


void log_msg(const char* tag, const char* message, ...) {

    va_list args;
    va_start(args, message);

    log_format(tag, message, args);

    va_end(args);

}


void log_version(const char* message, uint32_t version, ...) {

    va_list args;
    va_start(args, version);

    int major    = version >> 24;
    int minor    = (version >> 16) & 255;
    int revision = (version >>  8) & 255;
    int release  = version & 255;

    char version_message[MSG_BUFFER];

    if (release == 0)
        snprintf(version_message, MSG_BUFFER, 
                "%s %i.%i.%i unofficial release.", 
                message, major, minor, revision);
    else 
        snprintf(version_message, MSG_BUFFER,
                "%s %i.%i.%i release %i.",
                message, major, minor, revision, release);

    log_format(LOADING, version_message, args);

    va_end(args);

}
        
