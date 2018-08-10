///
/// @file    main.cpp
/// @author  LiuhuiDing@gmail.com
/// @date    2018-08-02 23:15:26
///

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <memory>
#include "tinyxml2.h"
using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::shared_ptr;
using std::make_shared;
using namespace tinyxml2;

void example3()
{
	XMLDocument doc;	//初始化该类
	doc.LoadFile("test3.xml");	//加载需要的xml文件
	XMLElement *root = doc.RootElement();
	XMLElement *channel = root->FirstChildElement("channel");
	XMLElement *element = channel->FirstChildElement();
	while(element)
	{
		cout << element->Name();
		if(element->GetText())	//标题有内容
			cout << " " << element->GetText() << endl;
		else
			cout << endl;
		if(element->FirstChildElement())	//有孩子
		{
			XMLElement *child = element->FirstChildElement();
			int i = 1;
			while(child)
			{
				cout << i << ": " << child->Name() << " " << child->GetText() << endl;
				++i;
				child = child->NextSiblingElement();
			}
		}
		element = element->NextSiblingElement();
	}
}

void example2()
{
	XMLDocument doc;	//初始化该类
	doc.LoadFile("test2.xml");	//加载需要的xml文件
	XMLElement *scene = doc.RootElement();
	XMLElement *surface = scene->FirstChildElement("node");
	while(surface)
	{
		XMLElement *surfaceChild = surface->FirstChildElement();
		const char* content;
		const XMLAttribute *attributeOfSurface = surface->FirstAttribute();
		cout << attributeOfSurface->Name() << ":" << attributeOfSurface->Value() << endl;
		while(surfaceChild)
		{
			content = surfaceChild->GetText();
			surfaceChild = surfaceChild->NextSiblingElement();
			cout << content << endl;
		}
		surface = surface->NextSiblingElement();
	}
}

struct RssItem{
	RssItem() = default;
	~RssItem() = default;
	string title;
	string link;
	string description;
	string pubDate;
	string creator;
	string content;
};

void traverse(shared_ptr<vector <RssItem>> _rss)
{
	std::ofstream _ostream("pagelib.dat");
	for(vector<RssItem>::const_iterator iter = _rss->cbegin(); iter != _rss->cend(); ++iter)
	{
		_ostream<<"<doc>"<<endl;
		_ostream<<"    <title>"<< iter->title << "</title>"<<endl;
		_ostream<<"    <link>"<< iter->link<<"</link>"<<endl;
		if(string() != iter->pubDate){ _ostream<<"    <pubDate>" << iter->pubDate << "</pubDate>" << endl; }
		if(string() != iter->creator){ _ostream<<"    <dc:creator>"<<iter->creator<<"</dc:creator>" << endl; }
		if(string() != iter->description) { _ostream<<"    <description>"<< iter->description<<"</description>"<<endl; }
		if(string() != iter->content) { _ostream<<"    <content>"<< iter->content<<"</content>"<<endl; }
		_ostream<<"</doc>"<<endl;
		_ostream << endl;
	}
	_ostream.close();
}

void example4()
{
	shared_ptr<vector<RssItem>> information_vector = make_shared<vector<RssItem>>();
	XMLDocument doc;
	doc.LoadFile("test5.xml");
	if(doc.Error()){
		std::cerr<<"load file error"<<endl;
		return;
	}
	//  doc.Print();
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
		cout << "<" << title->Name() << ">";
		if(title->GetText())
			cout << title->GetText();
		cout << "</" << title->Name() << ">" << endl;
	}
	if(link)
	{
		cout << "<" << link->Name() << ">";
		if(link->GetText())
			cout << link->GetText();
		cout << "</" << link->Name() << ">" << endl;
	}
	if(description)
	{
		cout << "<" << description->Name() << ">";
		if(description->GetText())
			cout << description->GetText();
		cout << "</" << description->Name() << ">" << endl;
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
		information_vector->push_back(tmp);
		item = item->NextSiblingElement();
	}
	traverse(information_vector);
}
int main()
{
	//example2();
	//example3();
	example4();
	return 0;
}
