///
/// @file    dictionary.cc
/// @author  LiuhuiDing@gmail.com
/// @date    2018-07-27 23:55:02
///

#include "dictionary.h"

Dictionary::Dictionary():
	filename_(std::string()), dic_queue_()
{}

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
	std::string word;
	std::string line;
	while(getline(ifs, line))
	{
		std::istringstream ss(line);
		while(ss>>word)
		{
			if(wordStandardizing(word))
			{
				dic_queue_.SortInsert(word);	//生成字典队列
			}
		}
	}
	ifs.close();
	return true;
}

void Dictionary::store(const std::string &filename)
{
	//生成字典文件
	std::ofstream ofs(filename+".dictionary", std::ios::out);
	DicItem dic;
	while(!dic_queue_.empty())	//队列输出
	{
		dic = dic_queue_.front();
		dic_queue_.pop();
		ofs << dic.word << " " << dic.times << std::endl;
	}
	ofs.close();
}

bool Dictionary::wordStandardizing(std::string &word)
{
	for(unsigned int i = 0; i < word.size(); i++)
	{
		if(isdigit(word[i]))	//是数字
		{
			return false;
		}
		else if(isupper(word[i]))	//大写转成小写
		{
			word[i] = tolower(word[i]);
		}
	}
	return true;
}
