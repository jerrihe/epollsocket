#include "EpollUnit.h"

EpollUnit::EpollUnit()
: m_epoll_fd(0)
, m_epoll_size(0){

}

EpollUnit::~EpollUnit() {

}

int32_t EpollUnit::Create(int32_t size) {
    m_epoll_fd = epoll_create(size);
    if (m_epoll_fd == -1) {
        printf("epoll create error \n");
    }
    return m_epoll_fd;
}

bool EpollUnit::AddEvent(int32_t fd, int32_t event_type, void* ptr) {
    Epoll_Event_info info;
    info.fd = fd;
    info.ptr = ptr;
    info.event_type = event_type;
    m_epoll_event_map[fd] = info;

    epoll_event ev;
    ev.data.fd = fd;
    ev.events = EPOLLIN | EPOLLOUT | EPOLLET;
    if (!procEvent(fd, EPOLL_CTL_ADD, &ev)) {
        return false;
    }

    return true;
}

bool EpollUnit::DelEvent(int32_t fd) {
    auto iter = m_epoll_event_map.find(fd);
    if (iter == m_epoll_event_map.end()) {
        printf("epoll event not find fd:%d \n", fd);
        return false;
    }

    m_epoll_event_map.erase(iter);
    procEvent(fd, EPOLL_CTL_DEL, nullptr);
    return true;
}

int32_t EpollUnit::GetEventType(int32_t fd) {
    auto iter = m_epoll_event_map.find(fd);
    if (iter == m_epoll_event_map.end()) {
        printf("epoll event not find fd:%d \n", fd);
        return -1;
    }
    return iter->second.event_type;
}

Epoll_Event_info* EpollUnit::GetEventInfo(int32_t fd) {
    auto iter = m_epoll_event_map.find(fd);
    if (iter == m_epoll_event_map.end()) {
        printf("epoll event not find fd:%d \n", fd);
        return nullptr;
    }
    return &iter->second;
}

bool EpollUnit::procEvent(int32_t fd, int32_t op, epoll_event* ev) {
    // EPOLL_CTL_ADD ：注册新的fd到epfd中；
    // EPOLL_CTL_MOD ：修改已经注册的fd的监听事件；
    // EPOLL_CTL_DEL ：从epfd中删除一个fd；
    // m_epoll_fd epoll_create返回的fd
    // fd 要监听的fd
    // ev 要监听的事件

    if (op != EPOLL_CTL_DEL) {
        if (ev == nullptr) {
            printf("epoll event is null fd:%d op:%d\n", fd, op);
            return false;
        }
    }

    if (epoll_ctl(m_epoll_fd, op, fd, ev) == -1) {
        printf("epoll add error \n");
        return false;
    }
    return true;
}

int32_t EpollUnit::Wait(struct epoll_event* ev, int32_t maxevents, int32_t timeout) {
    return epoll_wait(m_epoll_fd, ev, maxevents, timeout);

}

bool EpollUnit::Close() {
    close(m_epoll_fd);
    return true;
}

