cmake_minimum_required(VERSION 3.28)


project(cabledolphin C)

set(SOURCE_FOLDER ${CMAKE_CURRENT_LIST_DIR}/src)

set(SOURCES
    ${SOURCE_FOLDER}/main.c
)

add_subdirectory(${SOURCE_FOLDER}/frame_capture)


include_directories(./include)

add_executable(cabledolphin ${SOURCES})

target_link_libraries(cabledolphin pcap)