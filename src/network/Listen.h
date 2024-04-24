#ifndef __LISTEN_H__
#define __LISTEN_H__

#include <string>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

// #include "Agent.h"
#include "AgentManager.h"
#include "EpollUnit.h"
#include "../common/CommonType.h"
#include "Tcp.h"

class Listen : public Tcp {
public:
    Listen();
    ~Listen();

public:
    // 初始化
    bool Init(std::string ip, int32_t port);
    // 获取fd
    int32_t GetFd();
    // 获取ip
    std::string GetIp();
    // 获取端口
    int32_t GetPort();
    // accept
    void CallBackAccept(EpollUnit* epoll_unit);
    // close
    void Close();

private:
    int32_t m_fd;
    std::string m_ip;
    int32_t m_port;
};

#endif // __LISTEN_H__