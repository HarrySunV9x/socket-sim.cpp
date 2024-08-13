//
// Created by WorkHarry on 2024/8/8.
//

#include <cstring>
#include "include/validate_arg.h"

ValidateArg::ArgErrors ValidateArg::CheckArgs(int argc, char *argv[]) {
    if (argc <= 1) {
        return kNeedArg;
    }

    if ((strcmp(argv[1], "-server") != 0) && (strcmp(argv[1], "-client") != 0)) {
        return kUnknownParameter;
    }

    return kOK;
}
