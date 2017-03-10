/*
*  记录一些常用的算法
*/
#ifndef COMMON_ALGORITHM_H
#define COMMON_ALGORITHM_H
#include <string>
#include <iostream>

namespace alg
{


void Swap(char* a, char* b)
{
	char temp = *a;
	*a = *b;
	*b = temp;
}

/*
http://wuchong.me/blog/2014/07/28/permutation-and-combination-realize/
*/
void Permutation(char* str, size_t begin, int length)
{
	if (begin == length - 1)
	{
		std::cout << str << std::endl;
	}
	else
	{
		for (int idx = 0; idx < length; ++idx)
		{
			Swap(&str[begin], &str[idx]);
			Permutation(str, begin + 1, length);
			Swap(&str[begin], &str[idx]);
		}
	}
}
void Permutation(char* str)
{
	if (str == nullptr)
	{
		return;
	}
	Permutation(str, 0, strlen(str));
}

void Test_Agl()
{
	const char* str = "123";
	Permutation(const_cast<char*>(str));
}


}
#endif