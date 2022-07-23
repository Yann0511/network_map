
include_directories(
  ${CMAKE_SOURCE_DIR}/src/
  )

file(GLOB src . *.c)

add_library(networkMap OBJECT ${srcs})

add_subdirectory(tests)
