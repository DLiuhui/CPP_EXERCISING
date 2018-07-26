///
/// @file    queue.cc
/// @author  LiuhuiDing@gmail.com
/// @date    2018-07-26 21:08:57
///

#include "queue.h"

QueueNode::QueueNode():
	data_(0), next_(NULL)
{}

QueueNode::QueueNode(const dataType &data):
	data_(data), next_(NULL)
{}

QueueNode::QueueNode(const QueueNode &node):
	data_(node.data_), next_(NULL)
{}

QueueNode & QueueNode::operator=(const QueueNode &rhs)
{
	data_ = rhs.data_;
	next_ = NULL;
	return *this;
}

QueueNode::~QueueNode()
{
	//删除本节点
	//由于当节点在队列时，next_才会指向新的空间
	//delete next_会造成连锁删除
	next_ = NULL;
}

Queue::Queue():
	head_(new QueueNode), tail_(head_), size_(0)
{}

Queue::Queue(const Queue &queue):	//深拷贝一条队列
	head_(new QueueNode), tail_(head_), size_(queue.size_)
{
	if(size_ > 0)
	{
		QueueNode *ptr = queue.head_->next_;
		for(int i = 0; i < size_; i++)	//尾插
		{
			tail_->next_ = new QueueNode(*ptr);
			tail_ = tail_->next_;
			ptr = ptr->next_;
		}
	}
}

Queue::~Queue()
{
	if(size_ > 0)
	{
		QueueNode *p;
		for(int i = 0; i < size_; i++)
		{
			p = head_->next_;
			head_->next_ = p->next_;
			delete p;
		}
		size_ = 0;
	}
	tail_ = head_;
	delete head_;
}

QueueNode::dataType Queue::front() const
{
	if(empty())
	{
		return -1;
	}
	else
	{
		return head_->next_->data_;
	}
}

QueueNode::dataType Queue::back() const
{
	if(empty())
	{
		return -1;
	}
	else
	{
		return tail_->data_;
	}
}

bool Queue::push(const QueueNode::dataType &data)
{
	if(full())
	{
		return false;
	}
	else
	{
		size_++;
		tail_->next_ = new QueueNode(data);
		tail_ = tail_->next_;
		return true;
	}
}

bool Queue::pop()
{
	if(empty())
	{
		return false;
	}
	else
	{
		size_--;
		QueueNode *p;
		p = head_->next_;
		head_->next_ = p->next_;
		std::cout << p->data_ << std::endl;
		std::cout << head_->next_->data_ << std::endl;
		delete p;
		return true;
	}
}
