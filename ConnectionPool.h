#ifndef DATABASEPOOL_CONNECTIONPOOL_H
#define DATABASEPOOL_CONNECTIONPOOL_H
#include <queue>
#include <mutex>
#include <condition_variable>
#include "MysqlConn.h"
using namespace std;

// 实现懒汉模式的集中方式：
// 1.使用静态局部变量，但如果不支持C++11会有线程安全问题（为什么？）
// 2.使用互斥锁
// 3.使用callonce()

// 而饿汉模式是没有线程安全的——因为多个线程在访问时不涉及实例的创建

// 此处以懒汉模式实现单例模式 - 使用静态局部变量
class ConnectionPool {
public:
    ConnectionPool(const ConnectionPool& obj) = delete;
    ConnectionPool& operator=(const ConnectionPool& obj) = delete;

    static ConnectionPool* getConnectionPool();
    shared_ptr<MysqlConn> getConnection();
    ~ConnectionPool();
private:
    ConnectionPool();
    bool parseJsonFile();
    void produceConnection();
    void recycleConnection();
    void addConnection();

    string m_ip;            // ip地址
    string m_user;          // 用户名
    string m_passwd;        // 密码
    string m_dbName;        // 数据库名
    unsigned short m_port;  // 端口
    int m_minSize;          // 最小连接数
    int m_maxSize;          // 最大连接数
    int m_timeout;          // 超时时长
    int m_maxIdleTime;      // 最大的空闲时长
    queue<MysqlConn*> m_connectionQ;    // 连接池队列
    mutex m_mutexQ;
    condition_variable m_cond;
};


#endif //DATABASEPOOL_CONNECTIONPOOL_H
