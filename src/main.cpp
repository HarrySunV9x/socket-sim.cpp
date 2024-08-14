#include "include/validate_arg.h"
#include "include/logger.h"

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
    return 0;
}
