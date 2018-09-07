///
/// @file    2_21.cc
/// @author  LiuhuiDing@gmail.com
/// @date    2018-08-07 16:21:51
///

#include <cmath>
#include <algorithm>
#include <iostream>
using std::cin;
using std::cout;
using std::endl;

#define N 1000

//利用 厄拉多塞筛 实现在o(Nlog(N))时间求取小于N的所有素数
//制作整数2到N的表
//找出最小的未被删除的整数i
//删除2i，3i，4i。。。
//当i>N^(1/2)，算法结束
//
void FindPrime(int n)
{
	bool *array = new bool[n+1]();
	int m = sqrt(n);
	for(int i = 2; i <= m; ++i)
	{
		if(array[i] == true)
			continue;
		else
			for(int j = 2*i; j <= n; j += i)
			{
				array[j] = true;
			}
	}
	for(int i = 2; i < n; ++i)
	{
		if(!array[i])
			cout << i << " ";
	}
	cout << endl;
	delete []array;
}
int main(int argc, char **argv)
{
	FindPrime(1001);
	return 0;
}
