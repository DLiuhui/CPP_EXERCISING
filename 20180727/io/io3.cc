///
/// @file    io3.cc
/// @author  LiuhuiDing@gmail.com
/// @date    2018-07-27 16:47:52
///

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
using std::cin;
using std::cout;
using std::endl;
using std::getline;
using std::vector;
using std::string;
using std::istringstream;

struct PersonInfo
{
	string name;
	vector<string> phones;
};
int main(int argc, char **argv)
{
	string line, word;
	vector<PersonInfo> people;
	while(getline (cin, line))
	{
		PersonInfo info;
		istringstream record(line);
		record >> info.name;
		while(record >> word)
		{
			info.phones.push_back(word);
		}
		people.push_back(info);
	}
	for(auto &i : people)
	{
		cout << i.name << " ";
		for(auto &j : i.phones)
		{
			cout << j << " ";
		}
		cout << endl;
	}
	return 0;
}
