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
using namespace MyStl;
class Int
{
	public:
		Int()
			:value(new int)
		{}
		Int(int x)
			:value(new int(x))
		{}
		Int(const Int &x)
			:value(new int(*x.value))
		{}
		~Int()
		{
			delete value;
		}
		int& operator*() const
		{
			return *value;
		}
	private:
		int* value;
};

int main(int argc, char **argv)
{
	
	Vector<Int> vec;
	srand(time(NULL));
	cout << vec.size() << " " << vec.capacity() << endl;
	for(unsigned int i = 0; i < 50; i++)
	{
		vec.push_back(rand()%100 + 1);
	}
	cout << vec.size() << " " << vec.capacity() << endl;
	vec.reverse(100);
	cout << vec.size() << " " << vec.capacity() << endl;
	int i = 1;
	for(Vector<Int>::iterator iter = vec.begin(); iter != vec.end(); iter++)
	{
		cout << i++ << ": " << **iter << endl;
	}
	return 0;
}
