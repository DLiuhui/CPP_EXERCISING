 ///
 /// @file    vector_capacity.cpp
 /// @author  LiuhuiDing@gmail.com
 /// @date    2018-07-25 09:57:43
 ///
 
#include <iostream>
#include <vector>
using std::cin;
using std::cout;
using std::endl;
using std::vector;
 
int main(int argc, char **argv)
{
	vector<int> vec;
	cout << "size:" << vec.size() << " ";
	cout << "capacity:" << vec.capacity() << endl;
	for(unsigned int x = 0; x != 24; x++)
	{
		vec.push_back(x);
		cout << x << " ";
		cout << "size:" << vec.size() << " ";	
		cout << "capacity:" << vec.capacity() << endl;
	}
	vec.reserve(15);
	cout << "size:" << vec.size() << " ";	
	cout << "capacity:" << vec.capacity() << endl;
	vec.resize(15);
	cout << "size:" << vec.size() << " ";	
	cout << "capacity:" << vec.capacity() << endl;
	vec.clear();
	cout << "size:" << vec.size() << " ";	
	cout << "capacity:" << vec.capacity() << endl;
	return 0;
}
