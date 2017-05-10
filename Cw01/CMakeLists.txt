cmake_minimum_required (VERSION 2.6)

set(CMAKE_C_FLAGS "-std=c99 -Wall -g")


file(GLOB SRCS main.c main.h)

add_executable(main ${SRCS})

set_target_properties(main PROPERTIES RUNTIME_OUTPUT_DIRECTORY out)

target_link_libraries(main pthread)
