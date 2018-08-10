///
/// @file    posix.h
/// @author  LiuhuiDing@gmail.com
/// @date    2018-08-03 21:22:45
///

#ifndef POSIX_H_
#define POSIX_H_
#include <stdlib.h>
#include <pthread.h>
namespace MyPosix
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

	class MutexLockGuard	//互斥锁保护类，使用锁时在代码块内使用
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

	class Condition
	{
		public:
			Condition(MutexLock&);
			~Condition();
			Condition & operator=(const Condition &) = delete;
			Condition(const Condition &) = delete;
			void wait();
			void notify();
			void notifyAll();
		private:
			pthread_cond_t cond_;
			MutexLock &mutex_;
	};

};


#endif
