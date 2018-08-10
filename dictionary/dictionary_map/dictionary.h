///
/// @file    dictionary.h
/// @author  LiuhuiDing@gmail.com
/// @date    2018-07-27 22:27:40
///
//使用map容器实现
#ifndef DICTIONARY_H_
#define DICTIONARY_H_
#include <map>
#include <set>
#include <utility>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
//生成字典文件
class Dictionary
{
public:
	Dictionary();
	Dictionary(const std::string &filename);	//由外部文件初始化
	Dictionary(const Dictionary &dic);	//由其他字典初始化
	~Dictionary();
	void makeDictionary(const std::string&);	//从外部文件建立字典
	bool read(const std::string&);	//对读入的文章进行处理，方便字典统计，使用map保存
	void store(const std::string&);	//从.dic_make_file文件生成.dictionary文件
private:
	bool wordStandard(const std::string &) const;
	std::map<std::string, int> container_;	//存储容器
	std::string filename_;	//保存字典对应的文件名
};
#endif
