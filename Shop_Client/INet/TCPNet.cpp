#include "stdafx.h"
#include "TCPNet.h"
#include"packdef.h"

bool  TCPNet::m_bFlagQuit = true;
TCPKernel* TCPNet::m_pKernel=NULL;

TCPNet::TCPNet(TCPKernel* pKernel)
{
	m_sockClient = NULL;
	m_pKernel=pKernel;

}


TCPNet::~TCPNet(void)
{
}
bool TCPNet::ConnectServer()
{
	//1.选择种类 -- 
	WORD wVersionRequested;
    WSADATA wsaData;
    int err;

/* Use the MAKEWORD(lowbyte, highbyte) macro declared in Windef.h */
    wVersionRequested = MAKEWORD(2, 2);

    err = WSAStartup(wVersionRequested, &wsaData);
    if (err != 0) {
        /* Tell the user that we could not find a usable */
        /* Winsock DLL.                                  */
       // printf("WSAStartup failed with error: %d\n", err);
        return false;
    }


    if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2) {
        /* Tell the user that we could not find a usable */
        /* WinSock DLL.                                  */
       // printf("Could not find a usable version of Winsock.dll\n");
        DisConnectServer();
        return false;
    }
   
        

	//2.雇佣店长 -- socket 
	m_sockClient = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP );
	if(m_sockClient == INVALID_SOCKET )
	{
		DisConnectServer();
		 return false;
	}
	//3.选址 --- 
	sockaddr_in  addrServer;
	addrServer.sin_family = AF_INET;
	addrServer.sin_addr.S_un.S_addr = inet_addr(SERVERIP);
	addrServer.sin_port = htons(_DEFPORT);
	if(SOCKET_ERROR ==connect(m_sockClient,(const sockaddr*)&addrServer,sizeof(addrServer)))
	{
		 DisConnectServer();
		 return false;
	}
	
	//5.创建线程
	m_hThreadRecv = (HANDLE)_beginthreadex(NULL,0,&ThreadRecv,this,0,0);
	
	return true;
}


unsigned _stdcall TCPNet::ThreadRecv( void * lpvoid)
{
	TCPNet *pThis=(TCPNet *)lpvoid;
	char szbuf[_DEFSIZE] = {0};
	 int nRelReadNum; 
	 int nPacksize;
	 int nTempPacksize;
	 char *pbuffer=NULL;

	while(TCPNet::m_bFlagQuit)
	{
		//在发送数据之前先发送包大小，防止粘包问题

		//先接收包大小
		nRelReadNum =  recv(pThis->m_sockClient,(char *)&nPacksize,sizeof(int),0); //将包大小放在nPacksize里面
		 //接收包内容

	   if(nRelReadNum <=0)
	  {
		  //是不是服务器关闭
		  if(WSAECONNRESET  == GetLastError())
		  {
			  break;
		  }
		  continue;
	  }
	 //接收数据
	nTempPacksize=nPacksize; //记录还能装入多少数据
	pbuffer=new char[nTempPacksize]; //new一块包大小的缓冲区
	int noffsize=0; //偏移量
	while(nTempPacksize)
	{
		 nRelReadNum =  recv(pThis->m_sockClient,pbuffer+noffsize,nTempPacksize,0);
		if(nRelReadNum>0)
		{
			noffsize+=nRelReadNum;
			nTempPacksize-=nRelReadNum;
		}
	}

    //处理数据
	TCPNet::m_pKernel->DealDate(pbuffer);  //将传给sockwaiter的数据交给kernel处理
	
	delete []pbuffer;
	pbuffer=NULL;

	}
	return 0;
}


void TCPNet::DisConnectServer()
{
	m_bFlagQuit = false;
	if(m_hThreadRecv )
	{
		if(WAIT_TIMEOUT == WaitForSingleObject(m_hThreadRecv,100))
			TerminateThread(m_hThreadRecv,-1);
		
		CloseHandle(m_hThreadRecv);
		m_hThreadRecv = NULL;

	
	}
	
	WSACleanup();
	if(m_sockClient)
	{
		closesocket(m_sockClient);
		m_sockClient = NULL;
	}
}

bool TCPNet::SendData(char* szbuf,int nlen)
{
	if(!szbuf||nlen<=0)
	{
		return false;
	}

	//在发送数据之前先发送包大小，防止粘包问题
	if(send(m_sockClient,(char *)&nlen,sizeof(nlen),0)<0)  //先发送包大小
	{
		return false;
	}
	if(send(m_sockClient,szbuf,nlen,0)<0)
		return false;
	
	return true;
}