#pragma once
#include "noncopyable.h"
#include "MutexLock.h"
#include <errno.h>
#include <cstdint>

class Condition: noncopyable
{
public:
	explicit Condition(MutexLock &_mutex):
		mutex(_mutex)
	{   
		pthread_cond_init(&cond, NULL);
	}   
	~Condition()
	{   
		pthread_cond_destroy(&cond);
	}   
	void wait()
	{   
		pthread_cond_wait(&cond, mutex.get());
		//会先给mutex_解锁，然后等待条件。这两步是原子操作。在条件成立后，它会给mutex_加锁，然后返回，这两步也是原子操作。
	}   
	void notify()
	{   
		pthread_cond_signal(&cond);
	}   
	void notifyAll()
	{   
		pthread_cond_broadcast(&cond);
	}   
private:
	MutexLock &mutex;
	pthread_cond_t cond;
};


