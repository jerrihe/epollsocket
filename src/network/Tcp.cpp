#include "Tcp.h"

Tcp::Tcp() {
    m_event_type = EPOLL_EVENT_TYPE_NONE;
}

Tcp::~Tcp() {
}

void Tcp::set_event_type(int32_t event_type) {
    m_event_type = event_type;
}

int32_t Tcp::get_event_type() {
    return m_event_type;
}