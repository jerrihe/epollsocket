#include "Connect.h"

Connect::Connect()
: m_fd(-1)
, m_ip("")
, m_port(0)
, m_buff_read(nullptr)
, m_proc_msg(nullptr){
    
}

Connect::~Connect() {
    
}

bool Connect::Init(std::string ip, int32_t port) {
    m_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (m_fd < 0) {
        printf("socket error\n");
        return false;
    }

    m_port = port;
    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = inet_addr(ip.c_str());

    if (connect(m_fd, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
        printf("connect error\n");
        return false;
    }
    set_event_type(EPOLL_EVENT_TYPE_CLIENT);
    printf("connect to %s:%d\n", ip.c_str(), port);
    return true;
}

int32_t Connect::Recv() {
    char buf[1024] = {0};
    auto ret = read(m_fd, buf, sizeof(buf));
    if (ret < 0) {
        printf("read error\n");
        return -1;
    }
    printf("recv data:%s\n", buf);
    return ret;
}

int32_t Connect::Send(const char* data, int32_t len) {
    auto ret = write(m_fd, data, len);
    if (ret < 0) {
        printf("write error\n");
        return -1;
    }
    return ret;
}

void Connect::Close() {
    close(m_fd);
}