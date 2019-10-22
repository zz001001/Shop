1.执行make生成可执行文件
2.linux下安装mysql
http://dev.mysql.com/downloads/mysql/ 
3.修改mysql的初始密码
自行百度即可
成功登录应如下图


4.创建数据库
create database Shop；(数据库名，因为我在服务器使用的是Shop，更改源码后可自行更改)
创建成功后可以查看一下，命令为：show databases; 显示如下图


5.创建表
create table  user_purchaser（表名）
(
num int primary key（主键约束）,
name varchar(45) ,
pass varchar(45)
);

创建表以后，先使用命令use Shop;指定Shop数据库，然后使用命令show tables; 查看表。

6.在服务器Util.cpp文件中更改ip为你自己的IP，在客户端Packdef文件里的宏定义也同样更改ip为你自己的IP
7.服务器端可以运行./Shop -t 4(线程数) - p 8000（端口号）
在客户端使用的端口为8000，如果想更改端口需要在客户端文件Packdef中更改为你想用的端口，默认使用8000.
8.客户端可以在VS下运行，注册自己的信息到服务器端的数据库中。
