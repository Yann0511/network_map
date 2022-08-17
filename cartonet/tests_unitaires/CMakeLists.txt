cmake_minimum_required(VERSION 3.0)
project(cartonet C)

include(CTest)
link_directories("/usr/local/lib/")
include_directories("/usr/local/include/unity/")

find_program(MEMORYCHECK_COMMAND valgrind)
set(MEMORYCHECK_COMMAND_OPTIONS "--tracechildren=yes --leak-check=full --show-leak-kinds=all")
add_definitions(-ggdb3)

add_executable(cartonet tests.c ../fonctions.c)
target_link_libraries(cartonet unity pcap hiredis)
add_test(tests cartonet)
