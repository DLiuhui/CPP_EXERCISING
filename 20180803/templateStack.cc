///
/// @file    templateStack.cc
/// @author  LiuhuiDing@gmail.com
/// @date    2018-08-03 14:42:31
///

#include <iostream>
#include <vector>
#include <string>
using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::size_t;

template <typename Type, size_t kSize = 10>
class Stack
{
public:
	Stack():
		_top(0), _data()
	{
		_data.reserve(kSize);
	}
	~Stack() = default;
	void pop();
	void push(const Type &);
	bool empty()
	{
		return (_top == 0)?true:false;
	}
	bool full()
	{
		return (_top == kSize)?true:false;
	}
	Type & top();
private:
	int _top;
	vector<Type> _data;
};

template <typename Type, size_t kSize>
void Stack<Type, kSize>::pop()
{
	if(!empty())
		--_top;
}

template <typename Type, size_t kSize>
void Stack<Type, kSize>::push(const Type &data)
{
	if(!full())
	{
		++_top;
		_data.push_back(data);
	}
}

template <typename Type, size_t kSize>
Type & Stack<Type, kSize>::top()
{
	return _data[_top-1];
}

int main(int argc, char **argv)
{
	Stack<int> s;
	for(unsigned int i = 0; i < 20; i++)
	{
		s.push(i);
	}
	cout << s.full() << endl;
	cout << s.top() << endl;
	s.pop();
	cout << s.top() << endl;
	return 0;
}
