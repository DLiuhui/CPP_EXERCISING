///
/// @file    string.cc
/// @author  LiuhuiDing@gmail.com
/// @date    2018-07-31 20:31:06
///

#include "string.h"

namespace MyStd
{
	void String::allocChar()
	{
		void *p = new char[capacity_+4]();	//4个字节用于保存引用计数
		pstr_ = (char*)((char*)p+4);	//偏移四个字节保存字符串
		InitRefcnt(pstr_);	//引用计数=1
	}
	String::String():	//0参构造
		size_(0), capacity_(INITIAL_SIZE)
	{
		allocChar();
	}
	String::String(const String &str):
		pstr_(str.pstr_), size_(str.size_), capacity_(str.capacity_)
	{
		RefcntInc(pstr_);	//str引用计数+1
	}
	String::String(const char *str):
		size_(strlen(str)), capacity_(INITIAL_SIZE)
	{
		while(capacity_ < size_+1)
		{
			capacity_ *= 2;	//capacity扩容
		}
		allocChar();
		memcpy(pstr_, str, size_);
	}
	String::~String()
	{
		if(RefcntDec(pstr_) != 0)	//引用计数不为0
		{
			pstr_ = nullptr;
		}
		else
		{
			delete [](pstr_-4);
			pstr_ = nullptr;
		}
	}
	String & String::operator=(const String &rhs)
	{
		if(this != &rhs)	//防止自复制
		{
			if(RefcntDec(pstr_) == 0)	//左侧引用计数为0
			{
				delete [](pstr_-4);
			}
			pstr_ = rhs.pstr_;
			size_ = rhs.size_;
			capacity_ = rhs.capacity_;
			RefcntInc(pstr_);	//引用计数+1
		}
		return *this;
	}
	String & String::operator=(const char *str)
	{
		//重用上方重载的=
		*this = String(str);
		/*
		if(0 != strcmp(pstr_, str))	//如果字符串不相等
		{
			bool enough = true;
			size_ = strlen(str);
			while(capacity_ < size_ + 1)
			{
				capacity_ *= 2;
				enough = false;
			}
			if(RefcntDec(pstr_) == 0)	//左侧引用计数为0
			{
				if(enough)	//现有空间够用
				{
					memcpy(pstr_, str, size_);
					pstr_[size_] = '\0';
					RefcntInc(pstr_);	//引用计数+1
				}
				else	//不够用，重新分配
				{
					delete [](pstr_-4);
					allocChar();
					memcpy(pstr_, str, size_);
				}
			}
			else
			{
				//不为0，无需清理，为新的字符串申请空间
				allocChar();
				memcpy(pstr_, str, size_);
			}
		}
		*/
		return *this;
	}
	String & String::operator+=(const String &str)
	{
		bool enough = true;
		size_ = size_ + str.size_;
		while(capacity_ < size_ + 1)
		{
			capacity_ *= 2;	//扩容
			enough = false;
		}
		if(RefcntDec(pstr_) == 0)
		{
			if(enough)	//现有空间够用
			{
				strcat(pstr_, str.pstr_);	//追加
				RefcntInc(pstr_);	//ref+1
			}
			else
			{
				char *p = pstr_;
				allocChar();
				sprintf(pstr_, "%s%s", p, str.pstr_);
				delete [](p-4);
			}
		}
		else	//直接重新分配
		{
			char *p = pstr_;
			allocChar();
			sprintf(pstr_, "%s%s", p, str.pstr_);
		}
		return *this;
	}
	String & String::operator+=(const char *str)
	{	
		//重用上方重载的+=
		*this += String(str);
		/*
		bool enough = true;
		size_ = size_ + strlen(str);
		while(capacity_ < size_ + 1)
		{
			capacity_ *= 2;	//扩容
			enough = false;
		}
		if(RefcntDec(pstr_) == 0)
		{
			if(enough)	//现有空间够用
			{
				strcat(pstr_, str);	//追加
				RefcntInc(pstr_);	//ref+1
			}
			else
			{
				char *p = pstr_;
				allocChar();
				sprintf(pstr_, "%s%s", p, str);
				delete [](p-4);
			}
		}
		else	//直接重新分配
		{
			char *p = pstr_;
			allocChar();
			sprintf(pstr_, "%s%s", p, str);
		}
		*/
		return *this;
	}
	String::CharProxy String::operator[](unsigned int index)	
	{
		if(index >= size())	//访问越界
		{
			throw std::out_of_range("visit out of range");
		}
		else
		{
			return CharProxy(*this, index);	//返回的不是对象本身，不能返回引用
		}
	}
	/*
	const char & String::operator[](std::size_t index) const
	{
		if(index >= size_)	//访问越界
		{
			throw std::out_of_range("visit out of range");
		}
		else
		{
			return pstr_[index];
		}
	}
	*/
	std::ostream & operator<<(std::ostream &os, const String &s)
	{
		os << s.pstr_;
		return os;
	}
	std::istream & operator>>(std::istream &is, String &s)
	{
		//任意输入时不知道输入的数量
		//可以使用vector<char>
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
		s = p;
		delete []p;
		return is;
	}
	String operator+(const String &lhs, const String &rhs)
	{
		char *p = new char[lhs.size_ + rhs.size_ + 1]();
		sprintf(p, "%s%s", lhs.pstr_, rhs.pstr_);
		String s(p);
		delete []p;
		return s;
	}
	String operator+(const String &lhs, const char *rhs)
	{
		//重用上方重载的+
		return lhs + String(rhs);
		/*
		char *p = new char[lhs.size_ + strlen(rhs) + 1]();
		sprintf(p, "%s%s", lhs.pstr_, rhs);
		String s(p);
		delete []p;
		return s;
		*/
	}
	String operator+(const char *lhs, const String &rhs)
	{
		//重用上方重载的+
		return String(lhs) + rhs;
		/*
		char *p = new char[strlen(lhs) + rhs.size_ + 1]();
		sprintf(p, "%s%s", lhs, rhs.pstr_);
		String s(p);
		delete []p;
		return s;
		*/
	}
	char & String::CharProxy::operator=(const char &c)
	{
		if(self_.getRefcnt()==1)	//引用计数为1，直接修改
		{
			self_.pstr_[index_] = c;
		}
		else
		{
			char *p = self_.pstr_;
			RefcntDec(self_.pstr_);
			self_.allocChar();
			memcpy(self_.pstr_, p, self_.size_);
			self_.pstr_[index_] = c;
		}
		return self_.pstr_[index_];
	}
	//<<运算符的二重载，第一个版本是os<<String, 第二个版本是os<<CharProxy
	std::ostream & operator<<(std::ostream &os, const String::CharProxy &rhs)
	{
		os << rhs.self_.pstr_[rhs.index_];
		return os;
	}
}
