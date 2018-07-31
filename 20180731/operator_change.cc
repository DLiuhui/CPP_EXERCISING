///
/// @file    operator_change.cc
/// @author  LiuhuiDing@gmail.com
/// @date    2018-07-31 17:46:41
///

#include <iostream>
using std::cin;
using std::cout;
using std::endl;

class Complex
{
	public:
		Complex(double dreal = 0, double dimag = 0)
			: _dreal(dreal)
			  , _dimag(dimag)
	{
		cout << "Complex(double, double)" << endl;
	}

		friend std::ostream & operator<<(std::ostream & os, const Complex & rhs);

	private:
		double _dreal;
		double _dimag;
};

std::ostream & operator<<(std::ostream & os, const Complex & rhs)
{
	os << rhs._dreal;
	if(rhs._dimag > 0)
		os << " + " << rhs._dimag << "i";
	else if(rhs._dimag < 0)
		os << " - " << (-1) * rhs._dimag << "i";
	return os;
}

class Point
{
	public:
		Point(int ix = 0, int iy = 0)
			: _ix(ix)
			  , _iy(iy)
	{
		cout << "Point(int,int) " << endl;
	}

		void print() const
		{
			cout << "(" << _ix
				<< "," << _iy
				<< ")";
		}

		friend std::ostream & operator<<(std::ostream & os, const Point & rhs);
		//类型转换函数
		//1、必须是成员函数
		//2、没有参数
		//3、没有返回值类型，但是在函数体内必须以传值的方式返回一个目标类型变量
		//4、能不用就不用
		//
		operator int()
		{
			return _ix * _iy;
		}

		operator Complex()
		{
			return Complex(_ix, _iy);
		}
	private:
		int _ix;
		int _iy;
};

std::ostream & operator<<(std::ostream & os, const Point & rhs)
{
	os << "(" << rhs._ix
		<< "," << rhs._iy
		<< ")";
	return os;
}

int main(void)
{
	Point pt1(1, 2);

	int number = pt1;
	cout << "number = " << number << endl;

	Complex c1(-1, 2);
	cout << "c1 = " << c1 << endl;

	c1 = pt1;// 违反常规思维方式
	cout << "c1 = " << c1 << endl;
	cout << "pt1=" << pt1 << endl;	//会自动将Point对象准换成int型数据
	//隐式类型转化
	return 0;
}
