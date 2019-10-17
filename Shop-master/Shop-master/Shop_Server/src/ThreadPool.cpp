#include "ThreadPool.h"

CMyThreadPool::CMyThreadPool():m_MutexLock(),m_Condition(m_MutexLock),m_vecThread(20)
{
	m_nMaxThread = 0;
	m_nMinThread = 0;
	m_nRunThread = 0;
	m_nCurrentThread = 0;
	m_bThreadQuit = true;

}

CMyThreadPool::~CMyThreadPool()
{
	DestroyThreadPool();

	m_nMaxThread = 0;
	m_nMinThread = 0;
	m_nRunThread = 0;
	m_nCurrentThread = 0;
	m_bThreadQuit = false;
}

bool CMyThreadPool::CreateThreadPool(__uint32_t nMinThread, __uint32_t nMaxThread,__uint32_t nOriThread )
{
	if(nMinThread > nMaxThread || nOriThread > nMaxThread)
		return false;
	m_nMaxThread=nMaxThread;
	m_nMinThread=nMinThread;
	m_nOriThread=nOriThread;
	
	//创建线程
	for(__uint32_t i=0;i<m_nOriThread && m_nMinThread<=m_nOriThread;i++)
	{
		if((err=pthread_create(&m_vecThread[i],NULL,Threadpro,this))>0)
		{
			cout<<"create thread fail:"<<strerror(err)<<endl;
			return false;
		}
		if((err=pthread_detach(m_vecThread[i]))>0)
		{
			cout<<"set thread detach fail:"<<strerror(err)<<endl;
			return false;
		}
		++m_nCurrentThread;
	}
	//创建管理者线程
	 if((err=pthread_create(&m_managerid,NULL,Manager,this))>0)
	{
		cout<<"create thread fail:"<<strerror(err)<<endl;
		return false;
	}   
	if((err=pthread_detach(m_managerid))>0)
	{
		cout<<"set thread detach fail:"<<strerror(err)<<endl;
		return false;
	}  

	return true;
}

void *CMyThreadPool::Threadpro(void *lpThreadPool)
{
	cout<<"pthread tid:"<<pthread_self()<<endl;
	CMyThreadPool* pThis=(CMyThreadPool*)lpThreadPool;
	CTask *pTemp=NULL;
	while(pThis->m_bThreadQuit)
	{
		pThis->m_MutexLock.lock();
		while(pThis->m_quTask.empty() && pThis->m_bThreadQuit)
		{
			cout<<"pthread wait"<<endl;
			pThis->m_Condition.wait();
		
		}
		pThis->m_nRunThread++;
		
		if(pThis->m_quTask.empty())
		{
			pThis->m_MutexLock.unlock();
			break;
		}
		pTemp=pThis->m_quTask.front();
		pThis->m_quTask.pop();
		pThis->m_MutexLock.unlock();
		//执行任务
		pTemp->RunTask();

		delete pTemp;
		pTemp=NULL;



		pThis->m_MutexLock.lock();
		pThis->m_nRunThread--;
		pThis->m_MutexLock.unlock();
	}

}

void *CMyThreadPool::Manager(void *lpThreadPool)
{
	CMyThreadPool* pThis=(CMyThreadPool*)lpThreadPool;
	int cur,run,err;
	int add=0;
	while(pThis->m_bThreadQuit)
	{
		pThis->m_MutexLock.lock();
		cur=pThis->m_nCurrentThread;
		run=pThis->m_nRunThread;
		pThis->m_MutexLock.unlock();
		
		cout<<"Manager thread: "<<pthread_self()<<"cur thread num: "<<cur<<"run thread num: "<<run<<"run/cur: "<<(float)run/cur*(float)100<<endl;

		//动态扩容
		if((float)run/cur*(float)100 >(float)80 && pThis->m_nMaxThread > cur)
		{
			for(int i=0;i<pThis->m_nMaxThread;i++)
			{
				pThis->m_MutexLock.lock();
				if(pThis->m_vecThread[i]==0 || !pThis->If_thread_alive(pThis->m_vecThread[i]))
				{
					if((err=pthread_create(&pThis->m_vecThread[i],NULL,Threadpro,(void *)pThis))>0)
					{
						cout<<"create thread fail:"<<strerror(err)<<endl;
					}
					if((err=pthread_detach(pThis->m_vecThread[i]))>0)
					{
						cout<<"set thread detach fail:"<<strerror(err)<<endl;
					}
					++pThis->m_nCurrentThread;
					++add;
				}

				if(add==increase)
				{
					 pThis->m_MutexLock.unlock();
					 break;
				}
				pThis->m_MutexLock.unlock();
			}
		}

		//动态缩减
		if(run*2 < cur && cur>pThis->m_nMinThread)
		{
			for(int i=0;i<decrease;i++)
			{
				pThis->m_Condition.notify();
				pThis->m_MutexLock.lock();
				pThis->m_nCurrentThread--;
				pThis->m_MutexLock.unlock();
			}
		}
		sleep(2);
	
	}	
	
}
void CMyThreadPool::DestroyThreadPool()
{
	m_bThreadQuit=false;
	//清空任务
	{
		m_MutexLock.lock();
		if(!m_quTask.empty())
		{
			delete m_quTask.front();
			m_quTask.pop();
		}
	}
	//不需要回收锁和条件变量
	//不需要回收线程资源
}

bool CMyThreadPool::PushTask(CTask* pTask)
{
	if(!pTask)
		return false;
	//投递任务
		m_quTask.push(pTask);
		m_Condition.notify();

	return true;
}

 bool CMyThreadPool::If_thread_alive(pthread_t tid)
 {
	 if((pthread_kill(tid,0))==-1)
	 {
		 if(errno==ESRCH)
			 return false;
	 }
	 else
	 {
		 return true;
	 }
 

 }
