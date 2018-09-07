 ///
 /// @file    matrix.h
 /// @author  LiuhuiDing@gmail.com
 /// @date    2018-07-23 20:02:56
 ///
 
#ifndef __MATRIX_H__
#define __MATRIX_H__

#include <iostream>
#include <vector>

template <typename Object>
class Matrix
{
public:
	Matrix() = default;	//利用vector的内置初始化
	Matrix(int rows, int cols):
		array_(rows)
	{
		for(auto & this_row : array_)
		{
			this_row.resize(cols);
		}
	}
	Matrix(std::vector<std::vector<Object>> v):
		array_(v)
	{}
	//移动构造函数
	Matrix(std::vector<std::vector<Object>> && v):
		array_(std::move(v))
	{}
	/*出现m[i] = m[j] 的情况时，等号左侧需要是非const，右侧可以是const，
	 为了解决可以定义 返回 常量引用和非常量引用 两个版本的[]重载函数*/
	const std::vector<Object> & operator[](int row) const
	{
		return array_[row];
	}
	std::vector<Object> & operator[](int row)
	{
		return array_[row];
	}

	int numrows() const
	{
		return array_.size();
	}

	int numcols() const
	{
		return numrows() ? array_[0].size() : 0;	//如果行数为0，则列数也为0，矩阵空
	}

	void resize(int rows, int cols)
	{
		array_.resize(rows);	//改为rows行
		for(auto iter=array_.begin(); iter != array_.end(); iter++)
		{
			iter->resize(cols);	//每一行改为cols列
		}
	}
private:
	std::vector<std::vector<Object>> array_;
};
 
#endif
