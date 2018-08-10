///
/// @file    unodered_set.cc
/// @author  LiuhuiDing@gmail.com
/// @date    2018-08-06 20:31:30
///

#include <unordered_set>
#include <iostream>
using std::cin;
using std::cout;
using std::endl;
using std::unordered_set;

class Point
{
	public:
		Point(int ix = 0, int iy = 0):
			_ix(ix), _iy(iy)
	{
		cout << "Point(int=0, int= 0)" << endl;
	}
		int getX() const {	return _ix;	}
		int getY() const {	return _iy;	}
		~Point()
		{
			cout << "~Point()" << endl;
		}
		friend std::ostream & operator<<(std::ostream & os, const Point & rhs);
		friend bool operator==(const Point & lhs, const Point & rhs);
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

bool operator==(const Point &lhs, const Point &rhs)
{
	return lhs._ix == rhs._ix && rhs._iy == lhs._iy;
}

//为标准库的hash函数特例化
namespace std
{
	//std::hash
	template<>
		struct hash<Point>
		{
			size_t operator()(const Point & lhs) const
			{
				return (std::hash<int>()(lhs.getX()) << 1)
					^ (std::hash<int>()(lhs.getY()) >> 1);
			}
		};
}

//为对象重载单参数函数调用运算符
struct PointHasher
{
	size_t operator()(const Point & lhs) const
	{
		return (std::hash<int>()(lhs.getX()) << 1)
			^ (std::hash<int>()(lhs.getY()) >> 1);
	}
};

void test0(void)
{
	unordered_set<int> sets{5, 3, 2, 1, 3, 2, 8, 0, 9};
	for(auto & elem : sets)
	{
		cout << elem << endl;
	}
}

void test1(void)
{
	//容器在增加对象时均进行了拷贝操作
	unordered_set<Point> sets{
		Point(1, 2),
			Point(3, 4),
			Point(1, 2),
			Point(5, 6)
	};

	for(auto & elem : sets)
	{
		cout << elem << endl;
	}
}


void test2(void)
{
	unordered_set<Point, PointHasher> sets{
		Point(1, 2),
			Point(3, 4),
			Point(1, 2),
			Point(5, 6)
	};

	for(auto & elem : sets)
	{
		cout << elem << endl;
	}
}

int main(void)
{
	test0();
	test1();
	test2();
	return 0;
}
