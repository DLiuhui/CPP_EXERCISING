///
/// @file    map.cc
/// @author  LiuhuiDing@gmail.com
/// @date    2018-08-04 14:57:31
///

#include <string>
#include <iostream>
#include <map>
using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::map;
//map的一些拓展用法

int array[5] = {1,2,3,4,5};

	template <typename Container>
void display(const Container & c)	//使用通用的关联容器
{
	typename Container::const_iterator iter;	//此处一定也要加typename
	for(iter = c.cbegin(); iter != c.cend(); ++iter)
	{
		cout << iter->first << "-->" << iter->second << endl;
	}
}

void test0(void)
{
	//map默认情况下，按照升序进行排序std::less()
	//map初始化时指定 第三个参数：置入用户需要的排序函数
	//或者使用标准库
	//不能存放关键字相同但是值不同的元素，优先保存先插入的元素
	//
	//降序
	map<int, string, std::greater<int>> cities{
		std::pair<int, string>(1, "北京"),
			std::pair<int, string>(2, "上海"),
			std::make_pair(3, "广州"),
			std::make_pair(4, "深圳"),
			std::make_pair(1, "杭州")	//此处的 杭州无法覆盖 北京
	};
	display(cities);
	//升序
	map<int, string/*, std::less<int>*/> cities2{
		std::pair<int, string>(2, "上海"),
			std::make_pair(3, "广州"),
			std::make_pair(4, "深圳"),
			std::make_pair(1, "杭州")
	};
	display(cities2);
	//map可以使用下标访问运算符, 它既可以查找元素，也可以添加元素，还可以修改元素
	//如果下标对应的元素存在，可以直接访问到, 也可以直接赋值或者修改值
	//如果下标不存在，则直接创建一个相应的元素，但value的值是一个默认值
	//
	cout << cities[1] << endl;
	cout << cities[2] << endl;
	cout << cities[6] << endl;	//没有关键字为6的元素，会创建一个关键字为6的元素，值为空string
	cities[2] = "武汉";
	cities[0] = "南京";
	display(cities);
}

void test1(void)
{
	/*
	 *	map里面存放的元素是std::pair
	 *	map默认情况下， 按升序的方式进行排列
	 *	不能存放挂关键字相同的元素
	 *	*/
	map<string, string, std::greater<string>> cities{
		std::pair<string, string>("aa", "北京"),
			std::pair<string, string>("bb", "上海"),
			std::make_pair("cc", "广州"),
			std::make_pair("dd", "深圳"),
			std::make_pair("aa", "杭州")
	};
	display(cities);

	/*
	 *	map可以使用下标访问运算符, 它既可以查找元素，也可以添加元素，还可以修改元素
	 *	如果下标对应的元素存在，可以直接访问到, 也可以直接赋值或者修改值
	 *	如果下标不存在，则直接创建一个相应的元素，但value的值是一个默认值
	 *	*/

	cout << cities["aa"] << endl;
	cout << cities["bb"] << endl << endl;
	cities["cc"] = "武汉";
	cities["ee"] = "南京";
	display(cities);
}
int main(int argc, char **argv)
{
	test0();
	test1();
	return 0;
}
