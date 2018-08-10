///
/// @file    log5.cc
/// @author  LiuhuiDing@gmail.com
/// @date    2018-07-29 22:57:47
///

#include <iostream>
#include <log4cpp/NDC.hh>
using namespace log4cpp;
using std::cin;
using std::cout;
using std::endl;

int main(int argc, char **argv)
{
	cout << "1.empty NDC:" << NDC::get() << endl;
	NDC::push("context1");
	cout << "2.push context1:" << NDC::get() << endl;
	NDC::push("context2");
	cout << "3.push context2:" << NDC::get() << endl;
	NDC::push("context3");
	cout << "4.push context3:" << NDC::get() << endl;
	cout << "5.get depth:" << NDC::getDepth() << endl;
	cout << "6.pop:" << NDC::pop() << endl;
	cout << "7.after pop:" << NDC::get() << endl;
	NDC::clear();
	cout << "8.clear:" << NDC::get() << endl;
	return 0;
}
