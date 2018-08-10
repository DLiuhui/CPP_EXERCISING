 ///
 /// @file    string.cc
 /// @author  LiuhuiDing@gmail.com
 /// @date    2018-07-25 21:20:02
 ///
 
#include "string.h"

String::String():
	str_(new char[1]()), use_count_(new int(1))
{
	//str_[0] = '\0';	//可以不用
}

String::String(const String &str):
	str_(str.str_)/*此处直接把字符串首地址交给this->str,不用额外开辟空间，不然内存泄露*/,
	use_count_(str.use_count_)	//与str共享引用计数
{
	++*use_count_;	//引用计数+1
}

String::String(const char *str):
	str_(new char[strlen(str)+1/*需要考虑\0*/]()), use_count_(new int(1))/*引用计数为1*/
{
	strcpy(str_, str);
}

String & String::operator=(const String &rhs)
{
	++*rhs.use_count_;	//右侧引用计数+1
	--*use_count_;	//等号左侧引用计数-1
	if(0 == *use_count_)	//引用计数为0
	{
		delete use_count_;
		delete []str_;
	}
	str_ = rhs.str_;	/*此处直接把字符串首地址交给this->str,不用额外开辟空间，不然内存泄露*/
	use_count_ = rhs.use_count_;	//引用计数指向右侧
	return *this;
}

String & String::operator=(const char *str)
{
	--*use_count_;
	if(0 == *use_count_)
	{
		delete use_count_;
		delete []str_;
	}
	str_ = new char[strlen(str)+1];
	strcpy(str_, str);
	use_count_ = new int(1);
	return *this;
}

String::~String()
{
	--*use_count_;
	std::cout << *use_count_ << std::endl;
	if(0 == *use_count_)
	{
		delete use_count_;
		delete []str_;
	}
}

void String::print() const
{
	std::cout << str_ << std::endl;
}

void String::print_use() const
{
	std::cout << *use_count_ << std::endl;
}
