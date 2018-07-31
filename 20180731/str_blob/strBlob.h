///
/// @file    strBlob.h
/// @author  LiuhuiDing@gmail.com
/// @date    2018-07-31 09:35:47
///

#ifndef STR_BLOB_H_
#define STR_BLOB_H_
#include <iostream>
#include <vector>
#include <string>
#include <initializer_list>
#include <memory>
#include <stdexcept>

namespace Primer
{

using std::cout;
using std::vector;
using std::shared_ptr;
using std::make_shared;
using std::weak_ptr;
using std::string;

class StrBlobPtr;

class StrBlob
{
	friend StrBlobPtr;
	//使用默认default版本的拷贝、赋值、析构（shared_ptr 和 vector自带这些机制）
public:
	typedef vector<string>::size_type size_type;
	StrBlob();
	explicit StrBlob(std::initializer_list<string>);
	size_type size() const 
	{return data_->size();}
	bool empty() const
	{return data_->empty();}
	void push_back(const string &t)	//添加元素
	{data_->push_back(t);}
	void pop_back();	//删除元素，尾部删除
	string & front();	//访问头元素
	string & back();	//访问尾元素
	StrBlobPtr begin();
	StrBlobPtr end();
private:
	shared_ptr<vector<string>> data_;
	void check(size_type, const string &) const;	//在访问成员数据时检查数据是否存在
};

class StrBlobPtr	//StrBlob指针
{
public:
	StrBlobPtr():
		curr_(0)
	{}
	StrBlobPtr(StrBlob &a, size_t sz = 0):
		wptr_(a.data_), curr_(sz)
	{}
	string & deref() const;
	StrBlobPtr & incr();	//前缀递增
private:
	shared_ptr<vector<string>> check(std::size_t, const string&) const;
	weak_ptr<vector<string>> wptr_;
	std::size_t curr_;
};

}
#endif
