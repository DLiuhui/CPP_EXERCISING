///
/// @file    mutexlock.cc
/// @author  LiuhuiDing@gmail.com
/// @date    2018-07-30 11:20:29
///

#include "mutexlock.h"
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
}
