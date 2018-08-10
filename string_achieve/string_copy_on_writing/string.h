///
/// @file    string.h
/// @author  LiuhuiDing@gmail.com
/// @date    2018-07-30 09:58:21
///

#ifndef STRING_H_
#define STRING_H_
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <cstring>
#include <stdexcept>

//基于COW写时复制原理实现String
namespace MyStd
{

	class String
	{
		//定义代理类完成[]区分读写的任务
		//重载<<和=
		class CharProxy
		{
			public:
				CharProxy(String &s, unsigned int index):
					self_(s), index_(index)
				{}
				~CharProxy() = default;
				char & operator=(const char &);
				friend std::ostream & operator<<(std::ostream &, const CharProxy &);
			private:
				String &self_;	//指向string本身
				unsigned int index_;	//记录string的下标
		};
		public:
			String();
			String(const String &);	//拷贝其他字符串
			String(const char *);
			~String();
			String &operator=(const String &);
			String &operator=(const char *);

			String &operator+=(const String &);
			String &operator+=(const char *);
			CharProxy operator[](unsigned int);
			std::size_t size() const
			{
				return size_;
			}
			const char * c_str() const
			{
				return pstr_;
			}

			bool operator==(const String &rhs) const
			{
				return (strcmp(pstr_, rhs.pstr_) == 0)?true:false;
			}
			bool operator!=(const String &rhs) const
			{
				return (strcmp(pstr_, rhs.pstr_) != 0)?true:false;
			}
			bool operator<(const String &rhs) const
			{
				return (strcmp(pstr_, rhs.pstr_) < 0)?true:false;
			}
			bool operator>(const String &rhs) const
			{
				return (strcmp(pstr_, rhs.pstr_) > 0)?true:false;
			}
			bool operator<=(const String &rhs) const
			{
				return (strcmp(pstr_, rhs.pstr_) <= 0)?true:false;
			}
			bool operator>=(const String &rhs) const
			{
				return (strcmp(pstr_, rhs.pstr_) >= 0)?true:false;
			}
			static const int INITIAL_SIZE = 16;
			friend std::ostream & operator<<(std::ostream &, const String &);
			friend std::istream & operator>>(std::istream &, String &);
			friend String operator+(const String &, const String &);
			friend String operator+(const String &, const char *);
			friend String operator+(const char *, const String &);
			friend std::ostream & operator<<(std::ostream &, const CharProxy &);
			unsigned int getRefcnt() {return *(unsigned int*)(pstr_-4);}	//返回引用计数
		private:
			void allocChar();	//为字符串数组开辟新的空间
			char *pstr_;	//变长字符串数组
			unsigned int size_;	//当前字符串大小
			unsigned int capacity_;	//字符串存储空间容量
	};
#define RefcntInc(pstr_) ++(*(unsigned int*)(pstr_-4))	//引用计数+1
#define RefcntDec(pstr_) --(*(unsigned int*)(pstr_-4))	//引用计数-1
#define InitRefcnt(pstr_) *(unsigned int*)(pstr_-4) = 1	//初始化引用计数为1
}
#endif
