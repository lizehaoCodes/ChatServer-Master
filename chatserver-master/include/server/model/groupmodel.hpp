//------处理群组业务------
// -------allgroup、groupuser表的 数据操作类 -------
#ifndef GROUPMODEL_H
#define GROUPMODEL_H
#include "group.hpp"
#include <string>
#include <vector>
using namespace std;

// 提供 allgroup、groupuser 的操作接口方法
class GroupModel
{
public:
    // 创建群组
    bool createGroup(Group &group);
    // 加入群组
    void addGroup(int userid, int groupid, string role);
    // 查询用户所在群组信息
    vector<Group> queryGroups(int userid);
    // 群聊业务：根据 groupid 查询群组的用户id列表，群发消息给其它成员
    vector<int> queryGroupUsers(int userid, int groupid);
};

#endif