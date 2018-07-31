///
/// @file    complex.h
/// @author  LiuhuiDing@gmail.com
/// @date    2018-07-31 14:42:42
///


#ifndef COMPLEX_H_
#define COMPLEX_H_
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <limits>
namespace wdCoding
{

using std::cin;
using std::cout;
using std::endl;
using std::ostream;
using std::istream;

class ComplexNumber	//复数类
{
	friend ComplexNumber operator+(const ComplexNumber &, const ComplexNumber &);
	friend ComplexNumber operator-(const ComplexNumber &, const ComplexNumber &);
	friend ComplexNumber operator*(const ComplexNumber &, const ComplexNumber &);
	friend ComplexNumber operator/(const ComplexNumber &, const ComplexNumber &);
	friend ostream & operator<<(ostream &, const ComplexNumber &);
	friend istream & operator>>(istream &, ComplexNumber &);	//需要修改rhs
public:
	ComplexNumber(double real = 0.0, double image = 0.0):
		real_(real), imag_(image)
	{}
	ComplexNumber(const ComplexNumber &num):
		real_(num.real_), imag_(num.imag_)
	{}
	void display() const;
	ComplexNumber & operator=(const ComplexNumber &);
	bool operator<(const ComplexNumber &) const;	//只比较实部
	bool operator>(const ComplexNumber &) const;	//只比较实部
	bool operator==(const ComplexNumber &) const;
	ComplexNumber & operator++();	//前置自增
	ComplexNumber & operator--();	//前置自减
	ComplexNumber operator++(int);	//后置自增
	ComplexNumber operator--(int);	//后置自减
	double module() const	//取模
	{
		return sqrt(real_*real_ + imag_*imag_);
	}
private:
	void inputComplexNumber();
	double real_;	//实部
	double imag_;	//虚部
};
ComplexNumber operator+(const ComplexNumber &, const ComplexNumber &);
ComplexNumber operator-(const ComplexNumber &, const ComplexNumber &);
ComplexNumber operator*(const ComplexNumber &, const ComplexNumber &);
ComplexNumber operator/(const ComplexNumber &, const ComplexNumber &);
ostream & operator<<(ostream &, const ComplexNumber &);
istream & operator>>(istream &, ComplexNumber &);	//要修改rhs

#define module(complex_number) complex_number.module()
}


#endif
