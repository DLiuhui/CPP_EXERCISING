///
/// @file    rss_reader.h
/// @author  LiuhuiDing@gmail.com
/// @date    2018-08-05 16:57:58
///

#ifndef RSS_READER_H_
#define RSS_READER_H_
#include "tinyxml2.h"
#include <iostream>
#include <string>
#include <fstream>
#include <memory>
#include <vector>
#include <sstream>
#include <regex>

namespace WdCoding
{
	class RssReader
	{
		public:
			RssReader();
			~RssReader();
			void parseRss(std::string &&);	//解析rss .XML文件
			void dump() const;	//输出pagelib.dat文件
		private:
			std::ofstream & contentOut(std::ofstream &, const std::string &) const;	//对文章描述或者内容的处理输出
			struct RssItem
			{
				RssItem() = default;
				~RssItem() = default;
				std::string title;
				std::string link;
				std::string description;
				std::string pubDate;
				std::string creator;
				std::string content;
			};
			std::shared_ptr<std::vector<RssItem>> _rss;
			std::string _web_title;
			std::string _web_link;
			std::string _web_description;
	};
}

#endif
