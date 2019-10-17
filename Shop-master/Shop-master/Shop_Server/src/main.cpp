#include "ThreadPool.h"
#include "Epoll.h"
#include "Util.h"
#include "MyTask.h"
#include <iostream>
#include <getopt.h>
#include <string.h>
#include <ctype.h>

using namespace std;

/*  class CMyTask:public CTask
{
public:
	CMyTask(int client_fd)
	{
		m_client_fd=client_fd;
		len=0;
		memset(buffer,0,sizeof(buffer));
	}
	void RunTask()
	{
		if((len=readn(m_client_fd,buffer,sizeof(buffer)) >0)
		{
			int j=0;
			while(len > j)
			{
				buffer[j]=toupper(buffer[j]);
				j++;
			}
			writen(m_client_fd,buffer[j],len);
			bzero(&buffer,sizeof(buffer));
		}
	}
public:
	int m_client_fd;
	int len;
	char buffer[4096];

};*/

int main(int argc, char *argv[])
{
	int threadNum_Max=20;
	int threadNum_Min= 4;
	int threadNum_Ori=0;
	int port = 0; 

	//解析参数
	int opt;
	const char *str="t:p:";
	while((opt=getopt(argc,argv,str))!=-1)
	{   
		//getopt为解析命令可选项的函数
		//如果argv中解析出optstring中描述的选项字符，则返回该字符，如果该选项指定了参数，则全局变量optarg指向该参数；
		switch(opt)
		{
			case 't':
				{
					threadNum_Ori=atoi(optarg);
					break;
				}
			case 'p':
				{
					port=atoi(optarg);
					break;
				}
			default:
				break;
		}
	}   
	
	int server_fd=socket_bind_listen(port);
	int client_fd=0;
	struct sockaddr_in client_addr;
	memset(&client_addr, 0, sizeof(struct sockaddr_in));
	socklen_t client_addr_len = sizeof(client_addr);


	Epoll MyEpoll;
	CMyThreadPool MyThreadPool;
	MyThreadPool.CreateThreadPool(threadNum_Min,threadNum_Max,threadNum_Ori);

	__uint32_t events=EPOLLIN|EPOLLET;
	MyEpoll.Epoll_Add(server_fd,events);

	while(1)
	{
		int count=MyEpoll.Epoll_Wait();
		while(count)
		{
			count--;
			if(MyEpoll.events_[count].data.fd==server_fd)
			{
				if((client_fd=accept(server_fd,(struct sockaddr*)&client_addr, &client_addr_len))<0)
				{
					cout<<"client_fd fail"<<endl;
					break;
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
					break;
				}
			 	CMyTask *MyTask=new CMyTask(MyEpoll.events_[count].data.fd);
				MyThreadPool.PushTask(MyTask);

				sleep(2);

			}
			else if(MyEpoll.events_[count].events & EPOLLOUT)
			{
				cout<<"write"<<endl;
			}

		}

	}

	return 0;
}
