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

//需求：只生成堆对象，不能生成栈对象
//	new调用时会调用构造函数
//	delete调用时会调用析构函数
//	可以通过制作接口create和destroy来进行new、delete
//	但是调用create的前提是现在heap创建对象
//	所以只让析构函数私有化，定义销毁堆对象接口destroy

class Student
{
public:
	Student(int id, const char *name):
		id_(id), name_(new char[strlen(name)+1]())
	{
		strcpy(name_, name);
		cout << "Student()" << endl;
	}
	/*
	~Student()
	{
		delete []name_;
		cout << "~Student()" << endl;
	}
	*/
	void print() const
	{
		cout <<"id:" << id_ << " name:" << name_ << endl;
	}
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
	void destroy()
	{
		//this->~Student();	//只执行析构函数内部的delete，释放类对象的数组空间
		//但是堆上类对象空间并未释放，内存泄露
		
		delete this;	//此处不管是调用全局delete还是对象delete都能删除类对象的堆空间
	}
private:
	~Student()
	{
		delete []name_;
		cout << "~Student()" << endl;
	}
	int id_;
	char *name_;
};
int main(int argc, char **argv)
{
	Student *pstu = new Student(100, "xiongda");	//因为构造函数并未私有化，所以不论是全局new函数类的new都能调用成功
	pstu->print();
	pstu->destroy();
	//delete pstu;	//调用全局delete释放new的空间失败，因为delete无法调用私有析构函数
	//此时就需要使用类对象的delete
	//Student s(101, "Haa");
	//s.print();
	return 0;
}
