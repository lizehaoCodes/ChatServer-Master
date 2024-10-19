// -------friend表的 数据操作类 -------
#ifndef FRIENDMODEL_H
#define FRIENDMODEL_H
#include "user.hpp"
#include <vector>
using namespace std;

// 提供 friend表 的操作接口方法
class FriendModel
{
public:
    // 添加好友关系表
    void insert(int userid, int friendid);
    // 返回用户好友列表
    vector<User> query(int userid);
};

#endif