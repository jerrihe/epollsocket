#ifndef __COMMON_TYPE_H__Class
#define __COMMON_TYPE_H__Class


#include <string>
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>

#define MAX_EPOOLL_EVENTS 10

#define DELETEPTR(ptr) \
    if (ptr) {\
        delete ptr;\
        ptr = nullptr;\
    }\

enum EPOLL_EVENT_TYPE {
    EPOLL_EVENT_TYPE_NONE = 0,
    EPOLL_EVENT_TYPE_LISTEN = 1,
    EPOLL_EVENT_TYPE_CLIENT = 2,
};

#endif // __COMMON_TYPE_H__Class