///
/// @file    heap_only.cc
/// @author  LiuhuiDing@gmail.com
/// @date    2018-07-27 21:03:10
///

//目标：只能生成堆对象
#include <stdio.h>
#include <iostream>
using std::cin;
using std::cout;
using std::endl;
using std::string;

class Student
{
public:
	Student() = default;
	Student(const int i, const string &s):
		id_(i), name_(s)
	{}
	Student(const Student &stu):
		id_(stu.id_), name_(stu.name_)
	{}
	void print() const
	{
		cout << id_ << " " << name_ << endl;
	}
	void* operator new(size_t class_size)
	{
		void *ptr = malloc(class_size);
		return ptr;
	}
	void operator delete(void *p)
	{
		free(p);
	}
	void destroy()
	{
		delete this;
	}
private:
	~Student() = default;
	int id_;
	string name_;

};
int main(int argc, char **argv)
{
	Student *pstu = new Student(12, "ddrh");	//此处无法编译通过
	//Student stu(1221321, "hahah");	//此处编译无法通过
	pstu->print();
	pstu->destroy();
	return 0;
}
