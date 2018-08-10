///
/// @file    string_charproxy.cc
/// @author  LiuhuiDing@gmail.com
/// @date    2018-08-02 17:48:20
///
#include <stdio.h>
#include <string>
#include <cstring>
#include <iostream>
using std::cin;
using std::cout;
using std::endl;

//string类
//由于重载[]运算符存在无法区分读写的问题
//所以此时可以采用在string类里定义 代理类charProxy
//由charProxy类代理 为[]返回值区分读写的问题
//这样当str[i]只是执行读操作不会对str进行复制
//
//新的设计模式：代理模式
//
class String
{

	class CharProxy
	{
		friend std::ostream & operator<<(std::ostream &os, const CharProxy &rhs);
		public:
		CharProxy(String &self, unsigned int idx):
			_self(self), _idx(idx)
		{}

		char & operator=(const char &ch)
		{
			if(_idx < _self.size())
			{
				if(_self.refCount() > 1)	//进行复制
				{
					_self.decreaseRefcount();
					char *ptmp = new char[_self.size() + 5]() + 4;
					strcpy(ptmp, _self._pstr);
					_self._pstr = ptmp;
					_self.initRefcount();
				}
				//直接修改
				_self._pstr[_idx] = ch;
			}
			return _self._pstr[_idx];
		}
		//类型转换函数
		//如果在不重载<<运算符的情况下
		//因为可能要对该字符进行输出，以char型式输出，此时就需要进行类型转换
		operator char()	//隐式类型转换
		{ return _self._pstr[_idx];}
		private:
		String &_self;
		unsigned int _idx;
	};
	friend std::ostream & operator<<(std::ostream &os, const CharProxy &rhs);
	public:
	String():
		_pstr(new char[5]+4)
	{
		initRefcount();
	}
	String(const char *pstr):
		_pstr(new char[strlen(pstr)+5]() + 4)
	{
		strcpy(_pstr, pstr);
		initRefcount();
	}
	String(const String &rhs):
		_pstr(rhs._pstr)
	{
		increaseRefconut();
	}
	String & operator=(const String &rhs)
	{
		if(this != &rhs)
		{
			release();
			_pstr = rhs._pstr;
			increaseRefconut();
		}
		return *this;
	}
	~String()
	{
		release();
	}
	unsigned int size() const {return strlen(_pstr);}
	const char *c_str() const {return _pstr;}
	unsigned int refCount() const {return *(int*)(_pstr-4);}

	CharProxy operator[](unsigned int idx)
	{
		return CharProxy(*this, idx);
	}
	friend std::ostream & operator<<(std::ostream &os, const String &rhs);
	private:
	void initRefcount() {*(int*)(_pstr-4)=1;}
	void increaseRefconut() {++(*(int*)(_pstr-4));}
	void decreaseRefcount() {--(*(int*)(_pstr-4));}
	void release()
	{
		decreaseRefcount();
		if(refCount() == 0)
		{
			delete [](_pstr-4);
		}
	}
	char *_pstr;
};

//函数要使用String的私有类CharProxy和CharProxy的私有成员_self
//所以需要在String和CharProxy里都进行友元的声明
std::ostream & operator<<(std::ostream &os, const String::CharProxy &rhs)
{
	os << rhs._self._pstr[rhs._idx];
	return os;
}
std::ostream & operator<<(std::ostream &os, const String &rhs)
{
	os << rhs._pstr;
	return os;
}

int test0(void)
{
	String s1;
	String s2 = s1;
	cout << "s1 = " << s1 << endl;
	cout << "s2 = " << s2 << endl;
	cout << "s1 's refcount = " << s1.refCount() << endl;
	cout << "s2 's refcount = " << s2.refCount() << endl;

	return 0;
}

void test1(void)
{
	String s1 = "hello,world";
	String s2 = s1;
	cout << "s1 = " << s1 << endl;
	cout << "s2 = " << s2 << endl;
	cout << "s1 's refcount = " << s1.refCount() << endl;
	cout << "s2 's refcount = " << s2.refCount() << endl;
	printf("s1' address = %p\n", s1.c_str());
	printf("s2' address = %p\n", s2.c_str());

	cout << endl;
	String s3 = "shenzhen";
	printf("s3' address = %p\n", s3.c_str());
	cout << "s3 = " << s3 << endl;
	s3 = s1;
	cout << endl << " >> 执行赋值运算符操作:" << endl;
	cout << "s1 = " << s1 << endl;
	cout << "s2 = " << s2 << endl;
	cout << "s3 = " << s3 << endl;
	cout << "s1 's refcount = " << s1.refCount() << endl;
	cout << "s2 's refcount = " << s2.refCount() << endl;
	cout << "s3 's refcount = " << s3.refCount() << endl;
	printf("s1' address = %p\n", s1.c_str());
	printf("s2' address = %p\n", s2.c_str());
	printf("s3' address = %p\n", s3.c_str());

	cout << endl;
	s3[0] = 'X';
	cout << "执行修改操作:" << endl;
	cout << "s1 = " << s1 << endl;
	cout << "s2 = " << s2 << endl;
	cout << "s3 = " << s3 << endl;
	cout << "s1 's refcount = " << s1.refCount() << endl;
	cout << "s2 's refcount = " << s2.refCount() << endl;
	cout << "s3 's refcount = " << s3.refCount() << endl;
	printf("s1' address = %p\n", s1.c_str());
	printf("s2' address = %p\n", s2.c_str());
	printf("s3' address = %p\n", s3.c_str());

	cout << endl;
	cout << "s1[0] = " << s1[0] << endl;
	cout << "对 s1进行读操作" << endl;
	cout << "s1 = " << s1 << endl;
	cout << "s2 = " << s2 << endl;
	cout << "s3 = " << s3 << endl;
	cout << "s1 's refcount = " << s1.refCount() << endl;
	cout << "s2 's refcount = " << s2.refCount() << endl;
	cout << "s3 's refcount = " << s3.refCount() << endl;
	printf("s1' address = %p\n", s1.c_str());
	printf("s2' address = %p\n", s2.c_str());
	printf("s3' address = %p\n", s3.c_str());

}

int main(void)
{
	test1();

	return 0;
}
