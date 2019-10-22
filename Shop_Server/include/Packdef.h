#pragma once

//协议包类型
typedef int PackType;

//协议
#define _DEF_PROTOCOL_BASE   10

#define _DEF_PROTOCOL_REGISTER_RQ   _DEF_PROTOCOL_BASE +1  //注册
#define _DEF_PROTOCOL_REGISTER_RS   _DEF_PROTOCOL_BASE +2


#define _DEF_PROTOCOL_LOGIN_RQ   _DEF_PROTOCOL_BASE +3    //登录
#define _DEF_PROTOCOL_LOGIN_RS   _DEF_PROTOCOL_BASE +4

//边界值
#define _SQLLEN              300
#define _DEF_SIZE            64

//协议包数据结构
typedef struct STRU_REGISTER_RQ
{
	PackType m_nType;
	int      m_userid;
	char     m_szName[_DEF_SIZE];
	char     m_szPassWord[_DEF_SIZE];
	char     m_brole;
}STRU_LOGIN_RQ;

typedef struct STRU_REGISTER_RS
{
	PackType m_nType;
	char     m_szResult;
}STRU_LOGIN_RS;

//返回结果
#define user_purchaser     0
#define user_seller        1

#define _register_fail    0
#define _register_success  1

#define _login_fail    0
#define _login_success  1
