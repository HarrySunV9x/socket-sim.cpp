#include "spdlog/spdlog.h"
#include "include/validate_arg.h"

enum ArgErrors {
    kOK = 0,
    kErrorNeedArg,
};

int ValidateArg(int argc, char *argv[]) {
    if (argc == 1) {
        spdlog::error("socket_sim need args.");
        return 1;
    }

    return 0;
}

int main(int argc, char *argv[]) {
    spdlog::info("Welcome to spdlog!");

    ValidateArg(argc, argv);
    return 0;
}
