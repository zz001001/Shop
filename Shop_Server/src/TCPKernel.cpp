
#include "TCPKernel.h"
#include "TCPNet.h"

using namespace std;

TCPKernel::TCPKernel()
{
	m_pNet = new TCPNet(this);
}


TCPKernel::~TCPKernel()
{
	if(m_pNet)
	{
		delete m_pNet;
		m_pNet = NULL;
	}
}

bool TCPKernel::Open(int port,int threadNum_Min,int threadNum_Max,int threadNum_Ori)
{
	if(!m_sql.ConnectMySql("localhost","root","123456","Shop"))
		return false;
	if(!m_pNet->InitNetWork(port,threadNum_Min,threadNum_Max,threadNum_Ori))
		return false;
	if(!m_pNet->Wait())
		return false;

	return true;
}
void TCPKernel::Close()
{
	m_sql.DisConnect();
	m_pNet->UnInitNetWork();
}

ProtocolMap  m_ProtocolEntries[]=
{
	{_DEF_PROTOCOL_REGISTER_RQ,&TCPKernel::RegisterRq},
	{0,0}
};

void TCPKernel::DealDate(int sock,char* szbuf)
{
	cout<<"DealDate"<<endl;
	PackType *pType = (PackType*)szbuf;
	//遍历数组
	int i = 0;
	while(1)
	{
		if(m_ProtocolEntries[i].m_nType == *pType)
		{
			cout<<"type:"<<endl;
			(this->*m_ProtocolEntries[i].m_pfun)(sock,szbuf);
		}
		else if(m_ProtocolEntries[i].m_nType ==0 && m_ProtocolEntries[i].m_pfun ==0)
		{
			break;
		}

		i++;
	}
	//处理协议包
}

//注册请求
void TCPKernel::RegisterRq(int sock,char* szbuf)
{
	cout<<"RegisterRq"<<endl;
	STRU_REGISTER_RQ *pssr = (STRU_REGISTER_RQ*)szbuf;
	
	ostringstream szsql_os;
	STRU_REGISTER_RS srr;
	srr.m_nType = _DEF_PROTOCOL_REGISTER_RS;
	srr.m_szResult = _register_fail;
	//cout<<"type"<<pssr->m_nType<<"tel:"<<pssr->m_userid<<"name:"<<pssr->m_szName<<"pass:"<<pssr->m_szPassWord<<"role:"<<pssr->m_brole<<endl;

	if(pssr->m_brole == user_purchaser)
	{
		cout<<"write mysql"<<endl;
		//sprintf_s(szsql,"insert into user_purchaser values(%lld,'%s','%s')",pssr->m_userid,pssr->m_szName,pssr->m_szPassWord);
		szsql_os<<"insert into user_purchaser values(" << pssr->m_userid << ','<<"\'"<<pssr->m_szName<<"\'"<<','<<"\'" << pssr->m_szPassWord <<"\');";
		cout<<szsql_os.str()<<endl;
		if(m_sql.UpdateMySql((char*)szsql_os.str().c_str()))
		{

			cout<<"write mysql success"<<endl;
			srr.m_szResult = _register_success;

		}
	}
	cout<<"RegisterRq return"<<endl;
	m_pNet->SendData(sock,(char*)&srr,sizeof(srr));

}

