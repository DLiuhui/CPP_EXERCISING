///
/// @file    dictionary.h
/// @author  LiuhuiDing@gmail.com
/// @date    2018-07-27 22:27:40
///
#ifndef DICTIONARY_H_
#define DICTIONARY_H_
#include "queue.h"
#include <ctype.h>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
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
	~Dictionary();
	void makeDictionary(const std::string&);	//从外部文件建立字典
	bool read(const std::string&);	//对读入的文章进行处理，方便字典统计，生成字典队列dic_queue
	void store(const std::string&);	//从dic_queue生成.dictionary文件
private:
	bool wordStandardizing(std::string&);	//对单词标准化处理
	std::string filename_;	//保存字典对应的文件名
	Queue dic_queue_;	//存储字典序列
};
#endif
