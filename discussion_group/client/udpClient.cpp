#include "udpClient.h"


udpClient::udpClient(const std::string _srv_ip,const int &_srv_port)//客户端只需要服务器的ip和端口号
 :server_ip(_srv_ip)
 ,server_port(_srv_port)
{}

void udpClient::initClient()
{
    sock = socket(AF_INET,SOCK_DGRAM,0);//创建UDP套接字
    if(sock<0)
    {
        printf_log("create sock error",FATAL);
        exit(1);
    }
}

void udpClient::addUser(std::string &_friend)
{
    std::vector<std::string>::iterator iter=find(flist.begin(),flist.end(),_friend);//如果找不到这个好友的话那么就添加进好友列表
    if(iter == flist.end())
    {
        flist.push_back(_friend);
    }

}
void udpClient::delUser(std::string &_friend)
{
    //找到并删除好友
    std::vector<std::string>::iterator iter=find(flist.begin(),flist.end(),_friend);
    if(iter != flist.end()){
    flist.erase(iter);  
}
}


int udpClient::recvData(std::string &outString)
{
    char buf[1024];
    struct sockaddr_in remote;
    socklen_t len = sizeof(remote);
    ssize_t s = recvfrom(sock,buf,sizeof(buf),0,(struct sockaddr*)&remote,&len);//接受服务器发来的数据
    if(s>0)
    {
    buf[s] = '\0';
    outString = buf;
    }
    return s;
}

int udpClient::sendData(const std::string &inString)
{
    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(server_port);
    server.sin_addr.s_addr = inet_addr(server_ip.c_str());
    socklen_t len  = sizeof(server);
    ssize_t s = sendto(sock,inString.c_str(),inString.size(),0,(struct sockaddr*)&server,len);//发送数据，用sendto
    if(s>0)
    {
       // print_log("sento ")
    }
        return s;
}


udpClient::~udpClient()
{
    close(sock);
}
