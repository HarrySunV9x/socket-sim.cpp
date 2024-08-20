#include <netinet/in.h>
#include <memory>

#include "gtest/gtest.h"

#include "../src/include/socket_client.h"
#include "../src/include/socket_server.h"
#include "../src/include/socket_base.h"

// 定义测试类
class SocketClientTest : public ::testing::Test {
protected:
    void SetUp() override {
        m_socket = std::make_unique<SocketClient>();
    }

    void TearDown() override {
    }

public:
    std::unique_ptr<SocketBase> m_socket;
};

// 定义测试类
class SocketServerTest : public ::testing::Test {
protected:
    void SetUp() override {
        m_socket = std::make_unique<SocketServer>();
    }

    void TearDown() override {
    }

public:
    std::unique_ptr<SocketBase> m_socket;
};

TEST_F(SocketClientTest, InitTest) {
    EXPECT_EQ(m_socket->Init(), 0);
}
TEST_F(SocketClientTest, InitSetAddressTest) {
    EXPECT_EQ(m_socket->Init("127.1.0.2"), 0);
}
TEST_F(SocketClientTest, InitSetPortTest) {
    EXPECT_EQ(m_socket->Init("127.0.0.1", "24154"), 0);
}
TEST_F(SocketClientTest, InitSetAddressAndPortTest) {
    EXPECT_EQ(m_socket->Init("127.1.0.2", "24154"), 0);
}

TEST_F(SocketServerTest, InitTest) {
    EXPECT_EQ(m_socket->Init(), 0);
}
TEST_F(SocketServerTest, InitSetAddressTest) {
    EXPECT_EQ(m_socket->Init("127.1.0.2"), 0);
}
TEST_F(SocketServerTest, InitSetPortTest) {
    EXPECT_EQ(m_socket->Init("127.0.0.1", "24154"), 0);
}
TEST_F(SocketServerTest, InitSetAddressAndPortTest) {
    EXPECT_EQ(m_socket->Init("127.1.0.2", "24154"), 0);
}