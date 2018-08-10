///
/// @file    dictionary.h
/// @author  LiuhuiDing@gmail.com
/// @date    2018-07-27 22:27:40
///
#ifndef DICTIONARY_H_
#define DICTIONARY_H_
#include <ctype.h>
#include <vector>
#include <string>
#include <cstring>
#include <fstream>
#include <sstream>
#include <iostream>

namespace WdCoding
{

	//生成字典文件
	class Dictionary
	{
		public:
			struct DictionaryItem
			{
				std::string word_;
				int times_;
				DictionaryItem():
					word_(std::string()), times_(0)
				{}
				DictionaryItem(const std::string &s, int t):
					word_(s), times_(t)
				{}
			};
			Dictionary();
			Dictionary(const std::string &filename);	//由外部文件初始化
			~Dictionary();
			void makeDictionary(const std::string&);	//从外部文件建立字典
			bool read(const std::string&);	//对读入的文章进行处理，方便字典统计，生成字典队列dic_queue
			void store(const std::string&);	//从dic_queue生成.dictionary文件
			void makeHeap();	//建立大根堆
			void wordsOuccMost(unsigned int);	//输出出现次数最多的单词
		private:
			class Heap	//大根堆
			{
				public:
					Heap();
					~Heap();
					void heapInsert(const DictionaryItem &);	//堆插入
					DictionaryItem heapPop();	//堆删除
					unsigned int size() const {return heap_.size();}
					static const unsigned int INIT_SIZE = 100;
				private:
					void heapInsertSort();	//堆插入调整
					void heapPopSort();	//堆删除调整
					std::vector<DictionaryItem> heap_;
			};
			class Trie	//字典树
			{
				public:
					struct Node
					{
						int times_;	//根到该节点所构成的单词出现的次数
						bool end_;	//标记是否是最后一个结点
						Node *child_;	//指向26个字母的孩子节点
						Node():
							times_(0), end_(true), child_(NULL)
						{}
					};
					Trie():
						root_(new Node())
					{}
					~Trie();
					void insert(const std::string &);
					bool search(const std::string &) const;
					std::ofstream & printInPost(std::ofstream &os) const;	//先序遍历字典树并打印进文件
				private:
					//void treeInsert(Node*, const std::string);
					void destroy(Node *root);
					std::ofstream & postPrint(std::ofstream &, Node *, std::string) const;
					Node *root_;
			};
			bool wordStandardizing(std::string&);	//对单词标准化处理
			std::string filename_;	//保存字典对应的文件名
			Heap most_occuring_words_;	//出现次数最多的单词
			Trie word_tree_;	//字典树
	};

}
#endif
