#ifndef __PROC_MASG_H__
#define __PROC_MASG_H__

#include <string>
#include <string.h>
#include <unistd.h>

class ProcMsg {
public:
    ProcMsg();
    ~ProcMsg();


    // 获取数据
    char* getBuff();
    // 获取数据长度
    int32_t getLen();
    // 尾部递增
    void apend(void* buf, uint32_t len);
    // 重新分配
    bool reMalloc(uint32_t len);
    // 清空数据
    void clear(uint32_t len);
    // 获取数据
    void get(void** buf, uint32_t& size);

private:
    char* m_buff;
    uint32_t m_len;
    uint32_t m_size;
};


#endif // __PROC_MASG_H__