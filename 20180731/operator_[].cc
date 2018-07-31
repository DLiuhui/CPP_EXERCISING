///
/// @file    operator_[].cc
/// @author  LiuhuiDing@gmail.com
/// @date    2018-07-31 17:05:44
///

#include <iostream>
#include <string>
#include <cstring>
using std::cin;
using std::cout;
using std::endl;
//重载[]
//
class CharArray
{
	public:
		CharArray(int size)
			: size_(size)
			  , pdata_(new char[size]())
	{}
		char & operator[](size_t idx)
		{
			if(idx < size_)
			{
				return pdata_[idx];
			}
			else
			{
				//下标越界错误
				static char null = '\0';
				cout << "下标越界" << endl;
				return null;
			}
		}
		size_t size() const {return size_;}
		~CharArray()
		{
			delete []pdata_;
		}
	private:
		size_t size_;
		char *pdata_;
};
int main(int argc, char **argv)
{
	const char * pstr = "hello,world";
	CharArray ca(strlen(pstr) + 1);

	for(size_t idx = 0; idx != ca.size(); ++idx)
	{
		ca[idx] = pstr[idx];// 修改
	}
	cout << endl;

	for(size_t idx = 0; idx != ca.size(); ++idx)
	{
		cout << ca[idx] << " " <<  endl;
	}

	return 0;
}
