cmake_minimum_required(VERSION 3.26)
project(DatabasePool)

set(CMAKE_CXX_STANDARD 17)

include_directories("/usr/local/mysql/include") #本机MySQL下的include路径
include_directories("/usr/local/mysql/lib")
include_directories("./jsoncpp/include")
include_directories("./jsoncpp/include/json")
include_directories("./jsoncpp/lib")


add_executable(DatabasePool main.cpp
        MysqlConn.cpp
        MysqlConn.h
        ConnectionPool.cpp
        ConnectionPool.h)

target_link_libraries(DatabasePool /usr/local/mysql/lib/libmysqlclient.20.dylib)
target_link_libraries(DatabasePool /usr/local/jsoncpp/lib/libjsoncpp.20.dylib)


