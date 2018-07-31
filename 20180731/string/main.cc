///
/// @file    main.cc
/// @author  LiuhuiDing@gmail.com
/// @date    2018-07-31 21:35:08
///
#include "string.h"
#include <iostream>
using std::cin;
using std::cout;
using std::endl;
using MyStd::String;
int main(int argc, char **argv)
{
	String a("aaa");
	String b;
	b = "bbb";
	String c;
	cout << "input c:";
	cin >> c;
	cout << a << " " << b << " " << c << endl;
	c += a;
	cout << "c:" << c << endl;
	String d(b);
	cout << "d:" << d << endl;
	cout << "input d:";
	cin >> d;
	cout << "d:" << d << endl;
	String e("eee");
	e = d + c;
	cout << "e:"<< e << endl;
	String f("fff");
	f = b + "hahaha";
	cout << "f:" << f << endl;
	cout << f[0] << f[1] << f[5] << endl;
	return 0;
}
