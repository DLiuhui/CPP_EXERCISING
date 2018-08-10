///
/// @file    fstream2.cc
/// @author  LiuhuiDing@gmail.com
/// @date    2018-07-27 17:12:15
///
#include <string.h>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::string;
using std::ifstream;
using std::ofstream;
using std::fstream;

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

void test1(const vector<string> &vec)
{
	
	string filename = "test1.txt";
	//如果文件不存在，就创建一个
	//如果文件存在，则清空文件内容，再写入
	ofstream ofs(filename, ofstream::out);
	if(!ofs.good())
	{
		cout << "ostream error" << endl;
		return;
	}
	for(int i = 0; i < 20; i++)
	{
		cout << vec[i] << endl;
		ofs << vec[i] << "\n";
	}
	cout << "pos = " << ofs.tellp() << endl;
	ofs.close();
}

void test2()
{
	string filename = "test1.txt";
	ofstream ofs(filename, ofstream::app);
	if(!ofs.good())
	{
		cout << "ostream error" << endl;
		return;
	}
	cout << "pos=" << ofs.tellp() << endl;
	string line = "this is a new line";
	ofs << line;
	cout << "pos=" << ofs.tellp() << endl;
	ofs.close();
}

void test3()
{
	fstream fs;
	//fs.open("test2.txt");
	//没有则创建，有则追加写入
	fs.open("test2.txt", std::ios::out|std::ios::app);
	if(!fs)
	{
		cout << "fstream open error!" << endl;
		return;
	}
	int number;
	cout << "input numbers" << endl;
	for(int i = 0; i<5; i++)
	{
		cin >> number;
		fs << number << " ";
	}
	cout << "pos = " << fs.tellp() << endl;
	cout << "input more numbers:" << endl;
	for(int i = 0; i<5; i++)
	{
		cin >> number;
		fs << number << " ";
	}
	cout << "pos = " << fs.tellp() << endl;
	fs.seekg(std::ios::beg);
	for(int i = 0; i<10; i++)
	{
		fs >> number;
		cout << number << " ";
	}
	cout << endl;
	fs.close();
}

void test4()
{
	ifstream ifs("test2.txt", std::ios::ate);
	if(!ifs)
	{
		cout << "ifstream open error!" << endl;
		return;
	}
	size_t length = ifs.tellg();
	cout << "pos=" << length << endl;
	ifs.seekg(std::ios::beg);
	char buff[length+1];
	memset(buff,0,length+1);
	ifs.read(buff,length+1);
	string content(buff);
	cout << content << endl;
	ifs.close();
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
	test1(vec);
	test2();
	test3();
	test4();
	return 0;
}
