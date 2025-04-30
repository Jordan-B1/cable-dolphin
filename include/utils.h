#ifndef __UTILS_H__
#define __UTILS_H__

#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdarg.h>

#define SAFEVAL(x, val) if (!x) return val
#define SAFE(x) if (!x) return 0
#define PSAFE(x, y) if (!x) {printf y; return 0;}
#define ESAFE(x, y) if (!x) {perror(y); return 0;}

#define BASE_OUTPUT_BUFFER_SIZE 512

typedef struct output_buffer {
    char buffer[BASE_OUTPUT_BUFFER_SIZE];
    size_t cursor;
} output_buffer_t;

bool write_buffer(output_buffer_t *buffer, char *str, ...);


#endif // __UTILS_H__
