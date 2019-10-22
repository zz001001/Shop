#pragma once
#include <mysql/mysql.h>
#include <list>
#include <iostream>
#include <string>
using namespace std;

class MySql
{
public:
	MySql(void);
	~MySql(void);
public:
	bool  ConnectMySql(char *host,char *user,char *pass,char *db); //主机名，用户名，密码，数据库
	void  DisConnect();
	bool  SelectMySql(char* szSql,int nColumn,list<string>& lstStr);

	//更新：删除、插入、修改
	bool  UpdateMySql(char* szSql);

private:
	MYSQL *sock;         //mysql指针
	MYSQL_RES *results;  //查询成功返回的结果及集
	MYSQL_ROW record; 

};

