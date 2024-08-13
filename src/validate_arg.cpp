//
// Created by WorkHarry on 2024/8/8.
//

#include "include/validate_arg.h"

ValidateArg::ArgErrors ValidateArg::CheckArgs(int argc, char *argv[]) {
    if (argc == 1) {
        return kErrorNeedArg;
    }

    return kOK;
}
