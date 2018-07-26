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
		pos_x_(0), pos_y_(0),
		//refx(0), refy(0)	//引用不能绑定临时量
		//refx(orgin_point_x_), refy(orgin_point_y_)	//非常量引用不能绑定常量引用
		refx(pos_x_), refy(pos_y_)
	{}
	point(int x, int y):
		orgin_point_x_(0), orgin_point_y_(0),
		pos_x_(x), pos_y_(y),
		//refx(0), refy(0)
		//refx(orgin_point_x_), refy(orgin_point_y_)
		//refx(x), refy(y)	//原因同refx(0)
		refx(pos_x_), refy(pos_y_)
	{}
	point(const point &pt):
		orgin_point_x_(pt.orgin_point_x_),
		orgin_point_y_(pt.orgin_point_y_),
		pos_x_(pt.pos_x_),
		pos_y_(pt.pos_y_),
		//refx(pt.pos_x_), refy(pt.pos_y_)	//由于拷贝时，传入参数加了const修饰，所以非const引用用不能引用传入参数的成员（即使是入参的非const成员）
		refx(pt.refx), refy(pt.refy)	//但是可以绑定pt的引用成员
	{}
	void print() const
	{
		cout<< "原点：" << orgin_point_x_ << "," << orgin_point_y_ << " ";
		cout << "point: " << pos_x_ << "," << pos_y_ << endl;
		cout << "连接点:" << refx << "," << refy << endl;
	}
private:
	const int orgin_point_x_;
	const int orgin_point_y_;
	int pos_x_;
	int pos_y_;
	int &refx;
	int &refy;
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
