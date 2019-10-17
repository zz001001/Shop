#pragma once
#include "noncopyable.h"
#include <pthread.h>
#include <cstdio>



//互斥锁的封装
class MutexLock: noncopyable
{
public:
	MutexLock()
	{   
		pthread_mutex_init(&mutex, NULL);
	}   
	~MutexLock()
	{   
		pthread_mutex_lock(&mutex);
		pthread_mutex_destroy(&mutex);
	}   
	void lock()
	{   
		pthread_mutex_lock(&mutex);
	}   
	void unlock()
	{   
		pthread_mutex_unlock(&mutex);
	}   
	pthread_mutex_t *get()
	{   
		return &mutex;
	}   
private:
	pthread_mutex_t mutex;

		// 友元类不受访问权限影响
private:
	friend class Condition;
};


