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

/*
判断对象申请在堆上还是栈上
原理：局部变量onstack放在程序的栈顶，由于栈的结构是向下扩展（趋向于低地址）；且堆地址低于栈地址（依赖于os）
	  当然无法详细区分静态数据和堆数据，两者都会返回True
*/
bool OnHeap(const char* address)
{
	char onstack;
	return address < &onstack;
}
#endif