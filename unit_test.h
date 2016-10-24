#ifndef UINT_TEST_H
#define UINT_TEST_H
#include <iostream>
#include "pool_memory.h"
#include "dcl_List.h"

void TestPoolMemory()
{
	const size_t kSize = 32;
	PoolMemory<char> pool;
	char* p_new = pool.Allocate(kSize);
	pool.Deallocate(p_new, kSize);

	dcl_list::ListBase<char, PoolMemory<char>> base;

}
#endif