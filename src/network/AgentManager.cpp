#include "AgentManager.h"



AgentManager* AgentManager::m_instance = nullptr;
std::mutex AgentManager::m_mutex;

// AgentManager::AgentManager() {

// }

// AgentManager::~AgentManager() {

// }

void AgentManager::deleteInstance() {
    if (m_instance != nullptr) {
        delete m_instance;
        m_instance = nullptr;
    }
}

void AgentManager::init() {

}

void AgentManager::uninit() {
    for (auto it = m_agent_list.begin(); it != m_agent_list.end(); ++it) {
        if (it->second != nullptr) {
            it->second->Close();
        }
        DELETEPTR(it->second);
    }
    m_agent_list.clear();
}

int32_t AgentManager::AddAgent(Agent* agent) {
    if (agent == nullptr) {
        printf("agent is nullptr\n");
        return -1;
    }
    auto agent_fd = agent->GetFd();
    if (m_agent_list.find(agent_fd) != m_agent_list.end()) {
        printf("agent has exist\n");
        return -1;
    }
    printf("accept fd:%d \n", agent_fd);
    m_agent_list.insert(std::make_pair(agent_fd, agent));
    return agent_fd;
}

void AgentManager::DelAgent(int32_t agent_id) {
    auto it = m_agent_list.find(agent_id);
    if (it == m_agent_list.end()) {
        printf("agent not exist\n");
        return;
    }

    // 关闭文件描述符
    if (it->second != nullptr) {
        it->second->Close();
    }

    DELETEPTR(it->second);
    m_agent_list.erase(agent_id);
}

Agent* AgentManager::GetAgent(int32_t agent_id) {
    auto it = m_agent_list.find(agent_id);
    if (it == m_agent_list.end()) {
        printf("agent not exist\n");
        return nullptr;
    }
    return it->second;
}
