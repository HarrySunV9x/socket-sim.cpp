//
// Created by WorkHarry on 2024/8/16.
//

#ifndef SOCKET_SIM_CPP_SOCKET_CLIENT_H
#define SOCKET_SIM_CPP_SOCKET_CLIENT_H
#include "socket_base.h"

class SocketClient: public SocketBase{
public:
    SocketClient();
    ~SocketClient() override = default;

    int Init() override;
    int Init(std::string address) override;
    int Init(std::string address, std::string port) override;
    int Init(std::string address, std::string port, std::string message) override;
    int EstablishConnection() override;
    int ProcessData(int processFd) override;
    void Close() override;

private:
    std::string m_message;
};


#endif //SOCKET_SIM_CPP_SOCKET_CLIENT_H
