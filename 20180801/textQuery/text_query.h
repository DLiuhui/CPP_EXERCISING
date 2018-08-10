///
/// @file    text_query.h
/// @author  LiuhuiDing@gmail.com
/// @date    2018-08-01 22:15:36
///

#ifndef TEXT_QUERY_H_
#define TEXT_QUERY_H_
#include <iostream>
#include <string>
#include <cstring>
#include <map>
#include <set>
#include <fstream>
#include <sstream>
#include <vector>
#include <memory>
#include <stdexcept>
namespace Primer
{
	using std::cin;
	using std::cout;
	using std::endl;
	using std::vector;
	using std::string;
	using std::set;
	using std::map;
	using std::shared_ptr;
	using std::make_shared;
	class TextQuery
	{
		public:
			TextQuery();
			~TextQuery();
			void read(const string &);	//从输入文件读入
			void search(const string &) const;	//接收查询的单词，给出结果
		private:
			shared_ptr<vector<string>> ptext_;	//保存文本的每一行
			shared_ptr<map<string, set<int>>> pquery_;	//查询器，查询单词出现的每一行
	};
	TextQuery::TextQuery():
		ptext_(make_shared<vector<string>>()),	//make_share之后一定要加()，可以不放参数
		//不过这也就要求实例化的对象需要有无参构造函数
		pquery_(make_shared<map<string, set<int>>>())
	{}
	TextQuery::~TextQuery() = default;

	void TextQuery::read(const string & filename)
	{
		std::ifstream is(filename);
		if(!is)
		{
			cout << "file open error" << endl;
			return;
		}
		string line;
		string word;
		int line_idx = 0;	//行号
		while(std::getline(is, line))
		{
			ptext_->push_back(line);
			++line_idx;
			std::istringstream ss(line);
			bool flag = true;
			while(ss >> word)
			{
				flag = true;
				for(unsigned int i = 0; i<word.size(); ++i)
				{
					if(std::isdigit(word[i]))
					{
						flag = false;
						break;
					}
				}
				if(flag)
					(*pquery_)[word].insert(line_idx);
			}
		}
	}

	void TextQuery::search(const string &word) const
	{
		//使用find而不是下标，避免单词增加到map容器中
		auto iter = pquery_->find(word);
		if(iter != pquery_->end())	//找到
		{
			std::ofstream os("file");
			//执行打印
			os << iter->first << " occurs " << iter->second.size() <<
				((iter->second.size()>1)?" times":" time") << endl;
			for(auto i = iter->second.cbegin(); i != iter->second.cend(); i++)
			{
				os << *i << ": " << (*ptext_)[(*i)-1] << endl;
			}
			os.close();
		}
	}


	/*
	//C++ Primer 上的TextQuery解决方案

	class QueryResult;	//前向声明
	class TextQuery
	{
	public:
	using line_no = vector<string>::size_type;
	TextQuery(std::ifstream&);
	QueryResult query(const string&) const;
	private:
	shared_ptr<vector<string>> file;	//输入文件
	map<string, shared_ptr<set<line_no>>> wm;
	};

	class QueryResult
	{
	friend std::ostream & print(std::ostream &, const QueryResult &);
	public:
	QueryResult(string s, shared_ptr<set<TextQuery::line_no>> p, shared_ptr<vector<string>> f):
	sought(s), lines(p), file(f)
	{}
	private:
	string sought;
	shared_ptr<set<TextQuery::line_no>> lines;	//行号
	shared_ptr<vector<string>> file;	//输入的文件

	};
	TextQuery::TextQuery(std::ifstream &is):
	file(new vector<string>)
	{
	string text;
	while(std::getline(is, text))
	{
	file->push_back(text);
	int n = file->size();	//行号
	std::istringstream line(text);
	string word;
	while(line >> word)
	{
	auto &lines = wm[word];	//lines是一个智能指针
	if(!lines)	//当我们第一次遇见该单词，指针为空
	lines.reset(new set<line_no>);
	lines->insert(n);
	}
	}
	}
	QueryResult TextQuery::query(const string &sought) const
	{
	//如果未找到sought，我们将返回一个指向此set的指针
	static shared_ptr<set<line_no>> nodata(new set<line_no>);
	//使用find而不是下标，避免单词增加到wm中
	auto loc = wm.find(sought);
	if(loc == wm.end())
	return QueryResult(sought, nodata, file);
	else
	return QueryResult(sought, loc->second, file);
	}
	std::ostream &print(std::ostream &os, const QueryResult &qr)
	{
	os << qr.sought << " occurs " << qr.lines->size() << 
	((qr.lines->size()>1)?" times":" time") << endl;
	//打印出现的每一行
	for(auto num: *qr.lines)
	{
	os << "\tline " << num << ") " << (*qr.file)[num-1] << endl;
	}
	return os;
	}
	*/



}
#endif
