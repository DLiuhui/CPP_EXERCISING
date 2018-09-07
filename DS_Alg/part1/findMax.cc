 ///
 /// @file    main.cpp
 /// @author  LiuhuiDing@gmail.com
 /// @date    2018-07-23 10:19:52
 ///
 
#include <iostream>
#include <vector>
#include <string>
#include <cstring>
using namespace std;

class CaseInsensitiveCompare
{
public:
	bool is_less_than(const string &lhs, const string &rhs) const
	{
		return strcmp(lhs.c_str(), rhs.c_str()) < 0;
	}
};
template <typename Obj, typename Comparator>
const Obj & find_max(const vector<Obj> &arr, Comparator cmp)
{
	int max_index = 0;
	for(unsigned int i = 0; i < arr.size(); i++)
	{
		if(cmp.is_less_than(arr[max_index],arr[i]))
		{
			max_index = i;
		}
	}
	return arr[max_index];
}

int main()
{
	vector<string> arr(3);
	arr[0] = "ZEBRA";
	arr[1] = "alligator";
	arr[2] = "crocodile";
	cout<<find_max(arr, CaseInsensitiveCompare()) << endl;
	return 0;
}
