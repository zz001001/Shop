#include "TCPKernel.h"
#include "MySql.h"
#include "Util.h"
#include <iostream>
#include <getopt.h>
#include <string.h>
#include <ctype.h>

using namespace std;

int main(int argc, char *argv[])
{
	handle_for_sigpipe();

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
	
	TCPKernel *pTcpKernel=new TCPKernel;
	if(!pTcpKernel->Open(port,threadNum_Min,threadNum_Max,threadNum_Ori))
	{
		cout<<"服务器初始化失败"<<endl;
	}

	return 0;
}
