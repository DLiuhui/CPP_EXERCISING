///
/// @file    construct.h
/// @author  LiuhuiDing@gmail.com
/// @date    2018-08-08 17:58:21
///

#ifndef CONSTRUCT_H_
#define CONSTRUCT_H_
#include <stdio.h>
#include <new>
#include <iostream>
#include <type_traits>	//C++11的类型萃取模板
namespace MyStl
{
	//定义construct和destroy，负责对象的构造和析构
	template <typename T1, typename T2>
		inline void construct(T1* ptr, const T2& value)
		{
			new (ptr) T1(value);	//placement new
			//在p指向的空间调用T1的构造函数，要求空间必须存在
		}

	template <typename T>
		inline void destroy(T* ptr)
		{
			//利用placement new申请的内存不能直接delete
			//需要显式调用p->~T(); free(p);
			ptr->~T();
		}

	//判断元素的类比是否有trivial destructor也就是默认析构函数
	template <typename FowardIterator, typename T>
		inline void destroyAux(FowardIterator first, FowardIterator last)
		{
			//判断有无默认析构函数
			constexpr bool has_trivial_destructor = std::is_trivially_destructible<T>::value;
			if(has_trivial_destructor == false)
				for(; first != last; ++first)
				{
					destroy(&*first);	//先对迭代器解引用，然后将对象地址传递给destroy
					//无默认析构的情况下，对所有元素显式调用析构函数
				}
		}
	//重载destroy版本：接收范围内的迭代器
	template <typename FowardIterator>
		inline void destroy(FowardIterator first, FowardIterator last)
		{
			destroyAux(first, last);	//由代理删除器进行判断
		}
}

#endif
