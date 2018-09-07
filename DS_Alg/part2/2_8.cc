///
/// @file    2_8.cc
/// @author  LiuhuiDing@gmail.com
/// @date    2018-08-01 21:21:52
///
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <cstring>

#define N 300
using std::cin;
using std::cout;
using std::endl;

void fun1()
{
	int array[N] = {0};
	int i = 0, j = 0;
	while(i < N)
	{
		array[i] = rand()%N+1;	//生成随机数
		for(j = 0; j < i; j++)
		{
			if(array[i] == array[j])
			{
				break;
			}
		}
		if(j == i)
		{
			i++;
		}
	}
}

void fun2()
{
	int array[N] = {0};
	int arr[N] = {0};
	int i = 0;
	while(i < N)
	{
		array[i] = rand()%N+1;	//生成随机数
		if(0 == arr[array[i]-1])
		{
			arr[array[i]] = 1;
			i++;
		}
	}
}

void fun3()
{
	int array[N] = {0};
	for(int i = 0; i < N; i++)
	{
		array[i] = i+1;
	}
	for(int i = 0; i < N; i++)
	{
		std::swap(array[i], array[rand()%N]);
	}
}
int main(int argc, char **argv)
{
	srand(time(NULL));
	time_t start,end;
	start = time(NULL);
	fun1();
	end = time(NULL);
	cout << "1:" << difftime(end,start) << endl;
	start = time(NULL);
	fun2();
	end = time(NULL);
	cout << "2:" << difftime(end,start) << endl;
	start = time(NULL);
	fun3();
	end = time(NULL);
	cout << "3:" << difftime(end,start) << endl;

	return 0;
}
