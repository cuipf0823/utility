#ifndef UINT_TEST_H
#define UINT_TEST_H
#include <iostream>
#include "pool_memory.h"
#include "dcl_List.h"
#include "iterator.h"
#include "functions.h"

void TestInterator()
{
	ilist.insert_front(123);
	ilist.insert_front(23);
	ilist.insert_end(90);
	ilist.display();

	ulist.insert_end(8920);
	ulist.insert_front(7878);
	ulist.insert_end(666);
	ulist.insert_front(9090);
	ulist.display();

	strlist.insert_end("abc");
	strlist.insert_end("edf");
	strlist.insert_front("hhh");
	strlist.display();

	//iter = std::find(begin, end, 23);
}

void TestPoolMemory()
{
	const size_t kSize = 32;
	PoolMemory<char> pool;
	char* p_new = pool.Allocate(kSize);
	pool.Deallocate(p_new, kSize);

	dcl_list::ListBase<char, PoolMemory<char>> base;

}
void TestRevervse()
{
	char str[] = "12345abcdefg";
	reverse_by_swap(str, sizeof(str) - 1);
	std::cout << str << endl;
	reverse_by_xor(str, sizeof(str) - 1);
	std::cout << str << endl;
	reverse_by_std(str, sizeof(str) - 1);
	std::cout << str << endl;
}

void Test()
{
	TestInterator();
	TestPoolMemory();
	TestRevervse();
}

#endif