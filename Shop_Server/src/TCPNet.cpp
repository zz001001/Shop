#include "TCPNet.h"

TCPKernel *TCPNet::m_pKernel=NULL;

TCPNet::TCPNet(TCPKernel *pKernel):MyThreadPool(),MyEpoll()
{
	m_server_fd=0;
	m_pKernel=pKernel;
}

TCPNet::~TCPNet()
{

}

bool TCPNet::InitNetWork(int port,int threadNum_Min,int threadNum_Max,int threadNum_Ori)
{
	m_server_fd=socket_bind_listen(port);  //获得服务器socket
	MyThreadPool.CreateThreadPool(threadNum_Min,threadNum_Max,threadNum_Ori); //创建线程池

	return true;
}

bool TCPNet::UnInitNetWork()
{
	if(m_server_fd)
	{
		close(m_server_fd);
	}
	return true;
}

bool TCPNet::SendData(int sock,char* szbuf,int nlen)
{
	int len=0;
	if(!szbuf||nlen<=0)
	{
		return false;
	}
	//先发送包大小，防止粘包
	if((len=writen(sock,(char *)&nlen,sizeof(nlen))) < 0)
	{
		return false;
	}
	if((len=writen(sock,szbuf,nlen)) < 0)
	{
		return false;
	}

	return true;

}

bool TCPNet::Wait()
{
	int client_fd=0;
	struct sockaddr_in client_addr;
	memset(&client_addr, 0, sizeof(struct sockaddr_in));
	socklen_t client_addr_len = sizeof(client_addr);

	__uint32_t events=EPOLLIN|EPOLLET;
	MyEpoll.Epoll_Add(m_server_fd,events);
	while(1)
	{
		int count=MyEpoll.Epoll_Wait();
		while(count)
		{
			count--;
			if(MyEpoll.events_[count].data.fd==m_server_fd)
			{
				if((client_fd=accept(m_server_fd,(struct sockaddr*)&client_addr, &client_addr_len))<0)
				{
					cout<<"client_fd fail"<<endl;
					return false;
				}
				__uint32_t events=EPOLLIN|EPOLLET;
				MyEpoll.Epoll_Add(client_fd,events);

				setSocketNonBlocking(client_fd);

			}
			else if(MyEpoll.events_[count].events & EPOLLIN)
			{
				cout<<"have data"<<endl;
				if((client_fd=MyEpoll.events_[count].data.fd) < 0)
				{
					cout<<"connect fail"<<endl;
					return false;
				}
				cout<<"create MyTask"<<endl;
				CMyTask *MyTask=new CMyTask(MyEpoll.events_[count].data.fd,m_pKernel);
				MyThreadPool.PushTask(MyTask);

			}
			else if(MyEpoll.events_[count].events & EPOLLOUT)
			{
				cout<<"write"<<endl;
			}

		}

	}
	return true;

}
