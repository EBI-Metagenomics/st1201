function(st1201_add_test name data_filepath)

  add_executable(${name} ${name}.c)
  target_link_libraries(${name} ST1201::st1201)
  set_target_properties(${name} PROPERTIES C_STANDARD 99)
  add_test(NAME ${name} COMMAND ${name})
  target_compile_options(${name}
    PRIVATE
    $<$<STREQUAL:${CMAKE_C_COMPILER_ID},MSVC>:/W4 /WX>
    $<$<STREQUAL:${CMAKE_C_COMPILER_ID},GNU>:-pedantic -Wall -Wextra -Wshadow -Werror>
    $<$<STREQUAL:${CMAKE_C_COMPILER_ID},Clang>:-pedantic -Wall -Wextra -Wshadow -Werror>
    $<$<STREQUAL:${CMAKE_C_COMPILER_ID},AppleClang>:-pedantic -Wall -Wextra -Wshadow -Werror>
  )
  target_compile_definitions(${name} PUBLIC "ST1201_TEST_DATA_FILEPATH=\"${data_filepath}\"")

endfunction()

file(COPY data/1bytes.csv DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/data")
file(COPY data/2bytes.csv DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/data")
file(COPY data/4bytes.csv DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/data")
file(COPY data/8bytes.csv DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/data")

st1201_add_test(test_st1201 "${CMAKE_CURRENT_BINARY_DIR}/data/1bytes.csv")
