add_executable(hello_test testMain.cpp)

target_link_libraries(hello_test
        ${PROJECT_SOURCE_DIR}/lib/libgtest.a
        ${PROJECT_SOURCE_DIR}/lib/libgtest_main.a)
