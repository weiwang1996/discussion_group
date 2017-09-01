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
#include "data_pool.h"
#include <stdlib.h>
#include <pthread.h>
#include "dataType.h"

//定义udp服务器类
class udpServer
{
public:
    udpServer(const std::string _ip,const int &_port);
    void initServer();
    int recvData(std::string &outString);
    int sendData(const std::string &inString,\
            struct sockaddr_in &remote,socklen_t &len);
    int brocast();
    ~udpServer();
private:
    //拒绝拷贝构造和赋值
    udpServer(const udpServer&);
    udpServer& operator=(const udpServer&);
    void addUser(const struct sockaddr_in &remote);//添加用户
    void delUser(const struct sockaddr_in &remote);//删除用户
private:
    int sock;//socket
    std::string ip;//IP地址 （字符串类型）
    int port;//端口号
    std::map<in_addr_t,struct sockaddr_in>  user_list;//存储用户的map
    data_pool  pool;//数据池
};

#endif
