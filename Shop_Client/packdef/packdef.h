


#ifndef _PACKDEF_H
#define _PACKDEF_H

#define SERVERIP "192.168.17.128"

#define _DEF_THREADPOOLSIZE  1000




//Э��
#define _DEF_PROTOCOL_BASE   10

//ע�ᣨ���������ڣ�

#define _DEF_PROTOCOL_REGISTER_RQ   _DEF_PROTOCOL_BASE +1
#define _DEF_PROTOCOL_REGISTER_RS   _DEF_PROTOCOL_BASE +2

//��¼�����������ڣ�
#define _DEF_PROTOCOL_LOGIN_RQ   _DEF_PROTOCOL_BASE +3
#define _DEF_PROTOCOL_LOGIN_RS   _DEF_PROTOCOL_BASE +4


//����-----------
//��ȡ������Ϣ
#define _DEF_PROTOCOL_GETROOMINFO_RQ   _DEF_PROTOCOL_BASE +5
#define _DEF_PROTOCOL_GETROOMINFO_RS   _DEF_PROTOCOL_BASE +6

//���ķ�����Ϣ
#define _DEF_PROTOCOL_SETROOMINFO_RQ   _DEF_PROTOCOL_BASE +7
#define _DEF_PROTOCOL_SETROOMINFO_RS   _DEF_PROTOCOL_BASE +8

//��ʼֱ��
#define _DEF_PROTOCOL_STARTTRANSFER_RQ   _DEF_PROTOCOL_BASE +9
#define _DEF_PROTOCOL_STARTTRANSFER_RS   _DEF_PROTOCOL_BASE +10
//����-----------


//��Ƶ���Ĵ���-----
//���ļ�����ʽ����
#define _DEF_PROTOCOL_FILEHEADER_RQ      _DEF_PROTOCOL_BASE +11
#define _DEF_PROTOCOL_FILEHEADER_RS      _DEF_PROTOCOL_BASE +12

//�Ի���������ʽ����
#define _DEF_PROTOCOL_STREAMCONTENT_RQ      _DEF_PROTOCOL_BASE +13
#define _DEF_PROTOCOL_STREAMCONTENT_RS      _DEF_PROTOCOL_BASE +14
//��Ƶ���Ĵ���-----


//����------------
//��ȡ�����б�
#define _DEF_PROTOCOL_GETAUTHORLIST_RQ      _DEF_PROTOCOL_BASE +15
#define _DEF_PROTOCOL_GETAUTHORLIST_RS      _DEF_PROTOCOL_BASE +16
//ѡ������
#define _DEF_PROTOCOL_SELECTAUTHOR_RQ      _DEF_PROTOCOL_BASE +17
#define _DEF_PROTOCOL_SELECTAUTHOR_RS      _DEF_PROTOCOL_BASE +18
//����------------

//Э���
typedef int PackType;
//�߽�ֵ
#define _DEF_SIZE  64
#define _STREAMCONTENTSIZE  1000
#define _AUTHORNUM    10
#define SQILEN  300

//��ɫ
#define  user_purchaser 0
#define  user_seller  1

//���
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


//����ע��͵�¼Э���
typedef struct STRU_REGISTER_RQ  
{
	PackType m_nType;
	int      m_userid;
	char     m_szName[_DEF_SIZE];
	char     m_szPassWord[_DEF_SIZE];
	char     m_brole;  //��ɫ��ʶ���������ǹ��ڣ�
}STRU_LOGIN_RQ;

//�ظ�ע��͵�¼Э���
typedef struct STRU_REGISTER_RS
{
	PackType m_nType;
	char     m_szResult; //�����ע��͵�¼�Ƿ�ɹ���
}STRU_LOGIN_RS;

//����----------------------------------
//�������������ȡ������ϢЭ���
struct STRU_GETROOMINFO_RQ
{
	PackType m_nType;
	char     m_szName[_DEF_SIZE]; //������
};

//�ظ���ȡ����Э���
struct STRU_GETROOMINFO_RS
{
	PackType m_nType;
	long     m_roomid;
	char     m_szRoomName[_DEF_SIZE];
};

//���������������÷�����ϢЭ���
struct STRU_SETROOMINFO_RQ
{
	PackType m_nType;
	char     m_szRoomName[_DEF_SIZE]; //Ҫ���ĵķ�����
};

//�ظ����÷�����ϢЭ���
struct STRU_SETROOMINFO_RS
{
	PackType m_nType;
	char     m_szResult; //���ؽ�����Ƿ���óɹ���
};

//��������ʼֱ����
struct STRU_STARTTRANFER_RQ
{
	PackType m_nType;
	char     m_szName[_DEF_SIZE];
};

//�ظ�������ʼ�����
struct STRU_STARTTRANFER_RS
{
	PackType m_nType;
	char     m_szResult;
};

//��Ƶ�� ----------------------------- TCP������Ҫ�ظ���
struct STRU_STREAMCONTENT_RQ
{
	PackType m_nType;
	char     m_szName[_DEF_SIZE];
	char     m_szContent[_STREAMCONTENTSIZE];
	int      m_nLen;
};

//����-------------------------------------
//�������������б�Э���
struct STRU_GETAUTHORLIST_RQ
{
	PackType m_nType;
};


//������Ϣ
struct AuthorInfo
{
	char m_szName[_DEF_SIZE];
	char m_szRoomName[_DEF_SIZE];
	long m_roomid;
};

//�ظ����������б��
struct STRU_GETAUTHORLIST_RS
{
	PackType m_nType;
	AuthorInfo m_aryAuthor[_AUTHORNUM];
	int    m_nNum;
};

//ѡ�����������
struct STRU_SELECTAUTHOR_RQ
{
	PackType m_nType;
	char m_szName[_DEF_SIZE];
};

//�ظ�ѡ�����������
struct STRU_SELECTAUTHOR_RS
{
	PackType m_nType;
	char     m_szResult;
};

#endif



