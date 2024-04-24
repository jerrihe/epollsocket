#ifndef __CONNECT_H__
#define __CONNECT_H__

#include <string>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

#include "ProcMsg.h"
#include "Tcp.h"

class Connect : public Tcp{
public:
    Connect();
    ~Connect();
public:
    bool Init(std::string ip, int32_t port);
    int32_t Recv();
    int32_t Send(const char* data, int32_t len);
    void Close();

private:
    int32_t m_fd;
    std::string m_ip;
    int32_t m_port;

    char* m_buff_read;

    ProcMsg* m_proc_msg;
};

#endif