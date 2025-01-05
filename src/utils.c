#include "utils.h"

bool write_buffer(output_buffer_t *buffer, char *str, ...)
{
    va_list list;
    va_start(list, str);
    int len = vsprintf(buffer->buffer + buffer->cursor, str, list);


    if (len <= 0) {
        return false;
    }
    buffer->cursor += len;
    return true;
}