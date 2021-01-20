add_executable(test_libfundot main.c)

target_link_libraries(test_libfundot fundot)

enable_testing()

add_test(NAME test_libfundot_runs COMMAND test_libfundot)

add_test(NAME test_libfundot_adds COMMAND test_libfundot "1 + 1")

set_tests_properties(test_libfundot_adds
  PROPERTIES PASS_REGULAR_EXPRESSION "2"
  )
