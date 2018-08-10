///
/// @file    io1.cc
/// @author  LiuhuiDing@gmail.com
/// @date    2018-07-27 11:20:12
///
//流：流状态
#include <iostream>
#include <string>
#include <fstream>
#include <limits>
using std::cin;
using std::cout;
using std::endl;
using std::istream;
using std::string;

void printCin()
{
	cout << cin.bad() << " ";
	cout << cin.fail() << " ";
	cout << cin.eof() << " ";
	cout << cin.good() << endl;
}
/*
void printCinNow(istream &is)
{
	is.rdstate();
}
*/

int main(int argc, char **argv)
{
	cout << sizeof(cin) << " " << sizeof(cout) << endl;
	printCin();
	int number;
	while(cin >> number)
	{
		cout << "number = " << number << endl;
	}
	printCin();
	cin.clear();
	printCin();
	//在输入出错后，cin保存了错误输入，存储在缓冲区中
	//所以状态更新后cin直接将缓冲区内的信息读出
	//需要清空缓存区
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	cout << "clear all" << endl;
	string s;
	cin >> s;
	cout << "string：" << s << endl;
	cin >> number;
	cout << "num: " << number <<endl;
	return 0;
}
