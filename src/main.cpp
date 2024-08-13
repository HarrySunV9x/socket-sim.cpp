#include "spdlog/spdlog.h"
#include "include/validate_arg.h"

int main(int argc, char *argv[]) {
    spdlog::info("Welcome to spdlog!");

    ValidateArg &validateArg = ValidateArg::getInstance();

    ValidateArg::ArgErrors res = validateArg.CheckArgs(argc, argv);
    if (res == ValidateArg::kOK) {
        spdlog::info("{0}", validateArg.ErrorsInfo[res]);
    } else {
        spdlog::error("{0}", validateArg.ErrorsInfo[res]);
    }
    return 0;
}
