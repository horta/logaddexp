function(logaddexp_add_test name)

  add_executable(test_${name} ${name}.c)
  target_link_libraries(test_${name} LOGADDEXP::logaddexp)
  add_test(NAME ${name} COMMAND test_${name})
  target_compile_options(test_${name}
    PRIVATE
    $<$<BOOL:${WIN32}>:/W4 /WX>
    $<$<NOT:$<BOOL:${WIN32}>>:-pedantic -Wall -Wextra -Wshadow -Werror>
  )

endfunction()

logaddexp_add_test(logaddexp)
logaddexp_add_test(logaddexps)
logaddexp_add_test(logaddexpss)
