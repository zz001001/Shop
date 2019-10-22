#ifndef  _TCPIKERNEL_H
#define _TCPIKERNEL_H
#include"IKernel.h"
#include"packdef.h"
#include"INet.h"



using namespace std;
class TCPKernel;
typedef void (TCPKernel:: *pfun) (char* szbuf);

struct protcolmap
{
	PackType m_nType;
	pfun m_pfun;
};


class TCPKernel :public IKernel
{
public:
	TCPKernel();
	
	~TCPKernel();
	
public:
	bool Connect();
	void DisConnect();
	void DealDate(char *buffer);  //�ĸ�sock,��������ʲô����
	bool SendData(char* szbuf,int nlen);
public:
	void RegisterRs(char* szbuf); //ע��ظ�


};


#endif
