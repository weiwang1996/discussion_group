#include "udpServer.h"
#include <unistd.h>
using namespace std;

static void usage(std::string proc)
{
    cout<<"Usage:"<<proc<<"[local_ip] [local_port]"<<endl;
}
static void *runRecv(void *arg)//创建 接受数据的线程函数
{
    udpServer *svrp = (udpServer*)arg;
    std::string msg;
    for(;;)
    {
    svrp->recvData(msg);//死循环接受数据
    cout<<"client echo:"<<msg<<endl;
    }
}

static void *runSend(void *arg)//创建 发送数据的线程函数
{
    udpServer *svrp = (udpServer*)arg;
    for(;;)
    {
        svrp->brocast();//广播数据
    }
}
//./client 125.0.0.1 8888

int main(int argc,char *argv[])
{
    if(argc!=3)
    {
        usage(argv[0]);
        exit(1);
    }
    int port = atoi(argv[2]);
    udpServer svr(argv[1],port);
    svr.initServer();//初始化，绑定服务器的ip和port
    daemon(0,0);
    pthread_t recv_thread,send_thread;
    pthread_create(&recv_thread,NULL,runRecv,(void*)&svr);//创建接受线程
    pthread_create(&send_thread,NULL,runSend,(void*)&svr);//创建发送线程

    pthread_join(recv_thread,NULL);//主线程等待两个线程
    pthread_join(send_thread,NULL);
    return 0;
}

