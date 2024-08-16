#include "include/validate_arg.h"
#include "include/logger.h"
#include "include/socket_handler.h"

int main(int argc, char *argv[]) {
    fLogger->info("程序开始");
    ValidateArg &validateArg = ValidateArg::getInstance();
    ValidateArg::ArgErrors res = validateArg.CheckArgs(argc, argv);

    if (res != ValidateArg::kOK) {
        std::string errorStr = validateArg.ErrorsInfo[res];
        fLogger->error(errorStr);
        return 1;
    }

    fLogger->info("参数校验成功");

    if (SocketHandler::getInstance().m_socket == nullptr) {
        return 1;
    }

    if (SocketHandler::getInstance().m_socket->EstablishConnection() != 0) {
        SocketHandler::getInstance().m_socket->Close();
        return 1;
    }

    return 0;
}
