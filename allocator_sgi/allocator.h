///
/// @file    allocator.h
/// @author  LiuhuiDing@gmail.com
/// @date    2018-08-08 17:50:09
///

#ifndef ALLOCATOR_H_
#define ALLOCATOR_H_
#include "construct.h"
#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <new>
#include <iostream>
#include <algorithm>
#include <stdexcept>
#include <cstddef>
#include <climits>
namespace MyStl
{
	//SGI STL采用二级空间配置器结构
	//第一级空间配置器处理较大字节的内存块
	//第二级空间配置器以内存池的形式处理较小的内存块
	//
	//此为第一级
	class BaseMallocAlloc
	{
		typedef std::size_t size_type;
		public:
		static void* allocate(size_type n)
		{
			void* result = malloc(n);	//调用malloc分配空间
			if(result == 0)	//内存分配失败，启用内存不足版本的malloc
			{
				result = oomMalloc(n);
			}
			return result;
		}
		//重新分配空间
		static void* reallocate(void* ptr, size_type new_size, size_type old_size = 0)
		{
			void* result = realloc(ptr, new_size);
			if(0 == result)	//内存不足，改用oom版本的realloc
				result = oomRealloc(ptr, new_size);
			return result;
		}
		//空间释放
		static void deallocate(void *ptr)
		{
			free(ptr);
		}
		//设置空间配置处理函数
		//可以指定自己的空间配置函数
		static void (*setMallocHandler(void (*f)()))()
		{
			void (*old)() = mallocAllocOomHandler;
			mallocAllocOomHandler = f;
			return (old);
		}
		private:
		//处理内存不足的情况
		//oom:out of memory
		static void* oomMalloc(size_type);
		static void* oomRealloc(void*, size_type);
		static void (*mallocAllocOomHandler)();	//函数指针
	};
	//相当于为static成员设置初值，初始化为0，也就是nullptr
	//默认不设置空间处理函数
	void (*BaseMallocAlloc::mallocAllocOomHandler)() = 0;
	void* BaseMallocAlloc::oomMalloc(size_type n)
	{
		void (*myMallocHandler)();
		void* result;
		while(1)	//不断的尝试释放、配置
		{
			myMallocHandler = mallocAllocOomHandler;
			//如果未配置空间处理函数，直接报错
			if(0 == myMallocHandler) { throw std::bad_alloc(); }
			//如果配置了，执行相应的函数尝试释放空间
			(*myMallocHandler)();	//调用，尝试释放内存
			result = malloc(n);
			if(result)	//若分配成功，返回result，不然再次尝试
				return result;
		}
	}

	class DefaultAlloc	//二级空间配置器
	{
		typedef std::size_t size_type;
		public:
		static void* allocate(size_type);
		static void deallocate(void*, size_type);
		static void* reallocate(void*, size_type, size_type);
		private:
		union obj
		{
			union obj* free_list_link;	//内存表指针
			char client_data[1];
		};
		static size_type roundUp(size_type n)//将小空间大小上调至8的倍数
		{
			return ((n + ALIGN - 1) & ~(ALIGN - 1));//凑整技巧
		}
		static size_type getFreeListIndex(size_type n)//根据空间找自由链表的下标
		{
			return ((n + ALIGN - 1) / ALIGN - 1);
		}
		static void* refill(size_type);//填充自由链表
		static char* chunkAlloc(size_type, int&);//内存池空间分配
		static const size_type MAX_BYTES = 128;	//小型区块上限
		static const size_type ALIGN = 8;	//小型区块上调边界
		static const size_type NUM_FREE_LIST = MAX_BYTES/ALIGN;	//自由链表个数
		//将由所有配置器共享：
		//自由链表，内存池
		static obj* free_list[NUM_FREE_LIST];
		static char* start_free;	//内存池起始
		static char* end_free;	//内存池终止
		static size_type heap_size;//内存池大小
	};

	void* DefaultAlloc::allocate(size_type n)
	{
		void* result = nullptr;
		if(n > MAX_BYTES)
		{
			result = BaseMallocAlloc::allocate(n);
		}
		else
		{
			obj* my_free_list = free_list[getFreeListIndex(n)];
			if(0 == my_free_list)//表块不足
			{
				result = refill(roundUp(n));//对需要新分配的空间进行取整
			}
			else
			{
				obj* tmp = my_free_list;
				my_free_list = tmp->free_list_link;//指向下一个内存块
				result = tmp;
			}
		}
		return result;

	}

	void DefaultAlloc::deallocate(void* p, size_type n)
	{
		if(n > MAX_BYTES)
		{
			BaseMallocAlloc::deallocate(p);
		}
		else
		{
			obj* my_free_list = free_list[getFreeListIndex(n)];
			obj* q = (obj*)p;
			q->free_list_link = my_free_list;//类似于一个头插法的过程
			//插入块的next先指向头
			my_free_list = q;
		}
	}

	void* DefaultAlloc::reallocate(void* p, size_type new_size, size_type old_size)
	{
		void *result;
		if(old_size == new_size)
			return p;
		else
		{
			result = allocate(new_size);//申请新空间
			memcpy(result, p, old_size);//拷贝数据
			deallocate(p, old_size);//释放旧空间
		}
		return result;
	}

	void* DefaultAlloc::refill(size_type n)
	{
		int nobjs = 20;//默认分配20个区块
		char* chunk = chunkAlloc(n, nobjs);	//nobjs引用传递
		if(1 == nobjs)
		{
			return chunk;	//直接返回chunk首地址
		}
		else
		{
			obj* my_free_list;
			obj* result;
			obj* current_obj;
			obj* next_obj;
			my_free_list = free_list[getFreeListIndex(n)];
			result = (obj*)chunk;
			my_free_list = current_obj = (obj*)(chunk + n);
			//区块划分，从第二块开始，第一块直接交付用户
			for(int i = 2; i < nobjs; i++)
			{
				next_obj = (obj*)((char*)current_obj + n);
				current_obj->free_list_link = next_obj;
				current_obj = next_obj;
			}
			current_obj->free_list_link = 0;//最后一块指向空
			return result;
		}
	}

	char* DefaultAlloc::chunkAlloc(size_type size, int& nobjs)
	{
		char* result;
		size_type total_bytes = size * nobjs;
		size_type bytes_left = end_free - start_free;
		if(bytes_left > total_bytes)	//剩余空间够用
		{
			result = start_free;
			start_free = start_free + total_bytes;
			return result;
		}
		else if(bytes_left > size)	//剩余空间不足，但是可以分配出size大小区块
		{
			nobjs = bytes_left / size;
			result = start_free;
			start_free = start_free + nobjs * size;
			return result;
		}
		else//剩余空间不足以分配一块
		{
			size_type bytes_to_get = total_bytes * 2 + roundUp(1024);
			if(bytes_left > 0)//处理零头，将零头插入对应的表区
			{
				obj* my_free_list = free_list[getFreeListIndex(getFreeListIndex(bytes_left))];
				((obj*)start_free)->free_list_link = my_free_list;
				my_free_list = (obj*)start_free;
			}
			//申请堆空间
			start_free = (char*)malloc(bytes_to_get);
			if(start_free == 0)	//申请失败
			{
				//检查自己手头有没有未使用的大块
				//不对<size的区块进行配置
				//搜寻free_list
				obj* my_free_list;
				for(size_type i = size; i < MAX_BYTES; i += ALIGN)
				{
					my_free_list = free_list[getFreeListIndex(i)];
					if(0 != my_free_list)//有区块，进行回收
					{
						//回收数量默认一块
						start_free = (char*)my_free_list;
						my_free_list = ((obj*)start_free)->free_list_link;
						end_free = start_free + i;
						return chunkAlloc(size, nobjs);	//递归调用
					}
				}
				//手头已无可用
				start_free = (char*)BaseMallocAlloc::allocate(bytes_to_get);
				//调用第一级适配器里分配空间的函数
				//如果分配失败会报错，分配成功则退出if执行下一步
				end_free =start_free + bytes_to_get;
			}
			//申请成功
			end_free = start_free + bytes_to_get;
			heap_size += bytes_to_get;
			return chunkAlloc(size, nobjs);	//递归调用，重分配
		}
	}
	
	DefaultAlloc::obj* DefaultAlloc::free_list[NUM_FREE_LIST] = {0};
	char* DefaultAlloc::start_free = nullptr;	//内存池起始
	char* DefaultAlloc::end_free = nullptr;	//内存池终止
	DefaultAlloc::size_type DefaultAlloc::heap_size = 0;//内存池大小

	typedef BaseMallocAlloc firstAlloc;
	typedef DefaultAlloc secondAlloc;

	//空间配置器接口
	template <typename T, class Alloc = secondAlloc>//默认调用二级配置器
		class Allocator
		{
			typedef T value_type;
			typedef T* pointer;
			typedef const T* const_pointer;
			typedef T& reference;
			typedef const T& const_reference;
			typedef std::size_t size_type;
			typedef ptrdiff_t difference_type;	//定义在stddef.h/cstddef中
			public:
			template <typename NewType>
				struct rebind
				{
					typedef Allocator<NewType> other;
				};
			Allocator() = default;
			~Allocator() = default;
			Allocator(const Allocator& rhs) = default;
			pointer address(reference x) const
			{ return &x; }
			const_pointer address(const_reference x) const
			{ return &x; }
			pointer allocate(size_type n/*, const void* p = 0*/)
			{
				return (n == 0) ? 0 : (pointer)_alloc.allocate(n * sizeof(value_type));
			}
			void deallocate(pointer p, size_type n)
			{
				_alloc.deallocate(p, n * sizeof(value_type));
			}
			pointer reallocate(pointer p, size_type new_size, size_type old_size)
			{
				_alloc.reallocate(p, new_size * sizeof(value_type), old_size * sizeof(value_type));
			}
			size_type max_size()
			{
				return size_type(UINT_MAX/sizeof(value_type));//UINT_MAX在climits里面
			}
			void construct(pointer p, const_reference x)
			{
				MyStl::construct<value_type, value_type>(p, x);
			}
			void destroy(pointer p)
			{
				MyStl::destroy<value_type>(p);
			}
			private:
			Alloc _alloc;
		};
}

#endif
