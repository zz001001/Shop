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

	//��������
	int opt;
	const char *str="t:p:";
	while((opt=getopt(argc,argv,str))!=-1)
	{   
		//getoptΪ���������ѡ��ĺ���
		//���argv�н�����optstring��������ѡ���ַ����򷵻ظ��ַ��������ѡ��ָ���˲�������ȫ�ֱ���optargָ��ò�����
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
		cout<<"��������ʼ��ʧ��"<<endl;
	}

	return 0;
}
