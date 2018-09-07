 ///
 /// @file    1_13.h
 /// @author  LiuhuiDing@gmail.com
 /// @date    2018-07-23 22:08:46
 ///
 
#ifndef __COLLECTION_H__
#define __COLLECTION_H__

#include <iostream>
#include <string>
#include <vector>
#include <iterator>

template <typename Object>
class Collection
{
public:
	Collection()
	{
		size = 0;	//大小为0
	}
	Collection(Object &obj, const unsigned int size)
	{
		this->size = size;
		for(unsigned int i = 0; i < size; i++)
		{
			arr.push_back(obj);
		}
	}
	Collection(const Collection &item)
	{
		size = item.size;
		arr = item.arr;
	}
	bool is_empty() const
	{
		return size ? false:true;
	}
	void make_empty()
	{
		size = 0;
		arr.clear();	//执行vector的清空操作
	}
	void insert(const Object &key, const int pos)	//在pos位置插入
	{
		int i = 0;
		auto iter = arr.begin();
		while(i++ < pos+1 && iter != arr.end())
		{
			iter++;
		}
		arr.insert(iter, key);
		size++;
	}
	void insert(const Object &key)
	{
		arr.push_back(key);
		size++;
	}
	void remove(const int pos)
	{
		int i = 0;
		auto iter = arr.begin();
		while(i++ < pos && iter != arr.end())
		{
			iter++;
		}
		if(iter != arr.end())
		{
			arr.erase(iter);
			size--;
		}
	}
	void remove()
	{
		if(size > 0)
		{
			arr.erase(--arr.end());
			size--;
		}
	}
	bool contains(const Object &x) const
	{
		auto iter = arr.begin();
		while(iter != arr.end())
		{
			if(*iter == x)
				return true;
			iter++;
		}
		return false;
	}
	bool findMax(Object &x) const
	{
		if(!is_empty())
		{
			unsigned int pos = 0;
			for(unsigned int i = 0; i < arr.size(); i++)
			{
				if(arr[i] > arr[pos])
					pos = i;
			}
			x = arr[pos];
			return true;
		}
		return false;
	}
	bool findMin(Object &x) const
	{
		if(!is_empty())
		{
			unsigned int pos = 0;
			for(unsigned int i = 0; i < arr.size(); i++)
			{
				if(arr[i] < arr[pos])
					pos = i;
			}
			x = arr[pos];
			return true;
		}
		return false;
	}
private:
	std::vector<Object> arr;
	unsigned int size;
};
 
#endif
