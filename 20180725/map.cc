 ///
 /// @file    map.cc
 /// @author  LiuhuiDing@gmail.com
 /// @date    2018-07-25 17:21:25
 ///

//关联容器
#include <iostream>
#include <map>
#include <fstream>
#include <set>
#include <string>
#include <sstream>
#include <stdexcept>
#include <utility>
#define FILENAME "The_Holy_Bible.txt"

using namespace std;

int main(int argc, char **argv)
{
	ifstream input(FILENAME);
	map<string, size_t> word_count;
	set<string> include = {
		"God", "god"
	};
	string word;
	string line;
	while(getline(input, line))
	{	
		istringstream stream(line);
		while(stream >> word)
		{
			if(include.find(word) != include.end())
			{
				++word_count[word];
			}
		}
	}
	for(auto w = word_count.begin(); w != word_count.end(); w++)
	{
		cout << w->first << " occours " << w->second
			<< ((w->second>1)?" times":" time") << endl;
	}
	return 0;
}
