 ///
 /// @file    main.cpp
 /// @author  LiuhuiDing@gmail.com
 /// @date    2018-07-23 10:19:52
 ///
 
#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <cctype>
using namespace std;

//函数指针版本的模板

template <typename Obj>
const Obj & find_max(const vector<Obj> &arr, bool (*compare)(const Obj &x, const Obj &y))
{
	int max_index = 0;
	for(unsigned int i = 0; i < arr.size(); i++)
	{
		if(compare(arr[max_index], arr[i]))
		{
			max_index = i;
		}
	}
	return arr[max_index];
}

bool compare(const string &lhs, const string &rhs)
{
	return (strcmp(lhs.c_str(),rhs.c_str())<0) ? true : false;
}

int main()
{
	vector<string> arr(3);
	arr[0] = "ZEBRA";
	arr[1] = "alligator";
	arr[2] = "crocodile";
	cout<<find_max(arr, compare) << endl;
	return 0;
}
