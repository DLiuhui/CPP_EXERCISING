///
/// @file    rss_reader.cc
/// @author  LiuhuiDing@gmail.com
/// @date    2018-08-05 17:11:16
///

#include "rss_reader.h"
namespace WdCoding
{
	RssReader::RssReader():
		_rss(std::make_shared<std::vector<RssItem>>()),
		_web_title(std::string()),
		_web_link(std::string()),
		_web_description(std::string())
	{}

	RssReader::~RssReader() = default;

	void RssReader::parseRss(std::string && filename)
	{
		using tinyxml2::XMLElement;
		using tinyxml2::XMLDocument;
		using std::cout;
		using std::endl;
		XMLDocument doc;
		doc.LoadFile(filename.c_str());
		if(doc.Error()){
			std::cerr<<"load file error"<<endl;
			return;
		}
		XMLElement *root = doc.RootElement();
		XMLElement *channel = root->FirstChildElement("channel");
		if(NULL==channel){
			std::cerr<<"get first chile element error "<<endl;
			return;
		}
		XMLElement *title = channel->FirstChildElement("title");
		XMLElement *link = channel->FirstChildElement("link");
		XMLElement *description = channel->FirstChildElement("description");
		XMLElement *item = channel->FirstChildElement("item");
		if(title)
		{
			_web_title = title->GetText();
		}
		if(link)
		{
			_web_link = link->GetText();
		}
		if(description)
		{
			_web_description = title->GetText();
		}
		while(item)
		{
			RssItem tmp;
			XMLElement *item_child = item->FirstChildElement();
			while(item_child){
				if(!strcmp(item_child->Name(),"title")){
					tmp.title = item_child->GetText();
				}else if(!strcmp(item_child->Name(),"link")){
					tmp.link = item_child->GetText();
				}else if(!strcmp(item_child->Name(),"description")){
					tmp.description = item_child->GetText();
				}else if(!strncmp(item_child->Name(),"content", 7)){
					tmp.content = item_child->GetText();
				}else if(!strcmp(item_child->Name(),"pubDate")){
					tmp.pubDate = item_child->GetText();
				}else if(!strcmp(item_child->Name(),"dc:creator")){
					tmp.creator = item_child->GetText();
				}
				item_child = item_child->NextSiblingElement();
			}
			_rss->push_back(tmp);
			item = item->NextSiblingElement();
		}
	}

	void RssReader::dump() const
	{
		std::ofstream _ostream("pagelib.dat");
		if(std::string() != _web_title)
		{ _ostream<<"<title>" << _web_title << "</title>" << std::endl; };		
		if(std::string() != _web_link)
		{ _ostream<<"<link>" << _web_link << "</link>" << std::endl; };		
		if(std::string() != _web_description)
		{ _ostream<<"<description>" << _web_description << "</description>" << std::endl; };
		_ostream << std::endl;

		for(std::vector<RssItem>::const_iterator iter = _rss->cbegin(); iter != _rss->cend(); ++iter)
		{
			_ostream << "<doc>" << std::endl;
			_ostream << "    <title>"<< iter->title << "</title>"<<std::endl;
			_ostream << "    <link>" << iter->link << "</link>" << std::endl;
			if(std::string() != iter->pubDate){ _ostream << "    <pubDate>" << iter->pubDate << "</pubDate>" << std::endl; }
			if(std::string() != iter->creator){ _ostream << "    <dc:creator>" << iter->creator << "</dc:creator>" << std::endl; }
			if(std::string() != iter->description) 
			{
				_ostream << "    <description>";
				contentOut(_ostream, iter->description);
				_ostream << "    </description>" << std::endl; 
			}
			if(std::string() != iter->content)
			{
				_ostream << "    <content>" << std::endl;
				contentOut(_ostream, iter->content);
				_ostream << "    </content>" << std::endl; }
			_ostream << "</doc>" << std::endl;
			_ostream << std::endl;
		}
		_ostream.close();
	}

	std::ofstream & RssReader::contentOut(std::ofstream &os, const std::string &content) const
	{
		std::istringstream is(content);
		std::string line;	//按照行处理
		std::regex rule("<(\\S*?)[^>]*>.*?|<.*? />");
		std::regex para_end("</p>$");
		std::regex make_para("</p>");
		while(std::getline(is,line))
		{
			if(std::string() == line)
				os << line;
			else
			{
				line = std::regex_replace(line, para_end, "<p>");
				line = std::regex_replace(line, make_para, "\n    ");
				line = std::regex_replace(line, rule, "");
				if(std::string() == line)
					continue;
				os << "    " << line << std::endl;
			}
		}
		return os;
	}
}
