/*
	常见几种排序算法实现
*/
#ifndef COMMON_SORT_H
#define COMMON_SORT_H
#include <iostream>

//数组打印函数
void PrintArr(int arr[], int len)
{
	for (int i = 0; i < len; ++i)
	{
		std::cout << arr[i] << "\t";
	}
	std::cout << std::endl;
}

void  BubbleSort(int* a, int len)
{
	PrintArr(a, len);
	bool noswap = true;
	for (int i = 0; i < len; ++i)
	{
// 		for (int j = 0; j < len - i; ++j)
// 		{
// 			if (a[j] > a[j + 1])
// 			{
// 				int temp = a[j];
// 				a[j] = a[j + 1];
// 				a[j + 1] = temp;
// 				noswap = false;
// 			}
// 		}
// 		if (noswap)
// 		{
// 			break;
// 		}
		PrintArr(a, len);
	}
}



void TestSort()
{
	int arr[] = { 10, 23, 4, 90, 29, 78, 100, 66 };
 	int len = sizeof(arr) / sizeof(arr[0]);
 	BubbleSort(arr, len);
 	PrintArr(arr, len);
	for (auto& element : arr)
	{
		std::cout << element << "\t";
	}
		

}

#endif