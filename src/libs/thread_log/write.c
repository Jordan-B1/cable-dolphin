#include "write.h"

void safe_write(const char *msg, size_t len, int output_stream, pthread_mutex_t *lock) {
    pthread_mutex_lock(lock);
    write(output_stream, msg, len);
    pthread_mutex_unlock(lock);
}