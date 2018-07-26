 ///
 /// @file    static_computer.cc
 /// @author  LiuhuiDing@gmail.com
 /// @date    2018-07-26 14:36:39
 ///
 
#include <iostream>
#include <string>
#include <cstring>
using std::cin;
using std::cout;
using std::endl;

class computer
{
public:
	computer(const char *chr, const float p)
		:name(new char[strlen(chr)+1]), price(p)
	{
		strcpy(name, chr);
		total_price += p;
	}
	~computer()
	{
		if(name)
		{
			delete []name;
			name = NULL;	//防止野指针
		}
		total_price -= price;
	}
	static void print_total()
	{
		cout << "总价：" << total_price << endl;
	}
	static void print(computer &com)	//必须要传递参数
	{
		cout << "名称" << com.name << endl;
		cout << "价格" << com.price << endl;
	}
private:
	char *name;
	float price;
	static float total_price;
};

float computer::total_price = 0;	//初始化静态成员
int main(int argc, char **argv)
{
	computer com1("IBM", 7000);
	com1.print(com1);	//调用静态成员函数
	computer::print(com1);
	computer::print_total();
	computer com2("Lenv", 8000);
	com1.print(com2);
	com2.print_total();
	com1.~computer();
	computer::print(com2);
	computer::print_total();	//总价变为8000
	return 0;
}
