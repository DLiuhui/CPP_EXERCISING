///
/// @file    RAII.cc
/// @author  LiuhuiDing@gmail.com
/// @date    2018-08-30 21:14:46
///
//RAII资源管理技术

#include <stdio.h>
#include <iostream>
#include <stdexcept>
using std::cin;
using std::cout;
using std::endl;

class SafeFile
{
	public:
		SafeFile(const char* filename)
			:fptr_(fopen(filename, "w+"))
		{
			if(NULL == fptr_)
			{
				throw std::runtime_error("Open Error");
			}
		}
		~SafeFile()
		{ fclose(fptr_); }
		//禁止拷贝和复制
		SafeFile(const SafeFile&) = delete;
		SafeFile& operator=(const SafeFile&) = delete;
		void write(const char* str)
		{
			if(fputs(str, fptr_) == EOF)
			{
				throw std::runtime_error("Write Error");
			}
		}
		void write(const char* buffer, std::size_t num)
		{
			if(num != 0 && fwrite(buffer, 1, num, fptr_) == 0)
			{
				throw std::runtime_error("Open Error");
			}
		}
	private:
		FILE* fptr_;
};
int main(int argc, char **argv)
{
	SafeFile testVar("foo.test");
	testVar.write("Hello World.");
	return 0;
}
