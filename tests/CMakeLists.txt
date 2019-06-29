add_executable(tests_unic unity.c tests.c)
target_link_libraries(tests_unic UniC)
add_test(NAME tests_unicode COMMAND tests_unic)