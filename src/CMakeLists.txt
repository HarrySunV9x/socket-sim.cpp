# 设置源文件列表
set(SRC_FILES main.cpp
        validate_arg.cpp
        logger.cpp
        socket_base.cpp
        socket_server.cpp
        socket_handler.cpp
        socket_client.cpp
)

# 创建静态库
add_library(socket_test_lib STATIC
        validate_arg.cpp
        logger.cpp
        socket_base.cpp
        socket_server.cpp
        socket_handler.cpp
        socket_client.cpp)

# 创建可执行文件
add_executable(${APP_NAME} ${SRC_FILES})