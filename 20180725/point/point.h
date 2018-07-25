 ///
 /// @file    point.h
 /// @author  LiuhuiDing@gmail.com
 /// @date    2018-07-25 15:48:14
 ///
 
#ifndef POINT_H_
#define POINT_H_

#include <iostream>

class Point
{
public:
	Point();
	Point(const int, const int);
	void print() const;
	~Point();
private:
	int ix_;
	int iy_;
};

Point::Point():
	ix_(0), iy_(0) {}

Point::Point(const int x, const int y):
	ix_(x), iy_(y) {}

void Point::print() const
{
	std::cout << "(" << ix_ << "," << iy_ << ")" << std::endl;
}

Point::~Point()
{
	std::cout << "~Point()" << std::endl;
}
#endif
