//
// Created by WorkHarry on 2024/8/15.
//

#ifndef SOCKET_SIM_CPP_SOCKET_SERVER_H
#define SOCKET_SIM_CPP_SOCKET_SERVER_H
#include "socket_base.h"

class SocketServer: public SocketBase {
public:
    SocketServer();
    ~SocketServer() override = default;

    int Init() override;
    int Init(std::string address) override;
    int Init(std::string address, std::string port) override;
    int Init(std::string address, std::string port, std::string message) override;
    int EstablishConnection() override;
    int ProcessData(int processFd) override;
    void Close() override;

    int listenPort = -1;
};

#endif //SOCKET_SIM_CPP_SOCKET_SERVER_H
