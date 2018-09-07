 ///
 /// @file    IntCell.h
 /// @author  LiuhuiDing@gmail.com
 /// @date    2018-07-23 10:03:53
 ///
 
#ifndef __INTCELL_H__
#define __INTCELL_H__
#include <iostream>
#include <string>

class IntCell
{
	//friend bool operator<(const IntCell&, const IntCell&);
public:
	explicit IntCell(int initial_value = 0);	//构造函数
	IntCell(const IntCell&);	//拷贝构造函数
	int read() const;
	void write(int x);
	const IntCell & operator=(const IntCell&);
	const IntCell & operator=(const int);
	bool operator<(const IntCell&) const;
	~IntCell();
private:
	int *stored_value;
};



#endif
