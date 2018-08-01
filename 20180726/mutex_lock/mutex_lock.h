///
/// @file    mutex_lock.h
/// @author  LiuhuiDing@gmail.com
/// @date    2018-07-26 23:11:14
///

#ifndef MUTEX_LOCK_H_
#define MUTEX_LOCK_H_
#include <pthread.h>
#include <iostream>
class MutexLock
{
public:
	void lock();
	void unlock();
	pthread_mutex_t & mutex();
	static MutexLock* getLock()	//取得锁
	{
		if(NULL == pmutex_lock_)
		{
			pmutex_lock_ = new MutexLock();
		}
		return pmutex_lock_;
	}
	static void destroy()
	{
		if(pmutex_lock_)
		{
			delete pmutex_lock_;
		}
	}
private:
	MutexLock();
	~MutexLock();
	static MutexLock *pmutex_lock_;
	pthread_mutex_t mutex_;
};

class Condition
{
public:
	void wait();
	void notify();
	void notifyAll();
	pthread_cond_t & cond();	//取得锁
	static Condition* getCond()
	{
		if(NULL == pcondition_)
		{
			pcondition_ = new Condition();
		}
		return pcondition_;
	}
	static void destroy()
	{
		if(pcondition_)
		{
			delete pcondition_;
		}
	}
private:
	Condition();
	~Condition();
	static Condition *pcondition_;
	pthread_cond_t cond_;
};

#endif
