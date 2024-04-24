#include "Agent.h"

#define RECV_BUFFER_SIZE 4096

Agent::Agent()
: m_fd(-1)
, m_ip("")
, m_port(0)
, m_buff_read(nullptr)
, m_proc_msg(nullptr){
    m_buff_read =  (char *)malloc(RECV_BUFFER_SIZE);
    m_proc_msg = new ProcMsg();
}

Agent::~Agent() {
    if (m_buff_read != nullptr) {
        free(m_buff_read);
        m_buff_read = nullptr;
    }

    if (m_proc_msg) {
        delete m_proc_msg;
        m_proc_msg = nullptr;
    }
}

void Agent::init(int32_t fd, std::string ip) {
    m_fd = fd;
    m_ip = ip;
}

int32_t Agent::Recv() {
    if (m_fd > 0) {
        do {
            printf("recv data\n");
            auto ret = recv(m_fd, m_buff_read, RECV_BUFFER_SIZE, 0);
            printf("recv data :  %s ret:%u \n", m_buff_read, (uint32_t)ret);
            if ( ret == 0) {
                // 对方关闭
                printf("recv close");
                return 0;
            }
            if (ret > 0) {
                m_proc_msg->apend(m_buff_read, ret);
                printf("recv data end once\n");
            }
            else {
                break;
            }
        }
        while(true);
    }
    return -1;
}

ssize_t Agent::Send(char* buf,size_t len) {
    printf("send data:%s %d\n", buf, (int32_t)len);
    ssize_t ret = send(m_fd , buf, len, 0);
    if (ret < 0) {
        printf("send error\n");
        return -1;
    }
    return ret;
}

int32_t Agent::GetFd() {
    return m_fd;
}

void Agent::Close() {
    if (m_fd <= 0) {
        return;
    }
    close(m_fd);
}

ProcMsg* Agent::GetProcMsg() {
    return m_proc_msg;
}
