///
/// @file    operator_pointer.cc
/// @author  LiuhuiDing@gmail.com
/// @date    2018-07-31 17:15:13
///

#include <iostream>
using std::cin;
using std::cout;
using std::endl;
class Data
{
	public:
		Data()
			:ix_(10)
		{
			cout << "Data()" << endl;
		}
		int getX() const {return ix_;}
		~Data()
		{
			cout << "~Data()" << endl;
		}
	private:
		int ix_;
};

class MiddleLayer
{
	public:
		MiddleLayer()
			:pdata_(new Data)
		{
			cout << "MiddleLayer()" << endl;
		}
		//指针运算符返回值是指针
		Data * operator->()
		{
			return pdata_;
		}
		//解引用运算符
		Data & operator*()
		{
			return *pdata_;
		}
		~MiddleLayer()
		{
			cout << "~MiddleLayer()" << endl;
			delete pdata_;
		}
	private:
		Data *pdata_;
};

class ThirdLayer
{
	public:
		ThirdLayer()
			: _pMiddleLayer(new MiddleLayer())
		{
			cout << "ThirdLayer()" << endl;
		}
		//指针运算符返回一个重载了指针运算符的对象
		MiddleLayer & operator->()
		{
			return *_pMiddleLayer;
		}

		~ThirdLayer() 
		{
			cout << "~ThirdLayer()" << endl;
		}
	private:
		MiddleLayer * _pMiddleLayer;
};
int main(int argc, char **argv)
{
	MiddleLayer m1; //m1本身是对象，智能指针的雏形
	//重载了->和*，这样通过中间层就可以直接访问到数据层的接口
	//如果不重载，需要m1.pdata->getX()，但是由于pdata是m1的私有成员
	//所以无法直接访问
	cout << (*m1).getX() << endl;
	cout << m1->getX() << endl;
	cout << (m1.operator->())->getX() << endl;
	cout << endl;
	ThirdLayer tl;
	cout << tl->getX() << endl;
	cout << ((tl.operator->()).operator->())->getX() << endl;
	return 0;
}
