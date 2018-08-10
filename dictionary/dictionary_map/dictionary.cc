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
		store(filename);
	}
	else
	{
		filename_ = "\0";
	}
}

Dictionary::Dictionary(const Dictionary &dic):
	container_(dic.container_), filename_(dic.filename_)
{}

Dictionary::~Dictionary() = default;

void Dictionary::makeDictionary(const std::string &filename)
{
	if(read(filename))
	{
		store(filename);
		filename_ = filename;
	}
}

bool Dictionary::read(const std::string &filename)
{
	std::ifstream ifs(filename, std::ios::in);
	if(!ifs)
	{
		std::cout << "file path error" << std::endl;
		return false;
	}
	std::string line;
	std::string word;
	if(container_.size() > 0)	//清空之前的存储
	{
		container_.clear();
	}
	while(std::getline(ifs, line))
	{
		std::istringstream ss(line);
		while(ss >> word)
		{
			if(wordStandard(word))
				container_[word]++;
		}
	}
	ifs.close();
	return true;
}

void Dictionary::store(const std::string &filename)
{
	std::map<std::string,int> map;
	std::ofstream ofs(filename+".dictionary", std::ios::out);
	for(std::map<std::string,int>::const_iterator iter = container_.cbegin(); iter!=container_.cend(); iter++)
	{
		ofs << iter->first << " " << iter->second << std::endl;
	}
	ofs.close();
}

bool Dictionary::wordStandard(const std::string & word) const
{
	for(unsigned int i = 0; i < word.size(); i++)
	{
		if(isdigit(word[i]))
			return false;
		else if(isupper(word[i]))
			tolower(word[i]);
	}
	return true;
}
