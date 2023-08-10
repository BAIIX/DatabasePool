#include <iostream>
#include <memory>
#include <thread>
#include "MysqlConn.h"
#include "ConnectionPool.h"
using namespace std;
// 1.单线程
void del(){
    ConnectionPool* pool = ConnectionPool::getConnectionPool();
    shared_ptr<MysqlConn> conn = pool->getConnection();
    string sql = "delete from student;";
    conn->update(sql);
}

void op1(int begin, int end){   // 不使用连接池
    for(int i = begin; i < end; ++i){
        MysqlConn conn;
        conn.connect("root", "passwd", "BAI", "127.0.0.1");
        char sql[1024] = {0};
        sprintf(sql, "insert into student values(%d, 0, 0, 0, 0, 'bai', 20, '2002-02-15', '男')", i);
        conn.update(sql);
    }
}

void op2(ConnectionPool* pool, int begin, int end){     // 使用连接池
    for(int i = begin; i < end; ++i){
        shared_ptr<MysqlConn> conn = pool->getConnection();
        char sql[1024] = {0};
        sprintf(sql, "insert into student values(%d, 0, 0, 0, 0, 'bai', 20, '2002-02-15', '男')", i);
        conn->update(sql);
    }
}

void test1(){       // 单线程
#if 0
    steady_clock::time_point begin = steady_clock::now();
    op1(0, 5000);
    steady_clock::time_point end = steady_clock::now();
    auto length = end - begin;
    cout << "非连接池，单线程，用时：" << length.count() / 1000000 << "毫秒" << endl;
#else
    ConnectionPool* pool = ConnectionPool::getConnectionPool();
    steady_clock::time_point begin = steady_clock::now();
    op2(pool, 0, 5000);
    steady_clock::time_point end = steady_clock::now();
    auto length = end - begin;
    cout << "连接池，单线程，用时：" << length.count() / 1000000 << "毫秒" << endl;
#endif
}

// 2.多线程
void test2(){   // 多线程
#if 0
    MysqlConn conn;
    conn.connect("root", "ab040215", "test", "127.0.0.1");
    steady_clock::time_point begin = steady_clock::now();
    thread t1(op1, 0, 1000);
    thread t2(op1, 1000, 2000);
    thread t3(op1, 2000, 3000);
    thread t4(op1, 3000, 4000);
    thread t5(op1, 4000, 5000);
    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();
    steady_clock::time_point end = steady_clock::now();
    auto length = end - begin;
    cout << "非连接池，多线程，用时：" << length.count() / 1000000 << "毫秒" << endl;
#else
    ConnectionPool* pool = ConnectionPool::getConnectionPool();
    steady_clock::time_point begin = steady_clock::now();
    thread t1(op2, pool, 0, 1000);
    thread t2(op2, pool, 1000, 2000);
    thread t3(op2, pool, 2000, 3000);
    thread t4(op2, pool, 3000, 4000);
    thread t5(op2, pool, 4000, 5000);
    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();
    steady_clock::time_point end = steady_clock::now();
    auto length = end - begin;
    cout << "连接池，多线程，用时：" << length.count() / 1000000 << "毫秒" << endl;
#endif
}

void query(){   // 查询所有
    MysqlConn conn;
    conn.connect("root", "passwd", "BAI", "127.0.0.1");

    string sql = "select * from student";
    conn.query(sql);
    while(conn.next()){
        cout << conn.value(0) << ", "
                << conn.value(1) << ", "
                << conn.value(2) << ", "
                << conn.value(3) << ", "
                << conn.value(4) << ", "
                << conn.value(5) << ", "
                << conn.value(6) << ", "
                << conn.value(7) << ", "
                << conn.value(8) << endl;
    }
}

int main(){
    del();
    test1();
    del();
    test2();

    return 0;
}

