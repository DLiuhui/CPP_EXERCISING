///
/// @file    main.cc
/// @author  LiuhuiDing@gmail.com
/// @date    2018-08-03 17:37:14
///

#include "deque.h"
#include <iostream>
using std::cin;
using std::cout;
using std::endl;
using MyStd::Deque;

int main(int argc, char **argv)
{
	Deque<int> queue;
	queue.push_back(15);
	queue.push_back(26);
	cout << "back:" << queue.back() << endl;
	cout << "front" << queue.front() << endl;
	for(unsigned int i = 0; i < 100; ++i)
	{
		if(i % 2 == 0)
			queue.push_front(i);
		else
			queue.push_back(i);
	}
	cout << "back:" << queue.back() << endl;
	cout << "front" << queue.front() << endl;
	cout << queue.size() << endl;
	for(unsigned int i = 0; i < queue.size(); ++i)
	{
		cout << i+1 << ": "<< queue[i] << endl;
	}
	return 0;
}
