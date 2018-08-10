///
/// @file    main.cpp
/// @author  LiuhuiDing@gmail.com
/// @date    2018-08-02 23:15:26
///

#include "rss_reader.h"
#include "tinyxml2.h"
#include <iostream>
using std::cin;
using std::cout;
using std::endl;

int main()
{
	WdCoding::RssReader rss;
	rss.parseRss("test4.xml");
	rss.dump();
	return 0;
}
