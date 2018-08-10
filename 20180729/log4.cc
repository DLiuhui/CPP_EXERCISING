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
#include <log4cpp/FileAppender.hh>
#include <string>
#include <sstream>

using std::cin;
using std::cout;
using std::endl;

int main(int argc, char **argv)
{
	log4cpp::OstreamAppender *osAppender1 = new log4cpp::OstreamAppender("osAppender1", &cout);
	log4cpp::PatternLayout *pLayout1 = new log4cpp::PatternLayout;
	pLayout1->setConversionPattern("%d: %p---%m%n");
	osAppender1->setLayout(pLayout1);

	log4cpp::FileAppender *fileAppender = new log4cpp::FileAppender("fileAppender", "log4.log");
	log4cpp::PatternLayout *pLayout2 = new log4cpp::PatternLayout;
	pLayout2->setConversionPattern("%d: %p %c %x: %m%n");
	fileAppender->setLayout(pLayout2);
	fileAppender->setLayout(pLayout2);

	log4cpp::Category &root = log4cpp::Category::getRoot();
	root.setPriority(log4cpp::Priority::DEBUG);
	log4cpp::Category &sub1 = root.getInstance("sub1");
	sub1.addAppender(osAppender1);
	sub1.setPriority(log4cpp::Priority::DEBUG);
	sub1.error("suberror");
	log4cpp::Category &sub2 = root.getInstance("sub2");
	sub2.addAppender(fileAppender);
	sub2.setPriority(101);
	sub2.warn("sub2warning");
	sub2.fatal("sub2fatal");
	sub2.alert("sub2alert");
	sub2.crit("sub2cirt");
	log4cpp::Category::shutdown();
	return 0;
}
