 ///
 /// @file    NullPtr.cc
 /// @author  LiuhuiDing@gmail.com
 /// @date    2018-07-26 15:11:01
 ///
 
#include <iostream>
using std::cin;
using std::cout;
using std::endl;
 
class CNullPointCall
{
public:
	static void Test1()
	{
		cout << m_iStatic << endl;
	}
	void Test2()
	{
		cout << "2" << endl;
	}
	void Test3(int iTest)
	{
		cout << iTest << endl;
	}
	void Test4()
	{
		cout << m_iTest << endl;
	}
private:
	static int m_iStatic;
	int m_iTest;
};

int CNullPointCall::m_iStatic = 0;

int main(int argc, char **argv)
{
	CNullPointCall *p = NULL;
	p->Test1();	//能够调用，p是CNullPointCall类型，能够调用共享的静态类成员
	p->Test2();	//能够调用，不涉及类非静态成员访问，类的成员共享类成员函数
	p->Test3(10);	//能够调用，理由同Test2
	//p->Test4();	//不能调用，涉及到类成员访问，但是p是NULL，发生访存段错误
	return 0;
}
