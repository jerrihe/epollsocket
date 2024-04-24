#include "Listen.h"

Listen::Listen() {
}

Listen::~Listen() {
}

bool Listen::Init(std::string ip, int32_t port) {
    m_ip = ip;
    m_port = port;
    // 创建socket并设置为非阻塞
    m_fd = socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK, 0);
    if (m_fd == -1) {
        perror("socket");
        return false;
    }
    struct sockaddr_in listen_attr;
    memset(&listen_attr, 0, sizeof(listen_attr));

    listen_attr.sin_family = AF_INET;
    listen_attr.sin_port = htons(m_port);
    listen_attr.sin_addr.s_addr = inet_addr(m_ip.c_str());
    // 绑定
    int ret = bind(m_fd, (struct sockaddr*)&listen_attr, sizeof(listen_attr));
    if (ret == -1) {
        perror("bind error");
        return false;
    }
    // 设置监听
    ret = listen(m_fd, 10);
    if (ret == -1) {
        perror("listen error");
        return false;
    }
    set_event_type(EPOLL_EVENT_TYPE_LISTEN);
    printf("listen on %s:%d\n", m_ip.c_str(), m_port);
    return true;
}

int32_t Listen::GetFd() {
    return m_fd;
}

std::string Listen::GetIp() {
    return m_ip;
}

int32_t Listen::GetPort() {
    return m_port;
}

void Listen::CallBackAccept(EpollUnit* epoll_unit) {
    do {
        // 新增一个客户端新链接
        struct sockaddr_in addr;
        socklen_t socklen = sizeof(addr);
        int accept_sockfd = accept4(m_fd, (struct sockaddr *)&addr, &socklen, SOCK_NONBLOCK);
        if(accept_sockfd < 0)
        {
            return;
        }

        auto agent = new Agent();
        if (agent == nullptr) {
            printf("new agent failed %s \n", inet_ntoa(addr.sin_addr));
            delete agent;
            continue;
        }
        agent->init(accept_sockfd, inet_ntoa(addr.sin_addr));

        epoll_unit->AddEvent(accept_sockfd, EPOLL_EVENT_TYPE_CLIENT, agent);
        // epoll_unit->procEvent(accept_sockfd, EPOLL_CTL_ADD, &ev);

        GetAgentManager()->AddAgent(agent);
    } while (true);
}


void Listen::Close() {
    close(m_fd);
}