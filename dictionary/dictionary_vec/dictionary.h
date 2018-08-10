///
/// @file    dictionary.h
/// @author  LiuhuiDing@gmail.com
/// @date    2018-07-27 22:27:40
///
//先用vector实现
//比较简陋，容易实现
#ifndef DICTIONARY_H_
#define DICTIONARY_H_
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iostream>
struct DictionaryItem
{
	std::string word_;
	int times_;
	bool operator<(const DictionaryItem &rhs) const
	{
		return (word_ < rhs.word_) ? true:false;
	}
};
//生成字典文件
class Dictionary
{
public:
	Dictionary();
	Dictionary(const std::string &filename);	//由外部文件初始化
	Dictionary(const Dictionary &dic);	//由其他字典初始化
	~Dictionary();
	void makeDictionary(const std::string&);	//从外部文件建立字典
private:
	bool read(const std::string&);	//对读入的文章进行处理，方便字典统计，生成.dic_make_file文件
	void store(const std::string&);	//从.dic_make_file文件生成.dictionary文件
	std::string dictionary_file_;	//保存字典文件名
	std::string filename_;	//保存字典对应的文件名
};
#endif
