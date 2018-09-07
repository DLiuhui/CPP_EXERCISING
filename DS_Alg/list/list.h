///
/// @file    list.h
/// @author  LiuhuiDing@gmail.com
/// @date    2018-08-07 22:17:57
///
//双向链表
//

#ifndef LIST_H_
#define LIST_H_
#include <stdio.h>
#include <iostream>
namespace MyStd
{
	template <typename Object>
		class List
		{
			typedef std::size_t size_type;
			public:
			//类成员声明
				class const_iterator;
				class iterator;
			//基本函数
				List()
				{ init(); }
				List(const List &);
				~List();
				List & operator=(const List &);
				List(List &&);
				List & operator=(List &&);
			//功能函数成员
				//List迭代器
				iterator begin()
				{ return iterator(*this, _head->_next); }
				iterator end()
				{ return iterator(*this, _tail); }
				const_iterator cbegin() const
				{ return const_iterator(*this, _head->_next); }
				const_iterator cend() const
				{ return const_iterator(*this, _tail); }
				//功能函数
				size_type size() const
				{ return _theSize; }
				bool empty() const
				{ return _theSize == 0; }
				void clear()
				{
					while(!empty())
						pop_front();
				}
				Object & front()
				{ return *begin(); }
				const Object & front() const 
				{ return *begin(); }
				Object & back()
				{ return *--end(); }
				const Object & back() const
				{ return *--end(); }
				//以下的队列操作函数除了insert和erase
				//均调用insert和erase接口
				//使用公共的方法
				//精简代码
				void push_front(const Object & x)
				{ insert(begin(), x); }
				void push_front(Object && x)
				{ insert(begin(), std::move(x)); }
				void push_back(const Object & x)
				{ insert(end(), x); }
				void push_back(Object && x)
				{ insert(end(), std::move(x)); }
				void pop_front()
				{ erase(begin()); }
				void pop_back()
				{ erase(--end()); }
				iterator insert(iterator, const Object &);
				iterator insert(iterator, Object &&);
				iterator erase(iterator);
				iterator erase(iterator, iterator);
			private:
				struct Node;
				void init();
				size_type _theSize;	//表长
				Node *_head;	//头
				Node *_tail;	//尾
		};

	template <typename Object>
		struct List<Object>::Node	//只为List及其成员服务的Node类型
		{
			Object _data;
			Node *_prev;
			Node *_next;
			Node(const Object & d = Object(),
					Node *p = nullptr,
					Node *n = nullptr)
				:_data(d), _prev(p), _next(n)
			{}
			Node(Object && d,
					Node *p = nullptr,
					Node *n = nullptr)
				:_data(std::move(d)), _prev(p), _next(n)
			{}
			~Node() = default;
		};

	template <typename Object>
		class List<Object>::const_iterator
		{
			friend class List<Object>;	//class List可以使用iterator的私有成员
			public:
				const_iterator()
					:_theList(nullptr), _current(nullptr)
				{}
				const_iterator(const const_iterator & iter)
					:_theList(iter._theList), _current(iter._current)
				{ /*std::cout << "copy" << std::endl;*/ }
				const_iterator & operator=(const const_iterator & rhs)
				{
					_theList = rhs._theList;
					_current = rhs._current;
					/*std::cout << "do=" << std::endl;*/
					return *this;
				}
				const Object & operator*() const
				{ return retrieve(); }
				const_iterator & operator++()
				{
					if(_current)
						_current = _current->_next;
					//std::cout << "do const++" << std::endl;
					return *this;
				}
				const_iterator operator++(int)
				{
					const_iterator old = *this;
					++(*this);
					return old;
				}
				const_iterator & operator--()
				{
					if(_current)
						_current = _current->_prev;
					//std::cout << "do const--" << std::endl;
					return *this;
				}
				const_iterator operator--(int)
				{
					const_iterator old = *this;
					--(*this);
					return old;
				}
				bool operator==(const const_iterator &rhs) const
				{ return _current == rhs._current; }
				bool operator!=(const const_iterator &rhs) const
				{ return _current != rhs._current; }
				void assertIsValid() const	//检验iter的有效性
				{
					if(_theList == nullptr ||	//表未定义
							_current == nullptr ||	//节点未定义
							_current == _theList->_head
							)
						throw std::invalid_argument("pos invalid");
				}
			protected:
				Object & retrieve() const
				{ return _current->_data; }
				const_iterator(const List<Object> &list, Node *p)
					:_theList(&list), _current(p)
				{ /*std::cout << "cons const_iter" << std::endl;*/ }
				//成员
				const List<Object> *_theList;	//指向表本身
				Node *_current;
		};

	//继承常量迭代器
	//继承了const_iter类的 拷贝构造和=赋值函数
	//负责对iter类所继承的const_iter基类成员执行初始化
	//使用自己自定义的构造函数-》使用const_iter构造函数初始化基类成员
	//必须定义类自己版本的++，--，所以调用自己的++、--
	//如果调用基类的 ++、--
	//基类无法隐式类型转换成 iterator类型（只能iterator隐式类型转换成const_iter）
	template <typename Object>
		class List<Object>::iterator : public const_iterator
		{
			friend class List<Object>;	//class List可以使用iterator的私有成员
			public:
				iterator()
				{}
				Object & operator*()
				{ return const_iterator::retrieve(); }
				const Object & operator*() const
				{ return const_iterator::operator*(); }
				iterator & operator++()
				{
					if(this->_current)
						this->_current = this->_current->_next;
					//std::cout << "do ++" << std::endl;
					return *this;
				}
				iterator operator++(int)
				{
					iterator old = *this;
					++(*this);
					return old;
				}
				iterator & operator--()
				{
					if(this->_current)
						this->_current = this->_current->_prev;
					//std::cout << "do --" << std::endl;
					return *this;
				}
				iterator operator--(int)
				{
					iterator old = *this;
					--(*this);
					return old;
				}
			protected:
				iterator(const List<Object> &list, Node *p)
					:const_iterator(list, p)	//调用const_iterator的构造函数
				{ /*std::cout << "cons iter" << std::endl;*/ }
		};

	template <typename Object>
		void List<Object>::init()
		{
			_theSize = 0;
			_head = new Node;
			_tail = new Node;
			_head->_next = _tail;
			_tail->_prev = _head;
		}

	template <typename Object>
		List<Object>::List(const List & rhs)
		{
			init();
			for(auto & x : rhs)
				push_back(x);
		}
	
	template <typename Object>
		List<Object>::List(List && rhs)
		:_theSize(rhs._theSize), _head(rhs._head), _tail(rhs._tail)
		{
			rhs._theSize = 0;
			rhs._head = nullptr;
			rhs._tail = nullptr;
		}

	template <typename Object>
		List<Object> & List<Object>::operator=(const List & rhs)
		{
			List copy(rhs);	//生成一份拷贝，制作副本
			std::swap(*this, copy);	//交换所有权
			return *this;
		}

	template <typename Object>
		List<Object> & List<Object>::operator=(List && rhs)
		{
			std::swap(_theSize, rhs._theSize);
			std::swap(_head, rhs._head);
			std::swap(_tail, rhs._tail);
			return *this;
		}

	template <typename Object>
		List<Object>::~List()
		{
			clear();	//清空链表
			delete _head;
			delete _tail;
		}
	
	//插在当前节点之前，返回插入节点之后的迭代器
	template <typename Object>
		typename List<Object>::iterator 
		List<Object>::insert(iterator iter, const Object & x)
		{
			iter.assertIsValid();
			if(iter._theList != this)	//非当前表对象的迭代器
				throw std::invalid_argument("iterator not fit list");
			Node *p = new Node(x, iter._current->_prev, 
					iter._current);
			++_theSize;
			iter._current->_prev->_next = p;
			iter._current->_prev = p;
			return iter;
		}

	template <typename Object>
		typename List<Object>::iterator 
		List<Object>::insert(iterator iter, Object && x)
		{
			iter.assertIsValid();
			if(iter._theList != this)	//非当前表对象的迭代器
				throw std::invalid_argument("iterator not fit list");
			Node *p = new Node(std::move(x), iter._current->_prev, 
					iter._current);
			++_theSize;
			iter._current->_prev->_next = p;
			iter._current->_prev = p;
			return iter;
		}

	//删除指定的节点，返回被删除节点之后的迭代器
	template <typename Object>
		typename List<Object>::iterator 
		List<Object>::erase(iterator iter)
		{
			iter.assertIsValid();
			if(iter._theList != this)	//非当前表对象的迭代器
				throw std::invalid_argument("iterator not fit list");
			Node *p = iter._current;
			iterator retVal(*this, p->_next);
			p->_next->_prev = p->_prev;
			p->_prev->_next = p->_next;
			delete p;
			--_theSize;
			return retVal;
		}

	//删除从from开始到to之前的节点，返回to
	template <typename Object>
		typename List<Object>::iterator 
		List<Object>::erase(iterator from, iterator to)
		{
			to.assertIsValid();
			if(to._theList != this || from._theList != this)
				throw std::invalid_argument("iterator not fit list");
			for(iterator itr = from; itr != to;)
				itr = erase(itr);	//删除一个节点后itr后移
			return to;
		}

}


#endif
