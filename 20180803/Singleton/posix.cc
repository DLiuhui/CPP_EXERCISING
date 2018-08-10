///
/// @file    posix.cc
/// @author  LiuhuiDing@gmail.com
/// @date    2018-08-03 21:27:30
///

#include "posix.h"

namespace MyPosix
{
	MutexLock::MutexLock()
	{
		pthread_mutex_init(&mutex_, NULL);
	}

	MutexLock::~MutexLock()
	{
		pthread_mutex_destroy(&mutex_);
	}

	void MutexLock::lock()
	{
		pthread_mutex_lock(&mutex_);
	}

	void MutexLock::unlock()
	{
		pthread_mutex_unlock(&mutex_);
	}

	Condition::Condition(MutexLock &mutex):
		mutex_(mutex)
	{
		pthread_cond_init(&cond_, NULL);
	}
	Condition::~Condition()
	{
		pthread_cond_destroy(&cond_);
	}
	void Condition::wait()
	{
		pthread_cond_wait(&cond_, &mutex_.getLock());
	}
	void Condition::notify()
	{
		pthread_cond_signal(&cond_);
	}
	void Condition::notifyAll()
	{
		pthread_cond_broadcast(&cond_);
	}
}
