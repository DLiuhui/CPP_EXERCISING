///
/// @file    2_26.cc
/// @author  LiuhuiDing@gmail.com
/// @date    2018-08-07 17:29:42
///

//寻找主元
#include <algorithm>
#include <iostream>
#include <vector>
using std::cin;
using std::cout;
using std::endl;
#define MAX 100
int findMain(int array[], int size)
{
	//找主元，如果无主元返回-1
	if(size == 0)
		return -1;	//无主元
	if(size == 1)
		return array[0];	//主元
	if(size&1)	//是奇数
	{
		int tmp = array[size-1];
		int ret = findMain(array, size-1);
		if(-1 == ret)	//前子序列无主元素
		{
			int count = 0;
			for(int i = 0; i < size-1; ++i)
			{
				if(array[i] == tmp)
					++count;
			}
			if(count >= size/2)	//tmp是主元
				return tmp;
			else
				return -1;
		}
		else
			return ret;
	}
	else	//是偶数
	{
		int b[size/2];
		int j=0;
		for(int i = 0; i<size; i += 2)
		{
			if(array[i] == array[i+1])
			{
				b[j++] = array[i];
			}
		}
		return findMain(b,j);	//递归查询
	}

	//版本2
	/*
	//define Max_N
	//define Error
	int b[Max_N];
	int j = 0,i = 0;
	int num;
	if (N==0)
		exit(-1);
	if (N == 1)
	{
		if (A[N-1]!= Error)
			return (A[N-1]) ;
		else 
			return Error;
	}
	for (i = 0;i<=N-2;i += 2)
	{

		if (A[i] == A[i+1])
			b[j++] = A[i];
	}

	if (N%2)//处理N为奇数
	{
		for ( i=0,num=0;i<=j-1;i++) 
			if (b[i]==A[N-1]) num++;//考察最后一个元素是不是主元
		if (num+1>(j+1)/2) return A[N-1];
	}

	return(find(b,j));
	*/
}

int main(int argc, char **argv)
{

	int array[7] = {2,2,3,3,2,3,2};
	int array2[7] = {2,2,3,2,2,3,3};
	int array3[] = {5,5,3,5,6,7,5,3,5,3,1,5,5,2,5};
	cout << findMain(array, sizeof(array)/sizeof(int)) << endl;
	cout << findMain(array2, sizeof(array2)/sizeof(int)) << endl;
	cout << findMain(array3, sizeof(array3)/sizeof(int)) << endl;
	return 0;
}
