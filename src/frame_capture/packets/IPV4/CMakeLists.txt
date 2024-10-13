set(CMAKE_CXX_FLAGS "-Wall -Wextra")

add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/segments)

set(SOURCES
    ${SOURCES}
    PARENT_SCOPE
)
