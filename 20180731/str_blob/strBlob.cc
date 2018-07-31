///
/// @file    strBlob.cc
/// @author  LiuhuiDing@gmail.com
/// @date    2018-07-31 10:26:10
///

#include "strBlob.h"

namespace Primer
{

StrBlob::StrBlob():
	data_(make_shared<vector<string>>())
{}

StrBlob::StrBlob(std::initializer_list<string> li)
	:data_(make_shared<vector<string>>(li))
{}


void StrBlob::check(StrBlob::size_type i, const string &msg) const	//
{
	if(i >= data_->size())
	{
		throw std::out_of_range(msg);
	}
}

void StrBlob::pop_back()
{
	check(0, "pop_back on empty StrBlob");
	data_->pop_back();
}

string & StrBlob::front()
{
	check(0, "front on empty StrBlob");
	return data_->front();
}

string & StrBlob::back()
{
	check(0, "front on empty StrBlob");
	return data_->back();
}

StrBlobPtr StrBlob::begin()
{
	return StrBlobPtr(*this);
}
StrBlobPtr StrBlob::end()
{
	auto ret = StrBlobPtr(*this, data_->size());
	return ret;
}
shared_ptr<vector<string>> StrBlobPtr::check(std::size_t i, const string &msg) const
{
	auto ret = wptr_.lock();	//vector是否存在？
	if(!ret)
		throw std::runtime_error("unbound StrBlobPtr");
	if(i >= ret->size())
	{
		throw std::out_of_range(msg);
	}
	return ret;
}

string & StrBlobPtr::deref() const
{
	auto p = check(curr_, "deference past end");
	return (*p)[curr_];	//（*p）对象所指向的vector
}

StrBlobPtr & StrBlobPtr::incr()
{
	check(curr_, "increment past end of StrBlobPtr");
	++curr_;
	return *this;
}

}
