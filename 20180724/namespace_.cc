 ///
 /// @file    namespace_.cc
 /// @author  LiuhuiDing@gmail.com
 /// @date    2018-07-24 10:11:02
 ///
 
#include <iostream>
using std::cin;
using std::cout;
using std::endl;
 
int num = 1;

namespace B
{
	extern int num;	//声明num
	void dispB();	//先声明B::中的函数disB
}

namespace A
{
	int num = 10;
	void dispA()
	{
		int num = 11;
		cout << "dispA函数中的num:" << num << endl;	//直接打印dispA()函数内部的num
		cout << "A中的num：" << A::num << endl;	//A与B中都有num，声明 num所在命名空间
		cout << "B中的num：" << B::num << endl;
		cout << "全局num：" << ::num << endl;	//使用全局变量num，声明 匿名空间
		cout << "dispA:" << endl;
		//A空间内嵌套B空间内函数成员或变量
		//可以向将dispB在A空间之前进行声明
		B::dispB();
	}

}


namespace B
{
	int num = 20;
	void dispB()
	{
		int num = 21;
		cout << "dispB中的num" << num << endl;
		cout << "A中的num：" << A::num << endl;
		cout << "B中的num：" << B::num << endl;
		cout << "全局num：" << ::num << endl;
		cout << "dispB" << endl;
	}
}

int main(int argc, char **argv)
{
	A::dispA();
	B::dispB();
	return 0;
}
