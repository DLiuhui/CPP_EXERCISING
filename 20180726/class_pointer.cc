 ///
 /// @file    class_pointer.cc
 /// @author  LiuhuiDing@gmail.com
 /// @date    2018-07-26 15:40:06
 ///
 
#include <iostream>
using std::cin;
using std::cout;
using std::endl;
 
class point
{
public:
	point(int xp = 0, int yp = 0):
		x(xp), y(yp)
	{}
	~point()
	{
		cout << "xx" << endl;
	}
	void print() const
	{
		cout << x << "," << y << endl;
	}
	void Set(int xp, int yp)
	{
		x = xp;
		y = yp;
	}
private:
	int x;
	int y;
};
int main(int argc, char **argv)
{
	point *p = new point[2];	//申请动态内存，p得到连续空间首地址
	p[0].print();
	p[1].Set(4,5);
	p[1].print();
	delete []p;
	p = NULL;	//防止野指针
	return 0;
}
