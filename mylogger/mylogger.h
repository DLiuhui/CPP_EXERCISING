///
/// @file    mylogger.h
/// @author  LiuhuiDing@gmail.com
/// @date    2018-07-29 23:56:47
///

#ifndef MY_LOGGER_H
#define MY_LOGGER_H
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <iostream>
#include <string>
#include <sstream>
#include <log4cpp/Appender.hh>
#include <log4cpp/Category.hh>
#include <log4cpp/Priority.hh>
#include <log4cpp/OstreamAppender.hh>
#include <log4cpp/RollingFileAppender.hh>
#include <log4cpp/PatternLayout.hh>

namespace Log
{

class MyLogger
{
public:
	//使用模板 可变参数包
	template <typename ...Args>
	void warn(const char *msg, Args... args)
	{
		root_.warn(msg, args...);
	}
	template <typename ...Args>
	void error(const char *msg, Args... args)
	{
		root_.error(msg, args...);
	}
	template <typename ...Args>
	void debug(const char *msg, Args... args)
	{
		root_.debug(msg, args...);
	}
	template <typename ...Args>
	void info(const char *msg, Args... args)
	{
		root_.info(msg, args...);
	}
	void setLayout(const char *);	//重新设置格式
	static MyLogger * getLogger(const std::string &filename = "mylog",
			const std::string &layout = "%d [%p] %m%n")
	{
		if(NULL == pmylogger_)
		{
			pmylogger_ = new MyLogger(filename, layout);
		}
		return pmylogger_;
	}
	static void destroy()
	{
		if(pmylogger_)
		{
			delete pmylogger_;
		}
	}
private:
	MyLogger(const std::string&, const std::string&);
	~MyLogger();
	log4cpp::Category &root_;	//种类
	log4cpp::Appender *fileAppender_;	//输出：输出文件
	log4cpp::Appender *osAppender_;	//输出：控制台
	log4cpp::PatternLayout *fileLayout_;	//file格式
	log4cpp::PatternLayout *osLayout_;	//os格式
	static MyLogger *pmylogger_;
};

//利用宏将处理进行封装
//考虑到__FUNCTION__/__func__/__LINE__与函数实际运行情况相关联，调用宏是最好的
//可以输入可变参数的宏
#define logMsg(str) ((std::string(str) + \
				" [" + __FILE__ + "-" + __FUNCTION__ + "-"\
				+ std::to_string(__LINE__) + "]").c_str())\

//将宏修改为可接收可变参数宏，##__VA_ARGS__接收可变参数，##表示如果可变参数为空，则消去前导逗号
#define logWarn(str, ...) MyLogger::getLogger()->warn(logMsg(str), ##__VA_ARGS__)
#define logError(str, ...) MyLogger::getLogger()->error(logMsg(str), ##__VA_ARGS__)
#define logDebug(str, ...) MyLogger::getLogger()->debug(logMsg(str), ##__VA_ARGS__)
#define logInfo(str, ...) MyLogger::getLogger()->info(logMsg(str), ##__VA_ARGS__)

}
#endif
