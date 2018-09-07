///
/// @file    main.cc
/// @author  LiuhuiDing@gmail.com
/// @date    2018-08-01 20:52:12
///

#include "vector.h"
#include <ctime>
#include <iostream>
#include <string>
#include <cmath>
using std::cin;
using std::cout;
using std::endl;
using std::string;
using namespace MyStd;
int main(int argc, char **argv)
{
	
	Vector<int> vec;
	srand(time(NULL));
	for(unsigned int i = 0; i < 50; i++)
	{
		vec.push_back(rand()%100 + 1);
	}
	cout << vec.size() << " " << vec.capacity() << endl;
	vec.reverse(300);
	cout << vec.size() << " " << vec.capacity() << endl;
	for(Vector<int>::iterator iter = vec.begin(); iter != vec.end(); iter++)
	{
		cout << *iter << endl;
	}
	return 0;
}
