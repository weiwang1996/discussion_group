#include "udpServer.h"


udpServer::udpServer(const std::string _ip,const int &_port)
 :ip(_ip)
 ,port(_port)
 ,pool(1024)
{}

//初始化阶段，套接字的创建和绑定
void udpServer::initServer()
{
    sock = socket(AF_INET,SOCK_DGRAM,0);//创建UDP套接字 Ipv4
    if(sock<0)
    {
        printf_log("create sock error",FATAL);
        exit(1);
    }
    //绑定到local
    struct sockaddr_in local;
    local.sin_family = AF_INET;
    local.sin_port = htons(port);
    local.sin_addr.s_addr = inet_addr(ip.c_str());
   //绑定
   if(bind(sock,(struct sockaddr*)&local,sizeof(local))<0)
    {
        printf_log("bind socket error!",FATAL);
        exit(2);
    }
}

//map里面存放key（主键）为ip地址，value存放sockaddr_in 结构体，为什么不存放指针？
void udpServer::addUser(const struct sockaddr_in &remote)
{
    user_list.insert(std::pair<in_addr_t,struct sockaddr_in>(remote.sin_addr.s_addr,remote));
}

void udpServer::delUser(const struct sockaddr_in &remote)
{
    std::map<in_addr_t,struct sockaddr_in>::iterator iter = user_list.find(remote.sin_addr.s_addr);
    if(iter != user_list.end())
    {
        user_list.erase(iter->first);
    }
}

int udpServer::recvData(std::string &outString)
{
    char buf[1024];
    struct sockaddr_in remote;
    socklen_t len = sizeof(remote);
    ssize_t s = recvfrom(sock,buf,sizeof(buf),0,(struct sockaddr*)&remote,&len);
    if(s>0)
    {
    buf[s] = '\0';
    outString = buf;//接受数据
    pool.putData(outString);//放到数据池中，再去转发

    dataType data;
    data.stringToValue(outString);
    if(data.cmd == "QUIT")//当接收到的数据中cmd字段为QUIT表示该用户退出。
        {
        delUser(remote);
        }
        else
        {
    addUser(remote);//把该用户添加到map中进行控制
        }
    }
    return s;
}

int udpServer::sendData(const std::string &inString,struct sockaddr_in &remote,socklen_t &len)
{
    ssize_t s = sendto(sock,inString.c_str(),inString.size(),0,(struct sockaddr*)&remote,len);
    if(s>0)
    {
       // print_log("sento ")
    }
        return s;
}

int udpServer::brocast()
{
    std::string msg ;
    pool.getData(msg);//从数据池中拿出来数据
    std::map<in_addr_t,struct sockaddr_in>::iterator iter = user_list.begin();
    socklen_t len = 0;
    for(;iter!=user_list.end();iter++)//给所有在map中的用户发送出去
    {
        len = sizeof(iter->second);
        sendData(msg,iter->second,len);
    }

}

udpServer::~udpServer()
{
    close(sock);
}
