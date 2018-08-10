 ///
 /// @file    priority_queue.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2018-08-06 15:54:35
 ///
 
#include <math.h>
#include <iostream>
#include <queue>
#include <vector>
using std::cout;
using std::endl;
using std::vector;
using std::priority_queue;
 
int test0(void)
{
	//默认情况下，是按小于符号进行比较的，得到的是一个降序的排列
	//
	//优先级队列底层实现采用的是堆排序(默认情况下，是一个大顶堆)
	// 当堆顶的元素与新添加的元素进行比较时，如果返回值为true，则
	// 新添加的元素替换堆顶的元素，原来的堆顶的元素进行堆得调整
	//
	int array[10] = {4, 1, 2, 6, 5, 9, 7, 8, 3, 0};
	//priority_queue<int> pque(array, array + 10);
	priority_queue<int> pque;
	for(int idx = 0; idx != 10; ++idx) 
	{
		pque.push(array[idx]);
		cout << "当前队列中优先级别最高的是: " << pque.top() << endl;
	}

	while(!pque.empty())
	{
		cout << pque.top() << " ";
		pque.pop();
	}
	cout << endl;

	return 0;
}

int test1(void)
{
	int array[10] = {4, 1, 2, 6, 5, 9, 7, 8, 3, 0};
	priority_queue<int, vector<int>, std::greater<int>> pque;
	for(int idx = 0; idx != 10; ++idx) 
	{
		pque.push(array[idx]);
		cout << "当前队列中优先级别最高的是: " << pque.top() << endl;
	}

	while(!pque.empty())
	{
		cout << pque.top() << " ";
		pque.pop();
	}
	cout << endl;

	return 0;
}

class Point
{
public:
	Point(int ix = 0, int iy = 0)
	: _ix(ix)
	, _iy(iy)
	{
		//cout << "Point(int=0, int= 0)" << endl;
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
		//cout << "~Point()" << endl;
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


int test2(void)
{
	Point points[] = {
		Point(1, 2),
		Point(3, 4),
		Point(5, 6),
		Point(1, 6)
	};
	//对于标准容器库而言，所有放在其中的元素都要求是能够进行复制的
	//容器中存放的元素都是一个独立的副本

	priority_queue<Point, vector<Point>, std::greater<Point>> pque(points, points + 4);

	while(!pque.empty())
	{
		cout << pque.top() << " ";
		pque.pop();
	}
	cout << endl;

	return 0;
}

int main(void)
{
	test2();
	return 0;
}
