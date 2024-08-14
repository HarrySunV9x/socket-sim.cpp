//
// Created by WorkHarry on 2024/8/13.
//

#include "gtest/gtest.h"
#include "../src/include/validate_arg.h"

class ValidateArgTest : public ::testing::Test {
protected:
    void SetUp() override {
        // 在每个测试用例之前重置 optind
        // 否则getopt_long读取参数位置时不会重置
        optind = 1;
    }

    void TearDown() override {
        // 测试结束时候需要清除的状态
    }

    ValidateArg &validateArg = ValidateArg::getInstance();  // 全局获取参检单例
};

// 程序无参数测试
TEST_F(ValidateArgTest, ValidateArgNoParam) {
    char* argv1[] = {APP_NAME};
    EXPECT_EQ(ValidateArg::kNeedArg, validateArg.CheckArgs(1, argv1));
}

TEST_F(ValidateArgTest, ValidateArgServer) {
    char* argvServer[] = {APP_NAME, "--server"};
    EXPECT_EQ(ValidateArg::kOK, validateArg.CheckArgs(2, argvServer));
}

TEST_F(ValidateArgTest, ValidateArgClient) {
    char* argvClient[] = {APP_NAME, "--client"};
    EXPECT_EQ(ValidateArg::kOK, validateArg.CheckArgs(2, argvClient));
}