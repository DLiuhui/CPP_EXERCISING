 ///
 /// @file    io_iter.cc
 /// @author  LiuhuiDing@gmail.com
 /// @date    2018-07-25 16:48:43
 ///
 
#include <iostream>
#include <iterator>
#include <algorithm>
using std::cin;
using std::cout;
using std::endl;
using std::istream_iterator;
 
int main(int argc, char **argv)
{
	istream_iterator<int> int_it(cin);
	istream_iterator<int> eof;
	cout << std::accumulate(int_it, eof, 0) << endl;
	return 0;
}
