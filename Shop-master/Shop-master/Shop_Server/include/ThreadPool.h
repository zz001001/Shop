#pragma once
#include<iostream>
#include<vector>
#include<queue>
#include<unistd.h>
#include<string.h>
#include<sys/types.h>
#include<ctype.h>
#include<signal.h>
#include<errno.h>
#include<pthread.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include"MutexLock.h"
#include"Condition.h"

using namespace std;

class CTask
{
public:
	CTask() {};
	virtual ~CTask() {};
public:
	virtual void RunTask() {};

};


class CMyThreadPool
{
public:
	CMyThreadPool();
	~CMyThreadPool();
public:
	__uint32_t m_nMaxThread;           //�߳�������
	__uint32_t m_nMinThread;           //�߳���С����
	__uint32_t m_nOriThread;           //��ʼ�̸߳���
	__uint32_t m_nRunThread;           //�̷߳�æ����
	__uint32_t m_nCurrentThread;       //��ǰ�̸߳���
	bool  m_bThreadQuit;
	int err;
	vector<pthread_t> m_vecThread;  //�߳�id����
	pthread_t m_managerid;
	queue<CTask*> m_quTask;            //�������
	
	MutexLock m_MutexLock;             //������
	Condition m_Condition;             //��������

	static const int increase=5;
	static const int decrease=2;
public:
	bool CreateThreadPool(__uint32_t nMinThread , __uint32_t nMaxThread ,__uint32_t nOriThread);
	void DestroyThreadPool();
	bool PushTask(CTask* pTask);
	static void *Threadpro(void *lpThreadPool);  //�߳�ִ�к���
	static void *Manager(void *lpThreadPool);    //�������߳�
	bool If_thread_alive(pthread_t tid);

};
