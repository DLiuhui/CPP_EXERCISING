///
/// @file    main.cc
/// @author  LiuhuiDing@gmail.com
/// @date    2018-08-08 10:48:42
///
#include "list.h"
#include <iostream>
#include <string>
using std::cin;
using std::cout;
using std::endl;
using std::string;
using namespace MyStd;

int main(int argc, char **argv)
{
	List<int> list;
	cout << list.size() << endl;
	cout << list.empty() << endl;
	for(int i=0; i<100; ++i)
	{
		if(i&1)
		{
			list.push_back(i);
		}
		else
			list.push_front(i);
	}
	cout << list.size() << endl;
	cout << list.empty() << endl;
	cout << list.front() << endl;
	list.pop_front(); cout << list.front() << endl;
	cout << list.back() << endl;
	list.pop_back(); cout << list.back() << endl;
	List<int>::iterator iter = list.begin();
	cout << "begin: ";
	for(int i=0; i<20; ++i)
	{
		cout << *iter << " ";
		++iter;
	}
	cout << endl;
	List<int>::iterator iter2 = list.end();
	cout << "end: ";
	for(int i=0; i<20; ++i)
	{
		--iter2;
		cout << *iter2 << " ";
	}
	cout << endl;
	list.erase(iter, iter2);
	cout << list.size() << endl;
	return 0;
}
