///
/// @file    vector.h
/// @author  LiuhuiDing@gmail.com
/// @date    2018-08-01 00:00:53
///

#ifndef VECTOR_H_
#define VECTOR_H_
#include <stdio.h>
#include <iostream>
#include <string>
#include <stdexcept>
#include <memory>
#include <algorithm>
namespace MyStl
{
	template <typename type>
		inline const type max(const type lhs, const type rhs)
		{
			return (lhs>rhs)?lhs:rhs;
		}

	template <typename Object>		
	class Vector
	{
		typedef std::size_t size_type;
		public:
			//五大函数
			explicit Vector(size_type initSize = 0)
				:_start(_alloc.allocate(max<size_type>(initSize*2,SPARE_CAPACITY))),
				_end(_start),
				_end_of_storage(_start+max<size_type>(initSize*2, SPARE_CAPACITY))
			{}
			Vector(const Vector &rhs)	//拷贝构造，深拷贝
				:_start(_alloc.allocate(rhs.size())),
				_end(_start + rhs.size()),
				_end_of_storage(_start + rhs.capacity())
			{
				//对内存构造初始化
				for(size_type i = 0; i < rhs.size(); i++)
				{
					_alloc.construct(_start + i,*(rhs._start+i));
				}
			}
			Vector & operator=(const Vector &rhs)
			{
				Vector copy = rhs;	//调用拷贝构造函数，制作副本
				std::swap(*this, copy);	//使用更为高效的标准库交换
				return *this;
			}
			~Vector()
			{
				if(0 != capacity())
				{
					for(size_type i = 0; i < size(); ++i)
					{
						_alloc.destroy(_start + i);	//先对已经构造的空间进行析构
					}
					_alloc.deallocate(_start, capacity());
				}
			}
			void resize(size_type newSize)	//重分配数组个数
			{
				if(newSize > capacity())	//此时需要重分配空间
				{
					reverse(newSize * 2);
				}
			}
			void reverse(size_type newCapacity)	//重新分配空间
			{
				if(newCapacity < size())	//新的分配要求小于当前数组尺寸，什么都不做
					return;
				size_type oldCapa = capacity();
				size_type oldSize = size();
				Object *p = _alloc.allocate(newCapacity);
				/*
				//使用标准库中的uninitialized_copy()
				std::uninitialized_copy(_start, _end, p);
				*/
				for(size_type i = 0; i < oldSize; ++i)
				{
					_alloc.construct(p+i, *(_start+i));
					_alloc.destroy(_start + i);
				}
				std::swap(_start, p);
				_end = _start + oldSize;
				_end_of_storage = _start + newCapacity;
				_alloc.deallocate(p, oldCapa);	//销毁p
			}
			Object & operator[](unsigned int index)
			{
				if(index >= size())
				{
					throw std::out_of_range("visit out of range");
				}
				else
					return *(_start+index);
			}
			const Object & operator[](unsigned int index) const
			{
				if(index >= size())
				{
					throw std::out_of_range("visit out of range");
				}
				else
					return *(_start+index);
			}
			bool empty() const
			{
				return size() == 0;
			}
			size_type size() const	//因为是在堆上创建对象，所以end-start
			{
				return _end - _start;
			}
			size_type capacity() const
			{
				return _end_of_storage - _start;
			}
			void push_back(const Object &x)
			{
				if(size() == capacity())
				{
					reverse(2 * capacity());
				}
				_alloc.construct(_end++, x);
			}
			void pop_back()	//尾出
			{
				if(!empty())
					--_end;
			}
			const Object & back() const	//返回尾元素
			{
				return *(_end-1);
			}
			typedef Object * iterator;	//迭代器
			typedef const Object * const_iterator;	//常量迭代器
			iterator begin()	//起始迭代器
			{
				return _start;
			}
			iterator end()	//尾后迭代器
			{
				return _end;
			}
			const_iterator cbegin() const
			{
				return static_cast<const Object*>(_start);
			}
			const_iterator cend() const
			{
				return static_cast<const Object*>(_end);
			}
			static const size_type SPARE_CAPACITY = 16;
		private:
			static std::allocator<Object> _alloc;
			Object *_start;
			Object *_end;
			Object *_end_of_storage;
	};

	template <typename Object>
	std::allocator<Object> Vector<Object>::_alloc = std::allocator<Object>();

}

#endif
