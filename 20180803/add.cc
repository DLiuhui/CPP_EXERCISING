///
/// @file    add.cc
/// @author  LiuhuiDing@gmail.com
/// @date    2018-08-03 14:27:36
///

#include <string>
#include <cstring>
#include <iostream>
using std::cin;
using std::cout;
using std::endl;

//模板内的已知类型参数
//可以默认初始化，作为模板函数下的一个常量使用
//也可以在外部显式实例化，有用户修改其常量
template <typename Type, int kSize = 10>
Type multiply(Type x, Type y)
{
	return x*y*kSize;
}

//函数模板的声明
template <typename Type>
Type add(Type x, Type y);

//函数模板重载
template <typename Type>
Type add(Type a, Type b, Type c)
{
	return a+b+c;
}

//函数模板特化：
//要基于其对应的通用版本函数模板在其之前已经定义
//或者是声明的情况下才能编译通过
template <>
const char * add<const char*>(const char *p1, const char *p2)
{
	cout << "special add" << endl;
	char *ptmp = new char[strlen(p1)+strlen(p2)+1];
	strcpy(ptmp, p1);
	strcat(ptmp, p2);
	return ptmp;
}

/*
//普通函数跟函数模板可以重载
int add(int x, int y)
{	//普通函数的执行会优先于函数模板的执行
		cout << "int add(int,int)" << endl;
			return x + y;
}

double add(double x, double y)
{
		return x + y;
}

char add(char x, char y)
{
		return x + y;
}
*/


int main(int argc, char **argv)
{
	int a = 3, b = 4, c = 5;;
	double d1 = 11.11, d2 = 22.22;
	char c1 = 'A', c2 = 1;
	std::string s1 = "hello";
	std::string s2 = "world";

	const char * p1 = "hello";
	const char * p2 = "world";

	cout << "add(a, b) = " << add(a, b) << endl;//  隐式实例化
	cout << "add(d1, d2) = " << add<double>(d1, d2) << endl; // 显式实例化
	cout << "add(c1, c2) = " << add(c1, c2) << endl;
	cout << "add(a, b, c) = " << add(a, b, c) << endl;
	cout << "add(s1, s2) = " << add(s1, s2) << endl;
	cout << "add(p1, p2) = " << add(p1, p2) << endl;	//会调用add的特例化
	cout << endl;

	//在模板之前，是不能在函数调用时改变常量的值；
	//	//有了模板之后，可以在实参传递时改变常量的值
	cout << "multiply(a, b) = " << multiply<int, 5>(a, b) << endl;
	cout << multiply(a, b) << endl;
	return 0;
}

template <typename Type>
Type add(Type x, Type y)
{
	cout << "Type add(Type, Type)" << endl;
	return x+y;
}
