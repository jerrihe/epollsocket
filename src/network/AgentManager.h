#ifndef __AGENT_MANAGER_H__
#define __AGENT_MANAGER_H__

#include <map>
#include <string>

#include <mutex>
#include "Agent.h"

#include "../common/CommonType.h"
// #include "CommonType.h"


class AgentManager {
public:
    static AgentManager* GetInstance() {
        // 先判断是否为空，如果为空则进入，不为空说明已经存在实例，直接返回
		if (m_instance == nullptr) {
            //进入后加锁
			m_mutex.lock();
            //再判断一次，确保不会因为加锁期间多个线程同时进入
			if (m_instance == nullptr) {
				m_instance = new AgentManager();
			}
			m_mutex.unlock();//解锁
		}
        // if (m_instance == nullptr) {
        //     m_instance = new AgentManager();
        // }
		return m_instance;
	}
    static void deleteInstance() ;
private:
    AgentManager() {}
    ~AgentManager() {
        deleteInstance();
    }
public:
    void init();
    void uninit();
    int32_t AddAgent(Agent* agent);
    void DelAgent(int32_t agent_id);
    Agent* GetAgent(int32_t agent_id);
private:
    std::map<int32_t, Agent*> m_agent_list;
    static AgentManager* m_instance;
    static std::mutex m_mutex;
};

#define GetAgentManager() AgentManager::GetInstance()

#endif // __AGENT_MANAGER_H__