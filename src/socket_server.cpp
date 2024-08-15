//
// Created by WorkHarry on 2024/8/15.
//

#include "include/socket_server.h"
#include <sys/socket.h>					    // 引入socket数据类型与方法，如struct sockaddr、socket()、bind()等
#include <unistd.h>							// 与操作系统交互的方法，如close()
#include <netinet/in.h>					    // 包含了用于IP地址和端口号等数据结构，如IPPROTO_IP
#include <arpa/inet.h>                      // inet_addr
#include "include/logger.h"

#define MAX_TRY_PORT 5

SocketServer::SocketServer() = default;

void SocketServer::Close() {
    close(GetSocketFd());
}

int SocketServer::Init() {
    int serverFd = socket(AF_INET, SOCK_STREAM, IPPROTO_IP);
    if (serverFd < 0) {
        spdlog::error("socket创建失败： " + std::string(strerror(errno)));
        return -1;
    }
    SetSocketFd(serverFd);

    struct sockaddr_in socket_addr = {0};
    memset(&socket_addr, 0, sizeof(socket_addr));		            // 初始化socket_addr为0
    socket_addr.sin_family = AF_INET;                                       // 协议
    socket_addr.sin_addr.s_addr = inet_addr(GetAddress().c_str());	    // 域名

    for (int i = 0; i < MAX_TRY_PORT; i++) {
        int port = std::stoi(GetPort()) + i;
        socket_addr.sin_port = htons(port);	// 端口
        spdlog::info("正在尝试绑定: " + GetAddress() + std::to_string(port));      // 错误打印

        if (bind(serverFd, (struct sockaddr *)&socket_addr, sizeof(socket_addr)) == 0) {
            spdlog::info("绑定成功");
            return 0;
        }
    }

    spdlog::error("绑定失败： " + std::string(strerror(errno)));
    Close();
    return -1;
}
int SocketServer::Init(std::string address) {
    SetAddress(address);
    return Init();
}
int SocketServer::Init(std::string address, std::string port) {
    SetAddress(address);
    SetPort(port);
    return Init();
}

int SocketServer::ProcessData(int processFd) {
    char recvBuff[1024];
    int readLen = recv(processFd, recvBuff, 1024, 0);
    if(readLen < 0) {
        printf("Recv Socket Failed. err: %s", strerror(errno));		// 错误打印
        close(processFd);							// 接收失败关闭Socket
        return -1;  // 异常退出
    }

    std::string recvStr = recvBuff;
    // 数据处理逻辑，此处为打印
    spdlog::info("收到数据： {0}", recvStr.c_str());

    if (recvStr == "stop") {
        return 0;   // 正常退出
    }
    return 1;   // 继续收发
}

int SocketServer::EstablishConnection() {
    // 默认Server只支持一个链接
    if (listen(GetSocketFd(), 1) < 0) {
        spdlog::error("监听失败： " + std::string(strerror(errno)));
        Close();
        return -1;
    }
    int accept_socket = accept(GetSocketFd(), nullptr, nullptr);

    if (accept_socket < 0) {
        spdlog::error("接收失败： " + std::string(strerror(errno)));
        Close();
        return -1;
    }

    while(true) {
        if (ProcessData(accept_socket) < 0) {
            return -1;
        } else if (ProcessData(accept_socket) == 0) {
            return 0;
        }
    }
}


