#ifndef __TIMEHELPER_H_
#define __TIMEHELPER_H_

#include <stdint.h>

class TimeHelper {
public:
    TimeHelper();
    ~TimeHelper();
    
private:
    uint64_t m_cur_time;
};

#endif // __TIMEHELPER_H_