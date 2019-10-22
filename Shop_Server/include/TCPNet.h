#pragma once
#include "INet.h"
#include "TCPKernel.h"
#include "ThreadPool.h"
#include "Epoll.h"
#include "Util.h"
#include "MyTask.h"
#include <iostream>
#include <string.h>
#include <ctype.h>

using namespace std;

class TCPNet:public INet
{
public:
	TCPNet(TCPKernel * pKernel);
	virtual ~TCPNet();
public:
	bool InitNetWork(int port,int threadNum_Min,int threadNum_Max,int threadNum_Ori);
	bool UnInitNetWork();
	bool SendData(int sock,char* szbuf,int nlen);
	bool Wait();
public:
	static TCPKernel *m_pKernel;
	int m_server_fd;
	CMyThreadPool MyThreadPool;
	Epoll MyEpoll;

};
