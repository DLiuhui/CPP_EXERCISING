 ///
 /// @file    static_cast.cpp
 /// @author  LiuhuiDing@gmail.com
 /// @date    2018-07-24 21:06:42
 ///
//强制类型转换的使用
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
using std::cin;
using std::cout;
using std::endl;

void test0()	//C风格类型转换
{
	int val1 = 10;
	double val2 = (double)val1;
	double val3 = double(val1);
	cout << "val2=" << val2 << " val3=" << val3 << endl;
}

void test1()	//C++风格类型转换
{
	int val1 = 10;
	double val2 = static_cast<double>(val1);
	cout << "val2 = " << val2 << endl;
	//下面这句相当于 int *pint=(int *)malloc(sizeof(int));
	int *pint = static_cast<int *>(malloc(sizeof(int)));
	*pint=1;
	cout << pint << " " << *pint << endl;
	delete pint;
	//const_cast/dynamic_cast/reinterpret_cast
}
int main(int argc, char **argv)
{
	test0();
	test1();
	return 0;
}
