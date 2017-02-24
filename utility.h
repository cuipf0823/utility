/*
*  一些实用的类集合
*/
#ifndef COMMON_UTILITY_H
#define COMMON_UTILITY_H

#include <pthread.h>
#include <boost/noncopyable.hpp>

//线程锁
class Mutex : boost::noncopyable
{
public:
	Mutex()
	{
		pthread_mutex_init(&mutex_, NULL);
	}
	~Mutex()
	{
		pthread_mutex_destroy(&mutex_);
	}
	void Lock()
	{
		pthread_mutex_lock(&mutex_);
	}

	void Unlock()
	{
		pthread_mutex_lock(&mutex_);
	}
private:
	pthread_mutex_t mutex_;
};


#endif


