


#ifndef  _IKERNEL_H
#define _IKERNEL_H

#include"INet.h"

class IKernel
{
public:
	IKernel()
	{

	}
	virtual ~IKernel()
	{

	}
public:
	virtual bool Connect()=0;
	virtual void DisConnect()=0;
	virtual void DealDate(char *buffer)=0;  //�ĸ�sock,��������ʲô����
	virtual bool SendData(char* szbuf,int nlen)=0;
public:
	INet *pINet;
	
};


#endif
