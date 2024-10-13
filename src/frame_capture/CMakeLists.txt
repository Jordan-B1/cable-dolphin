add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/packets)

set(CMAKE_CXX_FLAGS "-Wall -Wextra")

set(SOURCES
    ${SOURCES}
    ${CMAKE_CURRENT_LIST_DIR}/index.c
    PARENT_SCOPE
)
