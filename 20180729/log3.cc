///
/// @file    helloworld_log4cpp.cc
/// @author  LiuhuiDing@gmail.com
/// @date    2018-07-29 20:30:39
///

#include <iostream>
#include <log4cpp/Category.hh>
#include <log4cpp/OstreamAppender.hh>
#include <log4cpp/BasicLayout.hh>
#include <log4cpp/Priority.hh>
#include <log4cpp/PatternLayout.hh>
#include <log4cpp/RollingFileAppender.hh>
#include <string>
#include <sstream>

using std::cin;
using std::cout;
using std::endl;

int main(int argc, char **argv)
{
	log4cpp::Appender *fileAppender = new log4cpp::FileAppender("fileAppender", "haha.log");
	log4cpp::RollingFileAppender *rollFileAppender = new log4cpp::RollingFileAppender("rollFileAppender", "xx.log", 5*1024,1);
	//设置输出格式
	log4cpp::PatternLayout *pLayout = new log4cpp::PatternLayout;
	pLayout->setConversionPattern("%d: %p %c %x: %m%n");
	log4cpp::PatternLayout *pLayout1 = new log4cpp::PatternLayout;
	pLayout1->setConversionPattern("%d: %p %c %x: %m%n");
	fileAppender->setLayout(pLayout);
	rollFileAppender->setLayout(pLayout1);

	log4cpp::Category &root = log4cpp::Category::getRoot().getInstance("RootName");
	root.addAppender(fileAppender);
	root.addAppender(rollFileAppender);
	root.setPriority(log4cpp::Priority::DEBUG);
	for(int i = 0; i < 100; i++)
	{
		std::string strError;
		std::ostringstream oss;
		oss << i << ":Root Error Message";
		strError = oss.str();
		root.error(strError);
	}
	log4cpp::Category::shutdown();
	return 0;
}
