 ///
 /// @file    main.cpp
 /// @author  LiuhuiDing@gmail.com
 /// @date    2018-07-23 10:19:52
 ///
 
#include <iostream>
#include <vector>
#include <string>
#include "employee.h"
using namespace std;

template <typename Obj>
const Obj & find_max(const vector<Obj> &a)
{
	int max_index = 0;
	for(unsigned int i = 0; i < a.size(); i++)
	{
		if(a[max_index] < a[i])
		{
			max_index = i;
		}
	}
	return a[max_index];
}

int main()
{
	vector<int> v1 = {1,2,3,6,4,5,5,7,2,3,1,4,5};
	vector<Employee> v2(3);
	v2[0].setValue("Gerge", 4000.00);
	v2[1].setValue("Bill", 20000.00);
	v2[2].setValue("Tom", 6000.00);
	cout << find_max(v1) << endl;
	cout << find_max(v2) << endl;
	return 0;
}
