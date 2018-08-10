///
/// @file    heap.h
/// @author  LiuhuiDing@gmail.com
/// @date    2018-08-06 20:52:53
///

#ifndef HEAP_H_
#define HEAP_H_
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <initializer_list>
#include <algorithm>
#include <utility>
namespace MyStd
{
	//默认为大根堆
	template <typename Object, class Compare = std::less<Object>>
	class Heap
	{
		typedef std::size_t size_type;
		public:
		Heap():
			_array(new Object[INIT_SIZE]()), _size(0), _capacity(INIT_SIZE)
		{}
		Heap(const std::initializer_list<Object> &);	//列表初始化
		Heap(const Heap &);
		Heap & operator=(const Heap &rhs);
		~Heap();
		void pop()
		{
			if(!empty())
			{
				--_size;
				heapPopAdjust();
			}
		}
		void push(const Object &);
		Object top() const	//const & 可以绑定右值
		{
			return empty() ? Object():_array[0];
		}
		size_type size() const
		{ return _size; }
		bool empty() const
		{ return _size == 0; }
		static const size_type INIT_SIZE = 16;
		private:
		void heapPushAdjust();	//插入调整
		void heapPopAdjust();	//出队调整
		Object *_array;
		size_type _size;	//元素数量
		size_type _capacity;
	};

	template <typename Object, class Compare>
	Heap<Object, Compare>::Heap(const std::initializer_list<Object> &list):
		_size(0), _capacity(list.size() * 2)	//插入时调整，size初始化还是0
	{
		_array = new Object[_capacity]();
		for(auto iter = list.begin(); iter != list.end(); ++iter)
		{
			push(*iter);
		}
	}

	template <typename Object, class Compare>
	Heap<Object, Compare>::Heap(const Heap &heap):
		_size(heap._size), _capacity(heap._capacity)
	{
		_array = new Object[_capacity]();
		memcpy(_array, heap._array, sizeof(Object) * _size);
	}

	template <typename Object, class Compare>
	Heap<Object, Compare> & Heap<Object, Compare>::operator=(const Heap &rhs)
	{
		if(this != &rhs)
		{
			_size = rhs._size;
			_capacity = rhs._capacity;
			_array = new Object[_capacity]();
			memcpy(_array, rhs._array, _size * sizeof(Object));
		}
		return *this;
	}

	template <typename Object, class Compare>
	Heap<Object, Compare>::~Heap()
	{
		if(_array)
			delete []_array;
	}

	template <typename Object, class Compare>
	void Heap<Object, Compare>::push(const Object &data)
	{
		if(_size + 1 == _capacity)
		{
			Object *p = _array;
			_array = new Object[_capacity * 2]();
			for(size_type i = 0; i < _size; ++i)
			{
				_array[i] = p[i];
			}
			delete []p;
		}
		_array[_size++] = data;
		heapPushAdjust();
	}

	template <typename Object, class Compare>
	void Heap<Object, Compare>::heapPushAdjust()
	{
		//从尾部插入，新节点向上调整
		using std::swap;
		size_type i = _size - 1;
		Compare cmp;
		while(i > 0)
		{
			if(cmp(_array[i/2], _array[i]))	//默认：父节点比子节点小，上调
			{
				swap(_array[i/2], _array[i]);
				i = i/2;
			}
			else
				break;
		}
	}

	template <typename Object, class Compare>
	void Heap<Object, Compare>::heapPopAdjust()
	{
		//pop中size已经-1
		//头元素出队，尾元素到顶端，向下调整
		using std::swap;
		Compare cmp;
		size_type i = 0;
		_array[0] = _array[_size];
		while(i*2 + 1 < _size)
		{
			if(i*2+2 < _size)	//存在两个子节点
			{
				size_type next;
				if(cmp(_array[i*2+1], _array[i*2+2]))	//默认：和两个子节点中较大的进行交换
				{
					next = i*2+2;
				}
				else
				{
					next = i*2+1;
				}
				if(cmp(_array[i], _array[next]))
				{
					swap(_array[i], _array[next]);
					i = next;
				}
				else
					break;
			}
			else	//只要有一个子节点，不管是否交换，都结束调整
			{
				if(cmp(_array[i], _array[i*2+1]))
					swap(_array[i], _array[i*2+1]);
				break;
			}
		}
	}

}

#endif
