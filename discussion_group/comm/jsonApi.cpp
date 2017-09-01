#include "jsonApi.h"
#include <string>

jsonApi::jsonApi()
{

}

int jsonApi::serialize(const Json::Value &val,std::string &outString)
{
#ifdef _FAST_
    Json::FastWriter w;
    outString = w.write(val);//Fast模型序列化 把很多字符串转化为{"name":"乔布斯","campany":"Apple","age":"12"}
#else
    Json::StyledWriter w;//Style模型序列化
    outString = w.write(val);
#endif
    return 0;
}
int jsonApi::deSerialize(std::string &inString,Json::Value &val)
{
    Json::Reader r;
    if(r.parse(inString,val,false)<0)//反序列化
    {
    return 0;
    }
    return 1;
}
jsonApi::~jsonApi()
{

}

