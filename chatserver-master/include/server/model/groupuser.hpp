//------处理群组业务------
#ifndef GROUPUSER_H
#define GROUPUSER_H
#include "user.hpp"

//-----groupuser表的 ORM 类-----
class GroupUser : public User
{
public:
    // 设置
    void setRole(string role) { this->role = role; }
    // 获取
    string getRole() { return this->role; }

private:
    string role; // 角色信息（creator\normal)
};

#endif