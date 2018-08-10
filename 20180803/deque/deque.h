///
/// @file    deque.h
/// @author  LiuhuiDing@gmail.com
/// @date    2018-08-03 15:48:55
///

#ifndef DEQUE_H_
#define DEQUE_H_

#include <iostream>
#include <string>
#include <stdexcept>

//双端队列要注意下标做减法时要判断是否会<0，如果<0则要调整到数组尾部
namespace MyStd
{
	template <typename Object, std::size_t Capacity = 1000>
	class Deque
	{
		typedef std::size_t size_type;
		public:
		Deque():
			_array(new Object[Capacity]()),
			_head(0), _tail(0)
		{}
		Deque(size_type size, const Object &data):
			_array(new Object[Capacity]()),
			_head(0), _tail(0)
		{
			if(size < Capacity)
			{
				_tail = size;
			}
			else
				_tail = Capacity;
			for(size_type i = _head; i < _tail; ++i)
			{
				_array[i] = data;
			}
		}
		Deque(size_type size):
			_array(new Object[Capacity]()),
			_head(0), _tail(0)
		{
			if(size < Capacity)
			{
				_tail = size;
			}
			else
				_tail = Capacity;
		}
		Deque(const Deque &q):
			_array(new Object[q.size()]), _head(q._head), _tail(q._tail)
		{
			memcpy(_array, q._array, sizeof(Object) * q.size());
		}
		~Deque()
		{
			if(_array)
			{
				delete []_array;
			}
		}
		Deque & operator=(const Deque &rhs)
		{
			Deque copy = rhs;
			std::swap(*this, copy);
			return *this;
		}
		Object & operator[](size_type idx)	//非常量版本用于左值
		{
			if(idx >= size())
				throw std::out_of_range("visit out of range");
			return _array[(_head + idx) % Capacity];
		}
		const Object & operator[](size_type idx) const	//常量版本用于右值
		{
			if(idx >= size())
				throw std::out_of_range("visit out of range");
			return _array[(_head + idx) % Capacity];
		}
		Object & front()
		{
			return _array[_head];
		}
		const Object & front() const
		{
			return _array[_head];
		}
		Object & back()
		{
			return (_tail)?_array[_tail - 1]:_array[Capacity - 1];
		}
		const Object & back() const
		{
			return (_tail)?_array[_tail - 1]:_array[Capacity - 1];
		}
		bool empty() const
		{
			return (_head == _tail)?true:false;
		}
		bool full() const
		{
			return (((_tail+1)%Capacity) == _head)?true:false;
		}
		size_type size() const
		{
			return (_tail > _head)?(_tail - _head):(_tail - _head + Capacity);
		}
		void clear()
		{_head = 0; _tail = 0;}
		void push_back(const Object & data)
		{
			if(!full())
			{
				_array[_tail] = data;
				_tail = (_tail + 1) % Capacity;
			}
		}
		void pop_back()
		{
			if(!empty())
			{
				if(_tail == 0)
					_tail = Capacity - 1;
				else
					--_tail;
			}
		}
		void push_front(const Object & data)
		{
			if(!full())
			{
				if(_head == 0)
					_head = Capacity - 1;
				else
					--_head;
				_array[_head] = data;
			}
		}
		void pop_front()
		{
			if(!empty())
				_head = (++_head)%Capacity;
		}
		private:
			Object *_array;
			size_type _head;
			size_type _tail;
	};

}


#endif
