///
/// @file    queue.h
/// @author  LiuhuiDing@gmail.com
/// @date    2018-07-26 20:51:45
///
//C++ 标准库提供了std::queue
//
//采用节点形式实现队列

#ifndef QUEUE_H_
#define QUEUE_H_
#define QUEUE_MAX_SIZE 100000
#include <stdio.h>
#include <iostream>
#include <string>

struct DicItem
{
	std::string word;
	int times;
	DicItem & operator=(const DicItem & rhs)
	{
		word = rhs.word;
		times = rhs.times;
		return *this;
	}
	bool operator<(const DicItem & rhs)
	{
		return (word < rhs.word) ? true : false;
	}
};
class Queue;
//节点指针的值应该有Queue类完成修改工作，任何对节点的赋值、创建操作，都不应该为next_赋值
//该规律可应用于其他非连续型数据结构
class QueueNode
{
	friend Queue;
	typedef DicItem dataType;
public:
	QueueNode();	//节点初始化时，应该保证next指针均为NULL
	QueueNode(const dataType&);	//同上
	QueueNode(const QueueNode&);	//同上
	QueueNode & operator=(const QueueNode&);	//单独使用节点，也应该保证next指针指向NULL，不影响任何队列
	~QueueNode();
private:
	dataType data_;
	QueueNode *next_;
};
class Queue
{
public:
	Queue();
	Queue(const Queue&);
	~Queue();
	QueueNode::dataType & front() const;
	QueueNode::dataType & back() const;
	bool push(const QueueNode::dataType&);	//尾插
	bool pop();	//头出
	bool empty() const
	{
		return (size_ == 0)?true:false;
	}
	bool full() const
	{
		return (size_ == max_size_)?true:false;
	}
	bool SortInsert(const std::string&);
	static void setMaxSize()	//设置最大队长
	{
		if(max_size_ <= 0)
		{
			max_size_ = QUEUE_MAX_SIZE;
		}
	}
private:
	QueueNode *head_;	//队头
	QueueNode *tail_;	//队尾
	int size_;	//队长
	static int max_size_;	//最大长度
};

#endif
