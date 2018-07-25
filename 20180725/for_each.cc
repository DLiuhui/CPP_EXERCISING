 //
 /// @file    for_each.cpp
 /// @author  LiuhuiDing@gmail.com
 /// @date    2018-07-25 10:59:31
 ///
 
#include <iostream>
#include <algorithm>
#include <vector>
using std::cin;
using std::cout;
using std::endl;
using std::vector;

struct Sum
{
	Sum():sum(0) {}
	void operator()(const int n) {sum+=n;};
	int sum;
};
int main(int argc, char **argv)
{
	int x = 11;
	vector<int> nums{3,4,2,8,15,267};
	auto print = [](const int &n) {cout << " " << n;};
	cout << "before:";
	std::for_each(nums.begin(), nums.end(), print);
	cout<<"\n";
	std::for_each(nums.begin(), nums.end(), [x](int &n){n=n*x+2;});
	Sum s = std::for_each(nums.begin(), nums.end(), Sum());
	cout<<"after:";
	std::for_each(nums.begin(), nums.end(), print);
	cout << "\n";
	cout << "sum:" << s.sum << endl;
	return 0;
}
