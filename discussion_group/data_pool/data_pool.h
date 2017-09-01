#ifndef _DATA_POOL_H_
#define _DATA_POOL_H_

#include <iostream>
#include <vector>
#include <string>
#include <semaphore.h>


class data_pool
{
public:
    data_pool(int _cap);
    void getData(std::string &outString);
    void putData(const std::string &inString);
    ~data_pool();
private:
    data_pool(const data_pool&);
private:
    int cap;//数据池总容量
    int size;//当前大小
    int product_step;//生产者
    int consumer_step;//消费者
    sem_t blank;//空格信号量
    sem_t data;//数据信号量
    std::vector<std::string> pool;//用vector，环形数组来存
};

#endif //__DATA_POOL_H__
