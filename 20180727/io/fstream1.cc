///
/// @file    fstream1.cc
/// @author  LiuhuiDing@gmail.com
/// @date    2018-07-27 14:50:35
///

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using std::cin;
using std::cout;
using std::endl;
using std::ifstream;
using std::ofstream;
using std::fstream;
using std::string;
using std::vector;

void test0(vector<string> &vec, char *file)
{
	ifstream ifs(file);
	if(!ifs)
	{
		cout << "no such file" << endl;
		return;
	}
	string line;
	while(std::getline(ifs,line))
	{
		vec.push_back(line);
	}
	ifs.close();	//不要忘了关闭打开的文件
}
int main(int argc, char **argv)
{
	if(argc < 2)
	{
		cout << "input file name" << endl;
		return -1;
	}
	vector<string> vec;
	test0(vec, argv[1]);
	int i = 0;
	for(vector<string>::iterator iter = vec.begin(); i < 10; iter += 2, i++)
	{
		cout << *iter << endl;
	}
	return 0;
}
