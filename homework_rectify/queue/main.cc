///
/// @file    main.cc
/// @author  LiuhuiDing@gmail.com
/// @date    2018-07-30 14:50:23
///

#include "queue.h"
#include <iostream>
using std::cin;
using std::cout;
using std::endl;

int main(int argc, char **argv)
{
	Queue que;
	cout << "此时队列是否为空? " << que.empty() << endl;
	que.push(1);
	cout << "此时队列是否为空? " << que.empty() << endl;

	for(int idx = 2; idx != 15; ++idx)
	{
		que.push(idx);
	}
	cout << "队头的元素是： " << que.front() << endl;
	cout << "队尾的元素是: " << que.back() << endl;

	que.pop();
	que.push(10);
	cout << "队头的元素是： " << que.front() << endl;
	cout << "队尾的元素是: " << que.back() << endl;


	cout << "此时队列是否已满? " << que.full() << endl;

#if 1
	while(!que.empty()) {
		cout << que.front() << endl;
		que.pop();
	}
	cout << "此时队列是否为空? " << que.empty() << endl;
#endif
	return 0;
}
