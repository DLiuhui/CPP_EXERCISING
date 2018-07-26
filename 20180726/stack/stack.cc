///
/// @file    stack.cc
/// @author  LiuhuiDing@gmail.com
/// @date    2018-07-26 18:06:08
///

#include "stack.h"

Stack::Stack():
	size_(0), capacity_(MIN(INITIAL_STACK_SIZE,max_size_))	//确定栈初始容量
{
	elem_ = new dataType[capacity_];	//为栈申请存储空间
}

Stack::Stack(const Stack &s):
	size_(s.size_), capacity_(s.capacity_), elem_(new dataType[capacity_])
{
	memcpy(elem_, s.elem_, sizeof(dataType)*size_);//深拷贝
}

Stack::Stack(const dataType *arr, int n)
{
	capacity_ = MIN(((n<INITIAL_STACK_SIZE) ? INITIAL_STACK_SIZE : n*2), max_size_);
	elem_ = new dataType[capacity_];
	if(n > capacity_)	//说明插入量比栈最大容量大
	{
		size_ = capacity_;
	}
	else
	{
		size_ = n;
	}
	for(int i = 0; i < size_; i++)
	{
		elem_[i] = arr[i];
	}
}

Stack::~Stack()
{
	size_ = 0;
	capacity_ = MIN(INITIAL_STACK_SIZE, max_size_);
	delete []elem_;	//删除栈存储空间
}

bool Stack::push(const dataType &data)	//入栈
{
	if(full())
	{
		return false;
	}
	else
	{
		size_++;
		if(size_ > capacity_)	//现有容量不足
		{
			int old = capacity_;
			capacity_ = MIN(capacity_*2, max_size_);	//扩容
			dataType *ptr = elem_;
			elem_ = new dataType[capacity_];
			memcpy(elem_, ptr, old*sizeof(dataType));	//将原有数据深拷贝
			delete []ptr;	//释放原有空间
		}
		elem_[size_-1] = data;
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
		size_--;
		bzero(&elem_[size_], sizeof(dataType));	//清空存储区
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
		get = elem_[size_-1];
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
		return elem_[size_-1];
	}
}


