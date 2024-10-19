//----------网络模块----------
// 网络模块解析msgid，派发相应的事件回调，到相对应的业务模块
// 网络层派发json到服务层，创建model层来解耦业务层代码和数据库操作
// 使用nginx的Tcp负载均衡，把集群的服务器进行负载，可在很短的时间内提升服务器的并发能力
#ifndef CHATSERVER_H
#define CHATSERVER_H
#include <muduo/net/TcpServer.h>
#include <muduo/net/EventLoop.h>
using namespace muduo;
using namespace muduo::net;

// 聊天服务器的主类
class ChatServer
{
public:
    // 初始化聊天服务器对象
    ChatServer(EventLoop *loop,
               const InetAddress &listenAddr,
               const string &nameArg);

    // 启动服务器
    void start();

private:
    // 处理连接事件的回调
    void onConnection(const TcpConnectionPtr &);

    // 处理读写事件的回调
    void onMessage(const TcpConnectionPtr &,
                   Buffer *,
                   Timestamp);

    TcpServer _server; // 组合的muduo库，实现服务器功能的类对象
    EventLoop *_loop;  // 指向事件循环对象的指针
};

#endif