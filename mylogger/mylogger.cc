///
/// @file    mylogger.cc
/// @author  LiuhuiDing@gmail.com
/// @date    2018-07-30 15:51:15
///

#include "mylogger.h"

namespace Log
{

MyLogger::MyLogger(const std::string &filename, const std::string &layout):
	root_(log4cpp::Category::getRoot().getInstance("RootName")),
	fileAppender_(new log4cpp::RollingFileAppender("RollingLog", filename, 5*1024*1024, 5)),
	osAppender_(new log4cpp::OstreamAppender("osAppender", &std::cout)),
	fileLayout_(new log4cpp::PatternLayout()),
	osLayout_(new log4cpp::PatternLayout())
{
	osLayout_->setConversionPattern(layout);	//格式设置
	fileLayout_->setConversionPattern(layout);
	root_.setPriority(log4cpp::Priority::DEBUG);
	root_.addAppender(fileAppender_);
	root_.addAppender(osAppender_);
	osAppender_->setLayout(osLayout_);
	fileAppender_->setLayout(fileLayout_);
}

MyLogger::~MyLogger()
{
	log4cpp::Category::shutdown();
}

void MyLogger::setLayout(const char *layout)
{
	osLayout_->setConversionPattern(layout);
	fileLayout_->setConversionPattern(layout);
	osAppender_->setLayout(osLayout_);
	fileAppender_->setLayout(fileLayout_);
}

}
