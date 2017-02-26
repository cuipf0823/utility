#ifndef UINT_TEST_H
#define UINT_TEST_H
#include <iostream>
#include "pool_memory.h"
#include "dcl_List.h"
#include "iterator.h"
#include "functions.h"
#include "lru_cache.h"
#include "sort.h"
#include "list_op.h"
#include "tree_op.h"

void TestInterator()
{
	iterator_test::List<int> ilist;
	ilist.insert_front(123);
	ilist.insert_front(23);
	ilist.insert_end(90);
	ilist.display();

	iterator_test::List<unsigned int> ulist;
	ulist.insert_end(8920);
	ulist.insert_front(7878);
	ulist.insert_end(666);
	ulist.insert_front(9090);
	ulist.display();

	iterator_test::List<std::string> strlist;
	strlist.insert_end("abc");
	strlist.insert_end("edf");
	strlist.insert_front("hhh");
	strlist.display();

	iterator_test::ListIter<iterator_test::ListItem<int>> begin(ilist.front());
	iterator_test::ListIter<iterator_test::ListItem<int>> end;
	iterator_test::ListIter<iterator_test::ListItem<int>> iter;
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
	std::cout << str << std::endl;
	reverse_by_xor(str, sizeof(str) - 1);
	std::cout << str << std::endl;
	reverse_by_std(str, sizeof(str) - 1);
	std::cout << str << std::endl;
}

void TestLRU()
{
	LRU::SharedLRUCache<int, int> cache(20);
	cache.Debug();
	auto* handle1 = cache.Insert(100, 200);
	auto* handle2 = cache.Insert(200, 300);
	cache.Debug();
	cache.Release(handle1);
	cache.Release(handle2);
	cache.Debug();
	auto* handle3 = cache.Insert(100, 200);
	auto* handle4 = cache.Insert(200, 300);
	cache.Debug();
	auto* finder = cache.LookUp(100);
	std::cout << finder->value << std::endl;
	cache.Release(handle3);
	cache.Release(handle4);
	cache.Release(finder);
	cache.Erase(100);
	cache.Debug();
	//cache.Prune();
	//cache.Debug();
}

void Test()
{
	TestInterator();
	TestPoolMemory();
	TestRevervse();
	std::cout << "=================================" << std::endl;
	TestLRU();
	std::cout << "=================================" << std::endl;
	TestSort();
    TestSearch();
	std::cout << "=================================" << std::endl;
	TestFunc();
	std::cout << "=================================" << std::endl;
    TestListOP();
    std::cout << "=================================" << std::endl;
    TestTreeOP();
}

#endif