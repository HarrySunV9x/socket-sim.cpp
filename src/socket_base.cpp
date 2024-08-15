//
// Created by WorkHarry on 2024/8/14.
//

#include "include/socket_base.h"

SocketBase::SocketBase(): s_type(kNone) {
}

int SocketBase::GetSocketFd() const {
    return s_fd;
}
void SocketBase::SetSocketFd(int socketFd) {
    SocketBase::s_fd = socketFd;
}

SocketBase::SocketType SocketBase::GetSocketType() const {
    return s_type;
}
void SocketBase::SetSocketType(SocketType socketType) {
    SocketBase::s_type = socketType;
}

const std::string &SocketBase::GetAddress() const {
    return s_address;
}
void SocketBase::SetAddress(const std::string &address) {
    SocketBase::s_address = address;
}

const std::string &SocketBase::GetPort() const {
    return s_port;
}
void SocketBase::SetPort(const std::string &port) {
    SocketBase::s_port = port;
}


