/*
	³£¼û¼¸ÖÖÅÅÐòËã·¨ÊµÏÖ
*/
#ifndef COMMON_SORT_H
#define COMMON_SORT_H
#include <iostream>

//Êý×é´òÓ¡º¯Êý
void PrintArr(int arr[], int len)
{
	for (int i = 0; i < len; ++i)
	{
		std::cout << arr[i] << "\t";
	}
	std::cout << std::endl;
}

//Ã°ÅÝÅÅÐò ÏàÁÚÁ½¸öÔªËØ±È½Ï Ê±¼ä¸´ÔÓ¶È£º×î»µÊÇO(n^2)	×îºÃµÄÇé¿öÏÂO(n)
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

//Ö±ï¿½Ó²ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ã·¨ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Ç½ï¿½Ò»ï¿½ï¿½ï¿½ï¿½Â¼ï¿½ï¿½ï¿½ëµ½ï¿½Ñ¾ï¿½ï¿½Åºï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Ð£ï¿½ï¿½Ó¶ï¿½ï¿½Èµï¿½Ò»ï¿½ï¿½ï¿½ÂµÄ£ï¿½Ôªï¿½Ø¼ï¿½1ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ Öªï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½
//Ê±ï¿½ä¸´ï¿½Ó¶È£ï¿½ï¿½î»µï¿½ï¿½O(n^2)	ï¿½ï¿½Ãµï¿½ï¿½ï¿½ï¿½ï¿½ï¿½O(n)
void InsertSort(int* a, int len)
{
	int idx = 0;
	int temp = 0;
	for (int i = 1; i < len; ++i)
	{	
		temp = a[i];
		{
			a[idx + 1] = a[idx];
		}
		a[idx + 1] = temp;
	}
}

void TestSort()
{
	int arr[] = { 4, 10, 23, 90, 29, 78, 100, 66 };
	int len = sizeof(arr) / sizeof(arr[0]);
	BubbleSort(arr, len);
	PrintArr(arr, len);
	InsertSort(arr, len);
	PrintArr(arr, len);
}

#endif