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
	__uint32_t m_nMaxThread;           //线程最大个数
	__uint32_t m_nMinThread;           //线程最小个数
	__uint32_t m_nOriThread;           //初始线程个数
	__uint32_t m_nRunThread;           //线程繁忙个数
	__uint32_t m_nCurrentThread;       //当前线程个数
	bool  m_bThreadQuit;
	int err;
	vector<pthread_t> m_vecThread;  //线程id数组
	pthread_t m_managerid;
	queue<CTask*> m_quTask;            //任务队列
	
	MutexLock m_MutexLock;             //互斥锁
	Condition m_Condition;             //条件变量

	static const int increase=5;
	static const int decrease=2;
public:
	bool CreateThreadPool(__uint32_t nMinThread , __uint32_t nMaxThread ,__uint32_t nOriThread);
	void DestroyThreadPool();
	bool PushTask(CTask* pTask);
	static void *Threadpro(void *lpThreadPool);  //线程执行函数
	static void *Manager(void *lpThreadPool);    //管理者线程
	bool If_thread_alive(pthread_t tid);

};
