macro(cbp_set_warning_flags)
  if(CMAKE_C_COMPILER_ID STREQUAL "MSVC")
    # /wd5105:
    # https://docs.microsoft.com/en-us/cpp/error-messages/compiler-warnings/c5105?view=msvc-160
    set(WARNING_FLAGS /W3 /wd5105)
  else()
    set(WARNING_FLAGS
        -Wall
        -Wextra
        -Wstrict-prototypes
        -Wshadow
        -Wconversion
        -Wmissing-prototypes
        -Wno-unused-parameter
        -Wsign-conversion
        -Wno-unused-function)

    if(NOT CMAKE_C_COMPILER_ID STREQUAL "GNU")
      list(APPEND WARNING_FLAGS -Wno-gnu-designator -Wno-empty-translation-unit
           -Wno-gnu-statement-expression -Wno-nullability-extension)
    endif()
  endif()
endmacro()
