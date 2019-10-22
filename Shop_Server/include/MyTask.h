#include "ThreadPool.h"
#include "Util.h"
#include "TCPKernel.h"
#include <iostream>
#include <unistd.h>
#include <ctype.h>
#include <string.h>
#include <error.h>

class CMyTask:public CTask
{
public:
	CMyTask(int client_fd,TCPKernel *pKernel);
	void RunTask();
public:
	int m_client_fd;
	static TCPKernel *m_Kernel;

};

