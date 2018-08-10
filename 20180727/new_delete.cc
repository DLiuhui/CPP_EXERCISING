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

void *operator new(size_t sz)
{
	cout << "all new:" << sz << endl;
	void *ret = malloc(sz);
	cout << "all new end" << endl;
	return ret;
}

void operator delete(void *ret)
{
	cout << "all delete" << endl;
	free(ret);
	cout << "all delete end" << endl;
}

class Student
{
public:
	Student(int id, const char *name):
		id_(id), name_(new char[strlen(name)+1])	//此处，new会调用全局版本的new
	{
		cout << "Student() begin" << endl;
		strcpy(name_, name);
		cout << "Student() end" << endl;
	}
	~Student()
	{
		cout << "~Student() begin" << endl;
		delete []name_;	//此处，会调用全局版本的delete
		cout << "~Student()" << endl;
	}
	void print() const
	{
		cout <<"id:" << id_ << " name:" << name_ << endl;
	}
	//重定义开辟空间的方式
	void *operator new(size_t sz)
	{
		cout << "stu new begin" << endl;
		cout << sz << endl;
		void *ret = malloc(sz);
		cout << "stu new end" << endl;
		return ret;
	}
	void operator delete(void *ptr)
	{
		cout << "stu delete begin" << endl;
		free(ptr);
		cout << "stu delete end" << endl;
	}
private:
	int id_;
	char *name_;
};
int main(int argc, char **argv)
{
	Student *pstu = new Student(100, "xiongda");	//调用stu版本的new
	pstu->print();
	delete pstu;	//调用stu版本的delete
	return 0;
}
