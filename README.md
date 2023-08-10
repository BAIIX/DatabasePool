# DatabasePool

原作者：@爱编程的大丙：https://subingwen.cn/

【C++/数据库/多线程/MySQL】**基于C++11的数据库连接池**

------

*Tip：CMakeLists.txt中的mysql和jsoncpp请自行更改路径*

- Student.sql用于创建一个数据库及名为student的空表
- dbconf.json用于配制数据
  - minSize：连接池中最小连接数
  - maxSize：连接池中最大连接数
    - 跟着敲完然后发现这个最大连接数没用到，实际用处：当连接数>maxSi ze时销毁一定数量的连接
  - maxIdelTime：单个连接最长存活时间

------

**main.cpp**中分别使用了不同的方法去执行sql语句（是否使用连接池，单线程/多线程）

然后通过计时去对比不同方法所用耗费的时间，达到模拟的效果
