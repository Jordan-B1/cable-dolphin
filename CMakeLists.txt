cmake_minimum_required(VERSION 3.28)


project(cabledolphin C)

set(CC clang)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

set(SOURCE_FOLDER ${CMAKE_CURRENT_LIST_DIR}/src)

set(SOURCES
    ${SOURCE_FOLDER}/main.c
    ${SOURCE_FOLDER}/utils.c
)

add_subdirectory(${SOURCE_FOLDER}/libs)
add_subdirectory(${SOURCE_FOLDER}/frame_capture)
add_subdirectory(${SOURCE_FOLDER}/interface)

include_directories(./include ./src/libs/2D_array ./src/libs/thread_log)

add_executable(cabledolphin ${SOURCES})

target_link_libraries(cabledolphin pcap)
target_link_libraries(cabledolphin 2D_ARRAY_LIB)
target_link_libraries(cabledolphin THREAD_LOG_LIB)