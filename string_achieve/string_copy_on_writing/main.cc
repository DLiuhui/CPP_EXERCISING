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
	/*
	String a("aaa");
	cout << "a-r:" << a.getRefcnt() << endl;
	String b;
	b = "bbb";
	cout << "b-r:" << b.getRefcnt() << endl;
	String c;
	cout << "input c:";
	cin >> c;
	cout << a << " " << b << " " << c << endl;
	cout << "c-r:" << c.getRefcnt() << endl;
	c += a;
	cout << "c:" << c << endl;
	cout << "a-r:" << a.getRefcnt() << endl;
	cout << "c-r:" << c.getRefcnt() << endl;
	String d(b);
	cout << "d:" << d << endl;
	cout << "d-r:" << d.getRefcnt() << endl;
	cout << "b-r:" << b.getRefcnt() << endl;
	cout << "input d:";
	cin >> d;
	cout << "d:" << d << endl;
	cout << "d-r:" << d.getRefcnt() << endl;
	cout << "b-r:" << b.getRefcnt() << endl;
	String e("eee");
	cout << "e-r:" << e.getRefcnt() << endl;
	e = d + c;
	cout << "e:"<< e << endl;
	cout << "e-r:" << e.getRefcnt() << endl;
	String f("fff");
	cout << "f-r:" << f.getRefcnt() << endl;
	f = b + "hahaha";
	cout << "f-r:" << f.getRefcnt() << endl;
	cout << "f:" << f << endl;
	cout << f[0] << f[1] << f[5] << endl;
	*/
	String s1 = "hello,world";
	String s2 = s1;
	String s3 = s2;
	cout << "sizeof(string) = " << sizeof(String) << endl;
	cout << "s1 = " << s1 << endl;
	cout << "s2 = " << s2 << endl;
	cout << "s3 = " << s3 << endl;
	cout << "s1[0] = " << s1[0] << endl;
	cout << "s2[3] = " << s2[3] << endl;
	printf("s1'address = %p\n", s1.c_str());
	printf("s2'address = %p\n", s2.c_str());
	printf("s3'address = %p\n\n", s3.c_str());

	s1[0] = 'X';
	cout << "执行修改操作:" << endl;
	cout << "s1 = " << s1 << endl;
	cout << "s2 = " << s2 << endl;
	cout << "s3 = " << s3 << endl;
	printf("s1'address = %p\n", s1.c_str());
	printf("s2'address = %p\n", s2.c_str());
	printf("s3'address = %p\n\n", s3.c_str());
	return 0;
}
