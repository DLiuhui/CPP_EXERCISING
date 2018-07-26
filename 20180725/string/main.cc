 ///
 /// @file    main.cc
 /// @author  LiuhuiDing@gmail.com
 /// @date    2018-07-25 21:52:56
 ///
 
#include "string.h"
#include <iostream>
#include <string>
#include <vector>
using std::cin;
using std::cout;
using std::endl;
 
int main()
{
	String str1;
	str1 = "Hello World";
	str1.print();
	cout << "1 "; str1.print_use();
	String str2("hahahahahah");
	str2.print();
	cout <<"2 "; str2.print_use();
	String str3(str1);
	str3.print();
	cout <<"3 "; str3.print_use();
	cout <<"1 "; str1.print_use();
	str1 = str2;
	str1.print();
	cout <<"1 "; str1.print_use();
	cout <<"2 "; str2.print_use();
	cout <<"3 "; str3.print_use();
	return 0;
}
