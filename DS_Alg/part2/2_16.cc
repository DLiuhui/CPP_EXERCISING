///
/// @file    2_16.cc
/// @author  LiuhuiDing@gmail.com
/// @date    2018-08-07 10:41:52
///

#include <iostream>
using std::cin;
using std::cout;
using std::endl;

static int count = 0;
int gdb1(int m, int n)
{
	++count;
	cout << count << endl;
	return (m==0)?n:gdb1(n%m, m);
}

int gdb2(int m, int n)
{
	++count;
	cout << count << endl;
	if(m<n)
		std::swap(m,n);
	if(n == 0)
		return m;
	if(m%2==0)
	{
		if(n%2==0)
			return 2*gdb2(m/2, n/2);
		else
			return gdb2(m/2,n);
	}
	else
	{
		if(n%2==0)
			return gdb2(m, n/2);
		else
			return gdb2((m+n)/2, (m-n)/2);
	}
}

int main(int argc, char **argv)
{
	int m = 58, n = 1056;
	count = 0;
	cout << gdb1(m,n) << " times:"<< count << endl;
	count = 0;
	cout << gdb2(m,n) << " times:" << count <<endl;
	return 0;
}
