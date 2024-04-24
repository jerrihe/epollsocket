    #include <iostream>
    #include <string>

    #include "../network/EpollUnit.h"
    #include "../network/Listen.h"

    using namespace std;

    void test_epoll(std::string ip, int32_t port) {
        auto listen = new Listen();
        listen->Init(ip, port);

        EpollUnit epoll;
        auto epoll_id = epoll.Create(1);

        printf("listen fd:%d \n", listen->GetFd());
        if (!epoll.AddEvent(listen->GetFd(), EPOLL_EVENT_TYPE_LISTEN, listen) ) {
            printf("epoll add event error \n");
            listen->Close();
            epoll.Close();
            delete listen;
            return;
        } 

        struct epoll_event events[MAX_EPOOLL_EVENTS];
        do {
            printf("wait epoll \n");
            int ret = epoll.Wait(events, MAX_EPOOLL_EVENTS, -1);
            if (ret < 0) {
                printf("epoll wait error \n");
                break;
            }
            printf("epoll event num:%d \n", ret);
            for (int i = 0; i < ret; i++) {
                auto event = events[i];

                auto epoll_event_info = epoll.GetEventInfo(event.data.fd);
                if (epoll_event_info == nullptr) {
                    printf("epoll event info is null \n");
                    continue;
                }
                printf("epoll event type:%d \n", epoll_event_info->event_type);
                switch (epoll_event_info->event_type)
                {
                    // 监听事件
                    case EPOLL_EVENT_TYPE_LISTEN: {
                        printf("listen event \n");
                        auto listen_evnet = (Listen*)epoll_event_info->ptr;

                        if(listen_evnet == nullptr) {
                            printf("listen event is null \n");
                            // epoll.procEvent(listen->GetFd(), EPOLL_CTL_DEL, nullptr);
                            // close(listen->GetFd());
                            break;
                        }
                        if (events[i].events & EPOLLIN) {
                            // 接收所有客户端链接
                            listen_evnet->CallBackAccept(&epoll);
                        }
                        break;
                    }
                    // 客户端事件
                    case EPOLL_EVENT_TYPE_CLIENT: {
                        printf("client event \n");
                        auto agent = (Agent*)epoll_event_info->ptr;
                        if (agent == nullptr) {
                            break;
                        }
                        // 是读事件
                        if (events[i].events & EPOLLIN) {
                            // 可读
                            if (agent->Recv() == 0) {
                                printf("recv error \n");
                                // 已经断开链接
                                GetAgentManager()->DelAgent(agent->GetFd());
                                epoll.procEvent(agent->GetFd(), EPOLL_CTL_DEL, nullptr);
                                break;
                            } 

                            auto proc_msg = agent->GetProcMsg();
                            if (proc_msg == nullptr) {
                                printf("proc msg is null \n");
                                break;
                            }

                            void* msg = nullptr;
                            uint32_t len = 0;
                            proc_msg->get(&msg, len);

                            printf("recv msg:%s \n", (char*)msg);

                            // 回复消息
                            agent->Send((char*)msg, len);

                            // 清空消息
                            proc_msg->clear(len);
                        }
                        else if (events[i].events & EPOLLOUT) {
                            // 可写
                            char send_buf[1024] = "hello client";
                        }

                        break;
                    }
                    default:
                        break;
                }
            }
        } while (true);
        epoll.Close();
        listen->Close();
        delete listen;
        GetAgentManager()->uninit();
        return;
    }

    int main() {
        test_epoll("127.0.0.1", 8888);
        return 0;
    }