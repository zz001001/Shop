#pragma once
#include "IKernel.h"
#include "MySql.h"
#include <sstream>
#include <iostream>
#include <string>

class TCPKernel;
typedef void (TCPKernel::*PFUN)(int ,char* );

struct ProtocolMap
{
	PackType m_nType;
	PFUN     m_pfun;
};


class TCPKernel :public IKernel
{
public:
	TCPKernel();
	virtual ~TCPKernel();
public:
	bool Open(int port,int threadNum_Min,int threadNum_Max,int threadNum_Ori);
	void Close();
	void DealDate(int sock,char *szbuf);
public:
	void RegisterRq(int sock,char* szbuf);
public:
	MySql m_sql;
};
