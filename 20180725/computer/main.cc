 ///
 /// @file    main.cc
 /// @author  LiuhuiDing@gmail.com
 /// @date    2018-07-25 15:37:55
 ///
 
#include "computer.h"
#include <iostream>
#include <string>
using std::cin;
using std::cout;
using std::endl;
using std::string;
 
int main(int argc, char **argv)
{
	Computer com1;
	com1.setBrand("Lenovo");
	com1.setPrice(10000);
	com1.print();
	com1.~Computer();	//显示调用析构函数，并不真正销毁对象
	//只执行析构函数内的语句，在函数结束对象销毁时会再次调用析构函数
	//不建议显示调用析构函数
	com1.print();
	Computer com2("Apple", 5999.99);
	com2.print();
	com2.~Computer();
	Computer com3;
	com3.print();
	return 0;
}
