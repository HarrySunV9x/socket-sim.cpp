//
// Created by WorkHarry on 2024/8/16.
//

#ifndef SOCKET_SIM_CPP_SOCKET_HANDLER_H
#define SOCKET_SIM_CPP_SOCKET_HANDLER_H

#include <memory>
#include "socket_base.h"

class SocketHandler {
public:
    static SocketHandler &getInstance(){
        static SocketHandler instance;
        return instance;
    }

    SocketHandler(const SocketHandler&) = delete;
    SocketHandler &operator= (const SocketHandler&) = delete;

    std::unique_ptr<SocketBase> m_socket;

private:
    SocketHandler(){};
    ~SocketHandler() = default;
};


#endif //SOCKET_SIM_CPP_SOCKET_HANDLER_H
