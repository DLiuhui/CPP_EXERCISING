 ///
 /// @file    main.cpp
 /// @author  LiuhuiDing@gmail.com
 /// @date    2018-07-24 11:52:50
 ///
 
#include <iostream>
#include "matrix.h"

template class Matrix<int>;

using std::cin;
using std::cout;
using std::endl;
 
int main(int argc, char **argv)
{
	Matrix<int> m;
	cout << m.numcols() << endl;
	cout << m.numrows() << endl;
	m.resize(8, 6);
	cout << m.numcols() << endl;
	cout << m.numrows() << endl;
	m.resize(5,5);
	cout << m.numcols() << endl;
	cout << m.numrows() << endl;
	return 0;
}
