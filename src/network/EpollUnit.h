#ifndef __EPOLL_UNIT_H__
#define __EPOLL_UNIT_H__

#include <sys/epoll.h>
#include <sys/types.h>
#include <map>

#include "../common/CommonType.h"

struct Epoll_Event_info {
    int32_t fd;
    void* ptr;
    int32_t event_type;
};

class EpollUnit {
public:
    EpollUnit();
    ~EpollUnit();

public:
    // create epoll  size；X版本后无实际用处
    int32_t Create(int32_t size);
    // add_epool_event
    bool AddEvent(int32_t fd, int32_t event_type, void* ptr);
    // del_epool_event
    bool DelEvent(int32_t fd);
    // get event_type by fd
    int32_t GetEventType(int32_t fd);
    // get epoll_event by fd
    Epoll_Event_info* GetEventInfo(int32_t fd);
    // proc fd to epoll
    bool procEvent(int32_t fd, int32_t op, struct epoll_event* ev);
    // wait event
    int32_t Wait(struct epoll_event* ev, int32_t maxevents, int32_t timeout);
    bool Close();

private:
    int32_t m_epoll_fd;
    int32_t m_epoll_size;
    std::map<int32_t, Epoll_Event_info> m_epoll_event_map;
};

#endif // __EPOLL_UNIT_H__