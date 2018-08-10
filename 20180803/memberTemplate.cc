///
/// @file    memberTemplate.cc
/// @author  LiuhuiDing@gmail.com
/// @date    2018-08-03 14:47:29
///

#include <iostream>
using std::cin;
using std::cout;
using std::endl;

class Point
{
	public:
		Point(double dx = 0, double dy = 0):
			_dx(dx), _dy(dy)
	{}
	//成员函数本身也可以是一个函数模板， 称为成员模板
		template <typename T>
		T typeCast()	//强制类型转换
		{
			return (T)_dx*_dy;
		}
		/*
		//特例化似乎不行
		template <>
		char typeCast<char>()
		{
			char c = 'a';
			cout << "wrong" << endl;
			return c;
		}
		*/
	private:
		double _dx;
		double _dy;
};

int main(int argc, char **argv)
{
	Point pt(1.1, 3.2);
	cout << pt.typeCast<int>() << endl;
	return 0;
}
