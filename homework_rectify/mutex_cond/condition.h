///
/// @file    conditon.h
/// @author  LiuhuiDing@gmail.com
/// @date    2018-07-30 11:48:40
///

#ifndef CONDITION_H_
#define CONDITION_H_
#include <iostream>
#include <pthread.h>

namespace MyPosix
{

class MutexLock;	//类的前向声明，无需在此头文件中引用“mutex.h”头文件，减少头文件交叉引用
class Condition
{
public:
	Condition(MutexLock&);
	~Condition();
	void wait();
	void notify();
	void notifyAll();
private:
	pthread_cond_t cond_;
	MutexLock &mutex_;	//此处应该为引用，Condition类对象不应该对mutex生命周期有影响
	//互斥锁和条件变量相互独立，各自负责自己对象的生命周期
	//但该锁同时与外部锁状态相关联
	//所以应该使用引用方式与外部类对象建立联系，而不应该在类内重新定义锁
};

}


#endif
