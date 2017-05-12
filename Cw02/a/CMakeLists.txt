cmake_minimum_required (VERSION 2.6)

set(CMAKE_C_FLAGS "-std=c99 -Wall -g")


file(GLOB SRCS1 main1.c main.h)
file(GLOB SRCS2 main2.c main.h)
file(GLOB SRCS3 main3.c main.h)
file(GLOB SRCS4 main4.c main.h)
file(GLOB SRCS5 main5.c main.h)

add_executable(main1 ${SRCS1})
add_executable(main2 ${SRCS2})
add_executable(main3 ${SRCS3})
add_executable(main4 ${SRCS4})
add_executable(main5 ${SRCS5})

set_target_properties(main1 PROPERTIES RUNTIME_OUTPUT_DIRECTORY out)
set_target_properties(main2 PROPERTIES RUNTIME_OUTPUT_DIRECTORY out)
set_target_properties(main3 PROPERTIES RUNTIME_OUTPUT_DIRECTORY out)
set_target_properties(main4 PROPERTIES RUNTIME_OUTPUT_DIRECTORY out)
set_target_properties(main5 PROPERTIES RUNTIME_OUTPUT_DIRECTORY out)

target_link_libraries(main1 pthread)
target_link_libraries(main2 pthread)
target_link_libraries(main3 pthread)
target_link_libraries(main4 pthread)
target_link_libraries(main5 pthread)
