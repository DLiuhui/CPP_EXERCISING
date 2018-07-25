 ///
 /// @file    main.cc
 /// @author  LiuhuiDing@gmail.com
 /// @date    2018-07-25 15:58:21
 ///

#include "point.h"
#include <iostream>
using std::cin;
using std::cout;
using std::endl;

void test0()
{
	Point pt;
	pt.print();
	Point pt2(1,2);
	pt2.print();
	pt2.~Point();
	int a = 3;
	int b(4);
	cout << "a=" << a << endl;
	cout << "b=" << b << endl;
}
int main(int argc, char **argv)
{
	test0();
	return 0;
}
