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



/*
* 求数值的整数次方
* 注意；1. double、float判断和0相等的方式；
*      2. 注意考虑base为0的情况；
*      3. 注意考虑exponent为负数的情况
*/
double PowerWithUnsignedExponent(double base, int exponent)
{
	double result = 1.0;
	for (int idx = 0; idx < exponent; ++idx)
	{
		result *= base;
	}
	return result;
}

/*
* 数值整数次方的优化方式
*/
double PowerUnsignedExpOptimize(double base, int exponent)
{
	if (exponent == 0)
	{
		return 1.0;
	}
	if (exponent == 1)
	{
		return base;
	}
	double result = PowerWithUnsignedExponent(base, exponent >> 1);
	result *= result;
	if (exponent & 0x1 == 1)
	{
		result *= base;
	}
	return result;
}

double Power(double base, int exponent)
{
	if ((base - 0.00 > -0.00000001) && (base - 0.00 < 0.0000001))
	{
		return base;
	}
	if (exponent >= 0)
	{
		return PowerWithUnsignedExponent(base, exponent);
	}
	else
	{
		unsigned int abs_exponent = static_cast<unsigned int>(-exponent);
		return 1.0 / PowerWithUnsignedExponent(base, abs_exponent);
	}
}


//测试
void TestFunc()
{
	std::cout << Power(2.0, 4) << std::endl;
	std::cout << Power(0.0, -2) << std::endl;
	std::cout << Power(3.0, -2) << std::endl;

}
#endif