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

/*
*  数组中出现次数超过一半的数字
*  算法: 利用折半方法可以实现,但这里使用另外一种方式:
*  数组中有一个数字出现的次数比其他所有数字出现次数的和还要多,遍历数组保存两个值:
*  1. 数组中的一个数字;
*  2. 一个是次数
*  遍历时:如果和保存数字一样,次数 + 1;不同的话 -1;次数为0时候,更换保存数字,且次数=1
*  最后的结果:一定是把次数设置为1时对应的数字
*  时间复杂度: o(n)
*/
int MoreThanHalfNum(int* nums, int length)
{
	if (nums == nullptr || length <= 0)
	{
		return 0;
	}
	int temp_num = nums[0];
	int times = 1;
	for (int idx = 1; idx < length; ++idx)
	{
		if (temp_num == nums[idx])
		{
			++times;
		}
		else
		{
			if (times == 0)
			{
				temp_num = nums[idx];
				times = 1;
			}
			else
			{
				--times;
			}
		}
	}
	return temp_num;
}

#include <set>
multiset<int, greater<int> >
void Test_Agl()
{
	const char* str = "abcc";
	char* ch = new char[strlen(str) + 1];
	strcpy(ch, str);
	//这样传递是错的,你传递指针是常量区的
	//Permutation(const_cast<char*>(str));
	Permutation(ch);
	delete[] ch;

	int arrs[] = { 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2 };
	int length = sizeof(arrs) / sizeof(arrs[0]);
	std::cout << MoreThanHalfNum(arrs, length) << std::endl;
}


}
#endif
