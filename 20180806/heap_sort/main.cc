///
/// @file    main.cc
/// @author  LiuhuiDing@gmail.com
/// @date    2018-08-06 22:15:17
///

#include "heap.h"
#include <iostream>
using std::cin;
using std::cout;
using std::endl;
using namespace MyStd;

int main(int argc, char **argv)
{
	Heap<int>heap({1,2,3,5,6,7,8,9,2,5,7,5,9,6,7,3,8,4,6});
	Heap<int, std::greater<int>> heap2({1,2,3,5,6,7,8,9,2,5,7,5,9,6,7,3,8,4,6});
	cout << heap.top() << endl;
	cout << heap2.top() << endl;
	unsigned int n = heap.size();
	for(unsigned int i = 0; i < n; ++i)
	{
		cout << heap.top() << endl;
		heap.pop();
	}
	n = heap2.size();
	for(unsigned int i = 0; i < n; ++i)
	{
		cout << heap2.top() << endl;
		heap2.pop();
	}
	return 0;
}
