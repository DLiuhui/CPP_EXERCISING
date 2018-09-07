///
/// @file    mutexlock.h
/// @author  LiuhuiDing@gmail.com
/// @date    2018-07-30 11:16:47
///

#ifndef MUTEX_LOCK_H_
#define MUTEX_LOCK_H_
#include <stdio.h>
#include <iostream>
#include <pthread.h>
namespace MyPosix	//此处的命名空间可以关联到其它文件里
{

class MutexLock
{
public:
	MutexLock();
	~MutexLock();
	MutexLock(const MutexLock &mutex) = delete;
	MutexLock & operator=(const MutexLock &rhs) = delete;
	void lock();
	void unlock();
	pthread_mutex_t & getLock() {return mutex_;}
private:
	pthread_mutex_t mutex_;
};

class MutexLockGuard	//互斥锁保护类
{
public:
	MutexLockGuard(MutexLock &mutex)
		:mutex_(mutex)
	{
		mutex_.lock();
	}
	~MutexLockGuard()
	{
		mutex_.unlock();
	}
private:
	MutexLock &mutex_;
};
}

#endif
