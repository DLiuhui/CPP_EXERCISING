 ///
 /// @file    point.cc
 /// @author  LiuhuiDing@gmail.com
 /// @date    2018-07-26 11:01:51
 ///
 
#include <iostream>
using std::cin;
using std::cout;
using std::endl;
 
class point
{
public:
	point():
		orgin_point_x_(0), orgin_point_y_(0),
		pos_x_(0), pos_y_(0)
	{}
	point(int x, int y):
		orgin_point_x_(0), orgin_point_y_(0),
		pos_x_(x), pos_y_(y)
	{}
	point(const point &pt):
		orgin_point_x_(pt.orgin_point_x_),
		orgin_point_y_(pt.orgin_point_y_),
		pos_x_(pt.pos_x_),
		pos_y_(pt.pos_y_)
	{}
	void print() const
	{
		cout<< "原点：" << orgin_point_x_ << "," << orgin_point_y_ << " ";
		cout << "point: " << pos_x_ << "," << pos_y_ << endl;
	}
private:
	const int orgin_point_x_;
	const int orgin_point_y_;
	int pos_x_;
	int pos_y_;
};
int main(int argc, char **argv)
{
	point pt1(3,4);
	pt1.print();
	point pt2(pt1);
	pt2.print();
	point pt3;
	pt3.print();
	return 0;
}
