/*
*	常见几种排序算法实现
*	常见查找算法实现
*   常见的算法
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
//复杂度：最坏O(n^2);
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
		if (i != min)
		{
			int temp = a[i];
			a[i] = a[min];
			a[min] = temp;
		}
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

//快速排序 	选择一个基准数，把比这个数小的挪到左边 这个数大的移动到右边 然后不断对左右两边执行这个操作 直到数组有序
//时间复杂度：平均时间复杂度：O(nlog2n);
int Partition(int* nums, int low, int high);
void QuickSort(int* nums, int begin, int end)
{
	if (begin < end)
	{
		int key = Partition(nums, begin, end);
		QuickSort(nums, begin, key - 1);
		QuickSort(nums, key + 1, end);
	}
}
/*
*/
int Partition(int* nums, int low, int high)
{
	if (nums == nullptr || low >= high)
    {
        //input invaild
        return -1;
    }

    int guard = nums[low];
    while (low < high)
    {
        while (low < high && nums[high] >= guard)
        {
            --high;
        }
        if (low < high)
        {
            nums[low] = nums[high];
            ++low;
        }
        while (low < high && nums[low] < guard)
        {
            ++low;
        }
        if (low < high)
        {
            nums[high] = nums[low];
            --high;
        }
    }
	nums[low] = guard;
	return low;
}

void TestSort()
{
	int arr[] = { 4, 10, 23, 90, 29, 78, 100, 66 };
	int arr1[] = { 90, 29, 78, 100, 66, 4, 10, 23};
	int len = sizeof(arr) / sizeof(arr[0]);
// 	BubbleSort(arr, len);
// 	PrintArr(arr, len);
	QuickSort(arr, 0, len);
	QuickSort(arr1, 0, len);
 	PrintArr(arr, len);
//	ShellSort(arr, len);
}


/*
 * *************************************************************
 */

//常见查找算法

/*
 * 1. 顺序查找算法  无序查找，属于线性查找 从序列到一端开始一次遍历
 * 时间复杂度：O(n)
 */

int SequenceSearch(int arr[], int length, int value)
{
	int index = 0;
	for (int idx = 0; idx < length; ++idx)
	{
		if (arr[idx] == value)
		{
			return idx;
		}
	}
	return -1;
}

/*
 * 2. 二分查找算法（折半查找）
 * 思想：根据给定的值和序列的值对比，相等 找到；不等 再依次查找左右子序列；
 * 注意：1. 二分查找的序列必须为有序序列，如果是无序的话，先排序；
 * 		 2. 对于插入删除频繁的队列，维护有序队列成本较高，不建议使用；
 * 时间复杂度：最坏是：O(log2(n + 1)); 平均：O(log2n)
 */

int BinarySearch(int arr[], int length, int value)
{
	int mid = 0;
	int low = 0;
	int high = length - 1;
	while (low < high)
	{
		mid = (low + high) / 2;
		if (arr[mid] == value)
		{
			return mid;
		}
		else if (arr[mid] < value)
		{
			low = mid + 1;
		}
		else
		{
			high = mid - 1;
		}
	}
	return -1;
}

int BinarySearchRe(int arr[], int low, int high, int value)
{
	if (low < high)
	{
		return -1;
	}

	int mid = (low + high) / 2;
	if (arr[mid] == value)
	{
		return mid;
	}
	else if (arr[mid] < value)
	{
		return BinarySearchRe(arr, mid + 1, high, value);
	}
	else
	{
		return BinarySearchRe(arr,  low,  mid - 1, value);
	}
}

/*
*	3. 插值查找算法
*   思想：基于二分查找算法，根据查找点在序列中的大概位置，将查找点修改为自适应的，提高查找效率；
*	注: 对于表长较大，而且元素分布比较均匀的表来说，该算法平均性能比二分查找要好很多，反之，不一定合适
*	时间复杂度：查找成功或者失败的时间复杂度均为O(log2(log2n))
*/
int InsertionSearch(int arr[], int length, int value)
{
	int mid = 0;
	int low = 0;
	int high = length - 1;
	while (low < high)
	{
		mid = low + (value - arr[low]) / (arr[high] - arr[low])*(high - low);
		if (arr[mid] == value)
		{
			return mid;
		}
		else if (arr[mid] < value)
		{
			low = mid + 1;
		}
		else
		{
			high = mid - 1;
		}
	}
	return -1;
}

void TestSearch()
{
	int arr[] = { 4, 10, 23, 29, 78, 100, 166 };
	int len = sizeof(arr) / sizeof(arr[0]);
	std::cout << SequenceSearch(arr, len, 29) << std::endl;
	std::cout << BinarySearch(arr, len, 29) << std::endl;
	std::cout << BinarySearchRe(arr, 0, len - 1, 299) << std::endl;
	std::cout << InsertionSearch(arr, len, 29) << std::endl;
}


/**
 *	斐波那契数组的计算迭代方式
 *  效率低
 */
long long FabonnacciRe(uint32_t n)
{
	if (n <= 1)
	{
		return n;
	}
	return FabonnacciRe(n - 1) + FabonnacciRe(n - 2);
}

long long Fabonnacci(uint32_t n)
{
	if (n <= 1)
	{
		return n;
	}
	long long fib_minus_one = 1;
	long long fib_minus_two = 2;
	long long fib_n = 0;
	for (int index = 2; index <= n; ++index)
	{
		fib_n = fib_minus_one + fib_minus_two;
		fib_minus_two = fib_minus_one;
		fib_minus_one = fib_n;
	}
	return fib_n;
}

#endif