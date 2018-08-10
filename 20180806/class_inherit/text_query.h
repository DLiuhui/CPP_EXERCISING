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
#include <algorithm>
namespace Primer
{
	//C++ Primer 上的TextQuery解决方案
	class QueryResult;	//前向声明
	//基类
	class TextQuery
	{
		public:
			using line_no = std::vector<std::string>::size_type;
			TextQuery(std::ifstream&);
			QueryResult query(const std::string&) const;
		private:
			std::shared_ptr<std::vector<std::string>> file;	//输入文件
			std::map<std::string, std::shared_ptr<std::set<line_no>>> wm;
	};

	class QueryResult
	{
		friend std::ostream & print(std::ostream &, const QueryResult &);
		public:
		QueryResult(std::string s, std::shared_ptr<std::set<TextQuery::line_no>> p, std::shared_ptr<std::vector<std::string>> f):
			sought(s), lines(p), file(f)
		{}
		std::shared_ptr<std::vector<std::string>> getFile() const
		{ return file; }
		typedef std::set<TextQuery::line_no>::iterator iterator;
		typedef std::set<TextQuery::line_no>::const_iterator const_iterator;
		iterator begin()
		{
			return lines->begin();
		}
		iterator end()
		{
			return lines->end();
		}
		const_iterator cbegin()
		{
			return lines->cbegin();
		}
		const_iterator cend()
		{
			return lines->cend();
		}

		private:
		std::string sought;
		std::shared_ptr<std::set<TextQuery::line_no>> lines;	//单词所对应的行号set
		std::shared_ptr<std::vector<std::string>> file;	//输入的文件
	};
	std::ostream & print(std::ostream &, const QueryResult &);

	//抽象基类
	//不希望用户和派生类直接使用，无public成员
	class Query_base
	{
		friend class Query;	//有Query负责与用户对接
		protected:
		using line_no = TextQuery::line_no;	//对于eval函数
		virtual ~Query_base() = default;
		private:
		//eval 返回当前Query匹配的QueryResult
		virtual QueryResult eval(const TextQuery &) const = 0;	//纯虚函数
		//rep 是表示查询的一个string
		virtual std::string rep() const = 0;	//纯虚函数
	};

	class Query	//基类接口
	{
		friend Query operator~(const Query &);
		friend Query operator|(const Query &, const Query &);
		friend Query operator&(const Query &, const Query &);
		friend std::ostream & operator<<(std::ostream &, const Query &);
		public:
		Query(const std::string &);	//构建新的WordQuery类型
		//接口函数：调用对应的Query_base操作，根据q的动态类型
		QueryResult eval(const TextQuery &t) const
		{ return q->eval(t); }
		std::string rep() const 
		{ return q->rep(); }
		private:
		//私有构造函数，不希望用户定义Query_base对象
		Query(std::shared_ptr<Query_base> query):
			q(query) 
		{}
		std::shared_ptr<Query_base> q;	//指向抽象基类的指针
	};

	class WordQuery : public Query_base
	{
		friend class Query;	//Query使用WordQurey类的构造函数
		WordQuery(const std::string &s):
			query_word(s)
		{}
		//具体的类：WordQuery将定义所有继承而来的虚函数
		QueryResult eval(const TextQuery &t) const
		{ return t.query(query_word); }
		std::string rep() const
		{ return query_word; }
		std::string query_word;	//要查找的单词
	};

	class NotQuery : public Query_base
	{
		friend Query operator~(const Query &);
		NotQuery(const Query &q):	//基于已有的Query对象进行转换
			query(q)
		{}
		std::string rep() const { return "~("+query.rep()+")"; }
		QueryResult eval(const TextQuery &) const;
		Query query;
	};

	class BinaryQuery: public Query_base
	{
		protected:
		BinaryQuery(const Query &l, const Query &r, const std::string &s):
			lhs(l), rhs(r), opSym(s)
		{}
		//BinaryQuery不定义eval
		std::string rep() const 
		{ return "(" + lhs.rep() + " " + opSym + " " + rhs.rep() + ")"; }
		Query lhs, rhs;
		std::string opSym;
	};

	class AndQuery : public BinaryQuery
	{
		friend Query operator&(const Query &, const Query &);
		AndQuery(const Query &l, const Query &r):
			BinaryQuery(l, r, "&")
		{}
		//AndQuery继承rep并定义其他纯虚函数
		QueryResult eval(const TextQuery &) const;
	};

	class OrQuery : public BinaryQuery
	{
		friend Query operator|(const Query &, const Query &);
		OrQuery(const Query &l, const Query &r):
			BinaryQuery(l, r, "|")
		{}
		//OrQuery继承rep并定义其他纯虚函数
		QueryResult eval(const TextQuery &) const;
	};
	



}
#endif
