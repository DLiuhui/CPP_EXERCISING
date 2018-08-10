///
/// @file    main.cc
/// @author  LiuhuiDing@gmail.com
/// @date    2018-08-01 23:05:07
///
#include "text_query.h"
#include <iostream>
using std::cin;
using std::cout;
using std::endl;

#define FILE2 "china_daily.txt"

int main(int argc, char **argv)
{
	Primer::TextQuery query;
	query.read(FILE2);
	query.search("the");
	return 0;
}
