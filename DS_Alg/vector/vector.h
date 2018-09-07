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
#include <algorithm>
namespace MyStd
{
	template <typename Object>		
	class Vector
	{
		public:
			//五大函数
			explicit Vector(unsigned int initSize = 0):
				theSize_(initSize),
				theCapacity_(initSize + SPARE_CAPACITY),
				array_(new Object[theCapacity_]())
			{}
			Vector(const Vector &rhs):	//拷贝构造
				theSize_(rhs.theSize_),
				theCapacity_(rhs.theCapacity_),
				array_(new Object[theCapacity_]())
			{
				//进行深拷贝
				memcpy(array_, rhs.array_, theSize_ * sizeof(Object));
			}
			Vector & operator=(const Vector &rhs)
			{
				if(this != &rhs)	//不是自复制
				{
					Vector copy = rhs;	//调用拷贝构造函数
					std::swap(*this, copy);	//使用更为高效的标准库交换
				}
				return *this;
			}
			Vector(Vector && rhs):	//移动构造函数
				theSize_(rhs.theSize_),
				theCapacity_(rhs.theCapacity_),
				array_(rhs.array_)
			{
				//清空rhs
				rhs.array_ = nullptr;
				rhs.theSize_ = 0;
				rhs.theCapacity_ = 0;
			}
			Vector & operator=(Vector &&rhs)	//移动赋值
			{
				std::swap(theSize_, rhs.theSize_);
				std::swap(theCapacity_, theCapacity_);
				std::swap(array_, rhs.array_);
				return *this;
			}
			~Vector()
			{
				if(array_)
				{
					delete []array_;
				}
			}
			void resize(unsigned int newSize)	//重分配数组个数
			{
				if(newSize > theCapacity_)	//此时需要重分配空间
				{
					reverse(newSize * 2);
				}
				for(unsigned int i = theSize_; i < newSize; ++i)
				{
					array_[i] = Object(0);	//此处存在风险，Object可能是复杂类型
				}
				theSize_ = newSize;
			}
			void reverse(unsigned int newCapacity)	//重新分配空间
			{
				if(newCapacity < theSize_)	//新的分配要求小于当前数组尺寸，什么都不做
					return;
				Object *p = new Object[newCapacity];	//申请新的空间
				for(unsigned int i = 0; i < theSize_; ++i)
				{
					p[i] = std::move(array_[i]);	//移动array_的元素到p
				}
				theCapacity_ = newCapacity;
				std::swap(array_, p);	//交换array_和p，array_获得p的空间，p指向移动后待删除的空间
				delete []p;	//删除就空间
			}
			Object & operator[](unsigned int index)
			{
				if(index >= theSize_)
				{
					throw std::out_of_range("visit out of range");
				}
				else
					return array_[index];
			}
			const Object & operator[](unsigned int index) const
			{
				if(index >= theSize_)
				{
					throw std::out_of_range("visit out of range");
				}
				else
					return array_[index];
			}
			bool empty() const
			{
				return size() == 0;
			}
			unsigned int size() const
			{
				return theSize_;
			}
			unsigned int capacity() const
			{
				return theCapacity_;
			}
			void push_back(const Object &x)
			{
				if(theSize_ == theCapacity_)
				{
					reverse(2 * theCapacity_ + 1);
				}
				array_[theSize_++] = x;
			}
			void push_back(Object &&x)
			{
				if(theSize_ == theCapacity_)
					reverse(2 * theCapacity_ + 1);
				array_[theSize_++] = std::move(x);
			}
			void pop_back()	//尾出
			{
				theSize_--;
			}
			const Object & back() const	//返回尾元素
			{
				return array_[theSize_ - 1];
			}
			typedef Object * iterator;	//迭代器
			typedef const Object * const_iterator;	//常量迭代器
			iterator begin()	//起始迭代器
			{
				return &array_[0];
			}
			iterator end()	//尾后迭代器
			{
				return &array_[size()];
			}
			const_iterator cbegin() const
			{
				return &array_[0];
			}
			const_iterator cend() const
			{
				return &array_[size()];
			}
			static const unsigned int SPARE_CAPACITY = 16;
		private:
			unsigned int theSize_;	//当前大小
			unsigned int theCapacity_;	//实际的存储空间分配大小
			Object *array_;	//对象数组
	};

}

#endif
