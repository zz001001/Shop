#include "stdafx.h"

#include"TCPKernel.h"
#include"TCPNet.h"
#include"zhiboAuthor.h"




TCPKernel ::TCPKernel()
{
	pINet=new TCPNet(this);
}
	
TCPKernel :: ~TCPKernel()
{
	if(pINet)
	{
		delete pINet;
		pINet=NULL;
	}
}


bool TCPKernel ::Connect()
{

	if(!pINet->ConnectServer())
		return false;
	
	return true;
}

void TCPKernel ::DisConnect()
{

	pINet->DisConnectServer();
}

bool TCPKernel ::SendData(char* szbuf,int nlen)
{
	pINet->SendData(szbuf,nlen);
	return true;
}

protcolmap m_procol[]={
	{_DEF_PROTOCOL_REGISTER_RS,&TCPKernel ::RegisterRs},
	{0,0}
};

void TCPKernel ::RegisterRs(char* szbuf)
{
	STRU_REGISTER_RS *pSrs=(STRU_REGISTER_RS *)szbuf;
	TCHAR *pResult=NULL;
	if(pSrs->m_szResult== _register_fail)
	{
		pResult=_T("_register_exist");
	}
	else
	{
		pResult=_T("_register_success");
	}
	MessageBox(NULL,pResult,_T("tip"),MB_OK);
}
void TCPKernel ::DealDate(char *buffer)  //哪个sock,传过来的什么数据
{
	//处理数据
	PackType *ptype=(PackType *)buffer;
	int i=0;
	while(1)
	{
		if(m_procol[i].m_nType==*ptype)
		{
			(this->*m_procol[i].m_pfun) (buffer);
		}
		else if(m_procol[i].m_nType==0 && m_procol[i].m_pfun==0)
		{
			break;
		}
		i++;
	}
}