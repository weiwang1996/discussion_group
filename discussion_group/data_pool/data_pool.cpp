#include "data_pool.h"

data_pool::data_pool(int _cap)
    :cap(_cap)
    ,size(0)
    ,pool(_cap)
{
    product_step = 0;
    consumer_step = 0;
    sem_init(&blank,0,cap);//初始化格子信号为整个环形队列的cap
    sem_init(&data,0,0);//初始化数据信号量为0
}

void data_pool::getData(std::string &outString)
{
    sem_wait(&data);//获得数据data数据进行V操作
    outString = pool[consumer_step];
    consumer_step++;
    consumer_step %= cap;//实现环形存储
    size--;
    sem_post(&blank);//对格子信号P操作
}

//生产数据
void data_pool::putData(const std::string &inString)
{
    sem_wait(&blank);//put数据和get数据刚好相反
    pool[product_step] = inString;
    product_step++;
    product_step%= cap;
    size++;
    sem_post(&data);
}

data_pool::~data_pool()
{
    cap=0;
    size=0;
    product_step = 0;
    consumer_step = 0;
    sem_destroy(&blank);
    sem_destroy(&data);
}
