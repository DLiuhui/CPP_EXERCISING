///
/// @file    singleton_v3.0.cc
/// @author  LiuhuiDing@gmail.com
/// @date    2018-08-01 13:36:26
///
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
using std::cin;
using std::cout;
using std::endl;

class Singleton
{
	public:
		//该模式很有用
		static Singleton *getInstance()
		{
			//多线程环境下安全
			pthread_once(&once_, init);	//在线程中该函数只调用一次
			return pInstance_;
		}
		static void init()	//初始化Singleton资源
		{
			if(NULL == pInstance_)
			{
				pInstance_ = new Singleton();
			}
			atexit(destroy);	//注册好退出函数
		}
		static void destroy()
		{
			if(pInstance_)
			{
				delete pInstance_;
			}
		}
	private:
		Singleton() {cout << "Singleton()" << endl;}
		~Singleton() {cout << "~Singleton()" << endl;}
		static Singleton *pInstance_;
		static pthread_once_t once_;
};

Singleton * Singleton::pInstance_ = NULL;	//饿汉模式
pthread_once_t Singleton::once_ = PTHREAD_ONCE_INIT;

int main(int argc, char **argv)
{
	Singleton * p1 = Singleton::getInstance();
	Singleton * p2 = Singleton::getInstance();

	printf("p1 = %p\n", p1);
	printf("p2 = %p\n", p2);
	return 0;
}
