///
/// @file    io1.cc
/// @author  LiuhuiDing@gmail.com
/// @date    2018-07-27 11:20:12
///
//流：流状态
#include <unistd.h>
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
	while(cin >> number || !cin.eof())
	{
		printCin();
		if(cin.fail())
		{
			//在输入出错后，cin保存了错误输入，存储在缓冲区中
			//所以状态更新后cin直接将缓冲区内的信息读出
			//需要清空缓存区
			//要先clear 再ignore
			//如果先ignore再clear或陷入死循环（下一次输入还是显示cin.fail=1）
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cout << "please input a number:" << endl;
			continue;
		}
		else if(cin.bad())
		{
			cout << "istream dump" << endl;
			return -1;
		}
		cout << "number:" << number << endl;
	}
	/*
	printCin();
	cin.clear();
	printCin();
	*/
	//cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	//cout << "clear all" << endl;
	return 0;
}
