#include "json.hpp"
using json = nlohmann::json;

#include <iostream>
#include <vector>
#include <map>
#include <string>
using namespace std;

// json序列化和反序列化
// 示例1
string func1()
{
    json js;
    js["msg_type"] = 2;
    js["from"] = "zhang san";
    js["to"] = "li si";
    js["msg"] = "Hello ,What are you doing?";
    //json数据序列化：
    //json数据 => 序列化成字符串(发到网络)
    return js.dump();
}

// 示例2
string func2()
{
    json js;
    // 添加数组
    js["id"] = {1, 2, 3, 4, 5};
    // 添加key-value
    js["name"] = "zhang san";
    // msg键对应的值:json字符串
    js["msg"]["zhang san"] = "hello world";
    js["msg"]["liu shuo"] = "hello china";
    // 上面等同于下面
    js["msg"] = {{"zhang san", "hello world"}, {"liu shuo", "hello china"}};
    // json数据 => 序列化成字符串(发送到网络)
    return js.dump();
}

// 示例3
string func3()
{
    json js;
    // 序列化vector容器
    vector<int> vec;
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(5);
    js["list"] = vec;
    // 序列化map容器
    map<int, string> m;
    m.insert({1, "黄山"});
    m.insert({2, "华山"});
    m.insert({3, "泰山"});
    js["path"] = m;
    // json数据 => 序列化成字符串(发到网络)
    return js.dump();
}
int main()
{
    //数据反序列化: 
    //json字符串 => 反序列化成josn数据（看作容器）
    string recvBuf = func3();
    json jsBuf = json::parse(recvBuf);

    // 示例1
    // cout<<jsBuf["msg_type"]<<endl;
    // cout<<jsBuf["from"]<<endl;
    // cout<<jsBuf["to"]<<endl;
    // cout<<jsBuf["msg"]<<endl;
    // 示例2
    // cout<<jsBuf["id"]<<endl;
    // auto arr = jsBuf["id"];
    // cout<<arr[2]<<endl;

    // auto msgJs= jsBuf["msg"];
    // cout<<msgJs["zhang san"]<<endl;
    // cout<<msgJs["liu shuo"]<<endl;

    // 示例3
    //数组反序列化
    vector<int> vec = jsBuf["list"];
    for (auto &v : vec)
    {
        cout << v << "";
    }
    cout << endl;
    //图反序列化
    map<int, string> mymap = jsBuf["path"];
    for (auto &m : mymap)
    {
        cout << m.first << " " << m.second << endl;
    }
    cout << endl;

    return 0;
}