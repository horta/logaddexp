if(CMAKE_C_COMPILER_ID MATCHES "GNU"
   OR CMAKE_CXX_COMPILER_ID MATCHES "GNU"
   OR CMAKE_C_COMPILER_ID MATCHES "(Apple)?[Cc]lang"
   OR CMAKE_CXX_COMPILER_ID MATCHES "(Apple)?[Cc]lang")
  # GCC/Clang
  add_compile_options(-Wall -Wextra)
elseif(MSVC)
  # MSVC
  add_compile_options(/W4)
endif()
