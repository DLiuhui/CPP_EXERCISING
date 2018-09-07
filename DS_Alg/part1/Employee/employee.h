 ///
 /// @file    employee.h
 /// @author  LiuhuiDing@gmail.com
 /// @date    2018-07-23 14:26:49
 ///
 
#ifndef __EMPLOYEE_H__
#define __EMPLOYEE_H__
#include <iostream>
#include <string>

class Employee
{
	friend std::ostream & operator<<(std::ostream&, const Employee&);
public:
	Employee();	//默认构造
	Employee(const std::string&, const double s = 0);
	Employee(const Employee&);	//拷贝构造
	void setValue(const std::string&, const double);
	const std::string &get_name() const;
	void print(std::ostream&) const;
	bool operator<(const Employee&) const;
	const Employee & operator=(const Employee&);
private:
	std::string name;
	double salary;
};

std::ostream & operator<<(std::ostream&, const Employee&);

#endif
