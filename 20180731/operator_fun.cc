///
/// @file    operator_fun.cc
/// @author  LiuhuiDing@gmail.com
/// @date    2018-07-31 17:38:01
///

#include <iostream>
using std::cin;
using std::cout;
using std::endl;
void display()
{
	static int counter = 0;
	cout << "display()" << endl;
	++counter;
}

//利用无成员类实现函数功能
struct Foo
{
	Foo() : counter(0) {}
	int operator()(int x, int y)
	{
		++counter;
		return x * y;
	}

	int operator()(int x, int y, int z)
	{
		return x + y + z;
	}
	int counter;
};

int main(int argc, char **argv)
{
	display();
	Foo foo;
	cout << foo(3,4) << endl;	//重载了函数调用运算符的类创建的对象
	//称为函数对象
	//函数对象携带了状态-》闭包
	//等效于lambda表达式（匿名函数对象）
	cout << foo.counter << endl;
	cout << foo(3,4,5) << endl;
	return 0;
}
