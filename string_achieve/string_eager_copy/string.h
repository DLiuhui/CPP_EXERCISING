///
/// @file    string.h
/// @author  LiuhuiDing@gmail.com
/// @date    2018-07-30 09:58:21
///

#ifndef STRING_H_
#define STRING_H_
#include <iostream>
#include <string>
#include <cstring>
#include <stdexcept>

namespace MyStd
{

	class String
	{
		public:
			String();
			String(const String &);	//拷贝其他字符串
			String(const char *);
			~String();
			String &operator=(const String &);
			String &operator=(const char *);

			String &operator+=(const String &);
			String &operator+=(const char *);

			//当出现str[i] = str[j] 的情况
			//左侧应该是非常量版本，右边必须是常量版本
			char &operator[](std::size_t);	//非常量版本
			const char &operator[](std::size_t) const;	//常量版本

			std::size_t size() const
			{
				return strlen(pstr_);
			}
			const char* c_str() const
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

			friend std::ostream & operator<<(std::ostream &, const String &);
			friend std::istream & operator>>(std::istream &, String &);
			friend String operator+(const String &, const String &);
			friend String operator+(const String &, const char *);
			friend String operator+(const char *, const String &);
		private:
			char *pstr_;	//变长字符串数组
	};

}
#endif
