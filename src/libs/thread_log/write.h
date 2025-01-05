#ifndef __WRITE_H__
#define __WRITE_H__

#include <pthread.h>
#include <unistd.h>

void safe_write(const char *msg, size_t len, int output_stream,
                pthread_mutex_t *lock);

#endif // __WRITE_H__
