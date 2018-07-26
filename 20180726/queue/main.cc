///
/// @file    main.cc
/// @author  LiuhuiDing@gmail.com
/// @date    2018-07-26 22:03:26
///

#include "queue.h"
#include <iostream>
using std::cin;
using std::cout;
using std::endl;

int Queue::max_size_ = 30;
int main(int argc, char **argv)
{
	Queue::setMaxSize();
	Queue q;
	for(int i = 0; i < 28; i++)
	{
		q.push(i * i);
	}
	cout << q.front() << endl;
	cout << q.back() << endl;
	if(!q.push(99))
	{
		cout << "full" << endl;
	}	
	if(!q.push(999))
	{
		cout << "full" << endl;
	}
	if(!q.push(9999))
	{
		cout << "full" << endl;
	}
	cout << q.front() << endl;
	cout << q.back() << endl;
	q.pop();
	cout << q.front() << endl;
	cout << q.back() << endl;
	q.pop();
	cout << q.front() << endl;
	cout << q.back() << endl;
	return 0;
}
