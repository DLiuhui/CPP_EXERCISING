///
/// @file    main.cc
/// @author  LiuhuiDing@gmail.com
/// @date    2018-07-26 20:37:52
///

#include "stack.h"
#include <iostream>
using std::cin;
using std::cout;
using std::endl;

unsigned int Stack::max_size_ = 100;

int main(int argc, char **argv)
{
	Stack::setMaxSize();
	Stack s;
	for(int i = 0; i < 98; i++)
	{
		s.push(i);
	}
	if(!s.push(10))
	{
		cout << "full" << endl;
	}	
	if(!s.push(12))
	{
		cout << "full" << endl;
	}
	if(!s.push(14))
	{
		cout << "full" << endl;
	}
	cout << s.returnTop() << endl;
	s.pop();
	cout << s.returnTop() << endl;
	s.pop(); s.pop(); s.pop();
	cout << s.returnTop() << endl;
	return 0;
}
