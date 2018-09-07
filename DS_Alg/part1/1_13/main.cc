 ///
 /// @file    main.cpp
 /// @author  LiuhuiDing@gmail.com
 /// @date    2018-07-23 23:33:46
 ///
 
#include <iostream>
#include "1_13.h"
using std::cin;
using std::cout;
using std::endl;
 
int main(int argc, char **argv)
{
	int x;
	Collection<int> bottle;
	if(bottle.is_empty())
	{
		cout << "empty" << endl;
	}
	for(int i = 0; i < 20; i++)
	{
		bottle.insert(i);
	}
	bottle.remove();
	cin >> x;
	cout << x << endl;
	if(bottle.contains(x))
	{
		cout << "find " << x <<endl;
	}
	else
	{
		cout << "not find " << x << endl;
	}
	return 0;
}
