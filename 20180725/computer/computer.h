 ///
 /// @file    computer.h
 /// @author  LiuhuiDing@gmail.com
 /// @date    2018-07-25 11:28:18
 ///
 
#ifndef __COMPUTER_H__
#define __COMPUTER_H__
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <string>

//代码风格
//类名首字母大写，无下划线
//在每一个数据成员之前或之后加“_”，ex:_client
//或者XXXXX
//成员函数采用：驼峰
//先public再protect再private
//采用分离编译，类对应的头文件最先引用
class Computer
{
public:
	Computer():	//brand采用string的默认构造函数
		price_(0.00) {}
	Computer(const std::string &s, const float p):	//带参构造
		brand_(s), price_(p) {}
	Computer(const Computer &pc):	//拷贝构造
		brand_(pc.brand_), price_(pc.price_) {}
	void setBrand(const std::string &brand)
	{
		brand_ = brand;
	}
	void setPrice(const float price)
	{
		price_ = price;
	}
	void print() const
	{
		std::cout << "brand:" << brand_ << " price:" << price_ << std::endl;
	}
	~Computer()
	{
		std::cout << "~Computer()" << std::endl;
	}
private:
	std::string brand_;	//品牌
	float price_;	//单价
};
 
 
#endif
