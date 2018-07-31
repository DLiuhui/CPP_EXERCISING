///
/// @file    main.cc
/// @author  LiuhuiDing@gmail.com
/// @date    2018-07-31 10:27:47
///

#include "strBlob.h"
#include "file.h"
#include <iostream>
#include <string>
#include <vector>
using std::cin;
using std::cout;
using std::endl;

int main(int argc, char **argv)
{
	Primer::StrBlob str({"dsd", "asdasd", "sadsad", "cvxcx", "hahah"});
	cout << str.size() << endl;
	cout << str.back() << endl;
	cout << str.front() << endl;
	Primer::makefile();
	return 0;
}
