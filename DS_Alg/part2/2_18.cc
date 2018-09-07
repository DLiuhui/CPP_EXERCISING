///
/// @file    2_18.cc
/// @author  LiuhuiDing@gmail.com
/// @date    2018-08-07 11:07:40
///

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <iostream>
#include <cmath>
using std::cin;
using std::cout;
using std::endl;

bool check(double a, double b)
{
	return (a*b > 0)? false:true;
}

double fun1(double low, double high, double (*f)(double x))
{
	double tmp = f((low+high)/2);
	if((tmp < 0 && -tmp<1e-4) || (tmp>0 && tmp < 1e-4))
	{
		return (low+high)/2;
	}
	else if(tmp * f(low) > 0)
		return fun1((low+high)/2, high, f);
	else
		return fun1(low, (low+high)/2, f);
}
double fun(double low, double high, double (*f)(double x))
{
	if(check(f(low), f(high)))
	{
		if(f(low)*f(high) == 0)
			return (f(low)==0) ? low:high;
		else
			return fun1(low, high, f);
	}
	else
	{
		cout << "error" << endl;
		exit(1);
	}
}

double f(double x)
{
	return x*x-2*x;
}
int main(int argc, char **argv)
{
	cout << fun(1,3,f) << endl;
	cout << fun(2,3,f) << endl;
	return 0;
}
