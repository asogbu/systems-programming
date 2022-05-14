/* timestamp.c: Timestamp Functions */

#include "timestamp.h"

#include <time.h>
#include <sys/time.h>

/**
 * Return current timestamp as a double.
 *
 * Utilizes gettimeofday for precision (accounting for seconds and
 * microseconds) and falls back to time (only account for seconds) if that
 * fails.
 *
 * @return  Current time as a double.
 **/
double timestamp() {
    struct timeval tv;
    if (gettimeofday(&tv, NULL) == 0) {
        return tv.tv_sec + (tv.tv_usec / 1000000.0);
    } else {
        return time(NULL);
    }
}

/* vim: set expandtab sts=4 sw=4 ts=8 ft=c: */
