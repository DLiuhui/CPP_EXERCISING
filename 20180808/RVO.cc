///
/// @file    RVO.cc
/// @author  LiuhuiDing@gmail.com
/// @date    2018-08-30 20:43:47
///

//编译器优化技术
//
#include <iostream>
using std::cin;
using std::cout;
using std::endl;

class Rational
{
	friend const Rational operator*(const Rational& rhs, const Rational& lhs);
	friend const Rational multi(const Rational& rhs, const Rational& lhs);
	public:
	Rational(int numerator = 0, int denominator = 1)
		:n_(numerator), d_(denominator)
	{
		cout << "Construct called" << endl;
	}
	~Rational()
	{
		cout << "Destroy called" << endl;			
	}
	Rational(const Rational& rhs)
		:n_(rhs.n_), d_(rhs.d_)
	{
		cout << "Copy Construct called" << endl;
	}
	int numerator() const { return n_; }
	int denominator() const { return d_; }
	private:
	int n_;
	int d_;
};

const Rational operator*(const Rational& rhs, const Rational& lhs)
{
	return Rational(rhs.n_*lhs.n_, rhs.d_*lhs.d_);
}
const Rational multi(const Rational& rhs, const Rational& lhs)
{
	std::cout << "...Enter operator *()..." << std::endl;
	Rational tmp(lhs.numerator() * rhs.numerator(),
			lhs.denominator() * rhs.denominator());
	std::cout << "...Leave operator *()..." << std::endl;
	return tmp;

}

int main(int argc, char **argv)
{
	Rational x(1,5), y(2,9);
	Rational z = x*y;
	cout << endl;
	Rational m = multi(x, y);
	cout << "calc result: " << z.numerator() << "/" << z.denominator() << endl;
	cout << "calc result: " << m.numerator() << "/" << m.denominator() << endl;
	return 0;
}
