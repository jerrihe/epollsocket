#ifndef __TCP_H_
#define __TCP_H_

#include <string>
#include "../common/CommonType.h"

class Tcp {
public:
    Tcp();
    ~Tcp();

    void set_event_type(int32_t event_type);
    int32_t get_event_type();
private:
    int32_t m_event_type;
};

#endif // __TCP_H_