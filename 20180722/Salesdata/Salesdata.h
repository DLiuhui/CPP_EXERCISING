#ifndef __SALESDATA_H__
#define __SALESDATA_H__

#include <iostream>
#include <string>

class Sales_data
{
	friend std::istream &read(std::istream&, Sales_data&);
	friend std::ostream &print(std::ostream&, const Sales_data&);
public:
	Sales_data();	//构造函数1
	Sales_data(const std::string, unsigned int, float);	//构造函数2
	Sales_data(const Sales_data&);	//拷贝构造函数
	Sales_data add(const Sales_data&, const Sales_data&);
	Sales_data &combine(const Sales_data&);
	std::string isbn() const;
	float average() const;
	Sales_data& operator=(const Sales_data&);
private:
	std::string book_NO;
	unsigned int unit_sold;
	float revenue;
};

std::istream &read(std::istream&, Sales_data&);
std::ostream &print(std::ostream&, const Sales_data&);

#endif
