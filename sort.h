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

//冒泡排序 相邻两个元素比较 时间复杂度：最坏是O(n^2)	最好的情况下O(n)
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

//直接插入排序算法 基本操作是将一个记录插入到已经排好序的有序表中，从而等到一个新的，元素加1的有序表 知道结束；
//时间复杂度：最坏是O(n^2)	最好的情况下O(n)
void InsertSort(int* a, int len)
{
	int idx = 0;
	int temp = 0;
	for (int i = 1; i < len; ++i)
	{	
		temp = a[i];
		for (idx = i - 1; idx >= 0 && a[idx] > temp; --idx)
		{
			a[idx + 1] = a[idx];
		}
		a[idx + 1] = temp;
	}
}

//选择排序算法
//原理:每次从乱序数组中找到最大（最小）的值，放在当前乱序数组头部，最终使数组有序
//复杂度：最坏O(0^2);
void SelectSort(int* a, int len)
{
	for (int i = 0; i < len; ++i)
	{
		int min = i;
		for (int j = i + 1; j < len; ++j)
		{
			if (a[j] < a[min])
			{
				min = j;
			}
		}
		int temp = a[i];
		a[i] = a[min];
		a[min] = temp;
	}
}

//shell排序  希尔排序是将数组按照一定步长分成几个子数组进行排序，通过逐渐缩短步长来完成最终排序
//时间复杂度：O(nlogn) ~~ O(n^2);
void ShellSort(int* a, int len)
{
	for (int gap = len >> 1; gap > 0; gap >>= 1)
	{
		for (int i = gap; i < len; ++i)
		{
			int temp = a[i];
			int j = i - gap;
			for (; j >= 0 && a[j] > temp; j -= gap)
			{
				a[j + gap] = a[j];
			}
			a[j + gap] = temp;
		}
	}
}

//归并排序 将一个数组打散成小数组，然后把小数组拼凑再排序知道数组有序
void MergeArray(int* nums, int begin, int mid, int end, int* temp)
{
	int lb = begin, rb = mid, tb = begin;
	while (lb != mid && rb != end)
	{
		if (nums[lb] < nums[rb])
		{
			temp[tb++] = nums[lb++];
		}
		else
		{
			temp[tb++] = nums[rb++];
		}
	}
	while (lb < mid)
	{
		temp[tb++] = nums[lb++];
	}
	while (rb < end)
	{
		temp[tb++] = nums[rb++];
	}

	for (int i = begin; i < end; i++)
	{
		nums[i] = temp[i];
	}
}

void MergeSort(int* nums, int begin, int end, int* temp)
{
	int mid = (begin + end) / 2;
	if (mid != begin) 
	{
		MergeSort(nums, begin, mid, temp);
		MergeSort(nums, mid, end, temp);
		MergeArray(nums, begin, mid, end, temp);
	}
}

void Swap(int& a, int& b)
{
	int temp = a;
	a = b;
	b = temp;
}

//快速排序 	选择一个基准数，把比这个数小的挪到左边 这个数大的移动到右边 然后不断对左右两边执行这个操作 知道数组有序
//时间复杂度：平均时间复杂度：O(nlog2n);
void QuickSort(int* nums, int begin, int end)
{
	if (begin < end - 1)
	{
		int lb = begin, rb = end - 1;
		while (lb < rb) 
		{
			while (nums[rb] >= nums[begin] && lb < rb)
			{
				rb--;
			}
			while (nums[lb] <= nums[begin] && lb < rb)
			{
				lb++;
			}
			Swap(nums[lb], nums[rb]);
		}
		Swap(nums[begin], nums[lb]);
		QuickSort(nums, begin, lb);
		QuickSort(nums, lb + 1, end);
	}
}

void TestSort()
{
	int arr[] = { 4, 10, 23, 90, 29, 78, 100, 66 };
	int len = sizeof(arr) / sizeof(arr[0]);
// 	BubbleSort(arr, len);
// 	PrintArr(arr, len);
 	QuickSort(arr, 0, len);
 	PrintArr(arr, len);
//	ShellSort(arr, len);
}

#endif