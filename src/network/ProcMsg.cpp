// created by jerri
#include "ProcMsg.h"

#define MINSIZE 64
// 收缩长度，缓存区大于32k时，尽量缩小，缩成当前数据的2倍大
#define SHRINK_BUFFER_SIZE 32768

ProcMsg::ProcMsg()
: m_buff(nullptr)
, m_len(0)
, m_size(MINSIZE) {
    m_buff = (char*)malloc(MINSIZE);
}

ProcMsg::~ProcMsg() {
    if (m_buff != nullptr) {
        free(m_buff);
        m_buff = nullptr;
    }
}

char* ProcMsg::getBuff() {
    return m_buff;
}

int32_t ProcMsg::getLen() {
    return m_len;
}

void ProcMsg::apend(void* buf, uint32_t len) {
    printf("apend %u\n", len);
    // 仍需求的大小
    uint32_t need_size = m_len + len;
    // 如果不够用，重新分配
    if (!reMalloc(need_size)) {
        printf("reMalloc failed\n");
        return;
    }
    // 拷贝数据
    memcpy(m_buff+m_len, buf, len);
    m_len += len;
    printf("apend end %s\n", m_buff);
}

bool ProcMsg::reMalloc(uint32_t size) {
    printf("reMalloc %d\n %d", size, m_size);
    // 如果长度大于当前长度，重新分配
    if (size > m_size) {
        do {
            m_size *= 2;
            printf("m_size %d size:%d\n", m_size, size);
        }
        while(size > m_size);
    }
    // 如果长度小于当前长度，且大于32k，缩小
    else if (m_size > SHRINK_BUFFER_SIZE && size*2 < m_size) {
        // shrink m_size in case larger than SHRINK_BUFFER_SIZE
        m_size /= 2;
    }
    // 如果长度小于当前长度，且小于32k，不做处理
    else {
        return true;
    }

    // 重新分配
    char *new_ptr = (char *)realloc(m_buff, m_size);
    if (nullptr != new_ptr) {
        m_buff = new_ptr;
        return true;
    }
    return false;
}

void ProcMsg::clear(uint32_t len) {
    if (len > 0) {
        m_len -= len;
        memmove(m_buff, m_buff+len, m_len);
    }
}

void ProcMsg::get(void** buf, uint32_t& len) {
    *buf = m_buff;
    len = m_len;
}