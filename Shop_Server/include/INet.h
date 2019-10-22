#pragma once
#include <iostream>

class INet
{
public:
	INet()
	{

	}
	virtual ~INet()
	{

	}
public:
	virtual bool InitNetWork(int port,int threadNum_Min,int threadNum_Max,int threadNum_Ori)=0;
	virtual bool UnInitNetWork()=0;
	virtual bool SendData(int sock,char *szbuf,int nlen)=0;
	virtual bool Wait()=0;
};
