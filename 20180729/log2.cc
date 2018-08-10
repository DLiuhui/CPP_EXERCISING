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
#include <log4cpp/StringQueueAppender.hh>
#include <queue>
#include <string>
using std::cin;
using std::cout;
using std::endl;

int main(int argc, char **argv)
{
	log4cpp::StringQueueAppender *strAppender = new log4cpp::StringQueueAppender("strAppender");
	//设置输出格式
	log4cpp::PatternLayout *pLayout = new log4cpp::PatternLayout;
	pLayout->setConversionPattern("%d: %p %c %x: %m%n");
	strAppender->setLayout(pLayout);
	log4cpp::Category &root = log4cpp::Category::getRoot();
	root.addAppender(strAppender);
	root.setPriority(log4cpp::Priority::DEBUG);

	root.error("Hello log4pp in a Error Message");
	root.warn("Hello log4cpp in a Warning Message");
	root.info("This is a information");
	std::queue<std::string> &myStrQ = strAppender->getQueue();
	while(!myStrQ.empty())
	{
		cout << myStrQ.front();
		myStrQ.pop();
	}
	log4cpp::Category::shutdown();
	return 0;
}
