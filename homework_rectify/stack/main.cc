///
/// @file    main.cc
/// @author  LiuhuiDing@gmail.com
/// @date    2018-07-30 14:32:55
///
#include "stack.h"
#include <iostream>
using std::cin;
using std::cout;
using std::endl;

int main(int argc, char **argv)
{
	Stack stack;
	cout << "此时栈是否为空? " << stack.empty() << endl;
	stack.push(1);
	cout << "此时栈是否为空? " << stack.empty() << endl;

	for(int idx = 2; idx != 15; ++idx)
	{
		stack.push(idx);
	}
	cout << "此时栈是否已满? " << stack.full() << endl;

	while(!stack.empty()) {
		cout << stack.top() << endl;
		stack.pop();
	}
	cout << "此时栈是否为空? " << stack.empty() << endl;
	return 0;
}
