include(FetchContent)

find_library(ZLOG_LIBRARY zlog)
find_path(ZLOG_INCLUDE_DIR zlog.h)

if(NOT ZLOG_LIBRARY OR NOT ZLOG_INCLUDE_DIR)
    message(WARNING "Zlog not found. Fetching and building zlog.")

    FetchContent_Declare(
        zlog
        GIT_REPOSITORY https://github.com/HardySimpson/zlog.git
        GIT_TAG master
    )
    FetchContent_MakeAvailable(zlog)

    execute_process(
        COMMAND make
        WORKING_DIRECTORY ${zlog_SOURCE_DIR}
        RESULT_VARIABLE MAKE_RESULT
    )

    if(NOT MAKE_RESULT EQUAL 0)
        message(FATAL_ERROR "Failed to build zlog.")
    endif()

    set(ZLOG_LIBRARY ${zlog_SOURCE_DIR}/src/libzlog.a PARENT_SCOPE) # Adjust to the built library location
    set(ZLOG_INCLUDE_DIR ${zlog_SOURCE_DIR}/src PARENT_SCOPE)
    set(ZLOG_INCLUDE_DIR ${zlog_SOURCE_DIR}/src)
endif()

include_directories(${ZLOG_INCLUDE_DIR} ./2D_array)

add_subdirectory(2D_array)