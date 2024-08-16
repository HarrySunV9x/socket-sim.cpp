//
// Created by WorkHarry on 2024/8/8.
//

#include <iostream>
#include "include/validate_arg.h"
#include "include/logger.h"
#include "include/socket_server.h"
#include "include/socket_handler.h"
#include "include/socket_client.h"

ValidateArg::ValidateArg() {
    long_opts = new struct option[]{
            {"help", no_argument, nullptr, 'h'},
            {"version", no_argument, nullptr, 'v'},
            {"server", no_argument, nullptr, 's'},
            {"client", no_argument, nullptr, 'c'},
            {"type", no_argument, nullptr, 't'},
            {"address", required_argument, nullptr, 'a'},
            {"port", required_argument, nullptr, 'p'},
            {"message", required_argument, nullptr, 'm'},
            {nullptr, no_argument, nullptr, 0}
    };

    ErrorsInfo = {
            {kOK, "参数校验成功"},
            {kNeedArg, "程序需要传入参数"},
            {kUnknownParameter, "未知参数"},
            {kInitFailed, "初始化Socket失败"},
            {kAddressError, "参数a使用错误"},
            {kPortError, "参数p使用错误"},
            {kMessageError, "只有Client可输入message"}
    };
}

ValidateArg::ArgErrors ValidateArg::CheckArgs(int argc, char *argv[]) {
    std::string address;
    std::string port;
    std::string message;

    if (argc <= 1) {
        return kNeedArg;
    }

    const auto opt = getopt_long(argc, argv, "hvsct:", long_opts, nullptr);

    switch (opt) {
        case 'h':
            GetHelp();
            break;
        case 'v':
            std::cout << APP_VERSION << std::endl;
            break;
        case 's':
            SocketHandler::getInstance().m_socket = std::make_unique<SocketServer>();
            SocketHandler::getInstance().m_socket->SetSocketType(SocketBase::kServer);
            break;
        case 'c':
            SocketHandler::getInstance().m_socket = std::make_unique<SocketClient>();
            SocketHandler::getInstance().m_socket->SetSocketType(SocketBase::kClient);
            break;
        case 'a':
            if (SocketHandler::getInstance().m_socket->GetSocketType() == SocketBase::kNone) {
                return kAddressError;
            }
            address = optarg;
            break;
        case 'p':
            if (SocketHandler::getInstance().m_socket->GetSocketType() == SocketBase::kNone) {
                return kPortError;
            }
            port = optarg;
            break;
        case 'm':
            if (SocketHandler::getInstance().m_socket->GetSocketType() != SocketBase::kClient) {
                return kMessageError;
            }
            message = optarg;
            break;
        case 't':
            break;
        default:
            return kUnknownParameter;
    }
    fLogger->info("参数校验完成");

    if (!address.empty() && !port.empty() && !message.empty()) {
        SocketHandler::getInstance().m_socket->Init(address, port, message);
    } else if (!address.empty() && !port.empty()) {
        SocketHandler::getInstance().m_socket->Init(address, port);
    } else if (!address.empty()) {
        SocketHandler::getInstance().m_socket->Init(address);
    } else if (!port.empty()) {
        SocketHandler::getInstance().m_socket->Init(DEFAULT_ADDRESS, port);
    } else {
        SocketHandler::getInstance().m_socket->Init();
    }

    return kOK;
}

void ValidateArg::GetHelp() {
    std::cout << "Usage: socket [options]\n"
              << "Options: \n"
              << "  -h, --help           查看帮助\n"
              << "  -v, --version        查看版本\n"
              << "  -s, --server         作为服务端启动\n"
              << "  -c, --client         作为客户端启动\n"
              << "  -t, --type           传输类型"
              << std::endl;
}
