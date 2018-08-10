///
/// @file    singleton_v2.0.cc
/// @author  LiuhuiDing@gmail.com
/// @date    2018-08-01 10:20:22
///

#include <iostream>
#include <string>
using std::cin;
using std::cout;
using std::endl;
using std::string;
//实现Singleton的自动空间释放
class Singleton
{
public:
	static Singleton *getInstance()
	{
		//在多线程环境下不是线程安全
		//可能两个线程同时拿到NULL的pInstance_
		//在堆上创建两块空间
		//解决方式
		//1、加锁：但是存在无效锁，pInstance_不为空的话会额外指向加解锁，牺牲效率
		//2、全局Singleton::getInstance，饱汉模式
		if(NULL == pInstance_)
		{
			pInstance_ = new Singleton();
		}
		return pInstance_;
	}
	static void destroy()
	{
		if(pInstance_)
			delete pInstance_;
	}
private:
	/*
	//使用嵌套类完成自动释放
	class AutoRelease	//只为Singleton提供服务
	{
	public:
		AutoRelease() {cout << "AutoRelease()" << endl;}
		~AutoRelease()
		{
			if(pInstance_)	//可以直接使用Singleton的静态变量
				//如果pInstance编程非静态，此处就无法直接调用，需要传参
				delete pInstance_;
			cout << "~AutoRelease" << endl;
		}
	};
	*/
	Singleton() {cout << "Singleton" << endl;}
	~Singleton() {cout << "~Singleton" << endl;}
	static Singleton *pInstance_;
	//static AutoRelease ar_;
};


//使用外部保护类保护Singleton类，实现自动释放
class UseSingleton
{
public:
	UseSingleton():
		ptr(Singleton::getInstance())
	{}
	~UseSingleton()
	{
		ptr->destroy();
	}
	//Singleton方法接口
	//type func()
	//{
	//ptr->Singleton::func();
	//}
private:
	Singleton *ptr;
};



//懒汉模式，懒加载，如果程序不需要调用Singleton里的资源可以节省空间
//Singleton *Singleton::pInstance = NULL;	//懒汉模式->懒加载
//饱汉模式，直接预分配好资源，能够做到多线程安全，线程内无需加解锁
//但是如程序不使用Singleton资源会浪费空间
Singleton *Singleton::pInstance_ = NULL;
//Singleton *Singleton::pInstance_ = getInstance();
//Singleton::AutoRelease Singleton::ar_;
int main(int argc, char **argv)
{
	UseSingleton use;
	return 0;
}
