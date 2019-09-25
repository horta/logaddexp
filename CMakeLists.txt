cmake_minimum_required(VERSION 3.4 FATAL_ERROR)
project(logaddexp LANGUAGES C)
set(CMAKE_C_STANDARD 11)

# Generate compile_commands.json file
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(CMAKE_C_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -pedantic -Wstrict-prototypes -Wshadow
    -Wconversion -Wmissing-prototypes -Wno-unused-parameter)
endif()

if( UNIX AND NOT BEOS )
  set(LIBS m)
endif()


enable_testing()

add_executable(test_logaddexp test/logaddexp.c)
target_include_directories(test_logaddexp PUBLIC ./)
target_link_libraries(test_logaddexp ${LIBS})
add_test(NAME logaddexp COMMAND test_logaddexp)

add_executable(test_logaddexps test/logaddexps.c)
target_include_directories(test_logaddexps PUBLIC ./)
target_link_libraries(test_logaddexp ${LIBS})
add_test(NAME logaddexps COMMAND test_logaddexps)

add_executable(test_logaddexpss test/logaddexpss.c)
target_include_directories(test_logaddexpss PUBLIC ./)
target_link_libraries(test_logaddexp ${LIBS})
add_test(NAME logaddexpss COMMAND test_logaddexpss)
