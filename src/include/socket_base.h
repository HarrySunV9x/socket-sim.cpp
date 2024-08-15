//
// Created by WorkHarry on 2024/8/14.
//

#ifndef SOCKET_SIM_CPP_SOCKET_BASE_H
#define SOCKET_SIM_CPP_SOCKET_BASE_H

#define DEFAULT_ADDRESS     "127.0.0.1"
#define DEFAULT_PORT        "21120"

#include <string>

class SocketBase {
public:
    enum SocketType {
        kNone = 0,
        kServer,
        kClient,
    };

    // - 当 const 出现在成员函数的声明或定义的结尾时，表示该函数是一个常量成员函数。
    //   常量成员函数不能修改类的任何成员变量
    // - [[nodiscard]] 是 C++17 引入的一种属性，表示调用某个函数的返回值不应被忽略。
    //   强制用户在调用这个函数时处理或使用它的返回值
    [[nodiscard]] int GetSocketFd() const;
    void SetSocketFd(int socketFd);
    [[nodiscard]] SocketType GetSocketType() const;
    void SetSocketType(SocketType socketType);
    [[nodiscard]] const std::string &GetAddress() const;
    void SetAddress(const std::string &address);
    [[nodiscard]] const std::string &GetPort() const;
    void SetPort(const std::string &port);


    /**
     * @brief 初始化socket，为收发做准备
     *
     * 例如：
     * 对Server来说，要Create、设置地址、Bind
     * 对Client来说，要Create、设置地址
     * 等行为
     *
     * @param address 如果修改地址的话...
     * @param port    如果修改端口的话...
     *
     * @return int , 0 代表成功， -1 代表失败
     */
    virtual int Init() = 0;
    virtual int Init(std::string address) = 0;
    virtual int Init(std::string address, std::string port) = 0;

    /**
     * @brief 用于建立通信
     *
     * 例如：
     * 对Server来说，要Listen、Accept
     * 对Client来说，要Connect
     *
     * @return int , 0 代表成功， -1 代表失败
     */
    virtual int EstablishConnection() = 0;

    /**
     * @brief 数据处理
     *
     * 例如：
     * 对Server来说，要Select、Recv
     * 对Client来说，要Send
     * 然后各自对数据进行相应的处理
     *
     * @param 进行数据处理的Fd
     * @return int , 0 代表成功， -1 代表失败
     */
    virtual int ProcessData(int processFd) = 0;

    /**
     * @brief 关闭socket进行的操作
     *
     * 关闭Socket进行的操作
     * 可以用来实现重连等自定义行为
     */
    virtual void Close() = 0;

    SocketBase();
    ~SocketBase() = default;

private:
    int s_fd = -1;
    SocketType s_type = kNone;
    std::string s_address = DEFAULT_ADDRESS;
    std::string s_port = DEFAULT_PORT;
};

#endif //SOCKET_SIM_CPP_SOCKET_BASE_H
