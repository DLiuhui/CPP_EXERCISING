 ///
 /// @file    1_5.cpp
 /// @author  LiuhuiDing@gmail.com
 /// @date    2018-07-23 21:51:47
 ///
 
#include <iostream>
using std::cin;
using std::cout;
using std::endl;
 
int fun(int n)
{
	if(n>0)
	{
		if(n%2==0)
		{
			return fun(n/2);
		}
		else
			return 1 + fun(n/2);
	}
	return 0;
}

int main(int argc, char **argv)
{
	int N;
	cin >> N;
	cout << fun(N) << endl;
	return 0;
}
