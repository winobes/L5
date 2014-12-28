#include "log.h"

void error(const char* message, ...) {
    
    va_list args;
    va_start(args, message);
    log_msg(ERROR, message, args);
    va_end(args);

    exit(1);

}

