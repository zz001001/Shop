#include "MyTask.h"

TCPKernel *CMyTask::m_Kernel=NULL;

CMyTask::CMyTask(int client_fd,TCPKernel *pKernel)
{
	m_client_fd=client_fd;
	m_Kernel=pKernel;
}
void CMyTask::RunTask()
{
	int nRelReadNum;
	int nPacksize;
	int nTempPacksize;
	int len;
	//先接收包大小
	nRelReadNum=read(m_client_fd,(char *)&nPacksize,sizeof(int));
	cout<<"client_fd:"<<m_client_fd<<"接收包大小："<<nPacksize<<"readNum:"<<nRelReadNum<<endl;
	if(nRelReadNum<=0)
	{
		//认为对端关闭里socket,不太确定是否可以这么判断，先这么写
		close(m_client_fd);
		return;
	}
	//接收数据
	char *pbuffer=new char[nPacksize+1]; //new 一块包大小的缓冲区
	if((len=read(m_client_fd,pbuffer,nPacksize)) < 0)
	{
		perror("readn fail");
		return;
	}
	cout<<"len:"<<len<<endl;

	STRU_REGISTER_RQ *p=(STRU_REGISTER_RQ*)pbuffer;
	cout<<"type:"<<p->m_nType<<"tel:"<<p->m_userid<<endl;
	//调用Kernel指针进行处理
	m_Kernel->DealDate(m_client_fd,pbuffer);

	delete []pbuffer;
	pbuffer=NULL;
}


