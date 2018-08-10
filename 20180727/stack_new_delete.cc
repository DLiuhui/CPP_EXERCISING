///
/// @file    student.cc
/// @author  LiuhuiDing@gmail.com
/// @date    2018-07-27 10:20:47
///
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <string>
using std::cin;
using std::cout;
using std::endl;

//需求：只能生成栈对象，不能生成堆对象
//该情况必须定义类版本的new 和 delete，不然为类指针用new、delete申请堆空间会调用全局版本的new 和 delete
//	调用new A()发生error
//	将类内重载new 改为私有->类对象new方法无法显式调用
//	考虑到A *p = a可以继续生成堆对象
//	将delete改为私有

class Student
{
public:
	Student(int id, const char *name):
		id_(id), name_(new char[strlen(name)+1]())
	{
		strcpy(name_, name);
		cout << "Student()" << endl;
	}
	~Student()
	{
		delete []name_;
		cout << "~Student()" << endl;
	}
	void print() const
	{
		cout <<"id:" << id_ << " name:" << name_ << endl;
	}
private:
	//重定义开辟空间的方式
	void *operator new(size_t sz)
	{
		cout << "operator new" << endl;
		cout << sz << endl;
		void *ret = malloc(sz);
		return ret;
	}
	void operator delete(void *ptr)
	{
		free(ptr);
		cout << "operator delete" << endl;
	}
	int id_;
	char *name_;
};
int main(int argc, char **argv)
{
	//Student *pstu = new Student(100, "xiongda");	//new私有化，无法显式调用
	//pstu->print();
	//delete pstu;	//delete私有化，无法显式调用
	Student s(101, "Haa");
	s.print();
	return 0;
}
