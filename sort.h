/*
	�������������㷨ʵ��
*/
#ifndef COMMON_SORT_H
#define COMMON_SORT_H
#include <iostream>

//�����ӡ����
void PrintArr(int arr[], int len)
{
	for (int i = 0; i < len; ++i)
	{
		std::cout << arr[i] << "\t";
	}
	std::cout << std::endl;
}

//ð������ ��������Ԫ�رȽ� ʱ�临�Ӷȣ����O(n^2)	��õ������O(n)
void  BubbleSort(int* a, int len)
{
	for (int i = 0; i < len; ++i)
	{
		bool noswap = true;
		for (int j = 0; j < len - i - 1; ++j)
		{
			if (a[j] > a[j + 1])
			{
				int temp = a[j];
				a[j] = a[j + 1];
				a[j + 1] = temp;
				noswap = false;
			}
		}
		if (noswap)
		{
			break;
		}
	}
}

void TestSort()
{
	int arr[] = { 4, 10, 23, 90, 29, 78, 100, 66 };
	int len = sizeof(arr) / sizeof(arr[0]);
	BubbleSort(arr, len);
	PrintArr(arr, len);
}

#endif