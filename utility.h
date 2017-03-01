/*
*  一些实用的类集合
*/
#ifndef COMMON_UTILITY_H
#define COMMON_UTILITY_H

#include <pthread.h>
#include <boost/noncopyable.hpp>

//线程锁
class MutexLock : boost::noncopyable
{
public:
	MutexLock()
	{
		pthread_mutex_init(&mutex_, NULL);
	}
	~MutexLock()
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

	pthread_mutex_t* GetThreadMutex()
	{
		return &mutex_;
	}

private:
	pthread_mutex_t mutex_;
};

class MutexLockGuard : boost::noncopyable
{
public:
	explicit MutexLockGuard(MutexLock& mutex) : mutex_(mutex)
	{
		mutex_.Lock();
	}
	~MutexLockGuard()
	{
		mutex_.Unlock();
	}
private:
	MutexLock& mutex_; 
};

/*
* 条件变量
*/
class Condition : boost::noncopyable
{
public:
	explicit Condition(MutexLock& mutex) :mutex_(mutex)
	{
		pthread_cond_init(&pcond_, NULL);
	}
	~Condition()
	{
		pthread_cond_destroy(&pcond_);
	}
	void Wait()
	{
		pthread_cond_wait(&pcond_, mutex_.GetThreadMutex());
	}
	void Notify()
	{
		pthread_cond_signal(&pcond_);
	}
	void NotifyAll()
	{
		pthread_cond_broadcast(&pcond_);
	}

private:
	pthread_cond_t pcond_;
	MutexLock& mutex_;
};



#endif


