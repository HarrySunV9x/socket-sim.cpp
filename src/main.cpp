#include "spdlog/spdlog.h"
#include "include/validate_arg.h"

int main(int argc, char *argv[]) {
    spdlog::info("程序开始");

    spdlog::debug("获取参数校验单例");
    ValidateArg &validateArg = ValidateArg::getInstance();

    spdlog::debug("进行参数校验");
    ValidateArg::ArgErrors res = validateArg.CheckArgs(argc, argv);
    if (res != ValidateArg::kOK) {
        spdlog::error("{0}", validateArg.ErrorsInfo[res]);
        return 1;
    }

    spdlog::info("参数校验成功");
    return 0;
}
