///
/// @file    dictionary.cc
/// @author  LiuhuiDing@gmail.com
/// @date    2018-07-27 23:55:02
///

#include "dictionary.h"

Dictionary::Dictionary() = default;

Dictionary::Dictionary(const std::string &filename)
{
	if(read(filename))
	{
		filename_ = filename;
		dictionary_file_ = filename + ".dictionary";
		store(filename);
	}
	else
	{
		filename_ = "\0";
		dictionary_file_ = "\0";
	}
}

Dictionary::Dictionary(const Dictionary &dic):
	dictionary_file_(dic.dictionary_file_), filename_(dic.filename_)
{}

Dictionary::~Dictionary() = default;

void Dictionary::makeDictionary(const std::string &filename)
{
	if(read(filename))
	{
		store(filename);
		filename_ = filename;
		dictionary_file_ = filename + ".dictionary";
	}
}

bool Dictionary::read(const std::string &filename)
{
	char c;
	std::ifstream ifs(filename, std::ios::in);
	if(!ifs)
	{
		std::cout << "file path error" << std::endl;
		return false;
	}
	std::ofstream ofs(filename+".dic_make_file", std::ios::out);
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
	return true;
}

void Dictionary::store(const std::string &filename)
{
	std::vector<DictionaryItem> vec;
	std::string word;
	std::string line;
	std::ifstream ifs(filename+".dic_make_file", std::ios::in);
	while(getline(ifs, line))
	{
		std::istringstream ss(line);
		std::vector<DictionaryItem>::iterator iter;
		while(ss>>word)
		{
			for(iter = vec.begin(); iter!=vec.end(); iter++)
			{
				if(word == iter->word_)
				{
					iter->times_++;
					break;
				}
			}
			if(iter == vec.end())	//未找到
			{
				vec.push_back({word, 1});
			}
		}
	}
	ifs.close();
	//对单词进行排序
	std::sort(vec.begin(), vec.end());
	std::ofstream ofs(filename+".dictionary", std::ios::out);
	for(std::vector<DictionaryItem>::const_iterator iter = vec.cbegin(); iter!=vec.cend(); iter++)
	{
		ofs << iter->word_ << " " << iter->times_ << std::endl;
	}
	ofs.close();
}
