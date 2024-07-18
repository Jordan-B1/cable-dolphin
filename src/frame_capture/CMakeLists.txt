add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/packets)

set(SOURCES
    ${SOURCES}
    ${CMAKE_CURRENT_LIST_DIR}/index.c
    PARENT_SCOPE
)
message(STATUS "Added frame_capture source files: ${SOURCES}")