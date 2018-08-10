 ///
 /// @file    vector.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2018-08-06 16:28:12
 ///
 
#include <math.h>
#include <iostream>
#include <vector>
#include <boost/ptr_container/ptr_vector.hpp>
using std::cout;
using std::endl;
using std::vector;
using boost::ptr_vector;

class Point
{
public:
	Point(int ix = 0, int iy = 0)
	: _ix(ix)
	, _iy(iy)
	{
		cout << "Point(int=0, int= 0)" << endl;
	}

	Point(const Point & rhs)
	: _ix(rhs._ix)
	, _iy(rhs._iy)
	{
		//cout << "Point(const Point &)" << endl;
	}

	int getX() const {	return _ix;	}
	int getY() const {	return _iy;	}

	int distance() const {
		return sqrt(_ix * _ix + _iy * _iy);
	}


	~Point()
	{
		cout << "~Point()" << endl;
	}

	friend std::ostream & operator<<(std::ostream & os, const Point & rhs);
	friend bool operator==(const Point & lhs, const Point & rhs);
	friend bool operator>(const Point & lhs, const Point & rhs);

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

bool operator>(const Point & lhs, const Point & rhs)
{
	return lhs.distance() > rhs.distance();
}
//判断两个对象是否相等
bool operator==(const Point & lhs, const Point & rhs)
{
	return lhs._ix == rhs._ix &&
		   rhs._iy == rhs._iy;
}

void test0(void)
{
	vector<Point> points{Point(1, 2), Point(3, 4), Point(5, 6)};
	for(auto & point : points)
	{
		cout << point << " ";
	}

	cout << points[0] << endl;
	cout << endl;
}
 
void test1(void)
{
	vector<Point*> points{new Point(1, 2), new Point(3, 4), new Point(5, 6)};
	for(auto & point : points)
	{
		cout << *point << " ";
	}
	cout << endl;

	for(auto & point : points) 
	{
		delete point;
	}
} 

void test2(void)
{
	//boost提供的指针容器
	//	ptr_vector
	//	ptr_deque
	//	ptr_list
	//	ptr_array
	//
	//	ptr_set
	//	ptr_map
	//	ptr_multiset
	//	ptr_multimap
	//
	//用智能指针可以代替
	ptr_vector<Point> points;
	cout << "points's size = " << points.size() << endl;
	cout << "points's capacity = " << points.capacity() << endl;
	points.push_back(new Point(1, 2));
	cout << "points's size = " << points.size() << endl;
	cout << "points's capacity = " << points.capacity() << endl;
	points.push_back(new Point(3, 4)); 
	cout << "points's size = " << points.size() << endl;
	cout << "points's capacity = " << points.capacity() << endl;
	points.push_back(new Point(5, 6));
	cout << "points's size = " << points.size() << endl;
	cout << "points's capacity = " << points.capacity() << endl;
	points.push_back(new Point(5, 6));
	cout << "points's size = " << points.size() << endl;
	cout << "points's capacity = " << points.capacity() << endl;
	points.push_back(new Point(5, 6));
	cout << "points's size = " << points.size() << endl;
	cout << "points's capacity = " << points.capacity() << endl;
	cout << endl;

	cout << "points[0] = " << points[0] << endl;
	points.replace(0, new Point(10, 11));//替换某一个元素，不会产生内存泄漏
	cout << "points[0] = " << points[0] << endl;

	cout << endl;

	for(auto & elem : points)
	{
		cout << elem << endl;
	}
}

void test3(void)
{
	Point * pts[2] = {new Point(11, 12), new Point(13, 14)};
	ptr_vector<Point> vec(2);
	vec.transfer(vec.begin(), pts, 2);
}


int main(void)
{
	//test0();
	//test1();
	//test2();
	test3();
	return 0;
}
