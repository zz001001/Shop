


#ifndef _PACKDEF_H
#define _PACKDEF_H

#define SERVERIP "192.168.17.128"

#define _DEF_THREADPOOLSIZE  1000




//协议
#define _DEF_PROTOCOL_BASE   10

//注册（主播、观众）

#define _DEF_PROTOCOL_REGISTER_RQ   _DEF_PROTOCOL_BASE +1
#define _DEF_PROTOCOL_REGISTER_RS   _DEF_PROTOCOL_BASE +2

//登录（主播、观众）
#define _DEF_PROTOCOL_LOGIN_RQ   _DEF_PROTOCOL_BASE +3
#define _DEF_PROTOCOL_LOGIN_RS   _DEF_PROTOCOL_BASE +4


//主播-----------
//获取房间信息
#define _DEF_PROTOCOL_GETROOMINFO_RQ   _DEF_PROTOCOL_BASE +5
#define _DEF_PROTOCOL_GETROOMINFO_RS   _DEF_PROTOCOL_BASE +6

//更改房间信息
#define _DEF_PROTOCOL_SETROOMINFO_RQ   _DEF_PROTOCOL_BASE +7
#define _DEF_PROTOCOL_SETROOMINFO_RS   _DEF_PROTOCOL_BASE +8

//开始直播
#define _DEF_PROTOCOL_STARTTRANSFER_RQ   _DEF_PROTOCOL_BASE +9
#define _DEF_PROTOCOL_STARTTRANSFER_RS   _DEF_PROTOCOL_BASE +10
//主播-----------


//视频流的传输-----
//以文件的形式传输
#define _DEF_PROTOCOL_FILEHEADER_RQ      _DEF_PROTOCOL_BASE +11
#define _DEF_PROTOCOL_FILEHEADER_RS      _DEF_PROTOCOL_BASE +12

//以缓冲区的形式传输
#define _DEF_PROTOCOL_STREAMCONTENT_RQ      _DEF_PROTOCOL_BASE +13
#define _DEF_PROTOCOL_STREAMCONTENT_RS      _DEF_PROTOCOL_BASE +14
//视频流的传输-----


//观众------------
//获取主播列表
#define _DEF_PROTOCOL_GETAUTHORLIST_RQ      _DEF_PROTOCOL_BASE +15
#define _DEF_PROTOCOL_GETAUTHORLIST_RS      _DEF_PROTOCOL_BASE +16
//选择主播
#define _DEF_PROTOCOL_SELECTAUTHOR_RQ      _DEF_PROTOCOL_BASE +17
#define _DEF_PROTOCOL_SELECTAUTHOR_RS      _DEF_PROTOCOL_BASE +18
//观众------------

//协议包
typedef int PackType;
//边界值
#define _DEF_SIZE  64
#define _STREAMCONTENTSIZE  1000
#define _AUTHORNUM    10
#define SQILEN  300

//角色
#define  user_purchaser 0
#define  user_seller  1

//结果
#define _register_fail    0
#define _register_success  1

#define  _register_tel_exist  0
#define  _register_username_exist 1
#define  _register_success  2

#define _login_usename_noexist 0
#define _login_password_err 1
#define _login_success  2

#define _setroom_fail 0
#define _setroom_success 1


//请求注册和登录协议包
typedef struct STRU_REGISTER_RQ  
{
	PackType m_nType;
	int      m_userid;
	char     m_szName[_DEF_SIZE];
	char     m_szPassWord[_DEF_SIZE];
	char     m_brole;  //角色（识别主播还是观众）
}STRU_LOGIN_RQ;

//回复注册和登录协议包
typedef struct STRU_REGISTER_RS
{
	PackType m_nType;
	char     m_szResult; //结果（注册和登录是否成功）
}STRU_LOGIN_RS;

//主播----------------------------------
//（主播）请求获取房间信息协议包
struct STRU_GETROOMINFO_RQ
{
	PackType m_nType;
	char     m_szName[_DEF_SIZE]; //主播名
};

//回复获取房间协议包
struct STRU_GETROOMINFO_RS
{
	PackType m_nType;
	long     m_roomid;
	char     m_szRoomName[_DEF_SIZE];
};

//（主播）请求设置房间信息协议包
struct STRU_SETROOMINFO_RQ
{
	PackType m_nType;
	char     m_szRoomName[_DEF_SIZE]; //要更改的房间名
};

//回复设置房间信息协议包
struct STRU_SETROOMINFO_RS
{
	PackType m_nType;
	char     m_szResult; //返回结果（是否更该成功）
};

//主播请求开始直播包
struct STRU_STARTTRANFER_RQ
{
	PackType m_nType;
	char     m_szName[_DEF_SIZE];
};

//回复主播开始请求包
struct STRU_STARTTRANFER_RS
{
	PackType m_nType;
	char     m_szResult;
};

//视频流 ----------------------------- TCP（不需要回复）
struct STRU_STREAMCONTENT_RQ
{
	PackType m_nType;
	char     m_szName[_DEF_SIZE];
	char     m_szContent[_STREAMCONTENTSIZE];
	int      m_nLen;
};

//观众-------------------------------------
//观众请求主播列表协议包
struct STRU_GETAUTHORLIST_RQ
{
	PackType m_nType;
};


//主播信息
struct AuthorInfo
{
	char m_szName[_DEF_SIZE];
	char m_szRoomName[_DEF_SIZE];
	long m_roomid;
};

//回复观众主播列表包
struct STRU_GETAUTHORLIST_RS
{
	PackType m_nType;
	AuthorInfo m_aryAuthor[_AUTHORNUM];
	int    m_nNum;
};

//选择主播请求包
struct STRU_SELECTAUTHOR_RQ
{
	PackType m_nType;
	char m_szName[_DEF_SIZE];
};

//回复选择主播请求包
struct STRU_SELECTAUTHOR_RS
{
	PackType m_nType;
	char     m_szResult;
};

#endif



