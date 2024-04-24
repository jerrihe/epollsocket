#ifndef __Agent_H__
#define __Agent_H__

#include <string>
#include <sys/socket.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

#include "ProcMsg.h"

class Agent {
public:
    Agent();
    ~Agent();

    void init(int32_t fd, std::string ip);
    // recv 
    int32_t Recv();
    // send
    ssize_t Send(char* buf,size_t len);
    // get fd
    int32_t GetFd();
    // close
    void Close();
    // get proc_msg
    ProcMsg* GetProcMsg();
private:
    int32_t m_fd;
    std::string m_ip;
    int32_t m_port;
    char* m_buff_read;

    ProcMsg* m_proc_msg;
};


#endif // __Agent_H__