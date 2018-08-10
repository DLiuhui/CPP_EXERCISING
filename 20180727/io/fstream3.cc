///
/// @file    fstream3.cc
/// @author  LiuhuiDing@gmail.com
/// @date    2018-07-27 20:23:54
///
//读取配置文件
#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::ifstream;
using std::istringstream;
using std::ostringstream;
using std::stringstream;

void test0()
{
	int num1 = 10;
	int num2 = 20;
	//功能类似sprintf
	stringstream ss;
	ss << "num1 " << num1 << " nun2 " << num2;	//每个元素之间利用空格分隔，方便读取
	cout << ss.str() << endl;
	string str;
	int number;
	while(!ss.eof())
	{
		ss >> str >> number;
		cout << "str:" << str << endl;
		cout << "number:" << number << endl;
	}
}

string int2str(int number)
{
	ostringstream os;
	os << number;
	return os.str();
}

//对配置文件解析
void readConfiguration(const string & filename)
{
	ifstream ifs(filename);
	if(!ifs)
	{
		cout << "file open error" << endl;
		return;
	}
	string key;
	string value;
	string line;
	while(getline(ifs, line))
	{
		istringstream iss(line);
		iss >> key >> value;
		cout << key << "-----"<< value << endl;
	}
}
int main(int argc, char **argv)
{
	test0();
	readConfiguration("config.txt");
	return 0;
}
