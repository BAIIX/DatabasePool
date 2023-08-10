//
// Created by 白 on 2023/8/9.
//

#include "MysqlConn.h"

MysqlConn::MysqlConn() {
    m_conn = mysql_init(nullptr);
    mysql_set_character_set(m_conn, "utf8");     // 设置借口的编码为utf8，避免读取中文时发生乱码
}

MysqlConn::~MysqlConn() {
    if(m_conn != nullptr){
        mysql_close(m_conn);
    }
    freeResult();
}

bool MysqlConn::connect(string user, string passwd, string dbName, string ip, unsigned short port) {
    MYSQL* ptr = mysql_real_connect(m_conn, ip.c_str(), user.c_str(), passwd.c_str(), dbName.c_str(), port, nullptr, 0);    // 接收的是一个char*类型的数据，因此要转换一下
    return (ptr != nullptr);
}

bool MysqlConn::update(string sql) {
    bool notSucceed = mysql_query(m_conn, sql.c_str());  // 返回为0代表执行成功，如果非0则执行失败了
    if(notSucceed) {
        return false;
    } else {
        return true;
    }
}

bool MysqlConn::query(string sql) {
    freeResult();
    bool notSucceed = mysql_query(m_conn, sql.c_str());  // 返回为0代表执行成功，如果非0则执行失败了
    if(notSucceed) {
        return false;
    } else {
        m_result = mysql_store_result(m_conn);
        return true;
    }
}

bool MysqlConn::next() {
    if(m_result != nullptr){
        m_row = mysql_fetch_row(m_result);
        if(m_row != nullptr) return true;
    }
    return false;
}

string MysqlConn::value(int index) {
    int rowCount = mysql_num_fields(m_result);
    if(index >= rowCount || index < 0){
        return string();
    }
    char* val = m_row[index];
    unsigned long length = mysql_fetch_lengths(m_result)[index];
    return string(val, length);     // 当val为二进制字符串，其中包含'\0'，那么转换成string时只会将'\0'前面的部分转换。为了避免这种情况出现，规定转换成string类型的长度
}

bool MysqlConn::transaction() {
    return mysql_autocommit(m_conn, false);     // 第二个参数为false指手动提交
}

bool MysqlConn::commit() {
    return mysql_commit(m_conn);
}

bool MysqlConn::rollback() {
    return mysql_rollback(m_conn);
}

void MysqlConn::freeResult() {
    if(m_result != nullptr){
        mysql_free_result(m_result);
        m_result = nullptr;
    }
}

void MysqlConn::refreshAliveTime() {
    m_alivetime = steady_clock::now();  // 纳秒
}

long long MysqlConn::getAliveTime() {
    nanoseconds res = steady_clock::now() - m_alivetime;
    milliseconds millsec = duration_cast<milliseconds>(res);
    return millsec.count();
}
