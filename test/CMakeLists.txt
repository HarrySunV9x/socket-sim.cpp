add_executable(hello_test
        validate_arg_test.cpp)

target_link_libraries(hello_test
        ${PROJECT_SOURCE_DIR}/lib/libgtest.a
        ${PROJECT_SOURCE_DIR}/lib/libgtest_main.a
        socket_test_lib)
