//
// Created by WorkHarry on 2024/8/13.
//

#include "gtest/gtest.h"
#include "../src/include/validate_arg.h"

TEST(ValidateArgTest, ValidateArgNoParam) {
    ValidateArg &validateArg = ValidateArg::getInstance();
    char* argv1[] = {"socket_sim_cpp"};

    EXPECT_EQ(ValidateArg::kNeedArg, validateArg.CheckArgs(1, argv1));
}

TEST(ValidateArgTest, ValidateArgOneParam) {
    ValidateArg &validateArg = ValidateArg::getInstance();
    char* argvServer[] = {"socket_sim_cpp", "-server"};
    char* argvClient[] = {"socket_sim_cpp", "-client"};
    char* argvOther[] = {"socket_sim_cpp", "other"};

    EXPECT_EQ(ValidateArg::kOK, validateArg.CheckArgs(2, argvServer));
    EXPECT_EQ(ValidateArg::kOK, validateArg.CheckArgs(2, argvClient));
    EXPECT_EQ(ValidateArg::kUnknownParameter, validateArg.CheckArgs(2, argvOther));
}