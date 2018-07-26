 ///
 /// @file    class_size.cc
 /// @author  LiuhuiDing@gmail.com
 /// @date    2018-07-26 15:46:54
 ///

#include <stdio.h>
#include <iostream>
using std::cin;
using std::cout;
using std::endl;

class cex
{
public:
	cex():
		f(b), g(d)
	{}
	void print() const	//成员函数定义，普通成员函数不影响对象大小
	{
		printf("%p\n%p\n%p\n%p\n", &a, &b, &c, &d);
		for(int i = 0; i < 5; i++)
		{
			printf("%p ", &e[i]);
		}
		printf("\n");
		printf("%p\n%p\n%p\n", &f,&g, &h);
	}
private:
	//类型，类型大小，实际存储空间占用
	int a;	//int 4 4
	char b;	//char 1 1+3(浪费)
	float c;	//float 4 4+4(浪费)
	double d;	//double 8 8
	short e[5];	//short 2*5 8(e[0~3])+2(e[4])+4(数组大小)+2(浪费)
	char &f;	//引用当成指针维护	8(64位机指针大小)
	double &g;	//8(64位机指针大小)
	static int h;	//公共成员，公共内存，不影响类对象大小
};

int cex::h = 10;

int main(int argc, char **argv)
{
	cex c;
	printf("%p\n", &c);
	cout << "size:" << sizeof(c) << endl;
	c.print();
	cex ca[2];
	cout << "size2:" << sizeof(ca) << endl;
	printf("%p\n", &ca[0]);
	printf("%p\n", &ca[1]);
	cout << "size3:" << sizeof(cex) << endl;
	return 0;
}
