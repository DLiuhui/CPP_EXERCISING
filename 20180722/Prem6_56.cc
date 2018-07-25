#include <iostream>
#include <vector>
using namespace std;

int f1(int v1, int v2)
{
	return v1+v2;
}
int f2(int v1, int v2) 
{
	return v1 - v2;
}
int f3(int v1, int v2) 
{
	return v1*v2;
}
int f4(int v1, int v2) 
{
	return v1/v2;
}

void compute(int a, int b, int(*p)(int, int))
{
	cout<<p(a,b)<<endl;
}
int main()
{
	decltype(f1) *p1 = f1, *p2=f2, *p3=f3, *p4=f4;
	vector<decltype(f1)*>vPtr = {p1,p2,p3,p4};
	for(auto ptr:vPtr)
	{
		compute(10, 5, ptr);
	}
	compute(7,8,&f1);
	return 0;
}
