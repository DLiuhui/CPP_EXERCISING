#include <iostream>
using namespace std;

int (*fun(int i))[5]
{
	int a[] = {1,2,3,4,5};
	int b[] = {6,7,8,9,10};
	return i>5 ? &b:&a;
}

int main()
{
	int a=4, b=7;
	int (*p)[5];
	p = fun(b);
	for(const int i:*p)
	{
		cout << i << endl;
	}
	return 0;
}
