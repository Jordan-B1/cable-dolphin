cmake_minimum_required(VERSION 3.29)

project(cabledolphin C)

set(SOURCE_FOLDER ./src)

set(SOURCES 
    ${SOURCE_FOLDER}/main.c
    ${SOURCE_FOLDER}/packet_capture/index.c
)

add_executable(cabledolphin ${SOURCES})
include_directories(./include)

target_link_libraries(cabledolphin pcap)