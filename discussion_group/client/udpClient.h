#ifndef _UDP_SERVER_
#define _UDP_SERVER_

#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include "log.h"
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string>
#include <map>
#include <stdlib.h>
#include <vector>
#include <algorithm>

class udpClient
{
public:
    udpClient(const std::string _srv_ip,const int &_srv_port);//构造
    void initClient();//初始化客户端类
    int recvData(std::string &outString);//接收数据
    int sendData(const std::string &inString);//发送数据
    void addUser(std::string &_friend);//添加好友
    void delUser(std::string &_friend);//删除好友
    ~udpClient();
    std::vector<std::string> flist;//好友列表
private:
    udpClient(const udpClient&);
private:
    int sock;
    std::string server_ip;//服务器ip
    int server_port;//服务器port
};

#endif
