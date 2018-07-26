 ///
 /// @file    string.h
 /// @author  LiuhuiDing@gmail.com
 /// @date    2018-07-25 21:01:24
 ///
 
#ifndef MY_STRING_H_
#define MY_STRING_H_
#include <stdio.h>
#include <string.h>
#include <iostream>

class String
{
public:
	String();
	String(const String&);
	String(const char*);
	String & operator=(const String&);
	String & operator=(const char*);
	~String();
	void print() const;	//查看字符串
	void print_use() const;	//查看引用计数（调试用，防止内存泄露）
private:
	char *str_;	//字符串
	int *use_count_;	//引用计数
};
 
#endif
