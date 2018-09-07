///
/// @file    main.cc
/// @author  LiuhuiDing@gmail.com
/// @date    2018-07-30 12:10:01
///
#include "mutexlock.h"
#include "condition.h"
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <string>
using std::cin;
using std::cout;
using std::endl;

//全局变量应该禁止复制操作，
//可以在类内禁止拷贝构造函数和=赋值函数
MyPosix::MutexLock g_lock;
MyPosix::Condition g_condition(g_lock);

struct package
{
	bool flag;
	int sum;
};

void *thread_func1(void *p)
{
	package *bag = (package*)p;
	while(1)
	{
		//如果线程在解锁操作之前就退出了，互斥锁未解开
		//此时很可能就会造成其它线程死锁
		//可以利用类的特性
		//定义一个mutexGuard保护类
		//类内的构造函数负责加锁
		//类的析构函数负责解锁
		//这样可以保证在线程代码块内不论何处退出
		//都会调用解锁（mutex——guard对象退出被销毁时调用析构函数）
		MyPosix::MutexLockGuard mutexlock(g_lock);
		while(bag->flag && bag->sum != 0)
		{
			g_condition.wait();	//使用while，防止因为异常信号唤醒线程
		}
		if(bag->sum == 0)
		{
			g_condition.notify();
			pthread_exit(NULL);
		}
		bag->sum--;
		bag->flag = true;
		cout << "1." << bag->sum << endl;
		sleep(1);
		g_condition.notify();
	}
}

void *thread_func2(void *p)
{
	package *bag = (package*)p;
	while(1)
	{
		MyPosix::MutexLockGuard mutexlock(g_lock);
		while(!bag->flag && bag->sum != 0)
		{
			g_condition.wait();
		}
		if(bag->sum == 0)
		{
			g_condition.notify();
			pthread_exit(NULL);
		}
		bag->sum--;
		bag->flag = false;
		cout << "2." << bag->sum << endl;
		sleep(1);
		g_condition.notify();
	}
}

int main(int argc, char **argv)
{
	pthread_t pid[2];
	package bag = {true, 10};
	pthread_create(&pid[0], NULL, thread_func1, &bag);
	pthread_create(&pid[1], NULL, thread_func2, &bag);
	pthread_join(pid[0], NULL);
	pthread_join(pid[1], NULL);
	cout << "over" << endl;
	return 0;
}
