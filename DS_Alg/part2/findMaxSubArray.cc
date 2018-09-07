#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>
#define SIZE 4000
using std::cin;
using std::cout;
using std::endl;
using std::vector;
int max(int a, int b, int c)
{
	if(a>b)
	{
		return (a>c)?a:c;
	}
	else
	{
		return (b>c)?b:c;
	}
}
//穷举o(n^3)
int find1(const vector<int> &a)
{
	int maxSum = 0;
	int sum = 0;
	for(unsigned int i = 0; i < a.size(); i++)
	{
		for(unsigned int j = i; j < a.size(); j++)
		{
			sum = 0;
			for(unsigned int k = i; k < j; k++)
			{
				sum += a[k];
			}
			if(sum > maxSum)
			{
				maxSum = sum;
			}
		}
	}
	return maxSum;
}
//改进型穷举o(n^2)
int find2(const vector<int> &a)
{
	int maxSum = 0;
	int sum = 0;
	for(unsigned int i = 0; i < a.size(); i++)
	{
		sum = 0;
		for(unsigned int j = i; j < a.size(); j++)
		{
			sum += a[j];
			if(sum > maxSum)
			{
				maxSum = sum;
			}
		}
	}
	return maxSum;
}
//分治o(NlogN)
//最大子序列要么在前一半，要么在后一半，要么跨越了中间
//寻找左半最大子序列，右半最大子序列，中间最大子序列
//比较，得出结构
//对左半边和右半边，递归处理
int find3(const vector<int> &a,int begin,int end)
{
	if(begin < end)
	{
		int mid = (begin + end) / 2;
		int leftSum = 1<<31, rightSum= 1<<31;
		int sum = 0;
		for(int i = mid; i>=begin; i--)
		{
			sum += a[i];
			if(sum > leftSum)
			{
				leftSum = sum;
			}
		}
		sum = 0;
		for(int i = mid+1; i <= end; i++)
		{
			sum += a[i];
			if(sum > rightSum)
			{
				rightSum = sum;
			}
		}
		//找左 找中间 找右
		return max(find3(a,begin,mid), leftSum+rightSum, find3(a,mid+1,end));
	}
	else
		return a[begin];
}

int find4(const vector<int> &a)
{
	int maxSum = 0, sum = 0;
	for(unsigned int j = 0; j < a.size(); j++)
	{
		sum += a[j];
		if(sum > maxSum)
		{
			maxSum = sum;
		}else if(sum < 0)
		{
			sum = 0;
		}
	}
	return maxSum;
}
int main(int argc, char **argv)
{
	srand(time(NULL));
	vector<int> a;
	for(int i = 0; i<SIZE; i++)
	{
		a.push_back(rand()%201 - 100);	//[-100, 100]
	}
	time_t start, end;
	start = time(NULL);
	cout<<find1(a)<<endl;
	end = time(NULL);
	cout << "time1="<<difftime(end, start)<<endl;
	start = time(NULL);
	cout<<find2(a)<<endl;
	end = time(NULL);
	cout << "time2="<<difftime(end, start)<<endl;
	start = time(NULL);
	cout<<find3(a, 0, a.size()-1)<<endl;
	end = time(NULL);
	cout << "time3="<<difftime(end, start)<<endl;
	start = time(NULL);
	cout<<find4(a)<<endl;
	end = time(NULL);
	cout << "time4="<<difftime(end, start)<<endl;
	return 0;
}
