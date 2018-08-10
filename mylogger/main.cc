///
/// @file    main.cc
/// @author  LiuhuiDing@gmail.com
/// @date    2018-07-30 15:57:07
///

#include "mylogger.h"
#include <iostream>
using std::cin;
using std::cout;
using std::endl;
using namespace Log;
MyLogger * MyLogger::pmylogger_ = NULL;
int main(int argc, char **argv)
{
	MyLogger *log = MyLogger::getLogger("A1");
	logInfo("info %d %s", 15, "hahahah");
	logError("error %s", "nononono");
	logWarn("warn %s", "xxxxxx");
	logDebug("debug %s", "gogogog");
	log->destroy();
	return 0;
}
