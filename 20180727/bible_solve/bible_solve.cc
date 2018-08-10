///
/// @file    bible_solve.cc
/// @author  LiuhuiDing@gmail.com
/// @date    2018-07-27 21:27:46
///

//先将《圣经》转格式，大写变小写，符号、tab变成空格
//统计每一行的单词与词频率
//存储单词：
//用vector
//用红黑树
//用std::map/std::size

//1、vector
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::string;
using std::ofstream;
using std::ifstream;
using std::getline;
using std::istringstream;

struct Word
{
	string word;
	int times;
};

void solveBible(const string &to, const string &from)
{
	char c;
	ifstream ifs(from, std::ios::in);
	ofstream ofs(to, std::ios::out);
	while(ifs.get(c))
	{
		if((c<='z'&& c>='a') || c=='\n')
		{
			ofs << c;
		}
		else if(c<='Z' && c>='A')
		{
			c = c+'a'-'A';
			ofs << c;
		}
		else
		{
			c = ' ';
			ofs << c;
		}
	}
	ifs.close();
	ofs.close();
}

void wordCount(vector<Word> &vec, const string &file)
{
	string word;
	string line;
	ifstream ifs(file, std::ios::in);
	while(getline(ifs, line))
	{
		istringstream ss(line);
		vector<Word>::iterator iter;
		while(ss>>word)
		{
			for(iter = vec.begin(); iter!=vec.end(); iter++)
			{
				if(word == iter->word)
				{
					iter->times++;
					break;
				}
			}
			if(iter == vec.end())	//未找到
			{
				vec.push_back({word, 1});
			}
		}
	}
}
int main(int argc, char **argv)
{
	//solveBible("The_Holy_Bible_Sol.bak", "The_Holy_Bible.bak");
	vector<Word> vec;
	wordCount(vec,"The_Holy_Bible_Sol.bak");
	ofstream os("Dictionary", std::ios::out);
	for(vector<Word>::iterator iter = vec.begin(); iter!=vec.end(); iter++)
	{
		os << iter->word << " " << iter->times << endl;
	}
	return 0;
}
