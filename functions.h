/*
* common function, common algorithm
*/


#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <iostream>
#include <algorithm>
using namespace std;

//翻转字符串函数 如：“12345”翻转成“54321”
void reverse_by_swap(char* str, int n)
{
	char* begin = str;
	char* end = str + n - 1;
	while (begin < end)
	{
		char tmp = *begin;
		*begin = *end;
		*end = tmp;
		++begin;
		--end;
	}
}


//使用异或的方式交换	效率低
void reverse_by_xor(char* str, int n)
{
	char* begin = str;
	char* end = str + n - 1;
	while (begin < end)
	{
		*begin ^= *end;
		*end ^= *begin;
		*begin ^= *end;
		++begin;
		--end;
	}
}

//使用stl算法
void reverse_by_std(char* str, int n)
{
	std::reverse(str, str + n);
}

void test()
{
	char str[] = "12345abcdefg";
	reverse_by_swap(str, sizeof(str) - 1);
	cout << str << endl;
	reverse_by_xor(str, sizeof(str) - 1);
	cout << str << endl;
	reverse_by_std(str, sizeof(str) - 1);
	cout << str << endl;
}
#endif