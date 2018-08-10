///
/// @file    dictionary.cc
/// @author  LiuhuiDing@gmail.com
/// @date    2018-07-27 23:55:02
///

#include "dictionary.h"

namespace WdCoding
{

	Dictionary::Dictionary():
		filename_(std::string()), most_occuring_words_(Heap()),
		word_tree_(Trie())
	{}

	Dictionary::~Dictionary() = default;

	Dictionary::Dictionary(const std::string &filename):
		filename_(std::string()), most_occuring_words_(Heap()),
		word_tree_(Trie())
	{
		if(read(filename))
		{
			filename_ = filename;
			store(filename);
		}
	}

	void Dictionary::makeDictionary(const std::string &filename)
	{
		if(read(filename))
		{
			store(filename);
		}
	}

	bool Dictionary::read(const std::string &filename)
	{
		std::ifstream ifs(filename, std::ios::in);
		if(!ifs)
		{
			std::cout << "file path error" << std::endl;
			return false;
		}
		filename_ = filename;
		std::string word;
		std::string line;
		while(getline(ifs, line))
		{
			std::istringstream ss(line);
			while(ss>>word)
			{
				if(wordStandardizing(word))
				{
					word_tree_.insert(word);
				}
			}
		}
		ifs.close();
		return true;
	}

	void Dictionary::store(const std::string &filename)
	{
		//生成字典文件
		std::ofstream ofs(filename+".dictionary", std::ios::out);
		//先序遍历字典树，写入字典文件
		word_tree_.printInPost(ofs);
		ofs.close();
	}

	void Dictionary::makeHeap()
	{
		std::ifstream ifs(filename_ + ".dictionary");
		if(!ifs)
		{
			std::cout << "Make heap fail, there is no dictionary file" << std::endl;
		}
		std::string word;
		std::string line;
		int times;
		while(std::getline(ifs, line))
		{
			std::istringstream ss(line);
			ss >> word >> times;
			most_occuring_words_.heapInsert(DictionaryItem(word,times));
		}
	}

	void Dictionary::wordsOuccMost(unsigned int n)
	{
		if(most_occuring_words_.size() == 0)
			makeHeap();
		DictionaryItem p;
		for(unsigned int i = 0; i < n; i++)
		{
			p = most_occuring_words_.heapPop();
			std::cout << p.word_ << " " << p.times_ << std::endl;
		}
	}
	bool Dictionary::wordStandardizing(std::string &word)
	{
		for(unsigned int i = 0; i < word.size(); i++)
		{
			if(isdigit(word[i]))	//是数字
			{
				return false;
			}
			else if(isupper(word[i]))	//大写转成小写
			{
				word[i] = tolower(word[i]);
			}
		}
		return true;
	}

	Dictionary::Heap::Heap()
	{
		heap_.reserve(INIT_SIZE);
	}
	Dictionary::Heap::~Heap() = default;

	void Dictionary::Heap::heapInsert(const DictionaryItem &item)
	{
		heap_.push_back(item);
		heapInsertSort();
	}
	void Dictionary::Heap::heapInsertSort()
	{
		unsigned int i = heap_.size()-1;
		while(i > 0)
		{
			if(heap_[i].times_ > heap_[(i-1)/2].times_)
			{
				std::swap(heap_[i], heap_[(i-1)/2]);
			}
			else
			{
				break;
			}
			i = (i-1)/2;
		}
	}
	Dictionary::DictionaryItem Dictionary::Heap::heapPop()
	{
		std::swap(heap_[0], heap_[heap_.size()-1]);	//交换顶和尾
		DictionaryItem p = heap_.back();
		heap_.erase(heap_.end()-1);
		heapPopSort();
		return p;
	}
	void Dictionary::Heap::heapPopSort()
	{
		unsigned int i = 0;
		while(i < heap_.size()/2)
		{
			if(i*2+2 <= heap_.size())	//存在两个子节点
			{
				if(heap_[2*i+1].times_ >= heap_[2*i+2].times_)
				{
					if(heap_[i].times_ < heap_[2*i+1].times_)
					{
						std::swap(heap_[i], heap_[2*i+1]);
						i = 2*i+1;
					}
					else
						break;
				}
				else
				{
					if(heap_[i].times_ < heap_[2*i+2].times_)
					{
						std::swap(heap_[i], heap_[2*i+2]);
						i = 2*i+2;
					}
					else
						break;
				}
			}
			else	//只有一个子节点
			{
				if(heap_[i].times_ < heap_[2*i+1].times_)
				{
					std::swap(heap_[i], heap_[2*i+1]);
				}
				break;
			}
		}
	}
	Dictionary::Trie::~Trie()
	{
		destroy(root_);
		delete root_;
	}
	void Dictionary::Trie::destroy(Node *root)
	{
		if(!root->end_)	//不是终端
		{
			for(unsigned int i = 0; i < 26; ++i)
				destroy(&root->child_[i]);
		}
		delete []root->child_;
	}
	void Dictionary::Trie::insert(const std::string &word)
	{
		Node *p = root_;
		for(unsigned int i = 0; i < word.size(); ++i)
		{
			//如果是终端点，则创建子节点
			//如果不是，则p向子节点移动
			if(p->end_)
			{
				p->end_ = false;
				p->child_ = new Node[26]();
				p = &p->child_[word[i] - 'a'];
			}
			else
			{
				p = &p->child_[word[i] - 'a'];
			}
		}
		p->times_++;
	}
	bool Dictionary::Trie::search(const std::string &word) const
	{
		Node *p = root_;
		for(unsigned int i = 0; i < word.size(); ++i)
		{
			if(p->end_)
				return false;
			else
				p = &p->child_[word[i]-'a'];
		}
		if(p->times_ > 0)
			return true;
		else
			return false;
	}
	std::ofstream & Dictionary::Trie::printInPost(std::ofstream &os) const
	{
		std::string output;
		postPrint(os, root_, output);
		return os;
	}
	std::ofstream & Dictionary::Trie::postPrint(std::ofstream &os, Node *root, std::string output) const
	{
		if(!root->end_)
		{
			static char c;
			for(unsigned int i = 0; i < 26; ++i)
			{
				c = 'a'+ i;
				if(root->child_[i].times_ > 0)	//单词出现了则打印
				{
					os << output << c <<  " " << root->child_[i].times_ << std::endl;
				}
				postPrint(os, &root->child_[i], output+c);	//否则继续先序遍历
			}
		}
		return os;
	}

}
