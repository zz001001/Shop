#include "ThreadPool.h"
#include "Util.h"
#include <iostream>
#include <ctype.h>
#include <string.h>

class CMyTask:public CTask
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
		 if((len=readn(m_client_fd,buffer,sizeof(buffer))) >0) 
		{
			int j=0;
			while(len > j)
			{
				buffer[j]=toupper(buffer[j]);
				j++;
			}
			writen(m_client_fd,buffer,len);
			bzero(&buffer,sizeof(buffer));
		}  
		cout<<"cllent_fd:"<<m_client_fd<<endl;
	}   
public:
	int m_client_fd;
	int len;
	char buffer[4096];

};

