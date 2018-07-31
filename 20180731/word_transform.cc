///
/// @file    word_transform.cc
/// @author  LiuhuiDing@gmail.com
/// @date    2018-07-30 23:37:28
///
#include <map>
#include <set>
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
using std::cin;
using std::cout;
using std::endl;
using std::map;
using std::set;
using std::ifstream;
using std::ofstream;
using std::string;
using std::getline;
using std::istringstream;


map<string, string> transRuleBuild(ifstream &rule)
{
	map<string, string> trans;
	string line;
	string word;
	string trans_word;
	while(getline(rule, line))	//读取行
	{
		istringstream stream(line);
		//读取规则
		stream >> word >> trans_word;
		trans[word] = trans_word;
	}
	return trans;
}
void word_transform(ifstream &rule, ifstream &file, ofstream &to)
{
	//建立转换规则
	map<string, string> trans_map = transRuleBuild(rule);
	string line;
	string word;
	map<string, string>::iterator iter;
	while(getline(file, line))	//读取行
	{
		istringstream stream(line);
		bool firstword = true;
		while(stream >> word)	//读取文字
		{
			if(firstword)	//如果是行首
				firstword = false;
			else
				to << " ";
			if((iter = trans_map.find(word)) != trans_map.cend())	//不是尾后迭代器，意味着找到
				to << iter->second;
			else
				to << word;
		}
		to << endl;	//打印换行
	}
}
int main(int argc, char **argv)
{
	ifstream rule("trans_file.txt");
	ifstream file("The_Holy_Bible.bak");
	ofstream to("haha.txt");
	word_transform(rule, file, to);
	return 0;
}
