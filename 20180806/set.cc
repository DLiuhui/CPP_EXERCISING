///
/// @file    set.cc
/// @author  LiuhuiDing@gmail.com
/// @date    2018-08-04 15:19:54
///

#include <cmath>
#include <set>
#include <utility>
#include <string>
#include <iostream>
using std::cin;
using std::cout;
using std::endl;
using std::set;
using std::string;

	template <typename Container>
void display(const Container & c)
{
	typename Container::const_iterator iter = c.cbegin();	//此处一定要加typename
	while(iter != c.cend())
	{
		cout << *iter << " ";
		++iter;
	}
	cout << endl;
}

void test0()
{
	//set默认情况下，会按升序的方式进行排列
	//set不能存放重复的元素
	//
	//set的底层实现采用的是红黑树
	//查找任意元素的时间复杂度为O(logN) --> 二分查找
	//
	int array[15] = {3,2,6,5,3,5,6,2,2,4,8,9,7,5,6};
	set<int, std::greater<int>> setInt(array, array+15);
	display(setInt);
	//set没有重载[]，不能使用下标运算符
	set<int>::iterator iter = setInt.begin();
	cout << *iter << endl;
	//*iter = 10; 只能读取set中的元素，不能修改
	//
	//添加新的元素，插入返回值的形式为pair
	std::pair<set<int>::iterator, bool> ret = setInt.insert(10);
	if(ret.second)
	{
		cout << "添加成功" << endl;
		cout << "*(ret.first) = " << *(ret.first) << endl;
	}else{
		cout << "添加失败，set之中已经有相应的值" << endl;
	}
	display(setInt);
	//查找方式
	std::size_t cnt = setInt.count(11);
	cout << "cnt = " << cnt << endl;
	cnt = setInt.count(5);
	cout << "cnt = " << cnt << endl;
	auto iter2 = setInt.find(11);
	if(iter2 != setInt.end())
		cout << "查找成功" << *iter2 << endl;
	else
		cout << "查找失败" << endl;
	iter2 = setInt.find(5);
	if(iter2 != setInt.end())
		cout << "查找成功" << *iter2 << endl;
	else
		cout << "查找失败" << endl;
}

class Point
{
	public:
		Point(int ix, int iy):
			_ix(ix), _iy(iy)
	{}

		friend std::ostream & operator<<(std::ostream & os, const Point & rhs);
		float distance() const
		{
			return sqrt(_ix * _ix + _iy * _iy);
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

bool operator<(const Point & lhs, const Point & rhs)
{
	return lhs.distance() < rhs.distance();
}

struct Compare
{
	bool operator()(const Point & lhs, const Point & rhs) const
	{
		return lhs.distance() > rhs.distance();
	}
};

void test1(void)
{
	//使用Compare可以定义Point类在set里的比较方式
	//重载Point的<运算符，可以定义Point的比较方式
	//set默认的排序方式是：升序
	//
	//set实例化的第二个参数可以实例化比较方式
	set<Point, Compare> setPoint{
		//set<Point> setPoint{
			Point(1, 2),
			Point(3, 4),
			Point(5, 6),
			Point(-1, 3),
			Point(1, 2)
		};
		for(auto & point : setPoint) {
			cout << point << endl;
		}
	}

	void test2(void)
	{
		std::pair<string, int> value("hello", 100);
		cout << value.first << " --> " << value.second << endl;
	}
	int main(int argc, char **argv)
	{
		test0();
		test1();
		test2();
		return 0;
	}
