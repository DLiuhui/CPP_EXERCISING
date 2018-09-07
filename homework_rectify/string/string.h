///
/// @file    string.h
/// @author  LiuhuiDing@gmail.com
/// @date    2018-07-30 09:58:21
///

#ifndef STRING_H_
#define STRING_H_
#include <string.h>
#include <iostream>
class String
{
	String():
		pstr_(new char[1]()/*加()会对申请的空间每个单元进行初始化*/)
	{}
	String(const String &s)
		:pstr_(new char[strlen(s.pstr_)+1]())
	{
		strcpy(pstr_, s.pstr_);
	}
	String & operator=(const String &rhs)
	{
		if(this != &rhs)	//如果不是自复制，防止自复制
		{
			delete []pstr_;
			//深拷贝
			pstr_ = new char[strlen(rhs.pstr_)+1];
			strcpy(pstr_, rhs.pstr_);
		}
		return *this;
	}
	~String()
	{
		if(NULL != pstr_)
		{
			delete []pstr_;
		}
	}
	void print() const
	{
		std::cout << pstr_ << std::endl;
	}
private:
	char *pstr_;
};


#endif
