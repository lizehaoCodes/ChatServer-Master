//----------网络模块----------
#include "chatserver.hpp"
#include "json.hpp"
#include "chatservice.hpp"
#include <iostream>
#include <functional>
#include <string>
using namespace std;
using namespace placeholders;
using json = nlohmann::json;

// 初始化聊天服务器对象
ChatServer::ChatServer(EventLoop *loop,
                       const InetAddress &listenAddr,
                       const string &nameArg)
    : _server(loop, listenAddr, nameArg), _loop(loop)
{
    // 注册连接回调
    _server.setConnectionCallback(std::bind(&ChatServer::onConnection, this, _1));

    // 注册消息回调
    _server.setMessageCallback(std::bind(&ChatServer::onMessage, this, _1, _2, _3));

    // 设置线程数量
    _server.setThreadNum(4);
}

// 启动服务器
void ChatServer::start()
{
    _server.start();
}

// 处理连接事件的回调
void ChatServer::onConnection(const TcpConnectionPtr &conn)
{
    // 客户端异常断开
    if (!conn->connected())
    {
        ChatService::instance()->clientCloseException(conn);
        conn->shutdown();
    }
}

// 处理读写事件的回调
void ChatServer::onMessage(const TcpConnectionPtr &conn,
                           Buffer *buffer,
                           Timestamp time)
{
    string buf = buffer->retrieveAllAsString();
    cout << buf << endl; // 测试
    // 反序列化
    json js = json::parse(buf);

    // 事件分发过程：
    // 目的：完全解耦 <网络模块> 和 <业务模块>
    // 通过js["msgid"] => 对应处理器（conn、js、time)
    auto msgHandler = ChatService::instance()->getHandler(js["msgid"].get<int>());
    // 回调msgid所绑定的处理器，执行响应的业务处理
    msgHandler(conn, js, time);
}