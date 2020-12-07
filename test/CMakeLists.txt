function(st1201_add_test name)

  add_executable(test_${name} ${name}.c)
  target_link_libraries(test_${name} ST1201::st1201)
  set_target_properties(test_${name} PROPERTIES C_STANDARD 99)
  add_test(NAME ${name} COMMAND test_${name})
  target_compile_options(test_${name}
    PRIVATE
    $<$<STREQUAL:${CMAKE_C_COMPILER_ID},MSVC>:/W4 /WX>
    $<$<STREQUAL:${CMAKE_C_COMPILER_ID},GNU>:-pedantic -Wall -Wextra -Wshadow -Werror>
    $<$<STREQUAL:${CMAKE_C_COMPILER_ID},Clang>:-pedantic -Wall -Wextra -Wshadow -Werror>
    $<$<STREQUAL:${CMAKE_C_COMPILER_ID},AppleClang>:-pedantic -Wall -Wextra -Wshadow -Werror>
  )

endfunction()

st1201_add_test(st1201)