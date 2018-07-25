 ///
 /// @file    reference.cpp
 /// @author  LiuhuiDing@gmail.com
 /// @date    2018-07-24 20:14:31
 ///
 
#include <iostream>
#include <stdio.h>
using std::cin;
using std::cout;
using std::endl;

void test0()
{
	int number = 10;
	int &ref = number;
	ref = 100;
	cout << "number=" << number << endl;
	cout << "ref=" << ref << endl;
	printf("number=%p\n", &number);
	printf("&ref=%p\n", &ref);	//ref的地址同number一样，说明ref实体其实就是number，ref是number别名
	const int &ref2 = 18;	//const引用可以绑定到右值（不能取地址）
	cout << "ref2=" << ref2 << endl;	//ref2=18
	printf("&ref2=%p\n", &ref2);	//可以取到地址
	//int &ref3 = 15;	//引用类型初始值必须是一个对象
	//printf("ref3=%p\n", &ref3);
}

int fun0()
{
	int number = 10;
	return number;	
	//执行return，会执行复制
	//如果返回值是类则会执行拷贝复制
}

int arr[5] = {1,2,3,4,5};

//引用作为函数返回值，返回的变量其生命周期要是大于函数的
//在执行return时未进行复制，所以执行效率也会更高
//就必须注意不能返回局部变量的引用
int &fun1(int idx)
{
	return arr[idx];
}

//返回了局部变量的引用
/*
int &fun2()
{
	int number = 10;
	return number;	//number在函数结束后，所占空间被释放
	//不能作为返回值
}
*/
//不能返回一个指向局部变量的指针
/*
int *fun3()
{
	int number = 10;
	return &number;
}
*/

//不要轻易返回一个堆空间变量的引用
//除非已经有了回收内存的策略
int &fun4()
{
	int *pint = new int(100);
	return *pint;
}

void test2()
{
	int number = fun1(1);
	cout << "number=" << number << endl;
	fun1(0) = 10;	//fun1返回右值，可以通过其修改arr
	cout << "arr[0]=" << arr[0] << endl;
	//cout << "fun4()=" << fun4() << endl;	//引起内存泄露，使用内存泄露检测工具会显示此处内存泄露
	int &ref = fun4();
	cout << "ref=" << ref << endl;
	delete &ref;	//及时清理内存空间
}
int main(int argc, char **argv)
{
	test0();
	test2();
	return 0;
}
