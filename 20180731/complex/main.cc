///
/// @file    main.cc
/// @author  LiuhuiDing@gmail.com
/// @date    2018-07-31 16:06:05
///
#include "complex.h"
#include <iostream>
using std::cin;
using std::cout;
using std::endl;
using namespace wdCoding;
int main(int argc, char **argv)
{
	ComplexNumber a(3.00, 4.00);
	cout << module(a) << endl;
	ComplexNumber b;
	cin >> b;
	cout << a + b << endl;
	cout << a - b << endl;
	cout << a * b << endl;
	cout << a / b << endl;
	cout << ++a << endl;
	cout << a++ << endl;

	return 0;
}
