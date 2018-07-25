 ///
 /// @file    new.cpp
 /// @author  LiuhuiDing@gmail.com
 /// @date    2018-07-24 18:11:45
 ///
 
#include <iostream>
using std::cin;
using std::cout;
using std::endl;
 
void test1()
{
	int *pint = new int(1);
	cout << "*pint=" << *pint << endl;
	delete pint;

	int *pint2 = new int[10]();	//默认初始化为全0
	for(int idx = 0; idx < 10; idx++)
	{
		cout << pint2[idx] << " ";
		pint2[idx] = idx;
	}
	cout << endl;
	int *pint3 = new int[10];	//默认初始化为全0
	for(int idx = 0; idx < 10; idx++)
	{
		cout << pint3[idx] << " ";
		pint3[idx] = idx;
	}
	cout << endl;
	delete [] pint2;
}
int main(int argc, char **argv)
{
	test1();
	return 0;
}
