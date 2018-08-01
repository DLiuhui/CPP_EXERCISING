///
/// @file    stack.cc
/// @author  LiuhuiDing@gmail.com
/// @date    2018-07-26 18:06:08
///

#include "stack.h"

Stack::Stack() = default;	//使用vector的默认创建过程

Stack::Stack(const Stack &s):
	elem_(s.elem_)
{}

Stack::Stack(const dataType *arr, int n)
{
	elem_.reserve(n + MIN(1000, n/4));	//预分配空间
	for(int i = 0; i < n; i++)
	{
		elem_.push_back(arr[1]);
	}
}
Stack::~Stack() = default;	//使用vector的默认销毁过程

bool Stack::push(const dataType &data)	//入栈
{
	if(full())
	{
		return false;
	}
	else
	{
		elem_.push_back(data);
		return true;
	}
}

bool Stack::pop()
{
	if(empty())
	{
		return false;
	}
	else
	{
		elem_.erase(elem_.end()-1);
		return true;
	}
}

bool Stack::getTop(dataType &get) const
{
	if(empty())
	{
		return false;
	}
	else
	{
		get = *(elem_.end()-1);	//尾后迭代器-1
		return true;
	}
}

Stack::dataType Stack::returnTop() const
{
	if(empty())
	{
		return -1;
	}
	else
	{
		return *(elem_.end()-1);	//尾后迭代器-1
	}
}


