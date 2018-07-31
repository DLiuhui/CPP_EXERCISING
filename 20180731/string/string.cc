///
/// @file    string.cc
/// @author  LiuhuiDing@gmail.com
/// @date    2018-07-31 20:31:06
///

#include "string.h"

namespace MyStd
{
	String::String():
		pstr_(new char[1]())
	{}
	String::String(const String &str):
		pstr_(new char[strlen(str.pstr_) + 1]())
	{
		strcpy(pstr_, str.pstr_);
	}
	String::String(const char *str):
		pstr_(new char[strlen(str) + 1]())
	{
		strcpy(pstr_, str);
	}
	String::~String()
	{
		if(NULL != pstr_)
		{
			delete []pstr_;
		}
	}
	String & String::operator=(const String &rhs)
	{
		if(this != &rhs)	//防止自复制
		{
			delete []pstr_;
			pstr_ = new char[strlen(rhs.pstr_) + 1]();
			strcpy(pstr_, rhs.pstr_);	//深拷贝
		}
		return *this;
	}
	String & String::operator=(const char *str)
	{
		if(0 != strcmp(pstr_, str))	//如果字符串不相等
		{
			delete []pstr_;
			pstr_ = new char[strlen(str) + 1]();
			strcpy(pstr_, str);
		}
		return *this;
	}
	String & String::operator+=(const String &str)
	{
		char *p = pstr_;
		pstr_ = new char[strlen(p) + strlen(str.pstr_) + 1]();
		sprintf(pstr_, "%s%s", p, str.pstr_);
		delete []p;
		return *this;
	}
	String & String::operator+=(const char *str)
	{
		char *p = pstr_;
		pstr_ = new char[strlen(p) + strlen(str) + 1]();
		sprintf(pstr_, "%s%s", p, str);
		delete []p;
		return *this; 
	}
	char & String::operator[](std::size_t index)
	{
		if(index >= size())	//访问越界
		{
			throw std::out_of_range("visit out of range");
		}
		else
		{
			return pstr_[index];
		}
	}
	const char & String::operator[](std::size_t index) const
	{
		if(index >= size())	//访问越界
		{
			throw std::out_of_range("visit out of range");
		}
		else
		{
			return pstr_[index];
		}
	}
	std::ostream & operator<<(std::ostream &os, const String &s)
	{
		os << s.pstr_;
		return os;
	}
	std::istream & operator>>(std::istream &is, String &s)
	{
		//任意输入时不知道输入的数量
		int pre_size = 100;
		char *p = new char[pre_size]();
		char c;
		int index = 0;
		while(is.get(c) && c!='\n')
		{
			if(index == pre_size)
			{
				pre_size *= 2;
				char *q = p;
				memcpy(p, q, index);
				delete []q;
			}
			p[index++] = c;
		}
		if(s.pstr_)
		{
			delete []s.pstr_;
		}
		s.pstr_ = new char[index + 1];
		strcpy(s.pstr_, p);
		delete []p;
		return is;
	}
	String operator+(const String &lhs, const String &rhs)
	{
		char *p = new char[strlen(lhs.pstr_) + strlen(rhs.pstr_) + 1]();
		sprintf(p, "%s%s", lhs.pstr_, rhs.pstr_);
		String s(p);
		delete []p;
		return s;
	}
	String operator+(const String &lhs, const char *rhs)
	{
		char *p = new char[strlen(lhs.pstr_) + strlen(rhs) + 1]();
		sprintf(p, "%s%s", lhs.pstr_, rhs);
		String s(p);
		delete []p;
		return s;
	}
	String operator+(const char *lhs, const String &rhs)
	{
		char *p = new char[strlen(lhs) + strlen(rhs.pstr_) + 1]();
		sprintf(p, "%s%s", lhs, rhs.pstr_);
		String s(p);
		delete []p;
		return s;
	}

}
