//
// Created by WorkHarry on 2024/8/16.
//

#include "include/socket_client.h"
#ifdef PLATFORM_WINDOWS
#include <winsock2.h>  // windows的socket头文件
#else
#include <arpa/inet.h>   // inet_addr
#include <netinet/in.h>  // 包含了用于IP地址和端口号等数据结构，如IPPROTO_IP
#include <sys/socket.h>  // 引入socket数据类型与方法，如struct sockaddr、socket()、bind()等
#include <unistd.h>      // 与操作系统交互的方法，如close()
#endif
#include "include/logger.h"
#include <iostream>

SocketClient::SocketClient() = default;

void SocketClient::Close() {
    close(GetSocketFd());
}

int SocketClient::Init() {
#ifdef PLATFORM_WINDOWS
    /* 初始化WindowsAPI */
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        spdlog::error("WSA Start Up Error");
        return -1;
    }
    spdlog::info("WSA Start Up");
#endif

    int serverFd = socket(AF_INET, SOCK_STREAM, IPPROTO_IP);
    if (serverFd < 0) {
        spdlog::error("socket创建失败");
        return -1;
    }
    SetSocketFd(serverFd);

    spdlog::info("Client Socket 创建成功, serverFd: {0}", serverFd);
    return 0;
}

int SocketClient::Init(std::string address) {
    SetAddress(address);
    return Init();
}
int SocketClient::Init(std::string address, std::string port) {
    SetAddress(address);
    SetSocketPort(port);
    return Init();
}

int SocketClient::Init(std::string address, std::string port, std::string message) {
    SetAddress(address);
    SetSocketPort(port);
    m_message = message;
    return Init();
}

int SocketClient::ProcessData(int processFd) {
    if (!m_message.empty()) {
        ssize_t sentLen = send(processFd, m_message.c_str(), m_message.size(), 0);
        if (sentLen != static_cast<ssize_t>(m_message.size())) {
            spdlog::error("数据发送失败. FD: {0}, 原因：{1}, 数据：{2}",
                          processFd, strerror(errno), m_message);
            Close();  // 确保连接关闭
            return -1;
        }
        spdlog::info("数据发送成功. FD: {0}, 数据：{1}", processFd, m_message);

        return 0;
    }
    while (true) {
        std::string message;
        std::cout << "请输入消息: ";
        std::getline(std::cin, message);  // 使用 std::getline 读取整行输入
        if (message.empty()) {
            continue;  // 跳过空输入
        }

        std::string sendBuffer = message;

        ssize_t sentLen = send(processFd, sendBuffer.c_str(), sendBuffer.size(), 0);
        if (sentLen != static_cast<ssize_t>(sendBuffer.size())) {
            spdlog::error("数据发送失败. FD: {0}, 原因：{1}, 数据：{2}",
                          processFd, strerror(errno), sendBuffer);
            Close();  // 确保连接关闭
            return -1;
        }
        spdlog::info("数据发送成功. FD: {0}, 数据：{1}", processFd, sendBuffer);
        char recvBuff[1024];
        spdlog::info("Client 正在等待接收数据...");
        int readLen = recv(processFd, recvBuff, sizeof(recvBuff) - 1, 0);
        if (readLen <= 0) {
            if (readLen == 0) {
                spdlog::error("连接关闭. FD: {0}", processFd);
            } else {
                spdlog::error("接收数据失败. FD: {0}, 原因：{1}", processFd, strerror(errno));
            }
            close(processFd);
            return -1;
        } else {
            recvBuff[readLen] = '\0';
            std::string recvStr = recvBuff;
            // 数据处理逻辑，此处为打印
            spdlog::info("收到数据： {0}", recvStr.c_str());
        }
        

    }

    return 0;  // 继续收发
}

int SocketClient::EstablishConnection() {
    struct sockaddr_in socket_addr = {0};
    memset(&socket_addr, 0, sizeof(socket_addr));                   // 初始化socket_addr为0
    socket_addr.sin_family = AF_INET;                               // 协议
    socket_addr.sin_addr.s_addr = inet_addr(GetAddress().c_str());  // 域名

    for (int i = 0; i < MAX_TRY_PORT; i++) {
        int port = std::stoi(GetPort()) + i;
        socket_addr.sin_port = htons(port);
        if (connect(GetSocketFd(), (struct sockaddr *)&socket_addr, sizeof(socket_addr)) == 0) {
            spdlog::info("连接成功, Fd: {0}, address: {1}, port: {2}", GetSocketFd(), GetAddress(), port);
            break;
        } else {
            spdlog::error("建立连接失败, FD: {0}, address: {1}, port: {2}, 原因：{3}",
                          GetSocketFd(), GetAddress(), port, strerror(errno));
        }
        if (i == MAX_TRY_PORT - 1) {
            spdlog::error("已遍历所有端口，Socket 退出");
            return -1;
        }
    }

    if (ProcessData(GetSocketFd()) < 0) {
        return -1;
    }

    return 0;
}