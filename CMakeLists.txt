cmake_minimum_required (VERSION 3.18)
project (NetworkMap C)

include(CTest)
link_directories("/usr/local/lib")
include_directories("/usr/local/include/unity" "./include")

find_program(MEMORYCHECK_COMMAND valgrind)
set( MEMORYCHECK_COMMAND_OPTIONS "--trace-children=yes --leak-check=full --show-leak-kinds=all" )

add_definitions(-ggdb3)
add_subdirectory (include src)
