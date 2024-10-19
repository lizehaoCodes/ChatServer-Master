/*
基于muduo网络库开发服务器(基于事件驱动、epoll I/O复用 + 线程池。整体基于reactor模型)
<网络模块解析消息，派发相应的事件回调，到业务模块>
1. 创建TcpServer对象
2. 创建EventLoop（事件循环）对象指针
3. 根据TcpServer构造函数的参数，提供ChatServer的默认构造（无默认，需提供）
4. 在ChatServer类的构造函数中，注册处理连接和读写事件的回调函数
5. 设置合适的服务端线程数量，muduo会自动分配I/O线程、Worker线程

muduo网络库：提供两个类
1.TcpServer: 用于编写服务器程序的
2.TcpClient: 用于编写客户端程序的
3.构成：1、epoll + 线程池
        2、两个模块：《网络模块》、《业务模块》（用户的连接和断开、用户的读写事件等）
*/
#include <muduo/net/TcpServer.h>
#include <muduo/net/EventLoop.h>
#include <iostream>
#include <functional> //绑定器
#include <string>
using namespace std;
using namespace muduo;
using namespace muduo::net;
using namespace placeholders; // 占位符

class ChatServer
{
public:
    // TcpServer没有默认构造，需提供
    ChatServer(EventLoop *loop,               // 事件循环（reactor 反应堆）
               const InetAddress &listenAddr, // ip + port
               const string &nameArg)         // 服务器名称
        : _server(loop, listenAddr, nameArg), _loop(loop)
    {
        // 注册用户连接和断开回调
        _server.setConnectionCallback(std::bind(&ChatServer::onConnection, this, _1)); // 占位符

        // 注册用户的读、写事件回调
        _server.setMessageCallback(std::bind(&ChatServer::onMessage, this, _1, _2, _3));

        // 设置服务器端的线程数量（1个I/O线程，3个Worker线程）
        _server.setThreadNum(4);
    }
    // 开启事件循环
    void start()
    {
        _server.start();
    }

private:
    // 访问ChatServer对象的成员变量，向ConnectionCallback提供参数
    void onConnection(const TcpConnectionPtr &conn)
    {
        if (conn->connected())
        {
            cout << conn->peerAddress().toIpPort() << "->" << conn->localAddress().toIpPort() << " State: online" << endl;
        }
        else
        {
            cout << conn->peerAddress().toIpPort() << "->" << conn->localAddress().toIpPort() << " State: Offline" << endl;
            conn->shutdown();//close(fd)
            //_loop->quit();
        }
    }
    // 处理用户读写事件的回调函数，向ConnectionCallback提供参数
    void onMessage(const TcpConnectionPtr &conn, // 连接
                   Buffer *buffer,               // 缓冲区
                   Timestamp time)               // 接收到数据的时间信息
    {
        string buf = buffer->retrieveAllAsString();
        cout << "Recv Data:" << buf << "Time:" << time.toString() << endl;
        conn->send(buf);
    }
    TcpServer _server; // 1
    EventLoop *_loop;  // 2
};
int main()
{
    EventLoop loop; // epoll
    InetAddress addr("127.0.0.1", 1112);
    ChatServer server(&loop, addr, "MyServer");

    server.start();
    loop.loop(); // epoll_wait以阻塞方式等待新用户连接、已连接用户的读写事件

    return 0;
}
/*
编译： g++ -o server server.cpp -lmuduo_net -lmuduo_base -lpthread 、 ctrl + shift + b（导入task）
连接客户端：telnet ip port
关闭客户端：ctrl + ] ,quit
关闭服务器：ctrl + c
*/