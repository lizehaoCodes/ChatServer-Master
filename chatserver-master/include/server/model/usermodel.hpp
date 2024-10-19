// -------user表 数据操作类 -------
#ifndef USERMODEL_H
#define USERMODEL_H
#include "user.hpp"

// 提供 user表 的操作接口方法
class UserModel
{
public:
    // 添加新用户到user表
    bool insert(User &user);
    // 根据用户id查询用户信息
    User query(int id);
    // 更新用户的状态信息
    bool updateState(User user);
    // 重置用户的状态信息
    void resetState();
};

#endif