///
/// @file    main.cc
/// @author  LiuhuiDing@gmail.com
/// @date    2018-08-01 23:05:07
///
#include "text_query.h"
#include <iostream>
#include <fstream>
using std::cin;
using std::cout;
using std::endl;

#define FILE2 "The_Holy_Bible.bak"

int main(int argc, char **argv)
{
	std::ifstream ifs(FILE2);
	Primer::TextQuery text(ifs);
	Primer::Query query = Primer::Query("god") & Primer::Query("earth") | Primer::Query("devil");
	Primer::print(cout ,query.eval(text));
	return 0;
}
