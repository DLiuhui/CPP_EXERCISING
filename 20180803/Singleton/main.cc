///
/// @file    main.cc
/// @author  LiuhuiDing@gmail.com
/// @date    2018-08-03 20:18:12
///

#include "singleton.h"
#include "posix.h"
#include <pthread.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <string>
#include <iostream>
using std::cin;
using std::cout;
using std::endl;
using std::string;
using namespace WdCoding;

MyPosix::MutexLock glock;
MyPosix::Condition gcondition(glock);

class Computer
{
	public:
		Computer():
			_name(string()), _price(0)
		{
			cout << "Computer()" << endl;
		}
		Computer(const string &s, double price):
			_name(s), _price(price)
		{
			cout << "Computer(string, double)" << endl;
		}
		~Computer()
		{
			cout << "~Computer()" << endl;
		}
		void print() const
		{
			cout << "Computer:" << _name << " " << _price << endl;
		}
		void priceInc()
		{
			_price += 500;
		}
	private:
		string _name;
		double _price;
		
};

class Point
{
	public:
		Point():
			_dx(0), _dy(0)
		{
			cout << "Point()" << endl;
		}
		Point(double x, double y):
			_dx(x), _dy(y)
		{
			cout << "Point(double, double)" << endl;
		}
		~Point()
		{
			cout << "~Point()" << endl;
		}
		void print() const
		{
			cout << "Point:" << _dx << " " << _dy << endl;
		}
		void go_next()
		{
			++_dx;
			++_dy;
		}
		bool isDestination() const
		{
			return (_dx >= 15 || _dy >= 15)?true:false;
		}
	private:
		double _dx;
		double _dy;
};

struct Resource
{
	Computer *computer;
	Point *point;
	int wheel;
	int tag;
	bool thread_ready;
	Resource():
		computer(Singleton<Computer>::getInstance("Lenovo", 8888.8)),
		point(Singleton<Point>::getInstance(3.33, 4.44)),
		wheel(0), tag(0), thread_ready(false)
	{}
	~Resource() = default;
};

template <typename ...Args>
void print(Args ...args)
{
	printf(std::forward<Args>(args)...);
}

void *pfun(void *p)
{
	Resource *package = (Resource *)p;	//取得资源
	package->thread_ready = true;
	while(1)
	{
		while(package->tag != (package->wheel % 3));
		MyPosix::MutexLockGuard guard(glock);
		if(package->point->isDestination())
		{
			pthread_exit(NULL);
		}
		package->computer->priceInc();
		package->point->go_next();
		cout << package->tag << ": ";
		package->computer->print();
		++package->wheel;
		cout << package->wheel << endl;
		sleep(1);
	}
}

int main(int argc, char **argv)
{
	Resource package;	//公共资源
	print("This is my %s %d\n", "fdsfd", 89);
	pthread_t pid[3];	//3线程
	for(int i = 0; i < 3; i++)
	{
		package.tag = i;
		pthread_create(&pid[i], NULL, pfun, &package);
		while(!package.thread_ready);	//等待子线程就绪
		package.thread_ready = false;
	}
	for(int i = 0; i < 3; i++)
	{
		pthread_join(pid[i], NULL);
	}
	package.computer->print();
	package.point->print();

	return 0;
}
