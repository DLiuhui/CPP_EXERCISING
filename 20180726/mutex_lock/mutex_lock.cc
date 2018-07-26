///
/// @file    mutex_lock.cc
/// @author  LiuhuiDing@gmail.com
/// @date    2018-07-26 23:17:42
///

#include "mutex_lock.h"

MutexLock::MutexLock()
{
	pthread_mutex_init(&mutex_, NULL);	//锁初始化
}

void MutexLock::lock()
{
	pthread_mutex_lock(&mutex_);
}

void MutexLock::unlock()
{
	pthread_mutex_unlock(&mutex_);
}

MutexLock::~MutexLock()
{
	pthread_mutex_destroy(&mutex_);	//销毁锁
}

Condition::Condition()
{
	pthread_cond_init(&cond_, NULL);
}

Condition::~Condition()
{
	pthread_cond_destroy(&cond_);
}

void Condition::wait()
{
	pthread_cond_wait(&cond_, &MutexLock::getLock()->mutex_);
}

void Condition::notify()
{
	pthread_cond_signal(&cond_);
}

void Condition::notifyall()
{
	pthread_cond_broadcast(&cond_);
}
