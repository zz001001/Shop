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
	bool  ConnectMySql(char *host,char *user,char *pass,char *db); //���������û��������룬���ݿ�
	void  DisConnect();
	bool  SelectMySql(char* szSql,int nColumn,list<string>& lstStr);

	//���£�ɾ�������롢�޸�
	bool  UpdateMySql(char* szSql);

private:
	MYSQL *sock;         //mysqlָ��
	MYSQL_RES *results;  //��ѯ�ɹ����صĽ������
	MYSQL_ROW record; 

};

