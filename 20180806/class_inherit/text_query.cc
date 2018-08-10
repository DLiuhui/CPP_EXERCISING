///
/// @file    text_query.cc
/// @author  LiuhuiDing@gmail.com
/// @date    2018-08-06 10:37:05
///

#include "text_query.h"

namespace Primer
{
	TextQuery::TextQuery(std::ifstream &is):
		file(new std::vector<std::string>)
	{
		using std::string;
		using std::set;
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

	QueryResult TextQuery::query(const std::string &sought) const
	{
		using std::shared_ptr;
		using std::set;
		//如果未找到sought，我们将返回一个指向此set的指针
		static shared_ptr<set<line_no>> nodata(new set<line_no>);
		//使用find而不是下标，避免单词增加到wm中
		auto loc = wm.find(sought);
		if(loc == wm.end())
			return QueryResult(sought, nodata, file);
		else
			return QueryResult(sought, loc->second, file);
	}
	Query::Query(const std::string &s):
		q(new WordQuery(s))
	{}
	std::ostream &print(std::ostream &os, const QueryResult &qr)
	{
		os << qr.sought << " occurs in " << qr.lines->size() << 
			((qr.lines->size()>1)?" lines":" line") << std::endl;
		//打印出现的每一行
		for(auto num: *qr.lines)
		{
			os << "\tline " << num << ") " << (*qr.file)[num-1] << std::endl;
		}
		return os;
	}
	Query operator~(const Query &operand)
	{
		return std::shared_ptr<Query_base>(new NotQuery(operand));
	}
	Query operator&(const Query &lhs, const Query &rhs)
	{
		return std::shared_ptr<Query_base>(new AndQuery(lhs, rhs));
	}
	Query operator|(const Query &lhs, const Query &rhs)
	{
		return std::shared_ptr<Query_base>(new OrQuery(lhs, rhs));
	}
	std::ostream & operator<<(std::ostream &os, const Query &query)
	{
		return os << query.rep();
	}

	QueryResult NotQuery::eval(const TextQuery &text) const
	{
		//通过Query对象对eval进行虚调用
		auto result = query.eval(text);
		auto ret_lines = std::make_shared<std::set<line_no>>();
		auto beg = result.begin(), end = result.end();
		auto sz = result.getFile()->size();
		for(std::size_t n = 0; n < sz; ++n)
		{
			//如果我们还没有处理完result的所有行
			//检验当前行是否存在
			if(beg == end || *beg != n)
				ret_lines->insert(n);	//如果不在result中，添加这一行
			else if(beg != end)
				++beg;	//否则继续获取下一行
		}
		return QueryResult(rep(), ret_lines, result.getFile());
	}
	QueryResult AndQuery::eval(const TextQuery &text) const
	{
		//通过Query对象对eval进行虚调用
		auto left = lhs.eval(text), right = rhs.eval(text);
		//保存left与right的交集set
		auto ret_lines = std::make_shared<std::set<line_no>>();
		//将两个范围的交集写入一个目的迭代器中
		//本次调用的目的迭代器向ret添加元素
		std::set_intersection(
				left.begin(), left.end(),
				right.begin(), right.end(),
				std::inserter(*ret_lines, ret_lines->begin())
				);
		return QueryResult(rep(), ret_lines, left.getFile());
	}
	QueryResult OrQuery::eval(const TextQuery &text) const
	{
		//通过Query对象对eval进行虚调用
		//调用eval返回每个对象的QueryResult
		auto left = lhs.eval(text), right = rhs.eval(text);
		//保存left与right的并集set
		auto ret_lines = std::make_shared<std::set<line_no>>(left.begin(), left.end());
		ret_lines->insert(right.begin(), right.end());
		//返回新的QueryResult，表示lhs和rhs的并集
		return QueryResult(rep(), ret_lines, left.getFile());
	}
}

