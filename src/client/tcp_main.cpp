#include <iostream>
#include "../network/Connect.h"

using namespace std;

int main() {
    auto conect = new Connect();
    conect->Init("127.0.0.1", 8888);

    while (true) {
        // 发送数据
        char send_buf[1024] = "hello server";
        auto ret = conect->Send(send_buf, sizeof(send_buf));
        if (ret < 0) {
            printf("send error\n");
            break;
        }


        printf("send_buf %s  %d\n", send_buf, ret);

        if (conect->Recv() == 0) {
            printf("server close\n");
            break;
        }
    }
    conect->Close();
    delete conect;
    return 0;
}
