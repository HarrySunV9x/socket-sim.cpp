//
// Created by WorkHarry on 2024/8/8.
//

#ifndef SOCKET_SIM_CPP_VALIDATE_ARG_H
#define SOCKET_SIM_CPP_VALIDATE_ARG_H
#include <map>
#include <string>
#include "getopt.h"

class ValidateArg {
public:
    enum ArgErrors {
        kOK = 0,
        kNeedArg,
        kUnknownParameter,
        kInitFailed,
        kAddressError,
        kPortError,
        kMessageError,
    };

    // 实现单例：公有静态引用
    static ValidateArg &getInstance()
    {
        // 实现单例：初始化唯一静态变量
        static ValidateArg instance;
        return instance;
    }

    // 实现单例：禁止移动与拷贝
    ValidateArg(const ValidateArg&) = delete;
    ValidateArg& operator=(const ValidateArg&) = delete;

    ArgErrors CheckArgs(int argc, char *argv[]);
    void GetHelp();

    std::map<ArgErrors, std::string> ErrorsInfo;

private:
    struct option *long_opts;
    // 实现单例：私有构造函数与析构函数
    ValidateArg();
    ~ValidateArg()= default;

};

#endif //SOCKET_SIM_CPP_VALIDATE_ARG_H
