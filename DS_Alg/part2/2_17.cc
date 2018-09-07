///
/// @file    2_17.cc
/// @author  LiuhuiDing@gmail.com
/// @date    2018-08-07 11:50:59
///

#include <time.h>
#include <string.h>
#include <iostream>
#include <algorithm>
using std::cin;
using std::cout;
using std::endl;
#define N 20
#define MAX(m, n) ((m)>(n))?(m):(n)
#define MIN(m, n) ((m)<(n))?(m):(n)

//寻找最小子序列和的o(N)算法
int findMinSub(const int arr[], int n)
{
	int thisSum = 0, minSum = 1 << 30;
	for(int i = 0; i < n; ++i)
	{
		thisSum+= arr[i];
		if(minSum > thisSum)
			minSum = thisSum;
		if(thisSum > 0)
			thisSum = 0;
	}
	return minSum;
}

struct sumSubArray
{
	int sum;
	int rank;
};
//最小正子序列和
int findMinSubUp(const int arr[], int n)
{
	//o(N^2)
	/*
	int thisSum = 0, minSum = 0;
	for(int i = 0; i < n; ++i)
	{
		thisSum = 0;
		for(int j = i; j < n; ++j)
		{
			thisSum += arr[j];
			if(minSum > thisSum && thisSum > 0)
				minSum = thisSum;
		}
	}
	*/
	sumSubArray *subArray = new sumSubArray[n]();
	subArray[0].sum = arr[0];
	subArray[0].rank = 0;
	for(int i = 1; i < n; ++i)
	{
		subArray[i].sum = arr[i] + subArray[i-1].sum;
		subArray[i].rank = i;
	}
	/*
	for(int i = 0; i < n; ++i)
	{
		cout << "(" << subArray[i].sum << "," << subArray[i].rank << ") ";
	}
	cout << endl;
	*/
	std::sort(&subArray[0], &subArray[n], 
			[](const sumSubArray &lhs, const sumSubArray &rhs){return lhs.sum < rhs.sum;});

	int thisSum = 0, minSum = 1 << 30;
	/*
	for(int i = 0; i < n; ++i)
	{
		cout << "(" << subArray[i].sum << "," << subArray[i].rank << ") ";
	}
	cout << endl;
	*/
	for(int i = 1; i<n ; ++i)
	{
		if(subArray[i].rank > subArray[i-1].rank)
		{
			thisSum = subArray[i].sum - subArray[i-1].sum;
			if(thisSum < minSum && thisSum > 0)
			{
				minSum = thisSum;
			}
		}
	}
	delete []subArray;
	return minSum;
}
//最大子序列乘积:分治法
long int findMaxMultiSub(int arr[], int beg, int end)
{
	if(beg == end)
		return arr[beg];
	long int left, right;
	int mid = (beg+end)/2;
	left = findMaxMultiSub(arr, beg, mid);
	right = findMaxMultiSub(arr, mid+1, end);
	long int multi = 1;
	long int leftNegaMax = 1, leftPostMax = 1;	//左半部正负最小值
	long int rightNegaMax = 1, rightPostMax = 1;	//右半部正负最小值
	for(int i = mid; i>=beg; --i)
	{
		multi *= arr[i];
		if(multi > 0)
		{
			if(leftPostMax < multi) leftPostMax = multi;
		}else{
			if(multi < leftNegaMax) leftNegaMax = multi;
		}
	}
	multi = 1;
	for(int i = mid+1; i <= end; ++i)
	{
		multi *= arr[i];
		if(multi > 0)
		{
			if(rightPostMax < multi) rightPostMax = multi;
		}else{
			if(multi < rightNegaMax) rightNegaMax = multi;
		}
	}
	multi = MAX(rightNegaMax*leftNegaMax, rightPostMax*leftPostMax);
	cout << left << " " << multi << " " << right << endl;
	return (left>multi)?((left>right)?left:right):((multi>right)?multi:right);
}

int main(int argc, char **argv)
{
	srand(time(NULL));
	int array[5] = {2, -3, -3, 7, 5};
	/*
	int array[N];
	for(int i = 0; i < N; ++i)
	{
		array[i] = rand()%101-50;
	}
	*/
	/*
	cout << findMinSub(array, N) << endl;
	cout << findMinSubUp(array, N) << endl;
	*/
	cout << findMaxMultiSub(array, 0, 4) << endl;
	return 0;
}
