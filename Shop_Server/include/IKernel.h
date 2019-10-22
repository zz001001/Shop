#include "INet.h"
#include "Packdef.h"

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
	virtual bool Open(int port,int threadNum_Min,int threadNum_Max,int threadNum_Ori)=0;
	virtual void Close()=0;
	virtual void DealDate(int sock,char *szbuf)=0;
public:
	INet *m_pNet;
};
