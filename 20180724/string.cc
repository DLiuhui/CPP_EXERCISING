 ///
 /// @file    string.cpp
 /// @author  LiuhuiDing@gmail.com
 /// @date    2018-07-24 17:49:09
 ///
 
#include <iostream>
#include <string>
#include <string.h>
#include <stdio.h>
#include <cstring>
using std::cin;
using std::cout;
using std::endl;
using std::string;
 
void test0()
{
	char str1[10] = "hello";
	char str2[] = ", world";
	const char *str3 = "hello world";
	int len = strlen(str1) + strlen(str2) + 1;
	char *pstr = (char*)calloc(len, 1);
	strcpy(pstr, str1);
	strcat(pstr, str2);
	cout << "pstr=" << pstr << endl;
	cout << "str3" << str3 << endl;
	free(pstr);
}

void test1()
{
	string s1 = "hello";
	string s2 = "world";
	string s3 = s1+s2;
	cout << "s3=" << s3 << endl;
	string s4 = s1 + ", world";
	cout << "s4=" << s4 << endl;
	string s5 = s1.append(",world");
	cout << "s5=" << s5 << endl;
	string s6 = s1.append(s2);
	cout << "s6=" << s6 << endl;
	for(size_t idx = 0; idx != s1.size(); ++idx)
	{
		cout << s1[idx] << " ";
	}
	cout << endl;
	for(auto &ch : s1)
	{
		cout << ch << " ";
	}
	cout << endl;
	//字符串截取
	string s9 = s1.substr(0,5);
	cout << "s9="<<s9<<endl;
	string s10 = s1.substr(6,5);
	cout << "s10="<<s10<<endl;
}

int main(int argc, char **argv)
{
	test0();
	test1();
	return 0;
}
