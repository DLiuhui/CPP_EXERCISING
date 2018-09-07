///
/// @file    stack.h
/// @author  LiuhuiDing@gmail.com
/// @date    2018-07-30 10:17:25
///

#ifndef STACK_H_
#define STACK_H_
#include <iostream>
#define SIZE_INITIAL 10
class Stack
{
public:
	Stack(int size = SIZE_INITIAL)
		:top_(-1), size_(size), array_(new int[size]())
	{}
	~Stack()
	{
		if(array_)
		{
			delete []array_;
		}
	}
	bool full() const
	{
		return top_ == size_-1;
	}
	bool empty() const
	{
		return top_ == -1;
	}
	int top() const
	{
		//判断过程在类外进行
		return array_[top_];
	}
	void pop()
	{
		if(!empty())
		{
			top_--;
		}
	}
	void push(int data)
	{
		if(!full())
		{
			array_[++top_] = data;
		}
	}
private:
	int top_;
	int size_;
	int *array_;
};

#endif
