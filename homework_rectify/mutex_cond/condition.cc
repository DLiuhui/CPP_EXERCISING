///
/// @file    condition.cc
/// @author  LiuhuiDing@gmail.com
/// @date    2018-07-30 12:01:59
///

#include "condition.h"
#include "mutexlock.h"

namespace MyPosix
{

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
