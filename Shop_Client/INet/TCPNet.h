#ifndef  _TCPNET_H
#define _TCPNET_H

#include"INet.h"
#include"TCPKernel.h"




#define _DEFPORT    8000
#define _DEFSIZE     1024

class TCPNet :public INet
{
public:
	TCPNet(TCPKernel* pKernel);
	virtual ~TCPNet();
public:
	bool ConnectServer();
	void DisConnectServer();
	bool SendData(char* szbuf,int nlen);
public:
	
	static  unsigned _stdcall ThreadRecv( void * );
private:
	SOCKET m_sockClient;
	
	HANDLE m_hThreadRecv;
	static bool   m_bFlagQuit;
	static TCPKernel* m_pKernel;
};


#endif
