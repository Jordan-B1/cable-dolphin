add_subdirectory(ARP)
add_subdirectory(RARP)
add_subdirectory(IPV4)
add_subdirectory(IPV6)

set(CMAKE_CXX_FLAGS "-Wall -Wextra")

set(SOURCES
    ${SOURCES}
    PARENT_SCOPE
)
