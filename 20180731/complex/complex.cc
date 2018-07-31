///
/// @file    complex.cc
/// @author  LiuhuiDing@gmail.com
/// @date    2018-07-31 15:03:51
///

#include "complex.h"

namespace wdCoding
{

void ComplexNumber::inputComplexNumber()
{
	cout << "输入复数实部：";
	while(cin >> real_ || !cin.eof())
	{
		if(cin.bad())
		{
			printf("input stream dump");
			exit(1);
		}
		else if(cin.fail())
		{
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			continue;
		}
		else
		{
			break;
		}
	}
	cout << "输入复数虚部：";
	while(cin >> imag_ || !cin.eof())
	{
		if(cin.bad())
		{
			printf("input stream dump");
			exit(1);
		}
		else if(cin.fail())
		{
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			continue;
		}
		else
		{
			break;
		}
	}
}

void ComplexNumber::display() const
{
	cout << real_;
	if(imag_<0)
	{
		cout << "-" << (-1)*imag_ << "i" << endl;
	}
	else
	{
		cout << "+" << imag_ << "i" << endl;
	}
}

ComplexNumber & ComplexNumber::operator=(const ComplexNumber &rhs)
{
	real_ = rhs.real_;
	imag_ = rhs.imag_;
	return *this;
}

bool ComplexNumber::operator<(const ComplexNumber &rhs) const
{
	return (real_<rhs.real_)?true:false;
}

bool ComplexNumber::operator>(const ComplexNumber &rhs) const
{
	return (real_>rhs.real_)?true:false;
}

bool ComplexNumber::operator==(const ComplexNumber &rhs) const
{
	return (real_==rhs.real_ && imag_==rhs.imag_)?true:false;
}
ComplexNumber & ComplexNumber::operator++()
{
	real_ = real_+1;
	imag_ = imag_+1;
	return *this;
}
ComplexNumber & ComplexNumber::operator--()
{
	real_ = real_-1;
	imag_ = imag_-1;
	return *this;
}
ComplexNumber ComplexNumber::operator++(int)
{
	ComplexNumber ret = *this;
	real_ = real_+1;
	imag_ = imag_+1;
	return ret;
}
ComplexNumber ComplexNumber::operator--(int)
{	
	ComplexNumber ret = *this;
	real_ = real_-1;
	imag_ = imag_-1;
	return ret;
}

ComplexNumber operator+(const ComplexNumber &lhs, const ComplexNumber &rhs)
{
	return ComplexNumber(lhs.real_+rhs.real_, lhs.imag_+rhs.imag_);
}

ComplexNumber operator-(const ComplexNumber &lhs, const ComplexNumber &rhs)
{
	return ComplexNumber(lhs.real_-rhs.real_, lhs.imag_-rhs.imag_);
}

ComplexNumber operator*(const ComplexNumber &lhs, const ComplexNumber &rhs)
{
	return ComplexNumber(lhs.real_ * rhs.real_ - lhs.imag_*rhs.imag_,
			lhs.imag_ * rhs.real_ + lhs.real_*rhs.imag_);
}
ComplexNumber operator/(const ComplexNumber &lhs, const ComplexNumber &rhs)
{
	return ComplexNumber((lhs.real_ * rhs.real_ + lhs.imag_*rhs.imag_)/module(rhs),
			(lhs.imag_*rhs.real_ - lhs.real_*rhs.imag_)/module(rhs));
}
ostream & operator<<(ostream &os, const ComplexNumber &rhs)
{
	os << rhs.real_;
	if(rhs.imag_<0)
	{
		os << "-" << (-1)*rhs.imag_ << "i";
	}
	else
	{
		os << "+" << rhs.imag_ << "i";
	}
	return os;
}
istream & operator>>(istream &is, ComplexNumber &rhs)
{
	rhs.inputComplexNumber();
	return is;
}

}
