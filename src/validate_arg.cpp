//
// Created by WorkHarry on 2024/8/8.
//

#include <iostream>
#include "include/validate_arg.h"
#include "include/logger.h"
#include "include/socket_server.h"

ValidateArg::ValidateArg() {
    long_opts = new struct option[]{
            {"help", no_argument, nullptr, 'h'},
            {"version", no_argument, nullptr, 'v'},
            {"server", no_argument, nullptr, 's'},
            {"client", no_argument, nullptr, 'c'},
            {"type", no_argument, nullptr, 't'},
            {nullptr, no_argument, nullptr, 0}
    };

    ErrorsInfo = {
            {kOK, "参数校验成功"},
            {kNeedArg, "程序需要传入参数"},
            {kUnknownParameter, "未知参数"}
    };
}

ValidateArg::ArgErrors ValidateArg::CheckArgs(int argc, char *argv[]) {
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
            break;
        case 'c':
            break;
        case 't':
            break;
        default:
            return kUnknownParameter;
    }
    fLogger->info("参数校验完成");
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
