///
/// @file    RAII_PTR.cc
/// @author  LiuhuiDing@gmail.com
/// @date    2018-08-30 22:33:04
///
//利用RAII模拟智能指针
#include <iostream>
#include <memory>
using std::cin;
using std::cout;
using std::endl;

template <typename T>
class RAII
{
	public:
		explicit RAII(T* p)
			:ptr_(p)
		{}
		~RAII()
		{
			delete ptr_;
		}
		void reset(T* p)
		{
			delete ptr_;
			ptr_ = p;
		}
		T* get() const
		{
			return ptr_;
		}
		T& operator*() const
		{
			return *ptr_;
		}
		void swap(RAII& other)
		{
			std::swap(ptr_, other.ptr_);
		}
	private:
		RAII(const RAII& other);	//禁止拷贝
		RAII& operator=(const RAII& other);	//禁止拷贝
		T* ptr_;
};


/*
** 现在即使p_成功而p2_失败，那么在Stack winding时也会调用
** RAII的析构函数保证了p_指向的Someresource被析构。
** Example中，已经不需要析构函数了
*/
template <typename SomeResource>
class Example {
	public:
	Example()
		: p_(new SomeResource()),
		p2_(new SomeResource()) {}
	Example(const Example& other)
		: p_(new SomeResource(*other.p_.get())),
		p2_(new SomeResource(*other.p2_.get())) {}
	Example& operator=(const Example& other) {
		//Self assignment?
		if (this==&other)
			return *this;
#if 0
		*p_=*other.p_;
		*p2_=*other.p2_;
#endif
		p_.reset(other.p_.get());
		p2_.reset(other.p2_.get());    
		return *this;
	}
	~Example() {
		std::cout << "Deleting Example, freeing SomeResource!" << std::endl;
	}
	private:
	RAII<SomeResource> p_;
	RAII<SomeResource> p2_;
};

int main(int argc, char **argv)
{
	Example<int> ex1;
	Example<int> ex2(ex1);
	return 0;
}
