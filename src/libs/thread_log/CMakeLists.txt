set(THREAD_LOG_LIB thread_log)

set(LIB_SOURCE
    write.c
)

add_library(THREAD_LOG_LIB STATIC ${LIB_SOURCE})