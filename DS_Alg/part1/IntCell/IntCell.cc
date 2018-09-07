 ///
 /// @file    IntCell.cpp
 /// @author  LiuhuiDing@gmail.com
 /// @date    2018-07-23 10:16:13
 ///
 
#include "IntCell.h"

IntCell::IntCell(int initial_value)
{
	stored_value = new int(initial_value);
}

IntCell::IntCell(const IntCell &newCell)
{
	stored_value = new int(*newCell.stored_value);
}

int IntCell::read() const
{
	return *stored_value;
}

void IntCell::write(int x)
{
	*stored_value = x;
}

const IntCell & IntCell::operator=(const IntCell &rhs)
{
	if(*stored_value != *rhs.stored_value)
	{
		*stored_value = *rhs.stored_value;
	}
	return *this;
}


const IntCell & IntCell::operator=(const int i)
{
	if(*stored_value != i)
	{
		*stored_value = i;
	}
	return *this;
}

bool IntCell::operator<(const IntCell &rhs) const
{
	return (*stored_value < *rhs.stored_value)?true:false;
}

IntCell::~IntCell()
{
	delete stored_value;	//释放空间
	std::cout<<"Destory cell"<<std::endl;
}

/*
bool operator<(const IntCell &lhs, const IntCell &rhs)
{
	return (*lhs.stored_value < *rhs.stored_value)?true:false;
}
*/
