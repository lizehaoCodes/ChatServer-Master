// -------offlinemessage表的 数据操作类 -------
#ifndef OFFLINEMESSAGEMODEL_H
#define OFFLINEMESSAGEMODEL_H
#include <string>
#include <vector>
using namespace std;

// 提供 离线消息表 的操作接口方法
class OfflineMsgModel
{
public:
    // 存储用户的离线消息
    void insert(int userid, string msg);

    // 删除用户的离线消息
    void remove(int userid);

    // 查询用户的离线消息
    vector<string> query(int userid);
};

#endif