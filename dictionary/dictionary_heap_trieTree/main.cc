///
/// @file    main.cc
/// @author  LiuhuiDing@gmail.com
/// @date    2018-07-27 23:58:33
///

#include <iostream>
#include "dictionary.h"
using std::cin;
using std::cout;
using std::endl;

int main(int argc, char **argv)
{
	WdCoding::Dictionary dic;
	dic.makeDictionary("The_Holy_Bible.bak");
	dic.wordsOuccMost(20);
	return 0;
}
