///
/// @file    stack.h
/// @author  LiuhuiDing@gmail.com
/// @date    2018-07-26 17:47:40
///
//C++中实现栈Stack
//1、C++提供标准库std::Stack
//2、也可以使用std::vector模拟Stack
//3、用动态数组
//
//此处使用动态数组new []


#ifndef STACK_H_
#define STACK_H_
#define MIN(x,y) (x)<(y)?(x):(y)
#define STACK_MAX_SIZE 4096	//如果未设定max_size_的话
#define INITIAL_STACK_SIZE 40	//stack的初始大小
#include <stdio.h>
#include <string.h>
#include <iostream>
class Stack
{
	typedef int dataType;
public:
	Stack();	//构造
	Stack(const Stack&);	//拷贝栈
	Stack(const dataType*, int);	//栈的数组初始化
	//Stack(const std::InitialList)栈的列表初始化
	~Stack();	//销毁栈
	bool push(const dataType&);	//入栈
	bool pop();	//出栈
	bool getTop(dataType &) const;	//传参得到栈顶元素
	dataType returnTop() const;	//返回栈顶元素
	bool empty() const	//判断栈空
	{
		return (size_ == 0)?true:false;
	}
	bool full() const	//判断栈满
	{
		return (size_ == max_size_)?true:false;
	}
	static void setMaxSize()	//设定max_size_
	{
		if(max_size_ <= 0)
		{
			max_size_ = STACK_MAX_SIZE;
		}
	}
private:
	int size_;	//栈大小
	int capacity_;	//栈的空间大小
	dataType *elem_;	//元素
	static int max_size_; //最大栈大小，如果设置成<=0值，则相当于不设置栈空间限制
};

#endif
