 ///
 /// @file    employee.cpp
 /// @author  LiuhuiDing@gmail.com
 /// @date    2018-07-23 14:33:21
 ///
#include "employee.h"

Employee::Employee():
	name("\0"), salary(0) {}

Employee::Employee(const std::string &e_name, const double s):
	name(e_name), salary(s) {}

Employee::Employee(const Employee &member):
	name(member.name, member.salary) {}

void Employee::setValue(const std::string &e_name, const double s)
{
	name = e_name;
	salary = s;
}

const std::string & Employee::get_name() const
{
	return name;
}

void Employee::print(std::ostream &out) const
{
	out<<name<<" "<<salary;
}

bool Employee::operator<(const Employee &rhs) const
{
	return (salary < rhs.salary) ? true : false;
}

const Employee & Employee::operator=(const Employee &rhs)
{
	name = rhs.name;
	salary = rhs.salary;
	return *this;
}

std::ostream & operator<<(std::ostream &os, const Employee &member)
{
	os << member.name << " " << member.salary;
	return os;
}

