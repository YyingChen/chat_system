#include"udpServer.h"

using namespace std;

static void usage(std::string proc)
{
    cout<<"Usage: "<<proc<<"[local_ip][local_port]"<<endl;
}

static void *runRecv(void* arg)
{
    udpServer* svrp=(udpServer*) arg;
    std::string msg;
    for(;;)
    {
      svrp->recvData(msg);
      cout<<"client:"<<msg<<endl;
    }
}
static void *runSend(void* arg)
{
    udpServer* svrp=(udpServer*) arg;
    for(;;)
    {
        svrp->brocast();
    }
}
int main(int argc,char* argv[])//./client 126.1.1.1 8080
{
    if(argc!=3)
    {
        usage(argv[0]);
        exit(1);
    }
    int port=atoi(argv[2]);
    udpServer svr(argv[1],port);
    svr.initServer();

    pthread_t recv_thread,send_thread;
    pthread_create(&recv_thread,NULL,runRecv,(void*)&svr);
    pthread_create(&send_thread,NULL,runSend,(void*)&svr);

    pthread_join(recv_thread,NULL);
    pthread_join(send_thread,NULL);
    return 0;
}
