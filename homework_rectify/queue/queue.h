///
/// @file    queue.h
/// @author  LiuhuiDing@gmail.com
/// @date    2018-07-30 14:38:27
///

#ifndef QUEUE_H_
#define QUEUE_H_
#include <iostream>
#define QUEUE_INITIAL 10
class Queue
{
public:
	Queue(int size = QUEUE_INITIAL+1):
		size_(size), head_(0), tail_(0), array_(new int[size]())
	{}
	~Queue()
	{
		if(array_)
		{
			delete []array_;
		}
	}
	bool empty() const
	{
		return head_ == tail_;
	}
	bool full() const
	{
		return ((tail_+1) % size_) == head_;
	}
	void push(int data)
	{
		if(!full())
		{
			array_[tail_++] = data;
			tail_ %= size_;
		}
	}
	void pop()
	{
		if(!empty())
		{
			head_++;
			head_ %= size_;
		}
	}
	int front() const
	{
		return array_[head_];
	}
	int back() const
	{
		return array_[(tail_-1)%size_];
	}
private:
	int size_;
	int head_;
	int tail_;
	int *array_;
};

#endif
