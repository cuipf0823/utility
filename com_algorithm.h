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
*  输入字符串 打印字符串的全排序
*  例如: adc 则打印顺序为 abc acb bac bca cba cab
*/
void Permutation(char* str, char* begin)
{
	if (*begin == '\0')
	{
		std::cout << str << std::endl;
	}
	else
	{
		for (char* ch = begin; *ch != '\0'; ++ch)
		{
			if (*ch != *begin)
			{
				Swap(ch, begin);
			}
			Permutation(str, begin + 1);
			if (*ch != *begin)
			{
				Swap(ch, begin);
			}
		}
	}
}
void Permutation(char* str)
{
	if (str == nullptr)
	{
		return;
	}
	Permutation(str, str);
}

void Test_Agl()
{
	const char* str = "abcc";
	char* ch = new char[strlen(str) + 1];
	strcpy(ch, str);
	//这样传递是错的,你看到你传递指针是常量区的
	//Permutation(const_cast<char*>(str));
	Permutation(ch);
	delete[] ch;
}


}
#endif