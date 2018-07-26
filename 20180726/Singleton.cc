///
/// @file    Singleton.cc
/// @author  LiuhuiDing@gmail.com
/// @date    2018-07-26 16:41:47
///

//单例设计模式
//要求：在内存中只能创建一个对象
//1、该对象不能是栈（全局）对象
//2、该对象只能放在堆中
//
//应用场景
//1、直接替换任意全局对象（变量）
//2、配置文件
//3、词典类
//4、被频繁构建析构的对象

#include <stdio.h>
#include <iostream>
using std::cin;
using std::cout;
using std::endl;

class Singleton
{
public:
	static Singleton *getInstance()	//提供公共接口
	{
		if(NULL == pInstance_)	//判断公共资源是否已经创建
		{
			pInstance_ = new Singleton();	//在类的内部调用构造函数
		}
		return pInstance_;
	}
	static void destroy()
	{
		if(pInstance_)
		{
			delete pInstance_;
		}
	}
	void print()
	{
		cout << "Singleton::print()" << endl;
	}
private:
	Singleton() {cout << "Singleton()" << endl;}
	~Singleton() {cout << "~Singleton()" << endl;}
	static Singleton *pInstance_;
};

Singleton *Singleton::pInstance_ = NULL;

int main(int argc, char **argv)
{
	//构造函数和析构函数私有，以下两种方式都不能创建。
	//Singleton s1;	//栈上创建
	//Singleton *p1 = new Singleton();	//堆上创建
	//利用公共接口进行创建
	Singleton *p1 = Singleton::getInstance();
	Singleton *p2 = Singleton::getInstance();
	printf("p1 = %p\n", p1);
	printf("p2 = %p\n", p2);
	Singleton::getInstance()->print();
	//delete p1;//析构函数私有化，无法编译通过
	Singleton::destroy();	//利用公共接口进行销毁
	return 0;
}
